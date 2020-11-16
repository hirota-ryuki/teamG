#pragma once
#include"Player/Player.h"
class Player;
class test :
	public IGameObject
{
public:
	test();
	~test();
	bool Start() override;
	void Update() override; //{};
private:
	Player* m_player = nullptr;
};

