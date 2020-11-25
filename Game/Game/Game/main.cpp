﻿#include "stdafx.h"
#include "system/system.h"
#include "Game.h"
#include "BackGround/BackGround.h"
#include"Title/Title.h"
//#include "BulletCollision/BroadphaseCollision/btOverlappingPairCallback.h"
//関数宣言
void InitRootSignature(RootSignature& rs);
void DebugMode(bool& isDebug);

/// <summary>
/// ディレクショナルライト
/// </summary>
struct DirectionalLight {
	Vector3  color;
	float pad0;			//パディング。
	Vector3  direction;
	float pad1;			//パディング。
	Vector3 eyePos;		//視点
	float specPow;		//スペキュラの絞り。
};

class Game;
class Title;
///////////////////////////////////////////////////////////////////
// ウィンドウプログラムのメイン関数。
///////////////////////////////////////////////////////////////////
int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow)
{
	/*
	//カレントディレクトリをAssetsに。
	size_t dir = 0;
	wchar_t wtextname[MAX_PATH] = { 0 };
	char textname[MAX_PATH] = { "Assets" };
	//char dir = { Assets };

	mbstowcs_s(&dir, wtextname, sizeof(MAX_PATH), textname, _TRUNCATE);
	SetCurrentDirectory(wtextname);*/
	//ゲームの初期化。
	InitGame(hInstance, hPrevInstance, lpCmdLine, nCmdShow, TEXT("Game"));

	//////////////////////////////////////
	// ここから初期化を行うコードを記述する。
	//////////////////////////////////////


	//ルートシグネチャを作成。
	RootSignature rootSignature;
	InitRootSignature(rootSignature);

	//ディレクションライト
	DirectionalLight light;
	light.direction.x = 1.0f;
	light.direction.y = -1.0f;
	light.direction.z = -1.0f;
	light.direction.Normalize();

	light.color.x = 1.0f;
	light.color.y = 1.0f;
	light.color.z = 1.0f;
	light.eyePos = g_camera3D->GetPosition();
	
	Vector3 planePos = { 0.0f, 0.0f, 20.0f };
	
	//G-Bufferを作成。
	RenderTarget albedRT;	//アルベドカラー書き込み用のレンダリングターゲット。
	albedRT.Create(FRAME_BUFFER_W, FRAME_BUFFER_H, 1, 1, DXGI_FORMAT_R8G8B8A8_UNORM, DXGI_FORMAT_D32_FLOAT);
	RenderTarget normalRT;	//法線書き込み用のレンダリングターゲット。
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
		DXGI_FORMAT_R32G32B32A32_FLOAT,		//ワールド座標を記録するので、32ビット浮動小数点バッファを利用する。
		DXGI_FORMAT_UNKNOWN
	);

	//ポストエフェクト的にディファードライティングを行うためのスプライトを初期化。
	SpriteInitData spriteInitData;
	//画面全体にレンダリングするので幅と高さはフレームバッファの幅と高さと同じ。
	spriteInitData.m_width = FRAME_BUFFER_W;
	spriteInitData.m_height = FRAME_BUFFER_H;
	//ディファードライティングで使用するテクスチャを設定。
	spriteInitData.m_textures[0] = &albedRT.GetRenderTargetTexture();
	spriteInitData.m_textures[1] = &normalRT.GetRenderTargetTexture();
	
	//ディファードライティングで使用するテクスチャにワールド座標テクスチャを追加。
	spriteInitData.m_textures[2] = &worldPosRT.GetRenderTargetTexture();
	spriteInitData.m_fxFilePath = "Assets/shader/sprite.fx";
	//spriteInitData.m_expandConstantBuffer = &light;
	//spriteInitData.m_expandConstantBufferSize = sizeof(light);
	//初期化データを使ってスプライトを作成。
	Sprite defferdLightinSpr;
	defferdLightinSpr.Init(spriteInitData);

	//デバッグモードのオンオフ。
	bool isDebug = false;
	Vector3 m_position = Vector3::Zero;
	auto& renderContext = g_graphicsEngine->GetRenderContext();
	Title* title = NewGO<Title>();
	// ここからゲームループ。
	while (DispatchWindowMessage())
	{
		//レンダリング開始。
		g_engine->BeginFrame();

		//レンダリングターゲットをG-Bufferに変更して書き込む。
		RenderTarget* rts[] = {
			&albedRT,	//0番目のレンダリングターゲット
			&normalRT,	//1番目のレンダリングターゲット
			&worldPosRT	//2番目のレンダリングターゲット
		};

		//まず、レンダリングターゲットとして設定できるようになるまで待つ。
		renderContext.WaitUntilToPossibleSetRenderTargets(ARRAYSIZE(rts), rts);
		//レンダリングターゲットを設定。
		renderContext.SetRenderTargets(ARRAYSIZE(rts), rts);
		//レンダリングターゲットをクリア。
		renderContext.ClearRenderTargetViews(ARRAYSIZE(rts), rts);

		//////////////////////////////////////
		//ここからコードを記述する。
		//////////////////////////////////////

		//物理エンジンの更新。
		g_physics.Update();

		//GameObjectManagerの更新。
		GameObjectManager::GetInstance().Update();

	
		//レンダリングターゲットへの書き込み待ち。
		renderContext.WaitUntilFinishDrawingToRenderTargets(ARRAYSIZE(rts), rts);
		
		//レンダリング先をフレームバッファに戻してスプライトをレンダリングする
		g_graphicsEngine->ChangeRenderTargetToFrameBuffer(renderContext);
		//G-Bufferの内容を元にしてディファードライティング。
		defferdLightinSpr.Draw(renderContext);
		
		//デバッグモード。
		DebugMode(isDebug);

		//ここからフォワードレンダリング。
		//深度ステンシルビューをG-Bufferを作成したときのものに変更する。
		renderContext.SetRenderTarget(g_graphicsEngine->GetCurrentFrameBuffuerRTV(), rts[0]->GetDSVCpuDescriptorHandle());

		//カメラ。
		g_camera3D->Update();
		
		//レンダリング終了。
		g_engine->EndFrame();
	}

	return 0;
}


//ルートシグネチャの初期化。
void InitRootSignature(RootSignature& rs)
{
	rs.Init(D3D12_FILTER_MIN_MAG_MIP_LINEAR,
		D3D12_TEXTURE_ADDRESS_MODE_WRAP,
		D3D12_TEXTURE_ADDRESS_MODE_WRAP,
		D3D12_TEXTURE_ADDRESS_MODE_WRAP);
}

//デバッグモード。
void DebugMode(bool& isDebug) 
{
	//ボタンで切り替え。
	if (g_pad[0]->IsTrigger(enButtonSelect))
	{
		isDebug = !isDebug;
	}
	if (isDebug)
	{
		//デバッグモード。
		g_physics.DebugDraw();
	}
}