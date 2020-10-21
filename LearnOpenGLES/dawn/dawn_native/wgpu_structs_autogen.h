
#ifndef DAWNNATIVE_WGPU_STRUCTS_H_
#define DAWNNATIVE_WGPU_STRUCTS_H_

#include "dawn/webgpu_cpp.h"
#include "dawn_native/Forward.h"

namespace dawn_native {


    struct ChainedStruct {
        ChainedStruct const * nextInChain = nullptr;
        wgpu::SType sType = wgpu::SType::Invalid;
    };

    struct AdapterProperties {
        ChainedStruct const * nextInChain = nullptr;
        uint32_t deviceID;
        uint32_t vendorID;
        char const * name;
        char const * driverDescription;
        wgpu::AdapterType adapterType;
        wgpu::BackendType backendType;
    };

    struct BindGroupEntry {
        uint32_t binding;
        BufferBase* buffer;
        uint64_t offset = 0;
        uint64_t size;
        SamplerBase* sampler;
        TextureViewBase* textureView;
    };

    struct BindGroupLayoutEntry {
        uint32_t binding;
        wgpu::ShaderStage visibility;
        wgpu::BindingType type;
        bool hasDynamicOffset = false;
        uint64_t minBufferBindingSize = 0;
        bool multisampled = false;
        wgpu::TextureViewDimension viewDimension = wgpu::TextureViewDimension::Undefined;
        wgpu::TextureComponentType textureComponentType = wgpu::TextureComponentType::Float;
        wgpu::TextureFormat storageTextureFormat = wgpu::TextureFormat::Undefined;
    };

    struct BlendDescriptor {
        wgpu::BlendOperation operation = wgpu::BlendOperation::Add;
        wgpu::BlendFactor srcFactor = wgpu::BlendFactor::One;
        wgpu::BlendFactor dstFactor = wgpu::BlendFactor::Zero;
    };

    struct BufferDescriptor {
        ChainedStruct const * nextInChain = nullptr;
        char const * label = nullptr;
        wgpu::BufferUsage usage;
        uint64_t size;
        bool mappedAtCreation = false;
    };

    struct Color {
        double r;
        double g;
        double b;
        double a;
    };

    struct CommandBufferDescriptor {
        ChainedStruct const * nextInChain = nullptr;
        char const * label = nullptr;
    };

    struct CommandEncoderDescriptor {
        ChainedStruct const * nextInChain = nullptr;
        char const * label = nullptr;
    };

    struct ComputePassDescriptor {
        ChainedStruct const * nextInChain = nullptr;
        char const * label = nullptr;
    };

    struct DeviceProperties {
        bool textureCompressionBC = false;
        bool shaderFloat16 = false;
        bool pipelineStatisticsQuery = false;
        bool timestampQuery = false;
    };

    struct Extent3D {
        uint32_t width = 1;
        uint32_t height = 1;
        uint32_t depth = 1;
    };

    struct FenceDescriptor {
        ChainedStruct const * nextInChain = nullptr;
        char const * label = nullptr;
        uint64_t initialValue = 0;
    };

    struct InstanceDescriptor {
        ChainedStruct const * nextInChain = nullptr;
    };

    struct Origin3D {
        uint32_t x = 0;
        uint32_t y = 0;
        uint32_t z = 0;
    };

    struct PipelineLayoutDescriptor {
        ChainedStruct const * nextInChain = nullptr;
        char const * label = nullptr;
        uint32_t bindGroupLayoutCount;
        BindGroupLayoutBase* const * bindGroupLayouts;
    };

    struct ProgrammableStageDescriptor {
        ChainedStruct const * nextInChain = nullptr;
        ShaderModuleBase* module;
        char const * entryPoint;
    };

    struct QuerySetDescriptor {
        ChainedStruct const * nextInChain = nullptr;
        char const * label = nullptr;
        wgpu::QueryType type;
        uint32_t count;
        wgpu::PipelineStatisticName const * pipelineStatistics;
        uint32_t pipelineStatisticsCount = 0;
    };

    struct RasterizationStateDescriptor {
        ChainedStruct const * nextInChain = nullptr;
        wgpu::FrontFace frontFace = wgpu::FrontFace::CCW;
        wgpu::CullMode cullMode = wgpu::CullMode::None;
        int32_t depthBias = 0;
        float depthBiasSlopeScale = 0.0f;
        float depthBiasClamp = 0.0f;
    };

    struct RenderBundleDescriptor {
        ChainedStruct const * nextInChain = nullptr;
        char const * label = nullptr;
    };

    struct RenderBundleEncoderDescriptor {
        ChainedStruct const * nextInChain = nullptr;
        char const * label = nullptr;
        uint32_t colorFormatsCount;
        wgpu::TextureFormat const * colorFormats;
        wgpu::TextureFormat depthStencilFormat = wgpu::TextureFormat::Undefined;
        uint32_t sampleCount = 1;
    };

