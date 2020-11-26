#pragma once
class Menu : public IGameObject
{
public:
	Menu() {};
	~Menu() {};
private:
	bool Start()override;
	void Update()override;
	void OnDestroy()override;
private:
	SpriteRender* m_menu = nullptr;
};

