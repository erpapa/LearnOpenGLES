
#include "mock_webgpu.h"

using namespace testing;

namespace {
    void ForwardBindGroupReference(WGPUBindGroup self) {
        auto object = reinterpret_cast<ProcTableAsClass::Object*>(self);
        return object->procs->BindGroupReference(self);
    }
    void ForwardBindGroupRelease(WGPUBindGroup self) {
        auto object = reinterpret_cast<ProcTableAsClass::Object*>(self);
        return object->procs->BindGroupRelease(self);
    }

    void ForwardBindGroupLayoutReference(WGPUBindGroupLayout self) {
        auto object = reinterpret_cast<ProcTableAsClass::Object*>(self);
        return object->procs->BindGroupLayoutReference(self);
    }
    void ForwardBindGroupLayoutRelease(WGPUBindGroupLayout self) {
        auto object = reinterpret_cast<ProcTableAsClass::Object*>(self);
        return object->procs->BindGroupLayoutRelease(self);
    }

    void ForwardBufferDestroy(WGPUBuffer self) {
        auto object = reinterpret_cast<ProcTableAsClass::Object*>(self);
        return object->procs->BufferDestroy(self);
    }
    void const * ForwardBufferGetConstMappedRange(WGPUBuffer self, size_t offset, size_t size) {
        auto object = reinterpret_cast<ProcTableAsClass::Object*>(self);
        return object->procs->BufferGetConstMappedRange(self, offset, size);
    }
    void * ForwardBufferGetMappedRange(WGPUBuffer self, size_t offset, size_t size) {
        auto object = reinterpret_cast<ProcTableAsClass::Object*>(self);
        return object->procs->BufferGetMappedRange(self, offset, size);
    }
    void ForwardBufferMapAsync(WGPUBuffer self, WGPUMapModeFlags mode, size_t offset, size_t size, WGPUBufferMapCallback callback, void * userdata) {
        auto object = reinterpret_cast<ProcTableAsClass::Object*>(self);
        return object->procs->BufferMapAsync(self, mode, offset, size, callback, userdata);
    }
    void ForwardBufferUnmap(WGPUBuffer self) {
        auto object = reinterpret_cast<ProcTableAsClass::Object*>(self);
        return object->procs->BufferUnmap(self);
    }
    void ForwardBufferReference(WGPUBuffer self) {
        auto object = reinterpret_cast<ProcTableAsClass::Object*>(self);
        return object->procs->BufferReference(self);
    }
    void ForwardBufferRelease(WGPUBuffer self) {
        auto object = reinterpret_cast<ProcTableAsClass::Object*>(self);
        return object->procs->BufferRelease(self);
    }

    void ForwardCommandBufferReference(WGPUCommandBuffer self) {
        auto object = reinterpret_cast<ProcTableAsClass::Object*>(self);
        return object->procs->CommandBufferReference(self);
    }
    void ForwardCommandBufferRelease(WGPUCommandBuffer self) {
        auto object = reinterpret_cast<ProcTableAsClass::Object*>(self);
        return object->procs->CommandBufferRelease(self);
    }

    WGPUComputePassEncoder ForwardCommandEncoderBeginComputePass(WGPUCommandEncoder self, WGPUComputePassDescriptor const * descriptor) {
        auto object = reinterpret_cast<ProcTableAsClass::Object*>(self);
        return object->procs->CommandEncoderBeginComputePass(self, descriptor);
    }
    WGPURenderPassEncoder ForwardCommandEncoderBeginRenderPass(WGPUCommandEncoder self, WGPURenderPassDescriptor const * descriptor) {
        auto object = reinterpret_cast<ProcTableAsClass::Object*>(self);
        return object->procs->CommandEncoderBeginRenderPass(self, descriptor);
    }
    void ForwardCommandEncoderCopyBufferToBuffer(WGPUCommandEncoder self, WGPUBuffer source, uint64_t sourceOffset, WGPUBuffer destination, uint64_t destinationOffset, uint64_t size) {
        auto object = reinterpret_cast<ProcTableAsClass::Object*>(self);
        return object->procs->CommandEncoderCopyBufferToBuffer(self, source, sourceOffset, destination, destinationOffset, size);
    }
    void ForwardCommandEncoderCopyBufferToTexture(WGPUCommandEncoder self, WGPUBufferCopyView const * source, WGPUTextureCopyView const * destination, WGPUExtent3D const * copySize) {
        auto object = reinterpret_cast<ProcTableAsClass::Object*>(self);
        return object->procs->CommandEncoderCopyBufferToTexture(self, source, destination, copySize);
    }
    void ForwardCommandEncoderCopyTextureToBuffer(WGPUCommandEncoder self, WGPUTextureCopyView const * source, WGPUBufferCopyView const * destination, WGPUExtent3D const * copySize) {
        auto object = reinterpret_cast<ProcTableAsClass::Object*>(self);
        return object->procs->CommandEncoderCopyTextureToBuffer(self, source, destination, copySize);
    }
    void ForwardCommandEncoderCopyTextureToTexture(WGPUCommandEncoder self, WGPUTextureCopyView const * source, WGPUTextureCopyView const * destination, WGPUExtent3D const * copySize) {
        auto object = reinterpret_cast<ProcTableAsClass::Object*>(self);
        return object->procs->CommandEncoderCopyTextureToTexture(self, source, destination, copySize);
    }
    WGPUCommandBuffer ForwardCommandEncoderFinish(WGPUCommandEncoder self, WGPUCommandBufferDescriptor const * descriptor) {
        auto object = reinterpret_cast<ProcTableAsClass::Object*>(self);
        return object->procs->CommandEncoderFinish(self, descriptor);
    }
    void ForwardCommandEncoderInsertDebugMarker(WGPUCommandEncoder self, char const * markerLabel) {
        auto object = reinterpret_cast<ProcTableAsClass::Object*>(self);
        return object->procs->CommandEncoderInsertDebugMarker(self, markerLabel);
    }
    void ForwardCommandEncoderPopDebugGroup(WGPUCommandEncoder self) {
        auto object = reinterpret_cast<ProcTableAsClass::Object*>(self);
        return object->procs->CommandEncoderPopDebugGroup(self);
    }
    void ForwardCommandEncoderPushDebugGroup(WGPUCommandEncoder self, char const * groupLabel) {
        auto object = reinterpret_cast<ProcTableAsClass::Object*>(self);
        return object->procs->CommandEncoderPushDebugGroup(self, groupLabel);
    }
    void ForwardCommandEncoderResolveQuerySet(WGPUCommandEncoder self, WGPUQuerySet querySet, uint32_t firstQuery, uint32_t queryCount, WGPUBuffer destination, uint64_t destinationOffset) {
        auto object = reinterpret_cast<ProcTableAsClass::Object*>(self);
        return object->procs->CommandEncoderResolveQuerySet(self, querySet, firstQuery, queryCount, destination, destinationOffset);
    }
    void ForwardCommandEncoderWriteTimestamp(WGPUCommandEncoder self, WGPUQuerySet querySet, uint32_t queryIndex) {
        auto object = reinterpret_cast<ProcTableAsClass::Object*>(self);
        return object->procs->CommandEncoderWriteTimestamp(self, querySet, queryIndex);
    }
    void ForwardCommandEncoderReference(WGPUCommandEncoder self) {
        auto object = reinterpret_cast<ProcTableAsClass::Object*>(self);
        return object->procs->CommandEncoderReference(self);
    }
    void ForwardCommandEncoderRelease(WGPUCommandEncoder self) {
        auto object = reinterpret_cast<ProcTableAsClass::Object*>(self);
        return object->procs->CommandEncoderRelease(self);
    }

    void ForwardComputePassEncoderDispatch(WGPUComputePassEncoder self, uint32_t x, uint32_t y, uint32_t z) {
        auto object = reinterpret_cast<ProcTableAsClass::Object*>(self);
        return object->procs->ComputePassEncoderDispatch(self, x, y, z);
    }
    void ForwardComputePassEncoderDispatchIndirect(WGPUComputePassEncoder self, WGPUBuffer indirectBuffer, uint64_t indirectOffset) {
        auto object = reinterpret_cast<ProcTableAsClass::Object*>(self);
        return object->procs->ComputePassEncoderDispatchIndirect(self, indirectBuffer, indirectOffset);
    }
    void ForwardComputePassEncoderEndPass(WGPUComputePassEncoder self) {
        auto object = reinterpret_cast<ProcTableAsClass::Object*>(self);
        return object->procs->ComputePassEncoderEndPass(self);
    }
    void ForwardComputePassEncoderInsertDebugMarker(WGPUComputePassEncoder self, char const * markerLabel) {
        auto object = reinterpret_cast<ProcTableAsClass::Object*>(self);
        return object->procs->ComputePassEncoderInsertDebugMarker(self, markerLabel);
    }
    void ForwardComputePassEncoderPopDebugGroup(WGPUComputePassEncoder self) {
        auto object = reinterpret_cast<ProcTableAsClass::Object*>(self);
        return object->procs->ComputePassEncoderPopDebugGroup(self);
    }
    void ForwardComputePassEncoderPushDebugGroup(WGPUComputePassEncoder self, char const * groupLabel) {
        auto object = reinterpret_cast<ProcTableAsClass::Object*>(self);
        return object->procs->ComputePassEncoderPushDebugGroup(self, groupLabel);
    }
    void ForwardComputePassEncoderSetBindGroup(WGPUComputePassEncoder self, uint32_t groupIndex, WGPUBindGroup group, uint32_t dynamicOffsetCount, uint32_t const * dynamicOffsets) {
        auto object = reinterpret_cast<ProcTableAsClass::Object*>(self);
        return object->procs->ComputePassEncoderSetBindGroup(self, groupIndex, group, dynamicOffsetCount, dynamicOffsets);
    }
    void ForwardComputePassEncoderSetPipeline(WGPUComputePassEncoder self, WGPUComputePipeline pipeline) {
        auto object = reinterpret_cast<ProcTableAsClass::Object*>(self);
        return object->procs->ComputePassEncoderSetPipeline(self, pipeline);
    }
    void ForwardComputePassEncoderWriteTimestamp(WGPUComputePassEncoder self, WGPUQuerySet querySet, uint32_t queryIndex) {
        auto object = reinterpret_cast<ProcTableAsClass::Object*>(self);
        return object->procs->ComputePassEncoderWriteTimestamp(self, querySet, queryIndex);
    }
    void ForwardComputePassEncoderReference(WGPUComputePassEncoder self) {
        auto object = reinterpret_cast<ProcTableAsClass::Object*>(self);
        return object->procs->ComputePassEncoderReference(self);
    }
    void ForwardComputePassEncoderRelease(WGPUComputePassEncoder self) {
        auto object = reinterpret_cast<ProcTableAsClass::Object*>(self);
        return object->procs->ComputePassEncoderRelease(self);
    }

