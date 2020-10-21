
// Command handlers & doers
bool HandleBufferDestroy(const volatile char** commands, size_t* size);

bool DoBufferDestroy(WGPUBuffer self);
bool HandleBufferMapAsync(const volatile char** commands, size_t* size);

bool DoBufferMapAsync(ObjectId bufferId, uint32_t requestSerial, WGPUMapModeFlags mode, size_t offset, size_t size, uint64_t handleCreateInfoLength, uint8_t const * handleCreateInfo);
bool HandleBufferUnmap(const volatile char** commands, size_t* size);

bool DoBufferUnmap(WGPUBuffer self);
bool HandleBufferUpdateMappedData(const volatile char** commands, size_t* size);

bool DoBufferUpdateMappedData(ObjectId bufferId, uint64_t writeFlushInfoLength, uint8_t const * writeFlushInfo);
bool HandleCommandEncoderBeginComputePass(const volatile char** commands, size_t* size);

bool DoCommandEncoderBeginComputePass(WGPUCommandEncoder self, WGPUComputePassDescriptor const * descriptor, WGPUComputePassEncoder* result);
bool HandleCommandEncoderBeginRenderPass(const volatile char** commands, size_t* size);

bool DoCommandEncoderBeginRenderPass(WGPUCommandEncoder self, WGPURenderPassDescriptor const * descriptor, WGPURenderPassEncoder* result);
bool HandleCommandEncoderCopyBufferToBuffer(const volatile char** commands, size_t* size);

bool DoCommandEncoderCopyBufferToBuffer(WGPUCommandEncoder self, WGPUBuffer source, uint64_t sourceOffset, WGPUBuffer destination, uint64_t destinationOffset, uint64_t size);
bool HandleCommandEncoderCopyBufferToTexture(const volatile char** commands, size_t* size);

bool DoCommandEncoderCopyBufferToTexture(WGPUCommandEncoder self, WGPUBufferCopyView const * source, WGPUTextureCopyView const * destination, WGPUExtent3D const * copySize);
bool HandleCommandEncoderCopyTextureToBuffer(const volatile char** commands, size_t* size);

bool DoCommandEncoderCopyTextureToBuffer(WGPUCommandEncoder self, WGPUTextureCopyView const * source, WGPUBufferCopyView const * destination, WGPUExtent3D const * copySize);
bool HandleCommandEncoderCopyTextureToTexture(const volatile char** commands, size_t* size);

bool DoCommandEncoderCopyTextureToTexture(WGPUCommandEncoder self, WGPUTextureCopyView const * source, WGPUTextureCopyView const * destination, WGPUExtent3D const * copySize);
bool HandleCommandEncoderFinish(const volatile char** commands, size_t* size);

bool DoCommandEncoderFinish(WGPUCommandEncoder self, WGPUCommandBufferDescriptor const * descriptor, WGPUCommandBuffer* result);
bool HandleCommandEncoderInsertDebugMarker(const volatile char** commands, size_t* size);

bool DoCommandEncoderInsertDebugMarker(WGPUCommandEncoder self, char const * markerLabel);
bool HandleCommandEncoderPopDebugGroup(const volatile char** commands, size_t* size);

bool DoCommandEncoderPopDebugGroup(WGPUCommandEncoder self);
bool HandleCommandEncoderPushDebugGroup(const volatile char** commands, size_t* size);

bool DoCommandEncoderPushDebugGroup(WGPUCommandEncoder self, char const * groupLabel);
bool HandleCommandEncoderResolveQuerySet(const volatile char** commands, size_t* size);

bool DoCommandEncoderResolveQuerySet(WGPUCommandEncoder self, WGPUQuerySet querySet, uint32_t firstQuery, uint32_t queryCount, WGPUBuffer destination, uint64_t destinationOffset);
bool HandleCommandEncoderWriteTimestamp(const volatile char** commands, size_t* size);

bool DoCommandEncoderWriteTimestamp(WGPUCommandEncoder self, WGPUQuerySet querySet, uint32_t queryIndex);
bool HandleComputePassEncoderDispatch(const volatile char** commands, size_t* size);

bool DoComputePassEncoderDispatch(WGPUComputePassEncoder self, uint32_t x, uint32_t y, uint32_t z);
bool HandleComputePassEncoderDispatchIndirect(const volatile char** commands, size_t* size);

bool DoComputePassEncoderDispatchIndirect(WGPUComputePassEncoder self, WGPUBuffer indirectBuffer, uint64_t indirectOffset);
bool HandleComputePassEncoderEndPass(const volatile char** commands, size_t* size);

