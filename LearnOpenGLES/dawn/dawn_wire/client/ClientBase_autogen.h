
#ifndef DAWNWIRE_CLIENT_CLIENTBASE_AUTOGEN_H_
#define DAWNWIRE_CLIENT_CLIENTBASE_AUTOGEN_H_

#include "dawn_wire/ChunkedCommandHandler.h"
#include "dawn_wire/WireCmd_autogen.h"
#include "dawn_wire/client/ApiObjects.h"
#include "dawn_wire/client/ObjectAllocator.h"

namespace dawn_wire { namespace client {

    class ClientBase : public ChunkedCommandHandler, public ObjectIdProvider {
      public:
        ClientBase() {
        }

        virtual ~ClientBase() {
        }

        const ObjectAllocator<BindGroup>& BindGroupAllocator() const {
            return mBindGroupAllocator;
        }
        ObjectAllocator<BindGroup>& BindGroupAllocator() {
            return mBindGroupAllocator;
        }
        const ObjectAllocator<BindGroupLayout>& BindGroupLayoutAllocator() const {
            return mBindGroupLayoutAllocator;
        }
        ObjectAllocator<BindGroupLayout>& BindGroupLayoutAllocator() {
            return mBindGroupLayoutAllocator;
        }
        const ObjectAllocator<Buffer>& BufferAllocator() const {
            return mBufferAllocator;
        }
        ObjectAllocator<Buffer>& BufferAllocator() {
            return mBufferAllocator;
        }
        const ObjectAllocator<CommandBuffer>& CommandBufferAllocator() const {
            return mCommandBufferAllocator;
        }
        ObjectAllocator<CommandBuffer>& CommandBufferAllocator() {
            return mCommandBufferAllocator;
        }
        const ObjectAllocator<CommandEncoder>& CommandEncoderAllocator() const {
            return mCommandEncoderAllocator;
        }
        ObjectAllocator<CommandEncoder>& CommandEncoderAllocator() {
            return mCommandEncoderAllocator;
        }
        const ObjectAllocator<ComputePassEncoder>& ComputePassEncoderAllocator() const {
            return mComputePassEncoderAllocator;
        }
        ObjectAllocator<ComputePassEncoder>& ComputePassEncoderAllocator() {
            return mComputePassEncoderAllocator;
        }
        const ObjectAllocator<ComputePipeline>& ComputePipelineAllocator() const {
            return mComputePipelineAllocator;
        }
        ObjectAllocator<ComputePipeline>& ComputePipelineAllocator() {
            return mComputePipelineAllocator;
        }
        const ObjectAllocator<Device>& DeviceAllocator() const {
            return mDeviceAllocator;
        }
        ObjectAllocator<Device>& DeviceAllocator() {
            return mDeviceAllocator;
        }
        const ObjectAllocator<Fence>& FenceAllocator() const {
            return mFenceAllocator;
        }
        ObjectAllocator<Fence>& FenceAllocator() {
            return mFenceAllocator;
        }
        const ObjectAllocator<Instance>& InstanceAllocator() const {
            return mInstanceAllocator;
        }
        ObjectAllocator<Instance>& InstanceAllocator() {
            return mInstanceAllocator;
        }
        const ObjectAllocator<PipelineLayout>& PipelineLayoutAllocator() const {
            return mPipelineLayoutAllocator;
        }
        ObjectAllocator<PipelineLayout>& PipelineLayoutAllocator() {
            return mPipelineLayoutAllocator;
        }
        const ObjectAllocator<QuerySet>& QuerySetAllocator() const {
            return mQuerySetAllocator;
        }
        ObjectAllocator<QuerySet>& QuerySetAllocator() {
            return mQuerySetAllocator;
        }
        const ObjectAllocator<Queue>& QueueAllocator() const {
            return mQueueAllocator;
        }
        ObjectAllocator<Queue>& QueueAllocator() {
            return mQueueAllocator;
        }
        const ObjectAllocator<RenderBundle>& RenderBundleAllocator() const {
            return mRenderBundleAllocator;
        }
        ObjectAllocator<RenderBundle>& RenderBundleAllocator() {
            return mRenderBundleAllocator;
        }
        const ObjectAllocator<RenderBundleEncoder>& RenderBundleEncoderAllocator() const {
            return mRenderBundleEncoderAllocator;
        }
        ObjectAllocator<RenderBundleEncoder>& RenderBundleEncoderAllocator() {
            return mRenderBundleEncoderAllocator;
        }
        const ObjectAllocator<RenderPassEncoder>& RenderPassEncoderAllocator() const {
            return mRenderPassEncoderAllocator;
        }
        ObjectAllocator<RenderPassEncoder>& RenderPassEncoderAllocator() {
            return mRenderPassEncoderAllocator;
        }
        const ObjectAllocator<RenderPipeline>& RenderPipelineAllocator() const {
            return mRenderPipelineAllocator;
        }
        ObjectAllocator<RenderPipeline>& RenderPipelineAllocator() {
            return mRenderPipelineAllocator;
        }
        const ObjectAllocator<Sampler>& SamplerAllocator() const {
            return mSamplerAllocator;
        }
        ObjectAllocator<Sampler>& SamplerAllocator() {
            return mSamplerAllocator;
        }
        const ObjectAllocator<ShaderModule>& ShaderModuleAllocator() const {
            return mShaderModuleAllocator;
        }
        ObjectAllocator<ShaderModule>& ShaderModuleAllocator() {
            return mShaderModuleAllocator;
        }
        const ObjectAllocator<Surface>& SurfaceAllocator() const {
            return mSurfaceAllocator;
        }
        ObjectAllocator<Surface>& SurfaceAllocator() {
            return mSurfaceAllocator;
        }
        const ObjectAllocator<SwapChain>& SwapChainAllocator() const {
            return mSwapChainAllocator;
        }
        ObjectAllocator<SwapChain>& SwapChainAllocator() {
            return mSwapChainAllocator;
        }
        const ObjectAllocator<Texture>& TextureAllocator() const {
            return mTextureAllocator;
        }
        ObjectAllocator<Texture>& TextureAllocator() {
            return mTextureAllocator;
        }
        const ObjectAllocator<TextureView>& TextureViewAllocator() const {
            return mTextureViewAllocator;
        }
        ObjectAllocator<TextureView>& TextureViewAllocator() {
            return mTextureViewAllocator;
        }

