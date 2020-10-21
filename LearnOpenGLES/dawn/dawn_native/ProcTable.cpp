
#include "dawn_native/dawn_platform.h"
#include "dawn_native/DawnNative.h"

#include <algorithm>
#include <vector>

#include "dawn_native/BindGroup.h"
#include "dawn_native/BindGroupLayout.h"
#include "dawn_native/Buffer.h"
#include "dawn_native/CommandBuffer.h"
#include "dawn_native/CommandEncoder.h"
#include "dawn_native/ComputePassEncoder.h"
#include "dawn_native/ComputePipeline.h"
#include "dawn_native/Device.h"
#include "dawn_native/Fence.h"
#include "dawn_native/Instance.h"
#include "dawn_native/PipelineLayout.h"
#include "dawn_native/QuerySet.h"
#include "dawn_native/Queue.h"
#include "dawn_native/RenderBundle.h"
#include "dawn_native/RenderBundleEncoder.h"
#include "dawn_native/RenderPassEncoder.h"
#include "dawn_native/RenderPipeline.h"
#include "dawn_native/Sampler.h"
#include "dawn_native/ShaderModule.h"
#include "dawn_native/Surface.h"
#include "dawn_native/SwapChain.h"
#include "dawn_native/Texture.h"

namespace dawn_native {

    // Type aliases to make all frontend types appear as if they have "Base" at the end when some
    // of them are actually pure-frontend and don't have the Base.
    using CommandEncoderBase = CommandEncoder;
    using ComputePassEncoderBase = ComputePassEncoder;
    using FenceBase = Fence;
    using RenderPassEncoderBase = RenderPassEncoder;
    using RenderBundleEncoderBase = RenderBundleEncoder;
    using SurfaceBase = Surface;

    namespace {


        void NativeBindGroupReference(WGPUBindGroup cSelf) {
            auto self = reinterpret_cast<BindGroupBase*>(cSelf);

            self->Reference();
        }

        void NativeBindGroupRelease(WGPUBindGroup cSelf) {
            auto self = reinterpret_cast<BindGroupBase*>(cSelf);

            self->Release();
        }

        void NativeBindGroupLayoutReference(WGPUBindGroupLayout cSelf) {
            auto self = reinterpret_cast<BindGroupLayoutBase*>(cSelf);

            self->Reference();
        }

        void NativeBindGroupLayoutRelease(WGPUBindGroupLayout cSelf) {
            auto self = reinterpret_cast<BindGroupLayoutBase*>(cSelf);

            self->Release();
        }

        void NativeBufferDestroy(WGPUBuffer cSelf) {
            auto self = reinterpret_cast<BufferBase*>(cSelf);

            self->Destroy();
        }

        void const * NativeBufferGetConstMappedRange(WGPUBuffer cSelf, size_t offset, size_t size) {
            auto self = reinterpret_cast<BufferBase*>(cSelf);

            auto offset_ = offset;
            auto size_ = size;
            auto result =            self->GetConstMappedRange(offset_, size_);
            return result;
        }

        void * NativeBufferGetMappedRange(WGPUBuffer cSelf, size_t offset, size_t size) {
            auto self = reinterpret_cast<BufferBase*>(cSelf);

            auto offset_ = offset;
            auto size_ = size;
            auto result =            self->GetMappedRange(offset_, size_);
            return result;
        }

        void NativeBufferMapAsync(WGPUBuffer cSelf, WGPUMapModeFlags mode, size_t offset, size_t size, WGPUBufferMapCallback callback, void * userdata) {
            auto self = reinterpret_cast<BufferBase*>(cSelf);

            auto mode_ = static_cast<wgpu::MapMode>(mode);
            auto offset_ = offset;
            auto size_ = size;
            auto callback_ = callback;
            auto userdata_ = reinterpret_cast<void * >(userdata);
            self->MapAsync(mode_, offset_, size_, callback_, userdata_);
        }

        void NativeBufferUnmap(WGPUBuffer cSelf) {
            auto self = reinterpret_cast<BufferBase*>(cSelf);

            self->Unmap();
        }

        void NativeBufferReference(WGPUBuffer cSelf) {
            auto self = reinterpret_cast<BufferBase*>(cSelf);

            self->Reference();
        }

        void NativeBufferRelease(WGPUBuffer cSelf) {
            auto self = reinterpret_cast<BufferBase*>(cSelf);

            self->Release();
        }

        void NativeCommandBufferReference(WGPUCommandBuffer cSelf) {
            auto self = reinterpret_cast<CommandBufferBase*>(cSelf);

            self->Reference();
        }

        void NativeCommandBufferRelease(WGPUCommandBuffer cSelf) {
            auto self = reinterpret_cast<CommandBufferBase*>(cSelf);

            self->Release();
        }

        WGPUComputePassEncoder NativeCommandEncoderBeginComputePass(WGPUCommandEncoder cSelf, WGPUComputePassDescriptor const * descriptor) {
            auto self = reinterpret_cast<CommandEncoderBase*>(cSelf);

            auto descriptor_ = reinterpret_cast<ComputePassDescriptor const * >(descriptor);
            auto result =            self->BeginComputePass(descriptor_);
            return reinterpret_cast<WGPUComputePassEncoder>(result);
        }

        WGPURenderPassEncoder NativeCommandEncoderBeginRenderPass(WGPUCommandEncoder cSelf, WGPURenderPassDescriptor const * descriptor) {
            auto self = reinterpret_cast<CommandEncoderBase*>(cSelf);

            auto descriptor_ = reinterpret_cast<RenderPassDescriptor const * >(descriptor);
            auto result =            self->BeginRenderPass(descriptor_);
            return reinterpret_cast<WGPURenderPassEncoder>(result);
        }

        void NativeCommandEncoderCopyBufferToBuffer(WGPUCommandEncoder cSelf, WGPUBuffer source, uint64_t sourceOffset, WGPUBuffer destination, uint64_t destinationOffset, uint64_t size) {
            auto self = reinterpret_cast<CommandEncoderBase*>(cSelf);

            auto source_ = reinterpret_cast<BufferBase* >(source);
            auto sourceOffset_ = sourceOffset;
            auto destination_ = reinterpret_cast<BufferBase* >(destination);
            auto destinationOffset_ = destinationOffset;
            auto size_ = size;
            self->CopyBufferToBuffer(source_, sourceOffset_, destination_, destinationOffset_, size_);
        }

        void NativeCommandEncoderCopyBufferToTexture(WGPUCommandEncoder cSelf, WGPUBufferCopyView const * source, WGPUTextureCopyView const * destination, WGPUExtent3D const * copySize) {
            auto self = reinterpret_cast<CommandEncoderBase*>(cSelf);

            auto source_ = reinterpret_cast<BufferCopyView const * >(source);
            auto destination_ = reinterpret_cast<TextureCopyView const * >(destination);
            auto copySize_ = reinterpret_cast<Extent3D const * >(copySize);
            self->CopyBufferToTexture(source_, destination_, copySize_);
        }

        void NativeCommandEncoderCopyTextureToBuffer(WGPUCommandEncoder cSelf, WGPUTextureCopyView const * source, WGPUBufferCopyView const * destination, WGPUExtent3D const * copySize) {
            auto self = reinterpret_cast<CommandEncoderBase*>(cSelf);

            auto source_ = reinterpret_cast<TextureCopyView const * >(source);
            auto destination_ = reinterpret_cast<BufferCopyView const * >(destination);
            auto copySize_ = reinterpret_cast<Extent3D const * >(copySize);
            self->CopyTextureToBuffer(source_, destination_, copySize_);
        }

        void NativeCommandEncoderCopyTextureToTexture(WGPUCommandEncoder cSelf, WGPUTextureCopyView const * source, WGPUTextureCopyView const * destination, WGPUExtent3D const * copySize) {
            auto self = reinterpret_cast<CommandEncoderBase*>(cSelf);

            auto source_ = reinterpret_cast<TextureCopyView const * >(source);
            auto destination_ = reinterpret_cast<TextureCopyView const * >(destination);
            auto copySize_ = reinterpret_cast<Extent3D const * >(copySize);
            self->CopyTextureToTexture(source_, destination_, copySize_);
        }

        WGPUCommandBuffer NativeCommandEncoderFinish(WGPUCommandEncoder cSelf, WGPUCommandBufferDescriptor const * descriptor) {
            auto self = reinterpret_cast<CommandEncoderBase*>(cSelf);

            auto descriptor_ = reinterpret_cast<CommandBufferDescriptor const * >(descriptor);
            auto result =            self->Finish(descriptor_);
            return reinterpret_cast<WGPUCommandBuffer>(result);
        }

        void NativeCommandEncoderInsertDebugMarker(WGPUCommandEncoder cSelf, char const * markerLabel) {
            auto self = reinterpret_cast<CommandEncoderBase*>(cSelf);

            auto markerLabel_ = reinterpret_cast<char const * >(markerLabel);
            self->InsertDebugMarker(markerLabel_);
        }

        void NativeCommandEncoderPopDebugGroup(WGPUCommandEncoder cSelf) {
            auto self = reinterpret_cast<CommandEncoderBase*>(cSelf);

            self->PopDebugGroup();
        }

        void NativeCommandEncoderPushDebugGroup(WGPUCommandEncoder cSelf, char const * groupLabel) {
            auto self = reinterpret_cast<CommandEncoderBase*>(cSelf);

            auto groupLabel_ = reinterpret_cast<char const * >(groupLabel);
            self->PushDebugGroup(groupLabel_);
        }

        void NativeCommandEncoderResolveQuerySet(WGPUCommandEncoder cSelf, WGPUQuerySet querySet, uint32_t firstQuery, uint32_t queryCount, WGPUBuffer destination, uint64_t destinationOffset) {
            auto self = reinterpret_cast<CommandEncoderBase*>(cSelf);

            auto querySet_ = reinterpret_cast<QuerySetBase* >(querySet);
            auto firstQuery_ = firstQuery;
            auto queryCount_ = queryCount;
            auto destination_ = reinterpret_cast<BufferBase* >(destination);
            auto destinationOffset_ = destinationOffset;
            self->ResolveQuerySet(querySet_, firstQuery_, queryCount_, destination_, destinationOffset_);
        }

