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

	bool		m_bAllive; // Dead üũ�� ���� bool

private:
	void SetDead() { m_bAllive = false; }
	// ���� �̺�Ʈ �Ŵ����� �ǵ帱 �� �ִ� �Լ�
	// �ڽĿ��Ե� �������� �ʰڴ�.
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
	// ��� ������Ʈ�� finalupdate �� �θ� �˾Ƽ� ó���� �ϴ� 
	// �ڽ��� �������̵��� �� �ϵ��� ���ƾ��Ѵ�.
	virtual void finalupdate() final;


	void component_render(HDC _dc);
	
	virtual CObject* Clone() = 0;

public:
	CObject();

	CObject(const CObject& _origin);

	virtual ~CObject();

	friend class CEventMgr;
};

