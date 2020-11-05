#pragma once
class test :
	public IGameObject
{
public:
	test();
	~test();
	bool Start() override { return true; };
	void Update() override {};
private:
};

