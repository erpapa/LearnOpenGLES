
#include "dawn_wire/WireCmd_autogen.h"

#include "common/Assert.h"
#include "dawn_wire/Wire.h"

#include <algorithm>
#include <cstring>
#include <limits>







namespace {

    struct WGPUChainedStructTransfer {
        WGPUSType sType;
        bool hasNext;
    };

}  // anonymous namespace



namespace dawn_wire {

    // Macro to simplify error handling, similar to DAWN_TRY but for DeserializeResult.
#define DESERIALIZE_TRY(EXPR) \
    do { \
        DeserializeResult exprResult = EXPR; \
        if (exprResult != DeserializeResult::Success) { \
            return exprResult; \
        } \
    } while (0)

    ObjectHandle::ObjectHandle() = default;
    ObjectHandle::ObjectHandle(ObjectId id, ObjectGeneration generation)
        : id(id), generation(generation) {
    }

    ObjectHandle::ObjectHandle(const volatile ObjectHandle& rhs)
        : id(rhs.id), generation(rhs.generation) {
    }
    ObjectHandle& ObjectHandle::operator=(const volatile ObjectHandle& rhs) {
        id = rhs.id;
        generation = rhs.generation;
        return *this;
    }

    ObjectHandle& ObjectHandle::AssignFrom(const ObjectHandle& rhs) {
        id = rhs.id;
        generation = rhs.generation;
        return *this;
    }
    ObjectHandle& ObjectHandle::AssignFrom(const volatile ObjectHandle& rhs) {
        id = rhs.id;
        generation = rhs.generation;
        return *this;
    }

    namespace {

        // Consumes from (buffer, size) enough memory to contain T[count] and return it in data.
        // Returns FatalError if not enough memory was available
        template <typename T>
        DeserializeResult GetPtrFromBuffer(const volatile char** buffer, size_t* size, size_t count, const volatile T** data) {
            constexpr size_t kMaxCountWithoutOverflows = std::numeric_limits<size_t>::max() / sizeof(T);
            if (count > kMaxCountWithoutOverflows) {
                return DeserializeResult::FatalError;
            }

            size_t totalSize = sizeof(T) * count;
            if (totalSize > *size) {
                return DeserializeResult::FatalError;
            }

            *data = reinterpret_cast<const volatile T*>(*buffer);
            *buffer += totalSize;
            *size -= totalSize;

            return DeserializeResult::Success;
        }

        // Allocates enough space from allocator to countain T[count] and return it in out.
        // Return FatalError if the allocator couldn't allocate the memory.
        template <typename T>
        DeserializeResult GetSpace(DeserializeAllocator* allocator, size_t count, T** out) {
            constexpr size_t kMaxCountWithoutOverflows = std::numeric_limits<size_t>::max() / sizeof(T);
            if (count > kMaxCountWithoutOverflows) {
                return DeserializeResult::FatalError;
            }

            size_t totalSize = sizeof(T) * count;
            *out = static_cast<T*>(allocator->GetSpace(totalSize));
            if (*out == nullptr) {
                return DeserializeResult::FatalError;
            }

            return DeserializeResult::Success;
        }

        size_t GetChainedStructExtraRequiredSize(const WGPUChainedStruct* chainedStruct);
        void SerializeChainedStruct(WGPUChainedStruct const* chainedStruct,
                                    char** buffer,
                                    const ObjectIdProvider& provider);
        DeserializeResult DeserializeChainedStruct(const WGPUChainedStruct** outChainNext,
                                                   const volatile char** buffer,
                                                   size_t* size,
                                                   DeserializeAllocator* allocator,
                                                   const ObjectIdResolver& resolver);

        
struct WGPUAdapterPropertiesTransfer {
    static_assert(1 <= 1,
                  "Record must be at most one of is_cmd, extensible, and chained.");
    bool hasNextInChain;

    uint32_t deviceID;
    uint32_t vendorID;
    WGPUAdapterType adapterType;
    WGPUBackendType backendType;


};



DAWN_DECLARE_UNUSED size_t WGPUAdapterPropertiesGetExtraRequiredSize(const WGPUAdapterProperties& record) {
    DAWN_UNUSED(record);

    size_t result = 0;

    if (record.nextInChain != nullptr) {
        result += GetChainedStructExtraRequiredSize(record.nextInChain);
    }


    {
    }
    {
    }
    {
        size_t memberLength = 1;
        result += memberLength * sizeof(char);
    }
    {
        size_t memberLength = 1;
        result += memberLength * sizeof(char);
    }
    {
    }
    {
    }

    return result;
}
// GetExtraRequiredSize isn't used for structures that are value members of other structures
// because we assume they cannot contain pointers themselves.
DAWN_UNUSED_FUNC(WGPUAdapterPropertiesGetExtraRequiredSize);

DAWN_DECLARE_UNUSED void WGPUAdapterPropertiesSerialize(const WGPUAdapterProperties& record, WGPUAdapterPropertiesTransfer* transfer,
                       char** buffer, const ObjectIdProvider& provider) {
    DAWN_UNUSED(buffer);


    transfer->deviceID = record.deviceID;
    transfer->vendorID = record.vendorID;
    transfer->adapterType = record.adapterType;
    transfer->backendType = record.backendType;

    if (record.nextInChain != nullptr) {
        transfer->hasNextInChain = true;
        SerializeChainedStruct(record.nextInChain, buffer, provider);
    } else {
        transfer->hasNextInChain = false;
    }




    {
        size_t memberLength = 1;
        auto memberBuffer = reinterpret_cast<char*>(*buffer);
        *buffer += memberLength * sizeof(char);

        for (size_t i = 0; i < memberLength; ++i) {
            memberBuffer[i] = record.name[i];
        }
    }

    {
        size_t memberLength = 1;
        auto memberBuffer = reinterpret_cast<char*>(*buffer);
        *buffer += memberLength * sizeof(char);

        for (size_t i = 0; i < memberLength; ++i) {
            memberBuffer[i] = record.driverDescription[i];
        }
    }
}
DAWN_UNUSED_FUNC(WGPUAdapterPropertiesSerialize);

DAWN_DECLARE_UNUSED DeserializeResult WGPUAdapterPropertiesDeserialize(WGPUAdapterProperties* record, const volatile WGPUAdapterPropertiesTransfer* transfer,
                                      const volatile char** buffer, size_t* size, DeserializeAllocator* allocator, const ObjectIdResolver& resolver) {
    DAWN_UNUSED(allocator);
    DAWN_UNUSED(buffer);
    DAWN_UNUSED(size);



    record->deviceID = transfer->deviceID;
    record->vendorID = transfer->vendorID;
    record->adapterType = transfer->adapterType;
    record->backendType = transfer->backendType;

    record->nextInChain = nullptr;
    if (transfer->hasNextInChain) {
        DESERIALIZE_TRY(DeserializeChainedStruct(&record->nextInChain, buffer, size, allocator, resolver));
    }




    {
        size_t memberLength = 1;
        auto memberBuffer = reinterpret_cast<const volatile char*>(buffer);
        DESERIALIZE_TRY(GetPtrFromBuffer(buffer, size, memberLength, &memberBuffer));

        char* copiedMembers = nullptr;
        DESERIALIZE_TRY(GetSpace(allocator, memberLength, &copiedMembers));
        record->name = copiedMembers;

        for (size_t i = 0; i < memberLength; ++i) {
            copiedMembers[i] = memberBuffer[i];
        }
    }

    {
        size_t memberLength = 1;
        auto memberBuffer = reinterpret_cast<const volatile char*>(buffer);
        DESERIALIZE_TRY(GetPtrFromBuffer(buffer, size, memberLength, &memberBuffer));

        char* copiedMembers = nullptr;
        DESERIALIZE_TRY(GetSpace(allocator, memberLength, &copiedMembers));
        record->driverDescription = copiedMembers;

        for (size_t i = 0; i < memberLength; ++i) {
            copiedMembers[i] = memberBuffer[i];
        }
    }

    return DeserializeResult::Success;
}
DAWN_UNUSED_FUNC(WGPUAdapterPropertiesDeserialize);

        
struct WGPUBindGroupEntryTransfer {
    static_assert(0 <= 1,
                  "Record must be at most one of is_cmd, extensible, and chained.");

    uint32_t binding;
    ObjectId buffer;
    uint64_t offset;
    uint64_t size;
    ObjectId sampler;
    ObjectId textureView;


};



DAWN_DECLARE_UNUSED size_t WGPUBindGroupEntryGetExtraRequiredSize(const WGPUBindGroupEntry& record) {
    DAWN_UNUSED(record);

    size_t result = 0;



    {
    }
    {
    }
    {
    }
    {
    }
    {
    }
    {
    }

    return result;
}
// GetExtraRequiredSize isn't used for structures that are value members of other structures
// because we assume they cannot contain pointers themselves.
DAWN_UNUSED_FUNC(WGPUBindGroupEntryGetExtraRequiredSize);

DAWN_DECLARE_UNUSED void WGPUBindGroupEntrySerialize(const WGPUBindGroupEntry& record, WGPUBindGroupEntryTransfer* transfer,
                       char** buffer, const ObjectIdProvider& provider) {
    DAWN_UNUSED(buffer);


    transfer->binding = record.binding;
    transfer->buffer = provider.GetOptionalId(record.buffer);

    transfer->offset = record.offset;
    transfer->size = record.size;
    transfer->sampler = provider.GetOptionalId(record.sampler);

    transfer->textureView = provider.GetOptionalId(record.textureView);





}
DAWN_UNUSED_FUNC(WGPUBindGroupEntrySerialize);

DAWN_DECLARE_UNUSED DeserializeResult WGPUBindGroupEntryDeserialize(WGPUBindGroupEntry* record, const volatile WGPUBindGroupEntryTransfer* transfer,
                                      const volatile char** buffer, size_t* size, DeserializeAllocator* allocator, const ObjectIdResolver& resolver) {
    DAWN_UNUSED(allocator);
    DAWN_UNUSED(buffer);
    DAWN_UNUSED(size);



    record->binding = transfer->binding;
    DESERIALIZE_TRY(resolver.GetOptionalFromId(transfer->buffer, &record->buffer));
    record->offset = transfer->offset;
    record->size = transfer->size;
    DESERIALIZE_TRY(resolver.GetOptionalFromId(transfer->sampler, &record->sampler));
    DESERIALIZE_TRY(resolver.GetOptionalFromId(transfer->textureView, &record->textureView));





    return DeserializeResult::Success;
}
DAWN_UNUSED_FUNC(WGPUBindGroupEntryDeserialize);

        
struct WGPUBindGroupLayoutEntryTransfer {
    static_assert(0 <= 1,
                  "Record must be at most one of is_cmd, extensible, and chained.");

    uint32_t binding;
    WGPUShaderStageFlags visibility;
    WGPUBindingType type;
    bool hasDynamicOffset;
    uint64_t minBufferBindingSize;
    bool multisampled;
    WGPUTextureViewDimension viewDimension;
    WGPUTextureComponentType textureComponentType;
    WGPUTextureFormat storageTextureFormat;


};



DAWN_DECLARE_UNUSED size_t WGPUBindGroupLayoutEntryGetExtraRequiredSize(const WGPUBindGroupLayoutEntry& record) {
    DAWN_UNUSED(record);

    size_t result = 0;



    {
    }
    {
    }
    {
    }
    {
    }
    {
    }
    {
    }
    {
    }
    {
    }
    {
    }

    return result;
}
// GetExtraRequiredSize isn't used for structures that are value members of other structures
// because we assume they cannot contain pointers themselves.
DAWN_UNUSED_FUNC(WGPUBindGroupLayoutEntryGetExtraRequiredSize);

DAWN_DECLARE_UNUSED void WGPUBindGroupLayoutEntrySerialize(const WGPUBindGroupLayoutEntry& record, WGPUBindGroupLayoutEntryTransfer* transfer,
                       char** buffer) {
    DAWN_UNUSED(buffer);


    transfer->binding = record.binding;
    transfer->visibility = record.visibility;
    transfer->type = record.type;
    transfer->hasDynamicOffset = record.hasDynamicOffset;
    transfer->minBufferBindingSize = record.minBufferBindingSize;
    transfer->multisampled = record.multisampled;
    transfer->viewDimension = record.viewDimension;
    transfer->textureComponentType = record.textureComponentType;
    transfer->storageTextureFormat = record.storageTextureFormat;




}
DAWN_UNUSED_FUNC(WGPUBindGroupLayoutEntrySerialize);

DAWN_DECLARE_UNUSED DeserializeResult WGPUBindGroupLayoutEntryDeserialize(WGPUBindGroupLayoutEntry* record, const volatile WGPUBindGroupLayoutEntryTransfer* transfer,
                                      const volatile char** buffer, size_t* size, DeserializeAllocator* allocator) {
    DAWN_UNUSED(allocator);
    DAWN_UNUSED(buffer);
    DAWN_UNUSED(size);



    record->binding = transfer->binding;
    record->visibility = transfer->visibility;
    record->type = transfer->type;
    record->hasDynamicOffset = transfer->hasDynamicOffset;
    record->minBufferBindingSize = transfer->minBufferBindingSize;
    record->multisampled = transfer->multisampled;
    record->viewDimension = transfer->viewDimension;
    record->textureComponentType = transfer->textureComponentType;
    record->storageTextureFormat = transfer->storageTextureFormat;





    return DeserializeResult::Success;
}
DAWN_UNUSED_FUNC(WGPUBindGroupLayoutEntryDeserialize);

        
struct WGPUBlendDescriptorTransfer {
    static_assert(0 <= 1,
                  "Record must be at most one of is_cmd, extensible, and chained.");

    WGPUBlendOperation operation;
    WGPUBlendFactor srcFactor;
    WGPUBlendFactor dstFactor;


};



DAWN_DECLARE_UNUSED size_t WGPUBlendDescriptorGetExtraRequiredSize(const WGPUBlendDescriptor& record) {
    DAWN_UNUSED(record);

    size_t result = 0;



    {
    }
    {
    }
    {
    }

    return result;
}
// GetExtraRequiredSize isn't used for structures that are value members of other structures
// because we assume they cannot contain pointers themselves.
DAWN_UNUSED_FUNC(WGPUBlendDescriptorGetExtraRequiredSize);

DAWN_DECLARE_UNUSED void WGPUBlendDescriptorSerialize(const WGPUBlendDescriptor& record, WGPUBlendDescriptorTransfer* transfer,
                       char** buffer) {
    DAWN_UNUSED(buffer);


    transfer->operation = record.operation;
    transfer->srcFactor = record.srcFactor;
    transfer->dstFactor = record.dstFactor;




}
DAWN_UNUSED_FUNC(WGPUBlendDescriptorSerialize);

DAWN_DECLARE_UNUSED DeserializeResult WGPUBlendDescriptorDeserialize(WGPUBlendDescriptor* record, const volatile WGPUBlendDescriptorTransfer* transfer,
                                      const volatile char** buffer, size_t* size, DeserializeAllocator* allocator) {
    DAWN_UNUSED(allocator);
    DAWN_UNUSED(buffer);
    DAWN_UNUSED(size);



    record->operation = transfer->operation;
    record->srcFactor = transfer->srcFactor;
    record->dstFactor = transfer->dstFactor;





    return DeserializeResult::Success;
}
DAWN_UNUSED_FUNC(WGPUBlendDescriptorDeserialize);

        
struct WGPUBufferDescriptorTransfer {
    static_assert(1 <= 1,
                  "Record must be at most one of is_cmd, extensible, and chained.");
    bool hasNextInChain;

    WGPUBufferUsageFlags usage;
    uint64_t size;
    bool mappedAtCreation;

    size_t labelStrlen;

    bool has_label;
};



DAWN_DECLARE_UNUSED size_t WGPUBufferDescriptorGetExtraRequiredSize(const WGPUBufferDescriptor& record) {
    DAWN_UNUSED(record);

    size_t result = 0;

    if (record.nextInChain != nullptr) {
        result += GetChainedStructExtraRequiredSize(record.nextInChain);
    }


    bool has_label = record.label != nullptr;
    if (has_label)
    {
    result += std::strlen(record.label);
    }

    {
    }
    {
    }
    {
    }

    return result;
}
// GetExtraRequiredSize isn't used for structures that are value members of other structures
// because we assume they cannot contain pointers themselves.
DAWN_UNUSED_FUNC(WGPUBufferDescriptorGetExtraRequiredSize);

DAWN_DECLARE_UNUSED void WGPUBufferDescriptorSerialize(const WGPUBufferDescriptor& record, WGPUBufferDescriptorTransfer* transfer,
                       char** buffer, const ObjectIdProvider& provider) {
    DAWN_UNUSED(buffer);


    transfer->usage = record.usage;
    transfer->size = record.size;
    transfer->mappedAtCreation = record.mappedAtCreation;

    if (record.nextInChain != nullptr) {
        transfer->hasNextInChain = true;
        SerializeChainedStruct(record.nextInChain, buffer, provider);
    } else {
        transfer->hasNextInChain = false;
    }



    bool has_label = record.label != nullptr;
    transfer->has_label = has_label;
    if (has_label)
    {
    transfer->labelStrlen = std::strlen(record.label);

    memcpy(*buffer, record.label, transfer->labelStrlen);
    *buffer += transfer->labelStrlen;
    }

}
DAWN_UNUSED_FUNC(WGPUBufferDescriptorSerialize);

DAWN_DECLARE_UNUSED DeserializeResult WGPUBufferDescriptorDeserialize(WGPUBufferDescriptor* record, const volatile WGPUBufferDescriptorTransfer* transfer,
                                      const volatile char** buffer, size_t* size, DeserializeAllocator* allocator, const ObjectIdResolver& resolver) {
    DAWN_UNUSED(allocator);
    DAWN_UNUSED(buffer);
    DAWN_UNUSED(size);



    record->usage = transfer->usage;
    record->size = transfer->size;
    record->mappedAtCreation = transfer->mappedAtCreation;

    record->nextInChain = nullptr;
    if (transfer->hasNextInChain) {
        DESERIALIZE_TRY(DeserializeChainedStruct(&record->nextInChain, buffer, size, allocator, resolver));
    }



    bool has_label = transfer->has_label;
    record->label = nullptr;
    if (has_label)
    {
        size_t stringLength = transfer->labelStrlen;
        const volatile char* stringInBuffer = nullptr;
        DESERIALIZE_TRY(GetPtrFromBuffer(buffer, size, stringLength, &stringInBuffer));

        char* copiedString = nullptr;
        DESERIALIZE_TRY(GetSpace(allocator, stringLength + 1, &copiedString));
        std::copy(stringInBuffer, stringInBuffer + stringLength, copiedString);
        copiedString[stringLength] = '\0';
        record->label = copiedString;
    }


    return DeserializeResult::Success;
}
DAWN_UNUSED_FUNC(WGPUBufferDescriptorDeserialize);

        
struct WGPUColorTransfer {
    static_assert(0 <= 1,
                  "Record must be at most one of is_cmd, extensible, and chained.");

    double r;
    double g;
    double b;
    double a;


};



DAWN_DECLARE_UNUSED size_t WGPUColorGetExtraRequiredSize(const WGPUColor& record) {
    DAWN_UNUSED(record);

    size_t result = 0;



    {
    }
    {
    }
    {
    }
    {
    }

    return result;
}
// GetExtraRequiredSize isn't used for structures that are value members of other structures
// because we assume they cannot contain pointers themselves.
DAWN_UNUSED_FUNC(WGPUColorGetExtraRequiredSize);

DAWN_DECLARE_UNUSED void WGPUColorSerialize(const WGPUColor& record, WGPUColorTransfer* transfer,
                       char** buffer) {
    DAWN_UNUSED(buffer);


    transfer->r = record.r;
    transfer->g = record.g;
    transfer->b = record.b;
    transfer->a = record.a;




}
DAWN_UNUSED_FUNC(WGPUColorSerialize);

DAWN_DECLARE_UNUSED DeserializeResult WGPUColorDeserialize(WGPUColor* record, const volatile WGPUColorTransfer* transfer,
                                      const volatile char** buffer, size_t* size, DeserializeAllocator* allocator) {
    DAWN_UNUSED(allocator);
    DAWN_UNUSED(buffer);
    DAWN_UNUSED(size);



    record->r = transfer->r;
    record->g = transfer->g;
    record->b = transfer->b;
    record->a = transfer->a;





    return DeserializeResult::Success;
}
DAWN_UNUSED_FUNC(WGPUColorDeserialize);

        
struct WGPUCommandBufferDescriptorTransfer {
    static_assert(1 <= 1,
                  "Record must be at most one of is_cmd, extensible, and chained.");
    bool hasNextInChain;


    size_t labelStrlen;

    bool has_label;
};



DAWN_DECLARE_UNUSED size_t WGPUCommandBufferDescriptorGetExtraRequiredSize(const WGPUCommandBufferDescriptor& record) {
    DAWN_UNUSED(record);

    size_t result = 0;

    if (record.nextInChain != nullptr) {
        result += GetChainedStructExtraRequiredSize(record.nextInChain);
    }


    bool has_label = record.label != nullptr;
    if (has_label)
    {
    result += std::strlen(record.label);
    }


    return result;
}
// GetExtraRequiredSize isn't used for structures that are value members of other structures
// because we assume they cannot contain pointers themselves.
DAWN_UNUSED_FUNC(WGPUCommandBufferDescriptorGetExtraRequiredSize);

DAWN_DECLARE_UNUSED void WGPUCommandBufferDescriptorSerialize(const WGPUCommandBufferDescriptor& record, WGPUCommandBufferDescriptorTransfer* transfer,
                       char** buffer, const ObjectIdProvider& provider) {
    DAWN_UNUSED(buffer);



    if (record.nextInChain != nullptr) {
        transfer->hasNextInChain = true;
        SerializeChainedStruct(record.nextInChain, buffer, provider);
    } else {
        transfer->hasNextInChain = false;
    }



    bool has_label = record.label != nullptr;
    transfer->has_label = has_label;
    if (has_label)
    {
    transfer->labelStrlen = std::strlen(record.label);

    memcpy(*buffer, record.label, transfer->labelStrlen);
    *buffer += transfer->labelStrlen;
    }

}
DAWN_UNUSED_FUNC(WGPUCommandBufferDescriptorSerialize);

DAWN_DECLARE_UNUSED DeserializeResult WGPUCommandBufferDescriptorDeserialize(WGPUCommandBufferDescriptor* record, const volatile WGPUCommandBufferDescriptorTransfer* transfer,
                                      const volatile char** buffer, size_t* size, DeserializeAllocator* allocator, const ObjectIdResolver& resolver) {
    DAWN_UNUSED(allocator);
    DAWN_UNUSED(buffer);
    DAWN_UNUSED(size);




    record->nextInChain = nullptr;
    if (transfer->hasNextInChain) {
        DESERIALIZE_TRY(DeserializeChainedStruct(&record->nextInChain, buffer, size, allocator, resolver));
    }



    bool has_label = transfer->has_label;
    record->label = nullptr;
    if (has_label)
    {
        size_t stringLength = transfer->labelStrlen;
        const volatile char* stringInBuffer = nullptr;
        DESERIALIZE_TRY(GetPtrFromBuffer(buffer, size, stringLength, &stringInBuffer));

        char* copiedString = nullptr;
        DESERIALIZE_TRY(GetSpace(allocator, stringLength + 1, &copiedString));
        std::copy(stringInBuffer, stringInBuffer + stringLength, copiedString);
        copiedString[stringLength] = '\0';
        record->label = copiedString;
    }


    return DeserializeResult::Success;
}
DAWN_UNUSED_FUNC(WGPUCommandBufferDescriptorDeserialize);

        
struct WGPUCommandEncoderDescriptorTransfer {
    static_assert(1 <= 1,
                  "Record must be at most one of is_cmd, extensible, and chained.");
    bool hasNextInChain;


    size_t labelStrlen;

    bool has_label;
};



DAWN_DECLARE_UNUSED size_t WGPUCommandEncoderDescriptorGetExtraRequiredSize(const WGPUCommandEncoderDescriptor& record) {
    DAWN_UNUSED(record);

    size_t result = 0;

    if (record.nextInChain != nullptr) {
        result += GetChainedStructExtraRequiredSize(record.nextInChain);
    }


    bool has_label = record.label != nullptr;
    if (has_label)
    {
    result += std::strlen(record.label);
    }


    return result;
}
// GetExtraRequiredSize isn't used for structures that are value members of other structures
// because we assume they cannot contain pointers themselves.
DAWN_UNUSED_FUNC(WGPUCommandEncoderDescriptorGetExtraRequiredSize);

DAWN_DECLARE_UNUSED void WGPUCommandEncoderDescriptorSerialize(const WGPUCommandEncoderDescriptor& record, WGPUCommandEncoderDescriptorTransfer* transfer,
                       char** buffer, const ObjectIdProvider& provider) {
    DAWN_UNUSED(buffer);



    if (record.nextInChain != nullptr) {
        transfer->hasNextInChain = true;
        SerializeChainedStruct(record.nextInChain, buffer, provider);
    } else {
        transfer->hasNextInChain = false;
    }



    bool has_label = record.label != nullptr;
    transfer->has_label = has_label;
    if (has_label)
    {
    transfer->labelStrlen = std::strlen(record.label);

    memcpy(*buffer, record.label, transfer->labelStrlen);
    *buffer += transfer->labelStrlen;
    }

}
DAWN_UNUSED_FUNC(WGPUCommandEncoderDescriptorSerialize);

DAWN_DECLARE_UNUSED DeserializeResult WGPUCommandEncoderDescriptorDeserialize(WGPUCommandEncoderDescriptor* record, const volatile WGPUCommandEncoderDescriptorTransfer* transfer,
                                      const volatile char** buffer, size_t* size, DeserializeAllocator* allocator, const ObjectIdResolver& resolver) {
    DAWN_UNUSED(allocator);
    DAWN_UNUSED(buffer);
    DAWN_UNUSED(size);




    record->nextInChain = nullptr;
    if (transfer->hasNextInChain) {
        DESERIALIZE_TRY(DeserializeChainedStruct(&record->nextInChain, buffer, size, allocator, resolver));
    }



    bool has_label = transfer->has_label;
    record->label = nullptr;
    if (has_label)
    {
        size_t stringLength = transfer->labelStrlen;
        const volatile char* stringInBuffer = nullptr;
        DESERIALIZE_TRY(GetPtrFromBuffer(buffer, size, stringLength, &stringInBuffer));

        char* copiedString = nullptr;
        DESERIALIZE_TRY(GetSpace(allocator, stringLength + 1, &copiedString));
        std::copy(stringInBuffer, stringInBuffer + stringLength, copiedString);
        copiedString[stringLength] = '\0';
        record->label = copiedString;
    }


    return DeserializeResult::Success;
}
DAWN_UNUSED_FUNC(WGPUCommandEncoderDescriptorDeserialize);

        
struct WGPUComputePassDescriptorTransfer {
    static_assert(1 <= 1,
                  "Record must be at most one of is_cmd, extensible, and chained.");
    bool hasNextInChain;


    size_t labelStrlen;

    bool has_label;
};



DAWN_DECLARE_UNUSED size_t WGPUComputePassDescriptorGetExtraRequiredSize(const WGPUComputePassDescriptor& record) {
    DAWN_UNUSED(record);

    size_t result = 0;

    if (record.nextInChain != nullptr) {
        result += GetChainedStructExtraRequiredSize(record.nextInChain);
    }


    bool has_label = record.label != nullptr;
    if (has_label)
    {
    result += std::strlen(record.label);
    }


    return result;
}
// GetExtraRequiredSize isn't used for structures that are value members of other structures
// because we assume they cannot contain pointers themselves.
DAWN_UNUSED_FUNC(WGPUComputePassDescriptorGetExtraRequiredSize);

DAWN_DECLARE_UNUSED void WGPUComputePassDescriptorSerialize(const WGPUComputePassDescriptor& record, WGPUComputePassDescriptorTransfer* transfer,
                       char** buffer, const ObjectIdProvider& provider) {
    DAWN_UNUSED(buffer);



    if (record.nextInChain != nullptr) {
        transfer->hasNextInChain = true;
        SerializeChainedStruct(record.nextInChain, buffer, provider);
    } else {
        transfer->hasNextInChain = false;
    }



    bool has_label = record.label != nullptr;
    transfer->has_label = has_label;
    if (has_label)
    {
    transfer->labelStrlen = std::strlen(record.label);

    memcpy(*buffer, record.label, transfer->labelStrlen);
    *buffer += transfer->labelStrlen;
    }

}
DAWN_UNUSED_FUNC(WGPUComputePassDescriptorSerialize);

DAWN_DECLARE_UNUSED DeserializeResult WGPUComputePassDescriptorDeserialize(WGPUComputePassDescriptor* record, const volatile WGPUComputePassDescriptorTransfer* transfer,
                                      const volatile char** buffer, size_t* size, DeserializeAllocator* allocator, const ObjectIdResolver& resolver) {
    DAWN_UNUSED(allocator);
    DAWN_UNUSED(buffer);
    DAWN_UNUSED(size);




    record->nextInChain = nullptr;
    if (transfer->hasNextInChain) {
        DESERIALIZE_TRY(DeserializeChainedStruct(&record->nextInChain, buffer, size, allocator, resolver));
    }



    bool has_label = transfer->has_label;
    record->label = nullptr;
    if (has_label)
    {
        size_t stringLength = transfer->labelStrlen;
        const volatile char* stringInBuffer = nullptr;
        DESERIALIZE_TRY(GetPtrFromBuffer(buffer, size, stringLength, &stringInBuffer));

        char* copiedString = nullptr;
        DESERIALIZE_TRY(GetSpace(allocator, stringLength + 1, &copiedString));
        std::copy(stringInBuffer, stringInBuffer + stringLength, copiedString);
        copiedString[stringLength] = '\0';
        record->label = copiedString;
    }


    return DeserializeResult::Success;
}
DAWN_UNUSED_FUNC(WGPUComputePassDescriptorDeserialize);

        
struct WGPUDevicePropertiesTransfer {
    static_assert(0 <= 1,
                  "Record must be at most one of is_cmd, extensible, and chained.");

    bool textureCompressionBC;
    bool shaderFloat16;
    bool pipelineStatisticsQuery;
    bool timestampQuery;


};



DAWN_DECLARE_UNUSED size_t WGPUDevicePropertiesGetExtraRequiredSize(const WGPUDeviceProperties& record) {
    DAWN_UNUSED(record);

    size_t result = 0;



    {
    }
    {
    }
    {
    }
    {
    }

    return result;
}
// GetExtraRequiredSize isn't used for structures that are value members of other structures
// because we assume they cannot contain pointers themselves.
DAWN_UNUSED_FUNC(WGPUDevicePropertiesGetExtraRequiredSize);

DAWN_DECLARE_UNUSED void WGPUDevicePropertiesSerialize(const WGPUDeviceProperties& record, WGPUDevicePropertiesTransfer* transfer,
                       char** buffer) {
    DAWN_UNUSED(buffer);


    transfer->textureCompressionBC = record.textureCompressionBC;
    transfer->shaderFloat16 = record.shaderFloat16;
    transfer->pipelineStatisticsQuery = record.pipelineStatisticsQuery;
    transfer->timestampQuery = record.timestampQuery;




}
DAWN_UNUSED_FUNC(WGPUDevicePropertiesSerialize);

DAWN_DECLARE_UNUSED DeserializeResult WGPUDevicePropertiesDeserialize(WGPUDeviceProperties* record, const volatile WGPUDevicePropertiesTransfer* transfer,
                                      const volatile char** buffer, size_t* size, DeserializeAllocator* allocator) {
    DAWN_UNUSED(allocator);
    DAWN_UNUSED(buffer);
    DAWN_UNUSED(size);



    record->textureCompressionBC = transfer->textureCompressionBC;
    record->shaderFloat16 = transfer->shaderFloat16;
    record->pipelineStatisticsQuery = transfer->pipelineStatisticsQuery;
    record->timestampQuery = transfer->timestampQuery;





    return DeserializeResult::Success;
}
DAWN_UNUSED_FUNC(WGPUDevicePropertiesDeserialize);

        
struct WGPUExtent3DTransfer {
    static_assert(0 <= 1,
                  "Record must be at most one of is_cmd, extensible, and chained.");

    uint32_t width;
    uint32_t height;
    uint32_t depth;


};



DAWN_DECLARE_UNUSED size_t WGPUExtent3DGetExtraRequiredSize(const WGPUExtent3D& record) {
    DAWN_UNUSED(record);

    size_t result = 0;



    {
    }
    {
    }
    {
    }

    return result;
}
// GetExtraRequiredSize isn't used for structures that are value members of other structures
// because we assume they cannot contain pointers themselves.
DAWN_UNUSED_FUNC(WGPUExtent3DGetExtraRequiredSize);

DAWN_DECLARE_UNUSED void WGPUExtent3DSerialize(const WGPUExtent3D& record, WGPUExtent3DTransfer* transfer,
                       char** buffer) {
    DAWN_UNUSED(buffer);


    transfer->width = record.width;
    transfer->height = record.height;
    transfer->depth = record.depth;




}
DAWN_UNUSED_FUNC(WGPUExtent3DSerialize);

DAWN_DECLARE_UNUSED DeserializeResult WGPUExtent3DDeserialize(WGPUExtent3D* record, const volatile WGPUExtent3DTransfer* transfer,
                                      const volatile char** buffer, size_t* size, DeserializeAllocator* allocator) {
    DAWN_UNUSED(allocator);
    DAWN_UNUSED(buffer);
    DAWN_UNUSED(size);



    record->width = transfer->width;
    record->height = transfer->height;
    record->depth = transfer->depth;





    return DeserializeResult::Success;
}
DAWN_UNUSED_FUNC(WGPUExtent3DDeserialize);

        
struct WGPUFenceDescriptorTransfer {
    static_assert(1 <= 1,
                  "Record must be at most one of is_cmd, extensible, and chained.");
    bool hasNextInChain;

    uint64_t initialValue;

    size_t labelStrlen;

    bool has_label;
};



DAWN_DECLARE_UNUSED size_t WGPUFenceDescriptorGetExtraRequiredSize(const WGPUFenceDescriptor& record) {
    DAWN_UNUSED(record);

    size_t result = 0;

    if (record.nextInChain != nullptr) {
        result += GetChainedStructExtraRequiredSize(record.nextInChain);
    }


    bool has_label = record.label != nullptr;
    if (has_label)
    {
    result += std::strlen(record.label);
    }

    {
    }

    return result;
}
// GetExtraRequiredSize isn't used for structures that are value members of other structures
// because we assume they cannot contain pointers themselves.
DAWN_UNUSED_FUNC(WGPUFenceDescriptorGetExtraRequiredSize);

DAWN_DECLARE_UNUSED void WGPUFenceDescriptorSerialize(const WGPUFenceDescriptor& record, WGPUFenceDescriptorTransfer* transfer,
                       char** buffer, const ObjectIdProvider& provider) {
    DAWN_UNUSED(buffer);


    transfer->initialValue = record.initialValue;

    if (record.nextInChain != nullptr) {
        transfer->hasNextInChain = true;
        SerializeChainedStruct(record.nextInChain, buffer, provider);
    } else {
        transfer->hasNextInChain = false;
    }



    bool has_label = record.label != nullptr;
    transfer->has_label = has_label;
    if (has_label)
    {
    transfer->labelStrlen = std::strlen(record.label);

    memcpy(*buffer, record.label, transfer->labelStrlen);
    *buffer += transfer->labelStrlen;
    }

}
DAWN_UNUSED_FUNC(WGPUFenceDescriptorSerialize);

DAWN_DECLARE_UNUSED DeserializeResult WGPUFenceDescriptorDeserialize(WGPUFenceDescriptor* record, const volatile WGPUFenceDescriptorTransfer* transfer,
                                      const volatile char** buffer, size_t* size, DeserializeAllocator* allocator, const ObjectIdResolver& resolver) {
    DAWN_UNUSED(allocator);
    DAWN_UNUSED(buffer);
    DAWN_UNUSED(size);



    record->initialValue = transfer->initialValue;

    record->nextInChain = nullptr;
    if (transfer->hasNextInChain) {
        DESERIALIZE_TRY(DeserializeChainedStruct(&record->nextInChain, buffer, size, allocator, resolver));
    }



    bool has_label = transfer->has_label;
    record->label = nullptr;
    if (has_label)
    {
        size_t stringLength = transfer->labelStrlen;
        const volatile char* stringInBuffer = nullptr;
        DESERIALIZE_TRY(GetPtrFromBuffer(buffer, size, stringLength, &stringInBuffer));

        char* copiedString = nullptr;
        DESERIALIZE_TRY(GetSpace(allocator, stringLength + 1, &copiedString));
        std::copy(stringInBuffer, stringInBuffer + stringLength, copiedString);
        copiedString[stringLength] = '\0';
        record->label = copiedString;
    }


    return DeserializeResult::Success;
}
DAWN_UNUSED_FUNC(WGPUFenceDescriptorDeserialize);

        
struct WGPUInstanceDescriptorTransfer {
    static_assert(1 <= 1,
                  "Record must be at most one of is_cmd, extensible, and chained.");
    bool hasNextInChain;



};



DAWN_DECLARE_UNUSED size_t WGPUInstanceDescriptorGetExtraRequiredSize(const WGPUInstanceDescriptor& record) {
    DAWN_UNUSED(record);

    size_t result = 0;

    if (record.nextInChain != nullptr) {
        result += GetChainedStructExtraRequiredSize(record.nextInChain);
    }



    return result;
}
// GetExtraRequiredSize isn't used for structures that are value members of other structures
// because we assume they cannot contain pointers themselves.
DAWN_UNUSED_FUNC(WGPUInstanceDescriptorGetExtraRequiredSize);

DAWN_DECLARE_UNUSED void WGPUInstanceDescriptorSerialize(const WGPUInstanceDescriptor& record, WGPUInstanceDescriptorTransfer* transfer,
                       char** buffer, const ObjectIdProvider& provider) {
    DAWN_UNUSED(buffer);



    if (record.nextInChain != nullptr) {
        transfer->hasNextInChain = true;
        SerializeChainedStruct(record.nextInChain, buffer, provider);
    } else {
        transfer->hasNextInChain = false;
    }



}
DAWN_UNUSED_FUNC(WGPUInstanceDescriptorSerialize);

DAWN_DECLARE_UNUSED DeserializeResult WGPUInstanceDescriptorDeserialize(WGPUInstanceDescriptor* record, const volatile WGPUInstanceDescriptorTransfer* transfer,
                                      const volatile char** buffer, size_t* size, DeserializeAllocator* allocator, const ObjectIdResolver& resolver) {
    DAWN_UNUSED(allocator);
    DAWN_UNUSED(buffer);
    DAWN_UNUSED(size);




    record->nextInChain = nullptr;
    if (transfer->hasNextInChain) {
        DESERIALIZE_TRY(DeserializeChainedStruct(&record->nextInChain, buffer, size, allocator, resolver));
    }




    return DeserializeResult::Success;
}
DAWN_UNUSED_FUNC(WGPUInstanceDescriptorDeserialize);

        
struct WGPUOrigin3DTransfer {
    static_assert(0 <= 1,
                  "Record must be at most one of is_cmd, extensible, and chained.");

    uint32_t x;
    uint32_t y;
    uint32_t z;


};



DAWN_DECLARE_UNUSED size_t WGPUOrigin3DGetExtraRequiredSize(const WGPUOrigin3D& record) {
    DAWN_UNUSED(record);

    size_t result = 0;



    {
    }
    {
    }
    {
    }

    return result;
}
// GetExtraRequiredSize isn't used for structures that are value members of other structures
// because we assume they cannot contain pointers themselves.
DAWN_UNUSED_FUNC(WGPUOrigin3DGetExtraRequiredSize);

DAWN_DECLARE_UNUSED void WGPUOrigin3DSerialize(const WGPUOrigin3D& record, WGPUOrigin3DTransfer* transfer,
                       char** buffer) {
    DAWN_UNUSED(buffer);


    transfer->x = record.x;
    transfer->y = record.y;
    transfer->z = record.z;




}
DAWN_UNUSED_FUNC(WGPUOrigin3DSerialize);

DAWN_DECLARE_UNUSED DeserializeResult WGPUOrigin3DDeserialize(WGPUOrigin3D* record, const volatile WGPUOrigin3DTransfer* transfer,
                                      const volatile char** buffer, size_t* size, DeserializeAllocator* allocator) {
    DAWN_UNUSED(allocator);
    DAWN_UNUSED(buffer);
    DAWN_UNUSED(size);



    record->x = transfer->x;
    record->y = transfer->y;
    record->z = transfer->z;





    return DeserializeResult::Success;
}
DAWN_UNUSED_FUNC(WGPUOrigin3DDeserialize);

        
struct WGPUPipelineLayoutDescriptorTransfer {
    static_assert(1 <= 1,
                  "Record must be at most one of is_cmd, extensible, and chained.");
    bool hasNextInChain;

    uint32_t bindGroupLayoutCount;

    size_t labelStrlen;

    bool has_label;
};



DAWN_DECLARE_UNUSED size_t WGPUPipelineLayoutDescriptorGetExtraRequiredSize(const WGPUPipelineLayoutDescriptor& record) {
    DAWN_UNUSED(record);

    size_t result = 0;

    if (record.nextInChain != nullptr) {
        result += GetChainedStructExtraRequiredSize(record.nextInChain);
    }


    bool has_label = record.label != nullptr;
    if (has_label)
    {
    result += std::strlen(record.label);
    }

    {
    }
    {
        size_t memberLength = record.bindGroupLayoutCount;
        result += memberLength * sizeof(ObjectId);
    }

    return result;
}
// GetExtraRequiredSize isn't used for structures that are value members of other structures
// because we assume they cannot contain pointers themselves.
DAWN_UNUSED_FUNC(WGPUPipelineLayoutDescriptorGetExtraRequiredSize);

DAWN_DECLARE_UNUSED void WGPUPipelineLayoutDescriptorSerialize(const WGPUPipelineLayoutDescriptor& record, WGPUPipelineLayoutDescriptorTransfer* transfer,
                       char** buffer, const ObjectIdProvider& provider) {
    DAWN_UNUSED(buffer);


    transfer->bindGroupLayoutCount = record.bindGroupLayoutCount;

    if (record.nextInChain != nullptr) {
        transfer->hasNextInChain = true;
        SerializeChainedStruct(record.nextInChain, buffer, provider);
    } else {
        transfer->hasNextInChain = false;
    }



    bool has_label = record.label != nullptr;
    transfer->has_label = has_label;
    if (has_label)
    {
    transfer->labelStrlen = std::strlen(record.label);

    memcpy(*buffer, record.label, transfer->labelStrlen);
    *buffer += transfer->labelStrlen;
    }


    {
        size_t memberLength = record.bindGroupLayoutCount;
        auto memberBuffer = reinterpret_cast<ObjectId*>(*buffer);
        *buffer += memberLength * sizeof(ObjectId);

        for (size_t i = 0; i < memberLength; ++i) {
            memberBuffer[i] = provider.GetId(record.bindGroupLayouts[i]);

        }
    }
}
DAWN_UNUSED_FUNC(WGPUPipelineLayoutDescriptorSerialize);

DAWN_DECLARE_UNUSED DeserializeResult WGPUPipelineLayoutDescriptorDeserialize(WGPUPipelineLayoutDescriptor* record, const volatile WGPUPipelineLayoutDescriptorTransfer* transfer,
                                      const volatile char** buffer, size_t* size, DeserializeAllocator* allocator, const ObjectIdResolver& resolver) {
    DAWN_UNUSED(allocator);
    DAWN_UNUSED(buffer);
    DAWN_UNUSED(size);



    record->bindGroupLayoutCount = transfer->bindGroupLayoutCount;

    record->nextInChain = nullptr;
    if (transfer->hasNextInChain) {
        DESERIALIZE_TRY(DeserializeChainedStruct(&record->nextInChain, buffer, size, allocator, resolver));
    }



    bool has_label = transfer->has_label;
    record->label = nullptr;
    if (has_label)
    {
        size_t stringLength = transfer->labelStrlen;
        const volatile char* stringInBuffer = nullptr;
        DESERIALIZE_TRY(GetPtrFromBuffer(buffer, size, stringLength, &stringInBuffer));

        char* copiedString = nullptr;
        DESERIALIZE_TRY(GetSpace(allocator, stringLength + 1, &copiedString));
        std::copy(stringInBuffer, stringInBuffer + stringLength, copiedString);
        copiedString[stringLength] = '\0';
        record->label = copiedString;
    }


    {
        size_t memberLength = record->bindGroupLayoutCount;
        auto memberBuffer = reinterpret_cast<const volatile ObjectId*>(buffer);
        DESERIALIZE_TRY(GetPtrFromBuffer(buffer, size, memberLength, &memberBuffer));

        WGPUBindGroupLayout* copiedMembers = nullptr;
        DESERIALIZE_TRY(GetSpace(allocator, memberLength, &copiedMembers));
        record->bindGroupLayouts = copiedMembers;

        for (size_t i = 0; i < memberLength; ++i) {
            DESERIALIZE_TRY(resolver.GetFromId(memberBuffer[i], &copiedMembers[i]));
        }
    }

    return DeserializeResult::Success;
}
DAWN_UNUSED_FUNC(WGPUPipelineLayoutDescriptorDeserialize);

        
struct WGPUProgrammableStageDescriptorTransfer {
    static_assert(1 <= 1,
                  "Record must be at most one of is_cmd, extensible, and chained.");
    bool hasNextInChain;

    ObjectId module;

    size_t entryPointStrlen;

};



DAWN_DECLARE_UNUSED size_t WGPUProgrammableStageDescriptorGetExtraRequiredSize(const WGPUProgrammableStageDescriptor& record) {
    DAWN_UNUSED(record);

    size_t result = 0;

    if (record.nextInChain != nullptr) {
        result += GetChainedStructExtraRequiredSize(record.nextInChain);
    }


    {
    result += std::strlen(record.entryPoint);
    }

    {
    }

    return result;
}
// GetExtraRequiredSize isn't used for structures that are value members of other structures
// because we assume they cannot contain pointers themselves.
DAWN_UNUSED_FUNC(WGPUProgrammableStageDescriptorGetExtraRequiredSize);

DAWN_DECLARE_UNUSED void WGPUProgrammableStageDescriptorSerialize(const WGPUProgrammableStageDescriptor& record, WGPUProgrammableStageDescriptorTransfer* transfer,
                       char** buffer, const ObjectIdProvider& provider) {
    DAWN_UNUSED(buffer);


    transfer->module = provider.GetId(record.module);


    if (record.nextInChain != nullptr) {
        transfer->hasNextInChain = true;
        SerializeChainedStruct(record.nextInChain, buffer, provider);
    } else {
        transfer->hasNextInChain = false;
    }



    {
    transfer->entryPointStrlen = std::strlen(record.entryPoint);

    memcpy(*buffer, record.entryPoint, transfer->entryPointStrlen);
    *buffer += transfer->entryPointStrlen;
    }

}
DAWN_UNUSED_FUNC(WGPUProgrammableStageDescriptorSerialize);

DAWN_DECLARE_UNUSED DeserializeResult WGPUProgrammableStageDescriptorDeserialize(WGPUProgrammableStageDescriptor* record, const volatile WGPUProgrammableStageDescriptorTransfer* transfer,
                                      const volatile char** buffer, size_t* size, DeserializeAllocator* allocator, const ObjectIdResolver& resolver) {
    DAWN_UNUSED(allocator);
    DAWN_UNUSED(buffer);
    DAWN_UNUSED(size);



    DESERIALIZE_TRY(resolver.GetFromId(transfer->module, &record->module));

    record->nextInChain = nullptr;
    if (transfer->hasNextInChain) {
        DESERIALIZE_TRY(DeserializeChainedStruct(&record->nextInChain, buffer, size, allocator, resolver));
    }



    {
        size_t stringLength = transfer->entryPointStrlen;
        const volatile char* stringInBuffer = nullptr;
        DESERIALIZE_TRY(GetPtrFromBuffer(buffer, size, stringLength, &stringInBuffer));

        char* copiedString = nullptr;
        DESERIALIZE_TRY(GetSpace(allocator, stringLength + 1, &copiedString));
        std::copy(stringInBuffer, stringInBuffer + stringLength, copiedString);
        copiedString[stringLength] = '\0';
        record->entryPoint = copiedString;
    }


    return DeserializeResult::Success;
}
DAWN_UNUSED_FUNC(WGPUProgrammableStageDescriptorDeserialize);

        
struct WGPUQuerySetDescriptorTransfer {
    static_assert(1 <= 1,
                  "Record must be at most one of is_cmd, extensible, and chained.");
    bool hasNextInChain;

    WGPUQueryType type;
    uint32_t count;
    uint32_t pipelineStatisticsCount;

    size_t labelStrlen;

    bool has_label;
};



DAWN_DECLARE_UNUSED size_t WGPUQuerySetDescriptorGetExtraRequiredSize(const WGPUQuerySetDescriptor& record) {
    DAWN_UNUSED(record);

    size_t result = 0;

    if (record.nextInChain != nullptr) {
        result += GetChainedStructExtraRequiredSize(record.nextInChain);
    }


    bool has_label = record.label != nullptr;
    if (has_label)
    {
    result += std::strlen(record.label);
    }

    {
    }
    {
    }
    {
        size_t memberLength = record.pipelineStatisticsCount;
        result += memberLength * sizeof(WGPUPipelineStatisticName);
    }
    {
    }

    return result;
}
// GetExtraRequiredSize isn't used for structures that are value members of other structures
// because we assume they cannot contain pointers themselves.
DAWN_UNUSED_FUNC(WGPUQuerySetDescriptorGetExtraRequiredSize);

DAWN_DECLARE_UNUSED void WGPUQuerySetDescriptorSerialize(const WGPUQuerySetDescriptor& record, WGPUQuerySetDescriptorTransfer* transfer,
                       char** buffer, const ObjectIdProvider& provider) {
    DAWN_UNUSED(buffer);


    transfer->type = record.type;
    transfer->count = record.count;
    transfer->pipelineStatisticsCount = record.pipelineStatisticsCount;

    if (record.nextInChain != nullptr) {
        transfer->hasNextInChain = true;
        SerializeChainedStruct(record.nextInChain, buffer, provider);
    } else {
        transfer->hasNextInChain = false;
    }



    bool has_label = record.label != nullptr;
    transfer->has_label = has_label;
    if (has_label)
    {
    transfer->labelStrlen = std::strlen(record.label);

    memcpy(*buffer, record.label, transfer->labelStrlen);
    *buffer += transfer->labelStrlen;
    }


    {
        size_t memberLength = record.pipelineStatisticsCount;
        auto memberBuffer = reinterpret_cast<WGPUPipelineStatisticName*>(*buffer);
        *buffer += memberLength * sizeof(WGPUPipelineStatisticName);

        for (size_t i = 0; i < memberLength; ++i) {
            memberBuffer[i] = record.pipelineStatistics[i];
        }
    }
}
DAWN_UNUSED_FUNC(WGPUQuerySetDescriptorSerialize);

DAWN_DECLARE_UNUSED DeserializeResult WGPUQuerySetDescriptorDeserialize(WGPUQuerySetDescriptor* record, const volatile WGPUQuerySetDescriptorTransfer* transfer,
                                      const volatile char** buffer, size_t* size, DeserializeAllocator* allocator, const ObjectIdResolver& resolver) {
    DAWN_UNUSED(allocator);
    DAWN_UNUSED(buffer);
    DAWN_UNUSED(size);



    record->type = transfer->type;
    record->count = transfer->count;
    record->pipelineStatisticsCount = transfer->pipelineStatisticsCount;

    record->nextInChain = nullptr;
    if (transfer->hasNextInChain) {
        DESERIALIZE_TRY(DeserializeChainedStruct(&record->nextInChain, buffer, size, allocator, resolver));
    }



    bool has_label = transfer->has_label;
    record->label = nullptr;
    if (has_label)
    {
        size_t stringLength = transfer->labelStrlen;
        const volatile char* stringInBuffer = nullptr;
        DESERIALIZE_TRY(GetPtrFromBuffer(buffer, size, stringLength, &stringInBuffer));

        char* copiedString = nullptr;
        DESERIALIZE_TRY(GetSpace(allocator, stringLength + 1, &copiedString));
        std::copy(stringInBuffer, stringInBuffer + stringLength, copiedString);
        copiedString[stringLength] = '\0';
        record->label = copiedString;
    }


    {
        size_t memberLength = record->pipelineStatisticsCount;
        auto memberBuffer = reinterpret_cast<const volatile WGPUPipelineStatisticName*>(buffer);
        DESERIALIZE_TRY(GetPtrFromBuffer(buffer, size, memberLength, &memberBuffer));

        WGPUPipelineStatisticName* copiedMembers = nullptr;
        DESERIALIZE_TRY(GetSpace(allocator, memberLength, &copiedMembers));
        record->pipelineStatistics = copiedMembers;

        for (size_t i = 0; i < memberLength; ++i) {
            copiedMembers[i] = memberBuffer[i];
        }
    }

    return DeserializeResult::Success;
}
DAWN_UNUSED_FUNC(WGPUQuerySetDescriptorDeserialize);

        
struct WGPURasterizationStateDescriptorTransfer {
    static_assert(1 <= 1,
                  "Record must be at most one of is_cmd, extensible, and chained.");
    bool hasNextInChain;

    WGPUFrontFace frontFace;
    WGPUCullMode cullMode;
    int32_t depthBias;
    float depthBiasSlopeScale;
    float depthBiasClamp;


};



DAWN_DECLARE_UNUSED size_t WGPURasterizationStateDescriptorGetExtraRequiredSize(const WGPURasterizationStateDescriptor& record) {
    DAWN_UNUSED(record);

    size_t result = 0;

    if (record.nextInChain != nullptr) {
        result += GetChainedStructExtraRequiredSize(record.nextInChain);
    }


    {
    }
    {
    }
    {
    }
    {
    }
    {
    }

    return result;
}
// GetExtraRequiredSize isn't used for structures that are value members of other structures
// because we assume they cannot contain pointers themselves.
DAWN_UNUSED_FUNC(WGPURasterizationStateDescriptorGetExtraRequiredSize);

DAWN_DECLARE_UNUSED void WGPURasterizationStateDescriptorSerialize(const WGPURasterizationStateDescriptor& record, WGPURasterizationStateDescriptorTransfer* transfer,
                       char** buffer, const ObjectIdProvider& provider) {
    DAWN_UNUSED(buffer);


    transfer->frontFace = record.frontFace;
    transfer->cullMode = record.cullMode;
    transfer->depthBias = record.depthBias;
    transfer->depthBiasSlopeScale = record.depthBiasSlopeScale;
    transfer->depthBiasClamp = record.depthBiasClamp;

    if (record.nextInChain != nullptr) {
        transfer->hasNextInChain = true;
        SerializeChainedStruct(record.nextInChain, buffer, provider);
    } else {
        transfer->hasNextInChain = false;
    }



}
DAWN_UNUSED_FUNC(WGPURasterizationStateDescriptorSerialize);

DAWN_DECLARE_UNUSED DeserializeResult WGPURasterizationStateDescriptorDeserialize(WGPURasterizationStateDescriptor* record, const volatile WGPURasterizationStateDescriptorTransfer* transfer,
                                      const volatile char** buffer, size_t* size, DeserializeAllocator* allocator, const ObjectIdResolver& resolver) {
    DAWN_UNUSED(allocator);
    DAWN_UNUSED(buffer);
    DAWN_UNUSED(size);



    record->frontFace = transfer->frontFace;
    record->cullMode = transfer->cullMode;
    record->depthBias = transfer->depthBias;
    record->depthBiasSlopeScale = transfer->depthBiasSlopeScale;
    record->depthBiasClamp = transfer->depthBiasClamp;

    record->nextInChain = nullptr;
    if (transfer->hasNextInChain) {
        DESERIALIZE_TRY(DeserializeChainedStruct(&record->nextInChain, buffer, size, allocator, resolver));
    }




    return DeserializeResult::Success;
}
DAWN_UNUSED_FUNC(WGPURasterizationStateDescriptorDeserialize);

        
struct WGPURenderBundleDescriptorTransfer {
    static_assert(1 <= 1,
                  "Record must be at most one of is_cmd, extensible, and chained.");
    bool hasNextInChain;


    size_t labelStrlen;

    bool has_label;
};



DAWN_DECLARE_UNUSED size_t WGPURenderBundleDescriptorGetExtraRequiredSize(const WGPURenderBundleDescriptor& record) {
    DAWN_UNUSED(record);

    size_t result = 0;

    if (record.nextInChain != nullptr) {
        result += GetChainedStructExtraRequiredSize(record.nextInChain);
    }


    bool has_label = record.label != nullptr;
    if (has_label)
    {
    result += std::strlen(record.label);
    }


    return result;
}
// GetExtraRequiredSize isn't used for structures that are value members of other structures
// because we assume they cannot contain pointers themselves.
DAWN_UNUSED_FUNC(WGPURenderBundleDescriptorGetExtraRequiredSize);

DAWN_DECLARE_UNUSED void WGPURenderBundleDescriptorSerialize(const WGPURenderBundleDescriptor& record, WGPURenderBundleDescriptorTransfer* transfer,
                       char** buffer, const ObjectIdProvider& provider) {
    DAWN_UNUSED(buffer);



    if (record.nextInChain != nullptr) {
        transfer->hasNextInChain = true;
        SerializeChainedStruct(record.nextInChain, buffer, provider);
    } else {
        transfer->hasNextInChain = false;
    }



    bool has_label = record.label != nullptr;
    transfer->has_label = has_label;
    if (has_label)
    {
    transfer->labelStrlen = std::strlen(record.label);

    memcpy(*buffer, record.label, transfer->labelStrlen);
    *buffer += transfer->labelStrlen;
    }

}
DAWN_UNUSED_FUNC(WGPURenderBundleDescriptorSerialize);

DAWN_DECLARE_UNUSED DeserializeResult WGPURenderBundleDescriptorDeserialize(WGPURenderBundleDescriptor* record, const volatile WGPURenderBundleDescriptorTransfer* transfer,
                                      const volatile char** buffer, size_t* size, DeserializeAllocator* allocator, const ObjectIdResolver& resolver) {
    DAWN_UNUSED(allocator);
    DAWN_UNUSED(buffer);
    DAWN_UNUSED(size);




    record->nextInChain = nullptr;
    if (transfer->hasNextInChain) {
        DESERIALIZE_TRY(DeserializeChainedStruct(&record->nextInChain, buffer, size, allocator, resolver));
    }



    bool has_label = transfer->has_label;
    record->label = nullptr;
    if (has_label)
    {
        size_t stringLength = transfer->labelStrlen;
        const volatile char* stringInBuffer = nullptr;
        DESERIALIZE_TRY(GetPtrFromBuffer(buffer, size, stringLength, &stringInBuffer));

        char* copiedString = nullptr;
        DESERIALIZE_TRY(GetSpace(allocator, stringLength + 1, &copiedString));
        std::copy(stringInBuffer, stringInBuffer + stringLength, copiedString);
        copiedString[stringLength] = '\0';
        record->label = copiedString;
    }


    return DeserializeResult::Success;
}
DAWN_UNUSED_FUNC(WGPURenderBundleDescriptorDeserialize);

        
struct WGPURenderBundleEncoderDescriptorTransfer {
    static_assert(1 <= 1,
                  "Record must be at most one of is_cmd, extensible, and chained.");
    bool hasNextInChain;

    uint32_t colorFormatsCount;
    WGPUTextureFormat depthStencilFormat;
    uint32_t sampleCount;

    size_t labelStrlen;

    bool has_label;
};



DAWN_DECLARE_UNUSED size_t WGPURenderBundleEncoderDescriptorGetExtraRequiredSize(const WGPURenderBundleEncoderDescriptor& record) {
    DAWN_UNUSED(record);

    size_t result = 0;

    if (record.nextInChain != nullptr) {
        result += GetChainedStructExtraRequiredSize(record.nextInChain);
    }


    bool has_label = record.label != nullptr;
    if (has_label)
    {
    result += std::strlen(record.label);
    }

    {
    }
    {
        size_t memberLength = record.colorFormatsCount;
        result += memberLength * sizeof(WGPUTextureFormat);
    }
    {
    }
    {
    }

    return result;
}
// GetExtraRequiredSize isn't used for structures that are value members of other structures
// because we assume they cannot contain pointers themselves.
DAWN_UNUSED_FUNC(WGPURenderBundleEncoderDescriptorGetExtraRequiredSize);

DAWN_DECLARE_UNUSED void WGPURenderBundleEncoderDescriptorSerialize(const WGPURenderBundleEncoderDescriptor& record, WGPURenderBundleEncoderDescriptorTransfer* transfer,
                       char** buffer, const ObjectIdProvider& provider) {
    DAWN_UNUSED(buffer);


    transfer->colorFormatsCount = record.colorFormatsCount;
    transfer->depthStencilFormat = record.depthStencilFormat;
    transfer->sampleCount = record.sampleCount;

    if (record.nextInChain != nullptr) {
        transfer->hasNextInChain = true;
        SerializeChainedStruct(record.nextInChain, buffer, provider);
    } else {
        transfer->hasNextInChain = false;
    }



    bool has_label = record.label != nullptr;
    transfer->has_label = has_label;
    if (has_label)
    {
    transfer->labelStrlen = std::strlen(record.label);

    memcpy(*buffer, record.label, transfer->labelStrlen);
    *buffer += transfer->labelStrlen;
    }


    {
        size_t memberLength = record.colorFormatsCount;
        auto memberBuffer = reinterpret_cast<WGPUTextureFormat*>(*buffer);
        *buffer += memberLength * sizeof(WGPUTextureFormat);

        for (size_t i = 0; i < memberLength; ++i) {
            memberBuffer[i] = record.colorFormats[i];
        }
    }
}
DAWN_UNUSED_FUNC(WGPURenderBundleEncoderDescriptorSerialize);

DAWN_DECLARE_UNUSED DeserializeResult WGPURenderBundleEncoderDescriptorDeserialize(WGPURenderBundleEncoderDescriptor* record, const volatile WGPURenderBundleEncoderDescriptorTransfer* transfer,
                                      const volatile char** buffer, size_t* size, DeserializeAllocator* allocator, const ObjectIdResolver& resolver) {
    DAWN_UNUSED(allocator);
    DAWN_UNUSED(buffer);
    DAWN_UNUSED(size);



    record->colorFormatsCount = transfer->colorFormatsCount;
    record->depthStencilFormat = transfer->depthStencilFormat;
    record->sampleCount = transfer->sampleCount;

    record->nextInChain = nullptr;
    if (transfer->hasNextInChain) {
        DESERIALIZE_TRY(DeserializeChainedStruct(&record->nextInChain, buffer, size, allocator, resolver));
    }



    bool has_label = transfer->has_label;
    record->label = nullptr;
    if (has_label)
    {
        size_t stringLength = transfer->labelStrlen;
        const volatile char* stringInBuffer = nullptr;
        DESERIALIZE_TRY(GetPtrFromBuffer(buffer, size, stringLength, &stringInBuffer));

        char* copiedString = nullptr;
        DESERIALIZE_TRY(GetSpace(allocator, stringLength + 1, &copiedString));
        std::copy(stringInBuffer, stringInBuffer + stringLength, copiedString);
        copiedString[stringLength] = '\0';
        record->label = copiedString;
    }


    {
        size_t memberLength = record->colorFormatsCount;
        auto memberBuffer = reinterpret_cast<const volatile WGPUTextureFormat*>(buffer);
        DESERIALIZE_TRY(GetPtrFromBuffer(buffer, size, memberLength, &memberBuffer));

        WGPUTextureFormat* copiedMembers = nullptr;
        DESERIALIZE_TRY(GetSpace(allocator, memberLength, &copiedMembers));
        record->colorFormats = copiedMembers;

        for (size_t i = 0; i < memberLength; ++i) {
            copiedMembers[i] = memberBuffer[i];
        }
    }

    return DeserializeResult::Success;
}
DAWN_UNUSED_FUNC(WGPURenderBundleEncoderDescriptorDeserialize);

        
struct WGPURenderPassDepthStencilAttachmentDescriptorTransfer {
    static_assert(0 <= 1,
                  "Record must be at most one of is_cmd, extensible, and chained.");

    ObjectId attachment;
    WGPULoadOp depthLoadOp;
    WGPUStoreOp depthStoreOp;
    float clearDepth;
    bool depthReadOnly;
    WGPULoadOp stencilLoadOp;
    WGPUStoreOp stencilStoreOp;
    uint32_t clearStencil;
    bool stencilReadOnly;


};



DAWN_DECLARE_UNUSED size_t WGPURenderPassDepthStencilAttachmentDescriptorGetExtraRequiredSize(const WGPURenderPassDepthStencilAttachmentDescriptor& record) {
    DAWN_UNUSED(record);

    size_t result = 0;



    {
    }
    {
    }
    {
    }
    {
    }
    {
    }
    {
    }
    {
    }
    {
    }
    {
    }

    return result;
}
// GetExtraRequiredSize isn't used for structures that are value members of other structures
// because we assume they cannot contain pointers themselves.
DAWN_UNUSED_FUNC(WGPURenderPassDepthStencilAttachmentDescriptorGetExtraRequiredSize);

DAWN_DECLARE_UNUSED void WGPURenderPassDepthStencilAttachmentDescriptorSerialize(const WGPURenderPassDepthStencilAttachmentDescriptor& record, WGPURenderPassDepthStencilAttachmentDescriptorTransfer* transfer,
                       char** buffer, const ObjectIdProvider& provider) {
    DAWN_UNUSED(buffer);


    transfer->attachment = provider.GetId(record.attachment);

    transfer->depthLoadOp = record.depthLoadOp;
    transfer->depthStoreOp = record.depthStoreOp;
    transfer->clearDepth = record.clearDepth;
    transfer->depthReadOnly = record.depthReadOnly;
    transfer->stencilLoadOp = record.stencilLoadOp;
    transfer->stencilStoreOp = record.stencilStoreOp;
    transfer->clearStencil = record.clearStencil;
    transfer->stencilReadOnly = record.stencilReadOnly;




}
DAWN_UNUSED_FUNC(WGPURenderPassDepthStencilAttachmentDescriptorSerialize);

DAWN_DECLARE_UNUSED DeserializeResult WGPURenderPassDepthStencilAttachmentDescriptorDeserialize(WGPURenderPassDepthStencilAttachmentDescriptor* record, const volatile WGPURenderPassDepthStencilAttachmentDescriptorTransfer* transfer,
                                      const volatile char** buffer, size_t* size, DeserializeAllocator* allocator, const ObjectIdResolver& resolver) {
    DAWN_UNUSED(allocator);
    DAWN_UNUSED(buffer);
    DAWN_UNUSED(size);



    DESERIALIZE_TRY(resolver.GetFromId(transfer->attachment, &record->attachment));
    record->depthLoadOp = transfer->depthLoadOp;
    record->depthStoreOp = transfer->depthStoreOp;
    record->clearDepth = transfer->clearDepth;
    record->depthReadOnly = transfer->depthReadOnly;
    record->stencilLoadOp = transfer->stencilLoadOp;
    record->stencilStoreOp = transfer->stencilStoreOp;
    record->clearStencil = transfer->clearStencil;
    record->stencilReadOnly = transfer->stencilReadOnly;





    return DeserializeResult::Success;
}
DAWN_UNUSED_FUNC(WGPURenderPassDepthStencilAttachmentDescriptorDeserialize);

        
struct WGPUSamplerDescriptorTransfer {
    static_assert(1 <= 1,
                  "Record must be at most one of is_cmd, extensible, and chained.");
    bool hasNextInChain;

    WGPUAddressMode addressModeU;
    WGPUAddressMode addressModeV;
    WGPUAddressMode addressModeW;
    WGPUFilterMode magFilter;
    WGPUFilterMode minFilter;
    WGPUFilterMode mipmapFilter;
    float lodMinClamp;
    float lodMaxClamp;
    WGPUCompareFunction compare;

    size_t labelStrlen;

    bool has_label;
};



DAWN_DECLARE_UNUSED size_t WGPUSamplerDescriptorGetExtraRequiredSize(const WGPUSamplerDescriptor& record) {
    DAWN_UNUSED(record);

    size_t result = 0;

    if (record.nextInChain != nullptr) {
        result += GetChainedStructExtraRequiredSize(record.nextInChain);
    }


    bool has_label = record.label != nullptr;
    if (has_label)
    {
    result += std::strlen(record.label);
    }

    {
    }
    {
    }
    {
    }
    {
    }
    {
    }
    {
    }
    {
    }
    {
    }
    {
    }

    return result;
}
// GetExtraRequiredSize isn't used for structures that are value members of other structures
// because we assume they cannot contain pointers themselves.
DAWN_UNUSED_FUNC(WGPUSamplerDescriptorGetExtraRequiredSize);

DAWN_DECLARE_UNUSED void WGPUSamplerDescriptorSerialize(const WGPUSamplerDescriptor& record, WGPUSamplerDescriptorTransfer* transfer,
                       char** buffer, const ObjectIdProvider& provider) {
    DAWN_UNUSED(buffer);


    transfer->addressModeU = record.addressModeU;
    transfer->addressModeV = record.addressModeV;
    transfer->addressModeW = record.addressModeW;
    transfer->magFilter = record.magFilter;
    transfer->minFilter = record.minFilter;
    transfer->mipmapFilter = record.mipmapFilter;
    transfer->lodMinClamp = record.lodMinClamp;
    transfer->lodMaxClamp = record.lodMaxClamp;
    transfer->compare = record.compare;

    if (record.nextInChain != nullptr) {
        transfer->hasNextInChain = true;
        SerializeChainedStruct(record.nextInChain, buffer, provider);
    } else {
        transfer->hasNextInChain = false;
    }



    bool has_label = record.label != nullptr;
    transfer->has_label = has_label;
    if (has_label)
    {
    transfer->labelStrlen = std::strlen(record.label);

    memcpy(*buffer, record.label, transfer->labelStrlen);
    *buffer += transfer->labelStrlen;
    }

}
DAWN_UNUSED_FUNC(WGPUSamplerDescriptorSerialize);

DAWN_DECLARE_UNUSED DeserializeResult WGPUSamplerDescriptorDeserialize(WGPUSamplerDescriptor* record, const volatile WGPUSamplerDescriptorTransfer* transfer,
                                      const volatile char** buffer, size_t* size, DeserializeAllocator* allocator, const ObjectIdResolver& resolver) {
    DAWN_UNUSED(allocator);
    DAWN_UNUSED(buffer);
    DAWN_UNUSED(size);



    record->addressModeU = transfer->addressModeU;
    record->addressModeV = transfer->addressModeV;
    record->addressModeW = transfer->addressModeW;
    record->magFilter = transfer->magFilter;
    record->minFilter = transfer->minFilter;
    record->mipmapFilter = transfer->mipmapFilter;
    record->lodMinClamp = transfer->lodMinClamp;
    record->lodMaxClamp = transfer->lodMaxClamp;
    record->compare = transfer->compare;

    record->nextInChain = nullptr;
    if (transfer->hasNextInChain) {
        DESERIALIZE_TRY(DeserializeChainedStruct(&record->nextInChain, buffer, size, allocator, resolver));
    }



    bool has_label = transfer->has_label;
    record->label = nullptr;
    if (has_label)
    {
        size_t stringLength = transfer->labelStrlen;
        const volatile char* stringInBuffer = nullptr;
        DESERIALIZE_TRY(GetPtrFromBuffer(buffer, size, stringLength, &stringInBuffer));

        char* copiedString = nullptr;
        DESERIALIZE_TRY(GetSpace(allocator, stringLength + 1, &copiedString));
        std::copy(stringInBuffer, stringInBuffer + stringLength, copiedString);
        copiedString[stringLength] = '\0';
        record->label = copiedString;
    }


    return DeserializeResult::Success;
}
DAWN_UNUSED_FUNC(WGPUSamplerDescriptorDeserialize);

        
struct WGPUSamplerDescriptorDummyAnisotropicFilteringTransfer {
    static_assert(1 <= 1,
                  "Record must be at most one of is_cmd, extensible, and chained.");
    WGPUChainedStructTransfer chain;

    float maxAnisotropy;


};


static_assert(offsetof(WGPUSamplerDescriptorDummyAnisotropicFilteringTransfer, chain) == 0, "");

DAWN_DECLARE_UNUSED size_t WGPUSamplerDescriptorDummyAnisotropicFilteringGetExtraRequiredSize(const WGPUSamplerDescriptorDummyAnisotropicFiltering& record) {
    DAWN_UNUSED(record);

    size_t result = 0;



    {
    }

    return result;
}
// GetExtraRequiredSize isn't used for structures that are value members of other structures
// because we assume they cannot contain pointers themselves.
DAWN_UNUSED_FUNC(WGPUSamplerDescriptorDummyAnisotropicFilteringGetExtraRequiredSize);

DAWN_DECLARE_UNUSED void WGPUSamplerDescriptorDummyAnisotropicFilteringSerialize(const WGPUSamplerDescriptorDummyAnisotropicFiltering& record, WGPUSamplerDescriptorDummyAnisotropicFilteringTransfer* transfer,
                       char** buffer, const ObjectIdProvider& provider) {
    DAWN_UNUSED(buffer);


    transfer->maxAnisotropy = record.maxAnisotropy;


    ASSERT(transfer->chain.sType == WGPUSType_SamplerDescriptorDummyAnisotropicFiltering);
    ASSERT(transfer->chain.hasNext == (record.chain.next != nullptr));


}
DAWN_UNUSED_FUNC(WGPUSamplerDescriptorDummyAnisotropicFilteringSerialize);

DAWN_DECLARE_UNUSED DeserializeResult WGPUSamplerDescriptorDummyAnisotropicFilteringDeserialize(WGPUSamplerDescriptorDummyAnisotropicFiltering* record, const volatile WGPUSamplerDescriptorDummyAnisotropicFilteringTransfer* transfer,
                                      const volatile char** buffer, size_t* size, DeserializeAllocator* allocator, const ObjectIdResolver& resolver) {
    DAWN_UNUSED(allocator);
    DAWN_UNUSED(buffer);
    DAWN_UNUSED(size);



    record->maxAnisotropy = transfer->maxAnisotropy;


    ASSERT(record->chain.sType == WGPUSType_SamplerDescriptorDummyAnisotropicFiltering);
    ASSERT(record->chain.next == nullptr);



    return DeserializeResult::Success;
}
DAWN_UNUSED_FUNC(WGPUSamplerDescriptorDummyAnisotropicFilteringDeserialize);

        
struct WGPUShaderModuleDescriptorTransfer {
    static_assert(1 <= 1,
                  "Record must be at most one of is_cmd, extensible, and chained.");
    bool hasNextInChain;


    size_t labelStrlen;

    bool has_label;
};



DAWN_DECLARE_UNUSED size_t WGPUShaderModuleDescriptorGetExtraRequiredSize(const WGPUShaderModuleDescriptor& record) {
    DAWN_UNUSED(record);

    size_t result = 0;

    if (record.nextInChain != nullptr) {
        result += GetChainedStructExtraRequiredSize(record.nextInChain);
    }


    bool has_label = record.label != nullptr;
    if (has_label)
    {
    result += std::strlen(record.label);
    }


    return result;
}
// GetExtraRequiredSize isn't used for structures that are value members of other structures
// because we assume they cannot contain pointers themselves.
DAWN_UNUSED_FUNC(WGPUShaderModuleDescriptorGetExtraRequiredSize);

DAWN_DECLARE_UNUSED void WGPUShaderModuleDescriptorSerialize(const WGPUShaderModuleDescriptor& record, WGPUShaderModuleDescriptorTransfer* transfer,
                       char** buffer, const ObjectIdProvider& provider) {
    DAWN_UNUSED(buffer);



    if (record.nextInChain != nullptr) {
        transfer->hasNextInChain = true;
        SerializeChainedStruct(record.nextInChain, buffer, provider);
    } else {
        transfer->hasNextInChain = false;
    }



    bool has_label = record.label != nullptr;
    transfer->has_label = has_label;
    if (has_label)
    {
    transfer->labelStrlen = std::strlen(record.label);

    memcpy(*buffer, record.label, transfer->labelStrlen);
    *buffer += transfer->labelStrlen;
    }

}
DAWN_UNUSED_FUNC(WGPUShaderModuleDescriptorSerialize);

DAWN_DECLARE_UNUSED DeserializeResult WGPUShaderModuleDescriptorDeserialize(WGPUShaderModuleDescriptor* record, const volatile WGPUShaderModuleDescriptorTransfer* transfer,
                                      const volatile char** buffer, size_t* size, DeserializeAllocator* allocator, const ObjectIdResolver& resolver) {
    DAWN_UNUSED(allocator);
    DAWN_UNUSED(buffer);
    DAWN_UNUSED(size);




    record->nextInChain = nullptr;
    if (transfer->hasNextInChain) {
        DESERIALIZE_TRY(DeserializeChainedStruct(&record->nextInChain, buffer, size, allocator, resolver));
    }



    bool has_label = transfer->has_label;
    record->label = nullptr;
    if (has_label)
    {
        size_t stringLength = transfer->labelStrlen;
        const volatile char* stringInBuffer = nullptr;
        DESERIALIZE_TRY(GetPtrFromBuffer(buffer, size, stringLength, &stringInBuffer));

        char* copiedString = nullptr;
        DESERIALIZE_TRY(GetSpace(allocator, stringLength + 1, &copiedString));
        std::copy(stringInBuffer, stringInBuffer + stringLength, copiedString);
        copiedString[stringLength] = '\0';
        record->label = copiedString;
    }


    return DeserializeResult::Success;
}
DAWN_UNUSED_FUNC(WGPUShaderModuleDescriptorDeserialize);

        
struct WGPUShaderModuleSPIRVDescriptorTransfer {
    static_assert(1 <= 1,
                  "Record must be at most one of is_cmd, extensible, and chained.");
    WGPUChainedStructTransfer chain;

    uint32_t codeSize;


};


static_assert(offsetof(WGPUShaderModuleSPIRVDescriptorTransfer, chain) == 0, "");

DAWN_DECLARE_UNUSED size_t WGPUShaderModuleSPIRVDescriptorGetExtraRequiredSize(const WGPUShaderModuleSPIRVDescriptor& record) {
    DAWN_UNUSED(record);

    size_t result = 0;



    {
    }
    {
        size_t memberLength = record.codeSize;
        result += memberLength * sizeof(uint32_t);
    }

    return result;
}
// GetExtraRequiredSize isn't used for structures that are value members of other structures
// because we assume they cannot contain pointers themselves.
DAWN_UNUSED_FUNC(WGPUShaderModuleSPIRVDescriptorGetExtraRequiredSize);

DAWN_DECLARE_UNUSED void WGPUShaderModuleSPIRVDescriptorSerialize(const WGPUShaderModuleSPIRVDescriptor& record, WGPUShaderModuleSPIRVDescriptorTransfer* transfer,
                       char** buffer, const ObjectIdProvider& provider) {
    DAWN_UNUSED(buffer);


    transfer->codeSize = record.codeSize;


    ASSERT(transfer->chain.sType == WGPUSType_ShaderModuleSPIRVDescriptor);
    ASSERT(transfer->chain.hasNext == (record.chain.next != nullptr));



    {
        size_t memberLength = record.codeSize;
        auto memberBuffer = reinterpret_cast<uint32_t*>(*buffer);
        *buffer += memberLength * sizeof(uint32_t);

        for (size_t i = 0; i < memberLength; ++i) {
            memberBuffer[i] = record.code[i];
        }
    }
}
DAWN_UNUSED_FUNC(WGPUShaderModuleSPIRVDescriptorSerialize);

DAWN_DECLARE_UNUSED DeserializeResult WGPUShaderModuleSPIRVDescriptorDeserialize(WGPUShaderModuleSPIRVDescriptor* record, const volatile WGPUShaderModuleSPIRVDescriptorTransfer* transfer,
                                      const volatile char** buffer, size_t* size, DeserializeAllocator* allocator, const ObjectIdResolver& resolver) {
    DAWN_UNUSED(allocator);
    DAWN_UNUSED(buffer);
    DAWN_UNUSED(size);



    record->codeSize = transfer->codeSize;


    ASSERT(record->chain.sType == WGPUSType_ShaderModuleSPIRVDescriptor);
    ASSERT(record->chain.next == nullptr);



    {
        size_t memberLength = record->codeSize;
        auto memberBuffer = reinterpret_cast<const volatile uint32_t*>(buffer);
        DESERIALIZE_TRY(GetPtrFromBuffer(buffer, size, memberLength, &memberBuffer));

        uint32_t* copiedMembers = nullptr;
        DESERIALIZE_TRY(GetSpace(allocator, memberLength, &copiedMembers));
        record->code = copiedMembers;

        for (size_t i = 0; i < memberLength; ++i) {
            copiedMembers[i] = memberBuffer[i];
        }
    }

    return DeserializeResult::Success;
}
DAWN_UNUSED_FUNC(WGPUShaderModuleSPIRVDescriptorDeserialize);

        
struct WGPUShaderModuleWGSLDescriptorTransfer {
    static_assert(1 <= 1,
                  "Record must be at most one of is_cmd, extensible, and chained.");
    WGPUChainedStructTransfer chain;


    size_t sourceStrlen;

};


static_assert(offsetof(WGPUShaderModuleWGSLDescriptorTransfer, chain) == 0, "");

DAWN_DECLARE_UNUSED size_t WGPUShaderModuleWGSLDescriptorGetExtraRequiredSize(const WGPUShaderModuleWGSLDescriptor& record) {
    DAWN_UNUSED(record);

    size_t result = 0;



    {
    result += std::strlen(record.source);
    }


    return result;
}
// GetExtraRequiredSize isn't used for structures that are value members of other structures
// because we assume they cannot contain pointers themselves.
DAWN_UNUSED_FUNC(WGPUShaderModuleWGSLDescriptorGetExtraRequiredSize);

DAWN_DECLARE_UNUSED void WGPUShaderModuleWGSLDescriptorSerialize(const WGPUShaderModuleWGSLDescriptor& record, WGPUShaderModuleWGSLDescriptorTransfer* transfer,
                       char** buffer, const ObjectIdProvider& provider) {
    DAWN_UNUSED(buffer);




    ASSERT(transfer->chain.sType == WGPUSType_ShaderModuleWGSLDescriptor);
    ASSERT(transfer->chain.hasNext == (record.chain.next != nullptr));


    {
    transfer->sourceStrlen = std::strlen(record.source);

    memcpy(*buffer, record.source, transfer->sourceStrlen);
    *buffer += transfer->sourceStrlen;
    }

}
DAWN_UNUSED_FUNC(WGPUShaderModuleWGSLDescriptorSerialize);

DAWN_DECLARE_UNUSED DeserializeResult WGPUShaderModuleWGSLDescriptorDeserialize(WGPUShaderModuleWGSLDescriptor* record, const volatile WGPUShaderModuleWGSLDescriptorTransfer* transfer,
                                      const volatile char** buffer, size_t* size, DeserializeAllocator* allocator, const ObjectIdResolver& resolver) {
    DAWN_UNUSED(allocator);
    DAWN_UNUSED(buffer);
    DAWN_UNUSED(size);





    ASSERT(record->chain.sType == WGPUSType_ShaderModuleWGSLDescriptor);
    ASSERT(record->chain.next == nullptr);


    {
        size_t stringLength = transfer->sourceStrlen;
        const volatile char* stringInBuffer = nullptr;
        DESERIALIZE_TRY(GetPtrFromBuffer(buffer, size, stringLength, &stringInBuffer));

        char* copiedString = nullptr;
        DESERIALIZE_TRY(GetSpace(allocator, stringLength + 1, &copiedString));
        std::copy(stringInBuffer, stringInBuffer + stringLength, copiedString);
        copiedString[stringLength] = '\0';
        record->source = copiedString;
    }


    return DeserializeResult::Success;
}
DAWN_UNUSED_FUNC(WGPUShaderModuleWGSLDescriptorDeserialize);

        
struct WGPUStencilStateFaceDescriptorTransfer {
    static_assert(0 <= 1,
                  "Record must be at most one of is_cmd, extensible, and chained.");

    WGPUCompareFunction compare;
    WGPUStencilOperation failOp;
    WGPUStencilOperation depthFailOp;
    WGPUStencilOperation passOp;


};



DAWN_DECLARE_UNUSED size_t WGPUStencilStateFaceDescriptorGetExtraRequiredSize(const WGPUStencilStateFaceDescriptor& record) {
    DAWN_UNUSED(record);

    size_t result = 0;



    {
    }
    {
    }
    {
    }
    {
    }

    return result;
}
// GetExtraRequiredSize isn't used for structures that are value members of other structures
// because we assume they cannot contain pointers themselves.
DAWN_UNUSED_FUNC(WGPUStencilStateFaceDescriptorGetExtraRequiredSize);

DAWN_DECLARE_UNUSED void WGPUStencilStateFaceDescriptorSerialize(const WGPUStencilStateFaceDescriptor& record, WGPUStencilStateFaceDescriptorTransfer* transfer,
                       char** buffer) {
    DAWN_UNUSED(buffer);


    transfer->compare = record.compare;
    transfer->failOp = record.failOp;
    transfer->depthFailOp = record.depthFailOp;
    transfer->passOp = record.passOp;




}
DAWN_UNUSED_FUNC(WGPUStencilStateFaceDescriptorSerialize);

DAWN_DECLARE_UNUSED DeserializeResult WGPUStencilStateFaceDescriptorDeserialize(WGPUStencilStateFaceDescriptor* record, const volatile WGPUStencilStateFaceDescriptorTransfer* transfer,
                                      const volatile char** buffer, size_t* size, DeserializeAllocator* allocator) {
    DAWN_UNUSED(allocator);
    DAWN_UNUSED(buffer);
    DAWN_UNUSED(size);



    record->compare = transfer->compare;
    record->failOp = transfer->failOp;
    record->depthFailOp = transfer->depthFailOp;
    record->passOp = transfer->passOp;





    return DeserializeResult::Success;
}
DAWN_UNUSED_FUNC(WGPUStencilStateFaceDescriptorDeserialize);

        
struct WGPUSurfaceDescriptorTransfer {
    static_assert(1 <= 1,
                  "Record must be at most one of is_cmd, extensible, and chained.");
    bool hasNextInChain;


    size_t labelStrlen;

    bool has_label;
};



DAWN_DECLARE_UNUSED size_t WGPUSurfaceDescriptorGetExtraRequiredSize(const WGPUSurfaceDescriptor& record) {
    DAWN_UNUSED(record);

    size_t result = 0;

    if (record.nextInChain != nullptr) {
        result += GetChainedStructExtraRequiredSize(record.nextInChain);
    }


    bool has_label = record.label != nullptr;
    if (has_label)
    {
    result += std::strlen(record.label);
    }


    return result;
}
// GetExtraRequiredSize isn't used for structures that are value members of other structures
// because we assume they cannot contain pointers themselves.
DAWN_UNUSED_FUNC(WGPUSurfaceDescriptorGetExtraRequiredSize);

DAWN_DECLARE_UNUSED void WGPUSurfaceDescriptorSerialize(const WGPUSurfaceDescriptor& record, WGPUSurfaceDescriptorTransfer* transfer,
                       char** buffer, const ObjectIdProvider& provider) {
    DAWN_UNUSED(buffer);



    if (record.nextInChain != nullptr) {
        transfer->hasNextInChain = true;
        SerializeChainedStruct(record.nextInChain, buffer, provider);
    } else {
        transfer->hasNextInChain = false;
    }



    bool has_label = record.label != nullptr;
    transfer->has_label = has_label;
    if (has_label)
    {
    transfer->labelStrlen = std::strlen(record.label);

    memcpy(*buffer, record.label, transfer->labelStrlen);
    *buffer += transfer->labelStrlen;
    }

}
DAWN_UNUSED_FUNC(WGPUSurfaceDescriptorSerialize);

DAWN_DECLARE_UNUSED DeserializeResult WGPUSurfaceDescriptorDeserialize(WGPUSurfaceDescriptor* record, const volatile WGPUSurfaceDescriptorTransfer* transfer,
                                      const volatile char** buffer, size_t* size, DeserializeAllocator* allocator, const ObjectIdResolver& resolver) {
    DAWN_UNUSED(allocator);
    DAWN_UNUSED(buffer);
    DAWN_UNUSED(size);




    record->nextInChain = nullptr;
    if (transfer->hasNextInChain) {
        DESERIALIZE_TRY(DeserializeChainedStruct(&record->nextInChain, buffer, size, allocator, resolver));
    }



    bool has_label = transfer->has_label;
    record->label = nullptr;
    if (has_label)
    {
        size_t stringLength = transfer->labelStrlen;
        const volatile char* stringInBuffer = nullptr;
        DESERIALIZE_TRY(GetPtrFromBuffer(buffer, size, stringLength, &stringInBuffer));

        char* copiedString = nullptr;
        DESERIALIZE_TRY(GetSpace(allocator, stringLength + 1, &copiedString));
        std::copy(stringInBuffer, stringInBuffer + stringLength, copiedString);
        copiedString[stringLength] = '\0';
        record->label = copiedString;
    }


    return DeserializeResult::Success;
}
DAWN_UNUSED_FUNC(WGPUSurfaceDescriptorDeserialize);

        
struct WGPUSurfaceDescriptorFromCanvasHTMLSelectorTransfer {
    static_assert(1 <= 1,
                  "Record must be at most one of is_cmd, extensible, and chained.");
    WGPUChainedStructTransfer chain;


    size_t selectorStrlen;

};


static_assert(offsetof(WGPUSurfaceDescriptorFromCanvasHTMLSelectorTransfer, chain) == 0, "");

DAWN_DECLARE_UNUSED size_t WGPUSurfaceDescriptorFromCanvasHTMLSelectorGetExtraRequiredSize(const WGPUSurfaceDescriptorFromCanvasHTMLSelector& record) {
    DAWN_UNUSED(record);

    size_t result = 0;



    {
    result += std::strlen(record.selector);
    }


    return result;
}
// GetExtraRequiredSize isn't used for structures that are value members of other structures
// because we assume they cannot contain pointers themselves.
DAWN_UNUSED_FUNC(WGPUSurfaceDescriptorFromCanvasHTMLSelectorGetExtraRequiredSize);

DAWN_DECLARE_UNUSED void WGPUSurfaceDescriptorFromCanvasHTMLSelectorSerialize(const WGPUSurfaceDescriptorFromCanvasHTMLSelector& record, WGPUSurfaceDescriptorFromCanvasHTMLSelectorTransfer* transfer,
                       char** buffer, const ObjectIdProvider& provider) {
    DAWN_UNUSED(buffer);




    ASSERT(transfer->chain.sType == WGPUSType_SurfaceDescriptorFromCanvasHTMLSelector);
    ASSERT(transfer->chain.hasNext == (record.chain.next != nullptr));


    {
    transfer->selectorStrlen = std::strlen(record.selector);

    memcpy(*buffer, record.selector, transfer->selectorStrlen);
    *buffer += transfer->selectorStrlen;
    }

}
DAWN_UNUSED_FUNC(WGPUSurfaceDescriptorFromCanvasHTMLSelectorSerialize);

DAWN_DECLARE_UNUSED DeserializeResult WGPUSurfaceDescriptorFromCanvasHTMLSelectorDeserialize(WGPUSurfaceDescriptorFromCanvasHTMLSelector* record, const volatile WGPUSurfaceDescriptorFromCanvasHTMLSelectorTransfer* transfer,
                                      const volatile char** buffer, size_t* size, DeserializeAllocator* allocator, const ObjectIdResolver& resolver) {
    DAWN_UNUSED(allocator);
    DAWN_UNUSED(buffer);
    DAWN_UNUSED(size);





    ASSERT(record->chain.sType == WGPUSType_SurfaceDescriptorFromCanvasHTMLSelector);
    ASSERT(record->chain.next == nullptr);


    {
        size_t stringLength = transfer->selectorStrlen;
        const volatile char* stringInBuffer = nullptr;
        DESERIALIZE_TRY(GetPtrFromBuffer(buffer, size, stringLength, &stringInBuffer));

        char* copiedString = nullptr;
        DESERIALIZE_TRY(GetSpace(allocator, stringLength + 1, &copiedString));
        std::copy(stringInBuffer, stringInBuffer + stringLength, copiedString);
        copiedString[stringLength] = '\0';
        record->selector = copiedString;
    }


    return DeserializeResult::Success;
}
DAWN_UNUSED_FUNC(WGPUSurfaceDescriptorFromCanvasHTMLSelectorDeserialize);

        
struct WGPUSwapChainDescriptorTransfer {
    static_assert(1 <= 1,
                  "Record must be at most one of is_cmd, extensible, and chained.");
    bool hasNextInChain;

    WGPUTextureUsageFlags usage;
    WGPUTextureFormat format;
    uint32_t width;
    uint32_t height;
    WGPUPresentMode presentMode;
    uint64_t implementation;

    size_t labelStrlen;

    bool has_label;
};



DAWN_DECLARE_UNUSED size_t WGPUSwapChainDescriptorGetExtraRequiredSize(const WGPUSwapChainDescriptor& record) {
    DAWN_UNUSED(record);

    size_t result = 0;

    if (record.nextInChain != nullptr) {
        result += GetChainedStructExtraRequiredSize(record.nextInChain);
    }


    bool has_label = record.label != nullptr;
    if (has_label)
    {
    result += std::strlen(record.label);
    }

    {
    }
    {
    }
    {
    }
    {
    }
    {
    }
    {
    }

    return result;
}
// GetExtraRequiredSize isn't used for structures that are value members of other structures
// because we assume they cannot contain pointers themselves.
DAWN_UNUSED_FUNC(WGPUSwapChainDescriptorGetExtraRequiredSize);

DAWN_DECLARE_UNUSED void WGPUSwapChainDescriptorSerialize(const WGPUSwapChainDescriptor& record, WGPUSwapChainDescriptorTransfer* transfer,
                       char** buffer, const ObjectIdProvider& provider) {
    DAWN_UNUSED(buffer);


    transfer->usage = record.usage;
    transfer->format = record.format;
    transfer->width = record.width;
    transfer->height = record.height;
    transfer->presentMode = record.presentMode;
    transfer->implementation = record.implementation;

    if (record.nextInChain != nullptr) {
        transfer->hasNextInChain = true;
        SerializeChainedStruct(record.nextInChain, buffer, provider);
    } else {
        transfer->hasNextInChain = false;
    }



    bool has_label = record.label != nullptr;
    transfer->has_label = has_label;
    if (has_label)
    {
    transfer->labelStrlen = std::strlen(record.label);

    memcpy(*buffer, record.label, transfer->labelStrlen);
    *buffer += transfer->labelStrlen;
    }

}
DAWN_UNUSED_FUNC(WGPUSwapChainDescriptorSerialize);

DAWN_DECLARE_UNUSED DeserializeResult WGPUSwapChainDescriptorDeserialize(WGPUSwapChainDescriptor* record, const volatile WGPUSwapChainDescriptorTransfer* transfer,
                                      const volatile char** buffer, size_t* size, DeserializeAllocator* allocator, const ObjectIdResolver& resolver) {
    DAWN_UNUSED(allocator);
    DAWN_UNUSED(buffer);
    DAWN_UNUSED(size);



    record->usage = transfer->usage;
    record->format = transfer->format;
    record->width = transfer->width;
    record->height = transfer->height;
    record->presentMode = transfer->presentMode;
    record->implementation = transfer->implementation;

    record->nextInChain = nullptr;
    if (transfer->hasNextInChain) {
        DESERIALIZE_TRY(DeserializeChainedStruct(&record->nextInChain, buffer, size, allocator, resolver));
    }



    bool has_label = transfer->has_label;
    record->label = nullptr;
    if (has_label)
    {
        size_t stringLength = transfer->labelStrlen;
        const volatile char* stringInBuffer = nullptr;
        DESERIALIZE_TRY(GetPtrFromBuffer(buffer, size, stringLength, &stringInBuffer));

        char* copiedString = nullptr;
        DESERIALIZE_TRY(GetSpace(allocator, stringLength + 1, &copiedString));
        std::copy(stringInBuffer, stringInBuffer + stringLength, copiedString);
        copiedString[stringLength] = '\0';
        record->label = copiedString;
    }


    return DeserializeResult::Success;
}
DAWN_UNUSED_FUNC(WGPUSwapChainDescriptorDeserialize);

        
struct WGPUTextureDataLayoutTransfer {
    static_assert(1 <= 1,
                  "Record must be at most one of is_cmd, extensible, and chained.");
    bool hasNextInChain;

    uint64_t offset;
    uint32_t bytesPerRow;
    uint32_t rowsPerImage;


};



DAWN_DECLARE_UNUSED size_t WGPUTextureDataLayoutGetExtraRequiredSize(const WGPUTextureDataLayout& record) {
    DAWN_UNUSED(record);

    size_t result = 0;

    if (record.nextInChain != nullptr) {
        result += GetChainedStructExtraRequiredSize(record.nextInChain);
    }


    {
    }
    {
    }
    {
    }

    return result;
}
// GetExtraRequiredSize isn't used for structures that are value members of other structures
// because we assume they cannot contain pointers themselves.
DAWN_UNUSED_FUNC(WGPUTextureDataLayoutGetExtraRequiredSize);

DAWN_DECLARE_UNUSED void WGPUTextureDataLayoutSerialize(const WGPUTextureDataLayout& record, WGPUTextureDataLayoutTransfer* transfer,
                       char** buffer, const ObjectIdProvider& provider) {
    DAWN_UNUSED(buffer);


    transfer->offset = record.offset;
    transfer->bytesPerRow = record.bytesPerRow;
    transfer->rowsPerImage = record.rowsPerImage;

    if (record.nextInChain != nullptr) {
        transfer->hasNextInChain = true;
        SerializeChainedStruct(record.nextInChain, buffer, provider);
    } else {
        transfer->hasNextInChain = false;
    }



}
DAWN_UNUSED_FUNC(WGPUTextureDataLayoutSerialize);

DAWN_DECLARE_UNUSED DeserializeResult WGPUTextureDataLayoutDeserialize(WGPUTextureDataLayout* record, const volatile WGPUTextureDataLayoutTransfer* transfer,
                                      const volatile char** buffer, size_t* size, DeserializeAllocator* allocator, const ObjectIdResolver& resolver) {
    DAWN_UNUSED(allocator);
    DAWN_UNUSED(buffer);
    DAWN_UNUSED(size);



    record->offset = transfer->offset;
    record->bytesPerRow = transfer->bytesPerRow;
    record->rowsPerImage = transfer->rowsPerImage;

    record->nextInChain = nullptr;
    if (transfer->hasNextInChain) {
        DESERIALIZE_TRY(DeserializeChainedStruct(&record->nextInChain, buffer, size, allocator, resolver));
    }




    return DeserializeResult::Success;
}
DAWN_UNUSED_FUNC(WGPUTextureDataLayoutDeserialize);

        
struct WGPUTextureViewDescriptorTransfer {
    static_assert(1 <= 1,
                  "Record must be at most one of is_cmd, extensible, and chained.");
    bool hasNextInChain;

    WGPUTextureFormat format;
    WGPUTextureViewDimension dimension;
    uint32_t baseMipLevel;
    uint32_t mipLevelCount;
    uint32_t baseArrayLayer;
    uint32_t arrayLayerCount;
    WGPUTextureAspect aspect;

    size_t labelStrlen;

    bool has_label;
};



DAWN_DECLARE_UNUSED size_t WGPUTextureViewDescriptorGetExtraRequiredSize(const WGPUTextureViewDescriptor& record) {
    DAWN_UNUSED(record);

    size_t result = 0;

    if (record.nextInChain != nullptr) {
        result += GetChainedStructExtraRequiredSize(record.nextInChain);
    }


    bool has_label = record.label != nullptr;
    if (has_label)
    {
    result += std::strlen(record.label);
    }

    {
    }
    {
    }
    {
    }
    {
    }
    {
    }
    {
    }
    {
    }

    return result;
}
// GetExtraRequiredSize isn't used for structures that are value members of other structures
// because we assume they cannot contain pointers themselves.
DAWN_UNUSED_FUNC(WGPUTextureViewDescriptorGetExtraRequiredSize);

DAWN_DECLARE_UNUSED void WGPUTextureViewDescriptorSerialize(const WGPUTextureViewDescriptor& record, WGPUTextureViewDescriptorTransfer* transfer,
                       char** buffer, const ObjectIdProvider& provider) {
    DAWN_UNUSED(buffer);


    transfer->format = record.format;
    transfer->dimension = record.dimension;
    transfer->baseMipLevel = record.baseMipLevel;
    transfer->mipLevelCount = record.mipLevelCount;
    transfer->baseArrayLayer = record.baseArrayLayer;
    transfer->arrayLayerCount = record.arrayLayerCount;
    transfer->aspect = record.aspect;

    if (record.nextInChain != nullptr) {
        transfer->hasNextInChain = true;
        SerializeChainedStruct(record.nextInChain, buffer, provider);
    } else {
        transfer->hasNextInChain = false;
    }



    bool has_label = record.label != nullptr;
    transfer->has_label = has_label;
    if (has_label)
    {
    transfer->labelStrlen = std::strlen(record.label);

    memcpy(*buffer, record.label, transfer->labelStrlen);
    *buffer += transfer->labelStrlen;
    }

}
DAWN_UNUSED_FUNC(WGPUTextureViewDescriptorSerialize);

DAWN_DECLARE_UNUSED DeserializeResult WGPUTextureViewDescriptorDeserialize(WGPUTextureViewDescriptor* record, const volatile WGPUTextureViewDescriptorTransfer* transfer,
                                      const volatile char** buffer, size_t* size, DeserializeAllocator* allocator, const ObjectIdResolver& resolver) {
    DAWN_UNUSED(allocator);
    DAWN_UNUSED(buffer);
    DAWN_UNUSED(size);



    record->format = transfer->format;
    record->dimension = transfer->dimension;
    record->baseMipLevel = transfer->baseMipLevel;
    record->mipLevelCount = transfer->mipLevelCount;
    record->baseArrayLayer = transfer->baseArrayLayer;
    record->arrayLayerCount = transfer->arrayLayerCount;
    record->aspect = transfer->aspect;

    record->nextInChain = nullptr;
    if (transfer->hasNextInChain) {
        DESERIALIZE_TRY(DeserializeChainedStruct(&record->nextInChain, buffer, size, allocator, resolver));
    }



    bool has_label = transfer->has_label;
    record->label = nullptr;
    if (has_label)
    {
        size_t stringLength = transfer->labelStrlen;
        const volatile char* stringInBuffer = nullptr;
        DESERIALIZE_TRY(GetPtrFromBuffer(buffer, size, stringLength, &stringInBuffer));

        char* copiedString = nullptr;
        DESERIALIZE_TRY(GetSpace(allocator, stringLength + 1, &copiedString));
        std::copy(stringInBuffer, stringInBuffer + stringLength, copiedString);
        copiedString[stringLength] = '\0';
        record->label = copiedString;
    }


    return DeserializeResult::Success;
}
DAWN_UNUSED_FUNC(WGPUTextureViewDescriptorDeserialize);

        
struct WGPUVertexAttributeDescriptorTransfer {
    static_assert(0 <= 1,
                  "Record must be at most one of is_cmd, extensible, and chained.");

    WGPUVertexFormat format;
    uint64_t offset;
    uint32_t shaderLocation;


};



DAWN_DECLARE_UNUSED size_t WGPUVertexAttributeDescriptorGetExtraRequiredSize(const WGPUVertexAttributeDescriptor& record) {
    DAWN_UNUSED(record);

    size_t result = 0;



    {
    }
    {
    }
    {
    }

    return result;
}
// GetExtraRequiredSize isn't used for structures that are value members of other structures
// because we assume they cannot contain pointers themselves.
DAWN_UNUSED_FUNC(WGPUVertexAttributeDescriptorGetExtraRequiredSize);

DAWN_DECLARE_UNUSED void WGPUVertexAttributeDescriptorSerialize(const WGPUVertexAttributeDescriptor& record, WGPUVertexAttributeDescriptorTransfer* transfer,
                       char** buffer) {
    DAWN_UNUSED(buffer);


    transfer->format = record.format;
    transfer->offset = record.offset;
    transfer->shaderLocation = record.shaderLocation;




}
DAWN_UNUSED_FUNC(WGPUVertexAttributeDescriptorSerialize);

DAWN_DECLARE_UNUSED DeserializeResult WGPUVertexAttributeDescriptorDeserialize(WGPUVertexAttributeDescriptor* record, const volatile WGPUVertexAttributeDescriptorTransfer* transfer,
                                      const volatile char** buffer, size_t* size, DeserializeAllocator* allocator) {
    DAWN_UNUSED(allocator);
    DAWN_UNUSED(buffer);
    DAWN_UNUSED(size);



    record->format = transfer->format;
    record->offset = transfer->offset;
    record->shaderLocation = transfer->shaderLocation;





    return DeserializeResult::Success;
}
DAWN_UNUSED_FUNC(WGPUVertexAttributeDescriptorDeserialize);

        
struct WGPUBindGroupDescriptorTransfer {
    static_assert(1 <= 1,
                  "Record must be at most one of is_cmd, extensible, and chained.");
    bool hasNextInChain;

    ObjectId layout;
    uint32_t entryCount;

    size_t labelStrlen;

    bool has_label;
};



DAWN_DECLARE_UNUSED size_t WGPUBindGroupDescriptorGetExtraRequiredSize(const WGPUBindGroupDescriptor& record) {
    DAWN_UNUSED(record);

    size_t result = 0;

    if (record.nextInChain != nullptr) {
        result += GetChainedStructExtraRequiredSize(record.nextInChain);
    }


    bool has_label = record.label != nullptr;
    if (has_label)
    {
    result += std::strlen(record.label);
    }

    {
    }
    {
    }
    {
        size_t memberLength = record.entryCount;
        result += memberLength * sizeof(WGPUBindGroupEntryTransfer);
        for (size_t i = 0; i < memberLength; ++i) {
            
            result += WGPUBindGroupEntryGetExtraRequiredSize(record.entries[i]);
        }
    }

    return result;
}
// GetExtraRequiredSize isn't used for structures that are value members of other structures
// because we assume they cannot contain pointers themselves.
DAWN_UNUSED_FUNC(WGPUBindGroupDescriptorGetExtraRequiredSize);

DAWN_DECLARE_UNUSED void WGPUBindGroupDescriptorSerialize(const WGPUBindGroupDescriptor& record, WGPUBindGroupDescriptorTransfer* transfer,
                       char** buffer, const ObjectIdProvider& provider) {
    DAWN_UNUSED(buffer);


    transfer->layout = provider.GetId(record.layout);

    transfer->entryCount = record.entryCount;

    if (record.nextInChain != nullptr) {
        transfer->hasNextInChain = true;
        SerializeChainedStruct(record.nextInChain, buffer, provider);
    } else {
        transfer->hasNextInChain = false;
    }



    bool has_label = record.label != nullptr;
    transfer->has_label = has_label;
    if (has_label)
    {
    transfer->labelStrlen = std::strlen(record.label);

    memcpy(*buffer, record.label, transfer->labelStrlen);
    *buffer += transfer->labelStrlen;
    }


    {
        size_t memberLength = record.entryCount;
        auto memberBuffer = reinterpret_cast<WGPUBindGroupEntryTransfer*>(*buffer);
        *buffer += memberLength * sizeof(WGPUBindGroupEntryTransfer);

        for (size_t i = 0; i < memberLength; ++i) {
            WGPUBindGroupEntrySerialize(record.entries[i], &memberBuffer[i], buffer, provider);

        }
    }
}
DAWN_UNUSED_FUNC(WGPUBindGroupDescriptorSerialize);

DAWN_DECLARE_UNUSED DeserializeResult WGPUBindGroupDescriptorDeserialize(WGPUBindGroupDescriptor* record, const volatile WGPUBindGroupDescriptorTransfer* transfer,
                                      const volatile char** buffer, size_t* size, DeserializeAllocator* allocator, const ObjectIdResolver& resolver) {
    DAWN_UNUSED(allocator);
    DAWN_UNUSED(buffer);
    DAWN_UNUSED(size);



    DESERIALIZE_TRY(resolver.GetFromId(transfer->layout, &record->layout));
    record->entryCount = transfer->entryCount;

    record->nextInChain = nullptr;
    if (transfer->hasNextInChain) {
        DESERIALIZE_TRY(DeserializeChainedStruct(&record->nextInChain, buffer, size, allocator, resolver));
    }



    bool has_label = transfer->has_label;
    record->label = nullptr;
    if (has_label)
    {
        size_t stringLength = transfer->labelStrlen;
        const volatile char* stringInBuffer = nullptr;
        DESERIALIZE_TRY(GetPtrFromBuffer(buffer, size, stringLength, &stringInBuffer));

        char* copiedString = nullptr;
        DESERIALIZE_TRY(GetSpace(allocator, stringLength + 1, &copiedString));
        std::copy(stringInBuffer, stringInBuffer + stringLength, copiedString);
        copiedString[stringLength] = '\0';
        record->label = copiedString;
    }


    {
        size_t memberLength = record->entryCount;
        auto memberBuffer = reinterpret_cast<const volatile WGPUBindGroupEntryTransfer*>(buffer);
        DESERIALIZE_TRY(GetPtrFromBuffer(buffer, size, memberLength, &memberBuffer));

        WGPUBindGroupEntry* copiedMembers = nullptr;
        DESERIALIZE_TRY(GetSpace(allocator, memberLength, &copiedMembers));
        record->entries = copiedMembers;

        for (size_t i = 0; i < memberLength; ++i) {
            DESERIALIZE_TRY(WGPUBindGroupEntryDeserialize(&copiedMembers[i], &memberBuffer[i], buffer, size, allocator, resolver));
        }
    }

    return DeserializeResult::Success;
}
DAWN_UNUSED_FUNC(WGPUBindGroupDescriptorDeserialize);

        
struct WGPUBindGroupLayoutDescriptorTransfer {
    static_assert(1 <= 1,
                  "Record must be at most one of is_cmd, extensible, and chained.");
    bool hasNextInChain;

    uint32_t entryCount;

    size_t labelStrlen;

    bool has_label;
};



DAWN_DECLARE_UNUSED size_t WGPUBindGroupLayoutDescriptorGetExtraRequiredSize(const WGPUBindGroupLayoutDescriptor& record) {
    DAWN_UNUSED(record);

    size_t result = 0;

    if (record.nextInChain != nullptr) {
        result += GetChainedStructExtraRequiredSize(record.nextInChain);
    }


    bool has_label = record.label != nullptr;
    if (has_label)
    {
    result += std::strlen(record.label);
    }

    {
    }
    {
        size_t memberLength = record.entryCount;
        result += memberLength * sizeof(WGPUBindGroupLayoutEntryTransfer);
        for (size_t i = 0; i < memberLength; ++i) {
            
            result += WGPUBindGroupLayoutEntryGetExtraRequiredSize(record.entries[i]);
        }
    }

    return result;
}
// GetExtraRequiredSize isn't used for structures that are value members of other structures
// because we assume they cannot contain pointers themselves.
DAWN_UNUSED_FUNC(WGPUBindGroupLayoutDescriptorGetExtraRequiredSize);

DAWN_DECLARE_UNUSED void WGPUBindGroupLayoutDescriptorSerialize(const WGPUBindGroupLayoutDescriptor& record, WGPUBindGroupLayoutDescriptorTransfer* transfer,
                       char** buffer, const ObjectIdProvider& provider) {
    DAWN_UNUSED(buffer);


    transfer->entryCount = record.entryCount;

    if (record.nextInChain != nullptr) {
        transfer->hasNextInChain = true;
        SerializeChainedStruct(record.nextInChain, buffer, provider);
    } else {
        transfer->hasNextInChain = false;
    }



    bool has_label = record.label != nullptr;
    transfer->has_label = has_label;
    if (has_label)
    {
    transfer->labelStrlen = std::strlen(record.label);

    memcpy(*buffer, record.label, transfer->labelStrlen);
    *buffer += transfer->labelStrlen;
    }


    {
        size_t memberLength = record.entryCount;
        auto memberBuffer = reinterpret_cast<WGPUBindGroupLayoutEntryTransfer*>(*buffer);
        *buffer += memberLength * sizeof(WGPUBindGroupLayoutEntryTransfer);

        for (size_t i = 0; i < memberLength; ++i) {
            WGPUBindGroupLayoutEntrySerialize(record.entries[i], &memberBuffer[i], buffer);

        }
    }
}
DAWN_UNUSED_FUNC(WGPUBindGroupLayoutDescriptorSerialize);

DAWN_DECLARE_UNUSED DeserializeResult WGPUBindGroupLayoutDescriptorDeserialize(WGPUBindGroupLayoutDescriptor* record, const volatile WGPUBindGroupLayoutDescriptorTransfer* transfer,
                                      const volatile char** buffer, size_t* size, DeserializeAllocator* allocator, const ObjectIdResolver& resolver) {
    DAWN_UNUSED(allocator);
    DAWN_UNUSED(buffer);
    DAWN_UNUSED(size);



    record->entryCount = transfer->entryCount;

    record->nextInChain = nullptr;
    if (transfer->hasNextInChain) {
        DESERIALIZE_TRY(DeserializeChainedStruct(&record->nextInChain, buffer, size, allocator, resolver));
    }



    bool has_label = transfer->has_label;
    record->label = nullptr;
    if (has_label)
    {
        size_t stringLength = transfer->labelStrlen;
        const volatile char* stringInBuffer = nullptr;
        DESERIALIZE_TRY(GetPtrFromBuffer(buffer, size, stringLength, &stringInBuffer));

        char* copiedString = nullptr;
        DESERIALIZE_TRY(GetSpace(allocator, stringLength + 1, &copiedString));
        std::copy(stringInBuffer, stringInBuffer + stringLength, copiedString);
        copiedString[stringLength] = '\0';
        record->label = copiedString;
    }


    {
        size_t memberLength = record->entryCount;
        auto memberBuffer = reinterpret_cast<const volatile WGPUBindGroupLayoutEntryTransfer*>(buffer);
        DESERIALIZE_TRY(GetPtrFromBuffer(buffer, size, memberLength, &memberBuffer));

        WGPUBindGroupLayoutEntry* copiedMembers = nullptr;
        DESERIALIZE_TRY(GetSpace(allocator, memberLength, &copiedMembers));
        record->entries = copiedMembers;

        for (size_t i = 0; i < memberLength; ++i) {
            DESERIALIZE_TRY(WGPUBindGroupLayoutEntryDeserialize(&copiedMembers[i], &memberBuffer[i], buffer, size, allocator));
        }
    }

    return DeserializeResult::Success;
}
DAWN_UNUSED_FUNC(WGPUBindGroupLayoutDescriptorDeserialize);

        
struct WGPUBufferCopyViewTransfer {
    static_assert(1 <= 1,
                  "Record must be at most one of is_cmd, extensible, and chained.");
    bool hasNextInChain;

    WGPUTextureDataLayoutTransfer layout;
    ObjectId buffer;


};



DAWN_DECLARE_UNUSED size_t WGPUBufferCopyViewGetExtraRequiredSize(const WGPUBufferCopyView& record) {
    DAWN_UNUSED(record);

    size_t result = 0;

    if (record.nextInChain != nullptr) {
        result += GetChainedStructExtraRequiredSize(record.nextInChain);
    }


    {
        result += WGPUTextureDataLayoutGetExtraRequiredSize(record.layout);
    }
    {
    }

    return result;
}
// GetExtraRequiredSize isn't used for structures that are value members of other structures
// because we assume they cannot contain pointers themselves.
DAWN_UNUSED_FUNC(WGPUBufferCopyViewGetExtraRequiredSize);

DAWN_DECLARE_UNUSED void WGPUBufferCopyViewSerialize(const WGPUBufferCopyView& record, WGPUBufferCopyViewTransfer* transfer,
                       char** buffer, const ObjectIdProvider& provider) {
    DAWN_UNUSED(buffer);


    WGPUTextureDataLayoutSerialize(record.layout, &transfer->layout, buffer, provider);

    transfer->buffer = provider.GetId(record.buffer);


    if (record.nextInChain != nullptr) {
        transfer->hasNextInChain = true;
        SerializeChainedStruct(record.nextInChain, buffer, provider);
    } else {
        transfer->hasNextInChain = false;
    }



}
DAWN_UNUSED_FUNC(WGPUBufferCopyViewSerialize);

DAWN_DECLARE_UNUSED DeserializeResult WGPUBufferCopyViewDeserialize(WGPUBufferCopyView* record, const volatile WGPUBufferCopyViewTransfer* transfer,
                                      const volatile char** buffer, size_t* size, DeserializeAllocator* allocator, const ObjectIdResolver& resolver) {
    DAWN_UNUSED(allocator);
    DAWN_UNUSED(buffer);
    DAWN_UNUSED(size);



    DESERIALIZE_TRY(WGPUTextureDataLayoutDeserialize(&record->layout, &transfer->layout, buffer, size, allocator, resolver));
    DESERIALIZE_TRY(resolver.GetFromId(transfer->buffer, &record->buffer));

    record->nextInChain = nullptr;
    if (transfer->hasNextInChain) {
        DESERIALIZE_TRY(DeserializeChainedStruct(&record->nextInChain, buffer, size, allocator, resolver));
    }




    return DeserializeResult::Success;
}
DAWN_UNUSED_FUNC(WGPUBufferCopyViewDeserialize);

        
struct WGPUColorStateDescriptorTransfer {
    static_assert(1 <= 1,
                  "Record must be at most one of is_cmd, extensible, and chained.");
    bool hasNextInChain;

    WGPUTextureFormat format;
    WGPUBlendDescriptorTransfer alphaBlend;
    WGPUBlendDescriptorTransfer colorBlend;
    WGPUColorWriteMaskFlags writeMask;


};



DAWN_DECLARE_UNUSED size_t WGPUColorStateDescriptorGetExtraRequiredSize(const WGPUColorStateDescriptor& record) {
    DAWN_UNUSED(record);

    size_t result = 0;

    if (record.nextInChain != nullptr) {
        result += GetChainedStructExtraRequiredSize(record.nextInChain);
    }


    {
    }
    {
        result += WGPUBlendDescriptorGetExtraRequiredSize(record.alphaBlend);
    }
    {
        result += WGPUBlendDescriptorGetExtraRequiredSize(record.colorBlend);
    }
    {
    }

    return result;
}
// GetExtraRequiredSize isn't used for structures that are value members of other structures
// because we assume they cannot contain pointers themselves.
DAWN_UNUSED_FUNC(WGPUColorStateDescriptorGetExtraRequiredSize);

DAWN_DECLARE_UNUSED void WGPUColorStateDescriptorSerialize(const WGPUColorStateDescriptor& record, WGPUColorStateDescriptorTransfer* transfer,
                       char** buffer, const ObjectIdProvider& provider) {
    DAWN_UNUSED(buffer);


    transfer->format = record.format;
    WGPUBlendDescriptorSerialize(record.alphaBlend, &transfer->alphaBlend, buffer);

    WGPUBlendDescriptorSerialize(record.colorBlend, &transfer->colorBlend, buffer);

    transfer->writeMask = record.writeMask;

    if (record.nextInChain != nullptr) {
        transfer->hasNextInChain = true;
        SerializeChainedStruct(record.nextInChain, buffer, provider);
    } else {
        transfer->hasNextInChain = false;
    }



}
DAWN_UNUSED_FUNC(WGPUColorStateDescriptorSerialize);

DAWN_DECLARE_UNUSED DeserializeResult WGPUColorStateDescriptorDeserialize(WGPUColorStateDescriptor* record, const volatile WGPUColorStateDescriptorTransfer* transfer,
                                      const volatile char** buffer, size_t* size, DeserializeAllocator* allocator, const ObjectIdResolver& resolver) {
    DAWN_UNUSED(allocator);
    DAWN_UNUSED(buffer);
    DAWN_UNUSED(size);



    record->format = transfer->format;
    DESERIALIZE_TRY(WGPUBlendDescriptorDeserialize(&record->alphaBlend, &transfer->alphaBlend, buffer, size, allocator));
    DESERIALIZE_TRY(WGPUBlendDescriptorDeserialize(&record->colorBlend, &transfer->colorBlend, buffer, size, allocator));
    record->writeMask = transfer->writeMask;

    record->nextInChain = nullptr;
    if (transfer->hasNextInChain) {
        DESERIALIZE_TRY(DeserializeChainedStruct(&record->nextInChain, buffer, size, allocator, resolver));
    }




    return DeserializeResult::Success;
}
DAWN_UNUSED_FUNC(WGPUColorStateDescriptorDeserialize);

        
struct WGPUComputePipelineDescriptorTransfer {
    static_assert(1 <= 1,
                  "Record must be at most one of is_cmd, extensible, and chained.");
    bool hasNextInChain;

    ObjectId layout;
    WGPUProgrammableStageDescriptorTransfer computeStage;

    size_t labelStrlen;

    bool has_label;
};



DAWN_DECLARE_UNUSED size_t WGPUComputePipelineDescriptorGetExtraRequiredSize(const WGPUComputePipelineDescriptor& record) {
    DAWN_UNUSED(record);

    size_t result = 0;

    if (record.nextInChain != nullptr) {
        result += GetChainedStructExtraRequiredSize(record.nextInChain);
    }


    bool has_label = record.label != nullptr;
    if (has_label)
    {
    result += std::strlen(record.label);
    }

    {
    }
    {
        result += WGPUProgrammableStageDescriptorGetExtraRequiredSize(record.computeStage);
    }

    return result;
}
// GetExtraRequiredSize isn't used for structures that are value members of other structures
// because we assume they cannot contain pointers themselves.
DAWN_UNUSED_FUNC(WGPUComputePipelineDescriptorGetExtraRequiredSize);

DAWN_DECLARE_UNUSED void WGPUComputePipelineDescriptorSerialize(const WGPUComputePipelineDescriptor& record, WGPUComputePipelineDescriptorTransfer* transfer,
                       char** buffer, const ObjectIdProvider& provider) {
    DAWN_UNUSED(buffer);


    transfer->layout = provider.GetOptionalId(record.layout);

    WGPUProgrammableStageDescriptorSerialize(record.computeStage, &transfer->computeStage, buffer, provider);


    if (record.nextInChain != nullptr) {
        transfer->hasNextInChain = true;
        SerializeChainedStruct(record.nextInChain, buffer, provider);
    } else {
        transfer->hasNextInChain = false;
    }



    bool has_label = record.label != nullptr;
    transfer->has_label = has_label;
    if (has_label)
    {
    transfer->labelStrlen = std::strlen(record.label);

    memcpy(*buffer, record.label, transfer->labelStrlen);
    *buffer += transfer->labelStrlen;
    }

}
DAWN_UNUSED_FUNC(WGPUComputePipelineDescriptorSerialize);

DAWN_DECLARE_UNUSED DeserializeResult WGPUComputePipelineDescriptorDeserialize(WGPUComputePipelineDescriptor* record, const volatile WGPUComputePipelineDescriptorTransfer* transfer,
                                      const volatile char** buffer, size_t* size, DeserializeAllocator* allocator, const ObjectIdResolver& resolver) {
    DAWN_UNUSED(allocator);
    DAWN_UNUSED(buffer);
    DAWN_UNUSED(size);



    DESERIALIZE_TRY(resolver.GetOptionalFromId(transfer->layout, &record->layout));
    DESERIALIZE_TRY(WGPUProgrammableStageDescriptorDeserialize(&record->computeStage, &transfer->computeStage, buffer, size, allocator, resolver));

    record->nextInChain = nullptr;
    if (transfer->hasNextInChain) {
        DESERIALIZE_TRY(DeserializeChainedStruct(&record->nextInChain, buffer, size, allocator, resolver));
    }



    bool has_label = transfer->has_label;
    record->label = nullptr;
    if (has_label)
    {
        size_t stringLength = transfer->labelStrlen;
        const volatile char* stringInBuffer = nullptr;
        DESERIALIZE_TRY(GetPtrFromBuffer(buffer, size, stringLength, &stringInBuffer));

        char* copiedString = nullptr;
        DESERIALIZE_TRY(GetSpace(allocator, stringLength + 1, &copiedString));
        std::copy(stringInBuffer, stringInBuffer + stringLength, copiedString);
        copiedString[stringLength] = '\0';
        record->label = copiedString;
    }


    return DeserializeResult::Success;
}
DAWN_UNUSED_FUNC(WGPUComputePipelineDescriptorDeserialize);

        
struct WGPUDepthStencilStateDescriptorTransfer {
    static_assert(1 <= 1,
                  "Record must be at most one of is_cmd, extensible, and chained.");
    bool hasNextInChain;

    WGPUTextureFormat format;
    bool depthWriteEnabled;
    WGPUCompareFunction depthCompare;
    WGPUStencilStateFaceDescriptorTransfer stencilFront;
    WGPUStencilStateFaceDescriptorTransfer stencilBack;
    uint32_t stencilReadMask;
    uint32_t stencilWriteMask;


};



DAWN_DECLARE_UNUSED size_t WGPUDepthStencilStateDescriptorGetExtraRequiredSize(const WGPUDepthStencilStateDescriptor& record) {
    DAWN_UNUSED(record);

    size_t result = 0;

    if (record.nextInChain != nullptr) {
        result += GetChainedStructExtraRequiredSize(record.nextInChain);
    }


    {
    }
    {
    }
    {
    }
    {
        result += WGPUStencilStateFaceDescriptorGetExtraRequiredSize(record.stencilFront);
    }
    {
        result += WGPUStencilStateFaceDescriptorGetExtraRequiredSize(record.stencilBack);
    }
    {
    }
    {
    }

    return result;
}
// GetExtraRequiredSize isn't used for structures that are value members of other structures
// because we assume they cannot contain pointers themselves.
DAWN_UNUSED_FUNC(WGPUDepthStencilStateDescriptorGetExtraRequiredSize);

DAWN_DECLARE_UNUSED void WGPUDepthStencilStateDescriptorSerialize(const WGPUDepthStencilStateDescriptor& record, WGPUDepthStencilStateDescriptorTransfer* transfer,
                       char** buffer, const ObjectIdProvider& provider) {
    DAWN_UNUSED(buffer);


    transfer->format = record.format;
    transfer->depthWriteEnabled = record.depthWriteEnabled;
    transfer->depthCompare = record.depthCompare;
    WGPUStencilStateFaceDescriptorSerialize(record.stencilFront, &transfer->stencilFront, buffer);

    WGPUStencilStateFaceDescriptorSerialize(record.stencilBack, &transfer->stencilBack, buffer);

    transfer->stencilReadMask = record.stencilReadMask;
    transfer->stencilWriteMask = record.stencilWriteMask;

    if (record.nextInChain != nullptr) {
        transfer->hasNextInChain = true;
        SerializeChainedStruct(record.nextInChain, buffer, provider);
    } else {
        transfer->hasNextInChain = false;
    }



}
DAWN_UNUSED_FUNC(WGPUDepthStencilStateDescriptorSerialize);

DAWN_DECLARE_UNUSED DeserializeResult WGPUDepthStencilStateDescriptorDeserialize(WGPUDepthStencilStateDescriptor* record, const volatile WGPUDepthStencilStateDescriptorTransfer* transfer,
                                      const volatile char** buffer, size_t* size, DeserializeAllocator* allocator, const ObjectIdResolver& resolver) {
    DAWN_UNUSED(allocator);
    DAWN_UNUSED(buffer);
    DAWN_UNUSED(size);



    record->format = transfer->format;
    record->depthWriteEnabled = transfer->depthWriteEnabled;
    record->depthCompare = transfer->depthCompare;
    DESERIALIZE_TRY(WGPUStencilStateFaceDescriptorDeserialize(&record->stencilFront, &transfer->stencilFront, buffer, size, allocator));
    DESERIALIZE_TRY(WGPUStencilStateFaceDescriptorDeserialize(&record->stencilBack, &transfer->stencilBack, buffer, size, allocator));
    record->stencilReadMask = transfer->stencilReadMask;
    record->stencilWriteMask = transfer->stencilWriteMask;

    record->nextInChain = nullptr;
    if (transfer->hasNextInChain) {
        DESERIALIZE_TRY(DeserializeChainedStruct(&record->nextInChain, buffer, size, allocator, resolver));
    }




    return DeserializeResult::Success;
}
DAWN_UNUSED_FUNC(WGPUDepthStencilStateDescriptorDeserialize);

        
struct WGPURenderPassColorAttachmentDescriptorTransfer {
    static_assert(0 <= 1,
                  "Record must be at most one of is_cmd, extensible, and chained.");

    ObjectId attachment;
    ObjectId resolveTarget;
    WGPULoadOp loadOp;
    WGPUStoreOp storeOp;
    WGPUColorTransfer clearColor;


};



DAWN_DECLARE_UNUSED size_t WGPURenderPassColorAttachmentDescriptorGetExtraRequiredSize(const WGPURenderPassColorAttachmentDescriptor& record) {
    DAWN_UNUSED(record);

    size_t result = 0;



    {
    }
    {
    }
    {
    }
    {
    }
    {
        result += WGPUColorGetExtraRequiredSize(record.clearColor);
    }

    return result;
}
// GetExtraRequiredSize isn't used for structures that are value members of other structures
// because we assume they cannot contain pointers themselves.
DAWN_UNUSED_FUNC(WGPURenderPassColorAttachmentDescriptorGetExtraRequiredSize);

DAWN_DECLARE_UNUSED void WGPURenderPassColorAttachmentDescriptorSerialize(const WGPURenderPassColorAttachmentDescriptor& record, WGPURenderPassColorAttachmentDescriptorTransfer* transfer,
                       char** buffer, const ObjectIdProvider& provider) {
    DAWN_UNUSED(buffer);


    transfer->attachment = provider.GetId(record.attachment);

    transfer->resolveTarget = provider.GetOptionalId(record.resolveTarget);

    transfer->loadOp = record.loadOp;
    transfer->storeOp = record.storeOp;
    WGPUColorSerialize(record.clearColor, &transfer->clearColor, buffer);





}
DAWN_UNUSED_FUNC(WGPURenderPassColorAttachmentDescriptorSerialize);

DAWN_DECLARE_UNUSED DeserializeResult WGPURenderPassColorAttachmentDescriptorDeserialize(WGPURenderPassColorAttachmentDescriptor* record, const volatile WGPURenderPassColorAttachmentDescriptorTransfer* transfer,
                                      const volatile char** buffer, size_t* size, DeserializeAllocator* allocator, const ObjectIdResolver& resolver) {
    DAWN_UNUSED(allocator);
    DAWN_UNUSED(buffer);
    DAWN_UNUSED(size);



    DESERIALIZE_TRY(resolver.GetFromId(transfer->attachment, &record->attachment));
    DESERIALIZE_TRY(resolver.GetOptionalFromId(transfer->resolveTarget, &record->resolveTarget));
    record->loadOp = transfer->loadOp;
    record->storeOp = transfer->storeOp;
    DESERIALIZE_TRY(WGPUColorDeserialize(&record->clearColor, &transfer->clearColor, buffer, size, allocator));





    return DeserializeResult::Success;
}
DAWN_UNUSED_FUNC(WGPURenderPassColorAttachmentDescriptorDeserialize);

        
struct WGPURenderPipelineDescriptorDummyExtensionTransfer {
    static_assert(1 <= 1,
                  "Record must be at most one of is_cmd, extensible, and chained.");
    WGPUChainedStructTransfer chain;

    WGPUProgrammableStageDescriptorTransfer dummyStage;


};


static_assert(offsetof(WGPURenderPipelineDescriptorDummyExtensionTransfer, chain) == 0, "");

DAWN_DECLARE_UNUSED size_t WGPURenderPipelineDescriptorDummyExtensionGetExtraRequiredSize(const WGPURenderPipelineDescriptorDummyExtension& record) {
    DAWN_UNUSED(record);

    size_t result = 0;



    {
        result += WGPUProgrammableStageDescriptorGetExtraRequiredSize(record.dummyStage);
    }

    return result;
}
// GetExtraRequiredSize isn't used for structures that are value members of other structures
// because we assume they cannot contain pointers themselves.
DAWN_UNUSED_FUNC(WGPURenderPipelineDescriptorDummyExtensionGetExtraRequiredSize);

DAWN_DECLARE_UNUSED void WGPURenderPipelineDescriptorDummyExtensionSerialize(const WGPURenderPipelineDescriptorDummyExtension& record, WGPURenderPipelineDescriptorDummyExtensionTransfer* transfer,
                       char** buffer, const ObjectIdProvider& provider) {
    DAWN_UNUSED(buffer);


    WGPUProgrammableStageDescriptorSerialize(record.dummyStage, &transfer->dummyStage, buffer, provider);



    ASSERT(transfer->chain.sType == WGPUSType_RenderPipelineDescriptorDummyExtension);
    ASSERT(transfer->chain.hasNext == (record.chain.next != nullptr));


}
DAWN_UNUSED_FUNC(WGPURenderPipelineDescriptorDummyExtensionSerialize);

DAWN_DECLARE_UNUSED DeserializeResult WGPURenderPipelineDescriptorDummyExtensionDeserialize(WGPURenderPipelineDescriptorDummyExtension* record, const volatile WGPURenderPipelineDescriptorDummyExtensionTransfer* transfer,
                                      const volatile char** buffer, size_t* size, DeserializeAllocator* allocator, const ObjectIdResolver& resolver) {
    DAWN_UNUSED(allocator);
    DAWN_UNUSED(buffer);
    DAWN_UNUSED(size);



    DESERIALIZE_TRY(WGPUProgrammableStageDescriptorDeserialize(&record->dummyStage, &transfer->dummyStage, buffer, size, allocator, resolver));


    ASSERT(record->chain.sType == WGPUSType_RenderPipelineDescriptorDummyExtension);
    ASSERT(record->chain.next == nullptr);



    return DeserializeResult::Success;
}
DAWN_UNUSED_FUNC(WGPURenderPipelineDescriptorDummyExtensionDeserialize);

        
struct WGPUTextureCopyViewTransfer {
    static_assert(1 <= 1,
                  "Record must be at most one of is_cmd, extensible, and chained.");
    bool hasNextInChain;

    ObjectId texture;
    uint32_t mipLevel;
    WGPUOrigin3DTransfer origin;
    WGPUTextureAspect aspect;


};



DAWN_DECLARE_UNUSED size_t WGPUTextureCopyViewGetExtraRequiredSize(const WGPUTextureCopyView& record) {
    DAWN_UNUSED(record);

    size_t result = 0;

    if (record.nextInChain != nullptr) {
        result += GetChainedStructExtraRequiredSize(record.nextInChain);
    }


    {
    }
    {
    }
    {
        result += WGPUOrigin3DGetExtraRequiredSize(record.origin);
    }
    {
    }

    return result;
}
// GetExtraRequiredSize isn't used for structures that are value members of other structures
// because we assume they cannot contain pointers themselves.
DAWN_UNUSED_FUNC(WGPUTextureCopyViewGetExtraRequiredSize);

DAWN_DECLARE_UNUSED void WGPUTextureCopyViewSerialize(const WGPUTextureCopyView& record, WGPUTextureCopyViewTransfer* transfer,
                       char** buffer, const ObjectIdProvider& provider) {
    DAWN_UNUSED(buffer);


    transfer->texture = provider.GetId(record.texture);

    transfer->mipLevel = record.mipLevel;
    WGPUOrigin3DSerialize(record.origin, &transfer->origin, buffer);

    transfer->aspect = record.aspect;

    if (record.nextInChain != nullptr) {
        transfer->hasNextInChain = true;
        SerializeChainedStruct(record.nextInChain, buffer, provider);
    } else {
        transfer->hasNextInChain = false;
    }



}
DAWN_UNUSED_FUNC(WGPUTextureCopyViewSerialize);

DAWN_DECLARE_UNUSED DeserializeResult WGPUTextureCopyViewDeserialize(WGPUTextureCopyView* record, const volatile WGPUTextureCopyViewTransfer* transfer,
                                      const volatile char** buffer, size_t* size, DeserializeAllocator* allocator, const ObjectIdResolver& resolver) {
    DAWN_UNUSED(allocator);
    DAWN_UNUSED(buffer);
    DAWN_UNUSED(size);



    DESERIALIZE_TRY(resolver.GetFromId(transfer->texture, &record->texture));
    record->mipLevel = transfer->mipLevel;
    DESERIALIZE_TRY(WGPUOrigin3DDeserialize(&record->origin, &transfer->origin, buffer, size, allocator));
    record->aspect = transfer->aspect;

    record->nextInChain = nullptr;
    if (transfer->hasNextInChain) {
        DESERIALIZE_TRY(DeserializeChainedStruct(&record->nextInChain, buffer, size, allocator, resolver));
    }




    return DeserializeResult::Success;
}
DAWN_UNUSED_FUNC(WGPUTextureCopyViewDeserialize);

        
struct WGPUTextureDescriptorTransfer {
    static_assert(1 <= 1,
                  "Record must be at most one of is_cmd, extensible, and chained.");
    bool hasNextInChain;

    WGPUTextureUsageFlags usage;
    WGPUTextureDimension dimension;
    WGPUExtent3DTransfer size;
    WGPUTextureFormat format;
    uint32_t mipLevelCount;
    uint32_t sampleCount;

    size_t labelStrlen;

    bool has_label;
};



DAWN_DECLARE_UNUSED size_t WGPUTextureDescriptorGetExtraRequiredSize(const WGPUTextureDescriptor& record) {
    DAWN_UNUSED(record);

    size_t result = 0;

    if (record.nextInChain != nullptr) {
        result += GetChainedStructExtraRequiredSize(record.nextInChain);
    }


    bool has_label = record.label != nullptr;
    if (has_label)
    {
    result += std::strlen(record.label);
    }

    {
    }
    {
    }
    {
        result += WGPUExtent3DGetExtraRequiredSize(record.size);
    }
    {
    }
    {
    }
    {
    }

    return result;
}
// GetExtraRequiredSize isn't used for structures that are value members of other structures
// because we assume they cannot contain pointers themselves.
DAWN_UNUSED_FUNC(WGPUTextureDescriptorGetExtraRequiredSize);

DAWN_DECLARE_UNUSED void WGPUTextureDescriptorSerialize(const WGPUTextureDescriptor& record, WGPUTextureDescriptorTransfer* transfer,
                       char** buffer, const ObjectIdProvider& provider) {
    DAWN_UNUSED(buffer);


    transfer->usage = record.usage;
    transfer->dimension = record.dimension;
    WGPUExtent3DSerialize(record.size, &transfer->size, buffer);

    transfer->format = record.format;
    transfer->mipLevelCount = record.mipLevelCount;
    transfer->sampleCount = record.sampleCount;

    if (record.nextInChain != nullptr) {
        transfer->hasNextInChain = true;
        SerializeChainedStruct(record.nextInChain, buffer, provider);
    } else {
        transfer->hasNextInChain = false;
    }



    bool has_label = record.label != nullptr;
    transfer->has_label = has_label;
    if (has_label)
    {
    transfer->labelStrlen = std::strlen(record.label);

    memcpy(*buffer, record.label, transfer->labelStrlen);
    *buffer += transfer->labelStrlen;
    }

}
DAWN_UNUSED_FUNC(WGPUTextureDescriptorSerialize);

DAWN_DECLARE_UNUSED DeserializeResult WGPUTextureDescriptorDeserialize(WGPUTextureDescriptor* record, const volatile WGPUTextureDescriptorTransfer* transfer,
                                      const volatile char** buffer, size_t* size, DeserializeAllocator* allocator, const ObjectIdResolver& resolver) {
    DAWN_UNUSED(allocator);
    DAWN_UNUSED(buffer);
    DAWN_UNUSED(size);



    record->usage = transfer->usage;
    record->dimension = transfer->dimension;
    DESERIALIZE_TRY(WGPUExtent3DDeserialize(&record->size, &transfer->size, buffer, size, allocator));
    record->format = transfer->format;
    record->mipLevelCount = transfer->mipLevelCount;
    record->sampleCount = transfer->sampleCount;

    record->nextInChain = nullptr;
    if (transfer->hasNextInChain) {
        DESERIALIZE_TRY(DeserializeChainedStruct(&record->nextInChain, buffer, size, allocator, resolver));
    }



    bool has_label = transfer->has_label;
    record->label = nullptr;
    if (has_label)
    {
        size_t stringLength = transfer->labelStrlen;
        const volatile char* stringInBuffer = nullptr;
        DESERIALIZE_TRY(GetPtrFromBuffer(buffer, size, stringLength, &stringInBuffer));

        char* copiedString = nullptr;
        DESERIALIZE_TRY(GetSpace(allocator, stringLength + 1, &copiedString));
        std::copy(stringInBuffer, stringInBuffer + stringLength, copiedString);
        copiedString[stringLength] = '\0';
        record->label = copiedString;
    }


    return DeserializeResult::Success;
}
DAWN_UNUSED_FUNC(WGPUTextureDescriptorDeserialize);

        
struct WGPUVertexBufferLayoutDescriptorTransfer {
    static_assert(0 <= 1,
                  "Record must be at most one of is_cmd, extensible, and chained.");

    uint64_t arrayStride;
    WGPUInputStepMode stepMode;
    uint32_t attributeCount;


};



DAWN_DECLARE_UNUSED size_t WGPUVertexBufferLayoutDescriptorGetExtraRequiredSize(const WGPUVertexBufferLayoutDescriptor& record) {
    DAWN_UNUSED(record);

    size_t result = 0;



    {
    }
    {
    }
    {
    }
    {
        size_t memberLength = record.attributeCount;
        result += memberLength * sizeof(WGPUVertexAttributeDescriptorTransfer);
        for (size_t i = 0; i < memberLength; ++i) {
            
            result += WGPUVertexAttributeDescriptorGetExtraRequiredSize(record.attributes[i]);
        }
    }

    return result;
}
// GetExtraRequiredSize isn't used for structures that are value members of other structures
// because we assume they cannot contain pointers themselves.
DAWN_UNUSED_FUNC(WGPUVertexBufferLayoutDescriptorGetExtraRequiredSize);

DAWN_DECLARE_UNUSED void WGPUVertexBufferLayoutDescriptorSerialize(const WGPUVertexBufferLayoutDescriptor& record, WGPUVertexBufferLayoutDescriptorTransfer* transfer,
                       char** buffer) {
    DAWN_UNUSED(buffer);


    transfer->arrayStride = record.arrayStride;
    transfer->stepMode = record.stepMode;
    transfer->attributeCount = record.attributeCount;





    {
        size_t memberLength = record.attributeCount;
        auto memberBuffer = reinterpret_cast<WGPUVertexAttributeDescriptorTransfer*>(*buffer);
        *buffer += memberLength * sizeof(WGPUVertexAttributeDescriptorTransfer);

        for (size_t i = 0; i < memberLength; ++i) {
            WGPUVertexAttributeDescriptorSerialize(record.attributes[i], &memberBuffer[i], buffer);

        }
    }
}
DAWN_UNUSED_FUNC(WGPUVertexBufferLayoutDescriptorSerialize);

DAWN_DECLARE_UNUSED DeserializeResult WGPUVertexBufferLayoutDescriptorDeserialize(WGPUVertexBufferLayoutDescriptor* record, const volatile WGPUVertexBufferLayoutDescriptorTransfer* transfer,
                                      const volatile char** buffer, size_t* size, DeserializeAllocator* allocator) {
    DAWN_UNUSED(allocator);
    DAWN_UNUSED(buffer);
    DAWN_UNUSED(size);



    record->arrayStride = transfer->arrayStride;
    record->stepMode = transfer->stepMode;
    record->attributeCount = transfer->attributeCount;





    {
        size_t memberLength = record->attributeCount;
        auto memberBuffer = reinterpret_cast<const volatile WGPUVertexAttributeDescriptorTransfer*>(buffer);
        DESERIALIZE_TRY(GetPtrFromBuffer(buffer, size, memberLength, &memberBuffer));

        WGPUVertexAttributeDescriptor* copiedMembers = nullptr;
        DESERIALIZE_TRY(GetSpace(allocator, memberLength, &copiedMembers));
        record->attributes = copiedMembers;

        for (size_t i = 0; i < memberLength; ++i) {
            DESERIALIZE_TRY(WGPUVertexAttributeDescriptorDeserialize(&copiedMembers[i], &memberBuffer[i], buffer, size, allocator));
        }
    }

    return DeserializeResult::Success;
}
DAWN_UNUSED_FUNC(WGPUVertexBufferLayoutDescriptorDeserialize);

        
struct WGPURenderPassDescriptorTransfer {
    static_assert(1 <= 1,
                  "Record must be at most one of is_cmd, extensible, and chained.");
    bool hasNextInChain;

    uint32_t colorAttachmentCount;
    ObjectId occlusionQuerySet;

    size_t labelStrlen;

    bool has_label;
    bool has_depthStencilAttachment;
};



DAWN_DECLARE_UNUSED size_t WGPURenderPassDescriptorGetExtraRequiredSize(const WGPURenderPassDescriptor& record) {
    DAWN_UNUSED(record);

    size_t result = 0;

    if (record.nextInChain != nullptr) {
        result += GetChainedStructExtraRequiredSize(record.nextInChain);
    }


    bool has_label = record.label != nullptr;
    if (has_label)
    {
    result += std::strlen(record.label);
    }

    {
    }
    {
        size_t memberLength = record.colorAttachmentCount;
        result += memberLength * sizeof(WGPURenderPassColorAttachmentDescriptorTransfer);
        for (size_t i = 0; i < memberLength; ++i) {
            
            result += WGPURenderPassColorAttachmentDescriptorGetExtraRequiredSize(record.colorAttachments[i]);
        }
    }
    if (record.depthStencilAttachment != nullptr)
    {
        size_t memberLength = 1;
        result += memberLength * sizeof(WGPURenderPassDepthStencilAttachmentDescriptorTransfer);
        for (size_t i = 0; i < memberLength; ++i) {
            
            result += WGPURenderPassDepthStencilAttachmentDescriptorGetExtraRequiredSize(record.depthStencilAttachment[i]);
        }
    }
    {
    }

    return result;
}
// GetExtraRequiredSize isn't used for structures that are value members of other structures
// because we assume they cannot contain pointers themselves.
DAWN_UNUSED_FUNC(WGPURenderPassDescriptorGetExtraRequiredSize);

DAWN_DECLARE_UNUSED void WGPURenderPassDescriptorSerialize(const WGPURenderPassDescriptor& record, WGPURenderPassDescriptorTransfer* transfer,
                       char** buffer, const ObjectIdProvider& provider) {
    DAWN_UNUSED(buffer);


    transfer->colorAttachmentCount = record.colorAttachmentCount;
    transfer->occlusionQuerySet = provider.GetOptionalId(record.occlusionQuerySet);


    if (record.nextInChain != nullptr) {
        transfer->hasNextInChain = true;
        SerializeChainedStruct(record.nextInChain, buffer, provider);
    } else {
        transfer->hasNextInChain = false;
    }



    bool has_label = record.label != nullptr;
    transfer->has_label = has_label;
    if (has_label)
    {
    transfer->labelStrlen = std::strlen(record.label);

    memcpy(*buffer, record.label, transfer->labelStrlen);
    *buffer += transfer->labelStrlen;
    }


    {
        size_t memberLength = record.colorAttachmentCount;
        auto memberBuffer = reinterpret_cast<WGPURenderPassColorAttachmentDescriptorTransfer*>(*buffer);
        *buffer += memberLength * sizeof(WGPURenderPassColorAttachmentDescriptorTransfer);

        for (size_t i = 0; i < memberLength; ++i) {
            WGPURenderPassColorAttachmentDescriptorSerialize(record.colorAttachments[i], &memberBuffer[i], buffer, provider);

        }
    }

    bool has_depthStencilAttachment = record.depthStencilAttachment != nullptr;
    transfer->has_depthStencilAttachment = has_depthStencilAttachment;
    if (has_depthStencilAttachment)
    {
        size_t memberLength = 1;
        auto memberBuffer = reinterpret_cast<WGPURenderPassDepthStencilAttachmentDescriptorTransfer*>(*buffer);
        *buffer += memberLength * sizeof(WGPURenderPassDepthStencilAttachmentDescriptorTransfer);

        for (size_t i = 0; i < memberLength; ++i) {
            WGPURenderPassDepthStencilAttachmentDescriptorSerialize(record.depthStencilAttachment[i], &memberBuffer[i], buffer, provider);

        }
    }
}
DAWN_UNUSED_FUNC(WGPURenderPassDescriptorSerialize);

DAWN_DECLARE_UNUSED DeserializeResult WGPURenderPassDescriptorDeserialize(WGPURenderPassDescriptor* record, const volatile WGPURenderPassDescriptorTransfer* transfer,
                                      const volatile char** buffer, size_t* size, DeserializeAllocator* allocator, const ObjectIdResolver& resolver) {
    DAWN_UNUSED(allocator);
    DAWN_UNUSED(buffer);
    DAWN_UNUSED(size);



    record->colorAttachmentCount = transfer->colorAttachmentCount;
    DESERIALIZE_TRY(resolver.GetOptionalFromId(transfer->occlusionQuerySet, &record->occlusionQuerySet));

    record->nextInChain = nullptr;
    if (transfer->hasNextInChain) {
        DESERIALIZE_TRY(DeserializeChainedStruct(&record->nextInChain, buffer, size, allocator, resolver));
    }



    bool has_label = transfer->has_label;
    record->label = nullptr;
    if (has_label)
    {
        size_t stringLength = transfer->labelStrlen;
        const volatile char* stringInBuffer = nullptr;
        DESERIALIZE_TRY(GetPtrFromBuffer(buffer, size, stringLength, &stringInBuffer));

        char* copiedString = nullptr;
        DESERIALIZE_TRY(GetSpace(allocator, stringLength + 1, &copiedString));
        std::copy(stringInBuffer, stringInBuffer + stringLength, copiedString);
        copiedString[stringLength] = '\0';
        record->label = copiedString;
    }


    {
        size_t memberLength = record->colorAttachmentCount;
        auto memberBuffer = reinterpret_cast<const volatile WGPURenderPassColorAttachmentDescriptorTransfer*>(buffer);
        DESERIALIZE_TRY(GetPtrFromBuffer(buffer, size, memberLength, &memberBuffer));

        WGPURenderPassColorAttachmentDescriptor* copiedMembers = nullptr;
        DESERIALIZE_TRY(GetSpace(allocator, memberLength, &copiedMembers));
        record->colorAttachments = copiedMembers;

        for (size_t i = 0; i < memberLength; ++i) {
            DESERIALIZE_TRY(WGPURenderPassColorAttachmentDescriptorDeserialize(&copiedMembers[i], &memberBuffer[i], buffer, size, allocator, resolver));
        }
    }

    bool has_depthStencilAttachment = transfer->has_depthStencilAttachment;
    record->depthStencilAttachment = nullptr;
    if (has_depthStencilAttachment)
    {
        size_t memberLength = 1;
        auto memberBuffer = reinterpret_cast<const volatile WGPURenderPassDepthStencilAttachmentDescriptorTransfer*>(buffer);
        DESERIALIZE_TRY(GetPtrFromBuffer(buffer, size, memberLength, &memberBuffer));

        WGPURenderPassDepthStencilAttachmentDescriptor* copiedMembers = nullptr;
        DESERIALIZE_TRY(GetSpace(allocator, memberLength, &copiedMembers));
        record->depthStencilAttachment = copiedMembers;

        for (size_t i = 0; i < memberLength; ++i) {
            DESERIALIZE_TRY(WGPURenderPassDepthStencilAttachmentDescriptorDeserialize(&copiedMembers[i], &memberBuffer[i], buffer, size, allocator, resolver));
        }
    }

    return DeserializeResult::Success;
}
DAWN_UNUSED_FUNC(WGPURenderPassDescriptorDeserialize);

        
struct WGPUVertexStateDescriptorTransfer {
    static_assert(1 <= 1,
                  "Record must be at most one of is_cmd, extensible, and chained.");
    bool hasNextInChain;

    WGPUIndexFormat indexFormat;
    uint32_t vertexBufferCount;


};



DAWN_DECLARE_UNUSED size_t WGPUVertexStateDescriptorGetExtraRequiredSize(const WGPUVertexStateDescriptor& record) {
    DAWN_UNUSED(record);

    size_t result = 0;

    if (record.nextInChain != nullptr) {
        result += GetChainedStructExtraRequiredSize(record.nextInChain);
    }


    {
    }
    {
    }
    {
        size_t memberLength = record.vertexBufferCount;
        result += memberLength * sizeof(WGPUVertexBufferLayoutDescriptorTransfer);
        for (size_t i = 0; i < memberLength; ++i) {
            
            result += WGPUVertexBufferLayoutDescriptorGetExtraRequiredSize(record.vertexBuffers[i]);
        }
    }

    return result;
}
// GetExtraRequiredSize isn't used for structures that are value members of other structures
// because we assume they cannot contain pointers themselves.
DAWN_UNUSED_FUNC(WGPUVertexStateDescriptorGetExtraRequiredSize);

DAWN_DECLARE_UNUSED void WGPUVertexStateDescriptorSerialize(const WGPUVertexStateDescriptor& record, WGPUVertexStateDescriptorTransfer* transfer,
                       char** buffer, const ObjectIdProvider& provider) {
    DAWN_UNUSED(buffer);


    transfer->indexFormat = record.indexFormat;
    transfer->vertexBufferCount = record.vertexBufferCount;

    if (record.nextInChain != nullptr) {
        transfer->hasNextInChain = true;
        SerializeChainedStruct(record.nextInChain, buffer, provider);
    } else {
        transfer->hasNextInChain = false;
    }




    {
        size_t memberLength = record.vertexBufferCount;
        auto memberBuffer = reinterpret_cast<WGPUVertexBufferLayoutDescriptorTransfer*>(*buffer);
        *buffer += memberLength * sizeof(WGPUVertexBufferLayoutDescriptorTransfer);

        for (size_t i = 0; i < memberLength; ++i) {
            WGPUVertexBufferLayoutDescriptorSerialize(record.vertexBuffers[i], &memberBuffer[i], buffer);

        }
    }
}
DAWN_UNUSED_FUNC(WGPUVertexStateDescriptorSerialize);

DAWN_DECLARE_UNUSED DeserializeResult WGPUVertexStateDescriptorDeserialize(WGPUVertexStateDescriptor* record, const volatile WGPUVertexStateDescriptorTransfer* transfer,
                                      const volatile char** buffer, size_t* size, DeserializeAllocator* allocator, const ObjectIdResolver& resolver) {
    DAWN_UNUSED(allocator);
    DAWN_UNUSED(buffer);
    DAWN_UNUSED(size);



    record->indexFormat = transfer->indexFormat;
    record->vertexBufferCount = transfer->vertexBufferCount;

    record->nextInChain = nullptr;
    if (transfer->hasNextInChain) {
        DESERIALIZE_TRY(DeserializeChainedStruct(&record->nextInChain, buffer, size, allocator, resolver));
    }




    {
        size_t memberLength = record->vertexBufferCount;
        auto memberBuffer = reinterpret_cast<const volatile WGPUVertexBufferLayoutDescriptorTransfer*>(buffer);
        DESERIALIZE_TRY(GetPtrFromBuffer(buffer, size, memberLength, &memberBuffer));

        WGPUVertexBufferLayoutDescriptor* copiedMembers = nullptr;
        DESERIALIZE_TRY(GetSpace(allocator, memberLength, &copiedMembers));
        record->vertexBuffers = copiedMembers;

        for (size_t i = 0; i < memberLength; ++i) {
            DESERIALIZE_TRY(WGPUVertexBufferLayoutDescriptorDeserialize(&copiedMembers[i], &memberBuffer[i], buffer, size, allocator));
        }
    }

    return DeserializeResult::Success;
}
DAWN_UNUSED_FUNC(WGPUVertexStateDescriptorDeserialize);

        
struct WGPURenderPipelineDescriptorTransfer {
    static_assert(1 <= 1,
                  "Record must be at most one of is_cmd, extensible, and chained.");
    bool hasNextInChain;

    ObjectId layout;
    WGPUProgrammableStageDescriptorTransfer vertexStage;
    WGPUPrimitiveTopology primitiveTopology;
    uint32_t sampleCount;
    uint32_t colorStateCount;
    uint32_t sampleMask;
    bool alphaToCoverageEnabled;

    size_t labelStrlen;

    bool has_label;
    bool has_fragmentStage;
    bool has_vertexState;
    bool has_rasterizationState;
    bool has_depthStencilState;
};



DAWN_DECLARE_UNUSED size_t WGPURenderPipelineDescriptorGetExtraRequiredSize(const WGPURenderPipelineDescriptor& record) {
    DAWN_UNUSED(record);

    size_t result = 0;

    if (record.nextInChain != nullptr) {
        result += GetChainedStructExtraRequiredSize(record.nextInChain);
    }


    bool has_label = record.label != nullptr;
    if (has_label)
    {
    result += std::strlen(record.label);
    }

    {
    }
    {
        result += WGPUProgrammableStageDescriptorGetExtraRequiredSize(record.vertexStage);
    }
    if (record.fragmentStage != nullptr)
    {
        size_t memberLength = 1;
        result += memberLength * sizeof(WGPUProgrammableStageDescriptorTransfer);
        for (size_t i = 0; i < memberLength; ++i) {
            
            result += WGPUProgrammableStageDescriptorGetExtraRequiredSize(record.fragmentStage[i]);
        }
    }
    if (record.vertexState != nullptr)
    {
        size_t memberLength = 1;
        result += memberLength * sizeof(WGPUVertexStateDescriptorTransfer);
        for (size_t i = 0; i < memberLength; ++i) {
            
            result += WGPUVertexStateDescriptorGetExtraRequiredSize(record.vertexState[i]);
        }
    }
    {
    }
    if (record.rasterizationState != nullptr)
    {
        size_t memberLength = 1;
        result += memberLength * sizeof(WGPURasterizationStateDescriptorTransfer);
        for (size_t i = 0; i < memberLength; ++i) {
            
            result += WGPURasterizationStateDescriptorGetExtraRequiredSize(record.rasterizationState[i]);
        }
    }
    {
    }
    if (record.depthStencilState != nullptr)
    {
        size_t memberLength = 1;
        result += memberLength * sizeof(WGPUDepthStencilStateDescriptorTransfer);
        for (size_t i = 0; i < memberLength; ++i) {
            
            result += WGPUDepthStencilStateDescriptorGetExtraRequiredSize(record.depthStencilState[i]);
        }
    }
    {
    }
    {
        size_t memberLength = record.colorStateCount;
        result += memberLength * sizeof(WGPUColorStateDescriptorTransfer);
        for (size_t i = 0; i < memberLength; ++i) {
            
            result += WGPUColorStateDescriptorGetExtraRequiredSize(record.colorStates[i]);
        }
    }
    {
    }
    {
    }

    return result;
}
// GetExtraRequiredSize isn't used for structures that are value members of other structures
// because we assume they cannot contain pointers themselves.
DAWN_UNUSED_FUNC(WGPURenderPipelineDescriptorGetExtraRequiredSize);

DAWN_DECLARE_UNUSED void WGPURenderPipelineDescriptorSerialize(const WGPURenderPipelineDescriptor& record, WGPURenderPipelineDescriptorTransfer* transfer,
                       char** buffer, const ObjectIdProvider& provider) {
    DAWN_UNUSED(buffer);


    transfer->layout = provider.GetOptionalId(record.layout);

    WGPUProgrammableStageDescriptorSerialize(record.vertexStage, &transfer->vertexStage, buffer, provider);

    transfer->primitiveTopology = record.primitiveTopology;
    transfer->sampleCount = record.sampleCount;
    transfer->colorStateCount = record.colorStateCount;
    transfer->sampleMask = record.sampleMask;
    transfer->alphaToCoverageEnabled = record.alphaToCoverageEnabled;

    if (record.nextInChain != nullptr) {
        transfer->hasNextInChain = true;
        SerializeChainedStruct(record.nextInChain, buffer, provider);
    } else {
        transfer->hasNextInChain = false;
    }



    bool has_label = record.label != nullptr;
    transfer->has_label = has_label;
    if (has_label)
    {
    transfer->labelStrlen = std::strlen(record.label);

    memcpy(*buffer, record.label, transfer->labelStrlen);
    *buffer += transfer->labelStrlen;
    }


    bool has_fragmentStage = record.fragmentStage != nullptr;
    transfer->has_fragmentStage = has_fragmentStage;
    if (has_fragmentStage)
    {
        size_t memberLength = 1;
        auto memberBuffer = reinterpret_cast<WGPUProgrammableStageDescriptorTransfer*>(*buffer);
        *buffer += memberLength * sizeof(WGPUProgrammableStageDescriptorTransfer);

        for (size_t i = 0; i < memberLength; ++i) {
            WGPUProgrammableStageDescriptorSerialize(record.fragmentStage[i], &memberBuffer[i], buffer, provider);

        }
    }

    bool has_vertexState = record.vertexState != nullptr;
    transfer->has_vertexState = has_vertexState;
    if (has_vertexState)
    {
        size_t memberLength = 1;
        auto memberBuffer = reinterpret_cast<WGPUVertexStateDescriptorTransfer*>(*buffer);
        *buffer += memberLength * sizeof(WGPUVertexStateDescriptorTransfer);

        for (size_t i = 0; i < memberLength; ++i) {
            WGPUVertexStateDescriptorSerialize(record.vertexState[i], &memberBuffer[i], buffer, provider);

        }
    }

    bool has_rasterizationState = record.rasterizationState != nullptr;
    transfer->has_rasterizationState = has_rasterizationState;
    if (has_rasterizationState)
    {
        size_t memberLength = 1;
        auto memberBuffer = reinterpret_cast<WGPURasterizationStateDescriptorTransfer*>(*buffer);
        *buffer += memberLength * sizeof(WGPURasterizationStateDescriptorTransfer);

        for (size_t i = 0; i < memberLength; ++i) {
            WGPURasterizationStateDescriptorSerialize(record.rasterizationState[i], &memberBuffer[i], buffer, provider);

        }
    }

    bool has_depthStencilState = record.depthStencilState != nullptr;
    transfer->has_depthStencilState = has_depthStencilState;
    if (has_depthStencilState)
    {
        size_t memberLength = 1;
        auto memberBuffer = reinterpret_cast<WGPUDepthStencilStateDescriptorTransfer*>(*buffer);
        *buffer += memberLength * sizeof(WGPUDepthStencilStateDescriptorTransfer);

        for (size_t i = 0; i < memberLength; ++i) {
            WGPUDepthStencilStateDescriptorSerialize(record.depthStencilState[i], &memberBuffer[i], buffer, provider);

        }
    }

    {
        size_t memberLength = record.colorStateCount;
        auto memberBuffer = reinterpret_cast<WGPUColorStateDescriptorTransfer*>(*buffer);
        *buffer += memberLength * sizeof(WGPUColorStateDescriptorTransfer);

        for (size_t i = 0; i < memberLength; ++i) {
            WGPUColorStateDescriptorSerialize(record.colorStates[i], &memberBuffer[i], buffer, provider);

        }
    }
}
DAWN_UNUSED_FUNC(WGPURenderPipelineDescriptorSerialize);

DAWN_DECLARE_UNUSED DeserializeResult WGPURenderPipelineDescriptorDeserialize(WGPURenderPipelineDescriptor* record, const volatile WGPURenderPipelineDescriptorTransfer* transfer,
                                      const volatile char** buffer, size_t* size, DeserializeAllocator* allocator, const ObjectIdResolver& resolver) {
    DAWN_UNUSED(allocator);
    DAWN_UNUSED(buffer);
    DAWN_UNUSED(size);



    DESERIALIZE_TRY(resolver.GetOptionalFromId(transfer->layout, &record->layout));
    DESERIALIZE_TRY(WGPUProgrammableStageDescriptorDeserialize(&record->vertexStage, &transfer->vertexStage, buffer, size, allocator, resolver));
    record->primitiveTopology = transfer->primitiveTopology;
    record->sampleCount = transfer->sampleCount;
    record->colorStateCount = transfer->colorStateCount;
    record->sampleMask = transfer->sampleMask;
    record->alphaToCoverageEnabled = transfer->alphaToCoverageEnabled;

    record->nextInChain = nullptr;
    if (transfer->hasNextInChain) {
        DESERIALIZE_TRY(DeserializeChainedStruct(&record->nextInChain, buffer, size, allocator, resolver));
    }



    bool has_label = transfer->has_label;
    record->label = nullptr;
    if (has_label)
    {
        size_t stringLength = transfer->labelStrlen;
        const volatile char* stringInBuffer = nullptr;
        DESERIALIZE_TRY(GetPtrFromBuffer(buffer, size, stringLength, &stringInBuffer));

        char* copiedString = nullptr;
        DESERIALIZE_TRY(GetSpace(allocator, stringLength + 1, &copiedString));
        std::copy(stringInBuffer, stringInBuffer + stringLength, copiedString);
        copiedString[stringLength] = '\0';
        record->label = copiedString;
    }


    bool has_fragmentStage = transfer->has_fragmentStage;
    record->fragmentStage = nullptr;
    if (has_fragmentStage)
    {
        size_t memberLength = 1;
        auto memberBuffer = reinterpret_cast<const volatile WGPUProgrammableStageDescriptorTransfer*>(buffer);
        DESERIALIZE_TRY(GetPtrFromBuffer(buffer, size, memberLength, &memberBuffer));

        WGPUProgrammableStageDescriptor* copiedMembers = nullptr;
        DESERIALIZE_TRY(GetSpace(allocator, memberLength, &copiedMembers));
        record->fragmentStage = copiedMembers;

        for (size_t i = 0; i < memberLength; ++i) {
            DESERIALIZE_TRY(WGPUProgrammableStageDescriptorDeserialize(&copiedMembers[i], &memberBuffer[i], buffer, size, allocator, resolver));
        }
    }

    bool has_vertexState = transfer->has_vertexState;
    record->vertexState = nullptr;
    if (has_vertexState)
    {
        size_t memberLength = 1;
        auto memberBuffer = reinterpret_cast<const volatile WGPUVertexStateDescriptorTransfer*>(buffer);
        DESERIALIZE_TRY(GetPtrFromBuffer(buffer, size, memberLength, &memberBuffer));

        WGPUVertexStateDescriptor* copiedMembers = nullptr;
        DESERIALIZE_TRY(GetSpace(allocator, memberLength, &copiedMembers));
        record->vertexState = copiedMembers;

        for (size_t i = 0; i < memberLength; ++i) {
            DESERIALIZE_TRY(WGPUVertexStateDescriptorDeserialize(&copiedMembers[i], &memberBuffer[i], buffer, size, allocator, resolver));
        }
    }

    bool has_rasterizationState = transfer->has_rasterizationState;
    record->rasterizationState = nullptr;
    if (has_rasterizationState)
    {
        size_t memberLength = 1;
        auto memberBuffer = reinterpret_cast<const volatile WGPURasterizationStateDescriptorTransfer*>(buffer);
        DESERIALIZE_TRY(GetPtrFromBuffer(buffer, size, memberLength, &memberBuffer));

        WGPURasterizationStateDescriptor* copiedMembers = nullptr;
        DESERIALIZE_TRY(GetSpace(allocator, memberLength, &copiedMembers));
        record->rasterizationState = copiedMembers;

        for (size_t i = 0; i < memberLength; ++i) {
            DESERIALIZE_TRY(WGPURasterizationStateDescriptorDeserialize(&copiedMembers[i], &memberBuffer[i], buffer, size, allocator, resolver));
        }
    }

    bool has_depthStencilState = transfer->has_depthStencilState;
    record->depthStencilState = nullptr;
    if (has_depthStencilState)
    {
        size_t memberLength = 1;
        auto memberBuffer = reinterpret_cast<const volatile WGPUDepthStencilStateDescriptorTransfer*>(buffer);
        DESERIALIZE_TRY(GetPtrFromBuffer(buffer, size, memberLength, &memberBuffer));

        WGPUDepthStencilStateDescriptor* copiedMembers = nullptr;
        DESERIALIZE_TRY(GetSpace(allocator, memberLength, &copiedMembers));
        record->depthStencilState = copiedMembers;

        for (size_t i = 0; i < memberLength; ++i) {
            DESERIALIZE_TRY(WGPUDepthStencilStateDescriptorDeserialize(&copiedMembers[i], &memberBuffer[i], buffer, size, allocator, resolver));
        }
    }

    {
        size_t memberLength = record->colorStateCount;
        auto memberBuffer = reinterpret_cast<const volatile WGPUColorStateDescriptorTransfer*>(buffer);
        DESERIALIZE_TRY(GetPtrFromBuffer(buffer, size, memberLength, &memberBuffer));

        WGPUColorStateDescriptor* copiedMembers = nullptr;
        DESERIALIZE_TRY(GetSpace(allocator, memberLength, &copiedMembers));
        record->colorStates = copiedMembers;

        for (size_t i = 0; i < memberLength; ++i) {
            DESERIALIZE_TRY(WGPUColorStateDescriptorDeserialize(&copiedMembers[i], &memberBuffer[i], buffer, size, allocator, resolver));
        }
    }

    return DeserializeResult::Success;
}
DAWN_UNUSED_FUNC(WGPURenderPipelineDescriptorDeserialize);


        size_t GetChainedStructExtraRequiredSize(const WGPUChainedStruct* chainedStruct) {
            ASSERT(chainedStruct != nullptr);
            size_t result = 0;
            while (chainedStruct != nullptr) {
                switch (chainedStruct->sType) {
                    case WGPUSType_SurfaceDescriptorFromCanvasHTMLSelector: {
                        const auto& typedStruct = *reinterpret_cast<WGPUSurfaceDescriptorFromCanvasHTMLSelector const *>(chainedStruct);
                        result += sizeof(WGPUSurfaceDescriptorFromCanvasHTMLSelectorTransfer);
                        result += WGPUSurfaceDescriptorFromCanvasHTMLSelectorGetExtraRequiredSize(typedStruct);
                        chainedStruct = typedStruct.chain.next;
                        break;
                    }
                    case WGPUSType_ShaderModuleSPIRVDescriptor: {
                        const auto& typedStruct = *reinterpret_cast<WGPUShaderModuleSPIRVDescriptor const *>(chainedStruct);
                        result += sizeof(WGPUShaderModuleSPIRVDescriptorTransfer);
                        result += WGPUShaderModuleSPIRVDescriptorGetExtraRequiredSize(typedStruct);
                        chainedStruct = typedStruct.chain.next;
                        break;
                    }
                    case WGPUSType_ShaderModuleWGSLDescriptor: {
                        const auto& typedStruct = *reinterpret_cast<WGPUShaderModuleWGSLDescriptor const *>(chainedStruct);
                        result += sizeof(WGPUShaderModuleWGSLDescriptorTransfer);
                        result += WGPUShaderModuleWGSLDescriptorGetExtraRequiredSize(typedStruct);
                        chainedStruct = typedStruct.chain.next;
                        break;
                    }
                    case WGPUSType_SamplerDescriptorDummyAnisotropicFiltering: {
                        const auto& typedStruct = *reinterpret_cast<WGPUSamplerDescriptorDummyAnisotropicFiltering const *>(chainedStruct);
                        result += sizeof(WGPUSamplerDescriptorDummyAnisotropicFilteringTransfer);
                        result += WGPUSamplerDescriptorDummyAnisotropicFilteringGetExtraRequiredSize(typedStruct);
                        chainedStruct = typedStruct.chain.next;
                        break;
                    }
                    case WGPUSType_RenderPipelineDescriptorDummyExtension: {
                        const auto& typedStruct = *reinterpret_cast<WGPURenderPipelineDescriptorDummyExtension const *>(chainedStruct);
                        result += sizeof(WGPURenderPipelineDescriptorDummyExtensionTransfer);
                        result += WGPURenderPipelineDescriptorDummyExtensionGetExtraRequiredSize(typedStruct);
                        chainedStruct = typedStruct.chain.next;
                        break;
                    }
                    default:
                        // Invalid enum. Reserve space just for the transfer header (sType and hasNext).
                        // Stop iterating because this is an error.
                        // TODO(crbug.com/dawn/369): Unknown sTypes are silently discarded.
                        ASSERT(chainedStruct->sType == WGPUSType_Invalid);
                        result += sizeof(WGPUChainedStructTransfer);
                        return result;
                }
            }
            return result;
        }

        void SerializeChainedStruct(WGPUChainedStruct const* chainedStruct,
                                    char** buffer,
                                    const ObjectIdProvider& provider) {
            ASSERT(chainedStruct != nullptr);
            ASSERT(buffer != nullptr);
            do {
                switch (chainedStruct->sType) {
                    case WGPUSType_SurfaceDescriptorFromCanvasHTMLSelector: {

                        auto* transfer = reinterpret_cast<WGPUSurfaceDescriptorFromCanvasHTMLSelectorTransfer*>(*buffer);
                        transfer->chain.sType = chainedStruct->sType;
                        transfer->chain.hasNext = chainedStruct->next != nullptr;

                        *buffer += sizeof(WGPUSurfaceDescriptorFromCanvasHTMLSelectorTransfer);
                        WGPUSurfaceDescriptorFromCanvasHTMLSelectorSerialize(*reinterpret_cast<WGPUSurfaceDescriptorFromCanvasHTMLSelector const*>(chainedStruct), transfer, buffer, provider);

                        chainedStruct = chainedStruct->next;
                    } break;
                    case WGPUSType_ShaderModuleSPIRVDescriptor: {

                        auto* transfer = reinterpret_cast<WGPUShaderModuleSPIRVDescriptorTransfer*>(*buffer);
                        transfer->chain.sType = chainedStruct->sType;
                        transfer->chain.hasNext = chainedStruct->next != nullptr;

                        *buffer += sizeof(WGPUShaderModuleSPIRVDescriptorTransfer);
                        WGPUShaderModuleSPIRVDescriptorSerialize(*reinterpret_cast<WGPUShaderModuleSPIRVDescriptor const*>(chainedStruct), transfer, buffer, provider);

                        chainedStruct = chainedStruct->next;
                    } break;
                    case WGPUSType_ShaderModuleWGSLDescriptor: {

                        auto* transfer = reinterpret_cast<WGPUShaderModuleWGSLDescriptorTransfer*>(*buffer);
                        transfer->chain.sType = chainedStruct->sType;
                        transfer->chain.hasNext = chainedStruct->next != nullptr;

                        *buffer += sizeof(WGPUShaderModuleWGSLDescriptorTransfer);
                        WGPUShaderModuleWGSLDescriptorSerialize(*reinterpret_cast<WGPUShaderModuleWGSLDescriptor const*>(chainedStruct), transfer, buffer, provider);

                        chainedStruct = chainedStruct->next;
                    } break;
                    case WGPUSType_SamplerDescriptorDummyAnisotropicFiltering: {

                        auto* transfer = reinterpret_cast<WGPUSamplerDescriptorDummyAnisotropicFilteringTransfer*>(*buffer);
                        transfer->chain.sType = chainedStruct->sType;
                        transfer->chain.hasNext = chainedStruct->next != nullptr;

                        *buffer += sizeof(WGPUSamplerDescriptorDummyAnisotropicFilteringTransfer);
                        WGPUSamplerDescriptorDummyAnisotropicFilteringSerialize(*reinterpret_cast<WGPUSamplerDescriptorDummyAnisotropicFiltering const*>(chainedStruct), transfer, buffer, provider);

                        chainedStruct = chainedStruct->next;
                    } break;
                    case WGPUSType_RenderPipelineDescriptorDummyExtension: {

                        auto* transfer = reinterpret_cast<WGPURenderPipelineDescriptorDummyExtensionTransfer*>(*buffer);
                        transfer->chain.sType = chainedStruct->sType;
                        transfer->chain.hasNext = chainedStruct->next != nullptr;

                        *buffer += sizeof(WGPURenderPipelineDescriptorDummyExtensionTransfer);
                        WGPURenderPipelineDescriptorDummyExtensionSerialize(*reinterpret_cast<WGPURenderPipelineDescriptorDummyExtension const*>(chainedStruct), transfer, buffer, provider);

                        chainedStruct = chainedStruct->next;
                    } break;
                    default: {
                        // Invalid enum. Serialize just the transfer header with Invalid as the sType.
                        // TODO(crbug.com/dawn/369): Unknown sTypes are silently discarded.
                        ASSERT(chainedStruct->sType == WGPUSType_Invalid);
                        WGPUChainedStructTransfer* transfer = reinterpret_cast<WGPUChainedStructTransfer*>(*buffer);
                        transfer->sType = WGPUSType_Invalid;
                        transfer->hasNext = false;

                        *buffer += sizeof(WGPUChainedStructTransfer);
                        return;
                    }
                }
            } while (chainedStruct != nullptr);
        }

        DeserializeResult DeserializeChainedStruct(const WGPUChainedStruct** outChainNext,
                                                   const volatile char** buffer,
                                                   size_t* size,
                                                   DeserializeAllocator* allocator,
                                                   const ObjectIdResolver& resolver) {
            bool hasNext;
            do {
                if (*size < sizeof(WGPUChainedStructTransfer)) {
                    return DeserializeResult::FatalError;
                }
                WGPUSType sType =
                    reinterpret_cast<const volatile WGPUChainedStructTransfer*>(*buffer)->sType;
                switch (sType) {
                    case WGPUSType_SurfaceDescriptorFromCanvasHTMLSelector: {
                        const volatile WGPUSurfaceDescriptorFromCanvasHTMLSelectorTransfer* transfer = nullptr;
                        DESERIALIZE_TRY(GetPtrFromBuffer(buffer, size, 1, &transfer));

                        WGPUSurfaceDescriptorFromCanvasHTMLSelector* outStruct = nullptr;
                        DESERIALIZE_TRY(GetSpace(allocator, sizeof(WGPUSurfaceDescriptorFromCanvasHTMLSelector), &outStruct));
                        outStruct->chain.sType = sType;
                        outStruct->chain.next = nullptr;

                        *outChainNext = &outStruct->chain;
                        outChainNext = &outStruct->chain.next;

                        DESERIALIZE_TRY(WGPUSurfaceDescriptorFromCanvasHTMLSelectorDeserialize(outStruct, transfer, buffer, size, allocator, resolver));

                        hasNext = transfer->chain.hasNext;
                    } break;
                    case WGPUSType_ShaderModuleSPIRVDescriptor: {
                        const volatile WGPUShaderModuleSPIRVDescriptorTransfer* transfer = nullptr;
                        DESERIALIZE_TRY(GetPtrFromBuffer(buffer, size, 1, &transfer));

                        WGPUShaderModuleSPIRVDescriptor* outStruct = nullptr;
                        DESERIALIZE_TRY(GetSpace(allocator, sizeof(WGPUShaderModuleSPIRVDescriptor), &outStruct));
                        outStruct->chain.sType = sType;
                        outStruct->chain.next = nullptr;

                        *outChainNext = &outStruct->chain;
                        outChainNext = &outStruct->chain.next;

                        DESERIALIZE_TRY(WGPUShaderModuleSPIRVDescriptorDeserialize(outStruct, transfer, buffer, size, allocator, resolver));

                        hasNext = transfer->chain.hasNext;
                    } break;
                    case WGPUSType_ShaderModuleWGSLDescriptor: {
                        const volatile WGPUShaderModuleWGSLDescriptorTransfer* transfer = nullptr;
                        DESERIALIZE_TRY(GetPtrFromBuffer(buffer, size, 1, &transfer));

                        WGPUShaderModuleWGSLDescriptor* outStruct = nullptr;
                        DESERIALIZE_TRY(GetSpace(allocator, sizeof(WGPUShaderModuleWGSLDescriptor), &outStruct));
                        outStruct->chain.sType = sType;
                        outStruct->chain.next = nullptr;

                        *outChainNext = &outStruct->chain;
                        outChainNext = &outStruct->chain.next;

                        DESERIALIZE_TRY(WGPUShaderModuleWGSLDescriptorDeserialize(outStruct, transfer, buffer, size, allocator, resolver));

                        hasNext = transfer->chain.hasNext;
                    } break;
                    case WGPUSType_SamplerDescriptorDummyAnisotropicFiltering: {
                        const volatile WGPUSamplerDescriptorDummyAnisotropicFilteringTransfer* transfer = nullptr;
                        DESERIALIZE_TRY(GetPtrFromBuffer(buffer, size, 1, &transfer));

                        WGPUSamplerDescriptorDummyAnisotropicFiltering* outStruct = nullptr;
                        DESERIALIZE_TRY(GetSpace(allocator, sizeof(WGPUSamplerDescriptorDummyAnisotropicFiltering), &outStruct));
                        outStruct->chain.sType = sType;
                        outStruct->chain.next = nullptr;

                        *outChainNext = &outStruct->chain;
                        outChainNext = &outStruct->chain.next;

                        DESERIALIZE_TRY(WGPUSamplerDescriptorDummyAnisotropicFilteringDeserialize(outStruct, transfer, buffer, size, allocator, resolver));

                        hasNext = transfer->chain.hasNext;
                    } break;
                    case WGPUSType_RenderPipelineDescriptorDummyExtension: {
                        const volatile WGPURenderPipelineDescriptorDummyExtensionTransfer* transfer = nullptr;
                        DESERIALIZE_TRY(GetPtrFromBuffer(buffer, size, 1, &transfer));

                        WGPURenderPipelineDescriptorDummyExtension* outStruct = nullptr;
                        DESERIALIZE_TRY(GetSpace(allocator, sizeof(WGPURenderPipelineDescriptorDummyExtension), &outStruct));
                        outStruct->chain.sType = sType;
                        outStruct->chain.next = nullptr;

                        *outChainNext = &outStruct->chain;
                        outChainNext = &outStruct->chain.next;

                        DESERIALIZE_TRY(WGPURenderPipelineDescriptorDummyExtensionDeserialize(outStruct, transfer, buffer, size, allocator, resolver));

                        hasNext = transfer->chain.hasNext;
                    } break;
                    default:
                        return DeserializeResult::FatalError;
                }
            } while (hasNext);

            return DeserializeResult::Success;
        }

        
struct BufferDestroyTransfer : CmdHeader {
    static_assert(1 <= 1,
                  "Record must be at most one of is_cmd, extensible, and chained.");
    WireCmd commandId;

    ObjectId self;


};

static_assert(offsetof(BufferDestroyTransfer, commandSize) == 0, "");
static_assert(offsetof(BufferDestroyTransfer, commandId) == sizeof(CmdHeader), "");


DAWN_DECLARE_UNUSED size_t BufferDestroyGetExtraRequiredSize(const BufferDestroyCmd& record) {
    DAWN_UNUSED(record);

    size_t result = 0;



    {
    }

    return result;
}
// GetExtraRequiredSize isn't used for structures that are value members of other structures
// because we assume they cannot contain pointers themselves.
DAWN_UNUSED_FUNC(BufferDestroyGetExtraRequiredSize);

DAWN_DECLARE_UNUSED void BufferDestroySerialize(const BufferDestroyCmd& record, BufferDestroyTransfer* transfer,
                       char** buffer, const ObjectIdProvider& provider) {
    DAWN_UNUSED(buffer);

    transfer->commandId = WireCmd::BufferDestroy;

    transfer->self = provider.GetId(record.self);





}
DAWN_UNUSED_FUNC(BufferDestroySerialize);

DAWN_DECLARE_UNUSED DeserializeResult BufferDestroyDeserialize(BufferDestroyCmd* record, const volatile BufferDestroyTransfer* transfer,
                                      const volatile char** buffer, size_t* size, DeserializeAllocator* allocator, const ObjectIdResolver& resolver) {
    DAWN_UNUSED(allocator);
    DAWN_UNUSED(buffer);
    DAWN_UNUSED(size);

    ASSERT(transfer->commandId == WireCmd::BufferDestroy);

    record->selfId = transfer->self;

    DESERIALIZE_TRY(resolver.GetFromId(transfer->self, &record->self));





    return DeserializeResult::Success;
}
DAWN_UNUSED_FUNC(BufferDestroyDeserialize);

        
struct BufferMapAsyncTransfer : CmdHeader {
    static_assert(1 <= 1,
                  "Record must be at most one of is_cmd, extensible, and chained.");
    WireCmd commandId;

    ObjectId bufferId;
    uint32_t requestSerial;
    WGPUMapModeFlags mode;
    size_t offset;
    size_t size;
    uint64_t handleCreateInfoLength;


};

static_assert(offsetof(BufferMapAsyncTransfer, commandSize) == 0, "");
static_assert(offsetof(BufferMapAsyncTransfer, commandId) == sizeof(CmdHeader), "");


DAWN_DECLARE_UNUSED size_t BufferMapAsyncGetExtraRequiredSize(const BufferMapAsyncCmd& record) {
    DAWN_UNUSED(record);

    size_t result = 0;



    {
    }
    {
    }
    {
    }
    {
    }
    {
    }
    {
    }

    return result;
}
// GetExtraRequiredSize isn't used for structures that are value members of other structures
// because we assume they cannot contain pointers themselves.
DAWN_UNUSED_FUNC(BufferMapAsyncGetExtraRequiredSize);

DAWN_DECLARE_UNUSED void BufferMapAsyncSerialize(const BufferMapAsyncCmd& record, BufferMapAsyncTransfer* transfer,
                       char** buffer) {
    DAWN_UNUSED(buffer);

    transfer->commandId = WireCmd::BufferMapAsync;

    transfer->bufferId = record.bufferId;
    transfer->requestSerial = record.requestSerial;
    transfer->mode = record.mode;
    transfer->offset = record.offset;
    transfer->size = record.size;
    transfer->handleCreateInfoLength = record.handleCreateInfoLength;




}
DAWN_UNUSED_FUNC(BufferMapAsyncSerialize);

DAWN_DECLARE_UNUSED DeserializeResult BufferMapAsyncDeserialize(BufferMapAsyncCmd* record, const volatile BufferMapAsyncTransfer* transfer,
                                      const volatile char** buffer, size_t* size, DeserializeAllocator* allocator) {
    DAWN_UNUSED(allocator);
    DAWN_UNUSED(buffer);
    DAWN_UNUSED(size);

    ASSERT(transfer->commandId == WireCmd::BufferMapAsync);


    record->bufferId = transfer->bufferId;
    record->requestSerial = transfer->requestSerial;
    record->mode = transfer->mode;
    record->offset = transfer->offset;
    record->size = transfer->size;
    record->handleCreateInfoLength = transfer->handleCreateInfoLength;





    {
        size_t memberLength = record->handleCreateInfoLength;
        auto memberBuffer = reinterpret_cast<const volatile uint8_t*>(buffer);
        DESERIALIZE_TRY(GetPtrFromBuffer(buffer, size, memberLength, &memberBuffer));

        uint8_t* copiedMembers = nullptr;
        DESERIALIZE_TRY(GetSpace(allocator, memberLength, &copiedMembers));
        record->handleCreateInfo = copiedMembers;

        for (size_t i = 0; i < memberLength; ++i) {
            copiedMembers[i] = memberBuffer[i];
        }
    }

    return DeserializeResult::Success;
}
DAWN_UNUSED_FUNC(BufferMapAsyncDeserialize);

        
struct BufferUnmapTransfer : CmdHeader {
    static_assert(1 <= 1,
                  "Record must be at most one of is_cmd, extensible, and chained.");
    WireCmd commandId;

    ObjectId self;


};

static_assert(offsetof(BufferUnmapTransfer, commandSize) == 0, "");
static_assert(offsetof(BufferUnmapTransfer, commandId) == sizeof(CmdHeader), "");


DAWN_DECLARE_UNUSED size_t BufferUnmapGetExtraRequiredSize(const BufferUnmapCmd& record) {
    DAWN_UNUSED(record);

    size_t result = 0;



    {
    }

    return result;
}
// GetExtraRequiredSize isn't used for structures that are value members of other structures
// because we assume they cannot contain pointers themselves.
DAWN_UNUSED_FUNC(BufferUnmapGetExtraRequiredSize);

DAWN_DECLARE_UNUSED void BufferUnmapSerialize(const BufferUnmapCmd& record, BufferUnmapTransfer* transfer,
                       char** buffer, const ObjectIdProvider& provider) {
    DAWN_UNUSED(buffer);

    transfer->commandId = WireCmd::BufferUnmap;

    transfer->self = provider.GetId(record.self);





}
DAWN_UNUSED_FUNC(BufferUnmapSerialize);

DAWN_DECLARE_UNUSED DeserializeResult BufferUnmapDeserialize(BufferUnmapCmd* record, const volatile BufferUnmapTransfer* transfer,
                                      const volatile char** buffer, size_t* size, DeserializeAllocator* allocator, const ObjectIdResolver& resolver) {
    DAWN_UNUSED(allocator);
    DAWN_UNUSED(buffer);
    DAWN_UNUSED(size);

    ASSERT(transfer->commandId == WireCmd::BufferUnmap);

    record->selfId = transfer->self;

    DESERIALIZE_TRY(resolver.GetFromId(transfer->self, &record->self));





    return DeserializeResult::Success;
}
DAWN_UNUSED_FUNC(BufferUnmapDeserialize);

        
struct BufferUpdateMappedDataTransfer : CmdHeader {
    static_assert(1 <= 1,
                  "Record must be at most one of is_cmd, extensible, and chained.");
    WireCmd commandId;

    ObjectId bufferId;
    uint64_t writeFlushInfoLength;


};

static_assert(offsetof(BufferUpdateMappedDataTransfer, commandSize) == 0, "");
static_assert(offsetof(BufferUpdateMappedDataTransfer, commandId) == sizeof(CmdHeader), "");


DAWN_DECLARE_UNUSED size_t BufferUpdateMappedDataGetExtraRequiredSize(const BufferUpdateMappedDataCmd& record) {
    DAWN_UNUSED(record);

    size_t result = 0;



    {
    }
    {
    }

    return result;
}
// GetExtraRequiredSize isn't used for structures that are value members of other structures
// because we assume they cannot contain pointers themselves.
DAWN_UNUSED_FUNC(BufferUpdateMappedDataGetExtraRequiredSize);

DAWN_DECLARE_UNUSED void BufferUpdateMappedDataSerialize(const BufferUpdateMappedDataCmd& record, BufferUpdateMappedDataTransfer* transfer,
                       char** buffer) {
    DAWN_UNUSED(buffer);

    transfer->commandId = WireCmd::BufferUpdateMappedData;

    transfer->bufferId = record.bufferId;
    transfer->writeFlushInfoLength = record.writeFlushInfoLength;




}
DAWN_UNUSED_FUNC(BufferUpdateMappedDataSerialize);

DAWN_DECLARE_UNUSED DeserializeResult BufferUpdateMappedDataDeserialize(BufferUpdateMappedDataCmd* record, const volatile BufferUpdateMappedDataTransfer* transfer,
                                      const volatile char** buffer, size_t* size, DeserializeAllocator* allocator) {
    DAWN_UNUSED(allocator);
    DAWN_UNUSED(buffer);
    DAWN_UNUSED(size);

    ASSERT(transfer->commandId == WireCmd::BufferUpdateMappedData);


    record->bufferId = transfer->bufferId;
    record->writeFlushInfoLength = transfer->writeFlushInfoLength;





    {
        size_t memberLength = record->writeFlushInfoLength;
        auto memberBuffer = reinterpret_cast<const volatile uint8_t*>(buffer);
        DESERIALIZE_TRY(GetPtrFromBuffer(buffer, size, memberLength, &memberBuffer));

        uint8_t* copiedMembers = nullptr;
        DESERIALIZE_TRY(GetSpace(allocator, memberLength, &copiedMembers));
        record->writeFlushInfo = copiedMembers;

        for (size_t i = 0; i < memberLength; ++i) {
            copiedMembers[i] = memberBuffer[i];
        }
    }

    return DeserializeResult::Success;
}
DAWN_UNUSED_FUNC(BufferUpdateMappedDataDeserialize);

        
struct CommandEncoderBeginComputePassTransfer : CmdHeader {
    static_assert(1 <= 1,
                  "Record must be at most one of is_cmd, extensible, and chained.");
    WireCmd commandId;

    ObjectId self;
    ObjectHandle result;


    bool has_descriptor;
};

static_assert(offsetof(CommandEncoderBeginComputePassTransfer, commandSize) == 0, "");
static_assert(offsetof(CommandEncoderBeginComputePassTransfer, commandId) == sizeof(CmdHeader), "");


DAWN_DECLARE_UNUSED size_t CommandEncoderBeginComputePassGetExtraRequiredSize(const CommandEncoderBeginComputePassCmd& record) {
    DAWN_UNUSED(record);

    size_t result = 0;



    {
    }
    if (record.descriptor != nullptr)
    {
        size_t memberLength = 1;
        result += memberLength * sizeof(WGPUComputePassDescriptorTransfer);
        for (size_t i = 0; i < memberLength; ++i) {
            
            result += WGPUComputePassDescriptorGetExtraRequiredSize(record.descriptor[i]);
        }
    }
    {
    }

    return result;
}
// GetExtraRequiredSize isn't used for structures that are value members of other structures
// because we assume they cannot contain pointers themselves.
DAWN_UNUSED_FUNC(CommandEncoderBeginComputePassGetExtraRequiredSize);

DAWN_DECLARE_UNUSED void CommandEncoderBeginComputePassSerialize(const CommandEncoderBeginComputePassCmd& record, CommandEncoderBeginComputePassTransfer* transfer,
                       char** buffer, const ObjectIdProvider& provider) {
    DAWN_UNUSED(buffer);

    transfer->commandId = WireCmd::CommandEncoderBeginComputePass;

    transfer->self = provider.GetId(record.self);

    transfer->result = record.result;





    bool has_descriptor = record.descriptor != nullptr;
    transfer->has_descriptor = has_descriptor;
    if (has_descriptor)
    {
        size_t memberLength = 1;
        auto memberBuffer = reinterpret_cast<WGPUComputePassDescriptorTransfer*>(*buffer);
        *buffer += memberLength * sizeof(WGPUComputePassDescriptorTransfer);

        for (size_t i = 0; i < memberLength; ++i) {
            WGPUComputePassDescriptorSerialize(record.descriptor[i], &memberBuffer[i], buffer, provider);

        }
    }
}
DAWN_UNUSED_FUNC(CommandEncoderBeginComputePassSerialize);

DAWN_DECLARE_UNUSED DeserializeResult CommandEncoderBeginComputePassDeserialize(CommandEncoderBeginComputePassCmd* record, const volatile CommandEncoderBeginComputePassTransfer* transfer,
                                      const volatile char** buffer, size_t* size, DeserializeAllocator* allocator, const ObjectIdResolver& resolver) {
    DAWN_UNUSED(allocator);
    DAWN_UNUSED(buffer);
    DAWN_UNUSED(size);

    ASSERT(transfer->commandId == WireCmd::CommandEncoderBeginComputePass);

    record->selfId = transfer->self;

    DESERIALIZE_TRY(resolver.GetFromId(transfer->self, &record->self));
    record->result = transfer->result;





    bool has_descriptor = transfer->has_descriptor;
    record->descriptor = nullptr;
    if (has_descriptor)
    {
        size_t memberLength = 1;
        auto memberBuffer = reinterpret_cast<const volatile WGPUComputePassDescriptorTransfer*>(buffer);
        DESERIALIZE_TRY(GetPtrFromBuffer(buffer, size, memberLength, &memberBuffer));

        WGPUComputePassDescriptor* copiedMembers = nullptr;
        DESERIALIZE_TRY(GetSpace(allocator, memberLength, &copiedMembers));
        record->descriptor = copiedMembers;

        for (size_t i = 0; i < memberLength; ++i) {
            DESERIALIZE_TRY(WGPUComputePassDescriptorDeserialize(&copiedMembers[i], &memberBuffer[i], buffer, size, allocator, resolver));
        }
    }

    return DeserializeResult::Success;
}
DAWN_UNUSED_FUNC(CommandEncoderBeginComputePassDeserialize);

        
struct CommandEncoderBeginRenderPassTransfer : CmdHeader {
    static_assert(1 <= 1,
                  "Record must be at most one of is_cmd, extensible, and chained.");
    WireCmd commandId;

    ObjectId self;
    ObjectHandle result;


};

static_assert(offsetof(CommandEncoderBeginRenderPassTransfer, commandSize) == 0, "");
static_assert(offsetof(CommandEncoderBeginRenderPassTransfer, commandId) == sizeof(CmdHeader), "");


DAWN_DECLARE_UNUSED size_t CommandEncoderBeginRenderPassGetExtraRequiredSize(const CommandEncoderBeginRenderPassCmd& record) {
    DAWN_UNUSED(record);

    size_t result = 0;



    {
    }
    {
        size_t memberLength = 1;
        result += memberLength * sizeof(WGPURenderPassDescriptorTransfer);
        for (size_t i = 0; i < memberLength; ++i) {
            
            result += WGPURenderPassDescriptorGetExtraRequiredSize(record.descriptor[i]);
        }
    }
    {
    }

    return result;
}
// GetExtraRequiredSize isn't used for structures that are value members of other structures
// because we assume they cannot contain pointers themselves.
DAWN_UNUSED_FUNC(CommandEncoderBeginRenderPassGetExtraRequiredSize);

DAWN_DECLARE_UNUSED void CommandEncoderBeginRenderPassSerialize(const CommandEncoderBeginRenderPassCmd& record, CommandEncoderBeginRenderPassTransfer* transfer,
                       char** buffer, const ObjectIdProvider& provider) {
    DAWN_UNUSED(buffer);

    transfer->commandId = WireCmd::CommandEncoderBeginRenderPass;

    transfer->self = provider.GetId(record.self);

    transfer->result = record.result;





    {
        size_t memberLength = 1;
        auto memberBuffer = reinterpret_cast<WGPURenderPassDescriptorTransfer*>(*buffer);
        *buffer += memberLength * sizeof(WGPURenderPassDescriptorTransfer);

        for (size_t i = 0; i < memberLength; ++i) {
            WGPURenderPassDescriptorSerialize(record.descriptor[i], &memberBuffer[i], buffer, provider);

        }
    }
}
DAWN_UNUSED_FUNC(CommandEncoderBeginRenderPassSerialize);

DAWN_DECLARE_UNUSED DeserializeResult CommandEncoderBeginRenderPassDeserialize(CommandEncoderBeginRenderPassCmd* record, const volatile CommandEncoderBeginRenderPassTransfer* transfer,
                                      const volatile char** buffer, size_t* size, DeserializeAllocator* allocator, const ObjectIdResolver& resolver) {
    DAWN_UNUSED(allocator);
    DAWN_UNUSED(buffer);
    DAWN_UNUSED(size);

    ASSERT(transfer->commandId == WireCmd::CommandEncoderBeginRenderPass);

    record->selfId = transfer->self;

    DESERIALIZE_TRY(resolver.GetFromId(transfer->self, &record->self));
    record->result = transfer->result;





    {
        size_t memberLength = 1;
        auto memberBuffer = reinterpret_cast<const volatile WGPURenderPassDescriptorTransfer*>(buffer);
        DESERIALIZE_TRY(GetPtrFromBuffer(buffer, size, memberLength, &memberBuffer));

        WGPURenderPassDescriptor* copiedMembers = nullptr;
        DESERIALIZE_TRY(GetSpace(allocator, memberLength, &copiedMembers));
        record->descriptor = copiedMembers;

        for (size_t i = 0; i < memberLength; ++i) {
            DESERIALIZE_TRY(WGPURenderPassDescriptorDeserialize(&copiedMembers[i], &memberBuffer[i], buffer, size, allocator, resolver));
        }
    }

    return DeserializeResult::Success;
}
DAWN_UNUSED_FUNC(CommandEncoderBeginRenderPassDeserialize);

        
struct CommandEncoderCopyBufferToBufferTransfer : CmdHeader {
    static_assert(1 <= 1,
                  "Record must be at most one of is_cmd, extensible, and chained.");
    WireCmd commandId;

    ObjectId self;
    ObjectId source;
    uint64_t sourceOffset;
    ObjectId destination;
    uint64_t destinationOffset;
    uint64_t size;


};

static_assert(offsetof(CommandEncoderCopyBufferToBufferTransfer, commandSize) == 0, "");
static_assert(offsetof(CommandEncoderCopyBufferToBufferTransfer, commandId) == sizeof(CmdHeader), "");


DAWN_DECLARE_UNUSED size_t CommandEncoderCopyBufferToBufferGetExtraRequiredSize(const CommandEncoderCopyBufferToBufferCmd& record) {
    DAWN_UNUSED(record);

    size_t result = 0;



    {
    }
    {
    }
    {
    }
    {
    }
    {
    }
    {
    }

    return result;
}
// GetExtraRequiredSize isn't used for structures that are value members of other structures
// because we assume they cannot contain pointers themselves.
DAWN_UNUSED_FUNC(CommandEncoderCopyBufferToBufferGetExtraRequiredSize);

DAWN_DECLARE_UNUSED void CommandEncoderCopyBufferToBufferSerialize(const CommandEncoderCopyBufferToBufferCmd& record, CommandEncoderCopyBufferToBufferTransfer* transfer,
                       char** buffer, const ObjectIdProvider& provider) {
    DAWN_UNUSED(buffer);

    transfer->commandId = WireCmd::CommandEncoderCopyBufferToBuffer;

    transfer->self = provider.GetId(record.self);

    transfer->source = provider.GetId(record.source);

    transfer->sourceOffset = record.sourceOffset;
    transfer->destination = provider.GetId(record.destination);

    transfer->destinationOffset = record.destinationOffset;
    transfer->size = record.size;




}
DAWN_UNUSED_FUNC(CommandEncoderCopyBufferToBufferSerialize);

DAWN_DECLARE_UNUSED DeserializeResult CommandEncoderCopyBufferToBufferDeserialize(CommandEncoderCopyBufferToBufferCmd* record, const volatile CommandEncoderCopyBufferToBufferTransfer* transfer,
                                      const volatile char** buffer, size_t* size, DeserializeAllocator* allocator, const ObjectIdResolver& resolver) {
    DAWN_UNUSED(allocator);
    DAWN_UNUSED(buffer);
    DAWN_UNUSED(size);

    ASSERT(transfer->commandId == WireCmd::CommandEncoderCopyBufferToBuffer);

    record->selfId = transfer->self;

    DESERIALIZE_TRY(resolver.GetFromId(transfer->self, &record->self));
    DESERIALIZE_TRY(resolver.GetFromId(transfer->source, &record->source));
    record->sourceOffset = transfer->sourceOffset;
    DESERIALIZE_TRY(resolver.GetFromId(transfer->destination, &record->destination));
    record->destinationOffset = transfer->destinationOffset;
    record->size = transfer->size;





    return DeserializeResult::Success;
}
DAWN_UNUSED_FUNC(CommandEncoderCopyBufferToBufferDeserialize);

        
struct CommandEncoderCopyBufferToTextureTransfer : CmdHeader {
    static_assert(1 <= 1,
                  "Record must be at most one of is_cmd, extensible, and chained.");
    WireCmd commandId;

    ObjectId self;


};

static_assert(offsetof(CommandEncoderCopyBufferToTextureTransfer, commandSize) == 0, "");
static_assert(offsetof(CommandEncoderCopyBufferToTextureTransfer, commandId) == sizeof(CmdHeader), "");


DAWN_DECLARE_UNUSED size_t CommandEncoderCopyBufferToTextureGetExtraRequiredSize(const CommandEncoderCopyBufferToTextureCmd& record) {
    DAWN_UNUSED(record);

    size_t result = 0;



    {
    }
    {
        size_t memberLength = 1;
        result += memberLength * sizeof(WGPUBufferCopyViewTransfer);
        for (size_t i = 0; i < memberLength; ++i) {
            
            result += WGPUBufferCopyViewGetExtraRequiredSize(record.source[i]);
        }
    }
    {
        size_t memberLength = 1;
        result += memberLength * sizeof(WGPUTextureCopyViewTransfer);
        for (size_t i = 0; i < memberLength; ++i) {
            
            result += WGPUTextureCopyViewGetExtraRequiredSize(record.destination[i]);
        }
    }
    {
        size_t memberLength = 1;
        result += memberLength * sizeof(WGPUExtent3DTransfer);
        for (size_t i = 0; i < memberLength; ++i) {
            
            result += WGPUExtent3DGetExtraRequiredSize(record.copySize[i]);
        }
    }

    return result;
}
// GetExtraRequiredSize isn't used for structures that are value members of other structures
// because we assume they cannot contain pointers themselves.
DAWN_UNUSED_FUNC(CommandEncoderCopyBufferToTextureGetExtraRequiredSize);

DAWN_DECLARE_UNUSED void CommandEncoderCopyBufferToTextureSerialize(const CommandEncoderCopyBufferToTextureCmd& record, CommandEncoderCopyBufferToTextureTransfer* transfer,
                       char** buffer, const ObjectIdProvider& provider) {
    DAWN_UNUSED(buffer);

    transfer->commandId = WireCmd::CommandEncoderCopyBufferToTexture;

    transfer->self = provider.GetId(record.self);






    {
        size_t memberLength = 1;
        auto memberBuffer = reinterpret_cast<WGPUBufferCopyViewTransfer*>(*buffer);
        *buffer += memberLength * sizeof(WGPUBufferCopyViewTransfer);

        for (size_t i = 0; i < memberLength; ++i) {
            WGPUBufferCopyViewSerialize(record.source[i], &memberBuffer[i], buffer, provider);

        }
    }

    {
        size_t memberLength = 1;
        auto memberBuffer = reinterpret_cast<WGPUTextureCopyViewTransfer*>(*buffer);
        *buffer += memberLength * sizeof(WGPUTextureCopyViewTransfer);

        for (size_t i = 0; i < memberLength; ++i) {
            WGPUTextureCopyViewSerialize(record.destination[i], &memberBuffer[i], buffer, provider);

        }
    }

    {
        size_t memberLength = 1;
        auto memberBuffer = reinterpret_cast<WGPUExtent3DTransfer*>(*buffer);
        *buffer += memberLength * sizeof(WGPUExtent3DTransfer);

        for (size_t i = 0; i < memberLength; ++i) {
            WGPUExtent3DSerialize(record.copySize[i], &memberBuffer[i], buffer);

        }
    }
}
DAWN_UNUSED_FUNC(CommandEncoderCopyBufferToTextureSerialize);

DAWN_DECLARE_UNUSED DeserializeResult CommandEncoderCopyBufferToTextureDeserialize(CommandEncoderCopyBufferToTextureCmd* record, const volatile CommandEncoderCopyBufferToTextureTransfer* transfer,
                                      const volatile char** buffer, size_t* size, DeserializeAllocator* allocator, const ObjectIdResolver& resolver) {
    DAWN_UNUSED(allocator);
    DAWN_UNUSED(buffer);
    DAWN_UNUSED(size);

    ASSERT(transfer->commandId == WireCmd::CommandEncoderCopyBufferToTexture);

    record->selfId = transfer->self;

    DESERIALIZE_TRY(resolver.GetFromId(transfer->self, &record->self));





    {
        size_t memberLength = 1;
        auto memberBuffer = reinterpret_cast<const volatile WGPUBufferCopyViewTransfer*>(buffer);
        DESERIALIZE_TRY(GetPtrFromBuffer(buffer, size, memberLength, &memberBuffer));

        WGPUBufferCopyView* copiedMembers = nullptr;
        DESERIALIZE_TRY(GetSpace(allocator, memberLength, &copiedMembers));
        record->source = copiedMembers;

        for (size_t i = 0; i < memberLength; ++i) {
            DESERIALIZE_TRY(WGPUBufferCopyViewDeserialize(&copiedMembers[i], &memberBuffer[i], buffer, size, allocator, resolver));
        }
    }

    {
        size_t memberLength = 1;
        auto memberBuffer = reinterpret_cast<const volatile WGPUTextureCopyViewTransfer*>(buffer);
        DESERIALIZE_TRY(GetPtrFromBuffer(buffer, size, memberLength, &memberBuffer));

        WGPUTextureCopyView* copiedMembers = nullptr;
        DESERIALIZE_TRY(GetSpace(allocator, memberLength, &copiedMembers));
        record->destination = copiedMembers;

        for (size_t i = 0; i < memberLength; ++i) {
            DESERIALIZE_TRY(WGPUTextureCopyViewDeserialize(&copiedMembers[i], &memberBuffer[i], buffer, size, allocator, resolver));
        }
    }

    {
        size_t memberLength = 1;
        auto memberBuffer = reinterpret_cast<const volatile WGPUExtent3DTransfer*>(buffer);
        DESERIALIZE_TRY(GetPtrFromBuffer(buffer, size, memberLength, &memberBuffer));

        WGPUExtent3D* copiedMembers = nullptr;
        DESERIALIZE_TRY(GetSpace(allocator, memberLength, &copiedMembers));
        record->copySize = copiedMembers;

        for (size_t i = 0; i < memberLength; ++i) {
            DESERIALIZE_TRY(WGPUExtent3DDeserialize(&copiedMembers[i], &memberBuffer[i], buffer, size, allocator));
        }
    }

    return DeserializeResult::Success;
}
DAWN_UNUSED_FUNC(CommandEncoderCopyBufferToTextureDeserialize);

        
struct CommandEncoderCopyTextureToBufferTransfer : CmdHeader {
    static_assert(1 <= 1,
                  "Record must be at most one of is_cmd, extensible, and chained.");
    WireCmd commandId;

    ObjectId self;


};

static_assert(offsetof(CommandEncoderCopyTextureToBufferTransfer, commandSize) == 0, "");
static_assert(offsetof(CommandEncoderCopyTextureToBufferTransfer, commandId) == sizeof(CmdHeader), "");


DAWN_DECLARE_UNUSED size_t CommandEncoderCopyTextureToBufferGetExtraRequiredSize(const CommandEncoderCopyTextureToBufferCmd& record) {
    DAWN_UNUSED(record);

    size_t result = 0;



    {
    }
    {
        size_t memberLength = 1;
        result += memberLength * sizeof(WGPUTextureCopyViewTransfer);
        for (size_t i = 0; i < memberLength; ++i) {
            
            result += WGPUTextureCopyViewGetExtraRequiredSize(record.source[i]);
        }
    }
    {
        size_t memberLength = 1;
        result += memberLength * sizeof(WGPUBufferCopyViewTransfer);
        for (size_t i = 0; i < memberLength; ++i) {
            
            result += WGPUBufferCopyViewGetExtraRequiredSize(record.destination[i]);
        }
    }
    {
        size_t memberLength = 1;
        result += memberLength * sizeof(WGPUExtent3DTransfer);
        for (size_t i = 0; i < memberLength; ++i) {
            
            result += WGPUExtent3DGetExtraRequiredSize(record.copySize[i]);
        }
    }

    return result;
}
// GetExtraRequiredSize isn't used for structures that are value members of other structures
// because we assume they cannot contain pointers themselves.
DAWN_UNUSED_FUNC(CommandEncoderCopyTextureToBufferGetExtraRequiredSize);

DAWN_DECLARE_UNUSED void CommandEncoderCopyTextureToBufferSerialize(const CommandEncoderCopyTextureToBufferCmd& record, CommandEncoderCopyTextureToBufferTransfer* transfer,
                       char** buffer, const ObjectIdProvider& provider) {
    DAWN_UNUSED(buffer);

    transfer->commandId = WireCmd::CommandEncoderCopyTextureToBuffer;

    transfer->self = provider.GetId(record.self);






    {
        size_t memberLength = 1;
        auto memberBuffer = reinterpret_cast<WGPUTextureCopyViewTransfer*>(*buffer);
        *buffer += memberLength * sizeof(WGPUTextureCopyViewTransfer);

        for (size_t i = 0; i < memberLength; ++i) {
            WGPUTextureCopyViewSerialize(record.source[i], &memberBuffer[i], buffer, provider);

        }
    }

    {
        size_t memberLength = 1;
        auto memberBuffer = reinterpret_cast<WGPUBufferCopyViewTransfer*>(*buffer);
        *buffer += memberLength * sizeof(WGPUBufferCopyViewTransfer);

        for (size_t i = 0; i < memberLength; ++i) {
            WGPUBufferCopyViewSerialize(record.destination[i], &memberBuffer[i], buffer, provider);

        }
    }

    {
        size_t memberLength = 1;
        auto memberBuffer = reinterpret_cast<WGPUExtent3DTransfer*>(*buffer);
        *buffer += memberLength * sizeof(WGPUExtent3DTransfer);

        for (size_t i = 0; i < memberLength; ++i) {
            WGPUExtent3DSerialize(record.copySize[i], &memberBuffer[i], buffer);

        }
    }
}
DAWN_UNUSED_FUNC(CommandEncoderCopyTextureToBufferSerialize);

DAWN_DECLARE_UNUSED DeserializeResult CommandEncoderCopyTextureToBufferDeserialize(CommandEncoderCopyTextureToBufferCmd* record, const volatile CommandEncoderCopyTextureToBufferTransfer* transfer,
                                      const volatile char** buffer, size_t* size, DeserializeAllocator* allocator, const ObjectIdResolver& resolver) {
    DAWN_UNUSED(allocator);
    DAWN_UNUSED(buffer);
    DAWN_UNUSED(size);

    ASSERT(transfer->commandId == WireCmd::CommandEncoderCopyTextureToBuffer);

    record->selfId = transfer->self;

    DESERIALIZE_TRY(resolver.GetFromId(transfer->self, &record->self));





    {
        size_t memberLength = 1;
        auto memberBuffer = reinterpret_cast<const volatile WGPUTextureCopyViewTransfer*>(buffer);
        DESERIALIZE_TRY(GetPtrFromBuffer(buffer, size, memberLength, &memberBuffer));

        WGPUTextureCopyView* copiedMembers = nullptr;
        DESERIALIZE_TRY(GetSpace(allocator, memberLength, &copiedMembers));
        record->source = copiedMembers;

        for (size_t i = 0; i < memberLength; ++i) {
            DESERIALIZE_TRY(WGPUTextureCopyViewDeserialize(&copiedMembers[i], &memberBuffer[i], buffer, size, allocator, resolver));
        }
    }

    {
        size_t memberLength = 1;
        auto memberBuffer = reinterpret_cast<const volatile WGPUBufferCopyViewTransfer*>(buffer);
        DESERIALIZE_TRY(GetPtrFromBuffer(buffer, size, memberLength, &memberBuffer));

        WGPUBufferCopyView* copiedMembers = nullptr;
        DESERIALIZE_TRY(GetSpace(allocator, memberLength, &copiedMembers));
        record->destination = copiedMembers;

        for (size_t i = 0; i < memberLength; ++i) {
            DESERIALIZE_TRY(WGPUBufferCopyViewDeserialize(&copiedMembers[i], &memberBuffer[i], buffer, size, allocator, resolver));
        }
    }

    {
        size_t memberLength = 1;
        auto memberBuffer = reinterpret_cast<const volatile WGPUExtent3DTransfer*>(buffer);
        DESERIALIZE_TRY(GetPtrFromBuffer(buffer, size, memberLength, &memberBuffer));

        WGPUExtent3D* copiedMembers = nullptr;
        DESERIALIZE_TRY(GetSpace(allocator, memberLength, &copiedMembers));
        record->copySize = copiedMembers;

        for (size_t i = 0; i < memberLength; ++i) {
            DESERIALIZE_TRY(WGPUExtent3DDeserialize(&copiedMembers[i], &memberBuffer[i], buffer, size, allocator));
        }
    }

    return DeserializeResult::Success;
}
DAWN_UNUSED_FUNC(CommandEncoderCopyTextureToBufferDeserialize);

        
struct CommandEncoderCopyTextureToTextureTransfer : CmdHeader {
    static_assert(1 <= 1,
                  "Record must be at most one of is_cmd, extensible, and chained.");
    WireCmd commandId;

    ObjectId self;


};

static_assert(offsetof(CommandEncoderCopyTextureToTextureTransfer, commandSize) == 0, "");
static_assert(offsetof(CommandEncoderCopyTextureToTextureTransfer, commandId) == sizeof(CmdHeader), "");


DAWN_DECLARE_UNUSED size_t CommandEncoderCopyTextureToTextureGetExtraRequiredSize(const CommandEncoderCopyTextureToTextureCmd& record) {
    DAWN_UNUSED(record);

    size_t result = 0;



    {
    }
    {
        size_t memberLength = 1;
        result += memberLength * sizeof(WGPUTextureCopyViewTransfer);
        for (size_t i = 0; i < memberLength; ++i) {
            
            result += WGPUTextureCopyViewGetExtraRequiredSize(record.source[i]);
        }
    }
    {
        size_t memberLength = 1;
        result += memberLength * sizeof(WGPUTextureCopyViewTransfer);
        for (size_t i = 0; i < memberLength; ++i) {
            
            result += WGPUTextureCopyViewGetExtraRequiredSize(record.destination[i]);
        }
    }
    {
        size_t memberLength = 1;
        result += memberLength * sizeof(WGPUExtent3DTransfer);
        for (size_t i = 0; i < memberLength; ++i) {
            
            result += WGPUExtent3DGetExtraRequiredSize(record.copySize[i]);
        }
    }

    return result;
}
// GetExtraRequiredSize isn't used for structures that are value members of other structures
// because we assume they cannot contain pointers themselves.
DAWN_UNUSED_FUNC(CommandEncoderCopyTextureToTextureGetExtraRequiredSize);

DAWN_DECLARE_UNUSED void CommandEncoderCopyTextureToTextureSerialize(const CommandEncoderCopyTextureToTextureCmd& record, CommandEncoderCopyTextureToTextureTransfer* transfer,
                       char** buffer, const ObjectIdProvider& provider) {
    DAWN_UNUSED(buffer);

    transfer->commandId = WireCmd::CommandEncoderCopyTextureToTexture;

    transfer->self = provider.GetId(record.self);






    {
        size_t memberLength = 1;
        auto memberBuffer = reinterpret_cast<WGPUTextureCopyViewTransfer*>(*buffer);
        *buffer += memberLength * sizeof(WGPUTextureCopyViewTransfer);

        for (size_t i = 0; i < memberLength; ++i) {
            WGPUTextureCopyViewSerialize(record.source[i], &memberBuffer[i], buffer, provider);

        }
    }

    {
        size_t memberLength = 1;
        auto memberBuffer = reinterpret_cast<WGPUTextureCopyViewTransfer*>(*buffer);
        *buffer += memberLength * sizeof(WGPUTextureCopyViewTransfer);

        for (size_t i = 0; i < memberLength; ++i) {
            WGPUTextureCopyViewSerialize(record.destination[i], &memberBuffer[i], buffer, provider);

        }
    }

    {
        size_t memberLength = 1;
        auto memberBuffer = reinterpret_cast<WGPUExtent3DTransfer*>(*buffer);
        *buffer += memberLength * sizeof(WGPUExtent3DTransfer);

        for (size_t i = 0; i < memberLength; ++i) {
            WGPUExtent3DSerialize(record.copySize[i], &memberBuffer[i], buffer);

        }
    }
}
DAWN_UNUSED_FUNC(CommandEncoderCopyTextureToTextureSerialize);

DAWN_DECLARE_UNUSED DeserializeResult CommandEncoderCopyTextureToTextureDeserialize(CommandEncoderCopyTextureToTextureCmd* record, const volatile CommandEncoderCopyTextureToTextureTransfer* transfer,
                                      const volatile char** buffer, size_t* size, DeserializeAllocator* allocator, const ObjectIdResolver& resolver) {
    DAWN_UNUSED(allocator);
    DAWN_UNUSED(buffer);
    DAWN_UNUSED(size);

    ASSERT(transfer->commandId == WireCmd::CommandEncoderCopyTextureToTexture);

    record->selfId = transfer->self;

    DESERIALIZE_TRY(resolver.GetFromId(transfer->self, &record->self));





    {
        size_t memberLength = 1;
        auto memberBuffer = reinterpret_cast<const volatile WGPUTextureCopyViewTransfer*>(buffer);
        DESERIALIZE_TRY(GetPtrFromBuffer(buffer, size, memberLength, &memberBuffer));

        WGPUTextureCopyView* copiedMembers = nullptr;
        DESERIALIZE_TRY(GetSpace(allocator, memberLength, &copiedMembers));
        record->source = copiedMembers;

        for (size_t i = 0; i < memberLength; ++i) {
            DESERIALIZE_TRY(WGPUTextureCopyViewDeserialize(&copiedMembers[i], &memberBuffer[i], buffer, size, allocator, resolver));
        }
    }

    {
        size_t memberLength = 1;
        auto memberBuffer = reinterpret_cast<const volatile WGPUTextureCopyViewTransfer*>(buffer);
        DESERIALIZE_TRY(GetPtrFromBuffer(buffer, size, memberLength, &memberBuffer));

        WGPUTextureCopyView* copiedMembers = nullptr;
        DESERIALIZE_TRY(GetSpace(allocator, memberLength, &copiedMembers));
        record->destination = copiedMembers;

        for (size_t i = 0; i < memberLength; ++i) {
            DESERIALIZE_TRY(WGPUTextureCopyViewDeserialize(&copiedMembers[i], &memberBuffer[i], buffer, size, allocator, resolver));
        }
    }

    {
        size_t memberLength = 1;
        auto memberBuffer = reinterpret_cast<const volatile WGPUExtent3DTransfer*>(buffer);
        DESERIALIZE_TRY(GetPtrFromBuffer(buffer, size, memberLength, &memberBuffer));

        WGPUExtent3D* copiedMembers = nullptr;
        DESERIALIZE_TRY(GetSpace(allocator, memberLength, &copiedMembers));
        record->copySize = copiedMembers;

        for (size_t i = 0; i < memberLength; ++i) {
            DESERIALIZE_TRY(WGPUExtent3DDeserialize(&copiedMembers[i], &memberBuffer[i], buffer, size, allocator));
        }
    }

    return DeserializeResult::Success;
}
DAWN_UNUSED_FUNC(CommandEncoderCopyTextureToTextureDeserialize);

        
struct CommandEncoderFinishTransfer : CmdHeader {
    static_assert(1 <= 1,
                  "Record must be at most one of is_cmd, extensible, and chained.");
    WireCmd commandId;

    ObjectId self;
    ObjectHandle result;


    bool has_descriptor;
};

static_assert(offsetof(CommandEncoderFinishTransfer, commandSize) == 0, "");
static_assert(offsetof(CommandEncoderFinishTransfer, commandId) == sizeof(CmdHeader), "");


DAWN_DECLARE_UNUSED size_t CommandEncoderFinishGetExtraRequiredSize(const CommandEncoderFinishCmd& record) {
    DAWN_UNUSED(record);

    size_t result = 0;



    {
    }
    if (record.descriptor != nullptr)
    {
        size_t memberLength = 1;
        result += memberLength * sizeof(WGPUCommandBufferDescriptorTransfer);
        for (size_t i = 0; i < memberLength; ++i) {
            
            result += WGPUCommandBufferDescriptorGetExtraRequiredSize(record.descriptor[i]);
        }
    }
    {
    }

    return result;
}
// GetExtraRequiredSize isn't used for structures that are value members of other structures
// because we assume they cannot contain pointers themselves.
DAWN_UNUSED_FUNC(CommandEncoderFinishGetExtraRequiredSize);

DAWN_DECLARE_UNUSED void CommandEncoderFinishSerialize(const CommandEncoderFinishCmd& record, CommandEncoderFinishTransfer* transfer,
                       char** buffer, const ObjectIdProvider& provider) {
    DAWN_UNUSED(buffer);

    transfer->commandId = WireCmd::CommandEncoderFinish;

    transfer->self = provider.GetId(record.self);

    transfer->result = record.result;





    bool has_descriptor = record.descriptor != nullptr;
    transfer->has_descriptor = has_descriptor;
    if (has_descriptor)
    {
        size_t memberLength = 1;
        auto memberBuffer = reinterpret_cast<WGPUCommandBufferDescriptorTransfer*>(*buffer);
        *buffer += memberLength * sizeof(WGPUCommandBufferDescriptorTransfer);

        for (size_t i = 0; i < memberLength; ++i) {
            WGPUCommandBufferDescriptorSerialize(record.descriptor[i], &memberBuffer[i], buffer, provider);

        }
    }
}
DAWN_UNUSED_FUNC(CommandEncoderFinishSerialize);

DAWN_DECLARE_UNUSED DeserializeResult CommandEncoderFinishDeserialize(CommandEncoderFinishCmd* record, const volatile CommandEncoderFinishTransfer* transfer,
                                      const volatile char** buffer, size_t* size, DeserializeAllocator* allocator, const ObjectIdResolver& resolver) {
    DAWN_UNUSED(allocator);
    DAWN_UNUSED(buffer);
    DAWN_UNUSED(size);

    ASSERT(transfer->commandId == WireCmd::CommandEncoderFinish);

    record->selfId = transfer->self;

    DESERIALIZE_TRY(resolver.GetFromId(transfer->self, &record->self));
    record->result = transfer->result;





    bool has_descriptor = transfer->has_descriptor;
    record->descriptor = nullptr;
    if (has_descriptor)
    {
        size_t memberLength = 1;
        auto memberBuffer = reinterpret_cast<const volatile WGPUCommandBufferDescriptorTransfer*>(buffer);
        DESERIALIZE_TRY(GetPtrFromBuffer(buffer, size, memberLength, &memberBuffer));

        WGPUCommandBufferDescriptor* copiedMembers = nullptr;
        DESERIALIZE_TRY(GetSpace(allocator, memberLength, &copiedMembers));
        record->descriptor = copiedMembers;

        for (size_t i = 0; i < memberLength; ++i) {
            DESERIALIZE_TRY(WGPUCommandBufferDescriptorDeserialize(&copiedMembers[i], &memberBuffer[i], buffer, size, allocator, resolver));
        }
    }

    return DeserializeResult::Success;
}
DAWN_UNUSED_FUNC(CommandEncoderFinishDeserialize);

        
struct CommandEncoderInsertDebugMarkerTransfer : CmdHeader {
    static_assert(1 <= 1,
                  "Record must be at most one of is_cmd, extensible, and chained.");
    WireCmd commandId;

    ObjectId self;

    size_t markerLabelStrlen;

};

static_assert(offsetof(CommandEncoderInsertDebugMarkerTransfer, commandSize) == 0, "");
static_assert(offsetof(CommandEncoderInsertDebugMarkerTransfer, commandId) == sizeof(CmdHeader), "");


DAWN_DECLARE_UNUSED size_t CommandEncoderInsertDebugMarkerGetExtraRequiredSize(const CommandEncoderInsertDebugMarkerCmd& record) {
    DAWN_UNUSED(record);

    size_t result = 0;



    {
    result += std::strlen(record.markerLabel);
    }

    {
    }

    return result;
}
// GetExtraRequiredSize isn't used for structures that are value members of other structures
// because we assume they cannot contain pointers themselves.
DAWN_UNUSED_FUNC(CommandEncoderInsertDebugMarkerGetExtraRequiredSize);

DAWN_DECLARE_UNUSED void CommandEncoderInsertDebugMarkerSerialize(const CommandEncoderInsertDebugMarkerCmd& record, CommandEncoderInsertDebugMarkerTransfer* transfer,
                       char** buffer, const ObjectIdProvider& provider) {
    DAWN_UNUSED(buffer);

    transfer->commandId = WireCmd::CommandEncoderInsertDebugMarker;

    transfer->self = provider.GetId(record.self);





    {
    transfer->markerLabelStrlen = std::strlen(record.markerLabel);

    memcpy(*buffer, record.markerLabel, transfer->markerLabelStrlen);
    *buffer += transfer->markerLabelStrlen;
    }

}
DAWN_UNUSED_FUNC(CommandEncoderInsertDebugMarkerSerialize);

DAWN_DECLARE_UNUSED DeserializeResult CommandEncoderInsertDebugMarkerDeserialize(CommandEncoderInsertDebugMarkerCmd* record, const volatile CommandEncoderInsertDebugMarkerTransfer* transfer,
                                      const volatile char** buffer, size_t* size, DeserializeAllocator* allocator, const ObjectIdResolver& resolver) {
    DAWN_UNUSED(allocator);
    DAWN_UNUSED(buffer);
    DAWN_UNUSED(size);

    ASSERT(transfer->commandId == WireCmd::CommandEncoderInsertDebugMarker);

    record->selfId = transfer->self;

    DESERIALIZE_TRY(resolver.GetFromId(transfer->self, &record->self));




    {
        size_t stringLength = transfer->markerLabelStrlen;
        const volatile char* stringInBuffer = nullptr;
        DESERIALIZE_TRY(GetPtrFromBuffer(buffer, size, stringLength, &stringInBuffer));

        char* copiedString = nullptr;
        DESERIALIZE_TRY(GetSpace(allocator, stringLength + 1, &copiedString));
        std::copy(stringInBuffer, stringInBuffer + stringLength, copiedString);
        copiedString[stringLength] = '\0';
        record->markerLabel = copiedString;
    }


    return DeserializeResult::Success;
}
DAWN_UNUSED_FUNC(CommandEncoderInsertDebugMarkerDeserialize);

        
struct CommandEncoderPopDebugGroupTransfer : CmdHeader {
    static_assert(1 <= 1,
                  "Record must be at most one of is_cmd, extensible, and chained.");
    WireCmd commandId;

    ObjectId self;


};

static_assert(offsetof(CommandEncoderPopDebugGroupTransfer, commandSize) == 0, "");
static_assert(offsetof(CommandEncoderPopDebugGroupTransfer, commandId) == sizeof(CmdHeader), "");


DAWN_DECLARE_UNUSED size_t CommandEncoderPopDebugGroupGetExtraRequiredSize(const CommandEncoderPopDebugGroupCmd& record) {
    DAWN_UNUSED(record);

    size_t result = 0;



    {
    }

    return result;
}
// GetExtraRequiredSize isn't used for structures that are value members of other structures
// because we assume they cannot contain pointers themselves.
DAWN_UNUSED_FUNC(CommandEncoderPopDebugGroupGetExtraRequiredSize);

DAWN_DECLARE_UNUSED void CommandEncoderPopDebugGroupSerialize(const CommandEncoderPopDebugGroupCmd& record, CommandEncoderPopDebugGroupTransfer* transfer,
                       char** buffer, const ObjectIdProvider& provider) {
    DAWN_UNUSED(buffer);

    transfer->commandId = WireCmd::CommandEncoderPopDebugGroup;

    transfer->self = provider.GetId(record.self);





}
DAWN_UNUSED_FUNC(CommandEncoderPopDebugGroupSerialize);

DAWN_DECLARE_UNUSED DeserializeResult CommandEncoderPopDebugGroupDeserialize(CommandEncoderPopDebugGroupCmd* record, const volatile CommandEncoderPopDebugGroupTransfer* transfer,
                                      const volatile char** buffer, size_t* size, DeserializeAllocator* allocator, const ObjectIdResolver& resolver) {
    DAWN_UNUSED(allocator);
    DAWN_UNUSED(buffer);
    DAWN_UNUSED(size);

    ASSERT(transfer->commandId == WireCmd::CommandEncoderPopDebugGroup);

    record->selfId = transfer->self;

    DESERIALIZE_TRY(resolver.GetFromId(transfer->self, &record->self));





    return DeserializeResult::Success;
}
DAWN_UNUSED_FUNC(CommandEncoderPopDebugGroupDeserialize);

        
struct CommandEncoderPushDebugGroupTransfer : CmdHeader {
    static_assert(1 <= 1,
                  "Record must be at most one of is_cmd, extensible, and chained.");
    WireCmd commandId;

    ObjectId self;

    size_t groupLabelStrlen;

};

static_assert(offsetof(CommandEncoderPushDebugGroupTransfer, commandSize) == 0, "");
static_assert(offsetof(CommandEncoderPushDebugGroupTransfer, commandId) == sizeof(CmdHeader), "");


DAWN_DECLARE_UNUSED size_t CommandEncoderPushDebugGroupGetExtraRequiredSize(const CommandEncoderPushDebugGroupCmd& record) {
    DAWN_UNUSED(record);

    size_t result = 0;



    {
    result += std::strlen(record.groupLabel);
    }

    {
    }

    return result;
}
// GetExtraRequiredSize isn't used for structures that are value members of other structures
// because we assume they cannot contain pointers themselves.
DAWN_UNUSED_FUNC(CommandEncoderPushDebugGroupGetExtraRequiredSize);

DAWN_DECLARE_UNUSED void CommandEncoderPushDebugGroupSerialize(const CommandEncoderPushDebugGroupCmd& record, CommandEncoderPushDebugGroupTransfer* transfer,
                       char** buffer, const ObjectIdProvider& provider) {
    DAWN_UNUSED(buffer);

    transfer->commandId = WireCmd::CommandEncoderPushDebugGroup;

    transfer->self = provider.GetId(record.self);





    {
    transfer->groupLabelStrlen = std::strlen(record.groupLabel);

    memcpy(*buffer, record.groupLabel, transfer->groupLabelStrlen);
    *buffer += transfer->groupLabelStrlen;
    }

}
DAWN_UNUSED_FUNC(CommandEncoderPushDebugGroupSerialize);

DAWN_DECLARE_UNUSED DeserializeResult CommandEncoderPushDebugGroupDeserialize(CommandEncoderPushDebugGroupCmd* record, const volatile CommandEncoderPushDebugGroupTransfer* transfer,
                                      const volatile char** buffer, size_t* size, DeserializeAllocator* allocator, const ObjectIdResolver& resolver) {
    DAWN_UNUSED(allocator);
    DAWN_UNUSED(buffer);
    DAWN_UNUSED(size);

    ASSERT(transfer->commandId == WireCmd::CommandEncoderPushDebugGroup);

    record->selfId = transfer->self;

    DESERIALIZE_TRY(resolver.GetFromId(transfer->self, &record->self));




    {
        size_t stringLength = transfer->groupLabelStrlen;
        const volatile char* stringInBuffer = nullptr;
        DESERIALIZE_TRY(GetPtrFromBuffer(buffer, size, stringLength, &stringInBuffer));

        char* copiedString = nullptr;
        DESERIALIZE_TRY(GetSpace(allocator, stringLength + 1, &copiedString));
        std::copy(stringInBuffer, stringInBuffer + stringLength, copiedString);
        copiedString[stringLength] = '\0';
        record->groupLabel = copiedString;
    }


    return DeserializeResult::Success;
}
DAWN_UNUSED_FUNC(CommandEncoderPushDebugGroupDeserialize);

        
struct CommandEncoderResolveQuerySetTransfer : CmdHeader {
    static_assert(1 <= 1,
                  "Record must be at most one of is_cmd, extensible, and chained.");
    WireCmd commandId;

    ObjectId self;
    ObjectId querySet;
    uint32_t firstQuery;
    uint32_t queryCount;
    ObjectId destination;
    uint64_t destinationOffset;


};

static_assert(offsetof(CommandEncoderResolveQuerySetTransfer, commandSize) == 0, "");
static_assert(offsetof(CommandEncoderResolveQuerySetTransfer, commandId) == sizeof(CmdHeader), "");


DAWN_DECLARE_UNUSED size_t CommandEncoderResolveQuerySetGetExtraRequiredSize(const CommandEncoderResolveQuerySetCmd& record) {
    DAWN_UNUSED(record);

    size_t result = 0;



    {
    }
    {
    }
    {
    }
    {
    }
    {
    }
    {
    }

    return result;
}
// GetExtraRequiredSize isn't used for structures that are value members of other structures
// because we assume they cannot contain pointers themselves.
DAWN_UNUSED_FUNC(CommandEncoderResolveQuerySetGetExtraRequiredSize);

DAWN_DECLARE_UNUSED void CommandEncoderResolveQuerySetSerialize(const CommandEncoderResolveQuerySetCmd& record, CommandEncoderResolveQuerySetTransfer* transfer,
                       char** buffer, const ObjectIdProvider& provider) {
    DAWN_UNUSED(buffer);

    transfer->commandId = WireCmd::CommandEncoderResolveQuerySet;

    transfer->self = provider.GetId(record.self);

    transfer->querySet = provider.GetId(record.querySet);

    transfer->firstQuery = record.firstQuery;
    transfer->queryCount = record.queryCount;
    transfer->destination = provider.GetId(record.destination);

    transfer->destinationOffset = record.destinationOffset;




}
DAWN_UNUSED_FUNC(CommandEncoderResolveQuerySetSerialize);

DAWN_DECLARE_UNUSED DeserializeResult CommandEncoderResolveQuerySetDeserialize(CommandEncoderResolveQuerySetCmd* record, const volatile CommandEncoderResolveQuerySetTransfer* transfer,
                                      const volatile char** buffer, size_t* size, DeserializeAllocator* allocator, const ObjectIdResolver& resolver) {
    DAWN_UNUSED(allocator);
    DAWN_UNUSED(buffer);
    DAWN_UNUSED(size);

    ASSERT(transfer->commandId == WireCmd::CommandEncoderResolveQuerySet);

    record->selfId = transfer->self;

    DESERIALIZE_TRY(resolver.GetFromId(transfer->self, &record->self));
    DESERIALIZE_TRY(resolver.GetFromId(transfer->querySet, &record->querySet));
    record->firstQuery = transfer->firstQuery;
    record->queryCount = transfer->queryCount;
    DESERIALIZE_TRY(resolver.GetFromId(transfer->destination, &record->destination));
    record->destinationOffset = transfer->destinationOffset;





    return DeserializeResult::Success;
}
DAWN_UNUSED_FUNC(CommandEncoderResolveQuerySetDeserialize);

        
struct CommandEncoderWriteTimestampTransfer : CmdHeader {
    static_assert(1 <= 1,
                  "Record must be at most one of is_cmd, extensible, and chained.");
    WireCmd commandId;

    ObjectId self;
    ObjectId querySet;
    uint32_t queryIndex;


};

static_assert(offsetof(CommandEncoderWriteTimestampTransfer, commandSize) == 0, "");
static_assert(offsetof(CommandEncoderWriteTimestampTransfer, commandId) == sizeof(CmdHeader), "");


DAWN_DECLARE_UNUSED size_t CommandEncoderWriteTimestampGetExtraRequiredSize(const CommandEncoderWriteTimestampCmd& record) {
    DAWN_UNUSED(record);

    size_t result = 0;



    {
    }
    {
    }
    {
    }

    return result;
}
// GetExtraRequiredSize isn't used for structures that are value members of other structures
// because we assume they cannot contain pointers themselves.
DAWN_UNUSED_FUNC(CommandEncoderWriteTimestampGetExtraRequiredSize);

DAWN_DECLARE_UNUSED void CommandEncoderWriteTimestampSerialize(const CommandEncoderWriteTimestampCmd& record, CommandEncoderWriteTimestampTransfer* transfer,
                       char** buffer, const ObjectIdProvider& provider) {
    DAWN_UNUSED(buffer);

    transfer->commandId = WireCmd::CommandEncoderWriteTimestamp;

    transfer->self = provider.GetId(record.self);

    transfer->querySet = provider.GetId(record.querySet);

    transfer->queryIndex = record.queryIndex;




}
DAWN_UNUSED_FUNC(CommandEncoderWriteTimestampSerialize);

DAWN_DECLARE_UNUSED DeserializeResult CommandEncoderWriteTimestampDeserialize(CommandEncoderWriteTimestampCmd* record, const volatile CommandEncoderWriteTimestampTransfer* transfer,
                                      const volatile char** buffer, size_t* size, DeserializeAllocator* allocator, const ObjectIdResolver& resolver) {
    DAWN_UNUSED(allocator);
    DAWN_UNUSED(buffer);
    DAWN_UNUSED(size);

    ASSERT(transfer->commandId == WireCmd::CommandEncoderWriteTimestamp);

    record->selfId = transfer->self;

    DESERIALIZE_TRY(resolver.GetFromId(transfer->self, &record->self));
    DESERIALIZE_TRY(resolver.GetFromId(transfer->querySet, &record->querySet));
    record->queryIndex = transfer->queryIndex;





    return DeserializeResult::Success;
}
DAWN_UNUSED_FUNC(CommandEncoderWriteTimestampDeserialize);

        
struct ComputePassEncoderDispatchTransfer : CmdHeader {
    static_assert(1 <= 1,
                  "Record must be at most one of is_cmd, extensible, and chained.");
    WireCmd commandId;

    ObjectId self;
    uint32_t x;
    uint32_t y;
    uint32_t z;


};

static_assert(offsetof(ComputePassEncoderDispatchTransfer, commandSize) == 0, "");
static_assert(offsetof(ComputePassEncoderDispatchTransfer, commandId) == sizeof(CmdHeader), "");


DAWN_DECLARE_UNUSED size_t ComputePassEncoderDispatchGetExtraRequiredSize(const ComputePassEncoderDispatchCmd& record) {
    DAWN_UNUSED(record);

    size_t result = 0;



    {
    }
    {
    }
    {
    }
    {
    }

    return result;
}
// GetExtraRequiredSize isn't used for structures that are value members of other structures
// because we assume they cannot contain pointers themselves.
DAWN_UNUSED_FUNC(ComputePassEncoderDispatchGetExtraRequiredSize);

DAWN_DECLARE_UNUSED void ComputePassEncoderDispatchSerialize(const ComputePassEncoderDispatchCmd& record, ComputePassEncoderDispatchTransfer* transfer,
                       char** buffer, const ObjectIdProvider& provider) {
    DAWN_UNUSED(buffer);

    transfer->commandId = WireCmd::ComputePassEncoderDispatch;

    transfer->self = provider.GetId(record.self);

    transfer->x = record.x;
    transfer->y = record.y;
    transfer->z = record.z;




}
DAWN_UNUSED_FUNC(ComputePassEncoderDispatchSerialize);

DAWN_DECLARE_UNUSED DeserializeResult ComputePassEncoderDispatchDeserialize(ComputePassEncoderDispatchCmd* record, const volatile ComputePassEncoderDispatchTransfer* transfer,
                                      const volatile char** buffer, size_t* size, DeserializeAllocator* allocator, const ObjectIdResolver& resolver) {
    DAWN_UNUSED(allocator);
    DAWN_UNUSED(buffer);
    DAWN_UNUSED(size);

    ASSERT(transfer->commandId == WireCmd::ComputePassEncoderDispatch);

    record->selfId = transfer->self;

    DESERIALIZE_TRY(resolver.GetFromId(transfer->self, &record->self));
    record->x = transfer->x;
    record->y = transfer->y;
    record->z = transfer->z;





    return DeserializeResult::Success;
}
DAWN_UNUSED_FUNC(ComputePassEncoderDispatchDeserialize);

        
struct ComputePassEncoderDispatchIndirectTransfer : CmdHeader {
    static_assert(1 <= 1,
                  "Record must be at most one of is_cmd, extensible, and chained.");
    WireCmd commandId;

    ObjectId self;
    ObjectId indirectBuffer;
    uint64_t indirectOffset;


};

static_assert(offsetof(ComputePassEncoderDispatchIndirectTransfer, commandSize) == 0, "");
static_assert(offsetof(ComputePassEncoderDispatchIndirectTransfer, commandId) == sizeof(CmdHeader), "");


DAWN_DECLARE_UNUSED size_t ComputePassEncoderDispatchIndirectGetExtraRequiredSize(const ComputePassEncoderDispatchIndirectCmd& record) {
    DAWN_UNUSED(record);

    size_t result = 0;



    {
    }
    {
    }
    {
    }

    return result;
}
// GetExtraRequiredSize isn't used for structures that are value members of other structures
// because we assume they cannot contain pointers themselves.
DAWN_UNUSED_FUNC(ComputePassEncoderDispatchIndirectGetExtraRequiredSize);

DAWN_DECLARE_UNUSED void ComputePassEncoderDispatchIndirectSerialize(const ComputePassEncoderDispatchIndirectCmd& record, ComputePassEncoderDispatchIndirectTransfer* transfer,
                       char** buffer, const ObjectIdProvider& provider) {
    DAWN_UNUSED(buffer);

    transfer->commandId = WireCmd::ComputePassEncoderDispatchIndirect;

    transfer->self = provider.GetId(record.self);

    transfer->indirectBuffer = provider.GetId(record.indirectBuffer);

    transfer->indirectOffset = record.indirectOffset;




}
DAWN_UNUSED_FUNC(ComputePassEncoderDispatchIndirectSerialize);

DAWN_DECLARE_UNUSED DeserializeResult ComputePassEncoderDispatchIndirectDeserialize(ComputePassEncoderDispatchIndirectCmd* record, const volatile ComputePassEncoderDispatchIndirectTransfer* transfer,
                                      const volatile char** buffer, size_t* size, DeserializeAllocator* allocator, const ObjectIdResolver& resolver) {
    DAWN_UNUSED(allocator);
    DAWN_UNUSED(buffer);
    DAWN_UNUSED(size);

    ASSERT(transfer->commandId == WireCmd::ComputePassEncoderDispatchIndirect);

    record->selfId = transfer->self;

    DESERIALIZE_TRY(resolver.GetFromId(transfer->self, &record->self));
    DESERIALIZE_TRY(resolver.GetFromId(transfer->indirectBuffer, &record->indirectBuffer));
    record->indirectOffset = transfer->indirectOffset;





    return DeserializeResult::Success;
}
DAWN_UNUSED_FUNC(ComputePassEncoderDispatchIndirectDeserialize);

        
struct ComputePassEncoderEndPassTransfer : CmdHeader {
    static_assert(1 <= 1,
                  "Record must be at most one of is_cmd, extensible, and chained.");
    WireCmd commandId;

    ObjectId self;


};

static_assert(offsetof(ComputePassEncoderEndPassTransfer, commandSize) == 0, "");
static_assert(offsetof(ComputePassEncoderEndPassTransfer, commandId) == sizeof(CmdHeader), "");


DAWN_DECLARE_UNUSED size_t ComputePassEncoderEndPassGetExtraRequiredSize(const ComputePassEncoderEndPassCmd& record) {
    DAWN_UNUSED(record);

    size_t result = 0;



    {
    }

    return result;
}
// GetExtraRequiredSize isn't used for structures that are value members of other structures
// because we assume they cannot contain pointers themselves.
DAWN_UNUSED_FUNC(ComputePassEncoderEndPassGetExtraRequiredSize);

DAWN_DECLARE_UNUSED void ComputePassEncoderEndPassSerialize(const ComputePassEncoderEndPassCmd& record, ComputePassEncoderEndPassTransfer* transfer,
                       char** buffer, const ObjectIdProvider& provider) {
    DAWN_UNUSED(buffer);

    transfer->commandId = WireCmd::ComputePassEncoderEndPass;

    transfer->self = provider.GetId(record.self);





}
DAWN_UNUSED_FUNC(ComputePassEncoderEndPassSerialize);

DAWN_DECLARE_UNUSED DeserializeResult ComputePassEncoderEndPassDeserialize(ComputePassEncoderEndPassCmd* record, const volatile ComputePassEncoderEndPassTransfer* transfer,
                                      const volatile char** buffer, size_t* size, DeserializeAllocator* allocator, const ObjectIdResolver& resolver) {
    DAWN_UNUSED(allocator);
    DAWN_UNUSED(buffer);
    DAWN_UNUSED(size);

    ASSERT(transfer->commandId == WireCmd::ComputePassEncoderEndPass);

    record->selfId = transfer->self;

    DESERIALIZE_TRY(resolver.GetFromId(transfer->self, &record->self));





    return DeserializeResult::Success;
}
DAWN_UNUSED_FUNC(ComputePassEncoderEndPassDeserialize);

        
struct ComputePassEncoderInsertDebugMarkerTransfer : CmdHeader {
    static_assert(1 <= 1,
                  "Record must be at most one of is_cmd, extensible, and chained.");
    WireCmd commandId;

    ObjectId self;

    size_t markerLabelStrlen;

};

static_assert(offsetof(ComputePassEncoderInsertDebugMarkerTransfer, commandSize) == 0, "");
static_assert(offsetof(ComputePassEncoderInsertDebugMarkerTransfer, commandId) == sizeof(CmdHeader), "");


DAWN_DECLARE_UNUSED size_t ComputePassEncoderInsertDebugMarkerGetExtraRequiredSize(const ComputePassEncoderInsertDebugMarkerCmd& record) {
    DAWN_UNUSED(record);

    size_t result = 0;



    {
    result += std::strlen(record.markerLabel);
    }

    {
    }

    return result;
}
// GetExtraRequiredSize isn't used for structures that are value members of other structures
// because we assume they cannot contain pointers themselves.
DAWN_UNUSED_FUNC(ComputePassEncoderInsertDebugMarkerGetExtraRequiredSize);

DAWN_DECLARE_UNUSED void ComputePassEncoderInsertDebugMarkerSerialize(const ComputePassEncoderInsertDebugMarkerCmd& record, ComputePassEncoderInsertDebugMarkerTransfer* transfer,
                       char** buffer, const ObjectIdProvider& provider) {
    DAWN_UNUSED(buffer);

    transfer->commandId = WireCmd::ComputePassEncoderInsertDebugMarker;

    transfer->self = provider.GetId(record.self);





    {
    transfer->markerLabelStrlen = std::strlen(record.markerLabel);

    memcpy(*buffer, record.markerLabel, transfer->markerLabelStrlen);
    *buffer += transfer->markerLabelStrlen;
    }

}
DAWN_UNUSED_FUNC(ComputePassEncoderInsertDebugMarkerSerialize);

DAWN_DECLARE_UNUSED DeserializeResult ComputePassEncoderInsertDebugMarkerDeserialize(ComputePassEncoderInsertDebugMarkerCmd* record, const volatile ComputePassEncoderInsertDebugMarkerTransfer* transfer,
                                      const volatile char** buffer, size_t* size, DeserializeAllocator* allocator, const ObjectIdResolver& resolver) {
    DAWN_UNUSED(allocator);
    DAWN_UNUSED(buffer);
    DAWN_UNUSED(size);

    ASSERT(transfer->commandId == WireCmd::ComputePassEncoderInsertDebugMarker);

    record->selfId = transfer->self;

    DESERIALIZE_TRY(resolver.GetFromId(transfer->self, &record->self));




    {
        size_t stringLength = transfer->markerLabelStrlen;
        const volatile char* stringInBuffer = nullptr;
        DESERIALIZE_TRY(GetPtrFromBuffer(buffer, size, stringLength, &stringInBuffer));

        char* copiedString = nullptr;
        DESERIALIZE_TRY(GetSpace(allocator, stringLength + 1, &copiedString));
        std::copy(stringInBuffer, stringInBuffer + stringLength, copiedString);
        copiedString[stringLength] = '\0';
        record->markerLabel = copiedString;
    }


    return DeserializeResult::Success;
}
DAWN_UNUSED_FUNC(ComputePassEncoderInsertDebugMarkerDeserialize);

        
struct ComputePassEncoderPopDebugGroupTransfer : CmdHeader {
    static_assert(1 <= 1,
                  "Record must be at most one of is_cmd, extensible, and chained.");
    WireCmd commandId;

    ObjectId self;


};

static_assert(offsetof(ComputePassEncoderPopDebugGroupTransfer, commandSize) == 0, "");
static_assert(offsetof(ComputePassEncoderPopDebugGroupTransfer, commandId) == sizeof(CmdHeader), "");


DAWN_DECLARE_UNUSED size_t ComputePassEncoderPopDebugGroupGetExtraRequiredSize(const ComputePassEncoderPopDebugGroupCmd& record) {
    DAWN_UNUSED(record);

    size_t result = 0;



    {
    }

    return result;
}
// GetExtraRequiredSize isn't used for structures that are value members of other structures
// because we assume they cannot contain pointers themselves.
DAWN_UNUSED_FUNC(ComputePassEncoderPopDebugGroupGetExtraRequiredSize);

DAWN_DECLARE_UNUSED void ComputePassEncoderPopDebugGroupSerialize(const ComputePassEncoderPopDebugGroupCmd& record, ComputePassEncoderPopDebugGroupTransfer* transfer,
                       char** buffer, const ObjectIdProvider& provider) {
    DAWN_UNUSED(buffer);

    transfer->commandId = WireCmd::ComputePassEncoderPopDebugGroup;

    transfer->self = provider.GetId(record.self);





}
DAWN_UNUSED_FUNC(ComputePassEncoderPopDebugGroupSerialize);

DAWN_DECLARE_UNUSED DeserializeResult ComputePassEncoderPopDebugGroupDeserialize(ComputePassEncoderPopDebugGroupCmd* record, const volatile ComputePassEncoderPopDebugGroupTransfer* transfer,
                                      const volatile char** buffer, size_t* size, DeserializeAllocator* allocator, const ObjectIdResolver& resolver) {
    DAWN_UNUSED(allocator);
    DAWN_UNUSED(buffer);
    DAWN_UNUSED(size);

    ASSERT(transfer->commandId == WireCmd::ComputePassEncoderPopDebugGroup);

    record->selfId = transfer->self;

    DESERIALIZE_TRY(resolver.GetFromId(transfer->self, &record->self));





    return DeserializeResult::Success;
}
DAWN_UNUSED_FUNC(ComputePassEncoderPopDebugGroupDeserialize);

        
struct ComputePassEncoderPushDebugGroupTransfer : CmdHeader {
    static_assert(1 <= 1,
                  "Record must be at most one of is_cmd, extensible, and chained.");
    WireCmd commandId;

    ObjectId self;

    size_t groupLabelStrlen;

};

static_assert(offsetof(ComputePassEncoderPushDebugGroupTransfer, commandSize) == 0, "");
static_assert(offsetof(ComputePassEncoderPushDebugGroupTransfer, commandId) == sizeof(CmdHeader), "");


DAWN_DECLARE_UNUSED size_t ComputePassEncoderPushDebugGroupGetExtraRequiredSize(const ComputePassEncoderPushDebugGroupCmd& record) {
    DAWN_UNUSED(record);

    size_t result = 0;



    {
    result += std::strlen(record.groupLabel);
    }

    {
    }

    return result;
}
// GetExtraRequiredSize isn't used for structures that are value members of other structures
// because we assume they cannot contain pointers themselves.
DAWN_UNUSED_FUNC(ComputePassEncoderPushDebugGroupGetExtraRequiredSize);

DAWN_DECLARE_UNUSED void ComputePassEncoderPushDebugGroupSerialize(const ComputePassEncoderPushDebugGroupCmd& record, ComputePassEncoderPushDebugGroupTransfer* transfer,
                       char** buffer, const ObjectIdProvider& provider) {
    DAWN_UNUSED(buffer);

    transfer->commandId = WireCmd::ComputePassEncoderPushDebugGroup;

    transfer->self = provider.GetId(record.self);





    {
    transfer->groupLabelStrlen = std::strlen(record.groupLabel);

    memcpy(*buffer, record.groupLabel, transfer->groupLabelStrlen);
    *buffer += transfer->groupLabelStrlen;
    }

}
DAWN_UNUSED_FUNC(ComputePassEncoderPushDebugGroupSerialize);

DAWN_DECLARE_UNUSED DeserializeResult ComputePassEncoderPushDebugGroupDeserialize(ComputePassEncoderPushDebugGroupCmd* record, const volatile ComputePassEncoderPushDebugGroupTransfer* transfer,
                                      const volatile char** buffer, size_t* size, DeserializeAllocator* allocator, const ObjectIdResolver& resolver) {
    DAWN_UNUSED(allocator);
    DAWN_UNUSED(buffer);
    DAWN_UNUSED(size);

    ASSERT(transfer->commandId == WireCmd::ComputePassEncoderPushDebugGroup);

    record->selfId = transfer->self;

    DESERIALIZE_TRY(resolver.GetFromId(transfer->self, &record->self));




    {
        size_t stringLength = transfer->groupLabelStrlen;
        const volatile char* stringInBuffer = nullptr;
        DESERIALIZE_TRY(GetPtrFromBuffer(buffer, size, stringLength, &stringInBuffer));

        char* copiedString = nullptr;
        DESERIALIZE_TRY(GetSpace(allocator, stringLength + 1, &copiedString));
        std::copy(stringInBuffer, stringInBuffer + stringLength, copiedString);
        copiedString[stringLength] = '\0';
        record->groupLabel = copiedString;
    }


    return DeserializeResult::Success;
}
DAWN_UNUSED_FUNC(ComputePassEncoderPushDebugGroupDeserialize);

        
struct ComputePassEncoderSetBindGroupTransfer : CmdHeader {
    static_assert(1 <= 1,
                  "Record must be at most one of is_cmd, extensible, and chained.");
    WireCmd commandId;

    ObjectId self;
    uint32_t groupIndex;
    ObjectId group;
    uint32_t dynamicOffsetCount;


    bool has_dynamicOffsets;
};

static_assert(offsetof(ComputePassEncoderSetBindGroupTransfer, commandSize) == 0, "");
static_assert(offsetof(ComputePassEncoderSetBindGroupTransfer, commandId) == sizeof(CmdHeader), "");


DAWN_DECLARE_UNUSED size_t ComputePassEncoderSetBindGroupGetExtraRequiredSize(const ComputePassEncoderSetBindGroupCmd& record) {
    DAWN_UNUSED(record);

    size_t result = 0;



    {
    }
    {
    }
    {
    }
    {
    }
    if (record.dynamicOffsets != nullptr)
    {
        size_t memberLength = record.dynamicOffsetCount;
        result += memberLength * sizeof(uint32_t);
    }

    return result;
}
// GetExtraRequiredSize isn't used for structures that are value members of other structures
// because we assume they cannot contain pointers themselves.
DAWN_UNUSED_FUNC(ComputePassEncoderSetBindGroupGetExtraRequiredSize);

DAWN_DECLARE_UNUSED void ComputePassEncoderSetBindGroupSerialize(const ComputePassEncoderSetBindGroupCmd& record, ComputePassEncoderSetBindGroupTransfer* transfer,
                       char** buffer, const ObjectIdProvider& provider) {
    DAWN_UNUSED(buffer);

    transfer->commandId = WireCmd::ComputePassEncoderSetBindGroup;

    transfer->self = provider.GetId(record.self);

    transfer->groupIndex = record.groupIndex;
    transfer->group = provider.GetId(record.group);

    transfer->dynamicOffsetCount = record.dynamicOffsetCount;





    bool has_dynamicOffsets = record.dynamicOffsets != nullptr;
    transfer->has_dynamicOffsets = has_dynamicOffsets;
    if (has_dynamicOffsets)
    {
        size_t memberLength = record.dynamicOffsetCount;
        auto memberBuffer = reinterpret_cast<uint32_t*>(*buffer);
        *buffer += memberLength * sizeof(uint32_t);

        for (size_t i = 0; i < memberLength; ++i) {
            memberBuffer[i] = record.dynamicOffsets[i];
        }
    }
}
DAWN_UNUSED_FUNC(ComputePassEncoderSetBindGroupSerialize);

DAWN_DECLARE_UNUSED DeserializeResult ComputePassEncoderSetBindGroupDeserialize(ComputePassEncoderSetBindGroupCmd* record, const volatile ComputePassEncoderSetBindGroupTransfer* transfer,
                                      const volatile char** buffer, size_t* size, DeserializeAllocator* allocator, const ObjectIdResolver& resolver) {
    DAWN_UNUSED(allocator);
    DAWN_UNUSED(buffer);
    DAWN_UNUSED(size);

    ASSERT(transfer->commandId == WireCmd::ComputePassEncoderSetBindGroup);

    record->selfId = transfer->self;

    DESERIALIZE_TRY(resolver.GetFromId(transfer->self, &record->self));
    record->groupIndex = transfer->groupIndex;
    DESERIALIZE_TRY(resolver.GetFromId(transfer->group, &record->group));
    record->dynamicOffsetCount = transfer->dynamicOffsetCount;





    bool has_dynamicOffsets = transfer->has_dynamicOffsets;
    record->dynamicOffsets = nullptr;
    if (has_dynamicOffsets)
    {
        size_t memberLength = record->dynamicOffsetCount;
        auto memberBuffer = reinterpret_cast<const volatile uint32_t*>(buffer);
        DESERIALIZE_TRY(GetPtrFromBuffer(buffer, size, memberLength, &memberBuffer));

        uint32_t* copiedMembers = nullptr;
        DESERIALIZE_TRY(GetSpace(allocator, memberLength, &copiedMembers));
        record->dynamicOffsets = copiedMembers;

        for (size_t i = 0; i < memberLength; ++i) {
            copiedMembers[i] = memberBuffer[i];
        }
    }

    return DeserializeResult::Success;
}
DAWN_UNUSED_FUNC(ComputePassEncoderSetBindGroupDeserialize);

        
struct ComputePassEncoderSetPipelineTransfer : CmdHeader {
    static_assert(1 <= 1,
                  "Record must be at most one of is_cmd, extensible, and chained.");
    WireCmd commandId;

    ObjectId self;
    ObjectId pipeline;


};

static_assert(offsetof(ComputePassEncoderSetPipelineTransfer, commandSize) == 0, "");
static_assert(offsetof(ComputePassEncoderSetPipelineTransfer, commandId) == sizeof(CmdHeader), "");


DAWN_DECLARE_UNUSED size_t ComputePassEncoderSetPipelineGetExtraRequiredSize(const ComputePassEncoderSetPipelineCmd& record) {
    DAWN_UNUSED(record);

    size_t result = 0;



    {
    }
    {
    }

    return result;
}
// GetExtraRequiredSize isn't used for structures that are value members of other structures
// because we assume they cannot contain pointers themselves.
DAWN_UNUSED_FUNC(ComputePassEncoderSetPipelineGetExtraRequiredSize);

DAWN_DECLARE_UNUSED void ComputePassEncoderSetPipelineSerialize(const ComputePassEncoderSetPipelineCmd& record, ComputePassEncoderSetPipelineTransfer* transfer,
                       char** buffer, const ObjectIdProvider& provider) {
    DAWN_UNUSED(buffer);

    transfer->commandId = WireCmd::ComputePassEncoderSetPipeline;

    transfer->self = provider.GetId(record.self);

    transfer->pipeline = provider.GetId(record.pipeline);





}
DAWN_UNUSED_FUNC(ComputePassEncoderSetPipelineSerialize);

DAWN_DECLARE_UNUSED DeserializeResult ComputePassEncoderSetPipelineDeserialize(ComputePassEncoderSetPipelineCmd* record, const volatile ComputePassEncoderSetPipelineTransfer* transfer,
                                      const volatile char** buffer, size_t* size, DeserializeAllocator* allocator, const ObjectIdResolver& resolver) {
    DAWN_UNUSED(allocator);
    DAWN_UNUSED(buffer);
    DAWN_UNUSED(size);

    ASSERT(transfer->commandId == WireCmd::ComputePassEncoderSetPipeline);

    record->selfId = transfer->self;

    DESERIALIZE_TRY(resolver.GetFromId(transfer->self, &record->self));
    DESERIALIZE_TRY(resolver.GetFromId(transfer->pipeline, &record->pipeline));





    return DeserializeResult::Success;
}
DAWN_UNUSED_FUNC(ComputePassEncoderSetPipelineDeserialize);

        
struct ComputePassEncoderWriteTimestampTransfer : CmdHeader {
    static_assert(1 <= 1,
                  "Record must be at most one of is_cmd, extensible, and chained.");
    WireCmd commandId;

    ObjectId self;
    ObjectId querySet;
    uint32_t queryIndex;


};

static_assert(offsetof(ComputePassEncoderWriteTimestampTransfer, commandSize) == 0, "");
static_assert(offsetof(ComputePassEncoderWriteTimestampTransfer, commandId) == sizeof(CmdHeader), "");


DAWN_DECLARE_UNUSED size_t ComputePassEncoderWriteTimestampGetExtraRequiredSize(const ComputePassEncoderWriteTimestampCmd& record) {
    DAWN_UNUSED(record);

    size_t result = 0;



    {
    }
    {
    }
    {
    }

    return result;
}
// GetExtraRequiredSize isn't used for structures that are value members of other structures
// because we assume they cannot contain pointers themselves.
DAWN_UNUSED_FUNC(ComputePassEncoderWriteTimestampGetExtraRequiredSize);

DAWN_DECLARE_UNUSED void ComputePassEncoderWriteTimestampSerialize(const ComputePassEncoderWriteTimestampCmd& record, ComputePassEncoderWriteTimestampTransfer* transfer,
                       char** buffer, const ObjectIdProvider& provider) {
    DAWN_UNUSED(buffer);

    transfer->commandId = WireCmd::ComputePassEncoderWriteTimestamp;

    transfer->self = provider.GetId(record.self);

    transfer->querySet = provider.GetId(record.querySet);

    transfer->queryIndex = record.queryIndex;




}
DAWN_UNUSED_FUNC(ComputePassEncoderWriteTimestampSerialize);

DAWN_DECLARE_UNUSED DeserializeResult ComputePassEncoderWriteTimestampDeserialize(ComputePassEncoderWriteTimestampCmd* record, const volatile ComputePassEncoderWriteTimestampTransfer* transfer,
                                      const volatile char** buffer, size_t* size, DeserializeAllocator* allocator, const ObjectIdResolver& resolver) {
    DAWN_UNUSED(allocator);
    DAWN_UNUSED(buffer);
    DAWN_UNUSED(size);

    ASSERT(transfer->commandId == WireCmd::ComputePassEncoderWriteTimestamp);

    record->selfId = transfer->self;

    DESERIALIZE_TRY(resolver.GetFromId(transfer->self, &record->self));
    DESERIALIZE_TRY(resolver.GetFromId(transfer->querySet, &record->querySet));
    record->queryIndex = transfer->queryIndex;





    return DeserializeResult::Success;
}
DAWN_UNUSED_FUNC(ComputePassEncoderWriteTimestampDeserialize);

        
struct ComputePipelineGetBindGroupLayoutTransfer : CmdHeader {
    static_assert(1 <= 1,
                  "Record must be at most one of is_cmd, extensible, and chained.");
    WireCmd commandId;

    ObjectId self;
    uint32_t groupIndex;
    ObjectHandle result;


};

static_assert(offsetof(ComputePipelineGetBindGroupLayoutTransfer, commandSize) == 0, "");
static_assert(offsetof(ComputePipelineGetBindGroupLayoutTransfer, commandId) == sizeof(CmdHeader), "");


DAWN_DECLARE_UNUSED size_t ComputePipelineGetBindGroupLayoutGetExtraRequiredSize(const ComputePipelineGetBindGroupLayoutCmd& record) {
    DAWN_UNUSED(record);

    size_t result = 0;



    {
    }
    {
    }
    {
    }

    return result;
}
// GetExtraRequiredSize isn't used for structures that are value members of other structures
// because we assume they cannot contain pointers themselves.
DAWN_UNUSED_FUNC(ComputePipelineGetBindGroupLayoutGetExtraRequiredSize);

DAWN_DECLARE_UNUSED void ComputePipelineGetBindGroupLayoutSerialize(const ComputePipelineGetBindGroupLayoutCmd& record, ComputePipelineGetBindGroupLayoutTransfer* transfer,
                       char** buffer, const ObjectIdProvider& provider) {
    DAWN_UNUSED(buffer);

    transfer->commandId = WireCmd::ComputePipelineGetBindGroupLayout;

    transfer->self = provider.GetId(record.self);

    transfer->groupIndex = record.groupIndex;
    transfer->result = record.result;




}
DAWN_UNUSED_FUNC(ComputePipelineGetBindGroupLayoutSerialize);

DAWN_DECLARE_UNUSED DeserializeResult ComputePipelineGetBindGroupLayoutDeserialize(ComputePipelineGetBindGroupLayoutCmd* record, const volatile ComputePipelineGetBindGroupLayoutTransfer* transfer,
                                      const volatile char** buffer, size_t* size, DeserializeAllocator* allocator, const ObjectIdResolver& resolver) {
    DAWN_UNUSED(allocator);
    DAWN_UNUSED(buffer);
    DAWN_UNUSED(size);

    ASSERT(transfer->commandId == WireCmd::ComputePipelineGetBindGroupLayout);

    record->selfId = transfer->self;

    DESERIALIZE_TRY(resolver.GetFromId(transfer->self, &record->self));
    record->groupIndex = transfer->groupIndex;
    record->result = transfer->result;





    return DeserializeResult::Success;
}
DAWN_UNUSED_FUNC(ComputePipelineGetBindGroupLayoutDeserialize);

        
struct DestroyObjectTransfer : CmdHeader {
    static_assert(1 <= 1,
                  "Record must be at most one of is_cmd, extensible, and chained.");
    WireCmd commandId;

    ObjectType objectType;
    ObjectId objectId;


};

static_assert(offsetof(DestroyObjectTransfer, commandSize) == 0, "");
static_assert(offsetof(DestroyObjectTransfer, commandId) == sizeof(CmdHeader), "");


DAWN_DECLARE_UNUSED size_t DestroyObjectGetExtraRequiredSize(const DestroyObjectCmd& record) {
    DAWN_UNUSED(record);

    size_t result = 0;



    {
    }
    {
    }

    return result;
}
// GetExtraRequiredSize isn't used for structures that are value members of other structures
// because we assume they cannot contain pointers themselves.
DAWN_UNUSED_FUNC(DestroyObjectGetExtraRequiredSize);

DAWN_DECLARE_UNUSED void DestroyObjectSerialize(const DestroyObjectCmd& record, DestroyObjectTransfer* transfer,
                       char** buffer) {
    DAWN_UNUSED(buffer);

    transfer->commandId = WireCmd::DestroyObject;

    transfer->objectType = record.objectType;
    transfer->objectId = record.objectId;




}
DAWN_UNUSED_FUNC(DestroyObjectSerialize);

DAWN_DECLARE_UNUSED DeserializeResult DestroyObjectDeserialize(DestroyObjectCmd* record, const volatile DestroyObjectTransfer* transfer,
                                      const volatile char** buffer, size_t* size, DeserializeAllocator* allocator) {
    DAWN_UNUSED(allocator);
    DAWN_UNUSED(buffer);
    DAWN_UNUSED(size);

    ASSERT(transfer->commandId == WireCmd::DestroyObject);


    record->objectType = transfer->objectType;
    record->objectId = transfer->objectId;





    return DeserializeResult::Success;
}
DAWN_UNUSED_FUNC(DestroyObjectDeserialize);

        
struct DeviceCreateBindGroupTransfer : CmdHeader {
    static_assert(1 <= 1,
                  "Record must be at most one of is_cmd, extensible, and chained.");
    WireCmd commandId;

    ObjectId self;
    ObjectHandle result;


};

static_assert(offsetof(DeviceCreateBindGroupTransfer, commandSize) == 0, "");
static_assert(offsetof(DeviceCreateBindGroupTransfer, commandId) == sizeof(CmdHeader), "");


DAWN_DECLARE_UNUSED size_t DeviceCreateBindGroupGetExtraRequiredSize(const DeviceCreateBindGroupCmd& record) {
    DAWN_UNUSED(record);

    size_t result = 0;



    {
    }
    {
        size_t memberLength = 1;
        result += memberLength * sizeof(WGPUBindGroupDescriptorTransfer);
        for (size_t i = 0; i < memberLength; ++i) {
            
            result += WGPUBindGroupDescriptorGetExtraRequiredSize(record.descriptor[i]);
        }
    }
    {
    }

    return result;
}
// GetExtraRequiredSize isn't used for structures that are value members of other structures
// because we assume they cannot contain pointers themselves.
DAWN_UNUSED_FUNC(DeviceCreateBindGroupGetExtraRequiredSize);

DAWN_DECLARE_UNUSED void DeviceCreateBindGroupSerialize(const DeviceCreateBindGroupCmd& record, DeviceCreateBindGroupTransfer* transfer,
                       char** buffer, const ObjectIdProvider& provider) {
    DAWN_UNUSED(buffer);

    transfer->commandId = WireCmd::DeviceCreateBindGroup;

    transfer->self = provider.GetId(record.self);

    transfer->result = record.result;





    {
        size_t memberLength = 1;
        auto memberBuffer = reinterpret_cast<WGPUBindGroupDescriptorTransfer*>(*buffer);
        *buffer += memberLength * sizeof(WGPUBindGroupDescriptorTransfer);

        for (size_t i = 0; i < memberLength; ++i) {
            WGPUBindGroupDescriptorSerialize(record.descriptor[i], &memberBuffer[i], buffer, provider);

        }
    }
}
DAWN_UNUSED_FUNC(DeviceCreateBindGroupSerialize);

DAWN_DECLARE_UNUSED DeserializeResult DeviceCreateBindGroupDeserialize(DeviceCreateBindGroupCmd* record, const volatile DeviceCreateBindGroupTransfer* transfer,
                                      const volatile char** buffer, size_t* size, DeserializeAllocator* allocator, const ObjectIdResolver& resolver) {
    DAWN_UNUSED(allocator);
    DAWN_UNUSED(buffer);
    DAWN_UNUSED(size);

    ASSERT(transfer->commandId == WireCmd::DeviceCreateBindGroup);

    record->selfId = transfer->self;

    DESERIALIZE_TRY(resolver.GetFromId(transfer->self, &record->self));
    record->result = transfer->result;





    {
        size_t memberLength = 1;
        auto memberBuffer = reinterpret_cast<const volatile WGPUBindGroupDescriptorTransfer*>(buffer);
        DESERIALIZE_TRY(GetPtrFromBuffer(buffer, size, memberLength, &memberBuffer));

        WGPUBindGroupDescriptor* copiedMembers = nullptr;
        DESERIALIZE_TRY(GetSpace(allocator, memberLength, &copiedMembers));
        record->descriptor = copiedMembers;

        for (size_t i = 0; i < memberLength; ++i) {
            DESERIALIZE_TRY(WGPUBindGroupDescriptorDeserialize(&copiedMembers[i], &memberBuffer[i], buffer, size, allocator, resolver));
        }
    }

    return DeserializeResult::Success;
}
DAWN_UNUSED_FUNC(DeviceCreateBindGroupDeserialize);

        
struct DeviceCreateBindGroupLayoutTransfer : CmdHeader {
    static_assert(1 <= 1,
                  "Record must be at most one of is_cmd, extensible, and chained.");
    WireCmd commandId;

    ObjectId self;
    ObjectHandle result;


};

static_assert(offsetof(DeviceCreateBindGroupLayoutTransfer, commandSize) == 0, "");
static_assert(offsetof(DeviceCreateBindGroupLayoutTransfer, commandId) == sizeof(CmdHeader), "");


DAWN_DECLARE_UNUSED size_t DeviceCreateBindGroupLayoutGetExtraRequiredSize(const DeviceCreateBindGroupLayoutCmd& record) {
    DAWN_UNUSED(record);

    size_t result = 0;



    {
    }
    {
        size_t memberLength = 1;
        result += memberLength * sizeof(WGPUBindGroupLayoutDescriptorTransfer);
        for (size_t i = 0; i < memberLength; ++i) {
            
            result += WGPUBindGroupLayoutDescriptorGetExtraRequiredSize(record.descriptor[i]);
        }
    }
    {
    }

    return result;
}
// GetExtraRequiredSize isn't used for structures that are value members of other structures
// because we assume they cannot contain pointers themselves.
DAWN_UNUSED_FUNC(DeviceCreateBindGroupLayoutGetExtraRequiredSize);

DAWN_DECLARE_UNUSED void DeviceCreateBindGroupLayoutSerialize(const DeviceCreateBindGroupLayoutCmd& record, DeviceCreateBindGroupLayoutTransfer* transfer,
                       char** buffer, const ObjectIdProvider& provider) {
    DAWN_UNUSED(buffer);

    transfer->commandId = WireCmd::DeviceCreateBindGroupLayout;

    transfer->self = provider.GetId(record.self);

    transfer->result = record.result;





    {
        size_t memberLength = 1;
        auto memberBuffer = reinterpret_cast<WGPUBindGroupLayoutDescriptorTransfer*>(*buffer);
        *buffer += memberLength * sizeof(WGPUBindGroupLayoutDescriptorTransfer);

        for (size_t i = 0; i < memberLength; ++i) {
            WGPUBindGroupLayoutDescriptorSerialize(record.descriptor[i], &memberBuffer[i], buffer, provider);

        }
    }
}
DAWN_UNUSED_FUNC(DeviceCreateBindGroupLayoutSerialize);

DAWN_DECLARE_UNUSED DeserializeResult DeviceCreateBindGroupLayoutDeserialize(DeviceCreateBindGroupLayoutCmd* record, const volatile DeviceCreateBindGroupLayoutTransfer* transfer,
                                      const volatile char** buffer, size_t* size, DeserializeAllocator* allocator, const ObjectIdResolver& resolver) {
    DAWN_UNUSED(allocator);
    DAWN_UNUSED(buffer);
    DAWN_UNUSED(size);

    ASSERT(transfer->commandId == WireCmd::DeviceCreateBindGroupLayout);

    record->selfId = transfer->self;

    DESERIALIZE_TRY(resolver.GetFromId(transfer->self, &record->self));
    record->result = transfer->result;





    {
        size_t memberLength = 1;
        auto memberBuffer = reinterpret_cast<const volatile WGPUBindGroupLayoutDescriptorTransfer*>(buffer);
        DESERIALIZE_TRY(GetPtrFromBuffer(buffer, size, memberLength, &memberBuffer));

        WGPUBindGroupLayoutDescriptor* copiedMembers = nullptr;
        DESERIALIZE_TRY(GetSpace(allocator, memberLength, &copiedMembers));
        record->descriptor = copiedMembers;

        for (size_t i = 0; i < memberLength; ++i) {
            DESERIALIZE_TRY(WGPUBindGroupLayoutDescriptorDeserialize(&copiedMembers[i], &memberBuffer[i], buffer, size, allocator, resolver));
        }
    }

    return DeserializeResult::Success;
}
DAWN_UNUSED_FUNC(DeviceCreateBindGroupLayoutDeserialize);

        
struct DeviceCreateBufferTransfer : CmdHeader {
    static_assert(1 <= 1,
                  "Record must be at most one of is_cmd, extensible, and chained.");
    WireCmd commandId;

    ObjectId device;
    ObjectHandle result;
    uint64_t handleCreateInfoLength;


};

static_assert(offsetof(DeviceCreateBufferTransfer, commandSize) == 0, "");
static_assert(offsetof(DeviceCreateBufferTransfer, commandId) == sizeof(CmdHeader), "");


DAWN_DECLARE_UNUSED size_t DeviceCreateBufferGetExtraRequiredSize(const DeviceCreateBufferCmd& record) {
    DAWN_UNUSED(record);

    size_t result = 0;



    {
    }
    {
        size_t memberLength = 1;
        result += memberLength * sizeof(WGPUBufferDescriptorTransfer);
        for (size_t i = 0; i < memberLength; ++i) {
            
            result += WGPUBufferDescriptorGetExtraRequiredSize(record.descriptor[i]);
        }
    }
    {
    }
    {
    }

    return result;
}
// GetExtraRequiredSize isn't used for structures that are value members of other structures
// because we assume they cannot contain pointers themselves.
DAWN_UNUSED_FUNC(DeviceCreateBufferGetExtraRequiredSize);

DAWN_DECLARE_UNUSED void DeviceCreateBufferSerialize(const DeviceCreateBufferCmd& record, DeviceCreateBufferTransfer* transfer,
                       char** buffer, const ObjectIdProvider& provider) {
    DAWN_UNUSED(buffer);

    transfer->commandId = WireCmd::DeviceCreateBuffer;

    transfer->device = provider.GetId(record.device);

    transfer->result = record.result;
    transfer->handleCreateInfoLength = record.handleCreateInfoLength;





    {
        size_t memberLength = 1;
        auto memberBuffer = reinterpret_cast<WGPUBufferDescriptorTransfer*>(*buffer);
        *buffer += memberLength * sizeof(WGPUBufferDescriptorTransfer);

        for (size_t i = 0; i < memberLength; ++i) {
            WGPUBufferDescriptorSerialize(record.descriptor[i], &memberBuffer[i], buffer, provider);

        }
    }
}
DAWN_UNUSED_FUNC(DeviceCreateBufferSerialize);

DAWN_DECLARE_UNUSED DeserializeResult DeviceCreateBufferDeserialize(DeviceCreateBufferCmd* record, const volatile DeviceCreateBufferTransfer* transfer,
                                      const volatile char** buffer, size_t* size, DeserializeAllocator* allocator, const ObjectIdResolver& resolver) {
    DAWN_UNUSED(allocator);
    DAWN_UNUSED(buffer);
    DAWN_UNUSED(size);

    ASSERT(transfer->commandId == WireCmd::DeviceCreateBuffer);


    DESERIALIZE_TRY(resolver.GetFromId(transfer->device, &record->device));
    record->result = transfer->result;
    record->handleCreateInfoLength = transfer->handleCreateInfoLength;





    {
        size_t memberLength = 1;
        auto memberBuffer = reinterpret_cast<const volatile WGPUBufferDescriptorTransfer*>(buffer);
        DESERIALIZE_TRY(GetPtrFromBuffer(buffer, size, memberLength, &memberBuffer));

        WGPUBufferDescriptor* copiedMembers = nullptr;
        DESERIALIZE_TRY(GetSpace(allocator, memberLength, &copiedMembers));
        record->descriptor = copiedMembers;

        for (size_t i = 0; i < memberLength; ++i) {
            DESERIALIZE_TRY(WGPUBufferDescriptorDeserialize(&copiedMembers[i], &memberBuffer[i], buffer, size, allocator, resolver));
        }
    }

    {
        size_t memberLength = record->handleCreateInfoLength;
        auto memberBuffer = reinterpret_cast<const volatile uint8_t*>(buffer);
        DESERIALIZE_TRY(GetPtrFromBuffer(buffer, size, memberLength, &memberBuffer));

        uint8_t* copiedMembers = nullptr;
        DESERIALIZE_TRY(GetSpace(allocator, memberLength, &copiedMembers));
        record->handleCreateInfo = copiedMembers;

        for (size_t i = 0; i < memberLength; ++i) {
            copiedMembers[i] = memberBuffer[i];
        }
    }

    return DeserializeResult::Success;
}
DAWN_UNUSED_FUNC(DeviceCreateBufferDeserialize);

        
struct DeviceCreateCommandEncoderTransfer : CmdHeader {
    static_assert(1 <= 1,
                  "Record must be at most one of is_cmd, extensible, and chained.");
    WireCmd commandId;

    ObjectId self;
    ObjectHandle result;


    bool has_descriptor;
};

static_assert(offsetof(DeviceCreateCommandEncoderTransfer, commandSize) == 0, "");
static_assert(offsetof(DeviceCreateCommandEncoderTransfer, commandId) == sizeof(CmdHeader), "");


DAWN_DECLARE_UNUSED size_t DeviceCreateCommandEncoderGetExtraRequiredSize(const DeviceCreateCommandEncoderCmd& record) {
    DAWN_UNUSED(record);

    size_t result = 0;



    {
    }
    if (record.descriptor != nullptr)
    {
        size_t memberLength = 1;
        result += memberLength * sizeof(WGPUCommandEncoderDescriptorTransfer);
        for (size_t i = 0; i < memberLength; ++i) {
            
            result += WGPUCommandEncoderDescriptorGetExtraRequiredSize(record.descriptor[i]);
        }
    }
    {
    }

    return result;
}
// GetExtraRequiredSize isn't used for structures that are value members of other structures
// because we assume they cannot contain pointers themselves.
DAWN_UNUSED_FUNC(DeviceCreateCommandEncoderGetExtraRequiredSize);

DAWN_DECLARE_UNUSED void DeviceCreateCommandEncoderSerialize(const DeviceCreateCommandEncoderCmd& record, DeviceCreateCommandEncoderTransfer* transfer,
                       char** buffer, const ObjectIdProvider& provider) {
    DAWN_UNUSED(buffer);

    transfer->commandId = WireCmd::DeviceCreateCommandEncoder;

    transfer->self = provider.GetId(record.self);

    transfer->result = record.result;





    bool has_descriptor = record.descriptor != nullptr;
    transfer->has_descriptor = has_descriptor;
    if (has_descriptor)
    {
        size_t memberLength = 1;
        auto memberBuffer = reinterpret_cast<WGPUCommandEncoderDescriptorTransfer*>(*buffer);
        *buffer += memberLength * sizeof(WGPUCommandEncoderDescriptorTransfer);

        for (size_t i = 0; i < memberLength; ++i) {
            WGPUCommandEncoderDescriptorSerialize(record.descriptor[i], &memberBuffer[i], buffer, provider);

        }
    }
}
DAWN_UNUSED_FUNC(DeviceCreateCommandEncoderSerialize);

DAWN_DECLARE_UNUSED DeserializeResult DeviceCreateCommandEncoderDeserialize(DeviceCreateCommandEncoderCmd* record, const volatile DeviceCreateCommandEncoderTransfer* transfer,
                                      const volatile char** buffer, size_t* size, DeserializeAllocator* allocator, const ObjectIdResolver& resolver) {
    DAWN_UNUSED(allocator);
    DAWN_UNUSED(buffer);
    DAWN_UNUSED(size);

    ASSERT(transfer->commandId == WireCmd::DeviceCreateCommandEncoder);

    record->selfId = transfer->self;

    DESERIALIZE_TRY(resolver.GetFromId(transfer->self, &record->self));
    record->result = transfer->result;





    bool has_descriptor = transfer->has_descriptor;
    record->descriptor = nullptr;
    if (has_descriptor)
    {
        size_t memberLength = 1;
        auto memberBuffer = reinterpret_cast<const volatile WGPUCommandEncoderDescriptorTransfer*>(buffer);
        DESERIALIZE_TRY(GetPtrFromBuffer(buffer, size, memberLength, &memberBuffer));

        WGPUCommandEncoderDescriptor* copiedMembers = nullptr;
        DESERIALIZE_TRY(GetSpace(allocator, memberLength, &copiedMembers));
        record->descriptor = copiedMembers;

        for (size_t i = 0; i < memberLength; ++i) {
            DESERIALIZE_TRY(WGPUCommandEncoderDescriptorDeserialize(&copiedMembers[i], &memberBuffer[i], buffer, size, allocator, resolver));
        }
    }

    return DeserializeResult::Success;
}
DAWN_UNUSED_FUNC(DeviceCreateCommandEncoderDeserialize);

        
struct DeviceCreateComputePipelineTransfer : CmdHeader {
    static_assert(1 <= 1,
                  "Record must be at most one of is_cmd, extensible, and chained.");
    WireCmd commandId;

    ObjectId self;
    ObjectHandle result;


};

static_assert(offsetof(DeviceCreateComputePipelineTransfer, commandSize) == 0, "");
static_assert(offsetof(DeviceCreateComputePipelineTransfer, commandId) == sizeof(CmdHeader), "");


DAWN_DECLARE_UNUSED size_t DeviceCreateComputePipelineGetExtraRequiredSize(const DeviceCreateComputePipelineCmd& record) {
    DAWN_UNUSED(record);

    size_t result = 0;



    {
    }
    {
        size_t memberLength = 1;
        result += memberLength * sizeof(WGPUComputePipelineDescriptorTransfer);
        for (size_t i = 0; i < memberLength; ++i) {
            
            result += WGPUComputePipelineDescriptorGetExtraRequiredSize(record.descriptor[i]);
        }
    }
    {
    }

    return result;
}
// GetExtraRequiredSize isn't used for structures that are value members of other structures
// because we assume they cannot contain pointers themselves.
DAWN_UNUSED_FUNC(DeviceCreateComputePipelineGetExtraRequiredSize);

DAWN_DECLARE_UNUSED void DeviceCreateComputePipelineSerialize(const DeviceCreateComputePipelineCmd& record, DeviceCreateComputePipelineTransfer* transfer,
                       char** buffer, const ObjectIdProvider& provider) {
    DAWN_UNUSED(buffer);

    transfer->commandId = WireCmd::DeviceCreateComputePipeline;

    transfer->self = provider.GetId(record.self);

    transfer->result = record.result;





    {
        size_t memberLength = 1;
        auto memberBuffer = reinterpret_cast<WGPUComputePipelineDescriptorTransfer*>(*buffer);
        *buffer += memberLength * sizeof(WGPUComputePipelineDescriptorTransfer);

        for (size_t i = 0; i < memberLength; ++i) {
            WGPUComputePipelineDescriptorSerialize(record.descriptor[i], &memberBuffer[i], buffer, provider);

        }
    }
}
DAWN_UNUSED_FUNC(DeviceCreateComputePipelineSerialize);

DAWN_DECLARE_UNUSED DeserializeResult DeviceCreateComputePipelineDeserialize(DeviceCreateComputePipelineCmd* record, const volatile DeviceCreateComputePipelineTransfer* transfer,
                                      const volatile char** buffer, size_t* size, DeserializeAllocator* allocator, const ObjectIdResolver& resolver) {
    DAWN_UNUSED(allocator);
    DAWN_UNUSED(buffer);
    DAWN_UNUSED(size);

    ASSERT(transfer->commandId == WireCmd::DeviceCreateComputePipeline);

    record->selfId = transfer->self;

    DESERIALIZE_TRY(resolver.GetFromId(transfer->self, &record->self));
    record->result = transfer->result;





    {
        size_t memberLength = 1;
        auto memberBuffer = reinterpret_cast<const volatile WGPUComputePipelineDescriptorTransfer*>(buffer);
        DESERIALIZE_TRY(GetPtrFromBuffer(buffer, size, memberLength, &memberBuffer));

        WGPUComputePipelineDescriptor* copiedMembers = nullptr;
        DESERIALIZE_TRY(GetSpace(allocator, memberLength, &copiedMembers));
        record->descriptor = copiedMembers;

        for (size_t i = 0; i < memberLength; ++i) {
            DESERIALIZE_TRY(WGPUComputePipelineDescriptorDeserialize(&copiedMembers[i], &memberBuffer[i], buffer, size, allocator, resolver));
        }
    }

    return DeserializeResult::Success;
}
DAWN_UNUSED_FUNC(DeviceCreateComputePipelineDeserialize);

        
struct DeviceCreateErrorBufferTransfer : CmdHeader {
    static_assert(1 <= 1,
                  "Record must be at most one of is_cmd, extensible, and chained.");
    WireCmd commandId;

    ObjectId self;
    ObjectHandle result;


};

static_assert(offsetof(DeviceCreateErrorBufferTransfer, commandSize) == 0, "");
static_assert(offsetof(DeviceCreateErrorBufferTransfer, commandId) == sizeof(CmdHeader), "");


DAWN_DECLARE_UNUSED size_t DeviceCreateErrorBufferGetExtraRequiredSize(const DeviceCreateErrorBufferCmd& record) {
    DAWN_UNUSED(record);

    size_t result = 0;



    {
    }
    {
    }

    return result;
}
// GetExtraRequiredSize isn't used for structures that are value members of other structures
// because we assume they cannot contain pointers themselves.
DAWN_UNUSED_FUNC(DeviceCreateErrorBufferGetExtraRequiredSize);

DAWN_DECLARE_UNUSED void DeviceCreateErrorBufferSerialize(const DeviceCreateErrorBufferCmd& record, DeviceCreateErrorBufferTransfer* transfer,
                       char** buffer, const ObjectIdProvider& provider) {
    DAWN_UNUSED(buffer);

    transfer->commandId = WireCmd::DeviceCreateErrorBuffer;

    transfer->self = provider.GetId(record.self);

    transfer->result = record.result;




}
DAWN_UNUSED_FUNC(DeviceCreateErrorBufferSerialize);

DAWN_DECLARE_UNUSED DeserializeResult DeviceCreateErrorBufferDeserialize(DeviceCreateErrorBufferCmd* record, const volatile DeviceCreateErrorBufferTransfer* transfer,
                                      const volatile char** buffer, size_t* size, DeserializeAllocator* allocator, const ObjectIdResolver& resolver) {
    DAWN_UNUSED(allocator);
    DAWN_UNUSED(buffer);
    DAWN_UNUSED(size);

    ASSERT(transfer->commandId == WireCmd::DeviceCreateErrorBuffer);

    record->selfId = transfer->self;

    DESERIALIZE_TRY(resolver.GetFromId(transfer->self, &record->self));
    record->result = transfer->result;





    return DeserializeResult::Success;
}
DAWN_UNUSED_FUNC(DeviceCreateErrorBufferDeserialize);

        
struct DeviceCreatePipelineLayoutTransfer : CmdHeader {
    static_assert(1 <= 1,
                  "Record must be at most one of is_cmd, extensible, and chained.");
    WireCmd commandId;

    ObjectId self;
    ObjectHandle result;


};

static_assert(offsetof(DeviceCreatePipelineLayoutTransfer, commandSize) == 0, "");
static_assert(offsetof(DeviceCreatePipelineLayoutTransfer, commandId) == sizeof(CmdHeader), "");


DAWN_DECLARE_UNUSED size_t DeviceCreatePipelineLayoutGetExtraRequiredSize(const DeviceCreatePipelineLayoutCmd& record) {
    DAWN_UNUSED(record);

    size_t result = 0;



    {
    }
    {
        size_t memberLength = 1;
        result += memberLength * sizeof(WGPUPipelineLayoutDescriptorTransfer);
        for (size_t i = 0; i < memberLength; ++i) {
            
            result += WGPUPipelineLayoutDescriptorGetExtraRequiredSize(record.descriptor[i]);
        }
    }
    {
    }

    return result;
}
// GetExtraRequiredSize isn't used for structures that are value members of other structures
// because we assume they cannot contain pointers themselves.
DAWN_UNUSED_FUNC(DeviceCreatePipelineLayoutGetExtraRequiredSize);

DAWN_DECLARE_UNUSED void DeviceCreatePipelineLayoutSerialize(const DeviceCreatePipelineLayoutCmd& record, DeviceCreatePipelineLayoutTransfer* transfer,
                       char** buffer, const ObjectIdProvider& provider) {
    DAWN_UNUSED(buffer);

    transfer->commandId = WireCmd::DeviceCreatePipelineLayout;

    transfer->self = provider.GetId(record.self);

    transfer->result = record.result;





    {
        size_t memberLength = 1;
        auto memberBuffer = reinterpret_cast<WGPUPipelineLayoutDescriptorTransfer*>(*buffer);
        *buffer += memberLength * sizeof(WGPUPipelineLayoutDescriptorTransfer);

        for (size_t i = 0; i < memberLength; ++i) {
            WGPUPipelineLayoutDescriptorSerialize(record.descriptor[i], &memberBuffer[i], buffer, provider);

        }
    }
}
DAWN_UNUSED_FUNC(DeviceCreatePipelineLayoutSerialize);

DAWN_DECLARE_UNUSED DeserializeResult DeviceCreatePipelineLayoutDeserialize(DeviceCreatePipelineLayoutCmd* record, const volatile DeviceCreatePipelineLayoutTransfer* transfer,
                                      const volatile char** buffer, size_t* size, DeserializeAllocator* allocator, const ObjectIdResolver& resolver) {
    DAWN_UNUSED(allocator);
    DAWN_UNUSED(buffer);
    DAWN_UNUSED(size);

    ASSERT(transfer->commandId == WireCmd::DeviceCreatePipelineLayout);

    record->selfId = transfer->self;

    DESERIALIZE_TRY(resolver.GetFromId(transfer->self, &record->self));
    record->result = transfer->result;





    {
        size_t memberLength = 1;
        auto memberBuffer = reinterpret_cast<const volatile WGPUPipelineLayoutDescriptorTransfer*>(buffer);
        DESERIALIZE_TRY(GetPtrFromBuffer(buffer, size, memberLength, &memberBuffer));

        WGPUPipelineLayoutDescriptor* copiedMembers = nullptr;
        DESERIALIZE_TRY(GetSpace(allocator, memberLength, &copiedMembers));
        record->descriptor = copiedMembers;

        for (size_t i = 0; i < memberLength; ++i) {
            DESERIALIZE_TRY(WGPUPipelineLayoutDescriptorDeserialize(&copiedMembers[i], &memberBuffer[i], buffer, size, allocator, resolver));
        }
    }

    return DeserializeResult::Success;
}
DAWN_UNUSED_FUNC(DeviceCreatePipelineLayoutDeserialize);

        
struct DeviceCreateQuerySetTransfer : CmdHeader {
    static_assert(1 <= 1,
                  "Record must be at most one of is_cmd, extensible, and chained.");
    WireCmd commandId;

    ObjectId self;
    ObjectHandle result;


};

static_assert(offsetof(DeviceCreateQuerySetTransfer, commandSize) == 0, "");
static_assert(offsetof(DeviceCreateQuerySetTransfer, commandId) == sizeof(CmdHeader), "");


DAWN_DECLARE_UNUSED size_t DeviceCreateQuerySetGetExtraRequiredSize(const DeviceCreateQuerySetCmd& record) {
    DAWN_UNUSED(record);

    size_t result = 0;



    {
    }
    {
        size_t memberLength = 1;
        result += memberLength * sizeof(WGPUQuerySetDescriptorTransfer);
        for (size_t i = 0; i < memberLength; ++i) {
            
            result += WGPUQuerySetDescriptorGetExtraRequiredSize(record.descriptor[i]);
        }
    }
    {
    }

    return result;
}
// GetExtraRequiredSize isn't used for structures that are value members of other structures
// because we assume they cannot contain pointers themselves.
DAWN_UNUSED_FUNC(DeviceCreateQuerySetGetExtraRequiredSize);

DAWN_DECLARE_UNUSED void DeviceCreateQuerySetSerialize(const DeviceCreateQuerySetCmd& record, DeviceCreateQuerySetTransfer* transfer,
                       char** buffer, const ObjectIdProvider& provider) {
    DAWN_UNUSED(buffer);

    transfer->commandId = WireCmd::DeviceCreateQuerySet;

    transfer->self = provider.GetId(record.self);

    transfer->result = record.result;





    {
        size_t memberLength = 1;
        auto memberBuffer = reinterpret_cast<WGPUQuerySetDescriptorTransfer*>(*buffer);
        *buffer += memberLength * sizeof(WGPUQuerySetDescriptorTransfer);

        for (size_t i = 0; i < memberLength; ++i) {
            WGPUQuerySetDescriptorSerialize(record.descriptor[i], &memberBuffer[i], buffer, provider);

        }
    }
}
DAWN_UNUSED_FUNC(DeviceCreateQuerySetSerialize);

DAWN_DECLARE_UNUSED DeserializeResult DeviceCreateQuerySetDeserialize(DeviceCreateQuerySetCmd* record, const volatile DeviceCreateQuerySetTransfer* transfer,
                                      const volatile char** buffer, size_t* size, DeserializeAllocator* allocator, const ObjectIdResolver& resolver) {
    DAWN_UNUSED(allocator);
    DAWN_UNUSED(buffer);
    DAWN_UNUSED(size);

    ASSERT(transfer->commandId == WireCmd::DeviceCreateQuerySet);

    record->selfId = transfer->self;

    DESERIALIZE_TRY(resolver.GetFromId(transfer->self, &record->self));
    record->result = transfer->result;





    {
        size_t memberLength = 1;
        auto memberBuffer = reinterpret_cast<const volatile WGPUQuerySetDescriptorTransfer*>(buffer);
        DESERIALIZE_TRY(GetPtrFromBuffer(buffer, size, memberLength, &memberBuffer));

        WGPUQuerySetDescriptor* copiedMembers = nullptr;
        DESERIALIZE_TRY(GetSpace(allocator, memberLength, &copiedMembers));
        record->descriptor = copiedMembers;

        for (size_t i = 0; i < memberLength; ++i) {
            DESERIALIZE_TRY(WGPUQuerySetDescriptorDeserialize(&copiedMembers[i], &memberBuffer[i], buffer, size, allocator, resolver));
        }
    }

    return DeserializeResult::Success;
}
DAWN_UNUSED_FUNC(DeviceCreateQuerySetDeserialize);

        
struct DeviceCreateReadyComputePipelineTransfer : CmdHeader {
    static_assert(1 <= 1,
                  "Record must be at most one of is_cmd, extensible, and chained.");
    WireCmd commandId;

    ObjectId device;
    uint64_t requestSerial;
    ObjectHandle pipelineObjectHandle;


};

static_assert(offsetof(DeviceCreateReadyComputePipelineTransfer, commandSize) == 0, "");
static_assert(offsetof(DeviceCreateReadyComputePipelineTransfer, commandId) == sizeof(CmdHeader), "");


DAWN_DECLARE_UNUSED size_t DeviceCreateReadyComputePipelineGetExtraRequiredSize(const DeviceCreateReadyComputePipelineCmd& record) {
    DAWN_UNUSED(record);

    size_t result = 0;



    {
    }
    {
    }
    {
    }
    {
        size_t memberLength = 1;
        result += memberLength * sizeof(WGPUComputePipelineDescriptorTransfer);
        for (size_t i = 0; i < memberLength; ++i) {
            
            result += WGPUComputePipelineDescriptorGetExtraRequiredSize(record.descriptor[i]);
        }
    }

    return result;
}
// GetExtraRequiredSize isn't used for structures that are value members of other structures
// because we assume they cannot contain pointers themselves.
DAWN_UNUSED_FUNC(DeviceCreateReadyComputePipelineGetExtraRequiredSize);

DAWN_DECLARE_UNUSED void DeviceCreateReadyComputePipelineSerialize(const DeviceCreateReadyComputePipelineCmd& record, DeviceCreateReadyComputePipelineTransfer* transfer,
                       char** buffer, const ObjectIdProvider& provider) {
    DAWN_UNUSED(buffer);

    transfer->commandId = WireCmd::DeviceCreateReadyComputePipeline;

    transfer->device = provider.GetId(record.device);

    transfer->requestSerial = record.requestSerial;
    transfer->pipelineObjectHandle = record.pipelineObjectHandle;





    {
        size_t memberLength = 1;
        auto memberBuffer = reinterpret_cast<WGPUComputePipelineDescriptorTransfer*>(*buffer);
        *buffer += memberLength * sizeof(WGPUComputePipelineDescriptorTransfer);

        for (size_t i = 0; i < memberLength; ++i) {
            WGPUComputePipelineDescriptorSerialize(record.descriptor[i], &memberBuffer[i], buffer, provider);

        }
    }
}
DAWN_UNUSED_FUNC(DeviceCreateReadyComputePipelineSerialize);

DAWN_DECLARE_UNUSED DeserializeResult DeviceCreateReadyComputePipelineDeserialize(DeviceCreateReadyComputePipelineCmd* record, const volatile DeviceCreateReadyComputePipelineTransfer* transfer,
                                      const volatile char** buffer, size_t* size, DeserializeAllocator* allocator, const ObjectIdResolver& resolver) {
    DAWN_UNUSED(allocator);
    DAWN_UNUSED(buffer);
    DAWN_UNUSED(size);

    ASSERT(transfer->commandId == WireCmd::DeviceCreateReadyComputePipeline);


    DESERIALIZE_TRY(resolver.GetFromId(transfer->device, &record->device));
    record->requestSerial = transfer->requestSerial;
    record->pipelineObjectHandle = transfer->pipelineObjectHandle;





    {
        size_t memberLength = 1;
        auto memberBuffer = reinterpret_cast<const volatile WGPUComputePipelineDescriptorTransfer*>(buffer);
        DESERIALIZE_TRY(GetPtrFromBuffer(buffer, size, memberLength, &memberBuffer));

        WGPUComputePipelineDescriptor* copiedMembers = nullptr;
        DESERIALIZE_TRY(GetSpace(allocator, memberLength, &copiedMembers));
        record->descriptor = copiedMembers;

        for (size_t i = 0; i < memberLength; ++i) {
            DESERIALIZE_TRY(WGPUComputePipelineDescriptorDeserialize(&copiedMembers[i], &memberBuffer[i], buffer, size, allocator, resolver));
        }
    }

    return DeserializeResult::Success;
}
DAWN_UNUSED_FUNC(DeviceCreateReadyComputePipelineDeserialize);

        
struct DeviceCreateReadyRenderPipelineTransfer : CmdHeader {
    static_assert(1 <= 1,
                  "Record must be at most one of is_cmd, extensible, and chained.");
    WireCmd commandId;

    ObjectId device;
    uint64_t requestSerial;
    ObjectHandle pipelineObjectHandle;


};

static_assert(offsetof(DeviceCreateReadyRenderPipelineTransfer, commandSize) == 0, "");
static_assert(offsetof(DeviceCreateReadyRenderPipelineTransfer, commandId) == sizeof(CmdHeader), "");


DAWN_DECLARE_UNUSED size_t DeviceCreateReadyRenderPipelineGetExtraRequiredSize(const DeviceCreateReadyRenderPipelineCmd& record) {
    DAWN_UNUSED(record);

    size_t result = 0;



    {
    }
    {
    }
    {
    }
    {
        size_t memberLength = 1;
        result += memberLength * sizeof(WGPURenderPipelineDescriptorTransfer);
        for (size_t i = 0; i < memberLength; ++i) {
            
            result += WGPURenderPipelineDescriptorGetExtraRequiredSize(record.descriptor[i]);
        }
    }

    return result;
}
// GetExtraRequiredSize isn't used for structures that are value members of other structures
// because we assume they cannot contain pointers themselves.
DAWN_UNUSED_FUNC(DeviceCreateReadyRenderPipelineGetExtraRequiredSize);

DAWN_DECLARE_UNUSED void DeviceCreateReadyRenderPipelineSerialize(const DeviceCreateReadyRenderPipelineCmd& record, DeviceCreateReadyRenderPipelineTransfer* transfer,
                       char** buffer, const ObjectIdProvider& provider) {
    DAWN_UNUSED(buffer);

    transfer->commandId = WireCmd::DeviceCreateReadyRenderPipeline;

    transfer->device = provider.GetId(record.device);

    transfer->requestSerial = record.requestSerial;
    transfer->pipelineObjectHandle = record.pipelineObjectHandle;





    {
        size_t memberLength = 1;
        auto memberBuffer = reinterpret_cast<WGPURenderPipelineDescriptorTransfer*>(*buffer);
        *buffer += memberLength * sizeof(WGPURenderPipelineDescriptorTransfer);

        for (size_t i = 0; i < memberLength; ++i) {
            WGPURenderPipelineDescriptorSerialize(record.descriptor[i], &memberBuffer[i], buffer, provider);

        }
    }
}
DAWN_UNUSED_FUNC(DeviceCreateReadyRenderPipelineSerialize);

DAWN_DECLARE_UNUSED DeserializeResult DeviceCreateReadyRenderPipelineDeserialize(DeviceCreateReadyRenderPipelineCmd* record, const volatile DeviceCreateReadyRenderPipelineTransfer* transfer,
                                      const volatile char** buffer, size_t* size, DeserializeAllocator* allocator, const ObjectIdResolver& resolver) {
    DAWN_UNUSED(allocator);
    DAWN_UNUSED(buffer);
    DAWN_UNUSED(size);

    ASSERT(transfer->commandId == WireCmd::DeviceCreateReadyRenderPipeline);


    DESERIALIZE_TRY(resolver.GetFromId(transfer->device, &record->device));
    record->requestSerial = transfer->requestSerial;
    record->pipelineObjectHandle = transfer->pipelineObjectHandle;





    {
        size_t memberLength = 1;
        auto memberBuffer = reinterpret_cast<const volatile WGPURenderPipelineDescriptorTransfer*>(buffer);
        DESERIALIZE_TRY(GetPtrFromBuffer(buffer, size, memberLength, &memberBuffer));

        WGPURenderPipelineDescriptor* copiedMembers = nullptr;
        DESERIALIZE_TRY(GetSpace(allocator, memberLength, &copiedMembers));
        record->descriptor = copiedMembers;

        for (size_t i = 0; i < memberLength; ++i) {
            DESERIALIZE_TRY(WGPURenderPipelineDescriptorDeserialize(&copiedMembers[i], &memberBuffer[i], buffer, size, allocator, resolver));
        }
    }

    return DeserializeResult::Success;
}
DAWN_UNUSED_FUNC(DeviceCreateReadyRenderPipelineDeserialize);

        
struct DeviceCreateRenderBundleEncoderTransfer : CmdHeader {
    static_assert(1 <= 1,
                  "Record must be at most one of is_cmd, extensible, and chained.");
    WireCmd commandId;

    ObjectId self;
    ObjectHandle result;


};

static_assert(offsetof(DeviceCreateRenderBundleEncoderTransfer, commandSize) == 0, "");
static_assert(offsetof(DeviceCreateRenderBundleEncoderTransfer, commandId) == sizeof(CmdHeader), "");


DAWN_DECLARE_UNUSED size_t DeviceCreateRenderBundleEncoderGetExtraRequiredSize(const DeviceCreateRenderBundleEncoderCmd& record) {
    DAWN_UNUSED(record);

    size_t result = 0;



    {
    }
    {
        size_t memberLength = 1;
        result += memberLength * sizeof(WGPURenderBundleEncoderDescriptorTransfer);
        for (size_t i = 0; i < memberLength; ++i) {
            
            result += WGPURenderBundleEncoderDescriptorGetExtraRequiredSize(record.descriptor[i]);
        }
    }
    {
    }

    return result;
}
// GetExtraRequiredSize isn't used for structures that are value members of other structures
// because we assume they cannot contain pointers themselves.
DAWN_UNUSED_FUNC(DeviceCreateRenderBundleEncoderGetExtraRequiredSize);

DAWN_DECLARE_UNUSED void DeviceCreateRenderBundleEncoderSerialize(const DeviceCreateRenderBundleEncoderCmd& record, DeviceCreateRenderBundleEncoderTransfer* transfer,
                       char** buffer, const ObjectIdProvider& provider) {
    DAWN_UNUSED(buffer);

    transfer->commandId = WireCmd::DeviceCreateRenderBundleEncoder;

    transfer->self = provider.GetId(record.self);

    transfer->result = record.result;





    {
        size_t memberLength = 1;
        auto memberBuffer = reinterpret_cast<WGPURenderBundleEncoderDescriptorTransfer*>(*buffer);
        *buffer += memberLength * sizeof(WGPURenderBundleEncoderDescriptorTransfer);

        for (size_t i = 0; i < memberLength; ++i) {
            WGPURenderBundleEncoderDescriptorSerialize(record.descriptor[i], &memberBuffer[i], buffer, provider);

        }
    }
}
DAWN_UNUSED_FUNC(DeviceCreateRenderBundleEncoderSerialize);

DAWN_DECLARE_UNUSED DeserializeResult DeviceCreateRenderBundleEncoderDeserialize(DeviceCreateRenderBundleEncoderCmd* record, const volatile DeviceCreateRenderBundleEncoderTransfer* transfer,
                                      const volatile char** buffer, size_t* size, DeserializeAllocator* allocator, const ObjectIdResolver& resolver) {
    DAWN_UNUSED(allocator);
    DAWN_UNUSED(buffer);
    DAWN_UNUSED(size);

    ASSERT(transfer->commandId == WireCmd::DeviceCreateRenderBundleEncoder);

    record->selfId = transfer->self;

    DESERIALIZE_TRY(resolver.GetFromId(transfer->self, &record->self));
    record->result = transfer->result;





    {
        size_t memberLength = 1;
        auto memberBuffer = reinterpret_cast<const volatile WGPURenderBundleEncoderDescriptorTransfer*>(buffer);
        DESERIALIZE_TRY(GetPtrFromBuffer(buffer, size, memberLength, &memberBuffer));

        WGPURenderBundleEncoderDescriptor* copiedMembers = nullptr;
        DESERIALIZE_TRY(GetSpace(allocator, memberLength, &copiedMembers));
        record->descriptor = copiedMembers;

        for (size_t i = 0; i < memberLength; ++i) {
            DESERIALIZE_TRY(WGPURenderBundleEncoderDescriptorDeserialize(&copiedMembers[i], &memberBuffer[i], buffer, size, allocator, resolver));
        }
    }

    return DeserializeResult::Success;
}
DAWN_UNUSED_FUNC(DeviceCreateRenderBundleEncoderDeserialize);

        
struct DeviceCreateRenderPipelineTransfer : CmdHeader {
    static_assert(1 <= 1,
                  "Record must be at most one of is_cmd, extensible, and chained.");
    WireCmd commandId;

    ObjectId self;
    ObjectHandle result;


};

static_assert(offsetof(DeviceCreateRenderPipelineTransfer, commandSize) == 0, "");
static_assert(offsetof(DeviceCreateRenderPipelineTransfer, commandId) == sizeof(CmdHeader), "");


DAWN_DECLARE_UNUSED size_t DeviceCreateRenderPipelineGetExtraRequiredSize(const DeviceCreateRenderPipelineCmd& record) {
    DAWN_UNUSED(record);

    size_t result = 0;



    {
    }
    {
        size_t memberLength = 1;
        result += memberLength * sizeof(WGPURenderPipelineDescriptorTransfer);
        for (size_t i = 0; i < memberLength; ++i) {
            
            result += WGPURenderPipelineDescriptorGetExtraRequiredSize(record.descriptor[i]);
        }
    }
    {
    }

    return result;
}
// GetExtraRequiredSize isn't used for structures that are value members of other structures
// because we assume they cannot contain pointers themselves.
DAWN_UNUSED_FUNC(DeviceCreateRenderPipelineGetExtraRequiredSize);

DAWN_DECLARE_UNUSED void DeviceCreateRenderPipelineSerialize(const DeviceCreateRenderPipelineCmd& record, DeviceCreateRenderPipelineTransfer* transfer,
                       char** buffer, const ObjectIdProvider& provider) {
    DAWN_UNUSED(buffer);

    transfer->commandId = WireCmd::DeviceCreateRenderPipeline;

    transfer->self = provider.GetId(record.self);

    transfer->result = record.result;





    {
        size_t memberLength = 1;
        auto memberBuffer = reinterpret_cast<WGPURenderPipelineDescriptorTransfer*>(*buffer);
        *buffer += memberLength * sizeof(WGPURenderPipelineDescriptorTransfer);

        for (size_t i = 0; i < memberLength; ++i) {
            WGPURenderPipelineDescriptorSerialize(record.descriptor[i], &memberBuffer[i], buffer, provider);

        }
    }
}
DAWN_UNUSED_FUNC(DeviceCreateRenderPipelineSerialize);

DAWN_DECLARE_UNUSED DeserializeResult DeviceCreateRenderPipelineDeserialize(DeviceCreateRenderPipelineCmd* record, const volatile DeviceCreateRenderPipelineTransfer* transfer,
                                      const volatile char** buffer, size_t* size, DeserializeAllocator* allocator, const ObjectIdResolver& resolver) {
    DAWN_UNUSED(allocator);
    DAWN_UNUSED(buffer);
    DAWN_UNUSED(size);

    ASSERT(transfer->commandId == WireCmd::DeviceCreateRenderPipeline);

    record->selfId = transfer->self;

    DESERIALIZE_TRY(resolver.GetFromId(transfer->self, &record->self));
    record->result = transfer->result;





    {
        size_t memberLength = 1;
        auto memberBuffer = reinterpret_cast<const volatile WGPURenderPipelineDescriptorTransfer*>(buffer);
        DESERIALIZE_TRY(GetPtrFromBuffer(buffer, size, memberLength, &memberBuffer));

        WGPURenderPipelineDescriptor* copiedMembers = nullptr;
        DESERIALIZE_TRY(GetSpace(allocator, memberLength, &copiedMembers));
        record->descriptor = copiedMembers;

        for (size_t i = 0; i < memberLength; ++i) {
            DESERIALIZE_TRY(WGPURenderPipelineDescriptorDeserialize(&copiedMembers[i], &memberBuffer[i], buffer, size, allocator, resolver));
        }
    }

    return DeserializeResult::Success;
}
DAWN_UNUSED_FUNC(DeviceCreateRenderPipelineDeserialize);

        
struct DeviceCreateSamplerTransfer : CmdHeader {
    static_assert(1 <= 1,
                  "Record must be at most one of is_cmd, extensible, and chained.");
    WireCmd commandId;

    ObjectId self;
    ObjectHandle result;


};

static_assert(offsetof(DeviceCreateSamplerTransfer, commandSize) == 0, "");
static_assert(offsetof(DeviceCreateSamplerTransfer, commandId) == sizeof(CmdHeader), "");


DAWN_DECLARE_UNUSED size_t DeviceCreateSamplerGetExtraRequiredSize(const DeviceCreateSamplerCmd& record) {
    DAWN_UNUSED(record);

    size_t result = 0;



    {
    }
    {
        size_t memberLength = 1;
        result += memberLength * sizeof(WGPUSamplerDescriptorTransfer);
        for (size_t i = 0; i < memberLength; ++i) {
            
            result += WGPUSamplerDescriptorGetExtraRequiredSize(record.descriptor[i]);
        }
    }
    {
    }

    return result;
}
// GetExtraRequiredSize isn't used for structures that are value members of other structures
// because we assume they cannot contain pointers themselves.
DAWN_UNUSED_FUNC(DeviceCreateSamplerGetExtraRequiredSize);

DAWN_DECLARE_UNUSED void DeviceCreateSamplerSerialize(const DeviceCreateSamplerCmd& record, DeviceCreateSamplerTransfer* transfer,
                       char** buffer, const ObjectIdProvider& provider) {
    DAWN_UNUSED(buffer);

    transfer->commandId = WireCmd::DeviceCreateSampler;

    transfer->self = provider.GetId(record.self);

    transfer->result = record.result;





    {
        size_t memberLength = 1;
        auto memberBuffer = reinterpret_cast<WGPUSamplerDescriptorTransfer*>(*buffer);
        *buffer += memberLength * sizeof(WGPUSamplerDescriptorTransfer);

        for (size_t i = 0; i < memberLength; ++i) {
            WGPUSamplerDescriptorSerialize(record.descriptor[i], &memberBuffer[i], buffer, provider);

        }
    }
}
DAWN_UNUSED_FUNC(DeviceCreateSamplerSerialize);

DAWN_DECLARE_UNUSED DeserializeResult DeviceCreateSamplerDeserialize(DeviceCreateSamplerCmd* record, const volatile DeviceCreateSamplerTransfer* transfer,
                                      const volatile char** buffer, size_t* size, DeserializeAllocator* allocator, const ObjectIdResolver& resolver) {
    DAWN_UNUSED(allocator);
    DAWN_UNUSED(buffer);
    DAWN_UNUSED(size);

    ASSERT(transfer->commandId == WireCmd::DeviceCreateSampler);

    record->selfId = transfer->self;

    DESERIALIZE_TRY(resolver.GetFromId(transfer->self, &record->self));
    record->result = transfer->result;





    {
        size_t memberLength = 1;
        auto memberBuffer = reinterpret_cast<const volatile WGPUSamplerDescriptorTransfer*>(buffer);
        DESERIALIZE_TRY(GetPtrFromBuffer(buffer, size, memberLength, &memberBuffer));

        WGPUSamplerDescriptor* copiedMembers = nullptr;
        DESERIALIZE_TRY(GetSpace(allocator, memberLength, &copiedMembers));
        record->descriptor = copiedMembers;

        for (size_t i = 0; i < memberLength; ++i) {
            DESERIALIZE_TRY(WGPUSamplerDescriptorDeserialize(&copiedMembers[i], &memberBuffer[i], buffer, size, allocator, resolver));
        }
    }

    return DeserializeResult::Success;
}
DAWN_UNUSED_FUNC(DeviceCreateSamplerDeserialize);

        
struct DeviceCreateShaderModuleTransfer : CmdHeader {
    static_assert(1 <= 1,
                  "Record must be at most one of is_cmd, extensible, and chained.");
    WireCmd commandId;

    ObjectId self;
    ObjectHandle result;


};

static_assert(offsetof(DeviceCreateShaderModuleTransfer, commandSize) == 0, "");
static_assert(offsetof(DeviceCreateShaderModuleTransfer, commandId) == sizeof(CmdHeader), "");


DAWN_DECLARE_UNUSED size_t DeviceCreateShaderModuleGetExtraRequiredSize(const DeviceCreateShaderModuleCmd& record) {
    DAWN_UNUSED(record);

    size_t result = 0;



    {
    }
    {
        size_t memberLength = 1;
        result += memberLength * sizeof(WGPUShaderModuleDescriptorTransfer);
        for (size_t i = 0; i < memberLength; ++i) {
            
            result += WGPUShaderModuleDescriptorGetExtraRequiredSize(record.descriptor[i]);
        }
    }
    {
    }

    return result;
}
// GetExtraRequiredSize isn't used for structures that are value members of other structures
// because we assume they cannot contain pointers themselves.
DAWN_UNUSED_FUNC(DeviceCreateShaderModuleGetExtraRequiredSize);

DAWN_DECLARE_UNUSED void DeviceCreateShaderModuleSerialize(const DeviceCreateShaderModuleCmd& record, DeviceCreateShaderModuleTransfer* transfer,
                       char** buffer, const ObjectIdProvider& provider) {
    DAWN_UNUSED(buffer);

    transfer->commandId = WireCmd::DeviceCreateShaderModule;

    transfer->self = provider.GetId(record.self);

    transfer->result = record.result;





    {
        size_t memberLength = 1;
        auto memberBuffer = reinterpret_cast<WGPUShaderModuleDescriptorTransfer*>(*buffer);
        *buffer += memberLength * sizeof(WGPUShaderModuleDescriptorTransfer);

        for (size_t i = 0; i < memberLength; ++i) {
            WGPUShaderModuleDescriptorSerialize(record.descriptor[i], &memberBuffer[i], buffer, provider);

        }
    }
}
DAWN_UNUSED_FUNC(DeviceCreateShaderModuleSerialize);

DAWN_DECLARE_UNUSED DeserializeResult DeviceCreateShaderModuleDeserialize(DeviceCreateShaderModuleCmd* record, const volatile DeviceCreateShaderModuleTransfer* transfer,
                                      const volatile char** buffer, size_t* size, DeserializeAllocator* allocator, const ObjectIdResolver& resolver) {
    DAWN_UNUSED(allocator);
    DAWN_UNUSED(buffer);
    DAWN_UNUSED(size);

    ASSERT(transfer->commandId == WireCmd::DeviceCreateShaderModule);

    record->selfId = transfer->self;

    DESERIALIZE_TRY(resolver.GetFromId(transfer->self, &record->self));
    record->result = transfer->result;





    {
        size_t memberLength = 1;
        auto memberBuffer = reinterpret_cast<const volatile WGPUShaderModuleDescriptorTransfer*>(buffer);
        DESERIALIZE_TRY(GetPtrFromBuffer(buffer, size, memberLength, &memberBuffer));

        WGPUShaderModuleDescriptor* copiedMembers = nullptr;
        DESERIALIZE_TRY(GetSpace(allocator, memberLength, &copiedMembers));
        record->descriptor = copiedMembers;

        for (size_t i = 0; i < memberLength; ++i) {
            DESERIALIZE_TRY(WGPUShaderModuleDescriptorDeserialize(&copiedMembers[i], &memberBuffer[i], buffer, size, allocator, resolver));
        }
    }

    return DeserializeResult::Success;
}
DAWN_UNUSED_FUNC(DeviceCreateShaderModuleDeserialize);

        
struct DeviceCreateSwapChainTransfer : CmdHeader {
    static_assert(1 <= 1,
                  "Record must be at most one of is_cmd, extensible, and chained.");
    WireCmd commandId;

    ObjectId self;
    ObjectId surface;
    ObjectHandle result;


};

static_assert(offsetof(DeviceCreateSwapChainTransfer, commandSize) == 0, "");
static_assert(offsetof(DeviceCreateSwapChainTransfer, commandId) == sizeof(CmdHeader), "");


DAWN_DECLARE_UNUSED size_t DeviceCreateSwapChainGetExtraRequiredSize(const DeviceCreateSwapChainCmd& record) {
    DAWN_UNUSED(record);

    size_t result = 0;



    {
    }
    {
    }
    {
        size_t memberLength = 1;
        result += memberLength * sizeof(WGPUSwapChainDescriptorTransfer);
        for (size_t i = 0; i < memberLength; ++i) {
            
            result += WGPUSwapChainDescriptorGetExtraRequiredSize(record.descriptor[i]);
        }
    }
    {
    }

    return result;
}
// GetExtraRequiredSize isn't used for structures that are value members of other structures
// because we assume they cannot contain pointers themselves.
DAWN_UNUSED_FUNC(DeviceCreateSwapChainGetExtraRequiredSize);

DAWN_DECLARE_UNUSED void DeviceCreateSwapChainSerialize(const DeviceCreateSwapChainCmd& record, DeviceCreateSwapChainTransfer* transfer,
                       char** buffer, const ObjectIdProvider& provider) {
    DAWN_UNUSED(buffer);

    transfer->commandId = WireCmd::DeviceCreateSwapChain;

    transfer->self = provider.GetId(record.self);

    transfer->surface = provider.GetOptionalId(record.surface);

    transfer->result = record.result;





    {
        size_t memberLength = 1;
        auto memberBuffer = reinterpret_cast<WGPUSwapChainDescriptorTransfer*>(*buffer);
        *buffer += memberLength * sizeof(WGPUSwapChainDescriptorTransfer);

        for (size_t i = 0; i < memberLength; ++i) {
            WGPUSwapChainDescriptorSerialize(record.descriptor[i], &memberBuffer[i], buffer, provider);

        }
    }
}
DAWN_UNUSED_FUNC(DeviceCreateSwapChainSerialize);

DAWN_DECLARE_UNUSED DeserializeResult DeviceCreateSwapChainDeserialize(DeviceCreateSwapChainCmd* record, const volatile DeviceCreateSwapChainTransfer* transfer,
                                      const volatile char** buffer, size_t* size, DeserializeAllocator* allocator, const ObjectIdResolver& resolver) {
    DAWN_UNUSED(allocator);
    DAWN_UNUSED(buffer);
    DAWN_UNUSED(size);

    ASSERT(transfer->commandId == WireCmd::DeviceCreateSwapChain);

    record->selfId = transfer->self;

    DESERIALIZE_TRY(resolver.GetFromId(transfer->self, &record->self));
    DESERIALIZE_TRY(resolver.GetOptionalFromId(transfer->surface, &record->surface));
    record->result = transfer->result;





    {
        size_t memberLength = 1;
        auto memberBuffer = reinterpret_cast<const volatile WGPUSwapChainDescriptorTransfer*>(buffer);
        DESERIALIZE_TRY(GetPtrFromBuffer(buffer, size, memberLength, &memberBuffer));

        WGPUSwapChainDescriptor* copiedMembers = nullptr;
        DESERIALIZE_TRY(GetSpace(allocator, memberLength, &copiedMembers));
        record->descriptor = copiedMembers;

        for (size_t i = 0; i < memberLength; ++i) {
            DESERIALIZE_TRY(WGPUSwapChainDescriptorDeserialize(&copiedMembers[i], &memberBuffer[i], buffer, size, allocator, resolver));
        }
    }

    return DeserializeResult::Success;
}
DAWN_UNUSED_FUNC(DeviceCreateSwapChainDeserialize);

        
struct DeviceCreateTextureTransfer : CmdHeader {
    static_assert(1 <= 1,
                  "Record must be at most one of is_cmd, extensible, and chained.");
    WireCmd commandId;

    ObjectId self;
    ObjectHandle result;


};

static_assert(offsetof(DeviceCreateTextureTransfer, commandSize) == 0, "");
static_assert(offsetof(DeviceCreateTextureTransfer, commandId) == sizeof(CmdHeader), "");


DAWN_DECLARE_UNUSED size_t DeviceCreateTextureGetExtraRequiredSize(const DeviceCreateTextureCmd& record) {
    DAWN_UNUSED(record);

    size_t result = 0;



    {
    }
    {
        size_t memberLength = 1;
        result += memberLength * sizeof(WGPUTextureDescriptorTransfer);
        for (size_t i = 0; i < memberLength; ++i) {
            
            result += WGPUTextureDescriptorGetExtraRequiredSize(record.descriptor[i]);
        }
    }
    {
    }

    return result;
}
// GetExtraRequiredSize isn't used for structures that are value members of other structures
// because we assume they cannot contain pointers themselves.
DAWN_UNUSED_FUNC(DeviceCreateTextureGetExtraRequiredSize);

DAWN_DECLARE_UNUSED void DeviceCreateTextureSerialize(const DeviceCreateTextureCmd& record, DeviceCreateTextureTransfer* transfer,
                       char** buffer, const ObjectIdProvider& provider) {
    DAWN_UNUSED(buffer);

    transfer->commandId = WireCmd::DeviceCreateTexture;

    transfer->self = provider.GetId(record.self);

    transfer->result = record.result;





    {
        size_t memberLength = 1;
        auto memberBuffer = reinterpret_cast<WGPUTextureDescriptorTransfer*>(*buffer);
        *buffer += memberLength * sizeof(WGPUTextureDescriptorTransfer);

        for (size_t i = 0; i < memberLength; ++i) {
            WGPUTextureDescriptorSerialize(record.descriptor[i], &memberBuffer[i], buffer, provider);

        }
    }
}
DAWN_UNUSED_FUNC(DeviceCreateTextureSerialize);

DAWN_DECLARE_UNUSED DeserializeResult DeviceCreateTextureDeserialize(DeviceCreateTextureCmd* record, const volatile DeviceCreateTextureTransfer* transfer,
                                      const volatile char** buffer, size_t* size, DeserializeAllocator* allocator, const ObjectIdResolver& resolver) {
    DAWN_UNUSED(allocator);
    DAWN_UNUSED(buffer);
    DAWN_UNUSED(size);

    ASSERT(transfer->commandId == WireCmd::DeviceCreateTexture);

    record->selfId = transfer->self;

    DESERIALIZE_TRY(resolver.GetFromId(transfer->self, &record->self));
    record->result = transfer->result;





    {
        size_t memberLength = 1;
        auto memberBuffer = reinterpret_cast<const volatile WGPUTextureDescriptorTransfer*>(buffer);
        DESERIALIZE_TRY(GetPtrFromBuffer(buffer, size, memberLength, &memberBuffer));

        WGPUTextureDescriptor* copiedMembers = nullptr;
        DESERIALIZE_TRY(GetSpace(allocator, memberLength, &copiedMembers));
        record->descriptor = copiedMembers;

        for (size_t i = 0; i < memberLength; ++i) {
            DESERIALIZE_TRY(WGPUTextureDescriptorDeserialize(&copiedMembers[i], &memberBuffer[i], buffer, size, allocator, resolver));
        }
    }

    return DeserializeResult::Success;
}
DAWN_UNUSED_FUNC(DeviceCreateTextureDeserialize);

        
struct DeviceGetDefaultQueueTransfer : CmdHeader {
    static_assert(1 <= 1,
                  "Record must be at most one of is_cmd, extensible, and chained.");
    WireCmd commandId;

    ObjectId self;
    ObjectHandle result;


};

static_assert(offsetof(DeviceGetDefaultQueueTransfer, commandSize) == 0, "");
static_assert(offsetof(DeviceGetDefaultQueueTransfer, commandId) == sizeof(CmdHeader), "");


DAWN_DECLARE_UNUSED size_t DeviceGetDefaultQueueGetExtraRequiredSize(const DeviceGetDefaultQueueCmd& record) {
    DAWN_UNUSED(record);

    size_t result = 0;



    {
    }
    {
    }

    return result;
}
// GetExtraRequiredSize isn't used for structures that are value members of other structures
// because we assume they cannot contain pointers themselves.
DAWN_UNUSED_FUNC(DeviceGetDefaultQueueGetExtraRequiredSize);

DAWN_DECLARE_UNUSED void DeviceGetDefaultQueueSerialize(const DeviceGetDefaultQueueCmd& record, DeviceGetDefaultQueueTransfer* transfer,
                       char** buffer, const ObjectIdProvider& provider) {
    DAWN_UNUSED(buffer);

    transfer->commandId = WireCmd::DeviceGetDefaultQueue;

    transfer->self = provider.GetId(record.self);

    transfer->result = record.result;




}
DAWN_UNUSED_FUNC(DeviceGetDefaultQueueSerialize);

DAWN_DECLARE_UNUSED DeserializeResult DeviceGetDefaultQueueDeserialize(DeviceGetDefaultQueueCmd* record, const volatile DeviceGetDefaultQueueTransfer* transfer,
                                      const volatile char** buffer, size_t* size, DeserializeAllocator* allocator, const ObjectIdResolver& resolver) {
    DAWN_UNUSED(allocator);
    DAWN_UNUSED(buffer);
    DAWN_UNUSED(size);

    ASSERT(transfer->commandId == WireCmd::DeviceGetDefaultQueue);

    record->selfId = transfer->self;

    DESERIALIZE_TRY(resolver.GetFromId(transfer->self, &record->self));
    record->result = transfer->result;





    return DeserializeResult::Success;
}
DAWN_UNUSED_FUNC(DeviceGetDefaultQueueDeserialize);

        
struct DeviceInjectErrorTransfer : CmdHeader {
    static_assert(1 <= 1,
                  "Record must be at most one of is_cmd, extensible, and chained.");
    WireCmd commandId;

    ObjectId self;
    WGPUErrorType type;

    size_t messageStrlen;

};

static_assert(offsetof(DeviceInjectErrorTransfer, commandSize) == 0, "");
static_assert(offsetof(DeviceInjectErrorTransfer, commandId) == sizeof(CmdHeader), "");


DAWN_DECLARE_UNUSED size_t DeviceInjectErrorGetExtraRequiredSize(const DeviceInjectErrorCmd& record) {
    DAWN_UNUSED(record);

    size_t result = 0;



    {
    result += std::strlen(record.message);
    }

    {
    }
    {
    }

    return result;
}
// GetExtraRequiredSize isn't used for structures that are value members of other structures
// because we assume they cannot contain pointers themselves.
DAWN_UNUSED_FUNC(DeviceInjectErrorGetExtraRequiredSize);

DAWN_DECLARE_UNUSED void DeviceInjectErrorSerialize(const DeviceInjectErrorCmd& record, DeviceInjectErrorTransfer* transfer,
                       char** buffer, const ObjectIdProvider& provider) {
    DAWN_UNUSED(buffer);

    transfer->commandId = WireCmd::DeviceInjectError;

    transfer->self = provider.GetId(record.self);

    transfer->type = record.type;




    {
    transfer->messageStrlen = std::strlen(record.message);

    memcpy(*buffer, record.message, transfer->messageStrlen);
    *buffer += transfer->messageStrlen;
    }

}
DAWN_UNUSED_FUNC(DeviceInjectErrorSerialize);

DAWN_DECLARE_UNUSED DeserializeResult DeviceInjectErrorDeserialize(DeviceInjectErrorCmd* record, const volatile DeviceInjectErrorTransfer* transfer,
                                      const volatile char** buffer, size_t* size, DeserializeAllocator* allocator, const ObjectIdResolver& resolver) {
    DAWN_UNUSED(allocator);
    DAWN_UNUSED(buffer);
    DAWN_UNUSED(size);

    ASSERT(transfer->commandId == WireCmd::DeviceInjectError);

    record->selfId = transfer->self;

    DESERIALIZE_TRY(resolver.GetFromId(transfer->self, &record->self));
    record->type = transfer->type;




    {
        size_t stringLength = transfer->messageStrlen;
        const volatile char* stringInBuffer = nullptr;
        DESERIALIZE_TRY(GetPtrFromBuffer(buffer, size, stringLength, &stringInBuffer));

        char* copiedString = nullptr;
        DESERIALIZE_TRY(GetSpace(allocator, stringLength + 1, &copiedString));
        std::copy(stringInBuffer, stringInBuffer + stringLength, copiedString);
        copiedString[stringLength] = '\0';
        record->message = copiedString;
    }


    return DeserializeResult::Success;
}
DAWN_UNUSED_FUNC(DeviceInjectErrorDeserialize);

        
struct DeviceLoseForTestingTransfer : CmdHeader {
    static_assert(1 <= 1,
                  "Record must be at most one of is_cmd, extensible, and chained.");
    WireCmd commandId;

    ObjectId self;


};

static_assert(offsetof(DeviceLoseForTestingTransfer, commandSize) == 0, "");
static_assert(offsetof(DeviceLoseForTestingTransfer, commandId) == sizeof(CmdHeader), "");


DAWN_DECLARE_UNUSED size_t DeviceLoseForTestingGetExtraRequiredSize(const DeviceLoseForTestingCmd& record) {
    DAWN_UNUSED(record);

    size_t result = 0;



    {
    }

    return result;
}
// GetExtraRequiredSize isn't used for structures that are value members of other structures
// because we assume they cannot contain pointers themselves.
DAWN_UNUSED_FUNC(DeviceLoseForTestingGetExtraRequiredSize);

DAWN_DECLARE_UNUSED void DeviceLoseForTestingSerialize(const DeviceLoseForTestingCmd& record, DeviceLoseForTestingTransfer* transfer,
                       char** buffer, const ObjectIdProvider& provider) {
    DAWN_UNUSED(buffer);

    transfer->commandId = WireCmd::DeviceLoseForTesting;

    transfer->self = provider.GetId(record.self);





}
DAWN_UNUSED_FUNC(DeviceLoseForTestingSerialize);

DAWN_DECLARE_UNUSED DeserializeResult DeviceLoseForTestingDeserialize(DeviceLoseForTestingCmd* record, const volatile DeviceLoseForTestingTransfer* transfer,
                                      const volatile char** buffer, size_t* size, DeserializeAllocator* allocator, const ObjectIdResolver& resolver) {
    DAWN_UNUSED(allocator);
    DAWN_UNUSED(buffer);
    DAWN_UNUSED(size);

    ASSERT(transfer->commandId == WireCmd::DeviceLoseForTesting);

    record->selfId = transfer->self;

    DESERIALIZE_TRY(resolver.GetFromId(transfer->self, &record->self));





    return DeserializeResult::Success;
}
DAWN_UNUSED_FUNC(DeviceLoseForTestingDeserialize);

        
struct DevicePopErrorScopeTransfer : CmdHeader {
    static_assert(1 <= 1,
                  "Record must be at most one of is_cmd, extensible, and chained.");
    WireCmd commandId;

    ObjectId device;
    uint64_t requestSerial;


};

static_assert(offsetof(DevicePopErrorScopeTransfer, commandSize) == 0, "");
static_assert(offsetof(DevicePopErrorScopeTransfer, commandId) == sizeof(CmdHeader), "");


DAWN_DECLARE_UNUSED size_t DevicePopErrorScopeGetExtraRequiredSize(const DevicePopErrorScopeCmd& record) {
    DAWN_UNUSED(record);

    size_t result = 0;



    {
    }
    {
    }

    return result;
}
// GetExtraRequiredSize isn't used for structures that are value members of other structures
// because we assume they cannot contain pointers themselves.
DAWN_UNUSED_FUNC(DevicePopErrorScopeGetExtraRequiredSize);

DAWN_DECLARE_UNUSED void DevicePopErrorScopeSerialize(const DevicePopErrorScopeCmd& record, DevicePopErrorScopeTransfer* transfer,
                       char** buffer, const ObjectIdProvider& provider) {
    DAWN_UNUSED(buffer);

    transfer->commandId = WireCmd::DevicePopErrorScope;

    transfer->device = provider.GetId(record.device);

    transfer->requestSerial = record.requestSerial;




}
DAWN_UNUSED_FUNC(DevicePopErrorScopeSerialize);

DAWN_DECLARE_UNUSED DeserializeResult DevicePopErrorScopeDeserialize(DevicePopErrorScopeCmd* record, const volatile DevicePopErrorScopeTransfer* transfer,
                                      const volatile char** buffer, size_t* size, DeserializeAllocator* allocator, const ObjectIdResolver& resolver) {
    DAWN_UNUSED(allocator);
    DAWN_UNUSED(buffer);
    DAWN_UNUSED(size);

    ASSERT(transfer->commandId == WireCmd::DevicePopErrorScope);


    DESERIALIZE_TRY(resolver.GetFromId(transfer->device, &record->device));
    record->requestSerial = transfer->requestSerial;





    return DeserializeResult::Success;
}
DAWN_UNUSED_FUNC(DevicePopErrorScopeDeserialize);

        
struct DevicePushErrorScopeTransfer : CmdHeader {
    static_assert(1 <= 1,
                  "Record must be at most one of is_cmd, extensible, and chained.");
    WireCmd commandId;

    ObjectId self;
    WGPUErrorFilter filter;


};

static_assert(offsetof(DevicePushErrorScopeTransfer, commandSize) == 0, "");
static_assert(offsetof(DevicePushErrorScopeTransfer, commandId) == sizeof(CmdHeader), "");


DAWN_DECLARE_UNUSED size_t DevicePushErrorScopeGetExtraRequiredSize(const DevicePushErrorScopeCmd& record) {
    DAWN_UNUSED(record);

    size_t result = 0;



    {
    }
    {
    }

    return result;
}
// GetExtraRequiredSize isn't used for structures that are value members of other structures
// because we assume they cannot contain pointers themselves.
DAWN_UNUSED_FUNC(DevicePushErrorScopeGetExtraRequiredSize);

DAWN_DECLARE_UNUSED void DevicePushErrorScopeSerialize(const DevicePushErrorScopeCmd& record, DevicePushErrorScopeTransfer* transfer,
                       char** buffer, const ObjectIdProvider& provider) {
    DAWN_UNUSED(buffer);

    transfer->commandId = WireCmd::DevicePushErrorScope;

    transfer->self = provider.GetId(record.self);

    transfer->filter = record.filter;




}
DAWN_UNUSED_FUNC(DevicePushErrorScopeSerialize);

DAWN_DECLARE_UNUSED DeserializeResult DevicePushErrorScopeDeserialize(DevicePushErrorScopeCmd* record, const volatile DevicePushErrorScopeTransfer* transfer,
                                      const volatile char** buffer, size_t* size, DeserializeAllocator* allocator, const ObjectIdResolver& resolver) {
    DAWN_UNUSED(allocator);
    DAWN_UNUSED(buffer);
    DAWN_UNUSED(size);

    ASSERT(transfer->commandId == WireCmd::DevicePushErrorScope);

    record->selfId = transfer->self;

    DESERIALIZE_TRY(resolver.GetFromId(transfer->self, &record->self));
    record->filter = transfer->filter;





    return DeserializeResult::Success;
}
DAWN_UNUSED_FUNC(DevicePushErrorScopeDeserialize);

        
struct DeviceTickTransfer : CmdHeader {
    static_assert(1 <= 1,
                  "Record must be at most one of is_cmd, extensible, and chained.");
    WireCmd commandId;

    ObjectId self;


};

static_assert(offsetof(DeviceTickTransfer, commandSize) == 0, "");
static_assert(offsetof(DeviceTickTransfer, commandId) == sizeof(CmdHeader), "");


DAWN_DECLARE_UNUSED size_t DeviceTickGetExtraRequiredSize(const DeviceTickCmd& record) {
    DAWN_UNUSED(record);

    size_t result = 0;



    {
    }

    return result;
}
// GetExtraRequiredSize isn't used for structures that are value members of other structures
// because we assume they cannot contain pointers themselves.
DAWN_UNUSED_FUNC(DeviceTickGetExtraRequiredSize);

DAWN_DECLARE_UNUSED void DeviceTickSerialize(const DeviceTickCmd& record, DeviceTickTransfer* transfer,
                       char** buffer, const ObjectIdProvider& provider) {
    DAWN_UNUSED(buffer);

    transfer->commandId = WireCmd::DeviceTick;

    transfer->self = provider.GetId(record.self);





}
DAWN_UNUSED_FUNC(DeviceTickSerialize);

DAWN_DECLARE_UNUSED DeserializeResult DeviceTickDeserialize(DeviceTickCmd* record, const volatile DeviceTickTransfer* transfer,
                                      const volatile char** buffer, size_t* size, DeserializeAllocator* allocator, const ObjectIdResolver& resolver) {
    DAWN_UNUSED(allocator);
    DAWN_UNUSED(buffer);
    DAWN_UNUSED(size);

    ASSERT(transfer->commandId == WireCmd::DeviceTick);

    record->selfId = transfer->self;

    DESERIALIZE_TRY(resolver.GetFromId(transfer->self, &record->self));





    return DeserializeResult::Success;
}
DAWN_UNUSED_FUNC(DeviceTickDeserialize);

        
struct FenceOnCompletionTransfer : CmdHeader {
    static_assert(1 <= 1,
                  "Record must be at most one of is_cmd, extensible, and chained.");
    WireCmd commandId;

    ObjectId fenceId;
    uint64_t value;
    uint64_t requestSerial;


};

static_assert(offsetof(FenceOnCompletionTransfer, commandSize) == 0, "");
static_assert(offsetof(FenceOnCompletionTransfer, commandId) == sizeof(CmdHeader), "");


DAWN_DECLARE_UNUSED size_t FenceOnCompletionGetExtraRequiredSize(const FenceOnCompletionCmd& record) {
    DAWN_UNUSED(record);

    size_t result = 0;



    {
    }
    {
    }
    {
    }

    return result;
}
// GetExtraRequiredSize isn't used for structures that are value members of other structures
// because we assume they cannot contain pointers themselves.
DAWN_UNUSED_FUNC(FenceOnCompletionGetExtraRequiredSize);

DAWN_DECLARE_UNUSED void FenceOnCompletionSerialize(const FenceOnCompletionCmd& record, FenceOnCompletionTransfer* transfer,
                       char** buffer) {
    DAWN_UNUSED(buffer);

    transfer->commandId = WireCmd::FenceOnCompletion;

    transfer->fenceId = record.fenceId;
    transfer->value = record.value;
    transfer->requestSerial = record.requestSerial;




}
DAWN_UNUSED_FUNC(FenceOnCompletionSerialize);

DAWN_DECLARE_UNUSED DeserializeResult FenceOnCompletionDeserialize(FenceOnCompletionCmd* record, const volatile FenceOnCompletionTransfer* transfer,
                                      const volatile char** buffer, size_t* size, DeserializeAllocator* allocator) {
    DAWN_UNUSED(allocator);
    DAWN_UNUSED(buffer);
    DAWN_UNUSED(size);

    ASSERT(transfer->commandId == WireCmd::FenceOnCompletion);


    record->fenceId = transfer->fenceId;
    record->value = transfer->value;
    record->requestSerial = transfer->requestSerial;





    return DeserializeResult::Success;
}
DAWN_UNUSED_FUNC(FenceOnCompletionDeserialize);

        
struct InstanceCreateSurfaceTransfer : CmdHeader {
    static_assert(1 <= 1,
                  "Record must be at most one of is_cmd, extensible, and chained.");
    WireCmd commandId;

    ObjectId self;
    ObjectHandle result;


};

static_assert(offsetof(InstanceCreateSurfaceTransfer, commandSize) == 0, "");
static_assert(offsetof(InstanceCreateSurfaceTransfer, commandId) == sizeof(CmdHeader), "");


DAWN_DECLARE_UNUSED size_t InstanceCreateSurfaceGetExtraRequiredSize(const InstanceCreateSurfaceCmd& record) {
    DAWN_UNUSED(record);

    size_t result = 0;



    {
    }
    {
        size_t memberLength = 1;
        result += memberLength * sizeof(WGPUSurfaceDescriptorTransfer);
        for (size_t i = 0; i < memberLength; ++i) {
            
            result += WGPUSurfaceDescriptorGetExtraRequiredSize(record.descriptor[i]);
        }
    }
    {
    }

    return result;
}
// GetExtraRequiredSize isn't used for structures that are value members of other structures
// because we assume they cannot contain pointers themselves.
DAWN_UNUSED_FUNC(InstanceCreateSurfaceGetExtraRequiredSize);

DAWN_DECLARE_UNUSED void InstanceCreateSurfaceSerialize(const InstanceCreateSurfaceCmd& record, InstanceCreateSurfaceTransfer* transfer,
                       char** buffer, const ObjectIdProvider& provider) {
    DAWN_UNUSED(buffer);

    transfer->commandId = WireCmd::InstanceCreateSurface;

    transfer->self = provider.GetId(record.self);

    transfer->result = record.result;





    {
        size_t memberLength = 1;
        auto memberBuffer = reinterpret_cast<WGPUSurfaceDescriptorTransfer*>(*buffer);
        *buffer += memberLength * sizeof(WGPUSurfaceDescriptorTransfer);

        for (size_t i = 0; i < memberLength; ++i) {
            WGPUSurfaceDescriptorSerialize(record.descriptor[i], &memberBuffer[i], buffer, provider);

        }
    }
}
DAWN_UNUSED_FUNC(InstanceCreateSurfaceSerialize);

DAWN_DECLARE_UNUSED DeserializeResult InstanceCreateSurfaceDeserialize(InstanceCreateSurfaceCmd* record, const volatile InstanceCreateSurfaceTransfer* transfer,
                                      const volatile char** buffer, size_t* size, DeserializeAllocator* allocator, const ObjectIdResolver& resolver) {
    DAWN_UNUSED(allocator);
    DAWN_UNUSED(buffer);
    DAWN_UNUSED(size);

    ASSERT(transfer->commandId == WireCmd::InstanceCreateSurface);

    record->selfId = transfer->self;

    DESERIALIZE_TRY(resolver.GetFromId(transfer->self, &record->self));
    record->result = transfer->result;





    {
        size_t memberLength = 1;
        auto memberBuffer = reinterpret_cast<const volatile WGPUSurfaceDescriptorTransfer*>(buffer);
        DESERIALIZE_TRY(GetPtrFromBuffer(buffer, size, memberLength, &memberBuffer));

        WGPUSurfaceDescriptor* copiedMembers = nullptr;
        DESERIALIZE_TRY(GetSpace(allocator, memberLength, &copiedMembers));
        record->descriptor = copiedMembers;

        for (size_t i = 0; i < memberLength; ++i) {
            DESERIALIZE_TRY(WGPUSurfaceDescriptorDeserialize(&copiedMembers[i], &memberBuffer[i], buffer, size, allocator, resolver));
        }
    }

    return DeserializeResult::Success;
}
DAWN_UNUSED_FUNC(InstanceCreateSurfaceDeserialize);

        
struct QuerySetDestroyTransfer : CmdHeader {
    static_assert(1 <= 1,
                  "Record must be at most one of is_cmd, extensible, and chained.");
    WireCmd commandId;

    ObjectId self;


};

static_assert(offsetof(QuerySetDestroyTransfer, commandSize) == 0, "");
static_assert(offsetof(QuerySetDestroyTransfer, commandId) == sizeof(CmdHeader), "");


DAWN_DECLARE_UNUSED size_t QuerySetDestroyGetExtraRequiredSize(const QuerySetDestroyCmd& record) {
    DAWN_UNUSED(record);

    size_t result = 0;



    {
    }

    return result;
}
// GetExtraRequiredSize isn't used for structures that are value members of other structures
// because we assume they cannot contain pointers themselves.
DAWN_UNUSED_FUNC(QuerySetDestroyGetExtraRequiredSize);

DAWN_DECLARE_UNUSED void QuerySetDestroySerialize(const QuerySetDestroyCmd& record, QuerySetDestroyTransfer* transfer,
                       char** buffer, const ObjectIdProvider& provider) {
    DAWN_UNUSED(buffer);

    transfer->commandId = WireCmd::QuerySetDestroy;

    transfer->self = provider.GetId(record.self);





}
DAWN_UNUSED_FUNC(QuerySetDestroySerialize);

DAWN_DECLARE_UNUSED DeserializeResult QuerySetDestroyDeserialize(QuerySetDestroyCmd* record, const volatile QuerySetDestroyTransfer* transfer,
                                      const volatile char** buffer, size_t* size, DeserializeAllocator* allocator, const ObjectIdResolver& resolver) {
    DAWN_UNUSED(allocator);
    DAWN_UNUSED(buffer);
    DAWN_UNUSED(size);

    ASSERT(transfer->commandId == WireCmd::QuerySetDestroy);

    record->selfId = transfer->self;

    DESERIALIZE_TRY(resolver.GetFromId(transfer->self, &record->self));





    return DeserializeResult::Success;
}
DAWN_UNUSED_FUNC(QuerySetDestroyDeserialize);

        
struct QueueCreateFenceTransfer : CmdHeader {
    static_assert(1 <= 1,
                  "Record must be at most one of is_cmd, extensible, and chained.");
    WireCmd commandId;

    ObjectId self;
    ObjectHandle result;


    bool has_descriptor;
};

static_assert(offsetof(QueueCreateFenceTransfer, commandSize) == 0, "");
static_assert(offsetof(QueueCreateFenceTransfer, commandId) == sizeof(CmdHeader), "");


DAWN_DECLARE_UNUSED size_t QueueCreateFenceGetExtraRequiredSize(const QueueCreateFenceCmd& record) {
    DAWN_UNUSED(record);

    size_t result = 0;



    {
    }
    if (record.descriptor != nullptr)
    {
        size_t memberLength = 1;
        result += memberLength * sizeof(WGPUFenceDescriptorTransfer);
        for (size_t i = 0; i < memberLength; ++i) {
            
            result += WGPUFenceDescriptorGetExtraRequiredSize(record.descriptor[i]);
        }
    }
    {
    }

    return result;
}
// GetExtraRequiredSize isn't used for structures that are value members of other structures
// because we assume they cannot contain pointers themselves.
DAWN_UNUSED_FUNC(QueueCreateFenceGetExtraRequiredSize);

DAWN_DECLARE_UNUSED void QueueCreateFenceSerialize(const QueueCreateFenceCmd& record, QueueCreateFenceTransfer* transfer,
                       char** buffer, const ObjectIdProvider& provider) {
    DAWN_UNUSED(buffer);

    transfer->commandId = WireCmd::QueueCreateFence;

    transfer->self = provider.GetId(record.self);

    transfer->result = record.result;





    bool has_descriptor = record.descriptor != nullptr;
    transfer->has_descriptor = has_descriptor;
    if (has_descriptor)
    {
        size_t memberLength = 1;
        auto memberBuffer = reinterpret_cast<WGPUFenceDescriptorTransfer*>(*buffer);
        *buffer += memberLength * sizeof(WGPUFenceDescriptorTransfer);

        for (size_t i = 0; i < memberLength; ++i) {
            WGPUFenceDescriptorSerialize(record.descriptor[i], &memberBuffer[i], buffer, provider);

        }
    }
}
DAWN_UNUSED_FUNC(QueueCreateFenceSerialize);

DAWN_DECLARE_UNUSED DeserializeResult QueueCreateFenceDeserialize(QueueCreateFenceCmd* record, const volatile QueueCreateFenceTransfer* transfer,
                                      const volatile char** buffer, size_t* size, DeserializeAllocator* allocator, const ObjectIdResolver& resolver) {
    DAWN_UNUSED(allocator);
    DAWN_UNUSED(buffer);
    DAWN_UNUSED(size);

    ASSERT(transfer->commandId == WireCmd::QueueCreateFence);

    record->selfId = transfer->self;

    DESERIALIZE_TRY(resolver.GetFromId(transfer->self, &record->self));
    record->result = transfer->result;





    bool has_descriptor = transfer->has_descriptor;
    record->descriptor = nullptr;
    if (has_descriptor)
    {
        size_t memberLength = 1;
        auto memberBuffer = reinterpret_cast<const volatile WGPUFenceDescriptorTransfer*>(buffer);
        DESERIALIZE_TRY(GetPtrFromBuffer(buffer, size, memberLength, &memberBuffer));

        WGPUFenceDescriptor* copiedMembers = nullptr;
        DESERIALIZE_TRY(GetSpace(allocator, memberLength, &copiedMembers));
        record->descriptor = copiedMembers;

        for (size_t i = 0; i < memberLength; ++i) {
            DESERIALIZE_TRY(WGPUFenceDescriptorDeserialize(&copiedMembers[i], &memberBuffer[i], buffer, size, allocator, resolver));
        }
    }

    return DeserializeResult::Success;
}
DAWN_UNUSED_FUNC(QueueCreateFenceDeserialize);

        
struct QueueSignalTransfer : CmdHeader {
    static_assert(1 <= 1,
                  "Record must be at most one of is_cmd, extensible, and chained.");
    WireCmd commandId;

    ObjectId self;
    ObjectId fence;
    uint64_t signalValue;


};

static_assert(offsetof(QueueSignalTransfer, commandSize) == 0, "");
static_assert(offsetof(QueueSignalTransfer, commandId) == sizeof(CmdHeader), "");


DAWN_DECLARE_UNUSED size_t QueueSignalGetExtraRequiredSize(const QueueSignalCmd& record) {
    DAWN_UNUSED(record);

    size_t result = 0;



    {
    }
    {
    }
    {
    }

    return result;
}
// GetExtraRequiredSize isn't used for structures that are value members of other structures
// because we assume they cannot contain pointers themselves.
DAWN_UNUSED_FUNC(QueueSignalGetExtraRequiredSize);

DAWN_DECLARE_UNUSED void QueueSignalSerialize(const QueueSignalCmd& record, QueueSignalTransfer* transfer,
                       char** buffer, const ObjectIdProvider& provider) {
    DAWN_UNUSED(buffer);

    transfer->commandId = WireCmd::QueueSignal;

    transfer->self = provider.GetId(record.self);

    transfer->fence = provider.GetId(record.fence);

    transfer->signalValue = record.signalValue;




}
DAWN_UNUSED_FUNC(QueueSignalSerialize);

DAWN_DECLARE_UNUSED DeserializeResult QueueSignalDeserialize(QueueSignalCmd* record, const volatile QueueSignalTransfer* transfer,
                                      const volatile char** buffer, size_t* size, DeserializeAllocator* allocator, const ObjectIdResolver& resolver) {
    DAWN_UNUSED(allocator);
    DAWN_UNUSED(buffer);
    DAWN_UNUSED(size);

    ASSERT(transfer->commandId == WireCmd::QueueSignal);

    record->selfId = transfer->self;

    DESERIALIZE_TRY(resolver.GetFromId(transfer->self, &record->self));
    DESERIALIZE_TRY(resolver.GetFromId(transfer->fence, &record->fence));
    record->signalValue = transfer->signalValue;





    return DeserializeResult::Success;
}
DAWN_UNUSED_FUNC(QueueSignalDeserialize);

        
struct QueueSubmitTransfer : CmdHeader {
    static_assert(1 <= 1,
                  "Record must be at most one of is_cmd, extensible, and chained.");
    WireCmd commandId;

    ObjectId self;
    uint32_t commandCount;


};

static_assert(offsetof(QueueSubmitTransfer, commandSize) == 0, "");
static_assert(offsetof(QueueSubmitTransfer, commandId) == sizeof(CmdHeader), "");


DAWN_DECLARE_UNUSED size_t QueueSubmitGetExtraRequiredSize(const QueueSubmitCmd& record) {
    DAWN_UNUSED(record);

    size_t result = 0;



    {
    }
    {
    }
    {
        size_t memberLength = record.commandCount;
        result += memberLength * sizeof(ObjectId);
    }

    return result;
}
// GetExtraRequiredSize isn't used for structures that are value members of other structures
// because we assume they cannot contain pointers themselves.
DAWN_UNUSED_FUNC(QueueSubmitGetExtraRequiredSize);

DAWN_DECLARE_UNUSED void QueueSubmitSerialize(const QueueSubmitCmd& record, QueueSubmitTransfer* transfer,
                       char** buffer, const ObjectIdProvider& provider) {
    DAWN_UNUSED(buffer);

    transfer->commandId = WireCmd::QueueSubmit;

    transfer->self = provider.GetId(record.self);

    transfer->commandCount = record.commandCount;





    {
        size_t memberLength = record.commandCount;
        auto memberBuffer = reinterpret_cast<ObjectId*>(*buffer);
        *buffer += memberLength * sizeof(ObjectId);

        for (size_t i = 0; i < memberLength; ++i) {
            memberBuffer[i] = provider.GetId(record.commands[i]);

        }
    }
}
DAWN_UNUSED_FUNC(QueueSubmitSerialize);

DAWN_DECLARE_UNUSED DeserializeResult QueueSubmitDeserialize(QueueSubmitCmd* record, const volatile QueueSubmitTransfer* transfer,
                                      const volatile char** buffer, size_t* size, DeserializeAllocator* allocator, const ObjectIdResolver& resolver) {
    DAWN_UNUSED(allocator);
    DAWN_UNUSED(buffer);
    DAWN_UNUSED(size);

    ASSERT(transfer->commandId == WireCmd::QueueSubmit);

    record->selfId = transfer->self;

    DESERIALIZE_TRY(resolver.GetFromId(transfer->self, &record->self));
    record->commandCount = transfer->commandCount;





    {
        size_t memberLength = record->commandCount;
        auto memberBuffer = reinterpret_cast<const volatile ObjectId*>(buffer);
        DESERIALIZE_TRY(GetPtrFromBuffer(buffer, size, memberLength, &memberBuffer));

        WGPUCommandBuffer* copiedMembers = nullptr;
        DESERIALIZE_TRY(GetSpace(allocator, memberLength, &copiedMembers));
        record->commands = copiedMembers;

        for (size_t i = 0; i < memberLength; ++i) {
            DESERIALIZE_TRY(resolver.GetFromId(memberBuffer[i], &copiedMembers[i]));
        }
    }

    return DeserializeResult::Success;
}
DAWN_UNUSED_FUNC(QueueSubmitDeserialize);

        
struct QueueWriteBufferInternalTransfer : CmdHeader {
    static_assert(1 <= 1,
                  "Record must be at most one of is_cmd, extensible, and chained.");
    WireCmd commandId;

    ObjectId queueId;
    ObjectId bufferId;
    uint64_t bufferOffset;
    size_t size;


};

static_assert(offsetof(QueueWriteBufferInternalTransfer, commandSize) == 0, "");
static_assert(offsetof(QueueWriteBufferInternalTransfer, commandId) == sizeof(CmdHeader), "");


DAWN_DECLARE_UNUSED size_t QueueWriteBufferInternalGetExtraRequiredSize(const QueueWriteBufferInternalCmd& record) {
    DAWN_UNUSED(record);

    size_t result = 0;



    {
    }
    {
    }
    {
    }
    {
        size_t memberLength = record.size;
        result += memberLength * sizeof(uint8_t);
    }
    {
    }

    return result;
}
// GetExtraRequiredSize isn't used for structures that are value members of other structures
// because we assume they cannot contain pointers themselves.
DAWN_UNUSED_FUNC(QueueWriteBufferInternalGetExtraRequiredSize);

DAWN_DECLARE_UNUSED void QueueWriteBufferInternalSerialize(const QueueWriteBufferInternalCmd& record, QueueWriteBufferInternalTransfer* transfer,
                       char** buffer) {
    DAWN_UNUSED(buffer);

    transfer->commandId = WireCmd::QueueWriteBufferInternal;

    transfer->queueId = record.queueId;
    transfer->bufferId = record.bufferId;
    transfer->bufferOffset = record.bufferOffset;
    transfer->size = record.size;





    {
        size_t memberLength = record.size;
        auto memberBuffer = reinterpret_cast<uint8_t*>(*buffer);
        *buffer += memberLength * sizeof(uint8_t);

        for (size_t i = 0; i < memberLength; ++i) {
            memberBuffer[i] = record.data[i];
        }
    }
}
DAWN_UNUSED_FUNC(QueueWriteBufferInternalSerialize);

DAWN_DECLARE_UNUSED DeserializeResult QueueWriteBufferInternalDeserialize(QueueWriteBufferInternalCmd* record, const volatile QueueWriteBufferInternalTransfer* transfer,
                                      const volatile char** buffer, size_t* size, DeserializeAllocator* allocator) {
    DAWN_UNUSED(allocator);
    DAWN_UNUSED(buffer);
    DAWN_UNUSED(size);

    ASSERT(transfer->commandId == WireCmd::QueueWriteBufferInternal);


    record->queueId = transfer->queueId;
    record->bufferId = transfer->bufferId;
    record->bufferOffset = transfer->bufferOffset;
    record->size = transfer->size;





    {
        size_t memberLength = record->size;
        auto memberBuffer = reinterpret_cast<const volatile uint8_t*>(buffer);
        DESERIALIZE_TRY(GetPtrFromBuffer(buffer, size, memberLength, &memberBuffer));

        uint8_t* copiedMembers = nullptr;
        DESERIALIZE_TRY(GetSpace(allocator, memberLength, &copiedMembers));
        record->data = copiedMembers;

        for (size_t i = 0; i < memberLength; ++i) {
            copiedMembers[i] = memberBuffer[i];
        }
    }

    return DeserializeResult::Success;
}
DAWN_UNUSED_FUNC(QueueWriteBufferInternalDeserialize);

        
struct QueueWriteTextureInternalTransfer : CmdHeader {
    static_assert(1 <= 1,
                  "Record must be at most one of is_cmd, extensible, and chained.");
    WireCmd commandId;

    ObjectId queueId;
    size_t dataSize;


};

static_assert(offsetof(QueueWriteTextureInternalTransfer, commandSize) == 0, "");
static_assert(offsetof(QueueWriteTextureInternalTransfer, commandId) == sizeof(CmdHeader), "");


DAWN_DECLARE_UNUSED size_t QueueWriteTextureInternalGetExtraRequiredSize(const QueueWriteTextureInternalCmd& record) {
    DAWN_UNUSED(record);

    size_t result = 0;



    {
    }
    {
        size_t memberLength = 1;
        result += memberLength * sizeof(WGPUTextureCopyViewTransfer);
        for (size_t i = 0; i < memberLength; ++i) {
            
            result += WGPUTextureCopyViewGetExtraRequiredSize(record.destination[i]);
        }
    }
    {
        size_t memberLength = record.dataSize;
        result += memberLength * sizeof(uint8_t);
    }
    {
    }
    {
        size_t memberLength = 1;
        result += memberLength * sizeof(WGPUTextureDataLayoutTransfer);
        for (size_t i = 0; i < memberLength; ++i) {
            
            result += WGPUTextureDataLayoutGetExtraRequiredSize(record.dataLayout[i]);
        }
    }
    {
        size_t memberLength = 1;
        result += memberLength * sizeof(WGPUExtent3DTransfer);
        for (size_t i = 0; i < memberLength; ++i) {
            
            result += WGPUExtent3DGetExtraRequiredSize(record.writeSize[i]);
        }
    }

    return result;
}
// GetExtraRequiredSize isn't used for structures that are value members of other structures
// because we assume they cannot contain pointers themselves.
DAWN_UNUSED_FUNC(QueueWriteTextureInternalGetExtraRequiredSize);

DAWN_DECLARE_UNUSED void QueueWriteTextureInternalSerialize(const QueueWriteTextureInternalCmd& record, QueueWriteTextureInternalTransfer* transfer,
                       char** buffer, const ObjectIdProvider& provider) {
    DAWN_UNUSED(buffer);

    transfer->commandId = WireCmd::QueueWriteTextureInternal;

    transfer->queueId = record.queueId;
    transfer->dataSize = record.dataSize;





    {
        size_t memberLength = 1;
        auto memberBuffer = reinterpret_cast<WGPUTextureCopyViewTransfer*>(*buffer);
        *buffer += memberLength * sizeof(WGPUTextureCopyViewTransfer);

        for (size_t i = 0; i < memberLength; ++i) {
            WGPUTextureCopyViewSerialize(record.destination[i], &memberBuffer[i], buffer, provider);

        }
    }

    {
        size_t memberLength = record.dataSize;
        auto memberBuffer = reinterpret_cast<uint8_t*>(*buffer);
        *buffer += memberLength * sizeof(uint8_t);

        for (size_t i = 0; i < memberLength; ++i) {
            memberBuffer[i] = record.data[i];
        }
    }

    {
        size_t memberLength = 1;
        auto memberBuffer = reinterpret_cast<WGPUTextureDataLayoutTransfer*>(*buffer);
        *buffer += memberLength * sizeof(WGPUTextureDataLayoutTransfer);

        for (size_t i = 0; i < memberLength; ++i) {
            WGPUTextureDataLayoutSerialize(record.dataLayout[i], &memberBuffer[i], buffer, provider);

        }
    }

    {
        size_t memberLength = 1;
        auto memberBuffer = reinterpret_cast<WGPUExtent3DTransfer*>(*buffer);
        *buffer += memberLength * sizeof(WGPUExtent3DTransfer);

        for (size_t i = 0; i < memberLength; ++i) {
            WGPUExtent3DSerialize(record.writeSize[i], &memberBuffer[i], buffer);

        }
    }
}
DAWN_UNUSED_FUNC(QueueWriteTextureInternalSerialize);

DAWN_DECLARE_UNUSED DeserializeResult QueueWriteTextureInternalDeserialize(QueueWriteTextureInternalCmd* record, const volatile QueueWriteTextureInternalTransfer* transfer,
                                      const volatile char** buffer, size_t* size, DeserializeAllocator* allocator, const ObjectIdResolver& resolver) {
    DAWN_UNUSED(allocator);
    DAWN_UNUSED(buffer);
    DAWN_UNUSED(size);

    ASSERT(transfer->commandId == WireCmd::QueueWriteTextureInternal);


    record->queueId = transfer->queueId;
    record->dataSize = transfer->dataSize;





    {
        size_t memberLength = 1;
        auto memberBuffer = reinterpret_cast<const volatile WGPUTextureCopyViewTransfer*>(buffer);
        DESERIALIZE_TRY(GetPtrFromBuffer(buffer, size, memberLength, &memberBuffer));

        WGPUTextureCopyView* copiedMembers = nullptr;
        DESERIALIZE_TRY(GetSpace(allocator, memberLength, &copiedMembers));
        record->destination = copiedMembers;

        for (size_t i = 0; i < memberLength; ++i) {
            DESERIALIZE_TRY(WGPUTextureCopyViewDeserialize(&copiedMembers[i], &memberBuffer[i], buffer, size, allocator, resolver));
        }
    }

    {
        size_t memberLength = record->dataSize;
        auto memberBuffer = reinterpret_cast<const volatile uint8_t*>(buffer);
        DESERIALIZE_TRY(GetPtrFromBuffer(buffer, size, memberLength, &memberBuffer));

        uint8_t* copiedMembers = nullptr;
        DESERIALIZE_TRY(GetSpace(allocator, memberLength, &copiedMembers));
        record->data = copiedMembers;

        for (size_t i = 0; i < memberLength; ++i) {
            copiedMembers[i] = memberBuffer[i];
        }
    }

    {
        size_t memberLength = 1;
        auto memberBuffer = reinterpret_cast<const volatile WGPUTextureDataLayoutTransfer*>(buffer);
        DESERIALIZE_TRY(GetPtrFromBuffer(buffer, size, memberLength, &memberBuffer));

        WGPUTextureDataLayout* copiedMembers = nullptr;
        DESERIALIZE_TRY(GetSpace(allocator, memberLength, &copiedMembers));
        record->dataLayout = copiedMembers;

        for (size_t i = 0; i < memberLength; ++i) {
            DESERIALIZE_TRY(WGPUTextureDataLayoutDeserialize(&copiedMembers[i], &memberBuffer[i], buffer, size, allocator, resolver));
        }
    }

    {
        size_t memberLength = 1;
        auto memberBuffer = reinterpret_cast<const volatile WGPUExtent3DTransfer*>(buffer);
        DESERIALIZE_TRY(GetPtrFromBuffer(buffer, size, memberLength, &memberBuffer));

        WGPUExtent3D* copiedMembers = nullptr;
        DESERIALIZE_TRY(GetSpace(allocator, memberLength, &copiedMembers));
        record->writeSize = copiedMembers;

        for (size_t i = 0; i < memberLength; ++i) {
            DESERIALIZE_TRY(WGPUExtent3DDeserialize(&copiedMembers[i], &memberBuffer[i], buffer, size, allocator));
        }
    }

    return DeserializeResult::Success;
}
DAWN_UNUSED_FUNC(QueueWriteTextureInternalDeserialize);

        
struct RenderBundleEncoderDrawTransfer : CmdHeader {
    static_assert(1 <= 1,
                  "Record must be at most one of is_cmd, extensible, and chained.");
    WireCmd commandId;

    ObjectId self;
    uint32_t vertexCount;
    uint32_t instanceCount;
    uint32_t firstVertex;
    uint32_t firstInstance;


};

static_assert(offsetof(RenderBundleEncoderDrawTransfer, commandSize) == 0, "");
static_assert(offsetof(RenderBundleEncoderDrawTransfer, commandId) == sizeof(CmdHeader), "");


DAWN_DECLARE_UNUSED size_t RenderBundleEncoderDrawGetExtraRequiredSize(const RenderBundleEncoderDrawCmd& record) {
    DAWN_UNUSED(record);

    size_t result = 0;



    {
    }
    {
    }
    {
    }
    {
    }
    {
    }

    return result;
}
// GetExtraRequiredSize isn't used for structures that are value members of other structures
// because we assume they cannot contain pointers themselves.
DAWN_UNUSED_FUNC(RenderBundleEncoderDrawGetExtraRequiredSize);

DAWN_DECLARE_UNUSED void RenderBundleEncoderDrawSerialize(const RenderBundleEncoderDrawCmd& record, RenderBundleEncoderDrawTransfer* transfer,
                       char** buffer, const ObjectIdProvider& provider) {
    DAWN_UNUSED(buffer);

    transfer->commandId = WireCmd::RenderBundleEncoderDraw;

    transfer->self = provider.GetId(record.self);

    transfer->vertexCount = record.vertexCount;
    transfer->instanceCount = record.instanceCount;
    transfer->firstVertex = record.firstVertex;
    transfer->firstInstance = record.firstInstance;




}
DAWN_UNUSED_FUNC(RenderBundleEncoderDrawSerialize);

DAWN_DECLARE_UNUSED DeserializeResult RenderBundleEncoderDrawDeserialize(RenderBundleEncoderDrawCmd* record, const volatile RenderBundleEncoderDrawTransfer* transfer,
                                      const volatile char** buffer, size_t* size, DeserializeAllocator* allocator, const ObjectIdResolver& resolver) {
    DAWN_UNUSED(allocator);
    DAWN_UNUSED(buffer);
    DAWN_UNUSED(size);

    ASSERT(transfer->commandId == WireCmd::RenderBundleEncoderDraw);

    record->selfId = transfer->self;

    DESERIALIZE_TRY(resolver.GetFromId(transfer->self, &record->self));
    record->vertexCount = transfer->vertexCount;
    record->instanceCount = transfer->instanceCount;
    record->firstVertex = transfer->firstVertex;
    record->firstInstance = transfer->firstInstance;





    return DeserializeResult::Success;
}
DAWN_UNUSED_FUNC(RenderBundleEncoderDrawDeserialize);

        
struct RenderBundleEncoderDrawIndexedTransfer : CmdHeader {
    static_assert(1 <= 1,
                  "Record must be at most one of is_cmd, extensible, and chained.");
    WireCmd commandId;

    ObjectId self;
    uint32_t indexCount;
    uint32_t instanceCount;
    uint32_t firstIndex;
    int32_t baseVertex;
    uint32_t firstInstance;


};

static_assert(offsetof(RenderBundleEncoderDrawIndexedTransfer, commandSize) == 0, "");
static_assert(offsetof(RenderBundleEncoderDrawIndexedTransfer, commandId) == sizeof(CmdHeader), "");


DAWN_DECLARE_UNUSED size_t RenderBundleEncoderDrawIndexedGetExtraRequiredSize(const RenderBundleEncoderDrawIndexedCmd& record) {
    DAWN_UNUSED(record);

    size_t result = 0;



    {
    }
    {
    }
    {
    }
    {
    }
    {
    }
    {
    }

    return result;
}
// GetExtraRequiredSize isn't used for structures that are value members of other structures
// because we assume they cannot contain pointers themselves.
DAWN_UNUSED_FUNC(RenderBundleEncoderDrawIndexedGetExtraRequiredSize);

DAWN_DECLARE_UNUSED void RenderBundleEncoderDrawIndexedSerialize(const RenderBundleEncoderDrawIndexedCmd& record, RenderBundleEncoderDrawIndexedTransfer* transfer,
                       char** buffer, const ObjectIdProvider& provider) {
    DAWN_UNUSED(buffer);

    transfer->commandId = WireCmd::RenderBundleEncoderDrawIndexed;

    transfer->self = provider.GetId(record.self);

    transfer->indexCount = record.indexCount;
    transfer->instanceCount = record.instanceCount;
    transfer->firstIndex = record.firstIndex;
    transfer->baseVertex = record.baseVertex;
    transfer->firstInstance = record.firstInstance;




}
DAWN_UNUSED_FUNC(RenderBundleEncoderDrawIndexedSerialize);

DAWN_DECLARE_UNUSED DeserializeResult RenderBundleEncoderDrawIndexedDeserialize(RenderBundleEncoderDrawIndexedCmd* record, const volatile RenderBundleEncoderDrawIndexedTransfer* transfer,
                                      const volatile char** buffer, size_t* size, DeserializeAllocator* allocator, const ObjectIdResolver& resolver) {
    DAWN_UNUSED(allocator);
    DAWN_UNUSED(buffer);
    DAWN_UNUSED(size);

    ASSERT(transfer->commandId == WireCmd::RenderBundleEncoderDrawIndexed);

    record->selfId = transfer->self;

    DESERIALIZE_TRY(resolver.GetFromId(transfer->self, &record->self));
    record->indexCount = transfer->indexCount;
    record->instanceCount = transfer->instanceCount;
    record->firstIndex = transfer->firstIndex;
    record->baseVertex = transfer->baseVertex;
    record->firstInstance = transfer->firstInstance;





    return DeserializeResult::Success;
}
DAWN_UNUSED_FUNC(RenderBundleEncoderDrawIndexedDeserialize);

        
struct RenderBundleEncoderDrawIndexedIndirectTransfer : CmdHeader {
    static_assert(1 <= 1,
                  "Record must be at most one of is_cmd, extensible, and chained.");
    WireCmd commandId;

    ObjectId self;
    ObjectId indirectBuffer;
    uint64_t indirectOffset;


};

static_assert(offsetof(RenderBundleEncoderDrawIndexedIndirectTransfer, commandSize) == 0, "");
static_assert(offsetof(RenderBundleEncoderDrawIndexedIndirectTransfer, commandId) == sizeof(CmdHeader), "");


DAWN_DECLARE_UNUSED size_t RenderBundleEncoderDrawIndexedIndirectGetExtraRequiredSize(const RenderBundleEncoderDrawIndexedIndirectCmd& record) {
    DAWN_UNUSED(record);

    size_t result = 0;



    {
    }
    {
    }
    {
    }

    return result;
}
// GetExtraRequiredSize isn't used for structures that are value members of other structures
// because we assume they cannot contain pointers themselves.
DAWN_UNUSED_FUNC(RenderBundleEncoderDrawIndexedIndirectGetExtraRequiredSize);

DAWN_DECLARE_UNUSED void RenderBundleEncoderDrawIndexedIndirectSerialize(const RenderBundleEncoderDrawIndexedIndirectCmd& record, RenderBundleEncoderDrawIndexedIndirectTransfer* transfer,
                       char** buffer, const ObjectIdProvider& provider) {
    DAWN_UNUSED(buffer);

    transfer->commandId = WireCmd::RenderBundleEncoderDrawIndexedIndirect;

    transfer->self = provider.GetId(record.self);

    transfer->indirectBuffer = provider.GetId(record.indirectBuffer);

    transfer->indirectOffset = record.indirectOffset;




}
DAWN_UNUSED_FUNC(RenderBundleEncoderDrawIndexedIndirectSerialize);

DAWN_DECLARE_UNUSED DeserializeResult RenderBundleEncoderDrawIndexedIndirectDeserialize(RenderBundleEncoderDrawIndexedIndirectCmd* record, const volatile RenderBundleEncoderDrawIndexedIndirectTransfer* transfer,
                                      const volatile char** buffer, size_t* size, DeserializeAllocator* allocator, const ObjectIdResolver& resolver) {
    DAWN_UNUSED(allocator);
    DAWN_UNUSED(buffer);
    DAWN_UNUSED(size);

    ASSERT(transfer->commandId == WireCmd::RenderBundleEncoderDrawIndexedIndirect);

    record->selfId = transfer->self;

    DESERIALIZE_TRY(resolver.GetFromId(transfer->self, &record->self));
    DESERIALIZE_TRY(resolver.GetFromId(transfer->indirectBuffer, &record->indirectBuffer));
    record->indirectOffset = transfer->indirectOffset;





    return DeserializeResult::Success;
}
DAWN_UNUSED_FUNC(RenderBundleEncoderDrawIndexedIndirectDeserialize);

        
struct RenderBundleEncoderDrawIndirectTransfer : CmdHeader {
    static_assert(1 <= 1,
                  "Record must be at most one of is_cmd, extensible, and chained.");
    WireCmd commandId;

    ObjectId self;
    ObjectId indirectBuffer;
    uint64_t indirectOffset;


};

static_assert(offsetof(RenderBundleEncoderDrawIndirectTransfer, commandSize) == 0, "");
static_assert(offsetof(RenderBundleEncoderDrawIndirectTransfer, commandId) == sizeof(CmdHeader), "");


DAWN_DECLARE_UNUSED size_t RenderBundleEncoderDrawIndirectGetExtraRequiredSize(const RenderBundleEncoderDrawIndirectCmd& record) {
    DAWN_UNUSED(record);

    size_t result = 0;



    {
    }
    {
    }
    {
    }

    return result;
}
// GetExtraRequiredSize isn't used for structures that are value members of other structures
// because we assume they cannot contain pointers themselves.
DAWN_UNUSED_FUNC(RenderBundleEncoderDrawIndirectGetExtraRequiredSize);

DAWN_DECLARE_UNUSED void RenderBundleEncoderDrawIndirectSerialize(const RenderBundleEncoderDrawIndirectCmd& record, RenderBundleEncoderDrawIndirectTransfer* transfer,
                       char** buffer, const ObjectIdProvider& provider) {
    DAWN_UNUSED(buffer);

    transfer->commandId = WireCmd::RenderBundleEncoderDrawIndirect;

    transfer->self = provider.GetId(record.self);

    transfer->indirectBuffer = provider.GetId(record.indirectBuffer);

    transfer->indirectOffset = record.indirectOffset;




}
DAWN_UNUSED_FUNC(RenderBundleEncoderDrawIndirectSerialize);

DAWN_DECLARE_UNUSED DeserializeResult RenderBundleEncoderDrawIndirectDeserialize(RenderBundleEncoderDrawIndirectCmd* record, const volatile RenderBundleEncoderDrawIndirectTransfer* transfer,
                                      const volatile char** buffer, size_t* size, DeserializeAllocator* allocator, const ObjectIdResolver& resolver) {
    DAWN_UNUSED(allocator);
    DAWN_UNUSED(buffer);
    DAWN_UNUSED(size);

    ASSERT(transfer->commandId == WireCmd::RenderBundleEncoderDrawIndirect);

    record->selfId = transfer->self;

    DESERIALIZE_TRY(resolver.GetFromId(transfer->self, &record->self));
    DESERIALIZE_TRY(resolver.GetFromId(transfer->indirectBuffer, &record->indirectBuffer));
    record->indirectOffset = transfer->indirectOffset;





    return DeserializeResult::Success;
}
DAWN_UNUSED_FUNC(RenderBundleEncoderDrawIndirectDeserialize);

        
struct RenderBundleEncoderFinishTransfer : CmdHeader {
    static_assert(1 <= 1,
                  "Record must be at most one of is_cmd, extensible, and chained.");
    WireCmd commandId;

    ObjectId self;
    ObjectHandle result;


    bool has_descriptor;
};

static_assert(offsetof(RenderBundleEncoderFinishTransfer, commandSize) == 0, "");
static_assert(offsetof(RenderBundleEncoderFinishTransfer, commandId) == sizeof(CmdHeader), "");


DAWN_DECLARE_UNUSED size_t RenderBundleEncoderFinishGetExtraRequiredSize(const RenderBundleEncoderFinishCmd& record) {
    DAWN_UNUSED(record);

    size_t result = 0;



    {
    }
    if (record.descriptor != nullptr)
    {
        size_t memberLength = 1;
        result += memberLength * sizeof(WGPURenderBundleDescriptorTransfer);
        for (size_t i = 0; i < memberLength; ++i) {
            
            result += WGPURenderBundleDescriptorGetExtraRequiredSize(record.descriptor[i]);
        }
    }
    {
    }

    return result;
}
// GetExtraRequiredSize isn't used for structures that are value members of other structures
// because we assume they cannot contain pointers themselves.
DAWN_UNUSED_FUNC(RenderBundleEncoderFinishGetExtraRequiredSize);

DAWN_DECLARE_UNUSED void RenderBundleEncoderFinishSerialize(const RenderBundleEncoderFinishCmd& record, RenderBundleEncoderFinishTransfer* transfer,
                       char** buffer, const ObjectIdProvider& provider) {
    DAWN_UNUSED(buffer);

    transfer->commandId = WireCmd::RenderBundleEncoderFinish;

    transfer->self = provider.GetId(record.self);

    transfer->result = record.result;





    bool has_descriptor = record.descriptor != nullptr;
    transfer->has_descriptor = has_descriptor;
    if (has_descriptor)
    {
        size_t memberLength = 1;
        auto memberBuffer = reinterpret_cast<WGPURenderBundleDescriptorTransfer*>(*buffer);
        *buffer += memberLength * sizeof(WGPURenderBundleDescriptorTransfer);

        for (size_t i = 0; i < memberLength; ++i) {
            WGPURenderBundleDescriptorSerialize(record.descriptor[i], &memberBuffer[i], buffer, provider);

        }
    }
}
DAWN_UNUSED_FUNC(RenderBundleEncoderFinishSerialize);

DAWN_DECLARE_UNUSED DeserializeResult RenderBundleEncoderFinishDeserialize(RenderBundleEncoderFinishCmd* record, const volatile RenderBundleEncoderFinishTransfer* transfer,
                                      const volatile char** buffer, size_t* size, DeserializeAllocator* allocator, const ObjectIdResolver& resolver) {
    DAWN_UNUSED(allocator);
    DAWN_UNUSED(buffer);
    DAWN_UNUSED(size);

    ASSERT(transfer->commandId == WireCmd::RenderBundleEncoderFinish);

    record->selfId = transfer->self;

    DESERIALIZE_TRY(resolver.GetFromId(transfer->self, &record->self));
    record->result = transfer->result;





    bool has_descriptor = transfer->has_descriptor;
    record->descriptor = nullptr;
    if (has_descriptor)
    {
        size_t memberLength = 1;
        auto memberBuffer = reinterpret_cast<const volatile WGPURenderBundleDescriptorTransfer*>(buffer);
        DESERIALIZE_TRY(GetPtrFromBuffer(buffer, size, memberLength, &memberBuffer));

        WGPURenderBundleDescriptor* copiedMembers = nullptr;
        DESERIALIZE_TRY(GetSpace(allocator, memberLength, &copiedMembers));
        record->descriptor = copiedMembers;

        for (size_t i = 0; i < memberLength; ++i) {
            DESERIALIZE_TRY(WGPURenderBundleDescriptorDeserialize(&copiedMembers[i], &memberBuffer[i], buffer, size, allocator, resolver));
        }
    }

    return DeserializeResult::Success;
}
DAWN_UNUSED_FUNC(RenderBundleEncoderFinishDeserialize);

        
struct RenderBundleEncoderInsertDebugMarkerTransfer : CmdHeader {
    static_assert(1 <= 1,
                  "Record must be at most one of is_cmd, extensible, and chained.");
    WireCmd commandId;

    ObjectId self;

    size_t markerLabelStrlen;

};

static_assert(offsetof(RenderBundleEncoderInsertDebugMarkerTransfer, commandSize) == 0, "");
static_assert(offsetof(RenderBundleEncoderInsertDebugMarkerTransfer, commandId) == sizeof(CmdHeader), "");


DAWN_DECLARE_UNUSED size_t RenderBundleEncoderInsertDebugMarkerGetExtraRequiredSize(const RenderBundleEncoderInsertDebugMarkerCmd& record) {
    DAWN_UNUSED(record);

    size_t result = 0;



    {
    result += std::strlen(record.markerLabel);
    }

    {
    }

    return result;
}
// GetExtraRequiredSize isn't used for structures that are value members of other structures
// because we assume they cannot contain pointers themselves.
DAWN_UNUSED_FUNC(RenderBundleEncoderInsertDebugMarkerGetExtraRequiredSize);

DAWN_DECLARE_UNUSED void RenderBundleEncoderInsertDebugMarkerSerialize(const RenderBundleEncoderInsertDebugMarkerCmd& record, RenderBundleEncoderInsertDebugMarkerTransfer* transfer,
                       char** buffer, const ObjectIdProvider& provider) {
    DAWN_UNUSED(buffer);

    transfer->commandId = WireCmd::RenderBundleEncoderInsertDebugMarker;

    transfer->self = provider.GetId(record.self);





    {
    transfer->markerLabelStrlen = std::strlen(record.markerLabel);

    memcpy(*buffer, record.markerLabel, transfer->markerLabelStrlen);
    *buffer += transfer->markerLabelStrlen;
    }

}
DAWN_UNUSED_FUNC(RenderBundleEncoderInsertDebugMarkerSerialize);

DAWN_DECLARE_UNUSED DeserializeResult RenderBundleEncoderInsertDebugMarkerDeserialize(RenderBundleEncoderInsertDebugMarkerCmd* record, const volatile RenderBundleEncoderInsertDebugMarkerTransfer* transfer,
                                      const volatile char** buffer, size_t* size, DeserializeAllocator* allocator, const ObjectIdResolver& resolver) {
    DAWN_UNUSED(allocator);
    DAWN_UNUSED(buffer);
    DAWN_UNUSED(size);

    ASSERT(transfer->commandId == WireCmd::RenderBundleEncoderInsertDebugMarker);

    record->selfId = transfer->self;

    DESERIALIZE_TRY(resolver.GetFromId(transfer->self, &record->self));




    {
        size_t stringLength = transfer->markerLabelStrlen;
        const volatile char* stringInBuffer = nullptr;
        DESERIALIZE_TRY(GetPtrFromBuffer(buffer, size, stringLength, &stringInBuffer));

        char* copiedString = nullptr;
        DESERIALIZE_TRY(GetSpace(allocator, stringLength + 1, &copiedString));
        std::copy(stringInBuffer, stringInBuffer + stringLength, copiedString);
        copiedString[stringLength] = '\0';
        record->markerLabel = copiedString;
    }


    return DeserializeResult::Success;
}
DAWN_UNUSED_FUNC(RenderBundleEncoderInsertDebugMarkerDeserialize);

        
struct RenderBundleEncoderPopDebugGroupTransfer : CmdHeader {
    static_assert(1 <= 1,
                  "Record must be at most one of is_cmd, extensible, and chained.");
    WireCmd commandId;

    ObjectId self;


};

static_assert(offsetof(RenderBundleEncoderPopDebugGroupTransfer, commandSize) == 0, "");
static_assert(offsetof(RenderBundleEncoderPopDebugGroupTransfer, commandId) == sizeof(CmdHeader), "");


DAWN_DECLARE_UNUSED size_t RenderBundleEncoderPopDebugGroupGetExtraRequiredSize(const RenderBundleEncoderPopDebugGroupCmd& record) {
    DAWN_UNUSED(record);

    size_t result = 0;



    {
    }

    return result;
}
// GetExtraRequiredSize isn't used for structures that are value members of other structures
// because we assume they cannot contain pointers themselves.
DAWN_UNUSED_FUNC(RenderBundleEncoderPopDebugGroupGetExtraRequiredSize);

DAWN_DECLARE_UNUSED void RenderBundleEncoderPopDebugGroupSerialize(const RenderBundleEncoderPopDebugGroupCmd& record, RenderBundleEncoderPopDebugGroupTransfer* transfer,
                       char** buffer, const ObjectIdProvider& provider) {
    DAWN_UNUSED(buffer);

    transfer->commandId = WireCmd::RenderBundleEncoderPopDebugGroup;

    transfer->self = provider.GetId(record.self);





}
DAWN_UNUSED_FUNC(RenderBundleEncoderPopDebugGroupSerialize);

DAWN_DECLARE_UNUSED DeserializeResult RenderBundleEncoderPopDebugGroupDeserialize(RenderBundleEncoderPopDebugGroupCmd* record, const volatile RenderBundleEncoderPopDebugGroupTransfer* transfer,
                                      const volatile char** buffer, size_t* size, DeserializeAllocator* allocator, const ObjectIdResolver& resolver) {
    DAWN_UNUSED(allocator);
    DAWN_UNUSED(buffer);
    DAWN_UNUSED(size);

    ASSERT(transfer->commandId == WireCmd::RenderBundleEncoderPopDebugGroup);

    record->selfId = transfer->self;

    DESERIALIZE_TRY(resolver.GetFromId(transfer->self, &record->self));





    return DeserializeResult::Success;
}
DAWN_UNUSED_FUNC(RenderBundleEncoderPopDebugGroupDeserialize);

        
struct RenderBundleEncoderPushDebugGroupTransfer : CmdHeader {
    static_assert(1 <= 1,
                  "Record must be at most one of is_cmd, extensible, and chained.");
    WireCmd commandId;

    ObjectId self;

    size_t groupLabelStrlen;

};

static_assert(offsetof(RenderBundleEncoderPushDebugGroupTransfer, commandSize) == 0, "");
static_assert(offsetof(RenderBundleEncoderPushDebugGroupTransfer, commandId) == sizeof(CmdHeader), "");


DAWN_DECLARE_UNUSED size_t RenderBundleEncoderPushDebugGroupGetExtraRequiredSize(const RenderBundleEncoderPushDebugGroupCmd& record) {
    DAWN_UNUSED(record);

    size_t result = 0;



    {
    result += std::strlen(record.groupLabel);
    }

    {
    }

    return result;
}
// GetExtraRequiredSize isn't used for structures that are value members of other structures
// because we assume they cannot contain pointers themselves.
DAWN_UNUSED_FUNC(RenderBundleEncoderPushDebugGroupGetExtraRequiredSize);

DAWN_DECLARE_UNUSED void RenderBundleEncoderPushDebugGroupSerialize(const RenderBundleEncoderPushDebugGroupCmd& record, RenderBundleEncoderPushDebugGroupTransfer* transfer,
                       char** buffer, const ObjectIdProvider& provider) {
    DAWN_UNUSED(buffer);

    transfer->commandId = WireCmd::RenderBundleEncoderPushDebugGroup;

    transfer->self = provider.GetId(record.self);





    {
    transfer->groupLabelStrlen = std::strlen(record.groupLabel);

    memcpy(*buffer, record.groupLabel, transfer->groupLabelStrlen);
    *buffer += transfer->groupLabelStrlen;
    }

}
DAWN_UNUSED_FUNC(RenderBundleEncoderPushDebugGroupSerialize);

DAWN_DECLARE_UNUSED DeserializeResult RenderBundleEncoderPushDebugGroupDeserialize(RenderBundleEncoderPushDebugGroupCmd* record, const volatile RenderBundleEncoderPushDebugGroupTransfer* transfer,
                                      const volatile char** buffer, size_t* size, DeserializeAllocator* allocator, const ObjectIdResolver& resolver) {
    DAWN_UNUSED(allocator);
    DAWN_UNUSED(buffer);
    DAWN_UNUSED(size);

    ASSERT(transfer->commandId == WireCmd::RenderBundleEncoderPushDebugGroup);

    record->selfId = transfer->self;

    DESERIALIZE_TRY(resolver.GetFromId(transfer->self, &record->self));




    {
        size_t stringLength = transfer->groupLabelStrlen;
        const volatile char* stringInBuffer = nullptr;
        DESERIALIZE_TRY(GetPtrFromBuffer(buffer, size, stringLength, &stringInBuffer));

        char* copiedString = nullptr;
        DESERIALIZE_TRY(GetSpace(allocator, stringLength + 1, &copiedString));
        std::copy(stringInBuffer, stringInBuffer + stringLength, copiedString);
        copiedString[stringLength] = '\0';
        record->groupLabel = copiedString;
    }


    return DeserializeResult::Success;
}
DAWN_UNUSED_FUNC(RenderBundleEncoderPushDebugGroupDeserialize);

        
struct RenderBundleEncoderSetBindGroupTransfer : CmdHeader {
    static_assert(1 <= 1,
                  "Record must be at most one of is_cmd, extensible, and chained.");
    WireCmd commandId;

    ObjectId self;
    uint32_t groupIndex;
    ObjectId group;
    uint32_t dynamicOffsetCount;


    bool has_dynamicOffsets;
};

static_assert(offsetof(RenderBundleEncoderSetBindGroupTransfer, commandSize) == 0, "");
static_assert(offsetof(RenderBundleEncoderSetBindGroupTransfer, commandId) == sizeof(CmdHeader), "");


DAWN_DECLARE_UNUSED size_t RenderBundleEncoderSetBindGroupGetExtraRequiredSize(const RenderBundleEncoderSetBindGroupCmd& record) {
    DAWN_UNUSED(record);

    size_t result = 0;



    {
    }
    {
    }
    {
    }
    {
    }
    if (record.dynamicOffsets != nullptr)
    {
        size_t memberLength = record.dynamicOffsetCount;
        result += memberLength * sizeof(uint32_t);
    }

    return result;
}
// GetExtraRequiredSize isn't used for structures that are value members of other structures
// because we assume they cannot contain pointers themselves.
DAWN_UNUSED_FUNC(RenderBundleEncoderSetBindGroupGetExtraRequiredSize);

DAWN_DECLARE_UNUSED void RenderBundleEncoderSetBindGroupSerialize(const RenderBundleEncoderSetBindGroupCmd& record, RenderBundleEncoderSetBindGroupTransfer* transfer,
                       char** buffer, const ObjectIdProvider& provider) {
    DAWN_UNUSED(buffer);

    transfer->commandId = WireCmd::RenderBundleEncoderSetBindGroup;

    transfer->self = provider.GetId(record.self);

    transfer->groupIndex = record.groupIndex;
    transfer->group = provider.GetId(record.group);

    transfer->dynamicOffsetCount = record.dynamicOffsetCount;





    bool has_dynamicOffsets = record.dynamicOffsets != nullptr;
    transfer->has_dynamicOffsets = has_dynamicOffsets;
    if (has_dynamicOffsets)
    {
        size_t memberLength = record.dynamicOffsetCount;
        auto memberBuffer = reinterpret_cast<uint32_t*>(*buffer);
        *buffer += memberLength * sizeof(uint32_t);

        for (size_t i = 0; i < memberLength; ++i) {
            memberBuffer[i] = record.dynamicOffsets[i];
        }
    }
}
DAWN_UNUSED_FUNC(RenderBundleEncoderSetBindGroupSerialize);

DAWN_DECLARE_UNUSED DeserializeResult RenderBundleEncoderSetBindGroupDeserialize(RenderBundleEncoderSetBindGroupCmd* record, const volatile RenderBundleEncoderSetBindGroupTransfer* transfer,
                                      const volatile char** buffer, size_t* size, DeserializeAllocator* allocator, const ObjectIdResolver& resolver) {
    DAWN_UNUSED(allocator);
    DAWN_UNUSED(buffer);
    DAWN_UNUSED(size);

    ASSERT(transfer->commandId == WireCmd::RenderBundleEncoderSetBindGroup);

    record->selfId = transfer->self;

    DESERIALIZE_TRY(resolver.GetFromId(transfer->self, &record->self));
    record->groupIndex = transfer->groupIndex;
    DESERIALIZE_TRY(resolver.GetFromId(transfer->group, &record->group));
    record->dynamicOffsetCount = transfer->dynamicOffsetCount;





    bool has_dynamicOffsets = transfer->has_dynamicOffsets;
    record->dynamicOffsets = nullptr;
    if (has_dynamicOffsets)
    {
        size_t memberLength = record->dynamicOffsetCount;
        auto memberBuffer = reinterpret_cast<const volatile uint32_t*>(buffer);
        DESERIALIZE_TRY(GetPtrFromBuffer(buffer, size, memberLength, &memberBuffer));

        uint32_t* copiedMembers = nullptr;
        DESERIALIZE_TRY(GetSpace(allocator, memberLength, &copiedMembers));
        record->dynamicOffsets = copiedMembers;

        for (size_t i = 0; i < memberLength; ++i) {
            copiedMembers[i] = memberBuffer[i];
        }
    }

    return DeserializeResult::Success;
}
DAWN_UNUSED_FUNC(RenderBundleEncoderSetBindGroupDeserialize);

        
struct RenderBundleEncoderSetIndexBufferTransfer : CmdHeader {
    static_assert(1 <= 1,
                  "Record must be at most one of is_cmd, extensible, and chained.");
    WireCmd commandId;

    ObjectId self;
    ObjectId buffer;
    uint64_t offset;
    uint64_t size;


};

static_assert(offsetof(RenderBundleEncoderSetIndexBufferTransfer, commandSize) == 0, "");
static_assert(offsetof(RenderBundleEncoderSetIndexBufferTransfer, commandId) == sizeof(CmdHeader), "");


DAWN_DECLARE_UNUSED size_t RenderBundleEncoderSetIndexBufferGetExtraRequiredSize(const RenderBundleEncoderSetIndexBufferCmd& record) {
    DAWN_UNUSED(record);

    size_t result = 0;



    {
    }
    {
    }
    {
    }
    {
    }

    return result;
}
// GetExtraRequiredSize isn't used for structures that are value members of other structures
// because we assume they cannot contain pointers themselves.
DAWN_UNUSED_FUNC(RenderBundleEncoderSetIndexBufferGetExtraRequiredSize);

DAWN_DECLARE_UNUSED void RenderBundleEncoderSetIndexBufferSerialize(const RenderBundleEncoderSetIndexBufferCmd& record, RenderBundleEncoderSetIndexBufferTransfer* transfer,
                       char** buffer, const ObjectIdProvider& provider) {
    DAWN_UNUSED(buffer);

    transfer->commandId = WireCmd::RenderBundleEncoderSetIndexBuffer;

    transfer->self = provider.GetId(record.self);

    transfer->buffer = provider.GetId(record.buffer);

    transfer->offset = record.offset;
    transfer->size = record.size;




}
DAWN_UNUSED_FUNC(RenderBundleEncoderSetIndexBufferSerialize);

DAWN_DECLARE_UNUSED DeserializeResult RenderBundleEncoderSetIndexBufferDeserialize(RenderBundleEncoderSetIndexBufferCmd* record, const volatile RenderBundleEncoderSetIndexBufferTransfer* transfer,
                                      const volatile char** buffer, size_t* size, DeserializeAllocator* allocator, const ObjectIdResolver& resolver) {
    DAWN_UNUSED(allocator);
    DAWN_UNUSED(buffer);
    DAWN_UNUSED(size);

    ASSERT(transfer->commandId == WireCmd::RenderBundleEncoderSetIndexBuffer);

    record->selfId = transfer->self;

    DESERIALIZE_TRY(resolver.GetFromId(transfer->self, &record->self));
    DESERIALIZE_TRY(resolver.GetFromId(transfer->buffer, &record->buffer));
    record->offset = transfer->offset;
    record->size = transfer->size;





    return DeserializeResult::Success;
}
DAWN_UNUSED_FUNC(RenderBundleEncoderSetIndexBufferDeserialize);

        
struct RenderBundleEncoderSetIndexBufferWithFormatTransfer : CmdHeader {
    static_assert(1 <= 1,
                  "Record must be at most one of is_cmd, extensible, and chained.");
    WireCmd commandId;

    ObjectId self;
    ObjectId buffer;
    WGPUIndexFormat format;
    uint64_t offset;
    uint64_t size;


};

static_assert(offsetof(RenderBundleEncoderSetIndexBufferWithFormatTransfer, commandSize) == 0, "");
static_assert(offsetof(RenderBundleEncoderSetIndexBufferWithFormatTransfer, commandId) == sizeof(CmdHeader), "");


DAWN_DECLARE_UNUSED size_t RenderBundleEncoderSetIndexBufferWithFormatGetExtraRequiredSize(const RenderBundleEncoderSetIndexBufferWithFormatCmd& record) {
    DAWN_UNUSED(record);

    size_t result = 0;



    {
    }
    {
    }
    {
    }
    {
    }
    {
    }

    return result;
}
// GetExtraRequiredSize isn't used for structures that are value members of other structures
// because we assume they cannot contain pointers themselves.
DAWN_UNUSED_FUNC(RenderBundleEncoderSetIndexBufferWithFormatGetExtraRequiredSize);

DAWN_DECLARE_UNUSED void RenderBundleEncoderSetIndexBufferWithFormatSerialize(const RenderBundleEncoderSetIndexBufferWithFormatCmd& record, RenderBundleEncoderSetIndexBufferWithFormatTransfer* transfer,
                       char** buffer, const ObjectIdProvider& provider) {
    DAWN_UNUSED(buffer);

    transfer->commandId = WireCmd::RenderBundleEncoderSetIndexBufferWithFormat;

    transfer->self = provider.GetId(record.self);

    transfer->buffer = provider.GetId(record.buffer);

    transfer->format = record.format;
    transfer->offset = record.offset;
    transfer->size = record.size;




}
DAWN_UNUSED_FUNC(RenderBundleEncoderSetIndexBufferWithFormatSerialize);

DAWN_DECLARE_UNUSED DeserializeResult RenderBundleEncoderSetIndexBufferWithFormatDeserialize(RenderBundleEncoderSetIndexBufferWithFormatCmd* record, const volatile RenderBundleEncoderSetIndexBufferWithFormatTransfer* transfer,
                                      const volatile char** buffer, size_t* size, DeserializeAllocator* allocator, const ObjectIdResolver& resolver) {
    DAWN_UNUSED(allocator);
    DAWN_UNUSED(buffer);
    DAWN_UNUSED(size);

    ASSERT(transfer->commandId == WireCmd::RenderBundleEncoderSetIndexBufferWithFormat);

    record->selfId = transfer->self;

    DESERIALIZE_TRY(resolver.GetFromId(transfer->self, &record->self));
    DESERIALIZE_TRY(resolver.GetFromId(transfer->buffer, &record->buffer));
    record->format = transfer->format;
    record->offset = transfer->offset;
    record->size = transfer->size;





    return DeserializeResult::Success;
}
DAWN_UNUSED_FUNC(RenderBundleEncoderSetIndexBufferWithFormatDeserialize);

        
struct RenderBundleEncoderSetPipelineTransfer : CmdHeader {
    static_assert(1 <= 1,
                  "Record must be at most one of is_cmd, extensible, and chained.");
    WireCmd commandId;

    ObjectId self;
    ObjectId pipeline;


};

static_assert(offsetof(RenderBundleEncoderSetPipelineTransfer, commandSize) == 0, "");
static_assert(offsetof(RenderBundleEncoderSetPipelineTransfer, commandId) == sizeof(CmdHeader), "");


DAWN_DECLARE_UNUSED size_t RenderBundleEncoderSetPipelineGetExtraRequiredSize(const RenderBundleEncoderSetPipelineCmd& record) {
    DAWN_UNUSED(record);

    size_t result = 0;



    {
    }
    {
    }

    return result;
}
// GetExtraRequiredSize isn't used for structures that are value members of other structures
// because we assume they cannot contain pointers themselves.
DAWN_UNUSED_FUNC(RenderBundleEncoderSetPipelineGetExtraRequiredSize);

DAWN_DECLARE_UNUSED void RenderBundleEncoderSetPipelineSerialize(const RenderBundleEncoderSetPipelineCmd& record, RenderBundleEncoderSetPipelineTransfer* transfer,
                       char** buffer, const ObjectIdProvider& provider) {
    DAWN_UNUSED(buffer);

    transfer->commandId = WireCmd::RenderBundleEncoderSetPipeline;

    transfer->self = provider.GetId(record.self);

    transfer->pipeline = provider.GetId(record.pipeline);





}
DAWN_UNUSED_FUNC(RenderBundleEncoderSetPipelineSerialize);

DAWN_DECLARE_UNUSED DeserializeResult RenderBundleEncoderSetPipelineDeserialize(RenderBundleEncoderSetPipelineCmd* record, const volatile RenderBundleEncoderSetPipelineTransfer* transfer,
                                      const volatile char** buffer, size_t* size, DeserializeAllocator* allocator, const ObjectIdResolver& resolver) {
    DAWN_UNUSED(allocator);
    DAWN_UNUSED(buffer);
    DAWN_UNUSED(size);

    ASSERT(transfer->commandId == WireCmd::RenderBundleEncoderSetPipeline);

    record->selfId = transfer->self;

    DESERIALIZE_TRY(resolver.GetFromId(transfer->self, &record->self));
    DESERIALIZE_TRY(resolver.GetFromId(transfer->pipeline, &record->pipeline));





    return DeserializeResult::Success;
}
DAWN_UNUSED_FUNC(RenderBundleEncoderSetPipelineDeserialize);

        
struct RenderBundleEncoderSetVertexBufferTransfer : CmdHeader {
    static_assert(1 <= 1,
                  "Record must be at most one of is_cmd, extensible, and chained.");
    WireCmd commandId;

    ObjectId self;
    uint32_t slot;
    ObjectId buffer;
    uint64_t offset;
    uint64_t size;


};

static_assert(offsetof(RenderBundleEncoderSetVertexBufferTransfer, commandSize) == 0, "");
static_assert(offsetof(RenderBundleEncoderSetVertexBufferTransfer, commandId) == sizeof(CmdHeader), "");


DAWN_DECLARE_UNUSED size_t RenderBundleEncoderSetVertexBufferGetExtraRequiredSize(const RenderBundleEncoderSetVertexBufferCmd& record) {
    DAWN_UNUSED(record);

    size_t result = 0;



    {
    }
    {
    }
    {
    }
    {
    }
    {
    }

    return result;
}
// GetExtraRequiredSize isn't used for structures that are value members of other structures
// because we assume they cannot contain pointers themselves.
DAWN_UNUSED_FUNC(RenderBundleEncoderSetVertexBufferGetExtraRequiredSize);

DAWN_DECLARE_UNUSED void RenderBundleEncoderSetVertexBufferSerialize(const RenderBundleEncoderSetVertexBufferCmd& record, RenderBundleEncoderSetVertexBufferTransfer* transfer,
                       char** buffer, const ObjectIdProvider& provider) {
    DAWN_UNUSED(buffer);

    transfer->commandId = WireCmd::RenderBundleEncoderSetVertexBuffer;

    transfer->self = provider.GetId(record.self);

    transfer->slot = record.slot;
    transfer->buffer = provider.GetId(record.buffer);

    transfer->offset = record.offset;
    transfer->size = record.size;




}
DAWN_UNUSED_FUNC(RenderBundleEncoderSetVertexBufferSerialize);

DAWN_DECLARE_UNUSED DeserializeResult RenderBundleEncoderSetVertexBufferDeserialize(RenderBundleEncoderSetVertexBufferCmd* record, const volatile RenderBundleEncoderSetVertexBufferTransfer* transfer,
                                      const volatile char** buffer, size_t* size, DeserializeAllocator* allocator, const ObjectIdResolver& resolver) {
    DAWN_UNUSED(allocator);
    DAWN_UNUSED(buffer);
    DAWN_UNUSED(size);

    ASSERT(transfer->commandId == WireCmd::RenderBundleEncoderSetVertexBuffer);

    record->selfId = transfer->self;

    DESERIALIZE_TRY(resolver.GetFromId(transfer->self, &record->self));
    record->slot = transfer->slot;
    DESERIALIZE_TRY(resolver.GetFromId(transfer->buffer, &record->buffer));
    record->offset = transfer->offset;
    record->size = transfer->size;





    return DeserializeResult::Success;
}
DAWN_UNUSED_FUNC(RenderBundleEncoderSetVertexBufferDeserialize);

        
struct RenderPassEncoderDrawTransfer : CmdHeader {
    static_assert(1 <= 1,
                  "Record must be at most one of is_cmd, extensible, and chained.");
    WireCmd commandId;

    ObjectId self;
    uint32_t vertexCount;
    uint32_t instanceCount;
    uint32_t firstVertex;
    uint32_t firstInstance;


};

static_assert(offsetof(RenderPassEncoderDrawTransfer, commandSize) == 0, "");
static_assert(offsetof(RenderPassEncoderDrawTransfer, commandId) == sizeof(CmdHeader), "");


DAWN_DECLARE_UNUSED size_t RenderPassEncoderDrawGetExtraRequiredSize(const RenderPassEncoderDrawCmd& record) {
    DAWN_UNUSED(record);

    size_t result = 0;



    {
    }
    {
    }
    {
    }
    {
    }
    {
    }

    return result;
}
// GetExtraRequiredSize isn't used for structures that are value members of other structures
// because we assume they cannot contain pointers themselves.
DAWN_UNUSED_FUNC(RenderPassEncoderDrawGetExtraRequiredSize);

DAWN_DECLARE_UNUSED void RenderPassEncoderDrawSerialize(const RenderPassEncoderDrawCmd& record, RenderPassEncoderDrawTransfer* transfer,
                       char** buffer, const ObjectIdProvider& provider) {
    DAWN_UNUSED(buffer);

    transfer->commandId = WireCmd::RenderPassEncoderDraw;

    transfer->self = provider.GetId(record.self);

    transfer->vertexCount = record.vertexCount;
    transfer->instanceCount = record.instanceCount;
    transfer->firstVertex = record.firstVertex;
    transfer->firstInstance = record.firstInstance;




}
DAWN_UNUSED_FUNC(RenderPassEncoderDrawSerialize);

DAWN_DECLARE_UNUSED DeserializeResult RenderPassEncoderDrawDeserialize(RenderPassEncoderDrawCmd* record, const volatile RenderPassEncoderDrawTransfer* transfer,
                                      const volatile char** buffer, size_t* size, DeserializeAllocator* allocator, const ObjectIdResolver& resolver) {
    DAWN_UNUSED(allocator);
    DAWN_UNUSED(buffer);
    DAWN_UNUSED(size);

    ASSERT(transfer->commandId == WireCmd::RenderPassEncoderDraw);

    record->selfId = transfer->self;

    DESERIALIZE_TRY(resolver.GetFromId(transfer->self, &record->self));
    record->vertexCount = transfer->vertexCount;
    record->instanceCount = transfer->instanceCount;
    record->firstVertex = transfer->firstVertex;
    record->firstInstance = transfer->firstInstance;





    return DeserializeResult::Success;
}
DAWN_UNUSED_FUNC(RenderPassEncoderDrawDeserialize);

        
struct RenderPassEncoderDrawIndexedTransfer : CmdHeader {
    static_assert(1 <= 1,
                  "Record must be at most one of is_cmd, extensible, and chained.");
    WireCmd commandId;

    ObjectId self;
    uint32_t indexCount;
    uint32_t instanceCount;
    uint32_t firstIndex;
    int32_t baseVertex;
    uint32_t firstInstance;


};

static_assert(offsetof(RenderPassEncoderDrawIndexedTransfer, commandSize) == 0, "");
static_assert(offsetof(RenderPassEncoderDrawIndexedTransfer, commandId) == sizeof(CmdHeader), "");


DAWN_DECLARE_UNUSED size_t RenderPassEncoderDrawIndexedGetExtraRequiredSize(const RenderPassEncoderDrawIndexedCmd& record) {
    DAWN_UNUSED(record);

    size_t result = 0;



    {
    }
    {
    }
    {
    }
    {
    }
    {
    }
    {
    }

    return result;
}
// GetExtraRequiredSize isn't used for structures that are value members of other structures
// because we assume they cannot contain pointers themselves.
DAWN_UNUSED_FUNC(RenderPassEncoderDrawIndexedGetExtraRequiredSize);

DAWN_DECLARE_UNUSED void RenderPassEncoderDrawIndexedSerialize(const RenderPassEncoderDrawIndexedCmd& record, RenderPassEncoderDrawIndexedTransfer* transfer,
                       char** buffer, const ObjectIdProvider& provider) {
    DAWN_UNUSED(buffer);

    transfer->commandId = WireCmd::RenderPassEncoderDrawIndexed;

    transfer->self = provider.GetId(record.self);

    transfer->indexCount = record.indexCount;
    transfer->instanceCount = record.instanceCount;
    transfer->firstIndex = record.firstIndex;
    transfer->baseVertex = record.baseVertex;
    transfer->firstInstance = record.firstInstance;




}
DAWN_UNUSED_FUNC(RenderPassEncoderDrawIndexedSerialize);

DAWN_DECLARE_UNUSED DeserializeResult RenderPassEncoderDrawIndexedDeserialize(RenderPassEncoderDrawIndexedCmd* record, const volatile RenderPassEncoderDrawIndexedTransfer* transfer,
                                      const volatile char** buffer, size_t* size, DeserializeAllocator* allocator, const ObjectIdResolver& resolver) {
    DAWN_UNUSED(allocator);
    DAWN_UNUSED(buffer);
    DAWN_UNUSED(size);

    ASSERT(transfer->commandId == WireCmd::RenderPassEncoderDrawIndexed);

    record->selfId = transfer->self;

    DESERIALIZE_TRY(resolver.GetFromId(transfer->self, &record->self));
    record->indexCount = transfer->indexCount;
    record->instanceCount = transfer->instanceCount;
    record->firstIndex = transfer->firstIndex;
    record->baseVertex = transfer->baseVertex;
    record->firstInstance = transfer->firstInstance;





    return DeserializeResult::Success;
}
DAWN_UNUSED_FUNC(RenderPassEncoderDrawIndexedDeserialize);

        
struct RenderPassEncoderDrawIndexedIndirectTransfer : CmdHeader {
    static_assert(1 <= 1,
                  "Record must be at most one of is_cmd, extensible, and chained.");
    WireCmd commandId;

    ObjectId self;
    ObjectId indirectBuffer;
    uint64_t indirectOffset;


};

static_assert(offsetof(RenderPassEncoderDrawIndexedIndirectTransfer, commandSize) == 0, "");
static_assert(offsetof(RenderPassEncoderDrawIndexedIndirectTransfer, commandId) == sizeof(CmdHeader), "");


DAWN_DECLARE_UNUSED size_t RenderPassEncoderDrawIndexedIndirectGetExtraRequiredSize(const RenderPassEncoderDrawIndexedIndirectCmd& record) {
    DAWN_UNUSED(record);

    size_t result = 0;



    {
    }
    {
    }
    {
    }

    return result;
}
// GetExtraRequiredSize isn't used for structures that are value members of other structures
// because we assume they cannot contain pointers themselves.
DAWN_UNUSED_FUNC(RenderPassEncoderDrawIndexedIndirectGetExtraRequiredSize);

DAWN_DECLARE_UNUSED void RenderPassEncoderDrawIndexedIndirectSerialize(const RenderPassEncoderDrawIndexedIndirectCmd& record, RenderPassEncoderDrawIndexedIndirectTransfer* transfer,
                       char** buffer, const ObjectIdProvider& provider) {
    DAWN_UNUSED(buffer);

    transfer->commandId = WireCmd::RenderPassEncoderDrawIndexedIndirect;

    transfer->self = provider.GetId(record.self);

    transfer->indirectBuffer = provider.GetId(record.indirectBuffer);

    transfer->indirectOffset = record.indirectOffset;




}
DAWN_UNUSED_FUNC(RenderPassEncoderDrawIndexedIndirectSerialize);

DAWN_DECLARE_UNUSED DeserializeResult RenderPassEncoderDrawIndexedIndirectDeserialize(RenderPassEncoderDrawIndexedIndirectCmd* record, const volatile RenderPassEncoderDrawIndexedIndirectTransfer* transfer,
                                      const volatile char** buffer, size_t* size, DeserializeAllocator* allocator, const ObjectIdResolver& resolver) {
    DAWN_UNUSED(allocator);
    DAWN_UNUSED(buffer);
    DAWN_UNUSED(size);

    ASSERT(transfer->commandId == WireCmd::RenderPassEncoderDrawIndexedIndirect);

    record->selfId = transfer->self;

    DESERIALIZE_TRY(resolver.GetFromId(transfer->self, &record->self));
    DESERIALIZE_TRY(resolver.GetFromId(transfer->indirectBuffer, &record->indirectBuffer));
    record->indirectOffset = transfer->indirectOffset;





    return DeserializeResult::Success;
}
DAWN_UNUSED_FUNC(RenderPassEncoderDrawIndexedIndirectDeserialize);

        
struct RenderPassEncoderDrawIndirectTransfer : CmdHeader {
    static_assert(1 <= 1,
                  "Record must be at most one of is_cmd, extensible, and chained.");
    WireCmd commandId;

    ObjectId self;
    ObjectId indirectBuffer;
    uint64_t indirectOffset;


};

static_assert(offsetof(RenderPassEncoderDrawIndirectTransfer, commandSize) == 0, "");
static_assert(offsetof(RenderPassEncoderDrawIndirectTransfer, commandId) == sizeof(CmdHeader), "");


DAWN_DECLARE_UNUSED size_t RenderPassEncoderDrawIndirectGetExtraRequiredSize(const RenderPassEncoderDrawIndirectCmd& record) {
    DAWN_UNUSED(record);

    size_t result = 0;



    {
    }
    {
    }
    {
    }

    return result;
}
// GetExtraRequiredSize isn't used for structures that are value members of other structures
// because we assume they cannot contain pointers themselves.
DAWN_UNUSED_FUNC(RenderPassEncoderDrawIndirectGetExtraRequiredSize);

DAWN_DECLARE_UNUSED void RenderPassEncoderDrawIndirectSerialize(const RenderPassEncoderDrawIndirectCmd& record, RenderPassEncoderDrawIndirectTransfer* transfer,
                       char** buffer, const ObjectIdProvider& provider) {
    DAWN_UNUSED(buffer);

    transfer->commandId = WireCmd::RenderPassEncoderDrawIndirect;

    transfer->self = provider.GetId(record.self);

    transfer->indirectBuffer = provider.GetId(record.indirectBuffer);

    transfer->indirectOffset = record.indirectOffset;




}
DAWN_UNUSED_FUNC(RenderPassEncoderDrawIndirectSerialize);

DAWN_DECLARE_UNUSED DeserializeResult RenderPassEncoderDrawIndirectDeserialize(RenderPassEncoderDrawIndirectCmd* record, const volatile RenderPassEncoderDrawIndirectTransfer* transfer,
                                      const volatile char** buffer, size_t* size, DeserializeAllocator* allocator, const ObjectIdResolver& resolver) {
    DAWN_UNUSED(allocator);
    DAWN_UNUSED(buffer);
    DAWN_UNUSED(size);

    ASSERT(transfer->commandId == WireCmd::RenderPassEncoderDrawIndirect);

    record->selfId = transfer->self;

    DESERIALIZE_TRY(resolver.GetFromId(transfer->self, &record->self));
    DESERIALIZE_TRY(resolver.GetFromId(transfer->indirectBuffer, &record->indirectBuffer));
    record->indirectOffset = transfer->indirectOffset;





    return DeserializeResult::Success;
}
DAWN_UNUSED_FUNC(RenderPassEncoderDrawIndirectDeserialize);

        
struct RenderPassEncoderEndPassTransfer : CmdHeader {
    static_assert(1 <= 1,
                  "Record must be at most one of is_cmd, extensible, and chained.");
    WireCmd commandId;

    ObjectId self;


};

static_assert(offsetof(RenderPassEncoderEndPassTransfer, commandSize) == 0, "");
static_assert(offsetof(RenderPassEncoderEndPassTransfer, commandId) == sizeof(CmdHeader), "");


DAWN_DECLARE_UNUSED size_t RenderPassEncoderEndPassGetExtraRequiredSize(const RenderPassEncoderEndPassCmd& record) {
    DAWN_UNUSED(record);

    size_t result = 0;



    {
    }

    return result;
}
// GetExtraRequiredSize isn't used for structures that are value members of other structures
// because we assume they cannot contain pointers themselves.
DAWN_UNUSED_FUNC(RenderPassEncoderEndPassGetExtraRequiredSize);

DAWN_DECLARE_UNUSED void RenderPassEncoderEndPassSerialize(const RenderPassEncoderEndPassCmd& record, RenderPassEncoderEndPassTransfer* transfer,
                       char** buffer, const ObjectIdProvider& provider) {
    DAWN_UNUSED(buffer);

    transfer->commandId = WireCmd::RenderPassEncoderEndPass;

    transfer->self = provider.GetId(record.self);





}
DAWN_UNUSED_FUNC(RenderPassEncoderEndPassSerialize);

DAWN_DECLARE_UNUSED DeserializeResult RenderPassEncoderEndPassDeserialize(RenderPassEncoderEndPassCmd* record, const volatile RenderPassEncoderEndPassTransfer* transfer,
                                      const volatile char** buffer, size_t* size, DeserializeAllocator* allocator, const ObjectIdResolver& resolver) {
    DAWN_UNUSED(allocator);
    DAWN_UNUSED(buffer);
    DAWN_UNUSED(size);

    ASSERT(transfer->commandId == WireCmd::RenderPassEncoderEndPass);

    record->selfId = transfer->self;

    DESERIALIZE_TRY(resolver.GetFromId(transfer->self, &record->self));





    return DeserializeResult::Success;
}
DAWN_UNUSED_FUNC(RenderPassEncoderEndPassDeserialize);

        
struct RenderPassEncoderExecuteBundlesTransfer : CmdHeader {
    static_assert(1 <= 1,
                  "Record must be at most one of is_cmd, extensible, and chained.");
    WireCmd commandId;

    ObjectId self;
    uint32_t bundlesCount;


};

static_assert(offsetof(RenderPassEncoderExecuteBundlesTransfer, commandSize) == 0, "");
static_assert(offsetof(RenderPassEncoderExecuteBundlesTransfer, commandId) == sizeof(CmdHeader), "");


DAWN_DECLARE_UNUSED size_t RenderPassEncoderExecuteBundlesGetExtraRequiredSize(const RenderPassEncoderExecuteBundlesCmd& record) {
    DAWN_UNUSED(record);

    size_t result = 0;



    {
    }
    {
    }
    {
        size_t memberLength = record.bundlesCount;
        result += memberLength * sizeof(ObjectId);
    }

    return result;
}
// GetExtraRequiredSize isn't used for structures that are value members of other structures
// because we assume they cannot contain pointers themselves.
DAWN_UNUSED_FUNC(RenderPassEncoderExecuteBundlesGetExtraRequiredSize);

DAWN_DECLARE_UNUSED void RenderPassEncoderExecuteBundlesSerialize(const RenderPassEncoderExecuteBundlesCmd& record, RenderPassEncoderExecuteBundlesTransfer* transfer,
                       char** buffer, const ObjectIdProvider& provider) {
    DAWN_UNUSED(buffer);

    transfer->commandId = WireCmd::RenderPassEncoderExecuteBundles;

    transfer->self = provider.GetId(record.self);

    transfer->bundlesCount = record.bundlesCount;





    {
        size_t memberLength = record.bundlesCount;
        auto memberBuffer = reinterpret_cast<ObjectId*>(*buffer);
        *buffer += memberLength * sizeof(ObjectId);

        for (size_t i = 0; i < memberLength; ++i) {
            memberBuffer[i] = provider.GetId(record.bundles[i]);

        }
    }
}
DAWN_UNUSED_FUNC(RenderPassEncoderExecuteBundlesSerialize);

DAWN_DECLARE_UNUSED DeserializeResult RenderPassEncoderExecuteBundlesDeserialize(RenderPassEncoderExecuteBundlesCmd* record, const volatile RenderPassEncoderExecuteBundlesTransfer* transfer,
                                      const volatile char** buffer, size_t* size, DeserializeAllocator* allocator, const ObjectIdResolver& resolver) {
    DAWN_UNUSED(allocator);
    DAWN_UNUSED(buffer);
    DAWN_UNUSED(size);

    ASSERT(transfer->commandId == WireCmd::RenderPassEncoderExecuteBundles);

    record->selfId = transfer->self;

    DESERIALIZE_TRY(resolver.GetFromId(transfer->self, &record->self));
    record->bundlesCount = transfer->bundlesCount;





    {
        size_t memberLength = record->bundlesCount;
        auto memberBuffer = reinterpret_cast<const volatile ObjectId*>(buffer);
        DESERIALIZE_TRY(GetPtrFromBuffer(buffer, size, memberLength, &memberBuffer));

        WGPURenderBundle* copiedMembers = nullptr;
        DESERIALIZE_TRY(GetSpace(allocator, memberLength, &copiedMembers));
        record->bundles = copiedMembers;

        for (size_t i = 0; i < memberLength; ++i) {
            DESERIALIZE_TRY(resolver.GetFromId(memberBuffer[i], &copiedMembers[i]));
        }
    }

    return DeserializeResult::Success;
}
DAWN_UNUSED_FUNC(RenderPassEncoderExecuteBundlesDeserialize);

        
struct RenderPassEncoderInsertDebugMarkerTransfer : CmdHeader {
    static_assert(1 <= 1,
                  "Record must be at most one of is_cmd, extensible, and chained.");
    WireCmd commandId;

    ObjectId self;

    size_t markerLabelStrlen;

};

static_assert(offsetof(RenderPassEncoderInsertDebugMarkerTransfer, commandSize) == 0, "");
static_assert(offsetof(RenderPassEncoderInsertDebugMarkerTransfer, commandId) == sizeof(CmdHeader), "");


DAWN_DECLARE_UNUSED size_t RenderPassEncoderInsertDebugMarkerGetExtraRequiredSize(const RenderPassEncoderInsertDebugMarkerCmd& record) {
    DAWN_UNUSED(record);

    size_t result = 0;



    {
    result += std::strlen(record.markerLabel);
    }

    {
    }

    return result;
}
// GetExtraRequiredSize isn't used for structures that are value members of other structures
// because we assume they cannot contain pointers themselves.
DAWN_UNUSED_FUNC(RenderPassEncoderInsertDebugMarkerGetExtraRequiredSize);

DAWN_DECLARE_UNUSED void RenderPassEncoderInsertDebugMarkerSerialize(const RenderPassEncoderInsertDebugMarkerCmd& record, RenderPassEncoderInsertDebugMarkerTransfer* transfer,
                       char** buffer, const ObjectIdProvider& provider) {
    DAWN_UNUSED(buffer);

    transfer->commandId = WireCmd::RenderPassEncoderInsertDebugMarker;

    transfer->self = provider.GetId(record.self);





    {
    transfer->markerLabelStrlen = std::strlen(record.markerLabel);

    memcpy(*buffer, record.markerLabel, transfer->markerLabelStrlen);
    *buffer += transfer->markerLabelStrlen;
    }

}
DAWN_UNUSED_FUNC(RenderPassEncoderInsertDebugMarkerSerialize);

DAWN_DECLARE_UNUSED DeserializeResult RenderPassEncoderInsertDebugMarkerDeserialize(RenderPassEncoderInsertDebugMarkerCmd* record, const volatile RenderPassEncoderInsertDebugMarkerTransfer* transfer,
                                      const volatile char** buffer, size_t* size, DeserializeAllocator* allocator, const ObjectIdResolver& resolver) {
    DAWN_UNUSED(allocator);
    DAWN_UNUSED(buffer);
    DAWN_UNUSED(size);

    ASSERT(transfer->commandId == WireCmd::RenderPassEncoderInsertDebugMarker);

    record->selfId = transfer->self;

    DESERIALIZE_TRY(resolver.GetFromId(transfer->self, &record->self));




    {
        size_t stringLength = transfer->markerLabelStrlen;
        const volatile char* stringInBuffer = nullptr;
        DESERIALIZE_TRY(GetPtrFromBuffer(buffer, size, stringLength, &stringInBuffer));

        char* copiedString = nullptr;
        DESERIALIZE_TRY(GetSpace(allocator, stringLength + 1, &copiedString));
        std::copy(stringInBuffer, stringInBuffer + stringLength, copiedString);
        copiedString[stringLength] = '\0';
        record->markerLabel = copiedString;
    }


    return DeserializeResult::Success;
}
DAWN_UNUSED_FUNC(RenderPassEncoderInsertDebugMarkerDeserialize);

        
struct RenderPassEncoderPopDebugGroupTransfer : CmdHeader {
    static_assert(1 <= 1,
                  "Record must be at most one of is_cmd, extensible, and chained.");
    WireCmd commandId;

    ObjectId self;


};

static_assert(offsetof(RenderPassEncoderPopDebugGroupTransfer, commandSize) == 0, "");
static_assert(offsetof(RenderPassEncoderPopDebugGroupTransfer, commandId) == sizeof(CmdHeader), "");


DAWN_DECLARE_UNUSED size_t RenderPassEncoderPopDebugGroupGetExtraRequiredSize(const RenderPassEncoderPopDebugGroupCmd& record) {
    DAWN_UNUSED(record);

    size_t result = 0;



    {
    }

    return result;
}
// GetExtraRequiredSize isn't used for structures that are value members of other structures
// because we assume they cannot contain pointers themselves.
DAWN_UNUSED_FUNC(RenderPassEncoderPopDebugGroupGetExtraRequiredSize);

DAWN_DECLARE_UNUSED void RenderPassEncoderPopDebugGroupSerialize(const RenderPassEncoderPopDebugGroupCmd& record, RenderPassEncoderPopDebugGroupTransfer* transfer,
                       char** buffer, const ObjectIdProvider& provider) {
    DAWN_UNUSED(buffer);

    transfer->commandId = WireCmd::RenderPassEncoderPopDebugGroup;

    transfer->self = provider.GetId(record.self);





}
DAWN_UNUSED_FUNC(RenderPassEncoderPopDebugGroupSerialize);

DAWN_DECLARE_UNUSED DeserializeResult RenderPassEncoderPopDebugGroupDeserialize(RenderPassEncoderPopDebugGroupCmd* record, const volatile RenderPassEncoderPopDebugGroupTransfer* transfer,
                                      const volatile char** buffer, size_t* size, DeserializeAllocator* allocator, const ObjectIdResolver& resolver) {
    DAWN_UNUSED(allocator);
    DAWN_UNUSED(buffer);
    DAWN_UNUSED(size);

    ASSERT(transfer->commandId == WireCmd::RenderPassEncoderPopDebugGroup);

    record->selfId = transfer->self;

    DESERIALIZE_TRY(resolver.GetFromId(transfer->self, &record->self));





    return DeserializeResult::Success;
}
DAWN_UNUSED_FUNC(RenderPassEncoderPopDebugGroupDeserialize);

        
struct RenderPassEncoderPushDebugGroupTransfer : CmdHeader {
    static_assert(1 <= 1,
                  "Record must be at most one of is_cmd, extensible, and chained.");
    WireCmd commandId;

    ObjectId self;

    size_t groupLabelStrlen;

};

static_assert(offsetof(RenderPassEncoderPushDebugGroupTransfer, commandSize) == 0, "");
static_assert(offsetof(RenderPassEncoderPushDebugGroupTransfer, commandId) == sizeof(CmdHeader), "");


DAWN_DECLARE_UNUSED size_t RenderPassEncoderPushDebugGroupGetExtraRequiredSize(const RenderPassEncoderPushDebugGroupCmd& record) {
    DAWN_UNUSED(record);

    size_t result = 0;



    {
    result += std::strlen(record.groupLabel);
    }

    {
    }

    return result;
}
// GetExtraRequiredSize isn't used for structures that are value members of other structures
// because we assume they cannot contain pointers themselves.
DAWN_UNUSED_FUNC(RenderPassEncoderPushDebugGroupGetExtraRequiredSize);

DAWN_DECLARE_UNUSED void RenderPassEncoderPushDebugGroupSerialize(const RenderPassEncoderPushDebugGroupCmd& record, RenderPassEncoderPushDebugGroupTransfer* transfer,
                       char** buffer, const ObjectIdProvider& provider) {
    DAWN_UNUSED(buffer);

    transfer->commandId = WireCmd::RenderPassEncoderPushDebugGroup;

    transfer->self = provider.GetId(record.self);





    {
    transfer->groupLabelStrlen = std::strlen(record.groupLabel);

    memcpy(*buffer, record.groupLabel, transfer->groupLabelStrlen);
    *buffer += transfer->groupLabelStrlen;
    }

}
DAWN_UNUSED_FUNC(RenderPassEncoderPushDebugGroupSerialize);

DAWN_DECLARE_UNUSED DeserializeResult RenderPassEncoderPushDebugGroupDeserialize(RenderPassEncoderPushDebugGroupCmd* record, const volatile RenderPassEncoderPushDebugGroupTransfer* transfer,
                                      const volatile char** buffer, size_t* size, DeserializeAllocator* allocator, const ObjectIdResolver& resolver) {
    DAWN_UNUSED(allocator);
    DAWN_UNUSED(buffer);
    DAWN_UNUSED(size);

    ASSERT(transfer->commandId == WireCmd::RenderPassEncoderPushDebugGroup);

    record->selfId = transfer->self;

    DESERIALIZE_TRY(resolver.GetFromId(transfer->self, &record->self));




    {
        size_t stringLength = transfer->groupLabelStrlen;
        const volatile char* stringInBuffer = nullptr;
        DESERIALIZE_TRY(GetPtrFromBuffer(buffer, size, stringLength, &stringInBuffer));

        char* copiedString = nullptr;
        DESERIALIZE_TRY(GetSpace(allocator, stringLength + 1, &copiedString));
        std::copy(stringInBuffer, stringInBuffer + stringLength, copiedString);
        copiedString[stringLength] = '\0';
        record->groupLabel = copiedString;
    }


    return DeserializeResult::Success;
}
DAWN_UNUSED_FUNC(RenderPassEncoderPushDebugGroupDeserialize);

        
struct RenderPassEncoderSetBindGroupTransfer : CmdHeader {
    static_assert(1 <= 1,
                  "Record must be at most one of is_cmd, extensible, and chained.");
    WireCmd commandId;

    ObjectId self;
    uint32_t groupIndex;
    ObjectId group;
    uint32_t dynamicOffsetCount;


    bool has_dynamicOffsets;
};

static_assert(offsetof(RenderPassEncoderSetBindGroupTransfer, commandSize) == 0, "");
static_assert(offsetof(RenderPassEncoderSetBindGroupTransfer, commandId) == sizeof(CmdHeader), "");


DAWN_DECLARE_UNUSED size_t RenderPassEncoderSetBindGroupGetExtraRequiredSize(const RenderPassEncoderSetBindGroupCmd& record) {
    DAWN_UNUSED(record);

    size_t result = 0;



    {
    }
    {
    }
    {
    }
    {
    }
    if (record.dynamicOffsets != nullptr)
    {
        size_t memberLength = record.dynamicOffsetCount;
        result += memberLength * sizeof(uint32_t);
    }

    return result;
}
// GetExtraRequiredSize isn't used for structures that are value members of other structures
// because we assume they cannot contain pointers themselves.
DAWN_UNUSED_FUNC(RenderPassEncoderSetBindGroupGetExtraRequiredSize);

DAWN_DECLARE_UNUSED void RenderPassEncoderSetBindGroupSerialize(const RenderPassEncoderSetBindGroupCmd& record, RenderPassEncoderSetBindGroupTransfer* transfer,
                       char** buffer, const ObjectIdProvider& provider) {
    DAWN_UNUSED(buffer);

    transfer->commandId = WireCmd::RenderPassEncoderSetBindGroup;

    transfer->self = provider.GetId(record.self);

    transfer->groupIndex = record.groupIndex;
    transfer->group = provider.GetId(record.group);

    transfer->dynamicOffsetCount = record.dynamicOffsetCount;





    bool has_dynamicOffsets = record.dynamicOffsets != nullptr;
    transfer->has_dynamicOffsets = has_dynamicOffsets;
    if (has_dynamicOffsets)
    {
        size_t memberLength = record.dynamicOffsetCount;
        auto memberBuffer = reinterpret_cast<uint32_t*>(*buffer);
        *buffer += memberLength * sizeof(uint32_t);

        for (size_t i = 0; i < memberLength; ++i) {
            memberBuffer[i] = record.dynamicOffsets[i];
        }
    }
}
DAWN_UNUSED_FUNC(RenderPassEncoderSetBindGroupSerialize);

DAWN_DECLARE_UNUSED DeserializeResult RenderPassEncoderSetBindGroupDeserialize(RenderPassEncoderSetBindGroupCmd* record, const volatile RenderPassEncoderSetBindGroupTransfer* transfer,
                                      const volatile char** buffer, size_t* size, DeserializeAllocator* allocator, const ObjectIdResolver& resolver) {
    DAWN_UNUSED(allocator);
    DAWN_UNUSED(buffer);
    DAWN_UNUSED(size);

    ASSERT(transfer->commandId == WireCmd::RenderPassEncoderSetBindGroup);

    record->selfId = transfer->self;

    DESERIALIZE_TRY(resolver.GetFromId(transfer->self, &record->self));
    record->groupIndex = transfer->groupIndex;
    DESERIALIZE_TRY(resolver.GetFromId(transfer->group, &record->group));
    record->dynamicOffsetCount = transfer->dynamicOffsetCount;





    bool has_dynamicOffsets = transfer->has_dynamicOffsets;
    record->dynamicOffsets = nullptr;
    if (has_dynamicOffsets)
    {
        size_t memberLength = record->dynamicOffsetCount;
        auto memberBuffer = reinterpret_cast<const volatile uint32_t*>(buffer);
        DESERIALIZE_TRY(GetPtrFromBuffer(buffer, size, memberLength, &memberBuffer));

        uint32_t* copiedMembers = nullptr;
        DESERIALIZE_TRY(GetSpace(allocator, memberLength, &copiedMembers));
        record->dynamicOffsets = copiedMembers;

        for (size_t i = 0; i < memberLength; ++i) {
            copiedMembers[i] = memberBuffer[i];
        }
    }

    return DeserializeResult::Success;
}
DAWN_UNUSED_FUNC(RenderPassEncoderSetBindGroupDeserialize);

        
struct RenderPassEncoderSetBlendColorTransfer : CmdHeader {
    static_assert(1 <= 1,
                  "Record must be at most one of is_cmd, extensible, and chained.");
    WireCmd commandId;

    ObjectId self;


};

static_assert(offsetof(RenderPassEncoderSetBlendColorTransfer, commandSize) == 0, "");
static_assert(offsetof(RenderPassEncoderSetBlendColorTransfer, commandId) == sizeof(CmdHeader), "");


DAWN_DECLARE_UNUSED size_t RenderPassEncoderSetBlendColorGetExtraRequiredSize(const RenderPassEncoderSetBlendColorCmd& record) {
    DAWN_UNUSED(record);

    size_t result = 0;



    {
    }
    {
        size_t memberLength = 1;
        result += memberLength * sizeof(WGPUColorTransfer);
        for (size_t i = 0; i < memberLength; ++i) {
            
            result += WGPUColorGetExtraRequiredSize(record.color[i]);
        }
    }

    return result;
}
// GetExtraRequiredSize isn't used for structures that are value members of other structures
// because we assume they cannot contain pointers themselves.
DAWN_UNUSED_FUNC(RenderPassEncoderSetBlendColorGetExtraRequiredSize);

DAWN_DECLARE_UNUSED void RenderPassEncoderSetBlendColorSerialize(const RenderPassEncoderSetBlendColorCmd& record, RenderPassEncoderSetBlendColorTransfer* transfer,
                       char** buffer, const ObjectIdProvider& provider) {
    DAWN_UNUSED(buffer);

    transfer->commandId = WireCmd::RenderPassEncoderSetBlendColor;

    transfer->self = provider.GetId(record.self);






    {
        size_t memberLength = 1;
        auto memberBuffer = reinterpret_cast<WGPUColorTransfer*>(*buffer);
        *buffer += memberLength * sizeof(WGPUColorTransfer);

        for (size_t i = 0; i < memberLength; ++i) {
            WGPUColorSerialize(record.color[i], &memberBuffer[i], buffer);

        }
    }
}
DAWN_UNUSED_FUNC(RenderPassEncoderSetBlendColorSerialize);

DAWN_DECLARE_UNUSED DeserializeResult RenderPassEncoderSetBlendColorDeserialize(RenderPassEncoderSetBlendColorCmd* record, const volatile RenderPassEncoderSetBlendColorTransfer* transfer,
                                      const volatile char** buffer, size_t* size, DeserializeAllocator* allocator, const ObjectIdResolver& resolver) {
    DAWN_UNUSED(allocator);
    DAWN_UNUSED(buffer);
    DAWN_UNUSED(size);

    ASSERT(transfer->commandId == WireCmd::RenderPassEncoderSetBlendColor);

    record->selfId = transfer->self;

    DESERIALIZE_TRY(resolver.GetFromId(transfer->self, &record->self));





    {
        size_t memberLength = 1;
        auto memberBuffer = reinterpret_cast<const volatile WGPUColorTransfer*>(buffer);
        DESERIALIZE_TRY(GetPtrFromBuffer(buffer, size, memberLength, &memberBuffer));

        WGPUColor* copiedMembers = nullptr;
        DESERIALIZE_TRY(GetSpace(allocator, memberLength, &copiedMembers));
        record->color = copiedMembers;

        for (size_t i = 0; i < memberLength; ++i) {
            DESERIALIZE_TRY(WGPUColorDeserialize(&copiedMembers[i], &memberBuffer[i], buffer, size, allocator));
        }
    }

    return DeserializeResult::Success;
}
DAWN_UNUSED_FUNC(RenderPassEncoderSetBlendColorDeserialize);

        
struct RenderPassEncoderSetIndexBufferTransfer : CmdHeader {
    static_assert(1 <= 1,
                  "Record must be at most one of is_cmd, extensible, and chained.");
    WireCmd commandId;

    ObjectId self;
    ObjectId buffer;
    uint64_t offset;
    uint64_t size;


};

static_assert(offsetof(RenderPassEncoderSetIndexBufferTransfer, commandSize) == 0, "");
static_assert(offsetof(RenderPassEncoderSetIndexBufferTransfer, commandId) == sizeof(CmdHeader), "");


DAWN_DECLARE_UNUSED size_t RenderPassEncoderSetIndexBufferGetExtraRequiredSize(const RenderPassEncoderSetIndexBufferCmd& record) {
    DAWN_UNUSED(record);

    size_t result = 0;



    {
    }
    {
    }
    {
    }
    {
    }

    return result;
}
// GetExtraRequiredSize isn't used for structures that are value members of other structures
// because we assume they cannot contain pointers themselves.
DAWN_UNUSED_FUNC(RenderPassEncoderSetIndexBufferGetExtraRequiredSize);

DAWN_DECLARE_UNUSED void RenderPassEncoderSetIndexBufferSerialize(const RenderPassEncoderSetIndexBufferCmd& record, RenderPassEncoderSetIndexBufferTransfer* transfer,
                       char** buffer, const ObjectIdProvider& provider) {
    DAWN_UNUSED(buffer);

    transfer->commandId = WireCmd::RenderPassEncoderSetIndexBuffer;

    transfer->self = provider.GetId(record.self);

    transfer->buffer = provider.GetId(record.buffer);

    transfer->offset = record.offset;
    transfer->size = record.size;




}
DAWN_UNUSED_FUNC(RenderPassEncoderSetIndexBufferSerialize);

DAWN_DECLARE_UNUSED DeserializeResult RenderPassEncoderSetIndexBufferDeserialize(RenderPassEncoderSetIndexBufferCmd* record, const volatile RenderPassEncoderSetIndexBufferTransfer* transfer,
                                      const volatile char** buffer, size_t* size, DeserializeAllocator* allocator, const ObjectIdResolver& resolver) {
    DAWN_UNUSED(allocator);
    DAWN_UNUSED(buffer);
    DAWN_UNUSED(size);

    ASSERT(transfer->commandId == WireCmd::RenderPassEncoderSetIndexBuffer);

    record->selfId = transfer->self;

    DESERIALIZE_TRY(resolver.GetFromId(transfer->self, &record->self));
    DESERIALIZE_TRY(resolver.GetFromId(transfer->buffer, &record->buffer));
    record->offset = transfer->offset;
    record->size = transfer->size;





    return DeserializeResult::Success;
}
DAWN_UNUSED_FUNC(RenderPassEncoderSetIndexBufferDeserialize);

        
struct RenderPassEncoderSetIndexBufferWithFormatTransfer : CmdHeader {
    static_assert(1 <= 1,
                  "Record must be at most one of is_cmd, extensible, and chained.");
    WireCmd commandId;

    ObjectId self;
    ObjectId buffer;
    WGPUIndexFormat format;
    uint64_t offset;
    uint64_t size;


};

static_assert(offsetof(RenderPassEncoderSetIndexBufferWithFormatTransfer, commandSize) == 0, "");
static_assert(offsetof(RenderPassEncoderSetIndexBufferWithFormatTransfer, commandId) == sizeof(CmdHeader), "");


DAWN_DECLARE_UNUSED size_t RenderPassEncoderSetIndexBufferWithFormatGetExtraRequiredSize(const RenderPassEncoderSetIndexBufferWithFormatCmd& record) {
    DAWN_UNUSED(record);

    size_t result = 0;



    {
    }
    {
    }
    {
    }
    {
    }
    {
    }

    return result;
}
// GetExtraRequiredSize isn't used for structures that are value members of other structures
// because we assume they cannot contain pointers themselves.
DAWN_UNUSED_FUNC(RenderPassEncoderSetIndexBufferWithFormatGetExtraRequiredSize);

DAWN_DECLARE_UNUSED void RenderPassEncoderSetIndexBufferWithFormatSerialize(const RenderPassEncoderSetIndexBufferWithFormatCmd& record, RenderPassEncoderSetIndexBufferWithFormatTransfer* transfer,
                       char** buffer, const ObjectIdProvider& provider) {
    DAWN_UNUSED(buffer);

    transfer->commandId = WireCmd::RenderPassEncoderSetIndexBufferWithFormat;

    transfer->self = provider.GetId(record.self);

    transfer->buffer = provider.GetId(record.buffer);

    transfer->format = record.format;
    transfer->offset = record.offset;
    transfer->size = record.size;




}
DAWN_UNUSED_FUNC(RenderPassEncoderSetIndexBufferWithFormatSerialize);

DAWN_DECLARE_UNUSED DeserializeResult RenderPassEncoderSetIndexBufferWithFormatDeserialize(RenderPassEncoderSetIndexBufferWithFormatCmd* record, const volatile RenderPassEncoderSetIndexBufferWithFormatTransfer* transfer,
                                      const volatile char** buffer, size_t* size, DeserializeAllocator* allocator, const ObjectIdResolver& resolver) {
    DAWN_UNUSED(allocator);
    DAWN_UNUSED(buffer);
    DAWN_UNUSED(size);

    ASSERT(transfer->commandId == WireCmd::RenderPassEncoderSetIndexBufferWithFormat);

    record->selfId = transfer->self;

    DESERIALIZE_TRY(resolver.GetFromId(transfer->self, &record->self));
    DESERIALIZE_TRY(resolver.GetFromId(transfer->buffer, &record->buffer));
    record->format = transfer->format;
    record->offset = transfer->offset;
    record->size = transfer->size;





    return DeserializeResult::Success;
}
DAWN_UNUSED_FUNC(RenderPassEncoderSetIndexBufferWithFormatDeserialize);

        
struct RenderPassEncoderSetPipelineTransfer : CmdHeader {
    static_assert(1 <= 1,
                  "Record must be at most one of is_cmd, extensible, and chained.");
    WireCmd commandId;

    ObjectId self;
    ObjectId pipeline;


};

static_assert(offsetof(RenderPassEncoderSetPipelineTransfer, commandSize) == 0, "");
static_assert(offsetof(RenderPassEncoderSetPipelineTransfer, commandId) == sizeof(CmdHeader), "");


DAWN_DECLARE_UNUSED size_t RenderPassEncoderSetPipelineGetExtraRequiredSize(const RenderPassEncoderSetPipelineCmd& record) {
    DAWN_UNUSED(record);

    size_t result = 0;



    {
    }
    {
    }

    return result;
}
// GetExtraRequiredSize isn't used for structures that are value members of other structures
// because we assume they cannot contain pointers themselves.
DAWN_UNUSED_FUNC(RenderPassEncoderSetPipelineGetExtraRequiredSize);

DAWN_DECLARE_UNUSED void RenderPassEncoderSetPipelineSerialize(const RenderPassEncoderSetPipelineCmd& record, RenderPassEncoderSetPipelineTransfer* transfer,
                       char** buffer, const ObjectIdProvider& provider) {
    DAWN_UNUSED(buffer);

    transfer->commandId = WireCmd::RenderPassEncoderSetPipeline;

    transfer->self = provider.GetId(record.self);

    transfer->pipeline = provider.GetId(record.pipeline);





}
DAWN_UNUSED_FUNC(RenderPassEncoderSetPipelineSerialize);

DAWN_DECLARE_UNUSED DeserializeResult RenderPassEncoderSetPipelineDeserialize(RenderPassEncoderSetPipelineCmd* record, const volatile RenderPassEncoderSetPipelineTransfer* transfer,
                                      const volatile char** buffer, size_t* size, DeserializeAllocator* allocator, const ObjectIdResolver& resolver) {
    DAWN_UNUSED(allocator);
    DAWN_UNUSED(buffer);
    DAWN_UNUSED(size);

    ASSERT(transfer->commandId == WireCmd::RenderPassEncoderSetPipeline);

    record->selfId = transfer->self;

    DESERIALIZE_TRY(resolver.GetFromId(transfer->self, &record->self));
    DESERIALIZE_TRY(resolver.GetFromId(transfer->pipeline, &record->pipeline));





    return DeserializeResult::Success;
}
DAWN_UNUSED_FUNC(RenderPassEncoderSetPipelineDeserialize);

        
struct RenderPassEncoderSetScissorRectTransfer : CmdHeader {
    static_assert(1 <= 1,
                  "Record must be at most one of is_cmd, extensible, and chained.");
    WireCmd commandId;

    ObjectId self;
    uint32_t x;
    uint32_t y;
    uint32_t width;
    uint32_t height;


};

static_assert(offsetof(RenderPassEncoderSetScissorRectTransfer, commandSize) == 0, "");
static_assert(offsetof(RenderPassEncoderSetScissorRectTransfer, commandId) == sizeof(CmdHeader), "");


DAWN_DECLARE_UNUSED size_t RenderPassEncoderSetScissorRectGetExtraRequiredSize(const RenderPassEncoderSetScissorRectCmd& record) {
    DAWN_UNUSED(record);

    size_t result = 0;



    {
    }
    {
    }
    {
    }
    {
    }
    {
    }

    return result;
}
// GetExtraRequiredSize isn't used for structures that are value members of other structures
// because we assume they cannot contain pointers themselves.
DAWN_UNUSED_FUNC(RenderPassEncoderSetScissorRectGetExtraRequiredSize);

DAWN_DECLARE_UNUSED void RenderPassEncoderSetScissorRectSerialize(const RenderPassEncoderSetScissorRectCmd& record, RenderPassEncoderSetScissorRectTransfer* transfer,
                       char** buffer, const ObjectIdProvider& provider) {
    DAWN_UNUSED(buffer);

    transfer->commandId = WireCmd::RenderPassEncoderSetScissorRect;

    transfer->self = provider.GetId(record.self);

    transfer->x = record.x;
    transfer->y = record.y;
    transfer->width = record.width;
    transfer->height = record.height;




}
DAWN_UNUSED_FUNC(RenderPassEncoderSetScissorRectSerialize);

DAWN_DECLARE_UNUSED DeserializeResult RenderPassEncoderSetScissorRectDeserialize(RenderPassEncoderSetScissorRectCmd* record, const volatile RenderPassEncoderSetScissorRectTransfer* transfer,
                                      const volatile char** buffer, size_t* size, DeserializeAllocator* allocator, const ObjectIdResolver& resolver) {
    DAWN_UNUSED(allocator);
    DAWN_UNUSED(buffer);
    DAWN_UNUSED(size);

    ASSERT(transfer->commandId == WireCmd::RenderPassEncoderSetScissorRect);

    record->selfId = transfer->self;

    DESERIALIZE_TRY(resolver.GetFromId(transfer->self, &record->self));
    record->x = transfer->x;
    record->y = transfer->y;
    record->width = transfer->width;
    record->height = transfer->height;





    return DeserializeResult::Success;
}
DAWN_UNUSED_FUNC(RenderPassEncoderSetScissorRectDeserialize);

        
struct RenderPassEncoderSetStencilReferenceTransfer : CmdHeader {
    static_assert(1 <= 1,
                  "Record must be at most one of is_cmd, extensible, and chained.");
    WireCmd commandId;

    ObjectId self;
    uint32_t reference;


};

static_assert(offsetof(RenderPassEncoderSetStencilReferenceTransfer, commandSize) == 0, "");
static_assert(offsetof(RenderPassEncoderSetStencilReferenceTransfer, commandId) == sizeof(CmdHeader), "");


DAWN_DECLARE_UNUSED size_t RenderPassEncoderSetStencilReferenceGetExtraRequiredSize(const RenderPassEncoderSetStencilReferenceCmd& record) {
    DAWN_UNUSED(record);

    size_t result = 0;



    {
    }
    {
    }

    return result;
}
// GetExtraRequiredSize isn't used for structures that are value members of other structures
// because we assume they cannot contain pointers themselves.
DAWN_UNUSED_FUNC(RenderPassEncoderSetStencilReferenceGetExtraRequiredSize);

DAWN_DECLARE_UNUSED void RenderPassEncoderSetStencilReferenceSerialize(const RenderPassEncoderSetStencilReferenceCmd& record, RenderPassEncoderSetStencilReferenceTransfer* transfer,
                       char** buffer, const ObjectIdProvider& provider) {
    DAWN_UNUSED(buffer);

    transfer->commandId = WireCmd::RenderPassEncoderSetStencilReference;

    transfer->self = provider.GetId(record.self);

    transfer->reference = record.reference;




}
DAWN_UNUSED_FUNC(RenderPassEncoderSetStencilReferenceSerialize);

DAWN_DECLARE_UNUSED DeserializeResult RenderPassEncoderSetStencilReferenceDeserialize(RenderPassEncoderSetStencilReferenceCmd* record, const volatile RenderPassEncoderSetStencilReferenceTransfer* transfer,
                                      const volatile char** buffer, size_t* size, DeserializeAllocator* allocator, const ObjectIdResolver& resolver) {
    DAWN_UNUSED(allocator);
    DAWN_UNUSED(buffer);
    DAWN_UNUSED(size);

    ASSERT(transfer->commandId == WireCmd::RenderPassEncoderSetStencilReference);

    record->selfId = transfer->self;

    DESERIALIZE_TRY(resolver.GetFromId(transfer->self, &record->self));
    record->reference = transfer->reference;





    return DeserializeResult::Success;
}
DAWN_UNUSED_FUNC(RenderPassEncoderSetStencilReferenceDeserialize);

        
struct RenderPassEncoderSetVertexBufferTransfer : CmdHeader {
    static_assert(1 <= 1,
                  "Record must be at most one of is_cmd, extensible, and chained.");
    WireCmd commandId;

    ObjectId self;
    uint32_t slot;
    ObjectId buffer;
    uint64_t offset;
    uint64_t size;


};

static_assert(offsetof(RenderPassEncoderSetVertexBufferTransfer, commandSize) == 0, "");
static_assert(offsetof(RenderPassEncoderSetVertexBufferTransfer, commandId) == sizeof(CmdHeader), "");


DAWN_DECLARE_UNUSED size_t RenderPassEncoderSetVertexBufferGetExtraRequiredSize(const RenderPassEncoderSetVertexBufferCmd& record) {
    DAWN_UNUSED(record);

    size_t result = 0;



    {
    }
    {
    }
    {
    }
    {
    }
    {
    }

    return result;
}
// GetExtraRequiredSize isn't used for structures that are value members of other structures
// because we assume they cannot contain pointers themselves.
DAWN_UNUSED_FUNC(RenderPassEncoderSetVertexBufferGetExtraRequiredSize);

DAWN_DECLARE_UNUSED void RenderPassEncoderSetVertexBufferSerialize(const RenderPassEncoderSetVertexBufferCmd& record, RenderPassEncoderSetVertexBufferTransfer* transfer,
                       char** buffer, const ObjectIdProvider& provider) {
    DAWN_UNUSED(buffer);

    transfer->commandId = WireCmd::RenderPassEncoderSetVertexBuffer;

    transfer->self = provider.GetId(record.self);

    transfer->slot = record.slot;
    transfer->buffer = provider.GetId(record.buffer);

    transfer->offset = record.offset;
    transfer->size = record.size;




}
DAWN_UNUSED_FUNC(RenderPassEncoderSetVertexBufferSerialize);

DAWN_DECLARE_UNUSED DeserializeResult RenderPassEncoderSetVertexBufferDeserialize(RenderPassEncoderSetVertexBufferCmd* record, const volatile RenderPassEncoderSetVertexBufferTransfer* transfer,
                                      const volatile char** buffer, size_t* size, DeserializeAllocator* allocator, const ObjectIdResolver& resolver) {
    DAWN_UNUSED(allocator);
    DAWN_UNUSED(buffer);
    DAWN_UNUSED(size);

    ASSERT(transfer->commandId == WireCmd::RenderPassEncoderSetVertexBuffer);

    record->selfId = transfer->self;

    DESERIALIZE_TRY(resolver.GetFromId(transfer->self, &record->self));
    record->slot = transfer->slot;
    DESERIALIZE_TRY(resolver.GetFromId(transfer->buffer, &record->buffer));
    record->offset = transfer->offset;
    record->size = transfer->size;





    return DeserializeResult::Success;
}
DAWN_UNUSED_FUNC(RenderPassEncoderSetVertexBufferDeserialize);

        
struct RenderPassEncoderSetViewportTransfer : CmdHeader {
    static_assert(1 <= 1,
                  "Record must be at most one of is_cmd, extensible, and chained.");
    WireCmd commandId;

    ObjectId self;
    float x;
    float y;
    float width;
    float height;
    float minDepth;
    float maxDepth;


};

static_assert(offsetof(RenderPassEncoderSetViewportTransfer, commandSize) == 0, "");
static_assert(offsetof(RenderPassEncoderSetViewportTransfer, commandId) == sizeof(CmdHeader), "");


DAWN_DECLARE_UNUSED size_t RenderPassEncoderSetViewportGetExtraRequiredSize(const RenderPassEncoderSetViewportCmd& record) {
    DAWN_UNUSED(record);

    size_t result = 0;



    {
    }
    {
    }
    {
    }
    {
    }
    {
    }
    {
    }
    {
    }

    return result;
}
// GetExtraRequiredSize isn't used for structures that are value members of other structures
// because we assume they cannot contain pointers themselves.
DAWN_UNUSED_FUNC(RenderPassEncoderSetViewportGetExtraRequiredSize);

DAWN_DECLARE_UNUSED void RenderPassEncoderSetViewportSerialize(const RenderPassEncoderSetViewportCmd& record, RenderPassEncoderSetViewportTransfer* transfer,
                       char** buffer, const ObjectIdProvider& provider) {
    DAWN_UNUSED(buffer);

    transfer->commandId = WireCmd::RenderPassEncoderSetViewport;

    transfer->self = provider.GetId(record.self);

    transfer->x = record.x;
    transfer->y = record.y;
    transfer->width = record.width;
    transfer->height = record.height;
    transfer->minDepth = record.minDepth;
    transfer->maxDepth = record.maxDepth;




}
DAWN_UNUSED_FUNC(RenderPassEncoderSetViewportSerialize);

DAWN_DECLARE_UNUSED DeserializeResult RenderPassEncoderSetViewportDeserialize(RenderPassEncoderSetViewportCmd* record, const volatile RenderPassEncoderSetViewportTransfer* transfer,
                                      const volatile char** buffer, size_t* size, DeserializeAllocator* allocator, const ObjectIdResolver& resolver) {
    DAWN_UNUSED(allocator);
    DAWN_UNUSED(buffer);
    DAWN_UNUSED(size);

    ASSERT(transfer->commandId == WireCmd::RenderPassEncoderSetViewport);

    record->selfId = transfer->self;

    DESERIALIZE_TRY(resolver.GetFromId(transfer->self, &record->self));
    record->x = transfer->x;
    record->y = transfer->y;
    record->width = transfer->width;
    record->height = transfer->height;
    record->minDepth = transfer->minDepth;
    record->maxDepth = transfer->maxDepth;





    return DeserializeResult::Success;
}
DAWN_UNUSED_FUNC(RenderPassEncoderSetViewportDeserialize);

        
struct RenderPassEncoderWriteTimestampTransfer : CmdHeader {
    static_assert(1 <= 1,
                  "Record must be at most one of is_cmd, extensible, and chained.");
    WireCmd commandId;

    ObjectId self;
    ObjectId querySet;
    uint32_t queryIndex;


};

static_assert(offsetof(RenderPassEncoderWriteTimestampTransfer, commandSize) == 0, "");
static_assert(offsetof(RenderPassEncoderWriteTimestampTransfer, commandId) == sizeof(CmdHeader), "");


DAWN_DECLARE_UNUSED size_t RenderPassEncoderWriteTimestampGetExtraRequiredSize(const RenderPassEncoderWriteTimestampCmd& record) {
    DAWN_UNUSED(record);

    size_t result = 0;



    {
    }
    {
    }
    {
    }

    return result;
}
// GetExtraRequiredSize isn't used for structures that are value members of other structures
// because we assume they cannot contain pointers themselves.
DAWN_UNUSED_FUNC(RenderPassEncoderWriteTimestampGetExtraRequiredSize);

DAWN_DECLARE_UNUSED void RenderPassEncoderWriteTimestampSerialize(const RenderPassEncoderWriteTimestampCmd& record, RenderPassEncoderWriteTimestampTransfer* transfer,
                       char** buffer, const ObjectIdProvider& provider) {
    DAWN_UNUSED(buffer);

    transfer->commandId = WireCmd::RenderPassEncoderWriteTimestamp;

    transfer->self = provider.GetId(record.self);

    transfer->querySet = provider.GetId(record.querySet);

    transfer->queryIndex = record.queryIndex;




}
DAWN_UNUSED_FUNC(RenderPassEncoderWriteTimestampSerialize);

DAWN_DECLARE_UNUSED DeserializeResult RenderPassEncoderWriteTimestampDeserialize(RenderPassEncoderWriteTimestampCmd* record, const volatile RenderPassEncoderWriteTimestampTransfer* transfer,
                                      const volatile char** buffer, size_t* size, DeserializeAllocator* allocator, const ObjectIdResolver& resolver) {
    DAWN_UNUSED(allocator);
    DAWN_UNUSED(buffer);
    DAWN_UNUSED(size);

    ASSERT(transfer->commandId == WireCmd::RenderPassEncoderWriteTimestamp);

    record->selfId = transfer->self;

    DESERIALIZE_TRY(resolver.GetFromId(transfer->self, &record->self));
    DESERIALIZE_TRY(resolver.GetFromId(transfer->querySet, &record->querySet));
    record->queryIndex = transfer->queryIndex;





    return DeserializeResult::Success;
}
DAWN_UNUSED_FUNC(RenderPassEncoderWriteTimestampDeserialize);

        
struct RenderPipelineGetBindGroupLayoutTransfer : CmdHeader {
    static_assert(1 <= 1,
                  "Record must be at most one of is_cmd, extensible, and chained.");
    WireCmd commandId;

    ObjectId self;
    uint32_t groupIndex;
    ObjectHandle result;


};

static_assert(offsetof(RenderPipelineGetBindGroupLayoutTransfer, commandSize) == 0, "");
static_assert(offsetof(RenderPipelineGetBindGroupLayoutTransfer, commandId) == sizeof(CmdHeader), "");


DAWN_DECLARE_UNUSED size_t RenderPipelineGetBindGroupLayoutGetExtraRequiredSize(const RenderPipelineGetBindGroupLayoutCmd& record) {
    DAWN_UNUSED(record);

    size_t result = 0;



    {
    }
    {
    }
    {
    }

    return result;
}
// GetExtraRequiredSize isn't used for structures that are value members of other structures
// because we assume they cannot contain pointers themselves.
DAWN_UNUSED_FUNC(RenderPipelineGetBindGroupLayoutGetExtraRequiredSize);

DAWN_DECLARE_UNUSED void RenderPipelineGetBindGroupLayoutSerialize(const RenderPipelineGetBindGroupLayoutCmd& record, RenderPipelineGetBindGroupLayoutTransfer* transfer,
                       char** buffer, const ObjectIdProvider& provider) {
    DAWN_UNUSED(buffer);

    transfer->commandId = WireCmd::RenderPipelineGetBindGroupLayout;

    transfer->self = provider.GetId(record.self);

    transfer->groupIndex = record.groupIndex;
    transfer->result = record.result;




}
DAWN_UNUSED_FUNC(RenderPipelineGetBindGroupLayoutSerialize);

DAWN_DECLARE_UNUSED DeserializeResult RenderPipelineGetBindGroupLayoutDeserialize(RenderPipelineGetBindGroupLayoutCmd* record, const volatile RenderPipelineGetBindGroupLayoutTransfer* transfer,
                                      const volatile char** buffer, size_t* size, DeserializeAllocator* allocator, const ObjectIdResolver& resolver) {
    DAWN_UNUSED(allocator);
    DAWN_UNUSED(buffer);
    DAWN_UNUSED(size);

    ASSERT(transfer->commandId == WireCmd::RenderPipelineGetBindGroupLayout);

    record->selfId = transfer->self;

    DESERIALIZE_TRY(resolver.GetFromId(transfer->self, &record->self));
    record->groupIndex = transfer->groupIndex;
    record->result = transfer->result;





    return DeserializeResult::Success;
}
DAWN_UNUSED_FUNC(RenderPipelineGetBindGroupLayoutDeserialize);

        
struct SwapChainConfigureTransfer : CmdHeader {
    static_assert(1 <= 1,
                  "Record must be at most one of is_cmd, extensible, and chained.");
    WireCmd commandId;

    ObjectId self;
    WGPUTextureFormat format;
    WGPUTextureUsageFlags allowedUsage;
    uint32_t width;
    uint32_t height;


};

static_assert(offsetof(SwapChainConfigureTransfer, commandSize) == 0, "");
static_assert(offsetof(SwapChainConfigureTransfer, commandId) == sizeof(CmdHeader), "");


DAWN_DECLARE_UNUSED size_t SwapChainConfigureGetExtraRequiredSize(const SwapChainConfigureCmd& record) {
    DAWN_UNUSED(record);

    size_t result = 0;



    {
    }
    {
    }
    {
    }
    {
    }
    {
    }

    return result;
}
// GetExtraRequiredSize isn't used for structures that are value members of other structures
// because we assume they cannot contain pointers themselves.
DAWN_UNUSED_FUNC(SwapChainConfigureGetExtraRequiredSize);

DAWN_DECLARE_UNUSED void SwapChainConfigureSerialize(const SwapChainConfigureCmd& record, SwapChainConfigureTransfer* transfer,
                       char** buffer, const ObjectIdProvider& provider) {
    DAWN_UNUSED(buffer);

    transfer->commandId = WireCmd::SwapChainConfigure;

    transfer->self = provider.GetId(record.self);

    transfer->format = record.format;
    transfer->allowedUsage = record.allowedUsage;
    transfer->width = record.width;
    transfer->height = record.height;




}
DAWN_UNUSED_FUNC(SwapChainConfigureSerialize);

DAWN_DECLARE_UNUSED DeserializeResult SwapChainConfigureDeserialize(SwapChainConfigureCmd* record, const volatile SwapChainConfigureTransfer* transfer,
                                      const volatile char** buffer, size_t* size, DeserializeAllocator* allocator, const ObjectIdResolver& resolver) {
    DAWN_UNUSED(allocator);
    DAWN_UNUSED(buffer);
    DAWN_UNUSED(size);

    ASSERT(transfer->commandId == WireCmd::SwapChainConfigure);

    record->selfId = transfer->self;

    DESERIALIZE_TRY(resolver.GetFromId(transfer->self, &record->self));
    record->format = transfer->format;
    record->allowedUsage = transfer->allowedUsage;
    record->width = transfer->width;
    record->height = transfer->height;





    return DeserializeResult::Success;
}
DAWN_UNUSED_FUNC(SwapChainConfigureDeserialize);

        
struct SwapChainGetCurrentTextureViewTransfer : CmdHeader {
    static_assert(1 <= 1,
                  "Record must be at most one of is_cmd, extensible, and chained.");
    WireCmd commandId;

    ObjectId self;
    ObjectHandle result;


};

static_assert(offsetof(SwapChainGetCurrentTextureViewTransfer, commandSize) == 0, "");
static_assert(offsetof(SwapChainGetCurrentTextureViewTransfer, commandId) == sizeof(CmdHeader), "");


DAWN_DECLARE_UNUSED size_t SwapChainGetCurrentTextureViewGetExtraRequiredSize(const SwapChainGetCurrentTextureViewCmd& record) {
    DAWN_UNUSED(record);

    size_t result = 0;



    {
    }
    {
    }

    return result;
}
// GetExtraRequiredSize isn't used for structures that are value members of other structures
// because we assume they cannot contain pointers themselves.
DAWN_UNUSED_FUNC(SwapChainGetCurrentTextureViewGetExtraRequiredSize);

DAWN_DECLARE_UNUSED void SwapChainGetCurrentTextureViewSerialize(const SwapChainGetCurrentTextureViewCmd& record, SwapChainGetCurrentTextureViewTransfer* transfer,
                       char** buffer, const ObjectIdProvider& provider) {
    DAWN_UNUSED(buffer);

    transfer->commandId = WireCmd::SwapChainGetCurrentTextureView;

    transfer->self = provider.GetId(record.self);

    transfer->result = record.result;




}
DAWN_UNUSED_FUNC(SwapChainGetCurrentTextureViewSerialize);

DAWN_DECLARE_UNUSED DeserializeResult SwapChainGetCurrentTextureViewDeserialize(SwapChainGetCurrentTextureViewCmd* record, const volatile SwapChainGetCurrentTextureViewTransfer* transfer,
                                      const volatile char** buffer, size_t* size, DeserializeAllocator* allocator, const ObjectIdResolver& resolver) {
    DAWN_UNUSED(allocator);
    DAWN_UNUSED(buffer);
    DAWN_UNUSED(size);

    ASSERT(transfer->commandId == WireCmd::SwapChainGetCurrentTextureView);

    record->selfId = transfer->self;

    DESERIALIZE_TRY(resolver.GetFromId(transfer->self, &record->self));
    record->result = transfer->result;





    return DeserializeResult::Success;
}
DAWN_UNUSED_FUNC(SwapChainGetCurrentTextureViewDeserialize);

        
struct SwapChainPresentTransfer : CmdHeader {
    static_assert(1 <= 1,
                  "Record must be at most one of is_cmd, extensible, and chained.");
    WireCmd commandId;

    ObjectId self;


};

static_assert(offsetof(SwapChainPresentTransfer, commandSize) == 0, "");
static_assert(offsetof(SwapChainPresentTransfer, commandId) == sizeof(CmdHeader), "");


DAWN_DECLARE_UNUSED size_t SwapChainPresentGetExtraRequiredSize(const SwapChainPresentCmd& record) {
    DAWN_UNUSED(record);

    size_t result = 0;



    {
    }

    return result;
}
// GetExtraRequiredSize isn't used for structures that are value members of other structures
// because we assume they cannot contain pointers themselves.
DAWN_UNUSED_FUNC(SwapChainPresentGetExtraRequiredSize);

DAWN_DECLARE_UNUSED void SwapChainPresentSerialize(const SwapChainPresentCmd& record, SwapChainPresentTransfer* transfer,
                       char** buffer, const ObjectIdProvider& provider) {
    DAWN_UNUSED(buffer);

    transfer->commandId = WireCmd::SwapChainPresent;

    transfer->self = provider.GetId(record.self);





}
DAWN_UNUSED_FUNC(SwapChainPresentSerialize);

DAWN_DECLARE_UNUSED DeserializeResult SwapChainPresentDeserialize(SwapChainPresentCmd* record, const volatile SwapChainPresentTransfer* transfer,
                                      const volatile char** buffer, size_t* size, DeserializeAllocator* allocator, const ObjectIdResolver& resolver) {
    DAWN_UNUSED(allocator);
    DAWN_UNUSED(buffer);
    DAWN_UNUSED(size);

    ASSERT(transfer->commandId == WireCmd::SwapChainPresent);

    record->selfId = transfer->self;

    DESERIALIZE_TRY(resolver.GetFromId(transfer->self, &record->self));





    return DeserializeResult::Success;
}
DAWN_UNUSED_FUNC(SwapChainPresentDeserialize);

        
struct TextureCreateViewTransfer : CmdHeader {
    static_assert(1 <= 1,
                  "Record must be at most one of is_cmd, extensible, and chained.");
    WireCmd commandId;

    ObjectId self;
    ObjectHandle result;


    bool has_descriptor;
};

static_assert(offsetof(TextureCreateViewTransfer, commandSize) == 0, "");
static_assert(offsetof(TextureCreateViewTransfer, commandId) == sizeof(CmdHeader), "");


DAWN_DECLARE_UNUSED size_t TextureCreateViewGetExtraRequiredSize(const TextureCreateViewCmd& record) {
    DAWN_UNUSED(record);

    size_t result = 0;



    {
    }
    if (record.descriptor != nullptr)
    {
        size_t memberLength = 1;
        result += memberLength * sizeof(WGPUTextureViewDescriptorTransfer);
        for (size_t i = 0; i < memberLength; ++i) {
            
            result += WGPUTextureViewDescriptorGetExtraRequiredSize(record.descriptor[i]);
        }
    }
    {
    }

    return result;
}
// GetExtraRequiredSize isn't used for structures that are value members of other structures
// because we assume they cannot contain pointers themselves.
DAWN_UNUSED_FUNC(TextureCreateViewGetExtraRequiredSize);

DAWN_DECLARE_UNUSED void TextureCreateViewSerialize(const TextureCreateViewCmd& record, TextureCreateViewTransfer* transfer,
                       char** buffer, const ObjectIdProvider& provider) {
    DAWN_UNUSED(buffer);

    transfer->commandId = WireCmd::TextureCreateView;

    transfer->self = provider.GetId(record.self);

    transfer->result = record.result;





    bool has_descriptor = record.descriptor != nullptr;
    transfer->has_descriptor = has_descriptor;
    if (has_descriptor)
    {
        size_t memberLength = 1;
        auto memberBuffer = reinterpret_cast<WGPUTextureViewDescriptorTransfer*>(*buffer);
        *buffer += memberLength * sizeof(WGPUTextureViewDescriptorTransfer);

        for (size_t i = 0; i < memberLength; ++i) {
            WGPUTextureViewDescriptorSerialize(record.descriptor[i], &memberBuffer[i], buffer, provider);

        }
    }
}
DAWN_UNUSED_FUNC(TextureCreateViewSerialize);

DAWN_DECLARE_UNUSED DeserializeResult TextureCreateViewDeserialize(TextureCreateViewCmd* record, const volatile TextureCreateViewTransfer* transfer,
                                      const volatile char** buffer, size_t* size, DeserializeAllocator* allocator, const ObjectIdResolver& resolver) {
    DAWN_UNUSED(allocator);
    DAWN_UNUSED(buffer);
    DAWN_UNUSED(size);

    ASSERT(transfer->commandId == WireCmd::TextureCreateView);

    record->selfId = transfer->self;

    DESERIALIZE_TRY(resolver.GetFromId(transfer->self, &record->self));
    record->result = transfer->result;





    bool has_descriptor = transfer->has_descriptor;
    record->descriptor = nullptr;
    if (has_descriptor)
    {
        size_t memberLength = 1;
        auto memberBuffer = reinterpret_cast<const volatile WGPUTextureViewDescriptorTransfer*>(buffer);
        DESERIALIZE_TRY(GetPtrFromBuffer(buffer, size, memberLength, &memberBuffer));

        WGPUTextureViewDescriptor* copiedMembers = nullptr;
        DESERIALIZE_TRY(GetSpace(allocator, memberLength, &copiedMembers));
        record->descriptor = copiedMembers;

        for (size_t i = 0; i < memberLength; ++i) {
            DESERIALIZE_TRY(WGPUTextureViewDescriptorDeserialize(&copiedMembers[i], &memberBuffer[i], buffer, size, allocator, resolver));
        }
    }

    return DeserializeResult::Success;
}
DAWN_UNUSED_FUNC(TextureCreateViewDeserialize);

        
struct TextureDestroyTransfer : CmdHeader {
    static_assert(1 <= 1,
                  "Record must be at most one of is_cmd, extensible, and chained.");
    WireCmd commandId;

    ObjectId self;


};

static_assert(offsetof(TextureDestroyTransfer, commandSize) == 0, "");
static_assert(offsetof(TextureDestroyTransfer, commandId) == sizeof(CmdHeader), "");


DAWN_DECLARE_UNUSED size_t TextureDestroyGetExtraRequiredSize(const TextureDestroyCmd& record) {
    DAWN_UNUSED(record);

    size_t result = 0;



    {
    }

    return result;
}
// GetExtraRequiredSize isn't used for structures that are value members of other structures
// because we assume they cannot contain pointers themselves.
DAWN_UNUSED_FUNC(TextureDestroyGetExtraRequiredSize);

DAWN_DECLARE_UNUSED void TextureDestroySerialize(const TextureDestroyCmd& record, TextureDestroyTransfer* transfer,
                       char** buffer, const ObjectIdProvider& provider) {
    DAWN_UNUSED(buffer);

    transfer->commandId = WireCmd::TextureDestroy;

    transfer->self = provider.GetId(record.self);





}
DAWN_UNUSED_FUNC(TextureDestroySerialize);

DAWN_DECLARE_UNUSED DeserializeResult TextureDestroyDeserialize(TextureDestroyCmd* record, const volatile TextureDestroyTransfer* transfer,
                                      const volatile char** buffer, size_t* size, DeserializeAllocator* allocator, const ObjectIdResolver& resolver) {
    DAWN_UNUSED(allocator);
    DAWN_UNUSED(buffer);
    DAWN_UNUSED(size);

    ASSERT(transfer->commandId == WireCmd::TextureDestroy);

    record->selfId = transfer->self;

    DESERIALIZE_TRY(resolver.GetFromId(transfer->self, &record->self));





    return DeserializeResult::Success;
}
DAWN_UNUSED_FUNC(TextureDestroyDeserialize);


        
struct ReturnBufferMapAsyncCallbackTransfer : CmdHeader {
    static_assert(1 <= 1,
                  "Record must be at most one of is_cmd, extensible, and chained.");
    ReturnWireCmd commandId;

    ObjectHandle buffer;
    uint32_t requestSerial;
    uint32_t status;
    uint64_t readInitialDataInfoLength;


};

static_assert(offsetof(ReturnBufferMapAsyncCallbackTransfer, commandSize) == 0, "");
static_assert(offsetof(ReturnBufferMapAsyncCallbackTransfer, commandId) == sizeof(CmdHeader), "");


DAWN_DECLARE_UNUSED size_t ReturnBufferMapAsyncCallbackGetExtraRequiredSize(const ReturnBufferMapAsyncCallbackCmd& record) {
    DAWN_UNUSED(record);

    size_t result = 0;



    {
    }
    {
    }
    {
    }
    {
    }

    return result;
}
// GetExtraRequiredSize isn't used for structures that are value members of other structures
// because we assume they cannot contain pointers themselves.
DAWN_UNUSED_FUNC(ReturnBufferMapAsyncCallbackGetExtraRequiredSize);

DAWN_DECLARE_UNUSED void ReturnBufferMapAsyncCallbackSerialize(const ReturnBufferMapAsyncCallbackCmd& record, ReturnBufferMapAsyncCallbackTransfer* transfer,
                       char** buffer) {
    DAWN_UNUSED(buffer);

    transfer->commandId = ReturnWireCmd::BufferMapAsyncCallback;

    transfer->buffer = record.buffer;
    transfer->requestSerial = record.requestSerial;
    transfer->status = record.status;
    transfer->readInitialDataInfoLength = record.readInitialDataInfoLength;




}
DAWN_UNUSED_FUNC(ReturnBufferMapAsyncCallbackSerialize);

DAWN_DECLARE_UNUSED DeserializeResult ReturnBufferMapAsyncCallbackDeserialize(ReturnBufferMapAsyncCallbackCmd* record, const volatile ReturnBufferMapAsyncCallbackTransfer* transfer,
                                      const volatile char** buffer, size_t* size, DeserializeAllocator* allocator) {
    DAWN_UNUSED(allocator);
    DAWN_UNUSED(buffer);
    DAWN_UNUSED(size);

    ASSERT(transfer->commandId == ReturnWireCmd::BufferMapAsyncCallback);


    record->buffer = transfer->buffer;
    record->requestSerial = transfer->requestSerial;
    record->status = transfer->status;
    record->readInitialDataInfoLength = transfer->readInitialDataInfoLength;





    {
        size_t memberLength = record->readInitialDataInfoLength;
        auto memberBuffer = reinterpret_cast<const volatile uint8_t*>(buffer);
        DESERIALIZE_TRY(GetPtrFromBuffer(buffer, size, memberLength, &memberBuffer));

        uint8_t* copiedMembers = nullptr;
        DESERIALIZE_TRY(GetSpace(allocator, memberLength, &copiedMembers));
        record->readInitialDataInfo = copiedMembers;

        for (size_t i = 0; i < memberLength; ++i) {
            copiedMembers[i] = memberBuffer[i];
        }
    }

    return DeserializeResult::Success;
}
DAWN_UNUSED_FUNC(ReturnBufferMapAsyncCallbackDeserialize);

        
struct ReturnDeviceCreateReadyComputePipelineCallbackTransfer : CmdHeader {
    static_assert(1 <= 1,
                  "Record must be at most one of is_cmd, extensible, and chained.");
    ReturnWireCmd commandId;

    uint64_t requestSerial;
    WGPUCreateReadyPipelineStatus status;

    size_t messageStrlen;

};

static_assert(offsetof(ReturnDeviceCreateReadyComputePipelineCallbackTransfer, commandSize) == 0, "");
static_assert(offsetof(ReturnDeviceCreateReadyComputePipelineCallbackTransfer, commandId) == sizeof(CmdHeader), "");


DAWN_DECLARE_UNUSED size_t ReturnDeviceCreateReadyComputePipelineCallbackGetExtraRequiredSize(const ReturnDeviceCreateReadyComputePipelineCallbackCmd& record) {
    DAWN_UNUSED(record);

    size_t result = 0;



    {
    result += std::strlen(record.message);
    }

    {
    }
    {
    }

    return result;
}
// GetExtraRequiredSize isn't used for structures that are value members of other structures
// because we assume they cannot contain pointers themselves.
DAWN_UNUSED_FUNC(ReturnDeviceCreateReadyComputePipelineCallbackGetExtraRequiredSize);

DAWN_DECLARE_UNUSED void ReturnDeviceCreateReadyComputePipelineCallbackSerialize(const ReturnDeviceCreateReadyComputePipelineCallbackCmd& record, ReturnDeviceCreateReadyComputePipelineCallbackTransfer* transfer,
                       char** buffer) {
    DAWN_UNUSED(buffer);

    transfer->commandId = ReturnWireCmd::DeviceCreateReadyComputePipelineCallback;

    transfer->requestSerial = record.requestSerial;
    transfer->status = record.status;




    {
    transfer->messageStrlen = std::strlen(record.message);

    memcpy(*buffer, record.message, transfer->messageStrlen);
    *buffer += transfer->messageStrlen;
    }

}
DAWN_UNUSED_FUNC(ReturnDeviceCreateReadyComputePipelineCallbackSerialize);

DAWN_DECLARE_UNUSED DeserializeResult ReturnDeviceCreateReadyComputePipelineCallbackDeserialize(ReturnDeviceCreateReadyComputePipelineCallbackCmd* record, const volatile ReturnDeviceCreateReadyComputePipelineCallbackTransfer* transfer,
                                      const volatile char** buffer, size_t* size, DeserializeAllocator* allocator) {
    DAWN_UNUSED(allocator);
    DAWN_UNUSED(buffer);
    DAWN_UNUSED(size);

    ASSERT(transfer->commandId == ReturnWireCmd::DeviceCreateReadyComputePipelineCallback);


    record->requestSerial = transfer->requestSerial;
    record->status = transfer->status;




    {
        size_t stringLength = transfer->messageStrlen;
        const volatile char* stringInBuffer = nullptr;
        DESERIALIZE_TRY(GetPtrFromBuffer(buffer, size, stringLength, &stringInBuffer));

        char* copiedString = nullptr;
        DESERIALIZE_TRY(GetSpace(allocator, stringLength + 1, &copiedString));
        std::copy(stringInBuffer, stringInBuffer + stringLength, copiedString);
        copiedString[stringLength] = '\0';
        record->message = copiedString;
    }


    return DeserializeResult::Success;
}
DAWN_UNUSED_FUNC(ReturnDeviceCreateReadyComputePipelineCallbackDeserialize);

        
struct ReturnDeviceCreateReadyRenderPipelineCallbackTransfer : CmdHeader {
    static_assert(1 <= 1,
                  "Record must be at most one of is_cmd, extensible, and chained.");
    ReturnWireCmd commandId;

    uint64_t requestSerial;
    WGPUCreateReadyPipelineStatus status;

    size_t messageStrlen;

};

static_assert(offsetof(ReturnDeviceCreateReadyRenderPipelineCallbackTransfer, commandSize) == 0, "");
static_assert(offsetof(ReturnDeviceCreateReadyRenderPipelineCallbackTransfer, commandId) == sizeof(CmdHeader), "");


DAWN_DECLARE_UNUSED size_t ReturnDeviceCreateReadyRenderPipelineCallbackGetExtraRequiredSize(const ReturnDeviceCreateReadyRenderPipelineCallbackCmd& record) {
    DAWN_UNUSED(record);

    size_t result = 0;



    {
    result += std::strlen(record.message);
    }

    {
    }
    {
    }

    return result;
}
// GetExtraRequiredSize isn't used for structures that are value members of other structures
// because we assume they cannot contain pointers themselves.
DAWN_UNUSED_FUNC(ReturnDeviceCreateReadyRenderPipelineCallbackGetExtraRequiredSize);

DAWN_DECLARE_UNUSED void ReturnDeviceCreateReadyRenderPipelineCallbackSerialize(const ReturnDeviceCreateReadyRenderPipelineCallbackCmd& record, ReturnDeviceCreateReadyRenderPipelineCallbackTransfer* transfer,
                       char** buffer) {
    DAWN_UNUSED(buffer);

    transfer->commandId = ReturnWireCmd::DeviceCreateReadyRenderPipelineCallback;

    transfer->requestSerial = record.requestSerial;
    transfer->status = record.status;




    {
    transfer->messageStrlen = std::strlen(record.message);

    memcpy(*buffer, record.message, transfer->messageStrlen);
    *buffer += transfer->messageStrlen;
    }

}
DAWN_UNUSED_FUNC(ReturnDeviceCreateReadyRenderPipelineCallbackSerialize);

DAWN_DECLARE_UNUSED DeserializeResult ReturnDeviceCreateReadyRenderPipelineCallbackDeserialize(ReturnDeviceCreateReadyRenderPipelineCallbackCmd* record, const volatile ReturnDeviceCreateReadyRenderPipelineCallbackTransfer* transfer,
                                      const volatile char** buffer, size_t* size, DeserializeAllocator* allocator) {
    DAWN_UNUSED(allocator);
    DAWN_UNUSED(buffer);
    DAWN_UNUSED(size);

    ASSERT(transfer->commandId == ReturnWireCmd::DeviceCreateReadyRenderPipelineCallback);


    record->requestSerial = transfer->requestSerial;
    record->status = transfer->status;




    {
        size_t stringLength = transfer->messageStrlen;
        const volatile char* stringInBuffer = nullptr;
        DESERIALIZE_TRY(GetPtrFromBuffer(buffer, size, stringLength, &stringInBuffer));

        char* copiedString = nullptr;
        DESERIALIZE_TRY(GetSpace(allocator, stringLength + 1, &copiedString));
        std::copy(stringInBuffer, stringInBuffer + stringLength, copiedString);
        copiedString[stringLength] = '\0';
        record->message = copiedString;
    }


    return DeserializeResult::Success;
}
DAWN_UNUSED_FUNC(ReturnDeviceCreateReadyRenderPipelineCallbackDeserialize);

        
struct ReturnDeviceLostCallbackTransfer : CmdHeader {
    static_assert(1 <= 1,
                  "Record must be at most one of is_cmd, extensible, and chained.");
    ReturnWireCmd commandId;


    size_t messageStrlen;

};

static_assert(offsetof(ReturnDeviceLostCallbackTransfer, commandSize) == 0, "");
static_assert(offsetof(ReturnDeviceLostCallbackTransfer, commandId) == sizeof(CmdHeader), "");


DAWN_DECLARE_UNUSED size_t ReturnDeviceLostCallbackGetExtraRequiredSize(const ReturnDeviceLostCallbackCmd& record) {
    DAWN_UNUSED(record);

    size_t result = 0;



    {
    result += std::strlen(record.message);
    }


    return result;
}
// GetExtraRequiredSize isn't used for structures that are value members of other structures
// because we assume they cannot contain pointers themselves.
DAWN_UNUSED_FUNC(ReturnDeviceLostCallbackGetExtraRequiredSize);

DAWN_DECLARE_UNUSED void ReturnDeviceLostCallbackSerialize(const ReturnDeviceLostCallbackCmd& record, ReturnDeviceLostCallbackTransfer* transfer,
                       char** buffer) {
    DAWN_UNUSED(buffer);

    transfer->commandId = ReturnWireCmd::DeviceLostCallback;





    {
    transfer->messageStrlen = std::strlen(record.message);

    memcpy(*buffer, record.message, transfer->messageStrlen);
    *buffer += transfer->messageStrlen;
    }

}
DAWN_UNUSED_FUNC(ReturnDeviceLostCallbackSerialize);

DAWN_DECLARE_UNUSED DeserializeResult ReturnDeviceLostCallbackDeserialize(ReturnDeviceLostCallbackCmd* record, const volatile ReturnDeviceLostCallbackTransfer* transfer,
                                      const volatile char** buffer, size_t* size, DeserializeAllocator* allocator) {
    DAWN_UNUSED(allocator);
    DAWN_UNUSED(buffer);
    DAWN_UNUSED(size);

    ASSERT(transfer->commandId == ReturnWireCmd::DeviceLostCallback);






    {
        size_t stringLength = transfer->messageStrlen;
        const volatile char* stringInBuffer = nullptr;
        DESERIALIZE_TRY(GetPtrFromBuffer(buffer, size, stringLength, &stringInBuffer));

        char* copiedString = nullptr;
        DESERIALIZE_TRY(GetSpace(allocator, stringLength + 1, &copiedString));
        std::copy(stringInBuffer, stringInBuffer + stringLength, copiedString);
        copiedString[stringLength] = '\0';
        record->message = copiedString;
    }


    return DeserializeResult::Success;
}
DAWN_UNUSED_FUNC(ReturnDeviceLostCallbackDeserialize);

        
struct ReturnDevicePopErrorScopeCallbackTransfer : CmdHeader {
    static_assert(1 <= 1,
                  "Record must be at most one of is_cmd, extensible, and chained.");
    ReturnWireCmd commandId;

    uint64_t requestSerial;
    WGPUErrorType type;

    size_t messageStrlen;

};

static_assert(offsetof(ReturnDevicePopErrorScopeCallbackTransfer, commandSize) == 0, "");
static_assert(offsetof(ReturnDevicePopErrorScopeCallbackTransfer, commandId) == sizeof(CmdHeader), "");


DAWN_DECLARE_UNUSED size_t ReturnDevicePopErrorScopeCallbackGetExtraRequiredSize(const ReturnDevicePopErrorScopeCallbackCmd& record) {
    DAWN_UNUSED(record);

    size_t result = 0;



    {
    result += std::strlen(record.message);
    }

    {
    }
    {
    }

    return result;
}
// GetExtraRequiredSize isn't used for structures that are value members of other structures
// because we assume they cannot contain pointers themselves.
DAWN_UNUSED_FUNC(ReturnDevicePopErrorScopeCallbackGetExtraRequiredSize);

DAWN_DECLARE_UNUSED void ReturnDevicePopErrorScopeCallbackSerialize(const ReturnDevicePopErrorScopeCallbackCmd& record, ReturnDevicePopErrorScopeCallbackTransfer* transfer,
                       char** buffer) {
    DAWN_UNUSED(buffer);

    transfer->commandId = ReturnWireCmd::DevicePopErrorScopeCallback;

    transfer->requestSerial = record.requestSerial;
    transfer->type = record.type;




    {
    transfer->messageStrlen = std::strlen(record.message);

    memcpy(*buffer, record.message, transfer->messageStrlen);
    *buffer += transfer->messageStrlen;
    }

}
DAWN_UNUSED_FUNC(ReturnDevicePopErrorScopeCallbackSerialize);

DAWN_DECLARE_UNUSED DeserializeResult ReturnDevicePopErrorScopeCallbackDeserialize(ReturnDevicePopErrorScopeCallbackCmd* record, const volatile ReturnDevicePopErrorScopeCallbackTransfer* transfer,
                                      const volatile char** buffer, size_t* size, DeserializeAllocator* allocator) {
    DAWN_UNUSED(allocator);
    DAWN_UNUSED(buffer);
    DAWN_UNUSED(size);

    ASSERT(transfer->commandId == ReturnWireCmd::DevicePopErrorScopeCallback);


    record->requestSerial = transfer->requestSerial;
    record->type = transfer->type;




    {
        size_t stringLength = transfer->messageStrlen;
        const volatile char* stringInBuffer = nullptr;
        DESERIALIZE_TRY(GetPtrFromBuffer(buffer, size, stringLength, &stringInBuffer));

        char* copiedString = nullptr;
        DESERIALIZE_TRY(GetSpace(allocator, stringLength + 1, &copiedString));
        std::copy(stringInBuffer, stringInBuffer + stringLength, copiedString);
        copiedString[stringLength] = '\0';
        record->message = copiedString;
    }


    return DeserializeResult::Success;
}
DAWN_UNUSED_FUNC(ReturnDevicePopErrorScopeCallbackDeserialize);

        
struct ReturnDeviceUncapturedErrorCallbackTransfer : CmdHeader {
    static_assert(1 <= 1,
                  "Record must be at most one of is_cmd, extensible, and chained.");
    ReturnWireCmd commandId;

    WGPUErrorType type;

    size_t messageStrlen;

};

static_assert(offsetof(ReturnDeviceUncapturedErrorCallbackTransfer, commandSize) == 0, "");
static_assert(offsetof(ReturnDeviceUncapturedErrorCallbackTransfer, commandId) == sizeof(CmdHeader), "");


DAWN_DECLARE_UNUSED size_t ReturnDeviceUncapturedErrorCallbackGetExtraRequiredSize(const ReturnDeviceUncapturedErrorCallbackCmd& record) {
    DAWN_UNUSED(record);

    size_t result = 0;



    {
    result += std::strlen(record.message);
    }

    {
    }

    return result;
}
// GetExtraRequiredSize isn't used for structures that are value members of other structures
// because we assume they cannot contain pointers themselves.
DAWN_UNUSED_FUNC(ReturnDeviceUncapturedErrorCallbackGetExtraRequiredSize);

DAWN_DECLARE_UNUSED void ReturnDeviceUncapturedErrorCallbackSerialize(const ReturnDeviceUncapturedErrorCallbackCmd& record, ReturnDeviceUncapturedErrorCallbackTransfer* transfer,
                       char** buffer) {
    DAWN_UNUSED(buffer);

    transfer->commandId = ReturnWireCmd::DeviceUncapturedErrorCallback;

    transfer->type = record.type;




    {
    transfer->messageStrlen = std::strlen(record.message);

    memcpy(*buffer, record.message, transfer->messageStrlen);
    *buffer += transfer->messageStrlen;
    }

}
DAWN_UNUSED_FUNC(ReturnDeviceUncapturedErrorCallbackSerialize);

DAWN_DECLARE_UNUSED DeserializeResult ReturnDeviceUncapturedErrorCallbackDeserialize(ReturnDeviceUncapturedErrorCallbackCmd* record, const volatile ReturnDeviceUncapturedErrorCallbackTransfer* transfer,
                                      const volatile char** buffer, size_t* size, DeserializeAllocator* allocator) {
    DAWN_UNUSED(allocator);
    DAWN_UNUSED(buffer);
    DAWN_UNUSED(size);

    ASSERT(transfer->commandId == ReturnWireCmd::DeviceUncapturedErrorCallback);


    record->type = transfer->type;




    {
        size_t stringLength = transfer->messageStrlen;
        const volatile char* stringInBuffer = nullptr;
        DESERIALIZE_TRY(GetPtrFromBuffer(buffer, size, stringLength, &stringInBuffer));

        char* copiedString = nullptr;
        DESERIALIZE_TRY(GetSpace(allocator, stringLength + 1, &copiedString));
        std::copy(stringInBuffer, stringInBuffer + stringLength, copiedString);
        copiedString[stringLength] = '\0';
        record->message = copiedString;
    }


    return DeserializeResult::Success;
}
DAWN_UNUSED_FUNC(ReturnDeviceUncapturedErrorCallbackDeserialize);

        
struct ReturnFenceOnCompletionCallbackTransfer : CmdHeader {
    static_assert(1 <= 1,
                  "Record must be at most one of is_cmd, extensible, and chained.");
    ReturnWireCmd commandId;

    ObjectHandle fence;
    uint64_t requestSerial;
    WGPUFenceCompletionStatus status;


};

static_assert(offsetof(ReturnFenceOnCompletionCallbackTransfer, commandSize) == 0, "");
static_assert(offsetof(ReturnFenceOnCompletionCallbackTransfer, commandId) == sizeof(CmdHeader), "");


DAWN_DECLARE_UNUSED size_t ReturnFenceOnCompletionCallbackGetExtraRequiredSize(const ReturnFenceOnCompletionCallbackCmd& record) {
    DAWN_UNUSED(record);

    size_t result = 0;



    {
    }
    {
    }
    {
    }

    return result;
}
// GetExtraRequiredSize isn't used for structures that are value members of other structures
// because we assume they cannot contain pointers themselves.
DAWN_UNUSED_FUNC(ReturnFenceOnCompletionCallbackGetExtraRequiredSize);

DAWN_DECLARE_UNUSED void ReturnFenceOnCompletionCallbackSerialize(const ReturnFenceOnCompletionCallbackCmd& record, ReturnFenceOnCompletionCallbackTransfer* transfer,
                       char** buffer) {
    DAWN_UNUSED(buffer);

    transfer->commandId = ReturnWireCmd::FenceOnCompletionCallback;

    transfer->fence = record.fence;
    transfer->requestSerial = record.requestSerial;
    transfer->status = record.status;




}
DAWN_UNUSED_FUNC(ReturnFenceOnCompletionCallbackSerialize);

DAWN_DECLARE_UNUSED DeserializeResult ReturnFenceOnCompletionCallbackDeserialize(ReturnFenceOnCompletionCallbackCmd* record, const volatile ReturnFenceOnCompletionCallbackTransfer* transfer,
                                      const volatile char** buffer, size_t* size, DeserializeAllocator* allocator) {
    DAWN_UNUSED(allocator);
    DAWN_UNUSED(buffer);
    DAWN_UNUSED(size);

    ASSERT(transfer->commandId == ReturnWireCmd::FenceOnCompletionCallback);


    record->fence = transfer->fence;
    record->requestSerial = transfer->requestSerial;
    record->status = transfer->status;





    return DeserializeResult::Success;
}
DAWN_UNUSED_FUNC(ReturnFenceOnCompletionCallbackDeserialize);

        
struct ReturnFenceUpdateCompletedValueTransfer : CmdHeader {
    static_assert(1 <= 1,
                  "Record must be at most one of is_cmd, extensible, and chained.");
    ReturnWireCmd commandId;

    ObjectHandle fence;
    uint64_t value;


};

static_assert(offsetof(ReturnFenceUpdateCompletedValueTransfer, commandSize) == 0, "");
static_assert(offsetof(ReturnFenceUpdateCompletedValueTransfer, commandId) == sizeof(CmdHeader), "");


DAWN_DECLARE_UNUSED size_t ReturnFenceUpdateCompletedValueGetExtraRequiredSize(const ReturnFenceUpdateCompletedValueCmd& record) {
    DAWN_UNUSED(record);

    size_t result = 0;



    {
    }
    {
    }

    return result;
}
// GetExtraRequiredSize isn't used for structures that are value members of other structures
// because we assume they cannot contain pointers themselves.
DAWN_UNUSED_FUNC(ReturnFenceUpdateCompletedValueGetExtraRequiredSize);

DAWN_DECLARE_UNUSED void ReturnFenceUpdateCompletedValueSerialize(const ReturnFenceUpdateCompletedValueCmd& record, ReturnFenceUpdateCompletedValueTransfer* transfer,
                       char** buffer) {
    DAWN_UNUSED(buffer);

    transfer->commandId = ReturnWireCmd::FenceUpdateCompletedValue;

    transfer->fence = record.fence;
    transfer->value = record.value;




}
DAWN_UNUSED_FUNC(ReturnFenceUpdateCompletedValueSerialize);

DAWN_DECLARE_UNUSED DeserializeResult ReturnFenceUpdateCompletedValueDeserialize(ReturnFenceUpdateCompletedValueCmd* record, const volatile ReturnFenceUpdateCompletedValueTransfer* transfer,
                                      const volatile char** buffer, size_t* size, DeserializeAllocator* allocator) {
    DAWN_UNUSED(allocator);
    DAWN_UNUSED(buffer);
    DAWN_UNUSED(size);

    ASSERT(transfer->commandId == ReturnWireCmd::FenceUpdateCompletedValue);


    record->fence = transfer->fence;
    record->value = transfer->value;





    return DeserializeResult::Success;
}
DAWN_UNUSED_FUNC(ReturnFenceUpdateCompletedValueDeserialize);

    }  // anonymous namespace

    
size_t BufferDestroyCmd::GetRequiredSize() const {
    size_t size = sizeof(BufferDestroyTransfer) + BufferDestroyGetExtraRequiredSize(*this);
    return size;
}

void BufferDestroyCmd::Serialize(size_t commandSize, char* buffer, const ObjectIdProvider& objectIdProvider) const {
    auto transfer = reinterpret_cast<BufferDestroyTransfer*>(buffer);
    transfer->commandSize = commandSize;
    buffer += sizeof(BufferDestroyTransfer);

    BufferDestroySerialize(*this, transfer, &buffer, objectIdProvider);
}

DeserializeResult BufferDestroyCmd::Deserialize(const volatile char** buffer, size_t* size, DeserializeAllocator* allocator, const ObjectIdResolver& resolver) {
    const volatile BufferDestroyTransfer* transfer = nullptr;
    DESERIALIZE_TRY(GetPtrFromBuffer(buffer, size, 1, &transfer));

    return BufferDestroyDeserialize(this, transfer, buffer, size, allocator, resolver);
}

    
size_t BufferMapAsyncCmd::GetRequiredSize() const {
    size_t size = sizeof(BufferMapAsyncTransfer) + BufferMapAsyncGetExtraRequiredSize(*this);
    return size;
}

void BufferMapAsyncCmd::Serialize(size_t commandSize, char* buffer, const ObjectIdProvider& objectIdProvider) const {
    auto transfer = reinterpret_cast<BufferMapAsyncTransfer*>(buffer);
    transfer->commandSize = commandSize;
    buffer += sizeof(BufferMapAsyncTransfer);

    BufferMapAsyncSerialize(*this, transfer, &buffer);
}

DeserializeResult BufferMapAsyncCmd::Deserialize(const volatile char** buffer, size_t* size, DeserializeAllocator* allocator) {
    const volatile BufferMapAsyncTransfer* transfer = nullptr;
    DESERIALIZE_TRY(GetPtrFromBuffer(buffer, size, 1, &transfer));

    return BufferMapAsyncDeserialize(this, transfer, buffer, size, allocator);
}

    
size_t BufferUnmapCmd::GetRequiredSize() const {
    size_t size = sizeof(BufferUnmapTransfer) + BufferUnmapGetExtraRequiredSize(*this);
    return size;
}

void BufferUnmapCmd::Serialize(size_t commandSize, char* buffer, const ObjectIdProvider& objectIdProvider) const {
    auto transfer = reinterpret_cast<BufferUnmapTransfer*>(buffer);
    transfer->commandSize = commandSize;
    buffer += sizeof(BufferUnmapTransfer);

    BufferUnmapSerialize(*this, transfer, &buffer, objectIdProvider);
}

DeserializeResult BufferUnmapCmd::Deserialize(const volatile char** buffer, size_t* size, DeserializeAllocator* allocator, const ObjectIdResolver& resolver) {
    const volatile BufferUnmapTransfer* transfer = nullptr;
    DESERIALIZE_TRY(GetPtrFromBuffer(buffer, size, 1, &transfer));

    return BufferUnmapDeserialize(this, transfer, buffer, size, allocator, resolver);
}

    
size_t BufferUpdateMappedDataCmd::GetRequiredSize() const {
    size_t size = sizeof(BufferUpdateMappedDataTransfer) + BufferUpdateMappedDataGetExtraRequiredSize(*this);
    return size;
}

void BufferUpdateMappedDataCmd::Serialize(size_t commandSize, char* buffer, const ObjectIdProvider& objectIdProvider) const {
    auto transfer = reinterpret_cast<BufferUpdateMappedDataTransfer*>(buffer);
    transfer->commandSize = commandSize;
    buffer += sizeof(BufferUpdateMappedDataTransfer);

    BufferUpdateMappedDataSerialize(*this, transfer, &buffer);
}

DeserializeResult BufferUpdateMappedDataCmd::Deserialize(const volatile char** buffer, size_t* size, DeserializeAllocator* allocator) {
    const volatile BufferUpdateMappedDataTransfer* transfer = nullptr;
    DESERIALIZE_TRY(GetPtrFromBuffer(buffer, size, 1, &transfer));

    return BufferUpdateMappedDataDeserialize(this, transfer, buffer, size, allocator);
}

    
size_t CommandEncoderBeginComputePassCmd::GetRequiredSize() const {
    size_t size = sizeof(CommandEncoderBeginComputePassTransfer) + CommandEncoderBeginComputePassGetExtraRequiredSize(*this);
    return size;
}

void CommandEncoderBeginComputePassCmd::Serialize(size_t commandSize, char* buffer, const ObjectIdProvider& objectIdProvider) const {
    auto transfer = reinterpret_cast<CommandEncoderBeginComputePassTransfer*>(buffer);
    transfer->commandSize = commandSize;
    buffer += sizeof(CommandEncoderBeginComputePassTransfer);

    CommandEncoderBeginComputePassSerialize(*this, transfer, &buffer, objectIdProvider);
}

DeserializeResult CommandEncoderBeginComputePassCmd::Deserialize(const volatile char** buffer, size_t* size, DeserializeAllocator* allocator, const ObjectIdResolver& resolver) {
    const volatile CommandEncoderBeginComputePassTransfer* transfer = nullptr;
    DESERIALIZE_TRY(GetPtrFromBuffer(buffer, size, 1, &transfer));

    return CommandEncoderBeginComputePassDeserialize(this, transfer, buffer, size, allocator, resolver);
}

    
size_t CommandEncoderBeginRenderPassCmd::GetRequiredSize() const {
    size_t size = sizeof(CommandEncoderBeginRenderPassTransfer) + CommandEncoderBeginRenderPassGetExtraRequiredSize(*this);
    return size;
}

void CommandEncoderBeginRenderPassCmd::Serialize(size_t commandSize, char* buffer, const ObjectIdProvider& objectIdProvider) const {
    auto transfer = reinterpret_cast<CommandEncoderBeginRenderPassTransfer*>(buffer);
    transfer->commandSize = commandSize;
    buffer += sizeof(CommandEncoderBeginRenderPassTransfer);

    CommandEncoderBeginRenderPassSerialize(*this, transfer, &buffer, objectIdProvider);
}

DeserializeResult CommandEncoderBeginRenderPassCmd::Deserialize(const volatile char** buffer, size_t* size, DeserializeAllocator* allocator, const ObjectIdResolver& resolver) {
    const volatile CommandEncoderBeginRenderPassTransfer* transfer = nullptr;
    DESERIALIZE_TRY(GetPtrFromBuffer(buffer, size, 1, &transfer));

    return CommandEncoderBeginRenderPassDeserialize(this, transfer, buffer, size, allocator, resolver);
}

    
size_t CommandEncoderCopyBufferToBufferCmd::GetRequiredSize() const {
    size_t size = sizeof(CommandEncoderCopyBufferToBufferTransfer) + CommandEncoderCopyBufferToBufferGetExtraRequiredSize(*this);
    return size;
}

void CommandEncoderCopyBufferToBufferCmd::Serialize(size_t commandSize, char* buffer, const ObjectIdProvider& objectIdProvider) const {
    auto transfer = reinterpret_cast<CommandEncoderCopyBufferToBufferTransfer*>(buffer);
    transfer->commandSize = commandSize;
    buffer += sizeof(CommandEncoderCopyBufferToBufferTransfer);

    CommandEncoderCopyBufferToBufferSerialize(*this, transfer, &buffer, objectIdProvider);
}

DeserializeResult CommandEncoderCopyBufferToBufferCmd::Deserialize(const volatile char** buffer, size_t* size, DeserializeAllocator* allocator, const ObjectIdResolver& resolver) {
    const volatile CommandEncoderCopyBufferToBufferTransfer* transfer = nullptr;
    DESERIALIZE_TRY(GetPtrFromBuffer(buffer, size, 1, &transfer));

    return CommandEncoderCopyBufferToBufferDeserialize(this, transfer, buffer, size, allocator, resolver);
}

    
size_t CommandEncoderCopyBufferToTextureCmd::GetRequiredSize() const {
    size_t size = sizeof(CommandEncoderCopyBufferToTextureTransfer) + CommandEncoderCopyBufferToTextureGetExtraRequiredSize(*this);
    return size;
}

void CommandEncoderCopyBufferToTextureCmd::Serialize(size_t commandSize, char* buffer, const ObjectIdProvider& objectIdProvider) const {
    auto transfer = reinterpret_cast<CommandEncoderCopyBufferToTextureTransfer*>(buffer);
    transfer->commandSize = commandSize;
    buffer += sizeof(CommandEncoderCopyBufferToTextureTransfer);

    CommandEncoderCopyBufferToTextureSerialize(*this, transfer, &buffer, objectIdProvider);
}

DeserializeResult CommandEncoderCopyBufferToTextureCmd::Deserialize(const volatile char** buffer, size_t* size, DeserializeAllocator* allocator, const ObjectIdResolver& resolver) {
    const volatile CommandEncoderCopyBufferToTextureTransfer* transfer = nullptr;
    DESERIALIZE_TRY(GetPtrFromBuffer(buffer, size, 1, &transfer));

    return CommandEncoderCopyBufferToTextureDeserialize(this, transfer, buffer, size, allocator, resolver);
}

    
size_t CommandEncoderCopyTextureToBufferCmd::GetRequiredSize() const {
    size_t size = sizeof(CommandEncoderCopyTextureToBufferTransfer) + CommandEncoderCopyTextureToBufferGetExtraRequiredSize(*this);
    return size;
}

void CommandEncoderCopyTextureToBufferCmd::Serialize(size_t commandSize, char* buffer, const ObjectIdProvider& objectIdProvider) const {
    auto transfer = reinterpret_cast<CommandEncoderCopyTextureToBufferTransfer*>(buffer);
    transfer->commandSize = commandSize;
    buffer += sizeof(CommandEncoderCopyTextureToBufferTransfer);

    CommandEncoderCopyTextureToBufferSerialize(*this, transfer, &buffer, objectIdProvider);
}

DeserializeResult CommandEncoderCopyTextureToBufferCmd::Deserialize(const volatile char** buffer, size_t* size, DeserializeAllocator* allocator, const ObjectIdResolver& resolver) {
    const volatile CommandEncoderCopyTextureToBufferTransfer* transfer = nullptr;
    DESERIALIZE_TRY(GetPtrFromBuffer(buffer, size, 1, &transfer));

    return CommandEncoderCopyTextureToBufferDeserialize(this, transfer, buffer, size, allocator, resolver);
}

    
size_t CommandEncoderCopyTextureToTextureCmd::GetRequiredSize() const {
    size_t size = sizeof(CommandEncoderCopyTextureToTextureTransfer) + CommandEncoderCopyTextureToTextureGetExtraRequiredSize(*this);
    return size;
}

void CommandEncoderCopyTextureToTextureCmd::Serialize(size_t commandSize, char* buffer, const ObjectIdProvider& objectIdProvider) const {
    auto transfer = reinterpret_cast<CommandEncoderCopyTextureToTextureTransfer*>(buffer);
    transfer->commandSize = commandSize;
    buffer += sizeof(CommandEncoderCopyTextureToTextureTransfer);

    CommandEncoderCopyTextureToTextureSerialize(*this, transfer, &buffer, objectIdProvider);
}

DeserializeResult CommandEncoderCopyTextureToTextureCmd::Deserialize(const volatile char** buffer, size_t* size, DeserializeAllocator* allocator, const ObjectIdResolver& resolver) {
    const volatile CommandEncoderCopyTextureToTextureTransfer* transfer = nullptr;
    DESERIALIZE_TRY(GetPtrFromBuffer(buffer, size, 1, &transfer));

    return CommandEncoderCopyTextureToTextureDeserialize(this, transfer, buffer, size, allocator, resolver);
}

    
size_t CommandEncoderFinishCmd::GetRequiredSize() const {
    size_t size = sizeof(CommandEncoderFinishTransfer) + CommandEncoderFinishGetExtraRequiredSize(*this);
    return size;
}

void CommandEncoderFinishCmd::Serialize(size_t commandSize, char* buffer, const ObjectIdProvider& objectIdProvider) const {
    auto transfer = reinterpret_cast<CommandEncoderFinishTransfer*>(buffer);
    transfer->commandSize = commandSize;
    buffer += sizeof(CommandEncoderFinishTransfer);

    CommandEncoderFinishSerialize(*this, transfer, &buffer, objectIdProvider);
}

DeserializeResult CommandEncoderFinishCmd::Deserialize(const volatile char** buffer, size_t* size, DeserializeAllocator* allocator, const ObjectIdResolver& resolver) {
    const volatile CommandEncoderFinishTransfer* transfer = nullptr;
    DESERIALIZE_TRY(GetPtrFromBuffer(buffer, size, 1, &transfer));

    return CommandEncoderFinishDeserialize(this, transfer, buffer, size, allocator, resolver);
}

    
size_t CommandEncoderInsertDebugMarkerCmd::GetRequiredSize() const {
    size_t size = sizeof(CommandEncoderInsertDebugMarkerTransfer) + CommandEncoderInsertDebugMarkerGetExtraRequiredSize(*this);
    return size;
}

void CommandEncoderInsertDebugMarkerCmd::Serialize(size_t commandSize, char* buffer, const ObjectIdProvider& objectIdProvider) const {
    auto transfer = reinterpret_cast<CommandEncoderInsertDebugMarkerTransfer*>(buffer);
    transfer->commandSize = commandSize;
    buffer += sizeof(CommandEncoderInsertDebugMarkerTransfer);

    CommandEncoderInsertDebugMarkerSerialize(*this, transfer, &buffer, objectIdProvider);
}

DeserializeResult CommandEncoderInsertDebugMarkerCmd::Deserialize(const volatile char** buffer, size_t* size, DeserializeAllocator* allocator, const ObjectIdResolver& resolver) {
    const volatile CommandEncoderInsertDebugMarkerTransfer* transfer = nullptr;
    DESERIALIZE_TRY(GetPtrFromBuffer(buffer, size, 1, &transfer));

    return CommandEncoderInsertDebugMarkerDeserialize(this, transfer, buffer, size, allocator, resolver);
}

    
size_t CommandEncoderPopDebugGroupCmd::GetRequiredSize() const {
    size_t size = sizeof(CommandEncoderPopDebugGroupTransfer) + CommandEncoderPopDebugGroupGetExtraRequiredSize(*this);
    return size;
}

void CommandEncoderPopDebugGroupCmd::Serialize(size_t commandSize, char* buffer, const ObjectIdProvider& objectIdProvider) const {
    auto transfer = reinterpret_cast<CommandEncoderPopDebugGroupTransfer*>(buffer);
    transfer->commandSize = commandSize;
    buffer += sizeof(CommandEncoderPopDebugGroupTransfer);

    CommandEncoderPopDebugGroupSerialize(*this, transfer, &buffer, objectIdProvider);
}

DeserializeResult CommandEncoderPopDebugGroupCmd::Deserialize(const volatile char** buffer, size_t* size, DeserializeAllocator* allocator, const ObjectIdResolver& resolver) {
    const volatile CommandEncoderPopDebugGroupTransfer* transfer = nullptr;
    DESERIALIZE_TRY(GetPtrFromBuffer(buffer, size, 1, &transfer));

    return CommandEncoderPopDebugGroupDeserialize(this, transfer, buffer, size, allocator, resolver);
}

    
size_t CommandEncoderPushDebugGroupCmd::GetRequiredSize() const {
    size_t size = sizeof(CommandEncoderPushDebugGroupTransfer) + CommandEncoderPushDebugGroupGetExtraRequiredSize(*this);
    return size;
}

void CommandEncoderPushDebugGroupCmd::Serialize(size_t commandSize, char* buffer, const ObjectIdProvider& objectIdProvider) const {
    auto transfer = reinterpret_cast<CommandEncoderPushDebugGroupTransfer*>(buffer);
    transfer->commandSize = commandSize;
    buffer += sizeof(CommandEncoderPushDebugGroupTransfer);

    CommandEncoderPushDebugGroupSerialize(*this, transfer, &buffer, objectIdProvider);
}

DeserializeResult CommandEncoderPushDebugGroupCmd::Deserialize(const volatile char** buffer, size_t* size, DeserializeAllocator* allocator, const ObjectIdResolver& resolver) {
    const volatile CommandEncoderPushDebugGroupTransfer* transfer = nullptr;
    DESERIALIZE_TRY(GetPtrFromBuffer(buffer, size, 1, &transfer));

    return CommandEncoderPushDebugGroupDeserialize(this, transfer, buffer, size, allocator, resolver);
}

    
size_t CommandEncoderResolveQuerySetCmd::GetRequiredSize() const {
    size_t size = sizeof(CommandEncoderResolveQuerySetTransfer) + CommandEncoderResolveQuerySetGetExtraRequiredSize(*this);
    return size;
}

void CommandEncoderResolveQuerySetCmd::Serialize(size_t commandSize, char* buffer, const ObjectIdProvider& objectIdProvider) const {
    auto transfer = reinterpret_cast<CommandEncoderResolveQuerySetTransfer*>(buffer);
    transfer->commandSize = commandSize;
    buffer += sizeof(CommandEncoderResolveQuerySetTransfer);

    CommandEncoderResolveQuerySetSerialize(*this, transfer, &buffer, objectIdProvider);
}

DeserializeResult CommandEncoderResolveQuerySetCmd::Deserialize(const volatile char** buffer, size_t* size, DeserializeAllocator* allocator, const ObjectIdResolver& resolver) {
    const volatile CommandEncoderResolveQuerySetTransfer* transfer = nullptr;
    DESERIALIZE_TRY(GetPtrFromBuffer(buffer, size, 1, &transfer));

    return CommandEncoderResolveQuerySetDeserialize(this, transfer, buffer, size, allocator, resolver);
}

    
size_t CommandEncoderWriteTimestampCmd::GetRequiredSize() const {
    size_t size = sizeof(CommandEncoderWriteTimestampTransfer) + CommandEncoderWriteTimestampGetExtraRequiredSize(*this);
    return size;
}

void CommandEncoderWriteTimestampCmd::Serialize(size_t commandSize, char* buffer, const ObjectIdProvider& objectIdProvider) const {
    auto transfer = reinterpret_cast<CommandEncoderWriteTimestampTransfer*>(buffer);
    transfer->commandSize = commandSize;
    buffer += sizeof(CommandEncoderWriteTimestampTransfer);

    CommandEncoderWriteTimestampSerialize(*this, transfer, &buffer, objectIdProvider);
}

DeserializeResult CommandEncoderWriteTimestampCmd::Deserialize(const volatile char** buffer, size_t* size, DeserializeAllocator* allocator, const ObjectIdResolver& resolver) {
    const volatile CommandEncoderWriteTimestampTransfer* transfer = nullptr;
    DESERIALIZE_TRY(GetPtrFromBuffer(buffer, size, 1, &transfer));

    return CommandEncoderWriteTimestampDeserialize(this, transfer, buffer, size, allocator, resolver);
}

    
size_t ComputePassEncoderDispatchCmd::GetRequiredSize() const {
    size_t size = sizeof(ComputePassEncoderDispatchTransfer) + ComputePassEncoderDispatchGetExtraRequiredSize(*this);
    return size;
}

void ComputePassEncoderDispatchCmd::Serialize(size_t commandSize, char* buffer, const ObjectIdProvider& objectIdProvider) const {
    auto transfer = reinterpret_cast<ComputePassEncoderDispatchTransfer*>(buffer);
    transfer->commandSize = commandSize;
    buffer += sizeof(ComputePassEncoderDispatchTransfer);

    ComputePassEncoderDispatchSerialize(*this, transfer, &buffer, objectIdProvider);
}

DeserializeResult ComputePassEncoderDispatchCmd::Deserialize(const volatile char** buffer, size_t* size, DeserializeAllocator* allocator, const ObjectIdResolver& resolver) {
    const volatile ComputePassEncoderDispatchTransfer* transfer = nullptr;
    DESERIALIZE_TRY(GetPtrFromBuffer(buffer, size, 1, &transfer));

    return ComputePassEncoderDispatchDeserialize(this, transfer, buffer, size, allocator, resolver);
}

    
size_t ComputePassEncoderDispatchIndirectCmd::GetRequiredSize() const {
    size_t size = sizeof(ComputePassEncoderDispatchIndirectTransfer) + ComputePassEncoderDispatchIndirectGetExtraRequiredSize(*this);
    return size;
}

void ComputePassEncoderDispatchIndirectCmd::Serialize(size_t commandSize, char* buffer, const ObjectIdProvider& objectIdProvider) const {
    auto transfer = reinterpret_cast<ComputePassEncoderDispatchIndirectTransfer*>(buffer);
    transfer->commandSize = commandSize;
    buffer += sizeof(ComputePassEncoderDispatchIndirectTransfer);

    ComputePassEncoderDispatchIndirectSerialize(*this, transfer, &buffer, objectIdProvider);
}

DeserializeResult ComputePassEncoderDispatchIndirectCmd::Deserialize(const volatile char** buffer, size_t* size, DeserializeAllocator* allocator, const ObjectIdResolver& resolver) {
    const volatile ComputePassEncoderDispatchIndirectTransfer* transfer = nullptr;
    DESERIALIZE_TRY(GetPtrFromBuffer(buffer, size, 1, &transfer));

    return ComputePassEncoderDispatchIndirectDeserialize(this, transfer, buffer, size, allocator, resolver);
}

    
size_t ComputePassEncoderEndPassCmd::GetRequiredSize() const {
    size_t size = sizeof(ComputePassEncoderEndPassTransfer) + ComputePassEncoderEndPassGetExtraRequiredSize(*this);
    return size;
}

void ComputePassEncoderEndPassCmd::Serialize(size_t commandSize, char* buffer, const ObjectIdProvider& objectIdProvider) const {
    auto transfer = reinterpret_cast<ComputePassEncoderEndPassTransfer*>(buffer);
    transfer->commandSize = commandSize;
    buffer += sizeof(ComputePassEncoderEndPassTransfer);

    ComputePassEncoderEndPassSerialize(*this, transfer, &buffer, objectIdProvider);
}

DeserializeResult ComputePassEncoderEndPassCmd::Deserialize(const volatile char** buffer, size_t* size, DeserializeAllocator* allocator, const ObjectIdResolver& resolver) {
    const volatile ComputePassEncoderEndPassTransfer* transfer = nullptr;
    DESERIALIZE_TRY(GetPtrFromBuffer(buffer, size, 1, &transfer));

    return ComputePassEncoderEndPassDeserialize(this, transfer, buffer, size, allocator, resolver);
}

    
size_t ComputePassEncoderInsertDebugMarkerCmd::GetRequiredSize() const {
    size_t size = sizeof(ComputePassEncoderInsertDebugMarkerTransfer) + ComputePassEncoderInsertDebugMarkerGetExtraRequiredSize(*this);
    return size;
}

void ComputePassEncoderInsertDebugMarkerCmd::Serialize(size_t commandSize, char* buffer, const ObjectIdProvider& objectIdProvider) const {
    auto transfer = reinterpret_cast<ComputePassEncoderInsertDebugMarkerTransfer*>(buffer);
    transfer->commandSize = commandSize;
    buffer += sizeof(ComputePassEncoderInsertDebugMarkerTransfer);

    ComputePassEncoderInsertDebugMarkerSerialize(*this, transfer, &buffer, objectIdProvider);
}

DeserializeResult ComputePassEncoderInsertDebugMarkerCmd::Deserialize(const volatile char** buffer, size_t* size, DeserializeAllocator* allocator, const ObjectIdResolver& resolver) {
    const volatile ComputePassEncoderInsertDebugMarkerTransfer* transfer = nullptr;
    DESERIALIZE_TRY(GetPtrFromBuffer(buffer, size, 1, &transfer));

    return ComputePassEncoderInsertDebugMarkerDeserialize(this, transfer, buffer, size, allocator, resolver);
}

    
size_t ComputePassEncoderPopDebugGroupCmd::GetRequiredSize() const {
    size_t size = sizeof(ComputePassEncoderPopDebugGroupTransfer) + ComputePassEncoderPopDebugGroupGetExtraRequiredSize(*this);
    return size;
}

void ComputePassEncoderPopDebugGroupCmd::Serialize(size_t commandSize, char* buffer, const ObjectIdProvider& objectIdProvider) const {
    auto transfer = reinterpret_cast<ComputePassEncoderPopDebugGroupTransfer*>(buffer);
    transfer->commandSize = commandSize;
    buffer += sizeof(ComputePassEncoderPopDebugGroupTransfer);

    ComputePassEncoderPopDebugGroupSerialize(*this, transfer, &buffer, objectIdProvider);
}

DeserializeResult ComputePassEncoderPopDebugGroupCmd::Deserialize(const volatile char** buffer, size_t* size, DeserializeAllocator* allocator, const ObjectIdResolver& resolver) {
    const volatile ComputePassEncoderPopDebugGroupTransfer* transfer = nullptr;
    DESERIALIZE_TRY(GetPtrFromBuffer(buffer, size, 1, &transfer));

    return ComputePassEncoderPopDebugGroupDeserialize(this, transfer, buffer, size, allocator, resolver);
}

    
size_t ComputePassEncoderPushDebugGroupCmd::GetRequiredSize() const {
    size_t size = sizeof(ComputePassEncoderPushDebugGroupTransfer) + ComputePassEncoderPushDebugGroupGetExtraRequiredSize(*this);
    return size;
}

void ComputePassEncoderPushDebugGroupCmd::Serialize(size_t commandSize, char* buffer, const ObjectIdProvider& objectIdProvider) const {
    auto transfer = reinterpret_cast<ComputePassEncoderPushDebugGroupTransfer*>(buffer);
    transfer->commandSize = commandSize;
    buffer += sizeof(ComputePassEncoderPushDebugGroupTransfer);

    ComputePassEncoderPushDebugGroupSerialize(*this, transfer, &buffer, objectIdProvider);
}

DeserializeResult ComputePassEncoderPushDebugGroupCmd::Deserialize(const volatile char** buffer, size_t* size, DeserializeAllocator* allocator, const ObjectIdResolver& resolver) {
    const volatile ComputePassEncoderPushDebugGroupTransfer* transfer = nullptr;
    DESERIALIZE_TRY(GetPtrFromBuffer(buffer, size, 1, &transfer));

    return ComputePassEncoderPushDebugGroupDeserialize(this, transfer, buffer, size, allocator, resolver);
}

    
size_t ComputePassEncoderSetBindGroupCmd::GetRequiredSize() const {
    size_t size = sizeof(ComputePassEncoderSetBindGroupTransfer) + ComputePassEncoderSetBindGroupGetExtraRequiredSize(*this);
    return size;
}

void ComputePassEncoderSetBindGroupCmd::Serialize(size_t commandSize, char* buffer, const ObjectIdProvider& objectIdProvider) const {
    auto transfer = reinterpret_cast<ComputePassEncoderSetBindGroupTransfer*>(buffer);
    transfer->commandSize = commandSize;
    buffer += sizeof(ComputePassEncoderSetBindGroupTransfer);

    ComputePassEncoderSetBindGroupSerialize(*this, transfer, &buffer, objectIdProvider);
}

DeserializeResult ComputePassEncoderSetBindGroupCmd::Deserialize(const volatile char** buffer, size_t* size, DeserializeAllocator* allocator, const ObjectIdResolver& resolver) {
    const volatile ComputePassEncoderSetBindGroupTransfer* transfer = nullptr;
    DESERIALIZE_TRY(GetPtrFromBuffer(buffer, size, 1, &transfer));

    return ComputePassEncoderSetBindGroupDeserialize(this, transfer, buffer, size, allocator, resolver);
}

    
size_t ComputePassEncoderSetPipelineCmd::GetRequiredSize() const {
    size_t size = sizeof(ComputePassEncoderSetPipelineTransfer) + ComputePassEncoderSetPipelineGetExtraRequiredSize(*this);
    return size;
}

void ComputePassEncoderSetPipelineCmd::Serialize(size_t commandSize, char* buffer, const ObjectIdProvider& objectIdProvider) const {
    auto transfer = reinterpret_cast<ComputePassEncoderSetPipelineTransfer*>(buffer);
    transfer->commandSize = commandSize;
    buffer += sizeof(ComputePassEncoderSetPipelineTransfer);

    ComputePassEncoderSetPipelineSerialize(*this, transfer, &buffer, objectIdProvider);
}

DeserializeResult ComputePassEncoderSetPipelineCmd::Deserialize(const volatile char** buffer, size_t* size, DeserializeAllocator* allocator, const ObjectIdResolver& resolver) {
    const volatile ComputePassEncoderSetPipelineTransfer* transfer = nullptr;
    DESERIALIZE_TRY(GetPtrFromBuffer(buffer, size, 1, &transfer));

    return ComputePassEncoderSetPipelineDeserialize(this, transfer, buffer, size, allocator, resolver);
}

    
size_t ComputePassEncoderWriteTimestampCmd::GetRequiredSize() const {
    size_t size = sizeof(ComputePassEncoderWriteTimestampTransfer) + ComputePassEncoderWriteTimestampGetExtraRequiredSize(*this);
    return size;
}

void ComputePassEncoderWriteTimestampCmd::Serialize(size_t commandSize, char* buffer, const ObjectIdProvider& objectIdProvider) const {
    auto transfer = reinterpret_cast<ComputePassEncoderWriteTimestampTransfer*>(buffer);
    transfer->commandSize = commandSize;
    buffer += sizeof(ComputePassEncoderWriteTimestampTransfer);

    ComputePassEncoderWriteTimestampSerialize(*this, transfer, &buffer, objectIdProvider);
}

DeserializeResult ComputePassEncoderWriteTimestampCmd::Deserialize(const volatile char** buffer, size_t* size, DeserializeAllocator* allocator, const ObjectIdResolver& resolver) {
    const volatile ComputePassEncoderWriteTimestampTransfer* transfer = nullptr;
    DESERIALIZE_TRY(GetPtrFromBuffer(buffer, size, 1, &transfer));

    return ComputePassEncoderWriteTimestampDeserialize(this, transfer, buffer, size, allocator, resolver);
}

    
size_t ComputePipelineGetBindGroupLayoutCmd::GetRequiredSize() const {
    size_t size = sizeof(ComputePipelineGetBindGroupLayoutTransfer) + ComputePipelineGetBindGroupLayoutGetExtraRequiredSize(*this);
    return size;
}

void ComputePipelineGetBindGroupLayoutCmd::Serialize(size_t commandSize, char* buffer, const ObjectIdProvider& objectIdProvider) const {
    auto transfer = reinterpret_cast<ComputePipelineGetBindGroupLayoutTransfer*>(buffer);
    transfer->commandSize = commandSize;
    buffer += sizeof(ComputePipelineGetBindGroupLayoutTransfer);

    ComputePipelineGetBindGroupLayoutSerialize(*this, transfer, &buffer, objectIdProvider);
}

DeserializeResult ComputePipelineGetBindGroupLayoutCmd::Deserialize(const volatile char** buffer, size_t* size, DeserializeAllocator* allocator, const ObjectIdResolver& resolver) {
    const volatile ComputePipelineGetBindGroupLayoutTransfer* transfer = nullptr;
    DESERIALIZE_TRY(GetPtrFromBuffer(buffer, size, 1, &transfer));

    return ComputePipelineGetBindGroupLayoutDeserialize(this, transfer, buffer, size, allocator, resolver);
}

    
size_t DestroyObjectCmd::GetRequiredSize() const {
    size_t size = sizeof(DestroyObjectTransfer) + DestroyObjectGetExtraRequiredSize(*this);
    return size;
}

void DestroyObjectCmd::Serialize(size_t commandSize, char* buffer, const ObjectIdProvider& objectIdProvider) const {
    auto transfer = reinterpret_cast<DestroyObjectTransfer*>(buffer);
    transfer->commandSize = commandSize;
    buffer += sizeof(DestroyObjectTransfer);

    DestroyObjectSerialize(*this, transfer, &buffer);
}

DeserializeResult DestroyObjectCmd::Deserialize(const volatile char** buffer, size_t* size, DeserializeAllocator* allocator) {
    const volatile DestroyObjectTransfer* transfer = nullptr;
    DESERIALIZE_TRY(GetPtrFromBuffer(buffer, size, 1, &transfer));

    return DestroyObjectDeserialize(this, transfer, buffer, size, allocator);
}

    
size_t DeviceCreateBindGroupCmd::GetRequiredSize() const {
    size_t size = sizeof(DeviceCreateBindGroupTransfer) + DeviceCreateBindGroupGetExtraRequiredSize(*this);
    return size;
}

void DeviceCreateBindGroupCmd::Serialize(size_t commandSize, char* buffer, const ObjectIdProvider& objectIdProvider) const {
    auto transfer = reinterpret_cast<DeviceCreateBindGroupTransfer*>(buffer);
    transfer->commandSize = commandSize;
    buffer += sizeof(DeviceCreateBindGroupTransfer);

    DeviceCreateBindGroupSerialize(*this, transfer, &buffer, objectIdProvider);
}

DeserializeResult DeviceCreateBindGroupCmd::Deserialize(const volatile char** buffer, size_t* size, DeserializeAllocator* allocator, const ObjectIdResolver& resolver) {
    const volatile DeviceCreateBindGroupTransfer* transfer = nullptr;
    DESERIALIZE_TRY(GetPtrFromBuffer(buffer, size, 1, &transfer));

    return DeviceCreateBindGroupDeserialize(this, transfer, buffer, size, allocator, resolver);
}

    
size_t DeviceCreateBindGroupLayoutCmd::GetRequiredSize() const {
    size_t size = sizeof(DeviceCreateBindGroupLayoutTransfer) + DeviceCreateBindGroupLayoutGetExtraRequiredSize(*this);
    return size;
}

void DeviceCreateBindGroupLayoutCmd::Serialize(size_t commandSize, char* buffer, const ObjectIdProvider& objectIdProvider) const {
    auto transfer = reinterpret_cast<DeviceCreateBindGroupLayoutTransfer*>(buffer);
    transfer->commandSize = commandSize;
    buffer += sizeof(DeviceCreateBindGroupLayoutTransfer);

    DeviceCreateBindGroupLayoutSerialize(*this, transfer, &buffer, objectIdProvider);
}

DeserializeResult DeviceCreateBindGroupLayoutCmd::Deserialize(const volatile char** buffer, size_t* size, DeserializeAllocator* allocator, const ObjectIdResolver& resolver) {
    const volatile DeviceCreateBindGroupLayoutTransfer* transfer = nullptr;
    DESERIALIZE_TRY(GetPtrFromBuffer(buffer, size, 1, &transfer));

    return DeviceCreateBindGroupLayoutDeserialize(this, transfer, buffer, size, allocator, resolver);
}

    
size_t DeviceCreateBufferCmd::GetRequiredSize() const {
    size_t size = sizeof(DeviceCreateBufferTransfer) + DeviceCreateBufferGetExtraRequiredSize(*this);
    return size;
}

void DeviceCreateBufferCmd::Serialize(size_t commandSize, char* buffer, const ObjectIdProvider& objectIdProvider) const {
    auto transfer = reinterpret_cast<DeviceCreateBufferTransfer*>(buffer);
    transfer->commandSize = commandSize;
    buffer += sizeof(DeviceCreateBufferTransfer);

    DeviceCreateBufferSerialize(*this, transfer, &buffer, objectIdProvider);
}

DeserializeResult DeviceCreateBufferCmd::Deserialize(const volatile char** buffer, size_t* size, DeserializeAllocator* allocator, const ObjectIdResolver& resolver) {
    const volatile DeviceCreateBufferTransfer* transfer = nullptr;
    DESERIALIZE_TRY(GetPtrFromBuffer(buffer, size, 1, &transfer));

    return DeviceCreateBufferDeserialize(this, transfer, buffer, size, allocator, resolver);
}

    
size_t DeviceCreateCommandEncoderCmd::GetRequiredSize() const {
    size_t size = sizeof(DeviceCreateCommandEncoderTransfer) + DeviceCreateCommandEncoderGetExtraRequiredSize(*this);
    return size;
}

void DeviceCreateCommandEncoderCmd::Serialize(size_t commandSize, char* buffer, const ObjectIdProvider& objectIdProvider) const {
    auto transfer = reinterpret_cast<DeviceCreateCommandEncoderTransfer*>(buffer);
    transfer->commandSize = commandSize;
    buffer += sizeof(DeviceCreateCommandEncoderTransfer);

    DeviceCreateCommandEncoderSerialize(*this, transfer, &buffer, objectIdProvider);
}

DeserializeResult DeviceCreateCommandEncoderCmd::Deserialize(const volatile char** buffer, size_t* size, DeserializeAllocator* allocator, const ObjectIdResolver& resolver) {
    const volatile DeviceCreateCommandEncoderTransfer* transfer = nullptr;
    DESERIALIZE_TRY(GetPtrFromBuffer(buffer, size, 1, &transfer));

    return DeviceCreateCommandEncoderDeserialize(this, transfer, buffer, size, allocator, resolver);
}

    
size_t DeviceCreateComputePipelineCmd::GetRequiredSize() const {
    size_t size = sizeof(DeviceCreateComputePipelineTransfer) + DeviceCreateComputePipelineGetExtraRequiredSize(*this);
    return size;
}

void DeviceCreateComputePipelineCmd::Serialize(size_t commandSize, char* buffer, const ObjectIdProvider& objectIdProvider) const {
    auto transfer = reinterpret_cast<DeviceCreateComputePipelineTransfer*>(buffer);
    transfer->commandSize = commandSize;
    buffer += sizeof(DeviceCreateComputePipelineTransfer);

    DeviceCreateComputePipelineSerialize(*this, transfer, &buffer, objectIdProvider);
}

DeserializeResult DeviceCreateComputePipelineCmd::Deserialize(const volatile char** buffer, size_t* size, DeserializeAllocator* allocator, const ObjectIdResolver& resolver) {
    const volatile DeviceCreateComputePipelineTransfer* transfer = nullptr;
    DESERIALIZE_TRY(GetPtrFromBuffer(buffer, size, 1, &transfer));

    return DeviceCreateComputePipelineDeserialize(this, transfer, buffer, size, allocator, resolver);
}

    
size_t DeviceCreateErrorBufferCmd::GetRequiredSize() const {
    size_t size = sizeof(DeviceCreateErrorBufferTransfer) + DeviceCreateErrorBufferGetExtraRequiredSize(*this);
    return size;
}

void DeviceCreateErrorBufferCmd::Serialize(size_t commandSize, char* buffer, const ObjectIdProvider& objectIdProvider) const {
    auto transfer = reinterpret_cast<DeviceCreateErrorBufferTransfer*>(buffer);
    transfer->commandSize = commandSize;
    buffer += sizeof(DeviceCreateErrorBufferTransfer);

    DeviceCreateErrorBufferSerialize(*this, transfer, &buffer, objectIdProvider);
}

DeserializeResult DeviceCreateErrorBufferCmd::Deserialize(const volatile char** buffer, size_t* size, DeserializeAllocator* allocator, const ObjectIdResolver& resolver) {
    const volatile DeviceCreateErrorBufferTransfer* transfer = nullptr;
    DESERIALIZE_TRY(GetPtrFromBuffer(buffer, size, 1, &transfer));

    return DeviceCreateErrorBufferDeserialize(this, transfer, buffer, size, allocator, resolver);
}

    
size_t DeviceCreatePipelineLayoutCmd::GetRequiredSize() const {
    size_t size = sizeof(DeviceCreatePipelineLayoutTransfer) + DeviceCreatePipelineLayoutGetExtraRequiredSize(*this);
    return size;
}

void DeviceCreatePipelineLayoutCmd::Serialize(size_t commandSize, char* buffer, const ObjectIdProvider& objectIdProvider) const {
    auto transfer = reinterpret_cast<DeviceCreatePipelineLayoutTransfer*>(buffer);
    transfer->commandSize = commandSize;
    buffer += sizeof(DeviceCreatePipelineLayoutTransfer);

    DeviceCreatePipelineLayoutSerialize(*this, transfer, &buffer, objectIdProvider);
}

DeserializeResult DeviceCreatePipelineLayoutCmd::Deserialize(const volatile char** buffer, size_t* size, DeserializeAllocator* allocator, const ObjectIdResolver& resolver) {
    const volatile DeviceCreatePipelineLayoutTransfer* transfer = nullptr;
    DESERIALIZE_TRY(GetPtrFromBuffer(buffer, size, 1, &transfer));

    return DeviceCreatePipelineLayoutDeserialize(this, transfer, buffer, size, allocator, resolver);
}

    
size_t DeviceCreateQuerySetCmd::GetRequiredSize() const {
    size_t size = sizeof(DeviceCreateQuerySetTransfer) + DeviceCreateQuerySetGetExtraRequiredSize(*this);
    return size;
}

void DeviceCreateQuerySetCmd::Serialize(size_t commandSize, char* buffer, const ObjectIdProvider& objectIdProvider) const {
    auto transfer = reinterpret_cast<DeviceCreateQuerySetTransfer*>(buffer);
    transfer->commandSize = commandSize;
    buffer += sizeof(DeviceCreateQuerySetTransfer);

    DeviceCreateQuerySetSerialize(*this, transfer, &buffer, objectIdProvider);
}

DeserializeResult DeviceCreateQuerySetCmd::Deserialize(const volatile char** buffer, size_t* size, DeserializeAllocator* allocator, const ObjectIdResolver& resolver) {
    const volatile DeviceCreateQuerySetTransfer* transfer = nullptr;
    DESERIALIZE_TRY(GetPtrFromBuffer(buffer, size, 1, &transfer));

    return DeviceCreateQuerySetDeserialize(this, transfer, buffer, size, allocator, resolver);
}

    
size_t DeviceCreateReadyComputePipelineCmd::GetRequiredSize() const {
    size_t size = sizeof(DeviceCreateReadyComputePipelineTransfer) + DeviceCreateReadyComputePipelineGetExtraRequiredSize(*this);
    return size;
}

void DeviceCreateReadyComputePipelineCmd::Serialize(size_t commandSize, char* buffer, const ObjectIdProvider& objectIdProvider) const {
    auto transfer = reinterpret_cast<DeviceCreateReadyComputePipelineTransfer*>(buffer);
    transfer->commandSize = commandSize;
    buffer += sizeof(DeviceCreateReadyComputePipelineTransfer);

    DeviceCreateReadyComputePipelineSerialize(*this, transfer, &buffer, objectIdProvider);
}

DeserializeResult DeviceCreateReadyComputePipelineCmd::Deserialize(const volatile char** buffer, size_t* size, DeserializeAllocator* allocator, const ObjectIdResolver& resolver) {
    const volatile DeviceCreateReadyComputePipelineTransfer* transfer = nullptr;
    DESERIALIZE_TRY(GetPtrFromBuffer(buffer, size, 1, &transfer));

    return DeviceCreateReadyComputePipelineDeserialize(this, transfer, buffer, size, allocator, resolver);
}

    
size_t DeviceCreateReadyRenderPipelineCmd::GetRequiredSize() const {
    size_t size = sizeof(DeviceCreateReadyRenderPipelineTransfer) + DeviceCreateReadyRenderPipelineGetExtraRequiredSize(*this);
    return size;
}

void DeviceCreateReadyRenderPipelineCmd::Serialize(size_t commandSize, char* buffer, const ObjectIdProvider& objectIdProvider) const {
    auto transfer = reinterpret_cast<DeviceCreateReadyRenderPipelineTransfer*>(buffer);
    transfer->commandSize = commandSize;
    buffer += sizeof(DeviceCreateReadyRenderPipelineTransfer);

    DeviceCreateReadyRenderPipelineSerialize(*this, transfer, &buffer, objectIdProvider);
}

DeserializeResult DeviceCreateReadyRenderPipelineCmd::Deserialize(const volatile char** buffer, size_t* size, DeserializeAllocator* allocator, const ObjectIdResolver& resolver) {
    const volatile DeviceCreateReadyRenderPipelineTransfer* transfer = nullptr;
    DESERIALIZE_TRY(GetPtrFromBuffer(buffer, size, 1, &transfer));

    return DeviceCreateReadyRenderPipelineDeserialize(this, transfer, buffer, size, allocator, resolver);
}

    
size_t DeviceCreateRenderBundleEncoderCmd::GetRequiredSize() const {
    size_t size = sizeof(DeviceCreateRenderBundleEncoderTransfer) + DeviceCreateRenderBundleEncoderGetExtraRequiredSize(*this);
    return size;
}

void DeviceCreateRenderBundleEncoderCmd::Serialize(size_t commandSize, char* buffer, const ObjectIdProvider& objectIdProvider) const {
    auto transfer = reinterpret_cast<DeviceCreateRenderBundleEncoderTransfer*>(buffer);
    transfer->commandSize = commandSize;
    buffer += sizeof(DeviceCreateRenderBundleEncoderTransfer);

    DeviceCreateRenderBundleEncoderSerialize(*this, transfer, &buffer, objectIdProvider);
}

DeserializeResult DeviceCreateRenderBundleEncoderCmd::Deserialize(const volatile char** buffer, size_t* size, DeserializeAllocator* allocator, const ObjectIdResolver& resolver) {
    const volatile DeviceCreateRenderBundleEncoderTransfer* transfer = nullptr;
    DESERIALIZE_TRY(GetPtrFromBuffer(buffer, size, 1, &transfer));

    return DeviceCreateRenderBundleEncoderDeserialize(this, transfer, buffer, size, allocator, resolver);
}

    
size_t DeviceCreateRenderPipelineCmd::GetRequiredSize() const {
    size_t size = sizeof(DeviceCreateRenderPipelineTransfer) + DeviceCreateRenderPipelineGetExtraRequiredSize(*this);
    return size;
}

void DeviceCreateRenderPipelineCmd::Serialize(size_t commandSize, char* buffer, const ObjectIdProvider& objectIdProvider) const {
    auto transfer = reinterpret_cast<DeviceCreateRenderPipelineTransfer*>(buffer);
    transfer->commandSize = commandSize;
    buffer += sizeof(DeviceCreateRenderPipelineTransfer);

    DeviceCreateRenderPipelineSerialize(*this, transfer, &buffer, objectIdProvider);
}

DeserializeResult DeviceCreateRenderPipelineCmd::Deserialize(const volatile char** buffer, size_t* size, DeserializeAllocator* allocator, const ObjectIdResolver& resolver) {
    const volatile DeviceCreateRenderPipelineTransfer* transfer = nullptr;
    DESERIALIZE_TRY(GetPtrFromBuffer(buffer, size, 1, &transfer));

    return DeviceCreateRenderPipelineDeserialize(this, transfer, buffer, size, allocator, resolver);
}

    
size_t DeviceCreateSamplerCmd::GetRequiredSize() const {
    size_t size = sizeof(DeviceCreateSamplerTransfer) + DeviceCreateSamplerGetExtraRequiredSize(*this);
    return size;
}

void DeviceCreateSamplerCmd::Serialize(size_t commandSize, char* buffer, const ObjectIdProvider& objectIdProvider) const {
    auto transfer = reinterpret_cast<DeviceCreateSamplerTransfer*>(buffer);
    transfer->commandSize = commandSize;
    buffer += sizeof(DeviceCreateSamplerTransfer);

    DeviceCreateSamplerSerialize(*this, transfer, &buffer, objectIdProvider);
}

DeserializeResult DeviceCreateSamplerCmd::Deserialize(const volatile char** buffer, size_t* size, DeserializeAllocator* allocator, const ObjectIdResolver& resolver) {
    const volatile DeviceCreateSamplerTransfer* transfer = nullptr;
    DESERIALIZE_TRY(GetPtrFromBuffer(buffer, size, 1, &transfer));

    return DeviceCreateSamplerDeserialize(this, transfer, buffer, size, allocator, resolver);
}

    
size_t DeviceCreateShaderModuleCmd::GetRequiredSize() const {
    size_t size = sizeof(DeviceCreateShaderModuleTransfer) + DeviceCreateShaderModuleGetExtraRequiredSize(*this);
    return size;
}

void DeviceCreateShaderModuleCmd::Serialize(size_t commandSize, char* buffer, const ObjectIdProvider& objectIdProvider) const {
    auto transfer = reinterpret_cast<DeviceCreateShaderModuleTransfer*>(buffer);
    transfer->commandSize = commandSize;
    buffer += sizeof(DeviceCreateShaderModuleTransfer);

    DeviceCreateShaderModuleSerialize(*this, transfer, &buffer, objectIdProvider);
}

DeserializeResult DeviceCreateShaderModuleCmd::Deserialize(const volatile char** buffer, size_t* size, DeserializeAllocator* allocator, const ObjectIdResolver& resolver) {
    const volatile DeviceCreateShaderModuleTransfer* transfer = nullptr;
    DESERIALIZE_TRY(GetPtrFromBuffer(buffer, size, 1, &transfer));

    return DeviceCreateShaderModuleDeserialize(this, transfer, buffer, size, allocator, resolver);
}

    
size_t DeviceCreateSwapChainCmd::GetRequiredSize() const {
    size_t size = sizeof(DeviceCreateSwapChainTransfer) + DeviceCreateSwapChainGetExtraRequiredSize(*this);
    return size;
}

void DeviceCreateSwapChainCmd::Serialize(size_t commandSize, char* buffer, const ObjectIdProvider& objectIdProvider) const {
    auto transfer = reinterpret_cast<DeviceCreateSwapChainTransfer*>(buffer);
    transfer->commandSize = commandSize;
    buffer += sizeof(DeviceCreateSwapChainTransfer);

    DeviceCreateSwapChainSerialize(*this, transfer, &buffer, objectIdProvider);
}

DeserializeResult DeviceCreateSwapChainCmd::Deserialize(const volatile char** buffer, size_t* size, DeserializeAllocator* allocator, const ObjectIdResolver& resolver) {
    const volatile DeviceCreateSwapChainTransfer* transfer = nullptr;
    DESERIALIZE_TRY(GetPtrFromBuffer(buffer, size, 1, &transfer));

    return DeviceCreateSwapChainDeserialize(this, transfer, buffer, size, allocator, resolver);
}

    
size_t DeviceCreateTextureCmd::GetRequiredSize() const {
    size_t size = sizeof(DeviceCreateTextureTransfer) + DeviceCreateTextureGetExtraRequiredSize(*this);
    return size;
}

void DeviceCreateTextureCmd::Serialize(size_t commandSize, char* buffer, const ObjectIdProvider& objectIdProvider) const {
    auto transfer = reinterpret_cast<DeviceCreateTextureTransfer*>(buffer);
    transfer->commandSize = commandSize;
    buffer += sizeof(DeviceCreateTextureTransfer);

    DeviceCreateTextureSerialize(*this, transfer, &buffer, objectIdProvider);
}

DeserializeResult DeviceCreateTextureCmd::Deserialize(const volatile char** buffer, size_t* size, DeserializeAllocator* allocator, const ObjectIdResolver& resolver) {
    const volatile DeviceCreateTextureTransfer* transfer = nullptr;
    DESERIALIZE_TRY(GetPtrFromBuffer(buffer, size, 1, &transfer));

    return DeviceCreateTextureDeserialize(this, transfer, buffer, size, allocator, resolver);
}

    
size_t DeviceGetDefaultQueueCmd::GetRequiredSize() const {
    size_t size = sizeof(DeviceGetDefaultQueueTransfer) + DeviceGetDefaultQueueGetExtraRequiredSize(*this);
    return size;
}

void DeviceGetDefaultQueueCmd::Serialize(size_t commandSize, char* buffer, const ObjectIdProvider& objectIdProvider) const {
    auto transfer = reinterpret_cast<DeviceGetDefaultQueueTransfer*>(buffer);
    transfer->commandSize = commandSize;
    buffer += sizeof(DeviceGetDefaultQueueTransfer);

    DeviceGetDefaultQueueSerialize(*this, transfer, &buffer, objectIdProvider);
}

DeserializeResult DeviceGetDefaultQueueCmd::Deserialize(const volatile char** buffer, size_t* size, DeserializeAllocator* allocator, const ObjectIdResolver& resolver) {
    const volatile DeviceGetDefaultQueueTransfer* transfer = nullptr;
    DESERIALIZE_TRY(GetPtrFromBuffer(buffer, size, 1, &transfer));

    return DeviceGetDefaultQueueDeserialize(this, transfer, buffer, size, allocator, resolver);
}

    
size_t DeviceInjectErrorCmd::GetRequiredSize() const {
    size_t size = sizeof(DeviceInjectErrorTransfer) + DeviceInjectErrorGetExtraRequiredSize(*this);
    return size;
}

void DeviceInjectErrorCmd::Serialize(size_t commandSize, char* buffer, const ObjectIdProvider& objectIdProvider) const {
    auto transfer = reinterpret_cast<DeviceInjectErrorTransfer*>(buffer);
    transfer->commandSize = commandSize;
    buffer += sizeof(DeviceInjectErrorTransfer);

    DeviceInjectErrorSerialize(*this, transfer, &buffer, objectIdProvider);
}

DeserializeResult DeviceInjectErrorCmd::Deserialize(const volatile char** buffer, size_t* size, DeserializeAllocator* allocator, const ObjectIdResolver& resolver) {
    const volatile DeviceInjectErrorTransfer* transfer = nullptr;
    DESERIALIZE_TRY(GetPtrFromBuffer(buffer, size, 1, &transfer));

    return DeviceInjectErrorDeserialize(this, transfer, buffer, size, allocator, resolver);
}

    
size_t DeviceLoseForTestingCmd::GetRequiredSize() const {
    size_t size = sizeof(DeviceLoseForTestingTransfer) + DeviceLoseForTestingGetExtraRequiredSize(*this);
    return size;
}

void DeviceLoseForTestingCmd::Serialize(size_t commandSize, char* buffer, const ObjectIdProvider& objectIdProvider) const {
    auto transfer = reinterpret_cast<DeviceLoseForTestingTransfer*>(buffer);
    transfer->commandSize = commandSize;
    buffer += sizeof(DeviceLoseForTestingTransfer);

    DeviceLoseForTestingSerialize(*this, transfer, &buffer, objectIdProvider);
}

DeserializeResult DeviceLoseForTestingCmd::Deserialize(const volatile char** buffer, size_t* size, DeserializeAllocator* allocator, const ObjectIdResolver& resolver) {
    const volatile DeviceLoseForTestingTransfer* transfer = nullptr;
    DESERIALIZE_TRY(GetPtrFromBuffer(buffer, size, 1, &transfer));

    return DeviceLoseForTestingDeserialize(this, transfer, buffer, size, allocator, resolver);
}

    
size_t DevicePopErrorScopeCmd::GetRequiredSize() const {
    size_t size = sizeof(DevicePopErrorScopeTransfer) + DevicePopErrorScopeGetExtraRequiredSize(*this);
    return size;
}

void DevicePopErrorScopeCmd::Serialize(size_t commandSize, char* buffer, const ObjectIdProvider& objectIdProvider) const {
    auto transfer = reinterpret_cast<DevicePopErrorScopeTransfer*>(buffer);
    transfer->commandSize = commandSize;
    buffer += sizeof(DevicePopErrorScopeTransfer);

    DevicePopErrorScopeSerialize(*this, transfer, &buffer, objectIdProvider);
}

DeserializeResult DevicePopErrorScopeCmd::Deserialize(const volatile char** buffer, size_t* size, DeserializeAllocator* allocator, const ObjectIdResolver& resolver) {
    const volatile DevicePopErrorScopeTransfer* transfer = nullptr;
    DESERIALIZE_TRY(GetPtrFromBuffer(buffer, size, 1, &transfer));

    return DevicePopErrorScopeDeserialize(this, transfer, buffer, size, allocator, resolver);
}

    
size_t DevicePushErrorScopeCmd::GetRequiredSize() const {
    size_t size = sizeof(DevicePushErrorScopeTransfer) + DevicePushErrorScopeGetExtraRequiredSize(*this);
    return size;
}

void DevicePushErrorScopeCmd::Serialize(size_t commandSize, char* buffer, const ObjectIdProvider& objectIdProvider) const {
    auto transfer = reinterpret_cast<DevicePushErrorScopeTransfer*>(buffer);
    transfer->commandSize = commandSize;
    buffer += sizeof(DevicePushErrorScopeTransfer);

    DevicePushErrorScopeSerialize(*this, transfer, &buffer, objectIdProvider);
}

DeserializeResult DevicePushErrorScopeCmd::Deserialize(const volatile char** buffer, size_t* size, DeserializeAllocator* allocator, const ObjectIdResolver& resolver) {
    const volatile DevicePushErrorScopeTransfer* transfer = nullptr;
    DESERIALIZE_TRY(GetPtrFromBuffer(buffer, size, 1, &transfer));

    return DevicePushErrorScopeDeserialize(this, transfer, buffer, size, allocator, resolver);
}

    
size_t DeviceTickCmd::GetRequiredSize() const {
    size_t size = sizeof(DeviceTickTransfer) + DeviceTickGetExtraRequiredSize(*this);
    return size;
}

void DeviceTickCmd::Serialize(size_t commandSize, char* buffer, const ObjectIdProvider& objectIdProvider) const {
    auto transfer = reinterpret_cast<DeviceTickTransfer*>(buffer);
    transfer->commandSize = commandSize;
    buffer += sizeof(DeviceTickTransfer);

    DeviceTickSerialize(*this, transfer, &buffer, objectIdProvider);
}

DeserializeResult DeviceTickCmd::Deserialize(const volatile char** buffer, size_t* size, DeserializeAllocator* allocator, const ObjectIdResolver& resolver) {
    const volatile DeviceTickTransfer* transfer = nullptr;
    DESERIALIZE_TRY(GetPtrFromBuffer(buffer, size, 1, &transfer));

    return DeviceTickDeserialize(this, transfer, buffer, size, allocator, resolver);
}

    
size_t FenceOnCompletionCmd::GetRequiredSize() const {
    size_t size = sizeof(FenceOnCompletionTransfer) + FenceOnCompletionGetExtraRequiredSize(*this);
    return size;
}

void FenceOnCompletionCmd::Serialize(size_t commandSize, char* buffer, const ObjectIdProvider& objectIdProvider) const {
    auto transfer = reinterpret_cast<FenceOnCompletionTransfer*>(buffer);
    transfer->commandSize = commandSize;
    buffer += sizeof(FenceOnCompletionTransfer);

    FenceOnCompletionSerialize(*this, transfer, &buffer);
}

DeserializeResult FenceOnCompletionCmd::Deserialize(const volatile char** buffer, size_t* size, DeserializeAllocator* allocator) {
    const volatile FenceOnCompletionTransfer* transfer = nullptr;
    DESERIALIZE_TRY(GetPtrFromBuffer(buffer, size, 1, &transfer));

    return FenceOnCompletionDeserialize(this, transfer, buffer, size, allocator);
}

    
size_t InstanceCreateSurfaceCmd::GetRequiredSize() const {
    size_t size = sizeof(InstanceCreateSurfaceTransfer) + InstanceCreateSurfaceGetExtraRequiredSize(*this);
    return size;
}

void InstanceCreateSurfaceCmd::Serialize(size_t commandSize, char* buffer, const ObjectIdProvider& objectIdProvider) const {
    auto transfer = reinterpret_cast<InstanceCreateSurfaceTransfer*>(buffer);
    transfer->commandSize = commandSize;
    buffer += sizeof(InstanceCreateSurfaceTransfer);

    InstanceCreateSurfaceSerialize(*this, transfer, &buffer, objectIdProvider);
}

DeserializeResult InstanceCreateSurfaceCmd::Deserialize(const volatile char** buffer, size_t* size, DeserializeAllocator* allocator, const ObjectIdResolver& resolver) {
    const volatile InstanceCreateSurfaceTransfer* transfer = nullptr;
    DESERIALIZE_TRY(GetPtrFromBuffer(buffer, size, 1, &transfer));

    return InstanceCreateSurfaceDeserialize(this, transfer, buffer, size, allocator, resolver);
}

    
size_t QuerySetDestroyCmd::GetRequiredSize() const {
    size_t size = sizeof(QuerySetDestroyTransfer) + QuerySetDestroyGetExtraRequiredSize(*this);
    return size;
}

void QuerySetDestroyCmd::Serialize(size_t commandSize, char* buffer, const ObjectIdProvider& objectIdProvider) const {
    auto transfer = reinterpret_cast<QuerySetDestroyTransfer*>(buffer);
    transfer->commandSize = commandSize;
    buffer += sizeof(QuerySetDestroyTransfer);

    QuerySetDestroySerialize(*this, transfer, &buffer, objectIdProvider);
}

DeserializeResult QuerySetDestroyCmd::Deserialize(const volatile char** buffer, size_t* size, DeserializeAllocator* allocator, const ObjectIdResolver& resolver) {
    const volatile QuerySetDestroyTransfer* transfer = nullptr;
    DESERIALIZE_TRY(GetPtrFromBuffer(buffer, size, 1, &transfer));

    return QuerySetDestroyDeserialize(this, transfer, buffer, size, allocator, resolver);
}

    
size_t QueueCreateFenceCmd::GetRequiredSize() const {
    size_t size = sizeof(QueueCreateFenceTransfer) + QueueCreateFenceGetExtraRequiredSize(*this);
    return size;
}

void QueueCreateFenceCmd::Serialize(size_t commandSize, char* buffer, const ObjectIdProvider& objectIdProvider) const {
    auto transfer = reinterpret_cast<QueueCreateFenceTransfer*>(buffer);
    transfer->commandSize = commandSize;
    buffer += sizeof(QueueCreateFenceTransfer);

    QueueCreateFenceSerialize(*this, transfer, &buffer, objectIdProvider);
}

DeserializeResult QueueCreateFenceCmd::Deserialize(const volatile char** buffer, size_t* size, DeserializeAllocator* allocator, const ObjectIdResolver& resolver) {
    const volatile QueueCreateFenceTransfer* transfer = nullptr;
    DESERIALIZE_TRY(GetPtrFromBuffer(buffer, size, 1, &transfer));

    return QueueCreateFenceDeserialize(this, transfer, buffer, size, allocator, resolver);
}

    
size_t QueueSignalCmd::GetRequiredSize() const {
    size_t size = sizeof(QueueSignalTransfer) + QueueSignalGetExtraRequiredSize(*this);
    return size;
}

void QueueSignalCmd::Serialize(size_t commandSize, char* buffer, const ObjectIdProvider& objectIdProvider) const {
    auto transfer = reinterpret_cast<QueueSignalTransfer*>(buffer);
    transfer->commandSize = commandSize;
    buffer += sizeof(QueueSignalTransfer);

    QueueSignalSerialize(*this, transfer, &buffer, objectIdProvider);
}

DeserializeResult QueueSignalCmd::Deserialize(const volatile char** buffer, size_t* size, DeserializeAllocator* allocator, const ObjectIdResolver& resolver) {
    const volatile QueueSignalTransfer* transfer = nullptr;
    DESERIALIZE_TRY(GetPtrFromBuffer(buffer, size, 1, &transfer));

    return QueueSignalDeserialize(this, transfer, buffer, size, allocator, resolver);
}

    
size_t QueueSubmitCmd::GetRequiredSize() const {
    size_t size = sizeof(QueueSubmitTransfer) + QueueSubmitGetExtraRequiredSize(*this);
    return size;
}

void QueueSubmitCmd::Serialize(size_t commandSize, char* buffer, const ObjectIdProvider& objectIdProvider) const {
    auto transfer = reinterpret_cast<QueueSubmitTransfer*>(buffer);
    transfer->commandSize = commandSize;
    buffer += sizeof(QueueSubmitTransfer);

    QueueSubmitSerialize(*this, transfer, &buffer, objectIdProvider);
}

DeserializeResult QueueSubmitCmd::Deserialize(const volatile char** buffer, size_t* size, DeserializeAllocator* allocator, const ObjectIdResolver& resolver) {
    const volatile QueueSubmitTransfer* transfer = nullptr;
    DESERIALIZE_TRY(GetPtrFromBuffer(buffer, size, 1, &transfer));

    return QueueSubmitDeserialize(this, transfer, buffer, size, allocator, resolver);
}

    
size_t QueueWriteBufferInternalCmd::GetRequiredSize() const {
    size_t size = sizeof(QueueWriteBufferInternalTransfer) + QueueWriteBufferInternalGetExtraRequiredSize(*this);
    return size;
}

void QueueWriteBufferInternalCmd::Serialize(size_t commandSize, char* buffer, const ObjectIdProvider& objectIdProvider) const {
    auto transfer = reinterpret_cast<QueueWriteBufferInternalTransfer*>(buffer);
    transfer->commandSize = commandSize;
    buffer += sizeof(QueueWriteBufferInternalTransfer);

    QueueWriteBufferInternalSerialize(*this, transfer, &buffer);
}

DeserializeResult QueueWriteBufferInternalCmd::Deserialize(const volatile char** buffer, size_t* size, DeserializeAllocator* allocator) {
    const volatile QueueWriteBufferInternalTransfer* transfer = nullptr;
    DESERIALIZE_TRY(GetPtrFromBuffer(buffer, size, 1, &transfer));

    return QueueWriteBufferInternalDeserialize(this, transfer, buffer, size, allocator);
}

    
size_t QueueWriteTextureInternalCmd::GetRequiredSize() const {
    size_t size = sizeof(QueueWriteTextureInternalTransfer) + QueueWriteTextureInternalGetExtraRequiredSize(*this);
    return size;
}

void QueueWriteTextureInternalCmd::Serialize(size_t commandSize, char* buffer, const ObjectIdProvider& objectIdProvider) const {
    auto transfer = reinterpret_cast<QueueWriteTextureInternalTransfer*>(buffer);
    transfer->commandSize = commandSize;
    buffer += sizeof(QueueWriteTextureInternalTransfer);

    QueueWriteTextureInternalSerialize(*this, transfer, &buffer, objectIdProvider);
}

DeserializeResult QueueWriteTextureInternalCmd::Deserialize(const volatile char** buffer, size_t* size, DeserializeAllocator* allocator, const ObjectIdResolver& resolver) {
    const volatile QueueWriteTextureInternalTransfer* transfer = nullptr;
    DESERIALIZE_TRY(GetPtrFromBuffer(buffer, size, 1, &transfer));

    return QueueWriteTextureInternalDeserialize(this, transfer, buffer, size, allocator, resolver);
}

    
size_t RenderBundleEncoderDrawCmd::GetRequiredSize() const {
    size_t size = sizeof(RenderBundleEncoderDrawTransfer) + RenderBundleEncoderDrawGetExtraRequiredSize(*this);
    return size;
}

void RenderBundleEncoderDrawCmd::Serialize(size_t commandSize, char* buffer, const ObjectIdProvider& objectIdProvider) const {
    auto transfer = reinterpret_cast<RenderBundleEncoderDrawTransfer*>(buffer);
    transfer->commandSize = commandSize;
    buffer += sizeof(RenderBundleEncoderDrawTransfer);

    RenderBundleEncoderDrawSerialize(*this, transfer, &buffer, objectIdProvider);
}

DeserializeResult RenderBundleEncoderDrawCmd::Deserialize(const volatile char** buffer, size_t* size, DeserializeAllocator* allocator, const ObjectIdResolver& resolver) {
    const volatile RenderBundleEncoderDrawTransfer* transfer = nullptr;
    DESERIALIZE_TRY(GetPtrFromBuffer(buffer, size, 1, &transfer));

    return RenderBundleEncoderDrawDeserialize(this, transfer, buffer, size, allocator, resolver);
}

    
size_t RenderBundleEncoderDrawIndexedCmd::GetRequiredSize() const {
    size_t size = sizeof(RenderBundleEncoderDrawIndexedTransfer) + RenderBundleEncoderDrawIndexedGetExtraRequiredSize(*this);
    return size;
}

void RenderBundleEncoderDrawIndexedCmd::Serialize(size_t commandSize, char* buffer, const ObjectIdProvider& objectIdProvider) const {
    auto transfer = reinterpret_cast<RenderBundleEncoderDrawIndexedTransfer*>(buffer);
    transfer->commandSize = commandSize;
    buffer += sizeof(RenderBundleEncoderDrawIndexedTransfer);

    RenderBundleEncoderDrawIndexedSerialize(*this, transfer, &buffer, objectIdProvider);
}

DeserializeResult RenderBundleEncoderDrawIndexedCmd::Deserialize(const volatile char** buffer, size_t* size, DeserializeAllocator* allocator, const ObjectIdResolver& resolver) {
    const volatile RenderBundleEncoderDrawIndexedTransfer* transfer = nullptr;
    DESERIALIZE_TRY(GetPtrFromBuffer(buffer, size, 1, &transfer));

    return RenderBundleEncoderDrawIndexedDeserialize(this, transfer, buffer, size, allocator, resolver);
}

    
size_t RenderBundleEncoderDrawIndexedIndirectCmd::GetRequiredSize() const {
    size_t size = sizeof(RenderBundleEncoderDrawIndexedIndirectTransfer) + RenderBundleEncoderDrawIndexedIndirectGetExtraRequiredSize(*this);
    return size;
}

void RenderBundleEncoderDrawIndexedIndirectCmd::Serialize(size_t commandSize, char* buffer, const ObjectIdProvider& objectIdProvider) const {
    auto transfer = reinterpret_cast<RenderBundleEncoderDrawIndexedIndirectTransfer*>(buffer);
    transfer->commandSize = commandSize;
    buffer += sizeof(RenderBundleEncoderDrawIndexedIndirectTransfer);

    RenderBundleEncoderDrawIndexedIndirectSerialize(*this, transfer, &buffer, objectIdProvider);
}

DeserializeResult RenderBundleEncoderDrawIndexedIndirectCmd::Deserialize(const volatile char** buffer, size_t* size, DeserializeAllocator* allocator, const ObjectIdResolver& resolver) {
    const volatile RenderBundleEncoderDrawIndexedIndirectTransfer* transfer = nullptr;
    DESERIALIZE_TRY(GetPtrFromBuffer(buffer, size, 1, &transfer));

    return RenderBundleEncoderDrawIndexedIndirectDeserialize(this, transfer, buffer, size, allocator, resolver);
}

    
size_t RenderBundleEncoderDrawIndirectCmd::GetRequiredSize() const {
    size_t size = sizeof(RenderBundleEncoderDrawIndirectTransfer) + RenderBundleEncoderDrawIndirectGetExtraRequiredSize(*this);
    return size;
}

void RenderBundleEncoderDrawIndirectCmd::Serialize(size_t commandSize, char* buffer, const ObjectIdProvider& objectIdProvider) const {
    auto transfer = reinterpret_cast<RenderBundleEncoderDrawIndirectTransfer*>(buffer);
    transfer->commandSize = commandSize;
    buffer += sizeof(RenderBundleEncoderDrawIndirectTransfer);

    RenderBundleEncoderDrawIndirectSerialize(*this, transfer, &buffer, objectIdProvider);
}

DeserializeResult RenderBundleEncoderDrawIndirectCmd::Deserialize(const volatile char** buffer, size_t* size, DeserializeAllocator* allocator, const ObjectIdResolver& resolver) {
    const volatile RenderBundleEncoderDrawIndirectTransfer* transfer = nullptr;
    DESERIALIZE_TRY(GetPtrFromBuffer(buffer, size, 1, &transfer));

    return RenderBundleEncoderDrawIndirectDeserialize(this, transfer, buffer, size, allocator, resolver);
}

    
size_t RenderBundleEncoderFinishCmd::GetRequiredSize() const {
    size_t size = sizeof(RenderBundleEncoderFinishTransfer) + RenderBundleEncoderFinishGetExtraRequiredSize(*this);
    return size;
}

void RenderBundleEncoderFinishCmd::Serialize(size_t commandSize, char* buffer, const ObjectIdProvider& objectIdProvider) const {
    auto transfer = reinterpret_cast<RenderBundleEncoderFinishTransfer*>(buffer);
    transfer->commandSize = commandSize;
    buffer += sizeof(RenderBundleEncoderFinishTransfer);

    RenderBundleEncoderFinishSerialize(*this, transfer, &buffer, objectIdProvider);
}

DeserializeResult RenderBundleEncoderFinishCmd::Deserialize(const volatile char** buffer, size_t* size, DeserializeAllocator* allocator, const ObjectIdResolver& resolver) {
    const volatile RenderBundleEncoderFinishTransfer* transfer = nullptr;
    DESERIALIZE_TRY(GetPtrFromBuffer(buffer, size, 1, &transfer));

    return RenderBundleEncoderFinishDeserialize(this, transfer, buffer, size, allocator, resolver);
}

    
size_t RenderBundleEncoderInsertDebugMarkerCmd::GetRequiredSize() const {
    size_t size = sizeof(RenderBundleEncoderInsertDebugMarkerTransfer) + RenderBundleEncoderInsertDebugMarkerGetExtraRequiredSize(*this);
    return size;
}

void RenderBundleEncoderInsertDebugMarkerCmd::Serialize(size_t commandSize, char* buffer, const ObjectIdProvider& objectIdProvider) const {
    auto transfer = reinterpret_cast<RenderBundleEncoderInsertDebugMarkerTransfer*>(buffer);
    transfer->commandSize = commandSize;
    buffer += sizeof(RenderBundleEncoderInsertDebugMarkerTransfer);

    RenderBundleEncoderInsertDebugMarkerSerialize(*this, transfer, &buffer, objectIdProvider);
}

DeserializeResult RenderBundleEncoderInsertDebugMarkerCmd::Deserialize(const volatile char** buffer, size_t* size, DeserializeAllocator* allocator, const ObjectIdResolver& resolver) {
    const volatile RenderBundleEncoderInsertDebugMarkerTransfer* transfer = nullptr;
    DESERIALIZE_TRY(GetPtrFromBuffer(buffer, size, 1, &transfer));

    return RenderBundleEncoderInsertDebugMarkerDeserialize(this, transfer, buffer, size, allocator, resolver);
}

    
size_t RenderBundleEncoderPopDebugGroupCmd::GetRequiredSize() const {
    size_t size = sizeof(RenderBundleEncoderPopDebugGroupTransfer) + RenderBundleEncoderPopDebugGroupGetExtraRequiredSize(*this);
    return size;
}

void RenderBundleEncoderPopDebugGroupCmd::Serialize(size_t commandSize, char* buffer, const ObjectIdProvider& objectIdProvider) const {
    auto transfer = reinterpret_cast<RenderBundleEncoderPopDebugGroupTransfer*>(buffer);
    transfer->commandSize = commandSize;
    buffer += sizeof(RenderBundleEncoderPopDebugGroupTransfer);

    RenderBundleEncoderPopDebugGroupSerialize(*this, transfer, &buffer, objectIdProvider);
}

DeserializeResult RenderBundleEncoderPopDebugGroupCmd::Deserialize(const volatile char** buffer, size_t* size, DeserializeAllocator* allocator, const ObjectIdResolver& resolver) {
    const volatile RenderBundleEncoderPopDebugGroupTransfer* transfer = nullptr;
    DESERIALIZE_TRY(GetPtrFromBuffer(buffer, size, 1, &transfer));

    return RenderBundleEncoderPopDebugGroupDeserialize(this, transfer, buffer, size, allocator, resolver);
}

    
size_t RenderBundleEncoderPushDebugGroupCmd::GetRequiredSize() const {
    size_t size = sizeof(RenderBundleEncoderPushDebugGroupTransfer) + RenderBundleEncoderPushDebugGroupGetExtraRequiredSize(*this);
    return size;
}

void RenderBundleEncoderPushDebugGroupCmd::Serialize(size_t commandSize, char* buffer, const ObjectIdProvider& objectIdProvider) const {
    auto transfer = reinterpret_cast<RenderBundleEncoderPushDebugGroupTransfer*>(buffer);
    transfer->commandSize = commandSize;
    buffer += sizeof(RenderBundleEncoderPushDebugGroupTransfer);

    RenderBundleEncoderPushDebugGroupSerialize(*this, transfer, &buffer, objectIdProvider);
}

DeserializeResult RenderBundleEncoderPushDebugGroupCmd::Deserialize(const volatile char** buffer, size_t* size, DeserializeAllocator* allocator, const ObjectIdResolver& resolver) {
    const volatile RenderBundleEncoderPushDebugGroupTransfer* transfer = nullptr;
    DESERIALIZE_TRY(GetPtrFromBuffer(buffer, size, 1, &transfer));

    return RenderBundleEncoderPushDebugGroupDeserialize(this, transfer, buffer, size, allocator, resolver);
}

    
size_t RenderBundleEncoderSetBindGroupCmd::GetRequiredSize() const {
    size_t size = sizeof(RenderBundleEncoderSetBindGroupTransfer) + RenderBundleEncoderSetBindGroupGetExtraRequiredSize(*this);
    return size;
}

void RenderBundleEncoderSetBindGroupCmd::Serialize(size_t commandSize, char* buffer, const ObjectIdProvider& objectIdProvider) const {
    auto transfer = reinterpret_cast<RenderBundleEncoderSetBindGroupTransfer*>(buffer);
    transfer->commandSize = commandSize;
    buffer += sizeof(RenderBundleEncoderSetBindGroupTransfer);

    RenderBundleEncoderSetBindGroupSerialize(*this, transfer, &buffer, objectIdProvider);
}

DeserializeResult RenderBundleEncoderSetBindGroupCmd::Deserialize(const volatile char** buffer, size_t* size, DeserializeAllocator* allocator, const ObjectIdResolver& resolver) {
    const volatile RenderBundleEncoderSetBindGroupTransfer* transfer = nullptr;
    DESERIALIZE_TRY(GetPtrFromBuffer(buffer, size, 1, &transfer));

    return RenderBundleEncoderSetBindGroupDeserialize(this, transfer, buffer, size, allocator, resolver);
}

    
size_t RenderBundleEncoderSetIndexBufferCmd::GetRequiredSize() const {
    size_t size = sizeof(RenderBundleEncoderSetIndexBufferTransfer) + RenderBundleEncoderSetIndexBufferGetExtraRequiredSize(*this);
    return size;
}

void RenderBundleEncoderSetIndexBufferCmd::Serialize(size_t commandSize, char* buffer, const ObjectIdProvider& objectIdProvider) const {
    auto transfer = reinterpret_cast<RenderBundleEncoderSetIndexBufferTransfer*>(buffer);
    transfer->commandSize = commandSize;
    buffer += sizeof(RenderBundleEncoderSetIndexBufferTransfer);

    RenderBundleEncoderSetIndexBufferSerialize(*this, transfer, &buffer, objectIdProvider);
}

DeserializeResult RenderBundleEncoderSetIndexBufferCmd::Deserialize(const volatile char** buffer, size_t* size, DeserializeAllocator* allocator, const ObjectIdResolver& resolver) {
    const volatile RenderBundleEncoderSetIndexBufferTransfer* transfer = nullptr;
    DESERIALIZE_TRY(GetPtrFromBuffer(buffer, size, 1, &transfer));

    return RenderBundleEncoderSetIndexBufferDeserialize(this, transfer, buffer, size, allocator, resolver);
}

    
size_t RenderBundleEncoderSetIndexBufferWithFormatCmd::GetRequiredSize() const {
    size_t size = sizeof(RenderBundleEncoderSetIndexBufferWithFormatTransfer) + RenderBundleEncoderSetIndexBufferWithFormatGetExtraRequiredSize(*this);
    return size;
}

void RenderBundleEncoderSetIndexBufferWithFormatCmd::Serialize(size_t commandSize, char* buffer, const ObjectIdProvider& objectIdProvider) const {
    auto transfer = reinterpret_cast<RenderBundleEncoderSetIndexBufferWithFormatTransfer*>(buffer);
    transfer->commandSize = commandSize;
    buffer += sizeof(RenderBundleEncoderSetIndexBufferWithFormatTransfer);

    RenderBundleEncoderSetIndexBufferWithFormatSerialize(*this, transfer, &buffer, objectIdProvider);
}

DeserializeResult RenderBundleEncoderSetIndexBufferWithFormatCmd::Deserialize(const volatile char** buffer, size_t* size, DeserializeAllocator* allocator, const ObjectIdResolver& resolver) {
    const volatile RenderBundleEncoderSetIndexBufferWithFormatTransfer* transfer = nullptr;
    DESERIALIZE_TRY(GetPtrFromBuffer(buffer, size, 1, &transfer));

    return RenderBundleEncoderSetIndexBufferWithFormatDeserialize(this, transfer, buffer, size, allocator, resolver);
}

    
size_t RenderBundleEncoderSetPipelineCmd::GetRequiredSize() const {
    size_t size = sizeof(RenderBundleEncoderSetPipelineTransfer) + RenderBundleEncoderSetPipelineGetExtraRequiredSize(*this);
    return size;
}

void RenderBundleEncoderSetPipelineCmd::Serialize(size_t commandSize, char* buffer, const ObjectIdProvider& objectIdProvider) const {
    auto transfer = reinterpret_cast<RenderBundleEncoderSetPipelineTransfer*>(buffer);
    transfer->commandSize = commandSize;
    buffer += sizeof(RenderBundleEncoderSetPipelineTransfer);

    RenderBundleEncoderSetPipelineSerialize(*this, transfer, &buffer, objectIdProvider);
}

DeserializeResult RenderBundleEncoderSetPipelineCmd::Deserialize(const volatile char** buffer, size_t* size, DeserializeAllocator* allocator, const ObjectIdResolver& resolver) {
    const volatile RenderBundleEncoderSetPipelineTransfer* transfer = nullptr;
    DESERIALIZE_TRY(GetPtrFromBuffer(buffer, size, 1, &transfer));

    return RenderBundleEncoderSetPipelineDeserialize(this, transfer, buffer, size, allocator, resolver);
}

    
size_t RenderBundleEncoderSetVertexBufferCmd::GetRequiredSize() const {
    size_t size = sizeof(RenderBundleEncoderSetVertexBufferTransfer) + RenderBundleEncoderSetVertexBufferGetExtraRequiredSize(*this);
    return size;
}

void RenderBundleEncoderSetVertexBufferCmd::Serialize(size_t commandSize, char* buffer, const ObjectIdProvider& objectIdProvider) const {
    auto transfer = reinterpret_cast<RenderBundleEncoderSetVertexBufferTransfer*>(buffer);
    transfer->commandSize = commandSize;
    buffer += sizeof(RenderBundleEncoderSetVertexBufferTransfer);

    RenderBundleEncoderSetVertexBufferSerialize(*this, transfer, &buffer, objectIdProvider);
}

DeserializeResult RenderBundleEncoderSetVertexBufferCmd::Deserialize(const volatile char** buffer, size_t* size, DeserializeAllocator* allocator, const ObjectIdResolver& resolver) {
    const volatile RenderBundleEncoderSetVertexBufferTransfer* transfer = nullptr;
    DESERIALIZE_TRY(GetPtrFromBuffer(buffer, size, 1, &transfer));

    return RenderBundleEncoderSetVertexBufferDeserialize(this, transfer, buffer, size, allocator, resolver);
}

    
size_t RenderPassEncoderDrawCmd::GetRequiredSize() const {
    size_t size = sizeof(RenderPassEncoderDrawTransfer) + RenderPassEncoderDrawGetExtraRequiredSize(*this);
    return size;
}

void RenderPassEncoderDrawCmd::Serialize(size_t commandSize, char* buffer, const ObjectIdProvider& objectIdProvider) const {
    auto transfer = reinterpret_cast<RenderPassEncoderDrawTransfer*>(buffer);
    transfer->commandSize = commandSize;
    buffer += sizeof(RenderPassEncoderDrawTransfer);

    RenderPassEncoderDrawSerialize(*this, transfer, &buffer, objectIdProvider);
}

DeserializeResult RenderPassEncoderDrawCmd::Deserialize(const volatile char** buffer, size_t* size, DeserializeAllocator* allocator, const ObjectIdResolver& resolver) {
    const volatile RenderPassEncoderDrawTransfer* transfer = nullptr;
    DESERIALIZE_TRY(GetPtrFromBuffer(buffer, size, 1, &transfer));

    return RenderPassEncoderDrawDeserialize(this, transfer, buffer, size, allocator, resolver);
}

    
size_t RenderPassEncoderDrawIndexedCmd::GetRequiredSize() const {
    size_t size = sizeof(RenderPassEncoderDrawIndexedTransfer) + RenderPassEncoderDrawIndexedGetExtraRequiredSize(*this);
    return size;
}

void RenderPassEncoderDrawIndexedCmd::Serialize(size_t commandSize, char* buffer, const ObjectIdProvider& objectIdProvider) const {
    auto transfer = reinterpret_cast<RenderPassEncoderDrawIndexedTransfer*>(buffer);
    transfer->commandSize = commandSize;
    buffer += sizeof(RenderPassEncoderDrawIndexedTransfer);

    RenderPassEncoderDrawIndexedSerialize(*this, transfer, &buffer, objectIdProvider);
}

DeserializeResult RenderPassEncoderDrawIndexedCmd::Deserialize(const volatile char** buffer, size_t* size, DeserializeAllocator* allocator, const ObjectIdResolver& resolver) {
    const volatile RenderPassEncoderDrawIndexedTransfer* transfer = nullptr;
    DESERIALIZE_TRY(GetPtrFromBuffer(buffer, size, 1, &transfer));

    return RenderPassEncoderDrawIndexedDeserialize(this, transfer, buffer, size, allocator, resolver);
}

    
size_t RenderPassEncoderDrawIndexedIndirectCmd::GetRequiredSize() const {
    size_t size = sizeof(RenderPassEncoderDrawIndexedIndirectTransfer) + RenderPassEncoderDrawIndexedIndirectGetExtraRequiredSize(*this);
    return size;
}

void RenderPassEncoderDrawIndexedIndirectCmd::Serialize(size_t commandSize, char* buffer, const ObjectIdProvider& objectIdProvider) const {
    auto transfer = reinterpret_cast<RenderPassEncoderDrawIndexedIndirectTransfer*>(buffer);
    transfer->commandSize = commandSize;
    buffer += sizeof(RenderPassEncoderDrawIndexedIndirectTransfer);

    RenderPassEncoderDrawIndexedIndirectSerialize(*this, transfer, &buffer, objectIdProvider);
}

DeserializeResult RenderPassEncoderDrawIndexedIndirectCmd::Deserialize(const volatile char** buffer, size_t* size, DeserializeAllocator* allocator, const ObjectIdResolver& resolver) {
    const volatile RenderPassEncoderDrawIndexedIndirectTransfer* transfer = nullptr;
    DESERIALIZE_TRY(GetPtrFromBuffer(buffer, size, 1, &transfer));

    return RenderPassEncoderDrawIndexedIndirectDeserialize(this, transfer, buffer, size, allocator, resolver);
}

    
size_t RenderPassEncoderDrawIndirectCmd::GetRequiredSize() const {
    size_t size = sizeof(RenderPassEncoderDrawIndirectTransfer) + RenderPassEncoderDrawIndirectGetExtraRequiredSize(*this);
    return size;
}

void RenderPassEncoderDrawIndirectCmd::Serialize(size_t commandSize, char* buffer, const ObjectIdProvider& objectIdProvider) const {
    auto transfer = reinterpret_cast<RenderPassEncoderDrawIndirectTransfer*>(buffer);
    transfer->commandSize = commandSize;
    buffer += sizeof(RenderPassEncoderDrawIndirectTransfer);

    RenderPassEncoderDrawIndirectSerialize(*this, transfer, &buffer, objectIdProvider);
}

DeserializeResult RenderPassEncoderDrawIndirectCmd::Deserialize(const volatile char** buffer, size_t* size, DeserializeAllocator* allocator, const ObjectIdResolver& resolver) {
    const volatile RenderPassEncoderDrawIndirectTransfer* transfer = nullptr;
    DESERIALIZE_TRY(GetPtrFromBuffer(buffer, size, 1, &transfer));

    return RenderPassEncoderDrawIndirectDeserialize(this, transfer, buffer, size, allocator, resolver);
}

    
size_t RenderPassEncoderEndPassCmd::GetRequiredSize() const {
    size_t size = sizeof(RenderPassEncoderEndPassTransfer) + RenderPassEncoderEndPassGetExtraRequiredSize(*this);
    return size;
}

void RenderPassEncoderEndPassCmd::Serialize(size_t commandSize, char* buffer, const ObjectIdProvider& objectIdProvider) const {
    auto transfer = reinterpret_cast<RenderPassEncoderEndPassTransfer*>(buffer);
    transfer->commandSize = commandSize;
    buffer += sizeof(RenderPassEncoderEndPassTransfer);

    RenderPassEncoderEndPassSerialize(*this, transfer, &buffer, objectIdProvider);
}

DeserializeResult RenderPassEncoderEndPassCmd::Deserialize(const volatile char** buffer, size_t* size, DeserializeAllocator* allocator, const ObjectIdResolver& resolver) {
    const volatile RenderPassEncoderEndPassTransfer* transfer = nullptr;
    DESERIALIZE_TRY(GetPtrFromBuffer(buffer, size, 1, &transfer));

    return RenderPassEncoderEndPassDeserialize(this, transfer, buffer, size, allocator, resolver);
}

    
size_t RenderPassEncoderExecuteBundlesCmd::GetRequiredSize() const {
    size_t size = sizeof(RenderPassEncoderExecuteBundlesTransfer) + RenderPassEncoderExecuteBundlesGetExtraRequiredSize(*this);
    return size;
}

void RenderPassEncoderExecuteBundlesCmd::Serialize(size_t commandSize, char* buffer, const ObjectIdProvider& objectIdProvider) const {
    auto transfer = reinterpret_cast<RenderPassEncoderExecuteBundlesTransfer*>(buffer);
    transfer->commandSize = commandSize;
    buffer += sizeof(RenderPassEncoderExecuteBundlesTransfer);

    RenderPassEncoderExecuteBundlesSerialize(*this, transfer, &buffer, objectIdProvider);
}

DeserializeResult RenderPassEncoderExecuteBundlesCmd::Deserialize(const volatile char** buffer, size_t* size, DeserializeAllocator* allocator, const ObjectIdResolver& resolver) {
    const volatile RenderPassEncoderExecuteBundlesTransfer* transfer = nullptr;
    DESERIALIZE_TRY(GetPtrFromBuffer(buffer, size, 1, &transfer));

    return RenderPassEncoderExecuteBundlesDeserialize(this, transfer, buffer, size, allocator, resolver);
}

    
size_t RenderPassEncoderInsertDebugMarkerCmd::GetRequiredSize() const {
    size_t size = sizeof(RenderPassEncoderInsertDebugMarkerTransfer) + RenderPassEncoderInsertDebugMarkerGetExtraRequiredSize(*this);
    return size;
}

void RenderPassEncoderInsertDebugMarkerCmd::Serialize(size_t commandSize, char* buffer, const ObjectIdProvider& objectIdProvider) const {
    auto transfer = reinterpret_cast<RenderPassEncoderInsertDebugMarkerTransfer*>(buffer);
    transfer->commandSize = commandSize;
    buffer += sizeof(RenderPassEncoderInsertDebugMarkerTransfer);

    RenderPassEncoderInsertDebugMarkerSerialize(*this, transfer, &buffer, objectIdProvider);
}

DeserializeResult RenderPassEncoderInsertDebugMarkerCmd::Deserialize(const volatile char** buffer, size_t* size, DeserializeAllocator* allocator, const ObjectIdResolver& resolver) {
    const volatile RenderPassEncoderInsertDebugMarkerTransfer* transfer = nullptr;
    DESERIALIZE_TRY(GetPtrFromBuffer(buffer, size, 1, &transfer));

    return RenderPassEncoderInsertDebugMarkerDeserialize(this, transfer, buffer, size, allocator, resolver);
}

    
size_t RenderPassEncoderPopDebugGroupCmd::GetRequiredSize() const {
    size_t size = sizeof(RenderPassEncoderPopDebugGroupTransfer) + RenderPassEncoderPopDebugGroupGetExtraRequiredSize(*this);
    return size;
}

void RenderPassEncoderPopDebugGroupCmd::Serialize(size_t commandSize, char* buffer, const ObjectIdProvider& objectIdProvider) const {
    auto transfer = reinterpret_cast<RenderPassEncoderPopDebugGroupTransfer*>(buffer);
    transfer->commandSize = commandSize;
    buffer += sizeof(RenderPassEncoderPopDebugGroupTransfer);

    RenderPassEncoderPopDebugGroupSerialize(*this, transfer, &buffer, objectIdProvider);
}

DeserializeResult RenderPassEncoderPopDebugGroupCmd::Deserialize(const volatile char** buffer, size_t* size, DeserializeAllocator* allocator, const ObjectIdResolver& resolver) {
    const volatile RenderPassEncoderPopDebugGroupTransfer* transfer = nullptr;
    DESERIALIZE_TRY(GetPtrFromBuffer(buffer, size, 1, &transfer));

    return RenderPassEncoderPopDebugGroupDeserialize(this, transfer, buffer, size, allocator, resolver);
}

    
size_t RenderPassEncoderPushDebugGroupCmd::GetRequiredSize() const {
    size_t size = sizeof(RenderPassEncoderPushDebugGroupTransfer) + RenderPassEncoderPushDebugGroupGetExtraRequiredSize(*this);
    return size;
}

void RenderPassEncoderPushDebugGroupCmd::Serialize(size_t commandSize, char* buffer, const ObjectIdProvider& objectIdProvider) const {
    auto transfer = reinterpret_cast<RenderPassEncoderPushDebugGroupTransfer*>(buffer);
    transfer->commandSize = commandSize;
    buffer += sizeof(RenderPassEncoderPushDebugGroupTransfer);

    RenderPassEncoderPushDebugGroupSerialize(*this, transfer, &buffer, objectIdProvider);
}

DeserializeResult RenderPassEncoderPushDebugGroupCmd::Deserialize(const volatile char** buffer, size_t* size, DeserializeAllocator* allocator, const ObjectIdResolver& resolver) {
    const volatile RenderPassEncoderPushDebugGroupTransfer* transfer = nullptr;
    DESERIALIZE_TRY(GetPtrFromBuffer(buffer, size, 1, &transfer));

    return RenderPassEncoderPushDebugGroupDeserialize(this, transfer, buffer, size, allocator, resolver);
}

    
size_t RenderPassEncoderSetBindGroupCmd::GetRequiredSize() const {
    size_t size = sizeof(RenderPassEncoderSetBindGroupTransfer) + RenderPassEncoderSetBindGroupGetExtraRequiredSize(*this);
    return size;
}

void RenderPassEncoderSetBindGroupCmd::Serialize(size_t commandSize, char* buffer, const ObjectIdProvider& objectIdProvider) const {
    auto transfer = reinterpret_cast<RenderPassEncoderSetBindGroupTransfer*>(buffer);
    transfer->commandSize = commandSize;
    buffer += sizeof(RenderPassEncoderSetBindGroupTransfer);

    RenderPassEncoderSetBindGroupSerialize(*this, transfer, &buffer, objectIdProvider);
}

DeserializeResult RenderPassEncoderSetBindGroupCmd::Deserialize(const volatile char** buffer, size_t* size, DeserializeAllocator* allocator, const ObjectIdResolver& resolver) {
    const volatile RenderPassEncoderSetBindGroupTransfer* transfer = nullptr;
    DESERIALIZE_TRY(GetPtrFromBuffer(buffer, size, 1, &transfer));

    return RenderPassEncoderSetBindGroupDeserialize(this, transfer, buffer, size, allocator, resolver);
}

    
size_t RenderPassEncoderSetBlendColorCmd::GetRequiredSize() const {
    size_t size = sizeof(RenderPassEncoderSetBlendColorTransfer) + RenderPassEncoderSetBlendColorGetExtraRequiredSize(*this);
    return size;
}

void RenderPassEncoderSetBlendColorCmd::Serialize(size_t commandSize, char* buffer, const ObjectIdProvider& objectIdProvider) const {
    auto transfer = reinterpret_cast<RenderPassEncoderSetBlendColorTransfer*>(buffer);
    transfer->commandSize = commandSize;
    buffer += sizeof(RenderPassEncoderSetBlendColorTransfer);

    RenderPassEncoderSetBlendColorSerialize(*this, transfer, &buffer, objectIdProvider);
}

DeserializeResult RenderPassEncoderSetBlendColorCmd::Deserialize(const volatile char** buffer, size_t* size, DeserializeAllocator* allocator, const ObjectIdResolver& resolver) {
    const volatile RenderPassEncoderSetBlendColorTransfer* transfer = nullptr;
    DESERIALIZE_TRY(GetPtrFromBuffer(buffer, size, 1, &transfer));

    return RenderPassEncoderSetBlendColorDeserialize(this, transfer, buffer, size, allocator, resolver);
}

    
size_t RenderPassEncoderSetIndexBufferCmd::GetRequiredSize() const {
    size_t size = sizeof(RenderPassEncoderSetIndexBufferTransfer) + RenderPassEncoderSetIndexBufferGetExtraRequiredSize(*this);
    return size;
}

void RenderPassEncoderSetIndexBufferCmd::Serialize(size_t commandSize, char* buffer, const ObjectIdProvider& objectIdProvider) const {
    auto transfer = reinterpret_cast<RenderPassEncoderSetIndexBufferTransfer*>(buffer);
    transfer->commandSize = commandSize;
    buffer += sizeof(RenderPassEncoderSetIndexBufferTransfer);

    RenderPassEncoderSetIndexBufferSerialize(*this, transfer, &buffer, objectIdProvider);
}

DeserializeResult RenderPassEncoderSetIndexBufferCmd::Deserialize(const volatile char** buffer, size_t* size, DeserializeAllocator* allocator, const ObjectIdResolver& resolver) {
    const volatile RenderPassEncoderSetIndexBufferTransfer* transfer = nullptr;
    DESERIALIZE_TRY(GetPtrFromBuffer(buffer, size, 1, &transfer));

    return RenderPassEncoderSetIndexBufferDeserialize(this, transfer, buffer, size, allocator, resolver);
}

    
size_t RenderPassEncoderSetIndexBufferWithFormatCmd::GetRequiredSize() const {
    size_t size = sizeof(RenderPassEncoderSetIndexBufferWithFormatTransfer) + RenderPassEncoderSetIndexBufferWithFormatGetExtraRequiredSize(*this);
    return size;
}

void RenderPassEncoderSetIndexBufferWithFormatCmd::Serialize(size_t commandSize, char* buffer, const ObjectIdProvider& objectIdProvider) const {
    auto transfer = reinterpret_cast<RenderPassEncoderSetIndexBufferWithFormatTransfer*>(buffer);
    transfer->commandSize = commandSize;
    buffer += sizeof(RenderPassEncoderSetIndexBufferWithFormatTransfer);

    RenderPassEncoderSetIndexBufferWithFormatSerialize(*this, transfer, &buffer, objectIdProvider);
}

DeserializeResult RenderPassEncoderSetIndexBufferWithFormatCmd::Deserialize(const volatile char** buffer, size_t* size, DeserializeAllocator* allocator, const ObjectIdResolver& resolver) {
    const volatile RenderPassEncoderSetIndexBufferWithFormatTransfer* transfer = nullptr;
    DESERIALIZE_TRY(GetPtrFromBuffer(buffer, size, 1, &transfer));

    return RenderPassEncoderSetIndexBufferWithFormatDeserialize(this, transfer, buffer, size, allocator, resolver);
}

    
size_t RenderPassEncoderSetPipelineCmd::GetRequiredSize() const {
    size_t size = sizeof(RenderPassEncoderSetPipelineTransfer) + RenderPassEncoderSetPipelineGetExtraRequiredSize(*this);
    return size;
}

void RenderPassEncoderSetPipelineCmd::Serialize(size_t commandSize, char* buffer, const ObjectIdProvider& objectIdProvider) const {
    auto transfer = reinterpret_cast<RenderPassEncoderSetPipelineTransfer*>(buffer);
    transfer->commandSize = commandSize;
    buffer += sizeof(RenderPassEncoderSetPipelineTransfer);

    RenderPassEncoderSetPipelineSerialize(*this, transfer, &buffer, objectIdProvider);
}

DeserializeResult RenderPassEncoderSetPipelineCmd::Deserialize(const volatile char** buffer, size_t* size, DeserializeAllocator* allocator, const ObjectIdResolver& resolver) {
    const volatile RenderPassEncoderSetPipelineTransfer* transfer = nullptr;
    DESERIALIZE_TRY(GetPtrFromBuffer(buffer, size, 1, &transfer));

    return RenderPassEncoderSetPipelineDeserialize(this, transfer, buffer, size, allocator, resolver);
}

    
size_t RenderPassEncoderSetScissorRectCmd::GetRequiredSize() const {
    size_t size = sizeof(RenderPassEncoderSetScissorRectTransfer) + RenderPassEncoderSetScissorRectGetExtraRequiredSize(*this);
    return size;
}

void RenderPassEncoderSetScissorRectCmd::Serialize(size_t commandSize, char* buffer, const ObjectIdProvider& objectIdProvider) const {
    auto transfer = reinterpret_cast<RenderPassEncoderSetScissorRectTransfer*>(buffer);
    transfer->commandSize = commandSize;
    buffer += sizeof(RenderPassEncoderSetScissorRectTransfer);

    RenderPassEncoderSetScissorRectSerialize(*this, transfer, &buffer, objectIdProvider);
}

DeserializeResult RenderPassEncoderSetScissorRectCmd::Deserialize(const volatile char** buffer, size_t* size, DeserializeAllocator* allocator, const ObjectIdResolver& resolver) {
    const volatile RenderPassEncoderSetScissorRectTransfer* transfer = nullptr;
    DESERIALIZE_TRY(GetPtrFromBuffer(buffer, size, 1, &transfer));

    return RenderPassEncoderSetScissorRectDeserialize(this, transfer, buffer, size, allocator, resolver);
}

    
size_t RenderPassEncoderSetStencilReferenceCmd::GetRequiredSize() const {
    size_t size = sizeof(RenderPassEncoderSetStencilReferenceTransfer) + RenderPassEncoderSetStencilReferenceGetExtraRequiredSize(*this);
    return size;
}

void RenderPassEncoderSetStencilReferenceCmd::Serialize(size_t commandSize, char* buffer, const ObjectIdProvider& objectIdProvider) const {
    auto transfer = reinterpret_cast<RenderPassEncoderSetStencilReferenceTransfer*>(buffer);
    transfer->commandSize = commandSize;
    buffer += sizeof(RenderPassEncoderSetStencilReferenceTransfer);

    RenderPassEncoderSetStencilReferenceSerialize(*this, transfer, &buffer, objectIdProvider);
}

DeserializeResult RenderPassEncoderSetStencilReferenceCmd::Deserialize(const volatile char** buffer, size_t* size, DeserializeAllocator* allocator, const ObjectIdResolver& resolver) {
    const volatile RenderPassEncoderSetStencilReferenceTransfer* transfer = nullptr;
    DESERIALIZE_TRY(GetPtrFromBuffer(buffer, size, 1, &transfer));

    return RenderPassEncoderSetStencilReferenceDeserialize(this, transfer, buffer, size, allocator, resolver);
}

    
size_t RenderPassEncoderSetVertexBufferCmd::GetRequiredSize() const {
    size_t size = sizeof(RenderPassEncoderSetVertexBufferTransfer) + RenderPassEncoderSetVertexBufferGetExtraRequiredSize(*this);
    return size;
}

void RenderPassEncoderSetVertexBufferCmd::Serialize(size_t commandSize, char* buffer, const ObjectIdProvider& objectIdProvider) const {
    auto transfer = reinterpret_cast<RenderPassEncoderSetVertexBufferTransfer*>(buffer);
    transfer->commandSize = commandSize;
    buffer += sizeof(RenderPassEncoderSetVertexBufferTransfer);

    RenderPassEncoderSetVertexBufferSerialize(*this, transfer, &buffer, objectIdProvider);
}

DeserializeResult RenderPassEncoderSetVertexBufferCmd::Deserialize(const volatile char** buffer, size_t* size, DeserializeAllocator* allocator, const ObjectIdResolver& resolver) {
    const volatile RenderPassEncoderSetVertexBufferTransfer* transfer = nullptr;
    DESERIALIZE_TRY(GetPtrFromBuffer(buffer, size, 1, &transfer));

    return RenderPassEncoderSetVertexBufferDeserialize(this, transfer, buffer, size, allocator, resolver);
}

    
size_t RenderPassEncoderSetViewportCmd::GetRequiredSize() const {
    size_t size = sizeof(RenderPassEncoderSetViewportTransfer) + RenderPassEncoderSetViewportGetExtraRequiredSize(*this);
    return size;
}

void RenderPassEncoderSetViewportCmd::Serialize(size_t commandSize, char* buffer, const ObjectIdProvider& objectIdProvider) const {
    auto transfer = reinterpret_cast<RenderPassEncoderSetViewportTransfer*>(buffer);
    transfer->commandSize = commandSize;
    buffer += sizeof(RenderPassEncoderSetViewportTransfer);

    RenderPassEncoderSetViewportSerialize(*this, transfer, &buffer, objectIdProvider);
}

DeserializeResult RenderPassEncoderSetViewportCmd::Deserialize(const volatile char** buffer, size_t* size, DeserializeAllocator* allocator, const ObjectIdResolver& resolver) {
    const volatile RenderPassEncoderSetViewportTransfer* transfer = nullptr;
    DESERIALIZE_TRY(GetPtrFromBuffer(buffer, size, 1, &transfer));

    return RenderPassEncoderSetViewportDeserialize(this, transfer, buffer, size, allocator, resolver);
}

    
size_t RenderPassEncoderWriteTimestampCmd::GetRequiredSize() const {
    size_t size = sizeof(RenderPassEncoderWriteTimestampTransfer) + RenderPassEncoderWriteTimestampGetExtraRequiredSize(*this);
    return size;
}

void RenderPassEncoderWriteTimestampCmd::Serialize(size_t commandSize, char* buffer, const ObjectIdProvider& objectIdProvider) const {
    auto transfer = reinterpret_cast<RenderPassEncoderWriteTimestampTransfer*>(buffer);
    transfer->commandSize = commandSize;
    buffer += sizeof(RenderPassEncoderWriteTimestampTransfer);

    RenderPassEncoderWriteTimestampSerialize(*this, transfer, &buffer, objectIdProvider);
}

DeserializeResult RenderPassEncoderWriteTimestampCmd::Deserialize(const volatile char** buffer, size_t* size, DeserializeAllocator* allocator, const ObjectIdResolver& resolver) {
    const volatile RenderPassEncoderWriteTimestampTransfer* transfer = nullptr;
    DESERIALIZE_TRY(GetPtrFromBuffer(buffer, size, 1, &transfer));

    return RenderPassEncoderWriteTimestampDeserialize(this, transfer, buffer, size, allocator, resolver);
}

    
size_t RenderPipelineGetBindGroupLayoutCmd::GetRequiredSize() const {
    size_t size = sizeof(RenderPipelineGetBindGroupLayoutTransfer) + RenderPipelineGetBindGroupLayoutGetExtraRequiredSize(*this);
    return size;
}

void RenderPipelineGetBindGroupLayoutCmd::Serialize(size_t commandSize, char* buffer, const ObjectIdProvider& objectIdProvider) const {
    auto transfer = reinterpret_cast<RenderPipelineGetBindGroupLayoutTransfer*>(buffer);
    transfer->commandSize = commandSize;
    buffer += sizeof(RenderPipelineGetBindGroupLayoutTransfer);

    RenderPipelineGetBindGroupLayoutSerialize(*this, transfer, &buffer, objectIdProvider);
}

DeserializeResult RenderPipelineGetBindGroupLayoutCmd::Deserialize(const volatile char** buffer, size_t* size, DeserializeAllocator* allocator, const ObjectIdResolver& resolver) {
    const volatile RenderPipelineGetBindGroupLayoutTransfer* transfer = nullptr;
    DESERIALIZE_TRY(GetPtrFromBuffer(buffer, size, 1, &transfer));

    return RenderPipelineGetBindGroupLayoutDeserialize(this, transfer, buffer, size, allocator, resolver);
}

    
size_t SwapChainConfigureCmd::GetRequiredSize() const {
    size_t size = sizeof(SwapChainConfigureTransfer) + SwapChainConfigureGetExtraRequiredSize(*this);
    return size;
}

void SwapChainConfigureCmd::Serialize(size_t commandSize, char* buffer, const ObjectIdProvider& objectIdProvider) const {
    auto transfer = reinterpret_cast<SwapChainConfigureTransfer*>(buffer);
    transfer->commandSize = commandSize;
    buffer += sizeof(SwapChainConfigureTransfer);

    SwapChainConfigureSerialize(*this, transfer, &buffer, objectIdProvider);
}

DeserializeResult SwapChainConfigureCmd::Deserialize(const volatile char** buffer, size_t* size, DeserializeAllocator* allocator, const ObjectIdResolver& resolver) {
    const volatile SwapChainConfigureTransfer* transfer = nullptr;
    DESERIALIZE_TRY(GetPtrFromBuffer(buffer, size, 1, &transfer));

    return SwapChainConfigureDeserialize(this, transfer, buffer, size, allocator, resolver);
}

    
size_t SwapChainGetCurrentTextureViewCmd::GetRequiredSize() const {
    size_t size = sizeof(SwapChainGetCurrentTextureViewTransfer) + SwapChainGetCurrentTextureViewGetExtraRequiredSize(*this);
    return size;
}

void SwapChainGetCurrentTextureViewCmd::Serialize(size_t commandSize, char* buffer, const ObjectIdProvider& objectIdProvider) const {
    auto transfer = reinterpret_cast<SwapChainGetCurrentTextureViewTransfer*>(buffer);
    transfer->commandSize = commandSize;
    buffer += sizeof(SwapChainGetCurrentTextureViewTransfer);

    SwapChainGetCurrentTextureViewSerialize(*this, transfer, &buffer, objectIdProvider);
}

DeserializeResult SwapChainGetCurrentTextureViewCmd::Deserialize(const volatile char** buffer, size_t* size, DeserializeAllocator* allocator, const ObjectIdResolver& resolver) {
    const volatile SwapChainGetCurrentTextureViewTransfer* transfer = nullptr;
    DESERIALIZE_TRY(GetPtrFromBuffer(buffer, size, 1, &transfer));

    return SwapChainGetCurrentTextureViewDeserialize(this, transfer, buffer, size, allocator, resolver);
}

    
size_t SwapChainPresentCmd::GetRequiredSize() const {
    size_t size = sizeof(SwapChainPresentTransfer) + SwapChainPresentGetExtraRequiredSize(*this);
    return size;
}

void SwapChainPresentCmd::Serialize(size_t commandSize, char* buffer, const ObjectIdProvider& objectIdProvider) const {
    auto transfer = reinterpret_cast<SwapChainPresentTransfer*>(buffer);
    transfer->commandSize = commandSize;
    buffer += sizeof(SwapChainPresentTransfer);

    SwapChainPresentSerialize(*this, transfer, &buffer, objectIdProvider);
}

DeserializeResult SwapChainPresentCmd::Deserialize(const volatile char** buffer, size_t* size, DeserializeAllocator* allocator, const ObjectIdResolver& resolver) {
    const volatile SwapChainPresentTransfer* transfer = nullptr;
    DESERIALIZE_TRY(GetPtrFromBuffer(buffer, size, 1, &transfer));

    return SwapChainPresentDeserialize(this, transfer, buffer, size, allocator, resolver);
}

    
size_t TextureCreateViewCmd::GetRequiredSize() const {
    size_t size = sizeof(TextureCreateViewTransfer) + TextureCreateViewGetExtraRequiredSize(*this);
    return size;
}

void TextureCreateViewCmd::Serialize(size_t commandSize, char* buffer, const ObjectIdProvider& objectIdProvider) const {
    auto transfer = reinterpret_cast<TextureCreateViewTransfer*>(buffer);
    transfer->commandSize = commandSize;
    buffer += sizeof(TextureCreateViewTransfer);

    TextureCreateViewSerialize(*this, transfer, &buffer, objectIdProvider);
}

DeserializeResult TextureCreateViewCmd::Deserialize(const volatile char** buffer, size_t* size, DeserializeAllocator* allocator, const ObjectIdResolver& resolver) {
    const volatile TextureCreateViewTransfer* transfer = nullptr;
    DESERIALIZE_TRY(GetPtrFromBuffer(buffer, size, 1, &transfer));

    return TextureCreateViewDeserialize(this, transfer, buffer, size, allocator, resolver);
}

    
size_t TextureDestroyCmd::GetRequiredSize() const {
    size_t size = sizeof(TextureDestroyTransfer) + TextureDestroyGetExtraRequiredSize(*this);
    return size;
}

void TextureDestroyCmd::Serialize(size_t commandSize, char* buffer, const ObjectIdProvider& objectIdProvider) const {
    auto transfer = reinterpret_cast<TextureDestroyTransfer*>(buffer);
    transfer->commandSize = commandSize;
    buffer += sizeof(TextureDestroyTransfer);

    TextureDestroySerialize(*this, transfer, &buffer, objectIdProvider);
}

DeserializeResult TextureDestroyCmd::Deserialize(const volatile char** buffer, size_t* size, DeserializeAllocator* allocator, const ObjectIdResolver& resolver) {
    const volatile TextureDestroyTransfer* transfer = nullptr;
    DESERIALIZE_TRY(GetPtrFromBuffer(buffer, size, 1, &transfer));

    return TextureDestroyDeserialize(this, transfer, buffer, size, allocator, resolver);
}


    
size_t ReturnBufferMapAsyncCallbackCmd::GetRequiredSize() const {
    size_t size = sizeof(ReturnBufferMapAsyncCallbackTransfer) + ReturnBufferMapAsyncCallbackGetExtraRequiredSize(*this);
    return size;
}

void ReturnBufferMapAsyncCallbackCmd::Serialize(size_t commandSize, char* buffer) const {
    auto transfer = reinterpret_cast<ReturnBufferMapAsyncCallbackTransfer*>(buffer);
    transfer->commandSize = commandSize;
    buffer += sizeof(ReturnBufferMapAsyncCallbackTransfer);

    ReturnBufferMapAsyncCallbackSerialize(*this, transfer, &buffer);
}

DeserializeResult ReturnBufferMapAsyncCallbackCmd::Deserialize(const volatile char** buffer, size_t* size, DeserializeAllocator* allocator) {
    const volatile ReturnBufferMapAsyncCallbackTransfer* transfer = nullptr;
    DESERIALIZE_TRY(GetPtrFromBuffer(buffer, size, 1, &transfer));

    return ReturnBufferMapAsyncCallbackDeserialize(this, transfer, buffer, size, allocator);
}

    
size_t ReturnDeviceCreateReadyComputePipelineCallbackCmd::GetRequiredSize() const {
    size_t size = sizeof(ReturnDeviceCreateReadyComputePipelineCallbackTransfer) + ReturnDeviceCreateReadyComputePipelineCallbackGetExtraRequiredSize(*this);
    return size;
}

void ReturnDeviceCreateReadyComputePipelineCallbackCmd::Serialize(size_t commandSize, char* buffer) const {
    auto transfer = reinterpret_cast<ReturnDeviceCreateReadyComputePipelineCallbackTransfer*>(buffer);
    transfer->commandSize = commandSize;
    buffer += sizeof(ReturnDeviceCreateReadyComputePipelineCallbackTransfer);

    ReturnDeviceCreateReadyComputePipelineCallbackSerialize(*this, transfer, &buffer);
}

DeserializeResult ReturnDeviceCreateReadyComputePipelineCallbackCmd::Deserialize(const volatile char** buffer, size_t* size, DeserializeAllocator* allocator) {
    const volatile ReturnDeviceCreateReadyComputePipelineCallbackTransfer* transfer = nullptr;
    DESERIALIZE_TRY(GetPtrFromBuffer(buffer, size, 1, &transfer));

    return ReturnDeviceCreateReadyComputePipelineCallbackDeserialize(this, transfer, buffer, size, allocator);
}

    
size_t ReturnDeviceCreateReadyRenderPipelineCallbackCmd::GetRequiredSize() const {
    size_t size = sizeof(ReturnDeviceCreateReadyRenderPipelineCallbackTransfer) + ReturnDeviceCreateReadyRenderPipelineCallbackGetExtraRequiredSize(*this);
    return size;
}

void ReturnDeviceCreateReadyRenderPipelineCallbackCmd::Serialize(size_t commandSize, char* buffer) const {
    auto transfer = reinterpret_cast<ReturnDeviceCreateReadyRenderPipelineCallbackTransfer*>(buffer);
    transfer->commandSize = commandSize;
    buffer += sizeof(ReturnDeviceCreateReadyRenderPipelineCallbackTransfer);

    ReturnDeviceCreateReadyRenderPipelineCallbackSerialize(*this, transfer, &buffer);
}

DeserializeResult ReturnDeviceCreateReadyRenderPipelineCallbackCmd::Deserialize(const volatile char** buffer, size_t* size, DeserializeAllocator* allocator) {
    const volatile ReturnDeviceCreateReadyRenderPipelineCallbackTransfer* transfer = nullptr;
    DESERIALIZE_TRY(GetPtrFromBuffer(buffer, size, 1, &transfer));

    return ReturnDeviceCreateReadyRenderPipelineCallbackDeserialize(this, transfer, buffer, size, allocator);
}

    
size_t ReturnDeviceLostCallbackCmd::GetRequiredSize() const {
    size_t size = sizeof(ReturnDeviceLostCallbackTransfer) + ReturnDeviceLostCallbackGetExtraRequiredSize(*this);
    return size;
}

void ReturnDeviceLostCallbackCmd::Serialize(size_t commandSize, char* buffer) const {
    auto transfer = reinterpret_cast<ReturnDeviceLostCallbackTransfer*>(buffer);
    transfer->commandSize = commandSize;
    buffer += sizeof(ReturnDeviceLostCallbackTransfer);

    ReturnDeviceLostCallbackSerialize(*this, transfer, &buffer);
}

DeserializeResult ReturnDeviceLostCallbackCmd::Deserialize(const volatile char** buffer, size_t* size, DeserializeAllocator* allocator) {
    const volatile ReturnDeviceLostCallbackTransfer* transfer = nullptr;
    DESERIALIZE_TRY(GetPtrFromBuffer(buffer, size, 1, &transfer));

    return ReturnDeviceLostCallbackDeserialize(this, transfer, buffer, size, allocator);
}

    
size_t ReturnDevicePopErrorScopeCallbackCmd::GetRequiredSize() const {
    size_t size = sizeof(ReturnDevicePopErrorScopeCallbackTransfer) + ReturnDevicePopErrorScopeCallbackGetExtraRequiredSize(*this);
    return size;
}

void ReturnDevicePopErrorScopeCallbackCmd::Serialize(size_t commandSize, char* buffer) const {
    auto transfer = reinterpret_cast<ReturnDevicePopErrorScopeCallbackTransfer*>(buffer);
    transfer->commandSize = commandSize;
    buffer += sizeof(ReturnDevicePopErrorScopeCallbackTransfer);

    ReturnDevicePopErrorScopeCallbackSerialize(*this, transfer, &buffer);
}

DeserializeResult ReturnDevicePopErrorScopeCallbackCmd::Deserialize(const volatile char** buffer, size_t* size, DeserializeAllocator* allocator) {
    const volatile ReturnDevicePopErrorScopeCallbackTransfer* transfer = nullptr;
    DESERIALIZE_TRY(GetPtrFromBuffer(buffer, size, 1, &transfer));

    return ReturnDevicePopErrorScopeCallbackDeserialize(this, transfer, buffer, size, allocator);
}

    
size_t ReturnDeviceUncapturedErrorCallbackCmd::GetRequiredSize() const {
    size_t size = sizeof(ReturnDeviceUncapturedErrorCallbackTransfer) + ReturnDeviceUncapturedErrorCallbackGetExtraRequiredSize(*this);
    return size;
}

void ReturnDeviceUncapturedErrorCallbackCmd::Serialize(size_t commandSize, char* buffer) const {
    auto transfer = reinterpret_cast<ReturnDeviceUncapturedErrorCallbackTransfer*>(buffer);
    transfer->commandSize = commandSize;
    buffer += sizeof(ReturnDeviceUncapturedErrorCallbackTransfer);

    ReturnDeviceUncapturedErrorCallbackSerialize(*this, transfer, &buffer);
}

DeserializeResult ReturnDeviceUncapturedErrorCallbackCmd::Deserialize(const volatile char** buffer, size_t* size, DeserializeAllocator* allocator) {
    const volatile ReturnDeviceUncapturedErrorCallbackTransfer* transfer = nullptr;
    DESERIALIZE_TRY(GetPtrFromBuffer(buffer, size, 1, &transfer));

    return ReturnDeviceUncapturedErrorCallbackDeserialize(this, transfer, buffer, size, allocator);
}

    
size_t ReturnFenceOnCompletionCallbackCmd::GetRequiredSize() const {
    size_t size = sizeof(ReturnFenceOnCompletionCallbackTransfer) + ReturnFenceOnCompletionCallbackGetExtraRequiredSize(*this);
    return size;
}

void ReturnFenceOnCompletionCallbackCmd::Serialize(size_t commandSize, char* buffer) const {
    auto transfer = reinterpret_cast<ReturnFenceOnCompletionCallbackTransfer*>(buffer);
    transfer->commandSize = commandSize;
    buffer += sizeof(ReturnFenceOnCompletionCallbackTransfer);

    ReturnFenceOnCompletionCallbackSerialize(*this, transfer, &buffer);
}

DeserializeResult ReturnFenceOnCompletionCallbackCmd::Deserialize(const volatile char** buffer, size_t* size, DeserializeAllocator* allocator) {
    const volatile ReturnFenceOnCompletionCallbackTransfer* transfer = nullptr;
    DESERIALIZE_TRY(GetPtrFromBuffer(buffer, size, 1, &transfer));

    return ReturnFenceOnCompletionCallbackDeserialize(this, transfer, buffer, size, allocator);
}

    
size_t ReturnFenceUpdateCompletedValueCmd::GetRequiredSize() const {
    size_t size = sizeof(ReturnFenceUpdateCompletedValueTransfer) + ReturnFenceUpdateCompletedValueGetExtraRequiredSize(*this);
    return size;
}

void ReturnFenceUpdateCompletedValueCmd::Serialize(size_t commandSize, char* buffer) const {
    auto transfer = reinterpret_cast<ReturnFenceUpdateCompletedValueTransfer*>(buffer);
    transfer->commandSize = commandSize;
    buffer += sizeof(ReturnFenceUpdateCompletedValueTransfer);

    ReturnFenceUpdateCompletedValueSerialize(*this, transfer, &buffer);
}

DeserializeResult ReturnFenceUpdateCompletedValueCmd::Deserialize(const volatile char** buffer, size_t* size, DeserializeAllocator* allocator) {
    const volatile ReturnFenceUpdateCompletedValueTransfer* transfer = nullptr;
    DESERIALIZE_TRY(GetPtrFromBuffer(buffer, size, 1, &transfer));

    return ReturnFenceUpdateCompletedValueDeserialize(this, transfer, buffer, size, allocator);
}


        // Implementations of serialization/deserialization of WPGUDeviceProperties.
        size_t SerializedWGPUDevicePropertiesSize(const WGPUDeviceProperties* deviceProperties) {
            return sizeof(WGPUDeviceProperties) +
                   WGPUDevicePropertiesGetExtraRequiredSize(*deviceProperties);
        }

        void SerializeWGPUDeviceProperties(const WGPUDeviceProperties* deviceProperties,
                                           char* serializeBuffer) {
            size_t devicePropertiesSize = SerializedWGPUDevicePropertiesSize(deviceProperties);
            WGPUDevicePropertiesTransfer* transfer =
                reinterpret_cast<WGPUDevicePropertiesTransfer*>(serializeBuffer);
            serializeBuffer += devicePropertiesSize;

            WGPUDevicePropertiesSerialize(*deviceProperties, transfer, &serializeBuffer);
        }

        bool DeserializeWGPUDeviceProperties(WGPUDeviceProperties* deviceProperties,
                                             const volatile char* deserializeBuffer) {
            size_t devicePropertiesSize = SerializedWGPUDevicePropertiesSize(deviceProperties);
            const volatile WGPUDevicePropertiesTransfer* transfer = nullptr;
            if (GetPtrFromBuffer(&deserializeBuffer, &devicePropertiesSize, 1, &transfer) !=
                DeserializeResult::Success) {
                return false;
            }

            return WGPUDevicePropertiesDeserialize(deviceProperties, transfer, &deserializeBuffer,
                                                   &devicePropertiesSize,
                                                   nullptr) == DeserializeResult::Success;
        }

}  // namespace dawn_wire