    struct RenderPassDepthStencilAttachmentDescriptor {
        TextureViewBase* attachment;
        wgpu::LoadOp depthLoadOp;
        wgpu::StoreOp depthStoreOp;
        float clearDepth;
        bool depthReadOnly = false;
        wgpu::LoadOp stencilLoadOp;
        wgpu::StoreOp stencilStoreOp;
        uint32_t clearStencil = 0;
        bool stencilReadOnly = false;
    };

    struct SamplerDescriptor {
        ChainedStruct const * nextInChain = nullptr;
        char const * label = nullptr;
        wgpu::AddressMode addressModeU = wgpu::AddressMode::ClampToEdge;
        wgpu::AddressMode addressModeV = wgpu::AddressMode::ClampToEdge;
        wgpu::AddressMode addressModeW = wgpu::AddressMode::ClampToEdge;
        wgpu::FilterMode magFilter = wgpu::FilterMode::Nearest;
        wgpu::FilterMode minFilter = wgpu::FilterMode::Nearest;
        wgpu::FilterMode mipmapFilter = wgpu::FilterMode::Nearest;
        float lodMinClamp = 0.0f;
        float lodMaxClamp = 1000.0f;
        wgpu::CompareFunction compare = wgpu::CompareFunction::Undefined;
    };

    struct SamplerDescriptorDummyAnisotropicFiltering : ChainedStruct {
        SamplerDescriptorDummyAnisotropicFiltering() {
            sType = wgpu::SType::SamplerDescriptorDummyAnisotropicFiltering;
        }
        alignas(ChainedStruct) float maxAnisotropy;
    };

    struct ShaderModuleDescriptor {
        ChainedStruct const * nextInChain = nullptr;
        char const * label = nullptr;
    };

    struct ShaderModuleSPIRVDescriptor : ChainedStruct {
        ShaderModuleSPIRVDescriptor() {
            sType = wgpu::SType::ShaderModuleSPIRVDescriptor;
        }
        alignas(ChainedStruct) uint32_t codeSize;
        uint32_t const * code;
    };

    struct ShaderModuleWGSLDescriptor : ChainedStruct {
        ShaderModuleWGSLDescriptor() {
            sType = wgpu::SType::ShaderModuleWGSLDescriptor;
        }
        alignas(ChainedStruct) char const * source;
    };

    struct StencilStateFaceDescriptor {
        wgpu::CompareFunction compare = wgpu::CompareFunction::Always;
        wgpu::StencilOperation failOp = wgpu::StencilOperation::Keep;
        wgpu::StencilOperation depthFailOp = wgpu::StencilOperation::Keep;
        wgpu::StencilOperation passOp = wgpu::StencilOperation::Keep;
    };

    struct SurfaceDescriptor {
        ChainedStruct const * nextInChain = nullptr;
        char const * label = nullptr;
    };

    struct SurfaceDescriptorFromCanvasHTMLSelector : ChainedStruct {
        SurfaceDescriptorFromCanvasHTMLSelector() {
            sType = wgpu::SType::SurfaceDescriptorFromCanvasHTMLSelector;
        }
        alignas(ChainedStruct) char const * selector;
    };

    struct SurfaceDescriptorFromMetalLayer : ChainedStruct {
        SurfaceDescriptorFromMetalLayer() {
            sType = wgpu::SType::SurfaceDescriptorFromMetalLayer;
        }
        alignas(ChainedStruct) void * layer;
    };

    struct SurfaceDescriptorFromWindowsHWND : ChainedStruct {
        SurfaceDescriptorFromWindowsHWND() {
            sType = wgpu::SType::SurfaceDescriptorFromWindowsHWND;
        }
        alignas(ChainedStruct) void * hinstance;
        void * hwnd;
    };

    struct SurfaceDescriptorFromXlib : ChainedStruct {
        SurfaceDescriptorFromXlib() {
            sType = wgpu::SType::SurfaceDescriptorFromXlib;
        }
        alignas(ChainedStruct) void * display;
        uint32_t window;
    };

    struct SwapChainDescriptor {
        ChainedStruct const * nextInChain = nullptr;
        char const * label = nullptr;
        wgpu::TextureUsage usage;
        wgpu::TextureFormat format;
        uint32_t width;
        uint32_t height;
        wgpu::PresentMode presentMode;
        uint64_t implementation = 0;
    };

    struct TextureDataLayout {
        ChainedStruct const * nextInChain = nullptr;
        uint64_t offset = 0;
        uint32_t bytesPerRow;
        uint32_t rowsPerImage = 0;
    };

    struct TextureViewDescriptor {
        ChainedStruct const * nextInChain = nullptr;
        char const * label = nullptr;
        wgpu::TextureFormat format = wgpu::TextureFormat::Undefined;
        wgpu::TextureViewDimension dimension = wgpu::TextureViewDimension::Undefined;
        uint32_t baseMipLevel = 0;
        uint32_t mipLevelCount = 0;
        uint32_t baseArrayLayer = 0;
        uint32_t arrayLayerCount = 0;
        wgpu::TextureAspect aspect = wgpu::TextureAspect::All;
    };

