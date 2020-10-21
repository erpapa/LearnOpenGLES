
#include "dawn_native/wgpu_structs_autogen.h"

namespace dawn_native {

    static_assert(sizeof(ChainedStruct) == sizeof(WGPUChainedStruct),
            "sizeof mismatch for ChainedStruct");
    static_assert(alignof(ChainedStruct) == alignof(WGPUChainedStruct),
            "alignof mismatch for ChainedStruct");
    static_assert(offsetof(ChainedStruct, nextInChain) == offsetof(WGPUChainedStruct, next),
            "offsetof mismatch for ChainedStruct::nextInChain");
    static_assert(offsetof(ChainedStruct, sType) == offsetof(WGPUChainedStruct, sType),
            "offsetof mismatch for ChainedStruct::sType");


    static_assert(sizeof(AdapterProperties) == sizeof(WGPUAdapterProperties), "sizeof mismatch for AdapterProperties");
    static_assert(alignof(AdapterProperties) == alignof(WGPUAdapterProperties), "alignof mismatch for AdapterProperties");

    static_assert(offsetof(AdapterProperties, nextInChain) == offsetof(WGPUAdapterProperties, nextInChain),
            "offsetof mismatch for AdapterProperties::nextInChain");
    static_assert(offsetof(AdapterProperties, deviceID) == offsetof(WGPUAdapterProperties, deviceID),
            "offsetof mismatch for AdapterProperties::deviceID");
    static_assert(offsetof(AdapterProperties, vendorID) == offsetof(WGPUAdapterProperties, vendorID),
            "offsetof mismatch for AdapterProperties::vendorID");
    static_assert(offsetof(AdapterProperties, name) == offsetof(WGPUAdapterProperties, name),
            "offsetof mismatch for AdapterProperties::name");
    static_assert(offsetof(AdapterProperties, driverDescription) == offsetof(WGPUAdapterProperties, driverDescription),
            "offsetof mismatch for AdapterProperties::driverDescription");
    static_assert(offsetof(AdapterProperties, adapterType) == offsetof(WGPUAdapterProperties, adapterType),
            "offsetof mismatch for AdapterProperties::adapterType");
    static_assert(offsetof(AdapterProperties, backendType) == offsetof(WGPUAdapterProperties, backendType),
            "offsetof mismatch for AdapterProperties::backendType");


    static_assert(sizeof(BindGroupEntry) == sizeof(WGPUBindGroupEntry), "sizeof mismatch for BindGroupEntry");
    static_assert(alignof(BindGroupEntry) == alignof(WGPUBindGroupEntry), "alignof mismatch for BindGroupEntry");

    static_assert(offsetof(BindGroupEntry, binding) == offsetof(WGPUBindGroupEntry, binding),
            "offsetof mismatch for BindGroupEntry::binding");
    static_assert(offsetof(BindGroupEntry, buffer) == offsetof(WGPUBindGroupEntry, buffer),
            "offsetof mismatch for BindGroupEntry::buffer");
    static_assert(offsetof(BindGroupEntry, offset) == offsetof(WGPUBindGroupEntry, offset),
            "offsetof mismatch for BindGroupEntry::offset");
    static_assert(offsetof(BindGroupEntry, size) == offsetof(WGPUBindGroupEntry, size),
            "offsetof mismatch for BindGroupEntry::size");
    static_assert(offsetof(BindGroupEntry, sampler) == offsetof(WGPUBindGroupEntry, sampler),
            "offsetof mismatch for BindGroupEntry::sampler");
    static_assert(offsetof(BindGroupEntry, textureView) == offsetof(WGPUBindGroupEntry, textureView),
            "offsetof mismatch for BindGroupEntry::textureView");


    static_assert(sizeof(BindGroupLayoutEntry) == sizeof(WGPUBindGroupLayoutEntry), "sizeof mismatch for BindGroupLayoutEntry");
    static_assert(alignof(BindGroupLayoutEntry) == alignof(WGPUBindGroupLayoutEntry), "alignof mismatch for BindGroupLayoutEntry");

    static_assert(offsetof(BindGroupLayoutEntry, binding) == offsetof(WGPUBindGroupLayoutEntry, binding),
            "offsetof mismatch for BindGroupLayoutEntry::binding");
    static_assert(offsetof(BindGroupLayoutEntry, visibility) == offsetof(WGPUBindGroupLayoutEntry, visibility),
            "offsetof mismatch for BindGroupLayoutEntry::visibility");
    static_assert(offsetof(BindGroupLayoutEntry, type) == offsetof(WGPUBindGroupLayoutEntry, type),
            "offsetof mismatch for BindGroupLayoutEntry::type");
    static_assert(offsetof(BindGroupLayoutEntry, hasDynamicOffset) == offsetof(WGPUBindGroupLayoutEntry, hasDynamicOffset),
            "offsetof mismatch for BindGroupLayoutEntry::hasDynamicOffset");
    static_assert(offsetof(BindGroupLayoutEntry, minBufferBindingSize) == offsetof(WGPUBindGroupLayoutEntry, minBufferBindingSize),
            "offsetof mismatch for BindGroupLayoutEntry::minBufferBindingSize");
    static_assert(offsetof(BindGroupLayoutEntry, multisampled) == offsetof(WGPUBindGroupLayoutEntry, multisampled),
            "offsetof mismatch for BindGroupLayoutEntry::multisampled");
    static_assert(offsetof(BindGroupLayoutEntry, viewDimension) == offsetof(WGPUBindGroupLayoutEntry, viewDimension),
            "offsetof mismatch for BindGroupLayoutEntry::viewDimension");
    static_assert(offsetof(BindGroupLayoutEntry, textureComponentType) == offsetof(WGPUBindGroupLayoutEntry, textureComponentType),
            "offsetof mismatch for BindGroupLayoutEntry::textureComponentType");
    static_assert(offsetof(BindGroupLayoutEntry, storageTextureFormat) == offsetof(WGPUBindGroupLayoutEntry, storageTextureFormat),
            "offsetof mismatch for BindGroupLayoutEntry::storageTextureFormat");


    static_assert(sizeof(BlendDescriptor) == sizeof(WGPUBlendDescriptor), "sizeof mismatch for BlendDescriptor");
    static_assert(alignof(BlendDescriptor) == alignof(WGPUBlendDescriptor), "alignof mismatch for BlendDescriptor");

    static_assert(offsetof(BlendDescriptor, operation) == offsetof(WGPUBlendDescriptor, operation),
            "offsetof mismatch for BlendDescriptor::operation");
    static_assert(offsetof(BlendDescriptor, srcFactor) == offsetof(WGPUBlendDescriptor, srcFactor),
            "offsetof mismatch for BlendDescriptor::srcFactor");
    static_assert(offsetof(BlendDescriptor, dstFactor) == offsetof(WGPUBlendDescriptor, dstFactor),
            "offsetof mismatch for BlendDescriptor::dstFactor");


    static_assert(sizeof(BufferDescriptor) == sizeof(WGPUBufferDescriptor), "sizeof mismatch for BufferDescriptor");
    static_assert(alignof(BufferDescriptor) == alignof(WGPUBufferDescriptor), "alignof mismatch for BufferDescriptor");

    static_assert(offsetof(BufferDescriptor, nextInChain) == offsetof(WGPUBufferDescriptor, nextInChain),
            "offsetof mismatch for BufferDescriptor::nextInChain");
    static_assert(offsetof(BufferDescriptor, label) == offsetof(WGPUBufferDescriptor, label),
            "offsetof mismatch for BufferDescriptor::label");
    static_assert(offsetof(BufferDescriptor, usage) == offsetof(WGPUBufferDescriptor, usage),
            "offsetof mismatch for BufferDescriptor::usage");
    static_assert(offsetof(BufferDescriptor, size) == offsetof(WGPUBufferDescriptor, size),
            "offsetof mismatch for BufferDescriptor::size");
    static_assert(offsetof(BufferDescriptor, mappedAtCreation) == offsetof(WGPUBufferDescriptor, mappedAtCreation),
            "offsetof mismatch for BufferDescriptor::mappedAtCreation");


