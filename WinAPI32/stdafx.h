#pragma once

//디버그,문자집합 매크로
#if defined UNICODE && defined _DEBUG
#pragma comment(linker, "/entry:wWinMainCRTStartup /subsystem:console") 
#elif defined _MBCS && defined _DEBUG
#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")
#endif 


#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // 거의 사용되지 않는 내용을 Windows 헤더에서 제외합니다.
// Windows 헤더 파일
#include <windows.h>
#include <iostream>
#include <tchar.h>
#include <vector>
#include <map>
#include <string>

using namespace std;

//문자집합 매크로
#ifdef _UNICODE
#define _tstring wstring
#define _tcout wcout
#else
#define _tstring string
#define _tcout cout
#endif


#include "MyFunc.h"
#include "BmpImg.h"


//싱글톤 추가
#include "KeyManager.h"
#define KEYMANAGER KeyManager::GetInstance()
#include "TimeManager.h"
#define TIMEMANAGER TimeManager::GetInstance()
#define g_ETime TimeManager::GetInstance()->GetElapsedTime()
#include "ImageManager.h"
#define IMGMANAGER ImageManager::GetInstance()
#define g_MemDC ImageManager::GetInstance()->getMemDC()
#include "SoundManager.h"
#define SOUNDMANAGER SoundManager::GetInstance()




#define WINNAME _T("WinAPI 32")
#define WINSTARTX 50
#define WINSTARTY 100
#define WINSIZEX 1200
#define WINSIZEY 600
#define FIXFRAME 60.0f


#define BULLETMAX 30
#define BOSSBULLETMAX 120

enum GAME_STATE
{
	MENU,
	INGAME,
	WINGAME,
	LOSEGAME,
	EXPLAN
};

//매크로 함수
#define SAFE_DELETE(p) {if(p){delete(p); (p)=nullptr;}}
#define SAFE_DELETE_ARRAY(p) {if(p) {delete[](p); (p) = nullptr;}

//전역변수
extern HINSTANCE	g_hInst;
extern HWND			g_hwnd;
extern FPOINT		g_ptMouse;
extern FPOINT		g_ptCam;