    WGPUBindGroupLayout ForwardComputePipelineGetBindGroupLayout(WGPUComputePipeline self, uint32_t groupIndex) {
        auto object = reinterpret_cast<ProcTableAsClass::Object*>(self);
        return object->procs->ComputePipelineGetBindGroupLayout(self, groupIndex);
    }
    void ForwardComputePipelineReference(WGPUComputePipeline self) {
        auto object = reinterpret_cast<ProcTableAsClass::Object*>(self);
        return object->procs->ComputePipelineReference(self);
    }
    void ForwardComputePipelineRelease(WGPUComputePipeline self) {
        auto object = reinterpret_cast<ProcTableAsClass::Object*>(self);
        return object->procs->ComputePipelineRelease(self);
    }

    WGPUBindGroup ForwardDeviceCreateBindGroup(WGPUDevice self, WGPUBindGroupDescriptor const * descriptor) {
        auto object = reinterpret_cast<ProcTableAsClass::Object*>(self);
        return object->procs->DeviceCreateBindGroup(self, descriptor);
    }
    WGPUBindGroupLayout ForwardDeviceCreateBindGroupLayout(WGPUDevice self, WGPUBindGroupLayoutDescriptor const * descriptor) {
        auto object = reinterpret_cast<ProcTableAsClass::Object*>(self);
        return object->procs->DeviceCreateBindGroupLayout(self, descriptor);
    }
    WGPUBuffer ForwardDeviceCreateBuffer(WGPUDevice self, WGPUBufferDescriptor const * descriptor) {
        auto object = reinterpret_cast<ProcTableAsClass::Object*>(self);
        return object->procs->DeviceCreateBuffer(self, descriptor);
    }
    WGPUCommandEncoder ForwardDeviceCreateCommandEncoder(WGPUDevice self, WGPUCommandEncoderDescriptor const * descriptor) {
        auto object = reinterpret_cast<ProcTableAsClass::Object*>(self);
        return object->procs->DeviceCreateCommandEncoder(self, descriptor);
    }
    WGPUComputePipeline ForwardDeviceCreateComputePipeline(WGPUDevice self, WGPUComputePipelineDescriptor const * descriptor) {
        auto object = reinterpret_cast<ProcTableAsClass::Object*>(self);
        return object->procs->DeviceCreateComputePipeline(self, descriptor);
    }
    WGPUBuffer ForwardDeviceCreateErrorBuffer(WGPUDevice self) {
        auto object = reinterpret_cast<ProcTableAsClass::Object*>(self);
        return object->procs->DeviceCreateErrorBuffer(self);
    }
    WGPUPipelineLayout ForwardDeviceCreatePipelineLayout(WGPUDevice self, WGPUPipelineLayoutDescriptor const * descriptor) {
        auto object = reinterpret_cast<ProcTableAsClass::Object*>(self);
        return object->procs->DeviceCreatePipelineLayout(self, descriptor);
    }
    WGPUQuerySet ForwardDeviceCreateQuerySet(WGPUDevice self, WGPUQuerySetDescriptor const * descriptor) {
        auto object = reinterpret_cast<ProcTableAsClass::Object*>(self);
        return object->procs->DeviceCreateQuerySet(self, descriptor);
    }
    void ForwardDeviceCreateReadyComputePipeline(WGPUDevice self, WGPUComputePipelineDescriptor const * descriptor, WGPUCreateReadyComputePipelineCallback callback, void * userdata) {
        auto object = reinterpret_cast<ProcTableAsClass::Object*>(self);
        return object->procs->DeviceCreateReadyComputePipeline(self, descriptor, callback, userdata);
    }
    void ForwardDeviceCreateReadyRenderPipeline(WGPUDevice self, WGPURenderPipelineDescriptor const * descriptor, WGPUCreateReadyRenderPipelineCallback callback, void * userdata) {
        auto object = reinterpret_cast<ProcTableAsClass::Object*>(self);
        return object->procs->DeviceCreateReadyRenderPipeline(self, descriptor, callback, userdata);
    }
    WGPURenderBundleEncoder ForwardDeviceCreateRenderBundleEncoder(WGPUDevice self, WGPURenderBundleEncoderDescriptor const * descriptor) {
        auto object = reinterpret_cast<ProcTableAsClass::Object*>(self);
        return object->procs->DeviceCreateRenderBundleEncoder(self, descriptor);
    }
    WGPURenderPipeline ForwardDeviceCreateRenderPipeline(WGPUDevice self, WGPURenderPipelineDescriptor const * descriptor) {
        auto object = reinterpret_cast<ProcTableAsClass::Object*>(self);
        return object->procs->DeviceCreateRenderPipeline(self, descriptor);
    }
    WGPUSampler ForwardDeviceCreateSampler(WGPUDevice self, WGPUSamplerDescriptor const * descriptor) {
        auto object = reinterpret_cast<ProcTableAsClass::Object*>(self);
        return object->procs->DeviceCreateSampler(self, descriptor);
    }
    WGPUShaderModule ForwardDeviceCreateShaderModule(WGPUDevice self, WGPUShaderModuleDescriptor const * descriptor) {
        auto object = reinterpret_cast<ProcTableAsClass::Object*>(self);
        return object->procs->DeviceCreateShaderModule(self, descriptor);
    }
    WGPUSwapChain ForwardDeviceCreateSwapChain(WGPUDevice self, WGPUSurface surface, WGPUSwapChainDescriptor const * descriptor) {
        auto object = reinterpret_cast<ProcTableAsClass::Object*>(self);
        return object->procs->DeviceCreateSwapChain(self, surface, descriptor);
    }
    WGPUTexture ForwardDeviceCreateTexture(WGPUDevice self, WGPUTextureDescriptor const * descriptor) {
        auto object = reinterpret_cast<ProcTableAsClass::Object*>(self);
        return object->procs->DeviceCreateTexture(self, descriptor);
    }
    WGPUQueue ForwardDeviceGetDefaultQueue(WGPUDevice self) {
        auto object = reinterpret_cast<ProcTableAsClass::Object*>(self);
        return object->procs->DeviceGetDefaultQueue(self);
    }
    void ForwardDeviceInjectError(WGPUDevice self, WGPUErrorType type, char const * message) {
        auto object = reinterpret_cast<ProcTableAsClass::Object*>(self);
        return object->procs->DeviceInjectError(self, type, message);
    }
    void ForwardDeviceLoseForTesting(WGPUDevice self) {
        auto object = reinterpret_cast<ProcTableAsClass::Object*>(self);
        return object->procs->DeviceLoseForTesting(self);
    }
    bool ForwardDevicePopErrorScope(WGPUDevice self, WGPUErrorCallback callback, void * userdata) {
        auto object = reinterpret_cast<ProcTableAsClass::Object*>(self);
        return object->procs->DevicePopErrorScope(self, callback, userdata);
    }
    void ForwardDevicePushErrorScope(WGPUDevice self, WGPUErrorFilter filter) {
        auto object = reinterpret_cast<ProcTableAsClass::Object*>(self);
        return object->procs->DevicePushErrorScope(self, filter);
    }
    void ForwardDeviceSetDeviceLostCallback(WGPUDevice self, WGPUDeviceLostCallback callback, void * userdata) {
        auto object = reinterpret_cast<ProcTableAsClass::Object*>(self);
        return object->procs->DeviceSetDeviceLostCallback(self, callback, userdata);
    }
    void ForwardDeviceSetUncapturedErrorCallback(WGPUDevice self, WGPUErrorCallback callback, void * userdata) {
        auto object = reinterpret_cast<ProcTableAsClass::Object*>(self);
        return object->procs->DeviceSetUncapturedErrorCallback(self, callback, userdata);
    }
    void ForwardDeviceTick(WGPUDevice self) {
        auto object = reinterpret_cast<ProcTableAsClass::Object*>(self);
        return object->procs->DeviceTick(self);
    }
    void ForwardDeviceReference(WGPUDevice self) {
        auto object = reinterpret_cast<ProcTableAsClass::Object*>(self);
        return object->procs->DeviceReference(self);
    }
    void ForwardDeviceRelease(WGPUDevice self) {
        auto object = reinterpret_cast<ProcTableAsClass::Object*>(self);
        return object->procs->DeviceRelease(self);
    }

