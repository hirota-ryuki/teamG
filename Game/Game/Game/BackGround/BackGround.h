#pragma once
class BackGround : public IGameObject
{
private:
	BackGround();
	~BackGround();
	bool Start()override;
	void Update()override;
public:
	SkinModelRender* m_bg = nullptr;				//�w�i����B
	Vector3 m_position = Vector3::Zero;				//�|�W�V�����B
	Vector3 m_scale = Vector3::Zero;				//�傫���B
	Quaternion m_rotation = Quaternion::Identity;	//��]
};
