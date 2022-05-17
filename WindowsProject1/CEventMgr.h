#pragma once

struct tEvent
{
	EVENT_TYPE eEven;
	DWORD lParam;
	DWORD wParam;
};
class CEventMgr
{
	SINGLE(CEventMgr);



private:
	vector<tEvent> m_vecEven;
public:
	void update();
};

