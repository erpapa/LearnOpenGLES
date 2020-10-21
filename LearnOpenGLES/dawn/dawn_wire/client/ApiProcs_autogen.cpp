
#include "common/Log.h"
#include "dawn_wire/client/ApiObjects.h"
#include "dawn_wire/client/Client.h"

#include <algorithm>
#include <cstring>
#include <string>
#include <vector>

namespace dawn_wire { namespace client {
    namespace {


        DAWN_DECLARE_UNUSED bool DeviceMatches(const Device* device, const WGPUBindGroup obj) {
            return device == reinterpret_cast<const BindGroup*>(obj)->device;
        }

        DAWN_DECLARE_UNUSED bool DeviceMatches(const Device* device, const WGPUBindGroup *const obj, uint32_t count = 1) {
            ASSERT(count == 0 || obj != nullptr);
            for (uint32_t i = 0; i < count; ++i) {
                if (!DeviceMatches(device, obj[i])) {
                    return false;
                }
            }
            return true;
        }
        DAWN_DECLARE_UNUSED bool DeviceMatches(const Device* device, const WGPUBindGroupLayout obj) {
            return device == reinterpret_cast<const BindGroupLayout*>(obj)->device;
        }

        DAWN_DECLARE_UNUSED bool DeviceMatches(const Device* device, const WGPUBindGroupLayout *const obj, uint32_t count = 1) {
            ASSERT(count == 0 || obj != nullptr);
            for (uint32_t i = 0; i < count; ++i) {
                if (!DeviceMatches(device, obj[i])) {
                    return false;
                }
            }
            return true;
        }
        DAWN_DECLARE_UNUSED bool DeviceMatches(const Device* device, const WGPUBuffer obj) {
            return device == reinterpret_cast<const Buffer*>(obj)->device;
        }

        DAWN_DECLARE_UNUSED bool DeviceMatches(const Device* device, const WGPUBuffer *const obj, uint32_t count = 1) {
            ASSERT(count == 0 || obj != nullptr);
            for (uint32_t i = 0; i < count; ++i) {
                if (!DeviceMatches(device, obj[i])) {
                    return false;
                }
            }
            return true;
        }
        DAWN_DECLARE_UNUSED bool DeviceMatches(const Device* device, const WGPUCommandBuffer obj) {
            return device == reinterpret_cast<const CommandBuffer*>(obj)->device;
        }

        DAWN_DECLARE_UNUSED bool DeviceMatches(const Device* device, const WGPUCommandBuffer *const obj, uint32_t count = 1) {
            ASSERT(count == 0 || obj != nullptr);
            for (uint32_t i = 0; i < count; ++i) {
                if (!DeviceMatches(device, obj[i])) {
                    return false;
                }
            }
            return true;
        }
        DAWN_DECLARE_UNUSED bool DeviceMatches(const Device* device, const WGPUCommandEncoder obj) {
            return device == reinterpret_cast<const CommandEncoder*>(obj)->device;
        }

        DAWN_DECLARE_UNUSED bool DeviceMatches(const Device* device, const WGPUCommandEncoder *const obj, uint32_t count = 1) {
            ASSERT(count == 0 || obj != nullptr);
            for (uint32_t i = 0; i < count; ++i) {
                if (!DeviceMatches(device, obj[i])) {
                    return false;
                }
            }
            return true;
        }
        DAWN_DECLARE_UNUSED bool DeviceMatches(const Device* device, const WGPUComputePassEncoder obj) {
            return device == reinterpret_cast<const ComputePassEncoder*>(obj)->device;
        }

        DAWN_DECLARE_UNUSED bool DeviceMatches(const Device* device, const WGPUComputePassEncoder *const obj, uint32_t count = 1) {
            ASSERT(count == 0 || obj != nullptr);
            for (uint32_t i = 0; i < count; ++i) {
                if (!DeviceMatches(device, obj[i])) {
                    return false;
                }
            }
            return true;
        }
        DAWN_DECLARE_UNUSED bool DeviceMatches(const Device* device, const WGPUComputePipeline obj) {
            return device == reinterpret_cast<const ComputePipeline*>(obj)->device;
        }

        DAWN_DECLARE_UNUSED bool DeviceMatches(const Device* device, const WGPUComputePipeline *const obj, uint32_t count = 1) {
            ASSERT(count == 0 || obj != nullptr);
            for (uint32_t i = 0; i < count; ++i) {
                if (!DeviceMatches(device, obj[i])) {
                    return false;
                }
            }
            return true;
        }
        DAWN_DECLARE_UNUSED bool DeviceMatches(const Device* device, const WGPUDevice obj) {
            return device == reinterpret_cast<const Device*>(obj)->device;
        }

        DAWN_DECLARE_UNUSED bool DeviceMatches(const Device* device, const WGPUDevice *const obj, uint32_t count = 1) {
            ASSERT(count == 0 || obj != nullptr);
            for (uint32_t i = 0; i < count; ++i) {
                if (!DeviceMatches(device, obj[i])) {
                    return false;
                }
            }
            return true;
        }
        DAWN_DECLARE_UNUSED bool DeviceMatches(const Device* device, const WGPUFence obj) {
            return device == reinterpret_cast<const Fence*>(obj)->device;
        }

        DAWN_DECLARE_UNUSED bool DeviceMatches(const Device* device, const WGPUFence *const obj, uint32_t count = 1) {
            ASSERT(count == 0 || obj != nullptr);
            for (uint32_t i = 0; i < count; ++i) {
                if (!DeviceMatches(device, obj[i])) {
                    return false;
                }
            }
            return true;
        }
        DAWN_DECLARE_UNUSED bool DeviceMatches(const Device* device, const WGPUInstance obj) {
            return device == reinterpret_cast<const Instance*>(obj)->device;
        }

        DAWN_DECLARE_UNUSED bool DeviceMatches(const Device* device, const WGPUInstance *const obj, uint32_t count = 1) {
            ASSERT(count == 0 || obj != nullptr);
            for (uint32_t i = 0; i < count; ++i) {
                if (!DeviceMatches(device, obj[i])) {
                    return false;
                }
            }
            return true;
        }
        DAWN_DECLARE_UNUSED bool DeviceMatches(const Device* device, const WGPUPipelineLayout obj) {
            return device == reinterpret_cast<const PipelineLayout*>(obj)->device;
        }

        DAWN_DECLARE_UNUSED bool DeviceMatches(const Device* device, const WGPUPipelineLayout *const obj, uint32_t count = 1) {
            ASSERT(count == 0 || obj != nullptr);
            for (uint32_t i = 0; i < count; ++i) {
                if (!DeviceMatches(device, obj[i])) {
                    return false;
                }
            }
            return true;
        }
        DAWN_DECLARE_UNUSED bool DeviceMatches(const Device* device, const WGPUQuerySet obj) {
            return device == reinterpret_cast<const QuerySet*>(obj)->device;
        }

        DAWN_DECLARE_UNUSED bool DeviceMatches(const Device* device, const WGPUQuerySet *const obj, uint32_t count = 1) {
            ASSERT(count == 0 || obj != nullptr);
            for (uint32_t i = 0; i < count; ++i) {
                if (!DeviceMatches(device, obj[i])) {
                    return false;
                }
            }
            return true;
        }
        DAWN_DECLARE_UNUSED bool DeviceMatches(const Device* device, const WGPUQueue obj) {
            return device == reinterpret_cast<const Queue*>(obj)->device;
        }

        DAWN_DECLARE_UNUSED bool DeviceMatches(const Device* device, const WGPUQueue *const obj, uint32_t count = 1) {
            ASSERT(count == 0 || obj != nullptr);
            for (uint32_t i = 0; i < count; ++i) {
                if (!DeviceMatches(device, obj[i])) {
                    return false;
                }
            }
            return true;
        }
        DAWN_DECLARE_UNUSED bool DeviceMatches(const Device* device, const WGPURenderBundle obj) {
            return device == reinterpret_cast<const RenderBundle*>(obj)->device;
        }

        DAWN_DECLARE_UNUSED bool DeviceMatches(const Device* device, const WGPURenderBundle *const obj, uint32_t count = 1) {
            ASSERT(count == 0 || obj != nullptr);
            for (uint32_t i = 0; i < count; ++i) {
                if (!DeviceMatches(device, obj[i])) {
                    return false;
                }
            }
            return true;
        }
        DAWN_DECLARE_UNUSED bool DeviceMatches(const Device* device, const WGPURenderBundleEncoder obj) {
            return device == reinterpret_cast<const RenderBundleEncoder*>(obj)->device;
        }

        DAWN_DECLARE_UNUSED bool DeviceMatches(const Device* device, const WGPURenderBundleEncoder *const obj, uint32_t count = 1) {
            ASSERT(count == 0 || obj != nullptr);
            for (uint32_t i = 0; i < count; ++i) {
                if (!DeviceMatches(device, obj[i])) {
                    return false;
                }
            }
            return true;
        }
        DAWN_DECLARE_UNUSED bool DeviceMatches(const Device* device, const WGPURenderPassEncoder obj) {
            return device == reinterpret_cast<const RenderPassEncoder*>(obj)->device;
        }

        DAWN_DECLARE_UNUSED bool DeviceMatches(const Device* device, const WGPURenderPassEncoder *const obj, uint32_t count = 1) {
            ASSERT(count == 0 || obj != nullptr);
            for (uint32_t i = 0; i < count; ++i) {
                if (!DeviceMatches(device, obj[i])) {
                    return false;
                }
            }
            return true;
        }
        DAWN_DECLARE_UNUSED bool DeviceMatches(const Device* device, const WGPURenderPipeline obj) {
            return device == reinterpret_cast<const RenderPipeline*>(obj)->device;
        }

        DAWN_DECLARE_UNUSED bool DeviceMatches(const Device* device, const WGPURenderPipeline *const obj, uint32_t count = 1) {
            ASSERT(count == 0 || obj != nullptr);
            for (uint32_t i = 0; i < count; ++i) {
                if (!DeviceMatches(device, obj[i])) {
                    return false;
                }
            }
            return true;
        }
        DAWN_DECLARE_UNUSED bool DeviceMatches(const Device* device, const WGPUSampler obj) {
            return device == reinterpret_cast<const Sampler*>(obj)->device;
        }

        DAWN_DECLARE_UNUSED bool DeviceMatches(const Device* device, const WGPUSampler *const obj, uint32_t count = 1) {
            ASSERT(count == 0 || obj != nullptr);
            for (uint32_t i = 0; i < count; ++i) {
                if (!DeviceMatches(device, obj[i])) {
                    return false;
                }
            }
            return true;
        }
        DAWN_DECLARE_UNUSED bool DeviceMatches(const Device* device, const WGPUShaderModule obj) {
            return device == reinterpret_cast<const ShaderModule*>(obj)->device;
        }

        DAWN_DECLARE_UNUSED bool DeviceMatches(const Device* device, const WGPUShaderModule *const obj, uint32_t count = 1) {
            ASSERT(count == 0 || obj != nullptr);
            for (uint32_t i = 0; i < count; ++i) {
                if (!DeviceMatches(device, obj[i])) {
                    return false;
                }
            }
            return true;
        }
        DAWN_DECLARE_UNUSED bool DeviceMatches(const Device* device, const WGPUSurface obj) {
            return device == reinterpret_cast<const Surface*>(obj)->device;
        }

        DAWN_DECLARE_UNUSED bool DeviceMatches(const Device* device, const WGPUSurface *const obj, uint32_t count = 1) {
            ASSERT(count == 0 || obj != nullptr);
            for (uint32_t i = 0; i < count; ++i) {
                if (!DeviceMatches(device, obj[i])) {
                    return false;
                }
            }
            return true;
        }
        DAWN_DECLARE_UNUSED bool DeviceMatches(const Device* device, const WGPUSwapChain obj) {
            return device == reinterpret_cast<const SwapChain*>(obj)->device;
        }

        DAWN_DECLARE_UNUSED bool DeviceMatches(const Device* device, const WGPUSwapChain *const obj, uint32_t count = 1) {
            ASSERT(count == 0 || obj != nullptr);
            for (uint32_t i = 0; i < count; ++i) {
                if (!DeviceMatches(device, obj[i])) {
                    return false;
                }
            }
            return true;
        }
        DAWN_DECLARE_UNUSED bool DeviceMatches(const Device* device, const WGPUTexture obj) {
            return device == reinterpret_cast<const Texture*>(obj)->device;
        }

        DAWN_DECLARE_UNUSED bool DeviceMatches(const Device* device, const WGPUTexture *const obj, uint32_t count = 1) {
            ASSERT(count == 0 || obj != nullptr);
            for (uint32_t i = 0; i < count; ++i) {
                if (!DeviceMatches(device, obj[i])) {
                    return false;
                }
            }
            return true;
        }
        DAWN_DECLARE_UNUSED bool DeviceMatches(const Device* device, const WGPUTextureView obj) {
            return device == reinterpret_cast<const TextureView*>(obj)->device;
        }

        DAWN_DECLARE_UNUSED bool DeviceMatches(const Device* device, const WGPUTextureView *const obj, uint32_t count = 1) {
            ASSERT(count == 0 || obj != nullptr);
            for (uint32_t i = 0; i < count; ++i) {
                if (!DeviceMatches(device, obj[i])) {
                    return false;
                }
            }
            return true;
        }

        bool DeviceMatches(const Device* device, WGPUChainedStruct const* chainedStruct);

        DAWN_DECLARE_UNUSED bool DeviceMatches(const Device* device, const WGPUAdapterProperties& obj) {
            if (!DeviceMatches(device, obj.nextInChain)) {
                return false;
            }
            return true;
        }

        DAWN_DECLARE_UNUSED bool DeviceMatches(const Device* device, const WGPUAdapterProperties *const obj, uint32_t count = 1) {
            for (uint32_t i = 0; i < count; ++i) {
                if (!DeviceMatches(device, obj[i])) {
                    return false;
                }
            }
            return true;
        }
        DAWN_DECLARE_UNUSED bool DeviceMatches(const Device* device, const WGPUBindGroupEntry& obj) {
            if (obj.buffer != nullptr)
            {
                if (!DeviceMatches(device, obj.buffer)) {
                    return false;
                }
            }
            if (obj.sampler != nullptr)
            {
                if (!DeviceMatches(device, obj.sampler)) {
                    return false;
                }
            }
            if (obj.textureView != nullptr)
            {
                if (!DeviceMatches(device, obj.textureView)) {
                    return false;
                }
            }
            return true;
        }

        DAWN_DECLARE_UNUSED bool DeviceMatches(const Device* device, const WGPUBindGroupEntry *const obj, uint32_t count = 1) {
            for (uint32_t i = 0; i < count; ++i) {
                if (!DeviceMatches(device, obj[i])) {
                    return false;
                }
            }
            return true;
        }
        DAWN_DECLARE_UNUSED bool DeviceMatches(const Device* device, const WGPUBufferDescriptor& obj) {
            if (!DeviceMatches(device, obj.nextInChain)) {
                return false;
            }
            return true;
        }

        DAWN_DECLARE_UNUSED bool DeviceMatches(const Device* device, const WGPUBufferDescriptor *const obj, uint32_t count = 1) {
            for (uint32_t i = 0; i < count; ++i) {
                if (!DeviceMatches(device, obj[i])) {
                    return false;
                }
            }
            return true;
        }
        DAWN_DECLARE_UNUSED bool DeviceMatches(const Device* device, const WGPUCommandBufferDescriptor& obj) {
            if (!DeviceMatches(device, obj.nextInChain)) {
                return false;
            }
            return true;
        }

        DAWN_DECLARE_UNUSED bool DeviceMatches(const Device* device, const WGPUCommandBufferDescriptor *const obj, uint32_t count = 1) {
            for (uint32_t i = 0; i < count; ++i) {
                if (!DeviceMatches(device, obj[i])) {
                    return false;
                }
            }
            return true;
        }
        DAWN_DECLARE_UNUSED bool DeviceMatches(const Device* device, const WGPUCommandEncoderDescriptor& obj) {
            if (!DeviceMatches(device, obj.nextInChain)) {
                return false;
            }
            return true;
        }

        DAWN_DECLARE_UNUSED bool DeviceMatches(const Device* device, const WGPUCommandEncoderDescriptor *const obj, uint32_t count = 1) {
            for (uint32_t i = 0; i < count; ++i) {
                if (!DeviceMatches(device, obj[i])) {
                    return false;
                }
            }
            return true;
        }
        DAWN_DECLARE_UNUSED bool DeviceMatches(const Device* device, const WGPUComputePassDescriptor& obj) {
            if (!DeviceMatches(device, obj.nextInChain)) {
                return false;
            }
            return true;
        }

        DAWN_DECLARE_UNUSED bool DeviceMatches(const Device* device, const WGPUComputePassDescriptor *const obj, uint32_t count = 1) {
            for (uint32_t i = 0; i < count; ++i) {
                if (!DeviceMatches(device, obj[i])) {
                    return false;
                }
            }
            return true;
        }
        DAWN_DECLARE_UNUSED bool DeviceMatches(const Device* device, const WGPUFenceDescriptor& obj) {
            if (!DeviceMatches(device, obj.nextInChain)) {
                return false;
            }
            return true;
        }

        DAWN_DECLARE_UNUSED bool DeviceMatches(const Device* device, const WGPUFenceDescriptor *const obj, uint32_t count = 1) {
            for (uint32_t i = 0; i < count; ++i) {
                if (!DeviceMatches(device, obj[i])) {
                    return false;
                }
            }
            return true;
        }
        DAWN_DECLARE_UNUSED bool DeviceMatches(const Device* device, const WGPUInstanceDescriptor& obj) {
            if (!DeviceMatches(device, obj.nextInChain)) {
                return false;
            }
            return true;
        }

        DAWN_DECLARE_UNUSED bool DeviceMatches(const Device* device, const WGPUInstanceDescriptor *const obj, uint32_t count = 1) {
            for (uint32_t i = 0; i < count; ++i) {
                if (!DeviceMatches(device, obj[i])) {
                    return false;
                }
            }
            return true;
        }
        DAWN_DECLARE_UNUSED bool DeviceMatches(const Device* device, const WGPUPipelineLayoutDescriptor& obj) {
            if (!DeviceMatches(device, obj.nextInChain)) {
                return false;
            }
            {
                if (!DeviceMatches(device, obj.bindGroupLayouts, obj.bindGroupLayoutCount)) {
                    return false;
                }
            }
            return true;
        }

        DAWN_DECLARE_UNUSED bool DeviceMatches(const Device* device, const WGPUPipelineLayoutDescriptor *const obj, uint32_t count = 1) {
            for (uint32_t i = 0; i < count; ++i) {
                if (!DeviceMatches(device, obj[i])) {
                    return false;
                }
            }
            return true;
        }
        DAWN_DECLARE_UNUSED bool DeviceMatches(const Device* device, const WGPUProgrammableStageDescriptor& obj) {
            if (!DeviceMatches(device, obj.nextInChain)) {
                return false;
            }
            {
                if (!DeviceMatches(device, obj.module)) {
                    return false;
                }
            }
            return true;
        }

        DAWN_DECLARE_UNUSED bool DeviceMatches(const Device* device, const WGPUProgrammableStageDescriptor *const obj, uint32_t count = 1) {
            for (uint32_t i = 0; i < count; ++i) {
                if (!DeviceMatches(device, obj[i])) {
                    return false;
                }
            }
            return true;
        }
        DAWN_DECLARE_UNUSED bool DeviceMatches(const Device* device, const WGPUQuerySetDescriptor& obj) {
            if (!DeviceMatches(device, obj.nextInChain)) {
                return false;
            }
            return true;
        }

        DAWN_DECLARE_UNUSED bool DeviceMatches(const Device* device, const WGPUQuerySetDescriptor *const obj, uint32_t count = 1) {
            for (uint32_t i = 0; i < count; ++i) {
                if (!DeviceMatches(device, obj[i])) {
                    return false;
                }
            }
            return true;
        }
        DAWN_DECLARE_UNUSED bool DeviceMatches(const Device* device, const WGPURasterizationStateDescriptor& obj) {
            if (!DeviceMatches(device, obj.nextInChain)) {
                return false;
            }
            return true;
        }

        DAWN_DECLARE_UNUSED bool DeviceMatches(const Device* device, const WGPURasterizationStateDescriptor *const obj, uint32_t count = 1) {
            for (uint32_t i = 0; i < count; ++i) {
                if (!DeviceMatches(device, obj[i])) {
                    return false;
                }
            }
            return true;
        }
        DAWN_DECLARE_UNUSED bool DeviceMatches(const Device* device, const WGPURenderBundleDescriptor& obj) {
            if (!DeviceMatches(device, obj.nextInChain)) {
                return false;
            }
            return true;
        }

        DAWN_DECLARE_UNUSED bool DeviceMatches(const Device* device, const WGPURenderBundleDescriptor *const obj, uint32_t count = 1) {
            for (uint32_t i = 0; i < count; ++i) {
                if (!DeviceMatches(device, obj[i])) {
                    return false;
                }
            }
            return true;
        }
        DAWN_DECLARE_UNUSED bool DeviceMatches(const Device* device, const WGPURenderBundleEncoderDescriptor& obj) {
            if (!DeviceMatches(device, obj.nextInChain)) {
                return false;
            }
            return true;
        }

        DAWN_DECLARE_UNUSED bool DeviceMatches(const Device* device, const WGPURenderBundleEncoderDescriptor *const obj, uint32_t count = 1) {
            for (uint32_t i = 0; i < count; ++i) {
                if (!DeviceMatches(device, obj[i])) {
                    return false;
                }
            }
            return true;
        }
        DAWN_DECLARE_UNUSED bool DeviceMatches(const Device* device, const WGPURenderPassDepthStencilAttachmentDescriptor& obj) {
            {
                if (!DeviceMatches(device, obj.attachment)) {
                    return false;
                }
            }
            return true;
        }

        DAWN_DECLARE_UNUSED bool DeviceMatches(const Device* device, const WGPURenderPassDepthStencilAttachmentDescriptor *const obj, uint32_t count = 1) {
            for (uint32_t i = 0; i < count; ++i) {
                if (!DeviceMatches(device, obj[i])) {
                    return false;
                }
            }
            return true;
        }
        DAWN_DECLARE_UNUSED bool DeviceMatches(const Device* device, const WGPUSamplerDescriptor& obj) {
            if (!DeviceMatches(device, obj.nextInChain)) {
                return false;
            }
            return true;
        }

