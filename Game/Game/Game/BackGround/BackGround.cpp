#include "stdafx.h"
#include "BackGround.h"

BackGround::BackGround()
{
	const Vector3 pos = {0.0f,-150.0f,0.0f};	//���u����B
	m_position = pos;
}

BackGround::~BackGround()
{

}

bool BackGround::Start()
{
	m_bg = NewGO<SkinModelRender>();
	//���f���h���[���Ă܂��B
	m_bg->Init("Assets/modelData/background/karimodel.tkm");
	m_bg->SetPos(m_position);
	return true;
}

void BackGround::Update()
{
	
}