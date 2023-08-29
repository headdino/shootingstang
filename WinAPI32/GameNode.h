#pragma once
class GameNode
{

public:
	//S_OK
	//���������� ȣ�� �� ���
	//
	//E_FAIL
	//�Լ��� ȣ���ϴ� �߿� ������ ���� ���
	//���� �����Լ�
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