        void NativeCommandEncoderWriteTimestamp(WGPUCommandEncoder cSelf, WGPUQuerySet querySet, uint32_t queryIndex) {
            auto self = reinterpret_cast<CommandEncoderBase*>(cSelf);

            auto querySet_ = reinterpret_cast<QuerySetBase* >(querySet);
            auto queryIndex_ = queryIndex;
            self->WriteTimestamp(querySet_, queryIndex_);
        }

        void NativeCommandEncoderReference(WGPUCommandEncoder cSelf) {
            auto self = reinterpret_cast<CommandEncoderBase*>(cSelf);

            self->Reference();
        }

        void NativeCommandEncoderRelease(WGPUCommandEncoder cSelf) {
            auto self = reinterpret_cast<CommandEncoderBase*>(cSelf);

            self->Release();
        }

        void NativeComputePassEncoderDispatch(WGPUComputePassEncoder cSelf, uint32_t x, uint32_t y, uint32_t z) {
            auto self = reinterpret_cast<ComputePassEncoderBase*>(cSelf);

            auto x_ = x;
            auto y_ = y;
            auto z_ = z;
            self->Dispatch(x_, y_, z_);
        }

        void NativeComputePassEncoderDispatchIndirect(WGPUComputePassEncoder cSelf, WGPUBuffer indirectBuffer, uint64_t indirectOffset) {
            auto self = reinterpret_cast<ComputePassEncoderBase*>(cSelf);

            auto indirectBuffer_ = reinterpret_cast<BufferBase* >(indirectBuffer);
            auto indirectOffset_ = indirectOffset;
            self->DispatchIndirect(indirectBuffer_, indirectOffset_);
        }

        void NativeComputePassEncoderEndPass(WGPUComputePassEncoder cSelf) {
            auto self = reinterpret_cast<ComputePassEncoderBase*>(cSelf);

            self->EndPass();
        }

        void NativeComputePassEncoderInsertDebugMarker(WGPUComputePassEncoder cSelf, char const * markerLabel) {
            auto self = reinterpret_cast<ComputePassEncoderBase*>(cSelf);

            auto markerLabel_ = reinterpret_cast<char const * >(markerLabel);
            self->InsertDebugMarker(markerLabel_);
        }

        void NativeComputePassEncoderPopDebugGroup(WGPUComputePassEncoder cSelf) {
            auto self = reinterpret_cast<ComputePassEncoderBase*>(cSelf);

            self->PopDebugGroup();
        }

        void NativeComputePassEncoderPushDebugGroup(WGPUComputePassEncoder cSelf, char const * groupLabel) {
            auto self = reinterpret_cast<ComputePassEncoderBase*>(cSelf);

            auto groupLabel_ = reinterpret_cast<char const * >(groupLabel);
            self->PushDebugGroup(groupLabel_);
        }

        void NativeComputePassEncoderSetBindGroup(WGPUComputePassEncoder cSelf, uint32_t groupIndex, WGPUBindGroup group, uint32_t dynamicOffsetCount, uint32_t const * dynamicOffsets) {
            auto self = reinterpret_cast<ComputePassEncoderBase*>(cSelf);

            auto groupIndex_ = groupIndex;
            auto group_ = reinterpret_cast<BindGroupBase* >(group);
            auto dynamicOffsetCount_ = dynamicOffsetCount;
            auto dynamicOffsets_ = reinterpret_cast<uint32_t const * >(dynamicOffsets);
            self->SetBindGroup(groupIndex_, group_, dynamicOffsetCount_, dynamicOffsets_);
        }

        void NativeComputePassEncoderSetPipeline(WGPUComputePassEncoder cSelf, WGPUComputePipeline pipeline) {
            auto self = reinterpret_cast<ComputePassEncoderBase*>(cSelf);

            auto pipeline_ = reinterpret_cast<ComputePipelineBase* >(pipeline);
            self->SetPipeline(pipeline_);
        }

        void NativeComputePassEncoderWriteTimestamp(WGPUComputePassEncoder cSelf, WGPUQuerySet querySet, uint32_t queryIndex) {
            auto self = reinterpret_cast<ComputePassEncoderBase*>(cSelf);

            auto querySet_ = reinterpret_cast<QuerySetBase* >(querySet);
            auto queryIndex_ = queryIndex;
            self->WriteTimestamp(querySet_, queryIndex_);
        }

        void NativeComputePassEncoderReference(WGPUComputePassEncoder cSelf) {
            auto self = reinterpret_cast<ComputePassEncoderBase*>(cSelf);

            self->Reference();
        }

        void NativeComputePassEncoderRelease(WGPUComputePassEncoder cSelf) {
            auto self = reinterpret_cast<ComputePassEncoderBase*>(cSelf);

            self->Release();
        }

        WGPUBindGroupLayout NativeComputePipelineGetBindGroupLayout(WGPUComputePipeline cSelf, uint32_t groupIndex) {
            auto self = reinterpret_cast<ComputePipelineBase*>(cSelf);

            auto groupIndex_ = groupIndex;
            auto result =            self->GetBindGroupLayout(groupIndex_);
            return reinterpret_cast<WGPUBindGroupLayout>(result);
        }

        void NativeComputePipelineReference(WGPUComputePipeline cSelf) {
            auto self = reinterpret_cast<ComputePipelineBase*>(cSelf);

            self->Reference();
        }

        void NativeComputePipelineRelease(WGPUComputePipeline cSelf) {
            auto self = reinterpret_cast<ComputePipelineBase*>(cSelf);

            self->Release();
        }

        WGPUBindGroup NativeDeviceCreateBindGroup(WGPUDevice cSelf, WGPUBindGroupDescriptor const * descriptor) {
            auto self = reinterpret_cast<DeviceBase*>(cSelf);

            auto descriptor_ = reinterpret_cast<BindGroupDescriptor const * >(descriptor);
            auto result =            self->CreateBindGroup(descriptor_);
            return reinterpret_cast<WGPUBindGroup>(result);
        }

        WGPUBindGroupLayout NativeDeviceCreateBindGroupLayout(WGPUDevice cSelf, WGPUBindGroupLayoutDescriptor const * descriptor) {
            auto self = reinterpret_cast<DeviceBase*>(cSelf);

            auto descriptor_ = reinterpret_cast<BindGroupLayoutDescriptor const * >(descriptor);
            auto result =            self->CreateBindGroupLayout(descriptor_);
            return reinterpret_cast<WGPUBindGroupLayout>(result);
        }

        WGPUBuffer NativeDeviceCreateBuffer(WGPUDevice cSelf, WGPUBufferDescriptor const * descriptor) {
            auto self = reinterpret_cast<DeviceBase*>(cSelf);

            auto descriptor_ = reinterpret_cast<BufferDescriptor const * >(descriptor);
            auto result =            self->CreateBuffer(descriptor_);
            return reinterpret_cast<WGPUBuffer>(result);
        }

        WGPUCommandEncoder NativeDeviceCreateCommandEncoder(WGPUDevice cSelf, WGPUCommandEncoderDescriptor const * descriptor) {
            auto self = reinterpret_cast<DeviceBase*>(cSelf);

            auto descriptor_ = reinterpret_cast<CommandEncoderDescriptor const * >(descriptor);
            auto result =            self->CreateCommandEncoder(descriptor_);
            return reinterpret_cast<WGPUCommandEncoder>(result);
        }

        WGPUComputePipeline NativeDeviceCreateComputePipeline(WGPUDevice cSelf, WGPUComputePipelineDescriptor const * descriptor) {
            auto self = reinterpret_cast<DeviceBase*>(cSelf);

            auto descriptor_ = reinterpret_cast<ComputePipelineDescriptor const * >(descriptor);
            auto result =            self->CreateComputePipeline(descriptor_);
            return reinterpret_cast<WGPUComputePipeline>(result);
        }

        WGPUBuffer NativeDeviceCreateErrorBuffer(WGPUDevice cSelf) {
            auto self = reinterpret_cast<DeviceBase*>(cSelf);

            auto result =            self->CreateErrorBuffer();
            return reinterpret_cast<WGPUBuffer>(result);
        }

        WGPUPipelineLayout NativeDeviceCreatePipelineLayout(WGPUDevice cSelf, WGPUPipelineLayoutDescriptor const * descriptor) {
            auto self = reinterpret_cast<DeviceBase*>(cSelf);

            auto descriptor_ = reinterpret_cast<PipelineLayoutDescriptor const * >(descriptor);
            auto result =            self->CreatePipelineLayout(descriptor_);
            return reinterpret_cast<WGPUPipelineLayout>(result);
        }

        WGPUQuerySet NativeDeviceCreateQuerySet(WGPUDevice cSelf, WGPUQuerySetDescriptor const * descriptor) {
            auto self = reinterpret_cast<DeviceBase*>(cSelf);

            auto descriptor_ = reinterpret_cast<QuerySetDescriptor const * >(descriptor);
            auto result =            self->CreateQuerySet(descriptor_);
            return reinterpret_cast<WGPUQuerySet>(result);
        }

        void NativeDeviceCreateReadyComputePipeline(WGPUDevice cSelf, WGPUComputePipelineDescriptor const * descriptor, WGPUCreateReadyComputePipelineCallback callback, void * userdata) {
            auto self = reinterpret_cast<DeviceBase*>(cSelf);

            auto descriptor_ = reinterpret_cast<ComputePipelineDescriptor const * >(descriptor);
            auto callback_ = callback;
            auto userdata_ = reinterpret_cast<void * >(userdata);
            self->CreateReadyComputePipeline(descriptor_, callback_, userdata_);
        }

