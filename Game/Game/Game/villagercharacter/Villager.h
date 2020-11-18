#pragma once
class Villager : public IGameObject
{
public:
	//このクラスは恐らく継承されるので、その時の関数を少しずつ書いておきます。
	void InitModel(const char* texFilePath);

private:
	bool Start()override;
	void Update()override;
	void InitModel();
private:
	SkinModelRender* m_villagerModel = nullptr;		//プレイヤーのモデル。
	CharacterController m_charaCon;					//キャラクターコントローラー。

	Vector3 m_position = Vector3::Zero;				//プレイヤーのポジション。
	Vector3 m_moveSpeed = Vector3::Zero;			//プレイヤーのスピード。

	Quaternion m_rotation = Quaternion::Identity;	//主に使う回転の変数。
	Quaternion m_rotating = Quaternion::Identity;	//モデルが動いてるとき使う回転変数。
};

