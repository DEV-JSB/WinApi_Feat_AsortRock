#include"pch.h"
#include"func.h"

class CObject;
#include "CEventMgr.h"
void CreateObject(CObject* _pObj, GROUP_TYPE _eGroup)
{
	tEvent evn = {};
	evn.eEven = EVENT_TYPE::CREATE_OBJECT;
	evn.lParam = (DWORD_PTR)_pObj; // ������ ���������� ��ǻ� �츮�� �ּҶ�¤� �ä��� �˰��ִ�.
	evn.wParam = (DWORD_PTR)_eGroup; // ������ ���������� ��ǻ� �츮�� enum �̶�°� �� �� �ִ�.

	CEventMgr::GetInst()->AddEvent(evn);
}