    static_assert(sizeof(Color) == sizeof(WGPUColor), "sizeof mismatch for Color");
    static_assert(alignof(Color) == alignof(WGPUColor), "alignof mismatch for Color");

    static_assert(offsetof(Color, r) == offsetof(WGPUColor, r),
            "offsetof mismatch for Color::r");
    static_assert(offsetof(Color, g) == offsetof(WGPUColor, g),
            "offsetof mismatch for Color::g");
    static_assert(offsetof(Color, b) == offsetof(WGPUColor, b),
            "offsetof mismatch for Color::b");
    static_assert(offsetof(Color, a) == offsetof(WGPUColor, a),
            "offsetof mismatch for Color::a");


    static_assert(sizeof(CommandBufferDescriptor) == sizeof(WGPUCommandBufferDescriptor), "sizeof mismatch for CommandBufferDescriptor");
    static_assert(alignof(CommandBufferDescriptor) == alignof(WGPUCommandBufferDescriptor), "alignof mismatch for CommandBufferDescriptor");

    static_assert(offsetof(CommandBufferDescriptor, nextInChain) == offsetof(WGPUCommandBufferDescriptor, nextInChain),
            "offsetof mismatch for CommandBufferDescriptor::nextInChain");
    static_assert(offsetof(CommandBufferDescriptor, label) == offsetof(WGPUCommandBufferDescriptor, label),
            "offsetof mismatch for CommandBufferDescriptor::label");


    static_assert(sizeof(CommandEncoderDescriptor) == sizeof(WGPUCommandEncoderDescriptor), "sizeof mismatch for CommandEncoderDescriptor");
    static_assert(alignof(CommandEncoderDescriptor) == alignof(WGPUCommandEncoderDescriptor), "alignof mismatch for CommandEncoderDescriptor");

    static_assert(offsetof(CommandEncoderDescriptor, nextInChain) == offsetof(WGPUCommandEncoderDescriptor, nextInChain),
            "offsetof mismatch for CommandEncoderDescriptor::nextInChain");
    static_assert(offsetof(CommandEncoderDescriptor, label) == offsetof(WGPUCommandEncoderDescriptor, label),
            "offsetof mismatch for CommandEncoderDescriptor::label");


    static_assert(sizeof(ComputePassDescriptor) == sizeof(WGPUComputePassDescriptor), "sizeof mismatch for ComputePassDescriptor");
    static_assert(alignof(ComputePassDescriptor) == alignof(WGPUComputePassDescriptor), "alignof mismatch for ComputePassDescriptor");

    static_assert(offsetof(ComputePassDescriptor, nextInChain) == offsetof(WGPUComputePassDescriptor, nextInChain),
            "offsetof mismatch for ComputePassDescriptor::nextInChain");
    static_assert(offsetof(ComputePassDescriptor, label) == offsetof(WGPUComputePassDescriptor, label),
            "offsetof mismatch for ComputePassDescriptor::label");


    static_assert(sizeof(DeviceProperties) == sizeof(WGPUDeviceProperties), "sizeof mismatch for DeviceProperties");
    static_assert(alignof(DeviceProperties) == alignof(WGPUDeviceProperties), "alignof mismatch for DeviceProperties");

    static_assert(offsetof(DeviceProperties, textureCompressionBC) == offsetof(WGPUDeviceProperties, textureCompressionBC),
            "offsetof mismatch for DeviceProperties::textureCompressionBC");
    static_assert(offsetof(DeviceProperties, shaderFloat16) == offsetof(WGPUDeviceProperties, shaderFloat16),
            "offsetof mismatch for DeviceProperties::shaderFloat16");
    static_assert(offsetof(DeviceProperties, pipelineStatisticsQuery) == offsetof(WGPUDeviceProperties, pipelineStatisticsQuery),
            "offsetof mismatch for DeviceProperties::pipelineStatisticsQuery");
    static_assert(offsetof(DeviceProperties, timestampQuery) == offsetof(WGPUDeviceProperties, timestampQuery),
            "offsetof mismatch for DeviceProperties::timestampQuery");


    static_assert(sizeof(Extent3D) == sizeof(WGPUExtent3D), "sizeof mismatch for Extent3D");
    static_assert(alignof(Extent3D) == alignof(WGPUExtent3D), "alignof mismatch for Extent3D");

    static_assert(offsetof(Extent3D, width) == offsetof(WGPUExtent3D, width),
            "offsetof mismatch for Extent3D::width");
    static_assert(offsetof(Extent3D, height) == offsetof(WGPUExtent3D, height),
            "offsetof mismatch for Extent3D::height");
    static_assert(offsetof(Extent3D, depth) == offsetof(WGPUExtent3D, depth),
            "offsetof mismatch for Extent3D::depth");


    static_assert(sizeof(FenceDescriptor) == sizeof(WGPUFenceDescriptor), "sizeof mismatch for FenceDescriptor");
    static_assert(alignof(FenceDescriptor) == alignof(WGPUFenceDescriptor), "alignof mismatch for FenceDescriptor");

    static_assert(offsetof(FenceDescriptor, nextInChain) == offsetof(WGPUFenceDescriptor, nextInChain),
            "offsetof mismatch for FenceDescriptor::nextInChain");
    static_assert(offsetof(FenceDescriptor, label) == offsetof(WGPUFenceDescriptor, label),
            "offsetof mismatch for FenceDescriptor::label");
    static_assert(offsetof(FenceDescriptor, initialValue) == offsetof(WGPUFenceDescriptor, initialValue),
            "offsetof mismatch for FenceDescriptor::initialValue");


    static_assert(sizeof(InstanceDescriptor) == sizeof(WGPUInstanceDescriptor), "sizeof mismatch for InstanceDescriptor");
    static_assert(alignof(InstanceDescriptor) == alignof(WGPUInstanceDescriptor), "alignof mismatch for InstanceDescriptor");

    static_assert(offsetof(InstanceDescriptor, nextInChain) == offsetof(WGPUInstanceDescriptor, nextInChain),
            "offsetof mismatch for InstanceDescriptor::nextInChain");


    static_assert(sizeof(Origin3D) == sizeof(WGPUOrigin3D), "sizeof mismatch for Origin3D");
    static_assert(alignof(Origin3D) == alignof(WGPUOrigin3D), "alignof mismatch for Origin3D");

    static_assert(offsetof(Origin3D, x) == offsetof(WGPUOrigin3D, x),
            "offsetof mismatch for Origin3D::x");
    static_assert(offsetof(Origin3D, y) == offsetof(WGPUOrigin3D, y),
            "offsetof mismatch for Origin3D::y");
    static_assert(offsetof(Origin3D, z) == offsetof(WGPUOrigin3D, z),
            "offsetof mismatch for Origin3D::z");


    static_assert(sizeof(PipelineLayoutDescriptor) == sizeof(WGPUPipelineLayoutDescriptor), "sizeof mismatch for PipelineLayoutDescriptor");
    static_assert(alignof(PipelineLayoutDescriptor) == alignof(WGPUPipelineLayoutDescriptor), "alignof mismatch for PipelineLayoutDescriptor");

    static_assert(offsetof(PipelineLayoutDescriptor, nextInChain) == offsetof(WGPUPipelineLayoutDescriptor, nextInChain),
            "offsetof mismatch for PipelineLayoutDescriptor::nextInChain");
    static_assert(offsetof(PipelineLayoutDescriptor, label) == offsetof(WGPUPipelineLayoutDescriptor, label),
            "offsetof mismatch for PipelineLayoutDescriptor::label");
    static_assert(offsetof(PipelineLayoutDescriptor, bindGroupLayoutCount) == offsetof(WGPUPipelineLayoutDescriptor, bindGroupLayoutCount),
            "offsetof mismatch for PipelineLayoutDescriptor::bindGroupLayoutCount");
    static_assert(offsetof(PipelineLayoutDescriptor, bindGroupLayouts) == offsetof(WGPUPipelineLayoutDescriptor, bindGroupLayouts),
            "offsetof mismatch for PipelineLayoutDescriptor::bindGroupLayouts");


