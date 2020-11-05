#pragma once
#pragma once
//NewGO�̗D�揇��
enum Prio {
	GOPrio_Defalut = 2,
	GOPrio_Sprite,
	GOPrio_DrawAfter,
	GOPrio_num,
};

class IGameObject
{
public:
	//���N���X�ɂ͉��z�f�X�g���N�^���K�v
	//�Y��Ȃ��悤��
	virtual ~IGameObject() {}

	/// <summary>
	/// �J�n�֐��B
	/// </summary>
	virtual bool Start() = 0;

	/// <summary>
	/// �X�V�֐��B
	/// </summary>
	virtual void Update() = 0;
	/// <summary>
	/// �|�[�Y����Ă��Ȃ��������Ă΂��X�V�֐�
	/// </summary>
	/// <remarks>
	/// ���̊֐��̓Q�[�����|�[�Y��ԂɂȂ�ƌĂ΂�Ȃ��Ȃ�܂��B
	/// �|�[�Y���Ɏ~�߂����X�V�����Ȃǂ́A���̊֐����I�[�o�[���C�h���Ď������Ă��������B
	/// </remarks>
	virtual void Update_NotPause() {}
	/// <summary>
	/// �폜�̒��O�ɌĂ΂��֐��B
	/// </summary>
	virtual void OnDestroy() {}

	/// <summary>
	///  �`��֐��B
	/// </summary>
	virtual void Draw() {}

	/// <summary>
	/// HUD�`�掞�ɌĂ΂�鏈���B
	/// </summary>
	virtual void DrawHUD() {}

	/// /// <summary>
	/// HUD�`�掞�ɌĂ΂�鏈���B
	/// </summary>
	virtual void DrawFont() {}

	/// <summary>
	/// �폜���N�G�X�g���s���B
	/// </summary>
	void RequestDelete()
	{
		isRequestDelete = true;
	}

	/// <summary>
	/// �폜���N�G�X�g���󂯂Ă��邩���ׂ�B
	/// </summary>
	/// <returns>
	/// true���Ԃ��Ă�����A���N�G�X�g���󂯂Ă���B
	/// </returns>
	bool IsRequestDelete()
	{
		return isRequestDelete;
	}
	/// <summary>
	/// �J�n�֐����Ă񂾂����ׂ�B
	/// </summary>
	/// <returns>
	/// true���Ԃ��Ă�����A�J�n�֐����Ă�ł���B
	/// </returns>
	bool IsStart()
	{
		return m_isStart;
	}
	/// <summary>
	/// �J�n�֐�������������ĂԊ֐��B
	/// </summary>
	void StartEnd()
	{
		m_isStart = true;
	}
	/// <summary>
	/// �l�[���L�[���Z�b�g����֐��B
	/// </summary>
	void SetNameKey(unsigned int namekey)
	{
		m_nameKey = namekey;
	}
	/// <summary>
	/// �l�[���L�[��Ԃ��֐��B
	/// </summary>
	/// <returns>�l�[���L�[�B</returns>
	unsigned int GetNameKey()
	{
		return m_nameKey;
	}
	/// <summary>
	/// �����ꂽ��Ԃɂ���֐��B
	/// </summary>
	void SetDelete()
	{
		m_isDelete = true;
	}
	/// <summary>
	/// �����ꂽ���ǂ����B
	/// </summary>
	/// <returns>�����ꂽ�t���O�B</returns>
	bool IsDelete()
	{
		return m_isDelete;
	}
	//friend�錾�A�t�����h�N���X�͎w�肳�ꂽ�N���X��private��protected�����o�ɃA�N�Z�X���邱�Ƃ��ł���B
	friend class GameObjectManager;
private:
	bool isRequestDelete = false;		//�폜�t���O�B
	bool m_isStart = false;				//�J�n�֐����Ă΂ꂽ���ǂ����B
	bool m_isDelete = false;			//�����ꂽ��Ԃ��ǂ����B
	unsigned int m_nameKey = 0;			//���O�L�[�B
	int prio;//�D�揇�ʁB
protected:
};