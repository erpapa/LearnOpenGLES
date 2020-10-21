
bool HandleBufferMapAsyncCallback(const volatile char** commands, size_t* size);
bool HandleDeviceCreateReadyComputePipelineCallback(const volatile char** commands, size_t* size);
bool HandleDeviceCreateReadyRenderPipelineCallback(const volatile char** commands, size_t* size);
bool HandleDeviceLostCallback(const volatile char** commands, size_t* size);
bool HandleDevicePopErrorScopeCallback(const volatile char** commands, size_t* size);
bool HandleDeviceUncapturedErrorCallback(const volatile char** commands, size_t* size);
bool HandleFenceOnCompletionCallback(const volatile char** commands, size_t* size);
bool HandleFenceUpdateCompletedValue(const volatile char** commands, size_t* size);

bool DoBufferMapAsyncCallback(Buffer* buffer, uint32_t requestSerial, uint32_t status, uint64_t readInitialDataInfoLength, uint8_t const * readInitialDataInfo);
bool DoDeviceCreateReadyComputePipelineCallback(uint64_t requestSerial, WGPUCreateReadyPipelineStatus status, char const * message);
bool DoDeviceCreateReadyRenderPipelineCallback(uint64_t requestSerial, WGPUCreateReadyPipelineStatus status, char const * message);
bool DoDeviceLostCallback(char const * message);
bool DoDevicePopErrorScopeCallback(uint64_t requestSerial, WGPUErrorType type, char const * message);
bool DoDeviceUncapturedErrorCallback(WGPUErrorType type, char const * message);
bool DoFenceOnCompletionCallback(Fence* fence, uint64_t requestSerial, WGPUFenceCompletionStatus status);
bool DoFenceUpdateCompletedValue(Fence* fence, uint64_t value);
