
#include "dawn_native/ValidationUtils_autogen.h"

namespace dawn_native {

    MaybeError ValidateAdapterType(wgpu::AdapterType value) {
        switch (value) {
            case wgpu::AdapterType::DiscreteGPU:
                return {};
            case wgpu::AdapterType::IntegratedGPU:
                return {};
            case wgpu::AdapterType::CPU:
                return {};
            case wgpu::AdapterType::Unknown:
                return {};
            default:
                return DAWN_VALIDATION_ERROR("Invalid value for WGPUAdapterType");
        }
    }

    MaybeError ValidateAddressMode(wgpu::AddressMode value) {
        switch (value) {
            case wgpu::AddressMode::Repeat:
                return {};
            case wgpu::AddressMode::MirrorRepeat:
                return {};
            case wgpu::AddressMode::ClampToEdge:
                return {};
            default:
                return DAWN_VALIDATION_ERROR("Invalid value for WGPUAddressMode");
        }
    }

    MaybeError ValidateBackendType(wgpu::BackendType value) {
        switch (value) {
            case wgpu::BackendType::Null:
                return {};
            case wgpu::BackendType::D3D11:
                return {};
            case wgpu::BackendType::D3D12:
                return {};
            case wgpu::BackendType::Metal:
                return {};
            case wgpu::BackendType::Vulkan:
                return {};
            case wgpu::BackendType::OpenGL:
                return {};
            case wgpu::BackendType::OpenGLES:
                return {};
            default:
                return DAWN_VALIDATION_ERROR("Invalid value for WGPUBackendType");
        }
    }

    MaybeError ValidateBindingType(wgpu::BindingType value) {
        switch (value) {
            case wgpu::BindingType::UniformBuffer:
                return {};
            case wgpu::BindingType::StorageBuffer:
                return {};
            case wgpu::BindingType::ReadonlyStorageBuffer:
                return {};
            case wgpu::BindingType::Sampler:
                return {};
            case wgpu::BindingType::ComparisonSampler:
                return {};
            case wgpu::BindingType::SampledTexture:
                return {};
            case wgpu::BindingType::MultisampledTexture:
                return {};
            case wgpu::BindingType::ReadonlyStorageTexture:
                return {};
            case wgpu::BindingType::WriteonlyStorageTexture:
                return {};
            default:
                return DAWN_VALIDATION_ERROR("Invalid value for WGPUBindingType");
        }
    }

    MaybeError ValidateBlendFactor(wgpu::BlendFactor value) {
        switch (value) {
            case wgpu::BlendFactor::Zero:
                return {};
            case wgpu::BlendFactor::One:
                return {};
            case wgpu::BlendFactor::SrcColor:
                return {};
            case wgpu::BlendFactor::OneMinusSrcColor:
                return {};
            case wgpu::BlendFactor::SrcAlpha:
                return {};
            case wgpu::BlendFactor::OneMinusSrcAlpha:
                return {};
            case wgpu::BlendFactor::DstColor:
                return {};
            case wgpu::BlendFactor::OneMinusDstColor:
                return {};
            case wgpu::BlendFactor::DstAlpha:
                return {};
            case wgpu::BlendFactor::OneMinusDstAlpha:
                return {};
            case wgpu::BlendFactor::SrcAlphaSaturated:
                return {};
            case wgpu::BlendFactor::BlendColor:
                return {};
            case wgpu::BlendFactor::OneMinusBlendColor:
                return {};
            default:
                return DAWN_VALIDATION_ERROR("Invalid value for WGPUBlendFactor");
        }
    }

    MaybeError ValidateBlendOperation(wgpu::BlendOperation value) {
        switch (value) {
            case wgpu::BlendOperation::Add:
                return {};
            case wgpu::BlendOperation::Subtract:
                return {};
            case wgpu::BlendOperation::ReverseSubtract:
                return {};
            case wgpu::BlendOperation::Min:
                return {};
            case wgpu::BlendOperation::Max:
                return {};
            default:
                return DAWN_VALIDATION_ERROR("Invalid value for WGPUBlendOperation");
        }
    }

