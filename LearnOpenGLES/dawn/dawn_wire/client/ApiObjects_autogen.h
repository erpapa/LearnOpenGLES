
#ifndef DAWNWIRE_CLIENT_APIOBJECTS_AUTOGEN_H_
#define DAWNWIRE_CLIENT_APIOBJECTS_AUTOGEN_H_

namespace dawn_wire { namespace client {

    struct BindGroup : ObjectBase {
        using ObjectBase::ObjectBase;
    };

    inline BindGroup* FromAPI(WGPUBindGroup obj) {
        return reinterpret_cast<BindGroup*>(obj);
    }
    inline WGPUBindGroup ToAPI(BindGroup* obj) {
        return reinterpret_cast<WGPUBindGroup>(obj);
    }

    struct BindGroupLayout : ObjectBase {
        using ObjectBase::ObjectBase;
    };

    inline BindGroupLayout* FromAPI(WGPUBindGroupLayout obj) {
        return reinterpret_cast<BindGroupLayout*>(obj);
    }
    inline WGPUBindGroupLayout ToAPI(BindGroupLayout* obj) {
        return reinterpret_cast<WGPUBindGroupLayout>(obj);
    }

    class Buffer;

    inline Buffer* FromAPI(WGPUBuffer obj) {
        return reinterpret_cast<Buffer*>(obj);
    }
    inline WGPUBuffer ToAPI(Buffer* obj) {
        return reinterpret_cast<WGPUBuffer>(obj);
    }

    struct CommandBuffer : ObjectBase {
        using ObjectBase::ObjectBase;
    };

    inline CommandBuffer* FromAPI(WGPUCommandBuffer obj) {
        return reinterpret_cast<CommandBuffer*>(obj);
    }
    inline WGPUCommandBuffer ToAPI(CommandBuffer* obj) {
        return reinterpret_cast<WGPUCommandBuffer>(obj);
    }

    struct CommandEncoder : ObjectBase {
        using ObjectBase::ObjectBase;
    };

    inline CommandEncoder* FromAPI(WGPUCommandEncoder obj) {
        return reinterpret_cast<CommandEncoder*>(obj);
    }
    inline WGPUCommandEncoder ToAPI(CommandEncoder* obj) {
        return reinterpret_cast<WGPUCommandEncoder>(obj);
    }

    struct ComputePassEncoder : ObjectBase {
        using ObjectBase::ObjectBase;
    };

    inline ComputePassEncoder* FromAPI(WGPUComputePassEncoder obj) {
        return reinterpret_cast<ComputePassEncoder*>(obj);
    }
    inline WGPUComputePassEncoder ToAPI(ComputePassEncoder* obj) {
        return reinterpret_cast<WGPUComputePassEncoder>(obj);
    }

    struct ComputePipeline : ObjectBase {
        using ObjectBase::ObjectBase;
    };

    inline ComputePipeline* FromAPI(WGPUComputePipeline obj) {
        return reinterpret_cast<ComputePipeline*>(obj);
    }
    inline WGPUComputePipeline ToAPI(ComputePipeline* obj) {
        return reinterpret_cast<WGPUComputePipeline>(obj);
    }

    class Device;

    inline Device* FromAPI(WGPUDevice obj) {
        return reinterpret_cast<Device*>(obj);
    }
    inline WGPUDevice ToAPI(Device* obj) {
        return reinterpret_cast<WGPUDevice>(obj);
    }

    class Fence;

    inline Fence* FromAPI(WGPUFence obj) {
        return reinterpret_cast<Fence*>(obj);
    }
    inline WGPUFence ToAPI(Fence* obj) {
        return reinterpret_cast<WGPUFence>(obj);
    }

    struct Instance : ObjectBase {
        using ObjectBase::ObjectBase;
    };

    inline Instance* FromAPI(WGPUInstance obj) {
        return reinterpret_cast<Instance*>(obj);
    }
    inline WGPUInstance ToAPI(Instance* obj) {
        return reinterpret_cast<WGPUInstance>(obj);
    }

    struct PipelineLayout : ObjectBase {
        using ObjectBase::ObjectBase;
    };

    inline PipelineLayout* FromAPI(WGPUPipelineLayout obj) {
        return reinterpret_cast<PipelineLayout*>(obj);
    }
    inline WGPUPipelineLayout ToAPI(PipelineLayout* obj) {
        return reinterpret_cast<WGPUPipelineLayout>(obj);
    }

    struct QuerySet : ObjectBase {
        using ObjectBase::ObjectBase;
    };