        void NativeDeviceCreateReadyRenderPipeline(WGPUDevice cSelf, WGPURenderPipelineDescriptor const * descriptor, WGPUCreateReadyRenderPipelineCallback callback, void * userdata) {
            auto self = reinterpret_cast<DeviceBase*>(cSelf);

            auto descriptor_ = reinterpret_cast<RenderPipelineDescriptor const * >(descriptor);
            auto callback_ = callback;
            auto userdata_ = reinterpret_cast<void * >(userdata);
            self->CreateReadyRenderPipeline(descriptor_, callback_, userdata_);
        }

        WGPURenderBundleEncoder NativeDeviceCreateRenderBundleEncoder(WGPUDevice cSelf, WGPURenderBundleEncoderDescriptor const * descriptor) {
            auto self = reinterpret_cast<DeviceBase*>(cSelf);

            auto descriptor_ = reinterpret_cast<RenderBundleEncoderDescriptor const * >(descriptor);
            auto result =            self->CreateRenderBundleEncoder(descriptor_);
            return reinterpret_cast<WGPURenderBundleEncoder>(result);
        }

        WGPURenderPipeline NativeDeviceCreateRenderPipeline(WGPUDevice cSelf, WGPURenderPipelineDescriptor const * descriptor) {
            auto self = reinterpret_cast<DeviceBase*>(cSelf);

            auto descriptor_ = reinterpret_cast<RenderPipelineDescriptor const * >(descriptor);
            auto result =            self->CreateRenderPipeline(descriptor_);
            return reinterpret_cast<WGPURenderPipeline>(result);
        }

        WGPUSampler NativeDeviceCreateSampler(WGPUDevice cSelf, WGPUSamplerDescriptor const * descriptor) {
            auto self = reinterpret_cast<DeviceBase*>(cSelf);

            auto descriptor_ = reinterpret_cast<SamplerDescriptor const * >(descriptor);
            auto result =            self->CreateSampler(descriptor_);
            return reinterpret_cast<WGPUSampler>(result);
        }

        WGPUShaderModule NativeDeviceCreateShaderModule(WGPUDevice cSelf, WGPUShaderModuleDescriptor const * descriptor) {
            auto self = reinterpret_cast<DeviceBase*>(cSelf);

            auto descriptor_ = reinterpret_cast<ShaderModuleDescriptor const * >(descriptor);
            auto result =            self->CreateShaderModule(descriptor_);
            return reinterpret_cast<WGPUShaderModule>(result);
        }

        WGPUSwapChain NativeDeviceCreateSwapChain(WGPUDevice cSelf, WGPUSurface surface, WGPUSwapChainDescriptor const * descriptor) {
            auto self = reinterpret_cast<DeviceBase*>(cSelf);

            auto surface_ = reinterpret_cast<SurfaceBase* >(surface);
            auto descriptor_ = reinterpret_cast<SwapChainDescriptor const * >(descriptor);
            auto result =            self->CreateSwapChain(surface_, descriptor_);
            return reinterpret_cast<WGPUSwapChain>(result);
        }

        WGPUTexture NativeDeviceCreateTexture(WGPUDevice cSelf, WGPUTextureDescriptor const * descriptor) {
            auto self = reinterpret_cast<DeviceBase*>(cSelf);

            auto descriptor_ = reinterpret_cast<TextureDescriptor const * >(descriptor);
            auto result =            self->CreateTexture(descriptor_);
            return reinterpret_cast<WGPUTexture>(result);
        }

        WGPUQueue NativeDeviceGetDefaultQueue(WGPUDevice cSelf) {
            auto self = reinterpret_cast<DeviceBase*>(cSelf);

            auto result =            self->GetDefaultQueue();
            return reinterpret_cast<WGPUQueue>(result);
        }

        void NativeDeviceInjectError(WGPUDevice cSelf, WGPUErrorType type, char const * message) {
            auto self = reinterpret_cast<DeviceBase*>(cSelf);

            auto type_ = static_cast<wgpu::ErrorType>(type);
            auto message_ = reinterpret_cast<char const * >(message);
            self->InjectError(type_, message_);
        }

        void NativeDeviceLoseForTesting(WGPUDevice cSelf) {
            auto self = reinterpret_cast<DeviceBase*>(cSelf);

            self->LoseForTesting();
        }

        bool NativeDevicePopErrorScope(WGPUDevice cSelf, WGPUErrorCallback callback, void * userdata) {
            auto self = reinterpret_cast<DeviceBase*>(cSelf);

            auto callback_ = callback;
            auto userdata_ = reinterpret_cast<void * >(userdata);
            auto result =            self->PopErrorScope(callback_, userdata_);
            return result;
        }

        void NativeDevicePushErrorScope(WGPUDevice cSelf, WGPUErrorFilter filter) {
            auto self = reinterpret_cast<DeviceBase*>(cSelf);

            auto filter_ = static_cast<wgpu::ErrorFilter>(filter);
            self->PushErrorScope(filter_);
        }

        void NativeDeviceSetDeviceLostCallback(WGPUDevice cSelf, WGPUDeviceLostCallback callback, void * userdata) {
            auto self = reinterpret_cast<DeviceBase*>(cSelf);

            auto callback_ = callback;
            auto userdata_ = reinterpret_cast<void * >(userdata);
            self->SetDeviceLostCallback(callback_, userdata_);
        }

        void NativeDeviceSetUncapturedErrorCallback(WGPUDevice cSelf, WGPUErrorCallback callback, void * userdata) {
            auto self = reinterpret_cast<DeviceBase*>(cSelf);

            auto callback_ = callback;
            auto userdata_ = reinterpret_cast<void * >(userdata);
            self->SetUncapturedErrorCallback(callback_, userdata_);
        }

        void NativeDeviceTick(WGPUDevice cSelf) {
            auto self = reinterpret_cast<DeviceBase*>(cSelf);

            self->Tick();
        }

        void NativeDeviceReference(WGPUDevice cSelf) {
            auto self = reinterpret_cast<DeviceBase*>(cSelf);

            self->Reference();
        }

        void NativeDeviceRelease(WGPUDevice cSelf) {
            auto self = reinterpret_cast<DeviceBase*>(cSelf);

            self->Release();
        }

        uint64_t NativeFenceGetCompletedValue(WGPUFence cSelf) {
            auto self = reinterpret_cast<FenceBase*>(cSelf);

            auto result =            self->GetCompletedValue();
            return result;
        }

        void NativeFenceOnCompletion(WGPUFence cSelf, uint64_t value, WGPUFenceOnCompletionCallback callback, void * userdata) {
            auto self = reinterpret_cast<FenceBase*>(cSelf);

            auto value_ = value;
            auto callback_ = callback;
            auto userdata_ = reinterpret_cast<void * >(userdata);
            self->OnCompletion(value_, callback_, userdata_);
        }

        void NativeFenceReference(WGPUFence cSelf) {
            auto self = reinterpret_cast<FenceBase*>(cSelf);

            self->Reference();
        }

        void NativeFenceRelease(WGPUFence cSelf) {
            auto self = reinterpret_cast<FenceBase*>(cSelf);

            self->Release();
        }

        WGPUSurface NativeInstanceCreateSurface(WGPUInstance cSelf, WGPUSurfaceDescriptor const * descriptor) {
            auto self = reinterpret_cast<InstanceBase*>(cSelf);

            auto descriptor_ = reinterpret_cast<SurfaceDescriptor const * >(descriptor);
            auto result =            self->CreateSurface(descriptor_);
            return reinterpret_cast<WGPUSurface>(result);
        }

        void NativeInstanceReference(WGPUInstance cSelf) {
            auto self = reinterpret_cast<InstanceBase*>(cSelf);

            self->Reference();
        }

        void NativeInstanceRelease(WGPUInstance cSelf) {
            auto self = reinterpret_cast<InstanceBase*>(cSelf);

            self->Release();
        }

        void NativePipelineLayoutReference(WGPUPipelineLayout cSelf) {
            auto self = reinterpret_cast<PipelineLayoutBase*>(cSelf);

            self->Reference();
        }

        void NativePipelineLayoutRelease(WGPUPipelineLayout cSelf) {
            auto self = reinterpret_cast<PipelineLayoutBase*>(cSelf);

            self->Release();
        }

        void NativeQuerySetDestroy(WGPUQuerySet cSelf) {
            auto self = reinterpret_cast<QuerySetBase*>(cSelf);

            self->Destroy();
        }

        void NativeQuerySetReference(WGPUQuerySet cSelf) {
            auto self = reinterpret_cast<QuerySetBase*>(cSelf);

            self->Reference();
        }

        void NativeQuerySetRelease(WGPUQuerySet cSelf) {
            auto self = reinterpret_cast<QuerySetBase*>(cSelf);

            self->Release();
        }

        WGPUFence NativeQueueCreateFence(WGPUQueue cSelf, WGPUFenceDescriptor const * descriptor) {
            auto self = reinterpret_cast<QueueBase*>(cSelf);

            auto descriptor_ = reinterpret_cast<FenceDescriptor const * >(descriptor);
            auto result =            self->CreateFence(descriptor_);
            return reinterpret_cast<WGPUFence>(result);
        }

        void NativeQueueSignal(WGPUQueue cSelf, WGPUFence fence, uint64_t signalValue) {
            auto self = reinterpret_cast<QueueBase*>(cSelf);

            auto fence_ = reinterpret_cast<FenceBase* >(fence);
            auto signalValue_ = signalValue;
            self->Signal(fence_, signalValue_);
        }

        void NativeQueueSubmit(WGPUQueue cSelf, uint32_t commandCount, WGPUCommandBuffer const * commands) {
            auto self = reinterpret_cast<QueueBase*>(cSelf);

            auto commandCount_ = commandCount;
            auto commands_ = reinterpret_cast<CommandBufferBase* const * >(commands);
            self->Submit(commandCount_, commands_);
        }

