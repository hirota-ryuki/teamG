#pragma once
//�R���W��������


/// <summary>
/// �R���W���������̑啪�ށB
/// </summary>
enum EnCollisionAttr{
	enCollisionAttr_Ground,
	enCollisionAttr_Character,
	enCollisionAttr_User,					//�ȉ��Ƀ��[�U�[��`�̃R���W����������ݒ肷��B
	enCollisionAttr_Map,					//�}�b�v�`�b�v�p�B
	enCollisionAttr_RigidBody,				//���̂����f���ō쐬�����Ƃ��Ɏg�p�B
	enCollisionAttr_PassingWallCharacter	//�ǂ�ʉ߂���L�����N�^�B
};