        DAWN_DECLARE_UNUSED bool DeviceMatches(const Device* device, const WGPUSamplerDescriptor *const obj, uint32_t count = 1) {
            for (uint32_t i = 0; i < count; ++i) {
                if (!DeviceMatches(device, obj[i])) {
                    return false;
                }
            }
            return true;
        }
        DAWN_DECLARE_UNUSED bool DeviceMatches(const Device* device, const WGPUSamplerDescriptorDummyAnisotropicFiltering& obj) {
            return true;
        }

        DAWN_DECLARE_UNUSED bool DeviceMatches(const Device* device, const WGPUSamplerDescriptorDummyAnisotropicFiltering *const obj, uint32_t count = 1) {
            for (uint32_t i = 0; i < count; ++i) {
                if (!DeviceMatches(device, obj[i])) {
                    return false;
                }
            }
            return true;
        }
        DAWN_DECLARE_UNUSED bool DeviceMatches(const Device* device, const WGPUShaderModuleDescriptor& obj) {
            if (!DeviceMatches(device, obj.nextInChain)) {
                return false;
            }
            return true;
        }

        DAWN_DECLARE_UNUSED bool DeviceMatches(const Device* device, const WGPUShaderModuleDescriptor *const obj, uint32_t count = 1) {
            for (uint32_t i = 0; i < count; ++i) {
                if (!DeviceMatches(device, obj[i])) {
                    return false;
                }
            }
            return true;
        }
        DAWN_DECLARE_UNUSED bool DeviceMatches(const Device* device, const WGPUShaderModuleSPIRVDescriptor& obj) {
            return true;
        }

        DAWN_DECLARE_UNUSED bool DeviceMatches(const Device* device, const WGPUShaderModuleSPIRVDescriptor *const obj, uint32_t count = 1) {
            for (uint32_t i = 0; i < count; ++i) {
                if (!DeviceMatches(device, obj[i])) {
                    return false;
                }
            }
            return true;
        }
        DAWN_DECLARE_UNUSED bool DeviceMatches(const Device* device, const WGPUShaderModuleWGSLDescriptor& obj) {
            return true;
        }

        DAWN_DECLARE_UNUSED bool DeviceMatches(const Device* device, const WGPUShaderModuleWGSLDescriptor *const obj, uint32_t count = 1) {
            for (uint32_t i = 0; i < count; ++i) {
                if (!DeviceMatches(device, obj[i])) {
                    return false;
                }
            }
            return true;
        }
        DAWN_DECLARE_UNUSED bool DeviceMatches(const Device* device, const WGPUSurfaceDescriptor& obj) {
            if (!DeviceMatches(device, obj.nextInChain)) {
                return false;
            }
            return true;
        }

        DAWN_DECLARE_UNUSED bool DeviceMatches(const Device* device, const WGPUSurfaceDescriptor *const obj, uint32_t count = 1) {
            for (uint32_t i = 0; i < count; ++i) {
                if (!DeviceMatches(device, obj[i])) {
                    return false;
                }
            }
            return true;
        }
        DAWN_DECLARE_UNUSED bool DeviceMatches(const Device* device, const WGPUSurfaceDescriptorFromCanvasHTMLSelector& obj) {
            return true;
        }

        DAWN_DECLARE_UNUSED bool DeviceMatches(const Device* device, const WGPUSurfaceDescriptorFromCanvasHTMLSelector *const obj, uint32_t count = 1) {
            for (uint32_t i = 0; i < count; ++i) {
                if (!DeviceMatches(device, obj[i])) {
                    return false;
                }
            }
            return true;
        }
        DAWN_DECLARE_UNUSED bool DeviceMatches(const Device* device, const WGPUSurfaceDescriptorFromMetalLayer& obj) {
            return true;
        }

        DAWN_DECLARE_UNUSED bool DeviceMatches(const Device* device, const WGPUSurfaceDescriptorFromMetalLayer *const obj, uint32_t count = 1) {
            for (uint32_t i = 0; i < count; ++i) {
                if (!DeviceMatches(device, obj[i])) {
                    return false;
                }
            }
            return true;
        }
        DAWN_DECLARE_UNUSED bool DeviceMatches(const Device* device, const WGPUSurfaceDescriptorFromWindowsHWND& obj) {
            return true;
        }

        DAWN_DECLARE_UNUSED bool DeviceMatches(const Device* device, const WGPUSurfaceDescriptorFromWindowsHWND *const obj, uint32_t count = 1) {
            for (uint32_t i = 0; i < count; ++i) {
                if (!DeviceMatches(device, obj[i])) {
                    return false;
                }
            }
            return true;
        }
        DAWN_DECLARE_UNUSED bool DeviceMatches(const Device* device, const WGPUSurfaceDescriptorFromXlib& obj) {
            return true;
        }

        DAWN_DECLARE_UNUSED bool DeviceMatches(const Device* device, const WGPUSurfaceDescriptorFromXlib *const obj, uint32_t count = 1) {
            for (uint32_t i = 0; i < count; ++i) {
                if (!DeviceMatches(device, obj[i])) {
                    return false;
                }
            }
            return true;
        }
        DAWN_DECLARE_UNUSED bool DeviceMatches(const Device* device, const WGPUSwapChainDescriptor& obj) {
            if (!DeviceMatches(device, obj.nextInChain)) {
                return false;
            }
            return true;
        }

        DAWN_DECLARE_UNUSED bool DeviceMatches(const Device* device, const WGPUSwapChainDescriptor *const obj, uint32_t count = 1) {
            for (uint32_t i = 0; i < count; ++i) {
                if (!DeviceMatches(device, obj[i])) {
                    return false;
                }
            }
            return true;
        }
        DAWN_DECLARE_UNUSED bool DeviceMatches(const Device* device, const WGPUTextureDataLayout& obj) {
            if (!DeviceMatches(device, obj.nextInChain)) {
                return false;
            }
            return true;
        }

        DAWN_DECLARE_UNUSED bool DeviceMatches(const Device* device, const WGPUTextureDataLayout *const obj, uint32_t count = 1) {
            for (uint32_t i = 0; i < count; ++i) {
                if (!DeviceMatches(device, obj[i])) {
                    return false;
                }
            }
            return true;
        }
        DAWN_DECLARE_UNUSED bool DeviceMatches(const Device* device, const WGPUTextureViewDescriptor& obj) {
            if (!DeviceMatches(device, obj.nextInChain)) {
                return false;
            }
            return true;
        }

        DAWN_DECLARE_UNUSED bool DeviceMatches(const Device* device, const WGPUTextureViewDescriptor *const obj, uint32_t count = 1) {
            for (uint32_t i = 0; i < count; ++i) {
                if (!DeviceMatches(device, obj[i])) {
                    return false;
                }
            }
            return true;
        }
        DAWN_DECLARE_UNUSED bool DeviceMatches(const Device* device, const WGPUBindGroupDescriptor& obj) {
            if (!DeviceMatches(device, obj.nextInChain)) {
                return false;
            }
            {
                if (!DeviceMatches(device, obj.layout)) {
                    return false;
                }
            }
            {
                if (!DeviceMatches(device, obj.entries, obj.entryCount)) {
                    return false;
                }
            }
            return true;
        }

        DAWN_DECLARE_UNUSED bool DeviceMatches(const Device* device, const WGPUBindGroupDescriptor *const obj, uint32_t count = 1) {
            for (uint32_t i = 0; i < count; ++i) {
                if (!DeviceMatches(device, obj[i])) {
                    return false;
                }
            }
            return true;
        }
        DAWN_DECLARE_UNUSED bool DeviceMatches(const Device* device, const WGPUBindGroupLayoutDescriptor& obj) {
            if (!DeviceMatches(device, obj.nextInChain)) {
                return false;
            }
            return true;
        }

        DAWN_DECLARE_UNUSED bool DeviceMatches(const Device* device, const WGPUBindGroupLayoutDescriptor *const obj, uint32_t count = 1) {
            for (uint32_t i = 0; i < count; ++i) {
                if (!DeviceMatches(device, obj[i])) {
                    return false;
                }
            }
            return true;
        }
        DAWN_DECLARE_UNUSED bool DeviceMatches(const Device* device, const WGPUBufferCopyView& obj) {
            if (!DeviceMatches(device, obj.nextInChain)) {
                return false;
            }
            {
                if (!DeviceMatches(device, obj.layout)) {
                    return false;
                }
            }
            {
                if (!DeviceMatches(device, obj.buffer)) {
                    return false;
                }
            }
            return true;
        }

        DAWN_DECLARE_UNUSED bool DeviceMatches(const Device* device, const WGPUBufferCopyView *const obj, uint32_t count = 1) {
            for (uint32_t i = 0; i < count; ++i) {
                if (!DeviceMatches(device, obj[i])) {
                    return false;
                }
            }
            return true;
        }
        DAWN_DECLARE_UNUSED bool DeviceMatches(const Device* device, const WGPUColorStateDescriptor& obj) {
            if (!DeviceMatches(device, obj.nextInChain)) {
                return false;
            }
            return true;
        }

        DAWN_DECLARE_UNUSED bool DeviceMatches(const Device* device, const WGPUColorStateDescriptor *const obj, uint32_t count = 1) {
            for (uint32_t i = 0; i < count; ++i) {
                if (!DeviceMatches(device, obj[i])) {
                    return false;
                }
            }
            return true;
        }
        DAWN_DECLARE_UNUSED bool DeviceMatches(const Device* device, const WGPUComputePipelineDescriptor& obj) {
            if (!DeviceMatches(device, obj.nextInChain)) {
                return false;
            }
            if (obj.layout != nullptr)
            {
                if (!DeviceMatches(device, obj.layout)) {
                    return false;
                }
            }
            {
                if (!DeviceMatches(device, obj.computeStage)) {
                    return false;
                }
            }
            return true;
        }

        DAWN_DECLARE_UNUSED bool DeviceMatches(const Device* device, const WGPUComputePipelineDescriptor *const obj, uint32_t count = 1) {
            for (uint32_t i = 0; i < count; ++i) {
                if (!DeviceMatches(device, obj[i])) {
                    return false;
                }
            }
            return true;
        }
        DAWN_DECLARE_UNUSED bool DeviceMatches(const Device* device, const WGPUDepthStencilStateDescriptor& obj) {
            if (!DeviceMatches(device, obj.nextInChain)) {
                return false;
            }
            return true;
        }

        DAWN_DECLARE_UNUSED bool DeviceMatches(const Device* device, const WGPUDepthStencilStateDescriptor *const obj, uint32_t count = 1) {
            for (uint32_t i = 0; i < count; ++i) {
                if (!DeviceMatches(device, obj[i])) {
                    return false;
                }
            }
            return true;
        }
        DAWN_DECLARE_UNUSED bool DeviceMatches(const Device* device, const WGPURenderPassColorAttachmentDescriptor& obj) {
            {
                if (!DeviceMatches(device, obj.attachment)) {
                    return false;
                }
            }
            if (obj.resolveTarget != nullptr)
            {
                if (!DeviceMatches(device, obj.resolveTarget)) {
                    return false;
                }
            }
            return true;
        }

        DAWN_DECLARE_UNUSED bool DeviceMatches(const Device* device, const WGPURenderPassColorAttachmentDescriptor *const obj, uint32_t count = 1) {
            for (uint32_t i = 0; i < count; ++i) {
                if (!DeviceMatches(device, obj[i])) {
                    return false;
                }
            }
            return true;
        }
        DAWN_DECLARE_UNUSED bool DeviceMatches(const Device* device, const WGPURenderPipelineDescriptorDummyExtension& obj) {
            {
                if (!DeviceMatches(device, obj.dummyStage)) {
                    return false;
                }
            }
            return true;
        }

        DAWN_DECLARE_UNUSED bool DeviceMatches(const Device* device, const WGPURenderPipelineDescriptorDummyExtension *const obj, uint32_t count = 1) {
            for (uint32_t i = 0; i < count; ++i) {
                if (!DeviceMatches(device, obj[i])) {
                    return false;
                }
            }
            return true;
        }
        DAWN_DECLARE_UNUSED bool DeviceMatches(const Device* device, const WGPUTextureCopyView& obj) {
            if (!DeviceMatches(device, obj.nextInChain)) {
                return false;
            }
            {
                if (!DeviceMatches(device, obj.texture)) {
                    return false;
                }
            }
            return true;
        }

        DAWN_DECLARE_UNUSED bool DeviceMatches(const Device* device, const WGPUTextureCopyView *const obj, uint32_t count = 1) {
            for (uint32_t i = 0; i < count; ++i) {
                if (!DeviceMatches(device, obj[i])) {
                    return false;
                }
            }
            return true;
        }
        DAWN_DECLARE_UNUSED bool DeviceMatches(const Device* device, const WGPUTextureDescriptor& obj) {
            if (!DeviceMatches(device, obj.nextInChain)) {
                return false;
            }
            return true;
        }

        DAWN_DECLARE_UNUSED bool DeviceMatches(const Device* device, const WGPUTextureDescriptor *const obj, uint32_t count = 1) {
            for (uint32_t i = 0; i < count; ++i) {
                if (!DeviceMatches(device, obj[i])) {
                    return false;
                }
            }
            return true;
        }
        DAWN_DECLARE_UNUSED bool DeviceMatches(const Device* device, const WGPURenderPassDescriptor& obj) {
            if (!DeviceMatches(device, obj.nextInChain)) {
                return false;
            }
            {
                if (!DeviceMatches(device, obj.colorAttachments, obj.colorAttachmentCount)) {
                    return false;
                }
            }
            if (obj.depthStencilAttachment != nullptr)
            {
                if (!DeviceMatches(device, obj.depthStencilAttachment, 1)) {
                    return false;
                }
            }
            if (obj.occlusionQuerySet != nullptr)
            {
                if (!DeviceMatches(device, obj.occlusionQuerySet)) {
                    return false;
                }
            }
            return true;
        }

        DAWN_DECLARE_UNUSED bool DeviceMatches(const Device* device, const WGPURenderPassDescriptor *const obj, uint32_t count = 1) {
            for (uint32_t i = 0; i < count; ++i) {
                if (!DeviceMatches(device, obj[i])) {
                    return false;
                }
            }
            return true;
        }
        DAWN_DECLARE_UNUSED bool DeviceMatches(const Device* device, const WGPUVertexStateDescriptor& obj) {
            if (!DeviceMatches(device, obj.nextInChain)) {
                return false;
            }
            return true;
        }

        DAWN_DECLARE_UNUSED bool DeviceMatches(const Device* device, const WGPUVertexStateDescriptor *const obj, uint32_t count = 1) {
            for (uint32_t i = 0; i < count; ++i) {
                if (!DeviceMatches(device, obj[i])) {
                    return false;
                }
            }
            return true;
        }
        DAWN_DECLARE_UNUSED bool DeviceMatches(const Device* device, const WGPURenderPipelineDescriptor& obj) {
            if (!DeviceMatches(device, obj.nextInChain)) {
                return false;
            }
            if (obj.layout != nullptr)
            {
                if (!DeviceMatches(device, obj.layout)) {
                    return false;
                }
            }
            {
                if (!DeviceMatches(device, obj.vertexStage)) {
                    return false;
                }
            }
            if (obj.fragmentStage != nullptr)
            {
                if (!DeviceMatches(device, obj.fragmentStage, 1)) {
                    return false;
                }
            }
            if (obj.vertexState != nullptr)
            {
                if (!DeviceMatches(device, obj.vertexState, 1)) {
                    return false;
                }
            }
            if (obj.rasterizationState != nullptr)
            {
                if (!DeviceMatches(device, obj.rasterizationState, 1)) {
                    return false;
                }
            }
            if (obj.depthStencilState != nullptr)
            {
                if (!DeviceMatches(device, obj.depthStencilState, 1)) {
                    return false;
                }
            }
            {
                if (!DeviceMatches(device, obj.colorStates, obj.colorStateCount)) {
                    return false;
                }
            }
            return true;
        }

        DAWN_DECLARE_UNUSED bool DeviceMatches(const Device* device, const WGPURenderPipelineDescriptor *const obj, uint32_t count = 1) {
            for (uint32_t i = 0; i < count; ++i) {
                if (!DeviceMatches(device, obj[i])) {
                    return false;
                }
            }
            return true;
        }

        bool DeviceMatches(const Device* device, WGPUChainedStruct const* chainedStruct) {
            while (chainedStruct != nullptr) {
                switch (chainedStruct->sType) {
                    case WGPUSType_SurfaceDescriptorFromMetalLayer: {
                        if (!DeviceMatches(device, reinterpret_cast<const WGPUSurfaceDescriptorFromMetalLayer*>(chainedStruct))) {
                            return false;
                        }
                        break;
                    }
                    case WGPUSType_SurfaceDescriptorFromWindowsHWND: {
                        if (!DeviceMatches(device, reinterpret_cast<const WGPUSurfaceDescriptorFromWindowsHWND*>(chainedStruct))) {
                            return false;
                        }
                        break;
                    }
                    case WGPUSType_SurfaceDescriptorFromXlib: {
                        if (!DeviceMatches(device, reinterpret_cast<const WGPUSurfaceDescriptorFromXlib*>(chainedStruct))) {
                            return false;
                        }
                        break;
                    }
                    case WGPUSType_SurfaceDescriptorFromCanvasHTMLSelector: {
                        if (!DeviceMatches(device, reinterpret_cast<const WGPUSurfaceDescriptorFromCanvasHTMLSelector*>(chainedStruct))) {
                            return false;
                        }
                        break;
                    }
                    case WGPUSType_ShaderModuleSPIRVDescriptor: {
                        if (!DeviceMatches(device, reinterpret_cast<const WGPUShaderModuleSPIRVDescriptor*>(chainedStruct))) {
                            return false;
                        }
                        break;
                    }
                    case WGPUSType_ShaderModuleWGSLDescriptor: {
                        if (!DeviceMatches(device, reinterpret_cast<const WGPUShaderModuleWGSLDescriptor*>(chainedStruct))) {
                            return false;
                        }
                        break;
                    }
                    case WGPUSType_SamplerDescriptorDummyAnisotropicFiltering: {
                        if (!DeviceMatches(device, reinterpret_cast<const WGPUSamplerDescriptorDummyAnisotropicFiltering*>(chainedStruct))) {
                            return false;
                        }
                        break;
                    }
                    case WGPUSType_RenderPipelineDescriptorDummyExtension: {
                        if (!DeviceMatches(device, reinterpret_cast<const WGPURenderPipelineDescriptorDummyExtension*>(chainedStruct))) {
                            return false;
                        }
                        break;
                    }
                    case WGPUSType_Invalid:
                        break;
                    default:
                        UNREACHABLE();
                        dawn::WarningLog()
                            << "All objects may not be from the same device. "
                            << "Unknown sType " << chainedStruct->sType << " discarded.";
                        return false;
                }
                chainedStruct = chainedStruct->next;
            }
            return true;
        }

    }  // anonymous namespace



    void ClientBindGroupRelease(WGPUBindGroup cObj) {
        BindGroup* obj = reinterpret_cast<BindGroup*>(cObj);
        obj->refcount --;

        if (obj->refcount > 0) {
            return;
        }

        DestroyObjectCmd cmd;
        cmd.objectType = ObjectType::BindGroup;
        cmd.objectId = obj->id;

        obj->device->GetClient()->SerializeCommand(cmd);
        obj->device->GetClient()->BindGroupAllocator().Free(obj);
    }

    void ClientBindGroupReference(WGPUBindGroup cObj) {
        BindGroup* obj = reinterpret_cast<BindGroup*>(cObj);
        obj->refcount ++;
    }


    void ClientBindGroupLayoutRelease(WGPUBindGroupLayout cObj) {
        BindGroupLayout* obj = reinterpret_cast<BindGroupLayout*>(cObj);
        obj->refcount --;

        if (obj->refcount > 0) {
            return;
        }

        DestroyObjectCmd cmd;
        cmd.objectType = ObjectType::BindGroupLayout;
        cmd.objectId = obj->id;

        obj->device->GetClient()->SerializeCommand(cmd);
        obj->device->GetClient()->BindGroupLayoutAllocator().Free(obj);
    }

    void ClientBindGroupLayoutReference(WGPUBindGroupLayout cObj) {
        BindGroupLayout* obj = reinterpret_cast<BindGroupLayout*>(cObj);
        obj->refcount ++;
    }


    static
    void ClientBufferDestroy(WGPUBuffer cSelf) {

        auto self = reinterpret_cast<Buffer*>(cSelf);
        return self->Destroy();
    }

    static
    void const * ClientBufferGetConstMappedRange(WGPUBuffer cSelf, size_t offset, size_t size) {
        {
            bool sameDevice = true;
            auto self = reinterpret_cast<Buffer*>(cSelf);
            Device* device = self->device;
            DAWN_UNUSED(device);

            do {
            } while (false);

            if (DAWN_UNLIKELY(!sameDevice)) {
                device->InjectError(WGPUErrorType_Validation,
                                    "All objects must be from the same device.");
                return {};
            }
        }

        auto self = reinterpret_cast<Buffer*>(cSelf);
        return self->GetConstMappedRange( offset,  size);
    }

    static
    void * ClientBufferGetMappedRange(WGPUBuffer cSelf, size_t offset, size_t size) {
        {
            bool sameDevice = true;
            auto self = reinterpret_cast<Buffer*>(cSelf);
            Device* device = self->device;
            DAWN_UNUSED(device);

            do {
            } while (false);

            if (DAWN_UNLIKELY(!sameDevice)) {
                device->InjectError(WGPUErrorType_Validation,
                                    "All objects must be from the same device.");
                return {};
            }
        }

        auto self = reinterpret_cast<Buffer*>(cSelf);
        return self->GetMappedRange( offset,  size);
    }

    static
    void ClientBufferMapAsync(WGPUBuffer cSelf, WGPUMapModeFlags mode, size_t offset, size_t size, WGPUBufferMapCallback callback, void * userdata) {
        {
            bool sameDevice = true;
            auto self = reinterpret_cast<Buffer*>(cSelf);
            Device* device = self->device;
            DAWN_UNUSED(device);

            do {
            } while (false);

            if (DAWN_UNLIKELY(!sameDevice)) {
                device->InjectError(WGPUErrorType_Validation,
                                    "All objects must be from the same device.");
                return;
            }
        }

        auto self = reinterpret_cast<Buffer*>(cSelf);
        return self->MapAsync( mode,  offset,  size,  callback,  userdata);
    }