    static_assert(sizeof(ProgrammableStageDescriptor) == sizeof(WGPUProgrammableStageDescriptor), "sizeof mismatch for ProgrammableStageDescriptor");
    static_assert(alignof(ProgrammableStageDescriptor) == alignof(WGPUProgrammableStageDescriptor), "alignof mismatch for ProgrammableStageDescriptor");

    static_assert(offsetof(ProgrammableStageDescriptor, nextInChain) == offsetof(WGPUProgrammableStageDescriptor, nextInChain),
            "offsetof mismatch for ProgrammableStageDescriptor::nextInChain");
    static_assert(offsetof(ProgrammableStageDescriptor, module) == offsetof(WGPUProgrammableStageDescriptor, module),
            "offsetof mismatch for ProgrammableStageDescriptor::module");
    static_assert(offsetof(ProgrammableStageDescriptor, entryPoint) == offsetof(WGPUProgrammableStageDescriptor, entryPoint),
            "offsetof mismatch for ProgrammableStageDescriptor::entryPoint");


    static_assert(sizeof(QuerySetDescriptor) == sizeof(WGPUQuerySetDescriptor), "sizeof mismatch for QuerySetDescriptor");
    static_assert(alignof(QuerySetDescriptor) == alignof(WGPUQuerySetDescriptor), "alignof mismatch for QuerySetDescriptor");

    static_assert(offsetof(QuerySetDescriptor, nextInChain) == offsetof(WGPUQuerySetDescriptor, nextInChain),
            "offsetof mismatch for QuerySetDescriptor::nextInChain");
    static_assert(offsetof(QuerySetDescriptor, label) == offsetof(WGPUQuerySetDescriptor, label),
            "offsetof mismatch for QuerySetDescriptor::label");
    static_assert(offsetof(QuerySetDescriptor, type) == offsetof(WGPUQuerySetDescriptor, type),
            "offsetof mismatch for QuerySetDescriptor::type");
    static_assert(offsetof(QuerySetDescriptor, count) == offsetof(WGPUQuerySetDescriptor, count),
            "offsetof mismatch for QuerySetDescriptor::count");
    static_assert(offsetof(QuerySetDescriptor, pipelineStatistics) == offsetof(WGPUQuerySetDescriptor, pipelineStatistics),
            "offsetof mismatch for QuerySetDescriptor::pipelineStatistics");
    static_assert(offsetof(QuerySetDescriptor, pipelineStatisticsCount) == offsetof(WGPUQuerySetDescriptor, pipelineStatisticsCount),
            "offsetof mismatch for QuerySetDescriptor::pipelineStatisticsCount");


    static_assert(sizeof(RasterizationStateDescriptor) == sizeof(WGPURasterizationStateDescriptor), "sizeof mismatch for RasterizationStateDescriptor");
    static_assert(alignof(RasterizationStateDescriptor) == alignof(WGPURasterizationStateDescriptor), "alignof mismatch for RasterizationStateDescriptor");

    static_assert(offsetof(RasterizationStateDescriptor, nextInChain) == offsetof(WGPURasterizationStateDescriptor, nextInChain),
            "offsetof mismatch for RasterizationStateDescriptor::nextInChain");
    static_assert(offsetof(RasterizationStateDescriptor, frontFace) == offsetof(WGPURasterizationStateDescriptor, frontFace),
            "offsetof mismatch for RasterizationStateDescriptor::frontFace");
    static_assert(offsetof(RasterizationStateDescriptor, cullMode) == offsetof(WGPURasterizationStateDescriptor, cullMode),
            "offsetof mismatch for RasterizationStateDescriptor::cullMode");
    static_assert(offsetof(RasterizationStateDescriptor, depthBias) == offsetof(WGPURasterizationStateDescriptor, depthBias),
            "offsetof mismatch for RasterizationStateDescriptor::depthBias");
    static_assert(offsetof(RasterizationStateDescriptor, depthBiasSlopeScale) == offsetof(WGPURasterizationStateDescriptor, depthBiasSlopeScale),
            "offsetof mismatch for RasterizationStateDescriptor::depthBiasSlopeScale");
    static_assert(offsetof(RasterizationStateDescriptor, depthBiasClamp) == offsetof(WGPURasterizationStateDescriptor, depthBiasClamp),
            "offsetof mismatch for RasterizationStateDescriptor::depthBiasClamp");


    static_assert(sizeof(RenderBundleDescriptor) == sizeof(WGPURenderBundleDescriptor), "sizeof mismatch for RenderBundleDescriptor");
    static_assert(alignof(RenderBundleDescriptor) == alignof(WGPURenderBundleDescriptor), "alignof mismatch for RenderBundleDescriptor");

    static_assert(offsetof(RenderBundleDescriptor, nextInChain) == offsetof(WGPURenderBundleDescriptor, nextInChain),
            "offsetof mismatch for RenderBundleDescriptor::nextInChain");
    static_assert(offsetof(RenderBundleDescriptor, label) == offsetof(WGPURenderBundleDescriptor, label),
            "offsetof mismatch for RenderBundleDescriptor::label");


    static_assert(sizeof(RenderBundleEncoderDescriptor) == sizeof(WGPURenderBundleEncoderDescriptor), "sizeof mismatch for RenderBundleEncoderDescriptor");
    static_assert(alignof(RenderBundleEncoderDescriptor) == alignof(WGPURenderBundleEncoderDescriptor), "alignof mismatch for RenderBundleEncoderDescriptor");

    static_assert(offsetof(RenderBundleEncoderDescriptor, nextInChain) == offsetof(WGPURenderBundleEncoderDescriptor, nextInChain),
            "offsetof mismatch for RenderBundleEncoderDescriptor::nextInChain");
    static_assert(offsetof(RenderBundleEncoderDescriptor, label) == offsetof(WGPURenderBundleEncoderDescriptor, label),
            "offsetof mismatch for RenderBundleEncoderDescriptor::label");
    static_assert(offsetof(RenderBundleEncoderDescriptor, colorFormatsCount) == offsetof(WGPURenderBundleEncoderDescriptor, colorFormatsCount),
            "offsetof mismatch for RenderBundleEncoderDescriptor::colorFormatsCount");
    static_assert(offsetof(RenderBundleEncoderDescriptor, colorFormats) == offsetof(WGPURenderBundleEncoderDescriptor, colorFormats),
            "offsetof mismatch for RenderBundleEncoderDescriptor::colorFormats");
    static_assert(offsetof(RenderBundleEncoderDescriptor, depthStencilFormat) == offsetof(WGPURenderBundleEncoderDescriptor, depthStencilFormat),
            "offsetof mismatch for RenderBundleEncoderDescriptor::depthStencilFormat");
    static_assert(offsetof(RenderBundleEncoderDescriptor, sampleCount) == offsetof(WGPURenderBundleEncoderDescriptor, sampleCount),
            "offsetof mismatch for RenderBundleEncoderDescriptor::sampleCount");


    static_assert(sizeof(RenderPassDepthStencilAttachmentDescriptor) == sizeof(WGPURenderPassDepthStencilAttachmentDescriptor), "sizeof mismatch for RenderPassDepthStencilAttachmentDescriptor");
    static_assert(alignof(RenderPassDepthStencilAttachmentDescriptor) == alignof(WGPURenderPassDepthStencilAttachmentDescriptor), "alignof mismatch for RenderPassDepthStencilAttachmentDescriptor");

