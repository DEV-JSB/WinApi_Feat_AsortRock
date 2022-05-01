#pragma once
class CTimeMgr
{
	SINGLE(CTimeMgr);
private:
	LARGE_INTEGER	m_llCurCount;
	LARGE_INTEGER	m_llPrevCount;

	LARGE_INTEGER	m_llFrequency; // : 1 �ʿ� ��ŭ ���� ������ ���� ���´�.
	
	double			m_dDT; // ������ ���� �ð� ��
	double			m_dAcc; // ������ ���� �ð� �� ������Ű��
	UINT			m_iCallCount; // �Լ� ȣ�� Ƚ�� üũ
	UINT			m_iFPS; // �ʴ� ȣ�� Ƚ��
								   
	// 1. FPS : 1�� ���� �� �������� �� �� �ִ��� ( Delta Time )
	// 2. 
public:
	void Init();
	void update();
	void render();

public:
	double GetDT() { return m_dDT; }
	float GetfDT() { return (float)m_dDT; }
};

