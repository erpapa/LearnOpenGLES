/**
 * webgpu.h
 * WebGPU/Dawn wrapper.
 */

#ifndef DAWN_WEBGPU_H_
#define DAWN_WEBGPU_H_

#ifdef __EMSCRIPTEN__
#include <webgpu/webgpu.h>
#else
#include <dawn/webgpu.h>
#endif

namespace webgpu {

typedef struct WindowHandleImpl* WindowHandle;

WGPUDevice create(WindowHandle window, WGPUBackendType type = WGPUBackendType_Force32);

WGPUQueue createDefaultQueue(WGPUDevice device);

WGPUSwapChain createSwapChain(WGPUDevice device, uint32_t width, uint32_t height);

WGPUTextureFormat getSwapChainFormat(WGPUDevice device);

void destoryDevice(WGPUDevice device);

void destoryQueue(WGPUQueue queue);

void destorySwapChain(WGPUSwapChain swapChain);

}

#endif
