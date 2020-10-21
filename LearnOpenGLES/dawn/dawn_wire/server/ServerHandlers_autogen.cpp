
#include "common/Assert.h"
#include "dawn_wire/server/Server.h"

namespace dawn_wire { namespace server {

    bool Server::HandleBufferDestroy(const volatile char** commands, size_t* size) {
        BufferDestroyCmd cmd;
        DeserializeResult deserializeResult = cmd.Deserialize(commands, size, &mAllocator, *this);

        if (deserializeResult == DeserializeResult::FatalError) {
            return false;
        }

        if (!PreHandleBufferDestroy(cmd)) {
            return false;
        }

        bool success = DoBufferDestroy(cmd.self);

        if (!success) {
            return false;
        }
        return true;
    }

    bool Server::HandleBufferMapAsync(const volatile char** commands, size_t* size) {
        BufferMapAsyncCmd cmd;
        DeserializeResult deserializeResult = cmd.Deserialize(commands, size, &mAllocator);

        if (deserializeResult == DeserializeResult::FatalError) {
            return false;
        }


        bool success = DoBufferMapAsync(cmd.bufferId, cmd.requestSerial, cmd.mode, cmd.offset, cmd.size, cmd.handleCreateInfoLength, cmd.handleCreateInfo);

        if (!success) {
            return false;
        }
        return true;
    }

    bool Server::HandleBufferUnmap(const volatile char** commands, size_t* size) {
        BufferUnmapCmd cmd;
        DeserializeResult deserializeResult = cmd.Deserialize(commands, size, &mAllocator, *this);

        if (deserializeResult == DeserializeResult::FatalError) {
            return false;
        }

        if (!PreHandleBufferUnmap(cmd)) {
            return false;
        }

        bool success = DoBufferUnmap(cmd.self);

        if (!success) {
            return false;
        }
        return true;
    }

    bool Server::HandleBufferUpdateMappedData(const volatile char** commands, size_t* size) {
        BufferUpdateMappedDataCmd cmd;
        DeserializeResult deserializeResult = cmd.Deserialize(commands, size, &mAllocator);

        if (deserializeResult == DeserializeResult::FatalError) {
            return false;
        }


        bool success = DoBufferUpdateMappedData(cmd.bufferId, cmd.writeFlushInfoLength, cmd.writeFlushInfo);

        if (!success) {
            return false;
        }
        return true;
    }

    bool Server::HandleCommandEncoderBeginComputePass(const volatile char** commands, size_t* size) {
        CommandEncoderBeginComputePassCmd cmd;
        DeserializeResult deserializeResult = cmd.Deserialize(commands, size, &mAllocator, *this);

        if (deserializeResult == DeserializeResult::FatalError) {
            return false;
        }



        auto* resultData = ComputePassEncoderObjects().Allocate(cmd.result.id);
        if (resultData == nullptr) {
            return false;
        }
        resultData->generation = cmd.result.generation;

        bool success = DoCommandEncoderBeginComputePass(cmd.self, cmd.descriptor, &resultData->handle);

        if (!success) {
            return false;
        }

        return true;
    }

    bool Server::HandleCommandEncoderBeginRenderPass(const volatile char** commands, size_t* size) {
        CommandEncoderBeginRenderPassCmd cmd;
        DeserializeResult deserializeResult = cmd.Deserialize(commands, size, &mAllocator, *this);

        if (deserializeResult == DeserializeResult::FatalError) {
            return false;
        }



        auto* resultData = RenderPassEncoderObjects().Allocate(cmd.result.id);
        if (resultData == nullptr) {
            return false;
        }
        resultData->generation = cmd.result.generation;

        bool success = DoCommandEncoderBeginRenderPass(cmd.self, cmd.descriptor, &resultData->handle);

        if (!success) {
            return false;
        }

        return true;
    }

    bool Server::HandleCommandEncoderCopyBufferToBuffer(const volatile char** commands, size_t* size) {
        CommandEncoderCopyBufferToBufferCmd cmd;
        DeserializeResult deserializeResult = cmd.Deserialize(commands, size, &mAllocator, *this);

        if (deserializeResult == DeserializeResult::FatalError) {
            return false;
        }


        bool success = DoCommandEncoderCopyBufferToBuffer(cmd.self, cmd.source, cmd.sourceOffset, cmd.destination, cmd.destinationOffset, cmd.size);

        if (!success) {
            return false;
        }
        return true;
    }

    bool Server::HandleCommandEncoderCopyBufferToTexture(const volatile char** commands, size_t* size) {
        CommandEncoderCopyBufferToTextureCmd cmd;
        DeserializeResult deserializeResult = cmd.Deserialize(commands, size, &mAllocator, *this);

        if (deserializeResult == DeserializeResult::FatalError) {
            return false;
        }


        bool success = DoCommandEncoderCopyBufferToTexture(cmd.self, cmd.source, cmd.destination, cmd.copySize);

        if (!success) {
            return false;
        }
        return true;
    }

    bool Server::HandleCommandEncoderCopyTextureToBuffer(const volatile char** commands, size_t* size) {
        CommandEncoderCopyTextureToBufferCmd cmd;
        DeserializeResult deserializeResult = cmd.Deserialize(commands, size, &mAllocator, *this);

        if (deserializeResult == DeserializeResult::FatalError) {
            return false;
        }


        bool success = DoCommandEncoderCopyTextureToBuffer(cmd.self, cmd.source, cmd.destination, cmd.copySize);

        if (!success) {
            return false;
        }
        return true;
    }

    bool Server::HandleCommandEncoderCopyTextureToTexture(const volatile char** commands, size_t* size) {
        CommandEncoderCopyTextureToTextureCmd cmd;
        DeserializeResult deserializeResult = cmd.Deserialize(commands, size, &mAllocator, *this);

        if (deserializeResult == DeserializeResult::FatalError) {
            return false;
        }


        bool success = DoCommandEncoderCopyTextureToTexture(cmd.self, cmd.source, cmd.destination, cmd.copySize);

        if (!success) {
            return false;
        }
        return true;
    }

    bool Server::HandleCommandEncoderFinish(const volatile char** commands, size_t* size) {
        CommandEncoderFinishCmd cmd;
        DeserializeResult deserializeResult = cmd.Deserialize(commands, size, &mAllocator, *this);

        if (deserializeResult == DeserializeResult::FatalError) {
            return false;
        }



        auto* resultData = CommandBufferObjects().Allocate(cmd.result.id);
        if (resultData == nullptr) {
            return false;
        }
        resultData->generation = cmd.result.generation;

        bool success = DoCommandEncoderFinish(cmd.self, cmd.descriptor, &resultData->handle);

        if (!success) {
            return false;
        }

        return true;
    }

    bool Server::HandleCommandEncoderInsertDebugMarker(const volatile char** commands, size_t* size) {
        CommandEncoderInsertDebugMarkerCmd cmd;
        DeserializeResult deserializeResult = cmd.Deserialize(commands, size, &mAllocator, *this);

        if (deserializeResult == DeserializeResult::FatalError) {
            return false;
        }


        bool success = DoCommandEncoderInsertDebugMarker(cmd.self, cmd.markerLabel);

        if (!success) {
            return false;
        }
        return true;
    }

    bool Server::HandleCommandEncoderPopDebugGroup(const volatile char** commands, size_t* size) {
        CommandEncoderPopDebugGroupCmd cmd;
        DeserializeResult deserializeResult = cmd.Deserialize(commands, size, &mAllocator, *this);

        if (deserializeResult == DeserializeResult::FatalError) {
            return false;
        }


        bool success = DoCommandEncoderPopDebugGroup(cmd.self);

        if (!success) {
            return false;
        }
        return true;
    }

    bool Server::HandleCommandEncoderPushDebugGroup(const volatile char** commands, size_t* size) {
        CommandEncoderPushDebugGroupCmd cmd;
        DeserializeResult deserializeResult = cmd.Deserialize(commands, size, &mAllocator, *this);

        if (deserializeResult == DeserializeResult::FatalError) {
            return false;
        }


        bool success = DoCommandEncoderPushDebugGroup(cmd.self, cmd.groupLabel);

        if (!success) {
            return false;
        }
        return true;
    }

    bool Server::HandleCommandEncoderResolveQuerySet(const volatile char** commands, size_t* size) {
        CommandEncoderResolveQuerySetCmd cmd;
        DeserializeResult deserializeResult = cmd.Deserialize(commands, size, &mAllocator, *this);

        if (deserializeResult == DeserializeResult::FatalError) {
            return false;
        }


        bool success = DoCommandEncoderResolveQuerySet(cmd.self, cmd.querySet, cmd.firstQuery, cmd.queryCount, cmd.destination, cmd.destinationOffset);

        if (!success) {
            return false;
        }
        return true;
    }

