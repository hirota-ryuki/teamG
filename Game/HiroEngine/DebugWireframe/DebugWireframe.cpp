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
	//ルートシグネチャを初期化。
	InitRootSignature();
	//シェーダーを初期化。
	InitSharder();
	//パイプラインステートを初期化。
	InitPipelineState();
	//定数バッファを初期化。
	InitConstantBuffer();
	//2頂点を記録する定数バッファの初期化。
	InitVertexCBuffer();
	//ディスクリプタヒープを初期化。
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
	m_Vshader.LoadVS(L"Assets/shader/DebugMode.fx", "VSMain");
	m_Pshader.LoadPS(L"Assets/shader/DebugMode.fx", "PSMain");
}

void DebugWireframe::InitPipelineState()
{
	// 頂点レイアウトを定義する。
	D3D12_INPUT_ELEMENT_DESC inputElementDescs[] =
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 },
		{ "COLOR", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 }
	};

	//パイプラインステートを作成。
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
	psoDesc.RTVFormats[0] = DXGI_FORMAT_R8G8B8A8_UNORM;		//アルベドカラー出力用。
	psoDesc.DSVFormat = DXGI_FORMAT_D32_FLOAT;
	psoDesc.SampleDesc.Count = 1;
	m_pipelineState.Init(psoDesc);
}

void DebugWireframe::InitVertexCBuffer()
{
	//2頂点を記録する定数バッファを作成。
	m_vertexCBuffer.Init(sizeof(Vertex) * NUM_VERTEX);
}

void DebugWireframe::InitConstantBuffer()
{
	m_constantBuffer.Init(sizeof(Matrix), nullptr);
}

void DebugWireframe::InitDescriptorHeap()
{
	//ディスクリプタヒープにディスクリプタを登録していく。
	m_descriptorHeap.RegistConstantBuffer(0, m_constantBuffer);
	//ディスクリプタヒープへの登録を確定させる。
	m_descriptorHeap.Commit();
}

void DebugWireframe::VertexCBufferUpdate(const btVector3& from, const btVector3& to, const btVector3& color)
{
	//頂点を書き換える。
	Vertex vers[2];/*
	vers[0].pos = from;
	vers[0].color = color;
	vers[1].pos = to;
	vers[1].color = color;*/
	vers[0].pos = Vector3{ 10,10,10 };
	vers[0].color = Vector3{ 10,10,10 };
	vers[1].pos = Vector3{ 10,10,10 };
	vers[1].color = Vector3{ 10,10,10 };
	//レンダリングコンテキストを取得。
	auto& rc = g_graphicsEngine->GetRenderContext();
	//頂点をどんな感じに描画するのか。
	//今回は頂点二つの間に線を描く設定。
	rc.SetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_LINELIST);
	//定数バッファの更新。
	m_vertexCBuffer.CopyToVRAM(vers);
}

void DebugWireframe::ConstantBufferUpdate()
{
	//定数バッファの更新(c++)。
	//mVPの更新(シェーダー)。
	Matrix VP;		//ビュー行列とプロジェクション行列
	//ビューとプロジェクションの掛け算
	auto v = g_camera3D->GetViewMatrix();
	auto p = g_camera3D->GetProjectionMatrix();
	VP.Multiply(v, p);
	//定数バッファに渡したい変数を格納(m_constantBufferの内容を上書き)
	m_constantBuffer.CopyToVRAM(&VP);
}

bool hoge = false;
/*
void DebugWireframe::Context()
{
	//デバイスコンテキストにモデルクラス等の設定が
	//残っているため上書きする（更新）	
}*/

//1フレーム内にdrawLineは線の数だけ行う
void DebugWireframe::drawLine(const btVector3 & from, const btVector3 & to, const btVector3 & color)
{
	//頂点バッファの更新。
	VertexCBufferUpdate(from, to, color);
	//定数バッファの更新。
	ConstantBufferUpdate();
	//レンダリングコンテキストを取得。
	auto& rc = g_graphicsEngine->GetRenderContext();
	rc.SetPipelineState(m_pipelineState);
	rc.SetDescriptorHeap(m_descriptorHeap);
	rc.DrawIndexed(NUM_VERTEX);
}