        void NativeQueueWriteBuffer(WGPUQueue cSelf, WGPUBuffer buffer, uint64_t bufferOffset, void const * data, size_t size) {
            auto self = reinterpret_cast<QueueBase*>(cSelf);

            auto buffer_ = reinterpret_cast<BufferBase* >(buffer);
            auto bufferOffset_ = bufferOffset;
            auto data_ = reinterpret_cast<void const * >(data);
            auto size_ = size;
            self->WriteBuffer(buffer_, bufferOffset_, data_, size_);
        }

        void NativeQueueWriteTexture(WGPUQueue cSelf, WGPUTextureCopyView const * destination, void const * data, size_t dataSize, WGPUTextureDataLayout const * dataLayout, WGPUExtent3D const * writeSize) {
            auto self = reinterpret_cast<QueueBase*>(cSelf);

            auto destination_ = reinterpret_cast<TextureCopyView const * >(destination);
            auto data_ = reinterpret_cast<void const * >(data);
            auto dataSize_ = dataSize;
            auto dataLayout_ = reinterpret_cast<TextureDataLayout const * >(dataLayout);
            auto writeSize_ = reinterpret_cast<Extent3D const * >(writeSize);
            self->WriteTexture(destination_, data_, dataSize_, dataLayout_, writeSize_);
        }

        void NativeQueueReference(WGPUQueue cSelf) {
            auto self = reinterpret_cast<QueueBase*>(cSelf);

            self->Reference();
        }

        void NativeQueueRelease(WGPUQueue cSelf) {
            auto self = reinterpret_cast<QueueBase*>(cSelf);

            self->Release();
        }

        void NativeRenderBundleReference(WGPURenderBundle cSelf) {
            auto self = reinterpret_cast<RenderBundleBase*>(cSelf);

            self->Reference();
        }

        void NativeRenderBundleRelease(WGPURenderBundle cSelf) {
            auto self = reinterpret_cast<RenderBundleBase*>(cSelf);

            self->Release();
        }

        void NativeRenderBundleEncoderDraw(WGPURenderBundleEncoder cSelf, uint32_t vertexCount, uint32_t instanceCount, uint32_t firstVertex, uint32_t firstInstance) {
            auto self = reinterpret_cast<RenderBundleEncoderBase*>(cSelf);

            auto vertexCount_ = vertexCount;
            auto instanceCount_ = instanceCount;
            auto firstVertex_ = firstVertex;
            auto firstInstance_ = firstInstance;
            self->Draw(vertexCount_, instanceCount_, firstVertex_, firstInstance_);
        }

        void NativeRenderBundleEncoderDrawIndexed(WGPURenderBundleEncoder cSelf, uint32_t indexCount, uint32_t instanceCount, uint32_t firstIndex, int32_t baseVertex, uint32_t firstInstance) {
            auto self = reinterpret_cast<RenderBundleEncoderBase*>(cSelf);

            auto indexCount_ = indexCount;
            auto instanceCount_ = instanceCount;
            auto firstIndex_ = firstIndex;
            auto baseVertex_ = baseVertex;
            auto firstInstance_ = firstInstance;
            self->DrawIndexed(indexCount_, instanceCount_, firstIndex_, baseVertex_, firstInstance_);
        }

        void NativeRenderBundleEncoderDrawIndexedIndirect(WGPURenderBundleEncoder cSelf, WGPUBuffer indirectBuffer, uint64_t indirectOffset) {
            auto self = reinterpret_cast<RenderBundleEncoderBase*>(cSelf);

            auto indirectBuffer_ = reinterpret_cast<BufferBase* >(indirectBuffer);
            auto indirectOffset_ = indirectOffset;
            self->DrawIndexedIndirect(indirectBuffer_, indirectOffset_);
        }

        void NativeRenderBundleEncoderDrawIndirect(WGPURenderBundleEncoder cSelf, WGPUBuffer indirectBuffer, uint64_t indirectOffset) {
            auto self = reinterpret_cast<RenderBundleEncoderBase*>(cSelf);

            auto indirectBuffer_ = reinterpret_cast<BufferBase* >(indirectBuffer);
            auto indirectOffset_ = indirectOffset;
            self->DrawIndirect(indirectBuffer_, indirectOffset_);
        }

        WGPURenderBundle NativeRenderBundleEncoderFinish(WGPURenderBundleEncoder cSelf, WGPURenderBundleDescriptor const * descriptor) {
            auto self = reinterpret_cast<RenderBundleEncoderBase*>(cSelf);

            auto descriptor_ = reinterpret_cast<RenderBundleDescriptor const * >(descriptor);
            auto result =            self->Finish(descriptor_);
            return reinterpret_cast<WGPURenderBundle>(result);
        }

        void NativeRenderBundleEncoderInsertDebugMarker(WGPURenderBundleEncoder cSelf, char const * markerLabel) {
            auto self = reinterpret_cast<RenderBundleEncoderBase*>(cSelf);

            auto markerLabel_ = reinterpret_cast<char const * >(markerLabel);
            self->InsertDebugMarker(markerLabel_);
        }

        void NativeRenderBundleEncoderPopDebugGroup(WGPURenderBundleEncoder cSelf) {
            auto self = reinterpret_cast<RenderBundleEncoderBase*>(cSelf);

            self->PopDebugGroup();
        }

        void NativeRenderBundleEncoderPushDebugGroup(WGPURenderBundleEncoder cSelf, char const * groupLabel) {
            auto self = reinterpret_cast<RenderBundleEncoderBase*>(cSelf);

            auto groupLabel_ = reinterpret_cast<char const * >(groupLabel);
            self->PushDebugGroup(groupLabel_);
        }

        void NativeRenderBundleEncoderSetBindGroup(WGPURenderBundleEncoder cSelf, uint32_t groupIndex, WGPUBindGroup group, uint32_t dynamicOffsetCount, uint32_t const * dynamicOffsets) {
            auto self = reinterpret_cast<RenderBundleEncoderBase*>(cSelf);

            auto groupIndex_ = groupIndex;
            auto group_ = reinterpret_cast<BindGroupBase* >(group);
            auto dynamicOffsetCount_ = dynamicOffsetCount;
            auto dynamicOffsets_ = reinterpret_cast<uint32_t const * >(dynamicOffsets);
            self->SetBindGroup(groupIndex_, group_, dynamicOffsetCount_, dynamicOffsets_);
        }

        void NativeRenderBundleEncoderSetIndexBuffer(WGPURenderBundleEncoder cSelf, WGPUBuffer buffer, uint64_t offset, uint64_t size) {
            auto self = reinterpret_cast<RenderBundleEncoderBase*>(cSelf);

            auto buffer_ = reinterpret_cast<BufferBase* >(buffer);
            auto offset_ = offset;
            auto size_ = size;
            self->SetIndexBuffer(buffer_, offset_, size_);
        }

        void NativeRenderBundleEncoderSetIndexBufferWithFormat(WGPURenderBundleEncoder cSelf, WGPUBuffer buffer, WGPUIndexFormat format, uint64_t offset, uint64_t size) {
            auto self = reinterpret_cast<RenderBundleEncoderBase*>(cSelf);

            auto buffer_ = reinterpret_cast<BufferBase* >(buffer);
            auto format_ = static_cast<wgpu::IndexFormat>(format);
            auto offset_ = offset;
            auto size_ = size;
            self->SetIndexBufferWithFormat(buffer_, format_, offset_, size_);
        }

        void NativeRenderBundleEncoderSetPipeline(WGPURenderBundleEncoder cSelf, WGPURenderPipeline pipeline) {
            auto self = reinterpret_cast<RenderBundleEncoderBase*>(cSelf);

            auto pipeline_ = reinterpret_cast<RenderPipelineBase* >(pipeline);
            self->SetPipeline(pipeline_);
        }

        void NativeRenderBundleEncoderSetVertexBuffer(WGPURenderBundleEncoder cSelf, uint32_t slot, WGPUBuffer buffer, uint64_t offset, uint64_t size) {
            auto self = reinterpret_cast<RenderBundleEncoderBase*>(cSelf);

            auto slot_ = slot;
            auto buffer_ = reinterpret_cast<BufferBase* >(buffer);
            auto offset_ = offset;
            auto size_ = size;
            self->SetVertexBuffer(slot_, buffer_, offset_, size_);
        }

        void NativeRenderBundleEncoderReference(WGPURenderBundleEncoder cSelf) {
            auto self = reinterpret_cast<RenderBundleEncoderBase*>(cSelf);

            self->Reference();
        }

        void NativeRenderBundleEncoderRelease(WGPURenderBundleEncoder cSelf) {
            auto self = reinterpret_cast<RenderBundleEncoderBase*>(cSelf);

            self->Release();
        }

        void NativeRenderPassEncoderDraw(WGPURenderPassEncoder cSelf, uint32_t vertexCount, uint32_t instanceCount, uint32_t firstVertex, uint32_t firstInstance) {
            auto self = reinterpret_cast<RenderPassEncoderBase*>(cSelf);

            auto vertexCount_ = vertexCount;
            auto instanceCount_ = instanceCount;
            auto firstVertex_ = firstVertex;
            auto firstInstance_ = firstInstance;
            self->Draw(vertexCount_, instanceCount_, firstVertex_, firstInstance_);
        }

        void NativeRenderPassEncoderDrawIndexed(WGPURenderPassEncoder cSelf, uint32_t indexCount, uint32_t instanceCount, uint32_t firstIndex, int32_t baseVertex, uint32_t firstInstance) {
            auto self = reinterpret_cast<RenderPassEncoderBase*>(cSelf);

            auto indexCount_ = indexCount;
            auto instanceCount_ = instanceCount;
            auto firstIndex_ = firstIndex;
            auto baseVertex_ = baseVertex;
            auto firstInstance_ = firstInstance;
            self->DrawIndexed(indexCount_, instanceCount_, firstIndex_, baseVertex_, firstInstance_);
        }

