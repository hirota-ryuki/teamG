#include "stdafx.h"
#include "system/system.h"
#include"Player/Player.h"
#include "test.h"
//�֐��錾
void InitRootSignature(RootSignature& rs);

/// <summary>
/// �f�B���N�V���i�����C�g
/// </summary>
struct DirectionalLight {
	Vector3  color;
	float pad0;			//�p�f�B���O�B
	Vector3  direction;
	float pad1;			//�p�f�B���O�B
	Vector3 eyePos;		//���_
	float specPow;		//�X�y�L�����̍i��B
};


///////////////////////////////////////////////////////////////////
// �E�B���h�E�v���O�����̃��C���֐��B
///////////////////////////////////////////////////////////////////
int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow)
{
	//�Q�[���̏������B
	InitGame(hInstance, hPrevInstance, lpCmdLine, nCmdShow, TEXT("Game"));

	//////////////////////////////////////
	// �������珉�������s���R�[�h���L�q����B
	//////////////////////////////////////


	//���[�g�V�O�l�`�����쐬�B
	RootSignature rootSignature;
	InitRootSignature(rootSignature);

	//�f�B���N�V�������C�g
	DirectionalLight light;
	light.direction.x = 1.0f;
	light.direction.y = -1.0f;
	light.direction.z = -1.0f;
	light.direction.Normalize();

	light.color.x = 1.0f;
	light.color.y = 1.0f;
	light.color.z = 1.0f;
	light.eyePos = g_camera3D->GetPosition();

	//���f�����������B
	ModelInitData modelInitData;
	////�l�^���f�����������B
	modelInitData.m_tkmFilePath = "Assets/modelData/unityChan.tkm";
	modelInitData.m_fxFilePath = "Assets/shader/model.fx";
	Model humanModel;
	humanModel.Init(modelInitData);
	humanModel.UpdateWorldMatrix({ -50.0f, 0.0f, 0.0f }, g_quatIdentity, g_vec3One);

	//���{�b�g���f�����������B
	modelInitData.m_tkmFilePath = "Assets/modelData/robo/robo.tkm";
	Model roboModel;
	roboModel.Init(modelInitData);
	roboModel.UpdateWorldMatrix({ 50.0f, 0.0f, 0.0f }, g_quatIdentity, { 10.0f, 10.0f, 10.0f });

	//�w�i���f�����������B
	modelInitData.m_tkmFilePath = "Assets/modelData/bg/bg.tkm";
	Model bgModel;
	bgModel.Init(modelInitData);
	/*
	//�������̋��̃��f�����������B
	ModelInitData transModelInitData;
	transModelInitData.m_tkmFilePath = "Assets/modelData/sphere.tkm";
	transModelInitData.m_fxFilePath = "Assets/shader/model.fx";
	//���������f���̓��f����`���Ƃ��Ƀ��C�e�B���O���s���̂ŁA���C�g�̏���n���B
	transModelInitData.m_expandConstantBuffer = &light;
	transModelInitData.m_expandConstantBufferSize = sizeof(light);
	//�s�N�Z���V�F�[�_�̃G���g���[�|�C���g���s�������f���Ƃ͈قȂ�B
	//�s�������f����PSMain�A���������f����PSMainTrans���g�p����B
	//�s�N�Z���V�F�[�_�̎����͌�Ŋm�F�B
	transModelInitData.m_psEntryPointFunc = "PSMainTrans";
	//�������̋��̃��f�����������B
	Model sphereModel;
	sphereModel.Init(transModelInitData);
	*/

	//step-1 �Z�����b�N���f�����������B
	ModelInitData toneModelInitData;
	toneModelInitData.m_tkmFilePath = "Assets/modelData/unityChan.tkm";
	toneModelInitData.m_fxFilePath = "Assets/shader/model.fx";
	toneModelInitData.m_psEntryPointFunc = "PSTone";

	Model toneModel;
	toneModel.Init(toneModelInitData);
	
	Vector3 planePos = { 0.0f, 0.0f, 20.0f };
	
	//G-Buffer���쐬�B
	RenderTarget albedRT;	//�A���x�h�J���[�������ݗp�̃����_�����O�^�[�Q�b�g�B
	albedRT.Create(FRAME_BUFFER_W, FRAME_BUFFER_H, 1, 1, DXGI_FORMAT_R8G8B8A8_UNORM, DXGI_FORMAT_D32_FLOAT);
	RenderTarget normalRT;	//�@���������ݗp�̃����_�����O�^�[�Q�b�g�B
	normalRT.Create(
		FRAME_BUFFER_W, 
		FRAME_BUFFER_H, 
		1, 
		1, 
		DXGI_FORMAT_R32G32B32A32_FLOAT, 
		DXGI_FORMAT_UNKNOWN
	);
	RenderTarget worldPosRT;
	worldPosRT.Create(
		FRAME_BUFFER_W, 
		FRAME_BUFFER_H, 
		1, 
		1, 
		DXGI_FORMAT_R32G32B32A32_FLOAT,		//���[���h���W���L�^����̂ŁA32�r�b�g���������_�o�b�t�@�𗘗p����B
		DXGI_FORMAT_UNKNOWN
	);

	//�|�X�g�G�t�F�N�g�I�Ƀf�B�t�@�[�h���C�e�B���O���s�����߂̃X�v���C�g���������B
	SpriteInitData spriteInitData;
	//��ʑS�̂Ƀ����_�����O����̂ŕ��ƍ����̓t���[���o�b�t�@�̕��ƍ����Ɠ����B
	spriteInitData.m_width = FRAME_BUFFER_W;
	spriteInitData.m_height = FRAME_BUFFER_H;
	//�f�B�t�@�[�h���C�e�B���O�Ŏg�p����e�N�X�`����ݒ�B
	spriteInitData.m_textures[0] = &albedRT.GetRenderTargetTexture();
	spriteInitData.m_textures[1] = &normalRT.GetRenderTargetTexture();
	
	//�f�B�t�@�[�h���C�e�B���O�Ŏg�p����e�N�X�`���Ƀ��[���h���W�e�N�X�`����ǉ��B
	spriteInitData.m_textures[2] = &worldPosRT.GetRenderTargetTexture();

	spriteInitData.m_fxFilePath = "Assets/shader/sprite.fx";
	spriteInitData.m_expandConstantBuffer = &light;
	spriteInitData.m_expandConstantBufferSize = sizeof(light);
	//�������f�[�^���g���ăX�v���C�g���쐬�B
	Sprite defferdLightinSpr;
	defferdLightinSpr.Init(spriteInitData);

	//////////////////////////////////////
	// ���������s���R�[�h�������̂͂����܂ŁI�I�I
	//////////////////////////////////////
	auto& renderContext = g_graphicsEngine->GetRenderContext();

	test* test1;
	test1 = NewGO<test>(GOPrio_Defalut,"test");

	// ��������Q�[�����[�v�B
	while (DispatchWindowMessage())
	{
		//GameObjectManager�̍X�V�B
		GameObjectManager::GetInstance().Update();
		auto test = GameObjectManager::GetInstance().GetListSize();
		//DeleteGOs("test");
		test = GameObjectManager::GetInstance().GetListSize();
		//�����_�����O�J�n�B
		g_engine->BeginFrame();
		if (g_pad[0]->IsPress(enButtonRight)) {
			planePos.x -= 1.0f;
		}
		if (g_pad[0]->IsPress(enButtonLeft)) {
			planePos.x += 1.0f;
		}
		if (g_pad[0]->IsPress(enButtonUp) ){
			planePos.z -= 1.0f;
		}
		if (g_pad[0]->IsPress(enButtonDown)) {
			planePos.z += 1.0f;
		}
		//sphereModel.UpdateWorldMatrix(planePos, g_quatIdentity, g_vec3One);
		//////////////////////////////////////
		//��������G��`���R�[�h���L�q����B
		//////////////////////////////////////

		//�����_�����O�^�[�Q�b�g��G-Buffer�ɕύX���ď������ށB
		RenderTarget* rts[] = {
			&albedRT,	//0�Ԗڂ̃����_�����O�^�[�Q�b�g
			&normalRT,	//1�Ԗڂ̃����_�����O�^�[�Q�b�g
			&worldPosRT	//2�Ԗڂ̃����_�����O�^�[�Q�b�g
		};

		//�܂��A�����_�����O�^�[�Q�b�g�Ƃ��Đݒ�ł���悤�ɂȂ�܂ő҂B
		renderContext.WaitUntilToPossibleSetRenderTargets(ARRAYSIZE(rts), rts);
		//�����_�����O�^�[�Q�b�g��ݒ�B
		renderContext.SetRenderTargets(ARRAYSIZE(rts), rts);
		//�����_�����O�^�[�Q�b�g���N���A�B
		renderContext.ClearRenderTargetViews(ARRAYSIZE(rts), rts);
		humanModel.Draw(renderContext);
		bgModel.Draw(renderContext);
		roboModel.Draw(renderContext);


		//�����_�����O�^�[�Q�b�g�ւ̏������ݑ҂��B
		renderContext.WaitUntilFinishDrawingToRenderTargets(ARRAYSIZE(rts), rts);
		
		//�����_�����O����t���[���o�b�t�@�ɖ߂��ăX�v���C�g�������_�����O����
		g_graphicsEngine->ChangeRenderTargetToFrameBuffer(renderContext);
		//G-Buffer�̓��e�����ɂ��ăf�B�t�@�[�h���C�e�B���O�B
		defferdLightinSpr.Draw(renderContext);
		
		//��������t�H���[�h�����_�����O�B
		//�[�x�X�e���V���r���[��G-Buffer���쐬�����Ƃ��̂��̂ɕύX����B
		renderContext.SetRenderTarget(g_graphicsEngine->GetCurrentFrameBuffuerRTV(), rts[0]->GetDSVCpuDescriptorHandle());
		
		//step-2 �Z�����b�N���f���̕`��
		toneModel.Draw(renderContext);
		
		//�������I�u�W�F�N�g��`��I
		//sphereModel.Draw(renderContext);

		/////////////////////////////////////////
		//�G��`���R�[�h�������̂͂����܂ŁI�I�I
		//////////////////////////////////////
		//�����_�����O�I���B
		g_engine->EndFrame();
	}

	return 0;
}


//���[�g�V�O�l�`���̏������B
void InitRootSignature(RootSignature& rs)
{
	rs.Init(D3D12_FILTER_MIN_MAG_MIP_LINEAR,
		D3D12_TEXTURE_ADDRESS_MODE_WRAP,
		D3D12_TEXTURE_ADDRESS_MODE_WRAP,
		D3D12_TEXTURE_ADDRESS_MODE_WRAP);
}
