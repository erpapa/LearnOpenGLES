
#ifndef DAWNWIRE_WIRECMD_AUTOGEN_H_
#define DAWNWIRE_WIRECMD_AUTOGEN_H_

#include <dawn/webgpu.h>

namespace dawn_wire {

    using ObjectId = uint32_t;
    using ObjectGeneration = uint32_t;
    struct ObjectHandle {
      ObjectId id;
      ObjectGeneration generation;

      ObjectHandle();
      ObjectHandle(ObjectId id, ObjectGeneration generation);

      ObjectHandle(const volatile ObjectHandle& rhs);
      ObjectHandle& operator=(const volatile ObjectHandle& rhs);

      // MSVC has a bug where it thinks the volatile copy assignment is a duplicate.
      // Workaround this by forwarding to a different function AssignFrom.
      template <typename T>
      ObjectHandle& operator=(const T& rhs) {
          return AssignFrom(rhs);
      }
      ObjectHandle& AssignFrom(const ObjectHandle& rhs);
      ObjectHandle& AssignFrom(const volatile ObjectHandle& rhs);
    };

    enum class DeserializeResult {
        Success,
        FatalError,
    };

    // Interface to allocate more space to deserialize pointed-to data.
    // nullptr is treated as an error.
    class DeserializeAllocator {
        public:
            virtual void* GetSpace(size_t size) = 0;
    };

    // Interface to convert an ID to a server object, if possible.
    // Methods return FatalError if the ID is for a non-existent object and Success otherwise.
    class ObjectIdResolver {
        public:
            virtual DeserializeResult GetFromId(ObjectId id, WGPUBindGroup* out) const = 0;
            virtual DeserializeResult GetOptionalFromId(ObjectId id, WGPUBindGroup* out) const = 0;
            virtual DeserializeResult GetFromId(ObjectId id, WGPUBindGroupLayout* out) const = 0;
            virtual DeserializeResult GetOptionalFromId(ObjectId id, WGPUBindGroupLayout* out) const = 0;
            virtual DeserializeResult GetFromId(ObjectId id, WGPUBuffer* out) const = 0;
            virtual DeserializeResult GetOptionalFromId(ObjectId id, WGPUBuffer* out) const = 0;
            virtual DeserializeResult GetFromId(ObjectId id, WGPUCommandBuffer* out) const = 0;
            virtual DeserializeResult GetOptionalFromId(ObjectId id, WGPUCommandBuffer* out) const = 0;
            virtual DeserializeResult GetFromId(ObjectId id, WGPUCommandEncoder* out) const = 0;
            virtual DeserializeResult GetOptionalFromId(ObjectId id, WGPUCommandEncoder* out) const = 0;
            virtual DeserializeResult GetFromId(ObjectId id, WGPUComputePassEncoder* out) const = 0;
            virtual DeserializeResult GetOptionalFromId(ObjectId id, WGPUComputePassEncoder* out) const = 0;
            virtual DeserializeResult GetFromId(ObjectId id, WGPUComputePipeline* out) const = 0;
            virtual DeserializeResult GetOptionalFromId(ObjectId id, WGPUComputePipeline* out) const = 0;
            virtual DeserializeResult GetFromId(ObjectId id, WGPUDevice* out) const = 0;
            virtual DeserializeResult GetOptionalFromId(ObjectId id, WGPUDevice* out) const = 0;
            virtual DeserializeResult GetFromId(ObjectId id, WGPUFence* out) const = 0;
            virtual DeserializeResult GetOptionalFromId(ObjectId id, WGPUFence* out) const = 0;
            virtual DeserializeResult GetFromId(ObjectId id, WGPUInstance* out) const = 0;
            virtual DeserializeResult GetOptionalFromId(ObjectId id, WGPUInstance* out) const = 0;
            virtual DeserializeResult GetFromId(ObjectId id, WGPUPipelineLayout* out) const = 0;
            virtual DeserializeResult GetOptionalFromId(ObjectId id, WGPUPipelineLayout* out) const = 0;
            virtual DeserializeResult GetFromId(ObjectId id, WGPUQuerySet* out) const = 0;
            virtual DeserializeResult GetOptionalFromId(ObjectId id, WGPUQuerySet* out) const = 0;
            virtual DeserializeResult GetFromId(ObjectId id, WGPUQueue* out) const = 0;
            virtual DeserializeResult GetOptionalFromId(ObjectId id, WGPUQueue* out) const = 0;
            virtual DeserializeResult GetFromId(ObjectId id, WGPURenderBundle* out) const = 0;
            virtual DeserializeResult GetOptionalFromId(ObjectId id, WGPURenderBundle* out) const = 0;
            virtual DeserializeResult GetFromId(ObjectId id, WGPURenderBundleEncoder* out) const = 0;
            virtual DeserializeResult GetOptionalFromId(ObjectId id, WGPURenderBundleEncoder* out) const = 0;
            virtual DeserializeResult GetFromId(ObjectId id, WGPURenderPassEncoder* out) const = 0;
            virtual DeserializeResult GetOptionalFromId(ObjectId id, WGPURenderPassEncoder* out) const = 0;
            virtual DeserializeResult GetFromId(ObjectId id, WGPURenderPipeline* out) const = 0;
            virtual DeserializeResult GetOptionalFromId(ObjectId id, WGPURenderPipeline* out) const = 0;
            virtual DeserializeResult GetFromId(ObjectId id, WGPUSampler* out) const = 0;
            virtual DeserializeResult GetOptionalFromId(ObjectId id, WGPUSampler* out) const = 0;
            virtual DeserializeResult GetFromId(ObjectId id, WGPUShaderModule* out) const = 0;
            virtual DeserializeResult GetOptionalFromId(ObjectId id, WGPUShaderModule* out) const = 0;
            virtual DeserializeResult GetFromId(ObjectId id, WGPUSurface* out) const = 0;
            virtual DeserializeResult GetOptionalFromId(ObjectId id, WGPUSurface* out) const = 0;
            virtual DeserializeResult GetFromId(ObjectId id, WGPUSwapChain* out) const = 0;
            virtual DeserializeResult GetOptionalFromId(ObjectId id, WGPUSwapChain* out) const = 0;
            virtual DeserializeResult GetFromId(ObjectId id, WGPUTexture* out) const = 0;
            virtual DeserializeResult GetOptionalFromId(ObjectId id, WGPUTexture* out) const = 0;
            virtual DeserializeResult GetFromId(ObjectId id, WGPUTextureView* out) const = 0;
            virtual DeserializeResult GetOptionalFromId(ObjectId id, WGPUTextureView* out) const = 0;
    };

