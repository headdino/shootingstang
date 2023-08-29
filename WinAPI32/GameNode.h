#pragma once
class GameNode
{

public:
	//S_OK
	//성공적으로 호출 된 경우
	//
	//E_FAIL
	//함수를 호출하는 중에 에러가 생길 경우
	//순수 가상함수
	virtual HRESULT init() = 0;
	virtual void release() = 0;
	virtual void update()  = 0;
	virtual void render()  = 0;
	LRESULT MainProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	//HDC& getHDC() { return m_hdc; }
	//HDC getHDC() { return m_hdc; }
	//void SetHDC(HDC _hdc) { m_hdc = _hdc; }
	GameNode();
	virtual ~GameNode();
};

