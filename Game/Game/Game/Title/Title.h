#pragma once

class Game;
class Title : public IGameObject
{
public:
	//多分大きく変更されると思うので、簡易処理だけ。
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