    // Interface to convert a client object to its ID for the wiring.
    class ObjectIdProvider {
        public:
            virtual ObjectId GetId(WGPUBindGroup object) const = 0;
            virtual ObjectId GetOptionalId(WGPUBindGroup object) const = 0;
            virtual ObjectId GetId(WGPUBindGroupLayout object) const = 0;
            virtual ObjectId GetOptionalId(WGPUBindGroupLayout object) const = 0;
            virtual ObjectId GetId(WGPUBuffer object) const = 0;
            virtual ObjectId GetOptionalId(WGPUBuffer object) const = 0;
            virtual ObjectId GetId(WGPUCommandBuffer object) const = 0;
            virtual ObjectId GetOptionalId(WGPUCommandBuffer object) const = 0;
            virtual ObjectId GetId(WGPUCommandEncoder object) const = 0;
            virtual ObjectId GetOptionalId(WGPUCommandEncoder object) const = 0;
            virtual ObjectId GetId(WGPUComputePassEncoder object) const = 0;
            virtual ObjectId GetOptionalId(WGPUComputePassEncoder object) const = 0;
            virtual ObjectId GetId(WGPUComputePipeline object) const = 0;
            virtual ObjectId GetOptionalId(WGPUComputePipeline object) const = 0;
            virtual ObjectId GetId(WGPUDevice object) const = 0;
            virtual ObjectId GetOptionalId(WGPUDevice object) const = 0;
            virtual ObjectId GetId(WGPUFence object) const = 0;
            virtual ObjectId GetOptionalId(WGPUFence object) const = 0;
            virtual ObjectId GetId(WGPUInstance object) const = 0;
            virtual ObjectId GetOptionalId(WGPUInstance object) const = 0;
            virtual ObjectId GetId(WGPUPipelineLayout object) const = 0;
            virtual ObjectId GetOptionalId(WGPUPipelineLayout object) const = 0;
            virtual ObjectId GetId(WGPUQuerySet object) const = 0;
            virtual ObjectId GetOptionalId(WGPUQuerySet object) const = 0;
            virtual ObjectId GetId(WGPUQueue object) const = 0;
            virtual ObjectId GetOptionalId(WGPUQueue object) const = 0;
            virtual ObjectId GetId(WGPURenderBundle object) const = 0;
            virtual ObjectId GetOptionalId(WGPURenderBundle object) const = 0;
            virtual ObjectId GetId(WGPURenderBundleEncoder object) const = 0;
            virtual ObjectId GetOptionalId(WGPURenderBundleEncoder object) const = 0;
            virtual ObjectId GetId(WGPURenderPassEncoder object) const = 0;
            virtual ObjectId GetOptionalId(WGPURenderPassEncoder object) const = 0;
            virtual ObjectId GetId(WGPURenderPipeline object) const = 0;
            virtual ObjectId GetOptionalId(WGPURenderPipeline object) const = 0;
            virtual ObjectId GetId(WGPUSampler object) const = 0;
            virtual ObjectId GetOptionalId(WGPUSampler object) const = 0;
            virtual ObjectId GetId(WGPUShaderModule object) const = 0;
            virtual ObjectId GetOptionalId(WGPUShaderModule object) const = 0;
            virtual ObjectId GetId(WGPUSurface object) const = 0;
            virtual ObjectId GetOptionalId(WGPUSurface object) const = 0;
            virtual ObjectId GetId(WGPUSwapChain object) const = 0;
            virtual ObjectId GetOptionalId(WGPUSwapChain object) const = 0;
            virtual ObjectId GetId(WGPUTexture object) const = 0;
            virtual ObjectId GetOptionalId(WGPUTexture object) const = 0;
            virtual ObjectId GetId(WGPUTextureView object) const = 0;
            virtual ObjectId GetOptionalId(WGPUTextureView object) const = 0;
    };

    enum class ObjectType : uint32_t {
        BindGroup,
        BindGroupLayout,
        Buffer,
        CommandBuffer,
        CommandEncoder,
        ComputePassEncoder,
        ComputePipeline,
        Device,
        Fence,
        Instance,
        PipelineLayout,
        QuerySet,
        Queue,
        RenderBundle,
        RenderBundleEncoder,
        RenderPassEncoder,
        RenderPipeline,
        Sampler,
        ShaderModule,
        Surface,
        SwapChain,
        Texture,
        TextureView,
    };

    enum class WireCmd : uint32_t {
        BufferDestroy,
        BufferMapAsync,
        BufferUnmap,
        BufferUpdateMappedData,
        CommandEncoderBeginComputePass,
        CommandEncoderBeginRenderPass,
        CommandEncoderCopyBufferToBuffer,
        CommandEncoderCopyBufferToTexture,
        CommandEncoderCopyTextureToBuffer,
        CommandEncoderCopyTextureToTexture,
        CommandEncoderFinish,
        CommandEncoderInsertDebugMarker,
        CommandEncoderPopDebugGroup,
        CommandEncoderPushDebugGroup,
        CommandEncoderResolveQuerySet,
        CommandEncoderWriteTimestamp,
        ComputePassEncoderDispatch,
        ComputePassEncoderDispatchIndirect,
        ComputePassEncoderEndPass,
        ComputePassEncoderInsertDebugMarker,
        ComputePassEncoderPopDebugGroup,
        ComputePassEncoderPushDebugGroup,
        ComputePassEncoderSetBindGroup,
        ComputePassEncoderSetPipeline,
        ComputePassEncoderWriteTimestamp,
        ComputePipelineGetBindGroupLayout,
        DestroyObject,
        DeviceCreateBindGroup,
        DeviceCreateBindGroupLayout,
        DeviceCreateBuffer,
        DeviceCreateCommandEncoder,
        DeviceCreateComputePipeline,
        DeviceCreateErrorBuffer,
        DeviceCreatePipelineLayout,
        DeviceCreateQuerySet,
        DeviceCreateReadyComputePipeline,
        DeviceCreateReadyRenderPipeline,
        DeviceCreateRenderBundleEncoder,
        DeviceCreateRenderPipeline,
        DeviceCreateSampler,
        DeviceCreateShaderModule,
        DeviceCreateSwapChain,
        DeviceCreateTexture,
        DeviceGetDefaultQueue,
        DeviceInjectError,
        DeviceLoseForTesting,
        DevicePopErrorScope,
        DevicePushErrorScope,
        DeviceTick,
        FenceOnCompletion,
        InstanceCreateSurface,
        QuerySetDestroy,
        QueueCreateFence,
        QueueSignal,
        QueueSubmit,
        QueueWriteBufferInternal,
        QueueWriteTextureInternal,
        RenderBundleEncoderDraw,
        RenderBundleEncoderDrawIndexed,
        RenderBundleEncoderDrawIndexedIndirect,
        RenderBundleEncoderDrawIndirect,
        RenderBundleEncoderFinish,
        RenderBundleEncoderInsertDebugMarker,
        RenderBundleEncoderPopDebugGroup,
        RenderBundleEncoderPushDebugGroup,
        RenderBundleEncoderSetBindGroup,
        RenderBundleEncoderSetIndexBuffer,
        RenderBundleEncoderSetIndexBufferWithFormat,
        RenderBundleEncoderSetPipeline,
        RenderBundleEncoderSetVertexBuffer,
        RenderPassEncoderDraw,
        RenderPassEncoderDrawIndexed,
        RenderPassEncoderDrawIndexedIndirect,
        RenderPassEncoderDrawIndirect,
        RenderPassEncoderEndPass,
        RenderPassEncoderExecuteBundles,
        RenderPassEncoderInsertDebugMarker,
        RenderPassEncoderPopDebugGroup,
        RenderPassEncoderPushDebugGroup,
        RenderPassEncoderSetBindGroup,
        RenderPassEncoderSetBlendColor,
        RenderPassEncoderSetIndexBuffer,
        RenderPassEncoderSetIndexBufferWithFormat,
        RenderPassEncoderSetPipeline,
        RenderPassEncoderSetScissorRect,
        RenderPassEncoderSetStencilReference,
        RenderPassEncoderSetVertexBuffer,
        RenderPassEncoderSetViewport,
        RenderPassEncoderWriteTimestamp,
        RenderPipelineGetBindGroupLayout,
        SwapChainConfigure,
        SwapChainGetCurrentTextureView,
        SwapChainPresent,
        TextureCreateView,
        TextureDestroy,
    };

    enum class ReturnWireCmd : uint32_t {
        BufferMapAsyncCallback,
        DeviceCreateReadyComputePipelineCallback,
        DeviceCreateReadyRenderPipelineCallback,
        DeviceLostCallback,
        DevicePopErrorScopeCallback,
        DeviceUncapturedErrorCallback,
        FenceOnCompletionCallback,
        FenceUpdateCompletedValue,
    };

    struct CmdHeader {
        uint64_t commandSize;
    };


    struct BufferDestroyCmd {
    size_t GetRequiredSize() const;

    void Serialize(size_t commandSize, char* serializeBuffer, const ObjectIdProvider& objectIdProvider) const;

    DeserializeResult Deserialize(const volatile char** buffer, size_t* size, DeserializeAllocator* allocator, const ObjectIdResolver& resolver);

    ObjectId selfId;

    WGPUBuffer self;
};

    struct BufferMapAsyncCmd {
    size_t GetRequiredSize() const;

    void Serialize(size_t commandSize, char* serializeBuffer, const ObjectIdProvider& objectIdProvider) const;

    DeserializeResult Deserialize(const volatile char** buffer, size_t* size, DeserializeAllocator* allocator);


    ObjectId bufferId;
    uint32_t requestSerial;
    WGPUMapModeFlags mode;
    size_t offset;
    size_t size;
    uint64_t handleCreateInfoLength;
    uint8_t const * handleCreateInfo;
};

    struct BufferUnmapCmd {
    size_t GetRequiredSize() const;

