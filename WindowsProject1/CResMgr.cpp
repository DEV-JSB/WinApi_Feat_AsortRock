#include "pch.h"
#include "CResMgr.h"
#include "CTexture.h"
#include "CPathMgr.h"
CResMgr::CResMgr()
{

}

CResMgr::~CResMgr()
{
	map<wstring, CTexture*>::iterator iter = m_mapTex.begin();
	Safe_Delete_Map(m_mapTex);
}
CTexture* CResMgr::FindTexture(const wstring& _strKey)
{
	// 맵의 반호나은 iterator 로 받아야 한다.
	map<wstring,CTexture*>::iterator iter = m_mapTex.find(_strKey);

	if (iter == m_mapTex.end())
		return nullptr;
	return iter->second;
}

CTexture* CResMgr::LoadTexture(const wstring& _strkey, const wstring& _strRelativePath)
{
	//이미 로딩된 리소스라면 굳이 새로 만들 필요가 없다.
	CTexture* pTex = FindTexture(_strkey);
	if (pTex != nullptr)
		return pTex;

	wstring strFilePath = CPathMgr::GetInst()->GetContentPath();
	strFilePath += _strRelativePath;

	pTex = new CTexture;
	pTex->Load(strFilePath);

	pTex->SetKey(_strkey);

	// 리소스 너가 니 자신의 경로를 알라!
	pTex->SetKey(_strkey);
	pTex->SetRelativePath(_strRelativePath);

	m_mapTex.insert(make_pair(_strkey, pTex));

	return pTex;
}


