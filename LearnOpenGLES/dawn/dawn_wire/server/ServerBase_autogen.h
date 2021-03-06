
#ifndef DAWNWIRE_SERVER_SERVERBASE_H_
#define DAWNWIRE_SERVER_SERVERBASE_H_

#include "dawn/dawn_proc_table.h"
#include "dawn_wire/ChunkedCommandHandler.h"
#include "dawn_wire/Wire.h"
#include "dawn_wire/WireCmd_autogen.h"
#include "dawn_wire/WireDeserializeAllocator.h"
#include "dawn_wire/server/ObjectStorage.h"

namespace dawn_wire { namespace server {

    class ServerBase : public ChunkedCommandHandler, public ObjectIdResolver {
      public:
        ServerBase() = default;
        virtual ~ServerBase() = default;

      protected:
        void DestroyAllObjects(const DawnProcTable& procs) {
            {
                std::vector<WGPUBindGroup> handles = mKnownBindGroup.AcquireAllHandles();
                for (WGPUBindGroup handle : handles) {
                    procs.bindGroupRelease(handle);
                }
            }
            {
                std::vector<WGPUBindGroupLayout> handles = mKnownBindGroupLayout.AcquireAllHandles();
                for (WGPUBindGroupLayout handle : handles) {
                    procs.bindGroupLayoutRelease(handle);
                }
            }
            {
                std::vector<WGPUBuffer> handles = mKnownBuffer.AcquireAllHandles();
                for (WGPUBuffer handle : handles) {
                    procs.bufferRelease(handle);
                }
            }
            {
                std::vector<WGPUCommandBuffer> handles = mKnownCommandBuffer.AcquireAllHandles();
                for (WGPUCommandBuffer handle : handles) {
                    procs.commandBufferRelease(handle);
                }
            }
            {
                std::vector<WGPUCommandEncoder> handles = mKnownCommandEncoder.AcquireAllHandles();
                for (WGPUCommandEncoder handle : handles) {
                    procs.commandEncoderRelease(handle);
                }
            }
            {
                std::vector<WGPUComputePassEncoder> handles = mKnownComputePassEncoder.AcquireAllHandles();
                for (WGPUComputePassEncoder handle : handles) {
                    procs.computePassEncoderRelease(handle);
                }
            }
            {
                std::vector<WGPUComputePipeline> handles = mKnownComputePipeline.AcquireAllHandles();
                for (WGPUComputePipeline handle : handles) {
                    procs.computePipelineRelease(handle);
                }
            }
            {
                std::vector<WGPUFence> handles = mKnownFence.AcquireAllHandles();
                for (WGPUFence handle : handles) {
                    procs.fenceRelease(handle);
                }
            }
            {
                std::vector<WGPUInstance> handles = mKnownInstance.AcquireAllHandles();
                for (WGPUInstance handle : handles) {
                    procs.instanceRelease(handle);
                }
            }
            {
                std::vector<WGPUPipelineLayout> handles = mKnownPipelineLayout.AcquireAllHandles();
                for (WGPUPipelineLayout handle : handles) {
                    procs.pipelineLayoutRelease(handle);
                }
            }
            {
                std::vector<WGPUQuerySet> handles = mKnownQuerySet.AcquireAllHandles();
                for (WGPUQuerySet handle : handles) {
                    procs.querySetRelease(handle);
                }
            }
            {
                std::vector<WGPUQueue> handles = mKnownQueue.AcquireAllHandles();
                for (WGPUQueue handle : handles) {
                    procs.queueRelease(handle);
                }
            }
            {
                std::vector<WGPURenderBundle> handles = mKnownRenderBundle.AcquireAllHandles();
                for (WGPURenderBundle handle : handles) {
                    procs.renderBundleRelease(handle);
                }
            }
            {
                std::vector<WGPURenderBundleEncoder> handles = mKnownRenderBundleEncoder.AcquireAllHandles();
                for (WGPURenderBundleEncoder handle : handles) {
                    procs.renderBundleEncoderRelease(handle);
                }
            }
            {
                std::vector<WGPURenderPassEncoder> handles = mKnownRenderPassEncoder.AcquireAllHandles();
                for (WGPURenderPassEncoder handle : handles) {
                    procs.renderPassEncoderRelease(handle);
                }
            }
            {
                std::vector<WGPURenderPipeline> handles = mKnownRenderPipeline.AcquireAllHandles();
                for (WGPURenderPipeline handle : handles) {
                    procs.renderPipelineRelease(handle);
                }
            }
            {
                std::vector<WGPUSampler> handles = mKnownSampler.AcquireAllHandles();
                for (WGPUSampler handle : handles) {
                    procs.samplerRelease(handle);
                }
            }
            {
                std::vector<WGPUShaderModule> handles = mKnownShaderModule.AcquireAllHandles();
                for (WGPUShaderModule handle : handles) {
                    procs.shaderModuleRelease(handle);
                }
            }
            {
                std::vector<WGPUSurface> handles = mKnownSurface.AcquireAllHandles();
                for (WGPUSurface handle : handles) {
                    procs.surfaceRelease(handle);
                }
            }
            {
                std::vector<WGPUSwapChain> handles = mKnownSwapChain.AcquireAllHandles();
                for (WGPUSwapChain handle : handles) {
                    procs.swapChainRelease(handle);
                }
            }
            {
                std::vector<WGPUTexture> handles = mKnownTexture.AcquireAllHandles();
                for (WGPUTexture handle : handles) {
                    procs.textureRelease(handle);
                }
            }
            {
                std::vector<WGPUTextureView> handles = mKnownTextureView.AcquireAllHandles();
                for (WGPUTextureView handle : handles) {
                    procs.textureViewRelease(handle);
                }
            }
        }