    void Serialize(size_t commandSize, char* serializeBuffer, const ObjectIdProvider& objectIdProvider) const;

    DeserializeResult Deserialize(const volatile char** buffer, size_t* size, DeserializeAllocator* allocator, const ObjectIdResolver& resolver);

    ObjectId selfId;

    WGPUBuffer self;
};

    struct BufferUpdateMappedDataCmd {
    size_t GetRequiredSize() const;

    void Serialize(size_t commandSize, char* serializeBuffer, const ObjectIdProvider& objectIdProvider) const;

    DeserializeResult Deserialize(const volatile char** buffer, size_t* size, DeserializeAllocator* allocator);


    ObjectId bufferId;
    uint64_t writeFlushInfoLength;
    uint8_t const * writeFlushInfo;
};

    struct CommandEncoderBeginComputePassCmd {
    size_t GetRequiredSize() const;

    void Serialize(size_t commandSize, char* serializeBuffer, const ObjectIdProvider& objectIdProvider) const;

    DeserializeResult Deserialize(const volatile char** buffer, size_t* size, DeserializeAllocator* allocator, const ObjectIdResolver& resolver);

    ObjectId selfId;

    WGPUCommandEncoder self;
    WGPUComputePassDescriptor const * descriptor;
    ObjectHandle result;
};

    struct CommandEncoderBeginRenderPassCmd {
    size_t GetRequiredSize() const;

    void Serialize(size_t commandSize, char* serializeBuffer, const ObjectIdProvider& objectIdProvider) const;

    DeserializeResult Deserialize(const volatile char** buffer, size_t* size, DeserializeAllocator* allocator, const ObjectIdResolver& resolver);

    ObjectId selfId;

    WGPUCommandEncoder self;
    WGPURenderPassDescriptor const * descriptor;
    ObjectHandle result;
};

    struct CommandEncoderCopyBufferToBufferCmd {
    size_t GetRequiredSize() const;

    void Serialize(size_t commandSize, char* serializeBuffer, const ObjectIdProvider& objectIdProvider) const;

    DeserializeResult Deserialize(const volatile char** buffer, size_t* size, DeserializeAllocator* allocator, const ObjectIdResolver& resolver);

    ObjectId selfId;

    WGPUCommandEncoder self;
    WGPUBuffer source;
    uint64_t sourceOffset;
    WGPUBuffer destination;
    uint64_t destinationOffset;
    uint64_t size;
};

    struct CommandEncoderCopyBufferToTextureCmd {
    size_t GetRequiredSize() const;

    void Serialize(size_t commandSize, char* serializeBuffer, const ObjectIdProvider& objectIdProvider) const;

    DeserializeResult Deserialize(const volatile char** buffer, size_t* size, DeserializeAllocator* allocator, const ObjectIdResolver& resolver);

    ObjectId selfId;

    WGPUCommandEncoder self;
    WGPUBufferCopyView const * source;
    WGPUTextureCopyView const * destination;
    WGPUExtent3D const * copySize;
};

    struct CommandEncoderCopyTextureToBufferCmd {
    size_t GetRequiredSize() const;

    void Serialize(size_t commandSize, char* serializeBuffer, const ObjectIdProvider& objectIdProvider) const;

    DeserializeResult Deserialize(const volatile char** buffer, size_t* size, DeserializeAllocator* allocator, const ObjectIdResolver& resolver);

    ObjectId selfId;

    WGPUCommandEncoder self;
    WGPUTextureCopyView const * source;
    WGPUBufferCopyView const * destination;
    WGPUExtent3D const * copySize;
};

    struct CommandEncoderCopyTextureToTextureCmd {
    size_t GetRequiredSize() const;

    void Serialize(size_t commandSize, char* serializeBuffer, const ObjectIdProvider& objectIdProvider) const;

    DeserializeResult Deserialize(const volatile char** buffer, size_t* size, DeserializeAllocator* allocator, const ObjectIdResolver& resolver);

    ObjectId selfId;

    WGPUCommandEncoder self;
    WGPUTextureCopyView const * source;
    WGPUTextureCopyView const * destination;
    WGPUExtent3D const * copySize;
};

    struct CommandEncoderFinishCmd {
    size_t GetRequiredSize() const;

    void Serialize(size_t commandSize, char* serializeBuffer, const ObjectIdProvider& objectIdProvider) const;

    DeserializeResult Deserialize(const volatile char** buffer, size_t* size, DeserializeAllocator* allocator, const ObjectIdResolver& resolver);

    ObjectId selfId;

    WGPUCommandEncoder self;
    WGPUCommandBufferDescriptor const * descriptor;
    ObjectHandle result;
};

    struct CommandEncoderInsertDebugMarkerCmd {
    size_t GetRequiredSize() const;

    void Serialize(size_t commandSize, char* serializeBuffer, const ObjectIdProvider& objectIdProvider) const;

    DeserializeResult Deserialize(const volatile char** buffer, size_t* size, DeserializeAllocator* allocator, const ObjectIdResolver& resolver);

    ObjectId selfId;

    WGPUCommandEncoder self;
    char const * markerLabel;
};

    struct CommandEncoderPopDebugGroupCmd {
    size_t GetRequiredSize() const;

    void Serialize(size_t commandSize, char* serializeBuffer, const ObjectIdProvider& objectIdProvider) const;

    DeserializeResult Deserialize(const volatile char** buffer, size_t* size, DeserializeAllocator* allocator, const ObjectIdResolver& resolver);

    ObjectId selfId;

    WGPUCommandEncoder self;
};

    struct CommandEncoderPushDebugGroupCmd {
    size_t GetRequiredSize() const;

    void Serialize(size_t commandSize, char* serializeBuffer, const ObjectIdProvider& objectIdProvider) const;

    DeserializeResult Deserialize(const volatile char** buffer, size_t* size, DeserializeAllocator* allocator, const ObjectIdResolver& resolver);

    ObjectId selfId;

    WGPUCommandEncoder self;
    char const * groupLabel;
};

    struct CommandEncoderResolveQuerySetCmd {
    size_t GetRequiredSize() const;

    void Serialize(size_t commandSize, char* serializeBuffer, const ObjectIdProvider& objectIdProvider) const;

    DeserializeResult Deserialize(const volatile char** buffer, size_t* size, DeserializeAllocator* allocator, const ObjectIdResolver& resolver);

    ObjectId selfId;

    WGPUCommandEncoder self;
    WGPUQuerySet querySet;
    uint32_t firstQuery;
    uint32_t queryCount;
    WGPUBuffer destination;
    uint64_t destinationOffset;
};

    struct CommandEncoderWriteTimestampCmd {
    size_t GetRequiredSize() const;

    void Serialize(size_t commandSize, char* serializeBuffer, const ObjectIdProvider& objectIdProvider) const;

    DeserializeResult Deserialize(const volatile char** buffer, size_t* size, DeserializeAllocator* allocator, const ObjectIdResolver& resolver);

    ObjectId selfId;

    WGPUCommandEncoder self;
    WGPUQuerySet querySet;
    uint32_t queryIndex;
};

    struct ComputePassEncoderDispatchCmd {
    size_t GetRequiredSize() const;

    void Serialize(size_t commandSize, char* serializeBuffer, const ObjectIdProvider& objectIdProvider) const;

    DeserializeResult Deserialize(const volatile char** buffer, size_t* size, DeserializeAllocator* allocator, const ObjectIdResolver& resolver);

    ObjectId selfId;

    WGPUComputePassEncoder self;
    uint32_t x;
    uint32_t y;
    uint32_t z;
};

    struct ComputePassEncoderDispatchIndirectCmd {
    size_t GetRequiredSize() const;

    void Serialize(size_t commandSize, char* serializeBuffer, const ObjectIdProvider& objectIdProvider) const;

    DeserializeResult Deserialize(const volatile char** buffer, size_t* size, DeserializeAllocator* allocator, const ObjectIdResolver& resolver);

    ObjectId selfId;

    WGPUComputePassEncoder self;
    WGPUBuffer indirectBuffer;
    uint64_t indirectOffset;
};

    struct ComputePassEncoderEndPassCmd {
    size_t GetRequiredSize() const;

    void Serialize(size_t commandSize, char* serializeBuffer, const ObjectIdProvider& objectIdProvider) const;

