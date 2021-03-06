#include "stdafx.h"
#include "SpriteRender.h"

SpriteRender::SpriteRender()
{
}

SpriteRender::~SpriteRender()
{
}

bool SpriteRender::Start()
{
	return true;
}

void SpriteRender::Init(const char* texFilePath, float w, float h)
{
	SpriteInitData	spriteInitData;
	spriteInitData.m_ddsFilePath[0] = texFilePath;
	spriteInitData.m_fxFilePath = "Assets/shader/spriterender.fx";
	spriteInitData.m_width = w;
	spriteInitData.m_height = h;
	m_sprite.Init(spriteInitData);
}

void SpriteRender::Update()
{
	//RotMultiply();
	m_sprite.Update(
		m_pos,
		m_rot,
		m_scale
	);
}

void SpriteRender::DrawHUD()
{
	if (m_isActive) {
		m_sprite.SetAlpha(m_alpha);
		auto& rc = g_graphicsEngine->GetRenderContext();
		m_sprite.Draw(rc);
	}
}