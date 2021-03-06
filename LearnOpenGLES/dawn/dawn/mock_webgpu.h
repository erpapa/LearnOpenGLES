
#ifndef MOCK_WEBGPU_H
#define MOCK_WEBGPU_H

#include <dawn/dawn_proc_table.h>
#include <dawn/webgpu.h>
#include <gmock/gmock.h>

#include <memory>

// An abstract base class representing a proc table so that API calls can be mocked. Most API calls
// are directly represented by a delete virtual method but others need minimal state tracking to be
// useful as mocks.
class ProcTableAsClass {
    public:
        virtual ~ProcTableAsClass();

        void GetProcTableAndDevice(DawnProcTable* table, WGPUDevice* device);

        // Creates an object that can be returned by a mocked call as in WillOnce(Return(foo)).
        // It returns an object of the write type that isn't equal to any previously returned object.
        // Otherwise some mock expectation could be triggered by two different objects having the same
        // value.
        WGPUBindGroup GetNewBindGroup();
        WGPUBindGroupLayout GetNewBindGroupLayout();
        WGPUBuffer GetNewBuffer();
        WGPUCommandBuffer GetNewCommandBuffer();
        WGPUCommandEncoder GetNewCommandEncoder();
        WGPUComputePassEncoder GetNewComputePassEncoder();
        WGPUComputePipeline GetNewComputePipeline();
        WGPUDevice GetNewDevice();
        WGPUFence GetNewFence();
        WGPUInstance GetNewInstance();
        WGPUPipelineLayout GetNewPipelineLayout();
        WGPUQuerySet GetNewQuerySet();
        WGPUQueue GetNewQueue();
        WGPURenderBundle GetNewRenderBundle();
        WGPURenderBundleEncoder GetNewRenderBundleEncoder();
        WGPURenderPassEncoder GetNewRenderPassEncoder();
        WGPURenderPipeline GetNewRenderPipeline();
        WGPUSampler GetNewSampler();
        WGPUShaderModule GetNewShaderModule();
        WGPUSurface GetNewSurface();
        WGPUSwapChain GetNewSwapChain();
        WGPUTexture GetNewTexture();
        WGPUTextureView GetNewTextureView();