    DeserializeResult Deserialize(const volatile char** buffer, size_t* size, DeserializeAllocator* allocator, const ObjectIdResolver& resolver);

    ObjectId selfId;

    WGPUComputePassEncoder self;
};

    struct ComputePassEncoderInsertDebugMarkerCmd {
    size_t GetRequiredSize() const;

    void Serialize(size_t commandSize, char* serializeBuffer, const ObjectIdProvider& objectIdProvider) const;

    DeserializeResult Deserialize(const volatile char** buffer, size_t* size, DeserializeAllocator* allocator, const ObjectIdResolver& resolver);

    ObjectId selfId;

    WGPUComputePassEncoder self;
    char const * markerLabel;
};

    struct ComputePassEncoderPopDebugGroupCmd {
    size_t GetRequiredSize() const;

    void Serialize(size_t commandSize, char* serializeBuffer, const ObjectIdProvider& objectIdProvider) const;

    DeserializeResult Deserialize(const volatile char** buffer, size_t* size, DeserializeAllocator* allocator, const ObjectIdResolver& resolver);

    ObjectId selfId;

    WGPUComputePassEncoder self;
};

    struct ComputePassEncoderPushDebugGroupCmd {
    size_t GetRequiredSize() const;

    void Serialize(size_t commandSize, char* serializeBuffer, const ObjectIdProvider& objectIdProvider) const;

    DeserializeResult Deserialize(const volatile char** buffer, size_t* size, DeserializeAllocator* allocator, const ObjectIdResolver& resolver);

    ObjectId selfId;

    WGPUComputePassEncoder self;
    char const * groupLabel;
};

    struct ComputePassEncoderSetBindGroupCmd {
    size_t GetRequiredSize() const;

    void Serialize(size_t commandSize, char* serializeBuffer, const ObjectIdProvider& objectIdProvider) const;

    DeserializeResult Deserialize(const volatile char** buffer, size_t* size, DeserializeAllocator* allocator, const ObjectIdResolver& resolver);

    ObjectId selfId;

    WGPUComputePassEncoder self;
    uint32_t groupIndex;
    WGPUBindGroup group;
    uint32_t dynamicOffsetCount;
    uint32_t const * dynamicOffsets;
};

    struct ComputePassEncoderSetPipelineCmd {
    size_t GetRequiredSize() const;

    void Serialize(size_t commandSize, char* serializeBuffer, const ObjectIdProvider& objectIdProvider) const;

    DeserializeResult Deserialize(const volatile char** buffer, size_t* size, DeserializeAllocator* allocator, const ObjectIdResolver& resolver);

    ObjectId selfId;

    WGPUComputePassEncoder self;
    WGPUComputePipeline pipeline;
};

    struct ComputePassEncoderWriteTimestampCmd {
    size_t GetRequiredSize() const;

    void Serialize(size_t commandSize, char* serializeBuffer, const ObjectIdProvider& objectIdProvider) const;

    DeserializeResult Deserialize(const volatile char** buffer, size_t* size, DeserializeAllocator* allocator, const ObjectIdResolver& resolver);

    ObjectId selfId;

    WGPUComputePassEncoder self;
    WGPUQuerySet querySet;
    uint32_t queryIndex;
};

    struct ComputePipelineGetBindGroupLayoutCmd {
    size_t GetRequiredSize() const;

    void Serialize(size_t commandSize, char* serializeBuffer, const ObjectIdProvider& objectIdProvider) const;

    DeserializeResult Deserialize(const volatile char** buffer, size_t* size, DeserializeAllocator* allocator, const ObjectIdResolver& resolver);

    ObjectId selfId;

    WGPUComputePipeline self;
    uint32_t groupIndex;
    ObjectHandle result;
};

    struct DestroyObjectCmd {
    size_t GetRequiredSize() const;

    void Serialize(size_t commandSize, char* serializeBuffer, const ObjectIdProvider& objectIdProvider) const;

    DeserializeResult Deserialize(const volatile char** buffer, size_t* size, DeserializeAllocator* allocator);


    ObjectType objectType;
    ObjectId objectId;
};

    struct DeviceCreateBindGroupCmd {
    size_t GetRequiredSize() const;

    void Serialize(size_t commandSize, char* serializeBuffer, const ObjectIdProvider& objectIdProvider) const;

    DeserializeResult Deserialize(const volatile char** buffer, size_t* size, DeserializeAllocator* allocator, const ObjectIdResolver& resolver);

    ObjectId selfId;

    WGPUDevice self;
    WGPUBindGroupDescriptor const * descriptor;
    ObjectHandle result;
};

    struct DeviceCreateBindGroupLayoutCmd {
    size_t GetRequiredSize() const;

    void Serialize(size_t commandSize, char* serializeBuffer, const ObjectIdProvider& objectIdProvider) const;

    DeserializeResult Deserialize(const volatile char** buffer, size_t* size, DeserializeAllocator* allocator, const ObjectIdResolver& resolver);

    ObjectId selfId;

    WGPUDevice self;
    WGPUBindGroupLayoutDescriptor const * descriptor;
    ObjectHandle result;
};

    struct DeviceCreateBufferCmd {
    size_t GetRequiredSize() const;

    void Serialize(size_t commandSize, char* serializeBuffer, const ObjectIdProvider& objectIdProvider) const;

    DeserializeResult Deserialize(const volatile char** buffer, size_t* size, DeserializeAllocator* allocator, const ObjectIdResolver& resolver);


    WGPUDevice device;
    WGPUBufferDescriptor const * descriptor;
    ObjectHandle result;
    uint64_t handleCreateInfoLength;
    uint8_t const * handleCreateInfo;
};

    struct DeviceCreateCommandEncoderCmd {
    size_t GetRequiredSize() const;

    void Serialize(size_t commandSize, char* serializeBuffer, const ObjectIdProvider& objectIdProvider) const;

    DeserializeResult Deserialize(const volatile char** buffer, size_t* size, DeserializeAllocator* allocator, const ObjectIdResolver& resolver);

    ObjectId selfId;

    WGPUDevice self;
    WGPUCommandEncoderDescriptor const * descriptor;
    ObjectHandle result;
};

    struct DeviceCreateComputePipelineCmd {
    size_t GetRequiredSize() const;

    void Serialize(size_t commandSize, char* serializeBuffer, const ObjectIdProvider& objectIdProvider) const;

    DeserializeResult Deserialize(const volatile char** buffer, size_t* size, DeserializeAllocator* allocator, const ObjectIdResolver& resolver);

    ObjectId selfId;

    WGPUDevice self;
    WGPUComputePipelineDescriptor const * descriptor;
    ObjectHandle result;
};

    struct DeviceCreateErrorBufferCmd {
    size_t GetRequiredSize() const;

    void Serialize(size_t commandSize, char* serializeBuffer, const ObjectIdProvider& objectIdProvider) const;

    DeserializeResult Deserialize(const volatile char** buffer, size_t* size, DeserializeAllocator* allocator, const ObjectIdResolver& resolver);

    ObjectId selfId;

    WGPUDevice self;
    ObjectHandle result;
};

    struct DeviceCreatePipelineLayoutCmd {
    size_t GetRequiredSize() const;

    void Serialize(size_t commandSize, char* serializeBuffer, const ObjectIdProvider& objectIdProvider) const;

    DeserializeResult Deserialize(const volatile char** buffer, size_t* size, DeserializeAllocator* allocator, const ObjectIdResolver& resolver);

    ObjectId selfId;

    WGPUDevice self;
    WGPUPipelineLayoutDescriptor const * descriptor;
    ObjectHandle result;
};

    struct DeviceCreateQuerySetCmd {
    size_t GetRequiredSize() const;

    void Serialize(size_t commandSize, char* serializeBuffer, const ObjectIdProvider& objectIdProvider) const;

    DeserializeResult Deserialize(const volatile char** buffer, size_t* size, DeserializeAllocator* allocator, const ObjectIdResolver& resolver);

    ObjectId selfId;

    WGPUDevice self;
    WGPUQuerySetDescriptor const * descriptor;
    ObjectHandle result;
};

    struct DeviceCreateReadyComputePipelineCmd {
    size_t GetRequiredSize() const;

