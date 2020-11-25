#include "stdafx.h"
#include "Villager.h"

bool Villager::Start()
{
	m_position += { 0.0f,0.0f,150.0f };
	InitModel();
	//���u����B
	return true;
}

void Villager::Update()
{
	m_position = m_charaCon.Execute(1.f / 60.f, m_moveSpeed);
}
//���͌p�����ĂȂ��̂ł�������g���Ă܂��B
void Villager::InitModel()
{
	m_villagerModel = NewGO<SkinModelRender>();
	m_villagerModel->Init("Assets/modelData/unityChan.tkm");
	m_villagerModel->SetPos(m_position);
	m_charaCon.Init(40.f, 75.f, m_position);
}
//�p���������Ɏg���\��ł���B
void Villager::InitModel(const char* texFilePath)
{
	m_villagerModel = NewGO<SkinModelRender>();
	m_villagerModel->Init(texFilePath);
	m_villagerModel->SetPos(m_position);
}

void Villager::OnDestroy()
{
	DeleteGO(m_villagerModel);
}
