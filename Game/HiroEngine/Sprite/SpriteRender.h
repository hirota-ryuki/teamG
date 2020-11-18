#pragma once

class SpriteRender :public IGameObject
{
public:
	SpriteRender();
	~SpriteRender();
	bool Start() override;
	void Update() override;
	void DrawHUD() override;
	void SetData(const CVector2& pos, const CQuaternion rot, const CVector3 scale)
	{
		m_pos = CVector3{ pos.x,pos.y, 0.0f };
		m_rot = rot;
		m_scale = scale;
	}
	/// <summary>
	/// ���W���Z�b�g�B
	/// </summary>
	void SetPos(const CVector2& pos)
	{
		m_pos = CVector3{ pos.x,pos.y, 0.0f };
	}
	/// <summary>
	/// ���W���擾�B
	/// </summary>
	/// <param name="m_rot">���W�B</param>
	CVector2 GetPos()
	{
		CVector2 pos = { m_pos.x,m_pos.y };
		return pos;
	}
	/// <summary>
	/// ��]���Z�b�g�B
	/// </summary>
	void SetRot(const CQuaternion rot)
	{
		m_rot = rot;
		m_rot.Multiply(CQuaternion::SpriteRot());
		m_isMulti = true;
	}
	/// <summary>
	/// ��]���擾�B
	/// </summary>
	/// <param name="m_rot">��]�B</param>
	CQuaternion GetRot()
	{
		return m_rot;
	}
	/// <summary>
	/// �摜�𔽓]������֐��B
	/// ���̉摜�����]����ĕ`�悳��邽�߁A
	/// ��񂾂����s�����Ȃ���΂Ȃ�Ȃ��B
	/// </summary>
	void RotMultiply()
	{
		if (!m_isMulti) {
			m_rot.Multiply(CQuaternion::SpriteRot());
			m_isMulti = true;
		}
	}
	/// <summary>
	/// �A���t�@�l���Z�b�g�B
	/// </summary>
	/// <param name="m_alpha">�A���t�@�l�B</param>
	void SetAlpha(const float alpha)
	{
		m_alpha = alpha;
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
	/// �������B
	/// </summary>
	/// <param name="texFilePath">�t�@�C���p�X�B</param>
	/// <param name="w">�����B</param>
	/// <param name="h">�c���B</param>
	void Init(const wchar_t* texFilePath, float w, float h);
	/// <summary>
	/// �X�v���C�g���Z�b�g�B
	/// </summary>
	/// <param name="sprite">�X�v���C�g�B</param>
	void SetSprite(const Sprite& sprite) {
		m_sprite = sprite;
	}
	/// <summary>
	/// �X�v���C�g���Q�b�g�B
	/// </summary>
	/// <returns>�X�v���C�g�B</returns>
	Sprite GetSprite()
	{
		return m_sprite;
	}
private:
	Sprite		m_sprite;
	CVector3	m_pos = CVector3::Zero();
	CQuaternion m_rot = CQuaternion::Identity();
	CVector3	m_scale = CVector3::One();
	float		m_alpha = 1.0f;					//�X�v���C�g�̃��l�B
	bool		m_isActive = true;				//�摜���h���[����Ă��邩�ǂ����B
	bool		m_isMulti = false;				//�摜�𔽓]���������ǂ����B
};