        void NativeRenderPassEncoderDrawIndexedIndirect(WGPURenderPassEncoder cSelf, WGPUBuffer indirectBuffer, uint64_t indirectOffset) {
            auto self = reinterpret_cast<RenderPassEncoderBase*>(cSelf);

            auto indirectBuffer_ = reinterpret_cast<BufferBase* >(indirectBuffer);
            auto indirectOffset_ = indirectOffset;
            self->DrawIndexedIndirect(indirectBuffer_, indirectOffset_);
        }

        void NativeRenderPassEncoderDrawIndirect(WGPURenderPassEncoder cSelf, WGPUBuffer indirectBuffer, uint64_t indirectOffset) {
            auto self = reinterpret_cast<RenderPassEncoderBase*>(cSelf);

            auto indirectBuffer_ = reinterpret_cast<BufferBase* >(indirectBuffer);
            auto indirectOffset_ = indirectOffset;
            self->DrawIndirect(indirectBuffer_, indirectOffset_);
        }

        void NativeRenderPassEncoderEndPass(WGPURenderPassEncoder cSelf) {
            auto self = reinterpret_cast<RenderPassEncoderBase*>(cSelf);

            self->EndPass();
        }

        void NativeRenderPassEncoderExecuteBundles(WGPURenderPassEncoder cSelf, uint32_t bundlesCount, WGPURenderBundle const * bundles) {
            auto self = reinterpret_cast<RenderPassEncoderBase*>(cSelf);

            auto bundlesCount_ = bundlesCount;
            auto bundles_ = reinterpret_cast<RenderBundleBase* const * >(bundles);
            self->ExecuteBundles(bundlesCount_, bundles_);
        }

        void NativeRenderPassEncoderInsertDebugMarker(WGPURenderPassEncoder cSelf, char const * markerLabel) {
            auto self = reinterpret_cast<RenderPassEncoderBase*>(cSelf);

            auto markerLabel_ = reinterpret_cast<char const * >(markerLabel);
            self->InsertDebugMarker(markerLabel_);
        }

        void NativeRenderPassEncoderPopDebugGroup(WGPURenderPassEncoder cSelf) {
            auto self = reinterpret_cast<RenderPassEncoderBase*>(cSelf);

            self->PopDebugGroup();
        }

        void NativeRenderPassEncoderPushDebugGroup(WGPURenderPassEncoder cSelf, char const * groupLabel) {
            auto self = reinterpret_cast<RenderPassEncoderBase*>(cSelf);

            auto groupLabel_ = reinterpret_cast<char const * >(groupLabel);
            self->PushDebugGroup(groupLabel_);
        }

        void NativeRenderPassEncoderSetBindGroup(WGPURenderPassEncoder cSelf, uint32_t groupIndex, WGPUBindGroup group, uint32_t dynamicOffsetCount, uint32_t const * dynamicOffsets) {
            auto self = reinterpret_cast<RenderPassEncoderBase*>(cSelf);

            auto groupIndex_ = groupIndex;
            auto group_ = reinterpret_cast<BindGroupBase* >(group);
            auto dynamicOffsetCount_ = dynamicOffsetCount;
            auto dynamicOffsets_ = reinterpret_cast<uint32_t const * >(dynamicOffsets);
            self->SetBindGroup(groupIndex_, group_, dynamicOffsetCount_, dynamicOffsets_);
        }

        void NativeRenderPassEncoderSetBlendColor(WGPURenderPassEncoder cSelf, WGPUColor const * color) {
            auto self = reinterpret_cast<RenderPassEncoderBase*>(cSelf);

            auto color_ = reinterpret_cast<Color const * >(color);
            self->SetBlendColor(color_);
        }

        void NativeRenderPassEncoderSetIndexBuffer(WGPURenderPassEncoder cSelf, WGPUBuffer buffer, uint64_t offset, uint64_t size) {
            auto self = reinterpret_cast<RenderPassEncoderBase*>(cSelf);

            auto buffer_ = reinterpret_cast<BufferBase* >(buffer);
            auto offset_ = offset;
            auto size_ = size;
            self->SetIndexBuffer(buffer_, offset_, size_);
        }

        void NativeRenderPassEncoderSetIndexBufferWithFormat(WGPURenderPassEncoder cSelf, WGPUBuffer buffer, WGPUIndexFormat format, uint64_t offset, uint64_t size) {
            auto self = reinterpret_cast<RenderPassEncoderBase*>(cSelf);

            auto buffer_ = reinterpret_cast<BufferBase* >(buffer);
            auto format_ = static_cast<wgpu::IndexFormat>(format);
            auto offset_ = offset;
            auto size_ = size;
            self->SetIndexBufferWithFormat(buffer_, format_, offset_, size_);
        }

        void NativeRenderPassEncoderSetPipeline(WGPURenderPassEncoder cSelf, WGPURenderPipeline pipeline) {
            auto self = reinterpret_cast<RenderPassEncoderBase*>(cSelf);

            auto pipeline_ = reinterpret_cast<RenderPipelineBase* >(pipeline);
            self->SetPipeline(pipeline_);
        }

        void NativeRenderPassEncoderSetScissorRect(WGPURenderPassEncoder cSelf, uint32_t x, uint32_t y, uint32_t width, uint32_t height) {
            auto self = reinterpret_cast<RenderPassEncoderBase*>(cSelf);

            auto x_ = x;
            auto y_ = y;
            auto width_ = width;
            auto height_ = height;
            self->SetScissorRect(x_, y_, width_, height_);
        }

        void NativeRenderPassEncoderSetStencilReference(WGPURenderPassEncoder cSelf, uint32_t reference) {
            auto self = reinterpret_cast<RenderPassEncoderBase*>(cSelf);

            auto reference_ = reference;
            self->SetStencilReference(reference_);
        }

        void NativeRenderPassEncoderSetVertexBuffer(WGPURenderPassEncoder cSelf, uint32_t slot, WGPUBuffer buffer, uint64_t offset, uint64_t size) {
            auto self = reinterpret_cast<RenderPassEncoderBase*>(cSelf);

            auto slot_ = slot;
            auto buffer_ = reinterpret_cast<BufferBase* >(buffer);
            auto offset_ = offset;
            auto size_ = size;
            self->SetVertexBuffer(slot_, buffer_, offset_, size_);
        }

        void NativeRenderPassEncoderSetViewport(WGPURenderPassEncoder cSelf, float x, float y, float width, float height, float minDepth, float maxDepth) {
            auto self = reinterpret_cast<RenderPassEncoderBase*>(cSelf);

            auto x_ = x;
            auto y_ = y;
            auto width_ = width;
            auto height_ = height;
            auto minDepth_ = minDepth;
            auto maxDepth_ = maxDepth;
            self->SetViewport(x_, y_, width_, height_, minDepth_, maxDepth_);
        }

        void NativeRenderPassEncoderWriteTimestamp(WGPURenderPassEncoder cSelf, WGPUQuerySet querySet, uint32_t queryIndex) {
            auto self = reinterpret_cast<RenderPassEncoderBase*>(cSelf);

            auto querySet_ = reinterpret_cast<QuerySetBase* >(querySet);
            auto queryIndex_ = queryIndex;
            self->WriteTimestamp(querySet_, queryIndex_);
        }

        void NativeRenderPassEncoderReference(WGPURenderPassEncoder cSelf) {
            auto self = reinterpret_cast<RenderPassEncoderBase*>(cSelf);

            self->Reference();
        }

        void NativeRenderPassEncoderRelease(WGPURenderPassEncoder cSelf) {
            auto self = reinterpret_cast<RenderPassEncoderBase*>(cSelf);

            self->Release();
        }

        WGPUBindGroupLayout NativeRenderPipelineGetBindGroupLayout(WGPURenderPipeline cSelf, uint32_t groupIndex) {
            auto self = reinterpret_cast<RenderPipelineBase*>(cSelf);

            auto groupIndex_ = groupIndex;
            auto result =            self->GetBindGroupLayout(groupIndex_);
            return reinterpret_cast<WGPUBindGroupLayout>(result);
        }

        void NativeRenderPipelineReference(WGPURenderPipeline cSelf) {
            auto self = reinterpret_cast<RenderPipelineBase*>(cSelf);

            self->Reference();
        }

        void NativeRenderPipelineRelease(WGPURenderPipeline cSelf) {
            auto self = reinterpret_cast<RenderPipelineBase*>(cSelf);

            self->Release();
        }

        void NativeSamplerReference(WGPUSampler cSelf) {
            auto self = reinterpret_cast<SamplerBase*>(cSelf);

            self->Reference();
        }

        void NativeSamplerRelease(WGPUSampler cSelf) {
            auto self = reinterpret_cast<SamplerBase*>(cSelf);

            self->Release();
        }

        void NativeShaderModuleReference(WGPUShaderModule cSelf) {
            auto self = reinterpret_cast<ShaderModuleBase*>(cSelf);

            self->Reference();
        }

        void NativeShaderModuleRelease(WGPUShaderModule cSelf) {
            auto self = reinterpret_cast<ShaderModuleBase*>(cSelf);

            self->Release();
        }

        void NativeSurfaceReference(WGPUSurface cSelf) {
            auto self = reinterpret_cast<SurfaceBase*>(cSelf);

            self->Reference();
        }

        void NativeSurfaceRelease(WGPUSurface cSelf) {
            auto self = reinterpret_cast<SurfaceBase*>(cSelf);

            self->Release();
        }

        void NativeSwapChainConfigure(WGPUSwapChain cSelf, WGPUTextureFormat format, WGPUTextureUsageFlags allowedUsage, uint32_t width, uint32_t height) {
            auto self = reinterpret_cast<SwapChainBase*>(cSelf);

            auto format_ = static_cast<wgpu::TextureFormat>(format);
            auto allowedUsage_ = static_cast<wgpu::TextureUsage>(allowedUsage);
            auto width_ = width;
            auto height_ = height;
            self->Configure(format_, allowedUsage_, width_, height_);
        }

