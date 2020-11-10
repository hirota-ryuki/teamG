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
	m_Vshader.LoadVS(L"shader/DebugMode.fx", "VSMain");
	m_Pshader.LoadPS(L"shader/DebugMode.fx", "PSMain");
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

void DebugWireframe::VertexBufferUpdate()
{
	//1. 頂点バッファを作成。
	int numVertex = 2;
	int vertexStride = sizeof(TkmFile::SVertex);
	m_vertexBuffer.Init()
}

void DebugWireframe::Prepare()
{
	
	////頂点バッファ////
	//構造体
	//Description 意味:説明
	D3D11_BUFFER_DESC desc{};
	//使い方　
	desc.Usage = D3D11_USAGE_DEFAULT;
	//サイズ 
	desc.ByteWidth = sizeof(Vertex) * 2;
	//頂点用にする
	desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	//0はCPUからアクセスできない。
	//0なら書かなくて良い。
	desc.CPUAccessFlags = 0;
	//仕上げ
	g_graphicsEngine->GetD3DDevice()->CreateBuffer(&desc, nullptr, &m_vertexBuffer);
	////頂点終了////
	
	
}


bool hoge = false;
void DebugWireframe::Context()
{
	//デバイスコンテキストにモデルクラス等の設定が
	//残っているため上書きする（更新）	
}

//1フレーム内にdrawLineは線の数だけ行う
void DebugWireframe::drawLine(const btVector3 & from, const btVector3 & to, const btVector3 & color)
{
	auto& rc = g_graphicsEngine->GetRenderContext();
	//定数バッファの更新。
	ConstantBufferUpdate();
}

void DebugWireframe::drawLine_kari(const btVector3& from, const btVector3& to, const btVector3& color)
{
	//頂点バッファの設定
	//引数のストライドとオフセット用に変数をつくる
	//引数がポインタのため
	UINT ver = sizeof(Vertex);
	UINT offset = 0;
	//定数バッファをデバイスコンテキストに設定
	dc->IASetVertexBuffers(
		0,					//レジスタの場所
		1,					//配列の要素数
		&m_vertexBuffer,	//定数バッファのポインタ
		&ver,				//頂点のサイズ,ストライド
		&offset				//頂点の配列のスタート地点,オフセット
	);

	//頂点の情報がどんな感じに入っているのかがわかる
	dc->IASetInputLayout(m_Vshader.GetInputLayout());

	//頂点をどんな感じに描画するのか
	//今回は頂点二つの間に線を描く設定
	dc->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_LINELIST);

	//頂点を書き換えてドローする関数
	Vertex vers[2];
	vers[0].pos = from;
	vers[0].color = color;
	vers[1].pos = to;
	vers[1].color = color;

	//引数verはver[0]のアドレス
	//Prepare関数のByteWidthでサイズを*2にすることで
	//verの要素数が二つであることがわかる
	dc->UpdateSubresource(m_vertexBuffer, 0, nullptr, vers, 0, 0);

	//描画
	//2は頂点数、0はオフセット
	dc->Draw(2, 0);
}
