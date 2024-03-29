#include "pch.h"
#include "CTexture.h"
#include"CCore.h"
CTexture::CTexture()
	: m_hBit(0)
	, m_dc(0)
	, m_bitInfo{}
{

}

CTexture::~CTexture()
{
	DeleteDC(m_dc);
	DeleteObject(m_hBit);
}

void CTexture::Load(const wstring& _strFilePath)
{
	///////////////////////////////////////////////////로드 뻘짓 씨게함;
	// bmp 파일을 그림판 에서 다시 형태를 바꿔서 저장해야 잘 불러옴;;;;
	// 그리고 뭐야 그 속성에서 디버그 솔루션 디렉토르 $(SolutionDir)Output\bin\ 변경해줘야함';
	// 파일로 부터 로딩한 데이터를 비트맵으로 생성
	m_hBit = (HBITMAP)LoadImage(nullptr, _strFilePath.c_str(), IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION | LR_LOADFROMFILE);
	assert(m_hBit);
	// 비트맵과 연결할 DC

	m_dc = CreateCompatibleDC(CCore::GetInst()->GetMainDC());
	
	// 비트맵과 DC 연결
	
	HBITMAP hPrevBit = (HBITMAP)SelectObject(m_dc, m_hBit);
	DeleteObject(hPrevBit);
	
	// 비트맵 정보를 얻어서 BITMAP 구조체에 넣음
	GetObject(m_hBit, sizeof(BITMAP), &m_bitInfo);

}