    struct VertexAttributeDescriptor {
        wgpu::VertexFormat format;
        uint64_t offset;
        uint32_t shaderLocation;
    };

    struct BindGroupDescriptor {
        ChainedStruct const * nextInChain = nullptr;
        char const * label = nullptr;
        BindGroupLayoutBase* layout;
        uint32_t entryCount;
        BindGroupEntry const * entries;
    };

    struct BindGroupLayoutDescriptor {
        ChainedStruct const * nextInChain = nullptr;
        char const * label = nullptr;
        uint32_t entryCount;
        BindGroupLayoutEntry const * entries;
    };

    struct BufferCopyView {
        ChainedStruct const * nextInChain = nullptr;
        TextureDataLayout layout;
        BufferBase* buffer;
    };

    struct ColorStateDescriptor {
        ChainedStruct const * nextInChain = nullptr;
        wgpu::TextureFormat format;
        BlendDescriptor alphaBlend;
        BlendDescriptor colorBlend;
        wgpu::ColorWriteMask writeMask = wgpu::ColorWriteMask::All;
    };

    struct ComputePipelineDescriptor {
        ChainedStruct const * nextInChain = nullptr;
        char const * label = nullptr;
        PipelineLayoutBase* layout;
        ProgrammableStageDescriptor computeStage;
    };

    struct DepthStencilStateDescriptor {
        ChainedStruct const * nextInChain = nullptr;
        wgpu::TextureFormat format;
        bool depthWriteEnabled = false;
        wgpu::CompareFunction depthCompare = wgpu::CompareFunction::Always;
        StencilStateFaceDescriptor stencilFront;
        StencilStateFaceDescriptor stencilBack;
        uint32_t stencilReadMask = 0xFFFFFFFF;
        uint32_t stencilWriteMask = 0xFFFFFFFF;
    };

    struct RenderPassColorAttachmentDescriptor {
        TextureViewBase* attachment;
        TextureViewBase* resolveTarget;
        wgpu::LoadOp loadOp;
        wgpu::StoreOp storeOp;
        Color clearColor;
    };

    struct RenderPipelineDescriptorDummyExtension : ChainedStruct {
        RenderPipelineDescriptorDummyExtension() {
            sType = wgpu::SType::RenderPipelineDescriptorDummyExtension;
        }
        alignas(ChainedStruct) ProgrammableStageDescriptor dummyStage;
    };

    struct TextureCopyView {
        ChainedStruct const * nextInChain = nullptr;
        TextureBase* texture;
        uint32_t mipLevel = 0;
        Origin3D origin;
        wgpu::TextureAspect aspect = wgpu::TextureAspect::All;
    };

    struct TextureDescriptor {
        ChainedStruct const * nextInChain = nullptr;
        char const * label = nullptr;
        wgpu::TextureUsage usage;
        wgpu::TextureDimension dimension = wgpu::TextureDimension::e2D;
        Extent3D size;
        wgpu::TextureFormat format;
        uint32_t mipLevelCount = 1;
        uint32_t sampleCount = 1;
    };

    struct VertexBufferLayoutDescriptor {
        uint64_t arrayStride;
        wgpu::InputStepMode stepMode = wgpu::InputStepMode::Vertex;
        uint32_t attributeCount;
        VertexAttributeDescriptor const * attributes;
    };

    struct RenderPassDescriptor {
        ChainedStruct const * nextInChain = nullptr;
        char const * label = nullptr;
        uint32_t colorAttachmentCount;
        RenderPassColorAttachmentDescriptor const * colorAttachments;
        RenderPassDepthStencilAttachmentDescriptor const * depthStencilAttachment = nullptr;
        QuerySetBase* occlusionQuerySet;
    };

    struct VertexStateDescriptor {
        ChainedStruct const * nextInChain = nullptr;
        wgpu::IndexFormat indexFormat = wgpu::IndexFormat::Undefined;
        uint32_t vertexBufferCount = 0;
        VertexBufferLayoutDescriptor const * vertexBuffers;
    };

    struct RenderPipelineDescriptor {
        ChainedStruct const * nextInChain = nullptr;
        char const * label = nullptr;
        PipelineLayoutBase* layout;
        ProgrammableStageDescriptor vertexStage;
        ProgrammableStageDescriptor const * fragmentStage = nullptr;
        VertexStateDescriptor const * vertexState = nullptr;
        wgpu::PrimitiveTopology primitiveTopology;
        RasterizationStateDescriptor const * rasterizationState = nullptr;
        uint32_t sampleCount = 1;
        DepthStencilStateDescriptor const * depthStencilState = nullptr;
        uint32_t colorStateCount;
        ColorStateDescriptor const * colorStates;
        uint32_t sampleMask = 0xFFFFFFFF;
        bool alphaToCoverageEnabled = false;
    };


} // namespace dawn_native

#endif  // DAWNNATIVE_WGPU_STRUCTS_H_