    uint64_t ForwardFenceGetCompletedValue(WGPUFence self) {
        auto object = reinterpret_cast<ProcTableAsClass::Object*>(self);
        return object->procs->FenceGetCompletedValue(self);
    }
    void ForwardFenceOnCompletion(WGPUFence self, uint64_t value, WGPUFenceOnCompletionCallback callback, void * userdata) {
        auto object = reinterpret_cast<ProcTableAsClass::Object*>(self);
        return object->procs->FenceOnCompletion(self, value, callback, userdata);
    }
    void ForwardFenceReference(WGPUFence self) {
        auto object = reinterpret_cast<ProcTableAsClass::Object*>(self);
        return object->procs->FenceReference(self);
    }
    void ForwardFenceRelease(WGPUFence self) {
        auto object = reinterpret_cast<ProcTableAsClass::Object*>(self);
        return object->procs->FenceRelease(self);
    }

    WGPUSurface ForwardInstanceCreateSurface(WGPUInstance self, WGPUSurfaceDescriptor const * descriptor) {
        auto object = reinterpret_cast<ProcTableAsClass::Object*>(self);
        return object->procs->InstanceCreateSurface(self, descriptor);
    }
    void ForwardInstanceReference(WGPUInstance self) {
        auto object = reinterpret_cast<ProcTableAsClass::Object*>(self);
        return object->procs->InstanceReference(self);
    }
    void ForwardInstanceRelease(WGPUInstance self) {
        auto object = reinterpret_cast<ProcTableAsClass::Object*>(self);
        return object->procs->InstanceRelease(self);
    }

    void ForwardPipelineLayoutReference(WGPUPipelineLayout self) {
        auto object = reinterpret_cast<ProcTableAsClass::Object*>(self);
        return object->procs->PipelineLayoutReference(self);
    }
    void ForwardPipelineLayoutRelease(WGPUPipelineLayout self) {
        auto object = reinterpret_cast<ProcTableAsClass::Object*>(self);
        return object->procs->PipelineLayoutRelease(self);
    }

    void ForwardQuerySetDestroy(WGPUQuerySet self) {
        auto object = reinterpret_cast<ProcTableAsClass::Object*>(self);
        return object->procs->QuerySetDestroy(self);
    }
    void ForwardQuerySetReference(WGPUQuerySet self) {
        auto object = reinterpret_cast<ProcTableAsClass::Object*>(self);
        return object->procs->QuerySetReference(self);
    }
    void ForwardQuerySetRelease(WGPUQuerySet self) {
        auto object = reinterpret_cast<ProcTableAsClass::Object*>(self);
        return object->procs->QuerySetRelease(self);
    }

    WGPUFence ForwardQueueCreateFence(WGPUQueue self, WGPUFenceDescriptor const * descriptor) {
        auto object = reinterpret_cast<ProcTableAsClass::Object*>(self);
        return object->procs->QueueCreateFence(self, descriptor);
    }
    void ForwardQueueSignal(WGPUQueue self, WGPUFence fence, uint64_t signalValue) {
        auto object = reinterpret_cast<ProcTableAsClass::Object*>(self);
        return object->procs->QueueSignal(self, fence, signalValue);
    }
    void ForwardQueueSubmit(WGPUQueue self, uint32_t commandCount, WGPUCommandBuffer const * commands) {
        auto object = reinterpret_cast<ProcTableAsClass::Object*>(self);
        return object->procs->QueueSubmit(self, commandCount, commands);
    }
    void ForwardQueueWriteBuffer(WGPUQueue self, WGPUBuffer buffer, uint64_t bufferOffset, void const * data, size_t size) {
        auto object = reinterpret_cast<ProcTableAsClass::Object*>(self);
        return object->procs->QueueWriteBuffer(self, buffer, bufferOffset, data, size);
    }
    void ForwardQueueWriteTexture(WGPUQueue self, WGPUTextureCopyView const * destination, void const * data, size_t dataSize, WGPUTextureDataLayout const * dataLayout, WGPUExtent3D const * writeSize) {
        auto object = reinterpret_cast<ProcTableAsClass::Object*>(self);
        return object->procs->QueueWriteTexture(self, destination, data, dataSize, dataLayout, writeSize);
    }
    void ForwardQueueReference(WGPUQueue self) {
        auto object = reinterpret_cast<ProcTableAsClass::Object*>(self);
        return object->procs->QueueReference(self);
    }
    void ForwardQueueRelease(WGPUQueue self) {
        auto object = reinterpret_cast<ProcTableAsClass::Object*>(self);
        return object->procs->QueueRelease(self);
    }

    void ForwardRenderBundleReference(WGPURenderBundle self) {
        auto object = reinterpret_cast<ProcTableAsClass::Object*>(self);
        return object->procs->RenderBundleReference(self);
    }
    void ForwardRenderBundleRelease(WGPURenderBundle self) {
        auto object = reinterpret_cast<ProcTableAsClass::Object*>(self);
        return object->procs->RenderBundleRelease(self);
    }

    void ForwardRenderBundleEncoderDraw(WGPURenderBundleEncoder self, uint32_t vertexCount, uint32_t instanceCount, uint32_t firstVertex, uint32_t firstInstance) {
        auto object = reinterpret_cast<ProcTableAsClass::Object*>(self);
        return object->procs->RenderBundleEncoderDraw(self, vertexCount, instanceCount, firstVertex, firstInstance);
    }
    void ForwardRenderBundleEncoderDrawIndexed(WGPURenderBundleEncoder self, uint32_t indexCount, uint32_t instanceCount, uint32_t firstIndex, int32_t baseVertex, uint32_t firstInstance) {
        auto object = reinterpret_cast<ProcTableAsClass::Object*>(self);
        return object->procs->RenderBundleEncoderDrawIndexed(self, indexCount, instanceCount, firstIndex, baseVertex, firstInstance);
    }
    void ForwardRenderBundleEncoderDrawIndexedIndirect(WGPURenderBundleEncoder self, WGPUBuffer indirectBuffer, uint64_t indirectOffset) {
        auto object = reinterpret_cast<ProcTableAsClass::Object*>(self);
        return object->procs->RenderBundleEncoderDrawIndexedIndirect(self, indirectBuffer, indirectOffset);
    }
    void ForwardRenderBundleEncoderDrawIndirect(WGPURenderBundleEncoder self, WGPUBuffer indirectBuffer, uint64_t indirectOffset) {
        auto object = reinterpret_cast<ProcTableAsClass::Object*>(self);
        return object->procs->RenderBundleEncoderDrawIndirect(self, indirectBuffer, indirectOffset);
    }
    WGPURenderBundle ForwardRenderBundleEncoderFinish(WGPURenderBundleEncoder self, WGPURenderBundleDescriptor const * descriptor) {
        auto object = reinterpret_cast<ProcTableAsClass::Object*>(self);
        return object->procs->RenderBundleEncoderFinish(self, descriptor);
    }
    void ForwardRenderBundleEncoderInsertDebugMarker(WGPURenderBundleEncoder self, char const * markerLabel) {
        auto object = reinterpret_cast<ProcTableAsClass::Object*>(self);
        return object->procs->RenderBundleEncoderInsertDebugMarker(self, markerLabel);
    }
    void ForwardRenderBundleEncoderPopDebugGroup(WGPURenderBundleEncoder self) {
        auto object = reinterpret_cast<ProcTableAsClass::Object*>(self);
        return object->procs->RenderBundleEncoderPopDebugGroup(self);
    }
    void ForwardRenderBundleEncoderPushDebugGroup(WGPURenderBundleEncoder self, char const * groupLabel) {
        auto object = reinterpret_cast<ProcTableAsClass::Object*>(self);
        return object->procs->RenderBundleEncoderPushDebugGroup(self, groupLabel);
    }
    void ForwardRenderBundleEncoderSetBindGroup(WGPURenderBundleEncoder self, uint32_t groupIndex, WGPUBindGroup group, uint32_t dynamicOffsetCount, uint32_t const * dynamicOffsets) {
        auto object = reinterpret_cast<ProcTableAsClass::Object*>(self);
        return object->procs->RenderBundleEncoderSetBindGroup(self, groupIndex, group, dynamicOffsetCount, dynamicOffsets);
    }
    void ForwardRenderBundleEncoderSetIndexBuffer(WGPURenderBundleEncoder self, WGPUBuffer buffer, uint64_t offset, uint64_t size) {
        auto object = reinterpret_cast<ProcTableAsClass::Object*>(self);
        return object->procs->RenderBundleEncoderSetIndexBuffer(self, buffer, offset, size);
    }
    void ForwardRenderBundleEncoderSetIndexBufferWithFormat(WGPURenderBundleEncoder self, WGPUBuffer buffer, WGPUIndexFormat format, uint64_t offset, uint64_t size) {
        auto object = reinterpret_cast<ProcTableAsClass::Object*>(self);
        return object->procs->RenderBundleEncoderSetIndexBufferWithFormat(self, buffer, format, offset, size);
    }
    void ForwardRenderBundleEncoderSetPipeline(WGPURenderBundleEncoder self, WGPURenderPipeline pipeline) {
        auto object = reinterpret_cast<ProcTableAsClass::Object*>(self);
        return object->procs->RenderBundleEncoderSetPipeline(self, pipeline);
    }
    void ForwardRenderBundleEncoderSetVertexBuffer(WGPURenderBundleEncoder self, uint32_t slot, WGPUBuffer buffer, uint64_t offset, uint64_t size) {
        auto object = reinterpret_cast<ProcTableAsClass::Object*>(self);
        return object->procs->RenderBundleEncoderSetVertexBuffer(self, slot, buffer, offset, size);
    }
    void ForwardRenderBundleEncoderReference(WGPURenderBundleEncoder self) {
        auto object = reinterpret_cast<ProcTableAsClass::Object*>(self);
        return object->procs->RenderBundleEncoderReference(self);
    }
    void ForwardRenderBundleEncoderRelease(WGPURenderBundleEncoder self) {
        auto object = reinterpret_cast<ProcTableAsClass::Object*>(self);
        return object->procs->RenderBundleEncoderRelease(self);
    }