    static_assert(offsetof(RenderPassDepthStencilAttachmentDescriptor, attachment) == offsetof(WGPURenderPassDepthStencilAttachmentDescriptor, attachment),
            "offsetof mismatch for RenderPassDepthStencilAttachmentDescriptor::attachment");
    static_assert(offsetof(RenderPassDepthStencilAttachmentDescriptor, depthLoadOp) == offsetof(WGPURenderPassDepthStencilAttachmentDescriptor, depthLoadOp),
            "offsetof mismatch for RenderPassDepthStencilAttachmentDescriptor::depthLoadOp");
    static_assert(offsetof(RenderPassDepthStencilAttachmentDescriptor, depthStoreOp) == offsetof(WGPURenderPassDepthStencilAttachmentDescriptor, depthStoreOp),
            "offsetof mismatch for RenderPassDepthStencilAttachmentDescriptor::depthStoreOp");
    static_assert(offsetof(RenderPassDepthStencilAttachmentDescriptor, clearDepth) == offsetof(WGPURenderPassDepthStencilAttachmentDescriptor, clearDepth),
            "offsetof mismatch for RenderPassDepthStencilAttachmentDescriptor::clearDepth");
    static_assert(offsetof(RenderPassDepthStencilAttachmentDescriptor, depthReadOnly) == offsetof(WGPURenderPassDepthStencilAttachmentDescriptor, depthReadOnly),
            "offsetof mismatch for RenderPassDepthStencilAttachmentDescriptor::depthReadOnly");
    static_assert(offsetof(RenderPassDepthStencilAttachmentDescriptor, stencilLoadOp) == offsetof(WGPURenderPassDepthStencilAttachmentDescriptor, stencilLoadOp),
            "offsetof mismatch for RenderPassDepthStencilAttachmentDescriptor::stencilLoadOp");
    static_assert(offsetof(RenderPassDepthStencilAttachmentDescriptor, stencilStoreOp) == offsetof(WGPURenderPassDepthStencilAttachmentDescriptor, stencilStoreOp),
            "offsetof mismatch for RenderPassDepthStencilAttachmentDescriptor::stencilStoreOp");
    static_assert(offsetof(RenderPassDepthStencilAttachmentDescriptor, clearStencil) == offsetof(WGPURenderPassDepthStencilAttachmentDescriptor, clearStencil),
            "offsetof mismatch for RenderPassDepthStencilAttachmentDescriptor::clearStencil");
    static_assert(offsetof(RenderPassDepthStencilAttachmentDescriptor, stencilReadOnly) == offsetof(WGPURenderPassDepthStencilAttachmentDescriptor, stencilReadOnly),
            "offsetof mismatch for RenderPassDepthStencilAttachmentDescriptor::stencilReadOnly");


    static_assert(sizeof(SamplerDescriptor) == sizeof(WGPUSamplerDescriptor), "sizeof mismatch for SamplerDescriptor");
    static_assert(alignof(SamplerDescriptor) == alignof(WGPUSamplerDescriptor), "alignof mismatch for SamplerDescriptor");

    static_assert(offsetof(SamplerDescriptor, nextInChain) == offsetof(WGPUSamplerDescriptor, nextInChain),
            "offsetof mismatch for SamplerDescriptor::nextInChain");
    static_assert(offsetof(SamplerDescriptor, label) == offsetof(WGPUSamplerDescriptor, label),
            "offsetof mismatch for SamplerDescriptor::label");
    static_assert(offsetof(SamplerDescriptor, addressModeU) == offsetof(WGPUSamplerDescriptor, addressModeU),
            "offsetof mismatch for SamplerDescriptor::addressModeU");
    static_assert(offsetof(SamplerDescriptor, addressModeV) == offsetof(WGPUSamplerDescriptor, addressModeV),
            "offsetof mismatch for SamplerDescriptor::addressModeV");
    static_assert(offsetof(SamplerDescriptor, addressModeW) == offsetof(WGPUSamplerDescriptor, addressModeW),
            "offsetof mismatch for SamplerDescriptor::addressModeW");
    static_assert(offsetof(SamplerDescriptor, magFilter) == offsetof(WGPUSamplerDescriptor, magFilter),
            "offsetof mismatch for SamplerDescriptor::magFilter");
    static_assert(offsetof(SamplerDescriptor, minFilter) == offsetof(WGPUSamplerDescriptor, minFilter),
            "offsetof mismatch for SamplerDescriptor::minFilter");
    static_assert(offsetof(SamplerDescriptor, mipmapFilter) == offsetof(WGPUSamplerDescriptor, mipmapFilter),
            "offsetof mismatch for SamplerDescriptor::mipmapFilter");
    static_assert(offsetof(SamplerDescriptor, lodMinClamp) == offsetof(WGPUSamplerDescriptor, lodMinClamp),
            "offsetof mismatch for SamplerDescriptor::lodMinClamp");
    static_assert(offsetof(SamplerDescriptor, lodMaxClamp) == offsetof(WGPUSamplerDescriptor, lodMaxClamp),
            "offsetof mismatch for SamplerDescriptor::lodMaxClamp");
    static_assert(offsetof(SamplerDescriptor, compare) == offsetof(WGPUSamplerDescriptor, compare),
            "offsetof mismatch for SamplerDescriptor::compare");


    static_assert(sizeof(SamplerDescriptorDummyAnisotropicFiltering) == sizeof(WGPUSamplerDescriptorDummyAnisotropicFiltering), "sizeof mismatch for SamplerDescriptorDummyAnisotropicFiltering");
    static_assert(alignof(SamplerDescriptorDummyAnisotropicFiltering) == alignof(WGPUSamplerDescriptorDummyAnisotropicFiltering), "alignof mismatch for SamplerDescriptorDummyAnisotropicFiltering");

    static_assert(offsetof(SamplerDescriptorDummyAnisotropicFiltering, maxAnisotropy) == offsetof(WGPUSamplerDescriptorDummyAnisotropicFiltering, maxAnisotropy),
            "offsetof mismatch for SamplerDescriptorDummyAnisotropicFiltering::maxAnisotropy");


    static_assert(sizeof(ShaderModuleDescriptor) == sizeof(WGPUShaderModuleDescriptor), "sizeof mismatch for ShaderModuleDescriptor");
    static_assert(alignof(ShaderModuleDescriptor) == alignof(WGPUShaderModuleDescriptor), "alignof mismatch for ShaderModuleDescriptor");

    static_assert(offsetof(ShaderModuleDescriptor, nextInChain) == offsetof(WGPUShaderModuleDescriptor, nextInChain),
            "offsetof mismatch for ShaderModuleDescriptor::nextInChain");
    static_assert(offsetof(ShaderModuleDescriptor, label) == offsetof(WGPUShaderModuleDescriptor, label),
            "offsetof mismatch for ShaderModuleDescriptor::label");


    static_assert(sizeof(ShaderModuleSPIRVDescriptor) == sizeof(WGPUShaderModuleSPIRVDescriptor), "sizeof mismatch for ShaderModuleSPIRVDescriptor");
    static_assert(alignof(ShaderModuleSPIRVDescriptor) == alignof(WGPUShaderModuleSPIRVDescriptor), "alignof mismatch for ShaderModuleSPIRVDescriptor");

    static_assert(offsetof(ShaderModuleSPIRVDescriptor, codeSize) == offsetof(WGPUShaderModuleSPIRVDescriptor, codeSize),
            "offsetof mismatch for ShaderModuleSPIRVDescriptor::codeSize");
    static_assert(offsetof(ShaderModuleSPIRVDescriptor, code) == offsetof(WGPUShaderModuleSPIRVDescriptor, code),
            "offsetof mismatch for ShaderModuleSPIRVDescriptor::code");


    static_assert(sizeof(ShaderModuleWGSLDescriptor) == sizeof(WGPUShaderModuleWGSLDescriptor), "sizeof mismatch for ShaderModuleWGSLDescriptor");
    static_assert(alignof(ShaderModuleWGSLDescriptor) == alignof(WGPUShaderModuleWGSLDescriptor), "alignof mismatch for ShaderModuleWGSLDescriptor");

    static_assert(offsetof(ShaderModuleWGSLDescriptor, source) == offsetof(WGPUShaderModuleWGSLDescriptor, source),
            "offsetof mismatch for ShaderModuleWGSLDescriptor::source");


    static_assert(sizeof(StencilStateFaceDescriptor) == sizeof(WGPUStencilStateFaceDescriptor), "sizeof mismatch for StencilStateFaceDescriptor");
    static_assert(alignof(StencilStateFaceDescriptor) == alignof(WGPUStencilStateFaceDescriptor), "alignof mismatch for StencilStateFaceDescriptor");

