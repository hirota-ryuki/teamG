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
	/// 初期化。	
	/// </summary>
	void Init();
	/// <summary>
	/// ディスクリプタヒープの初期化。
	/// </summary>
	void InitDescriptorHeap();
	/// <summary>
	/// 定数バッファの初期化。
	/// </summary>
	void InitConstantBuffer();
	/// <summary>
	/// パイプラインステートの初期化。
	/// </summary>
	void InitPipelineState();
	/// <summary>
	/// シェーダーの初期化。
	/// </summary>
	void InitSharder();
	/// <summary>
	/// ルートシグネチャの初期化。
	/// </summary>
	void InitRootSignature();
	/// <summary>
	/// 定数バッファの更新。
	/// </summary>
	void ConstantBufferUpdate();
	/// <summary>
	/// 頂点バッファの更新。
	/// </summary>
	void VertexBufferUpdate();
	/// <summary>
	/// 設定の準備
	/// </summary>
	void Prepare();
	/// <summary>
	/// デバイスコンテキストに設定
	/// 1フレーム内に一回
	/// </summary>
	void Context();
	/// 必須
	/// <summary>
	/// 線ごとに一回ずつ呼ばれる
	/// </summary>
	/// <param name="from"></param>
	/// <param name="to"></param>
	/// <param name="color"></param>
	void    drawLine(const btVector3& from, const btVector3& to, const btVector3& color) override;
	void    drawLine_kari(const btVector3& from, const btVector3& to, const btVector3& color) ;
	void    setDebugMode(int debugMode) override {};
	int     getDebugMode() const override 
	{
		return true;
	};

	//何もしなくても問題なし {}　必要であれば定義
	void    drawContactPoint(const btVector3& PointOnB, const btVector3& normalOnB, btScalar distance, int lifeTime, const btVector3& color) override {};
	void    reportErrorWarning(const char* warningString) override {};
	void    draw3dText(const btVector3& location, const char* textString) override {};
private:
	struct Vertex 
	{
		Vector3 pos;
		Vector3 color;
	};
	
	ConstantBuffer		m_constantBuffer;			//定数バッファ。
	VertexBuffer		m_vertexBuffer;				//頂点バッファ。
	RootSignature		m_rootSignature;			//ルートシグネチャ。
	Shader				m_Vshader;					//頂点シェーダー。
	Shader				m_Pshader;					//ピクセルシェーダー。
	PipelineState		m_pipelineState;			//パイプラインステート。
	DescriptorHeap		m_descriptorHeap;			//ディスクリプタヒープ。	
};