    bool Server::HandleCommandEncoderWriteTimestamp(const volatile char** commands, size_t* size) {
        CommandEncoderWriteTimestampCmd cmd;
        DeserializeResult deserializeResult = cmd.Deserialize(commands, size, &mAllocator, *this);

        if (deserializeResult == DeserializeResult::FatalError) {
            return false;
        }


        bool success = DoCommandEncoderWriteTimestamp(cmd.self, cmd.querySet, cmd.queryIndex);

        if (!success) {
            return false;
        }
        return true;
    }

    bool Server::HandleComputePassEncoderDispatch(const volatile char** commands, size_t* size) {
        ComputePassEncoderDispatchCmd cmd;
        DeserializeResult deserializeResult = cmd.Deserialize(commands, size, &mAllocator, *this);

        if (deserializeResult == DeserializeResult::FatalError) {
            return false;
        }


        bool success = DoComputePassEncoderDispatch(cmd.self, cmd.x, cmd.y, cmd.z);

        if (!success) {
            return false;
        }
        return true;
    }

    bool Server::HandleComputePassEncoderDispatchIndirect(const volatile char** commands, size_t* size) {
        ComputePassEncoderDispatchIndirectCmd cmd;
        DeserializeResult deserializeResult = cmd.Deserialize(commands, size, &mAllocator, *this);

        if (deserializeResult == DeserializeResult::FatalError) {
            return false;
        }


        bool success = DoComputePassEncoderDispatchIndirect(cmd.self, cmd.indirectBuffer, cmd.indirectOffset);

        if (!success) {
            return false;
        }
        return true;
    }

    bool Server::HandleComputePassEncoderEndPass(const volatile char** commands, size_t* size) {
        ComputePassEncoderEndPassCmd cmd;
        DeserializeResult deserializeResult = cmd.Deserialize(commands, size, &mAllocator, *this);

        if (deserializeResult == DeserializeResult::FatalError) {
            return false;
        }


        bool success = DoComputePassEncoderEndPass(cmd.self);

        if (!success) {
            return false;
        }
        return true;
    }

    bool Server::HandleComputePassEncoderInsertDebugMarker(const volatile char** commands, size_t* size) {
        ComputePassEncoderInsertDebugMarkerCmd cmd;
        DeserializeResult deserializeResult = cmd.Deserialize(commands, size, &mAllocator, *this);

        if (deserializeResult == DeserializeResult::FatalError) {
            return false;
        }


        bool success = DoComputePassEncoderInsertDebugMarker(cmd.self, cmd.markerLabel);

        if (!success) {
            return false;
        }
        return true;
    }

    bool Server::HandleComputePassEncoderPopDebugGroup(const volatile char** commands, size_t* size) {
        ComputePassEncoderPopDebugGroupCmd cmd;
        DeserializeResult deserializeResult = cmd.Deserialize(commands, size, &mAllocator, *this);

        if (deserializeResult == DeserializeResult::FatalError) {
            return false;
        }


        bool success = DoComputePassEncoderPopDebugGroup(cmd.self);

        if (!success) {
            return false;
        }
        return true;
    }

    bool Server::HandleComputePassEncoderPushDebugGroup(const volatile char** commands, size_t* size) {
        ComputePassEncoderPushDebugGroupCmd cmd;
        DeserializeResult deserializeResult = cmd.Deserialize(commands, size, &mAllocator, *this);

        if (deserializeResult == DeserializeResult::FatalError) {
            return false;
        }


        bool success = DoComputePassEncoderPushDebugGroup(cmd.self, cmd.groupLabel);

        if (!success) {
            return false;
        }
        return true;
    }

    bool Server::HandleComputePassEncoderSetBindGroup(const volatile char** commands, size_t* size) {
        ComputePassEncoderSetBindGroupCmd cmd;
        DeserializeResult deserializeResult = cmd.Deserialize(commands, size, &mAllocator, *this);

        if (deserializeResult == DeserializeResult::FatalError) {
            return false;
        }


        bool success = DoComputePassEncoderSetBindGroup(cmd.self, cmd.groupIndex, cmd.group, cmd.dynamicOffsetCount, cmd.dynamicOffsets);

        if (!success) {
            return false;
        }
        return true;
    }

    bool Server::HandleComputePassEncoderSetPipeline(const volatile char** commands, size_t* size) {
        ComputePassEncoderSetPipelineCmd cmd;
        DeserializeResult deserializeResult = cmd.Deserialize(commands, size, &mAllocator, *this);

        if (deserializeResult == DeserializeResult::FatalError) {
            return false;
        }


        bool success = DoComputePassEncoderSetPipeline(cmd.self, cmd.pipeline);

        if (!success) {
            return false;
        }
        return true;
    }

    bool Server::HandleComputePassEncoderWriteTimestamp(const volatile char** commands, size_t* size) {
        ComputePassEncoderWriteTimestampCmd cmd;
        DeserializeResult deserializeResult = cmd.Deserialize(commands, size, &mAllocator, *this);

        if (deserializeResult == DeserializeResult::FatalError) {
            return false;
        }


        bool success = DoComputePassEncoderWriteTimestamp(cmd.self, cmd.querySet, cmd.queryIndex);

        if (!success) {
            return false;
        }
        return true;
    }

    bool Server::HandleComputePipelineGetBindGroupLayout(const volatile char** commands, size_t* size) {
        ComputePipelineGetBindGroupLayoutCmd cmd;
        DeserializeResult deserializeResult = cmd.Deserialize(commands, size, &mAllocator, *this);

        if (deserializeResult == DeserializeResult::FatalError) {
            return false;
        }



        auto* resultData = BindGroupLayoutObjects().Allocate(cmd.result.id);
        if (resultData == nullptr) {
            return false;
        }
        resultData->generation = cmd.result.generation;

        bool success = DoComputePipelineGetBindGroupLayout(cmd.self, cmd.groupIndex, &resultData->handle);

        if (!success) {
            return false;
        }

        return true;
    }

    bool Server::HandleDestroyObject(const volatile char** commands, size_t* size) {
        DestroyObjectCmd cmd;
        DeserializeResult deserializeResult = cmd.Deserialize(commands, size, &mAllocator);

        if (deserializeResult == DeserializeResult::FatalError) {
            return false;
        }


        bool success = DoDestroyObject(cmd.objectType, cmd.objectId);

        if (!success) {
            return false;
        }
        return true;
    }

    bool Server::HandleDeviceCreateBindGroup(const volatile char** commands, size_t* size) {
        DeviceCreateBindGroupCmd cmd;
        DeserializeResult deserializeResult = cmd.Deserialize(commands, size, &mAllocator, *this);

        if (deserializeResult == DeserializeResult::FatalError) {
            return false;
        }



        auto* resultData = BindGroupObjects().Allocate(cmd.result.id);
        if (resultData == nullptr) {
            return false;
        }
        resultData->generation = cmd.result.generation;

        bool success = DoDeviceCreateBindGroup(cmd.self, cmd.descriptor, &resultData->handle);

        if (!success) {
            return false;
        }

        return true;
    }

    bool Server::HandleDeviceCreateBindGroupLayout(const volatile char** commands, size_t* size) {
        DeviceCreateBindGroupLayoutCmd cmd;
        DeserializeResult deserializeResult = cmd.Deserialize(commands, size, &mAllocator, *this);

        if (deserializeResult == DeserializeResult::FatalError) {
            return false;
        }



        auto* resultData = BindGroupLayoutObjects().Allocate(cmd.result.id);
        if (resultData == nullptr) {
            return false;
        }
        resultData->generation = cmd.result.generation;

        bool success = DoDeviceCreateBindGroupLayout(cmd.self, cmd.descriptor, &resultData->handle);

        if (!success) {
            return false;
        }

        return true;
    }

    bool Server::HandleDeviceCreateBuffer(const volatile char** commands, size_t* size) {
        DeviceCreateBufferCmd cmd;
        DeserializeResult deserializeResult = cmd.Deserialize(commands, size, &mAllocator, *this);

        if (deserializeResult == DeserializeResult::FatalError) {
            return false;
        }


        bool success = DoDeviceCreateBuffer(cmd.device, cmd.descriptor, cmd.result, cmd.handleCreateInfoLength, cmd.handleCreateInfo);

        if (!success) {
            return false;
        }
        return true;
    }

