#include "stdafx.h"
#include "Villager.h"

bool Villager::Start()
{
	InitModel();
	//仮置き場。
	return true;
}

void Villager::Update()
{
	m_position = m_charaCon.Execute(1.f / 60.f, m_moveSpeed);
}
//今は継承してないのでこちらを使ってます。
void Villager::InitModel()
{
	m_villagerModel = NewGO<SkinModelRender>();
	m_villagerModel->Init("Assets/modelData/unityChan.tkm");
	m_position;
	m_villagerModel->SetPos(m_position);
}
//継承した時に使う予定である。
void Villager::InitModel(const char* texFilePath)
{
	m_villagerModel = NewGO<SkinModelRender>();
	m_villagerModel->Init(texFilePath);
	m_villagerModel->SetPos(m_position);
}
