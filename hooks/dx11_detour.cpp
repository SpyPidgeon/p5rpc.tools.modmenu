#include <d3d11.h>
#include "displaystructwindow.h"

#include "backends/imgui_impl_dx11.h"
#include "backends/imgui_impl_win32.h"

extern HMODULE dll_handle;

typedef long(__stdcall* present)(IDXGISwapChain*, UINT, UINT);
present p_present;
present p_present_target;
bool get_present_pointer()
{
	DXGI_SWAP_CHAIN_DESC sd;
	ZeroMemory(&sd, sizeof(sd));
	sd.BufferCount = 2;
	sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	sd.OutputWindow = FindWindowA(NULL, "Persona 5 Royal");
	sd.SampleDesc.Count = 1;
	sd.Windowed = TRUE;
	sd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;

	IDXGISwapChain* swap_chain;
	ID3D11Device* device;

	const D3D_FEATURE_LEVEL feature_levels[] = { D3D_FEATURE_LEVEL_11_0, D3D_FEATURE_LEVEL_10_0, };
	if (D3D11CreateDeviceAndSwapChain(
		NULL,
		D3D_DRIVER_TYPE_HARDWARE,
		NULL,
		0,
		feature_levels,
		2,
		D3D11_SDK_VERSION,
		&sd,
		&swap_chain,
		&device,
		nullptr,
		nullptr) == S_OK)
	{
		void** p_vtable = *reinterpret_cast<void***>(swap_chain);
		swap_chain->Release();
		device->Release();
		//context->Release();
		p_present_target = (present)p_vtable[8];
		return true;
	}
	return false;
}

bool init = false;
bool fetchContext = true;
HWND window = NULL;
ID3D11Device* p_device = NULL;
ID3D11DeviceContext* p_context = NULL;
ID3D11RenderTargetView* mainRenderTargetView = NULL;

WNDPROC oWndProc;
extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
LRESULT __stdcall WndProc(const HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {

	auto context = ImGui::GetCurrentContext();

	switch (uMsg)
	{
	case WM_KILLFOCUS:
		if (context != nullptr) ImGui::DestroyContext();

		p_device = nullptr;
		p_context = nullptr;

		if (mainRenderTargetView != nullptr) mainRenderTargetView->Release();
		mainRenderTargetView = nullptr;
		fetchContext = false;
		return CallWindowProc(oWndProc, hWnd, uMsg, wParam, lParam);
	}

	if (init && context != nullptr)
	{
		ImGui_ImplWin32_WndProcHandler(hWnd, uMsg, wParam, lParam);
		return CallWindowProc(oWndProc, hWnd, uMsg, wParam, lParam);
	}

	return CallWindowProc(oWndProc, hWnd, uMsg, wParam, lParam);
}

static long __stdcall detour_present(IDXGISwapChain* p_swap_chain, UINT sync_interval, UINT flags) {

	if (p_swap_chain == nullptr)
		return p_present(p_swap_chain, sync_interval, flags);

	if (!fetchContext)
		return p_present(p_swap_chain, sync_interval, flags);

	if (!init) {
		if (SUCCEEDED(p_swap_chain->GetDevice(__uuidof(ID3D11Device), (void**)&p_device)))
		{
			if (p_device == nullptr) return p_present(p_swap_chain, sync_interval, flags);

			p_device->GetImmediateContext(&p_context);

			if (p_context == nullptr) return p_present(p_swap_chain, sync_interval, flags);

			DXGI_SWAP_CHAIN_DESC sd;
			p_swap_chain->GetDesc(&sd);

			window = sd.OutputWindow;
			ID3D11Texture2D* pBackBuffer;
			p_swap_chain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);

			if (pBackBuffer == nullptr) return p_present(p_swap_chain, sync_interval, flags);

			p_device->CreateRenderTargetView(pBackBuffer, NULL, &mainRenderTargetView);
			pBackBuffer->Release();

			if (mainRenderTargetView == nullptr) return p_present(p_swap_chain, sync_interval, flags);

			if (oWndProc == nullptr) oWndProc = (WNDPROC)SetWindowLongPtr(window, GWLP_WNDPROC, (LONG_PTR)WndProc);
			ImGui::CreateContext();

			if (ImGui::GetCurrentContext() == nullptr) return p_present(p_swap_chain, sync_interval, flags);

			ImGuiIO& io = ImGui::GetIO();
			io.ConfigFlags = ImGuiConfigFlags_NoMouseCursorChange;
			ImGui_ImplWin32_Init(window);
			ImGui_ImplDX11_Init(p_device, p_context);
			init = true;
		}
		else
			return p_present(p_swap_chain, sync_interval, flags);
	}

	if (p_context != nullptr)
	{
		ImGui_ImplDX11_NewFrame();
		ImGui_ImplWin32_NewFrame();

		ImGui::NewFrame();

		RenderStructWidgets();

		ImGui::EndFrame();
		ImGui::Render();

		p_context->OMSetRenderTargets(1, &mainRenderTargetView, NULL);
		ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
	}

	return p_present(p_swap_chain, sync_interval, flags);
}