    bool Server::HandleDeviceCreateCommandEncoder(const volatile char** commands, size_t* size) {
        DeviceCreateCommandEncoderCmd cmd;
        DeserializeResult deserializeResult = cmd.Deserialize(commands, size, &mAllocator, *this);

        if (deserializeResult == DeserializeResult::FatalError) {
            return false;
        }



        auto* resultData = CommandEncoderObjects().Allocate(cmd.result.id);
        if (resultData == nullptr) {
            return false;
        }
        resultData->generation = cmd.result.generation;

        bool success = DoDeviceCreateCommandEncoder(cmd.self, cmd.descriptor, &resultData->handle);

        if (!success) {
            return false;
        }

        return true;
    }

    bool Server::HandleDeviceCreateComputePipeline(const volatile char** commands, size_t* size) {
        DeviceCreateComputePipelineCmd cmd;
        DeserializeResult deserializeResult = cmd.Deserialize(commands, size, &mAllocator, *this);

        if (deserializeResult == DeserializeResult::FatalError) {
            return false;
        }



        auto* resultData = ComputePipelineObjects().Allocate(cmd.result.id);
        if (resultData == nullptr) {
            return false;
        }
        resultData->generation = cmd.result.generation;

        bool success = DoDeviceCreateComputePipeline(cmd.self, cmd.descriptor, &resultData->handle);

        if (!success) {
            return false;
        }

        return true;
    }

    bool Server::HandleDeviceCreateErrorBuffer(const volatile char** commands, size_t* size) {
        DeviceCreateErrorBufferCmd cmd;
        DeserializeResult deserializeResult = cmd.Deserialize(commands, size, &mAllocator, *this);

        if (deserializeResult == DeserializeResult::FatalError) {
            return false;
        }



        auto* resultData = BufferObjects().Allocate(cmd.result.id);
        if (resultData == nullptr) {
            return false;
        }
        resultData->generation = cmd.result.generation;

        bool success = DoDeviceCreateErrorBuffer(cmd.self, &resultData->handle);

        if (!success) {
            return false;
        }

        return true;
    }

    bool Server::HandleDeviceCreatePipelineLayout(const volatile char** commands, size_t* size) {
        DeviceCreatePipelineLayoutCmd cmd;
        DeserializeResult deserializeResult = cmd.Deserialize(commands, size, &mAllocator, *this);

        if (deserializeResult == DeserializeResult::FatalError) {
            return false;
        }



        auto* resultData = PipelineLayoutObjects().Allocate(cmd.result.id);
        if (resultData == nullptr) {
            return false;
        }
        resultData->generation = cmd.result.generation;

        bool success = DoDeviceCreatePipelineLayout(cmd.self, cmd.descriptor, &resultData->handle);

        if (!success) {
            return false;
        }

        return true;
    }

    bool Server::HandleDeviceCreateQuerySet(const volatile char** commands, size_t* size) {
        DeviceCreateQuerySetCmd cmd;
        DeserializeResult deserializeResult = cmd.Deserialize(commands, size, &mAllocator, *this);

        if (deserializeResult == DeserializeResult::FatalError) {
            return false;
        }



        auto* resultData = QuerySetObjects().Allocate(cmd.result.id);
        if (resultData == nullptr) {
            return false;
        }
        resultData->generation = cmd.result.generation;

        bool success = DoDeviceCreateQuerySet(cmd.self, cmd.descriptor, &resultData->handle);

        if (!success) {
            return false;
        }

        return true;
    }

    bool Server::HandleDeviceCreateReadyComputePipeline(const volatile char** commands, size_t* size) {
        DeviceCreateReadyComputePipelineCmd cmd;
        DeserializeResult deserializeResult = cmd.Deserialize(commands, size, &mAllocator, *this);

        if (deserializeResult == DeserializeResult::FatalError) {
            return false;
        }


        bool success = DoDeviceCreateReadyComputePipeline(cmd.device, cmd.requestSerial, cmd.pipelineObjectHandle, cmd.descriptor);

        if (!success) {
            return false;
        }
        return true;
    }

    bool Server::HandleDeviceCreateReadyRenderPipeline(const volatile char** commands, size_t* size) {
        DeviceCreateReadyRenderPipelineCmd cmd;
        DeserializeResult deserializeResult = cmd.Deserialize(commands, size, &mAllocator, *this);

        if (deserializeResult == DeserializeResult::FatalError) {
            return false;
        }


        bool success = DoDeviceCreateReadyRenderPipeline(cmd.device, cmd.requestSerial, cmd.pipelineObjectHandle, cmd.descriptor);

        if (!success) {
            return false;
        }
        return true;
    }

    bool Server::HandleDeviceCreateRenderBundleEncoder(const volatile char** commands, size_t* size) {
        DeviceCreateRenderBundleEncoderCmd cmd;
        DeserializeResult deserializeResult = cmd.Deserialize(commands, size, &mAllocator, *this);

        if (deserializeResult == DeserializeResult::FatalError) {
            return false;
        }



        auto* resultData = RenderBundleEncoderObjects().Allocate(cmd.result.id);
        if (resultData == nullptr) {
            return false;
        }
        resultData->generation = cmd.result.generation;

        bool success = DoDeviceCreateRenderBundleEncoder(cmd.self, cmd.descriptor, &resultData->handle);

        if (!success) {
            return false;
        }

        return true;
    }

    bool Server::HandleDeviceCreateRenderPipeline(const volatile char** commands, size_t* size) {
        DeviceCreateRenderPipelineCmd cmd;
        DeserializeResult deserializeResult = cmd.Deserialize(commands, size, &mAllocator, *this);

        if (deserializeResult == DeserializeResult::FatalError) {
            return false;
        }



        auto* resultData = RenderPipelineObjects().Allocate(cmd.result.id);
        if (resultData == nullptr) {
            return false;
        }
        resultData->generation = cmd.result.generation;

        bool success = DoDeviceCreateRenderPipeline(cmd.self, cmd.descriptor, &resultData->handle);

        if (!success) {
            return false;
        }

        return true;
    }

    bool Server::HandleDeviceCreateSampler(const volatile char** commands, size_t* size) {
        DeviceCreateSamplerCmd cmd;
        DeserializeResult deserializeResult = cmd.Deserialize(commands, size, &mAllocator, *this);

        if (deserializeResult == DeserializeResult::FatalError) {
            return false;
        }



        auto* resultData = SamplerObjects().Allocate(cmd.result.id);
        if (resultData == nullptr) {
            return false;
        }
        resultData->generation = cmd.result.generation;

        bool success = DoDeviceCreateSampler(cmd.self, cmd.descriptor, &resultData->handle);

        if (!success) {
            return false;
        }

        return true;
    }

    bool Server::HandleDeviceCreateShaderModule(const volatile char** commands, size_t* size) {
        DeviceCreateShaderModuleCmd cmd;
        DeserializeResult deserializeResult = cmd.Deserialize(commands, size, &mAllocator, *this);

        if (deserializeResult == DeserializeResult::FatalError) {
            return false;
        }



        auto* resultData = ShaderModuleObjects().Allocate(cmd.result.id);
        if (resultData == nullptr) {
            return false;
        }
        resultData->generation = cmd.result.generation;

        bool success = DoDeviceCreateShaderModule(cmd.self, cmd.descriptor, &resultData->handle);

        if (!success) {
            return false;
        }

        return true;
    }

    bool Server::HandleDeviceCreateSwapChain(const volatile char** commands, size_t* size) {
        DeviceCreateSwapChainCmd cmd;
        DeserializeResult deserializeResult = cmd.Deserialize(commands, size, &mAllocator, *this);

        if (deserializeResult == DeserializeResult::FatalError) {
            return false;
        }



        auto* resultData = SwapChainObjects().Allocate(cmd.result.id);
        if (resultData == nullptr) {
            return false;
        }
        resultData->generation = cmd.result.generation;

        bool success = DoDeviceCreateSwapChain(cmd.self, cmd.surface, cmd.descriptor, &resultData->handle);

        if (!success) {
            return false;
        }

        return true;
    }

    bool Server::HandleDeviceCreateTexture(const volatile char** commands, size_t* size) {
        DeviceCreateTextureCmd cmd;
        DeserializeResult deserializeResult = cmd.Deserialize(commands, size, &mAllocator, *this);

        if (deserializeResult == DeserializeResult::FatalError) {
            return false;
        }



        auto* resultData = TextureObjects().Allocate(cmd.result.id);
        if (resultData == nullptr) {
            return false;
        }
        resultData->generation = cmd.result.generation;

        bool success = DoDeviceCreateTexture(cmd.self, cmd.descriptor, &resultData->handle);

        if (!success) {
            return false;
        }

        return true;
    }

