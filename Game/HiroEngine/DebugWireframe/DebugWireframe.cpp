#include "stdafx.h"
#include "DebugWireframe.h"


DebugWireframe::DebugWireframe()
{
}


DebugWireframe::~DebugWireframe()
{
}

void DebugWireframe::Init()
{	
	//���[�g�V�O�l�`�����������B
	InitRootSignature();
	//�V�F�[�_�[���������B
	InitSharder();
	//�p�C�v���C���X�e�[�g���������B
	InitPipelineState();
	//�萔�o�b�t�@���������B
	InitConstantBuffer();
	//�f�B�X�N���v�^�q�[�v���������B
	InitDescriptorHeap();
}

void DebugWireframe::InitRootSignature()
{
	m_rootSignature.Init(
		D3D12_FILTER_MIN_MAG_MIP_LINEAR,
		D3D12_TEXTURE_ADDRESS_MODE_WRAP,
		D3D12_TEXTURE_ADDRESS_MODE_WRAP,
		D3D12_TEXTURE_ADDRESS_MODE_WRAP
	);
}

void DebugWireframe::InitSharder()
{
	m_Vshader.LoadVS(L"shader/DebugMode.fx", "VSMain");
	m_Pshader.LoadPS(L"shader/DebugMode.fx", "PSMain");
}

void DebugWireframe::InitPipelineState()
{
	// ���_���C�A�E�g���`����B
	D3D12_INPUT_ELEMENT_DESC inputElementDescs[] =
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 },
		{ "COLOR", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 }
	};

	//�p�C�v���C���X�e�[�g���쐬�B
	D3D12_GRAPHICS_PIPELINE_STATE_DESC psoDesc = { 0 };
	psoDesc.InputLayout = { inputElementDescs, _countof(inputElementDescs) };
	psoDesc.pRootSignature = m_rootSignature.Get();
	psoDesc.VS = CD3DX12_SHADER_BYTECODE(m_Vshader.GetCompiledBlob());
	psoDesc.PS = CD3DX12_SHADER_BYTECODE(m_Pshader.GetCompiledBlob());
	psoDesc.RasterizerState = CD3DX12_RASTERIZER_DESC(D3D12_DEFAULT);
	psoDesc.BlendState = CD3DX12_BLEND_DESC(D3D12_DEFAULT);
	psoDesc.DepthStencilState.DepthEnable = TRUE;
	psoDesc.DepthStencilState.DepthWriteMask = D3D12_DEPTH_WRITE_MASK_ALL;
	psoDesc.DepthStencilState.DepthFunc = D3D12_COMPARISON_FUNC_LESS_EQUAL;
	psoDesc.DepthStencilState.StencilEnable = FALSE;
	psoDesc.SampleMask = UINT_MAX;
	psoDesc.PrimitiveTopologyType = D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE;
	psoDesc.NumRenderTargets = 3;
	psoDesc.RTVFormats[0] = DXGI_FORMAT_R8G8B8A8_UNORM;		//�A���x�h�J���[�o�͗p�B
	psoDesc.DSVFormat = DXGI_FORMAT_D32_FLOAT;
	psoDesc.SampleDesc.Count = 1;
	m_pipelineState.Init(psoDesc);
}

void DebugWireframe::InitConstantBuffer()
{
	m_constantBuffer.Init(sizeof(Matrix), nullptr);
}

void DebugWireframe::InitDescriptorHeap()
{
	//�f�B�X�N���v�^�q�[�v�Ƀf�B�X�N���v�^��o�^���Ă����B
	m_descriptorHeap.RegistConstantBuffer(0, m_constantBuffer);
	//�f�B�X�N���v�^�q�[�v�ւ̓o�^���m�肳����B
	m_descriptorHeap.Commit();
}

