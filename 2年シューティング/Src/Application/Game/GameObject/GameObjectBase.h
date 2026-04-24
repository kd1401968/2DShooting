#pragma once
class c_GameObjectBase 
{
public:

	c_GameObjectBase() {}
	virtual ~c_GameObjectBase() {}

	virtual  void Init() {};
	virtual void Update() {};
	virtual void Draw() {};
	virtual void Release() {};

};