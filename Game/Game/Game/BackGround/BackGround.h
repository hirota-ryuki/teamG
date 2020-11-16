#pragma once
class BackGround : public IGameObject
{
public:
	BackGround();
	~BackGround();
	bool Start()override;
	void Update()override;
private:
	SkinModelRender* m_bg = nullptr;				//背景だよ。
	Vector3 m_position = Vector3::Zero;				//ポジション。
	Vector3 m_scale = Vector3::Zero;				//大きさ。
	Quaternion m_rotation = Quaternion::Identity;	//回転
};