    static
    void ClientBufferUnmap(WGPUBuffer cSelf) {

        auto self = reinterpret_cast<Buffer*>(cSelf);
        return self->Unmap();
    }

    void ClientBufferRelease(WGPUBuffer cObj) {
        Buffer* obj = reinterpret_cast<Buffer*>(cObj);
        obj->refcount --;

        if (obj->refcount > 0) {
            return;
        }

        DestroyObjectCmd cmd;
        cmd.objectType = ObjectType::Buffer;
        cmd.objectId = obj->id;

        obj->device->GetClient()->SerializeCommand(cmd);
        obj->device->GetClient()->BufferAllocator().Free(obj);
    }

    void ClientBufferReference(WGPUBuffer cObj) {
        Buffer* obj = reinterpret_cast<Buffer*>(cObj);
        obj->refcount ++;
    }


    void ClientCommandBufferRelease(WGPUCommandBuffer cObj) {
        CommandBuffer* obj = reinterpret_cast<CommandBuffer*>(cObj);
        obj->refcount --;

        if (obj->refcount > 0) {
            return;
        }

        DestroyObjectCmd cmd;
        cmd.objectType = ObjectType::CommandBuffer;
        cmd.objectId = obj->id;

        obj->device->GetClient()->SerializeCommand(cmd);
        obj->device->GetClient()->CommandBufferAllocator().Free(obj);
    }

    void ClientCommandBufferReference(WGPUCommandBuffer cObj) {
        CommandBuffer* obj = reinterpret_cast<CommandBuffer*>(cObj);
        obj->refcount ++;
    }


    WGPUComputePassEncoder ClientCommandEncoderBeginComputePass(WGPUCommandEncoder cSelf, WGPUComputePassDescriptor const * descriptor) {
        {
            bool sameDevice = true;
            auto self = reinterpret_cast<CommandEncoder*>(cSelf);
            Device* device = self->device;
            DAWN_UNUSED(device);

            do {
                if (descriptor != nullptr)
                {
                    if (!DeviceMatches(device, descriptor, 1)) {
                        sameDevice = false;
                        break;
                    }
                }
            } while (false);

            if (DAWN_UNLIKELY(!sameDevice)) {
                device->InjectError(WGPUErrorType_Validation,
                                    "All objects must be from the same device.");
                // Allocate an object without registering it on the server. This is backed by a real allocation on
                // the client so commands can be sent with it. But because it's not allocated on the server, it will
                // be a fatal error to use it.
                auto self = reinterpret_cast<CommandEncoder*>(cSelf);
                auto* allocation = self->device->GetClient()->ComputePassEncoderAllocator().New(self->device);
                return reinterpret_cast<WGPUComputePassEncoder>(allocation->object.get());
            }
        }

        auto self = reinterpret_cast<CommandEncoder*>(cSelf);
        Device* device = self->device;
        CommandEncoderBeginComputePassCmd cmd;

        cmd.self = cSelf;

        auto* allocation = self->device->GetClient()->ComputePassEncoderAllocator().New(self->device);
        cmd.result = ObjectHandle{allocation->object->id, allocation->generation};

        cmd.descriptor = descriptor;

        device->GetClient()->SerializeCommand(cmd);

        return reinterpret_cast<WGPUComputePassEncoder>(allocation->object.get());
    }

    WGPURenderPassEncoder ClientCommandEncoderBeginRenderPass(WGPUCommandEncoder cSelf, WGPURenderPassDescriptor const * descriptor) {
        {
            bool sameDevice = true;
            auto self = reinterpret_cast<CommandEncoder*>(cSelf);
            Device* device = self->device;
            DAWN_UNUSED(device);

            do {
                {
                    if (!DeviceMatches(device, descriptor, 1)) {
                        sameDevice = false;
                        break;
                    }
                }
            } while (false);

            if (DAWN_UNLIKELY(!sameDevice)) {
                device->InjectError(WGPUErrorType_Validation,
                                    "All objects must be from the same device.");
                // Allocate an object without registering it on the server. This is backed by a real allocation on
                // the client so commands can be sent with it. But because it's not allocated on the server, it will
                // be a fatal error to use it.
                auto self = reinterpret_cast<CommandEncoder*>(cSelf);
                auto* allocation = self->device->GetClient()->RenderPassEncoderAllocator().New(self->device);
                return reinterpret_cast<WGPURenderPassEncoder>(allocation->object.get());
            }
        }

        auto self = reinterpret_cast<CommandEncoder*>(cSelf);
        Device* device = self->device;
        CommandEncoderBeginRenderPassCmd cmd;

        cmd.self = cSelf;

        auto* allocation = self->device->GetClient()->RenderPassEncoderAllocator().New(self->device);
        cmd.result = ObjectHandle{allocation->object->id, allocation->generation};

        cmd.descriptor = descriptor;

        device->GetClient()->SerializeCommand(cmd);

        return reinterpret_cast<WGPURenderPassEncoder>(allocation->object.get());
    }

    void ClientCommandEncoderCopyBufferToBuffer(WGPUCommandEncoder cSelf, WGPUBuffer source, uint64_t sourceOffset, WGPUBuffer destination, uint64_t destinationOffset, uint64_t size) {
        {
            bool sameDevice = true;
            auto self = reinterpret_cast<CommandEncoder*>(cSelf);
            Device* device = self->device;
            DAWN_UNUSED(device);

            do {
                {
                    if (!DeviceMatches(device, source)) {
                        sameDevice = false;
                        break;
                    }
                }
                {
                    if (!DeviceMatches(device, destination)) {
                        sameDevice = false;
                        break;
                    }
                }
            } while (false);

            if (DAWN_UNLIKELY(!sameDevice)) {
                device->InjectError(WGPUErrorType_Validation,
                                    "All objects must be from the same device.");
                return;
            }
        }

        auto self = reinterpret_cast<CommandEncoder*>(cSelf);
        Device* device = self->device;
        CommandEncoderCopyBufferToBufferCmd cmd;

        cmd.self = cSelf;


        cmd.source = source;
        cmd.sourceOffset = sourceOffset;
        cmd.destination = destination;
        cmd.destinationOffset = destinationOffset;
        cmd.size = size;

        device->GetClient()->SerializeCommand(cmd);

    }

    void ClientCommandEncoderCopyBufferToTexture(WGPUCommandEncoder cSelf, WGPUBufferCopyView const * source, WGPUTextureCopyView const * destination, WGPUExtent3D const * copySize) {
        {
            bool sameDevice = true;
            auto self = reinterpret_cast<CommandEncoder*>(cSelf);
            Device* device = self->device;
            DAWN_UNUSED(device);

            do {
                {
                    if (!DeviceMatches(device, source, 1)) {
                        sameDevice = false;
                        break;
                    }
                }
                {
                    if (!DeviceMatches(device, destination, 1)) {
                        sameDevice = false;
                        break;
                    }
                }
            } while (false);

            if (DAWN_UNLIKELY(!sameDevice)) {
                device->InjectError(WGPUErrorType_Validation,
                                    "All objects must be from the same device.");
                return;
            }
        }

        auto self = reinterpret_cast<CommandEncoder*>(cSelf);
        Device* device = self->device;
        CommandEncoderCopyBufferToTextureCmd cmd;

        cmd.self = cSelf;


        cmd.source = source;
        cmd.destination = destination;
        cmd.copySize = copySize;

        device->GetClient()->SerializeCommand(cmd);

    }

    void ClientCommandEncoderCopyTextureToBuffer(WGPUCommandEncoder cSelf, WGPUTextureCopyView const * source, WGPUBufferCopyView const * destination, WGPUExtent3D const * copySize) {
        {
            bool sameDevice = true;
            auto self = reinterpret_cast<CommandEncoder*>(cSelf);
            Device* device = self->device;
            DAWN_UNUSED(device);

            do {
                {
                    if (!DeviceMatches(device, source, 1)) {
                        sameDevice = false;
                        break;
                    }
                }
                {
                    if (!DeviceMatches(device, destination, 1)) {
                        sameDevice = false;
                        break;
                    }
                }
            } while (false);

            if (DAWN_UNLIKELY(!sameDevice)) {
                device->InjectError(WGPUErrorType_Validation,
                                    "All objects must be from the same device.");
                return;
            }
        }

        auto self = reinterpret_cast<CommandEncoder*>(cSelf);
        Device* device = self->device;
        CommandEncoderCopyTextureToBufferCmd cmd;

        cmd.self = cSelf;


        cmd.source = source;
        cmd.destination = destination;
        cmd.copySize = copySize;

        device->GetClient()->SerializeCommand(cmd);

    }

    void ClientCommandEncoderCopyTextureToTexture(WGPUCommandEncoder cSelf, WGPUTextureCopyView const * source, WGPUTextureCopyView const * destination, WGPUExtent3D const * copySize) {
        {
            bool sameDevice = true;
            auto self = reinterpret_cast<CommandEncoder*>(cSelf);
            Device* device = self->device;
            DAWN_UNUSED(device);

            do {
                {
                    if (!DeviceMatches(device, source, 1)) {
                        sameDevice = false;
                        break;
                    }
                }
                {
                    if (!DeviceMatches(device, destination, 1)) {
                        sameDevice = false;
                        break;
                    }
                }
            } while (false);

            if (DAWN_UNLIKELY(!sameDevice)) {
                device->InjectError(WGPUErrorType_Validation,
                                    "All objects must be from the same device.");
                return;
            }
        }

        auto self = reinterpret_cast<CommandEncoder*>(cSelf);
        Device* device = self->device;
        CommandEncoderCopyTextureToTextureCmd cmd;

        cmd.self = cSelf;


        cmd.source = source;
        cmd.destination = destination;
        cmd.copySize = copySize;

        device->GetClient()->SerializeCommand(cmd);

    }

    WGPUCommandBuffer ClientCommandEncoderFinish(WGPUCommandEncoder cSelf, WGPUCommandBufferDescriptor const * descriptor) {
        {
            bool sameDevice = true;
            auto self = reinterpret_cast<CommandEncoder*>(cSelf);
            Device* device = self->device;
            DAWN_UNUSED(device);

            do {
                if (descriptor != nullptr)
                {
                    if (!DeviceMatches(device, descriptor, 1)) {
                        sameDevice = false;
                        break;
                    }
                }
            } while (false);

            if (DAWN_UNLIKELY(!sameDevice)) {
                device->InjectError(WGPUErrorType_Validation,
                                    "All objects must be from the same device.");
                // Allocate an object without registering it on the server. This is backed by a real allocation on
                // the client so commands can be sent with it. But because it's not allocated on the server, it will
                // be a fatal error to use it.
                auto self = reinterpret_cast<CommandEncoder*>(cSelf);
                auto* allocation = self->device->GetClient()->CommandBufferAllocator().New(self->device);
                return reinterpret_cast<WGPUCommandBuffer>(allocation->object.get());
            }
        }

        auto self = reinterpret_cast<CommandEncoder*>(cSelf);
        Device* device = self->device;
        CommandEncoderFinishCmd cmd;

        cmd.self = cSelf;

        auto* allocation = self->device->GetClient()->CommandBufferAllocator().New(self->device);
        cmd.result = ObjectHandle{allocation->object->id, allocation->generation};

        cmd.descriptor = descriptor;

        device->GetClient()->SerializeCommand(cmd);

        return reinterpret_cast<WGPUCommandBuffer>(allocation->object.get());
    }

    void ClientCommandEncoderInsertDebugMarker(WGPUCommandEncoder cSelf, char const * markerLabel) {
        {
            bool sameDevice = true;
            auto self = reinterpret_cast<CommandEncoder*>(cSelf);
            Device* device = self->device;
            DAWN_UNUSED(device);

            do {
            } while (false);

            if (DAWN_UNLIKELY(!sameDevice)) {
                device->InjectError(WGPUErrorType_Validation,
                                    "All objects must be from the same device.");
                return;
            }
        }

        auto self = reinterpret_cast<CommandEncoder*>(cSelf);
        Device* device = self->device;
        CommandEncoderInsertDebugMarkerCmd cmd;

        cmd.self = cSelf;


        cmd.markerLabel = markerLabel;

        device->GetClient()->SerializeCommand(cmd);

    }

    void ClientCommandEncoderPopDebugGroup(WGPUCommandEncoder cSelf) {

        auto self = reinterpret_cast<CommandEncoder*>(cSelf);
        Device* device = self->device;
        CommandEncoderPopDebugGroupCmd cmd;

        cmd.self = cSelf;



        device->GetClient()->SerializeCommand(cmd);

    }

    void ClientCommandEncoderPushDebugGroup(WGPUCommandEncoder cSelf, char const * groupLabel) {
        {
            bool sameDevice = true;
            auto self = reinterpret_cast<CommandEncoder*>(cSelf);
            Device* device = self->device;
            DAWN_UNUSED(device);

            do {
            } while (false);

            if (DAWN_UNLIKELY(!sameDevice)) {
                device->InjectError(WGPUErrorType_Validation,
                                    "All objects must be from the same device.");
                return;
            }
        }

        auto self = reinterpret_cast<CommandEncoder*>(cSelf);
        Device* device = self->device;
        CommandEncoderPushDebugGroupCmd cmd;

        cmd.self = cSelf;


        cmd.groupLabel = groupLabel;

        device->GetClient()->SerializeCommand(cmd);

    }

    void ClientCommandEncoderResolveQuerySet(WGPUCommandEncoder cSelf, WGPUQuerySet querySet, uint32_t firstQuery, uint32_t queryCount, WGPUBuffer destination, uint64_t destinationOffset) {
        {
            bool sameDevice = true;
            auto self = reinterpret_cast<CommandEncoder*>(cSelf);
            Device* device = self->device;
            DAWN_UNUSED(device);

            do {
                {
                    if (!DeviceMatches(device, querySet)) {
                        sameDevice = false;
                        break;
                    }
                }
                {
                    if (!DeviceMatches(device, destination)) {
                        sameDevice = false;
                        break;
                    }
                }
            } while (false);

            if (DAWN_UNLIKELY(!sameDevice)) {
                device->InjectError(WGPUErrorType_Validation,
                                    "All objects must be from the same device.");
                return;
            }
        }

        auto self = reinterpret_cast<CommandEncoder*>(cSelf);
        Device* device = self->device;
        CommandEncoderResolveQuerySetCmd cmd;

        cmd.self = cSelf;


        cmd.querySet = querySet;
        cmd.firstQuery = firstQuery;
        cmd.queryCount = queryCount;
        cmd.destination = destination;
        cmd.destinationOffset = destinationOffset;

        device->GetClient()->SerializeCommand(cmd);

    }

    void ClientCommandEncoderWriteTimestamp(WGPUCommandEncoder cSelf, WGPUQuerySet querySet, uint32_t queryIndex) {
        {
            bool sameDevice = true;
            auto self = reinterpret_cast<CommandEncoder*>(cSelf);
            Device* device = self->device;
            DAWN_UNUSED(device);

            do {
                {
                    if (!DeviceMatches(device, querySet)) {
                        sameDevice = false;
                        break;
                    }
                }
            } while (false);

            if (DAWN_UNLIKELY(!sameDevice)) {
                device->InjectError(WGPUErrorType_Validation,
                                    "All objects must be from the same device.");
                return;
            }
        }

        auto self = reinterpret_cast<CommandEncoder*>(cSelf);
        Device* device = self->device;
        CommandEncoderWriteTimestampCmd cmd;

        cmd.self = cSelf;


        cmd.querySet = querySet;
        cmd.queryIndex = queryIndex;

        device->GetClient()->SerializeCommand(cmd);

    }

    void ClientCommandEncoderRelease(WGPUCommandEncoder cObj) {
        CommandEncoder* obj = reinterpret_cast<CommandEncoder*>(cObj);
        obj->refcount --;

        if (obj->refcount > 0) {
            return;
        }

        DestroyObjectCmd cmd;
        cmd.objectType = ObjectType::CommandEncoder;
        cmd.objectId = obj->id;

        obj->device->GetClient()->SerializeCommand(cmd);
        obj->device->GetClient()->CommandEncoderAllocator().Free(obj);
    }

    void ClientCommandEncoderReference(WGPUCommandEncoder cObj) {
        CommandEncoder* obj = reinterpret_cast<CommandEncoder*>(cObj);
        obj->refcount ++;
    }


    void ClientComputePassEncoderDispatch(WGPUComputePassEncoder cSelf, uint32_t x, uint32_t y, uint32_t z) {
        {
            bool sameDevice = true;
            auto self = reinterpret_cast<ComputePassEncoder*>(cSelf);
            Device* device = self->device;
            DAWN_UNUSED(device);

            do {
            } while (false);

            if (DAWN_UNLIKELY(!sameDevice)) {
                device->InjectError(WGPUErrorType_Validation,
                                    "All objects must be from the same device.");
                return;
            }
        }

        auto self = reinterpret_cast<ComputePassEncoder*>(cSelf);
        Device* device = self->device;
        ComputePassEncoderDispatchCmd cmd;

        cmd.self = cSelf;


        cmd.x = x;
        cmd.y = y;
        cmd.z = z;

        device->GetClient()->SerializeCommand(cmd);

    }

    void ClientComputePassEncoderDispatchIndirect(WGPUComputePassEncoder cSelf, WGPUBuffer indirectBuffer, uint64_t indirectOffset) {
        {
            bool sameDevice = true;
            auto self = reinterpret_cast<ComputePassEncoder*>(cSelf);
            Device* device = self->device;
            DAWN_UNUSED(device);

            do {
                {
                    if (!DeviceMatches(device, indirectBuffer)) {
                        sameDevice = false;
                        break;
                    }
                }
            } while (false);

            if (DAWN_UNLIKELY(!sameDevice)) {
                device->InjectError(WGPUErrorType_Validation,
                                    "All objects must be from the same device.");
                return;
            }
        }

        auto self = reinterpret_cast<ComputePassEncoder*>(cSelf);
        Device* device = self->device;
        ComputePassEncoderDispatchIndirectCmd cmd;

        cmd.self = cSelf;


        cmd.indirectBuffer = indirectBuffer;
        cmd.indirectOffset = indirectOffset;

        device->GetClient()->SerializeCommand(cmd);

    }

    void ClientComputePassEncoderEndPass(WGPUComputePassEncoder cSelf) {

        auto self = reinterpret_cast<ComputePassEncoder*>(cSelf);
        Device* device = self->device;
        ComputePassEncoderEndPassCmd cmd;

        cmd.self = cSelf;



        device->GetClient()->SerializeCommand(cmd);

    }

    void ClientComputePassEncoderInsertDebugMarker(WGPUComputePassEncoder cSelf, char const * markerLabel) {
        {
            bool sameDevice = true;
            auto self = reinterpret_cast<ComputePassEncoder*>(cSelf);
            Device* device = self->device;
            DAWN_UNUSED(device);

            do {
            } while (false);

            if (DAWN_UNLIKELY(!sameDevice)) {
                device->InjectError(WGPUErrorType_Validation,
                                    "All objects must be from the same device.");
                return;
            }
        }

        auto self = reinterpret_cast<ComputePassEncoder*>(cSelf);
        Device* device = self->device;
        ComputePassEncoderInsertDebugMarkerCmd cmd;

        cmd.self = cSelf;


        cmd.markerLabel = markerLabel;

        device->GetClient()->SerializeCommand(cmd);

    }

    void ClientComputePassEncoderPopDebugGroup(WGPUComputePassEncoder cSelf) {

        auto self = reinterpret_cast<ComputePassEncoder*>(cSelf);
        Device* device = self->device;
        ComputePassEncoderPopDebugGroupCmd cmd;

        cmd.self = cSelf;



        device->GetClient()->SerializeCommand(cmd);

    }

    void ClientComputePassEncoderPushDebugGroup(WGPUComputePassEncoder cSelf, char const * groupLabel) {
        {
            bool sameDevice = true;
            auto self = reinterpret_cast<ComputePassEncoder*>(cSelf);
            Device* device = self->device;
            DAWN_UNUSED(device);

            do {
            } while (false);

            if (DAWN_UNLIKELY(!sameDevice)) {
                device->InjectError(WGPUErrorType_Validation,
                                    "All objects must be from the same device.");
                return;
            }
        }

        auto self = reinterpret_cast<ComputePassEncoder*>(cSelf);
        Device* device = self->device;
        ComputePassEncoderPushDebugGroupCmd cmd;

        cmd.self = cSelf;


        cmd.groupLabel = groupLabel;

        device->GetClient()->SerializeCommand(cmd);

    }

    void ClientComputePassEncoderSetBindGroup(WGPUComputePassEncoder cSelf, uint32_t groupIndex, WGPUBindGroup group, uint32_t dynamicOffsetCount, uint32_t const * dynamicOffsets) {
        {
            bool sameDevice = true;
            auto self = reinterpret_cast<ComputePassEncoder*>(cSelf);
            Device* device = self->device;
            DAWN_UNUSED(device);

            do {
                {
                    if (!DeviceMatches(device, group)) {
                        sameDevice = false;
                        break;
                    }
                }
            } while (false);

            if (DAWN_UNLIKELY(!sameDevice)) {
                device->InjectError(WGPUErrorType_Validation,
                                    "All objects must be from the same device.");
                return;
            }
        }

        auto self = reinterpret_cast<ComputePassEncoder*>(cSelf);
        Device* device = self->device;
        ComputePassEncoderSetBindGroupCmd cmd;

        cmd.self = cSelf;


        cmd.groupIndex = groupIndex;
        cmd.group = group;
        cmd.dynamicOffsetCount = dynamicOffsetCount;
        cmd.dynamicOffsets = dynamicOffsets;

        device->GetClient()->SerializeCommand(cmd);

    }