    bool Server::HandleDeviceGetDefaultQueue(const volatile char** commands, size_t* size) {
        DeviceGetDefaultQueueCmd cmd;
        DeserializeResult deserializeResult = cmd.Deserialize(commands, size, &mAllocator, *this);

        if (deserializeResult == DeserializeResult::FatalError) {
            return false;
        }



        auto* resultData = QueueObjects().Allocate(cmd.result.id);
        if (resultData == nullptr) {
            return false;
        }
        resultData->generation = cmd.result.generation;

        bool success = DoDeviceGetDefaultQueue(cmd.self, &resultData->handle);

        if (!success) {
            return false;
        }

        return true;
    }

    bool Server::HandleDeviceInjectError(const volatile char** commands, size_t* size) {
        DeviceInjectErrorCmd cmd;
        DeserializeResult deserializeResult = cmd.Deserialize(commands, size, &mAllocator, *this);

        if (deserializeResult == DeserializeResult::FatalError) {
            return false;
        }


        bool success = DoDeviceInjectError(cmd.self, cmd.type, cmd.message);

        if (!success) {
            return false;
        }
        return true;
    }

    bool Server::HandleDeviceLoseForTesting(const volatile char** commands, size_t* size) {
        DeviceLoseForTestingCmd cmd;
        DeserializeResult deserializeResult = cmd.Deserialize(commands, size, &mAllocator, *this);

        if (deserializeResult == DeserializeResult::FatalError) {
            return false;
        }


        bool success = DoDeviceLoseForTesting(cmd.self);

        if (!success) {
            return false;
        }
        return true;
    }

    bool Server::HandleDevicePopErrorScope(const volatile char** commands, size_t* size) {
        DevicePopErrorScopeCmd cmd;
        DeserializeResult deserializeResult = cmd.Deserialize(commands, size, &mAllocator, *this);

        if (deserializeResult == DeserializeResult::FatalError) {
            return false;
        }


        bool success = DoDevicePopErrorScope(cmd.device, cmd.requestSerial);

        if (!success) {
            return false;
        }
        return true;
    }

    bool Server::HandleDevicePushErrorScope(const volatile char** commands, size_t* size) {
        DevicePushErrorScopeCmd cmd;
        DeserializeResult deserializeResult = cmd.Deserialize(commands, size, &mAllocator, *this);

        if (deserializeResult == DeserializeResult::FatalError) {
            return false;
        }


        bool success = DoDevicePushErrorScope(cmd.self, cmd.filter);

        if (!success) {
            return false;
        }
        return true;
    }

    bool Server::HandleDeviceTick(const volatile char** commands, size_t* size) {
        DeviceTickCmd cmd;
        DeserializeResult deserializeResult = cmd.Deserialize(commands, size, &mAllocator, *this);

        if (deserializeResult == DeserializeResult::FatalError) {
            return false;
        }


        bool success = DoDeviceTick(cmd.self);

        if (!success) {
            return false;
        }
        return true;
    }

    bool Server::HandleFenceOnCompletion(const volatile char** commands, size_t* size) {
        FenceOnCompletionCmd cmd;
        DeserializeResult deserializeResult = cmd.Deserialize(commands, size, &mAllocator);

        if (deserializeResult == DeserializeResult::FatalError) {
            return false;
        }


        bool success = DoFenceOnCompletion(cmd.fenceId, cmd.value, cmd.requestSerial);

        if (!success) {
            return false;
        }
        return true;
    }

    bool Server::HandleInstanceCreateSurface(const volatile char** commands, size_t* size) {
        InstanceCreateSurfaceCmd cmd;
        DeserializeResult deserializeResult = cmd.Deserialize(commands, size, &mAllocator, *this);

        if (deserializeResult == DeserializeResult::FatalError) {
            return false;
        }



        auto* resultData = SurfaceObjects().Allocate(cmd.result.id);
        if (resultData == nullptr) {
            return false;
        }
        resultData->generation = cmd.result.generation;

        bool success = DoInstanceCreateSurface(cmd.self, cmd.descriptor, &resultData->handle);

        if (!success) {
            return false;
        }

        return true;
    }

    bool Server::HandleQuerySetDestroy(const volatile char** commands, size_t* size) {
        QuerySetDestroyCmd cmd;
        DeserializeResult deserializeResult = cmd.Deserialize(commands, size, &mAllocator, *this);

        if (deserializeResult == DeserializeResult::FatalError) {
            return false;
        }


        bool success = DoQuerySetDestroy(cmd.self);

        if (!success) {
            return false;
        }
        return true;
    }

    bool Server::HandleQueueCreateFence(const volatile char** commands, size_t* size) {
        QueueCreateFenceCmd cmd;
        DeserializeResult deserializeResult = cmd.Deserialize(commands, size, &mAllocator, *this);

        if (deserializeResult == DeserializeResult::FatalError) {
            return false;
        }



        auto* resultData = FenceObjects().Allocate(cmd.result.id);
        if (resultData == nullptr) {
            return false;
        }
        resultData->generation = cmd.result.generation;

        bool success = DoQueueCreateFence(cmd.self, cmd.descriptor, &resultData->handle);

        if (!success) {
            return false;
        }
        FenceObjectIdTable().Store(resultData->handle, cmd.result.id);

        return true;
    }

    bool Server::HandleQueueSignal(const volatile char** commands, size_t* size) {
        QueueSignalCmd cmd;
        DeserializeResult deserializeResult = cmd.Deserialize(commands, size, &mAllocator, *this);

        if (deserializeResult == DeserializeResult::FatalError) {
            return false;
        }


        bool success = DoQueueSignal(cmd.self, cmd.fence, cmd.signalValue);

        if (!success) {
            return false;
        }
        return true;
    }

    bool Server::HandleQueueSubmit(const volatile char** commands, size_t* size) {
        QueueSubmitCmd cmd;
        DeserializeResult deserializeResult = cmd.Deserialize(commands, size, &mAllocator, *this);

        if (deserializeResult == DeserializeResult::FatalError) {
            return false;
        }


        bool success = DoQueueSubmit(cmd.self, cmd.commandCount, cmd.commands);

        if (!success) {
            return false;
        }
        return true;
    }

    bool Server::HandleQueueWriteBufferInternal(const volatile char** commands, size_t* size) {
        QueueWriteBufferInternalCmd cmd;
        DeserializeResult deserializeResult = cmd.Deserialize(commands, size, &mAllocator);

        if (deserializeResult == DeserializeResult::FatalError) {
            return false;
        }


        bool success = DoQueueWriteBufferInternal(cmd.queueId, cmd.bufferId, cmd.bufferOffset, cmd.data, cmd.size);

        if (!success) {
            return false;
        }
        return true;
    }

    bool Server::HandleQueueWriteTextureInternal(const volatile char** commands, size_t* size) {
        QueueWriteTextureInternalCmd cmd;
        DeserializeResult deserializeResult = cmd.Deserialize(commands, size, &mAllocator, *this);

        if (deserializeResult == DeserializeResult::FatalError) {
            return false;
        }


        bool success = DoQueueWriteTextureInternal(cmd.queueId, cmd.destination, cmd.data, cmd.dataSize, cmd.dataLayout, cmd.writeSize);

        if (!success) {
            return false;
        }
        return true;
    }

    bool Server::HandleRenderBundleEncoderDraw(const volatile char** commands, size_t* size) {
        RenderBundleEncoderDrawCmd cmd;
        DeserializeResult deserializeResult = cmd.Deserialize(commands, size, &mAllocator, *this);

        if (deserializeResult == DeserializeResult::FatalError) {
            return false;
        }


        bool success = DoRenderBundleEncoderDraw(cmd.self, cmd.vertexCount, cmd.instanceCount, cmd.firstVertex, cmd.firstInstance);

        if (!success) {
            return false;
        }
        return true;
    }

    bool Server::HandleRenderBundleEncoderDrawIndexed(const volatile char** commands, size_t* size) {
        RenderBundleEncoderDrawIndexedCmd cmd;
        DeserializeResult deserializeResult = cmd.Deserialize(commands, size, &mAllocator, *this);

        if (deserializeResult == DeserializeResult::FatalError) {
            return false;
        }


        bool success = DoRenderBundleEncoderDrawIndexed(cmd.self, cmd.indexCount, cmd.instanceCount, cmd.firstIndex, cmd.baseVertex, cmd.firstInstance);

        if (!success) {
            return false;
        }
        return true;
    }