    void ForwardRenderPassEncoderDraw(WGPURenderPassEncoder self, uint32_t vertexCount, uint32_t instanceCount, uint32_t firstVertex, uint32_t firstInstance) {
        auto object = reinterpret_cast<ProcTableAsClass::Object*>(self);
        return object->procs->RenderPassEncoderDraw(self, vertexCount, instanceCount, firstVertex, firstInstance);
    }
    void ForwardRenderPassEncoderDrawIndexed(WGPURenderPassEncoder self, uint32_t indexCount, uint32_t instanceCount, uint32_t firstIndex, int32_t baseVertex, uint32_t firstInstance) {
        auto object = reinterpret_cast<ProcTableAsClass::Object*>(self);
        return object->procs->RenderPassEncoderDrawIndexed(self, indexCount, instanceCount, firstIndex, baseVertex, firstInstance);
    }
    void ForwardRenderPassEncoderDrawIndexedIndirect(WGPURenderPassEncoder self, WGPUBuffer indirectBuffer, uint64_t indirectOffset) {
        auto object = reinterpret_cast<ProcTableAsClass::Object*>(self);
        return object->procs->RenderPassEncoderDrawIndexedIndirect(self, indirectBuffer, indirectOffset);
    }
    void ForwardRenderPassEncoderDrawIndirect(WGPURenderPassEncoder self, WGPUBuffer indirectBuffer, uint64_t indirectOffset) {
        auto object = reinterpret_cast<ProcTableAsClass::Object*>(self);
        return object->procs->RenderPassEncoderDrawIndirect(self, indirectBuffer, indirectOffset);
    }
    void ForwardRenderPassEncoderEndPass(WGPURenderPassEncoder self) {
        auto object = reinterpret_cast<ProcTableAsClass::Object*>(self);
        return object->procs->RenderPassEncoderEndPass(self);
    }
    void ForwardRenderPassEncoderExecuteBundles(WGPURenderPassEncoder self, uint32_t bundlesCount, WGPURenderBundle const * bundles) {
        auto object = reinterpret_cast<ProcTableAsClass::Object*>(self);
        return object->procs->RenderPassEncoderExecuteBundles(self, bundlesCount, bundles);
    }
    void ForwardRenderPassEncoderInsertDebugMarker(WGPURenderPassEncoder self, char const * markerLabel) {
        auto object = reinterpret_cast<ProcTableAsClass::Object*>(self);
        return object->procs->RenderPassEncoderInsertDebugMarker(self, markerLabel);
    }
    void ForwardRenderPassEncoderPopDebugGroup(WGPURenderPassEncoder self) {
        auto object = reinterpret_cast<ProcTableAsClass::Object*>(self);
        return object->procs->RenderPassEncoderPopDebugGroup(self);
    }
    void ForwardRenderPassEncoderPushDebugGroup(WGPURenderPassEncoder self, char const * groupLabel) {
        auto object = reinterpret_cast<ProcTableAsClass::Object*>(self);
        return object->procs->RenderPassEncoderPushDebugGroup(self, groupLabel);
    }
    void ForwardRenderPassEncoderSetBindGroup(WGPURenderPassEncoder self, uint32_t groupIndex, WGPUBindGroup group, uint32_t dynamicOffsetCount, uint32_t const * dynamicOffsets) {
        auto object = reinterpret_cast<ProcTableAsClass::Object*>(self);
        return object->procs->RenderPassEncoderSetBindGroup(self, groupIndex, group, dynamicOffsetCount, dynamicOffsets);
    }
    void ForwardRenderPassEncoderSetBlendColor(WGPURenderPassEncoder self, WGPUColor const * color) {
        auto object = reinterpret_cast<ProcTableAsClass::Object*>(self);
        return object->procs->RenderPassEncoderSetBlendColor(self, color);
    }
    void ForwardRenderPassEncoderSetIndexBuffer(WGPURenderPassEncoder self, WGPUBuffer buffer, uint64_t offset, uint64_t size) {
        auto object = reinterpret_cast<ProcTableAsClass::Object*>(self);
        return object->procs->RenderPassEncoderSetIndexBuffer(self, buffer, offset, size);
    }
    void ForwardRenderPassEncoderSetIndexBufferWithFormat(WGPURenderPassEncoder self, WGPUBuffer buffer, WGPUIndexFormat format, uint64_t offset, uint64_t size) {
        auto object = reinterpret_cast<ProcTableAsClass::Object*>(self);
        return object->procs->RenderPassEncoderSetIndexBufferWithFormat(self, buffer, format, offset, size);
    }
    void ForwardRenderPassEncoderSetPipeline(WGPURenderPassEncoder self, WGPURenderPipeline pipeline) {
        auto object = reinterpret_cast<ProcTableAsClass::Object*>(self);
        return object->procs->RenderPassEncoderSetPipeline(self, pipeline);
    }
    void ForwardRenderPassEncoderSetScissorRect(WGPURenderPassEncoder self, uint32_t x, uint32_t y, uint32_t width, uint32_t height) {
        auto object = reinterpret_cast<ProcTableAsClass::Object*>(self);
        return object->procs->RenderPassEncoderSetScissorRect(self, x, y, width, height);
    }
    void ForwardRenderPassEncoderSetStencilReference(WGPURenderPassEncoder self, uint32_t reference) {
        auto object = reinterpret_cast<ProcTableAsClass::Object*>(self);
        return object->procs->RenderPassEncoderSetStencilReference(self, reference);
    }
    void ForwardRenderPassEncoderSetVertexBuffer(WGPURenderPassEncoder self, uint32_t slot, WGPUBuffer buffer, uint64_t offset, uint64_t size) {
        auto object = reinterpret_cast<ProcTableAsClass::Object*>(self);
        return object->procs->RenderPassEncoderSetVertexBuffer(self, slot, buffer, offset, size);
    }
    void ForwardRenderPassEncoderSetViewport(WGPURenderPassEncoder self, float x, float y, float width, float height, float minDepth, float maxDepth) {
        auto object = reinterpret_cast<ProcTableAsClass::Object*>(self);
        return object->procs->RenderPassEncoderSetViewport(self, x, y, width, height, minDepth, maxDepth);
    }
    void ForwardRenderPassEncoderWriteTimestamp(WGPURenderPassEncoder self, WGPUQuerySet querySet, uint32_t queryIndex) {
        auto object = reinterpret_cast<ProcTableAsClass::Object*>(self);
        return object->procs->RenderPassEncoderWriteTimestamp(self, querySet, queryIndex);
    }
    void ForwardRenderPassEncoderReference(WGPURenderPassEncoder self) {
        auto object = reinterpret_cast<ProcTableAsClass::Object*>(self);
        return object->procs->RenderPassEncoderReference(self);
    }
    void ForwardRenderPassEncoderRelease(WGPURenderPassEncoder self) {
        auto object = reinterpret_cast<ProcTableAsClass::Object*>(self);
        return object->procs->RenderPassEncoderRelease(self);
    }

    WGPUBindGroupLayout ForwardRenderPipelineGetBindGroupLayout(WGPURenderPipeline self, uint32_t groupIndex) {
        auto object = reinterpret_cast<ProcTableAsClass::Object*>(self);
        return object->procs->RenderPipelineGetBindGroupLayout(self, groupIndex);
    }
    void ForwardRenderPipelineReference(WGPURenderPipeline self) {
        auto object = reinterpret_cast<ProcTableAsClass::Object*>(self);
        return object->procs->RenderPipelineReference(self);
    }
    void ForwardRenderPipelineRelease(WGPURenderPipeline self) {
        auto object = reinterpret_cast<ProcTableAsClass::Object*>(self);
        return object->procs->RenderPipelineRelease(self);
    }

    void ForwardSamplerReference(WGPUSampler self) {
        auto object = reinterpret_cast<ProcTableAsClass::Object*>(self);
        return object->procs->SamplerReference(self);
    }
    void ForwardSamplerRelease(WGPUSampler self) {
        auto object = reinterpret_cast<ProcTableAsClass::Object*>(self);
        return object->procs->SamplerRelease(self);
    }

    void ForwardShaderModuleReference(WGPUShaderModule self) {
        auto object = reinterpret_cast<ProcTableAsClass::Object*>(self);
        return object->procs->ShaderModuleReference(self);
    }
    void ForwardShaderModuleRelease(WGPUShaderModule self) {
        auto object = reinterpret_cast<ProcTableAsClass::Object*>(self);
        return object->procs->ShaderModuleRelease(self);
    }