        virtual void BindGroupReference(WGPUBindGroup self) = 0;
        virtual void BindGroupRelease(WGPUBindGroup self) = 0;
        virtual void BindGroupLayoutReference(WGPUBindGroupLayout self) = 0;
        virtual void BindGroupLayoutRelease(WGPUBindGroupLayout self) = 0;
        virtual void BufferDestroy(WGPUBuffer buffer) = 0;
        virtual void const * BufferGetConstMappedRange(WGPUBuffer buffer, size_t offset, size_t size) = 0;
        virtual void * BufferGetMappedRange(WGPUBuffer buffer, size_t offset, size_t size) = 0;
        virtual void BufferUnmap(WGPUBuffer buffer) = 0;
        virtual void BufferReference(WGPUBuffer self) = 0;
        virtual void BufferRelease(WGPUBuffer self) = 0;
        virtual void CommandBufferReference(WGPUCommandBuffer self) = 0;
        virtual void CommandBufferRelease(WGPUCommandBuffer self) = 0;
        virtual WGPUComputePassEncoder CommandEncoderBeginComputePass(WGPUCommandEncoder commandEncoder, WGPUComputePassDescriptor const * descriptor) = 0;
        virtual WGPURenderPassEncoder CommandEncoderBeginRenderPass(WGPUCommandEncoder commandEncoder, WGPURenderPassDescriptor const * descriptor) = 0;
        virtual void CommandEncoderCopyBufferToBuffer(WGPUCommandEncoder commandEncoder, WGPUBuffer source, uint64_t sourceOffset, WGPUBuffer destination, uint64_t destinationOffset, uint64_t size) = 0;
        virtual void CommandEncoderCopyBufferToTexture(WGPUCommandEncoder commandEncoder, WGPUBufferCopyView const * source, WGPUTextureCopyView const * destination, WGPUExtent3D const * copySize) = 0;
        virtual void CommandEncoderCopyTextureToBuffer(WGPUCommandEncoder commandEncoder, WGPUTextureCopyView const * source, WGPUBufferCopyView const * destination, WGPUExtent3D const * copySize) = 0;
        virtual void CommandEncoderCopyTextureToTexture(WGPUCommandEncoder commandEncoder, WGPUTextureCopyView const * source, WGPUTextureCopyView const * destination, WGPUExtent3D const * copySize) = 0;
        virtual WGPUCommandBuffer CommandEncoderFinish(WGPUCommandEncoder commandEncoder, WGPUCommandBufferDescriptor const * descriptor) = 0;
        virtual void CommandEncoderInsertDebugMarker(WGPUCommandEncoder commandEncoder, char const * markerLabel) = 0;
        virtual void CommandEncoderPopDebugGroup(WGPUCommandEncoder commandEncoder) = 0;
        virtual void CommandEncoderPushDebugGroup(WGPUCommandEncoder commandEncoder, char const * groupLabel) = 0;
        virtual void CommandEncoderResolveQuerySet(WGPUCommandEncoder commandEncoder, WGPUQuerySet querySet, uint32_t firstQuery, uint32_t queryCount, WGPUBuffer destination, uint64_t destinationOffset) = 0;
        virtual void CommandEncoderWriteTimestamp(WGPUCommandEncoder commandEncoder, WGPUQuerySet querySet, uint32_t queryIndex) = 0;
        virtual void CommandEncoderReference(WGPUCommandEncoder self) = 0;
        virtual void CommandEncoderRelease(WGPUCommandEncoder self) = 0;
        virtual void ComputePassEncoderDispatch(WGPUComputePassEncoder computePassEncoder, uint32_t x, uint32_t y, uint32_t z) = 0;
        virtual void ComputePassEncoderDispatchIndirect(WGPUComputePassEncoder computePassEncoder, WGPUBuffer indirectBuffer, uint64_t indirectOffset) = 0;
        virtual void ComputePassEncoderEndPass(WGPUComputePassEncoder computePassEncoder) = 0;
        virtual void ComputePassEncoderInsertDebugMarker(WGPUComputePassEncoder computePassEncoder, char const * markerLabel) = 0;
        virtual void ComputePassEncoderPopDebugGroup(WGPUComputePassEncoder computePassEncoder) = 0;
        virtual void ComputePassEncoderPushDebugGroup(WGPUComputePassEncoder computePassEncoder, char const * groupLabel) = 0;
        virtual void ComputePassEncoderSetBindGroup(WGPUComputePassEncoder computePassEncoder, uint32_t groupIndex, WGPUBindGroup group, uint32_t dynamicOffsetCount, uint32_t const * dynamicOffsets) = 0;
        virtual void ComputePassEncoderSetPipeline(WGPUComputePassEncoder computePassEncoder, WGPUComputePipeline pipeline) = 0;
        virtual void ComputePassEncoderWriteTimestamp(WGPUComputePassEncoder computePassEncoder, WGPUQuerySet querySet, uint32_t queryIndex) = 0;
        virtual void ComputePassEncoderReference(WGPUComputePassEncoder self) = 0;
        virtual void ComputePassEncoderRelease(WGPUComputePassEncoder self) = 0;
        virtual WGPUBindGroupLayout ComputePipelineGetBindGroupLayout(WGPUComputePipeline computePipeline, uint32_t groupIndex) = 0;
        virtual void ComputePipelineReference(WGPUComputePipeline self) = 0;
        virtual void ComputePipelineRelease(WGPUComputePipeline self) = 0;
        virtual WGPUBindGroup DeviceCreateBindGroup(WGPUDevice device, WGPUBindGroupDescriptor const * descriptor) = 0;
        virtual WGPUBindGroupLayout DeviceCreateBindGroupLayout(WGPUDevice device, WGPUBindGroupLayoutDescriptor const * descriptor) = 0;
        virtual WGPUBuffer DeviceCreateBuffer(WGPUDevice device, WGPUBufferDescriptor const * descriptor) = 0;
        virtual WGPUCommandEncoder DeviceCreateCommandEncoder(WGPUDevice device, WGPUCommandEncoderDescriptor const * descriptor) = 0;
        virtual WGPUComputePipeline DeviceCreateComputePipeline(WGPUDevice device, WGPUComputePipelineDescriptor const * descriptor) = 0;
        virtual WGPUBuffer DeviceCreateErrorBuffer(WGPUDevice device) = 0;
        virtual WGPUPipelineLayout DeviceCreatePipelineLayout(WGPUDevice device, WGPUPipelineLayoutDescriptor const * descriptor) = 0;
        virtual WGPUQuerySet DeviceCreateQuerySet(WGPUDevice device, WGPUQuerySetDescriptor const * descriptor) = 0;
        virtual WGPURenderBundleEncoder DeviceCreateRenderBundleEncoder(WGPUDevice device, WGPURenderBundleEncoderDescriptor const * descriptor) = 0;
        virtual WGPURenderPipeline DeviceCreateRenderPipeline(WGPUDevice device, WGPURenderPipelineDescriptor const * descriptor) = 0;
        virtual WGPUSampler DeviceCreateSampler(WGPUDevice device, WGPUSamplerDescriptor const * descriptor) = 0;
        virtual WGPUShaderModule DeviceCreateShaderModule(WGPUDevice device, WGPUShaderModuleDescriptor const * descriptor) = 0;
        virtual WGPUSwapChain DeviceCreateSwapChain(WGPUDevice device, WGPUSurface surface, WGPUSwapChainDescriptor const * descriptor) = 0;
        virtual WGPUTexture DeviceCreateTexture(WGPUDevice device, WGPUTextureDescriptor const * descriptor) = 0;
        virtual WGPUQueue DeviceGetDefaultQueue(WGPUDevice device) = 0;
        virtual void DeviceInjectError(WGPUDevice device, WGPUErrorType type, char const * message) = 0;
        virtual void DeviceLoseForTesting(WGPUDevice device) = 0;
        virtual void DevicePushErrorScope(WGPUDevice device, WGPUErrorFilter filter) = 0;
        virtual void DeviceTick(WGPUDevice device) = 0;
        virtual void DeviceReference(WGPUDevice self) = 0;
        virtual void DeviceRelease(WGPUDevice self) = 0;
        virtual uint64_t FenceGetCompletedValue(WGPUFence fence) = 0;
        virtual void FenceReference(WGPUFence self) = 0;
        virtual void FenceRelease(WGPUFence self) = 0;
        virtual WGPUSurface InstanceCreateSurface(WGPUInstance instance, WGPUSurfaceDescriptor const * descriptor) = 0;
        virtual void InstanceReference(WGPUInstance self) = 0;
        virtual void InstanceRelease(WGPUInstance self) = 0;
        virtual void PipelineLayoutReference(WGPUPipelineLayout self) = 0;
        virtual void PipelineLayoutRelease(WGPUPipelineLayout self) = 0;
        virtual void QuerySetDestroy(WGPUQuerySet querySet) = 0;
        virtual void QuerySetReference(WGPUQuerySet self) = 0;
        virtual void QuerySetRelease(WGPUQuerySet self) = 0;
        virtual WGPUFence QueueCreateFence(WGPUQueue queue, WGPUFenceDescriptor const * descriptor) = 0;
        virtual void QueueSignal(WGPUQueue queue, WGPUFence fence, uint64_t signalValue) = 0;
        virtual void QueueSubmit(WGPUQueue queue, uint32_t commandCount, WGPUCommandBuffer const * commands) = 0;
        virtual void QueueWriteBuffer(WGPUQueue queue, WGPUBuffer buffer, uint64_t bufferOffset, void const * data, size_t size) = 0;
        virtual void QueueWriteTexture(WGPUQueue queue, WGPUTextureCopyView const * destination, void const * data, size_t dataSize, WGPUTextureDataLayout const * dataLayout, WGPUExtent3D const * writeSize) = 0;
        virtual void QueueReference(WGPUQueue self) = 0;
        virtual void QueueRelease(WGPUQueue self) = 0;
        virtual void RenderBundleReference(WGPURenderBundle self) = 0;
        virtual void RenderBundleRelease(WGPURenderBundle self) = 0;
        virtual void RenderBundleEncoderDraw(WGPURenderBundleEncoder renderBundleEncoder, uint32_t vertexCount, uint32_t instanceCount, uint32_t firstVertex, uint32_t firstInstance) = 0;
        virtual void RenderBundleEncoderDrawIndexed(WGPURenderBundleEncoder renderBundleEncoder, uint32_t indexCount, uint32_t instanceCount, uint32_t firstIndex, int32_t baseVertex, uint32_t firstInstance) = 0;
        virtual void RenderBundleEncoderDrawIndexedIndirect(WGPURenderBundleEncoder renderBundleEncoder, WGPUBuffer indirectBuffer, uint64_t indirectOffset) = 0;
        virtual void RenderBundleEncoderDrawIndirect(WGPURenderBundleEncoder renderBundleEncoder, WGPUBuffer indirectBuffer, uint64_t indirectOffset) = 0;
        virtual WGPURenderBundle RenderBundleEncoderFinish(WGPURenderBundleEncoder renderBundleEncoder, WGPURenderBundleDescriptor const * descriptor) = 0;
        virtual void RenderBundleEncoderInsertDebugMarker(WGPURenderBundleEncoder renderBundleEncoder, char const * markerLabel) = 0;
        virtual void RenderBundleEncoderPopDebugGroup(WGPURenderBundleEncoder renderBundleEncoder) = 0;
        virtual void RenderBundleEncoderPushDebugGroup(WGPURenderBundleEncoder renderBundleEncoder, char const * groupLabel) = 0;
        virtual void RenderBundleEncoderSetBindGroup(WGPURenderBundleEncoder renderBundleEncoder, uint32_t groupIndex, WGPUBindGroup group, uint32_t dynamicOffsetCount, uint32_t const * dynamicOffsets) = 0;
        virtual void RenderBundleEncoderSetIndexBuffer(WGPURenderBundleEncoder renderBundleEncoder, WGPUBuffer buffer, uint64_t offset, uint64_t size) = 0;
        virtual void RenderBundleEncoderSetIndexBufferWithFormat(WGPURenderBundleEncoder renderBundleEncoder, WGPUBuffer buffer, WGPUIndexFormat format, uint64_t offset, uint64_t size) = 0;
        virtual void RenderBundleEncoderSetPipeline(WGPURenderBundleEncoder renderBundleEncoder, WGPURenderPipeline pipeline) = 0;
        virtual void RenderBundleEncoderSetVertexBuffer(WGPURenderBundleEncoder renderBundleEncoder, uint32_t slot, WGPUBuffer buffer, uint64_t offset, uint64_t size) = 0;
        virtual void RenderBundleEncoderReference(WGPURenderBundleEncoder self) = 0;
        virtual void RenderBundleEncoderRelease(WGPURenderBundleEncoder self) = 0;
        virtual void RenderPassEncoderDraw(WGPURenderPassEncoder renderPassEncoder, uint32_t vertexCount, uint32_t instanceCount, uint32_t firstVertex, uint32_t firstInstance) = 0;
        virtual void RenderPassEncoderDrawIndexed(WGPURenderPassEncoder renderPassEncoder, uint32_t indexCount, uint32_t instanceCount, uint32_t firstIndex, int32_t baseVertex, uint32_t firstInstance) = 0;
        virtual void RenderPassEncoderDrawIndexedIndirect(WGPURenderPassEncoder renderPassEncoder, WGPUBuffer indirectBuffer, uint64_t indirectOffset) = 0;
        virtual void RenderPassEncoderDrawIndirect(WGPURenderPassEncoder renderPassEncoder, WGPUBuffer indirectBuffer, uint64_t indirectOffset) = 0;
        virtual void RenderPassEncoderEndPass(WGPURenderPassEncoder renderPassEncoder) = 0;
        virtual void RenderPassEncoderExecuteBundles(WGPURenderPassEncoder renderPassEncoder, uint32_t bundlesCount, WGPURenderBundle const * bundles) = 0;
        virtual void RenderPassEncoderInsertDebugMarker(WGPURenderPassEncoder renderPassEncoder, char const * markerLabel) = 0;
        virtual void RenderPassEncoderPopDebugGroup(WGPURenderPassEncoder renderPassEncoder) = 0;
        virtual void RenderPassEncoderPushDebugGroup(WGPURenderPassEncoder renderPassEncoder, char const * groupLabel) = 0;
        virtual void RenderPassEncoderSetBindGroup(WGPURenderPassEncoder renderPassEncoder, uint32_t groupIndex, WGPUBindGroup group, uint32_t dynamicOffsetCount, uint32_t const * dynamicOffsets) = 0;
        virtual void RenderPassEncoderSetBlendColor(WGPURenderPassEncoder renderPassEncoder, WGPUColor const * color) = 0;
        virtual void RenderPassEncoderSetIndexBuffer(WGPURenderPassEncoder renderPassEncoder, WGPUBuffer buffer, uint64_t offset, uint64_t size) = 0;
        virtual void RenderPassEncoderSetIndexBufferWithFormat(WGPURenderPassEncoder renderPassEncoder, WGPUBuffer buffer, WGPUIndexFormat format, uint64_t offset, uint64_t size) = 0;
        virtual void RenderPassEncoderSetPipeline(WGPURenderPassEncoder renderPassEncoder, WGPURenderPipeline pipeline) = 0;
        virtual void RenderPassEncoderSetScissorRect(WGPURenderPassEncoder renderPassEncoder, uint32_t x, uint32_t y, uint32_t width, uint32_t height) = 0;
        virtual void RenderPassEncoderSetStencilReference(WGPURenderPassEncoder renderPassEncoder, uint32_t reference) = 0;
        virtual void RenderPassEncoderSetVertexBuffer(WGPURenderPassEncoder renderPassEncoder, uint32_t slot, WGPUBuffer buffer, uint64_t offset, uint64_t size) = 0;
        virtual void RenderPassEncoderSetViewport(WGPURenderPassEncoder renderPassEncoder, float x, float y, float width, float height, float minDepth, float maxDepth) = 0;
        virtual void RenderPassEncoderWriteTimestamp(WGPURenderPassEncoder renderPassEncoder, WGPUQuerySet querySet, uint32_t queryIndex) = 0;
        virtual void RenderPassEncoderReference(WGPURenderPassEncoder self) = 0;
        virtual void RenderPassEncoderRelease(WGPURenderPassEncoder self) = 0;
        virtual WGPUBindGroupLayout RenderPipelineGetBindGroupLayout(WGPURenderPipeline renderPipeline, uint32_t groupIndex) = 0;
        virtual void RenderPipelineReference(WGPURenderPipeline self) = 0;
        virtual void RenderPipelineRelease(WGPURenderPipeline self) = 0;
        virtual void SamplerReference(WGPUSampler self) = 0;
        virtual void SamplerRelease(WGPUSampler self) = 0;
        virtual void ShaderModuleReference(WGPUShaderModule self) = 0;
        virtual void ShaderModuleRelease(WGPUShaderModule self) = 0;
        virtual void SurfaceReference(WGPUSurface self) = 0;
        virtual void SurfaceRelease(WGPUSurface self) = 0;
        virtual void SwapChainConfigure(WGPUSwapChain swapChain, WGPUTextureFormat format, WGPUTextureUsageFlags allowedUsage, uint32_t width, uint32_t height) = 0;
        virtual WGPUTextureView SwapChainGetCurrentTextureView(WGPUSwapChain swapChain) = 0;
        virtual void SwapChainPresent(WGPUSwapChain swapChain) = 0;
        virtual void SwapChainReference(WGPUSwapChain self) = 0;
        virtual void SwapChainRelease(WGPUSwapChain self) = 0;
        virtual WGPUTextureView TextureCreateView(WGPUTexture texture, WGPUTextureViewDescriptor const * descriptor) = 0;
        virtual void TextureDestroy(WGPUTexture texture) = 0;
        virtual void TextureReference(WGPUTexture self) = 0;
        virtual void TextureRelease(WGPUTexture self) = 0;
        virtual void TextureViewReference(WGPUTextureView self) = 0;
        virtual void TextureViewRelease(WGPUTextureView self) = 0;

