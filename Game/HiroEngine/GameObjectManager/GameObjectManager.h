#pragma once
#include "util/Util.h"
#include <list>

class GameObjectManager
{
private:
	GameObjectManager();
	~GameObjectManager();
public:
	//シングルトン。
	static GameObjectManager& GetInstance()
	{
		static GameObjectManager instance;
		return instance;
	}
	/// <summary>
	/// ゲームオブジェクトを追加。
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
	/// 更新。
	/// </summary>
	void Update();
	/// <summary>
	/// GameObjectを消去する関数。
	/// </summary>
	void Delete();
	/// <summary>
	/// 描画。
	/// </summary>
	void Render();
	/// <summary>
	/// GameObjectの開始関数と更新関数。
	/// </summary>
	void StartAndUpdate();
private:
	///
	///	ゲームオブジェクトの名前キーを作成。
	///
	static unsigned int MakeGameObjectNameKey(const char* objectName)
	{
		static const unsigned int defaultNameKey = Util::MakeHash("Undefined");	//名前キー。
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
	//ベクタは新しい道を別で作りつつ配列を更新していくが、
	//リストは道を延長していくので今回の場合はリストのほうが良い。
	std::list< IGameObject* > m_goList[GOPrio_num];	//ゲームオブジェクトのリスト。
	std::list< IGameObject* > m_DeleteGOList;		//削除予定のゲームオブジェクトのリスト。
	bool		m_isPause = false;					//一時停止用の真偽。
};

template <class T>
static inline T* NewGO(int prio, const char* objectName = nullptr)
{
	return GameObjectManager::GetInstance().NewGO<T>(prio, objectName);
}