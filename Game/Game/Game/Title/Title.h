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
	void OnDestroy()override;
	void TitleState();
private:
	SpriteRender* m_title = nullptr;
	bool isGameStart_flag = false;
};

