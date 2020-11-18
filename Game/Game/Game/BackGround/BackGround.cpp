#include "stdafx.h"
#include "BackGround.h"

BackGround::BackGround()
{
	
}

BackGround::~BackGround()
{

}

bool BackGround::Start()
{	
	InitModel();
	return true;
}

void BackGround::Update()
{
	
}

void BackGround::InitModel()
{
	m_bg = NewGO<SkinModelRender>();
	m_bg->Init("Assets/modelData/background/Model.tkm");
	m_bg->SetPos(m_position);
}