    void Serialize(size_t commandSize, char* serializeBuffer, const ObjectIdProvider& objectIdProvider) const;

    DeserializeResult Deserialize(const volatile char** buffer, size_t* size, DeserializeAllocator* allocator, const ObjectIdResolver& resolver);


    WGPUDevice device;
    uint64_t requestSerial;
    ObjectHandle pipelineObjectHandle;
    WGPUComputePipelineDescriptor const * descriptor;
};

    struct DeviceCreateReadyRenderPipelineCmd {
    size_t GetRequiredSize() const;

    void Serialize(size_t commandSize, char* serializeBuffer, const ObjectIdProvider& objectIdProvider) const;

    DeserializeResult Deserialize(const volatile char** buffer, size_t* size, DeserializeAllocator* allocator, const ObjectIdResolver& resolver);


    WGPUDevice device;
    uint64_t requestSerial;
    ObjectHandle pipelineObjectHandle;
    WGPURenderPipelineDescriptor const * descriptor;
};

    struct DeviceCreateRenderBundleEncoderCmd {
    size_t GetRequiredSize() const;

    void Serialize(size_t commandSize, char* serializeBuffer, const ObjectIdProvider& objectIdProvider) const;

    DeserializeResult Deserialize(const volatile char** buffer, size_t* size, DeserializeAllocator* allocator, const ObjectIdResolver& resolver);

    ObjectId selfId;

    WGPUDevice self;
    WGPURenderBundleEncoderDescriptor const * descriptor;
    ObjectHandle result;
};

    struct DeviceCreateRenderPipelineCmd {
    size_t GetRequiredSize() const;

    void Serialize(size_t commandSize, char* serializeBuffer, const ObjectIdProvider& objectIdProvider) const;

    DeserializeResult Deserialize(const volatile char** buffer, size_t* size, DeserializeAllocator* allocator, const ObjectIdResolver& resolver);

    ObjectId selfId;

    WGPUDevice self;
    WGPURenderPipelineDescriptor const * descriptor;
    ObjectHandle result;
};

    struct DeviceCreateSamplerCmd {
    size_t GetRequiredSize() const;

    void Serialize(size_t commandSize, char* serializeBuffer, const ObjectIdProvider& objectIdProvider) const;

    DeserializeResult Deserialize(const volatile char** buffer, size_t* size, DeserializeAllocator* allocator, const ObjectIdResolver& resolver);

    ObjectId selfId;

    WGPUDevice self;
    WGPUSamplerDescriptor const * descriptor;
    ObjectHandle result;
};

    struct DeviceCreateShaderModuleCmd {
    size_t GetRequiredSize() const;

    void Serialize(size_t commandSize, char* serializeBuffer, const ObjectIdProvider& objectIdProvider) const;

    DeserializeResult Deserialize(const volatile char** buffer, size_t* size, DeserializeAllocator* allocator, const ObjectIdResolver& resolver);

    ObjectId selfId;

    WGPUDevice self;
    WGPUShaderModuleDescriptor const * descriptor;
    ObjectHandle result;
};

    struct DeviceCreateSwapChainCmd {
    size_t GetRequiredSize() const;

    void Serialize(size_t commandSize, char* serializeBuffer, const ObjectIdProvider& objectIdProvider) const;

    DeserializeResult Deserialize(const volatile char** buffer, size_t* size, DeserializeAllocator* allocator, const ObjectIdResolver& resolver);

    ObjectId selfId;

    WGPUDevice self;
    WGPUSurface surface;
    WGPUSwapChainDescriptor const * descriptor;
    ObjectHandle result;
};

    struct DeviceCreateTextureCmd {
    size_t GetRequiredSize() const;

    void Serialize(size_t commandSize, char* serializeBuffer, const ObjectIdProvider& objectIdProvider) const;

    DeserializeResult Deserialize(const volatile char** buffer, size_t* size, DeserializeAllocator* allocator, const ObjectIdResolver& resolver);

    ObjectId selfId;

    WGPUDevice self;
    WGPUTextureDescriptor const * descriptor;
    ObjectHandle result;
};

    struct DeviceGetDefaultQueueCmd {
    size_t GetRequiredSize() const;

    void Serialize(size_t commandSize, char* serializeBuffer, const ObjectIdProvider& objectIdProvider) const;

    DeserializeResult Deserialize(const volatile char** buffer, size_t* size, DeserializeAllocator* allocator, const ObjectIdResolver& resolver);

    ObjectId selfId;

    WGPUDevice self;
    ObjectHandle result;
};

    struct DeviceInjectErrorCmd {
    size_t GetRequiredSize() const;

    void Serialize(size_t commandSize, char* serializeBuffer, const ObjectIdProvider& objectIdProvider) const;

    DeserializeResult Deserialize(const volatile char** buffer, size_t* size, DeserializeAllocator* allocator, const ObjectIdResolver& resolver);

    ObjectId selfId;

    WGPUDevice self;
    WGPUErrorType type;
    char const * message;
};

    struct DeviceLoseForTestingCmd {
    size_t GetRequiredSize() const;

    void Serialize(size_t commandSize, char* serializeBuffer, const ObjectIdProvider& objectIdProvider) const;

    DeserializeResult Deserialize(const volatile char** buffer, size_t* size, DeserializeAllocator* allocator, const ObjectIdResolver& resolver);

    ObjectId selfId;

    WGPUDevice self;
};

    struct DevicePopErrorScopeCmd {
    size_t GetRequiredSize() const;

    void Serialize(size_t commandSize, char* serializeBuffer, const ObjectIdProvider& objectIdProvider) const;

    DeserializeResult Deserialize(const volatile char** buffer, size_t* size, DeserializeAllocator* allocator, const ObjectIdResolver& resolver);


    WGPUDevice device;
    uint64_t requestSerial;
};

    struct DevicePushErrorScopeCmd {
    size_t GetRequiredSize() const;

    void Serialize(size_t commandSize, char* serializeBuffer, const ObjectIdProvider& objectIdProvider) const;

    DeserializeResult Deserialize(const volatile char** buffer, size_t* size, DeserializeAllocator* allocator, const ObjectIdResolver& resolver);

    ObjectId selfId;

    WGPUDevice self;
    WGPUErrorFilter filter;
};

    struct DeviceTickCmd {
    size_t GetRequiredSize() const;

    void Serialize(size_t commandSize, char* serializeBuffer, const ObjectIdProvider& objectIdProvider) const;

    DeserializeResult Deserialize(const volatile char** buffer, size_t* size, DeserializeAllocator* allocator, const ObjectIdResolver& resolver);

    ObjectId selfId;

    WGPUDevice self;
};

    struct FenceOnCompletionCmd {
    size_t GetRequiredSize() const;

    void Serialize(size_t commandSize, char* serializeBuffer, const ObjectIdProvider& objectIdProvider) const;

    DeserializeResult Deserialize(const volatile char** buffer, size_t* size, DeserializeAllocator* allocator);


    ObjectId fenceId;
    uint64_t value;
    uint64_t requestSerial;
};

    struct InstanceCreateSurfaceCmd {
    size_t GetRequiredSize() const;

    void Serialize(size_t commandSize, char* serializeBuffer, const ObjectIdProvider& objectIdProvider) const;

    DeserializeResult Deserialize(const volatile char** buffer, size_t* size, DeserializeAllocator* allocator, const ObjectIdResolver& resolver);

    ObjectId selfId;

    WGPUInstance self;
    WGPUSurfaceDescriptor const * descriptor;
    ObjectHandle result;
};

    struct QuerySetDestroyCmd {
    size_t GetRequiredSize() const;

    void Serialize(size_t commandSize, char* serializeBuffer, const ObjectIdProvider& objectIdProvider) const;

    DeserializeResult Deserialize(const volatile char** buffer, size_t* size, DeserializeAllocator* allocator, const ObjectIdResolver& resolver);

    ObjectId selfId;

    WGPUQuerySet self;
};

    struct QueueCreateFenceCmd {
    size_t GetRequiredSize() const;

    void Serialize(size_t commandSize, char* serializeBuffer, const ObjectIdProvider& objectIdProvider) const;

    DeserializeResult Deserialize(const volatile char** buffer, size_t* size, DeserializeAllocator* allocator, const ObjectIdResolver& resolver);

