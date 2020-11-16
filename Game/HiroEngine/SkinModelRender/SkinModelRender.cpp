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
	//モデルを初期化。
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
	//ワールド行列の更新。
	m_model.UpdateWorldMatrix(m_pos, m_rot, m_scale);
	//Updateを呼んだ。
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
	//ビュー行列の逆行列を計算。
	m_viewMatrixInv.Inverse(g_camera3D->GetViewMatrix());
	//モデルの前方向。
	m_forward.Set(m_viewMatrixInv.m[2][0], m_viewMatrixInv.m[2][1], m_viewMatrixInv.m[2][2]);
	//モデルの右方向。
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