    void ForwardSurfaceReference(WGPUSurface self) {
        auto object = reinterpret_cast<ProcTableAsClass::Object*>(self);
        return object->procs->SurfaceReference(self);
    }
    void ForwardSurfaceRelease(WGPUSurface self) {
        auto object = reinterpret_cast<ProcTableAsClass::Object*>(self);
        return object->procs->SurfaceRelease(self);
    }

    void ForwardSwapChainConfigure(WGPUSwapChain self, WGPUTextureFormat format, WGPUTextureUsageFlags allowedUsage, uint32_t width, uint32_t height) {
        auto object = reinterpret_cast<ProcTableAsClass::Object*>(self);
        return object->procs->SwapChainConfigure(self, format, allowedUsage, width, height);
    }
    WGPUTextureView ForwardSwapChainGetCurrentTextureView(WGPUSwapChain self) {
        auto object = reinterpret_cast<ProcTableAsClass::Object*>(self);
        return object->procs->SwapChainGetCurrentTextureView(self);
    }
    void ForwardSwapChainPresent(WGPUSwapChain self) {
        auto object = reinterpret_cast<ProcTableAsClass::Object*>(self);
        return object->procs->SwapChainPresent(self);
    }
    void ForwardSwapChainReference(WGPUSwapChain self) {
        auto object = reinterpret_cast<ProcTableAsClass::Object*>(self);
        return object->procs->SwapChainReference(self);
    }
    void ForwardSwapChainRelease(WGPUSwapChain self) {
        auto object = reinterpret_cast<ProcTableAsClass::Object*>(self);
        return object->procs->SwapChainRelease(self);
    }

    WGPUTextureView ForwardTextureCreateView(WGPUTexture self, WGPUTextureViewDescriptor const * descriptor) {
        auto object = reinterpret_cast<ProcTableAsClass::Object*>(self);
        return object->procs->TextureCreateView(self, descriptor);
    }
    void ForwardTextureDestroy(WGPUTexture self) {
        auto object = reinterpret_cast<ProcTableAsClass::Object*>(self);
        return object->procs->TextureDestroy(self);
    }
    void ForwardTextureReference(WGPUTexture self) {
        auto object = reinterpret_cast<ProcTableAsClass::Object*>(self);
        return object->procs->TextureReference(self);
    }
    void ForwardTextureRelease(WGPUTexture self) {
        auto object = reinterpret_cast<ProcTableAsClass::Object*>(self);
        return object->procs->TextureRelease(self);
    }

    void ForwardTextureViewReference(WGPUTextureView self) {
        auto object = reinterpret_cast<ProcTableAsClass::Object*>(self);
        return object->procs->TextureViewReference(self);
    }
    void ForwardTextureViewRelease(WGPUTextureView self) {
        auto object = reinterpret_cast<ProcTableAsClass::Object*>(self);
        return object->procs->TextureViewRelease(self);
    }

}

ProcTableAsClass::~ProcTableAsClass() {
}