        // Stores callback and userdata and calls the On* methods
        void DeviceCreateReadyComputePipeline(WGPUDevice self,
                                              WGPUComputePipelineDescriptor const * descriptor,
                                              WGPUCreateReadyComputePipelineCallback callback,
                                              void* userdata);
        void DeviceCreateReadyRenderPipeline(WGPUDevice self,
                                             WGPURenderPipelineDescriptor const * descriptor,
                                             WGPUCreateReadyRenderPipelineCallback callback,
                                             void* userdata);
        void DeviceSetUncapturedErrorCallback(WGPUDevice self,
                                    WGPUErrorCallback callback,
                                    void* userdata);
        void DeviceSetDeviceLostCallback(WGPUDevice self,
                                         WGPUDeviceLostCallback callback,
                                         void* userdata);
        bool DevicePopErrorScope(WGPUDevice self, WGPUErrorCallback callback, void* userdata);
        void BufferMapAsync(WGPUBuffer self,
                            WGPUMapModeFlags mode,
                            size_t offset,
                            size_t size,
                            WGPUBufferMapCallback callback,
                            void* userdata);
        void FenceOnCompletion(WGPUFence self,
                               uint64_t value,
                               WGPUFenceOnCompletionCallback callback,
                               void* userdata);

        // Special cased mockable methods
        virtual void OnDeviceCreateReadyComputePipelineCallback(
            WGPUDevice device,
            WGPUComputePipelineDescriptor const * descriptor,
            WGPUCreateReadyComputePipelineCallback callback,
            void* userdata) = 0;
        virtual void OnDeviceCreateReadyRenderPipelineCallback(
            WGPUDevice device,
            WGPURenderPipelineDescriptor const * descriptor,
            WGPUCreateReadyRenderPipelineCallback callback,
            void* userdata) = 0;
        virtual void OnDeviceSetUncapturedErrorCallback(WGPUDevice device,
                                              WGPUErrorCallback callback,
                                              void* userdata) = 0;
        virtual void OnDeviceSetDeviceLostCallback(WGPUDevice device,
                                                   WGPUDeviceLostCallback callback,
                                                   void* userdata) = 0;
        virtual bool OnDevicePopErrorScopeCallback(WGPUDevice device,
                                              WGPUErrorCallback callback,
                                              void* userdata) = 0;
        virtual void OnBufferMapAsyncCallback(WGPUBuffer buffer,
                                              WGPUBufferMapCallback callback,
                                              void* userdata) = 0;
        virtual void OnFenceOnCompletionCallback(WGPUFence fence,
                                                 uint64_t value,
                                                 WGPUFenceOnCompletionCallback callback,
                                                 void* userdata) = 0;