        const KnownObjects<WGPUBindGroup>& BindGroupObjects() const {
            return mKnownBindGroup;
        }
        KnownObjects<WGPUBindGroup>& BindGroupObjects() {
            return mKnownBindGroup;
        }
        const KnownObjects<WGPUBindGroupLayout>& BindGroupLayoutObjects() const {
            return mKnownBindGroupLayout;
        }
        KnownObjects<WGPUBindGroupLayout>& BindGroupLayoutObjects() {
            return mKnownBindGroupLayout;
        }
        const KnownObjects<WGPUBuffer>& BufferObjects() const {
            return mKnownBuffer;
        }
        KnownObjects<WGPUBuffer>& BufferObjects() {
            return mKnownBuffer;
        }
        const KnownObjects<WGPUCommandBuffer>& CommandBufferObjects() const {
            return mKnownCommandBuffer;
        }
        KnownObjects<WGPUCommandBuffer>& CommandBufferObjects() {
            return mKnownCommandBuffer;
        }
        const KnownObjects<WGPUCommandEncoder>& CommandEncoderObjects() const {
            return mKnownCommandEncoder;
        }
        KnownObjects<WGPUCommandEncoder>& CommandEncoderObjects() {
            return mKnownCommandEncoder;
        }
        const KnownObjects<WGPUComputePassEncoder>& ComputePassEncoderObjects() const {
            return mKnownComputePassEncoder;
        }
        KnownObjects<WGPUComputePassEncoder>& ComputePassEncoderObjects() {
            return mKnownComputePassEncoder;
        }
        const KnownObjects<WGPUComputePipeline>& ComputePipelineObjects() const {
            return mKnownComputePipeline;
        }
        KnownObjects<WGPUComputePipeline>& ComputePipelineObjects() {
            return mKnownComputePipeline;
        }
        const KnownObjects<WGPUDevice>& DeviceObjects() const {
            return mKnownDevice;
        }
        KnownObjects<WGPUDevice>& DeviceObjects() {
            return mKnownDevice;
        }
        const KnownObjects<WGPUFence>& FenceObjects() const {
            return mKnownFence;
        }
        KnownObjects<WGPUFence>& FenceObjects() {
            return mKnownFence;
        }
        const KnownObjects<WGPUInstance>& InstanceObjects() const {
            return mKnownInstance;
        }
        KnownObjects<WGPUInstance>& InstanceObjects() {
            return mKnownInstance;
        }
        const KnownObjects<WGPUPipelineLayout>& PipelineLayoutObjects() const {
            return mKnownPipelineLayout;
        }
        KnownObjects<WGPUPipelineLayout>& PipelineLayoutObjects() {
            return mKnownPipelineLayout;
        }
        const KnownObjects<WGPUQuerySet>& QuerySetObjects() const {
            return mKnownQuerySet;
        }
        KnownObjects<WGPUQuerySet>& QuerySetObjects() {
            return mKnownQuerySet;
        }
        const KnownObjects<WGPUQueue>& QueueObjects() const {
            return mKnownQueue;
        }
        KnownObjects<WGPUQueue>& QueueObjects() {
            return mKnownQueue;
        }
        const KnownObjects<WGPURenderBundle>& RenderBundleObjects() const {
            return mKnownRenderBundle;
        }
        KnownObjects<WGPURenderBundle>& RenderBundleObjects() {
            return mKnownRenderBundle;
        }
        const KnownObjects<WGPURenderBundleEncoder>& RenderBundleEncoderObjects() const {
            return mKnownRenderBundleEncoder;
        }
        KnownObjects<WGPURenderBundleEncoder>& RenderBundleEncoderObjects() {
            return mKnownRenderBundleEncoder;
        }
        const KnownObjects<WGPURenderPassEncoder>& RenderPassEncoderObjects() const {
            return mKnownRenderPassEncoder;
        }
        KnownObjects<WGPURenderPassEncoder>& RenderPassEncoderObjects() {
            return mKnownRenderPassEncoder;
        }
        const KnownObjects<WGPURenderPipeline>& RenderPipelineObjects() const {
            return mKnownRenderPipeline;
        }
        KnownObjects<WGPURenderPipeline>& RenderPipelineObjects() {
            return mKnownRenderPipeline;
        }
        const KnownObjects<WGPUSampler>& SamplerObjects() const {
            return mKnownSampler;
        }
        KnownObjects<WGPUSampler>& SamplerObjects() {
            return mKnownSampler;
        }
        const KnownObjects<WGPUShaderModule>& ShaderModuleObjects() const {
            return mKnownShaderModule;
        }
        KnownObjects<WGPUShaderModule>& ShaderModuleObjects() {
            return mKnownShaderModule;
        }
        const KnownObjects<WGPUSurface>& SurfaceObjects() const {
            return mKnownSurface;
        }
        KnownObjects<WGPUSurface>& SurfaceObjects() {
            return mKnownSurface;
        }
        const KnownObjects<WGPUSwapChain>& SwapChainObjects() const {
            return mKnownSwapChain;
        }
        KnownObjects<WGPUSwapChain>& SwapChainObjects() {
            return mKnownSwapChain;
        }
        const KnownObjects<WGPUTexture>& TextureObjects() const {
            return mKnownTexture;
        }
        KnownObjects<WGPUTexture>& TextureObjects() {
            return mKnownTexture;
        }
        const KnownObjects<WGPUTextureView>& TextureViewObjects() const {
            return mKnownTextureView;
        }
        KnownObjects<WGPUTextureView>& TextureViewObjects() {
            return mKnownTextureView;
        }

