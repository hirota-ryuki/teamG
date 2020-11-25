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
	void OnDestroy()override;
	void TitleState();
private:
	SpriteRender* m_title = nullptr;
	bool isGameStart_flag = false;
};

