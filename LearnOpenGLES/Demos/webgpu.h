/**
 * \file webgpu.h
 * WebGPU/Dawn wrapper.
 */
#pragma once

#ifdef __EMSCRIPTEN__
#include <webgpu/webgpu.h>
#else
#include <dawn/webgpu.h>
#endif


namespace webgpu {

typedef struct HandleImpl* Handle;

WGPUDevice create(Handle window, WGPUBackendType type = WGPUBackendType_Force32);

WGPUSwapChain createSwapChain(WGPUDevice device, uint32_t width, uint32_t height);

/**
 * See \c #createSwapChain();
 */
WGPUTextureFormat getSwapChainFormat(WGPUDevice device);

void destorySwapImpl(void);
}
