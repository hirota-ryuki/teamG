#pragma once

class SkinModelRender : public IGameObject
{
public:
	SkinModelRender();
	~SkinModelRender();
	void Update() override;
	bool Start() override { return true; };
	void Draw() override;
	/// <summary>
	/// ワールド行列を更新。
	/// </summary>
	void UpdateWorldMatrix();
	/// <summary>
	/// スキンモデルの初期化。
	/// </summary>
	/// <param name="texFilePath">モデルのファイルパス</param>
	void Init(const char* texFilePath);
	/*
	/// <summary>
	/// 法線マップの初期化処理。
	/// </summary>
	/// <param name="filePath">法線マップのファイルパス。</param>
	void InitNormalMap(const wchar_t* filePath);
	/// <summary>
	/// スペキュラマップの初期化処理。
	/// </summary>
	/// <param name="filePath">スペキュラマップのファイルパス。</param>
	void InitSpecMap(const wchar_t* filePath);*/
	/// <summary>
	/// 座標、回転を設定
	/// 拡大率は触れないように
	/// </summary>
	/// <param name="pos">座標</param>
	/// <param name="rot">回転</param>
	void SetData(Vector3 pos, Quaternion rot)
	{
		m_pos = pos;
		m_rot = rot;
	}
	
	/// <summary>
	/// 座標を設定
	/// </summary>
	/// <param name="pos">座標</param>
	void SetPos(Vector3 pos)
	{
		m_pos = pos;
	}
	/// <summary>
	/// ポジションを取得。
	/// </summary>
	/// <returns>座標。</returns>
	Vector3 GetPos()
	{
		return m_pos;
	}
	/// <summary>
	/// 回転を設定
	/// </summary>
	/// <param name="pos">回転</param>
	void SetRot(Quaternion rot)
	{
		m_rot = rot;
	}
	/// <summary>
	/// 回転を取得。
	/// </summary>
	/// <returns>回転。</returns>
	Quaternion GetRot()
	{
		return m_rot;
	}
	/// <summary>
	/// 描画するかどうか。
	/// 呼ばれたらtrueとfalseを入れ替える。
	/// </summary>
	void ChangeActive()
	{
		m_isActive = !m_isActive;
	}
	/// <summary>
	/// 描画するかどうか。
	/// trueかfalseかを指定する。
	/// </summary>
	void ActiveMode(bool active)
	{
		m_isActive = active;
	}
	/// <summary>
	/// スキンモデルを取得。
	/// </summary>
	/// <returns>スキンモデル</returns>
	Model& GetModel()
	{
		return m_model;
	}
	/*!
	* @brief	モデルの前方方向を取得。
	*/
	const Vector3& GetForward() const
	{
		return m_forward;
	}
	/*!
	* @brief	モデルの横方方向を取得。
	*/
	const Vector3& GetRight() const
	{
		return m_right;
	}
	/*
	void SetLight(int light, CVector4 direction, float color) {
		m_model.SetLight(light, direction, color);
	}
	/// <summary>
	/// 影を設定する関数。
	/// 基本はtrue。
	/// </summary>
	/// <param name="shadow">影を設定するかどうか。</param>
	void SetShadowCaster(bool shadow) {
		m_isShadow = shadow;
	}
	/// <summary>
	/// シャドウレシーバーのフラグを設定する。
	/// </summary>
	/// <param name="flag">trueを渡すとシャドウレシーバーになる</param>
	/// <remarks>
	/// シャドウレシーバーとは影を落とされるオブジェクトのことです。
	/// シャドウキャスターによって生成された、シャドウマップを利用して
	/// 自身に影を落とします。
	/// オブジェクトがシャドウレシーバーかつシャドウキャスターになっている場合は
	/// セルフシャドウ(自分の影が自分に落ちる)を行うことができます。
	/// </remarks>
	void SetShadowReciever(bool flag)
	{
		m_model.SetShadowReciever(flag);
	}
	/// <summary>
	/// ディレクションライトの方向をセット。
	/// </summary>
	/// <param name="LDir">方向</param>
	void SetDirectionLightDirection(CVector4 LDir) {
		m_model.SetDirectionLightDirection(LDir);
	}
	/// <summary>
	///ディレクションライトの色をセット。
	/// </summary>
	/// <param name="LColor">色</param>
	void SetDirectionLightColor(CVector4 LColor) {
		m_model.SetDirectionLightColor(LColor);
	}
	/// <summary>
	/// スペキュラの累乗数をセット。
	/// </summary>
	/// <param name="spec">累乗数</param>
	void SetSpec(float spec) {
		m_model.SetSpec(spec);
	}
	/// <summary>
	/// アンビエントライトをセット。
	/// </summary>
	/// <param name="spec">アンビエントライト</param>
	void SetAmbientLight(Vector3 ambientLight) {
		m_model.SetAmbientLight(ambientLight);
	}*/
private:
	Model		m_model;								//スキンモデル。
	Vector3		m_pos = Vector3::Zero;
	Quaternion		m_rot = Quaternion::Identity;
	Vector3		m_scale = Vector3::One;
	bool			m_isActive = true;
	bool			m_isUpdate = false;						//Update関数が呼ばれたかどうか。
	Vector3		m_forward = Vector3::Front;			//カメラの前方。
	Vector3		m_right = Vector3::Right;			//カメラの右。
	Matrix			m_viewMatrixInv = Matrix::Identity;	//ビューの逆行列。
	bool			m_isShadow = true;						//影を落とすかどうか。
};