    static_assert(offsetof(StencilStateFaceDescriptor, compare) == offsetof(WGPUStencilStateFaceDescriptor, compare),
            "offsetof mismatch for StencilStateFaceDescriptor::compare");
    static_assert(offsetof(StencilStateFaceDescriptor, failOp) == offsetof(WGPUStencilStateFaceDescriptor, failOp),
            "offsetof mismatch for StencilStateFaceDescriptor::failOp");
    static_assert(offsetof(StencilStateFaceDescriptor, depthFailOp) == offsetof(WGPUStencilStateFaceDescriptor, depthFailOp),
            "offsetof mismatch for StencilStateFaceDescriptor::depthFailOp");
    static_assert(offsetof(StencilStateFaceDescriptor, passOp) == offsetof(WGPUStencilStateFaceDescriptor, passOp),
            "offsetof mismatch for StencilStateFaceDescriptor::passOp");


    static_assert(sizeof(SurfaceDescriptor) == sizeof(WGPUSurfaceDescriptor), "sizeof mismatch for SurfaceDescriptor");
    static_assert(alignof(SurfaceDescriptor) == alignof(WGPUSurfaceDescriptor), "alignof mismatch for SurfaceDescriptor");

    static_assert(offsetof(SurfaceDescriptor, nextInChain) == offsetof(WGPUSurfaceDescriptor, nextInChain),
            "offsetof mismatch for SurfaceDescriptor::nextInChain");
    static_assert(offsetof(SurfaceDescriptor, label) == offsetof(WGPUSurfaceDescriptor, label),
            "offsetof mismatch for SurfaceDescriptor::label");


    static_assert(sizeof(SurfaceDescriptorFromCanvasHTMLSelector) == sizeof(WGPUSurfaceDescriptorFromCanvasHTMLSelector), "sizeof mismatch for SurfaceDescriptorFromCanvasHTMLSelector");
    static_assert(alignof(SurfaceDescriptorFromCanvasHTMLSelector) == alignof(WGPUSurfaceDescriptorFromCanvasHTMLSelector), "alignof mismatch for SurfaceDescriptorFromCanvasHTMLSelector");

    static_assert(offsetof(SurfaceDescriptorFromCanvasHTMLSelector, selector) == offsetof(WGPUSurfaceDescriptorFromCanvasHTMLSelector, selector),
            "offsetof mismatch for SurfaceDescriptorFromCanvasHTMLSelector::selector");


    static_assert(sizeof(SurfaceDescriptorFromMetalLayer) == sizeof(WGPUSurfaceDescriptorFromMetalLayer), "sizeof mismatch for SurfaceDescriptorFromMetalLayer");
    static_assert(alignof(SurfaceDescriptorFromMetalLayer) == alignof(WGPUSurfaceDescriptorFromMetalLayer), "alignof mismatch for SurfaceDescriptorFromMetalLayer");

    static_assert(offsetof(SurfaceDescriptorFromMetalLayer, layer) == offsetof(WGPUSurfaceDescriptorFromMetalLayer, layer),
            "offsetof mismatch for SurfaceDescriptorFromMetalLayer::layer");


    static_assert(sizeof(SurfaceDescriptorFromWindowsHWND) == sizeof(WGPUSurfaceDescriptorFromWindowsHWND), "sizeof mismatch for SurfaceDescriptorFromWindowsHWND");
    static_assert(alignof(SurfaceDescriptorFromWindowsHWND) == alignof(WGPUSurfaceDescriptorFromWindowsHWND), "alignof mismatch for SurfaceDescriptorFromWindowsHWND");

    static_assert(offsetof(SurfaceDescriptorFromWindowsHWND, hinstance) == offsetof(WGPUSurfaceDescriptorFromWindowsHWND, hinstance),
            "offsetof mismatch for SurfaceDescriptorFromWindowsHWND::hinstance");
    static_assert(offsetof(SurfaceDescriptorFromWindowsHWND, hwnd) == offsetof(WGPUSurfaceDescriptorFromWindowsHWND, hwnd),
            "offsetof mismatch for SurfaceDescriptorFromWindowsHWND::hwnd");


    static_assert(sizeof(SurfaceDescriptorFromXlib) == sizeof(WGPUSurfaceDescriptorFromXlib), "sizeof mismatch for SurfaceDescriptorFromXlib");
    static_assert(alignof(SurfaceDescriptorFromXlib) == alignof(WGPUSurfaceDescriptorFromXlib), "alignof mismatch for SurfaceDescriptorFromXlib");

    static_assert(offsetof(SurfaceDescriptorFromXlib, display) == offsetof(WGPUSurfaceDescriptorFromXlib, display),
            "offsetof mismatch for SurfaceDescriptorFromXlib::display");
    static_assert(offsetof(SurfaceDescriptorFromXlib, window) == offsetof(WGPUSurfaceDescriptorFromXlib, window),
            "offsetof mismatch for SurfaceDescriptorFromXlib::window");


    static_assert(sizeof(SwapChainDescriptor) == sizeof(WGPUSwapChainDescriptor), "sizeof mismatch for SwapChainDescriptor");
    static_assert(alignof(SwapChainDescriptor) == alignof(WGPUSwapChainDescriptor), "alignof mismatch for SwapChainDescriptor");

    static_assert(offsetof(SwapChainDescriptor, nextInChain) == offsetof(WGPUSwapChainDescriptor, nextInChain),
            "offsetof mismatch for SwapChainDescriptor::nextInChain");
    static_assert(offsetof(SwapChainDescriptor, label) == offsetof(WGPUSwapChainDescriptor, label),
            "offsetof mismatch for SwapChainDescriptor::label");
    static_assert(offsetof(SwapChainDescriptor, usage) == offsetof(WGPUSwapChainDescriptor, usage),
            "offsetof mismatch for SwapChainDescriptor::usage");
    static_assert(offsetof(SwapChainDescriptor, format) == offsetof(WGPUSwapChainDescriptor, format),
            "offsetof mismatch for SwapChainDescriptor::format");
    static_assert(offsetof(SwapChainDescriptor, width) == offsetof(WGPUSwapChainDescriptor, width),
            "offsetof mismatch for SwapChainDescriptor::width");
    static_assert(offsetof(SwapChainDescriptor, height) == offsetof(WGPUSwapChainDescriptor, height),
            "offsetof mismatch for SwapChainDescriptor::height");
    static_assert(offsetof(SwapChainDescriptor, presentMode) == offsetof(WGPUSwapChainDescriptor, presentMode),
            "offsetof mismatch for SwapChainDescriptor::presentMode");
    static_assert(offsetof(SwapChainDescriptor, implementation) == offsetof(WGPUSwapChainDescriptor, implementation),
            "offsetof mismatch for SwapChainDescriptor::implementation");


    static_assert(sizeof(TextureDataLayout) == sizeof(WGPUTextureDataLayout), "sizeof mismatch for TextureDataLayout");
    static_assert(alignof(TextureDataLayout) == alignof(WGPUTextureDataLayout), "alignof mismatch for TextureDataLayout");

    static_assert(offsetof(TextureDataLayout, nextInChain) == offsetof(WGPUTextureDataLayout, nextInChain),
            "offsetof mismatch for TextureDataLayout::nextInChain");
    static_assert(offsetof(TextureDataLayout, offset) == offsetof(WGPUTextureDataLayout, offset),
            "offsetof mismatch for TextureDataLayout::offset");
    static_assert(offsetof(TextureDataLayout, bytesPerRow) == offsetof(WGPUTextureDataLayout, bytesPerRow),
            "offsetof mismatch for TextureDataLayout::bytesPerRow");
    static_assert(offsetof(TextureDataLayout, rowsPerImage) == offsetof(WGPUTextureDataLayout, rowsPerImage),
            "offsetof mismatch for TextureDataLayout::rowsPerImage");


    static_assert(sizeof(TextureViewDescriptor) == sizeof(WGPUTextureViewDescriptor), "sizeof mismatch for TextureViewDescriptor");
    static_assert(alignof(TextureViewDescriptor) == alignof(WGPUTextureViewDescriptor), "alignof mismatch for TextureViewDescriptor");