    void ClientComputePassEncoderSetPipeline(WGPUComputePassEncoder cSelf, WGPUComputePipeline pipeline) {
        {
            bool sameDevice = true;
            auto self = reinterpret_cast<ComputePassEncoder*>(cSelf);
            Device* device = self->device;
            DAWN_UNUSED(device);

            do {
                {
                    if (!DeviceMatches(device, pipeline)) {
                        sameDevice = false;
                        break;
                    }
                }
            } while (false);

            if (DAWN_UNLIKELY(!sameDevice)) {
                device->InjectError(WGPUErrorType_Validation,
                                    "All objects must be from the same device.");
                return;
            }
        }

        auto self = reinterpret_cast<ComputePassEncoder*>(cSelf);
        Device* device = self->device;
        ComputePassEncoderSetPipelineCmd cmd;

        cmd.self = cSelf;


        cmd.pipeline = pipeline;

        device->GetClient()->SerializeCommand(cmd);

    }

    void ClientComputePassEncoderWriteTimestamp(WGPUComputePassEncoder cSelf, WGPUQuerySet querySet, uint32_t queryIndex) {
        {
            bool sameDevice = true;
            auto self = reinterpret_cast<ComputePassEncoder*>(cSelf);
            Device* device = self->device;
            DAWN_UNUSED(device);

            do {
                {
                    if (!DeviceMatches(device, querySet)) {
                        sameDevice = false;
                        break;
                    }
                }
            } while (false);

            if (DAWN_UNLIKELY(!sameDevice)) {
                device->InjectError(WGPUErrorType_Validation,
                                    "All objects must be from the same device.");
                return;
            }
        }

        auto self = reinterpret_cast<ComputePassEncoder*>(cSelf);
        Device* device = self->device;
        ComputePassEncoderWriteTimestampCmd cmd;

        cmd.self = cSelf;


        cmd.querySet = querySet;
        cmd.queryIndex = queryIndex;

        device->GetClient()->SerializeCommand(cmd);

    }

    void ClientComputePassEncoderRelease(WGPUComputePassEncoder cObj) {
        ComputePassEncoder* obj = reinterpret_cast<ComputePassEncoder*>(cObj);
        obj->refcount --;

        if (obj->refcount > 0) {
            return;
        }

        DestroyObjectCmd cmd;
        cmd.objectType = ObjectType::ComputePassEncoder;
        cmd.objectId = obj->id;

        obj->device->GetClient()->SerializeCommand(cmd);
        obj->device->GetClient()->ComputePassEncoderAllocator().Free(obj);
    }

    void ClientComputePassEncoderReference(WGPUComputePassEncoder cObj) {
        ComputePassEncoder* obj = reinterpret_cast<ComputePassEncoder*>(cObj);
        obj->refcount ++;
    }


    WGPUBindGroupLayout ClientComputePipelineGetBindGroupLayout(WGPUComputePipeline cSelf, uint32_t groupIndex) {
        {
            bool sameDevice = true;
            auto self = reinterpret_cast<ComputePipeline*>(cSelf);
            Device* device = self->device;
            DAWN_UNUSED(device);

            do {
            } while (false);

            if (DAWN_UNLIKELY(!sameDevice)) {
                device->InjectError(WGPUErrorType_Validation,
                                    "All objects must be from the same device.");
                // Allocate an object without registering it on the server. This is backed by a real allocation on
                // the client so commands can be sent with it. But because it's not allocated on the server, it will
                // be a fatal error to use it.
                auto self = reinterpret_cast<ComputePipeline*>(cSelf);
                auto* allocation = self->device->GetClient()->BindGroupLayoutAllocator().New(self->device);
                return reinterpret_cast<WGPUBindGroupLayout>(allocation->object.get());
            }
        }

        auto self = reinterpret_cast<ComputePipeline*>(cSelf);
        Device* device = self->device;
        ComputePipelineGetBindGroupLayoutCmd cmd;

        cmd.self = cSelf;

        auto* allocation = self->device->GetClient()->BindGroupLayoutAllocator().New(self->device);
        cmd.result = ObjectHandle{allocation->object->id, allocation->generation};

        cmd.groupIndex = groupIndex;

        device->GetClient()->SerializeCommand(cmd);

        return reinterpret_cast<WGPUBindGroupLayout>(allocation->object.get());
    }

    void ClientComputePipelineRelease(WGPUComputePipeline cObj) {
        ComputePipeline* obj = reinterpret_cast<ComputePipeline*>(cObj);
        obj->refcount --;

        if (obj->refcount > 0) {
            return;
        }

        DestroyObjectCmd cmd;
        cmd.objectType = ObjectType::ComputePipeline;
        cmd.objectId = obj->id;

        obj->device->GetClient()->SerializeCommand(cmd);
        obj->device->GetClient()->ComputePipelineAllocator().Free(obj);
    }

    void ClientComputePipelineReference(WGPUComputePipeline cObj) {
        ComputePipeline* obj = reinterpret_cast<ComputePipeline*>(cObj);
        obj->refcount ++;
    }


    WGPUBindGroup ClientDeviceCreateBindGroup(WGPUDevice cSelf, WGPUBindGroupDescriptor const * descriptor) {
        {
            bool sameDevice = true;
            auto self = reinterpret_cast<Device*>(cSelf);
            Device* device = self->device;
            DAWN_UNUSED(device);

            do {
                {
                    if (!DeviceMatches(device, descriptor, 1)) {
                        sameDevice = false;
                        break;
                    }
                }
            } while (false);

            if (DAWN_UNLIKELY(!sameDevice)) {
                device->InjectError(WGPUErrorType_Validation,
                                    "All objects must be from the same device.");
                // Allocate an object without registering it on the server. This is backed by a real allocation on
                // the client so commands can be sent with it. But because it's not allocated on the server, it will
                // be a fatal error to use it.
                auto self = reinterpret_cast<Device*>(cSelf);
                auto* allocation = self->device->GetClient()->BindGroupAllocator().New(self->device);
                return reinterpret_cast<WGPUBindGroup>(allocation->object.get());
            }
        }

        auto self = reinterpret_cast<Device*>(cSelf);
        Device* device = self->device;
        DeviceCreateBindGroupCmd cmd;

        cmd.self = cSelf;

        auto* allocation = self->device->GetClient()->BindGroupAllocator().New(self->device);
        cmd.result = ObjectHandle{allocation->object->id, allocation->generation};

        cmd.descriptor = descriptor;

        device->GetClient()->SerializeCommand(cmd);

        return reinterpret_cast<WGPUBindGroup>(allocation->object.get());
    }

    WGPUBindGroupLayout ClientDeviceCreateBindGroupLayout(WGPUDevice cSelf, WGPUBindGroupLayoutDescriptor const * descriptor) {
        {
            bool sameDevice = true;
            auto self = reinterpret_cast<Device*>(cSelf);
            Device* device = self->device;
            DAWN_UNUSED(device);

            do {
                {
                    if (!DeviceMatches(device, descriptor, 1)) {
                        sameDevice = false;
                        break;
                    }
                }
            } while (false);

            if (DAWN_UNLIKELY(!sameDevice)) {
                device->InjectError(WGPUErrorType_Validation,
                                    "All objects must be from the same device.");
                // Allocate an object without registering it on the server. This is backed by a real allocation on
                // the client so commands can be sent with it. But because it's not allocated on the server, it will
                // be a fatal error to use it.
                auto self = reinterpret_cast<Device*>(cSelf);
                auto* allocation = self->device->GetClient()->BindGroupLayoutAllocator().New(self->device);
                return reinterpret_cast<WGPUBindGroupLayout>(allocation->object.get());
            }
        }

        auto self = reinterpret_cast<Device*>(cSelf);
        Device* device = self->device;
        DeviceCreateBindGroupLayoutCmd cmd;

        cmd.self = cSelf;

        auto* allocation = self->device->GetClient()->BindGroupLayoutAllocator().New(self->device);
        cmd.result = ObjectHandle{allocation->object->id, allocation->generation};

        cmd.descriptor = descriptor;

        device->GetClient()->SerializeCommand(cmd);

        return reinterpret_cast<WGPUBindGroupLayout>(allocation->object.get());
    }

    static
    WGPUBuffer ClientDeviceCreateBuffer(WGPUDevice cSelf, WGPUBufferDescriptor const * descriptor) {
        {
            bool sameDevice = true;
            auto self = reinterpret_cast<Device*>(cSelf);
            Device* device = self->device;
            DAWN_UNUSED(device);

            do {
                {
                    if (!DeviceMatches(device, descriptor, 1)) {
                        sameDevice = false;
                        break;
                    }
                }
            } while (false);

            if (DAWN_UNLIKELY(!sameDevice)) {
                device->InjectError(WGPUErrorType_Validation,
                                    "All objects must be from the same device.");
                // Allocate an object without registering it on the server. This is backed by a real allocation on
                // the client so commands can be sent with it. But because it's not allocated on the server, it will
                // be a fatal error to use it.
                auto self = reinterpret_cast<Device*>(cSelf);
                auto* allocation = self->device->GetClient()->BufferAllocator().New(self->device);
                return reinterpret_cast<WGPUBuffer>(allocation->object.get());
            }
        }

        auto self = reinterpret_cast<Device*>(cSelf);
        return self->CreateBuffer( descriptor);
    }

    WGPUCommandEncoder ClientDeviceCreateCommandEncoder(WGPUDevice cSelf, WGPUCommandEncoderDescriptor const * descriptor) {
        {
            bool sameDevice = true;
            auto self = reinterpret_cast<Device*>(cSelf);
            Device* device = self->device;
            DAWN_UNUSED(device);

            do {
                if (descriptor != nullptr)
                {
                    if (!DeviceMatches(device, descriptor, 1)) {
                        sameDevice = false;
                        break;
                    }
                }
            } while (false);

            if (DAWN_UNLIKELY(!sameDevice)) {
                device->InjectError(WGPUErrorType_Validation,
                                    "All objects must be from the same device.");
                // Allocate an object without registering it on the server. This is backed by a real allocation on
                // the client so commands can be sent with it. But because it's not allocated on the server, it will
                // be a fatal error to use it.
                auto self = reinterpret_cast<Device*>(cSelf);
                auto* allocation = self->device->GetClient()->CommandEncoderAllocator().New(self->device);
                return reinterpret_cast<WGPUCommandEncoder>(allocation->object.get());
            }
        }

        auto self = reinterpret_cast<Device*>(cSelf);
        Device* device = self->device;
        DeviceCreateCommandEncoderCmd cmd;

        cmd.self = cSelf;

        auto* allocation = self->device->GetClient()->CommandEncoderAllocator().New(self->device);
        cmd.result = ObjectHandle{allocation->object->id, allocation->generation};

        cmd.descriptor = descriptor;

        device->GetClient()->SerializeCommand(cmd);

        return reinterpret_cast<WGPUCommandEncoder>(allocation->object.get());
    }

    WGPUComputePipeline ClientDeviceCreateComputePipeline(WGPUDevice cSelf, WGPUComputePipelineDescriptor const * descriptor) {
        {
            bool sameDevice = true;
            auto self = reinterpret_cast<Device*>(cSelf);
            Device* device = self->device;
            DAWN_UNUSED(device);

            do {
                {
                    if (!DeviceMatches(device, descriptor, 1)) {
                        sameDevice = false;
                        break;
                    }
                }
            } while (false);

            if (DAWN_UNLIKELY(!sameDevice)) {
                device->InjectError(WGPUErrorType_Validation,
                                    "All objects must be from the same device.");
                // Allocate an object without registering it on the server. This is backed by a real allocation on
                // the client so commands can be sent with it. But because it's not allocated on the server, it will
                // be a fatal error to use it.
                auto self = reinterpret_cast<Device*>(cSelf);
                auto* allocation = self->device->GetClient()->ComputePipelineAllocator().New(self->device);
                return reinterpret_cast<WGPUComputePipeline>(allocation->object.get());
            }
        }

        auto self = reinterpret_cast<Device*>(cSelf);
        Device* device = self->device;
        DeviceCreateComputePipelineCmd cmd;

        cmd.self = cSelf;

        auto* allocation = self->device->GetClient()->ComputePipelineAllocator().New(self->device);
        cmd.result = ObjectHandle{allocation->object->id, allocation->generation};

        cmd.descriptor = descriptor;

        device->GetClient()->SerializeCommand(cmd);

        return reinterpret_cast<WGPUComputePipeline>(allocation->object.get());
    }

    static
    WGPUBuffer ClientDeviceCreateErrorBuffer(WGPUDevice cSelf) {

        auto self = reinterpret_cast<Device*>(cSelf);
        return self->CreateErrorBuffer();
    }

    WGPUPipelineLayout ClientDeviceCreatePipelineLayout(WGPUDevice cSelf, WGPUPipelineLayoutDescriptor const * descriptor) {
        {
            bool sameDevice = true;
            auto self = reinterpret_cast<Device*>(cSelf);
            Device* device = self->device;
            DAWN_UNUSED(device);

            do {
                {
                    if (!DeviceMatches(device, descriptor, 1)) {
                        sameDevice = false;
                        break;
                    }
                }
            } while (false);

            if (DAWN_UNLIKELY(!sameDevice)) {
                device->InjectError(WGPUErrorType_Validation,
                                    "All objects must be from the same device.");
                // Allocate an object without registering it on the server. This is backed by a real allocation on
                // the client so commands can be sent with it. But because it's not allocated on the server, it will
                // be a fatal error to use it.
                auto self = reinterpret_cast<Device*>(cSelf);
                auto* allocation = self->device->GetClient()->PipelineLayoutAllocator().New(self->device);
                return reinterpret_cast<WGPUPipelineLayout>(allocation->object.get());
            }
        }

        auto self = reinterpret_cast<Device*>(cSelf);
        Device* device = self->device;
        DeviceCreatePipelineLayoutCmd cmd;

        cmd.self = cSelf;

        auto* allocation = self->device->GetClient()->PipelineLayoutAllocator().New(self->device);
        cmd.result = ObjectHandle{allocation->object->id, allocation->generation};

        cmd.descriptor = descriptor;

        device->GetClient()->SerializeCommand(cmd);

        return reinterpret_cast<WGPUPipelineLayout>(allocation->object.get());
    }

    WGPUQuerySet ClientDeviceCreateQuerySet(WGPUDevice cSelf, WGPUQuerySetDescriptor const * descriptor) {
        {
            bool sameDevice = true;
            auto self = reinterpret_cast<Device*>(cSelf);
            Device* device = self->device;
            DAWN_UNUSED(device);

            do {
                {
                    if (!DeviceMatches(device, descriptor, 1)) {
                        sameDevice = false;
                        break;
                    }
                }
            } while (false);

            if (DAWN_UNLIKELY(!sameDevice)) {
                device->InjectError(WGPUErrorType_Validation,
                                    "All objects must be from the same device.");
                // Allocate an object without registering it on the server. This is backed by a real allocation on
                // the client so commands can be sent with it. But because it's not allocated on the server, it will
                // be a fatal error to use it.
                auto self = reinterpret_cast<Device*>(cSelf);
                auto* allocation = self->device->GetClient()->QuerySetAllocator().New(self->device);
                return reinterpret_cast<WGPUQuerySet>(allocation->object.get());
            }
        }

        auto self = reinterpret_cast<Device*>(cSelf);
        Device* device = self->device;
        DeviceCreateQuerySetCmd cmd;

        cmd.self = cSelf;

        auto* allocation = self->device->GetClient()->QuerySetAllocator().New(self->device);
        cmd.result = ObjectHandle{allocation->object->id, allocation->generation};

        cmd.descriptor = descriptor;

        device->GetClient()->SerializeCommand(cmd);

        return reinterpret_cast<WGPUQuerySet>(allocation->object.get());
    }

    static
    void ClientDeviceCreateReadyComputePipeline(WGPUDevice cSelf, WGPUComputePipelineDescriptor const * descriptor, WGPUCreateReadyComputePipelineCallback callback, void * userdata) {
        {
            bool sameDevice = true;
            auto self = reinterpret_cast<Device*>(cSelf);
            Device* device = self->device;
            DAWN_UNUSED(device);

            do {
                {
                    if (!DeviceMatches(device, descriptor, 1)) {
                        sameDevice = false;
                        break;
                    }
                }
            } while (false);

            if (DAWN_UNLIKELY(!sameDevice)) {
                device->InjectError(WGPUErrorType_Validation,
                                    "All objects must be from the same device.");
                return;
            }
        }

        auto self = reinterpret_cast<Device*>(cSelf);
        return self->CreateReadyComputePipeline( descriptor,  callback,  userdata);
    }

    static
    void ClientDeviceCreateReadyRenderPipeline(WGPUDevice cSelf, WGPURenderPipelineDescriptor const * descriptor, WGPUCreateReadyRenderPipelineCallback callback, void * userdata) {
        {
            bool sameDevice = true;
            auto self = reinterpret_cast<Device*>(cSelf);
            Device* device = self->device;
            DAWN_UNUSED(device);

            do {
                {
                    if (!DeviceMatches(device, descriptor, 1)) {
                        sameDevice = false;
                        break;
                    }
                }
            } while (false);

            if (DAWN_UNLIKELY(!sameDevice)) {
                device->InjectError(WGPUErrorType_Validation,
                                    "All objects must be from the same device.");
                return;
            }
        }

        auto self = reinterpret_cast<Device*>(cSelf);
        return self->CreateReadyRenderPipeline( descriptor,  callback,  userdata);
    }

    WGPURenderBundleEncoder ClientDeviceCreateRenderBundleEncoder(WGPUDevice cSelf, WGPURenderBundleEncoderDescriptor const * descriptor) {
        {
            bool sameDevice = true;
            auto self = reinterpret_cast<Device*>(cSelf);
            Device* device = self->device;
            DAWN_UNUSED(device);

            do {
                {
                    if (!DeviceMatches(device, descriptor, 1)) {
                        sameDevice = false;
                        break;
                    }
                }
            } while (false);

            if (DAWN_UNLIKELY(!sameDevice)) {
                device->InjectError(WGPUErrorType_Validation,
                                    "All objects must be from the same device.");
                // Allocate an object without registering it on the server. This is backed by a real allocation on
                // the client so commands can be sent with it. But because it's not allocated on the server, it will
                // be a fatal error to use it.
                auto self = reinterpret_cast<Device*>(cSelf);
                auto* allocation = self->device->GetClient()->RenderBundleEncoderAllocator().New(self->device);
                return reinterpret_cast<WGPURenderBundleEncoder>(allocation->object.get());
            }
        }

        auto self = reinterpret_cast<Device*>(cSelf);
        Device* device = self->device;
        DeviceCreateRenderBundleEncoderCmd cmd;

        cmd.self = cSelf;

        auto* allocation = self->device->GetClient()->RenderBundleEncoderAllocator().New(self->device);
        cmd.result = ObjectHandle{allocation->object->id, allocation->generation};

        cmd.descriptor = descriptor;

        device->GetClient()->SerializeCommand(cmd);

        return reinterpret_cast<WGPURenderBundleEncoder>(allocation->object.get());
    }

    WGPURenderPipeline ClientDeviceCreateRenderPipeline(WGPUDevice cSelf, WGPURenderPipelineDescriptor const * descriptor) {
        {
            bool sameDevice = true;
            auto self = reinterpret_cast<Device*>(cSelf);
            Device* device = self->device;
            DAWN_UNUSED(device);

            do {
                {
                    if (!DeviceMatches(device, descriptor, 1)) {
                        sameDevice = false;
                        break;
                    }
                }
            } while (false);

            if (DAWN_UNLIKELY(!sameDevice)) {
                device->InjectError(WGPUErrorType_Validation,
                                    "All objects must be from the same device.");
                // Allocate an object without registering it on the server. This is backed by a real allocation on
                // the client so commands can be sent with it. But because it's not allocated on the server, it will
                // be a fatal error to use it.
                auto self = reinterpret_cast<Device*>(cSelf);
                auto* allocation = self->device->GetClient()->RenderPipelineAllocator().New(self->device);
                return reinterpret_cast<WGPURenderPipeline>(allocation->object.get());
            }
        }

        auto self = reinterpret_cast<Device*>(cSelf);
        Device* device = self->device;
        DeviceCreateRenderPipelineCmd cmd;

        cmd.self = cSelf;

        auto* allocation = self->device->GetClient()->RenderPipelineAllocator().New(self->device);
        cmd.result = ObjectHandle{allocation->object->id, allocation->generation};

        cmd.descriptor = descriptor;

        device->GetClient()->SerializeCommand(cmd);

        return reinterpret_cast<WGPURenderPipeline>(allocation->object.get());
    }

    WGPUSampler ClientDeviceCreateSampler(WGPUDevice cSelf, WGPUSamplerDescriptor const * descriptor) {
        {
            bool sameDevice = true;
            auto self = reinterpret_cast<Device*>(cSelf);
            Device* device = self->device;
            DAWN_UNUSED(device);

            do {
                {
                    if (!DeviceMatches(device, descriptor, 1)) {
                        sameDevice = false;
                        break;
                    }
                }
            } while (false);

            if (DAWN_UNLIKELY(!sameDevice)) {
                device->InjectError(WGPUErrorType_Validation,
                                    "All objects must be from the same device.");
                // Allocate an object without registering it on the server. This is backed by a real allocation on
                // the client so commands can be sent with it. But because it's not allocated on the server, it will
                // be a fatal error to use it.
                auto self = reinterpret_cast<Device*>(cSelf);
                auto* allocation = self->device->GetClient()->SamplerAllocator().New(self->device);
                return reinterpret_cast<WGPUSampler>(allocation->object.get());
            }
        }

        auto self = reinterpret_cast<Device*>(cSelf);
        Device* device = self->device;
        DeviceCreateSamplerCmd cmd;

        cmd.self = cSelf;

        auto* allocation = self->device->GetClient()->SamplerAllocator().New(self->device);
        cmd.result = ObjectHandle{allocation->object->id, allocation->generation};

        cmd.descriptor = descriptor;

        device->GetClient()->SerializeCommand(cmd);

        return reinterpret_cast<WGPUSampler>(allocation->object.get());
    }

