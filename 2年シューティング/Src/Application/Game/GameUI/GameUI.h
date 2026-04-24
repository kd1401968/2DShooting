#pragma once
class c_GameUI
{
public:

	c_GameUI() {}
	~c_GameUI() {}

	void Init();
	void Update(int i);
	void Draw();

private:

	void Release();
};