    inline QuerySet* FromAPI(WGPUQuerySet obj) {
        return reinterpret_cast<QuerySet*>(obj);
    }
    inline WGPUQuerySet ToAPI(QuerySet* obj) {
        return reinterpret_cast<WGPUQuerySet>(obj);
    }

    class Queue;

    inline Queue* FromAPI(WGPUQueue obj) {
        return reinterpret_cast<Queue*>(obj);
    }
    inline WGPUQueue ToAPI(Queue* obj) {
        return reinterpret_cast<WGPUQueue>(obj);
    }

    struct RenderBundle : ObjectBase {
        using ObjectBase::ObjectBase;
    };

    inline RenderBundle* FromAPI(WGPURenderBundle obj) {
        return reinterpret_cast<RenderBundle*>(obj);
    }
    inline WGPURenderBundle ToAPI(RenderBundle* obj) {
        return reinterpret_cast<WGPURenderBundle>(obj);
    }

    struct RenderBundleEncoder : ObjectBase {
        using ObjectBase::ObjectBase;
    };

    inline RenderBundleEncoder* FromAPI(WGPURenderBundleEncoder obj) {
        return reinterpret_cast<RenderBundleEncoder*>(obj);
    }
    inline WGPURenderBundleEncoder ToAPI(RenderBundleEncoder* obj) {
        return reinterpret_cast<WGPURenderBundleEncoder>(obj);
    }

    struct RenderPassEncoder : ObjectBase {
        using ObjectBase::ObjectBase;
    };

    inline RenderPassEncoder* FromAPI(WGPURenderPassEncoder obj) {
        return reinterpret_cast<RenderPassEncoder*>(obj);
    }
    inline WGPURenderPassEncoder ToAPI(RenderPassEncoder* obj) {
        return reinterpret_cast<WGPURenderPassEncoder>(obj);
    }

    struct RenderPipeline : ObjectBase {
        using ObjectBase::ObjectBase;
    };

    inline RenderPipeline* FromAPI(WGPURenderPipeline obj) {
        return reinterpret_cast<RenderPipeline*>(obj);
    }
    inline WGPURenderPipeline ToAPI(RenderPipeline* obj) {
        return reinterpret_cast<WGPURenderPipeline>(obj);
    }

    struct Sampler : ObjectBase {
        using ObjectBase::ObjectBase;
    };

    inline Sampler* FromAPI(WGPUSampler obj) {
        return reinterpret_cast<Sampler*>(obj);
    }
    inline WGPUSampler ToAPI(Sampler* obj) {
        return reinterpret_cast<WGPUSampler>(obj);
    }

    struct ShaderModule : ObjectBase {
        using ObjectBase::ObjectBase;
    };

    inline ShaderModule* FromAPI(WGPUShaderModule obj) {
        return reinterpret_cast<ShaderModule*>(obj);
    }
    inline WGPUShaderModule ToAPI(ShaderModule* obj) {
        return reinterpret_cast<WGPUShaderModule>(obj);
    }

    struct Surface : ObjectBase {
        using ObjectBase::ObjectBase;
    };

    inline Surface* FromAPI(WGPUSurface obj) {
        return reinterpret_cast<Surface*>(obj);
    }
    inline WGPUSurface ToAPI(Surface* obj) {
        return reinterpret_cast<WGPUSurface>(obj);
    }

    struct SwapChain : ObjectBase {
        using ObjectBase::ObjectBase;
    };

    inline SwapChain* FromAPI(WGPUSwapChain obj) {
        return reinterpret_cast<SwapChain*>(obj);
    }
    inline WGPUSwapChain ToAPI(SwapChain* obj) {
        return reinterpret_cast<WGPUSwapChain>(obj);
    }

    struct Texture : ObjectBase {
        using ObjectBase::ObjectBase;
    };

    inline Texture* FromAPI(WGPUTexture obj) {
        return reinterpret_cast<Texture*>(obj);
    }
    inline WGPUTexture ToAPI(Texture* obj) {
        return reinterpret_cast<WGPUTexture>(obj);
    }

    struct TextureView : ObjectBase {
        using ObjectBase::ObjectBase;
    };

    inline TextureView* FromAPI(WGPUTextureView obj) {
        return reinterpret_cast<TextureView*>(obj);
    }
    inline WGPUTextureView ToAPI(TextureView* obj) {
        return reinterpret_cast<WGPUTextureView>(obj);
    }

}}  // namespace dawn_wire::client

#endif  // DAWNWIRE_CLIENT_APIOBJECTS_AUTOGEN_H_