    WGPUShaderModule ClientDeviceCreateShaderModule(WGPUDevice cSelf, WGPUShaderModuleDescriptor const * descriptor) {
        {
            bool sameDevice = true;
            auto self = reinterpret_cast<Device*>(cSelf);
            Device* device = self->device;
            DAWN_UNUSED(device);

            do {
                {
                    if (!DeviceMatches(device, descriptor, 1)) {
                        sameDevice = false;
                        break;
                    }
                }
            } while (false);

            if (DAWN_UNLIKELY(!sameDevice)) {
                device->InjectError(WGPUErrorType_Validation,
                                    "All objects must be from the same device.");
                // Allocate an object without registering it on the server. This is backed by a real allocation on
                // the client so commands can be sent with it. But because it's not allocated on the server, it will
                // be a fatal error to use it.
                auto self = reinterpret_cast<Device*>(cSelf);
                auto* allocation = self->device->GetClient()->ShaderModuleAllocator().New(self->device);
                return reinterpret_cast<WGPUShaderModule>(allocation->object.get());
            }
        }

        auto self = reinterpret_cast<Device*>(cSelf);
        Device* device = self->device;
        DeviceCreateShaderModuleCmd cmd;

        cmd.self = cSelf;

        auto* allocation = self->device->GetClient()->ShaderModuleAllocator().New(self->device);
        cmd.result = ObjectHandle{allocation->object->id, allocation->generation};

        cmd.descriptor = descriptor;

        device->GetClient()->SerializeCommand(cmd);

        return reinterpret_cast<WGPUShaderModule>(allocation->object.get());
    }

    WGPUSwapChain ClientDeviceCreateSwapChain(WGPUDevice cSelf, WGPUSurface surface, WGPUSwapChainDescriptor const * descriptor) {
        {
            bool sameDevice = true;
            auto self = reinterpret_cast<Device*>(cSelf);
            Device* device = self->device;
            DAWN_UNUSED(device);

            do {
                if (surface != nullptr)
                {
                    if (!DeviceMatches(device, surface)) {
                        sameDevice = false;
                        break;
                    }
                }
                {
                    if (!DeviceMatches(device, descriptor, 1)) {
                        sameDevice = false;
                        break;
                    }
                }
            } while (false);

            if (DAWN_UNLIKELY(!sameDevice)) {
                device->InjectError(WGPUErrorType_Validation,
                                    "All objects must be from the same device.");
                // Allocate an object without registering it on the server. This is backed by a real allocation on
                // the client so commands can be sent with it. But because it's not allocated on the server, it will
                // be a fatal error to use it.
                auto self = reinterpret_cast<Device*>(cSelf);
                auto* allocation = self->device->GetClient()->SwapChainAllocator().New(self->device);
                return reinterpret_cast<WGPUSwapChain>(allocation->object.get());
            }
        }

        auto self = reinterpret_cast<Device*>(cSelf);
        Device* device = self->device;
        DeviceCreateSwapChainCmd cmd;

        cmd.self = cSelf;

        auto* allocation = self->device->GetClient()->SwapChainAllocator().New(self->device);
        cmd.result = ObjectHandle{allocation->object->id, allocation->generation};

        cmd.surface = surface;
        cmd.descriptor = descriptor;

        device->GetClient()->SerializeCommand(cmd);

        return reinterpret_cast<WGPUSwapChain>(allocation->object.get());
    }

    WGPUTexture ClientDeviceCreateTexture(WGPUDevice cSelf, WGPUTextureDescriptor const * descriptor) {
        {
            bool sameDevice = true;
            auto self = reinterpret_cast<Device*>(cSelf);
            Device* device = self->device;
            DAWN_UNUSED(device);

            do {
                {
                    if (!DeviceMatches(device, descriptor, 1)) {
                        sameDevice = false;
                        break;
                    }
                }
            } while (false);

            if (DAWN_UNLIKELY(!sameDevice)) {
                device->InjectError(WGPUErrorType_Validation,
                                    "All objects must be from the same device.");
                // Allocate an object without registering it on the server. This is backed by a real allocation on
                // the client so commands can be sent with it. But because it's not allocated on the server, it will
                // be a fatal error to use it.
                auto self = reinterpret_cast<Device*>(cSelf);
                auto* allocation = self->device->GetClient()->TextureAllocator().New(self->device);
                return reinterpret_cast<WGPUTexture>(allocation->object.get());
            }
        }

        auto self = reinterpret_cast<Device*>(cSelf);
        Device* device = self->device;
        DeviceCreateTextureCmd cmd;

        cmd.self = cSelf;

        auto* allocation = self->device->GetClient()->TextureAllocator().New(self->device);
        cmd.result = ObjectHandle{allocation->object->id, allocation->generation};

        cmd.descriptor = descriptor;

        device->GetClient()->SerializeCommand(cmd);

        return reinterpret_cast<WGPUTexture>(allocation->object.get());
    }

    static
    WGPUQueue ClientDeviceGetDefaultQueue(WGPUDevice cSelf) {

        auto self = reinterpret_cast<Device*>(cSelf);
        return self->GetDefaultQueue();
    }

    static
    void ClientDeviceInjectError(WGPUDevice cSelf, WGPUErrorType type, char const * message) {
        {
            bool sameDevice = true;
            auto self = reinterpret_cast<Device*>(cSelf);
            Device* device = self->device;
            DAWN_UNUSED(device);

            do {
            } while (false);

            if (DAWN_UNLIKELY(!sameDevice)) {
                device->InjectError(WGPUErrorType_Validation,
                                    "All objects must be from the same device.");
                return;
            }
        }

        auto self = reinterpret_cast<Device*>(cSelf);
        return self->InjectError( type,  message);
    }

    void ClientDeviceLoseForTesting(WGPUDevice cSelf) {

        auto self = reinterpret_cast<Device*>(cSelf);
        Device* device = self->device;
        DeviceLoseForTestingCmd cmd;

        cmd.self = cSelf;



        device->GetClient()->SerializeCommand(cmd);

    }

    static
    bool ClientDevicePopErrorScope(WGPUDevice cSelf, WGPUErrorCallback callback, void * userdata) {
        {
            bool sameDevice = true;
            auto self = reinterpret_cast<Device*>(cSelf);
            Device* device = self->device;
            DAWN_UNUSED(device);

            do {
            } while (false);

            if (DAWN_UNLIKELY(!sameDevice)) {
                device->InjectError(WGPUErrorType_Validation,
                                    "All objects must be from the same device.");
                return {};
            }
        }

        auto self = reinterpret_cast<Device*>(cSelf);
        return self->PopErrorScope( callback,  userdata);
    }

    static
    void ClientDevicePushErrorScope(WGPUDevice cSelf, WGPUErrorFilter filter) {
        {
            bool sameDevice = true;
            auto self = reinterpret_cast<Device*>(cSelf);
            Device* device = self->device;
            DAWN_UNUSED(device);

            do {
            } while (false);

            if (DAWN_UNLIKELY(!sameDevice)) {
                device->InjectError(WGPUErrorType_Validation,
                                    "All objects must be from the same device.");
                return;
            }
        }

        auto self = reinterpret_cast<Device*>(cSelf);
        return self->PushErrorScope( filter);
    }

    static
    void ClientDeviceSetDeviceLostCallback(WGPUDevice cSelf, WGPUDeviceLostCallback callback, void * userdata) {
        {
            bool sameDevice = true;
            auto self = reinterpret_cast<Device*>(cSelf);
            Device* device = self->device;
            DAWN_UNUSED(device);

            do {
            } while (false);

            if (DAWN_UNLIKELY(!sameDevice)) {
                device->InjectError(WGPUErrorType_Validation,
                                    "All objects must be from the same device.");
                return;
            }
        }

        auto self = reinterpret_cast<Device*>(cSelf);
        return self->SetDeviceLostCallback( callback,  userdata);
    }

    static
    void ClientDeviceSetUncapturedErrorCallback(WGPUDevice cSelf, WGPUErrorCallback callback, void * userdata) {
        {
            bool sameDevice = true;
            auto self = reinterpret_cast<Device*>(cSelf);
            Device* device = self->device;
            DAWN_UNUSED(device);

            do {
            } while (false);

            if (DAWN_UNLIKELY(!sameDevice)) {
                device->InjectError(WGPUErrorType_Validation,
                                    "All objects must be from the same device.");
                return;
            }
        }

        auto self = reinterpret_cast<Device*>(cSelf);
        return self->SetUncapturedErrorCallback( callback,  userdata);
    }

    void ClientDeviceTick(WGPUDevice cSelf) {

        auto self = reinterpret_cast<Device*>(cSelf);
        Device* device = self->device;
        DeviceTickCmd cmd;

        cmd.self = cSelf;



        device->GetClient()->SerializeCommand(cmd);

    }



    static
    uint64_t ClientFenceGetCompletedValue(WGPUFence cSelf) {

        auto self = reinterpret_cast<Fence*>(cSelf);
        return self->GetCompletedValue();
    }

    static
    void ClientFenceOnCompletion(WGPUFence cSelf, uint64_t value, WGPUFenceOnCompletionCallback callback, void * userdata) {
        {
            bool sameDevice = true;
            auto self = reinterpret_cast<Fence*>(cSelf);
            Device* device = self->device;
            DAWN_UNUSED(device);

            do {
            } while (false);

            if (DAWN_UNLIKELY(!sameDevice)) {
                device->InjectError(WGPUErrorType_Validation,
                                    "All objects must be from the same device.");
                return;
            }
        }

        auto self = reinterpret_cast<Fence*>(cSelf);
        return self->OnCompletion( value,  callback,  userdata);
    }

    void ClientFenceRelease(WGPUFence cObj) {
        Fence* obj = reinterpret_cast<Fence*>(cObj);
        obj->refcount --;

        if (obj->refcount > 0) {
            return;
        }

        DestroyObjectCmd cmd;
        cmd.objectType = ObjectType::Fence;
        cmd.objectId = obj->id;

        obj->device->GetClient()->SerializeCommand(cmd);
        obj->device->GetClient()->FenceAllocator().Free(obj);
    }

    void ClientFenceReference(WGPUFence cObj) {
        Fence* obj = reinterpret_cast<Fence*>(cObj);
        obj->refcount ++;
    }


    WGPUSurface ClientInstanceCreateSurface(WGPUInstance cSelf, WGPUSurfaceDescriptor const * descriptor) {
        {
            bool sameDevice = true;
            auto self = reinterpret_cast<Instance*>(cSelf);
            Device* device = self->device;
            DAWN_UNUSED(device);

            do {
                {
                    if (!DeviceMatches(device, descriptor, 1)) {
                        sameDevice = false;
                        break;
                    }
                }
            } while (false);

            if (DAWN_UNLIKELY(!sameDevice)) {
                device->InjectError(WGPUErrorType_Validation,
                                    "All objects must be from the same device.");
                // Allocate an object without registering it on the server. This is backed by a real allocation on
                // the client so commands can be sent with it. But because it's not allocated on the server, it will
                // be a fatal error to use it.
                auto self = reinterpret_cast<Instance*>(cSelf);
                auto* allocation = self->device->GetClient()->SurfaceAllocator().New(self->device);
                return reinterpret_cast<WGPUSurface>(allocation->object.get());
            }
        }

        auto self = reinterpret_cast<Instance*>(cSelf);
        Device* device = self->device;
        InstanceCreateSurfaceCmd cmd;

        cmd.self = cSelf;

        auto* allocation = self->device->GetClient()->SurfaceAllocator().New(self->device);
        cmd.result = ObjectHandle{allocation->object->id, allocation->generation};

        cmd.descriptor = descriptor;

        device->GetClient()->SerializeCommand(cmd);

        return reinterpret_cast<WGPUSurface>(allocation->object.get());
    }

    void ClientInstanceRelease(WGPUInstance cObj) {
        Instance* obj = reinterpret_cast<Instance*>(cObj);
        obj->refcount --;

        if (obj->refcount > 0) {
            return;
        }

        DestroyObjectCmd cmd;
        cmd.objectType = ObjectType::Instance;
        cmd.objectId = obj->id;

        obj->device->GetClient()->SerializeCommand(cmd);
        obj->device->GetClient()->InstanceAllocator().Free(obj);
    }

    void ClientInstanceReference(WGPUInstance cObj) {
        Instance* obj = reinterpret_cast<Instance*>(cObj);
        obj->refcount ++;
    }


    void ClientPipelineLayoutRelease(WGPUPipelineLayout cObj) {
        PipelineLayout* obj = reinterpret_cast<PipelineLayout*>(cObj);
        obj->refcount --;

        if (obj->refcount > 0) {
            return;
        }

        DestroyObjectCmd cmd;
        cmd.objectType = ObjectType::PipelineLayout;
        cmd.objectId = obj->id;

        obj->device->GetClient()->SerializeCommand(cmd);
        obj->device->GetClient()->PipelineLayoutAllocator().Free(obj);
    }

    void ClientPipelineLayoutReference(WGPUPipelineLayout cObj) {
        PipelineLayout* obj = reinterpret_cast<PipelineLayout*>(cObj);
        obj->refcount ++;
    }


    void ClientQuerySetDestroy(WGPUQuerySet cSelf) {

        auto self = reinterpret_cast<QuerySet*>(cSelf);
        Device* device = self->device;
        QuerySetDestroyCmd cmd;

        cmd.self = cSelf;



        device->GetClient()->SerializeCommand(cmd);

    }

    void ClientQuerySetRelease(WGPUQuerySet cObj) {
        QuerySet* obj = reinterpret_cast<QuerySet*>(cObj);
        obj->refcount --;

        if (obj->refcount > 0) {
            return;
        }

        DestroyObjectCmd cmd;
        cmd.objectType = ObjectType::QuerySet;
        cmd.objectId = obj->id;

        obj->device->GetClient()->SerializeCommand(cmd);
        obj->device->GetClient()->QuerySetAllocator().Free(obj);
    }

    void ClientQuerySetReference(WGPUQuerySet cObj) {
        QuerySet* obj = reinterpret_cast<QuerySet*>(cObj);
        obj->refcount ++;
    }


    static
    WGPUFence ClientQueueCreateFence(WGPUQueue cSelf, WGPUFenceDescriptor const * descriptor) {
        {
            bool sameDevice = true;
            auto self = reinterpret_cast<Queue*>(cSelf);
            Device* device = self->device;
            DAWN_UNUSED(device);

            do {
                if (descriptor != nullptr)
                {
                    if (!DeviceMatches(device, descriptor, 1)) {
                        sameDevice = false;
                        break;
                    }
                }
            } while (false);

            if (DAWN_UNLIKELY(!sameDevice)) {
                device->InjectError(WGPUErrorType_Validation,
                                    "All objects must be from the same device.");
                // Allocate an object without registering it on the server. This is backed by a real allocation on
                // the client so commands can be sent with it. But because it's not allocated on the server, it will
                // be a fatal error to use it.
                auto self = reinterpret_cast<Queue*>(cSelf);
                auto* allocation = self->device->GetClient()->FenceAllocator().New(self->device);
                return reinterpret_cast<WGPUFence>(allocation->object.get());
            }
        }

        auto self = reinterpret_cast<Queue*>(cSelf);
        return self->CreateFence( descriptor);
    }

    void ClientQueueSignal(WGPUQueue cSelf, WGPUFence fence, uint64_t signalValue) {
        {
            bool sameDevice = true;
            auto self = reinterpret_cast<Queue*>(cSelf);
            Device* device = self->device;
            DAWN_UNUSED(device);

            do {
                {
                    if (!DeviceMatches(device, fence)) {
                        sameDevice = false;
                        break;
                    }
                }
            } while (false);

            if (DAWN_UNLIKELY(!sameDevice)) {
                device->InjectError(WGPUErrorType_Validation,
                                    "All objects must be from the same device.");
                return;
            }
        }

        auto self = reinterpret_cast<Queue*>(cSelf);
        Device* device = self->device;
        QueueSignalCmd cmd;

        cmd.self = cSelf;


        cmd.fence = fence;
        cmd.signalValue = signalValue;

        device->GetClient()->SerializeCommand(cmd);

    }

    void ClientQueueSubmit(WGPUQueue cSelf, uint32_t commandCount, WGPUCommandBuffer const * commands) {
        {
            bool sameDevice = true;
            auto self = reinterpret_cast<Queue*>(cSelf);
            Device* device = self->device;
            DAWN_UNUSED(device);

            do {
                {
                    if (!DeviceMatches(device, commands, commandCount)) {
                        sameDevice = false;
                        break;
                    }
                }
            } while (false);

            if (DAWN_UNLIKELY(!sameDevice)) {
                device->InjectError(WGPUErrorType_Validation,
                                    "All objects must be from the same device.");
                return;
            }
        }

        auto self = reinterpret_cast<Queue*>(cSelf);
        Device* device = self->device;
        QueueSubmitCmd cmd;

        cmd.self = cSelf;


        cmd.commandCount = commandCount;
        cmd.commands = commands;

        device->GetClient()->SerializeCommand(cmd);

    }

    static
    void ClientQueueWriteBuffer(WGPUQueue cSelf, WGPUBuffer buffer, uint64_t bufferOffset, void const * data, size_t size) {
        {
            bool sameDevice = true;
            auto self = reinterpret_cast<Queue*>(cSelf);
            Device* device = self->device;
            DAWN_UNUSED(device);

            do {
                {
                    if (!DeviceMatches(device, buffer)) {
                        sameDevice = false;
                        break;
                    }
                }
            } while (false);

            if (DAWN_UNLIKELY(!sameDevice)) {
                device->InjectError(WGPUErrorType_Validation,
                                    "All objects must be from the same device.");
                return;
            }
        }

        auto self = reinterpret_cast<Queue*>(cSelf);
        return self->WriteBuffer( buffer,  bufferOffset,  data,  size);
    }

    static
    void ClientQueueWriteTexture(WGPUQueue cSelf, WGPUTextureCopyView const * destination, void const * data, size_t dataSize, WGPUTextureDataLayout const * dataLayout, WGPUExtent3D const * writeSize) {
        {
            bool sameDevice = true;
            auto self = reinterpret_cast<Queue*>(cSelf);
            Device* device = self->device;
            DAWN_UNUSED(device);

            do {
                {
                    if (!DeviceMatches(device, destination, 1)) {
                        sameDevice = false;
                        break;
                    }
                }
                {
                    if (!DeviceMatches(device, dataLayout, 1)) {
                        sameDevice = false;
                        break;
                    }
                }
            } while (false);

            if (DAWN_UNLIKELY(!sameDevice)) {
                device->InjectError(WGPUErrorType_Validation,
                                    "All objects must be from the same device.");
                return;
            }
        }

        auto self = reinterpret_cast<Queue*>(cSelf);
        return self->WriteTexture( destination,  data,  dataSize,  dataLayout,  writeSize);
    }

    void ClientQueueRelease(WGPUQueue cObj) {
        Queue* obj = reinterpret_cast<Queue*>(cObj);
        obj->refcount --;

        if (obj->refcount > 0) {
            return;
        }

        DestroyObjectCmd cmd;
        cmd.objectType = ObjectType::Queue;
        cmd.objectId = obj->id;

        obj->device->GetClient()->SerializeCommand(cmd);
        obj->device->GetClient()->QueueAllocator().Free(obj);
    }

    void ClientQueueReference(WGPUQueue cObj) {
        Queue* obj = reinterpret_cast<Queue*>(cObj);
        obj->refcount ++;
    }


    void ClientRenderBundleRelease(WGPURenderBundle cObj) {
        RenderBundle* obj = reinterpret_cast<RenderBundle*>(cObj);
        obj->refcount --;

        if (obj->refcount > 0) {
            return;
        }

        DestroyObjectCmd cmd;
        cmd.objectType = ObjectType::RenderBundle;
        cmd.objectId = obj->id;

        obj->device->GetClient()->SerializeCommand(cmd);
        obj->device->GetClient()->RenderBundleAllocator().Free(obj);
    }

    void ClientRenderBundleReference(WGPURenderBundle cObj) {
        RenderBundle* obj = reinterpret_cast<RenderBundle*>(cObj);
        obj->refcount ++;
    }


    void ClientRenderBundleEncoderDraw(WGPURenderBundleEncoder cSelf, uint32_t vertexCount, uint32_t instanceCount, uint32_t firstVertex, uint32_t firstInstance) {
        {
            bool sameDevice = true;
            auto self = reinterpret_cast<RenderBundleEncoder*>(cSelf);
            Device* device = self->device;
            DAWN_UNUSED(device);

            do {
            } while (false);

            if (DAWN_UNLIKELY(!sameDevice)) {
                device->InjectError(WGPUErrorType_Validation,
                                    "All objects must be from the same device.");
                return;
            }
        }

        auto self = reinterpret_cast<RenderBundleEncoder*>(cSelf);
        Device* device = self->device;
        RenderBundleEncoderDrawCmd cmd;

        cmd.self = cSelf;


        cmd.vertexCount = vertexCount;
        cmd.instanceCount = instanceCount;
        cmd.firstVertex = firstVertex;
        cmd.firstInstance = firstInstance;

        device->GetClient()->SerializeCommand(cmd);

    }

    void ClientRenderBundleEncoderDrawIndexed(WGPURenderBundleEncoder cSelf, uint32_t indexCount, uint32_t instanceCount, uint32_t firstIndex, int32_t baseVertex, uint32_t firstInstance) {
        {
            bool sameDevice = true;
            auto self = reinterpret_cast<RenderBundleEncoder*>(cSelf);
            Device* device = self->device;
            DAWN_UNUSED(device);

            do {
            } while (false);

            if (DAWN_UNLIKELY(!sameDevice)) {
                device->InjectError(WGPUErrorType_Validation,
                                    "All objects must be from the same device.");
                return;
            }
        }

        auto self = reinterpret_cast<RenderBundleEncoder*>(cSelf);
        Device* device = self->device;
        RenderBundleEncoderDrawIndexedCmd cmd;

        cmd.self = cSelf;


        cmd.indexCount = indexCount;
        cmd.instanceCount = instanceCount;
        cmd.firstIndex = firstIndex;
        cmd.baseVertex = baseVertex;
        cmd.firstInstance = firstInstance;

        device->GetClient()->SerializeCommand(cmd);

    }

    void ClientRenderBundleEncoderDrawIndexedIndirect(WGPURenderBundleEncoder cSelf, WGPUBuffer indirectBuffer, uint64_t indirectOffset) {
        {
            bool sameDevice = true;
            auto self = reinterpret_cast<RenderBundleEncoder*>(cSelf);
            Device* device = self->device;
            DAWN_UNUSED(device);

            do {
                {
                    if (!DeviceMatches(device, indirectBuffer)) {
                        sameDevice = false;
                        break;
                    }
                }
            } while (false);

            if (DAWN_UNLIKELY(!sameDevice)) {
                device->InjectError(WGPUErrorType_Validation,
                                    "All objects must be from the same device.");
                return;
            }
        }

        auto self = reinterpret_cast<RenderBundleEncoder*>(cSelf);
        Device* device = self->device;
        RenderBundleEncoderDrawIndexedIndirectCmd cmd;

        cmd.self = cSelf;


        cmd.indirectBuffer = indirectBuffer;
        cmd.indirectOffset = indirectOffset;

        device->GetClient()->SerializeCommand(cmd);

    }