void DebugWireframe::ConstantBufferUpdate()
{
	//�萔�o�b�t�@�̍X�V(c++)�B
	//mVP�̍X�V(�V�F�[�_�[)�B
	Matrix VP;		//�r���[�s��ƃv���W�F�N�V�����s��
	//�r���[�ƃv���W�F�N�V�����̊|���Z
	auto v = g_camera3D->GetViewMatrix();
	auto p = g_camera3D->GetProjectionMatrix();
	VP.Multiply(v, p);
	//�萔�o�b�t�@�ɓn�������ϐ����i�[(m_constantBuffer�̓��e���㏑��)
	m_constantBuffer.CopyToVRAM(&VP);
}

void DebugWireframe::VertexBufferUpdate()
{
	//1. ���_�o�b�t�@���쐬�B
	int numVertex = 2;
	int vertexStride = sizeof(TkmFile::SVertex);
	m_vertexBuffer.Init()
}

void DebugWireframe::Prepare()
{
	
	////���_�o�b�t�@////
	//�\����
	//Description �Ӗ�:����
	D3D11_BUFFER_DESC desc{};
	//�g�����@
	desc.Usage = D3D11_USAGE_DEFAULT;
	//�T�C�Y 
	desc.ByteWidth = sizeof(Vertex) * 2;
	//���_�p�ɂ���
	desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	//0��CPU����A�N�Z�X�ł��Ȃ��B
	//0�Ȃ珑���Ȃ��ėǂ��B
	desc.CPUAccessFlags = 0;
	//�d�グ
	g_graphicsEngine->GetD3DDevice()->CreateBuffer(&desc, nullptr, &m_vertexBuffer);
	////���_�I��////
	
	
}


bool hoge = false;
void DebugWireframe::Context()
{
	//�f�o�C�X�R���e�L�X�g�Ƀ��f���N���X���̐ݒ肪
	//�c���Ă��邽�ߏ㏑������i�X�V�j	
}

//1�t���[������drawLine�͐��̐������s��
void DebugWireframe::drawLine(const btVector3 & from, const btVector3 & to, const btVector3 & color)
{
	auto& rc = g_graphicsEngine->GetRenderContext();
	//�萔�o�b�t�@�̍X�V�B
	ConstantBufferUpdate();
}

void DebugWireframe::drawLine_kari(const btVector3& from, const btVector3& to, const btVector3& color)
{
	//���_�o�b�t�@�̐ݒ�
	//�����̃X�g���C�h�ƃI�t�Z�b�g�p�ɕϐ�������
	//�������|�C���^�̂���
	UINT ver = sizeof(Vertex);
	UINT offset = 0;
	//�萔�o�b�t�@���f�o�C�X�R���e�L�X�g�ɐݒ�
	dc->IASetVertexBuffers(
		0,					//���W�X�^�̏ꏊ
		1,					//�z��̗v�f��
		&m_vertexBuffer,	//�萔�o�b�t�@�̃|�C���^
		&ver,				//���_�̃T�C�Y,�X�g���C�h
		&offset				//���_�̔z��̃X�^�[�g�n�_,�I�t�Z�b�g
	);

	//���_�̏�񂪂ǂ�Ȋ����ɓ����Ă���̂����킩��
	dc->IASetInputLayout(m_Vshader.GetInputLayout());

	//���_���ǂ�Ȋ����ɕ`�悷��̂�
	//����͒��_��̊Ԃɐ���`���ݒ�
	dc->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_LINELIST);

	//���_�����������ăh���[����֐�
	Vertex vers[2];
	vers[0].pos = from;
	vers[0].color = color;
	vers[1].pos = to;
	vers[1].color = color;

	//����ver��ver[0]�̃A�h���X
	//Prepare�֐���ByteWidth�ŃT�C�Y��*2�ɂ��邱�Ƃ�
	//ver�̗v�f������ł��邱�Ƃ��킩��
	dc->UpdateSubresource(m_vertexBuffer, 0, nullptr, vers, 0, 0);

	//�`��
	//2�͒��_���A0�̓I�t�Z�b�g
	dc->Draw(2, 0);
}