    bool Server::HandleRenderBundleEncoderDrawIndexedIndirect(const volatile char** commands, size_t* size) {
        RenderBundleEncoderDrawIndexedIndirectCmd cmd;
        DeserializeResult deserializeResult = cmd.Deserialize(commands, size, &mAllocator, *this);

        if (deserializeResult == DeserializeResult::FatalError) {
            return false;
        }


        bool success = DoRenderBundleEncoderDrawIndexedIndirect(cmd.self, cmd.indirectBuffer, cmd.indirectOffset);

        if (!success) {
            return false;
        }
        return true;
    }

    bool Server::HandleRenderBundleEncoderDrawIndirect(const volatile char** commands, size_t* size) {
        RenderBundleEncoderDrawIndirectCmd cmd;
        DeserializeResult deserializeResult = cmd.Deserialize(commands, size, &mAllocator, *this);

        if (deserializeResult == DeserializeResult::FatalError) {
            return false;
        }


        bool success = DoRenderBundleEncoderDrawIndirect(cmd.self, cmd.indirectBuffer, cmd.indirectOffset);

        if (!success) {
            return false;
        }
        return true;
    }

    bool Server::HandleRenderBundleEncoderFinish(const volatile char** commands, size_t* size) {
        RenderBundleEncoderFinishCmd cmd;
        DeserializeResult deserializeResult = cmd.Deserialize(commands, size, &mAllocator, *this);

        if (deserializeResult == DeserializeResult::FatalError) {
            return false;
        }



        auto* resultData = RenderBundleObjects().Allocate(cmd.result.id);
        if (resultData == nullptr) {
            return false;
        }
        resultData->generation = cmd.result.generation;

        bool success = DoRenderBundleEncoderFinish(cmd.self, cmd.descriptor, &resultData->handle);

        if (!success) {
            return false;
        }

        return true;
    }

    bool Server::HandleRenderBundleEncoderInsertDebugMarker(const volatile char** commands, size_t* size) {
        RenderBundleEncoderInsertDebugMarkerCmd cmd;
        DeserializeResult deserializeResult = cmd.Deserialize(commands, size, &mAllocator, *this);

        if (deserializeResult == DeserializeResult::FatalError) {
            return false;
        }


        bool success = DoRenderBundleEncoderInsertDebugMarker(cmd.self, cmd.markerLabel);

        if (!success) {
            return false;
        }
        return true;
    }

    bool Server::HandleRenderBundleEncoderPopDebugGroup(const volatile char** commands, size_t* size) {
        RenderBundleEncoderPopDebugGroupCmd cmd;
        DeserializeResult deserializeResult = cmd.Deserialize(commands, size, &mAllocator, *this);

        if (deserializeResult == DeserializeResult::FatalError) {
            return false;
        }


        bool success = DoRenderBundleEncoderPopDebugGroup(cmd.self);

        if (!success) {
            return false;
        }
        return true;
    }

    bool Server::HandleRenderBundleEncoderPushDebugGroup(const volatile char** commands, size_t* size) {
        RenderBundleEncoderPushDebugGroupCmd cmd;
        DeserializeResult deserializeResult = cmd.Deserialize(commands, size, &mAllocator, *this);

        if (deserializeResult == DeserializeResult::FatalError) {
            return false;
        }


        bool success = DoRenderBundleEncoderPushDebugGroup(cmd.self, cmd.groupLabel);

        if (!success) {
            return false;
        }
        return true;
    }

    bool Server::HandleRenderBundleEncoderSetBindGroup(const volatile char** commands, size_t* size) {
        RenderBundleEncoderSetBindGroupCmd cmd;
        DeserializeResult deserializeResult = cmd.Deserialize(commands, size, &mAllocator, *this);

        if (deserializeResult == DeserializeResult::FatalError) {
            return false;
        }


        bool success = DoRenderBundleEncoderSetBindGroup(cmd.self, cmd.groupIndex, cmd.group, cmd.dynamicOffsetCount, cmd.dynamicOffsets);

        if (!success) {
            return false;
        }
        return true;
    }

    bool Server::HandleRenderBundleEncoderSetIndexBuffer(const volatile char** commands, size_t* size) {
        RenderBundleEncoderSetIndexBufferCmd cmd;
        DeserializeResult deserializeResult = cmd.Deserialize(commands, size, &mAllocator, *this);

        if (deserializeResult == DeserializeResult::FatalError) {
            return false;
        }


        bool success = DoRenderBundleEncoderSetIndexBuffer(cmd.self, cmd.buffer, cmd.offset, cmd.size);

        if (!success) {
            return false;
        }
        return true;
    }

    bool Server::HandleRenderBundleEncoderSetIndexBufferWithFormat(const volatile char** commands, size_t* size) {
        RenderBundleEncoderSetIndexBufferWithFormatCmd cmd;
        DeserializeResult deserializeResult = cmd.Deserialize(commands, size, &mAllocator, *this);

        if (deserializeResult == DeserializeResult::FatalError) {
            return false;
        }


        bool success = DoRenderBundleEncoderSetIndexBufferWithFormat(cmd.self, cmd.buffer, cmd.format, cmd.offset, cmd.size);

        if (!success) {
            return false;
        }
        return true;
    }

    bool Server::HandleRenderBundleEncoderSetPipeline(const volatile char** commands, size_t* size) {
        RenderBundleEncoderSetPipelineCmd cmd;
        DeserializeResult deserializeResult = cmd.Deserialize(commands, size, &mAllocator, *this);

        if (deserializeResult == DeserializeResult::FatalError) {
            return false;
        }


        bool success = DoRenderBundleEncoderSetPipeline(cmd.self, cmd.pipeline);

        if (!success) {
            return false;
        }
        return true;
    }

    bool Server::HandleRenderBundleEncoderSetVertexBuffer(const volatile char** commands, size_t* size) {
        RenderBundleEncoderSetVertexBufferCmd cmd;
        DeserializeResult deserializeResult = cmd.Deserialize(commands, size, &mAllocator, *this);

        if (deserializeResult == DeserializeResult::FatalError) {
            return false;
        }


        bool success = DoRenderBundleEncoderSetVertexBuffer(cmd.self, cmd.slot, cmd.buffer, cmd.offset, cmd.size);

        if (!success) {
            return false;
        }
        return true;
    }

    bool Server::HandleRenderPassEncoderDraw(const volatile char** commands, size_t* size) {
        RenderPassEncoderDrawCmd cmd;
        DeserializeResult deserializeResult = cmd.Deserialize(commands, size, &mAllocator, *this);

        if (deserializeResult == DeserializeResult::FatalError) {
            return false;
        }


        bool success = DoRenderPassEncoderDraw(cmd.self, cmd.vertexCount, cmd.instanceCount, cmd.firstVertex, cmd.firstInstance);

        if (!success) {
            return false;
        }
        return true;
    }

    bool Server::HandleRenderPassEncoderDrawIndexed(const volatile char** commands, size_t* size) {
        RenderPassEncoderDrawIndexedCmd cmd;
        DeserializeResult deserializeResult = cmd.Deserialize(commands, size, &mAllocator, *this);

        if (deserializeResult == DeserializeResult::FatalError) {
            return false;
        }


        bool success = DoRenderPassEncoderDrawIndexed(cmd.self, cmd.indexCount, cmd.instanceCount, cmd.firstIndex, cmd.baseVertex, cmd.firstInstance);

        if (!success) {
            return false;
        }
        return true;
    }

    bool Server::HandleRenderPassEncoderDrawIndexedIndirect(const volatile char** commands, size_t* size) {
        RenderPassEncoderDrawIndexedIndirectCmd cmd;
        DeserializeResult deserializeResult = cmd.Deserialize(commands, size, &mAllocator, *this);

        if (deserializeResult == DeserializeResult::FatalError) {
            return false;
        }


        bool success = DoRenderPassEncoderDrawIndexedIndirect(cmd.self, cmd.indirectBuffer, cmd.indirectOffset);

        if (!success) {
            return false;
        }
        return true;
    }

    bool Server::HandleRenderPassEncoderDrawIndirect(const volatile char** commands, size_t* size) {
        RenderPassEncoderDrawIndirectCmd cmd;
        DeserializeResult deserializeResult = cmd.Deserialize(commands, size, &mAllocator, *this);

        if (deserializeResult == DeserializeResult::FatalError) {
            return false;
        }


        bool success = DoRenderPassEncoderDrawIndirect(cmd.self, cmd.indirectBuffer, cmd.indirectOffset);

        if (!success) {
            return false;
        }
        return true;
    }

