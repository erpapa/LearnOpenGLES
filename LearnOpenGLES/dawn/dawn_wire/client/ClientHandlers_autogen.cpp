
#include "common/Assert.h"
#include "dawn_wire/client/Client.h"

#include <string>

namespace dawn_wire { namespace client {
    bool Client::HandleBufferMapAsyncCallback(const volatile char** commands, size_t* size) {
        ReturnBufferMapAsyncCallbackCmd cmd;
        DeserializeResult deserializeResult = cmd.Deserialize(commands, size, &mAllocator);

        if (deserializeResult == DeserializeResult::FatalError) {
            return false;
        }


        Buffer* buffer = BufferAllocator().GetObject(cmd.buffer.id);
        uint32_t bufferGeneration = BufferAllocator().GetGeneration(cmd.buffer.id);
        if (bufferGeneration != cmd.buffer.generation) {
            buffer = nullptr;
        }

        return DoBufferMapAsyncCallback(buffer, cmd.requestSerial, cmd.status, cmd.readInitialDataInfoLength, cmd.readInitialDataInfo);
    }
    bool Client::HandleDeviceCreateReadyComputePipelineCallback(const volatile char** commands, size_t* size) {
        ReturnDeviceCreateReadyComputePipelineCallbackCmd cmd;
        DeserializeResult deserializeResult = cmd.Deserialize(commands, size, &mAllocator);

        if (deserializeResult == DeserializeResult::FatalError) {
            return false;
        }


        return DoDeviceCreateReadyComputePipelineCallback(cmd.requestSerial, cmd.status, cmd.message);
    }
    bool Client::HandleDeviceCreateReadyRenderPipelineCallback(const volatile char** commands, size_t* size) {
        ReturnDeviceCreateReadyRenderPipelineCallbackCmd cmd;
        DeserializeResult deserializeResult = cmd.Deserialize(commands, size, &mAllocator);

        if (deserializeResult == DeserializeResult::FatalError) {
            return false;
        }


        return DoDeviceCreateReadyRenderPipelineCallback(cmd.requestSerial, cmd.status, cmd.message);
    }
    bool Client::HandleDeviceLostCallback(const volatile char** commands, size_t* size) {
        ReturnDeviceLostCallbackCmd cmd;
        DeserializeResult deserializeResult = cmd.Deserialize(commands, size, &mAllocator);

        if (deserializeResult == DeserializeResult::FatalError) {
            return false;
        }


        return DoDeviceLostCallback(cmd.message);
    }
    bool Client::HandleDevicePopErrorScopeCallback(const volatile char** commands, size_t* size) {
        ReturnDevicePopErrorScopeCallbackCmd cmd;
        DeserializeResult deserializeResult = cmd.Deserialize(commands, size, &mAllocator);

        if (deserializeResult == DeserializeResult::FatalError) {
            return false;
        }


        return DoDevicePopErrorScopeCallback(cmd.requestSerial, cmd.type, cmd.message);
    }
    bool Client::HandleDeviceUncapturedErrorCallback(const volatile char** commands, size_t* size) {
        ReturnDeviceUncapturedErrorCallbackCmd cmd;
        DeserializeResult deserializeResult = cmd.Deserialize(commands, size, &mAllocator);

        if (deserializeResult == DeserializeResult::FatalError) {
            return false;
        }


        return DoDeviceUncapturedErrorCallback(cmd.type, cmd.message);
    }
    bool Client::HandleFenceOnCompletionCallback(const volatile char** commands, size_t* size) {
        ReturnFenceOnCompletionCallbackCmd cmd;
        DeserializeResult deserializeResult = cmd.Deserialize(commands, size, &mAllocator);

        if (deserializeResult == DeserializeResult::FatalError) {
            return false;
        }


        Fence* fence = FenceAllocator().GetObject(cmd.fence.id);
        uint32_t fenceGeneration = FenceAllocator().GetGeneration(cmd.fence.id);
        if (fenceGeneration != cmd.fence.generation) {
            fence = nullptr;
        }

        return DoFenceOnCompletionCallback(fence, cmd.requestSerial, cmd.status);
    }
    bool Client::HandleFenceUpdateCompletedValue(const volatile char** commands, size_t* size) {
        ReturnFenceUpdateCompletedValueCmd cmd;
        DeserializeResult deserializeResult = cmd.Deserialize(commands, size, &mAllocator);

        if (deserializeResult == DeserializeResult::FatalError) {
            return false;
        }


        Fence* fence = FenceAllocator().GetObject(cmd.fence.id);
        uint32_t fenceGeneration = FenceAllocator().GetGeneration(cmd.fence.id);
        if (fenceGeneration != cmd.fence.generation) {
            fence = nullptr;
        }

        return DoFenceUpdateCompletedValue(fence, cmd.value);
    }

    const volatile char* Client::HandleCommandsImpl(const volatile char* commands, size_t size) {
        while (size >= sizeof(CmdHeader) + sizeof(ReturnWireCmd)) {
            // Start by chunked command handling, if it is done, then it means the whole buffer
            // was consumed by it, so we return a pointer to the end of the commands.
            switch (HandleChunkedCommands(commands, size)) {
                case ChunkedCommandsResult::Consumed:
                    return commands + size;
                case ChunkedCommandsResult::Error:
                    return nullptr;
                case ChunkedCommandsResult::Passthrough:
                    break;
            }

            ReturnWireCmd cmdId = *reinterpret_cast<const volatile ReturnWireCmd*>(commands + sizeof(CmdHeader));
            bool success = false;
            switch (cmdId) {
                case ReturnWireCmd::BufferMapAsyncCallback:
                    success = HandleBufferMapAsyncCallback(&commands, &size);
                    break;
                case ReturnWireCmd::DeviceCreateReadyComputePipelineCallback:
                    success = HandleDeviceCreateReadyComputePipelineCallback(&commands, &size);
                    break;
                case ReturnWireCmd::DeviceCreateReadyRenderPipelineCallback:
                    success = HandleDeviceCreateReadyRenderPipelineCallback(&commands, &size);
                    break;
                case ReturnWireCmd::DeviceLostCallback:
                    success = HandleDeviceLostCallback(&commands, &size);
                    break;
                case ReturnWireCmd::DevicePopErrorScopeCallback:
                    success = HandleDevicePopErrorScopeCallback(&commands, &size);
                    break;
                case ReturnWireCmd::DeviceUncapturedErrorCallback:
                    success = HandleDeviceUncapturedErrorCallback(&commands, &size);
                    break;
                case ReturnWireCmd::FenceOnCompletionCallback:
                    success = HandleFenceOnCompletionCallback(&commands, &size);
                    break;
                case ReturnWireCmd::FenceUpdateCompletedValue:
                    success = HandleFenceUpdateCompletedValue(&commands, &size);
                    break;
                default:
                    success = false;
            }

            if (!success) {
                return nullptr;
            }
            mAllocator.Reset();
        }

        if (size != 0) {
            return nullptr;
        }

        return commands;
    }
}}  // namespace dawn_wire::client