      private:
        // Implementation of the ObjectIdProvider interface
        ObjectId GetId(WGPUBindGroup object) const final {
            return object == nullptr ? 0 : reinterpret_cast<BindGroup*>(object)->id;
        }
        ObjectId GetOptionalId(WGPUBindGroup object) const final {
            if (object == nullptr) {
                return 0;
            }
            return GetId(object);
        }
        ObjectId GetId(WGPUBindGroupLayout object) const final {
            return object == nullptr ? 0 : reinterpret_cast<BindGroupLayout*>(object)->id;
        }
        ObjectId GetOptionalId(WGPUBindGroupLayout object) const final {
            if (object == nullptr) {
                return 0;
            }
            return GetId(object);
        }
        ObjectId GetId(WGPUBuffer object) const final {
            return object == nullptr ? 0 : reinterpret_cast<Buffer*>(object)->id;
        }
        ObjectId GetOptionalId(WGPUBuffer object) const final {
            if (object == nullptr) {
                return 0;
            }
            return GetId(object);
        }
        ObjectId GetId(WGPUCommandBuffer object) const final {
            return object == nullptr ? 0 : reinterpret_cast<CommandBuffer*>(object)->id;
        }
        ObjectId GetOptionalId(WGPUCommandBuffer object) const final {
            if (object == nullptr) {
                return 0;
            }
            return GetId(object);
        }
        ObjectId GetId(WGPUCommandEncoder object) const final {
            return object == nullptr ? 0 : reinterpret_cast<CommandEncoder*>(object)->id;
        }
        ObjectId GetOptionalId(WGPUCommandEncoder object) const final {
            if (object == nullptr) {
                return 0;
            }
            return GetId(object);
        }
        ObjectId GetId(WGPUComputePassEncoder object) const final {
            return object == nullptr ? 0 : reinterpret_cast<ComputePassEncoder*>(object)->id;
        }
        ObjectId GetOptionalId(WGPUComputePassEncoder object) const final {
            if (object == nullptr) {
                return 0;
            }
            return GetId(object);
        }
        ObjectId GetId(WGPUComputePipeline object) const final {
            return object == nullptr ? 0 : reinterpret_cast<ComputePipeline*>(object)->id;
        }
        ObjectId GetOptionalId(WGPUComputePipeline object) const final {
            if (object == nullptr) {
                return 0;
            }
            return GetId(object);
        }
        ObjectId GetId(WGPUDevice object) const final {
            return object == nullptr ? 0 : reinterpret_cast<Device*>(object)->id;
        }
        ObjectId GetOptionalId(WGPUDevice object) const final {
            if (object == nullptr) {
                return 0;
            }
            return GetId(object);
        }
        ObjectId GetId(WGPUFence object) const final {
            return object == nullptr ? 0 : reinterpret_cast<Fence*>(object)->id;
        }
        ObjectId GetOptionalId(WGPUFence object) const final {
            if (object == nullptr) {
                return 0;
            }
            return GetId(object);
        }
        ObjectId GetId(WGPUInstance object) const final {
            return object == nullptr ? 0 : reinterpret_cast<Instance*>(object)->id;
        }
        ObjectId GetOptionalId(WGPUInstance object) const final {
            if (object == nullptr) {
                return 0;
            }
            return GetId(object);
        }
        ObjectId GetId(WGPUPipelineLayout object) const final {
            return object == nullptr ? 0 : reinterpret_cast<PipelineLayout*>(object)->id;
        }
        ObjectId GetOptionalId(WGPUPipelineLayout object) const final {
            if (object == nullptr) {
                return 0;
            }
            return GetId(object);
        }
        ObjectId GetId(WGPUQuerySet object) const final {
            return object == nullptr ? 0 : reinterpret_cast<QuerySet*>(object)->id;
        }
        ObjectId GetOptionalId(WGPUQuerySet object) const final {
            if (object == nullptr) {
                return 0;
            }
            return GetId(object);
        }
        ObjectId GetId(WGPUQueue object) const final {
            return object == nullptr ? 0 : reinterpret_cast<Queue*>(object)->id;
        }
        ObjectId GetOptionalId(WGPUQueue object) const final {
            if (object == nullptr) {
                return 0;
            }
            return GetId(object);
        }
        ObjectId GetId(WGPURenderBundle object) const final {
            return object == nullptr ? 0 : reinterpret_cast<RenderBundle*>(object)->id;
        }
        ObjectId GetOptionalId(WGPURenderBundle object) const final {
            if (object == nullptr) {
                return 0;
            }
            return GetId(object);
        }
        ObjectId GetId(WGPURenderBundleEncoder object) const final {
            return object == nullptr ? 0 : reinterpret_cast<RenderBundleEncoder*>(object)->id;
        }
        ObjectId GetOptionalId(WGPURenderBundleEncoder object) const final {
            if (object == nullptr) {
                return 0;
            }
            return GetId(object);
        }
        ObjectId GetId(WGPURenderPassEncoder object) const final {
            return object == nullptr ? 0 : reinterpret_cast<RenderPassEncoder*>(object)->id;
        }
        ObjectId GetOptionalId(WGPURenderPassEncoder object) const final {
            if (object == nullptr) {
                return 0;
            }
            return GetId(object);
        }
        ObjectId GetId(WGPURenderPipeline object) const final {
            return object == nullptr ? 0 : reinterpret_cast<RenderPipeline*>(object)->id;
        }
        ObjectId GetOptionalId(WGPURenderPipeline object) const final {
            if (object == nullptr) {
                return 0;
            }
            return GetId(object);
        }
        ObjectId GetId(WGPUSampler object) const final {
            return object == nullptr ? 0 : reinterpret_cast<Sampler*>(object)->id;
        }
        ObjectId GetOptionalId(WGPUSampler object) const final {
            if (object == nullptr) {
                return 0;
            }
            return GetId(object);
        }
        ObjectId GetId(WGPUShaderModule object) const final {
            return object == nullptr ? 0 : reinterpret_cast<ShaderModule*>(object)->id;
        }
        ObjectId GetOptionalId(WGPUShaderModule object) const final {
            if (object == nullptr) {
                return 0;
            }
            return GetId(object);
        }
        ObjectId GetId(WGPUSurface object) const final {
            return object == nullptr ? 0 : reinterpret_cast<Surface*>(object)->id;
        }
        ObjectId GetOptionalId(WGPUSurface object) const final {
            if (object == nullptr) {
                return 0;
            }
            return GetId(object);
        }
        ObjectId GetId(WGPUSwapChain object) const final {
            return object == nullptr ? 0 : reinterpret_cast<SwapChain*>(object)->id;
        }
        ObjectId GetOptionalId(WGPUSwapChain object) const final {
            if (object == nullptr) {
                return 0;
            }
            return GetId(object);
        }
        ObjectId GetId(WGPUTexture object) const final {
            return object == nullptr ? 0 : reinterpret_cast<Texture*>(object)->id;
        }
        ObjectId GetOptionalId(WGPUTexture object) const final {
            if (object == nullptr) {
                return 0;
            }
            return GetId(object);
        }
        ObjectId GetId(WGPUTextureView object) const final {
            return object == nullptr ? 0 : reinterpret_cast<TextureView*>(object)->id;
        }
        ObjectId GetOptionalId(WGPUTextureView object) const final {
            if (object == nullptr) {
                return 0;
            }
            return GetId(object);
        }

