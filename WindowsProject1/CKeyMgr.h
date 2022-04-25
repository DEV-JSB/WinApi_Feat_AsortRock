#pragma once


enum class KEY_STATE
{
	NONE ,// ������ �ʾҰ� , �������� ������ �ʾҾ��� ����

	TAP , // �� ���� ���� 
	HOLD , // ������ �ִ�
	AWAY// �� �� ����
};

enum class KEY
{
	LEFT,
	RIGHT,
	UP,
	DOWN,

	Q,
	W,
	E,
	R,
	T,
	Y,
	U,
	I,
	O,
	P,
	A,
	S,
	D,
	F,
	G,
	Z,
	X,
	C,
	V,
	B,

	ALT,
	CTRL,
	LSHIFT,
	SPACE,
	ENTER,
	ESC,

	LAST
};

struct tKeyInfo
{
	KEY_STATE	eState;	// Ű�� ���°�
	bool		bPrevPush;	// ���� �����ӿ��� ���ȴ��� ����
};


class CKeyMgr
{

	SINGLE(CKeyMgr);
private:
	vector<tKeyInfo>m_vecKey;
public:
	void Init();
	void update();

public:
	KEY_STATE GetKeyState(KEY _eKey)
	{
		return m_vecKey[(int)_eKey].eState;
	}

};