    void ClientRenderBundleEncoderDrawIndirect(WGPURenderBundleEncoder cSelf, WGPUBuffer indirectBuffer, uint64_t indirectOffset) {
        {
            bool sameDevice = true;
            auto self = reinterpret_cast<RenderBundleEncoder*>(cSelf);
            Device* device = self->device;
            DAWN_UNUSED(device);

            do {
                {
                    if (!DeviceMatches(device, indirectBuffer)) {
                        sameDevice = false;
                        break;
                    }
                }
            } while (false);

            if (DAWN_UNLIKELY(!sameDevice)) {
                device->InjectError(WGPUErrorType_Validation,
                                    "All objects must be from the same device.");
                return;
            }
        }

        auto self = reinterpret_cast<RenderBundleEncoder*>(cSelf);
        Device* device = self->device;
        RenderBundleEncoderDrawIndirectCmd cmd;

        cmd.self = cSelf;


        cmd.indirectBuffer = indirectBuffer;
        cmd.indirectOffset = indirectOffset;

        device->GetClient()->SerializeCommand(cmd);

    }

    WGPURenderBundle ClientRenderBundleEncoderFinish(WGPURenderBundleEncoder cSelf, WGPURenderBundleDescriptor const * descriptor) {
        {
            bool sameDevice = true;
            auto self = reinterpret_cast<RenderBundleEncoder*>(cSelf);
            Device* device = self->device;
            DAWN_UNUSED(device);

            do {
                if (descriptor != nullptr)
                {
                    if (!DeviceMatches(device, descriptor, 1)) {
                        sameDevice = false;
                        break;
                    }
                }
            } while (false);

            if (DAWN_UNLIKELY(!sameDevice)) {
                device->InjectError(WGPUErrorType_Validation,
                                    "All objects must be from the same device.");
                // Allocate an object without registering it on the server. This is backed by a real allocation on
                // the client so commands can be sent with it. But because it's not allocated on the server, it will
                // be a fatal error to use it.
                auto self = reinterpret_cast<RenderBundleEncoder*>(cSelf);
                auto* allocation = self->device->GetClient()->RenderBundleAllocator().New(self->device);
                return reinterpret_cast<WGPURenderBundle>(allocation->object.get());
            }
        }

        auto self = reinterpret_cast<RenderBundleEncoder*>(cSelf);
        Device* device = self->device;
        RenderBundleEncoderFinishCmd cmd;

        cmd.self = cSelf;

        auto* allocation = self->device->GetClient()->RenderBundleAllocator().New(self->device);
        cmd.result = ObjectHandle{allocation->object->id, allocation->generation};

        cmd.descriptor = descriptor;

        device->GetClient()->SerializeCommand(cmd);

        return reinterpret_cast<WGPURenderBundle>(allocation->object.get());
    }

    void ClientRenderBundleEncoderInsertDebugMarker(WGPURenderBundleEncoder cSelf, char const * markerLabel) {
        {
            bool sameDevice = true;
            auto self = reinterpret_cast<RenderBundleEncoder*>(cSelf);
            Device* device = self->device;
            DAWN_UNUSED(device);

            do {
            } while (false);

            if (DAWN_UNLIKELY(!sameDevice)) {
                device->InjectError(WGPUErrorType_Validation,
                                    "All objects must be from the same device.");
                return;
            }
        }

        auto self = reinterpret_cast<RenderBundleEncoder*>(cSelf);
        Device* device = self->device;
        RenderBundleEncoderInsertDebugMarkerCmd cmd;

        cmd.self = cSelf;


        cmd.markerLabel = markerLabel;

        device->GetClient()->SerializeCommand(cmd);

    }

    void ClientRenderBundleEncoderPopDebugGroup(WGPURenderBundleEncoder cSelf) {

        auto self = reinterpret_cast<RenderBundleEncoder*>(cSelf);
        Device* device = self->device;
        RenderBundleEncoderPopDebugGroupCmd cmd;

        cmd.self = cSelf;



        device->GetClient()->SerializeCommand(cmd);

    }

    void ClientRenderBundleEncoderPushDebugGroup(WGPURenderBundleEncoder cSelf, char const * groupLabel) {
        {
            bool sameDevice = true;
            auto self = reinterpret_cast<RenderBundleEncoder*>(cSelf);
            Device* device = self->device;
            DAWN_UNUSED(device);

            do {
            } while (false);

            if (DAWN_UNLIKELY(!sameDevice)) {
                device->InjectError(WGPUErrorType_Validation,
                                    "All objects must be from the same device.");
                return;
            }
        }

        auto self = reinterpret_cast<RenderBundleEncoder*>(cSelf);
        Device* device = self->device;
        RenderBundleEncoderPushDebugGroupCmd cmd;

        cmd.self = cSelf;


        cmd.groupLabel = groupLabel;

        device->GetClient()->SerializeCommand(cmd);

    }

    void ClientRenderBundleEncoderSetBindGroup(WGPURenderBundleEncoder cSelf, uint32_t groupIndex, WGPUBindGroup group, uint32_t dynamicOffsetCount, uint32_t const * dynamicOffsets) {
        {
            bool sameDevice = true;
            auto self = reinterpret_cast<RenderBundleEncoder*>(cSelf);
            Device* device = self->device;
            DAWN_UNUSED(device);

            do {
                {
                    if (!DeviceMatches(device, group)) {
                        sameDevice = false;
                        break;
                    }
                }
            } while (false);

            if (DAWN_UNLIKELY(!sameDevice)) {
                device->InjectError(WGPUErrorType_Validation,
                                    "All objects must be from the same device.");
                return;
            }
        }

        auto self = reinterpret_cast<RenderBundleEncoder*>(cSelf);
        Device* device = self->device;
        RenderBundleEncoderSetBindGroupCmd cmd;

        cmd.self = cSelf;


        cmd.groupIndex = groupIndex;
        cmd.group = group;
        cmd.dynamicOffsetCount = dynamicOffsetCount;
        cmd.dynamicOffsets = dynamicOffsets;

        device->GetClient()->SerializeCommand(cmd);

    }

    void ClientRenderBundleEncoderSetIndexBuffer(WGPURenderBundleEncoder cSelf, WGPUBuffer buffer, uint64_t offset, uint64_t size) {
        {
            bool sameDevice = true;
            auto self = reinterpret_cast<RenderBundleEncoder*>(cSelf);
            Device* device = self->device;
            DAWN_UNUSED(device);

            do {
                {
                    if (!DeviceMatches(device, buffer)) {
                        sameDevice = false;
                        break;
                    }
                }
            } while (false);

            if (DAWN_UNLIKELY(!sameDevice)) {
                device->InjectError(WGPUErrorType_Validation,
                                    "All objects must be from the same device.");
                return;
            }
        }

        auto self = reinterpret_cast<RenderBundleEncoder*>(cSelf);
        Device* device = self->device;
        RenderBundleEncoderSetIndexBufferCmd cmd;

        cmd.self = cSelf;


        cmd.buffer = buffer;
        cmd.offset = offset;
        cmd.size = size;

        device->GetClient()->SerializeCommand(cmd);

    }

    void ClientRenderBundleEncoderSetIndexBufferWithFormat(WGPURenderBundleEncoder cSelf, WGPUBuffer buffer, WGPUIndexFormat format, uint64_t offset, uint64_t size) {
        {
            bool sameDevice = true;
            auto self = reinterpret_cast<RenderBundleEncoder*>(cSelf);
            Device* device = self->device;
            DAWN_UNUSED(device);

            do {
                {
                    if (!DeviceMatches(device, buffer)) {
                        sameDevice = false;
                        break;
                    }
                }
            } while (false);

            if (DAWN_UNLIKELY(!sameDevice)) {
                device->InjectError(WGPUErrorType_Validation,
                                    "All objects must be from the same device.");
                return;
            }
        }

        auto self = reinterpret_cast<RenderBundleEncoder*>(cSelf);
        Device* device = self->device;
        RenderBundleEncoderSetIndexBufferWithFormatCmd cmd;

        cmd.self = cSelf;


        cmd.buffer = buffer;
        cmd.format = format;
        cmd.offset = offset;
        cmd.size = size;

        device->GetClient()->SerializeCommand(cmd);

    }

    void ClientRenderBundleEncoderSetPipeline(WGPURenderBundleEncoder cSelf, WGPURenderPipeline pipeline) {
        {
            bool sameDevice = true;
            auto self = reinterpret_cast<RenderBundleEncoder*>(cSelf);
            Device* device = self->device;
            DAWN_UNUSED(device);

            do {
                {
                    if (!DeviceMatches(device, pipeline)) {
                        sameDevice = false;
                        break;
                    }
                }
            } while (false);

            if (DAWN_UNLIKELY(!sameDevice)) {
                device->InjectError(WGPUErrorType_Validation,
                                    "All objects must be from the same device.");
                return;
            }
        }

        auto self = reinterpret_cast<RenderBundleEncoder*>(cSelf);
        Device* device = self->device;
        RenderBundleEncoderSetPipelineCmd cmd;

        cmd.self = cSelf;


        cmd.pipeline = pipeline;

        device->GetClient()->SerializeCommand(cmd);

    }

    void ClientRenderBundleEncoderSetVertexBuffer(WGPURenderBundleEncoder cSelf, uint32_t slot, WGPUBuffer buffer, uint64_t offset, uint64_t size) {
        {
            bool sameDevice = true;
            auto self = reinterpret_cast<RenderBundleEncoder*>(cSelf);
            Device* device = self->device;
            DAWN_UNUSED(device);

            do {
                {
                    if (!DeviceMatches(device, buffer)) {
                        sameDevice = false;
                        break;
                    }
                }
            } while (false);

            if (DAWN_UNLIKELY(!sameDevice)) {
                device->InjectError(WGPUErrorType_Validation,
                                    "All objects must be from the same device.");
                return;
            }
        }

        auto self = reinterpret_cast<RenderBundleEncoder*>(cSelf);
        Device* device = self->device;
        RenderBundleEncoderSetVertexBufferCmd cmd;

        cmd.self = cSelf;


        cmd.slot = slot;
        cmd.buffer = buffer;
        cmd.offset = offset;
        cmd.size = size;

        device->GetClient()->SerializeCommand(cmd);

    }

    void ClientRenderBundleEncoderRelease(WGPURenderBundleEncoder cObj) {
        RenderBundleEncoder* obj = reinterpret_cast<RenderBundleEncoder*>(cObj);
        obj->refcount --;

        if (obj->refcount > 0) {
            return;
        }

        DestroyObjectCmd cmd;
        cmd.objectType = ObjectType::RenderBundleEncoder;
        cmd.objectId = obj->id;

        obj->device->GetClient()->SerializeCommand(cmd);
        obj->device->GetClient()->RenderBundleEncoderAllocator().Free(obj);
    }

    void ClientRenderBundleEncoderReference(WGPURenderBundleEncoder cObj) {
        RenderBundleEncoder* obj = reinterpret_cast<RenderBundleEncoder*>(cObj);
        obj->refcount ++;
    }


    void ClientRenderPassEncoderDraw(WGPURenderPassEncoder cSelf, uint32_t vertexCount, uint32_t instanceCount, uint32_t firstVertex, uint32_t firstInstance) {
        {
            bool sameDevice = true;
            auto self = reinterpret_cast<RenderPassEncoder*>(cSelf);
            Device* device = self->device;
            DAWN_UNUSED(device);

            do {
            } while (false);

            if (DAWN_UNLIKELY(!sameDevice)) {
                device->InjectError(WGPUErrorType_Validation,
                                    "All objects must be from the same device.");
                return;
            }
        }

        auto self = reinterpret_cast<RenderPassEncoder*>(cSelf);
        Device* device = self->device;
        RenderPassEncoderDrawCmd cmd;

        cmd.self = cSelf;


        cmd.vertexCount = vertexCount;
        cmd.instanceCount = instanceCount;
        cmd.firstVertex = firstVertex;
        cmd.firstInstance = firstInstance;

        device->GetClient()->SerializeCommand(cmd);

    }

    void ClientRenderPassEncoderDrawIndexed(WGPURenderPassEncoder cSelf, uint32_t indexCount, uint32_t instanceCount, uint32_t firstIndex, int32_t baseVertex, uint32_t firstInstance) {
        {
            bool sameDevice = true;
            auto self = reinterpret_cast<RenderPassEncoder*>(cSelf);
            Device* device = self->device;
            DAWN_UNUSED(device);

            do {
            } while (false);

            if (DAWN_UNLIKELY(!sameDevice)) {
                device->InjectError(WGPUErrorType_Validation,
                                    "All objects must be from the same device.");
                return;
            }
        }

        auto self = reinterpret_cast<RenderPassEncoder*>(cSelf);
        Device* device = self->device;
        RenderPassEncoderDrawIndexedCmd cmd;

        cmd.self = cSelf;


        cmd.indexCount = indexCount;
        cmd.instanceCount = instanceCount;
        cmd.firstIndex = firstIndex;
        cmd.baseVertex = baseVertex;
        cmd.firstInstance = firstInstance;

        device->GetClient()->SerializeCommand(cmd);

    }

    void ClientRenderPassEncoderDrawIndexedIndirect(WGPURenderPassEncoder cSelf, WGPUBuffer indirectBuffer, uint64_t indirectOffset) {
        {
            bool sameDevice = true;
            auto self = reinterpret_cast<RenderPassEncoder*>(cSelf);
            Device* device = self->device;
            DAWN_UNUSED(device);

            do {
                {
                    if (!DeviceMatches(device, indirectBuffer)) {
                        sameDevice = false;
                        break;
                    }
                }
            } while (false);

            if (DAWN_UNLIKELY(!sameDevice)) {
                device->InjectError(WGPUErrorType_Validation,
                                    "All objects must be from the same device.");
                return;
            }
        }

        auto self = reinterpret_cast<RenderPassEncoder*>(cSelf);
        Device* device = self->device;
        RenderPassEncoderDrawIndexedIndirectCmd cmd;

        cmd.self = cSelf;


        cmd.indirectBuffer = indirectBuffer;
        cmd.indirectOffset = indirectOffset;

        device->GetClient()->SerializeCommand(cmd);

    }

    void ClientRenderPassEncoderDrawIndirect(WGPURenderPassEncoder cSelf, WGPUBuffer indirectBuffer, uint64_t indirectOffset) {
        {
            bool sameDevice = true;
            auto self = reinterpret_cast<RenderPassEncoder*>(cSelf);
            Device* device = self->device;
            DAWN_UNUSED(device);

            do {
                {
                    if (!DeviceMatches(device, indirectBuffer)) {
                        sameDevice = false;
                        break;
                    }
                }
            } while (false);

            if (DAWN_UNLIKELY(!sameDevice)) {
                device->InjectError(WGPUErrorType_Validation,
                                    "All objects must be from the same device.");
                return;
            }
        }

        auto self = reinterpret_cast<RenderPassEncoder*>(cSelf);
        Device* device = self->device;
        RenderPassEncoderDrawIndirectCmd cmd;

        cmd.self = cSelf;


        cmd.indirectBuffer = indirectBuffer;
        cmd.indirectOffset = indirectOffset;

        device->GetClient()->SerializeCommand(cmd);

    }

    void ClientRenderPassEncoderEndPass(WGPURenderPassEncoder cSelf) {

        auto self = reinterpret_cast<RenderPassEncoder*>(cSelf);
        Device* device = self->device;
        RenderPassEncoderEndPassCmd cmd;

        cmd.self = cSelf;



        device->GetClient()->SerializeCommand(cmd);

    }

    void ClientRenderPassEncoderExecuteBundles(WGPURenderPassEncoder cSelf, uint32_t bundlesCount, WGPURenderBundle const * bundles) {
        {
            bool sameDevice = true;
            auto self = reinterpret_cast<RenderPassEncoder*>(cSelf);
            Device* device = self->device;
            DAWN_UNUSED(device);

            do {
                {
                    if (!DeviceMatches(device, bundles, bundlesCount)) {
                        sameDevice = false;
                        break;
                    }
                }
            } while (false);

            if (DAWN_UNLIKELY(!sameDevice)) {
                device->InjectError(WGPUErrorType_Validation,
                                    "All objects must be from the same device.");
                return;
            }
        }

        auto self = reinterpret_cast<RenderPassEncoder*>(cSelf);
        Device* device = self->device;
        RenderPassEncoderExecuteBundlesCmd cmd;

        cmd.self = cSelf;


        cmd.bundlesCount = bundlesCount;
        cmd.bundles = bundles;

        device->GetClient()->SerializeCommand(cmd);

    }

    void ClientRenderPassEncoderInsertDebugMarker(WGPURenderPassEncoder cSelf, char const * markerLabel) {
        {
            bool sameDevice = true;
            auto self = reinterpret_cast<RenderPassEncoder*>(cSelf);
            Device* device = self->device;
            DAWN_UNUSED(device);

            do {
            } while (false);

            if (DAWN_UNLIKELY(!sameDevice)) {
                device->InjectError(WGPUErrorType_Validation,
                                    "All objects must be from the same device.");
                return;
            }
        }

        auto self = reinterpret_cast<RenderPassEncoder*>(cSelf);
        Device* device = self->device;
        RenderPassEncoderInsertDebugMarkerCmd cmd;

        cmd.self = cSelf;


        cmd.markerLabel = markerLabel;

        device->GetClient()->SerializeCommand(cmd);

    }

    void ClientRenderPassEncoderPopDebugGroup(WGPURenderPassEncoder cSelf) {

        auto self = reinterpret_cast<RenderPassEncoder*>(cSelf);
        Device* device = self->device;
        RenderPassEncoderPopDebugGroupCmd cmd;

        cmd.self = cSelf;



        device->GetClient()->SerializeCommand(cmd);

    }

    void ClientRenderPassEncoderPushDebugGroup(WGPURenderPassEncoder cSelf, char const * groupLabel) {
        {
            bool sameDevice = true;
            auto self = reinterpret_cast<RenderPassEncoder*>(cSelf);
            Device* device = self->device;
            DAWN_UNUSED(device);

            do {
            } while (false);

            if (DAWN_UNLIKELY(!sameDevice)) {
                device->InjectError(WGPUErrorType_Validation,
                                    "All objects must be from the same device.");
                return;
            }
        }

        auto self = reinterpret_cast<RenderPassEncoder*>(cSelf);
        Device* device = self->device;
        RenderPassEncoderPushDebugGroupCmd cmd;

        cmd.self = cSelf;


        cmd.groupLabel = groupLabel;

        device->GetClient()->SerializeCommand(cmd);

    }

    void ClientRenderPassEncoderSetBindGroup(WGPURenderPassEncoder cSelf, uint32_t groupIndex, WGPUBindGroup group, uint32_t dynamicOffsetCount, uint32_t const * dynamicOffsets) {
        {
            bool sameDevice = true;
            auto self = reinterpret_cast<RenderPassEncoder*>(cSelf);
            Device* device = self->device;
            DAWN_UNUSED(device);

            do {
                {
                    if (!DeviceMatches(device, group)) {
                        sameDevice = false;
                        break;
                    }
                }
            } while (false);

            if (DAWN_UNLIKELY(!sameDevice)) {
                device->InjectError(WGPUErrorType_Validation,
                                    "All objects must be from the same device.");
                return;
            }
        }

        auto self = reinterpret_cast<RenderPassEncoder*>(cSelf);
        Device* device = self->device;
        RenderPassEncoderSetBindGroupCmd cmd;

        cmd.self = cSelf;


        cmd.groupIndex = groupIndex;
        cmd.group = group;
        cmd.dynamicOffsetCount = dynamicOffsetCount;
        cmd.dynamicOffsets = dynamicOffsets;

        device->GetClient()->SerializeCommand(cmd);

    }

    void ClientRenderPassEncoderSetBlendColor(WGPURenderPassEncoder cSelf, WGPUColor const * color) {
        {
            bool sameDevice = true;
            auto self = reinterpret_cast<RenderPassEncoder*>(cSelf);
            Device* device = self->device;
            DAWN_UNUSED(device);

            do {
            } while (false);

            if (DAWN_UNLIKELY(!sameDevice)) {
                device->InjectError(WGPUErrorType_Validation,
                                    "All objects must be from the same device.");
                return;
            }
        }

        auto self = reinterpret_cast<RenderPassEncoder*>(cSelf);
        Device* device = self->device;
        RenderPassEncoderSetBlendColorCmd cmd;

        cmd.self = cSelf;


        cmd.color = color;

        device->GetClient()->SerializeCommand(cmd);

    }

    void ClientRenderPassEncoderSetIndexBuffer(WGPURenderPassEncoder cSelf, WGPUBuffer buffer, uint64_t offset, uint64_t size) {
        {
            bool sameDevice = true;
            auto self = reinterpret_cast<RenderPassEncoder*>(cSelf);
            Device* device = self->device;
            DAWN_UNUSED(device);

            do {
                {
                    if (!DeviceMatches(device, buffer)) {
                        sameDevice = false;
                        break;
                    }
                }
            } while (false);

            if (DAWN_UNLIKELY(!sameDevice)) {
                device->InjectError(WGPUErrorType_Validation,
                                    "All objects must be from the same device.");
                return;
            }
        }

        auto self = reinterpret_cast<RenderPassEncoder*>(cSelf);
        Device* device = self->device;
        RenderPassEncoderSetIndexBufferCmd cmd;

        cmd.self = cSelf;


        cmd.buffer = buffer;
        cmd.offset = offset;
        cmd.size = size;

        device->GetClient()->SerializeCommand(cmd);

    }

