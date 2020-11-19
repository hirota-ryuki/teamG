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
	SpriteInitData		m_spriteInitData;
	m_spriteInitData.m_ddsFilePath[0] = texFilePath;
}

void SpriteRender::Update()
{
	//RotMultiply();
	m_sprite.UpdateWorldMatrix(
		m_pos,
		m_rot,
		m_scale
	);
}

void SpriteRender::DrawHUD()
{
	if (m_isActive) {
		//スプライト
		CMatrix mView;
		CMatrix mProj;
		mView.MakeLookAt(
			{ 0, 0, 1 },
			{ 0, 0, 0 },
			{ 0, 1, 0 }
		);
		mProj.MakeOrthoProjectionMatrix(1280, 720, 0, 100);
		m_sprite.SetAlpha(m_alpha);
		m_sprite.Draw(mView, mProj);
	}
}