    MaybeError ValidateBufferMapAsyncStatus(wgpu::BufferMapAsyncStatus value) {
        switch (value) {
            case wgpu::BufferMapAsyncStatus::Success:
                return {};
            case wgpu::BufferMapAsyncStatus::Error:
                return {};
            case wgpu::BufferMapAsyncStatus::Unknown:
                return {};
            case wgpu::BufferMapAsyncStatus::DeviceLost:
                return {};
            case wgpu::BufferMapAsyncStatus::DestroyedBeforeCallback:
                return {};
            case wgpu::BufferMapAsyncStatus::UnmappedBeforeCallback:
                return {};
            default:
                return DAWN_VALIDATION_ERROR("Invalid value for WGPUBufferMapAsyncStatus");
        }
    }

    MaybeError ValidateCompareFunction(wgpu::CompareFunction value) {
        switch (value) {
            case wgpu::CompareFunction::Undefined:
                return {};
            case wgpu::CompareFunction::Never:
                return {};
            case wgpu::CompareFunction::Less:
                return {};
            case wgpu::CompareFunction::LessEqual:
                return {};
            case wgpu::CompareFunction::Greater:
                return {};
            case wgpu::CompareFunction::GreaterEqual:
                return {};
            case wgpu::CompareFunction::Equal:
                return {};
            case wgpu::CompareFunction::NotEqual:
                return {};
            case wgpu::CompareFunction::Always:
                return {};
            default:
                return DAWN_VALIDATION_ERROR("Invalid value for WGPUCompareFunction");
        }
    }

    MaybeError ValidateCreateReadyPipelineStatus(wgpu::CreateReadyPipelineStatus value) {
        switch (value) {
            case wgpu::CreateReadyPipelineStatus::Success:
                return {};
            case wgpu::CreateReadyPipelineStatus::Error:
                return {};
            case wgpu::CreateReadyPipelineStatus::DeviceLost:
                return {};
            case wgpu::CreateReadyPipelineStatus::Unknown:
                return {};
            default:
                return DAWN_VALIDATION_ERROR("Invalid value for WGPUCreateReadyPipelineStatus");
        }
    }

    MaybeError ValidateCullMode(wgpu::CullMode value) {
        switch (value) {
            case wgpu::CullMode::None:
                return {};
            case wgpu::CullMode::Front:
                return {};
            case wgpu::CullMode::Back:
                return {};
            default:
                return DAWN_VALIDATION_ERROR("Invalid value for WGPUCullMode");
        }
    }

    MaybeError ValidateErrorFilter(wgpu::ErrorFilter value) {
        switch (value) {
            case wgpu::ErrorFilter::None:
                return {};
            case wgpu::ErrorFilter::Validation:
                return {};
            case wgpu::ErrorFilter::OutOfMemory:
                return {};
            default:
                return DAWN_VALIDATION_ERROR("Invalid value for WGPUErrorFilter");
        }
    }

    MaybeError ValidateErrorType(wgpu::ErrorType value) {
        switch (value) {
            case wgpu::ErrorType::NoError:
                return {};
            case wgpu::ErrorType::Validation:
                return {};
            case wgpu::ErrorType::OutOfMemory:
                return {};
            case wgpu::ErrorType::Unknown:
                return {};
            case wgpu::ErrorType::DeviceLost:
                return {};
            default:
                return DAWN_VALIDATION_ERROR("Invalid value for WGPUErrorType");
        }
    }

    MaybeError ValidateFenceCompletionStatus(wgpu::FenceCompletionStatus value) {
        switch (value) {
            case wgpu::FenceCompletionStatus::Success:
                return {};
            case wgpu::FenceCompletionStatus::Error:
                return {};
            case wgpu::FenceCompletionStatus::Unknown:
                return {};
            case wgpu::FenceCompletionStatus::DeviceLost:
                return {};
            default:
                return DAWN_VALIDATION_ERROR("Invalid value for WGPUFenceCompletionStatus");
        }
    }