        WGPUTextureView NativeSwapChainGetCurrentTextureView(WGPUSwapChain cSelf) {
            auto self = reinterpret_cast<SwapChainBase*>(cSelf);

            auto result =            self->GetCurrentTextureView();
            return reinterpret_cast<WGPUTextureView>(result);
        }

        void NativeSwapChainPresent(WGPUSwapChain cSelf) {
            auto self = reinterpret_cast<SwapChainBase*>(cSelf);

            self->Present();
        }

        void NativeSwapChainReference(WGPUSwapChain cSelf) {
            auto self = reinterpret_cast<SwapChainBase*>(cSelf);

            self->Reference();
        }

        void NativeSwapChainRelease(WGPUSwapChain cSelf) {
            auto self = reinterpret_cast<SwapChainBase*>(cSelf);

            self->Release();
        }

        WGPUTextureView NativeTextureCreateView(WGPUTexture cSelf, WGPUTextureViewDescriptor const * descriptor) {
            auto self = reinterpret_cast<TextureBase*>(cSelf);

            auto descriptor_ = reinterpret_cast<TextureViewDescriptor const * >(descriptor);
            auto result =            self->CreateView(descriptor_);
            return reinterpret_cast<WGPUTextureView>(result);
        }

        void NativeTextureDestroy(WGPUTexture cSelf) {
            auto self = reinterpret_cast<TextureBase*>(cSelf);

            self->Destroy();
        }

        void NativeTextureReference(WGPUTexture cSelf) {
            auto self = reinterpret_cast<TextureBase*>(cSelf);

            self->Reference();
        }

        void NativeTextureRelease(WGPUTexture cSelf) {
            auto self = reinterpret_cast<TextureBase*>(cSelf);

            self->Release();
        }

        void NativeTextureViewReference(WGPUTextureView cSelf) {
            auto self = reinterpret_cast<TextureViewBase*>(cSelf);

            self->Reference();
        }

        void NativeTextureViewRelease(WGPUTextureView cSelf) {
            auto self = reinterpret_cast<TextureViewBase*>(cSelf);

            self->Release();
        }

