#include "stdafx.h"
#include "Title.h"
#include"Game.h"
Title::Title()
{
	//SpriteInitDataに情報ぶち込んでSpriteでドローする。
	
}

Title::~Title()
{
	m_tileSprite->~Sprite();
}

bool Title::Start()
{
	TitleInit();
	return true;
}

void Title::Update()
{
	if (g_pad[0]->IsTrigger(enButtonStart))
	{
		Game* m_game = NewGO<Game>();
		DeleteGO(this);
	}
}

void Title::TitleInit()
{
	m_spriteInitData.m_width = FRAME_BUFFER_W;
	m_spriteInitData.m_height = FRAME_BUFFER_H;
	m_spriteInitData.m_ddsFilePath[0] = "Assets/image/sample_00.dds";
	//スプライトに渡しております
	m_tileSprite->Init(m_spriteInitData);
}