    MaybeError ValidateFilterMode(wgpu::FilterMode value) {
        switch (value) {
            case wgpu::FilterMode::Nearest:
                return {};
            case wgpu::FilterMode::Linear:
                return {};
            default:
                return DAWN_VALIDATION_ERROR("Invalid value for WGPUFilterMode");
        }
    }

    MaybeError ValidateFrontFace(wgpu::FrontFace value) {
        switch (value) {
            case wgpu::FrontFace::CCW:
                return {};
            case wgpu::FrontFace::CW:
                return {};
            default:
                return DAWN_VALIDATION_ERROR("Invalid value for WGPUFrontFace");
        }
    }

    MaybeError ValidateIndexFormat(wgpu::IndexFormat value) {
        switch (value) {
            case wgpu::IndexFormat::Undefined:
                return {};
            case wgpu::IndexFormat::Uint16:
                return {};
            case wgpu::IndexFormat::Uint32:
                return {};
            default:
                return DAWN_VALIDATION_ERROR("Invalid value for WGPUIndexFormat");
        }
    }

    MaybeError ValidateInputStepMode(wgpu::InputStepMode value) {
        switch (value) {
            case wgpu::InputStepMode::Vertex:
                return {};
            case wgpu::InputStepMode::Instance:
                return {};
            default:
                return DAWN_VALIDATION_ERROR("Invalid value for WGPUInputStepMode");
        }
    }

    MaybeError ValidateLoadOp(wgpu::LoadOp value) {
        switch (value) {
            case wgpu::LoadOp::Clear:
                return {};
            case wgpu::LoadOp::Load:
                return {};
            default:
                return DAWN_VALIDATION_ERROR("Invalid value for WGPULoadOp");
        }
    }

    MaybeError ValidatePipelineStatisticName(wgpu::PipelineStatisticName value) {
        switch (value) {
            case wgpu::PipelineStatisticName::VertexShaderInvocations:
                return {};
            case wgpu::PipelineStatisticName::ClipperInvocations:
                return {};
            case wgpu::PipelineStatisticName::ClipperPrimitivesOut:
                return {};
            case wgpu::PipelineStatisticName::FragmentShaderInvocations:
                return {};
            case wgpu::PipelineStatisticName::ComputeShaderInvocations:
                return {};
            default:
                return DAWN_VALIDATION_ERROR("Invalid value for WGPUPipelineStatisticName");
        }
    }

    MaybeError ValidatePresentMode(wgpu::PresentMode value) {
        switch (value) {
            case wgpu::PresentMode::Immediate:
                return {};
            case wgpu::PresentMode::Mailbox:
                return {};
            case wgpu::PresentMode::Fifo:
                return {};
            default:
                return DAWN_VALIDATION_ERROR("Invalid value for WGPUPresentMode");
        }
    }

    MaybeError ValidatePrimitiveTopology(wgpu::PrimitiveTopology value) {
        switch (value) {
            case wgpu::PrimitiveTopology::PointList:
                return {};
            case wgpu::PrimitiveTopology::LineList:
                return {};
            case wgpu::PrimitiveTopology::LineStrip:
                return {};
            case wgpu::PrimitiveTopology::TriangleList:
                return {};
            case wgpu::PrimitiveTopology::TriangleStrip:
                return {};
            default:
                return DAWN_VALIDATION_ERROR("Invalid value for WGPUPrimitiveTopology");
        }
    }

    MaybeError ValidateQueryType(wgpu::QueryType value) {
        switch (value) {
            case wgpu::QueryType::Occlusion:
                return {};
            case wgpu::QueryType::PipelineStatistics:
                return {};
            case wgpu::QueryType::Timestamp:
                return {};
            default:
                return DAWN_VALIDATION_ERROR("Invalid value for WGPUQueryType");
        }
    }

