#include "stdafx.h"
#include "GameObjectManager.h"

GameObjectManager::GameObjectManager()
{
}

GameObjectManager::~GameObjectManager()
{
}

void GameObjectManager::Update()
{
	StartAndUpdate();

	Render();

	Delete();
}

void GameObjectManager::Delete()
{
	//�폜
	for (auto GO : m_DeleteGOList) {
		auto& goExecList = m_goList[GO->prio];
		//�Q�[���I�u�W�F�N�g���X�g����Y���̃I�u�W�F�N�g�̉ӏ���T����
		auto it = std::find(goExecList.begin(), goExecList.end(), GO);
		//�폜
		delete (*it);
		//�Q�[���I�u�W�F�N�g���X�g����폜
		goExecList.erase(it);
	}
	m_DeleteGOList.clear();
}

void GameObjectManager::Render()
{
	//�h���[
	for (int i = 0; i < GOPrio_num; i++) {
		for (auto go : m_goList[i]) {
			if (!go->m_isDelete) {
				go->Draw();
			}
		}
	}
}

void GameObjectManager::StartAndUpdate()
{
	//�o�^����Ă���Q�[���I�u�W�F�N�g�̍X�V�������ĂԁB
	for (int i = 0; i < GOPrio_num; i++) {
		for (auto go : m_goList[i]) {
			if (!go->IsStart()) {
				if (go->Start()) {
					go->StartEnd();
				}
			}
			else {
				if (!go->m_isDelete) {
					go->Update();
					if (!m_isPause) {
						//�|�[�Y���łȂ����
						go->Update_NotPause();
					}
				}
			}

		}
	}
}

	