    static_assert(offsetof(TextureViewDescriptor, nextInChain) == offsetof(WGPUTextureViewDescriptor, nextInChain),
            "offsetof mismatch for TextureViewDescriptor::nextInChain");
    static_assert(offsetof(TextureViewDescriptor, label) == offsetof(WGPUTextureViewDescriptor, label),
            "offsetof mismatch for TextureViewDescriptor::label");
    static_assert(offsetof(TextureViewDescriptor, format) == offsetof(WGPUTextureViewDescriptor, format),
            "offsetof mismatch for TextureViewDescriptor::format");
    static_assert(offsetof(TextureViewDescriptor, dimension) == offsetof(WGPUTextureViewDescriptor, dimension),
            "offsetof mismatch for TextureViewDescriptor::dimension");
    static_assert(offsetof(TextureViewDescriptor, baseMipLevel) == offsetof(WGPUTextureViewDescriptor, baseMipLevel),
            "offsetof mismatch for TextureViewDescriptor::baseMipLevel");
    static_assert(offsetof(TextureViewDescriptor, mipLevelCount) == offsetof(WGPUTextureViewDescriptor, mipLevelCount),
            "offsetof mismatch for TextureViewDescriptor::mipLevelCount");
    static_assert(offsetof(TextureViewDescriptor, baseArrayLayer) == offsetof(WGPUTextureViewDescriptor, baseArrayLayer),
            "offsetof mismatch for TextureViewDescriptor::baseArrayLayer");
    static_assert(offsetof(TextureViewDescriptor, arrayLayerCount) == offsetof(WGPUTextureViewDescriptor, arrayLayerCount),
            "offsetof mismatch for TextureViewDescriptor::arrayLayerCount");
    static_assert(offsetof(TextureViewDescriptor, aspect) == offsetof(WGPUTextureViewDescriptor, aspect),
            "offsetof mismatch for TextureViewDescriptor::aspect");


    static_assert(sizeof(VertexAttributeDescriptor) == sizeof(WGPUVertexAttributeDescriptor), "sizeof mismatch for VertexAttributeDescriptor");
    static_assert(alignof(VertexAttributeDescriptor) == alignof(WGPUVertexAttributeDescriptor), "alignof mismatch for VertexAttributeDescriptor");

    static_assert(offsetof(VertexAttributeDescriptor, format) == offsetof(WGPUVertexAttributeDescriptor, format),
            "offsetof mismatch for VertexAttributeDescriptor::format");
    static_assert(offsetof(VertexAttributeDescriptor, offset) == offsetof(WGPUVertexAttributeDescriptor, offset),
            "offsetof mismatch for VertexAttributeDescriptor::offset");
    static_assert(offsetof(VertexAttributeDescriptor, shaderLocation) == offsetof(WGPUVertexAttributeDescriptor, shaderLocation),
            "offsetof mismatch for VertexAttributeDescriptor::shaderLocation");


    static_assert(sizeof(BindGroupDescriptor) == sizeof(WGPUBindGroupDescriptor), "sizeof mismatch for BindGroupDescriptor");
    static_assert(alignof(BindGroupDescriptor) == alignof(WGPUBindGroupDescriptor), "alignof mismatch for BindGroupDescriptor");

    static_assert(offsetof(BindGroupDescriptor, nextInChain) == offsetof(WGPUBindGroupDescriptor, nextInChain),
            "offsetof mismatch for BindGroupDescriptor::nextInChain");
    static_assert(offsetof(BindGroupDescriptor, label) == offsetof(WGPUBindGroupDescriptor, label),
            "offsetof mismatch for BindGroupDescriptor::label");
    static_assert(offsetof(BindGroupDescriptor, layout) == offsetof(WGPUBindGroupDescriptor, layout),
            "offsetof mismatch for BindGroupDescriptor::layout");
    static_assert(offsetof(BindGroupDescriptor, entryCount) == offsetof(WGPUBindGroupDescriptor, entryCount),
            "offsetof mismatch for BindGroupDescriptor::entryCount");
    static_assert(offsetof(BindGroupDescriptor, entries) == offsetof(WGPUBindGroupDescriptor, entries),
            "offsetof mismatch for BindGroupDescriptor::entries");


    static_assert(sizeof(BindGroupLayoutDescriptor) == sizeof(WGPUBindGroupLayoutDescriptor), "sizeof mismatch for BindGroupLayoutDescriptor");
    static_assert(alignof(BindGroupLayoutDescriptor) == alignof(WGPUBindGroupLayoutDescriptor), "alignof mismatch for BindGroupLayoutDescriptor");

    static_assert(offsetof(BindGroupLayoutDescriptor, nextInChain) == offsetof(WGPUBindGroupLayoutDescriptor, nextInChain),
            "offsetof mismatch for BindGroupLayoutDescriptor::nextInChain");
    static_assert(offsetof(BindGroupLayoutDescriptor, label) == offsetof(WGPUBindGroupLayoutDescriptor, label),
            "offsetof mismatch for BindGroupLayoutDescriptor::label");
    static_assert(offsetof(BindGroupLayoutDescriptor, entryCount) == offsetof(WGPUBindGroupLayoutDescriptor, entryCount),
            "offsetof mismatch for BindGroupLayoutDescriptor::entryCount");
    static_assert(offsetof(BindGroupLayoutDescriptor, entries) == offsetof(WGPUBindGroupLayoutDescriptor, entries),
            "offsetof mismatch for BindGroupLayoutDescriptor::entries");


    static_assert(sizeof(BufferCopyView) == sizeof(WGPUBufferCopyView), "sizeof mismatch for BufferCopyView");
    static_assert(alignof(BufferCopyView) == alignof(WGPUBufferCopyView), "alignof mismatch for BufferCopyView");

    static_assert(offsetof(BufferCopyView, nextInChain) == offsetof(WGPUBufferCopyView, nextInChain),
            "offsetof mismatch for BufferCopyView::nextInChain");
    static_assert(offsetof(BufferCopyView, layout) == offsetof(WGPUBufferCopyView, layout),
            "offsetof mismatch for BufferCopyView::layout");
    static_assert(offsetof(BufferCopyView, buffer) == offsetof(WGPUBufferCopyView, buffer),
            "offsetof mismatch for BufferCopyView::buffer");


    static_assert(sizeof(ColorStateDescriptor) == sizeof(WGPUColorStateDescriptor), "sizeof mismatch for ColorStateDescriptor");
    static_assert(alignof(ColorStateDescriptor) == alignof(WGPUColorStateDescriptor), "alignof mismatch for ColorStateDescriptor");

    static_assert(offsetof(ColorStateDescriptor, nextInChain) == offsetof(WGPUColorStateDescriptor, nextInChain),
            "offsetof mismatch for ColorStateDescriptor::nextInChain");
    static_assert(offsetof(ColorStateDescriptor, format) == offsetof(WGPUColorStateDescriptor, format),
            "offsetof mismatch for ColorStateDescriptor::format");
    static_assert(offsetof(ColorStateDescriptor, alphaBlend) == offsetof(WGPUColorStateDescriptor, alphaBlend),
            "offsetof mismatch for ColorStateDescriptor::alphaBlend");
    static_assert(offsetof(ColorStateDescriptor, colorBlend) == offsetof(WGPUColorStateDescriptor, colorBlend),
            "offsetof mismatch for ColorStateDescriptor::colorBlend");
    static_assert(offsetof(ColorStateDescriptor, writeMask) == offsetof(WGPUColorStateDescriptor, writeMask),
            "offsetof mismatch for ColorStateDescriptor::writeMask");


    static_assert(sizeof(ComputePipelineDescriptor) == sizeof(WGPUComputePipelineDescriptor), "sizeof mismatch for ComputePipelineDescriptor");
    static_assert(alignof(ComputePipelineDescriptor) == alignof(WGPUComputePipelineDescriptor), "alignof mismatch for ComputePipelineDescriptor");