    MaybeError ValidateSType(wgpu::SType value) {
        switch (value) {
            case wgpu::SType::SurfaceDescriptorFromMetalLayer:
                return {};
            case wgpu::SType::SurfaceDescriptorFromWindowsHWND:
                return {};
            case wgpu::SType::SurfaceDescriptorFromXlib:
                return {};
            case wgpu::SType::SurfaceDescriptorFromCanvasHTMLSelector:
                return {};
            case wgpu::SType::ShaderModuleSPIRVDescriptor:
                return {};
            case wgpu::SType::ShaderModuleWGSLDescriptor:
                return {};
            case wgpu::SType::SamplerDescriptorDummyAnisotropicFiltering:
                return {};
            case wgpu::SType::RenderPipelineDescriptorDummyExtension:
                return {};
            default:
                return DAWN_VALIDATION_ERROR("Invalid value for WGPUSType");
        }
    }

    MaybeError ValidateStencilOperation(wgpu::StencilOperation value) {
        switch (value) {
            case wgpu::StencilOperation::Keep:
                return {};
            case wgpu::StencilOperation::Zero:
                return {};
            case wgpu::StencilOperation::Replace:
                return {};
            case wgpu::StencilOperation::Invert:
                return {};
            case wgpu::StencilOperation::IncrementClamp:
                return {};
            case wgpu::StencilOperation::DecrementClamp:
                return {};
            case wgpu::StencilOperation::IncrementWrap:
                return {};
            case wgpu::StencilOperation::DecrementWrap:
                return {};
            default:
                return DAWN_VALIDATION_ERROR("Invalid value for WGPUStencilOperation");
        }
    }

    MaybeError ValidateStoreOp(wgpu::StoreOp value) {
        switch (value) {
            case wgpu::StoreOp::Store:
                return {};
            case wgpu::StoreOp::Clear:
                return {};
            default:
                return DAWN_VALIDATION_ERROR("Invalid value for WGPUStoreOp");
        }
    }

    MaybeError ValidateTextureAspect(wgpu::TextureAspect value) {
        switch (value) {
            case wgpu::TextureAspect::All:
                return {};
            case wgpu::TextureAspect::StencilOnly:
                return {};
            case wgpu::TextureAspect::DepthOnly:
                return {};
            default:
                return DAWN_VALIDATION_ERROR("Invalid value for WGPUTextureAspect");
        }
    }

    MaybeError ValidateTextureComponentType(wgpu::TextureComponentType value) {
        switch (value) {
            case wgpu::TextureComponentType::Float:
                return {};
            case wgpu::TextureComponentType::Sint:
                return {};
            case wgpu::TextureComponentType::Uint:
                return {};
            case wgpu::TextureComponentType::DepthComparison:
                return {};
            default:
                return DAWN_VALIDATION_ERROR("Invalid value for WGPUTextureComponentType");
        }
    }

    MaybeError ValidateTextureDimension(wgpu::TextureDimension value) {
        switch (value) {
            case wgpu::TextureDimension::e1D:
                return {};
            case wgpu::TextureDimension::e2D:
                return {};
            case wgpu::TextureDimension::e3D:
                return {};
            default:
                return DAWN_VALIDATION_ERROR("Invalid value for WGPUTextureDimension");
        }
    }

