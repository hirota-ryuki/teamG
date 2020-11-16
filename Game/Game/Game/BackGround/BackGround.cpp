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
	const Vector3 pos = {0.0f,-150.0f,0.0f};	//仮置き場。
	m_position = pos;
	m_bg = NewGO<SkinModelRender>();
	//モデルドローしてます。
	m_bg->Init("Assets/modelData/unityChan.tkm");
	//m_bg->Init("Assets/modelData/background/karimodel.tkm");
	m_bg->SetPos(m_position);
	return true;
}

void BackGround::Update()
{
	
}