    static_assert(offsetof(ComputePipelineDescriptor, nextInChain) == offsetof(WGPUComputePipelineDescriptor, nextInChain),
            "offsetof mismatch for ComputePipelineDescriptor::nextInChain");
    static_assert(offsetof(ComputePipelineDescriptor, label) == offsetof(WGPUComputePipelineDescriptor, label),
            "offsetof mismatch for ComputePipelineDescriptor::label");
    static_assert(offsetof(ComputePipelineDescriptor, layout) == offsetof(WGPUComputePipelineDescriptor, layout),
            "offsetof mismatch for ComputePipelineDescriptor::layout");
    static_assert(offsetof(ComputePipelineDescriptor, computeStage) == offsetof(WGPUComputePipelineDescriptor, computeStage),
            "offsetof mismatch for ComputePipelineDescriptor::computeStage");


    static_assert(sizeof(DepthStencilStateDescriptor) == sizeof(WGPUDepthStencilStateDescriptor), "sizeof mismatch for DepthStencilStateDescriptor");
    static_assert(alignof(DepthStencilStateDescriptor) == alignof(WGPUDepthStencilStateDescriptor), "alignof mismatch for DepthStencilStateDescriptor");

    static_assert(offsetof(DepthStencilStateDescriptor, nextInChain) == offsetof(WGPUDepthStencilStateDescriptor, nextInChain),
            "offsetof mismatch for DepthStencilStateDescriptor::nextInChain");
    static_assert(offsetof(DepthStencilStateDescriptor, format) == offsetof(WGPUDepthStencilStateDescriptor, format),
            "offsetof mismatch for DepthStencilStateDescriptor::format");
    static_assert(offsetof(DepthStencilStateDescriptor, depthWriteEnabled) == offsetof(WGPUDepthStencilStateDescriptor, depthWriteEnabled),
            "offsetof mismatch for DepthStencilStateDescriptor::depthWriteEnabled");
    static_assert(offsetof(DepthStencilStateDescriptor, depthCompare) == offsetof(WGPUDepthStencilStateDescriptor, depthCompare),
            "offsetof mismatch for DepthStencilStateDescriptor::depthCompare");
    static_assert(offsetof(DepthStencilStateDescriptor, stencilFront) == offsetof(WGPUDepthStencilStateDescriptor, stencilFront),
            "offsetof mismatch for DepthStencilStateDescriptor::stencilFront");
    static_assert(offsetof(DepthStencilStateDescriptor, stencilBack) == offsetof(WGPUDepthStencilStateDescriptor, stencilBack),
            "offsetof mismatch for DepthStencilStateDescriptor::stencilBack");
    static_assert(offsetof(DepthStencilStateDescriptor, stencilReadMask) == offsetof(WGPUDepthStencilStateDescriptor, stencilReadMask),
            "offsetof mismatch for DepthStencilStateDescriptor::stencilReadMask");
    static_assert(offsetof(DepthStencilStateDescriptor, stencilWriteMask) == offsetof(WGPUDepthStencilStateDescriptor, stencilWriteMask),
            "offsetof mismatch for DepthStencilStateDescriptor::stencilWriteMask");


    static_assert(sizeof(RenderPassColorAttachmentDescriptor) == sizeof(WGPURenderPassColorAttachmentDescriptor), "sizeof mismatch for RenderPassColorAttachmentDescriptor");
    static_assert(alignof(RenderPassColorAttachmentDescriptor) == alignof(WGPURenderPassColorAttachmentDescriptor), "alignof mismatch for RenderPassColorAttachmentDescriptor");

    static_assert(offsetof(RenderPassColorAttachmentDescriptor, attachment) == offsetof(WGPURenderPassColorAttachmentDescriptor, attachment),
            "offsetof mismatch for RenderPassColorAttachmentDescriptor::attachment");
    static_assert(offsetof(RenderPassColorAttachmentDescriptor, resolveTarget) == offsetof(WGPURenderPassColorAttachmentDescriptor, resolveTarget),
            "offsetof mismatch for RenderPassColorAttachmentDescriptor::resolveTarget");
    static_assert(offsetof(RenderPassColorAttachmentDescriptor, loadOp) == offsetof(WGPURenderPassColorAttachmentDescriptor, loadOp),
            "offsetof mismatch for RenderPassColorAttachmentDescriptor::loadOp");
    static_assert(offsetof(RenderPassColorAttachmentDescriptor, storeOp) == offsetof(WGPURenderPassColorAttachmentDescriptor, storeOp),
            "offsetof mismatch for RenderPassColorAttachmentDescriptor::storeOp");
    static_assert(offsetof(RenderPassColorAttachmentDescriptor, clearColor) == offsetof(WGPURenderPassColorAttachmentDescriptor, clearColor),
            "offsetof mismatch for RenderPassColorAttachmentDescriptor::clearColor");


    static_assert(sizeof(RenderPipelineDescriptorDummyExtension) == sizeof(WGPURenderPipelineDescriptorDummyExtension), "sizeof mismatch for RenderPipelineDescriptorDummyExtension");
    static_assert(alignof(RenderPipelineDescriptorDummyExtension) == alignof(WGPURenderPipelineDescriptorDummyExtension), "alignof mismatch for RenderPipelineDescriptorDummyExtension");

    static_assert(offsetof(RenderPipelineDescriptorDummyExtension, dummyStage) == offsetof(WGPURenderPipelineDescriptorDummyExtension, dummyStage),
            "offsetof mismatch for RenderPipelineDescriptorDummyExtension::dummyStage");


    static_assert(sizeof(TextureCopyView) == sizeof(WGPUTextureCopyView), "sizeof mismatch for TextureCopyView");
    static_assert(alignof(TextureCopyView) == alignof(WGPUTextureCopyView), "alignof mismatch for TextureCopyView");

    static_assert(offsetof(TextureCopyView, nextInChain) == offsetof(WGPUTextureCopyView, nextInChain),
            "offsetof mismatch for TextureCopyView::nextInChain");
    static_assert(offsetof(TextureCopyView, texture) == offsetof(WGPUTextureCopyView, texture),
            "offsetof mismatch for TextureCopyView::texture");
    static_assert(offsetof(TextureCopyView, mipLevel) == offsetof(WGPUTextureCopyView, mipLevel),
            "offsetof mismatch for TextureCopyView::mipLevel");
    static_assert(offsetof(TextureCopyView, origin) == offsetof(WGPUTextureCopyView, origin),
            "offsetof mismatch for TextureCopyView::origin");
    static_assert(offsetof(TextureCopyView, aspect) == offsetof(WGPUTextureCopyView, aspect),
            "offsetof mismatch for TextureCopyView::aspect");


    static_assert(sizeof(TextureDescriptor) == sizeof(WGPUTextureDescriptor), "sizeof mismatch for TextureDescriptor");
    static_assert(alignof(TextureDescriptor) == alignof(WGPUTextureDescriptor), "alignof mismatch for TextureDescriptor");

    static_assert(offsetof(TextureDescriptor, nextInChain) == offsetof(WGPUTextureDescriptor, nextInChain),
            "offsetof mismatch for TextureDescriptor::nextInChain");
    static_assert(offsetof(TextureDescriptor, label) == offsetof(WGPUTextureDescriptor, label),
            "offsetof mismatch for TextureDescriptor::label");
    static_assert(offsetof(TextureDescriptor, usage) == offsetof(WGPUTextureDescriptor, usage),
            "offsetof mismatch for TextureDescriptor::usage");
    static_assert(offsetof(TextureDescriptor, dimension) == offsetof(WGPUTextureDescriptor, dimension),
            "offsetof mismatch for TextureDescriptor::dimension");
    static_assert(offsetof(TextureDescriptor, size) == offsetof(WGPUTextureDescriptor, size),
            "offsetof mismatch for TextureDescriptor::size");
    static_assert(offsetof(TextureDescriptor, format) == offsetof(WGPUTextureDescriptor, format),
            "offsetof mismatch for TextureDescriptor::format");
    static_assert(offsetof(TextureDescriptor, mipLevelCount) == offsetof(WGPUTextureDescriptor, mipLevelCount),
            "offsetof mismatch for TextureDescriptor::mipLevelCount");
    static_assert(offsetof(TextureDescriptor, sampleCount) == offsetof(WGPUTextureDescriptor, sampleCount),
            "offsetof mismatch for TextureDescriptor::sampleCount");