        // Calls the stored callbacks
        void CallDeviceCreateReadyComputePipelineCallback(WGPUDevice device,
                                                          WGPUCreateReadyPipelineStatus status,
                                                          WGPUComputePipeline pipeline,
                                                          const char* message);
        void CallDeviceCreateReadyRenderPipelineCallback(WGPUDevice device,
                                                         WGPUCreateReadyPipelineStatus status,
                                                         WGPURenderPipeline pipeline,
                                                         const char* message);
        void CallDeviceErrorCallback(WGPUDevice device, WGPUErrorType type, const char* message);
        void CallDeviceLostCallback(WGPUDevice device, const char* message);
        void CallMapAsyncCallback(WGPUBuffer buffer, WGPUBufferMapAsyncStatus status);
        void CallFenceOnCompletionCallback(WGPUFence fence, WGPUFenceCompletionStatus status);

        struct Object {
            ProcTableAsClass* procs = nullptr;
            WGPUErrorCallback deviceErrorCallback = nullptr;
            WGPUCreateReadyComputePipelineCallback createReadyComputePipelineCallback = nullptr;
            WGPUCreateReadyRenderPipelineCallback createReadyRenderPipelineCallback = nullptr;
            WGPUDeviceLostCallback deviceLostCallback = nullptr;
            WGPUBufferMapCallback mapAsyncCallback = nullptr;
            WGPUFenceOnCompletionCallback fenceOnCompletionCallback = nullptr;
            void* userdata = 0;
        };