        const ObjectIdLookupTable<WGPUFence>& FenceObjectIdTable() const {
            return mFenceIdTable;
        }
        ObjectIdLookupTable<WGPUFence>& FenceObjectIdTable() {
            return mFenceIdTable;
        }

      private:
        // Implementation of the ObjectIdResolver interface
        DeserializeResult GetFromId(ObjectId id, WGPUBindGroup* out) const final {
            auto data = mKnownBindGroup.Get(id);
            if (data == nullptr) {
                return DeserializeResult::FatalError;
            }

            *out = data->handle;
            return DeserializeResult::Success;
        }

        DeserializeResult GetOptionalFromId(ObjectId id, WGPUBindGroup* out) const final {
            if (id == 0) {
                *out = nullptr;
                return DeserializeResult::Success;
            }

            return GetFromId(id, out);
        }
        DeserializeResult GetFromId(ObjectId id, WGPUBindGroupLayout* out) const final {
            auto data = mKnownBindGroupLayout.Get(id);
            if (data == nullptr) {
                return DeserializeResult::FatalError;
            }

            *out = data->handle;
            return DeserializeResult::Success;
        }

        DeserializeResult GetOptionalFromId(ObjectId id, WGPUBindGroupLayout* out) const final {
            if (id == 0) {
                *out = nullptr;
                return DeserializeResult::Success;
            }

            return GetFromId(id, out);
        }
        DeserializeResult GetFromId(ObjectId id, WGPUBuffer* out) const final {
            auto data = mKnownBuffer.Get(id);
            if (data == nullptr) {
                return DeserializeResult::FatalError;
            }

            *out = data->handle;
            return DeserializeResult::Success;
        }

