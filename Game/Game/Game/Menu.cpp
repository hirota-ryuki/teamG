#include "stdafx.h"
#include "Menu.h"

bool Menu::Start()
{
	m_menu = NewGO<SpriteRender>(GOPrio_Sprite);
	m_menu->Init("Assets/sprite/onepiece.dds", 120.f, 50.f);
	return true;
}

void Menu::Update()
{
	//���͉����Ȃ��B
}

void Menu::OnDestroy()
{
	DeleteGO(m_menu);
}