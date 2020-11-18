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
	/// 初期化。	
	/// </summary>
	void Init();
	/// 必須。
	/// <summary>
	/// 線ごとに一回ずつ呼ばれる。
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

	//何もしなくても問題なし {}　必要であれば定義
	void    drawContactPoint(const btVector3& PointOnB, const btVector3& normalOnB, btScalar distance, int lifeTime, const btVector3& color) override {};
	void    reportErrorWarning(const char* warningString) override {};
	void    draw3dText(const btVector3& location, const char* textString) override {};
	void Begin()
	{
		m_numLine = 0;
		m_vertexList.clear();
	}
	void End();
private:
	/// <summary>
	/// ルートシグネチャの初期化。
	/// </summary>
	void InitRootSignature();
	/// <summary>
	/// シェーダーの初期化。
	/// </summary>
	void InitSharder();
	/// <summary>
	/// パイプラインステートの初期化。
	/// </summary>
	void InitPipelineState();
	/// <summary>
	/// 2頂点を記録する定数バッファの初期化。
	/// </summary>
	void InitVertexCBuffer();
	/// <summary>
	/// 定数バッファの初期化。
	/// </summary>
	void InitConstantBuffer();
	/// <summary>
	/// ディスクリプタヒープの初期化。
	/// </summary>
	void InitDescriptorHeap();	
	/// <summary>
	/// 頂点バッファの更新。
	/// </summary>
	void VertexCBufferUpdate(const btVector3& from, const btVector3& to, const btVector3& color);
	/// <summary>
	/// 定数バッファの更新。
	/// </summary>
	void ConstantBufferUpdate();
	/// <summary>
	/// レンダーコンテキストの更新。
	/// </summary>
	void RenderContextUpdate();
private:
	struct Vertex 
	{
		Vector3 pos;
		Vector3 color;
	};
	std::vector<Vertex>	m_vertexList;				//描画する頂点のリスト
	ConstantBuffer		m_constantBuffer;			//定数バッファ。
	VertexBuffer		m_vertexCBuffer;
	IndexBuffer			m_indexBuffer;
	RootSignature		m_rootSignature;			//ルートシグネチャ。
	Shader				m_Vshader;					//頂点シェーダー。
	Shader				m_Pshader;					//ピクセルシェーダー。
	PipelineState		m_pipelineState;			//パイプラインステート。
	DescriptorHeap		m_descriptorHeap;			//ディスクリプタヒープ。	
	static const int	MAX_VERTEX = 10000000;		//頂点の最大数。
	int m_numLine = 0;								//描画するラインの数。
};

