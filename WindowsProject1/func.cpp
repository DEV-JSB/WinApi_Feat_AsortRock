#include"pch.h"
#include"func.h"


#include "CEventMgr.h"


void CreateObject(CObject* _pObj, GROUP_TYPE _eGroup)
{
	tEvent evn = {};
	evn.eEven = EVENT_TYPE::CREATE_OBJECT;
	evn.lParam = (DWORD_PTR)_pObj; // ������ ���������� ��ǻ� �츮�� �ּҶ�¤� �ä��� �˰��ִ�.
	evn.wParam = (DWORD_PTR)_eGroup; // ������ ���������� ��ǻ� �츮�� enum �̶�°� �� �� �ִ�.

	CEventMgr::GetInst()->AddEvent(evn);
}

void DeleteObject(CObject* _pObj)
{
	tEvent evn = {};
	evn.eEven = EVENT_TYPE::DELETE_OBJECT;
	evn.lParam = (DWORD_PTR)_pObj; // ������ ���������� ��ǻ� �츮�� �ּҶ�¤� �ä��� �˰��ִ�.

	CEventMgr::GetInst()->AddEvent(evn);
}

void ChangeScene(SCENE_TYPE _eNext)
{
	tEvent evn = {};
	evn.eEven = EVENT_TYPE::SCENE_CHANGE;
	evn.lParam = (DWORD_PTR)_eNext;

	CEventMgr::GetInst()->AddEvent(evn);

}