    ObjectId selfId;

    WGPUQueue self;
    WGPUFenceDescriptor const * descriptor;
    ObjectHandle result;
};

    struct QueueSignalCmd {
    size_t GetRequiredSize() const;

    void Serialize(size_t commandSize, char* serializeBuffer, const ObjectIdProvider& objectIdProvider) const;

    DeserializeResult Deserialize(const volatile char** buffer, size_t* size, DeserializeAllocator* allocator, const ObjectIdResolver& resolver);

    ObjectId selfId;

    WGPUQueue self;
    WGPUFence fence;
    uint64_t signalValue;
};

    struct QueueSubmitCmd {
    size_t GetRequiredSize() const;

    void Serialize(size_t commandSize, char* serializeBuffer, const ObjectIdProvider& objectIdProvider) const;

    DeserializeResult Deserialize(const volatile char** buffer, size_t* size, DeserializeAllocator* allocator, const ObjectIdResolver& resolver);

    ObjectId selfId;

    WGPUQueue self;
    uint32_t commandCount;
    WGPUCommandBuffer const * commands;
};

    struct QueueWriteBufferInternalCmd {
    size_t GetRequiredSize() const;

    void Serialize(size_t commandSize, char* serializeBuffer, const ObjectIdProvider& objectIdProvider) const;

    DeserializeResult Deserialize(const volatile char** buffer, size_t* size, DeserializeAllocator* allocator);


    ObjectId queueId;
    ObjectId bufferId;
    uint64_t bufferOffset;
    uint8_t const * data;
    size_t size;
};

    struct QueueWriteTextureInternalCmd {
    size_t GetRequiredSize() const;

    void Serialize(size_t commandSize, char* serializeBuffer, const ObjectIdProvider& objectIdProvider) const;

    DeserializeResult Deserialize(const volatile char** buffer, size_t* size, DeserializeAllocator* allocator, const ObjectIdResolver& resolver);


    ObjectId queueId;
    WGPUTextureCopyView const * destination;
    uint8_t const * data;
    size_t dataSize;
    WGPUTextureDataLayout const * dataLayout;
    WGPUExtent3D const * writeSize;
};

    struct RenderBundleEncoderDrawCmd {
    size_t GetRequiredSize() const;

    void Serialize(size_t commandSize, char* serializeBuffer, const ObjectIdProvider& objectIdProvider) const;

    DeserializeResult Deserialize(const volatile char** buffer, size_t* size, DeserializeAllocator* allocator, const ObjectIdResolver& resolver);

    ObjectId selfId;

    WGPURenderBundleEncoder self;
    uint32_t vertexCount;
    uint32_t instanceCount;
    uint32_t firstVertex;
    uint32_t firstInstance;
};

    struct RenderBundleEncoderDrawIndexedCmd {
    size_t GetRequiredSize() const;

    void Serialize(size_t commandSize, char* serializeBuffer, const ObjectIdProvider& objectIdProvider) const;

    DeserializeResult Deserialize(const volatile char** buffer, size_t* size, DeserializeAllocator* allocator, const ObjectIdResolver& resolver);

    ObjectId selfId;

    WGPURenderBundleEncoder self;
    uint32_t indexCount;
    uint32_t instanceCount;
    uint32_t firstIndex;
    int32_t baseVertex;
    uint32_t firstInstance;
};

    struct RenderBundleEncoderDrawIndexedIndirectCmd {
    size_t GetRequiredSize() const;

    void Serialize(size_t commandSize, char* serializeBuffer, const ObjectIdProvider& objectIdProvider) const;

    DeserializeResult Deserialize(const volatile char** buffer, size_t* size, DeserializeAllocator* allocator, const ObjectIdResolver& resolver);

    ObjectId selfId;

    WGPURenderBundleEncoder self;
    WGPUBuffer indirectBuffer;
    uint64_t indirectOffset;
};

    struct RenderBundleEncoderDrawIndirectCmd {
    size_t GetRequiredSize() const;

    void Serialize(size_t commandSize, char* serializeBuffer, const ObjectIdProvider& objectIdProvider) const;

    DeserializeResult Deserialize(const volatile char** buffer, size_t* size, DeserializeAllocator* allocator, const ObjectIdResolver& resolver);

    ObjectId selfId;

    WGPURenderBundleEncoder self;
    WGPUBuffer indirectBuffer;
    uint64_t indirectOffset;
};

    struct RenderBundleEncoderFinishCmd {
    size_t GetRequiredSize() const;

    void Serialize(size_t commandSize, char* serializeBuffer, const ObjectIdProvider& objectIdProvider) const;

    DeserializeResult Deserialize(const volatile char** buffer, size_t* size, DeserializeAllocator* allocator, const ObjectIdResolver& resolver);

    ObjectId selfId;

    WGPURenderBundleEncoder self;
    WGPURenderBundleDescriptor const * descriptor;
    ObjectHandle result;
};

    struct RenderBundleEncoderInsertDebugMarkerCmd {
    size_t GetRequiredSize() const;

    void Serialize(size_t commandSize, char* serializeBuffer, const ObjectIdProvider& objectIdProvider) const;

    DeserializeResult Deserialize(const volatile char** buffer, size_t* size, DeserializeAllocator* allocator, const ObjectIdResolver& resolver);

    ObjectId selfId;

    WGPURenderBundleEncoder self;
    char const * markerLabel;
};

    struct RenderBundleEncoderPopDebugGroupCmd {
    size_t GetRequiredSize() const;

    void Serialize(size_t commandSize, char* serializeBuffer, const ObjectIdProvider& objectIdProvider) const;

    DeserializeResult Deserialize(const volatile char** buffer, size_t* size, DeserializeAllocator* allocator, const ObjectIdResolver& resolver);

    ObjectId selfId;

    WGPURenderBundleEncoder self;
};

    struct RenderBundleEncoderPushDebugGroupCmd {
    size_t GetRequiredSize() const;

    void Serialize(size_t commandSize, char* serializeBuffer, const ObjectIdProvider& objectIdProvider) const;

    DeserializeResult Deserialize(const volatile char** buffer, size_t* size, DeserializeAllocator* allocator, const ObjectIdResolver& resolver);

    ObjectId selfId;

    WGPURenderBundleEncoder self;
    char const * groupLabel;
};

    struct RenderBundleEncoderSetBindGroupCmd {
    size_t GetRequiredSize() const;

    void Serialize(size_t commandSize, char* serializeBuffer, const ObjectIdProvider& objectIdProvider) const;

    DeserializeResult Deserialize(const volatile char** buffer, size_t* size, DeserializeAllocator* allocator, const ObjectIdResolver& resolver);

    ObjectId selfId;

    WGPURenderBundleEncoder self;
    uint32_t groupIndex;
    WGPUBindGroup group;
    uint32_t dynamicOffsetCount;
    uint32_t const * dynamicOffsets;
};

    struct RenderBundleEncoderSetIndexBufferCmd {
    size_t GetRequiredSize() const;

    void Serialize(size_t commandSize, char* serializeBuffer, const ObjectIdProvider& objectIdProvider) const;

    DeserializeResult Deserialize(const volatile char** buffer, size_t* size, DeserializeAllocator* allocator, const ObjectIdResolver& resolver);

    ObjectId selfId;

    WGPURenderBundleEncoder self;
    WGPUBuffer buffer;
    uint64_t offset;
    uint64_t size;
};

    struct RenderBundleEncoderSetIndexBufferWithFormatCmd {
    size_t GetRequiredSize() const;

    void Serialize(size_t commandSize, char* serializeBuffer, const ObjectIdProvider& objectIdProvider) const;

    DeserializeResult Deserialize(const volatile char** buffer, size_t* size, DeserializeAllocator* allocator, const ObjectIdResolver& resolver);

    ObjectId selfId;

    WGPURenderBundleEncoder self;
    WGPUBuffer buffer;
    WGPUIndexFormat format;
    uint64_t offset;
    uint64_t size;
};

    struct RenderBundleEncoderSetPipelineCmd {
    size_t GetRequiredSize() const;

    void Serialize(size_t commandSize, char* serializeBuffer, const ObjectIdProvider& objectIdProvider) const;

