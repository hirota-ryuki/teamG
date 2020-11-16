#include "stdafx.h"
#include "system/system.h"
#include "test.h"
#include "Game/Game.h"
//#include "BulletCollision/BroadphaseCollision/btOverlappingPairCallback.h"
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
	// �������珉������s���R�[�h��L�q����B
	//////////////////////////////////////


	//���[�g�V�O�l�`����쐬�B
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

	//���f����������B
	ModelInitData modelInitData;
	////�l�^���f����������B
	modelInitData.m_tkmFilePath = "Assets/modelData/unityChan.tkm";
	modelInitData.m_fxFilePath = "Assets/shader/model.fx";
	Model humanModel;
	humanModel.Init(modelInitData);
	//humanModel.UpdateWorldMatrix({ -50.0f, 0.0f, 0.0f }, g_quatIdentity, g_vec3One);

	
	Vector3 planePos = { 0.0f, 0.0f, 20.0f };
	
	//G-Buffer��쐬�B
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
		DXGI_FORMAT_R32G32B32A32_FLOAT,		//���[���h���W��L�^����̂ŁA32�r�b�g���������_�o�b�t�@�𗘗p����B
		DXGI_FORMAT_UNKNOWN
	);

	//�|�X�g�G�t�F�N�g�I�Ƀf�B�t�@�[�h���C�e�B���O��s�����߂̃X�v���C�g��������B
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
	//�������f�[�^��g���ăX�v���C�g��쐬�B
	Sprite defferdLightinSpr;
	defferdLightinSpr.Init(spriteInitData);

	//�f�o�b�O���[�h�̃I���I�t�B
	bool isDebug = false;
	Vector3 m_position = Vector3::Zero;
	CharacterController m_charaCon;								//�L�����N�^�[�R���g���[���[�B

	//�L�����R���̏�����
	m_charaCon.Init(
		80.f,
		200.f,
		m_position
	);

	auto& renderContext = g_graphicsEngine->GetRenderContext();
	NewGO<Game>(GOPrio_Defalut,"MainGame");
	//NewGO<test>(GOPrio_Defalut,"Game");
	// ��������Q�[�����[�v�B
	while (DispatchWindowMessage())
	{
		//�����_�����O�J�n�B
		g_engine->BeginFrame();

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
		//�����_�����O�^�[�Q�b�g��N���A�B
		renderContext.ClearRenderTargetViews(ARRAYSIZE(rts), rts);

		//////////////////////////////////////
		//��������R�[�h��L�q����B
		//////////////////////////////////////

		//�����G���W���̍X�V�B
		g_physics.Update();

		//GameObjectManager�̍X�V�B
		GameObjectManager::GetInstance().Update();

		//humanModel.Draw(renderContext);

		//float lStick_x = (g_pad[0]->GetLStickXF());
		//float lStick_z = (g_pad[0]->GetLStickYF());

		//planePos.x += lStick_x;
		//planePos.z += lStick_z;
		//�����_�����O�^�[�Q�b�g�ւ̏������ݑ҂��B
		renderContext.WaitUntilFinishDrawingToRenderTargets(ARRAYSIZE(rts), rts);
		
		//�����_�����O���t���[���o�b�t�@�ɖ߂��ăX�v���C�g������_�����O����
		g_graphicsEngine->ChangeRenderTargetToFrameBuffer(renderContext);
		//G-Buffer�̓�e����ɂ��ăf�B�t�@�[�h���C�e�B���O�B
		defferdLightinSpr.Draw(renderContext);
		
		//��������t�H���[�h�����_�����O�B
		//�[�x�X�e���V���r���[��G-Buffer��쐬�����Ƃ��̂�̂ɕύX����B
		renderContext.SetRenderTarget(g_graphicsEngine->GetCurrentFrameBuffuerRTV(), rts[0]->GetDSVCpuDescriptorHandle());
	
		//半透明オブジェクトを描画！
		//sphereModel.Draw(renderContext);
		//humanModel.UpdateWorldMatrix(planePos, g_quatIdentity, g_vec3One);

		//�J����
		//Vector3 m_toPos = { 0.0f, 100.0f, -450.0f };
		//Vector3 m_target = planePos;
		//m_target.y += 50.0f;
		//Vector3 m_pos = planePos + m_toPos;
		//g_camera3D->SetPosition(m_pos);
		//g_camera3D->SetTarget(m_target);
		//g_camera3D->Update();
		/////////////////////////////////////////
		//絵を描くコードを書くのはここまで！！！
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

//�f�o�b�O���[�h�B
void DubugMode(bool& isDebug) {
	
}