    bool Server::HandleRenderPassEncoderEndPass(const volatile char** commands, size_t* size) {
        RenderPassEncoderEndPassCmd cmd;
        DeserializeResult deserializeResult = cmd.Deserialize(commands, size, &mAllocator, *this);

        if (deserializeResult == DeserializeResult::FatalError) {
            return false;
        }


        bool success = DoRenderPassEncoderEndPass(cmd.self);

        if (!success) {
            return false;
        }
        return true;
    }

    bool Server::HandleRenderPassEncoderExecuteBundles(const volatile char** commands, size_t* size) {
        RenderPassEncoderExecuteBundlesCmd cmd;
        DeserializeResult deserializeResult = cmd.Deserialize(commands, size, &mAllocator, *this);

        if (deserializeResult == DeserializeResult::FatalError) {
            return false;
        }


        bool success = DoRenderPassEncoderExecuteBundles(cmd.self, cmd.bundlesCount, cmd.bundles);

        if (!success) {
            return false;
        }
        return true;
    }

    bool Server::HandleRenderPassEncoderInsertDebugMarker(const volatile char** commands, size_t* size) {
        RenderPassEncoderInsertDebugMarkerCmd cmd;
        DeserializeResult deserializeResult = cmd.Deserialize(commands, size, &mAllocator, *this);

        if (deserializeResult == DeserializeResult::FatalError) {
            return false;
        }


        bool success = DoRenderPassEncoderInsertDebugMarker(cmd.self, cmd.markerLabel);

        if (!success) {
            return false;
        }
        return true;
    }

    bool Server::HandleRenderPassEncoderPopDebugGroup(const volatile char** commands, size_t* size) {
        RenderPassEncoderPopDebugGroupCmd cmd;
        DeserializeResult deserializeResult = cmd.Deserialize(commands, size, &mAllocator, *this);

        if (deserializeResult == DeserializeResult::FatalError) {
            return false;
        }


        bool success = DoRenderPassEncoderPopDebugGroup(cmd.self);

        if (!success) {
            return false;
        }
        return true;
    }

    bool Server::HandleRenderPassEncoderPushDebugGroup(const volatile char** commands, size_t* size) {
        RenderPassEncoderPushDebugGroupCmd cmd;
        DeserializeResult deserializeResult = cmd.Deserialize(commands, size, &mAllocator, *this);

        if (deserializeResult == DeserializeResult::FatalError) {
            return false;
        }


        bool success = DoRenderPassEncoderPushDebugGroup(cmd.self, cmd.groupLabel);

        if (!success) {
            return false;
        }
        return true;
    }

    bool Server::HandleRenderPassEncoderSetBindGroup(const volatile char** commands, size_t* size) {
        RenderPassEncoderSetBindGroupCmd cmd;
        DeserializeResult deserializeResult = cmd.Deserialize(commands, size, &mAllocator, *this);

        if (deserializeResult == DeserializeResult::FatalError) {
            return false;
        }


        bool success = DoRenderPassEncoderSetBindGroup(cmd.self, cmd.groupIndex, cmd.group, cmd.dynamicOffsetCount, cmd.dynamicOffsets);

        if (!success) {
            return false;
        }
        return true;
    }

    bool Server::HandleRenderPassEncoderSetBlendColor(const volatile char** commands, size_t* size) {
        RenderPassEncoderSetBlendColorCmd cmd;
        DeserializeResult deserializeResult = cmd.Deserialize(commands, size, &mAllocator, *this);

        if (deserializeResult == DeserializeResult::FatalError) {
            return false;
        }


        bool success = DoRenderPassEncoderSetBlendColor(cmd.self, cmd.color);

        if (!success) {
            return false;
        }
        return true;
    }

    bool Server::HandleRenderPassEncoderSetIndexBuffer(const volatile char** commands, size_t* size) {
        RenderPassEncoderSetIndexBufferCmd cmd;
        DeserializeResult deserializeResult = cmd.Deserialize(commands, size, &mAllocator, *this);

        if (deserializeResult == DeserializeResult::FatalError) {
            return false;
        }


        bool success = DoRenderPassEncoderSetIndexBuffer(cmd.self, cmd.buffer, cmd.offset, cmd.size);

        if (!success) {
            return false;
        }
        return true;
    }

    bool Server::HandleRenderPassEncoderSetIndexBufferWithFormat(const volatile char** commands, size_t* size) {
        RenderPassEncoderSetIndexBufferWithFormatCmd cmd;
        DeserializeResult deserializeResult = cmd.Deserialize(commands, size, &mAllocator, *this);

        if (deserializeResult == DeserializeResult::FatalError) {
            return false;
        }


        bool success = DoRenderPassEncoderSetIndexBufferWithFormat(cmd.self, cmd.buffer, cmd.format, cmd.offset, cmd.size);

        if (!success) {
            return false;
        }
        return true;
    }

    bool Server::HandleRenderPassEncoderSetPipeline(const volatile char** commands, size_t* size) {
        RenderPassEncoderSetPipelineCmd cmd;
        DeserializeResult deserializeResult = cmd.Deserialize(commands, size, &mAllocator, *this);

        if (deserializeResult == DeserializeResult::FatalError) {
            return false;
        }


        bool success = DoRenderPassEncoderSetPipeline(cmd.self, cmd.pipeline);

        if (!success) {
            return false;
        }
        return true;
    }

    bool Server::HandleRenderPassEncoderSetScissorRect(const volatile char** commands, size_t* size) {
        RenderPassEncoderSetScissorRectCmd cmd;
        DeserializeResult deserializeResult = cmd.Deserialize(commands, size, &mAllocator, *this);

        if (deserializeResult == DeserializeResult::FatalError) {
            return false;
        }


        bool success = DoRenderPassEncoderSetScissorRect(cmd.self, cmd.x, cmd.y, cmd.width, cmd.height);

        if (!success) {
            return false;
        }
        return true;
    }

    bool Server::HandleRenderPassEncoderSetStencilReference(const volatile char** commands, size_t* size) {
        RenderPassEncoderSetStencilReferenceCmd cmd;
        DeserializeResult deserializeResult = cmd.Deserialize(commands, size, &mAllocator, *this);

        if (deserializeResult == DeserializeResult::FatalError) {
            return false;
        }


        bool success = DoRenderPassEncoderSetStencilReference(cmd.self, cmd.reference);

        if (!success) {
            return false;
        }
        return true;
    }

    bool Server::HandleRenderPassEncoderSetVertexBuffer(const volatile char** commands, size_t* size) {
        RenderPassEncoderSetVertexBufferCmd cmd;
        DeserializeResult deserializeResult = cmd.Deserialize(commands, size, &mAllocator, *this);

        if (deserializeResult == DeserializeResult::FatalError) {
            return false;
        }


        bool success = DoRenderPassEncoderSetVertexBuffer(cmd.self, cmd.slot, cmd.buffer, cmd.offset, cmd.size);

        if (!success) {
            return false;
        }
        return true;
    }

    bool Server::HandleRenderPassEncoderSetViewport(const volatile char** commands, size_t* size) {
        RenderPassEncoderSetViewportCmd cmd;
        DeserializeResult deserializeResult = cmd.Deserialize(commands, size, &mAllocator, *this);

        if (deserializeResult == DeserializeResult::FatalError) {
            return false;
        }


        bool success = DoRenderPassEncoderSetViewport(cmd.self, cmd.x, cmd.y, cmd.width, cmd.height, cmd.minDepth, cmd.maxDepth);

        if (!success) {
            return false;
        }
        return true;
    }

    bool Server::HandleRenderPassEncoderWriteTimestamp(const volatile char** commands, size_t* size) {
        RenderPassEncoderWriteTimestampCmd cmd;
        DeserializeResult deserializeResult = cmd.Deserialize(commands, size, &mAllocator, *this);

        if (deserializeResult == DeserializeResult::FatalError) {
            return false;
        }


        bool success = DoRenderPassEncoderWriteTimestamp(cmd.self, cmd.querySet, cmd.queryIndex);

        if (!success) {
            return false;
        }
        return true;
    }

    bool Server::HandleRenderPipelineGetBindGroupLayout(const volatile char** commands, size_t* size) {
        RenderPipelineGetBindGroupLayoutCmd cmd;
        DeserializeResult deserializeResult = cmd.Deserialize(commands, size, &mAllocator, *this);

        if (deserializeResult == DeserializeResult::FatalError) {
            return false;
        }



        auto* resultData = BindGroupLayoutObjects().Allocate(cmd.result.id);
        if (resultData == nullptr) {
            return false;
        }
        resultData->generation = cmd.result.generation;

        bool success = DoRenderPipelineGetBindGroupLayout(cmd.self, cmd.groupIndex, &resultData->handle);

        if (!success) {
            return false;
        }

        return true;
    }