void ProcTableAsClass::GetProcTableAndDevice(DawnProcTable* table, WGPUDevice* device) {
    *device = GetNewDevice();

    table->bindGroupReference = reinterpret_cast<WGPUProcBindGroupReference>(ForwardBindGroupReference);
    table->bindGroupRelease = reinterpret_cast<WGPUProcBindGroupRelease>(ForwardBindGroupRelease);
    table->bindGroupLayoutReference = reinterpret_cast<WGPUProcBindGroupLayoutReference>(ForwardBindGroupLayoutReference);
    table->bindGroupLayoutRelease = reinterpret_cast<WGPUProcBindGroupLayoutRelease>(ForwardBindGroupLayoutRelease);
    table->bufferDestroy = reinterpret_cast<WGPUProcBufferDestroy>(ForwardBufferDestroy);
    table->bufferGetConstMappedRange = reinterpret_cast<WGPUProcBufferGetConstMappedRange>(ForwardBufferGetConstMappedRange);
    table->bufferGetMappedRange = reinterpret_cast<WGPUProcBufferGetMappedRange>(ForwardBufferGetMappedRange);
    table->bufferMapAsync = reinterpret_cast<WGPUProcBufferMapAsync>(ForwardBufferMapAsync);
    table->bufferUnmap = reinterpret_cast<WGPUProcBufferUnmap>(ForwardBufferUnmap);
    table->bufferReference = reinterpret_cast<WGPUProcBufferReference>(ForwardBufferReference);
    table->bufferRelease = reinterpret_cast<WGPUProcBufferRelease>(ForwardBufferRelease);
    table->commandBufferReference = reinterpret_cast<WGPUProcCommandBufferReference>(ForwardCommandBufferReference);
    table->commandBufferRelease = reinterpret_cast<WGPUProcCommandBufferRelease>(ForwardCommandBufferRelease);
    table->commandEncoderBeginComputePass = reinterpret_cast<WGPUProcCommandEncoderBeginComputePass>(ForwardCommandEncoderBeginComputePass);
    table->commandEncoderBeginRenderPass = reinterpret_cast<WGPUProcCommandEncoderBeginRenderPass>(ForwardCommandEncoderBeginRenderPass);
    table->commandEncoderCopyBufferToBuffer = reinterpret_cast<WGPUProcCommandEncoderCopyBufferToBuffer>(ForwardCommandEncoderCopyBufferToBuffer);
    table->commandEncoderCopyBufferToTexture = reinterpret_cast<WGPUProcCommandEncoderCopyBufferToTexture>(ForwardCommandEncoderCopyBufferToTexture);
    table->commandEncoderCopyTextureToBuffer = reinterpret_cast<WGPUProcCommandEncoderCopyTextureToBuffer>(ForwardCommandEncoderCopyTextureToBuffer);
    table->commandEncoderCopyTextureToTexture = reinterpret_cast<WGPUProcCommandEncoderCopyTextureToTexture>(ForwardCommandEncoderCopyTextureToTexture);
    table->commandEncoderFinish = reinterpret_cast<WGPUProcCommandEncoderFinish>(ForwardCommandEncoderFinish);
    table->commandEncoderInsertDebugMarker = reinterpret_cast<WGPUProcCommandEncoderInsertDebugMarker>(ForwardCommandEncoderInsertDebugMarker);
    table->commandEncoderPopDebugGroup = reinterpret_cast<WGPUProcCommandEncoderPopDebugGroup>(ForwardCommandEncoderPopDebugGroup);
    table->commandEncoderPushDebugGroup = reinterpret_cast<WGPUProcCommandEncoderPushDebugGroup>(ForwardCommandEncoderPushDebugGroup);
    table->commandEncoderResolveQuerySet = reinterpret_cast<WGPUProcCommandEncoderResolveQuerySet>(ForwardCommandEncoderResolveQuerySet);
    table->commandEncoderWriteTimestamp = reinterpret_cast<WGPUProcCommandEncoderWriteTimestamp>(ForwardCommandEncoderWriteTimestamp);
    table->commandEncoderReference = reinterpret_cast<WGPUProcCommandEncoderReference>(ForwardCommandEncoderReference);
    table->commandEncoderRelease = reinterpret_cast<WGPUProcCommandEncoderRelease>(ForwardCommandEncoderRelease);
    table->computePassEncoderDispatch = reinterpret_cast<WGPUProcComputePassEncoderDispatch>(ForwardComputePassEncoderDispatch);
    table->computePassEncoderDispatchIndirect = reinterpret_cast<WGPUProcComputePassEncoderDispatchIndirect>(ForwardComputePassEncoderDispatchIndirect);
    table->computePassEncoderEndPass = reinterpret_cast<WGPUProcComputePassEncoderEndPass>(ForwardComputePassEncoderEndPass);
    table->computePassEncoderInsertDebugMarker = reinterpret_cast<WGPUProcComputePassEncoderInsertDebugMarker>(ForwardComputePassEncoderInsertDebugMarker);
    table->computePassEncoderPopDebugGroup = reinterpret_cast<WGPUProcComputePassEncoderPopDebugGroup>(ForwardComputePassEncoderPopDebugGroup);
    table->computePassEncoderPushDebugGroup = reinterpret_cast<WGPUProcComputePassEncoderPushDebugGroup>(ForwardComputePassEncoderPushDebugGroup);
    table->computePassEncoderSetBindGroup = reinterpret_cast<WGPUProcComputePassEncoderSetBindGroup>(ForwardComputePassEncoderSetBindGroup);
    table->computePassEncoderSetPipeline = reinterpret_cast<WGPUProcComputePassEncoderSetPipeline>(ForwardComputePassEncoderSetPipeline);
    table->computePassEncoderWriteTimestamp = reinterpret_cast<WGPUProcComputePassEncoderWriteTimestamp>(ForwardComputePassEncoderWriteTimestamp);
    table->computePassEncoderReference = reinterpret_cast<WGPUProcComputePassEncoderReference>(ForwardComputePassEncoderReference);
    table->computePassEncoderRelease = reinterpret_cast<WGPUProcComputePassEncoderRelease>(ForwardComputePassEncoderRelease);
    table->computePipelineGetBindGroupLayout = reinterpret_cast<WGPUProcComputePipelineGetBindGroupLayout>(ForwardComputePipelineGetBindGroupLayout);
    table->computePipelineReference = reinterpret_cast<WGPUProcComputePipelineReference>(ForwardComputePipelineReference);
    table->computePipelineRelease = reinterpret_cast<WGPUProcComputePipelineRelease>(ForwardComputePipelineRelease);
    table->deviceCreateBindGroup = reinterpret_cast<WGPUProcDeviceCreateBindGroup>(ForwardDeviceCreateBindGroup);
    table->deviceCreateBindGroupLayout = reinterpret_cast<WGPUProcDeviceCreateBindGroupLayout>(ForwardDeviceCreateBindGroupLayout);
    table->deviceCreateBuffer = reinterpret_cast<WGPUProcDeviceCreateBuffer>(ForwardDeviceCreateBuffer);
    table->deviceCreateCommandEncoder = reinterpret_cast<WGPUProcDeviceCreateCommandEncoder>(ForwardDeviceCreateCommandEncoder);
    table->deviceCreateComputePipeline = reinterpret_cast<WGPUProcDeviceCreateComputePipeline>(ForwardDeviceCreateComputePipeline);
    table->deviceCreateErrorBuffer = reinterpret_cast<WGPUProcDeviceCreateErrorBuffer>(ForwardDeviceCreateErrorBuffer);
    table->deviceCreatePipelineLayout = reinterpret_cast<WGPUProcDeviceCreatePipelineLayout>(ForwardDeviceCreatePipelineLayout);
    table->deviceCreateQuerySet = reinterpret_cast<WGPUProcDeviceCreateQuerySet>(ForwardDeviceCreateQuerySet);
    table->deviceCreateReadyComputePipeline = reinterpret_cast<WGPUProcDeviceCreateReadyComputePipeline>(ForwardDeviceCreateReadyComputePipeline);
    table->deviceCreateReadyRenderPipeline = reinterpret_cast<WGPUProcDeviceCreateReadyRenderPipeline>(ForwardDeviceCreateReadyRenderPipeline);
    table->deviceCreateRenderBundleEncoder = reinterpret_cast<WGPUProcDeviceCreateRenderBundleEncoder>(ForwardDeviceCreateRenderBundleEncoder);
    table->deviceCreateRenderPipeline = reinterpret_cast<WGPUProcDeviceCreateRenderPipeline>(ForwardDeviceCreateRenderPipeline);
    table->deviceCreateSampler = reinterpret_cast<WGPUProcDeviceCreateSampler>(ForwardDeviceCreateSampler);
    table->deviceCreateShaderModule = reinterpret_cast<WGPUProcDeviceCreateShaderModule>(ForwardDeviceCreateShaderModule);
    table->deviceCreateSwapChain = reinterpret_cast<WGPUProcDeviceCreateSwapChain>(ForwardDeviceCreateSwapChain);
    table->deviceCreateTexture = reinterpret_cast<WGPUProcDeviceCreateTexture>(ForwardDeviceCreateTexture);
    table->deviceGetDefaultQueue = reinterpret_cast<WGPUProcDeviceGetDefaultQueue>(ForwardDeviceGetDefaultQueue);
    table->deviceInjectError = reinterpret_cast<WGPUProcDeviceInjectError>(ForwardDeviceInjectError);
    table->deviceLoseForTesting = reinterpret_cast<WGPUProcDeviceLoseForTesting>(ForwardDeviceLoseForTesting);
    table->devicePopErrorScope = reinterpret_cast<WGPUProcDevicePopErrorScope>(ForwardDevicePopErrorScope);
    table->devicePushErrorScope = reinterpret_cast<WGPUProcDevicePushErrorScope>(ForwardDevicePushErrorScope);
    table->deviceSetDeviceLostCallback = reinterpret_cast<WGPUProcDeviceSetDeviceLostCallback>(ForwardDeviceSetDeviceLostCallback);
    table->deviceSetUncapturedErrorCallback = reinterpret_cast<WGPUProcDeviceSetUncapturedErrorCallback>(ForwardDeviceSetUncapturedErrorCallback);
    table->deviceTick = reinterpret_cast<WGPUProcDeviceTick>(ForwardDeviceTick);
    table->deviceReference = reinterpret_cast<WGPUProcDeviceReference>(ForwardDeviceReference);
    table->deviceRelease = reinterpret_cast<WGPUProcDeviceRelease>(ForwardDeviceRelease);
    table->fenceGetCompletedValue = reinterpret_cast<WGPUProcFenceGetCompletedValue>(ForwardFenceGetCompletedValue);
    table->fenceOnCompletion = reinterpret_cast<WGPUProcFenceOnCompletion>(ForwardFenceOnCompletion);
    table->fenceReference = reinterpret_cast<WGPUProcFenceReference>(ForwardFenceReference);
    table->fenceRelease = reinterpret_cast<WGPUProcFenceRelease>(ForwardFenceRelease);
    table->instanceCreateSurface = reinterpret_cast<WGPUProcInstanceCreateSurface>(ForwardInstanceCreateSurface);
    table->instanceReference = reinterpret_cast<WGPUProcInstanceReference>(ForwardInstanceReference);
    table->instanceRelease = reinterpret_cast<WGPUProcInstanceRelease>(ForwardInstanceRelease);
    table->pipelineLayoutReference = reinterpret_cast<WGPUProcPipelineLayoutReference>(ForwardPipelineLayoutReference);
    table->pipelineLayoutRelease = reinterpret_cast<WGPUProcPipelineLayoutRelease>(ForwardPipelineLayoutRelease);
    table->querySetDestroy = reinterpret_cast<WGPUProcQuerySetDestroy>(ForwardQuerySetDestroy);
    table->querySetReference = reinterpret_cast<WGPUProcQuerySetReference>(ForwardQuerySetReference);
    table->querySetRelease = reinterpret_cast<WGPUProcQuerySetRelease>(ForwardQuerySetRelease);
    table->queueCreateFence = reinterpret_cast<WGPUProcQueueCreateFence>(ForwardQueueCreateFence);
    table->queueSignal = reinterpret_cast<WGPUProcQueueSignal>(ForwardQueueSignal);
    table->queueSubmit = reinterpret_cast<WGPUProcQueueSubmit>(ForwardQueueSubmit);
    table->queueWriteBuffer = reinterpret_cast<WGPUProcQueueWriteBuffer>(ForwardQueueWriteBuffer);
    table->queueWriteTexture = reinterpret_cast<WGPUProcQueueWriteTexture>(ForwardQueueWriteTexture);
    table->queueReference = reinterpret_cast<WGPUProcQueueReference>(ForwardQueueReference);
    table->queueRelease = reinterpret_cast<WGPUProcQueueRelease>(ForwardQueueRelease);
    table->renderBundleReference = reinterpret_cast<WGPUProcRenderBundleReference>(ForwardRenderBundleReference);
    table->renderBundleRelease = reinterpret_cast<WGPUProcRenderBundleRelease>(ForwardRenderBundleRelease);
    table->renderBundleEncoderDraw = reinterpret_cast<WGPUProcRenderBundleEncoderDraw>(ForwardRenderBundleEncoderDraw);
    table->renderBundleEncoderDrawIndexed = reinterpret_cast<WGPUProcRenderBundleEncoderDrawIndexed>(ForwardRenderBundleEncoderDrawIndexed);
    table->renderBundleEncoderDrawIndexedIndirect = reinterpret_cast<WGPUProcRenderBundleEncoderDrawIndexedIndirect>(ForwardRenderBundleEncoderDrawIndexedIndirect);
    table->renderBundleEncoderDrawIndirect = reinterpret_cast<WGPUProcRenderBundleEncoderDrawIndirect>(ForwardRenderBundleEncoderDrawIndirect);
    table->renderBundleEncoderFinish = reinterpret_cast<WGPUProcRenderBundleEncoderFinish>(ForwardRenderBundleEncoderFinish);
    table->renderBundleEncoderInsertDebugMarker = reinterpret_cast<WGPUProcRenderBundleEncoderInsertDebugMarker>(ForwardRenderBundleEncoderInsertDebugMarker);
    table->renderBundleEncoderPopDebugGroup = reinterpret_cast<WGPUProcRenderBundleEncoderPopDebugGroup>(ForwardRenderBundleEncoderPopDebugGroup);
    table->renderBundleEncoderPushDebugGroup = reinterpret_cast<WGPUProcRenderBundleEncoderPushDebugGroup>(ForwardRenderBundleEncoderPushDebugGroup);
    table->renderBundleEncoderSetBindGroup = reinterpret_cast<WGPUProcRenderBundleEncoderSetBindGroup>(ForwardRenderBundleEncoderSetBindGroup);
    table->renderBundleEncoderSetIndexBuffer = reinterpret_cast<WGPUProcRenderBundleEncoderSetIndexBuffer>(ForwardRenderBundleEncoderSetIndexBuffer);
    table->renderBundleEncoderSetIndexBufferWithFormat = reinterpret_cast<WGPUProcRenderBundleEncoderSetIndexBufferWithFormat>(ForwardRenderBundleEncoderSetIndexBufferWithFormat);
    table->renderBundleEncoderSetPipeline = reinterpret_cast<WGPUProcRenderBundleEncoderSetPipeline>(ForwardRenderBundleEncoderSetPipeline);
    table->renderBundleEncoderSetVertexBuffer = reinterpret_cast<WGPUProcRenderBundleEncoderSetVertexBuffer>(ForwardRenderBundleEncoderSetVertexBuffer);
    table->renderBundleEncoderReference = reinterpret_cast<WGPUProcRenderBundleEncoderReference>(ForwardRenderBundleEncoderReference);
    table->renderBundleEncoderRelease = reinterpret_cast<WGPUProcRenderBundleEncoderRelease>(ForwardRenderBundleEncoderRelease);
    table->renderPassEncoderDraw = reinterpret_cast<WGPUProcRenderPassEncoderDraw>(ForwardRenderPassEncoderDraw);
    table->renderPassEncoderDrawIndexed = reinterpret_cast<WGPUProcRenderPassEncoderDrawIndexed>(ForwardRenderPassEncoderDrawIndexed);
    table->renderPassEncoderDrawIndexedIndirect = reinterpret_cast<WGPUProcRenderPassEncoderDrawIndexedIndirect>(ForwardRenderPassEncoderDrawIndexedIndirect);
    table->renderPassEncoderDrawIndirect = reinterpret_cast<WGPUProcRenderPassEncoderDrawIndirect>(ForwardRenderPassEncoderDrawIndirect);
    table->renderPassEncoderEndPass = reinterpret_cast<WGPUProcRenderPassEncoderEndPass>(ForwardRenderPassEncoderEndPass);
    table->renderPassEncoderExecuteBundles = reinterpret_cast<WGPUProcRenderPassEncoderExecuteBundles>(ForwardRenderPassEncoderExecuteBundles);
    table->renderPassEncoderInsertDebugMarker = reinterpret_cast<WGPUProcRenderPassEncoderInsertDebugMarker>(ForwardRenderPassEncoderInsertDebugMarker);
    table->renderPassEncoderPopDebugGroup = reinterpret_cast<WGPUProcRenderPassEncoderPopDebugGroup>(ForwardRenderPassEncoderPopDebugGroup);
    table->renderPassEncoderPushDebugGroup = reinterpret_cast<WGPUProcRenderPassEncoderPushDebugGroup>(ForwardRenderPassEncoderPushDebugGroup);
    table->renderPassEncoderSetBindGroup = reinterpret_cast<WGPUProcRenderPassEncoderSetBindGroup>(ForwardRenderPassEncoderSetBindGroup);
    table->renderPassEncoderSetBlendColor = reinterpret_cast<WGPUProcRenderPassEncoderSetBlendColor>(ForwardRenderPassEncoderSetBlendColor);
    table->renderPassEncoderSetIndexBuffer = reinterpret_cast<WGPUProcRenderPassEncoderSetIndexBuffer>(ForwardRenderPassEncoderSetIndexBuffer);
    table->renderPassEncoderSetIndexBufferWithFormat = reinterpret_cast<WGPUProcRenderPassEncoderSetIndexBufferWithFormat>(ForwardRenderPassEncoderSetIndexBufferWithFormat);
    table->renderPassEncoderSetPipeline = reinterpret_cast<WGPUProcRenderPassEncoderSetPipeline>(ForwardRenderPassEncoderSetPipeline);
    table->renderPassEncoderSetScissorRect = reinterpret_cast<WGPUProcRenderPassEncoderSetScissorRect>(ForwardRenderPassEncoderSetScissorRect);
    table->renderPassEncoderSetStencilReference = reinterpret_cast<WGPUProcRenderPassEncoderSetStencilReference>(ForwardRenderPassEncoderSetStencilReference);
    table->renderPassEncoderSetVertexBuffer = reinterpret_cast<WGPUProcRenderPassEncoderSetVertexBuffer>(ForwardRenderPassEncoderSetVertexBuffer);
    table->renderPassEncoderSetViewport = reinterpret_cast<WGPUProcRenderPassEncoderSetViewport>(ForwardRenderPassEncoderSetViewport);
    table->renderPassEncoderWriteTimestamp = reinterpret_cast<WGPUProcRenderPassEncoderWriteTimestamp>(ForwardRenderPassEncoderWriteTimestamp);
    table->renderPassEncoderReference = reinterpret_cast<WGPUProcRenderPassEncoderReference>(ForwardRenderPassEncoderReference);
    table->renderPassEncoderRelease = reinterpret_cast<WGPUProcRenderPassEncoderRelease>(ForwardRenderPassEncoderRelease);
    table->renderPipelineGetBindGroupLayout = reinterpret_cast<WGPUProcRenderPipelineGetBindGroupLayout>(ForwardRenderPipelineGetBindGroupLayout);
    table->renderPipelineReference = reinterpret_cast<WGPUProcRenderPipelineReference>(ForwardRenderPipelineReference);
    table->renderPipelineRelease = reinterpret_cast<WGPUProcRenderPipelineRelease>(ForwardRenderPipelineRelease);
    table->samplerReference = reinterpret_cast<WGPUProcSamplerReference>(ForwardSamplerReference);
    table->samplerRelease = reinterpret_cast<WGPUProcSamplerRelease>(ForwardSamplerRelease);
    table->shaderModuleReference = reinterpret_cast<WGPUProcShaderModuleReference>(ForwardShaderModuleReference);
    table->shaderModuleRelease = reinterpret_cast<WGPUProcShaderModuleRelease>(ForwardShaderModuleRelease);
    table->surfaceReference = reinterpret_cast<WGPUProcSurfaceReference>(ForwardSurfaceReference);
    table->surfaceRelease = reinterpret_cast<WGPUProcSurfaceRelease>(ForwardSurfaceRelease);
    table->swapChainConfigure = reinterpret_cast<WGPUProcSwapChainConfigure>(ForwardSwapChainConfigure);
    table->swapChainGetCurrentTextureView = reinterpret_cast<WGPUProcSwapChainGetCurrentTextureView>(ForwardSwapChainGetCurrentTextureView);
    table->swapChainPresent = reinterpret_cast<WGPUProcSwapChainPresent>(ForwardSwapChainPresent);
    table->swapChainReference = reinterpret_cast<WGPUProcSwapChainReference>(ForwardSwapChainReference);
    table->swapChainRelease = reinterpret_cast<WGPUProcSwapChainRelease>(ForwardSwapChainRelease);
    table->textureCreateView = reinterpret_cast<WGPUProcTextureCreateView>(ForwardTextureCreateView);
    table->textureDestroy = reinterpret_cast<WGPUProcTextureDestroy>(ForwardTextureDestroy);
    table->textureReference = reinterpret_cast<WGPUProcTextureReference>(ForwardTextureReference);
    table->textureRelease = reinterpret_cast<WGPUProcTextureRelease>(ForwardTextureRelease);
    table->textureViewReference = reinterpret_cast<WGPUProcTextureViewReference>(ForwardTextureViewReference);
    table->textureViewRelease = reinterpret_cast<WGPUProcTextureViewRelease>(ForwardTextureViewRelease);
}