        ObjectAllocator<BindGroup> mBindGroupAllocator;
        ObjectAllocator<BindGroupLayout> mBindGroupLayoutAllocator;
        ObjectAllocator<Buffer> mBufferAllocator;
        ObjectAllocator<CommandBuffer> mCommandBufferAllocator;
        ObjectAllocator<CommandEncoder> mCommandEncoderAllocator;
        ObjectAllocator<ComputePassEncoder> mComputePassEncoderAllocator;
        ObjectAllocator<ComputePipeline> mComputePipelineAllocator;
        ObjectAllocator<Device> mDeviceAllocator;
        ObjectAllocator<Fence> mFenceAllocator;
        ObjectAllocator<Instance> mInstanceAllocator;
        ObjectAllocator<PipelineLayout> mPipelineLayoutAllocator;
        ObjectAllocator<QuerySet> mQuerySetAllocator;
        ObjectAllocator<Queue> mQueueAllocator;
        ObjectAllocator<RenderBundle> mRenderBundleAllocator;
        ObjectAllocator<RenderBundleEncoder> mRenderBundleEncoderAllocator;
        ObjectAllocator<RenderPassEncoder> mRenderPassEncoderAllocator;
        ObjectAllocator<RenderPipeline> mRenderPipelineAllocator;
        ObjectAllocator<Sampler> mSamplerAllocator;
        ObjectAllocator<ShaderModule> mShaderModuleAllocator;
        ObjectAllocator<Surface> mSurfaceAllocator;
        ObjectAllocator<SwapChain> mSwapChainAllocator;
        ObjectAllocator<Texture> mTextureAllocator;
        ObjectAllocator<TextureView> mTextureViewAllocator;
    };

}}  // namespace dawn_wire::client

#endif  // DAWNWIRE_CLIENT_CLIENTBASE_AUTOGEN_H_