    bool Server::HandleSwapChainConfigure(const volatile char** commands, size_t* size) {
        SwapChainConfigureCmd cmd;
        DeserializeResult deserializeResult = cmd.Deserialize(commands, size, &mAllocator, *this);

        if (deserializeResult == DeserializeResult::FatalError) {
            return false;
        }


        bool success = DoSwapChainConfigure(cmd.self, cmd.format, cmd.allowedUsage, cmd.width, cmd.height);

        if (!success) {
            return false;
        }
        return true;
    }

    bool Server::HandleSwapChainGetCurrentTextureView(const volatile char** commands, size_t* size) {
        SwapChainGetCurrentTextureViewCmd cmd;
        DeserializeResult deserializeResult = cmd.Deserialize(commands, size, &mAllocator, *this);

        if (deserializeResult == DeserializeResult::FatalError) {
            return false;
        }



        auto* resultData = TextureViewObjects().Allocate(cmd.result.id);
        if (resultData == nullptr) {
            return false;
        }
        resultData->generation = cmd.result.generation;

        bool success = DoSwapChainGetCurrentTextureView(cmd.self, &resultData->handle);

        if (!success) {
            return false;
        }

        return true;
    }

    bool Server::HandleSwapChainPresent(const volatile char** commands, size_t* size) {
        SwapChainPresentCmd cmd;
        DeserializeResult deserializeResult = cmd.Deserialize(commands, size, &mAllocator, *this);

        if (deserializeResult == DeserializeResult::FatalError) {
            return false;
        }


        bool success = DoSwapChainPresent(cmd.self);

        if (!success) {
            return false;
        }
        return true;
    }

    bool Server::HandleTextureCreateView(const volatile char** commands, size_t* size) {
        TextureCreateViewCmd cmd;
        DeserializeResult deserializeResult = cmd.Deserialize(commands, size, &mAllocator, *this);

        if (deserializeResult == DeserializeResult::FatalError) {
            return false;
        }



        auto* resultData = TextureViewObjects().Allocate(cmd.result.id);
        if (resultData == nullptr) {
            return false;
        }
        resultData->generation = cmd.result.generation;

        bool success = DoTextureCreateView(cmd.self, cmd.descriptor, &resultData->handle);

        if (!success) {
            return false;
        }

        return true;
    }

    bool Server::HandleTextureDestroy(const volatile char** commands, size_t* size) {
        TextureDestroyCmd cmd;
        DeserializeResult deserializeResult = cmd.Deserialize(commands, size, &mAllocator, *this);

        if (deserializeResult == DeserializeResult::FatalError) {
            return false;
        }


        bool success = DoTextureDestroy(cmd.self);

        if (!success) {
            return false;
        }
        return true;
    }

