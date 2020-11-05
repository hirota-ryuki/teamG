#include "stdafx.h"
#include "hrEngine.h"
#include "GraphicsEngine.h"

HrEngine* g_engine = nullptr;

HrEngine::~HrEngine()
{
	if (m_graphicsEngine) {
		delete m_graphicsEngine;
	}
}
void HrEngine::Init(HWND hwnd, UINT frameBufferWidth, UINT frameBufferHeight)
{
	//グラフィックエンジンの初期化。
	m_graphicsEngine = new GraphicsEngine();
	m_graphicsEngine->Init(hwnd, frameBufferWidth, frameBufferHeight);
	//ゲームパッドの初期化。
	for (int i = 0; i < GamePad::CONNECT_PAD_MAX; i++) {
		g_pad[i] = &m_pad[i];
	}
}
void HrEngine::BeginFrame()
{
	m_graphicsEngine->BeginRender();
	for (auto& pad : m_pad) {
		pad.BeginFrame();
		pad.Update();
	}
}
void HrEngine::EndFrame()
{
	m_graphicsEngine->EndRender();
}