    private:
        // Remembers the values returned by GetNew* so they can be freed.
        std::vector<std::unique_ptr<Object>> mObjects;
};

class MockProcTable : public ProcTableAsClass {
    public:
        MockProcTable();
        ~MockProcTable() override;

        void IgnoreAllReleaseCalls();


        MOCK_METHOD(void, BindGroupReference, (WGPUBindGroup self), (override));
        MOCK_METHOD(void, BindGroupRelease, (WGPUBindGroup self), (override));

        MOCK_METHOD(void, BindGroupLayoutReference, (WGPUBindGroupLayout self), (override));
        MOCK_METHOD(void, BindGroupLayoutRelease, (WGPUBindGroupLayout self), (override));
        MOCK_METHOD(void, BufferDestroy, (WGPUBuffer buffer), (override));
        MOCK_METHOD(void const *, BufferGetConstMappedRange, (WGPUBuffer buffer, size_t offset, size_t size), (override));
        MOCK_METHOD(void *, BufferGetMappedRange, (WGPUBuffer buffer, size_t offset, size_t size), (override));
        MOCK_METHOD(void, BufferUnmap, (WGPUBuffer buffer), (override));

        MOCK_METHOD(void, BufferReference, (WGPUBuffer self), (override));
        MOCK_METHOD(void, BufferRelease, (WGPUBuffer self), (override));

        MOCK_METHOD(void, CommandBufferReference, (WGPUCommandBuffer self), (override));
        MOCK_METHOD(void, CommandBufferRelease, (WGPUCommandBuffer self), (override));
        MOCK_METHOD(WGPUComputePassEncoder, CommandEncoderBeginComputePass, (WGPUCommandEncoder commandEncoder, WGPUComputePassDescriptor const * descriptor), (override));
        MOCK_METHOD(WGPURenderPassEncoder, CommandEncoderBeginRenderPass, (WGPUCommandEncoder commandEncoder, WGPURenderPassDescriptor const * descriptor), (override));
        MOCK_METHOD(void, CommandEncoderCopyBufferToBuffer, (WGPUCommandEncoder commandEncoder, WGPUBuffer source, uint64_t sourceOffset, WGPUBuffer destination, uint64_t destinationOffset, uint64_t size), (override));
        MOCK_METHOD(void, CommandEncoderCopyBufferToTexture, (WGPUCommandEncoder commandEncoder, WGPUBufferCopyView const * source, WGPUTextureCopyView const * destination, WGPUExtent3D const * copySize), (override));
        MOCK_METHOD(void, CommandEncoderCopyTextureToBuffer, (WGPUCommandEncoder commandEncoder, WGPUTextureCopyView const * source, WGPUBufferCopyView const * destination, WGPUExtent3D const * copySize), (override));
        MOCK_METHOD(void, CommandEncoderCopyTextureToTexture, (WGPUCommandEncoder commandEncoder, WGPUTextureCopyView const * source, WGPUTextureCopyView const * destination, WGPUExtent3D const * copySize), (override));
        MOCK_METHOD(WGPUCommandBuffer, CommandEncoderFinish, (WGPUCommandEncoder commandEncoder, WGPUCommandBufferDescriptor const * descriptor), (override));
        MOCK_METHOD(void, CommandEncoderInsertDebugMarker, (WGPUCommandEncoder commandEncoder, char const * markerLabel), (override));
        MOCK_METHOD(void, CommandEncoderPopDebugGroup, (WGPUCommandEncoder commandEncoder), (override));
        MOCK_METHOD(void, CommandEncoderPushDebugGroup, (WGPUCommandEncoder commandEncoder, char const * groupLabel), (override));
        MOCK_METHOD(void, CommandEncoderResolveQuerySet, (WGPUCommandEncoder commandEncoder, WGPUQuerySet querySet, uint32_t firstQuery, uint32_t queryCount, WGPUBuffer destination, uint64_t destinationOffset), (override));
        MOCK_METHOD(void, CommandEncoderWriteTimestamp, (WGPUCommandEncoder commandEncoder, WGPUQuerySet querySet, uint32_t queryIndex), (override));

        MOCK_METHOD(void, CommandEncoderReference, (WGPUCommandEncoder self), (override));
        MOCK_METHOD(void, CommandEncoderRelease, (WGPUCommandEncoder self), (override));
        MOCK_METHOD(void, ComputePassEncoderDispatch, (WGPUComputePassEncoder computePassEncoder, uint32_t x, uint32_t y, uint32_t z), (override));
        MOCK_METHOD(void, ComputePassEncoderDispatchIndirect, (WGPUComputePassEncoder computePassEncoder, WGPUBuffer indirectBuffer, uint64_t indirectOffset), (override));
        MOCK_METHOD(void, ComputePassEncoderEndPass, (WGPUComputePassEncoder computePassEncoder), (override));
        MOCK_METHOD(void, ComputePassEncoderInsertDebugMarker, (WGPUComputePassEncoder computePassEncoder, char const * markerLabel), (override));
        MOCK_METHOD(void, ComputePassEncoderPopDebugGroup, (WGPUComputePassEncoder computePassEncoder), (override));
        MOCK_METHOD(void, ComputePassEncoderPushDebugGroup, (WGPUComputePassEncoder computePassEncoder, char const * groupLabel), (override));
        MOCK_METHOD(void, ComputePassEncoderSetBindGroup, (WGPUComputePassEncoder computePassEncoder, uint32_t groupIndex, WGPUBindGroup group, uint32_t dynamicOffsetCount, uint32_t const * dynamicOffsets), (override));
        MOCK_METHOD(void, ComputePassEncoderSetPipeline, (WGPUComputePassEncoder computePassEncoder, WGPUComputePipeline pipeline), (override));
        MOCK_METHOD(void, ComputePassEncoderWriteTimestamp, (WGPUComputePassEncoder computePassEncoder, WGPUQuerySet querySet, uint32_t queryIndex), (override));