void ProcTableAsClass::DeviceSetUncapturedErrorCallback(WGPUDevice self,
                                                        WGPUErrorCallback callback,
                                                        void* userdata) {
    auto object = reinterpret_cast<ProcTableAsClass::Object*>(self);
    object->deviceErrorCallback = callback;
    object->userdata = userdata;

    OnDeviceSetUncapturedErrorCallback(self, callback, userdata);
}

void ProcTableAsClass::DeviceSetDeviceLostCallback(WGPUDevice self,
                                                   WGPUDeviceLostCallback callback,
                                                   void* userdata) {
    auto object = reinterpret_cast<ProcTableAsClass::Object*>(self);
    object->deviceLostCallback = callback;
    object->userdata = userdata;

    OnDeviceSetDeviceLostCallback(self, callback, userdata);
}

bool ProcTableAsClass::DevicePopErrorScope(WGPUDevice self,
                                           WGPUErrorCallback callback,
                                           void* userdata) {
    return OnDevicePopErrorScopeCallback(self, callback, userdata);
}

void ProcTableAsClass::BufferMapAsync(WGPUBuffer self,
                                      WGPUMapModeFlags mode,
                                      size_t offset,
                                      size_t size,
                                      WGPUBufferMapCallback callback,
                                      void* userdata) {
    auto object = reinterpret_cast<ProcTableAsClass::Object*>(self);
    object->mapAsyncCallback = callback;
    object->userdata = userdata;

    OnBufferMapAsyncCallback(self, callback, userdata);
}

void ProcTableAsClass::FenceOnCompletion(WGPUFence self,
                                         uint64_t value,
                                         WGPUFenceOnCompletionCallback callback,
                                         void* userdata) {
    auto object = reinterpret_cast<ProcTableAsClass::Object*>(self);
    object->fenceOnCompletionCallback = callback;
    object->userdata = userdata;

    OnFenceOnCompletionCallback(self, value, callback, userdata);
}

void ProcTableAsClass::DeviceCreateReadyComputePipeline(
    WGPUDevice self,
    WGPUComputePipelineDescriptor const * descriptor,
    WGPUCreateReadyComputePipelineCallback callback,
    void* userdata) {
    auto object = reinterpret_cast<ProcTableAsClass::Object*>(self);
    object->createReadyComputePipelineCallback = callback;
    object->userdata = userdata;

    OnDeviceCreateReadyComputePipelineCallback(self, descriptor, callback, userdata);
}

void ProcTableAsClass::DeviceCreateReadyRenderPipeline(
    WGPUDevice self,
    WGPURenderPipelineDescriptor const * descriptor,
    WGPUCreateReadyRenderPipelineCallback callback,
    void* userdata) {
    auto object = reinterpret_cast<ProcTableAsClass::Object*>(self);
    object->createReadyRenderPipelineCallback = callback;
    object->userdata = userdata;

    OnDeviceCreateReadyRenderPipelineCallback(self, descriptor, callback, userdata);
}

void ProcTableAsClass::CallDeviceErrorCallback(WGPUDevice device,
                                               WGPUErrorType type,
                                               const char* message) {
    auto object = reinterpret_cast<ProcTableAsClass::Object*>(device);
    object->deviceErrorCallback(type, message, object->userdata);
}

