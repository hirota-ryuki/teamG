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
	//削除
	for (auto GO : m_DeleteGOList) {
		auto& goExecList = m_goList[GO->prio];
		//ゲームオブジェクトリストから該当のオブジェクトの箇所を探して
		auto it = std::find(goExecList.begin(), goExecList.end(), GO);
		//削除
		delete (*it);
		//ゲームオブジェクトリストから削除
		goExecList.erase(it);
	}
	m_DeleteGOList.clear();
}

void GameObjectManager::Render()
{
	//ドロー
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
	//登録されているゲームオブジェクトの更新処理を呼ぶ。
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
						//ポーズ中でなければ
						go->Update_NotPause();
					}
				}
			}

		}
	}
}

	