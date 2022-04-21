#pragma once
class CCore
{
private:
	static CCore* g_pInst;
public:
	static CCore* GetInstance()
	{
		// ���� ȣ�� �� ��� ( static ������ �ݵ�� �ʱ�ȭ�� �ѹ��� �̷������ )
		// 2�� �̻� ȣ�� �� ���
		if (nullptr == g_pInst)
		{
			g_pInst = new CCore;
		}
		return g_pInst;
	}
	static void Release()
	{
		if (nullptr != g_pInst)
		{
			delete g_pInst;
			g_pInst = nullptr;
		}
	}
private:
	CCore();
	~CCore();
};