        struct ProcEntry {
            WGPUProc proc;
            const char* name;
        };
        static const ProcEntry sProcMap[] = {
            { reinterpret_cast<WGPUProc>(NativeBindGroupLayoutReference), "wgpuBindGroupLayoutReference" },
            { reinterpret_cast<WGPUProc>(NativeBindGroupLayoutRelease), "wgpuBindGroupLayoutRelease" },
            { reinterpret_cast<WGPUProc>(NativeBindGroupReference), "wgpuBindGroupReference" },
            { reinterpret_cast<WGPUProc>(NativeBindGroupRelease), "wgpuBindGroupRelease" },
            { reinterpret_cast<WGPUProc>(NativeBufferDestroy), "wgpuBufferDestroy" },
            { reinterpret_cast<WGPUProc>(NativeBufferGetConstMappedRange), "wgpuBufferGetConstMappedRange" },
            { reinterpret_cast<WGPUProc>(NativeBufferGetMappedRange), "wgpuBufferGetMappedRange" },
            { reinterpret_cast<WGPUProc>(NativeBufferMapAsync), "wgpuBufferMapAsync" },
            { reinterpret_cast<WGPUProc>(NativeBufferReference), "wgpuBufferReference" },
            { reinterpret_cast<WGPUProc>(NativeBufferRelease), "wgpuBufferRelease" },
            { reinterpret_cast<WGPUProc>(NativeBufferUnmap), "wgpuBufferUnmap" },
            { reinterpret_cast<WGPUProc>(NativeCommandBufferReference), "wgpuCommandBufferReference" },
            { reinterpret_cast<WGPUProc>(NativeCommandBufferRelease), "wgpuCommandBufferRelease" },
            { reinterpret_cast<WGPUProc>(NativeCommandEncoderBeginComputePass), "wgpuCommandEncoderBeginComputePass" },
            { reinterpret_cast<WGPUProc>(NativeCommandEncoderBeginRenderPass), "wgpuCommandEncoderBeginRenderPass" },
            { reinterpret_cast<WGPUProc>(NativeCommandEncoderCopyBufferToBuffer), "wgpuCommandEncoderCopyBufferToBuffer" },
            { reinterpret_cast<WGPUProc>(NativeCommandEncoderCopyBufferToTexture), "wgpuCommandEncoderCopyBufferToTexture" },
            { reinterpret_cast<WGPUProc>(NativeCommandEncoderCopyTextureToBuffer), "wgpuCommandEncoderCopyTextureToBuffer" },
            { reinterpret_cast<WGPUProc>(NativeCommandEncoderCopyTextureToTexture), "wgpuCommandEncoderCopyTextureToTexture" },
            { reinterpret_cast<WGPUProc>(NativeCommandEncoderFinish), "wgpuCommandEncoderFinish" },
            { reinterpret_cast<WGPUProc>(NativeCommandEncoderInsertDebugMarker), "wgpuCommandEncoderInsertDebugMarker" },
            { reinterpret_cast<WGPUProc>(NativeCommandEncoderPopDebugGroup), "wgpuCommandEncoderPopDebugGroup" },
            { reinterpret_cast<WGPUProc>(NativeCommandEncoderPushDebugGroup), "wgpuCommandEncoderPushDebugGroup" },
            { reinterpret_cast<WGPUProc>(NativeCommandEncoderReference), "wgpuCommandEncoderReference" },
            { reinterpret_cast<WGPUProc>(NativeCommandEncoderRelease), "wgpuCommandEncoderRelease" },
            { reinterpret_cast<WGPUProc>(NativeCommandEncoderResolveQuerySet), "wgpuCommandEncoderResolveQuerySet" },
            { reinterpret_cast<WGPUProc>(NativeCommandEncoderWriteTimestamp), "wgpuCommandEncoderWriteTimestamp" },
            { reinterpret_cast<WGPUProc>(NativeComputePassEncoderDispatch), "wgpuComputePassEncoderDispatch" },
            { reinterpret_cast<WGPUProc>(NativeComputePassEncoderDispatchIndirect), "wgpuComputePassEncoderDispatchIndirect" },
            { reinterpret_cast<WGPUProc>(NativeComputePassEncoderEndPass), "wgpuComputePassEncoderEndPass" },
            { reinterpret_cast<WGPUProc>(NativeComputePassEncoderInsertDebugMarker), "wgpuComputePassEncoderInsertDebugMarker" },
            { reinterpret_cast<WGPUProc>(NativeComputePassEncoderPopDebugGroup), "wgpuComputePassEncoderPopDebugGroup" },
            { reinterpret_cast<WGPUProc>(NativeComputePassEncoderPushDebugGroup), "wgpuComputePassEncoderPushDebugGroup" },
            { reinterpret_cast<WGPUProc>(NativeComputePassEncoderReference), "wgpuComputePassEncoderReference" },
            { reinterpret_cast<WGPUProc>(NativeComputePassEncoderRelease), "wgpuComputePassEncoderRelease" },
            { reinterpret_cast<WGPUProc>(NativeComputePassEncoderSetBindGroup), "wgpuComputePassEncoderSetBindGroup" },
            { reinterpret_cast<WGPUProc>(NativeComputePassEncoderSetPipeline), "wgpuComputePassEncoderSetPipeline" },
            { reinterpret_cast<WGPUProc>(NativeComputePassEncoderWriteTimestamp), "wgpuComputePassEncoderWriteTimestamp" },
            { reinterpret_cast<WGPUProc>(NativeComputePipelineGetBindGroupLayout), "wgpuComputePipelineGetBindGroupLayout" },
            { reinterpret_cast<WGPUProc>(NativeComputePipelineReference), "wgpuComputePipelineReference" },
            { reinterpret_cast<WGPUProc>(NativeComputePipelineRelease), "wgpuComputePipelineRelease" },
            { reinterpret_cast<WGPUProc>(NativeDeviceCreateBindGroup), "wgpuDeviceCreateBindGroup" },
            { reinterpret_cast<WGPUProc>(NativeDeviceCreateBindGroupLayout), "wgpuDeviceCreateBindGroupLayout" },
            { reinterpret_cast<WGPUProc>(NativeDeviceCreateBuffer), "wgpuDeviceCreateBuffer" },
            { reinterpret_cast<WGPUProc>(NativeDeviceCreateCommandEncoder), "wgpuDeviceCreateCommandEncoder" },
            { reinterpret_cast<WGPUProc>(NativeDeviceCreateComputePipeline), "wgpuDeviceCreateComputePipeline" },
            { reinterpret_cast<WGPUProc>(NativeDeviceCreateErrorBuffer), "wgpuDeviceCreateErrorBuffer" },
            { reinterpret_cast<WGPUProc>(NativeDeviceCreatePipelineLayout), "wgpuDeviceCreatePipelineLayout" },
            { reinterpret_cast<WGPUProc>(NativeDeviceCreateQuerySet), "wgpuDeviceCreateQuerySet" },
            { reinterpret_cast<WGPUProc>(NativeDeviceCreateReadyComputePipeline), "wgpuDeviceCreateReadyComputePipeline" },
            { reinterpret_cast<WGPUProc>(NativeDeviceCreateReadyRenderPipeline), "wgpuDeviceCreateReadyRenderPipeline" },
            { reinterpret_cast<WGPUProc>(NativeDeviceCreateRenderBundleEncoder), "wgpuDeviceCreateRenderBundleEncoder" },
            { reinterpret_cast<WGPUProc>(NativeDeviceCreateRenderPipeline), "wgpuDeviceCreateRenderPipeline" },
            { reinterpret_cast<WGPUProc>(NativeDeviceCreateSampler), "wgpuDeviceCreateSampler" },
            { reinterpret_cast<WGPUProc>(NativeDeviceCreateShaderModule), "wgpuDeviceCreateShaderModule" },
            { reinterpret_cast<WGPUProc>(NativeDeviceCreateSwapChain), "wgpuDeviceCreateSwapChain" },
            { reinterpret_cast<WGPUProc>(NativeDeviceCreateTexture), "wgpuDeviceCreateTexture" },
            { reinterpret_cast<WGPUProc>(NativeDeviceGetDefaultQueue), "wgpuDeviceGetDefaultQueue" },
            { reinterpret_cast<WGPUProc>(NativeDeviceInjectError), "wgpuDeviceInjectError" },
            { reinterpret_cast<WGPUProc>(NativeDeviceLoseForTesting), "wgpuDeviceLoseForTesting" },
            { reinterpret_cast<WGPUProc>(NativeDevicePopErrorScope), "wgpuDevicePopErrorScope" },
            { reinterpret_cast<WGPUProc>(NativeDevicePushErrorScope), "wgpuDevicePushErrorScope" },
            { reinterpret_cast<WGPUProc>(NativeDeviceReference), "wgpuDeviceReference" },
            { reinterpret_cast<WGPUProc>(NativeDeviceRelease), "wgpuDeviceRelease" },
            { reinterpret_cast<WGPUProc>(NativeDeviceSetDeviceLostCallback), "wgpuDeviceSetDeviceLostCallback" },
            { reinterpret_cast<WGPUProc>(NativeDeviceSetUncapturedErrorCallback), "wgpuDeviceSetUncapturedErrorCallback" },
            { reinterpret_cast<WGPUProc>(NativeDeviceTick), "wgpuDeviceTick" },
            { reinterpret_cast<WGPUProc>(NativeFenceGetCompletedValue), "wgpuFenceGetCompletedValue" },
            { reinterpret_cast<WGPUProc>(NativeFenceOnCompletion), "wgpuFenceOnCompletion" },
            { reinterpret_cast<WGPUProc>(NativeFenceReference), "wgpuFenceReference" },
            { reinterpret_cast<WGPUProc>(NativeFenceRelease), "wgpuFenceRelease" },
            { reinterpret_cast<WGPUProc>(NativeInstanceCreateSurface), "wgpuInstanceCreateSurface" },
            { reinterpret_cast<WGPUProc>(NativeInstanceReference), "wgpuInstanceReference" },
            { reinterpret_cast<WGPUProc>(NativeInstanceRelease), "wgpuInstanceRelease" },
            { reinterpret_cast<WGPUProc>(NativePipelineLayoutReference), "wgpuPipelineLayoutReference" },
            { reinterpret_cast<WGPUProc>(NativePipelineLayoutRelease), "wgpuPipelineLayoutRelease" },
            { reinterpret_cast<WGPUProc>(NativeQuerySetDestroy), "wgpuQuerySetDestroy" },
            { reinterpret_cast<WGPUProc>(NativeQuerySetReference), "wgpuQuerySetReference" },
            { reinterpret_cast<WGPUProc>(NativeQuerySetRelease), "wgpuQuerySetRelease" },
            { reinterpret_cast<WGPUProc>(NativeQueueCreateFence), "wgpuQueueCreateFence" },
            { reinterpret_cast<WGPUProc>(NativeQueueReference), "wgpuQueueReference" },
            { reinterpret_cast<WGPUProc>(NativeQueueRelease), "wgpuQueueRelease" },
            { reinterpret_cast<WGPUProc>(NativeQueueSignal), "wgpuQueueSignal" },
            { reinterpret_cast<WGPUProc>(NativeQueueSubmit), "wgpuQueueSubmit" },
            { reinterpret_cast<WGPUProc>(NativeQueueWriteBuffer), "wgpuQueueWriteBuffer" },
            { reinterpret_cast<WGPUProc>(NativeQueueWriteTexture), "wgpuQueueWriteTexture" },
            { reinterpret_cast<WGPUProc>(NativeRenderBundleEncoderDraw), "wgpuRenderBundleEncoderDraw" },
            { reinterpret_cast<WGPUProc>(NativeRenderBundleEncoderDrawIndexed), "wgpuRenderBundleEncoderDrawIndexed" },
            { reinterpret_cast<WGPUProc>(NativeRenderBundleEncoderDrawIndexedIndirect), "wgpuRenderBundleEncoderDrawIndexedIndirect" },
            { reinterpret_cast<WGPUProc>(NativeRenderBundleEncoderDrawIndirect), "wgpuRenderBundleEncoderDrawIndirect" },
            { reinterpret_cast<WGPUProc>(NativeRenderBundleEncoderFinish), "wgpuRenderBundleEncoderFinish" },
            { reinterpret_cast<WGPUProc>(NativeRenderBundleEncoderInsertDebugMarker), "wgpuRenderBundleEncoderInsertDebugMarker" },
            { reinterpret_cast<WGPUProc>(NativeRenderBundleEncoderPopDebugGroup), "wgpuRenderBundleEncoderPopDebugGroup" },
            { reinterpret_cast<WGPUProc>(NativeRenderBundleEncoderPushDebugGroup), "wgpuRenderBundleEncoderPushDebugGroup" },
            { reinterpret_cast<WGPUProc>(NativeRenderBundleEncoderReference), "wgpuRenderBundleEncoderReference" },
            { reinterpret_cast<WGPUProc>(NativeRenderBundleEncoderRelease), "wgpuRenderBundleEncoderRelease" },
            { reinterpret_cast<WGPUProc>(NativeRenderBundleEncoderSetBindGroup), "wgpuRenderBundleEncoderSetBindGroup" },
            { reinterpret_cast<WGPUProc>(NativeRenderBundleEncoderSetIndexBuffer), "wgpuRenderBundleEncoderSetIndexBuffer" },
            { reinterpret_cast<WGPUProc>(NativeRenderBundleEncoderSetIndexBufferWithFormat), "wgpuRenderBundleEncoderSetIndexBufferWithFormat" },
            { reinterpret_cast<WGPUProc>(NativeRenderBundleEncoderSetPipeline), "wgpuRenderBundleEncoderSetPipeline" },
            { reinterpret_cast<WGPUProc>(NativeRenderBundleEncoderSetVertexBuffer), "wgpuRenderBundleEncoderSetVertexBuffer" },
            { reinterpret_cast<WGPUProc>(NativeRenderBundleReference), "wgpuRenderBundleReference" },
            { reinterpret_cast<WGPUProc>(NativeRenderBundleRelease), "wgpuRenderBundleRelease" },
            { reinterpret_cast<WGPUProc>(NativeRenderPassEncoderDraw), "wgpuRenderPassEncoderDraw" },
            { reinterpret_cast<WGPUProc>(NativeRenderPassEncoderDrawIndexed), "wgpuRenderPassEncoderDrawIndexed" },
            { reinterpret_cast<WGPUProc>(NativeRenderPassEncoderDrawIndexedIndirect), "wgpuRenderPassEncoderDrawIndexedIndirect" },
            { reinterpret_cast<WGPUProc>(NativeRenderPassEncoderDrawIndirect), "wgpuRenderPassEncoderDrawIndirect" },
            { reinterpret_cast<WGPUProc>(NativeRenderPassEncoderEndPass), "wgpuRenderPassEncoderEndPass" },
            { reinterpret_cast<WGPUProc>(NativeRenderPassEncoderExecuteBundles), "wgpuRenderPassEncoderExecuteBundles" },
            { reinterpret_cast<WGPUProc>(NativeRenderPassEncoderInsertDebugMarker), "wgpuRenderPassEncoderInsertDebugMarker" },
            { reinterpret_cast<WGPUProc>(NativeRenderPassEncoderPopDebugGroup), "wgpuRenderPassEncoderPopDebugGroup" },
            { reinterpret_cast<WGPUProc>(NativeRenderPassEncoderPushDebugGroup), "wgpuRenderPassEncoderPushDebugGroup" },
            { reinterpret_cast<WGPUProc>(NativeRenderPassEncoderReference), "wgpuRenderPassEncoderReference" },
            { reinterpret_cast<WGPUProc>(NativeRenderPassEncoderRelease), "wgpuRenderPassEncoderRelease" },
            { reinterpret_cast<WGPUProc>(NativeRenderPassEncoderSetBindGroup), "wgpuRenderPassEncoderSetBindGroup" },
            { reinterpret_cast<WGPUProc>(NativeRenderPassEncoderSetBlendColor), "wgpuRenderPassEncoderSetBlendColor" },
            { reinterpret_cast<WGPUProc>(NativeRenderPassEncoderSetIndexBuffer), "wgpuRenderPassEncoderSetIndexBuffer" },
            { reinterpret_cast<WGPUProc>(NativeRenderPassEncoderSetIndexBufferWithFormat), "wgpuRenderPassEncoderSetIndexBufferWithFormat" },
            { reinterpret_cast<WGPUProc>(NativeRenderPassEncoderSetPipeline), "wgpuRenderPassEncoderSetPipeline" },
            { reinterpret_cast<WGPUProc>(NativeRenderPassEncoderSetScissorRect), "wgpuRenderPassEncoderSetScissorRect" },
            { reinterpret_cast<WGPUProc>(NativeRenderPassEncoderSetStencilReference), "wgpuRenderPassEncoderSetStencilReference" },
            { reinterpret_cast<WGPUProc>(NativeRenderPassEncoderSetVertexBuffer), "wgpuRenderPassEncoderSetVertexBuffer" },
            { reinterpret_cast<WGPUProc>(NativeRenderPassEncoderSetViewport), "wgpuRenderPassEncoderSetViewport" },
            { reinterpret_cast<WGPUProc>(NativeRenderPassEncoderWriteTimestamp), "wgpuRenderPassEncoderWriteTimestamp" },
            { reinterpret_cast<WGPUProc>(NativeRenderPipelineGetBindGroupLayout), "wgpuRenderPipelineGetBindGroupLayout" },
            { reinterpret_cast<WGPUProc>(NativeRenderPipelineReference), "wgpuRenderPipelineReference" },
            { reinterpret_cast<WGPUProc>(NativeRenderPipelineRelease), "wgpuRenderPipelineRelease" },
            { reinterpret_cast<WGPUProc>(NativeSamplerReference), "wgpuSamplerReference" },
            { reinterpret_cast<WGPUProc>(NativeSamplerRelease), "wgpuSamplerRelease" },
            { reinterpret_cast<WGPUProc>(NativeShaderModuleReference), "wgpuShaderModuleReference" },
            { reinterpret_cast<WGPUProc>(NativeShaderModuleRelease), "wgpuShaderModuleRelease" },
            { reinterpret_cast<WGPUProc>(NativeSurfaceReference), "wgpuSurfaceReference" },
            { reinterpret_cast<WGPUProc>(NativeSurfaceRelease), "wgpuSurfaceRelease" },
            { reinterpret_cast<WGPUProc>(NativeSwapChainConfigure), "wgpuSwapChainConfigure" },
            { reinterpret_cast<WGPUProc>(NativeSwapChainGetCurrentTextureView), "wgpuSwapChainGetCurrentTextureView" },
            { reinterpret_cast<WGPUProc>(NativeSwapChainPresent), "wgpuSwapChainPresent" },
            { reinterpret_cast<WGPUProc>(NativeSwapChainReference), "wgpuSwapChainReference" },
            { reinterpret_cast<WGPUProc>(NativeSwapChainRelease), "wgpuSwapChainRelease" },
            { reinterpret_cast<WGPUProc>(NativeTextureCreateView), "wgpuTextureCreateView" },
            { reinterpret_cast<WGPUProc>(NativeTextureDestroy), "wgpuTextureDestroy" },
            { reinterpret_cast<WGPUProc>(NativeTextureReference), "wgpuTextureReference" },
            { reinterpret_cast<WGPUProc>(NativeTextureRelease), "wgpuTextureRelease" },
            { reinterpret_cast<WGPUProc>(NativeTextureViewReference), "wgpuTextureViewReference" },
            { reinterpret_cast<WGPUProc>(NativeTextureViewRelease), "wgpuTextureViewRelease" },
        };
        static constexpr size_t sProcMapSize = sizeof(sProcMap) / sizeof(sProcMap[0]);
    }