    void ClientRenderPassEncoderSetIndexBufferWithFormat(WGPURenderPassEncoder cSelf, WGPUBuffer buffer, WGPUIndexFormat format, uint64_t offset, uint64_t size) {
        {
            bool sameDevice = true;
            auto self = reinterpret_cast<RenderPassEncoder*>(cSelf);
            Device* device = self->device;
            DAWN_UNUSED(device);

            do {
                {
                    if (!DeviceMatches(device, buffer)) {
                        sameDevice = false;
                        break;
                    }
                }
            } while (false);

            if (DAWN_UNLIKELY(!sameDevice)) {
                device->InjectError(WGPUErrorType_Validation,
                                    "All objects must be from the same device.");
                return;
            }
        }

        auto self = reinterpret_cast<RenderPassEncoder*>(cSelf);
        Device* device = self->device;
        RenderPassEncoderSetIndexBufferWithFormatCmd cmd;

        cmd.self = cSelf;


        cmd.buffer = buffer;
        cmd.format = format;
        cmd.offset = offset;
        cmd.size = size;

        device->GetClient()->SerializeCommand(cmd);

    }

    void ClientRenderPassEncoderSetPipeline(WGPURenderPassEncoder cSelf, WGPURenderPipeline pipeline) {
        {
            bool sameDevice = true;
            auto self = reinterpret_cast<RenderPassEncoder*>(cSelf);
            Device* device = self->device;
            DAWN_UNUSED(device);

            do {
                {
                    if (!DeviceMatches(device, pipeline)) {
                        sameDevice = false;
                        break;
                    }
                }
            } while (false);

            if (DAWN_UNLIKELY(!sameDevice)) {
                device->InjectError(WGPUErrorType_Validation,
                                    "All objects must be from the same device.");
                return;
            }
        }

        auto self = reinterpret_cast<RenderPassEncoder*>(cSelf);
        Device* device = self->device;
        RenderPassEncoderSetPipelineCmd cmd;

        cmd.self = cSelf;


        cmd.pipeline = pipeline;

        device->GetClient()->SerializeCommand(cmd);

    }

    void ClientRenderPassEncoderSetScissorRect(WGPURenderPassEncoder cSelf, uint32_t x, uint32_t y, uint32_t width, uint32_t height) {
        {
            bool sameDevice = true;
            auto self = reinterpret_cast<RenderPassEncoder*>(cSelf);
            Device* device = self->device;
            DAWN_UNUSED(device);

            do {
            } while (false);

            if (DAWN_UNLIKELY(!sameDevice)) {
                device->InjectError(WGPUErrorType_Validation,
                                    "All objects must be from the same device.");
                return;
            }
        }

        auto self = reinterpret_cast<RenderPassEncoder*>(cSelf);
        Device* device = self->device;
        RenderPassEncoderSetScissorRectCmd cmd;

        cmd.self = cSelf;


        cmd.x = x;
        cmd.y = y;
        cmd.width = width;
        cmd.height = height;

        device->GetClient()->SerializeCommand(cmd);

    }

    void ClientRenderPassEncoderSetStencilReference(WGPURenderPassEncoder cSelf, uint32_t reference) {
        {
            bool sameDevice = true;
            auto self = reinterpret_cast<RenderPassEncoder*>(cSelf);
            Device* device = self->device;
            DAWN_UNUSED(device);

            do {
            } while (false);

            if (DAWN_UNLIKELY(!sameDevice)) {
                device->InjectError(WGPUErrorType_Validation,
                                    "All objects must be from the same device.");
                return;
            }
        }

        auto self = reinterpret_cast<RenderPassEncoder*>(cSelf);
        Device* device = self->device;
        RenderPassEncoderSetStencilReferenceCmd cmd;

        cmd.self = cSelf;


        cmd.reference = reference;

        device->GetClient()->SerializeCommand(cmd);

    }

    void ClientRenderPassEncoderSetVertexBuffer(WGPURenderPassEncoder cSelf, uint32_t slot, WGPUBuffer buffer, uint64_t offset, uint64_t size) {
        {
            bool sameDevice = true;
            auto self = reinterpret_cast<RenderPassEncoder*>(cSelf);
            Device* device = self->device;
            DAWN_UNUSED(device);

            do {
                {
                    if (!DeviceMatches(device, buffer)) {
                        sameDevice = false;
                        break;
                    }
                }
            } while (false);

            if (DAWN_UNLIKELY(!sameDevice)) {
                device->InjectError(WGPUErrorType_Validation,
                                    "All objects must be from the same device.");
                return;
            }
        }

        auto self = reinterpret_cast<RenderPassEncoder*>(cSelf);
        Device* device = self->device;
        RenderPassEncoderSetVertexBufferCmd cmd;

        cmd.self = cSelf;


        cmd.slot = slot;
        cmd.buffer = buffer;
        cmd.offset = offset;
        cmd.size = size;

        device->GetClient()->SerializeCommand(cmd);

    }

    void ClientRenderPassEncoderSetViewport(WGPURenderPassEncoder cSelf, float x, float y, float width, float height, float minDepth, float maxDepth) {
        {
            bool sameDevice = true;
            auto self = reinterpret_cast<RenderPassEncoder*>(cSelf);
            Device* device = self->device;
            DAWN_UNUSED(device);

            do {
            } while (false);

            if (DAWN_UNLIKELY(!sameDevice)) {
                device->InjectError(WGPUErrorType_Validation,
                                    "All objects must be from the same device.");
                return;
            }
        }

        auto self = reinterpret_cast<RenderPassEncoder*>(cSelf);
        Device* device = self->device;
        RenderPassEncoderSetViewportCmd cmd;

        cmd.self = cSelf;


        cmd.x = x;
        cmd.y = y;
        cmd.width = width;
        cmd.height = height;
        cmd.minDepth = minDepth;
        cmd.maxDepth = maxDepth;

        device->GetClient()->SerializeCommand(cmd);

    }

    void ClientRenderPassEncoderWriteTimestamp(WGPURenderPassEncoder cSelf, WGPUQuerySet querySet, uint32_t queryIndex) {
        {
            bool sameDevice = true;
            auto self = reinterpret_cast<RenderPassEncoder*>(cSelf);
            Device* device = self->device;
            DAWN_UNUSED(device);

            do {
                {
                    if (!DeviceMatches(device, querySet)) {
                        sameDevice = false;
                        break;
                    }
                }
            } while (false);

            if (DAWN_UNLIKELY(!sameDevice)) {
                device->InjectError(WGPUErrorType_Validation,
                                    "All objects must be from the same device.");
                return;
            }
        }

        auto self = reinterpret_cast<RenderPassEncoder*>(cSelf);
        Device* device = self->device;
        RenderPassEncoderWriteTimestampCmd cmd;

        cmd.self = cSelf;


        cmd.querySet = querySet;
        cmd.queryIndex = queryIndex;

        device->GetClient()->SerializeCommand(cmd);

    }

    void ClientRenderPassEncoderRelease(WGPURenderPassEncoder cObj) {
        RenderPassEncoder* obj = reinterpret_cast<RenderPassEncoder*>(cObj);
        obj->refcount --;

        if (obj->refcount > 0) {
            return;
        }

        DestroyObjectCmd cmd;
        cmd.objectType = ObjectType::RenderPassEncoder;
        cmd.objectId = obj->id;

        obj->device->GetClient()->SerializeCommand(cmd);
        obj->device->GetClient()->RenderPassEncoderAllocator().Free(obj);
    }

    void ClientRenderPassEncoderReference(WGPURenderPassEncoder cObj) {
        RenderPassEncoder* obj = reinterpret_cast<RenderPassEncoder*>(cObj);
        obj->refcount ++;
    }


    WGPUBindGroupLayout ClientRenderPipelineGetBindGroupLayout(WGPURenderPipeline cSelf, uint32_t groupIndex) {
        {
            bool sameDevice = true;
            auto self = reinterpret_cast<RenderPipeline*>(cSelf);
            Device* device = self->device;
            DAWN_UNUSED(device);

            do {
            } while (false);

            if (DAWN_UNLIKELY(!sameDevice)) {
                device->InjectError(WGPUErrorType_Validation,
                                    "All objects must be from the same device.");
                // Allocate an object without registering it on the server. This is backed by a real allocation on
                // the client so commands can be sent with it. But because it's not allocated on the server, it will
                // be a fatal error to use it.
                auto self = reinterpret_cast<RenderPipeline*>(cSelf);
                auto* allocation = self->device->GetClient()->BindGroupLayoutAllocator().New(self->device);
                return reinterpret_cast<WGPUBindGroupLayout>(allocation->object.get());
            }
        }

        auto self = reinterpret_cast<RenderPipeline*>(cSelf);
        Device* device = self->device;
        RenderPipelineGetBindGroupLayoutCmd cmd;

        cmd.self = cSelf;

        auto* allocation = self->device->GetClient()->BindGroupLayoutAllocator().New(self->device);
        cmd.result = ObjectHandle{allocation->object->id, allocation->generation};

        cmd.groupIndex = groupIndex;

        device->GetClient()->SerializeCommand(cmd);

        return reinterpret_cast<WGPUBindGroupLayout>(allocation->object.get());
    }

    void ClientRenderPipelineRelease(WGPURenderPipeline cObj) {
        RenderPipeline* obj = reinterpret_cast<RenderPipeline*>(cObj);
        obj->refcount --;

        if (obj->refcount > 0) {
            return;
        }

        DestroyObjectCmd cmd;
        cmd.objectType = ObjectType::RenderPipeline;
        cmd.objectId = obj->id;

        obj->device->GetClient()->SerializeCommand(cmd);
        obj->device->GetClient()->RenderPipelineAllocator().Free(obj);
    }

    void ClientRenderPipelineReference(WGPURenderPipeline cObj) {
        RenderPipeline* obj = reinterpret_cast<RenderPipeline*>(cObj);
        obj->refcount ++;
    }


    void ClientSamplerRelease(WGPUSampler cObj) {
        Sampler* obj = reinterpret_cast<Sampler*>(cObj);
        obj->refcount --;

        if (obj->refcount > 0) {
            return;
        }

        DestroyObjectCmd cmd;
        cmd.objectType = ObjectType::Sampler;
        cmd.objectId = obj->id;

        obj->device->GetClient()->SerializeCommand(cmd);
        obj->device->GetClient()->SamplerAllocator().Free(obj);
    }

    void ClientSamplerReference(WGPUSampler cObj) {
        Sampler* obj = reinterpret_cast<Sampler*>(cObj);
        obj->refcount ++;
    }


    void ClientShaderModuleRelease(WGPUShaderModule cObj) {
        ShaderModule* obj = reinterpret_cast<ShaderModule*>(cObj);
        obj->refcount --;

        if (obj->refcount > 0) {
            return;
        }

        DestroyObjectCmd cmd;
        cmd.objectType = ObjectType::ShaderModule;
        cmd.objectId = obj->id;

        obj->device->GetClient()->SerializeCommand(cmd);
        obj->device->GetClient()->ShaderModuleAllocator().Free(obj);
    }

    void ClientShaderModuleReference(WGPUShaderModule cObj) {
        ShaderModule* obj = reinterpret_cast<ShaderModule*>(cObj);
        obj->refcount ++;
    }


    void ClientSurfaceRelease(WGPUSurface cObj) {
        Surface* obj = reinterpret_cast<Surface*>(cObj);
        obj->refcount --;

        if (obj->refcount > 0) {
            return;
        }

        DestroyObjectCmd cmd;
        cmd.objectType = ObjectType::Surface;
        cmd.objectId = obj->id;

        obj->device->GetClient()->SerializeCommand(cmd);
        obj->device->GetClient()->SurfaceAllocator().Free(obj);
    }

    void ClientSurfaceReference(WGPUSurface cObj) {
        Surface* obj = reinterpret_cast<Surface*>(cObj);
        obj->refcount ++;
    }


    void ClientSwapChainConfigure(WGPUSwapChain cSelf, WGPUTextureFormat format, WGPUTextureUsageFlags allowedUsage, uint32_t width, uint32_t height) {
        {
            bool sameDevice = true;
            auto self = reinterpret_cast<SwapChain*>(cSelf);
            Device* device = self->device;
            DAWN_UNUSED(device);

            do {
            } while (false);

            if (DAWN_UNLIKELY(!sameDevice)) {
                device->InjectError(WGPUErrorType_Validation,
                                    "All objects must be from the same device.");
                return;
            }
        }

        auto self = reinterpret_cast<SwapChain*>(cSelf);
        Device* device = self->device;
        SwapChainConfigureCmd cmd;

        cmd.self = cSelf;


        cmd.format = format;
        cmd.allowedUsage = allowedUsage;
        cmd.width = width;
        cmd.height = height;

        device->GetClient()->SerializeCommand(cmd);

    }

    WGPUTextureView ClientSwapChainGetCurrentTextureView(WGPUSwapChain cSelf) {

        auto self = reinterpret_cast<SwapChain*>(cSelf);
        Device* device = self->device;
        SwapChainGetCurrentTextureViewCmd cmd;

        cmd.self = cSelf;

        auto* allocation = self->device->GetClient()->TextureViewAllocator().New(self->device);
        cmd.result = ObjectHandle{allocation->object->id, allocation->generation};


        device->GetClient()->SerializeCommand(cmd);

        return reinterpret_cast<WGPUTextureView>(allocation->object.get());
    }

    void ClientSwapChainPresent(WGPUSwapChain cSelf) {

        auto self = reinterpret_cast<SwapChain*>(cSelf);
        Device* device = self->device;
        SwapChainPresentCmd cmd;

        cmd.self = cSelf;



        device->GetClient()->SerializeCommand(cmd);

    }

    void ClientSwapChainRelease(WGPUSwapChain cObj) {
        SwapChain* obj = reinterpret_cast<SwapChain*>(cObj);
        obj->refcount --;

        if (obj->refcount > 0) {
            return;
        }

        DestroyObjectCmd cmd;
        cmd.objectType = ObjectType::SwapChain;
        cmd.objectId = obj->id;

        obj->device->GetClient()->SerializeCommand(cmd);
        obj->device->GetClient()->SwapChainAllocator().Free(obj);
    }

    void ClientSwapChainReference(WGPUSwapChain cObj) {
        SwapChain* obj = reinterpret_cast<SwapChain*>(cObj);
        obj->refcount ++;
    }


    WGPUTextureView ClientTextureCreateView(WGPUTexture cSelf, WGPUTextureViewDescriptor const * descriptor) {
        {
            bool sameDevice = true;
            auto self = reinterpret_cast<Texture*>(cSelf);
            Device* device = self->device;
            DAWN_UNUSED(device);

            do {
                if (descriptor != nullptr)
                {
                    if (!DeviceMatches(device, descriptor, 1)) {
                        sameDevice = false;
                        break;
                    }
                }
            } while (false);

            if (DAWN_UNLIKELY(!sameDevice)) {
                device->InjectError(WGPUErrorType_Validation,
                                    "All objects must be from the same device.");
                // Allocate an object without registering it on the server. This is backed by a real allocation on
                // the client so commands can be sent with it. But because it's not allocated on the server, it will
                // be a fatal error to use it.
                auto self = reinterpret_cast<Texture*>(cSelf);
                auto* allocation = self->device->GetClient()->TextureViewAllocator().New(self->device);
                return reinterpret_cast<WGPUTextureView>(allocation->object.get());
            }
        }

        auto self = reinterpret_cast<Texture*>(cSelf);
        Device* device = self->device;
        TextureCreateViewCmd cmd;

        cmd.self = cSelf;

        auto* allocation = self->device->GetClient()->TextureViewAllocator().New(self->device);
        cmd.result = ObjectHandle{allocation->object->id, allocation->generation};

        cmd.descriptor = descriptor;

        device->GetClient()->SerializeCommand(cmd);

        return reinterpret_cast<WGPUTextureView>(allocation->object.get());
    }

    void ClientTextureDestroy(WGPUTexture cSelf) {

        auto self = reinterpret_cast<Texture*>(cSelf);
        Device* device = self->device;
        TextureDestroyCmd cmd;

        cmd.self = cSelf;



        device->GetClient()->SerializeCommand(cmd);

    }

    void ClientTextureRelease(WGPUTexture cObj) {
        Texture* obj = reinterpret_cast<Texture*>(cObj);
        obj->refcount --;

        if (obj->refcount > 0) {
            return;
        }

        DestroyObjectCmd cmd;
        cmd.objectType = ObjectType::Texture;
        cmd.objectId = obj->id;

        obj->device->GetClient()->SerializeCommand(cmd);
        obj->device->GetClient()->TextureAllocator().Free(obj);
    }

    void ClientTextureReference(WGPUTexture cObj) {
        Texture* obj = reinterpret_cast<Texture*>(cObj);
        obj->refcount ++;
    }


    void ClientTextureViewRelease(WGPUTextureView cObj) {
        TextureView* obj = reinterpret_cast<TextureView*>(cObj);
        obj->refcount --;

        if (obj->refcount > 0) {
            return;
        }

        DestroyObjectCmd cmd;
        cmd.objectType = ObjectType::TextureView;
        cmd.objectId = obj->id;

        obj->device->GetClient()->SerializeCommand(cmd);
        obj->device->GetClient()->TextureViewAllocator().Free(obj);
    }

    void ClientTextureViewReference(WGPUTextureView cObj) {
        TextureView* obj = reinterpret_cast<TextureView*>(cObj);
        obj->refcount ++;
    }

    namespace {
        WGPUInstance ClientCreateInstance(WGPUInstanceDescriptor const* descriptor) {
            UNREACHABLE();
            return nullptr;
        }

        void ClientDeviceReference(WGPUDevice) {
        }

        void ClientDeviceRelease(WGPUDevice) {
        }