        DeserializeResult GetOptionalFromId(ObjectId id, WGPUBuffer* out) const final {
            if (id == 0) {
                *out = nullptr;
                return DeserializeResult::Success;
            }

            return GetFromId(id, out);
        }
        DeserializeResult GetFromId(ObjectId id, WGPUCommandBuffer* out) const final {
            auto data = mKnownCommandBuffer.Get(id);
            if (data == nullptr) {
                return DeserializeResult::FatalError;
            }

            *out = data->handle;
            return DeserializeResult::Success;
        }

        DeserializeResult GetOptionalFromId(ObjectId id, WGPUCommandBuffer* out) const final {
            if (id == 0) {
                *out = nullptr;
                return DeserializeResult::Success;
            }

            return GetFromId(id, out);
        }
        DeserializeResult GetFromId(ObjectId id, WGPUCommandEncoder* out) const final {
            auto data = mKnownCommandEncoder.Get(id);
            if (data == nullptr) {
                return DeserializeResult::FatalError;
            }

            *out = data->handle;
            return DeserializeResult::Success;
        }

        DeserializeResult GetOptionalFromId(ObjectId id, WGPUCommandEncoder* out) const final {
            if (id == 0) {
                *out = nullptr;
                return DeserializeResult::Success;
            }

            return GetFromId(id, out);
        }
        DeserializeResult GetFromId(ObjectId id, WGPUComputePassEncoder* out) const final {
            auto data = mKnownComputePassEncoder.Get(id);
            if (data == nullptr) {
                return DeserializeResult::FatalError;
            }

            *out = data->handle;
            return DeserializeResult::Success;
        }

        DeserializeResult GetOptionalFromId(ObjectId id, WGPUComputePassEncoder* out) const final {
            if (id == 0) {
                *out = nullptr;
                return DeserializeResult::Success;
            }

            return GetFromId(id, out);
        }
        DeserializeResult GetFromId(ObjectId id, WGPUComputePipeline* out) const final {
            auto data = mKnownComputePipeline.Get(id);
            if (data == nullptr) {
                return DeserializeResult::FatalError;
            }

            *out = data->handle;
            return DeserializeResult::Success;
        }

        DeserializeResult GetOptionalFromId(ObjectId id, WGPUComputePipeline* out) const final {
            if (id == 0) {
                *out = nullptr;
                return DeserializeResult::Success;
            }

            return GetFromId(id, out);
        }
        DeserializeResult GetFromId(ObjectId id, WGPUDevice* out) const final {
            auto data = mKnownDevice.Get(id);
            if (data == nullptr) {
                return DeserializeResult::FatalError;
            }

            *out = data->handle;
            return DeserializeResult::Success;
        }

        DeserializeResult GetOptionalFromId(ObjectId id, WGPUDevice* out) const final {
            if (id == 0) {
                *out = nullptr;
                return DeserializeResult::Success;
            }

            return GetFromId(id, out);
        }
        DeserializeResult GetFromId(ObjectId id, WGPUFence* out) const final {
            auto data = mKnownFence.Get(id);
            if (data == nullptr) {
                return DeserializeResult::FatalError;
            }

            *out = data->handle;
            return DeserializeResult::Success;
        }

        DeserializeResult GetOptionalFromId(ObjectId id, WGPUFence* out) const final {
            if (id == 0) {
                *out = nullptr;
                return DeserializeResult::Success;
            }

            return GetFromId(id, out);
        }
        DeserializeResult GetFromId(ObjectId id, WGPUInstance* out) const final {
            auto data = mKnownInstance.Get(id);
            if (data == nullptr) {
                return DeserializeResult::FatalError;
            }

            *out = data->handle;
            return DeserializeResult::Success;
        }

        DeserializeResult GetOptionalFromId(ObjectId id, WGPUInstance* out) const final {
            if (id == 0) {
                *out = nullptr;
                return DeserializeResult::Success;
            }

            return GetFromId(id, out);
        }
        DeserializeResult GetFromId(ObjectId id, WGPUPipelineLayout* out) const final {
            auto data = mKnownPipelineLayout.Get(id);
            if (data == nullptr) {
                return DeserializeResult::FatalError;
            }

            *out = data->handle;
            return DeserializeResult::Success;
        }