void ProcTableAsClass::CallDeviceLostCallback(WGPUDevice device, const char* message) {
    auto object = reinterpret_cast<ProcTableAsClass::Object*>(device);
    object->deviceLostCallback(message, object->userdata);
}

void ProcTableAsClass::CallMapAsyncCallback(WGPUBuffer buffer, WGPUBufferMapAsyncStatus status) {
    auto object = reinterpret_cast<ProcTableAsClass::Object*>(buffer);
    object->mapAsyncCallback(status, object->userdata);
}

void ProcTableAsClass::CallFenceOnCompletionCallback(WGPUFence fence,
                                                     WGPUFenceCompletionStatus status) {
    auto object = reinterpret_cast<ProcTableAsClass::Object*>(fence);
    object->fenceOnCompletionCallback(status, object->userdata);
}

void ProcTableAsClass::CallDeviceCreateReadyComputePipelineCallback(WGPUDevice device,
                                                                    WGPUCreateReadyPipelineStatus status,
                                                                    WGPUComputePipeline pipeline,
                                                                    const char* message) {
    auto object = reinterpret_cast<ProcTableAsClass::Object*>(device);
    object->createReadyComputePipelineCallback(status, pipeline, message, object->userdata);
}

void ProcTableAsClass::CallDeviceCreateReadyRenderPipelineCallback(WGPUDevice device,
                                                                   WGPUCreateReadyPipelineStatus status,
                                                                   WGPURenderPipeline pipeline,
                                                                   const char* message) {
    auto object = reinterpret_cast<ProcTableAsClass::Object*>(device);
    object->createReadyRenderPipelineCallback(status, pipeline, message, object->userdata);
}

WGPUBindGroup ProcTableAsClass::GetNewBindGroup() {
    mObjects.emplace_back(new Object);
    mObjects.back()->procs = this;
    return reinterpret_cast<WGPUBindGroup>(mObjects.back().get());
}
WGPUBindGroupLayout ProcTableAsClass::GetNewBindGroupLayout() {
    mObjects.emplace_back(new Object);
    mObjects.back()->procs = this;
    return reinterpret_cast<WGPUBindGroupLayout>(mObjects.back().get());
}
WGPUBuffer ProcTableAsClass::GetNewBuffer() {
    mObjects.emplace_back(new Object);
    mObjects.back()->procs = this;
    return reinterpret_cast<WGPUBuffer>(mObjects.back().get());
}
WGPUCommandBuffer ProcTableAsClass::GetNewCommandBuffer() {
    mObjects.emplace_back(new Object);
    mObjects.back()->procs = this;
    return reinterpret_cast<WGPUCommandBuffer>(mObjects.back().get());
}
WGPUCommandEncoder ProcTableAsClass::GetNewCommandEncoder() {
    mObjects.emplace_back(new Object);
    mObjects.back()->procs = this;
    return reinterpret_cast<WGPUCommandEncoder>(mObjects.back().get());
}
WGPUComputePassEncoder ProcTableAsClass::GetNewComputePassEncoder() {
    mObjects.emplace_back(new Object);
    mObjects.back()->procs = this;
    return reinterpret_cast<WGPUComputePassEncoder>(mObjects.back().get());
}
WGPUComputePipeline ProcTableAsClass::GetNewComputePipeline() {
    mObjects.emplace_back(new Object);
    mObjects.back()->procs = this;
    return reinterpret_cast<WGPUComputePipeline>(mObjects.back().get());
}
WGPUDevice ProcTableAsClass::GetNewDevice() {
    mObjects.emplace_back(new Object);
    mObjects.back()->procs = this;
    return reinterpret_cast<WGPUDevice>(mObjects.back().get());
}
WGPUFence ProcTableAsClass::GetNewFence() {
    mObjects.emplace_back(new Object);
    mObjects.back()->procs = this;
    return reinterpret_cast<WGPUFence>(mObjects.back().get());
}
WGPUInstance ProcTableAsClass::GetNewInstance() {
    mObjects.emplace_back(new Object);
    mObjects.back()->procs = this;
    return reinterpret_cast<WGPUInstance>(mObjects.back().get());
}
WGPUPipelineLayout ProcTableAsClass::GetNewPipelineLayout() {
    mObjects.emplace_back(new Object);
    mObjects.back()->procs = this;
    return reinterpret_cast<WGPUPipelineLayout>(mObjects.back().get());
}
WGPUQuerySet ProcTableAsClass::GetNewQuerySet() {
    mObjects.emplace_back(new Object);
    mObjects.back()->procs = this;
    return reinterpret_cast<WGPUQuerySet>(mObjects.back().get());
}
WGPUQueue ProcTableAsClass::GetNewQueue() {
    mObjects.emplace_back(new Object);
    mObjects.back()->procs = this;
    return reinterpret_cast<WGPUQueue>(mObjects.back().get());
}
WGPURenderBundle ProcTableAsClass::GetNewRenderBundle() {
    mObjects.emplace_back(new Object);
    mObjects.back()->procs = this;
    return reinterpret_cast<WGPURenderBundle>(mObjects.back().get());
}
WGPURenderBundleEncoder ProcTableAsClass::GetNewRenderBundleEncoder() {
    mObjects.emplace_back(new Object);
    mObjects.back()->procs = this;
    return reinterpret_cast<WGPURenderBundleEncoder>(mObjects.back().get());
}
WGPURenderPassEncoder ProcTableAsClass::GetNewRenderPassEncoder() {
    mObjects.emplace_back(new Object);
    mObjects.back()->procs = this;
    return reinterpret_cast<WGPURenderPassEncoder>(mObjects.back().get());
}
WGPURenderPipeline ProcTableAsClass::GetNewRenderPipeline() {
    mObjects.emplace_back(new Object);
    mObjects.back()->procs = this;
    return reinterpret_cast<WGPURenderPipeline>(mObjects.back().get());
}
WGPUSampler ProcTableAsClass::GetNewSampler() {
    mObjects.emplace_back(new Object);
    mObjects.back()->procs = this;
    return reinterpret_cast<WGPUSampler>(mObjects.back().get());
}
WGPUShaderModule ProcTableAsClass::GetNewShaderModule() {
    mObjects.emplace_back(new Object);
    mObjects.back()->procs = this;
    return reinterpret_cast<WGPUShaderModule>(mObjects.back().get());
}
WGPUSurface ProcTableAsClass::GetNewSurface() {
    mObjects.emplace_back(new Object);
    mObjects.back()->procs = this;
    return reinterpret_cast<WGPUSurface>(mObjects.back().get());
}
WGPUSwapChain ProcTableAsClass::GetNewSwapChain() {
    mObjects.emplace_back(new Object);
    mObjects.back()->procs = this;
    return reinterpret_cast<WGPUSwapChain>(mObjects.back().get());
}
WGPUTexture ProcTableAsClass::GetNewTexture() {
    mObjects.emplace_back(new Object);
    mObjects.back()->procs = this;
    return reinterpret_cast<WGPUTexture>(mObjects.back().get());
}
WGPUTextureView ProcTableAsClass::GetNewTextureView() {
    mObjects.emplace_back(new Object);
    mObjects.back()->procs = this;
    return reinterpret_cast<WGPUTextureView>(mObjects.back().get());
}

MockProcTable::MockProcTable() = default;

MockProcTable::~MockProcTable() = default;

void MockProcTable::IgnoreAllReleaseCalls() {
    EXPECT_CALL(*this, BindGroupRelease(_)).Times(AnyNumber());
    EXPECT_CALL(*this, BindGroupLayoutRelease(_)).Times(AnyNumber());
    EXPECT_CALL(*this, BufferRelease(_)).Times(AnyNumber());
    EXPECT_CALL(*this, CommandBufferRelease(_)).Times(AnyNumber());
    EXPECT_CALL(*this, CommandEncoderRelease(_)).Times(AnyNumber());
    EXPECT_CALL(*this, ComputePassEncoderRelease(_)).Times(AnyNumber());
    EXPECT_CALL(*this, ComputePipelineRelease(_)).Times(AnyNumber());
    EXPECT_CALL(*this, DeviceRelease(_)).Times(AnyNumber());
    EXPECT_CALL(*this, FenceRelease(_)).Times(AnyNumber());
    EXPECT_CALL(*this, InstanceRelease(_)).Times(AnyNumber());
    EXPECT_CALL(*this, PipelineLayoutRelease(_)).Times(AnyNumber());
    EXPECT_CALL(*this, QuerySetRelease(_)).Times(AnyNumber());
    EXPECT_CALL(*this, QueueRelease(_)).Times(AnyNumber());
    EXPECT_CALL(*this, RenderBundleRelease(_)).Times(AnyNumber());
    EXPECT_CALL(*this, RenderBundleEncoderRelease(_)).Times(AnyNumber());
    EXPECT_CALL(*this, RenderPassEncoderRelease(_)).Times(AnyNumber());
    EXPECT_CALL(*this, RenderPipelineRelease(_)).Times(AnyNumber());
    EXPECT_CALL(*this, SamplerRelease(_)).Times(AnyNumber());
    EXPECT_CALL(*this, ShaderModuleRelease(_)).Times(AnyNumber());
    EXPECT_CALL(*this, SurfaceRelease(_)).Times(AnyNumber());
    EXPECT_CALL(*this, SwapChainRelease(_)).Times(AnyNumber());
    EXPECT_CALL(*this, TextureRelease(_)).Times(AnyNumber());
    EXPECT_CALL(*this, TextureViewRelease(_)).Times(AnyNumber());
}
