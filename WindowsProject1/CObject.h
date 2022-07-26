#pragma once
#include"global.h"

#include"CCamera.h"

class CCollider;
class CAnimator;

class CObject
{
private:

	wstring		m_strName;

	Vec2		m_vPos;
	Vec2		m_vScale;

	CCollider*	m_pCollider;
	CAnimator*  m_pAnimator;

	bool		m_bAllive; // Dead 체크를 위한 bool

private:
	void SetDead() { m_bAllive = false; }
	// 오직 이벤트 매니저만 건드릴 수 있는 함수
	// 자식에게도 공개하지 않겠다.
public:
	void SetPos(Vec2 _vPos) { m_vPos = _vPos; }
	void SetScale(Vec2 _vScale) { m_vScale = _vScale; }

	Vec2 GetPos() { return m_vPos; }
	Vec2 GetScale() { return m_vScale; }

	void SetName(const wstring& _strName) { m_strName = _strName; }
	const wstring& GetName() { return m_strName; }

	CCollider* GetCollider() { return m_pCollider; }
	CAnimator* GetAnimator() { return m_pAnimator; }


	bool IsDead() { return !m_bAllive; }

	void CreateCollider();
	void CreateAnimator();


	virtual void OnCollision(CCollider* _pOther) {}
	virtual void OnCollisionEnter(CCollider* _pOther) {}
	virtual void OnCollisionExit(CCollider* _pOther) {}

public:
	virtual void update() = 0;
	virtual void render(HDC _dc);
	// 모든 오브젝트의 finalupdate 는 부모가 알아서 처리를 하니 
	// 자식이 오버라이딩을 못 하도록 막아야한다.
	virtual void finalupdate() final;


	void component_render(HDC _dc);
	
	virtual CObject* Clone() = 0;

public:
	CObject();

	CObject(const CObject& _origin);

	virtual ~CObject();

	friend class CEventMgr;
};