bool DoComputePassEncoderEndPass(WGPUComputePassEncoder self);
bool HandleComputePassEncoderInsertDebugMarker(const volatile char** commands, size_t* size);

bool DoComputePassEncoderInsertDebugMarker(WGPUComputePassEncoder self, char const * markerLabel);
bool HandleComputePassEncoderPopDebugGroup(const volatile char** commands, size_t* size);

bool DoComputePassEncoderPopDebugGroup(WGPUComputePassEncoder self);
bool HandleComputePassEncoderPushDebugGroup(const volatile char** commands, size_t* size);

bool DoComputePassEncoderPushDebugGroup(WGPUComputePassEncoder self, char const * groupLabel);
bool HandleComputePassEncoderSetBindGroup(const volatile char** commands, size_t* size);

bool DoComputePassEncoderSetBindGroup(WGPUComputePassEncoder self, uint32_t groupIndex, WGPUBindGroup group, uint32_t dynamicOffsetCount, uint32_t const * dynamicOffsets);
bool HandleComputePassEncoderSetPipeline(const volatile char** commands, size_t* size);

bool DoComputePassEncoderSetPipeline(WGPUComputePassEncoder self, WGPUComputePipeline pipeline);
bool HandleComputePassEncoderWriteTimestamp(const volatile char** commands, size_t* size);

bool DoComputePassEncoderWriteTimestamp(WGPUComputePassEncoder self, WGPUQuerySet querySet, uint32_t queryIndex);
bool HandleComputePipelineGetBindGroupLayout(const volatile char** commands, size_t* size);

bool DoComputePipelineGetBindGroupLayout(WGPUComputePipeline self, uint32_t groupIndex, WGPUBindGroupLayout* result);
bool HandleDestroyObject(const volatile char** commands, size_t* size);

bool DoDestroyObject(ObjectType objectType, ObjectId objectId);
bool HandleDeviceCreateBindGroup(const volatile char** commands, size_t* size);

bool DoDeviceCreateBindGroup(WGPUDevice self, WGPUBindGroupDescriptor const * descriptor, WGPUBindGroup* result);
bool HandleDeviceCreateBindGroupLayout(const volatile char** commands, size_t* size);

bool DoDeviceCreateBindGroupLayout(WGPUDevice self, WGPUBindGroupLayoutDescriptor const * descriptor, WGPUBindGroupLayout* result);
bool HandleDeviceCreateBuffer(const volatile char** commands, size_t* size);

bool DoDeviceCreateBuffer(WGPUDevice device, WGPUBufferDescriptor const * descriptor, ObjectHandle result, uint64_t handleCreateInfoLength, uint8_t const * handleCreateInfo);
bool HandleDeviceCreateCommandEncoder(const volatile char** commands, size_t* size);

bool DoDeviceCreateCommandEncoder(WGPUDevice self, WGPUCommandEncoderDescriptor const * descriptor, WGPUCommandEncoder* result);
bool HandleDeviceCreateComputePipeline(const volatile char** commands, size_t* size);

bool DoDeviceCreateComputePipeline(WGPUDevice self, WGPUComputePipelineDescriptor const * descriptor, WGPUComputePipeline* result);
bool HandleDeviceCreateErrorBuffer(const volatile char** commands, size_t* size);

bool DoDeviceCreateErrorBuffer(WGPUDevice self, WGPUBuffer* result);
bool HandleDeviceCreatePipelineLayout(const volatile char** commands, size_t* size);

bool DoDeviceCreatePipelineLayout(WGPUDevice self, WGPUPipelineLayoutDescriptor const * descriptor, WGPUPipelineLayout* result);
bool HandleDeviceCreateQuerySet(const volatile char** commands, size_t* size);

bool DoDeviceCreateQuerySet(WGPUDevice self, WGPUQuerySetDescriptor const * descriptor, WGPUQuerySet* result);
bool HandleDeviceCreateReadyComputePipeline(const volatile char** commands, size_t* size);

bool DoDeviceCreateReadyComputePipeline(WGPUDevice device, uint64_t requestSerial, ObjectHandle pipelineObjectHandle, WGPUComputePipelineDescriptor const * descriptor);
bool HandleDeviceCreateReadyRenderPipeline(const volatile char** commands, size_t* size);

bool DoDeviceCreateReadyRenderPipeline(WGPUDevice device, uint64_t requestSerial, ObjectHandle pipelineObjectHandle, WGPURenderPipelineDescriptor const * descriptor);
bool HandleDeviceCreateRenderBundleEncoder(const volatile char** commands, size_t* size);

