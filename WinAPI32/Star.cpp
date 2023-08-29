#include "stdafx.h"
#include "Star.h"


Star::Star()
{
	ZeroMemory(m_pl, sizeof(m_pl));
	ZeroMemory(&m_rcWall, sizeof(m_rcWall));

	//널초기화
}


Star::~Star()
{
}

HRESULT Star::init()
{
	m_pl[0].p = PointMake(60.0f, WINSIZEY - 60.0f);
	m_pl[1].p = PointMake(WINSIZEX - 60.0f, WINSIZEY - 60.0f);

	m_pl[0].rc = RectMakeCenter(m_pl[0].p.x, m_pl[0].p.y, 100.0f, 100.0f);
	m_pl[1].rc = RectMakeCenter(m_pl[1].p.x, m_pl[1].p.y, 100.0f, 100.0f);


	m_pl[0].angle = 60.0f;
	m_pl[1].angle = 120.0f;

	m_pl[0].hp = 100.0f;
	m_pl[1].hp = 100.0f;
	m_pl[0].frame = 1;
	m_pl[1].frame = 0;

	m_rcWall = RectMake(350.0f, WINSIZEY - 178.0f, 100.0f, 178.0f);
	m_turn = TURN_1p;

	m_power = 0.0f;
	m_gravity = 0.0f;


	return S_OK;
}

void Star::release()
{
}

void Star::update()
{
	
	if (KEYMANAGER->StayKeyDown(VK_UP))//0,1,2
	{
		if (m_turn < TURN_2p) m_pl[0].angle += g_ETime * 60.0f;
		else m_pl[1].angle -= g_ETime * 60.0f;
	}
	if (KEYMANAGER->StayKeyDown(VK_DOWN) )//6,7,8
	{
		if (m_turn < TURN_2p) m_pl[0].angle -= g_ETime * 60.0f;
		else m_pl[1].angle += g_ETime * 60.0f;
	}
	// 키를 누를때 힘값을 주기
	if (KEYMANAGER->StayKeyDown(VK_SPACE))
	{
		m_power += g_ETime * 100.0f;
		if (m_power > 100)m_power = 0.0f;

		if (m_turn < TURN_2p)
		{
			m_pl[0].frame = 3;
		}
		else
		{
			m_pl[1].frame = 2;
		}

	}
	//발사 되는 순간
	if (KEYMANAGER->isKeyUp(VK_SPACE))
	{
		if (m_turn < TURN_2p)
		{
			m_pl[0].frame = 1;
			m_rcEgg = RectMakeCenter(m_pl[0].p.x, m_pl[0].p.y, 50.0f, 50.0f);
			m_turn = TURN_1pFire;
		}
		else
		{
			m_pl[1].frame = 0;
			m_rcEgg = RectMakeCenter(m_pl[1].p.x, m_pl[1].p.y, 50.0f, 50.0f);
			m_turn = TURN_2pFire;
		}
	}
	//발사 되는 중
	if (m_turn == TURN_1pFire)
	{
		m_rcEgg.left += cosf(m_pl[0].angle*TORADIAN)*m_power*g_ETime *3.0f;
		m_rcEgg.right += cosf(m_pl[0].angle*TORADIAN)*m_power*g_ETime *3.0f;
		m_rcEgg.top -= sinf(m_pl[0].angle*TORADIAN)*m_power*g_ETime *3.0f;
		m_rcEgg.bottom -= sinf(m_pl[0].angle*TORADIAN)*m_power*g_ETime *3.0f;
		m_rcEgg.top += m_gravity;
		m_rcEgg.bottom += m_gravity;
		m_gravity += g_ETime;

		//바닥에 닿은 순간
		if (m_rcEgg.top > WINSIZEY)
		{
			m_gravity = 0.0f;
			m_power = 0.0f;
			m_turn = TURN_2p;
		}
		//벽에 닿았을때
		if (IntersectRect(m_rcEgg, m_rcWall))
		{
			m_gravity = 0.0f;
			m_power = 0.0f;
			m_turn = TURN_2p;
		}

		//플레이어에게 맞추는 경우
		if (IntersectRect(m_rcEgg, m_pl[1].rc))
		{
			m_gravity = 0.0f;
			m_power = 0.0f;
			m_turn = TURN_2p;
			m_pl[1].hp -= 25.0f;
		}

	}

	if (m_turn == TURN_2pFire)
	{
		m_rcEgg.left += cosf(m_pl[1].angle*TORADIAN)*m_power*g_ETime *3.0f;
		m_rcEgg.right += cosf(m_pl[1].angle*TORADIAN)*m_power*g_ETime *3.0f;
		m_rcEgg.top -= sinf(m_pl[1].angle*TORADIAN)*m_power*g_ETime *3.0f;
		m_rcEgg.bottom -= sinf(m_pl[1].angle*TORADIAN)*m_power*g_ETime *3.0f;
		m_rcEgg.top += m_gravity;
		m_rcEgg.bottom += m_gravity;
		m_gravity += g_ETime;

		//바닥에 닿은 순간
		if (m_rcEgg.top > WINSIZEY)
		{
			m_gravity = 0.0f;
			m_power = 0.0f;
			m_turn = TURN_1p;
		}
		//벽에 닿았을때
		if (IntersectRect(m_rcEgg, m_rcWall))
		{
			m_gravity = 0.0f;
			m_power = 0.0f;
			m_turn = TURN_1p;
		}

		//플레이어에게 맞추는 경우
		if (IntersectRect(m_rcEgg, m_pl[0].rc))
		{
			m_gravity = 0.0f;
			m_power = 0.0f;
			m_turn = TURN_1p;
			m_pl[0].hp -= 25.0f;
		}

	}




}