        DeserializeResult GetOptionalFromId(ObjectId id, WGPUPipelineLayout* out) const final {
            if (id == 0) {
                *out = nullptr;
                return DeserializeResult::Success;
            }

            return GetFromId(id, out);
        }
        DeserializeResult GetFromId(ObjectId id, WGPUQuerySet* out) const final {
            auto data = mKnownQuerySet.Get(id);
            if (data == nullptr) {
                return DeserializeResult::FatalError;
            }

            *out = data->handle;
            return DeserializeResult::Success;
        }

        DeserializeResult GetOptionalFromId(ObjectId id, WGPUQuerySet* out) const final {
            if (id == 0) {
                *out = nullptr;
                return DeserializeResult::Success;
            }

            return GetFromId(id, out);
        }
        DeserializeResult GetFromId(ObjectId id, WGPUQueue* out) const final {
            auto data = mKnownQueue.Get(id);
            if (data == nullptr) {
                return DeserializeResult::FatalError;
            }

            *out = data->handle;
            return DeserializeResult::Success;
        }

        DeserializeResult GetOptionalFromId(ObjectId id, WGPUQueue* out) const final {
            if (id == 0) {
                *out = nullptr;
                return DeserializeResult::Success;
            }

            return GetFromId(id, out);
        }
        DeserializeResult GetFromId(ObjectId id, WGPURenderBundle* out) const final {
            auto data = mKnownRenderBundle.Get(id);
            if (data == nullptr) {
                return DeserializeResult::FatalError;
            }

            *out = data->handle;
            return DeserializeResult::Success;
        }

        DeserializeResult GetOptionalFromId(ObjectId id, WGPURenderBundle* out) const final {
            if (id == 0) {
                *out = nullptr;
                return DeserializeResult::Success;
            }

            return GetFromId(id, out);
        }
        DeserializeResult GetFromId(ObjectId id, WGPURenderBundleEncoder* out) const final {
            auto data = mKnownRenderBundleEncoder.Get(id);
            if (data == nullptr) {
                return DeserializeResult::FatalError;
            }

            *out = data->handle;
            return DeserializeResult::Success;
        }

        DeserializeResult GetOptionalFromId(ObjectId id, WGPURenderBundleEncoder* out) const final {
            if (id == 0) {
                *out = nullptr;
                return DeserializeResult::Success;
            }

            return GetFromId(id, out);
        }
        DeserializeResult GetFromId(ObjectId id, WGPURenderPassEncoder* out) const final {
            auto data = mKnownRenderPassEncoder.Get(id);
            if (data == nullptr) {
                return DeserializeResult::FatalError;
            }

            *out = data->handle;
            return DeserializeResult::Success;
        }

        DeserializeResult GetOptionalFromId(ObjectId id, WGPURenderPassEncoder* out) const final {
            if (id == 0) {
                *out = nullptr;
                return DeserializeResult::Success;
            }

            return GetFromId(id, out);
        }
        DeserializeResult GetFromId(ObjectId id, WGPURenderPipeline* out) const final {
            auto data = mKnownRenderPipeline.Get(id);
            if (data == nullptr) {
                return DeserializeResult::FatalError;
            }

            *out = data->handle;
            return DeserializeResult::Success;
        }

        DeserializeResult GetOptionalFromId(ObjectId id, WGPURenderPipeline* out) const final {
            if (id == 0) {
                *out = nullptr;
                return DeserializeResult::Success;
            }

            return GetFromId(id, out);
        }
        DeserializeResult GetFromId(ObjectId id, WGPUSampler* out) const final {
            auto data = mKnownSampler.Get(id);
            if (data == nullptr) {
                return DeserializeResult::FatalError;
            }

            *out = data->handle;
            return DeserializeResult::Success;
        }

        DeserializeResult GetOptionalFromId(ObjectId id, WGPUSampler* out) const final {
            if (id == 0) {
                *out = nullptr;
                return DeserializeResult::Success;
            }

            return GetFromId(id, out);
        }
        DeserializeResult GetFromId(ObjectId id, WGPUShaderModule* out) const final {
            auto data = mKnownShaderModule.Get(id);
            if (data == nullptr) {
                return DeserializeResult::FatalError;
            }

            *out = data->handle;
            return DeserializeResult::Success;
        }