bool DoDeviceCreateRenderBundleEncoder(WGPUDevice self, WGPURenderBundleEncoderDescriptor const * descriptor, WGPURenderBundleEncoder* result);
bool HandleDeviceCreateRenderPipeline(const volatile char** commands, size_t* size);

bool DoDeviceCreateRenderPipeline(WGPUDevice self, WGPURenderPipelineDescriptor const * descriptor, WGPURenderPipeline* result);
bool HandleDeviceCreateSampler(const volatile char** commands, size_t* size);

bool DoDeviceCreateSampler(WGPUDevice self, WGPUSamplerDescriptor const * descriptor, WGPUSampler* result);
bool HandleDeviceCreateShaderModule(const volatile char** commands, size_t* size);

bool DoDeviceCreateShaderModule(WGPUDevice self, WGPUShaderModuleDescriptor const * descriptor, WGPUShaderModule* result);
bool HandleDeviceCreateSwapChain(const volatile char** commands, size_t* size);

bool DoDeviceCreateSwapChain(WGPUDevice self, WGPUSurface surface, WGPUSwapChainDescriptor const * descriptor, WGPUSwapChain* result);
bool HandleDeviceCreateTexture(const volatile char** commands, size_t* size);

bool DoDeviceCreateTexture(WGPUDevice self, WGPUTextureDescriptor const * descriptor, WGPUTexture* result);
bool HandleDeviceGetDefaultQueue(const volatile char** commands, size_t* size);

bool DoDeviceGetDefaultQueue(WGPUDevice self, WGPUQueue* result);
bool HandleDeviceInjectError(const volatile char** commands, size_t* size);

bool DoDeviceInjectError(WGPUDevice self, WGPUErrorType type, char const * message);
bool HandleDeviceLoseForTesting(const volatile char** commands, size_t* size);

bool DoDeviceLoseForTesting(WGPUDevice self);
bool HandleDevicePopErrorScope(const volatile char** commands, size_t* size);

bool DoDevicePopErrorScope(WGPUDevice device, uint64_t requestSerial);
bool HandleDevicePushErrorScope(const volatile char** commands, size_t* size);

bool DoDevicePushErrorScope(WGPUDevice self, WGPUErrorFilter filter);
bool HandleDeviceTick(const volatile char** commands, size_t* size);

bool DoDeviceTick(WGPUDevice self);
bool HandleFenceOnCompletion(const volatile char** commands, size_t* size);

bool DoFenceOnCompletion(ObjectId fenceId, uint64_t value, uint64_t requestSerial);
bool HandleInstanceCreateSurface(const volatile char** commands, size_t* size);

bool DoInstanceCreateSurface(WGPUInstance self, WGPUSurfaceDescriptor const * descriptor, WGPUSurface* result);
bool HandleQuerySetDestroy(const volatile char** commands, size_t* size);

bool DoQuerySetDestroy(WGPUQuerySet self);
bool HandleQueueCreateFence(const volatile char** commands, size_t* size);

bool DoQueueCreateFence(WGPUQueue self, WGPUFenceDescriptor const * descriptor, WGPUFence* result);
bool HandleQueueSignal(const volatile char** commands, size_t* size);

bool DoQueueSignal(WGPUQueue self, WGPUFence fence, uint64_t signalValue);
bool HandleQueueSubmit(const volatile char** commands, size_t* size);

bool DoQueueSubmit(WGPUQueue self, uint32_t commandCount, WGPUCommandBuffer const * commands);
bool HandleQueueWriteBufferInternal(const volatile char** commands, size_t* size);

bool DoQueueWriteBufferInternal(ObjectId queueId, ObjectId bufferId, uint64_t bufferOffset, uint8_t const * data, size_t size);
bool HandleQueueWriteTextureInternal(const volatile char** commands, size_t* size);

bool DoQueueWriteTextureInternal(ObjectId queueId, WGPUTextureCopyView const * destination, uint8_t const * data, size_t dataSize, WGPUTextureDataLayout const * dataLayout, WGPUExtent3D const * writeSize);
bool HandleRenderBundleEncoderDraw(const volatile char** commands, size_t* size);

bool DoRenderBundleEncoderDraw(WGPURenderBundleEncoder self, uint32_t vertexCount, uint32_t instanceCount, uint32_t firstVertex, uint32_t firstInstance);
bool HandleRenderBundleEncoderDrawIndexed(const volatile char** commands, size_t* size);

