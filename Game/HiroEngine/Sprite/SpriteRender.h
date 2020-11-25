#pragma once

class SpriteRender :public IGameObject
{
public:
	SpriteRender();
	~SpriteRender();
	bool Start() override;
	void Update() override;
	void DrawHUD() override;
	/// <summary>
	/// �������B
	/// </summary>
	/// <param name="texFilePath">�t�@�C���p�X�B</param>
	/// <param name="w">�����B</param>
	/// <param name="h">�c���B</param>
	void Init(const char* texFilePath, float w, float h);
	/// <summary>
	/// �f�[�^���Z�b�g�B
	/// </summary>
	/// <param name="pos">���W�B</param>
	/// <param name="rot">��]�B</param>
	/// <param name="scale">�g�嗦�B</param>
	void SetData(const Vector2& pos, const Quaternion rot, const Vector3 scale)
	{
		m_pos = Vector3{ pos.x,pos.y, 0.0f };
		m_rot = rot;
		m_scale = scale;
	}
	/// <summary>
	/// ���W���Z�b�g�B
	/// </summary>
	void SetPos(const Vector2& pos)
	{
		m_pos = Vector3{ pos.x,pos.y, 0.0f };
	}
	/// <summary>
	/// ���W���擾�B
	/// </summary>
	/// <param name="m_rot">���W�B</param>
	Vector2 GetPos()
	{
		Vector2 pos = { m_pos.x,m_pos.y };
		return pos;
	}
	/// <summary>
	/// ��]���Z�b�g�B
	/// </summary>
	void SetRot(const Quaternion rot)
	{
		m_rot = rot;
		m_rot.Multiply(Quaternion::SpriteRot());
		m_isMulti = true;
	}
	/// <summary>
	/// ��]���擾�B
	/// </summary>
	/// <param name="m_rot">��]�B</param>
	Quaternion GetRot()
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
			m_rot.Multiply(Quaternion::SpriteRot());
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
	Sprite				m_sprite;
	Vector3				m_pos = Vector3::Zero;
	Quaternion			m_rot = Quaternion::Identity;
	Vector3				m_scale = Vector3::One;
	float				m_alpha = 1.0f;					//�X�v���C�g�̃��l�B
	bool				m_isActive = true;				//�摜���h���[����Ă��邩�ǂ����B
	bool				m_isMulti = false;				//�摜�𔽓]���������ǂ����B
};

