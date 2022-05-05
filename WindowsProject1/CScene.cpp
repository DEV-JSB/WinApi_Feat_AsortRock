#include "pch.h"
#include "CScene.h"
#include"CObject.h"

void CScene::update()
{
	for (UINT i = 0; i < (UINT)GROUP_TYPE::END; ++i)
	{
		for (size_t j = 0; j < m_arrvecObj[i].size(); ++j)
		{
			m_arrvecObj[i][j]->update();
		}
	}
}

void CScene::finalupdate()
{
	for (UINT i = 0; i < (UINT)GROUP_TYPE::END; ++i)
	{
		for (size_t j = 0; j < m_arrvecObj[i].size(); ++j)
		{
			m_arrvecObj[i][j]->finalupdate();
		}
	}
}

void CScene::render(HDC _hdc)
{
	for (UINT i = 0; i < (UINT)GROUP_TYPE::END; ++i)
	{
		for (size_t j = 0; j < m_arrvecObj[i].size(); ++j)
		{
			m_arrvecObj[i][j]->render(_hdc);
		}
	}
}

CScene::CScene()
{
}

CScene::~CScene()
{
	for (UINT i = 0; i < (UINT)GROUP_TYPE::END; ++i)
	{
		// m_arrvecObj[i] �׷� ������ j ��ü ����
		for (size_t j = 0; j < m_arrvecObj[i].size(); ++i)
		{
			delete m_arrvecObj[i][j];
		}
	}
}