    static_assert(sizeof(VertexBufferLayoutDescriptor) == sizeof(WGPUVertexBufferLayoutDescriptor), "sizeof mismatch for VertexBufferLayoutDescriptor");
    static_assert(alignof(VertexBufferLayoutDescriptor) == alignof(WGPUVertexBufferLayoutDescriptor), "alignof mismatch for VertexBufferLayoutDescriptor");

    static_assert(offsetof(VertexBufferLayoutDescriptor, arrayStride) == offsetof(WGPUVertexBufferLayoutDescriptor, arrayStride),
            "offsetof mismatch for VertexBufferLayoutDescriptor::arrayStride");
    static_assert(offsetof(VertexBufferLayoutDescriptor, stepMode) == offsetof(WGPUVertexBufferLayoutDescriptor, stepMode),
            "offsetof mismatch for VertexBufferLayoutDescriptor::stepMode");
    static_assert(offsetof(VertexBufferLayoutDescriptor, attributeCount) == offsetof(WGPUVertexBufferLayoutDescriptor, attributeCount),
            "offsetof mismatch for VertexBufferLayoutDescriptor::attributeCount");
    static_assert(offsetof(VertexBufferLayoutDescriptor, attributes) == offsetof(WGPUVertexBufferLayoutDescriptor, attributes),
            "offsetof mismatch for VertexBufferLayoutDescriptor::attributes");


    static_assert(sizeof(RenderPassDescriptor) == sizeof(WGPURenderPassDescriptor), "sizeof mismatch for RenderPassDescriptor");
    static_assert(alignof(RenderPassDescriptor) == alignof(WGPURenderPassDescriptor), "alignof mismatch for RenderPassDescriptor");

    static_assert(offsetof(RenderPassDescriptor, nextInChain) == offsetof(WGPURenderPassDescriptor, nextInChain),
            "offsetof mismatch for RenderPassDescriptor::nextInChain");
    static_assert(offsetof(RenderPassDescriptor, label) == offsetof(WGPURenderPassDescriptor, label),
            "offsetof mismatch for RenderPassDescriptor::label");
    static_assert(offsetof(RenderPassDescriptor, colorAttachmentCount) == offsetof(WGPURenderPassDescriptor, colorAttachmentCount),
            "offsetof mismatch for RenderPassDescriptor::colorAttachmentCount");
    static_assert(offsetof(RenderPassDescriptor, colorAttachments) == offsetof(WGPURenderPassDescriptor, colorAttachments),
            "offsetof mismatch for RenderPassDescriptor::colorAttachments");
    static_assert(offsetof(RenderPassDescriptor, depthStencilAttachment) == offsetof(WGPURenderPassDescriptor, depthStencilAttachment),
            "offsetof mismatch for RenderPassDescriptor::depthStencilAttachment");
    static_assert(offsetof(RenderPassDescriptor, occlusionQuerySet) == offsetof(WGPURenderPassDescriptor, occlusionQuerySet),
            "offsetof mismatch for RenderPassDescriptor::occlusionQuerySet");


    static_assert(sizeof(VertexStateDescriptor) == sizeof(WGPUVertexStateDescriptor), "sizeof mismatch for VertexStateDescriptor");
    static_assert(alignof(VertexStateDescriptor) == alignof(WGPUVertexStateDescriptor), "alignof mismatch for VertexStateDescriptor");

    static_assert(offsetof(VertexStateDescriptor, nextInChain) == offsetof(WGPUVertexStateDescriptor, nextInChain),
            "offsetof mismatch for VertexStateDescriptor::nextInChain");
    static_assert(offsetof(VertexStateDescriptor, indexFormat) == offsetof(WGPUVertexStateDescriptor, indexFormat),
            "offsetof mismatch for VertexStateDescriptor::indexFormat");
    static_assert(offsetof(VertexStateDescriptor, vertexBufferCount) == offsetof(WGPUVertexStateDescriptor, vertexBufferCount),
            "offsetof mismatch for VertexStateDescriptor::vertexBufferCount");
    static_assert(offsetof(VertexStateDescriptor, vertexBuffers) == offsetof(WGPUVertexStateDescriptor, vertexBuffers),
            "offsetof mismatch for VertexStateDescriptor::vertexBuffers");


    static_assert(sizeof(RenderPipelineDescriptor) == sizeof(WGPURenderPipelineDescriptor), "sizeof mismatch for RenderPipelineDescriptor");
    static_assert(alignof(RenderPipelineDescriptor) == alignof(WGPURenderPipelineDescriptor), "alignof mismatch for RenderPipelineDescriptor");

    static_assert(offsetof(RenderPipelineDescriptor, nextInChain) == offsetof(WGPURenderPipelineDescriptor, nextInChain),
            "offsetof mismatch for RenderPipelineDescriptor::nextInChain");
    static_assert(offsetof(RenderPipelineDescriptor, label) == offsetof(WGPURenderPipelineDescriptor, label),
            "offsetof mismatch for RenderPipelineDescriptor::label");
    static_assert(offsetof(RenderPipelineDescriptor, layout) == offsetof(WGPURenderPipelineDescriptor, layout),
            "offsetof mismatch for RenderPipelineDescriptor::layout");
    static_assert(offsetof(RenderPipelineDescriptor, vertexStage) == offsetof(WGPURenderPipelineDescriptor, vertexStage),
            "offsetof mismatch for RenderPipelineDescriptor::vertexStage");
    static_assert(offsetof(RenderPipelineDescriptor, fragmentStage) == offsetof(WGPURenderPipelineDescriptor, fragmentStage),
            "offsetof mismatch for RenderPipelineDescriptor::fragmentStage");
    static_assert(offsetof(RenderPipelineDescriptor, vertexState) == offsetof(WGPURenderPipelineDescriptor, vertexState),
            "offsetof mismatch for RenderPipelineDescriptor::vertexState");
    static_assert(offsetof(RenderPipelineDescriptor, primitiveTopology) == offsetof(WGPURenderPipelineDescriptor, primitiveTopology),
            "offsetof mismatch for RenderPipelineDescriptor::primitiveTopology");
    static_assert(offsetof(RenderPipelineDescriptor, rasterizationState) == offsetof(WGPURenderPipelineDescriptor, rasterizationState),
            "offsetof mismatch for RenderPipelineDescriptor::rasterizationState");
    static_assert(offsetof(RenderPipelineDescriptor, sampleCount) == offsetof(WGPURenderPipelineDescriptor, sampleCount),
            "offsetof mismatch for RenderPipelineDescriptor::sampleCount");
    static_assert(offsetof(RenderPipelineDescriptor, depthStencilState) == offsetof(WGPURenderPipelineDescriptor, depthStencilState),
            "offsetof mismatch for RenderPipelineDescriptor::depthStencilState");
    static_assert(offsetof(RenderPipelineDescriptor, colorStateCount) == offsetof(WGPURenderPipelineDescriptor, colorStateCount),
            "offsetof mismatch for RenderPipelineDescriptor::colorStateCount");
    static_assert(offsetof(RenderPipelineDescriptor, colorStates) == offsetof(WGPURenderPipelineDescriptor, colorStates),
            "offsetof mismatch for RenderPipelineDescriptor::colorStates");
    static_assert(offsetof(RenderPipelineDescriptor, sampleMask) == offsetof(WGPURenderPipelineDescriptor, sampleMask),
            "offsetof mismatch for RenderPipelineDescriptor::sampleMask");
    static_assert(offsetof(RenderPipelineDescriptor, alphaToCoverageEnabled) == offsetof(WGPURenderPipelineDescriptor, alphaToCoverageEnabled),
            "offsetof mismatch for RenderPipelineDescriptor::alphaToCoverageEnabled");

}
