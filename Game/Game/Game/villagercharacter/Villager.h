#pragma once
class Villager : public IGameObject
{
public:
	//���̃N���X�͋��炭�p�������̂ŁA���̎��̊֐��������������Ă����܂��B
	void InitModel(const char* texFilePath);

private:
	bool Start()override;
	void Update()override;
	void InitModel();
private:
	SkinModelRender* m_villagerModel = nullptr;		//�v���C���[�̃��f���B
	CharacterController m_charaCon;					//�L�����N�^�[�R���g���[���[�B

	Vector3 m_position = Vector3::Zero;				//�v���C���[�̃|�W�V�����B
	Vector3 m_moveSpeed = Vector3::Zero;			//�v���C���[�̃X�s�[�h�B

	Quaternion m_rotation = Quaternion::Identity;	//��Ɏg����]�̕ϐ��B
	Quaternion m_rotating = Quaternion::Identity;	//���f���������Ă�Ƃ��g����]�ϐ��B
};