        DeserializeResult GetOptionalFromId(ObjectId id, WGPUShaderModule* out) const final {
            if (id == 0) {
                *out = nullptr;
                return DeserializeResult::Success;
            }

            return GetFromId(id, out);
        }
        DeserializeResult GetFromId(ObjectId id, WGPUSurface* out) const final {
            auto data = mKnownSurface.Get(id);
            if (data == nullptr) {
                return DeserializeResult::FatalError;
            }

            *out = data->handle;
            return DeserializeResult::Success;
        }

        DeserializeResult GetOptionalFromId(ObjectId id, WGPUSurface* out) const final {
            if (id == 0) {
                *out = nullptr;
                return DeserializeResult::Success;
            }

            return GetFromId(id, out);
        }
        DeserializeResult GetFromId(ObjectId id, WGPUSwapChain* out) const final {
            auto data = mKnownSwapChain.Get(id);
            if (data == nullptr) {
                return DeserializeResult::FatalError;
            }

            *out = data->handle;
            return DeserializeResult::Success;
        }

        DeserializeResult GetOptionalFromId(ObjectId id, WGPUSwapChain* out) const final {
            if (id == 0) {
                *out = nullptr;
                return DeserializeResult::Success;
            }

            return GetFromId(id, out);
        }
        DeserializeResult GetFromId(ObjectId id, WGPUTexture* out) const final {
            auto data = mKnownTexture.Get(id);
            if (data == nullptr) {
                return DeserializeResult::FatalError;
            }

            *out = data->handle;
            return DeserializeResult::Success;
        }

        DeserializeResult GetOptionalFromId(ObjectId id, WGPUTexture* out) const final {
            if (id == 0) {
                *out = nullptr;
                return DeserializeResult::Success;
            }

            return GetFromId(id, out);
        }
        DeserializeResult GetFromId(ObjectId id, WGPUTextureView* out) const final {
            auto data = mKnownTextureView.Get(id);
            if (data == nullptr) {
                return DeserializeResult::FatalError;
            }

            *out = data->handle;
            return DeserializeResult::Success;
        }

        DeserializeResult GetOptionalFromId(ObjectId id, WGPUTextureView* out) const final {
            if (id == 0) {
                *out = nullptr;
                return DeserializeResult::Success;
            }

            return GetFromId(id, out);
        }

        KnownObjects<WGPUBindGroup> mKnownBindGroup;
        KnownObjects<WGPUBindGroupLayout> mKnownBindGroupLayout;
        KnownObjects<WGPUBuffer> mKnownBuffer;
        KnownObjects<WGPUCommandBuffer> mKnownCommandBuffer;
        KnownObjects<WGPUCommandEncoder> mKnownCommandEncoder;
        KnownObjects<WGPUComputePassEncoder> mKnownComputePassEncoder;
        KnownObjects<WGPUComputePipeline> mKnownComputePipeline;
        KnownObjects<WGPUDevice> mKnownDevice;
        KnownObjects<WGPUFence> mKnownFence;
        KnownObjects<WGPUInstance> mKnownInstance;
        KnownObjects<WGPUPipelineLayout> mKnownPipelineLayout;
        KnownObjects<WGPUQuerySet> mKnownQuerySet;
        KnownObjects<WGPUQueue> mKnownQueue;
        KnownObjects<WGPURenderBundle> mKnownRenderBundle;
        KnownObjects<WGPURenderBundleEncoder> mKnownRenderBundleEncoder;
        KnownObjects<WGPURenderPassEncoder> mKnownRenderPassEncoder;
        KnownObjects<WGPURenderPipeline> mKnownRenderPipeline;
        KnownObjects<WGPUSampler> mKnownSampler;
        KnownObjects<WGPUShaderModule> mKnownShaderModule;
        KnownObjects<WGPUSurface> mKnownSurface;
        KnownObjects<WGPUSwapChain> mKnownSwapChain;
        KnownObjects<WGPUTexture> mKnownTexture;
        KnownObjects<WGPUTextureView> mKnownTextureView;

        ObjectIdLookupTable<WGPUFence> mFenceIdTable;
    };

}}  // namespace dawn_wire::server

#endif  // DAWNWIRE_SERVER_SERVERBASE_H_
