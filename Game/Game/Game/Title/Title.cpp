#include "stdafx.h"
#include "Title.h"
#include"Game.h"
Title::Title()
{
	
}

Title::~Title()
{
}

bool Title::Start()
{
	TitleInit();
	return true;
}

void Title::Update()
{
	TitleState();
}
//生成。
void Title::TitleInit()
{
	m_title = NewGO<SpriteRender>(GOPrio_Sprite);
	m_title->Init("Assets/image/KARI.dds", FRAME_BUFFER_W, FRAME_BUFFER_H);
}

void Title::OnDestroy()
{
	DeleteGO(m_title);
}

void Title::TitleState()
{
	//Game生成と削除を同時にしないように。
	switch (isGameStart_flag)
	{
	case false:
		if (g_pad[0]->IsTrigger(enButtonA))
		{
			Game* m_game = NewGO<Game>();
			isGameStart_flag = true;
		}
		break;
	case true:
		DeleteGO(this);
		break;
	}
}