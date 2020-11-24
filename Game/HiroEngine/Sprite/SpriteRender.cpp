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
	spriteInitData.m_fxFilePath = "Assets/shader/sprite.fx";
	spriteInitData.m_width = w;
	spriteInitData.m_height = h;
	//ディレクションライト
	DirectionalLight light;
	light.direction.x = 0.0f;
	light.direction.y = 0.0f;
	light.direction.z = 0.0f;
	light.direction.Normalize();

	light.color.x = 1.0f;
	light.color.y = 1.0f;
	light.color.z = 1.0f;
	light.eyePos = g_camera3D->GetPosition();
	spriteInitData.m_expandConstantBuffer = &light;
	spriteInitData.m_expandConstantBufferSize = sizeof(light);
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