bool DoRenderBundleEncoderDrawIndexed(WGPURenderBundleEncoder self, uint32_t indexCount, uint32_t instanceCount, uint32_t firstIndex, int32_t baseVertex, uint32_t firstInstance);
bool HandleRenderBundleEncoderDrawIndexedIndirect(const volatile char** commands, size_t* size);

bool DoRenderBundleEncoderDrawIndexedIndirect(WGPURenderBundleEncoder self, WGPUBuffer indirectBuffer, uint64_t indirectOffset);
bool HandleRenderBundleEncoderDrawIndirect(const volatile char** commands, size_t* size);

bool DoRenderBundleEncoderDrawIndirect(WGPURenderBundleEncoder self, WGPUBuffer indirectBuffer, uint64_t indirectOffset);
bool HandleRenderBundleEncoderFinish(const volatile char** commands, size_t* size);

bool DoRenderBundleEncoderFinish(WGPURenderBundleEncoder self, WGPURenderBundleDescriptor const * descriptor, WGPURenderBundle* result);
bool HandleRenderBundleEncoderInsertDebugMarker(const volatile char** commands, size_t* size);

bool DoRenderBundleEncoderInsertDebugMarker(WGPURenderBundleEncoder self, char const * markerLabel);
bool HandleRenderBundleEncoderPopDebugGroup(const volatile char** commands, size_t* size);

bool DoRenderBundleEncoderPopDebugGroup(WGPURenderBundleEncoder self);
bool HandleRenderBundleEncoderPushDebugGroup(const volatile char** commands, size_t* size);

bool DoRenderBundleEncoderPushDebugGroup(WGPURenderBundleEncoder self, char const * groupLabel);
bool HandleRenderBundleEncoderSetBindGroup(const volatile char** commands, size_t* size);

bool DoRenderBundleEncoderSetBindGroup(WGPURenderBundleEncoder self, uint32_t groupIndex, WGPUBindGroup group, uint32_t dynamicOffsetCount, uint32_t const * dynamicOffsets);
bool HandleRenderBundleEncoderSetIndexBuffer(const volatile char** commands, size_t* size);

bool DoRenderBundleEncoderSetIndexBuffer(WGPURenderBundleEncoder self, WGPUBuffer buffer, uint64_t offset, uint64_t size);
bool HandleRenderBundleEncoderSetIndexBufferWithFormat(const volatile char** commands, size_t* size);

bool DoRenderBundleEncoderSetIndexBufferWithFormat(WGPURenderBundleEncoder self, WGPUBuffer buffer, WGPUIndexFormat format, uint64_t offset, uint64_t size);
bool HandleRenderBundleEncoderSetPipeline(const volatile char** commands, size_t* size);

bool DoRenderBundleEncoderSetPipeline(WGPURenderBundleEncoder self, WGPURenderPipeline pipeline);
bool HandleRenderBundleEncoderSetVertexBuffer(const volatile char** commands, size_t* size);

bool DoRenderBundleEncoderSetVertexBuffer(WGPURenderBundleEncoder self, uint32_t slot, WGPUBuffer buffer, uint64_t offset, uint64_t size);
bool HandleRenderPassEncoderDraw(const volatile char** commands, size_t* size);

bool DoRenderPassEncoderDraw(WGPURenderPassEncoder self, uint32_t vertexCount, uint32_t instanceCount, uint32_t firstVertex, uint32_t firstInstance);
bool HandleRenderPassEncoderDrawIndexed(const volatile char** commands, size_t* size);

bool DoRenderPassEncoderDrawIndexed(WGPURenderPassEncoder self, uint32_t indexCount, uint32_t instanceCount, uint32_t firstIndex, int32_t baseVertex, uint32_t firstInstance);
bool HandleRenderPassEncoderDrawIndexedIndirect(const volatile char** commands, size_t* size);

bool DoRenderPassEncoderDrawIndexedIndirect(WGPURenderPassEncoder self, WGPUBuffer indirectBuffer, uint64_t indirectOffset);
bool HandleRenderPassEncoderDrawIndirect(const volatile char** commands, size_t* size);

bool DoRenderPassEncoderDrawIndirect(WGPURenderPassEncoder self, WGPUBuffer indirectBuffer, uint64_t indirectOffset);
bool HandleRenderPassEncoderEndPass(const volatile char** commands, size_t* size);

bool DoRenderPassEncoderEndPass(WGPURenderPassEncoder self);
bool HandleRenderPassEncoderExecuteBundles(const volatile char** commands, size_t* size);

bool DoRenderPassEncoderExecuteBundles(WGPURenderPassEncoder self, uint32_t bundlesCount, WGPURenderBundle const * bundles);
bool HandleRenderPassEncoderInsertDebugMarker(const volatile char** commands, size_t* size);

