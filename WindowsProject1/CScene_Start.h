#pragma once
#include"CScene.h"
class CScene_Start :
	public CScene
{
public:
	virtual void Enter();
	virtual void Exit();
	virtual void update();
public:
	CScene_Start();
	~CScene_Start();
};