        MOCK_METHOD(void, ComputePassEncoderReference, (WGPUComputePassEncoder self), (override));
        MOCK_METHOD(void, ComputePassEncoderRelease, (WGPUComputePassEncoder self), (override));
        MOCK_METHOD(WGPUBindGroupLayout, ComputePipelineGetBindGroupLayout, (WGPUComputePipeline computePipeline, uint32_t groupIndex), (override));

        MOCK_METHOD(void, ComputePipelineReference, (WGPUComputePipeline self), (override));
        MOCK_METHOD(void, ComputePipelineRelease, (WGPUComputePipeline self), (override));
        MOCK_METHOD(WGPUBindGroup, DeviceCreateBindGroup, (WGPUDevice device, WGPUBindGroupDescriptor const * descriptor), (override));
        MOCK_METHOD(WGPUBindGroupLayout, DeviceCreateBindGroupLayout, (WGPUDevice device, WGPUBindGroupLayoutDescriptor const * descriptor), (override));
        MOCK_METHOD(WGPUBuffer, DeviceCreateBuffer, (WGPUDevice device, WGPUBufferDescriptor const * descriptor), (override));
        MOCK_METHOD(WGPUCommandEncoder, DeviceCreateCommandEncoder, (WGPUDevice device, WGPUCommandEncoderDescriptor const * descriptor), (override));
        MOCK_METHOD(WGPUComputePipeline, DeviceCreateComputePipeline, (WGPUDevice device, WGPUComputePipelineDescriptor const * descriptor), (override));
        MOCK_METHOD(WGPUBuffer, DeviceCreateErrorBuffer, (WGPUDevice device), (override));
        MOCK_METHOD(WGPUPipelineLayout, DeviceCreatePipelineLayout, (WGPUDevice device, WGPUPipelineLayoutDescriptor const * descriptor), (override));
        MOCK_METHOD(WGPUQuerySet, DeviceCreateQuerySet, (WGPUDevice device, WGPUQuerySetDescriptor const * descriptor), (override));
        MOCK_METHOD(WGPURenderBundleEncoder, DeviceCreateRenderBundleEncoder, (WGPUDevice device, WGPURenderBundleEncoderDescriptor const * descriptor), (override));
        MOCK_METHOD(WGPURenderPipeline, DeviceCreateRenderPipeline, (WGPUDevice device, WGPURenderPipelineDescriptor const * descriptor), (override));
        MOCK_METHOD(WGPUSampler, DeviceCreateSampler, (WGPUDevice device, WGPUSamplerDescriptor const * descriptor), (override));
        MOCK_METHOD(WGPUShaderModule, DeviceCreateShaderModule, (WGPUDevice device, WGPUShaderModuleDescriptor const * descriptor), (override));
        MOCK_METHOD(WGPUSwapChain, DeviceCreateSwapChain, (WGPUDevice device, WGPUSurface surface, WGPUSwapChainDescriptor const * descriptor), (override));
        MOCK_METHOD(WGPUTexture, DeviceCreateTexture, (WGPUDevice device, WGPUTextureDescriptor const * descriptor), (override));
        MOCK_METHOD(WGPUQueue, DeviceGetDefaultQueue, (WGPUDevice device), (override));
        MOCK_METHOD(void, DeviceInjectError, (WGPUDevice device, WGPUErrorType type, char const * message), (override));
        MOCK_METHOD(void, DeviceLoseForTesting, (WGPUDevice device), (override));
        MOCK_METHOD(void, DevicePushErrorScope, (WGPUDevice device, WGPUErrorFilter filter), (override));
        MOCK_METHOD(void, DeviceTick, (WGPUDevice device), (override));

        MOCK_METHOD(void, DeviceReference, (WGPUDevice self), (override));
        MOCK_METHOD(void, DeviceRelease, (WGPUDevice self), (override));
        MOCK_METHOD(uint64_t, FenceGetCompletedValue, (WGPUFence fence), (override));

        MOCK_METHOD(void, FenceReference, (WGPUFence self), (override));
        MOCK_METHOD(void, FenceRelease, (WGPUFence self), (override));
        MOCK_METHOD(WGPUSurface, InstanceCreateSurface, (WGPUInstance instance, WGPUSurfaceDescriptor const * descriptor), (override));

        MOCK_METHOD(void, InstanceReference, (WGPUInstance self), (override));
        MOCK_METHOD(void, InstanceRelease, (WGPUInstance self), (override));

        MOCK_METHOD(void, PipelineLayoutReference, (WGPUPipelineLayout self), (override));
        MOCK_METHOD(void, PipelineLayoutRelease, (WGPUPipelineLayout self), (override));
        MOCK_METHOD(void, QuerySetDestroy, (WGPUQuerySet querySet), (override));

