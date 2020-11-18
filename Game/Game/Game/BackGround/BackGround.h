#pragma once
class BackGround : public IGameObject
{
public:
	BackGround();
	~BackGround();
	bool Start()override;
	void Update()override;
	void InitModel();
private:
	SkinModelRender*	m_bg = nullptr;						//背景だよ。
	Vector3				m_position = { 0.0f,0.0f,0.0f };	//ポジション。
	Vector3				m_scale = {5.0f,5.0f,5.0f};			//大きさ。
	Quaternion			m_rotation = Quaternion::Identity;	//回転。
};

