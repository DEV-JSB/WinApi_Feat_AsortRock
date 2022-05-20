#include "pch.h"
#include "CScene.h"
#include"CObject.h"

void CScene::update()
{
	for (UINT i = 0; i < (UINT)GROUP_TYPE::END; ++i)
	{
		for (size_t j = 0; j < m_arrvecObj[i].size(); ++j)
		{
			if (!m_arrvecObj[i][j]->IsDead())
			{
				m_arrvecObj[i][j]->update();
			}
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
		vector<CObject*>::iterator iter = m_arrvecObj[i].begin();
		for (; iter != m_arrvecObj[i].end();)
		{
			if (!(*iter)->IsDead())
			{
				(*iter)->render(_hdc);
				++iter;
			}
			else
			{
				iter = m_arrvecObj[i].erase(iter);
			}
		}
	}
}

void CScene::DeleteGroup(GROUP_TYPE _eTarget)
{
	Safe_Delete_Vec<CObject*>(m_arrvecObj[(UINT)_eTarget]);
}

void CScene::DeleteAll()
{
	for (UINT i = 0; i < (UINT)GROUP_TYPE::END; ++i)
	{
		DeleteGroup((GROUP_TYPE)i);
	}
}

CScene::CScene()
{
}

CScene::~CScene()
{
	for (UINT i = 0; i < (UINT)GROUP_TYPE::END; ++i)
	{
		// m_arrvecObj[i] 그룹 벡터의 j 물체 삭제
		for (size_t j = 0; j < m_arrvecObj[i].size(); ++i)
		{
			delete m_arrvecObj[i][j];
		}
	}
}