        MOCK_METHOD(void, QuerySetReference, (WGPUQuerySet self), (override));
        MOCK_METHOD(void, QuerySetRelease, (WGPUQuerySet self), (override));
        MOCK_METHOD(WGPUFence, QueueCreateFence, (WGPUQueue queue, WGPUFenceDescriptor const * descriptor), (override));
        MOCK_METHOD(void, QueueSignal, (WGPUQueue queue, WGPUFence fence, uint64_t signalValue), (override));
        MOCK_METHOD(void, QueueSubmit, (WGPUQueue queue, uint32_t commandCount, WGPUCommandBuffer const * commands), (override));
        MOCK_METHOD(void, QueueWriteBuffer, (WGPUQueue queue, WGPUBuffer buffer, uint64_t bufferOffset, void const * data, size_t size), (override));
        MOCK_METHOD(void, QueueWriteTexture, (WGPUQueue queue, WGPUTextureCopyView const * destination, void const * data, size_t dataSize, WGPUTextureDataLayout const * dataLayout, WGPUExtent3D const * writeSize), (override));

        MOCK_METHOD(void, QueueReference, (WGPUQueue self), (override));
        MOCK_METHOD(void, QueueRelease, (WGPUQueue self), (override));

        MOCK_METHOD(void, RenderBundleReference, (WGPURenderBundle self), (override));
        MOCK_METHOD(void, RenderBundleRelease, (WGPURenderBundle self), (override));
        MOCK_METHOD(void, RenderBundleEncoderDraw, (WGPURenderBundleEncoder renderBundleEncoder, uint32_t vertexCount, uint32_t instanceCount, uint32_t firstVertex, uint32_t firstInstance), (override));
        MOCK_METHOD(void, RenderBundleEncoderDrawIndexed, (WGPURenderBundleEncoder renderBundleEncoder, uint32_t indexCount, uint32_t instanceCount, uint32_t firstIndex, int32_t baseVertex, uint32_t firstInstance), (override));
        MOCK_METHOD(void, RenderBundleEncoderDrawIndexedIndirect, (WGPURenderBundleEncoder renderBundleEncoder, WGPUBuffer indirectBuffer, uint64_t indirectOffset), (override));
        MOCK_METHOD(void, RenderBundleEncoderDrawIndirect, (WGPURenderBundleEncoder renderBundleEncoder, WGPUBuffer indirectBuffer, uint64_t indirectOffset), (override));
        MOCK_METHOD(WGPURenderBundle, RenderBundleEncoderFinish, (WGPURenderBundleEncoder renderBundleEncoder, WGPURenderBundleDescriptor const * descriptor), (override));
        MOCK_METHOD(void, RenderBundleEncoderInsertDebugMarker, (WGPURenderBundleEncoder renderBundleEncoder, char const * markerLabel), (override));
        MOCK_METHOD(void, RenderBundleEncoderPopDebugGroup, (WGPURenderBundleEncoder renderBundleEncoder), (override));
        MOCK_METHOD(void, RenderBundleEncoderPushDebugGroup, (WGPURenderBundleEncoder renderBundleEncoder, char const * groupLabel), (override));
        MOCK_METHOD(void, RenderBundleEncoderSetBindGroup, (WGPURenderBundleEncoder renderBundleEncoder, uint32_t groupIndex, WGPUBindGroup group, uint32_t dynamicOffsetCount, uint32_t const * dynamicOffsets), (override));
        MOCK_METHOD(void, RenderBundleEncoderSetIndexBuffer, (WGPURenderBundleEncoder renderBundleEncoder, WGPUBuffer buffer, uint64_t offset, uint64_t size), (override));
        MOCK_METHOD(void, RenderBundleEncoderSetIndexBufferWithFormat, (WGPURenderBundleEncoder renderBundleEncoder, WGPUBuffer buffer, WGPUIndexFormat format, uint64_t offset, uint64_t size), (override));
        MOCK_METHOD(void, RenderBundleEncoderSetPipeline, (WGPURenderBundleEncoder renderBundleEncoder, WGPURenderPipeline pipeline), (override));
        MOCK_METHOD(void, RenderBundleEncoderSetVertexBuffer, (WGPURenderBundleEncoder renderBundleEncoder, uint32_t slot, WGPUBuffer buffer, uint64_t offset, uint64_t size), (override));