    DeserializeResult Deserialize(const volatile char** buffer, size_t* size, DeserializeAllocator* allocator, const ObjectIdResolver& resolver);

    ObjectId selfId;

    WGPURenderBundleEncoder self;
    WGPURenderPipeline pipeline;
};

    struct RenderBundleEncoderSetVertexBufferCmd {
    size_t GetRequiredSize() const;

    void Serialize(size_t commandSize, char* serializeBuffer, const ObjectIdProvider& objectIdProvider) const;

    DeserializeResult Deserialize(const volatile char** buffer, size_t* size, DeserializeAllocator* allocator, const ObjectIdResolver& resolver);

    ObjectId selfId;

    WGPURenderBundleEncoder self;
    uint32_t slot;
    WGPUBuffer buffer;
    uint64_t offset;
    uint64_t size;
};

    struct RenderPassEncoderDrawCmd {
    size_t GetRequiredSize() const;

    void Serialize(size_t commandSize, char* serializeBuffer, const ObjectIdProvider& objectIdProvider) const;

    DeserializeResult Deserialize(const volatile char** buffer, size_t* size, DeserializeAllocator* allocator, const ObjectIdResolver& resolver);

    ObjectId selfId;

    WGPURenderPassEncoder self;
    uint32_t vertexCount;
    uint32_t instanceCount;
    uint32_t firstVertex;
    uint32_t firstInstance;
};

    struct RenderPassEncoderDrawIndexedCmd {
    size_t GetRequiredSize() const;

    void Serialize(size_t commandSize, char* serializeBuffer, const ObjectIdProvider& objectIdProvider) const;

    DeserializeResult Deserialize(const volatile char** buffer, size_t* size, DeserializeAllocator* allocator, const ObjectIdResolver& resolver);

    ObjectId selfId;

    WGPURenderPassEncoder self;
    uint32_t indexCount;
    uint32_t instanceCount;
    uint32_t firstIndex;
    int32_t baseVertex;
    uint32_t firstInstance;
};

    struct RenderPassEncoderDrawIndexedIndirectCmd {
    size_t GetRequiredSize() const;

    void Serialize(size_t commandSize, char* serializeBuffer, const ObjectIdProvider& objectIdProvider) const;

    DeserializeResult Deserialize(const volatile char** buffer, size_t* size, DeserializeAllocator* allocator, const ObjectIdResolver& resolver);

    ObjectId selfId;

    WGPURenderPassEncoder self;
    WGPUBuffer indirectBuffer;
    uint64_t indirectOffset;
};

    struct RenderPassEncoderDrawIndirectCmd {
    size_t GetRequiredSize() const;

    void Serialize(size_t commandSize, char* serializeBuffer, const ObjectIdProvider& objectIdProvider) const;

    DeserializeResult Deserialize(const volatile char** buffer, size_t* size, DeserializeAllocator* allocator, const ObjectIdResolver& resolver);

    ObjectId selfId;

    WGPURenderPassEncoder self;
    WGPUBuffer indirectBuffer;
    uint64_t indirectOffset;
};

    struct RenderPassEncoderEndPassCmd {
    size_t GetRequiredSize() const;

    void Serialize(size_t commandSize, char* serializeBuffer, const ObjectIdProvider& objectIdProvider) const;

    DeserializeResult Deserialize(const volatile char** buffer, size_t* size, DeserializeAllocator* allocator, const ObjectIdResolver& resolver);

    ObjectId selfId;

    WGPURenderPassEncoder self;
};

    struct RenderPassEncoderExecuteBundlesCmd {
    size_t GetRequiredSize() const;

    void Serialize(size_t commandSize, char* serializeBuffer, const ObjectIdProvider& objectIdProvider) const;

    DeserializeResult Deserialize(const volatile char** buffer, size_t* size, DeserializeAllocator* allocator, const ObjectIdResolver& resolver);

    ObjectId selfId;

    WGPURenderPassEncoder self;
    uint32_t bundlesCount;
    WGPURenderBundle const * bundles;
};

    struct RenderPassEncoderInsertDebugMarkerCmd {
    size_t GetRequiredSize() const;

    void Serialize(size_t commandSize, char* serializeBuffer, const ObjectIdProvider& objectIdProvider) const;

    DeserializeResult Deserialize(const volatile char** buffer, size_t* size, DeserializeAllocator* allocator, const ObjectIdResolver& resolver);

    ObjectId selfId;

    WGPURenderPassEncoder self;
    char const * markerLabel;
};

    struct RenderPassEncoderPopDebugGroupCmd {
    size_t GetRequiredSize() const;

    void Serialize(size_t commandSize, char* serializeBuffer, const ObjectIdProvider& objectIdProvider) const;

    DeserializeResult Deserialize(const volatile char** buffer, size_t* size, DeserializeAllocator* allocator, const ObjectIdResolver& resolver);

    ObjectId selfId;

    WGPURenderPassEncoder self;
};

    struct RenderPassEncoderPushDebugGroupCmd {
    size_t GetRequiredSize() const;

    void Serialize(size_t commandSize, char* serializeBuffer, const ObjectIdProvider& objectIdProvider) const;

    DeserializeResult Deserialize(const volatile char** buffer, size_t* size, DeserializeAllocator* allocator, const ObjectIdResolver& resolver);

    ObjectId selfId;

    WGPURenderPassEncoder self;
    char const * groupLabel;
};

    struct RenderPassEncoderSetBindGroupCmd {
    size_t GetRequiredSize() const;

    void Serialize(size_t commandSize, char* serializeBuffer, const ObjectIdProvider& objectIdProvider) const;

    DeserializeResult Deserialize(const volatile char** buffer, size_t* size, DeserializeAllocator* allocator, const ObjectIdResolver& resolver);

    ObjectId selfId;

    WGPURenderPassEncoder self;
    uint32_t groupIndex;
    WGPUBindGroup group;
    uint32_t dynamicOffsetCount;
    uint32_t const * dynamicOffsets;
};

    struct RenderPassEncoderSetBlendColorCmd {
    size_t GetRequiredSize() const;

    void Serialize(size_t commandSize, char* serializeBuffer, const ObjectIdProvider& objectIdProvider) const;

    DeserializeResult Deserialize(const volatile char** buffer, size_t* size, DeserializeAllocator* allocator, const ObjectIdResolver& resolver);

    ObjectId selfId;

    WGPURenderPassEncoder self;
    WGPUColor const * color;
};

    struct RenderPassEncoderSetIndexBufferCmd {
    size_t GetRequiredSize() const;

    void Serialize(size_t commandSize, char* serializeBuffer, const ObjectIdProvider& objectIdProvider) const;

    DeserializeResult Deserialize(const volatile char** buffer, size_t* size, DeserializeAllocator* allocator, const ObjectIdResolver& resolver);

    ObjectId selfId;

    WGPURenderPassEncoder self;
    WGPUBuffer buffer;
    uint64_t offset;
    uint64_t size;
};

    struct RenderPassEncoderSetIndexBufferWithFormatCmd {
    size_t GetRequiredSize() const;

    void Serialize(size_t commandSize, char* serializeBuffer, const ObjectIdProvider& objectIdProvider) const;

    DeserializeResult Deserialize(const volatile char** buffer, size_t* size, DeserializeAllocator* allocator, const ObjectIdResolver& resolver);

    ObjectId selfId;

    WGPURenderPassEncoder self;
    WGPUBuffer buffer;
    WGPUIndexFormat format;
    uint64_t offset;
    uint64_t size;
};

    struct RenderPassEncoderSetPipelineCmd {
    size_t GetRequiredSize() const;

    void Serialize(size_t commandSize, char* serializeBuffer, const ObjectIdProvider& objectIdProvider) const;

    DeserializeResult Deserialize(const volatile char** buffer, size_t* size, DeserializeAllocator* allocator, const ObjectIdResolver& resolver);

    ObjectId selfId;

    WGPURenderPassEncoder self;
    WGPURenderPipeline pipeline;
};

    struct RenderPassEncoderSetScissorRectCmd {
    size_t GetRequiredSize() const;

    void Serialize(size_t commandSize, char* serializeBuffer, const ObjectIdProvider& objectIdProvider) const;

    DeserializeResult Deserialize(const volatile char** buffer, size_t* size, DeserializeAllocator* allocator, const ObjectIdResolver& resolver);

