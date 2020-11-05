#include "stdafx.h"
#include "Player.h"

Player::Player()
{
	//�v���C���[�𐶐����郂�f���ƃV�F�[�_�[�̏��B
	playerInitData.m_tkmFilePath = "Assets/modelData/unityChan.tkm";
	playerInitData.m_fxFilePath = "Assets/shader/model.fx";
	//���f���ɂԂ����ނ��B
	playerModel.Init(playerInitData);
}

Player::~Player()
{
}

bool Player::Start()
{
	return true;
}
//�X�V�֐�
void Player::Update()
{
	RenderUpdate();
}
//�`��X�V�֐��B��ɏ�����\����B
void Player::RenderUpdate()
{
	playerModel.UpdateWorldMatrix({ -50.0f, 0.0f, 0.0f }, g_quatIdentity, g_vec3One);
}
//�ړ��������������֐��B
void Player::MoveOperation()
{
	float ZERO = 0.0f;
	//stick�̓��͂ɍ��킹�ē����܂��B
	float lStick_x = (g_pad[0]->GetLStickXF());
	float lStick_z = (g_pad[0]->GetLStickYF());
	//�J�����̑O������
	cameraForward = g_camera3D->GetForward();
	cameraRight = g_camera3D->GetRight();
	//XZ���ʂł̑O�������A�E�����ɕϊ�
	cameraForward.y = ZERO;
	cameraForward.Normalize();
	cameraRight.y = ZERO;
	cameraRight.Normalize();
	//XZ�����̈ړ����x���N���A�B
	m_moveSpeed.x = ZERO;
	m_moveSpeed.z = ZERO;
	//�ړ��B
	
}