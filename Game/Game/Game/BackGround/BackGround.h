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
	SkinModelRender*	m_bg = nullptr;						//�w�i����B
	Vector3				m_position = { 0.0f,0.0f,0.0f };	//�|�W�V�����B
	Vector3				m_scale = {5.0f,5.0f,5.0f};			//�傫���B
	Quaternion			m_rotation = Quaternion::Identity;	//��]�B
};