    WGPUInstance NativeCreateInstance(WGPUInstanceDescriptor const* cDescriptor) {
        const dawn_native::InstanceDescriptor* descriptor =
            reinterpret_cast<const dawn_native::InstanceDescriptor*>(cDescriptor);
        return reinterpret_cast<WGPUInstance>(InstanceBase::Create(descriptor));
    }

    WGPUProc NativeGetProcAddress(WGPUDevice, const char* procName) {
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
            return reinterpret_cast<WGPUProc>(NativeGetProcAddress);
        }

        if (strcmp(procName, "wgpuCreateInstance") == 0) {
            return reinterpret_cast<WGPUProc>(NativeCreateInstance);
        }

        return nullptr;
    }

    std::vector<const char*> GetProcMapNamesForTestingInternal() {
        std::vector<const char*> result;
        result.reserve(sProcMapSize);
        for (const ProcEntry& entry : sProcMap) {
            result.push_back(entry.name);
        }
        return result;
    }

    static DawnProcTable gProcTable = {
        NativeGetProcAddress,
        NativeCreateInstance,
        NativeBindGroupReference,
        NativeBindGroupRelease,
        NativeBindGroupLayoutReference,
        NativeBindGroupLayoutRelease,
        NativeBufferDestroy,
        NativeBufferGetConstMappedRange,
        NativeBufferGetMappedRange,
        NativeBufferMapAsync,
        NativeBufferUnmap,
        NativeBufferReference,
        NativeBufferRelease,
        NativeCommandBufferReference,
        NativeCommandBufferRelease,
        NativeCommandEncoderBeginComputePass,
        NativeCommandEncoderBeginRenderPass,
        NativeCommandEncoderCopyBufferToBuffer,
        NativeCommandEncoderCopyBufferToTexture,
        NativeCommandEncoderCopyTextureToBuffer,
        NativeCommandEncoderCopyTextureToTexture,
        NativeCommandEncoderFinish,
        NativeCommandEncoderInsertDebugMarker,
        NativeCommandEncoderPopDebugGroup,
        NativeCommandEncoderPushDebugGroup,
        NativeCommandEncoderResolveQuerySet,
        NativeCommandEncoderWriteTimestamp,
        NativeCommandEncoderReference,
        NativeCommandEncoderRelease,
        NativeComputePassEncoderDispatch,
        NativeComputePassEncoderDispatchIndirect,
        NativeComputePassEncoderEndPass,
        NativeComputePassEncoderInsertDebugMarker,
        NativeComputePassEncoderPopDebugGroup,
        NativeComputePassEncoderPushDebugGroup,
        NativeComputePassEncoderSetBindGroup,
        NativeComputePassEncoderSetPipeline,
        NativeComputePassEncoderWriteTimestamp,
        NativeComputePassEncoderReference,
        NativeComputePassEncoderRelease,
        NativeComputePipelineGetBindGroupLayout,
        NativeComputePipelineReference,
        NativeComputePipelineRelease,
        NativeDeviceCreateBindGroup,
        NativeDeviceCreateBindGroupLayout,
        NativeDeviceCreateBuffer,
        NativeDeviceCreateCommandEncoder,
        NativeDeviceCreateComputePipeline,
        NativeDeviceCreateErrorBuffer,
        NativeDeviceCreatePipelineLayout,
        NativeDeviceCreateQuerySet,
        NativeDeviceCreateReadyComputePipeline,
        NativeDeviceCreateReadyRenderPipeline,
        NativeDeviceCreateRenderBundleEncoder,
        NativeDeviceCreateRenderPipeline,
        NativeDeviceCreateSampler,
        NativeDeviceCreateShaderModule,
        NativeDeviceCreateSwapChain,
        NativeDeviceCreateTexture,
        NativeDeviceGetDefaultQueue,
        NativeDeviceInjectError,
        NativeDeviceLoseForTesting,
        NativeDevicePopErrorScope,
        NativeDevicePushErrorScope,
        NativeDeviceSetDeviceLostCallback,
        NativeDeviceSetUncapturedErrorCallback,
        NativeDeviceTick,
        NativeDeviceReference,
        NativeDeviceRelease,
        NativeFenceGetCompletedValue,
        NativeFenceOnCompletion,
        NativeFenceReference,
        NativeFenceRelease,
        NativeInstanceCreateSurface,
        NativeInstanceReference,
        NativeInstanceRelease,
        NativePipelineLayoutReference,
        NativePipelineLayoutRelease,
        NativeQuerySetDestroy,
        NativeQuerySetReference,
        NativeQuerySetRelease,
        NativeQueueCreateFence,
        NativeQueueSignal,
        NativeQueueSubmit,
        NativeQueueWriteBuffer,
        NativeQueueWriteTexture,
        NativeQueueReference,
        NativeQueueRelease,
        NativeRenderBundleReference,
        NativeRenderBundleRelease,
        NativeRenderBundleEncoderDraw,
        NativeRenderBundleEncoderDrawIndexed,
        NativeRenderBundleEncoderDrawIndexedIndirect,
        NativeRenderBundleEncoderDrawIndirect,
        NativeRenderBundleEncoderFinish,
        NativeRenderBundleEncoderInsertDebugMarker,
        NativeRenderBundleEncoderPopDebugGroup,
        NativeRenderBundleEncoderPushDebugGroup,
        NativeRenderBundleEncoderSetBindGroup,
        NativeRenderBundleEncoderSetIndexBuffer,
        NativeRenderBundleEncoderSetIndexBufferWithFormat,
        NativeRenderBundleEncoderSetPipeline,
        NativeRenderBundleEncoderSetVertexBuffer,
        NativeRenderBundleEncoderReference,
        NativeRenderBundleEncoderRelease,
        NativeRenderPassEncoderDraw,
        NativeRenderPassEncoderDrawIndexed,
        NativeRenderPassEncoderDrawIndexedIndirect,
        NativeRenderPassEncoderDrawIndirect,
        NativeRenderPassEncoderEndPass,
        NativeRenderPassEncoderExecuteBundles,
        NativeRenderPassEncoderInsertDebugMarker,
        NativeRenderPassEncoderPopDebugGroup,
        NativeRenderPassEncoderPushDebugGroup,
        NativeRenderPassEncoderSetBindGroup,
        NativeRenderPassEncoderSetBlendColor,
        NativeRenderPassEncoderSetIndexBuffer,
        NativeRenderPassEncoderSetIndexBufferWithFormat,
        NativeRenderPassEncoderSetPipeline,
        NativeRenderPassEncoderSetScissorRect,
        NativeRenderPassEncoderSetStencilReference,
        NativeRenderPassEncoderSetVertexBuffer,
        NativeRenderPassEncoderSetViewport,
        NativeRenderPassEncoderWriteTimestamp,
        NativeRenderPassEncoderReference,
        NativeRenderPassEncoderRelease,
        NativeRenderPipelineGetBindGroupLayout,
        NativeRenderPipelineReference,
        NativeRenderPipelineRelease,
        NativeSamplerReference,
        NativeSamplerRelease,
        NativeShaderModuleReference,
        NativeShaderModuleRelease,
        NativeSurfaceReference,
        NativeSurfaceRelease,
        NativeSwapChainConfigure,
        NativeSwapChainGetCurrentTextureView,
        NativeSwapChainPresent,
        NativeSwapChainReference,
        NativeSwapChainRelease,
        NativeTextureCreateView,
        NativeTextureDestroy,
        NativeTextureReference,
        NativeTextureRelease,
        NativeTextureViewReference,
        NativeTextureViewRelease,
    };

    const DawnProcTable& GetProcsAutogen() {
        return gProcTable;
    }
}