    ObjectId selfId;

    WGPURenderPassEncoder self;
    uint32_t x;
    uint32_t y;
    uint32_t width;
    uint32_t height;
};

    struct RenderPassEncoderSetStencilReferenceCmd {
    size_t GetRequiredSize() const;

    void Serialize(size_t commandSize, char* serializeBuffer, const ObjectIdProvider& objectIdProvider) const;

    DeserializeResult Deserialize(const volatile char** buffer, size_t* size, DeserializeAllocator* allocator, const ObjectIdResolver& resolver);

    ObjectId selfId;

    WGPURenderPassEncoder self;
    uint32_t reference;
};

    struct RenderPassEncoderSetVertexBufferCmd {
    size_t GetRequiredSize() const;

    void Serialize(size_t commandSize, char* serializeBuffer, const ObjectIdProvider& objectIdProvider) const;

    DeserializeResult Deserialize(const volatile char** buffer, size_t* size, DeserializeAllocator* allocator, const ObjectIdResolver& resolver);

    ObjectId selfId;

    WGPURenderPassEncoder self;
    uint32_t slot;
    WGPUBuffer buffer;
    uint64_t offset;
    uint64_t size;
};

    struct RenderPassEncoderSetViewportCmd {
    size_t GetRequiredSize() const;

    void Serialize(size_t commandSize, char* serializeBuffer, const ObjectIdProvider& objectIdProvider) const;

    DeserializeResult Deserialize(const volatile char** buffer, size_t* size, DeserializeAllocator* allocator, const ObjectIdResolver& resolver);

    ObjectId selfId;

    WGPURenderPassEncoder self;
    float x;
    float y;
    float width;
    float height;
    float minDepth;
    float maxDepth;
};

    struct RenderPassEncoderWriteTimestampCmd {
    size_t GetRequiredSize() const;

    void Serialize(size_t commandSize, char* serializeBuffer, const ObjectIdProvider& objectIdProvider) const;

    DeserializeResult Deserialize(const volatile char** buffer, size_t* size, DeserializeAllocator* allocator, const ObjectIdResolver& resolver);

    ObjectId selfId;

    WGPURenderPassEncoder self;
    WGPUQuerySet querySet;
    uint32_t queryIndex;
};

    struct RenderPipelineGetBindGroupLayoutCmd {
    size_t GetRequiredSize() const;

    void Serialize(size_t commandSize, char* serializeBuffer, const ObjectIdProvider& objectIdProvider) const;

    DeserializeResult Deserialize(const volatile char** buffer, size_t* size, DeserializeAllocator* allocator, const ObjectIdResolver& resolver);

    ObjectId selfId;

    WGPURenderPipeline self;
    uint32_t groupIndex;
    ObjectHandle result;
};

    struct SwapChainConfigureCmd {
    size_t GetRequiredSize() const;

    void Serialize(size_t commandSize, char* serializeBuffer, const ObjectIdProvider& objectIdProvider) const;

    DeserializeResult Deserialize(const volatile char** buffer, size_t* size, DeserializeAllocator* allocator, const ObjectIdResolver& resolver);

    ObjectId selfId;

    WGPUSwapChain self;
    WGPUTextureFormat format;
    WGPUTextureUsageFlags allowedUsage;
    uint32_t width;
    uint32_t height;
};

    struct SwapChainGetCurrentTextureViewCmd {
    size_t GetRequiredSize() const;

    void Serialize(size_t commandSize, char* serializeBuffer, const ObjectIdProvider& objectIdProvider) const;

    DeserializeResult Deserialize(const volatile char** buffer, size_t* size, DeserializeAllocator* allocator, const ObjectIdResolver& resolver);

    ObjectId selfId;

    WGPUSwapChain self;
    ObjectHandle result;
};

    struct SwapChainPresentCmd {
    size_t GetRequiredSize() const;

    void Serialize(size_t commandSize, char* serializeBuffer, const ObjectIdProvider& objectIdProvider) const;

    DeserializeResult Deserialize(const volatile char** buffer, size_t* size, DeserializeAllocator* allocator, const ObjectIdResolver& resolver);

    ObjectId selfId;

    WGPUSwapChain self;
};

    struct TextureCreateViewCmd {
    size_t GetRequiredSize() const;

    void Serialize(size_t commandSize, char* serializeBuffer, const ObjectIdProvider& objectIdProvider) const;

    DeserializeResult Deserialize(const volatile char** buffer, size_t* size, DeserializeAllocator* allocator, const ObjectIdResolver& resolver);

    ObjectId selfId;

    WGPUTexture self;
    WGPUTextureViewDescriptor const * descriptor;
    ObjectHandle result;
};

    struct TextureDestroyCmd {
    size_t GetRequiredSize() const;

    void Serialize(size_t commandSize, char* serializeBuffer, const ObjectIdProvider& objectIdProvider) const;

    DeserializeResult Deserialize(const volatile char** buffer, size_t* size, DeserializeAllocator* allocator, const ObjectIdResolver& resolver);

    ObjectId selfId;

    WGPUTexture self;
};


    struct ReturnBufferMapAsyncCallbackCmd {
    size_t GetRequiredSize() const;

    void Serialize(size_t commandSize, char* serializeBuffer) const;

    DeserializeResult Deserialize(const volatile char** buffer, size_t* size, DeserializeAllocator* allocator);


    ObjectHandle buffer;
    uint32_t requestSerial;
    uint32_t status;
    uint64_t readInitialDataInfoLength;
    uint8_t const * readInitialDataInfo;
};

    struct ReturnDeviceCreateReadyComputePipelineCallbackCmd {
    size_t GetRequiredSize() const;

    void Serialize(size_t commandSize, char* serializeBuffer) const;

    DeserializeResult Deserialize(const volatile char** buffer, size_t* size, DeserializeAllocator* allocator);


    uint64_t requestSerial;
    WGPUCreateReadyPipelineStatus status;
    char const * message;
};

    struct ReturnDeviceCreateReadyRenderPipelineCallbackCmd {
    size_t GetRequiredSize() const;

    void Serialize(size_t commandSize, char* serializeBuffer) const;

    DeserializeResult Deserialize(const volatile char** buffer, size_t* size, DeserializeAllocator* allocator);


    uint64_t requestSerial;
    WGPUCreateReadyPipelineStatus status;
    char const * message;
};

    struct ReturnDeviceLostCallbackCmd {
    size_t GetRequiredSize() const;

    void Serialize(size_t commandSize, char* serializeBuffer) const;

    DeserializeResult Deserialize(const volatile char** buffer, size_t* size, DeserializeAllocator* allocator);


    char const * message;
};

    struct ReturnDevicePopErrorScopeCallbackCmd {
    size_t GetRequiredSize() const;

    void Serialize(size_t commandSize, char* serializeBuffer) const;

    DeserializeResult Deserialize(const volatile char** buffer, size_t* size, DeserializeAllocator* allocator);


    uint64_t requestSerial;
    WGPUErrorType type;
    char const * message;
};

    struct ReturnDeviceUncapturedErrorCallbackCmd {
    size_t GetRequiredSize() const;

    void Serialize(size_t commandSize, char* serializeBuffer) const;

    DeserializeResult Deserialize(const volatile char** buffer, size_t* size, DeserializeAllocator* allocator);


    WGPUErrorType type;
    char const * message;
};

    struct ReturnFenceOnCompletionCallbackCmd {
    size_t GetRequiredSize() const;

    void Serialize(size_t commandSize, char* serializeBuffer) const;

    DeserializeResult Deserialize(const volatile char** buffer, size_t* size, DeserializeAllocator* allocator);


    ObjectHandle fence;
    uint64_t requestSerial;
    WGPUFenceCompletionStatus status;
};

    struct ReturnFenceUpdateCompletedValueCmd {
    size_t GetRequiredSize() const;

    void Serialize(size_t commandSize, char* serializeBuffer) const;

    DeserializeResult Deserialize(const volatile char** buffer, size_t* size, DeserializeAllocator* allocator);


    ObjectHandle fence;
    uint64_t value;
};


}  // namespace dawn_wire

#endif // DAWNWIRE_WIRECMD_AUTOGEN_H_