        MOCK_METHOD(void, RenderBundleEncoderReference, (WGPURenderBundleEncoder self), (override));
        MOCK_METHOD(void, RenderBundleEncoderRelease, (WGPURenderBundleEncoder self), (override));
        MOCK_METHOD(void, RenderPassEncoderDraw, (WGPURenderPassEncoder renderPassEncoder, uint32_t vertexCount, uint32_t instanceCount, uint32_t firstVertex, uint32_t firstInstance), (override));
        MOCK_METHOD(void, RenderPassEncoderDrawIndexed, (WGPURenderPassEncoder renderPassEncoder, uint32_t indexCount, uint32_t instanceCount, uint32_t firstIndex, int32_t baseVertex, uint32_t firstInstance), (override));
        MOCK_METHOD(void, RenderPassEncoderDrawIndexedIndirect, (WGPURenderPassEncoder renderPassEncoder, WGPUBuffer indirectBuffer, uint64_t indirectOffset), (override));
        MOCK_METHOD(void, RenderPassEncoderDrawIndirect, (WGPURenderPassEncoder renderPassEncoder, WGPUBuffer indirectBuffer, uint64_t indirectOffset), (override));
        MOCK_METHOD(void, RenderPassEncoderEndPass, (WGPURenderPassEncoder renderPassEncoder), (override));
        MOCK_METHOD(void, RenderPassEncoderExecuteBundles, (WGPURenderPassEncoder renderPassEncoder, uint32_t bundlesCount, WGPURenderBundle const * bundles), (override));
        MOCK_METHOD(void, RenderPassEncoderInsertDebugMarker, (WGPURenderPassEncoder renderPassEncoder, char const * markerLabel), (override));
        MOCK_METHOD(void, RenderPassEncoderPopDebugGroup, (WGPURenderPassEncoder renderPassEncoder), (override));
        MOCK_METHOD(void, RenderPassEncoderPushDebugGroup, (WGPURenderPassEncoder renderPassEncoder, char const * groupLabel), (override));
        MOCK_METHOD(void, RenderPassEncoderSetBindGroup, (WGPURenderPassEncoder renderPassEncoder, uint32_t groupIndex, WGPUBindGroup group, uint32_t dynamicOffsetCount, uint32_t const * dynamicOffsets), (override));
        MOCK_METHOD(void, RenderPassEncoderSetBlendColor, (WGPURenderPassEncoder renderPassEncoder, WGPUColor const * color), (override));
        MOCK_METHOD(void, RenderPassEncoderSetIndexBuffer, (WGPURenderPassEncoder renderPassEncoder, WGPUBuffer buffer, uint64_t offset, uint64_t size), (override));
        MOCK_METHOD(void, RenderPassEncoderSetIndexBufferWithFormat, (WGPURenderPassEncoder renderPassEncoder, WGPUBuffer buffer, WGPUIndexFormat format, uint64_t offset, uint64_t size), (override));
        MOCK_METHOD(void, RenderPassEncoderSetPipeline, (WGPURenderPassEncoder renderPassEncoder, WGPURenderPipeline pipeline), (override));
        MOCK_METHOD(void, RenderPassEncoderSetScissorRect, (WGPURenderPassEncoder renderPassEncoder, uint32_t x, uint32_t y, uint32_t width, uint32_t height), (override));
        MOCK_METHOD(void, RenderPassEncoderSetStencilReference, (WGPURenderPassEncoder renderPassEncoder, uint32_t reference), (override));
        MOCK_METHOD(void, RenderPassEncoderSetVertexBuffer, (WGPURenderPassEncoder renderPassEncoder, uint32_t slot, WGPUBuffer buffer, uint64_t offset, uint64_t size), (override));
        MOCK_METHOD(void, RenderPassEncoderSetViewport, (WGPURenderPassEncoder renderPassEncoder, float x, float y, float width, float height, float minDepth, float maxDepth), (override));
        MOCK_METHOD(void, RenderPassEncoderWriteTimestamp, (WGPURenderPassEncoder renderPassEncoder, WGPUQuerySet querySet, uint32_t queryIndex), (override));

        MOCK_METHOD(void, RenderPassEncoderReference, (WGPURenderPassEncoder self), (override));
        MOCK_METHOD(void, RenderPassEncoderRelease, (WGPURenderPassEncoder self), (override));
        MOCK_METHOD(WGPUBindGroupLayout, RenderPipelineGetBindGroupLayout, (WGPURenderPipeline renderPipeline, uint32_t groupIndex), (override));

        MOCK_METHOD(void, RenderPipelineReference, (WGPURenderPipeline self), (override));
        MOCK_METHOD(void, RenderPipelineRelease, (WGPURenderPipeline self), (override));

        MOCK_METHOD(void, SamplerReference, (WGPUSampler self), (override));
        MOCK_METHOD(void, SamplerRelease, (WGPUSampler self), (override));

        MOCK_METHOD(void, ShaderModuleReference, (WGPUShaderModule self), (override));
        MOCK_METHOD(void, ShaderModuleRelease, (WGPUShaderModule self), (override));

        MOCK_METHOD(void, SurfaceReference, (WGPUSurface self), (override));
        MOCK_METHOD(void, SurfaceRelease, (WGPUSurface self), (override));
        MOCK_METHOD(void, SwapChainConfigure, (WGPUSwapChain swapChain, WGPUTextureFormat format, WGPUTextureUsageFlags allowedUsage, uint32_t width, uint32_t height), (override));
        MOCK_METHOD(WGPUTextureView, SwapChainGetCurrentTextureView, (WGPUSwapChain swapChain), (override));
        MOCK_METHOD(void, SwapChainPresent, (WGPUSwapChain swapChain), (override));

        MOCK_METHOD(void, SwapChainReference, (WGPUSwapChain self), (override));
        MOCK_METHOD(void, SwapChainRelease, (WGPUSwapChain self), (override));
        MOCK_METHOD(WGPUTextureView, TextureCreateView, (WGPUTexture texture, WGPUTextureViewDescriptor const * descriptor), (override));
        MOCK_METHOD(void, TextureDestroy, (WGPUTexture texture), (override));

        MOCK_METHOD(void, TextureReference, (WGPUTexture self), (override));
        MOCK_METHOD(void, TextureRelease, (WGPUTexture self), (override));

        MOCK_METHOD(void, TextureViewReference, (WGPUTextureView self), (override));
        MOCK_METHOD(void, TextureViewRelease, (WGPUTextureView self), (override));

        MOCK_METHOD(void,
                    OnDeviceCreateReadyComputePipelineCallback,
                    (WGPUDevice device, WGPUComputePipelineDescriptor const * descriptor,
                     WGPUCreateReadyComputePipelineCallback callback,
                     void* userdata),
                    (override));
        MOCK_METHOD(void,
                    OnDeviceCreateReadyRenderPipelineCallback,
                    (WGPUDevice device, WGPURenderPipelineDescriptor const * descriptor,
                     WGPUCreateReadyRenderPipelineCallback callback,
                     void* userdata),
                    (override));
        MOCK_METHOD(void, OnDeviceSetUncapturedErrorCallback, (WGPUDevice device, WGPUErrorCallback callback, void* userdata), (override));
        MOCK_METHOD(void, OnDeviceSetDeviceLostCallback, (WGPUDevice device, WGPUDeviceLostCallback callback, void* userdata), (override));
        MOCK_METHOD(bool, OnDevicePopErrorScopeCallback, (WGPUDevice device, WGPUErrorCallback callback, void* userdata), (override));
        MOCK_METHOD(void,
                    OnBufferMapAsyncCallback,
                    (WGPUBuffer buffer, WGPUBufferMapCallback callback, void* userdata),
                    (override));
        MOCK_METHOD(void, OnFenceOnCompletionCallback, (WGPUFence fence, uint64_t value, WGPUFenceOnCompletionCallback callback, void* userdata), (override));
};

#endif  // MOCK_WEBGPU_H
