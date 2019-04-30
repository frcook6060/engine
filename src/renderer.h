#pragma once



#define SAFE_RELEASE(d) if(d) { d->Release(); } 

void rend_init();

void rend_release();


void rend_clear(const glm::vec4& color, float depth);

void rend_clearColor(const glm::vec4& color);
void rend_clearDepth(float depth);

void rend_present();

IDXGISwapChain* rend_getSwapChain();
ID3D11Device* rend_getDevice();
ID3D11DeviceContext* rend_getContext();

