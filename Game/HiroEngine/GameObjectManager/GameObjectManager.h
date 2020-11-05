#pragma once
#include "util/Util.h"
#include <list>

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
	/// <summary>
	/// GameObject�̊J�n�֐��ƍX�V�֐��B
	/// </summary>
	void StartAndUpdate();
private:
	///
	///	�Q�[���I�u�W�F�N�g�̖��O�L�[���쐬�B
	///
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
private:
	//�x�N�^�͐V��������ʂō��z����X�V���Ă������A
	//���X�g�͓����������Ă����̂ō���̏ꍇ�̓��X�g�̂ق����ǂ��B
	std::list< IGameObject* > m_goList[GOPrio_num];	//�Q�[���I�u�W�F�N�g�̃��X�g�B
	std::list< IGameObject* > m_DeleteGOList;		//�폜�\��̃Q�[���I�u�W�F�N�g�̃��X�g�B
	bool		m_isPause = false;					//�ꎞ��~�p�̐^�U�B
};

template <class T>
static inline T* NewGO(int prio, const char* objectName = nullptr)
{
	return GameObjectManager::GetInstance().NewGO<T>(prio, objectName);
}