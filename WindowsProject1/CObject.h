#pragma once

class CCollider;

class CObject
{
private:

	wstring m_strName;

	Vec2	m_vPos;
	Vec2	m_vScale;

	CCollider* m_pCollider;

public:
	void SetPos(Vec2 _vPos) { m_vPos = _vPos; }
	void SetScale(Vec2 _vScale) { m_vScale = _vScale; }

	Vec2 GetPos() { return m_vPos; }
	Vec2 GetScale() { return m_vScale; }

	void SetName(const wstring& _strName) { m_strName = _strName; }
	const wstring& GetName() { return m_strName; }

	CCollider* GetCollider() { return m_pCollider; }

	void CreateCollider();

public:
	virtual void update() = 0;
	virtual void render(HDC _dc);
	// 모든 오브젝트의 finalupdate 는 부모가 알아서 처리를 하니 
	// 자식이 오버라이딩을 못 하도록 막아야한다.
	virtual void finalupdate() final;


	void component_render(HDC _dc);
	
	virtual void OnCollision(CCollider* _pOther) {}
	virtual void OnCollisionEnter(CCollider* _pOther) {}
	virtual void OnCollisionExit(CCollider* _pOther) {}

public:
	CObject();
	virtual ~CObject();
};

