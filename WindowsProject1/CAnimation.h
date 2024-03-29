#pragma once
#include"global.h"

class CAnimator;
class CTexture;

struct tAnimFrm
{
	// 각각의 한프레임이 어떻게 동작하는지 기억하기 위해 구조체 선언
	Vec2	vLT;
	// 텍스쳐 내에서 좌상단
	Vec2	vSlice;
	// 자를 사이즈 영역
	Vec2	vOffset;

	float	fDuration;
	// 유지를 시킬 시간


};


class CAnimation
{
private:
	wstring				m_strName;
	CAnimator*			m_pAnimator;
	CTexture*			m_pTex; // Animation 이 사용하는 텍스쳐

	vector<tAnimFrm>	m_vecFrm; // 모든 프레임 정보
	int					m_iCurFrm; // 현재 프레임

	float				m_fAccTime; // 시간 누적
	bool				m_bFinish;  // 재생 끝 도달 여부
public:
	const wstring& GetName(){return m_strName;}
	bool IsFinish() { return m_bFinish; }
	void SetFrame(int _iFrameIdx)
	{
		m_bFinish = false;
		m_iCurFrm = _iFrameIdx;
		m_fAccTime = 0.f;
	}

	tAnimFrm& GetFrame(int _iIdx) { return m_vecFrm[_iIdx]; }
	UINT GetMaxFrame() { return (UINT)m_vecFrm.size(); }

private:
	void SetName(const wstring& _strName) { m_strName = _strName; }
	

public:
	void update();
	void render(HDC _dc);


	void Create(CTexture* _pTex, Vec2 _vLT, Vec2 _SliceSize, Vec2 _vStep, float _fDuration,UINT _iFrameCount);

public:

	CAnimation();
	~CAnimation();
	friend class CAnimator;
};

