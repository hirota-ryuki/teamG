#pragma once

class SkinModelRender : public IGameObject
{
public:
	SkinModelRender();
	~SkinModelRender();
	void Update() override;
	bool Start() override;
	void Draw() override;
	/// <summary>
	/// ���[���h�s����X�V�B
	/// </summary>
	void UpdateWorldMatrix();
	/// <summary>
	/// �X�L�����f���̏������B
	/// </summary>
	/// <param name="texFilePath">���f���̃t�@�C���p�X</param>
	void Init(const wchar_t* texFilePath);
	/// <summary>
	/// �@���}�b�v�̏����������B
	/// </summary>
	/// <param name="filePath">�@���}�b�v�̃t�@�C���p�X�B</param>
	void InitNormalMap(const wchar_t* filePath);
	/// <summary>
	/// �X�y�L�����}�b�v�̏����������B
	/// </summary>
	/// <param name="filePath">�X�y�L�����}�b�v�̃t�@�C���p�X�B</param>
	void InitSpecMap(const wchar_t* filePath);
	/// <summary>
	/// ���W�A��]��ݒ�
	/// �g�嗦�͐G��Ȃ��悤��
	/// </summary>
	/// <param name="pos">���W</param>
	/// <param name="rot">��]</param>
	void SetData(CVector3 pos, CQuaternion rot)
	{
		m_pos = pos;
		m_rot = rot;
	}
	
	/// <summary>
	/// ���W��ݒ�
	/// </summary>
	/// <param name="pos">���W</param>
	void SetPos(CVector3 pos)
	{
		m_pos = pos;
	}
	/// <summary>
	/// �|�W�V�������擾�B
	/// </summary>
	/// <returns>���W�B</returns>
	CVector3 GetPos()
	{
		return m_pos;
	}
	/// <summary>
	/// ��]��ݒ�
	/// </summary>
	/// <param name="pos">��]</param>
	void SetRot(CQuaternion rot)
	{
		m_rot = rot;
	}
	/// <summary>
	/// ��]���擾�B
	/// </summary>
	/// <returns>��]�B</returns>
	CQuaternion GetRot()
	{
		return m_rot;
	}
	/// <summary>
	/// �`�悷�邩�ǂ����B
	/// �Ă΂ꂽ��true��false�����ւ���B
	/// </summary>
	void ChangeActive()
	{
		m_isActive = !m_isActive;
	}
	/// <summary>
	/// �`�悷�邩�ǂ����B
	/// true��false�����w�肷��B
	/// </summary>
	void ActiveMode(bool active)
	{
		m_isActive = active;
	}
	/// <summary>
	/// �X�L�����f�����擾�B
	/// </summary>
	/// <returns>�X�L�����f��</returns>
	SkinModel& GetModel()
	{
		return m_model;
	}
	/*!
	* @brief	���f���̑O���������擾�B
	*/
	const CVector3& GetForward() const
	{
		return m_forward;
	}
	/*!
	* @brief	���f���̉����������擾�B
	*/
	const CVector3& GetRight() const
	{
		return m_right;
	}
	void SetLight(int light, CVector4 direction, float color) {
		m_model.SetLight(light, direction, color);
	}
	/// <summary>
	/// �e��ݒ肷��֐��B
	/// ��{��true�B
	/// </summary>
	/// <param name="shadow">�e��ݒ肷�邩�ǂ����B</param>
	void SetShadowCaster(bool shadow) {
		m_isShadow = shadow;
	}
	/// <summary>
	/// �V���h�E���V�[�o�[�̃t���O��ݒ肷��B
	/// </summary>
	/// <param name="flag">true��n���ƃV���h�E���V�[�o�[�ɂȂ�</param>
	/// <remarks>
	/// �V���h�E���V�[�o�[�Ƃ͉e�𗎂Ƃ����I�u�W�F�N�g�̂��Ƃł��B
	/// �V���h�E�L���X�^�[�ɂ���Đ������ꂽ�A�V���h�E�}�b�v�𗘗p����
	/// ���g�ɉe�𗎂Ƃ��܂��B
	/// �I�u�W�F�N�g���V���h�E���V�[�o�[���V���h�E�L���X�^�[�ɂȂ��Ă���ꍇ��
	/// �Z���t�V���h�E(�����̉e�������ɗ�����)���s�����Ƃ��ł��܂��B
	/// </remarks>
	void SetShadowReciever(bool flag)
	{
		m_model.SetShadowReciever(flag);
	}
	/// <summary>
	/// �f�B���N�V�������C�g�̕������Z�b�g�B
	/// </summary>
	/// <param name="LDir">����</param>
	void SetDirectionLightDirection(CVector4 LDir) {
		m_model.SetDirectionLightDirection(LDir);
	}
	/// <summary>
	///�f�B���N�V�������C�g�̐F���Z�b�g�B
	/// </summary>
	/// <param name="LColor">�F</param>
	void SetDirectionLightColor(CVector4 LColor) {
		m_model.SetDirectionLightColor(LColor);
	}
	/// <summary>
	/// �X�y�L�����̗ݏ搔���Z�b�g�B
	/// </summary>
	/// <param name="spec">�ݏ搔</param>
	void SetSpec(float spec) {
		m_model.SetSpec(spec);
	}
	/// <summary>
	/// �A���r�G���g���C�g���Z�b�g�B
	/// </summary>
	/// <param name="spec">�A���r�G���g���C�g</param>
	void SetAmbientLight(CVector3 ambientLight) {
		m_model.SetAmbientLight(ambientLight);
	}
private:
	SkinModel		m_model;								//�X�L�����f���B
	CVector3		m_pos = CVector3::Zero();
	CQuaternion		m_rot = CQuaternion::SpriteRot();
	CVector3		m_scale = CVector3::One();
	bool			m_isActive = true;
	bool			m_isUpdate = false;						//Update�֐����Ă΂ꂽ���ǂ����B
	CVector3		m_forward = CVector3::Front();			//�J�����̑O���B
	CVector3		m_right = CVector3::Right();			//�J�����̉E�B
	CMatrix			m_viewMatrixInv = CMatrix::Identity();	//�r���[�̋t�s��B
	bool			m_isShadow = true;						//�e�𗎂Ƃ����ǂ����B
};