bool DoRenderPassEncoderInsertDebugMarker(WGPURenderPassEncoder self, char const * markerLabel);
bool HandleRenderPassEncoderPopDebugGroup(const volatile char** commands, size_t* size);

bool DoRenderPassEncoderPopDebugGroup(WGPURenderPassEncoder self);
bool HandleRenderPassEncoderPushDebugGroup(const volatile char** commands, size_t* size);

bool DoRenderPassEncoderPushDebugGroup(WGPURenderPassEncoder self, char const * groupLabel);
bool HandleRenderPassEncoderSetBindGroup(const volatile char** commands, size_t* size);

bool DoRenderPassEncoderSetBindGroup(WGPURenderPassEncoder self, uint32_t groupIndex, WGPUBindGroup group, uint32_t dynamicOffsetCount, uint32_t const * dynamicOffsets);
bool HandleRenderPassEncoderSetBlendColor(const volatile char** commands, size_t* size);

bool DoRenderPassEncoderSetBlendColor(WGPURenderPassEncoder self, WGPUColor const * color);
bool HandleRenderPassEncoderSetIndexBuffer(const volatile char** commands, size_t* size);

bool DoRenderPassEncoderSetIndexBuffer(WGPURenderPassEncoder self, WGPUBuffer buffer, uint64_t offset, uint64_t size);
bool HandleRenderPassEncoderSetIndexBufferWithFormat(const volatile char** commands, size_t* size);

bool DoRenderPassEncoderSetIndexBufferWithFormat(WGPURenderPassEncoder self, WGPUBuffer buffer, WGPUIndexFormat format, uint64_t offset, uint64_t size);
bool HandleRenderPassEncoderSetPipeline(const volatile char** commands, size_t* size);

bool DoRenderPassEncoderSetPipeline(WGPURenderPassEncoder self, WGPURenderPipeline pipeline);
bool HandleRenderPassEncoderSetScissorRect(const volatile char** commands, size_t* size);

bool DoRenderPassEncoderSetScissorRect(WGPURenderPassEncoder self, uint32_t x, uint32_t y, uint32_t width, uint32_t height);
bool HandleRenderPassEncoderSetStencilReference(const volatile char** commands, size_t* size);

bool DoRenderPassEncoderSetStencilReference(WGPURenderPassEncoder self, uint32_t reference);
bool HandleRenderPassEncoderSetVertexBuffer(const volatile char** commands, size_t* size);

bool DoRenderPassEncoderSetVertexBuffer(WGPURenderPassEncoder self, uint32_t slot, WGPUBuffer buffer, uint64_t offset, uint64_t size);
bool HandleRenderPassEncoderSetViewport(const volatile char** commands, size_t* size);

bool DoRenderPassEncoderSetViewport(WGPURenderPassEncoder self, float x, float y, float width, float height, float minDepth, float maxDepth);
bool HandleRenderPassEncoderWriteTimestamp(const volatile char** commands, size_t* size);

bool DoRenderPassEncoderWriteTimestamp(WGPURenderPassEncoder self, WGPUQuerySet querySet, uint32_t queryIndex);
bool HandleRenderPipelineGetBindGroupLayout(const volatile char** commands, size_t* size);

bool DoRenderPipelineGetBindGroupLayout(WGPURenderPipeline self, uint32_t groupIndex, WGPUBindGroupLayout* result);
bool HandleSwapChainConfigure(const volatile char** commands, size_t* size);

bool DoSwapChainConfigure(WGPUSwapChain self, WGPUTextureFormat format, WGPUTextureUsageFlags allowedUsage, uint32_t width, uint32_t height);
bool HandleSwapChainGetCurrentTextureView(const volatile char** commands, size_t* size);

bool DoSwapChainGetCurrentTextureView(WGPUSwapChain self, WGPUTextureView* result);
bool HandleSwapChainPresent(const volatile char** commands, size_t* size);

bool DoSwapChainPresent(WGPUSwapChain self);
bool HandleTextureCreateView(const volatile char** commands, size_t* size);

bool DoTextureCreateView(WGPUTexture self, WGPUTextureViewDescriptor const * descriptor, WGPUTextureView* result);
bool HandleTextureDestroy(const volatile char** commands, size_t* size);

bool DoTextureDestroy(WGPUTexture self);

bool PreHandleBufferDestroy(const BufferDestroyCmd& cmd);
bool PreHandleBufferUnmap(const BufferUnmapCmd& cmd);
