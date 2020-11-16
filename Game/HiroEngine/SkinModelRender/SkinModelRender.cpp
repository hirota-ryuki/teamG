#include "stdafx.h"
#include "SkinModelRender.h"

SkinModelRender::SkinModelRender()
{
}


SkinModelRender::~SkinModelRender()
{
}

void SkinModelRender::Init(const char* texFilePath)
{
	//���f�����������B
	ModelInitData modelInitData;
	modelInitData.m_tkmFilePath = texFilePath;
	modelInitData.m_fxFilePath = "Assets/shader/model.fx";
	m_model.Init(modelInitData);
}

void SkinModelRender::Update()
{	
	UpdateWorldMatrix();
	/*if (m_isShadow) {
		ShadowMap::GetInstance().RegistShadowCaster(&m_model);
	}*/
}

void SkinModelRender::UpdateWorldMatrix()
{
	//���[���h�s��̍X�V�B
	m_model.UpdateWorldMatrix(m_pos, m_rot, m_scale);
	//Update���Ă񂾁B
	m_isUpdate = true;
}
void SkinModelRender::Draw()
{
	if (m_isUpdate) {
		if (m_isActive) {
			auto& rc = g_graphicsEngine->GetRenderContext();
			m_model.Draw(rc);
		}
	}	
	//�r���[�s��̋t�s����v�Z�B
	m_viewMatrixInv.Inverse(g_camera3D->GetViewMatrix());
	//���f���̑O�����B
	m_forward.Set(m_viewMatrixInv.m[2][0], m_viewMatrixInv.m[2][1], m_viewMatrixInv.m[2][2]);
	//���f���̉E�����B
	m_right.Set(m_viewMatrixInv.m[0][0], m_viewMatrixInv.m[0][1], m_viewMatrixInv.m[0][2]);
}

/*
void SkinModelRender::InitNormalMap(const wchar_t * filePath)
{
	m_model.InitNormalMap(filePath);
}

void SkinModelRender::InitSpecMap(const wchar_t * filePath)
{
	m_model.InitSpecMap(filePath);
}*/
