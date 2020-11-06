#pragma once
#include "bulletPhysics/src/LinearMath/btIDebugDraw.h"
#include "Shader.h"

class DebugWireframe :
	public btIDebugDraw
{
public:
	DebugWireframe();
	~DebugWireframe();
	/// <summary>
	/// �f�B�X�N���v�^�q�[�v�̏������B
	/// </summary>
	void InitDescriptorHeap();
	/// <summary>
	/// �p�C�v���C���X�e�[�g�̏������B
	/// </summary>
	void InitPipelineState(RenderContext& rc);
	/// <summary>
	/// �V�F�[�_�[�̏������B
	/// </summary>
	void InitSharder();
	/// <summary>
	/// �ݒ�̏���
	/// </summary>
	void Prepare();
	/// <summary>
	/// �f�o�C�X�R���e�L�X�g�ɐݒ�
	/// 1�t���[�����Ɉ��
	/// </summary>
	void Context();
	//�K�{
	/// <summary>
	/// �����ƂɈ�񂸂Ă΂��
	/// </summary>
	/// <param name="from"></param>
	/// <param name="to"></param>
	/// <param name="color"></param>
	void    drawLine(const btVector3& from, const btVector3& to, const btVector3& color) override;
	void    setDebugMode(int debugMode) override {};
	int     getDebugMode() const override 
	{
		return true;
	};

	//�������Ȃ��Ă����Ȃ� {}�@�K�v�ł���Β�`
	void    drawContactPoint(const btVector3& PointOnB, const btVector3& normalOnB, btScalar distance, int lifeTime, const btVector3& color) override {};
	void    reportErrorWarning(const char* warningString) override {};
	void    draw3dText(const btVector3& location, const char* textString) override {};
private:
	struct Vertex 
	{
		Vector3 pos;
		Vector3 color;
	};
	
	ID3D11Buffer*		m_vertexBuffer = nullptr;			//���_�o�b�t�@�B
	ID3D11Buffer*		m_constantBuffer = nullptr;			//�萔�o�b�t�@�B
	DescriptorHeap		m_descriptorHeap;		//�f�B�X�N���v�^�q�[�v�B
	RootSignature m_rootSignature;					//���[�g�V�O�l�`���B
	PipelineState m_pipelineState;		//�p�C�v���C���X�e�[�g�B


	Shader m_Vshader;	//���_�V�F�[�_�[
	Shader m_Pshader;	//�s�N�Z���V�F�[�_�[
};

