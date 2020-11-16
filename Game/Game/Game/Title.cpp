#include "stdafx.h"
#include "Title.h"

Title::Title()
{
	//SpriteInitData�ɏ��Ԃ������Sprite�Ńh���[����B
	m_spriteInitData.m_width = FRAME_BUFFER_W;
	m_spriteInitData.m_height = FRAME_BUFFER_H;
	m_spriteInitData.m_ddsFilePath[0] = "Assets/image/sample_00.dds";
}

Title::~Title()
{
	m_tileSprite->~Sprite();
}

bool Title::Start()
{
	//�X�v���C�g�ɓn���Ă���܂�
	m_tileSprite->Init(m_spriteInitData);
	return true;
}

void Title::Update()
{
	if (g_pad[0]->IsTrigger(enButtonStart))
	{
		DeleteGO(this);
	}
}