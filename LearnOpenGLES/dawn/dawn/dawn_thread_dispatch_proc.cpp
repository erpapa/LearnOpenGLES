#include "dawn/dawn_thread_dispatch_proc.h"

#include <thread>

static DawnProcTable nullProcs;
thread_local DawnProcTable perThreadProcs;

void dawnProcSetPerThreadProcs(const DawnProcTable* procs) {
    if (procs) {
        perThreadProcs = *procs;
    } else {
        perThreadProcs = nullProcs;
    }
}

static WGPUProc ThreadDispatchGetProcAddress(WGPUDevice device, const char* procName) {
    return perThreadProcs.getProcAddress(device, procName);
}

static WGPUInstance ThreadDispatchCreateInstance(WGPUInstanceDescriptor const * descriptor) {
    return perThreadProcs.createInstance(descriptor);
}

static void ThreadDispatchBindGroupReference(WGPUBindGroup bindGroup) {
    perThreadProcs.bindGroupReference(bindGroup);
}
static void ThreadDispatchBindGroupRelease(WGPUBindGroup bindGroup) {
    perThreadProcs.bindGroupRelease(bindGroup);
}
static void ThreadDispatchBindGroupLayoutReference(WGPUBindGroupLayout bindGroupLayout) {
    perThreadProcs.bindGroupLayoutReference(bindGroupLayout);
}
static void ThreadDispatchBindGroupLayoutRelease(WGPUBindGroupLayout bindGroupLayout) {
    perThreadProcs.bindGroupLayoutRelease(bindGroupLayout);
}
static void ThreadDispatchBufferDestroy(WGPUBuffer buffer) {
    perThreadProcs.bufferDestroy(buffer);
}
static void const * ThreadDispatchBufferGetConstMappedRange(WGPUBuffer buffer, size_t offset, size_t size) {
return     perThreadProcs.bufferGetConstMappedRange(buffer, offset, size);
}
static void * ThreadDispatchBufferGetMappedRange(WGPUBuffer buffer, size_t offset, size_t size) {
return     perThreadProcs.bufferGetMappedRange(buffer, offset, size);
}
static void ThreadDispatchBufferMapAsync(WGPUBuffer buffer, WGPUMapModeFlags mode, size_t offset, size_t size, WGPUBufferMapCallback callback, void * userdata) {
    perThreadProcs.bufferMapAsync(buffer, mode, offset, size, callback, userdata);
}
static void ThreadDispatchBufferUnmap(WGPUBuffer buffer) {
    perThreadProcs.bufferUnmap(buffer);
}
static void ThreadDispatchBufferReference(WGPUBuffer buffer) {
    perThreadProcs.bufferReference(buffer);
}
static void ThreadDispatchBufferRelease(WGPUBuffer buffer) {
    perThreadProcs.bufferRelease(buffer);
}
static void ThreadDispatchCommandBufferReference(WGPUCommandBuffer commandBuffer) {
    perThreadProcs.commandBufferReference(commandBuffer);
}
static void ThreadDispatchCommandBufferRelease(WGPUCommandBuffer commandBuffer) {
    perThreadProcs.commandBufferRelease(commandBuffer);
}
static WGPUComputePassEncoder ThreadDispatchCommandEncoderBeginComputePass(WGPUCommandEncoder commandEncoder, WGPUComputePassDescriptor const * descriptor) {
return     perThreadProcs.commandEncoderBeginComputePass(commandEncoder, descriptor);
}
static WGPURenderPassEncoder ThreadDispatchCommandEncoderBeginRenderPass(WGPUCommandEncoder commandEncoder, WGPURenderPassDescriptor const * descriptor) {
return     perThreadProcs.commandEncoderBeginRenderPass(commandEncoder, descriptor);
}
static void ThreadDispatchCommandEncoderCopyBufferToBuffer(WGPUCommandEncoder commandEncoder, WGPUBuffer source, uint64_t sourceOffset, WGPUBuffer destination, uint64_t destinationOffset, uint64_t size) {
    perThreadProcs.commandEncoderCopyBufferToBuffer(commandEncoder, source, sourceOffset, destination, destinationOffset, size);
}
static void ThreadDispatchCommandEncoderCopyBufferToTexture(WGPUCommandEncoder commandEncoder, WGPUBufferCopyView const * source, WGPUTextureCopyView const * destination, WGPUExtent3D const * copySize) {
    perThreadProcs.commandEncoderCopyBufferToTexture(commandEncoder, source, destination, copySize);
}
static void ThreadDispatchCommandEncoderCopyTextureToBuffer(WGPUCommandEncoder commandEncoder, WGPUTextureCopyView const * source, WGPUBufferCopyView const * destination, WGPUExtent3D const * copySize) {
    perThreadProcs.commandEncoderCopyTextureToBuffer(commandEncoder, source, destination, copySize);
}
static void ThreadDispatchCommandEncoderCopyTextureToTexture(WGPUCommandEncoder commandEncoder, WGPUTextureCopyView const * source, WGPUTextureCopyView const * destination, WGPUExtent3D const * copySize) {
    perThreadProcs.commandEncoderCopyTextureToTexture(commandEncoder, source, destination, copySize);
}
static WGPUCommandBuffer ThreadDispatchCommandEncoderFinish(WGPUCommandEncoder commandEncoder, WGPUCommandBufferDescriptor const * descriptor) {
return     perThreadProcs.commandEncoderFinish(commandEncoder, descriptor);
}
static void ThreadDispatchCommandEncoderInsertDebugMarker(WGPUCommandEncoder commandEncoder, char const * markerLabel) {
    perThreadProcs.commandEncoderInsertDebugMarker(commandEncoder, markerLabel);
}
static void ThreadDispatchCommandEncoderPopDebugGroup(WGPUCommandEncoder commandEncoder) {
    perThreadProcs.commandEncoderPopDebugGroup(commandEncoder);
}
static void ThreadDispatchCommandEncoderPushDebugGroup(WGPUCommandEncoder commandEncoder, char const * groupLabel) {
    perThreadProcs.commandEncoderPushDebugGroup(commandEncoder, groupLabel);
}
static void ThreadDispatchCommandEncoderResolveQuerySet(WGPUCommandEncoder commandEncoder, WGPUQuerySet querySet, uint32_t firstQuery, uint32_t queryCount, WGPUBuffer destination, uint64_t destinationOffset) {
    perThreadProcs.commandEncoderResolveQuerySet(commandEncoder, querySet, firstQuery, queryCount, destination, destinationOffset);
}
static void ThreadDispatchCommandEncoderWriteTimestamp(WGPUCommandEncoder commandEncoder, WGPUQuerySet querySet, uint32_t queryIndex) {
    perThreadProcs.commandEncoderWriteTimestamp(commandEncoder, querySet, queryIndex);
}
static void ThreadDispatchCommandEncoderReference(WGPUCommandEncoder commandEncoder) {
    perThreadProcs.commandEncoderReference(commandEncoder);
}
static void ThreadDispatchCommandEncoderRelease(WGPUCommandEncoder commandEncoder) {
    perThreadProcs.commandEncoderRelease(commandEncoder);
}
static void ThreadDispatchComputePassEncoderDispatch(WGPUComputePassEncoder computePassEncoder, uint32_t x, uint32_t y, uint32_t z) {
    perThreadProcs.computePassEncoderDispatch(computePassEncoder, x, y, z);
}
static void ThreadDispatchComputePassEncoderDispatchIndirect(WGPUComputePassEncoder computePassEncoder, WGPUBuffer indirectBuffer, uint64_t indirectOffset) {
    perThreadProcs.computePassEncoderDispatchIndirect(computePassEncoder, indirectBuffer, indirectOffset);
}
static void ThreadDispatchComputePassEncoderEndPass(WGPUComputePassEncoder computePassEncoder) {
    perThreadProcs.computePassEncoderEndPass(computePassEncoder);
}
static void ThreadDispatchComputePassEncoderInsertDebugMarker(WGPUComputePassEncoder computePassEncoder, char const * markerLabel) {
    perThreadProcs.computePassEncoderInsertDebugMarker(computePassEncoder, markerLabel);
}
static void ThreadDispatchComputePassEncoderPopDebugGroup(WGPUComputePassEncoder computePassEncoder) {
    perThreadProcs.computePassEncoderPopDebugGroup(computePassEncoder);
}
static void ThreadDispatchComputePassEncoderPushDebugGroup(WGPUComputePassEncoder computePassEncoder, char const * groupLabel) {
    perThreadProcs.computePassEncoderPushDebugGroup(computePassEncoder, groupLabel);
}
static void ThreadDispatchComputePassEncoderSetBindGroup(WGPUComputePassEncoder computePassEncoder, uint32_t groupIndex, WGPUBindGroup group, uint32_t dynamicOffsetCount, uint32_t const * dynamicOffsets) {
    perThreadProcs.computePassEncoderSetBindGroup(computePassEncoder, groupIndex, group, dynamicOffsetCount, dynamicOffsets);
}
static void ThreadDispatchComputePassEncoderSetPipeline(WGPUComputePassEncoder computePassEncoder, WGPUComputePipeline pipeline) {
    perThreadProcs.computePassEncoderSetPipeline(computePassEncoder, pipeline);
}
static void ThreadDispatchComputePassEncoderWriteTimestamp(WGPUComputePassEncoder computePassEncoder, WGPUQuerySet querySet, uint32_t queryIndex) {
    perThreadProcs.computePassEncoderWriteTimestamp(computePassEncoder, querySet, queryIndex);
}
static void ThreadDispatchComputePassEncoderReference(WGPUComputePassEncoder computePassEncoder) {
    perThreadProcs.computePassEncoderReference(computePassEncoder);
}
static void ThreadDispatchComputePassEncoderRelease(WGPUComputePassEncoder computePassEncoder) {
    perThreadProcs.computePassEncoderRelease(computePassEncoder);
}
static WGPUBindGroupLayout ThreadDispatchComputePipelineGetBindGroupLayout(WGPUComputePipeline computePipeline, uint32_t groupIndex) {
return     perThreadProcs.computePipelineGetBindGroupLayout(computePipeline, groupIndex);
}
static void ThreadDispatchComputePipelineReference(WGPUComputePipeline computePipeline) {
    perThreadProcs.computePipelineReference(computePipeline);
}
static void ThreadDispatchComputePipelineRelease(WGPUComputePipeline computePipeline) {
    perThreadProcs.computePipelineRelease(computePipeline);
}
static WGPUBindGroup ThreadDispatchDeviceCreateBindGroup(WGPUDevice device, WGPUBindGroupDescriptor const * descriptor) {
return     perThreadProcs.deviceCreateBindGroup(device, descriptor);
}
static WGPUBindGroupLayout ThreadDispatchDeviceCreateBindGroupLayout(WGPUDevice device, WGPUBindGroupLayoutDescriptor const * descriptor) {
return     perThreadProcs.deviceCreateBindGroupLayout(device, descriptor);
}
static WGPUBuffer ThreadDispatchDeviceCreateBuffer(WGPUDevice device, WGPUBufferDescriptor const * descriptor) {
return     perThreadProcs.deviceCreateBuffer(device, descriptor);
}
static WGPUCommandEncoder ThreadDispatchDeviceCreateCommandEncoder(WGPUDevice device, WGPUCommandEncoderDescriptor const * descriptor) {
return     perThreadProcs.deviceCreateCommandEncoder(device, descriptor);
}
static WGPUComputePipeline ThreadDispatchDeviceCreateComputePipeline(WGPUDevice device, WGPUComputePipelineDescriptor const * descriptor) {
return     perThreadProcs.deviceCreateComputePipeline(device, descriptor);
}
static WGPUBuffer ThreadDispatchDeviceCreateErrorBuffer(WGPUDevice device) {
return     perThreadProcs.deviceCreateErrorBuffer(device);
}
static WGPUPipelineLayout ThreadDispatchDeviceCreatePipelineLayout(WGPUDevice device, WGPUPipelineLayoutDescriptor const * descriptor) {
return     perThreadProcs.deviceCreatePipelineLayout(device, descriptor);
}
static WGPUQuerySet ThreadDispatchDeviceCreateQuerySet(WGPUDevice device, WGPUQuerySetDescriptor const * descriptor) {
return     perThreadProcs.deviceCreateQuerySet(device, descriptor);
}
static void ThreadDispatchDeviceCreateReadyComputePipeline(WGPUDevice device, WGPUComputePipelineDescriptor const * descriptor, WGPUCreateReadyComputePipelineCallback callback, void * userdata) {
    perThreadProcs.deviceCreateReadyComputePipeline(device, descriptor, callback, userdata);
}
static void ThreadDispatchDeviceCreateReadyRenderPipeline(WGPUDevice device, WGPURenderPipelineDescriptor const * descriptor, WGPUCreateReadyRenderPipelineCallback callback, void * userdata) {
    perThreadProcs.deviceCreateReadyRenderPipeline(device, descriptor, callback, userdata);
}
static WGPURenderBundleEncoder ThreadDispatchDeviceCreateRenderBundleEncoder(WGPUDevice device, WGPURenderBundleEncoderDescriptor const * descriptor) {
return     perThreadProcs.deviceCreateRenderBundleEncoder(device, descriptor);
}
static WGPURenderPipeline ThreadDispatchDeviceCreateRenderPipeline(WGPUDevice device, WGPURenderPipelineDescriptor const * descriptor) {
return     perThreadProcs.deviceCreateRenderPipeline(device, descriptor);
}
static WGPUSampler ThreadDispatchDeviceCreateSampler(WGPUDevice device, WGPUSamplerDescriptor const * descriptor) {
return     perThreadProcs.deviceCreateSampler(device, descriptor);
}
static WGPUShaderModule ThreadDispatchDeviceCreateShaderModule(WGPUDevice device, WGPUShaderModuleDescriptor const * descriptor) {
return     perThreadProcs.deviceCreateShaderModule(device, descriptor);
}
static WGPUSwapChain ThreadDispatchDeviceCreateSwapChain(WGPUDevice device, WGPUSurface surface, WGPUSwapChainDescriptor const * descriptor) {
return     perThreadProcs.deviceCreateSwapChain(device, surface, descriptor);
}
static WGPUTexture ThreadDispatchDeviceCreateTexture(WGPUDevice device, WGPUTextureDescriptor const * descriptor) {
return     perThreadProcs.deviceCreateTexture(device, descriptor);
}
static WGPUQueue ThreadDispatchDeviceGetDefaultQueue(WGPUDevice device) {
return     perThreadProcs.deviceGetDefaultQueue(device);
}
static void ThreadDispatchDeviceInjectError(WGPUDevice device, WGPUErrorType type, char const * message) {
    perThreadProcs.deviceInjectError(device, type, message);
}
static void ThreadDispatchDeviceLoseForTesting(WGPUDevice device) {
    perThreadProcs.deviceLoseForTesting(device);
}
static bool ThreadDispatchDevicePopErrorScope(WGPUDevice device, WGPUErrorCallback callback, void * userdata) {
return     perThreadProcs.devicePopErrorScope(device, callback, userdata);
}
static void ThreadDispatchDevicePushErrorScope(WGPUDevice device, WGPUErrorFilter filter) {
    perThreadProcs.devicePushErrorScope(device, filter);
}
static void ThreadDispatchDeviceSetDeviceLostCallback(WGPUDevice device, WGPUDeviceLostCallback callback, void * userdata) {
    perThreadProcs.deviceSetDeviceLostCallback(device, callback, userdata);
}
static void ThreadDispatchDeviceSetUncapturedErrorCallback(WGPUDevice device, WGPUErrorCallback callback, void * userdata) {
    perThreadProcs.deviceSetUncapturedErrorCallback(device, callback, userdata);
}
static void ThreadDispatchDeviceTick(WGPUDevice device) {
    perThreadProcs.deviceTick(device);
}
static void ThreadDispatchDeviceReference(WGPUDevice device) {
    perThreadProcs.deviceReference(device);
}
static void ThreadDispatchDeviceRelease(WGPUDevice device) {
    perThreadProcs.deviceRelease(device);
}
static uint64_t ThreadDispatchFenceGetCompletedValue(WGPUFence fence) {
return     perThreadProcs.fenceGetCompletedValue(fence);
}
static void ThreadDispatchFenceOnCompletion(WGPUFence fence, uint64_t value, WGPUFenceOnCompletionCallback callback, void * userdata) {
    perThreadProcs.fenceOnCompletion(fence, value, callback, userdata);
}
static void ThreadDispatchFenceReference(WGPUFence fence) {
    perThreadProcs.fenceReference(fence);
}
static void ThreadDispatchFenceRelease(WGPUFence fence) {
    perThreadProcs.fenceRelease(fence);
}
static WGPUSurface ThreadDispatchInstanceCreateSurface(WGPUInstance instance, WGPUSurfaceDescriptor const * descriptor) {
return     perThreadProcs.instanceCreateSurface(instance, descriptor);
}
static void ThreadDispatchInstanceReference(WGPUInstance instance) {
    perThreadProcs.instanceReference(instance);
}
static void ThreadDispatchInstanceRelease(WGPUInstance instance) {
    perThreadProcs.instanceRelease(instance);
}
static void ThreadDispatchPipelineLayoutReference(WGPUPipelineLayout pipelineLayout) {
    perThreadProcs.pipelineLayoutReference(pipelineLayout);
}
static void ThreadDispatchPipelineLayoutRelease(WGPUPipelineLayout pipelineLayout) {
    perThreadProcs.pipelineLayoutRelease(pipelineLayout);
}
static void ThreadDispatchQuerySetDestroy(WGPUQuerySet querySet) {
    perThreadProcs.querySetDestroy(querySet);
}
static void ThreadDispatchQuerySetReference(WGPUQuerySet querySet) {
    perThreadProcs.querySetReference(querySet);
}
static void ThreadDispatchQuerySetRelease(WGPUQuerySet querySet) {
    perThreadProcs.querySetRelease(querySet);
}
static WGPUFence ThreadDispatchQueueCreateFence(WGPUQueue queue, WGPUFenceDescriptor const * descriptor) {
return     perThreadProcs.queueCreateFence(queue, descriptor);
}
static void ThreadDispatchQueueSignal(WGPUQueue queue, WGPUFence fence, uint64_t signalValue) {
    perThreadProcs.queueSignal(queue, fence, signalValue);
}
static void ThreadDispatchQueueSubmit(WGPUQueue queue, uint32_t commandCount, WGPUCommandBuffer const * commands) {
    perThreadProcs.queueSubmit(queue, commandCount, commands);
}
static void ThreadDispatchQueueWriteBuffer(WGPUQueue queue, WGPUBuffer buffer, uint64_t bufferOffset, void const * data, size_t size) {
    perThreadProcs.queueWriteBuffer(queue, buffer, bufferOffset, data, size);
}
static void ThreadDispatchQueueWriteTexture(WGPUQueue queue, WGPUTextureCopyView const * destination, void const * data, size_t dataSize, WGPUTextureDataLayout const * dataLayout, WGPUExtent3D const * writeSize) {
    perThreadProcs.queueWriteTexture(queue, destination, data, dataSize, dataLayout, writeSize);
}
static void ThreadDispatchQueueReference(WGPUQueue queue) {
    perThreadProcs.queueReference(queue);
}
static void ThreadDispatchQueueRelease(WGPUQueue queue) {
    perThreadProcs.queueRelease(queue);
}
static void ThreadDispatchRenderBundleReference(WGPURenderBundle renderBundle) {
    perThreadProcs.renderBundleReference(renderBundle);
}
static void ThreadDispatchRenderBundleRelease(WGPURenderBundle renderBundle) {
    perThreadProcs.renderBundleRelease(renderBundle);
}
static void ThreadDispatchRenderBundleEncoderDraw(WGPURenderBundleEncoder renderBundleEncoder, uint32_t vertexCount, uint32_t instanceCount, uint32_t firstVertex, uint32_t firstInstance) {
    perThreadProcs.renderBundleEncoderDraw(renderBundleEncoder, vertexCount, instanceCount, firstVertex, firstInstance);
}
static void ThreadDispatchRenderBundleEncoderDrawIndexed(WGPURenderBundleEncoder renderBundleEncoder, uint32_t indexCount, uint32_t instanceCount, uint32_t firstIndex, int32_t baseVertex, uint32_t firstInstance) {
    perThreadProcs.renderBundleEncoderDrawIndexed(renderBundleEncoder, indexCount, instanceCount, firstIndex, baseVertex, firstInstance);
}
static void ThreadDispatchRenderBundleEncoderDrawIndexedIndirect(WGPURenderBundleEncoder renderBundleEncoder, WGPUBuffer indirectBuffer, uint64_t indirectOffset) {
    perThreadProcs.renderBundleEncoderDrawIndexedIndirect(renderBundleEncoder, indirectBuffer, indirectOffset);
}
static void ThreadDispatchRenderBundleEncoderDrawIndirect(WGPURenderBundleEncoder renderBundleEncoder, WGPUBuffer indirectBuffer, uint64_t indirectOffset) {
    perThreadProcs.renderBundleEncoderDrawIndirect(renderBundleEncoder, indirectBuffer, indirectOffset);
}
static WGPURenderBundle ThreadDispatchRenderBundleEncoderFinish(WGPURenderBundleEncoder renderBundleEncoder, WGPURenderBundleDescriptor const * descriptor) {
return     perThreadProcs.renderBundleEncoderFinish(renderBundleEncoder, descriptor);
}
static void ThreadDispatchRenderBundleEncoderInsertDebugMarker(WGPURenderBundleEncoder renderBundleEncoder, char const * markerLabel) {
    perThreadProcs.renderBundleEncoderInsertDebugMarker(renderBundleEncoder, markerLabel);
}
static void ThreadDispatchRenderBundleEncoderPopDebugGroup(WGPURenderBundleEncoder renderBundleEncoder) {
    perThreadProcs.renderBundleEncoderPopDebugGroup(renderBundleEncoder);
}
static void ThreadDispatchRenderBundleEncoderPushDebugGroup(WGPURenderBundleEncoder renderBundleEncoder, char const * groupLabel) {
    perThreadProcs.renderBundleEncoderPushDebugGroup(renderBundleEncoder, groupLabel);
}
static void ThreadDispatchRenderBundleEncoderSetBindGroup(WGPURenderBundleEncoder renderBundleEncoder, uint32_t groupIndex, WGPUBindGroup group, uint32_t dynamicOffsetCount, uint32_t const * dynamicOffsets) {
    perThreadProcs.renderBundleEncoderSetBindGroup(renderBundleEncoder, groupIndex, group, dynamicOffsetCount, dynamicOffsets);
}
static void ThreadDispatchRenderBundleEncoderSetIndexBuffer(WGPURenderBundleEncoder renderBundleEncoder, WGPUBuffer buffer, uint64_t offset, uint64_t size) {
    perThreadProcs.renderBundleEncoderSetIndexBuffer(renderBundleEncoder, buffer, offset, size);
}
static void ThreadDispatchRenderBundleEncoderSetIndexBufferWithFormat(WGPURenderBundleEncoder renderBundleEncoder, WGPUBuffer buffer, WGPUIndexFormat format, uint64_t offset, uint64_t size) {
    perThreadProcs.renderBundleEncoderSetIndexBufferWithFormat(renderBundleEncoder, buffer, format, offset, size);
}
static void ThreadDispatchRenderBundleEncoderSetPipeline(WGPURenderBundleEncoder renderBundleEncoder, WGPURenderPipeline pipeline) {
    perThreadProcs.renderBundleEncoderSetPipeline(renderBundleEncoder, pipeline);
}
static void ThreadDispatchRenderBundleEncoderSetVertexBuffer(WGPURenderBundleEncoder renderBundleEncoder, uint32_t slot, WGPUBuffer buffer, uint64_t offset, uint64_t size) {
    perThreadProcs.renderBundleEncoderSetVertexBuffer(renderBundleEncoder, slot, buffer, offset, size);
}
static void ThreadDispatchRenderBundleEncoderReference(WGPURenderBundleEncoder renderBundleEncoder) {
    perThreadProcs.renderBundleEncoderReference(renderBundleEncoder);
}
static void ThreadDispatchRenderBundleEncoderRelease(WGPURenderBundleEncoder renderBundleEncoder) {
    perThreadProcs.renderBundleEncoderRelease(renderBundleEncoder);
}
static void ThreadDispatchRenderPassEncoderDraw(WGPURenderPassEncoder renderPassEncoder, uint32_t vertexCount, uint32_t instanceCount, uint32_t firstVertex, uint32_t firstInstance) {
    perThreadProcs.renderPassEncoderDraw(renderPassEncoder, vertexCount, instanceCount, firstVertex, firstInstance);
}
static void ThreadDispatchRenderPassEncoderDrawIndexed(WGPURenderPassEncoder renderPassEncoder, uint32_t indexCount, uint32_t instanceCount, uint32_t firstIndex, int32_t baseVertex, uint32_t firstInstance) {
    perThreadProcs.renderPassEncoderDrawIndexed(renderPassEncoder, indexCount, instanceCount, firstIndex, baseVertex, firstInstance);
}
static void ThreadDispatchRenderPassEncoderDrawIndexedIndirect(WGPURenderPassEncoder renderPassEncoder, WGPUBuffer indirectBuffer, uint64_t indirectOffset) {
    perThreadProcs.renderPassEncoderDrawIndexedIndirect(renderPassEncoder, indirectBuffer, indirectOffset);
}
static void ThreadDispatchRenderPassEncoderDrawIndirect(WGPURenderPassEncoder renderPassEncoder, WGPUBuffer indirectBuffer, uint64_t indirectOffset) {
    perThreadProcs.renderPassEncoderDrawIndirect(renderPassEncoder, indirectBuffer, indirectOffset);
}
static void ThreadDispatchRenderPassEncoderEndPass(WGPURenderPassEncoder renderPassEncoder) {
    perThreadProcs.renderPassEncoderEndPass(renderPassEncoder);
}
static void ThreadDispatchRenderPassEncoderExecuteBundles(WGPURenderPassEncoder renderPassEncoder, uint32_t bundlesCount, WGPURenderBundle const * bundles) {
    perThreadProcs.renderPassEncoderExecuteBundles(renderPassEncoder, bundlesCount, bundles);
}
static void ThreadDispatchRenderPassEncoderInsertDebugMarker(WGPURenderPassEncoder renderPassEncoder, char const * markerLabel) {
    perThreadProcs.renderPassEncoderInsertDebugMarker(renderPassEncoder, markerLabel);
}
static void ThreadDispatchRenderPassEncoderPopDebugGroup(WGPURenderPassEncoder renderPassEncoder) {
    perThreadProcs.renderPassEncoderPopDebugGroup(renderPassEncoder);
}
static void ThreadDispatchRenderPassEncoderPushDebugGroup(WGPURenderPassEncoder renderPassEncoder, char const * groupLabel) {
    perThreadProcs.renderPassEncoderPushDebugGroup(renderPassEncoder, groupLabel);
}
static void ThreadDispatchRenderPassEncoderSetBindGroup(WGPURenderPassEncoder renderPassEncoder, uint32_t groupIndex, WGPUBindGroup group, uint32_t dynamicOffsetCount, uint32_t const * dynamicOffsets) {
    perThreadProcs.renderPassEncoderSetBindGroup(renderPassEncoder, groupIndex, group, dynamicOffsetCount, dynamicOffsets);
}
static void ThreadDispatchRenderPassEncoderSetBlendColor(WGPURenderPassEncoder renderPassEncoder, WGPUColor const * color) {
    perThreadProcs.renderPassEncoderSetBlendColor(renderPassEncoder, color);
}
static void ThreadDispatchRenderPassEncoderSetIndexBuffer(WGPURenderPassEncoder renderPassEncoder, WGPUBuffer buffer, uint64_t offset, uint64_t size) {
    perThreadProcs.renderPassEncoderSetIndexBuffer(renderPassEncoder, buffer, offset, size);
}
static void ThreadDispatchRenderPassEncoderSetIndexBufferWithFormat(WGPURenderPassEncoder renderPassEncoder, WGPUBuffer buffer, WGPUIndexFormat format, uint64_t offset, uint64_t size) {
    perThreadProcs.renderPassEncoderSetIndexBufferWithFormat(renderPassEncoder, buffer, format, offset, size);
}
static void ThreadDispatchRenderPassEncoderSetPipeline(WGPURenderPassEncoder renderPassEncoder, WGPURenderPipeline pipeline) {
    perThreadProcs.renderPassEncoderSetPipeline(renderPassEncoder, pipeline);
}
static void ThreadDispatchRenderPassEncoderSetScissorRect(WGPURenderPassEncoder renderPassEncoder, uint32_t x, uint32_t y, uint32_t width, uint32_t height) {
    perThreadProcs.renderPassEncoderSetScissorRect(renderPassEncoder, x, y, width, height);
}
static void ThreadDispatchRenderPassEncoderSetStencilReference(WGPURenderPassEncoder renderPassEncoder, uint32_t reference) {
    perThreadProcs.renderPassEncoderSetStencilReference(renderPassEncoder, reference);
}
static void ThreadDispatchRenderPassEncoderSetVertexBuffer(WGPURenderPassEncoder renderPassEncoder, uint32_t slot, WGPUBuffer buffer, uint64_t offset, uint64_t size) {
    perThreadProcs.renderPassEncoderSetVertexBuffer(renderPassEncoder, slot, buffer, offset, size);
}
static void ThreadDispatchRenderPassEncoderSetViewport(WGPURenderPassEncoder renderPassEncoder, float x, float y, float width, float height, float minDepth, float maxDepth) {
    perThreadProcs.renderPassEncoderSetViewport(renderPassEncoder, x, y, width, height, minDepth, maxDepth);
}
static void ThreadDispatchRenderPassEncoderWriteTimestamp(WGPURenderPassEncoder renderPassEncoder, WGPUQuerySet querySet, uint32_t queryIndex) {
    perThreadProcs.renderPassEncoderWriteTimestamp(renderPassEncoder, querySet, queryIndex);
}
static void ThreadDispatchRenderPassEncoderReference(WGPURenderPassEncoder renderPassEncoder) {
    perThreadProcs.renderPassEncoderReference(renderPassEncoder);
}
static void ThreadDispatchRenderPassEncoderRelease(WGPURenderPassEncoder renderPassEncoder) {
    perThreadProcs.renderPassEncoderRelease(renderPassEncoder);
}
static WGPUBindGroupLayout ThreadDispatchRenderPipelineGetBindGroupLayout(WGPURenderPipeline renderPipeline, uint32_t groupIndex) {
return     perThreadProcs.renderPipelineGetBindGroupLayout(renderPipeline, groupIndex);
}
static void ThreadDispatchRenderPipelineReference(WGPURenderPipeline renderPipeline) {
    perThreadProcs.renderPipelineReference(renderPipeline);
}
static void ThreadDispatchRenderPipelineRelease(WGPURenderPipeline renderPipeline) {
    perThreadProcs.renderPipelineRelease(renderPipeline);
}
static void ThreadDispatchSamplerReference(WGPUSampler sampler) {
    perThreadProcs.samplerReference(sampler);
}
static void ThreadDispatchSamplerRelease(WGPUSampler sampler) {
    perThreadProcs.samplerRelease(sampler);
}
static void ThreadDispatchShaderModuleReference(WGPUShaderModule shaderModule) {
    perThreadProcs.shaderModuleReference(shaderModule);
}
static void ThreadDispatchShaderModuleRelease(WGPUShaderModule shaderModule) {
    perThreadProcs.shaderModuleRelease(shaderModule);
}
static void ThreadDispatchSurfaceReference(WGPUSurface surface) {
    perThreadProcs.surfaceReference(surface);
}
static void ThreadDispatchSurfaceRelease(WGPUSurface surface) {
    perThreadProcs.surfaceRelease(surface);
}
static void ThreadDispatchSwapChainConfigure(WGPUSwapChain swapChain, WGPUTextureFormat format, WGPUTextureUsageFlags allowedUsage, uint32_t width, uint32_t height) {
    perThreadProcs.swapChainConfigure(swapChain, format, allowedUsage, width, height);
}
static WGPUTextureView ThreadDispatchSwapChainGetCurrentTextureView(WGPUSwapChain swapChain) {
return     perThreadProcs.swapChainGetCurrentTextureView(swapChain);
}
static void ThreadDispatchSwapChainPresent(WGPUSwapChain swapChain) {
    perThreadProcs.swapChainPresent(swapChain);
}
static void ThreadDispatchSwapChainReference(WGPUSwapChain swapChain) {
    perThreadProcs.swapChainReference(swapChain);
}
static void ThreadDispatchSwapChainRelease(WGPUSwapChain swapChain) {
    perThreadProcs.swapChainRelease(swapChain);
}
static WGPUTextureView ThreadDispatchTextureCreateView(WGPUTexture texture, WGPUTextureViewDescriptor const * descriptor) {
return     perThreadProcs.textureCreateView(texture, descriptor);
}
static void ThreadDispatchTextureDestroy(WGPUTexture texture) {
    perThreadProcs.textureDestroy(texture);
}
static void ThreadDispatchTextureReference(WGPUTexture texture) {
    perThreadProcs.textureReference(texture);
}
static void ThreadDispatchTextureRelease(WGPUTexture texture) {
    perThreadProcs.textureRelease(texture);
}
static void ThreadDispatchTextureViewReference(WGPUTextureView textureView) {
    perThreadProcs.textureViewReference(textureView);
}
static void ThreadDispatchTextureViewRelease(WGPUTextureView textureView) {
    perThreadProcs.textureViewRelease(textureView);
}

