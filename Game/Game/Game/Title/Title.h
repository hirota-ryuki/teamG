#pragma once

class Game;
class Title : public IGameObject
{
public:
	//�����傫���ύX�����Ǝv���̂ŁA�ȈՏ��������B
	Title();
	~Title();
	bool Start()override;
	void Update()override;
	void TitleInit();
private:
	//Game* m_game = nullptr;
	Sprite* m_tileSprite = nullptr;
	SpriteInitData m_spriteInitData;
};

