/*!
 * @brief	シンプルなモデル表示用のシェーダー。
 */



//モデル用の定数バッファ
cbuffer ModelCb : register(b0){
	float4x4 mWorld;
	float4x4 mView;
	float4x4 mProj;
};

//頂点シェーダーへの入力。
struct SVSIn{
	float4 pos 		: POSITION;
	float3 normal	: NORMAL;
	float2 uv 		: TEXCOORD0;
};
//ピクセルシェーダーへの入力。
struct SPSIn{
	float4 pos 			: SV_POSITION;
	float3 normal		: NORMAL;
	float2 uv 			: TEXCOORD0;
	float3 worldPos		: TEXCOORD1;	//ワールド座標。
};

//ピクセルシェーダーからの出力。
struct SPSOut{
	float4 albedo	: SV_Target0;	//アルベド
	float3 normal	: SV_Target1;	//法線。
	float3 worldPos : SV_Target2;	//ワールド座標。
};
//モデルテクスチャ。
Texture2D<float4> g_texture : register(t0);	

//サンプラステート。
sampler g_sampler : register(s0);

/// <summary>
/// モデル用の頂点シェーダーのエントリーポイント。
/// </summary>
SPSIn VSMain(SVSIn vsIn, uniform bool hasSkin)
{
	SPSIn psIn;

	psIn.pos = mul(mWorld, vsIn.pos);	//モデルの頂点をワールド座標系に変換。	+
	
	//step ??? 頂点シェーダーからワールド座標を出力。
	psIn.worldPos = psIn.pos;

	psIn.pos = mul(mView, psIn.pos);	//ワールド座標系からカメラ座標系に変換。
	psIn.pos = mul(mProj, psIn.pos);	//カメラ座標系からスクリーン座標系に変換。
	psIn.normal = normalize(mul(mWorld, vsIn.normal));
	psIn.uv = vsIn.uv;

	return psIn;
}
/// <summary>
/// モデル用のピクセルシェーダーのエントリーポイント
/// </summary>
SPSOut PSMain( SPSIn psIn )
{
	//G-Bufferに出力。
	SPSOut psOut;
	//アルベドカラーを出力。
	psOut.albedo = g_texture.Sample(g_sampler, psIn.uv);
	//法線を出力。
	psOut.normal = psIn.normal;

	psOut.worldPos = psIn.worldPos;
	return psOut;
}
//step-3 ライトの情報を受け取るための定数バッファを追加。
cbuffer DirectionLight : register(b1){
	float3 ligColor;
	float3 ligDirection;
	float3 eyePos;
};

//step-4 半透明オブジェクト用のピクセルシェーダーを実装。

//step-3 トゥーン用のシェーダー
float4 PSTone( SPSIn psIn ) : SV_Target0
{
	float4 albedo = g_texture.Sample(g_sampler,psIn.uv);
	//課題1　簡易リムライト
	float4 lig = albedo*1.5f;
	float Dot = dot(eyePos,psIn.normal);
	if(Dot>=-1.0f){
		albedo.xyz=float3(1.0f,1.0f,1.0f);
		//albedo.xyz=lig.xyz;
	}
	/*
	float4 ligColor = albedo*1.5f;
	float3 eyeDir =float3(0.0f,0.0f,-1.0f);
	float lim =(1.0f-dot(-psIn.normal,eyeDir));
	if(lim >0.5f){
		albedo.xyz=ligColor.xyz;
	}*/

	//課題2　2諧調陰影
	return albedo;
}