extern "C" {
    DawnProcTable dawnThreadDispatchProcTable = {
        ThreadDispatchGetProcAddress,
        ThreadDispatchCreateInstance,
ThreadDispatchBindGroupReference,
ThreadDispatchBindGroupRelease,
ThreadDispatchBindGroupLayoutReference,
ThreadDispatchBindGroupLayoutRelease,
ThreadDispatchBufferDestroy,
ThreadDispatchBufferGetConstMappedRange,
ThreadDispatchBufferGetMappedRange,
ThreadDispatchBufferMapAsync,
ThreadDispatchBufferUnmap,
ThreadDispatchBufferReference,
ThreadDispatchBufferRelease,
ThreadDispatchCommandBufferReference,
ThreadDispatchCommandBufferRelease,
ThreadDispatchCommandEncoderBeginComputePass,
ThreadDispatchCommandEncoderBeginRenderPass,
ThreadDispatchCommandEncoderCopyBufferToBuffer,
ThreadDispatchCommandEncoderCopyBufferToTexture,
ThreadDispatchCommandEncoderCopyTextureToBuffer,
ThreadDispatchCommandEncoderCopyTextureToTexture,
ThreadDispatchCommandEncoderFinish,
ThreadDispatchCommandEncoderInsertDebugMarker,
ThreadDispatchCommandEncoderPopDebugGroup,
ThreadDispatchCommandEncoderPushDebugGroup,
ThreadDispatchCommandEncoderResolveQuerySet,
ThreadDispatchCommandEncoderWriteTimestamp,
ThreadDispatchCommandEncoderReference,
ThreadDispatchCommandEncoderRelease,
ThreadDispatchComputePassEncoderDispatch,
ThreadDispatchComputePassEncoderDispatchIndirect,
ThreadDispatchComputePassEncoderEndPass,
ThreadDispatchComputePassEncoderInsertDebugMarker,
ThreadDispatchComputePassEncoderPopDebugGroup,
ThreadDispatchComputePassEncoderPushDebugGroup,
ThreadDispatchComputePassEncoderSetBindGroup,
ThreadDispatchComputePassEncoderSetPipeline,
ThreadDispatchComputePassEncoderWriteTimestamp,
ThreadDispatchComputePassEncoderReference,
ThreadDispatchComputePassEncoderRelease,
ThreadDispatchComputePipelineGetBindGroupLayout,
ThreadDispatchComputePipelineReference,
ThreadDispatchComputePipelineRelease,
ThreadDispatchDeviceCreateBindGroup,
ThreadDispatchDeviceCreateBindGroupLayout,
ThreadDispatchDeviceCreateBuffer,
ThreadDispatchDeviceCreateCommandEncoder,
ThreadDispatchDeviceCreateComputePipeline,
ThreadDispatchDeviceCreateErrorBuffer,
ThreadDispatchDeviceCreatePipelineLayout,
ThreadDispatchDeviceCreateQuerySet,
ThreadDispatchDeviceCreateReadyComputePipeline,
ThreadDispatchDeviceCreateReadyRenderPipeline,
ThreadDispatchDeviceCreateRenderBundleEncoder,
ThreadDispatchDeviceCreateRenderPipeline,
ThreadDispatchDeviceCreateSampler,
ThreadDispatchDeviceCreateShaderModule,
ThreadDispatchDeviceCreateSwapChain,
ThreadDispatchDeviceCreateTexture,
ThreadDispatchDeviceGetDefaultQueue,
ThreadDispatchDeviceInjectError,
ThreadDispatchDeviceLoseForTesting,
ThreadDispatchDevicePopErrorScope,
ThreadDispatchDevicePushErrorScope,
ThreadDispatchDeviceSetDeviceLostCallback,
ThreadDispatchDeviceSetUncapturedErrorCallback,
ThreadDispatchDeviceTick,
ThreadDispatchDeviceReference,
ThreadDispatchDeviceRelease,
ThreadDispatchFenceGetCompletedValue,
ThreadDispatchFenceOnCompletion,
ThreadDispatchFenceReference,
ThreadDispatchFenceRelease,
ThreadDispatchInstanceCreateSurface,
ThreadDispatchInstanceReference,
ThreadDispatchInstanceRelease,
ThreadDispatchPipelineLayoutReference,
ThreadDispatchPipelineLayoutRelease,
ThreadDispatchQuerySetDestroy,
ThreadDispatchQuerySetReference,
ThreadDispatchQuerySetRelease,
ThreadDispatchQueueCreateFence,
ThreadDispatchQueueSignal,
ThreadDispatchQueueSubmit,
ThreadDispatchQueueWriteBuffer,
ThreadDispatchQueueWriteTexture,
ThreadDispatchQueueReference,
ThreadDispatchQueueRelease,
ThreadDispatchRenderBundleReference,
ThreadDispatchRenderBundleRelease,
ThreadDispatchRenderBundleEncoderDraw,
ThreadDispatchRenderBundleEncoderDrawIndexed,
ThreadDispatchRenderBundleEncoderDrawIndexedIndirect,
ThreadDispatchRenderBundleEncoderDrawIndirect,
ThreadDispatchRenderBundleEncoderFinish,
ThreadDispatchRenderBundleEncoderInsertDebugMarker,
ThreadDispatchRenderBundleEncoderPopDebugGroup,
ThreadDispatchRenderBundleEncoderPushDebugGroup,
ThreadDispatchRenderBundleEncoderSetBindGroup,
ThreadDispatchRenderBundleEncoderSetIndexBuffer,
ThreadDispatchRenderBundleEncoderSetIndexBufferWithFormat,
ThreadDispatchRenderBundleEncoderSetPipeline,
ThreadDispatchRenderBundleEncoderSetVertexBuffer,
ThreadDispatchRenderBundleEncoderReference,
ThreadDispatchRenderBundleEncoderRelease,
ThreadDispatchRenderPassEncoderDraw,
ThreadDispatchRenderPassEncoderDrawIndexed,
ThreadDispatchRenderPassEncoderDrawIndexedIndirect,
ThreadDispatchRenderPassEncoderDrawIndirect,
ThreadDispatchRenderPassEncoderEndPass,
ThreadDispatchRenderPassEncoderExecuteBundles,
ThreadDispatchRenderPassEncoderInsertDebugMarker,
ThreadDispatchRenderPassEncoderPopDebugGroup,
ThreadDispatchRenderPassEncoderPushDebugGroup,
ThreadDispatchRenderPassEncoderSetBindGroup,
ThreadDispatchRenderPassEncoderSetBlendColor,
ThreadDispatchRenderPassEncoderSetIndexBuffer,
ThreadDispatchRenderPassEncoderSetIndexBufferWithFormat,
ThreadDispatchRenderPassEncoderSetPipeline,
ThreadDispatchRenderPassEncoderSetScissorRect,
ThreadDispatchRenderPassEncoderSetStencilReference,
ThreadDispatchRenderPassEncoderSetVertexBuffer,
ThreadDispatchRenderPassEncoderSetViewport,
ThreadDispatchRenderPassEncoderWriteTimestamp,
ThreadDispatchRenderPassEncoderReference,
ThreadDispatchRenderPassEncoderRelease,
ThreadDispatchRenderPipelineGetBindGroupLayout,
ThreadDispatchRenderPipelineReference,
ThreadDispatchRenderPipelineRelease,
ThreadDispatchSamplerReference,
ThreadDispatchSamplerRelease,
ThreadDispatchShaderModuleReference,
ThreadDispatchShaderModuleRelease,
ThreadDispatchSurfaceReference,
ThreadDispatchSurfaceRelease,
ThreadDispatchSwapChainConfigure,
ThreadDispatchSwapChainGetCurrentTextureView,
ThreadDispatchSwapChainPresent,
ThreadDispatchSwapChainReference,
ThreadDispatchSwapChainRelease,
ThreadDispatchTextureCreateView,
ThreadDispatchTextureDestroy,
ThreadDispatchTextureReference,
ThreadDispatchTextureRelease,
ThreadDispatchTextureViewReference,
ThreadDispatchTextureViewRelease,
    };
}
