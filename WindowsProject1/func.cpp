#include"pch.h"
#include"func.h"

class CObject;
#include "CEventMgr.h"
void CreateObject(CObject* _pObj, GROUP_TYPE _eGroup)
{
	tEvent evn = {};
	evn.eEven = EVENT_TYPE::CREATE_OBJECT;
	evn.lParam = (DWORD_PTR)_pObj; // 정수로 저장했지만 사실상 우리는 주소라는ㄱ ㅓㅅ을 알고있다.
	evn.wParam = (DWORD_PTR)_eGroup; // 정수로 저장했지만 사실상 우리는 enum 이라는걸 알 고 있다.

	CEventMgr::GetInst()->AddEvent(evn);
}