    MaybeError ValidateTextureFormat(wgpu::TextureFormat value) {
        switch (value) {
            case wgpu::TextureFormat::R8Unorm:
                return {};
            case wgpu::TextureFormat::R8Snorm:
                return {};
            case wgpu::TextureFormat::R8Uint:
                return {};
            case wgpu::TextureFormat::R8Sint:
                return {};
            case wgpu::TextureFormat::R16Uint:
                return {};
            case wgpu::TextureFormat::R16Sint:
                return {};
            case wgpu::TextureFormat::R16Float:
                return {};
            case wgpu::TextureFormat::RG8Unorm:
                return {};
            case wgpu::TextureFormat::RG8Snorm:
                return {};
            case wgpu::TextureFormat::RG8Uint:
                return {};
            case wgpu::TextureFormat::RG8Sint:
                return {};
            case wgpu::TextureFormat::R32Float:
                return {};
            case wgpu::TextureFormat::R32Uint:
                return {};
            case wgpu::TextureFormat::R32Sint:
                return {};
            case wgpu::TextureFormat::RG16Uint:
                return {};
            case wgpu::TextureFormat::RG16Sint:
                return {};
            case wgpu::TextureFormat::RG16Float:
                return {};
            case wgpu::TextureFormat::RGBA8Unorm:
                return {};
            case wgpu::TextureFormat::RGBA8UnormSrgb:
                return {};
            case wgpu::TextureFormat::RGBA8Snorm:
                return {};
            case wgpu::TextureFormat::RGBA8Uint:
                return {};
            case wgpu::TextureFormat::RGBA8Sint:
                return {};
            case wgpu::TextureFormat::BGRA8Unorm:
                return {};
            case wgpu::TextureFormat::BGRA8UnormSrgb:
                return {};
            case wgpu::TextureFormat::RGB10A2Unorm:
                return {};
            case wgpu::TextureFormat::RG11B10Ufloat:
                return {};
            case wgpu::TextureFormat::RGB9E5Ufloat:
                return {};
            case wgpu::TextureFormat::RG32Float:
                return {};
            case wgpu::TextureFormat::RG32Uint:
                return {};
            case wgpu::TextureFormat::RG32Sint:
                return {};
            case wgpu::TextureFormat::RGBA16Uint:
                return {};
            case wgpu::TextureFormat::RGBA16Sint:
                return {};
            case wgpu::TextureFormat::RGBA16Float:
                return {};
            case wgpu::TextureFormat::RGBA32Float:
                return {};
            case wgpu::TextureFormat::RGBA32Uint:
                return {};
            case wgpu::TextureFormat::RGBA32Sint:
                return {};
            case wgpu::TextureFormat::Depth32Float:
                return {};
            case wgpu::TextureFormat::Depth24Plus:
                return {};
            case wgpu::TextureFormat::Depth24PlusStencil8:
                return {};
            case wgpu::TextureFormat::BC1RGBAUnorm:
                return {};
            case wgpu::TextureFormat::BC1RGBAUnormSrgb:
                return {};
            case wgpu::TextureFormat::BC2RGBAUnorm:
                return {};
            case wgpu::TextureFormat::BC2RGBAUnormSrgb:
                return {};
            case wgpu::TextureFormat::BC3RGBAUnorm:
                return {};
            case wgpu::TextureFormat::BC3RGBAUnormSrgb:
                return {};
            case wgpu::TextureFormat::BC4RUnorm:
                return {};
            case wgpu::TextureFormat::BC4RSnorm:
                return {};
            case wgpu::TextureFormat::BC5RGUnorm:
                return {};
            case wgpu::TextureFormat::BC5RGSnorm:
                return {};
            case wgpu::TextureFormat::BC6HRGBUfloat:
                return {};
            case wgpu::TextureFormat::BC6HRGBFloat:
                return {};
            case wgpu::TextureFormat::BC7RGBAUnorm:
                return {};
            case wgpu::TextureFormat::BC7RGBAUnormSrgb:
                return {};
            default:
                return DAWN_VALIDATION_ERROR("Invalid value for WGPUTextureFormat");
        }
    }