void Star::render()
{
	//알
	if (m_turn % 2 == 1)
	{
		IMGMANAGER->render("Egg", g_MemDC, m_rcEgg.left, m_rcEgg.top);
	}

	HBRUSH brush = CreateSolidBrush(RGB(0, 255, 0));
	HBRUSH obrush = static_cast<HBRUSH>(SelectObject(g_MemDC,brush));
	//hp바
	RectangleMake(g_MemDC, static_cast<int>(m_pl[0].rc.left), static_cast<int>(m_pl[0].rc.top - 30.0f),
		static_cast<int>(m_pl[0].hp), 20);
	RectangleMake(g_MemDC, static_cast<int>(m_pl[1].rc.left), static_cast<int>(m_pl[1].rc.top - 30.0f),
		static_cast<int>(m_pl[1].hp), 20);

	SelectObject(g_MemDC, obrush);
	DeleteObject(brush);


	HBRUSH brush2 = CreateSolidBrush(RGB(255, 0, 0));
	HBRUSH obrush2 = static_cast<HBRUSH>(SelectObject(g_MemDC, brush2));
	//파워바
	if (m_turn < TURN_2p)
	{
		RectangleMake(g_MemDC, static_cast<int>(m_pl[0].rc.left), static_cast<int>(m_pl[0].rc.top - 60.0f),
			static_cast<int>(m_power), 20);
	}
	else
	{
		RectangleMake(g_MemDC, static_cast<int>(m_pl[1].rc.left), static_cast<int>(m_pl[1].rc.top - 60.0f),
			static_cast<int>(m_power), 20);
	}
	SelectObject(g_MemDC, obrush2);
	DeleteObject(brush2);



	//포신
	if (m_turn < TURN_2p)
	{
		LineMake(g_MemDC, static_cast<int>(m_pl[0].p.x), static_cast<int>(m_pl[0].p.y),
			static_cast<int>(m_pl[0].p.x + cosf(m_pl[0].angle*TORADIAN)* 140.0f),
			static_cast<int>(m_pl[0].p.y - sinf(m_pl[0].angle*TORADIAN)* 140.0f));
	}
	else
	{
		LineMake(g_MemDC, static_cast<int>(m_pl[1].p.x), static_cast<int>(m_pl[1].p.y),
			static_cast<int>(m_pl[1].p.x + cosf(m_pl[1].angle*TORADIAN)* 140.0f),
			static_cast<int>(m_pl[1].p.y - sinf(m_pl[1].angle*TORADIAN)* 140.0f));
	}


	IMGMANAGER->frameRender("Yoshi", g_MemDC, m_pl[0].frame, 0, m_pl[0].rc.left, m_pl[0].rc.top, 100, 120);
	IMGMANAGER->frameRender("Yoshi", g_MemDC, m_pl[1].frame, 0, m_pl[1].rc.left, m_pl[1].rc.top, 100, 120);
	IMGMANAGER->render("Wall", g_MemDC,m_rcWall.left, m_rcWall.top,100,178);



}
