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
	// ���� ��ȣ���� iterator �� �޾ƾ� �Ѵ�.
	map<wstring,CTexture*>::iterator iter = m_mapTex.find(_strKey);

	if (iter == m_mapTex.end())
		return nullptr;
	return iter->second;
}

CTexture* CResMgr::LoadTexture(const wstring& _strkey, const wstring& _strRelativePath)
{
	//�̹� �ε��� ���ҽ���� ���� ���� ���� �ʿ䰡 ����.
	CTexture* pTex = FindTexture(_strkey);
	if (pTex != nullptr)
		return pTex;

	wstring strFilePath = CPathMgr::GetInst()->GetContentPath();
	strFilePath += _strRelativePath;

	pTex = new CTexture;
	pTex->Load(strFilePath);

	pTex->SetKey(_strkey);

	// ���ҽ� �ʰ� �� �ڽ��� ��θ� �˶�!
	pTex->SetKey(_strkey);
	pTex->SetRelativePath(_strRelativePath);

	m_mapTex.insert(make_pair(_strkey, pTex));

	return pTex;
}