    const volatile char* Server::HandleCommandsImpl(const volatile char* commands, size_t size) {
        mProcs.deviceTick(DeviceObjects().Get(1)->handle);

        while (size >= sizeof(CmdHeader) + sizeof(WireCmd)) {
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

            WireCmd cmdId = *reinterpret_cast<const volatile WireCmd*>(commands + sizeof(CmdHeader));
            bool success = false;
            switch (cmdId) {
                case WireCmd::BufferDestroy:
                    success = HandleBufferDestroy(&commands, &size);
                    break;
                case WireCmd::BufferMapAsync:
                    success = HandleBufferMapAsync(&commands, &size);
                    break;
                case WireCmd::BufferUnmap:
                    success = HandleBufferUnmap(&commands, &size);
                    break;
                case WireCmd::BufferUpdateMappedData:
                    success = HandleBufferUpdateMappedData(&commands, &size);
                    break;
                case WireCmd::CommandEncoderBeginComputePass:
                    success = HandleCommandEncoderBeginComputePass(&commands, &size);
                    break;
                case WireCmd::CommandEncoderBeginRenderPass:
                    success = HandleCommandEncoderBeginRenderPass(&commands, &size);
                    break;
                case WireCmd::CommandEncoderCopyBufferToBuffer:
                    success = HandleCommandEncoderCopyBufferToBuffer(&commands, &size);
                    break;
                case WireCmd::CommandEncoderCopyBufferToTexture:
                    success = HandleCommandEncoderCopyBufferToTexture(&commands, &size);
                    break;
                case WireCmd::CommandEncoderCopyTextureToBuffer:
                    success = HandleCommandEncoderCopyTextureToBuffer(&commands, &size);
                    break;
                case WireCmd::CommandEncoderCopyTextureToTexture:
                    success = HandleCommandEncoderCopyTextureToTexture(&commands, &size);
                    break;
                case WireCmd::CommandEncoderFinish:
                    success = HandleCommandEncoderFinish(&commands, &size);
                    break;
                case WireCmd::CommandEncoderInsertDebugMarker:
                    success = HandleCommandEncoderInsertDebugMarker(&commands, &size);
                    break;
                case WireCmd::CommandEncoderPopDebugGroup:
                    success = HandleCommandEncoderPopDebugGroup(&commands, &size);
                    break;
                case WireCmd::CommandEncoderPushDebugGroup:
                    success = HandleCommandEncoderPushDebugGroup(&commands, &size);
                    break;
                case WireCmd::CommandEncoderResolveQuerySet:
                    success = HandleCommandEncoderResolveQuerySet(&commands, &size);
                    break;
                case WireCmd::CommandEncoderWriteTimestamp:
                    success = HandleCommandEncoderWriteTimestamp(&commands, &size);
                    break;
                case WireCmd::ComputePassEncoderDispatch:
                    success = HandleComputePassEncoderDispatch(&commands, &size);
                    break;
                case WireCmd::ComputePassEncoderDispatchIndirect:
                    success = HandleComputePassEncoderDispatchIndirect(&commands, &size);
                    break;
                case WireCmd::ComputePassEncoderEndPass:
                    success = HandleComputePassEncoderEndPass(&commands, &size);
                    break;
                case WireCmd::ComputePassEncoderInsertDebugMarker:
                    success = HandleComputePassEncoderInsertDebugMarker(&commands, &size);
                    break;
                case WireCmd::ComputePassEncoderPopDebugGroup:
                    success = HandleComputePassEncoderPopDebugGroup(&commands, &size);
                    break;
                case WireCmd::ComputePassEncoderPushDebugGroup:
                    success = HandleComputePassEncoderPushDebugGroup(&commands, &size);
                    break;
                case WireCmd::ComputePassEncoderSetBindGroup:
                    success = HandleComputePassEncoderSetBindGroup(&commands, &size);
                    break;
                case WireCmd::ComputePassEncoderSetPipeline:
                    success = HandleComputePassEncoderSetPipeline(&commands, &size);
                    break;
                case WireCmd::ComputePassEncoderWriteTimestamp:
                    success = HandleComputePassEncoderWriteTimestamp(&commands, &size);
                    break;
                case WireCmd::ComputePipelineGetBindGroupLayout:
                    success = HandleComputePipelineGetBindGroupLayout(&commands, &size);
                    break;
                case WireCmd::DestroyObject:
                    success = HandleDestroyObject(&commands, &size);
                    break;
                case WireCmd::DeviceCreateBindGroup:
                    success = HandleDeviceCreateBindGroup(&commands, &size);
                    break;
                case WireCmd::DeviceCreateBindGroupLayout:
                    success = HandleDeviceCreateBindGroupLayout(&commands, &size);
                    break;
                case WireCmd::DeviceCreateBuffer:
                    success = HandleDeviceCreateBuffer(&commands, &size);
                    break;
                case WireCmd::DeviceCreateCommandEncoder:
                    success = HandleDeviceCreateCommandEncoder(&commands, &size);
                    break;
                case WireCmd::DeviceCreateComputePipeline:
                    success = HandleDeviceCreateComputePipeline(&commands, &size);
                    break;
                case WireCmd::DeviceCreateErrorBuffer:
                    success = HandleDeviceCreateErrorBuffer(&commands, &size);
                    break;
                case WireCmd::DeviceCreatePipelineLayout:
                    success = HandleDeviceCreatePipelineLayout(&commands, &size);
                    break;
                case WireCmd::DeviceCreateQuerySet:
                    success = HandleDeviceCreateQuerySet(&commands, &size);
                    break;
                case WireCmd::DeviceCreateReadyComputePipeline:
                    success = HandleDeviceCreateReadyComputePipeline(&commands, &size);
                    break;
                case WireCmd::DeviceCreateReadyRenderPipeline:
                    success = HandleDeviceCreateReadyRenderPipeline(&commands, &size);
                    break;
                case WireCmd::DeviceCreateRenderBundleEncoder:
                    success = HandleDeviceCreateRenderBundleEncoder(&commands, &size);
                    break;
                case WireCmd::DeviceCreateRenderPipeline:
                    success = HandleDeviceCreateRenderPipeline(&commands, &size);
                    break;
                case WireCmd::DeviceCreateSampler:
                    success = HandleDeviceCreateSampler(&commands, &size);
                    break;
                case WireCmd::DeviceCreateShaderModule:
                    success = HandleDeviceCreateShaderModule(&commands, &size);
                    break;
                case WireCmd::DeviceCreateSwapChain:
                    success = HandleDeviceCreateSwapChain(&commands, &size);
                    break;
                case WireCmd::DeviceCreateTexture:
                    success = HandleDeviceCreateTexture(&commands, &size);
                    break;
                case WireCmd::DeviceGetDefaultQueue:
                    success = HandleDeviceGetDefaultQueue(&commands, &size);
                    break;
                case WireCmd::DeviceInjectError:
                    success = HandleDeviceInjectError(&commands, &size);
                    break;
                case WireCmd::DeviceLoseForTesting:
                    success = HandleDeviceLoseForTesting(&commands, &size);
                    break;
                case WireCmd::DevicePopErrorScope:
                    success = HandleDevicePopErrorScope(&commands, &size);
                    break;
                case WireCmd::DevicePushErrorScope:
                    success = HandleDevicePushErrorScope(&commands, &size);
                    break;
                case WireCmd::DeviceTick:
                    success = HandleDeviceTick(&commands, &size);
                    break;
                case WireCmd::FenceOnCompletion:
                    success = HandleFenceOnCompletion(&commands, &size);
                    break;
                case WireCmd::InstanceCreateSurface:
                    success = HandleInstanceCreateSurface(&commands, &size);
                    break;
                case WireCmd::QuerySetDestroy:
                    success = HandleQuerySetDestroy(&commands, &size);
                    break;
                case WireCmd::QueueCreateFence:
                    success = HandleQueueCreateFence(&commands, &size);
                    break;
                case WireCmd::QueueSignal:
                    success = HandleQueueSignal(&commands, &size);
                    break;
                case WireCmd::QueueSubmit:
                    success = HandleQueueSubmit(&commands, &size);
                    break;
                case WireCmd::QueueWriteBufferInternal:
                    success = HandleQueueWriteBufferInternal(&commands, &size);
                    break;
                case WireCmd::QueueWriteTextureInternal:
                    success = HandleQueueWriteTextureInternal(&commands, &size);
                    break;
                case WireCmd::RenderBundleEncoderDraw:
                    success = HandleRenderBundleEncoderDraw(&commands, &size);
                    break;
                case WireCmd::RenderBundleEncoderDrawIndexed:
                    success = HandleRenderBundleEncoderDrawIndexed(&commands, &size);
                    break;
                case WireCmd::RenderBundleEncoderDrawIndexedIndirect:
                    success = HandleRenderBundleEncoderDrawIndexedIndirect(&commands, &size);
                    break;
                case WireCmd::RenderBundleEncoderDrawIndirect:
                    success = HandleRenderBundleEncoderDrawIndirect(&commands, &size);
                    break;
                case WireCmd::RenderBundleEncoderFinish:
                    success = HandleRenderBundleEncoderFinish(&commands, &size);
                    break;
                case WireCmd::RenderBundleEncoderInsertDebugMarker:
                    success = HandleRenderBundleEncoderInsertDebugMarker(&commands, &size);
                    break;
                case WireCmd::RenderBundleEncoderPopDebugGroup:
                    success = HandleRenderBundleEncoderPopDebugGroup(&commands, &size);
                    break;
                case WireCmd::RenderBundleEncoderPushDebugGroup:
                    success = HandleRenderBundleEncoderPushDebugGroup(&commands, &size);
                    break;
                case WireCmd::RenderBundleEncoderSetBindGroup:
                    success = HandleRenderBundleEncoderSetBindGroup(&commands, &size);
                    break;
                case WireCmd::RenderBundleEncoderSetIndexBuffer:
                    success = HandleRenderBundleEncoderSetIndexBuffer(&commands, &size);
                    break;
                case WireCmd::RenderBundleEncoderSetIndexBufferWithFormat:
                    success = HandleRenderBundleEncoderSetIndexBufferWithFormat(&commands, &size);
                    break;
                case WireCmd::RenderBundleEncoderSetPipeline:
                    success = HandleRenderBundleEncoderSetPipeline(&commands, &size);
                    break;
                case WireCmd::RenderBundleEncoderSetVertexBuffer:
                    success = HandleRenderBundleEncoderSetVertexBuffer(&commands, &size);
                    break;
                case WireCmd::RenderPassEncoderDraw:
                    success = HandleRenderPassEncoderDraw(&commands, &size);
                    break;
                case WireCmd::RenderPassEncoderDrawIndexed:
                    success = HandleRenderPassEncoderDrawIndexed(&commands, &size);
                    break;
                case WireCmd::RenderPassEncoderDrawIndexedIndirect:
                    success = HandleRenderPassEncoderDrawIndexedIndirect(&commands, &size);
                    break;
                case WireCmd::RenderPassEncoderDrawIndirect:
                    success = HandleRenderPassEncoderDrawIndirect(&commands, &size);
                    break;
                case WireCmd::RenderPassEncoderEndPass:
                    success = HandleRenderPassEncoderEndPass(&commands, &size);
                    break;
                case WireCmd::RenderPassEncoderExecuteBundles:
                    success = HandleRenderPassEncoderExecuteBundles(&commands, &size);
                    break;
                case WireCmd::RenderPassEncoderInsertDebugMarker:
                    success = HandleRenderPassEncoderInsertDebugMarker(&commands, &size);
                    break;
                case WireCmd::RenderPassEncoderPopDebugGroup:
                    success = HandleRenderPassEncoderPopDebugGroup(&commands, &size);
                    break;
                case WireCmd::RenderPassEncoderPushDebugGroup:
                    success = HandleRenderPassEncoderPushDebugGroup(&commands, &size);
                    break;
                case WireCmd::RenderPassEncoderSetBindGroup:
                    success = HandleRenderPassEncoderSetBindGroup(&commands, &size);
                    break;
                case WireCmd::RenderPassEncoderSetBlendColor:
                    success = HandleRenderPassEncoderSetBlendColor(&commands, &size);
                    break;
                case WireCmd::RenderPassEncoderSetIndexBuffer:
                    success = HandleRenderPassEncoderSetIndexBuffer(&commands, &size);
                    break;
                case WireCmd::RenderPassEncoderSetIndexBufferWithFormat:
                    success = HandleRenderPassEncoderSetIndexBufferWithFormat(&commands, &size);
                    break;
                case WireCmd::RenderPassEncoderSetPipeline:
                    success = HandleRenderPassEncoderSetPipeline(&commands, &size);
                    break;
                case WireCmd::RenderPassEncoderSetScissorRect:
                    success = HandleRenderPassEncoderSetScissorRect(&commands, &size);
                    break;
                case WireCmd::RenderPassEncoderSetStencilReference:
                    success = HandleRenderPassEncoderSetStencilReference(&commands, &size);
                    break;
                case WireCmd::RenderPassEncoderSetVertexBuffer:
                    success = HandleRenderPassEncoderSetVertexBuffer(&commands, &size);
                    break;
                case WireCmd::RenderPassEncoderSetViewport:
                    success = HandleRenderPassEncoderSetViewport(&commands, &size);
                    break;
                case WireCmd::RenderPassEncoderWriteTimestamp:
                    success = HandleRenderPassEncoderWriteTimestamp(&commands, &size);
                    break;
                case WireCmd::RenderPipelineGetBindGroupLayout:
                    success = HandleRenderPipelineGetBindGroupLayout(&commands, &size);
                    break;
                case WireCmd::SwapChainConfigure:
                    success = HandleSwapChainConfigure(&commands, &size);
                    break;
                case WireCmd::SwapChainGetCurrentTextureView:
                    success = HandleSwapChainGetCurrentTextureView(&commands, &size);
                    break;
                case WireCmd::SwapChainPresent:
                    success = HandleSwapChainPresent(&commands, &size);
                    break;
                case WireCmd::TextureCreateView:
                    success = HandleTextureCreateView(&commands, &size);
                    break;
                case WireCmd::TextureDestroy:
                    success = HandleTextureDestroy(&commands, &size);
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

}}  // namespace dawn_wire::server
