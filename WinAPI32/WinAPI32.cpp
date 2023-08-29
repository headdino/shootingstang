#include "stdafx.h"
#include "MainGame.h"



//접두어 _g ,_m
// n int,short
// l long
// d double
// w word
// b bool byte
// c const
// p 포인터
// lp 롱 포인터
// sz,str 문자열
// hwnd 윈도우 핸들
// h 리소스 핸들


// 전역 변수:
//실행되고 있는 프로그램의 메모리 시작주소를 가지고 있다.
//프로그램당 하나의 인스턴스를 가지고 관리함
//윈도우창을 관리하는 핸들
//윈도우창 여러개 사용 하는 경우 여러개의 핸들이 필요함
HINSTANCE	g_hInst;                                // 현재 인스턴스입니다.]
HWND		g_hwnd;
FPOINT		g_ptMouse = { 0.0f , 0.0f };
FPOINT		g_ptCam = { 0.0f , 0.0f };

MainGame*	Mg;


//LPSTER -> char*
//LPCSTER -> const char*
//LPWSTR -> wchar*
//LPCWSTR -> const wchar*
//LPTSTR
//LPCTSTR



// 이 코드 모듈에 포함된 함수의 선언을 전달합니다:
//윈도우 프로시져 : 메세지를 운영체제에 전달 강제로 운영체제가 호출해준다
//hwnd :어느 윈도우에서 발생한 메세지인지 구분
//message : 메세지 구분 번호
//wparam : 마우스 버튼의 상태 키보드 조합키의 상태를 전달한다.
//lparam : 마우스 클릭 좌표 전달
//callball 어떤 이벤트가 발생했을때 나에 알려달라고 하는것
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
void SetWindowSize(int x, int y, int width, int height);


int APIENTRY _tWinMain(HINSTANCE hInstance,
                      HINSTANCE hPrevInstance,
                      LPTSTR    lpCmdLine,
                      int       nCmdShow)
{


	WNDCLASS	wc;	//window infomation struct
	ZeroMemory(&wc, sizeof(WNDCLASS));

	// 참조하지 않은 인자에 대해 경고를 표시하지 않는다.
	UNREFERENCED_PARAMETER(lpCmdLine);

	//비트연산자   111
	//윈도우 클래스의 스타일을 지정
	wc.style = CS_HREDRAW | CS_VREDRAW;
	//메세지를 처리하는 함수를 지정(프로시져)
	wc.lpfnWndProc = static_cast<WNDPROC>(WndProc);
	//윈도우 클래스 에서 사용하고자 하는 여분의 메모리 양을 바이트 단위로 지정
	wc.cbClsExtra = 0;
	//cbClsExtra 유사하되 개별 윈도우에서 사용하고자 하는 여분의 메모리양을 지정
	wc.cbWndExtra = 0;
	//윈도우 클래스를 등록한 응용 프로그램의 인스턴스 핸들
	wc.hInstance = hInstance;
	//클래스 커서를 지정
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	//타이틀바의 좌상단에 보여줄 아이콘 윈도우가 최소화 되었을때 보여줄 아이콘을 지정
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	//윈도우 작업영역에 칠할 배경 브러시
	wc.hbrBackground = static_cast<HBRUSH>(GetStockObject(GRAY_BRUSH));
	//등록하고자 하는 윈도우의 이름
	wc.lpszClassName = WINNAME;
	//클래스로부터 만들어진 윈도우가 사용할 메뉴 지장
	wc.lpszMenuName = nullptr;

	//운영체제의 레지스터에 이 프로그램을 등록한다.
	if (RegisterClass(&wc) == false)
	{
		return FALSE;
	}

	//핸들 인스턴스 저장
	g_hInst = hInstance;
	g_hwnd = CreateWindow(
		WINNAME,				//윈도우 클래스의 이름
		WINNAME,				//윈도우 타이틀바 이름
		WS_OVERLAPPEDWINDOW,	//윈도우 스타일
		WINSTARTX,					    //창의 시작 x좌표
		WINSTARTY,						//창의 시작 y좌표
		WINSIZEX,					//창의 가로크기
		WINSIZEY,					//창의 세로크기
		nullptr,				//부모 윈도우
		nullptr,				//메뉴 핸들
		hInstance,				//인스턴스 지정
		hInstance				
	);

	if (g_hwnd == false)
	{
		return FALSE;
	}

	//화면 작업 사이즈 영역 계산
	SetWindowSize(WINSTARTX, WINSTARTY, WINSIZEX, WINSIZEY);


	Mg = new MainGame;
	//메인게임 클래스 초기화 실패했다면 바로 종료
	if (FAILED(Mg->init()))
	{
		return 0;
	}


	
	//생성한 프로그램을 디스플레이의 최상위로 올린다.
	ShowWindow(g_hwnd, nCmdShow);
	
	//메인 윈도우 갱신
	UpdateWindow(g_hwnd);

    MSG msg;
	ZeroMemory(&msg, sizeof(MSG));

    // 기본 메시지 루프입니다:
	//겟 메세지는 메세지가 입력될때 까지 계속 대기하고 있음
    /*while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }*/

	//TranslateMessage : 키보드 입력 메세지를 처리
	//입력키가 문자인지 확인 후 대문자,소문자,한글,영문 등등
	//WM_CHAR 메세지를 발생시킨다.

	//DispatchMessage : 윈도우 프로시져에 전달된 메세지를 실제 윈도우에 전달
	
	while (1)
	{
		if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT)
				break;
			TranslateMessage(&msg);
			DispatchMessage(&msg);

		}
		else
		{
			TIMEMANAGER->SetFrame(FIXFRAME);
			Mg->update();
			Mg->render();
		}
	}

	Mg->release();
	SAFE_DELETE(Mg);

	DestroyWindow(g_hwnd);
	UnregisterClass(WINNAME, hInstance);

    return static_cast<int> (msg.wParam);
}



LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	return Mg->MainProc(hWnd, message, wParam, lParam);
}

void SetWindowSize(int x, int y, int width, int height)
{
	RECT rc;
	rc.left = 0;
	rc.top = 0;
	rc.right = width;
	rc.bottom = height;
	//실제 윈도우 크기 조정
	AdjustWindowRect(&rc, WS_CAPTION | WS_SYSMENU, false);
	//위 RECT 정보로 윈도우 사이즈 셋팅
	SetWindowPos(g_hwnd, NULL, x, y, (rc.right - rc.left), (rc.bottom - rc.top),
		SWP_NOZORDER | SWP_NOMOVE);

}