    MaybeError ValidateTextureViewDimension(wgpu::TextureViewDimension value) {
        switch (value) {
            case wgpu::TextureViewDimension::e1D:
                return {};
            case wgpu::TextureViewDimension::e2D:
                return {};
            case wgpu::TextureViewDimension::e2DArray:
                return {};
            case wgpu::TextureViewDimension::Cube:
                return {};
            case wgpu::TextureViewDimension::CubeArray:
                return {};
            case wgpu::TextureViewDimension::e3D:
                return {};
            default:
                return DAWN_VALIDATION_ERROR("Invalid value for WGPUTextureViewDimension");
        }
    }

    MaybeError ValidateVertexFormat(wgpu::VertexFormat value) {
        switch (value) {
            case wgpu::VertexFormat::UChar2:
                return {};
            case wgpu::VertexFormat::UChar4:
                return {};
            case wgpu::VertexFormat::Char2:
                return {};
            case wgpu::VertexFormat::Char4:
                return {};
            case wgpu::VertexFormat::UChar2Norm:
                return {};
            case wgpu::VertexFormat::UChar4Norm:
                return {};
            case wgpu::VertexFormat::Char2Norm:
                return {};
            case wgpu::VertexFormat::Char4Norm:
                return {};
            case wgpu::VertexFormat::UShort2:
                return {};
            case wgpu::VertexFormat::UShort4:
                return {};
            case wgpu::VertexFormat::Short2:
                return {};
            case wgpu::VertexFormat::Short4:
                return {};
            case wgpu::VertexFormat::UShort2Norm:
                return {};
            case wgpu::VertexFormat::UShort4Norm:
                return {};
            case wgpu::VertexFormat::Short2Norm:
                return {};
            case wgpu::VertexFormat::Short4Norm:
                return {};
            case wgpu::VertexFormat::Half2:
                return {};
            case wgpu::VertexFormat::Half4:
                return {};
            case wgpu::VertexFormat::Float:
                return {};
            case wgpu::VertexFormat::Float2:
                return {};
            case wgpu::VertexFormat::Float3:
                return {};
            case wgpu::VertexFormat::Float4:
                return {};
            case wgpu::VertexFormat::UInt:
                return {};
            case wgpu::VertexFormat::UInt2:
                return {};
            case wgpu::VertexFormat::UInt3:
                return {};
            case wgpu::VertexFormat::UInt4:
                return {};
            case wgpu::VertexFormat::Int:
                return {};
            case wgpu::VertexFormat::Int2:
                return {};
            case wgpu::VertexFormat::Int3:
                return {};
            case wgpu::VertexFormat::Int4:
                return {};
            default:
                return DAWN_VALIDATION_ERROR("Invalid value for WGPUVertexFormat");
        }
    }


    MaybeError ValidateBufferUsage(wgpu::BufferUsage value) {
        if ((value & static_cast<wgpu::BufferUsage>(~1023)) == 0) {
            return {};
        }
        return DAWN_VALIDATION_ERROR("Invalid value for WGPUBufferUsage");
    }

    MaybeError ValidateColorWriteMask(wgpu::ColorWriteMask value) {
        if ((value & static_cast<wgpu::ColorWriteMask>(~15)) == 0) {
            return {};
        }
        return DAWN_VALIDATION_ERROR("Invalid value for WGPUColorWriteMask");
    }

    MaybeError ValidateMapMode(wgpu::MapMode value) {
        if ((value & static_cast<wgpu::MapMode>(~3)) == 0) {
            return {};
        }
        return DAWN_VALIDATION_ERROR("Invalid value for WGPUMapMode");
    }

    MaybeError ValidateShaderStage(wgpu::ShaderStage value) {
        if ((value & static_cast<wgpu::ShaderStage>(~7)) == 0) {
            return {};
        }
        return DAWN_VALIDATION_ERROR("Invalid value for WGPUShaderStage");
    }

    MaybeError ValidateTextureUsage(wgpu::TextureUsage value) {
        if ((value & static_cast<wgpu::TextureUsage>(~63)) == 0) {
            return {};
        }
        return DAWN_VALIDATION_ERROR("Invalid value for WGPUTextureUsage");
    }


} // namespace dawn_native
