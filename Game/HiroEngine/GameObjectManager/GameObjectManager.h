#pragma once
#include "util/Util.h"
#include <list>
#include <iostream>
#include <functional>

class GameObjectManager
{
private:
	GameObjectManager();
	~GameObjectManager();
public:
	//�V���O���g���B
	static GameObjectManager& GetInstance()
	{
		static GameObjectManager instance;
		return instance;
	}
	/// <summary>
	/// �Q�[���I�u�W�F�N�g��ǉ��B
	/// </summary>
	template <class T>
	T* NewGO(int prio, const char* objectName)
	{
		(void*)objectName;
		T* newObj = new T;
		m_goList[prio].push_back(newObj);
		unsigned int hash = MakeGameObjectNameKey(objectName);
		newObj->SetNameKey(hash);
		newObj->prio = prio;
		return newObj;
	}
	/// <summary>
	/// �Q�[���I�u�W�F�N�g�����X�g����폜����B
	/// </summary>
	/// <param name="go">�폜����Q�[���I�u�W�F�N�g</param>
	void DeleteGO(IGameObject* go)
	{
		for (int i = 0; i < GOPrio_num; i++) {
			//���X�g���猟�����āA����������폜����B
			for (auto it = m_goList[i].begin(); it != m_goList[i].end(); it++) {
				if ((*it) == go) {
					if (!go->IsDelete()) {
						//���������B
						//�폜���N�G�X�g�𑗂�B
						go->SetDelete();
						m_DeleteGOList.emplace_back(go);
						go->OnDestroy();
					}
					return;
				}
			}
		}
	}
	template<class T>
	void FindGameObjects(const char* objectName, std::function<bool(T* go)> func)
	{
		unsigned int nameKey = Util::MakeHash(objectName);
		for (int i = 0; i < GOPrio_num; i++) {
			for (auto go : m_goList[i]) {
				if (go->GetNameKey() == nameKey) {
					//�������B
					T* p = dynamic_cast<T*>(go);
					if (p != nullptr) {
						if (func(p) == false) {
							//�N�G�����f�B
							return;
						}
					}
				}
			}
		}
	}
	/// <summary>
	/// �X�V�B
	/// </summary>
	void Update();
	/// <summary>
	/// GameObject����������֐��B
	/// </summary>
	void Delete();
	/// <summary>
	/// �`��B
	/// </summary>
	void Render();
	const std::list< IGameObject* >& GetListSize() const {
		return m_goList[2];
	}
private:	
	/// <summary>
	/// �Q�[���I�u�W�F�N�g�̖��O�L�[���쐬�B
	/// </summary>
	static unsigned int MakeGameObjectNameKey(const char* objectName)
	{
		static const unsigned int defaultNameKey = Util::MakeHash("Undefined");	//���O�L�[�B
		unsigned int hash;
		if (objectName == nullptr) {
			hash = defaultNameKey;
		}
		else {
			hash = Util::MakeHash(objectName);
		}
		return hash;
	}
	/// <summary>
	/// GameObject�̊J�n�֐��ƍX�V�֐��B
	/// </summary>
	void StartAndUpdate();
private:
	//�x�N�^�͐V��������ʂō��z����X�V���Ă������A
	//���X�g�͓����������Ă����̂ō���̏ꍇ�̓��X�g�̂ق����ǂ��B
	std::list< IGameObject* >	m_goList[GOPrio_num];	//�Q�[���I�u�W�F�N�g�̃��X�g�B
	std::list< IGameObject* >	m_DeleteGOList;			//�폜�\��̃Q�[���I�u�W�F�N�g�̃��X�g�B
	bool						m_isPause = false;		//�ꎞ��~�p�̐^�U�B
};

template <class T>
static inline T* NewGO(int prio = GOPrio_Defalut, const char* objectName = nullptr)
{
	return GameObjectManager::GetInstance().NewGO<T>(prio, objectName);
}

static inline void DeleteGO(IGameObject* go)
{
	return GameObjectManager::GetInstance().DeleteGO(go);
}

/*!
	*@brief	�Q�[���I�u�W�F�N�g�̌����̃w���p�[�֐��B
	*@details
	* �����̃Q�[���I�u�W�F�N�g�ɑS�Ăɑ΂��āA�N�G�����s�������ꍇ�Ɏg�p���Ă��������B
	*@param[in]	objectName	�Q�[���I�u�W�F�N�g�̖��O�B
	*@param[in]	func		�Q�[���I�u�W�F�N�g�����������Ƃ��ɌĂ΂��R�[���o�b�N�֐��B
	*/
template<class T>
static inline void QueryGOs(const char* objectName, std::function<bool(T* go)> func)
{
	return GameObjectManager::GetInstance().FindGameObjects<T>(objectName, func);
}

/*!
	*@brief	�Q�[���I�u�W�F�N�g�𖼑O�w��ō폜�B
	*@details
	* ���O�������s���邽�ߒx���ł��B
	*@param[in]	objectName		�폜����Q�[���I�u�W�F�N�g�̖��O�B
	*/
static inline void DeleteGOs(const char* objectName)
{
	QueryGOs<IGameObject>(objectName, [](auto go) {
		DeleteGO(go);
		return true;
	});
}