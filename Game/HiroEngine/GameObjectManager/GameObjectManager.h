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
	/// ゲームオブジェクトをリストから削除する。
	/// </summary>
	/// <param name="go">削除するゲームオブジェクト</param>
	void DeleteGO(IGameObject* go)
	{
		for (int i = 0; i < GOPrio_num; i++) {
			//リストから検索して、見つかったら削除する。
			for (auto it = m_goList[i].begin(); it != m_goList[i].end(); it++) {
				if ((*it) == go) {
					if (!go->IsDelete()) {
						//見つかった。
						//削除リクエストを送る。
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
					//見つけた。
					T* p = dynamic_cast<T*>(go);
					if (p != nullptr) {
						if (func(p) == false) {
							//クエリ中断。
							return;
						}
					}
				}
			}
		}
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
	const std::list< IGameObject* >& GetListSize() const {
		return m_goList[2];
	}
private:	
	/// <summary>
	/// ゲームオブジェクトの名前キーを作成。
	/// </summary>
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
	/// <summary>
	/// GameObjectの開始関数と更新関数。
	/// </summary>
	void StartAndUpdate();
private:
	//ベクタは新しい道を別で作りつつ配列を更新していくが、
	//リストは道を延長していくので今回の場合はリストのほうが良い。
	std::list< IGameObject* >	m_goList[GOPrio_num];	//ゲームオブジェクトのリスト。
	std::list< IGameObject* >	m_DeleteGOList;			//削除予定のゲームオブジェクトのリスト。
	bool						m_isPause = false;		//一時停止用の真偽。
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
	*@brief	ゲームオブジェクトの検索のヘルパー関数。
	*@details
	* 同名のゲームオブジェクトに全てに対して、クエリを行いたい場合に使用してください。
	*@param[in]	objectName	ゲームオブジェクトの名前。
	*@param[in]	func		ゲームオブジェクトが見つかったときに呼ばれるコールバック関数。
	*/
template<class T>
static inline void QueryGOs(const char* objectName, std::function<bool(T* go)> func)
{
	return GameObjectManager::GetInstance().FindGameObjects<T>(objectName, func);
}

/*!
	*@brief	ゲームオブジェクトを名前指定で削除。
	*@details
	* 名前検索が行われるため遅いです。
	*@param[in]	objectName		削除するゲームオブジェクトの名前。
	*/
static inline void DeleteGOs(const char* objectName)
{
	QueryGOs<IGameObject>(objectName, [](auto go) {
		DeleteGO(go);
		return true;
	});
}