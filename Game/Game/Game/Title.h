#pragma once
class Title : public IGameObject
{
public:
	//�����傫���ύX�����Ǝv���̂ŁA�ȈՏ��������B
	Title();
	~Title();
	bool Start()override;
	void Update()override;
private:
	Sprite* m_tileSprite = nullptr;
	SpriteInitData m_spriteInitData;
};