        struct ProcEntry {
            WGPUProc proc;
            const char* name;
        };
        static const ProcEntry sProcMap[] = {
            { reinterpret_cast<WGPUProc>(ClientBindGroupLayoutReference), "wgpuBindGroupLayoutReference" },
            { reinterpret_cast<WGPUProc>(ClientBindGroupLayoutRelease), "wgpuBindGroupLayoutRelease" },
            { reinterpret_cast<WGPUProc>(ClientBindGroupReference), "wgpuBindGroupReference" },
            { reinterpret_cast<WGPUProc>(ClientBindGroupRelease), "wgpuBindGroupRelease" },
            { reinterpret_cast<WGPUProc>(ClientBufferDestroy), "wgpuBufferDestroy" },
            { reinterpret_cast<WGPUProc>(ClientBufferGetConstMappedRange), "wgpuBufferGetConstMappedRange" },
            { reinterpret_cast<WGPUProc>(ClientBufferGetMappedRange), "wgpuBufferGetMappedRange" },
            { reinterpret_cast<WGPUProc>(ClientBufferMapAsync), "wgpuBufferMapAsync" },
            { reinterpret_cast<WGPUProc>(ClientBufferReference), "wgpuBufferReference" },
            { reinterpret_cast<WGPUProc>(ClientBufferRelease), "wgpuBufferRelease" },
            { reinterpret_cast<WGPUProc>(ClientBufferUnmap), "wgpuBufferUnmap" },
            { reinterpret_cast<WGPUProc>(ClientCommandBufferReference), "wgpuCommandBufferReference" },
            { reinterpret_cast<WGPUProc>(ClientCommandBufferRelease), "wgpuCommandBufferRelease" },
            { reinterpret_cast<WGPUProc>(ClientCommandEncoderBeginComputePass), "wgpuCommandEncoderBeginComputePass" },
            { reinterpret_cast<WGPUProc>(ClientCommandEncoderBeginRenderPass), "wgpuCommandEncoderBeginRenderPass" },
            { reinterpret_cast<WGPUProc>(ClientCommandEncoderCopyBufferToBuffer), "wgpuCommandEncoderCopyBufferToBuffer" },
            { reinterpret_cast<WGPUProc>(ClientCommandEncoderCopyBufferToTexture), "wgpuCommandEncoderCopyBufferToTexture" },
            { reinterpret_cast<WGPUProc>(ClientCommandEncoderCopyTextureToBuffer), "wgpuCommandEncoderCopyTextureToBuffer" },
            { reinterpret_cast<WGPUProc>(ClientCommandEncoderCopyTextureToTexture), "wgpuCommandEncoderCopyTextureToTexture" },
            { reinterpret_cast<WGPUProc>(ClientCommandEncoderFinish), "wgpuCommandEncoderFinish" },
            { reinterpret_cast<WGPUProc>(ClientCommandEncoderInsertDebugMarker), "wgpuCommandEncoderInsertDebugMarker" },
            { reinterpret_cast<WGPUProc>(ClientCommandEncoderPopDebugGroup), "wgpuCommandEncoderPopDebugGroup" },
            { reinterpret_cast<WGPUProc>(ClientCommandEncoderPushDebugGroup), "wgpuCommandEncoderPushDebugGroup" },
            { reinterpret_cast<WGPUProc>(ClientCommandEncoderReference), "wgpuCommandEncoderReference" },
            { reinterpret_cast<WGPUProc>(ClientCommandEncoderRelease), "wgpuCommandEncoderRelease" },
            { reinterpret_cast<WGPUProc>(ClientCommandEncoderResolveQuerySet), "wgpuCommandEncoderResolveQuerySet" },
            { reinterpret_cast<WGPUProc>(ClientCommandEncoderWriteTimestamp), "wgpuCommandEncoderWriteTimestamp" },
            { reinterpret_cast<WGPUProc>(ClientComputePassEncoderDispatch), "wgpuComputePassEncoderDispatch" },
            { reinterpret_cast<WGPUProc>(ClientComputePassEncoderDispatchIndirect), "wgpuComputePassEncoderDispatchIndirect" },
            { reinterpret_cast<WGPUProc>(ClientComputePassEncoderEndPass), "wgpuComputePassEncoderEndPass" },
            { reinterpret_cast<WGPUProc>(ClientComputePassEncoderInsertDebugMarker), "wgpuComputePassEncoderInsertDebugMarker" },
            { reinterpret_cast<WGPUProc>(ClientComputePassEncoderPopDebugGroup), "wgpuComputePassEncoderPopDebugGroup" },
            { reinterpret_cast<WGPUProc>(ClientComputePassEncoderPushDebugGroup), "wgpuComputePassEncoderPushDebugGroup" },
            { reinterpret_cast<WGPUProc>(ClientComputePassEncoderReference), "wgpuComputePassEncoderReference" },
            { reinterpret_cast<WGPUProc>(ClientComputePassEncoderRelease), "wgpuComputePassEncoderRelease" },
            { reinterpret_cast<WGPUProc>(ClientComputePassEncoderSetBindGroup), "wgpuComputePassEncoderSetBindGroup" },
            { reinterpret_cast<WGPUProc>(ClientComputePassEncoderSetPipeline), "wgpuComputePassEncoderSetPipeline" },
            { reinterpret_cast<WGPUProc>(ClientComputePassEncoderWriteTimestamp), "wgpuComputePassEncoderWriteTimestamp" },
            { reinterpret_cast<WGPUProc>(ClientComputePipelineGetBindGroupLayout), "wgpuComputePipelineGetBindGroupLayout" },
            { reinterpret_cast<WGPUProc>(ClientComputePipelineReference), "wgpuComputePipelineReference" },
            { reinterpret_cast<WGPUProc>(ClientComputePipelineRelease), "wgpuComputePipelineRelease" },
            { reinterpret_cast<WGPUProc>(ClientDeviceCreateBindGroup), "wgpuDeviceCreateBindGroup" },
            { reinterpret_cast<WGPUProc>(ClientDeviceCreateBindGroupLayout), "wgpuDeviceCreateBindGroupLayout" },
            { reinterpret_cast<WGPUProc>(ClientDeviceCreateBuffer), "wgpuDeviceCreateBuffer" },
            { reinterpret_cast<WGPUProc>(ClientDeviceCreateCommandEncoder), "wgpuDeviceCreateCommandEncoder" },
            { reinterpret_cast<WGPUProc>(ClientDeviceCreateComputePipeline), "wgpuDeviceCreateComputePipeline" },
            { reinterpret_cast<WGPUProc>(ClientDeviceCreateErrorBuffer), "wgpuDeviceCreateErrorBuffer" },
            { reinterpret_cast<WGPUProc>(ClientDeviceCreatePipelineLayout), "wgpuDeviceCreatePipelineLayout" },
            { reinterpret_cast<WGPUProc>(ClientDeviceCreateQuerySet), "wgpuDeviceCreateQuerySet" },
            { reinterpret_cast<WGPUProc>(ClientDeviceCreateReadyComputePipeline), "wgpuDeviceCreateReadyComputePipeline" },
            { reinterpret_cast<WGPUProc>(ClientDeviceCreateReadyRenderPipeline), "wgpuDeviceCreateReadyRenderPipeline" },
            { reinterpret_cast<WGPUProc>(ClientDeviceCreateRenderBundleEncoder), "wgpuDeviceCreateRenderBundleEncoder" },
            { reinterpret_cast<WGPUProc>(ClientDeviceCreateRenderPipeline), "wgpuDeviceCreateRenderPipeline" },
            { reinterpret_cast<WGPUProc>(ClientDeviceCreateSampler), "wgpuDeviceCreateSampler" },
            { reinterpret_cast<WGPUProc>(ClientDeviceCreateShaderModule), "wgpuDeviceCreateShaderModule" },
            { reinterpret_cast<WGPUProc>(ClientDeviceCreateSwapChain), "wgpuDeviceCreateSwapChain" },
            { reinterpret_cast<WGPUProc>(ClientDeviceCreateTexture), "wgpuDeviceCreateTexture" },
            { reinterpret_cast<WGPUProc>(ClientDeviceGetDefaultQueue), "wgpuDeviceGetDefaultQueue" },
            { reinterpret_cast<WGPUProc>(ClientDeviceInjectError), "wgpuDeviceInjectError" },
            { reinterpret_cast<WGPUProc>(ClientDeviceLoseForTesting), "wgpuDeviceLoseForTesting" },
            { reinterpret_cast<WGPUProc>(ClientDevicePopErrorScope), "wgpuDevicePopErrorScope" },
            { reinterpret_cast<WGPUProc>(ClientDevicePushErrorScope), "wgpuDevicePushErrorScope" },
            { reinterpret_cast<WGPUProc>(ClientDeviceReference), "wgpuDeviceReference" },
            { reinterpret_cast<WGPUProc>(ClientDeviceRelease), "wgpuDeviceRelease" },
            { reinterpret_cast<WGPUProc>(ClientDeviceSetDeviceLostCallback), "wgpuDeviceSetDeviceLostCallback" },
            { reinterpret_cast<WGPUProc>(ClientDeviceSetUncapturedErrorCallback), "wgpuDeviceSetUncapturedErrorCallback" },
            { reinterpret_cast<WGPUProc>(ClientDeviceTick), "wgpuDeviceTick" },
            { reinterpret_cast<WGPUProc>(ClientFenceGetCompletedValue), "wgpuFenceGetCompletedValue" },
            { reinterpret_cast<WGPUProc>(ClientFenceOnCompletion), "wgpuFenceOnCompletion" },
            { reinterpret_cast<WGPUProc>(ClientFenceReference), "wgpuFenceReference" },
            { reinterpret_cast<WGPUProc>(ClientFenceRelease), "wgpuFenceRelease" },
            { reinterpret_cast<WGPUProc>(ClientInstanceCreateSurface), "wgpuInstanceCreateSurface" },
            { reinterpret_cast<WGPUProc>(ClientInstanceReference), "wgpuInstanceReference" },
            { reinterpret_cast<WGPUProc>(ClientInstanceRelease), "wgpuInstanceRelease" },
            { reinterpret_cast<WGPUProc>(ClientPipelineLayoutReference), "wgpuPipelineLayoutReference" },
            { reinterpret_cast<WGPUProc>(ClientPipelineLayoutRelease), "wgpuPipelineLayoutRelease" },
            { reinterpret_cast<WGPUProc>(ClientQuerySetDestroy), "wgpuQuerySetDestroy" },
            { reinterpret_cast<WGPUProc>(ClientQuerySetReference), "wgpuQuerySetReference" },
            { reinterpret_cast<WGPUProc>(ClientQuerySetRelease), "wgpuQuerySetRelease" },
            { reinterpret_cast<WGPUProc>(ClientQueueCreateFence), "wgpuQueueCreateFence" },
            { reinterpret_cast<WGPUProc>(ClientQueueReference), "wgpuQueueReference" },
            { reinterpret_cast<WGPUProc>(ClientQueueRelease), "wgpuQueueRelease" },
            { reinterpret_cast<WGPUProc>(ClientQueueSignal), "wgpuQueueSignal" },
            { reinterpret_cast<WGPUProc>(ClientQueueSubmit), "wgpuQueueSubmit" },
            { reinterpret_cast<WGPUProc>(ClientQueueWriteBuffer), "wgpuQueueWriteBuffer" },
            { reinterpret_cast<WGPUProc>(ClientQueueWriteTexture), "wgpuQueueWriteTexture" },
            { reinterpret_cast<WGPUProc>(ClientRenderBundleEncoderDraw), "wgpuRenderBundleEncoderDraw" },
            { reinterpret_cast<WGPUProc>(ClientRenderBundleEncoderDrawIndexed), "wgpuRenderBundleEncoderDrawIndexed" },
            { reinterpret_cast<WGPUProc>(ClientRenderBundleEncoderDrawIndexedIndirect), "wgpuRenderBundleEncoderDrawIndexedIndirect" },
            { reinterpret_cast<WGPUProc>(ClientRenderBundleEncoderDrawIndirect), "wgpuRenderBundleEncoderDrawIndirect" },
            { reinterpret_cast<WGPUProc>(ClientRenderBundleEncoderFinish), "wgpuRenderBundleEncoderFinish" },
            { reinterpret_cast<WGPUProc>(ClientRenderBundleEncoderInsertDebugMarker), "wgpuRenderBundleEncoderInsertDebugMarker" },
            { reinterpret_cast<WGPUProc>(ClientRenderBundleEncoderPopDebugGroup), "wgpuRenderBundleEncoderPopDebugGroup" },
            { reinterpret_cast<WGPUProc>(ClientRenderBundleEncoderPushDebugGroup), "wgpuRenderBundleEncoderPushDebugGroup" },
            { reinterpret_cast<WGPUProc>(ClientRenderBundleEncoderReference), "wgpuRenderBundleEncoderReference" },
            { reinterpret_cast<WGPUProc>(ClientRenderBundleEncoderRelease), "wgpuRenderBundleEncoderRelease" },
            { reinterpret_cast<WGPUProc>(ClientRenderBundleEncoderSetBindGroup), "wgpuRenderBundleEncoderSetBindGroup" },
            { reinterpret_cast<WGPUProc>(ClientRenderBundleEncoderSetIndexBuffer), "wgpuRenderBundleEncoderSetIndexBuffer" },
            { reinterpret_cast<WGPUProc>(ClientRenderBundleEncoderSetIndexBufferWithFormat), "wgpuRenderBundleEncoderSetIndexBufferWithFormat" },
            { reinterpret_cast<WGPUProc>(ClientRenderBundleEncoderSetPipeline), "wgpuRenderBundleEncoderSetPipeline" },
            { reinterpret_cast<WGPUProc>(ClientRenderBundleEncoderSetVertexBuffer), "wgpuRenderBundleEncoderSetVertexBuffer" },
            { reinterpret_cast<WGPUProc>(ClientRenderBundleReference), "wgpuRenderBundleReference" },
            { reinterpret_cast<WGPUProc>(ClientRenderBundleRelease), "wgpuRenderBundleRelease" },
            { reinterpret_cast<WGPUProc>(ClientRenderPassEncoderDraw), "wgpuRenderPassEncoderDraw" },
            { reinterpret_cast<WGPUProc>(ClientRenderPassEncoderDrawIndexed), "wgpuRenderPassEncoderDrawIndexed" },
            { reinterpret_cast<WGPUProc>(ClientRenderPassEncoderDrawIndexedIndirect), "wgpuRenderPassEncoderDrawIndexedIndirect" },
            { reinterpret_cast<WGPUProc>(ClientRenderPassEncoderDrawIndirect), "wgpuRenderPassEncoderDrawIndirect" },
            { reinterpret_cast<WGPUProc>(ClientRenderPassEncoderEndPass), "wgpuRenderPassEncoderEndPass" },
            { reinterpret_cast<WGPUProc>(ClientRenderPassEncoderExecuteBundles), "wgpuRenderPassEncoderExecuteBundles" },
            { reinterpret_cast<WGPUProc>(ClientRenderPassEncoderInsertDebugMarker), "wgpuRenderPassEncoderInsertDebugMarker" },
            { reinterpret_cast<WGPUProc>(ClientRenderPassEncoderPopDebugGroup), "wgpuRenderPassEncoderPopDebugGroup" },
            { reinterpret_cast<WGPUProc>(ClientRenderPassEncoderPushDebugGroup), "wgpuRenderPassEncoderPushDebugGroup" },
            { reinterpret_cast<WGPUProc>(ClientRenderPassEncoderReference), "wgpuRenderPassEncoderReference" },
            { reinterpret_cast<WGPUProc>(ClientRenderPassEncoderRelease), "wgpuRenderPassEncoderRelease" },
            { reinterpret_cast<WGPUProc>(ClientRenderPassEncoderSetBindGroup), "wgpuRenderPassEncoderSetBindGroup" },
            { reinterpret_cast<WGPUProc>(ClientRenderPassEncoderSetBlendColor), "wgpuRenderPassEncoderSetBlendColor" },
            { reinterpret_cast<WGPUProc>(ClientRenderPassEncoderSetIndexBuffer), "wgpuRenderPassEncoderSetIndexBuffer" },
            { reinterpret_cast<WGPUProc>(ClientRenderPassEncoderSetIndexBufferWithFormat), "wgpuRenderPassEncoderSetIndexBufferWithFormat" },
            { reinterpret_cast<WGPUProc>(ClientRenderPassEncoderSetPipeline), "wgpuRenderPassEncoderSetPipeline" },
            { reinterpret_cast<WGPUProc>(ClientRenderPassEncoderSetScissorRect), "wgpuRenderPassEncoderSetScissorRect" },
            { reinterpret_cast<WGPUProc>(ClientRenderPassEncoderSetStencilReference), "wgpuRenderPassEncoderSetStencilReference" },
            { reinterpret_cast<WGPUProc>(ClientRenderPassEncoderSetVertexBuffer), "wgpuRenderPassEncoderSetVertexBuffer" },
            { reinterpret_cast<WGPUProc>(ClientRenderPassEncoderSetViewport), "wgpuRenderPassEncoderSetViewport" },
            { reinterpret_cast<WGPUProc>(ClientRenderPassEncoderWriteTimestamp), "wgpuRenderPassEncoderWriteTimestamp" },
            { reinterpret_cast<WGPUProc>(ClientRenderPipelineGetBindGroupLayout), "wgpuRenderPipelineGetBindGroupLayout" },
            { reinterpret_cast<WGPUProc>(ClientRenderPipelineReference), "wgpuRenderPipelineReference" },
            { reinterpret_cast<WGPUProc>(ClientRenderPipelineRelease), "wgpuRenderPipelineRelease" },
            { reinterpret_cast<WGPUProc>(ClientSamplerReference), "wgpuSamplerReference" },
            { reinterpret_cast<WGPUProc>(ClientSamplerRelease), "wgpuSamplerRelease" },
            { reinterpret_cast<WGPUProc>(ClientShaderModuleReference), "wgpuShaderModuleReference" },
            { reinterpret_cast<WGPUProc>(ClientShaderModuleRelease), "wgpuShaderModuleRelease" },
            { reinterpret_cast<WGPUProc>(ClientSurfaceReference), "wgpuSurfaceReference" },
            { reinterpret_cast<WGPUProc>(ClientSurfaceRelease), "wgpuSurfaceRelease" },
            { reinterpret_cast<WGPUProc>(ClientSwapChainConfigure), "wgpuSwapChainConfigure" },
            { reinterpret_cast<WGPUProc>(ClientSwapChainGetCurrentTextureView), "wgpuSwapChainGetCurrentTextureView" },
            { reinterpret_cast<WGPUProc>(ClientSwapChainPresent), "wgpuSwapChainPresent" },
            { reinterpret_cast<WGPUProc>(ClientSwapChainReference), "wgpuSwapChainReference" },
            { reinterpret_cast<WGPUProc>(ClientSwapChainRelease), "wgpuSwapChainRelease" },
            { reinterpret_cast<WGPUProc>(ClientTextureCreateView), "wgpuTextureCreateView" },
            { reinterpret_cast<WGPUProc>(ClientTextureDestroy), "wgpuTextureDestroy" },
            { reinterpret_cast<WGPUProc>(ClientTextureReference), "wgpuTextureReference" },
            { reinterpret_cast<WGPUProc>(ClientTextureRelease), "wgpuTextureRelease" },
            { reinterpret_cast<WGPUProc>(ClientTextureViewReference), "wgpuTextureViewReference" },
            { reinterpret_cast<WGPUProc>(ClientTextureViewRelease), "wgpuTextureViewRelease" },
        };
        static constexpr size_t sProcMapSize = sizeof(sProcMap) / sizeof(sProcMap[0]);
    }  // anonymous namespace

    WGPUProc ClientGetProcAddress(WGPUDevice, const char* procName) {
        if (procName == nullptr) {
            return nullptr;
        }

        const ProcEntry* entry = std::lower_bound(&sProcMap[0], &sProcMap[sProcMapSize], procName,
            [](const ProcEntry &a, const char *b) -> bool {
                return strcmp(a.name, b) < 0;
            }
        );

        if (entry != &sProcMap[sProcMapSize] && strcmp(entry->name, procName) == 0) {
            return entry->proc;
        }

        // Special case the two free-standing functions of the API.
        if (strcmp(procName, "wgpuGetProcAddress") == 0) {
            return reinterpret_cast<WGPUProc>(ClientGetProcAddress);
        }

        if (strcmp(procName, "wgpuCreateInstance") == 0) {
            return reinterpret_cast<WGPUProc>(ClientCreateInstance);
        }

        return nullptr;
    }

    std::vector<const char*> GetProcMapNamesForTesting() {
        std::vector<const char*> result;
        result.reserve(sProcMapSize);
        for (const ProcEntry& entry : sProcMap) {
            result.push_back(entry.name);
        }
        return result;
    }

    static DawnProcTable gProcTable = {
        ClientGetProcAddress,
        ClientCreateInstance,
        ClientBindGroupReference,
        ClientBindGroupRelease,
        ClientBindGroupLayoutReference,
        ClientBindGroupLayoutRelease,
        ClientBufferDestroy,
        ClientBufferGetConstMappedRange,
        ClientBufferGetMappedRange,
        ClientBufferMapAsync,
        ClientBufferUnmap,
        ClientBufferReference,
        ClientBufferRelease,
        ClientCommandBufferReference,
        ClientCommandBufferRelease,
        ClientCommandEncoderBeginComputePass,
        ClientCommandEncoderBeginRenderPass,
        ClientCommandEncoderCopyBufferToBuffer,
        ClientCommandEncoderCopyBufferToTexture,
        ClientCommandEncoderCopyTextureToBuffer,
        ClientCommandEncoderCopyTextureToTexture,
        ClientCommandEncoderFinish,
        ClientCommandEncoderInsertDebugMarker,
        ClientCommandEncoderPopDebugGroup,
        ClientCommandEncoderPushDebugGroup,
        ClientCommandEncoderResolveQuerySet,
        ClientCommandEncoderWriteTimestamp,
        ClientCommandEncoderReference,
        ClientCommandEncoderRelease,
        ClientComputePassEncoderDispatch,
        ClientComputePassEncoderDispatchIndirect,
        ClientComputePassEncoderEndPass,
        ClientComputePassEncoderInsertDebugMarker,
        ClientComputePassEncoderPopDebugGroup,
        ClientComputePassEncoderPushDebugGroup,
        ClientComputePassEncoderSetBindGroup,
        ClientComputePassEncoderSetPipeline,
        ClientComputePassEncoderWriteTimestamp,
        ClientComputePassEncoderReference,
        ClientComputePassEncoderRelease,
        ClientComputePipelineGetBindGroupLayout,
        ClientComputePipelineReference,
        ClientComputePipelineRelease,
        ClientDeviceCreateBindGroup,
        ClientDeviceCreateBindGroupLayout,
        ClientDeviceCreateBuffer,
        ClientDeviceCreateCommandEncoder,
        ClientDeviceCreateComputePipeline,
        ClientDeviceCreateErrorBuffer,
        ClientDeviceCreatePipelineLayout,
        ClientDeviceCreateQuerySet,
        ClientDeviceCreateReadyComputePipeline,
        ClientDeviceCreateReadyRenderPipeline,
        ClientDeviceCreateRenderBundleEncoder,
        ClientDeviceCreateRenderPipeline,
        ClientDeviceCreateSampler,
        ClientDeviceCreateShaderModule,
        ClientDeviceCreateSwapChain,
        ClientDeviceCreateTexture,
        ClientDeviceGetDefaultQueue,
        ClientDeviceInjectError,
        ClientDeviceLoseForTesting,
        ClientDevicePopErrorScope,
        ClientDevicePushErrorScope,
        ClientDeviceSetDeviceLostCallback,
        ClientDeviceSetUncapturedErrorCallback,
        ClientDeviceTick,
        ClientDeviceReference,
        ClientDeviceRelease,
        ClientFenceGetCompletedValue,
        ClientFenceOnCompletion,
        ClientFenceReference,
        ClientFenceRelease,
        ClientInstanceCreateSurface,
        ClientInstanceReference,
        ClientInstanceRelease,
        ClientPipelineLayoutReference,
        ClientPipelineLayoutRelease,
        ClientQuerySetDestroy,
        ClientQuerySetReference,
        ClientQuerySetRelease,
        ClientQueueCreateFence,
        ClientQueueSignal,
        ClientQueueSubmit,
        ClientQueueWriteBuffer,
        ClientQueueWriteTexture,
        ClientQueueReference,
        ClientQueueRelease,
        ClientRenderBundleReference,
        ClientRenderBundleRelease,
        ClientRenderBundleEncoderDraw,
        ClientRenderBundleEncoderDrawIndexed,
        ClientRenderBundleEncoderDrawIndexedIndirect,
        ClientRenderBundleEncoderDrawIndirect,
        ClientRenderBundleEncoderFinish,
        ClientRenderBundleEncoderInsertDebugMarker,
        ClientRenderBundleEncoderPopDebugGroup,
        ClientRenderBundleEncoderPushDebugGroup,
        ClientRenderBundleEncoderSetBindGroup,
        ClientRenderBundleEncoderSetIndexBuffer,
        ClientRenderBundleEncoderSetIndexBufferWithFormat,
        ClientRenderBundleEncoderSetPipeline,
        ClientRenderBundleEncoderSetVertexBuffer,
        ClientRenderBundleEncoderReference,
        ClientRenderBundleEncoderRelease,
        ClientRenderPassEncoderDraw,
        ClientRenderPassEncoderDrawIndexed,
        ClientRenderPassEncoderDrawIndexedIndirect,
        ClientRenderPassEncoderDrawIndirect,
        ClientRenderPassEncoderEndPass,
        ClientRenderPassEncoderExecuteBundles,
        ClientRenderPassEncoderInsertDebugMarker,
        ClientRenderPassEncoderPopDebugGroup,
        ClientRenderPassEncoderPushDebugGroup,
        ClientRenderPassEncoderSetBindGroup,
        ClientRenderPassEncoderSetBlendColor,
        ClientRenderPassEncoderSetIndexBuffer,
        ClientRenderPassEncoderSetIndexBufferWithFormat,
        ClientRenderPassEncoderSetPipeline,
        ClientRenderPassEncoderSetScissorRect,
        ClientRenderPassEncoderSetStencilReference,
        ClientRenderPassEncoderSetVertexBuffer,
        ClientRenderPassEncoderSetViewport,
        ClientRenderPassEncoderWriteTimestamp,
        ClientRenderPassEncoderReference,
        ClientRenderPassEncoderRelease,
        ClientRenderPipelineGetBindGroupLayout,
        ClientRenderPipelineReference,
        ClientRenderPipelineRelease,
        ClientSamplerReference,
        ClientSamplerRelease,
        ClientShaderModuleReference,
        ClientShaderModuleRelease,
        ClientSurfaceReference,
        ClientSurfaceRelease,
        ClientSwapChainConfigure,
        ClientSwapChainGetCurrentTextureView,
        ClientSwapChainPresent,
        ClientSwapChainReference,
        ClientSwapChainRelease,
        ClientTextureCreateView,
        ClientTextureDestroy,
        ClientTextureReference,
        ClientTextureRelease,
        ClientTextureViewReference,
        ClientTextureViewRelease,
    };
    const DawnProcTable& GetProcs() {
        return gProcTable;
    }
}}  // namespace dawn_wire::client
