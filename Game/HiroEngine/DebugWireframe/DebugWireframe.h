#pragma once
#include "LinearMath/btIDebugDraw.h"
#include "Shader.h"

class DebugWireframe :
	public btIDebugDraw
{
public:
	DebugWireframe();
	~DebugWireframe();
	/// <summary>
	/// �������B	
	/// </summary>
	void Init();
	/// <summary>
	/// �f�B�X�N���v�^�q�[�v�̏������B
	/// </summary>
	void InitDescriptorHeap();
	/// <summary>
	/// 2���_���L�^����萔�o�b�t�@�̏������B
	/// </summary>
	void InitVertexCBuffer();
	/// <summary>
	/// �萔�o�b�t�@�̏������B
	/// </summary>
	void InitConstantBuffer();
	/// <summary>
	/// �p�C�v���C���X�e�[�g�̏������B
	/// </summary>
	void InitPipelineState();
	/// <summary>
	/// �V�F�[�_�[�̏������B
	/// </summary>
	void InitSharder();
	/// <summary>
	/// ���[�g�V�O�l�`���̏������B
	/// </summary>
	void InitRootSignature();
	/// <summary>
	/// 2���_���L�^����萔�o�b�t�@�̍X�V�B
	/// </summary>
	void VertexCBufferUpdate(const btVector3& from, const btVector3& to, const btVector3& color);
	/// <summary>
	/// �萔�o�b�t�@�̍X�V�B
	/// </summary>
	void ConstantBufferUpdate();
	/// <summary>
	/// �ݒ�̏���
	/// </summary>
	void Prepare();
	/// <summary>
	/// �f�o�C�X�R���e�L�X�g�ɐݒ�
	/// 1�t���[�����Ɉ��
	/// </summary>
	void Context();
	/// �K�{
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
	
	ConstantBuffer		m_constantBuffer;			//�萔�o�b�t�@�B
	ConstantBuffer		m_vertexCBuffer;			//2���_���L�^����萔�o�b�t�@�B���_�o�b�t�@(VertexBuffer)�ł͂Ȃ��B
	RootSignature		m_rootSignature;			//���[�g�V�O�l�`���B
	Shader				m_Vshader;					//���_�V�F�[�_�[�B
	Shader				m_Pshader;					//�s�N�Z���V�F�[�_�[�B
	PipelineState		m_pipelineState;			//�p�C�v���C���X�e�[�g�B
	DescriptorHeap		m_descriptorHeap;			//�f�B�X�N���v�^�q�[�v�B	
	const int			NUM_VERTEX = 2;				//���_�̌��B�����`�����邽�߂̍Œ���̐��B

};

