#include "stdafx.h"
#include "monster.h"


monster::monster()
{
}


monster::~monster()
{
}

HRESULT monster::init()
{


	return S_OK;
}

void monster::release()
{
}

void monster::update()
{
	
}

void monster::render()
{

}

void monster::SwitchState()
{
	switch (m_monsterState)
	{
		//움직이는 상태일때
	case M_MOVE:
		//움직이는 타입에 따라서
		switch (m_moveType)
		{
			//x로만 이동하는지
		case ONLYX: m_monster.pt.x -= m_monster.moveSpeed * g_ETime;
			break;
			//x,y 둘다이동하는지 해줌
		case XANDY:
			m_monster.pt.x -= m_monster.moveSpeed * g_ETime;
			if (m_isUp)
			{
				m_monster.pt.y -= m_monster.moveSpeed * g_ETime;
				if (m_monster.pt.y <= 0) m_isUp = false;
			}
			else if(!m_isUp)
			{
				m_monster.pt.y += m_monster.moveSpeed * g_ETime;
				if (m_monster.rc.bottom >= WINSIZEY) m_isUp = true;
			}
			break;
		case BOSS_MOVE:
			break;
		}
		
		break;
	case M_HIT:
		if (m_StateTime >= m_HitTime)
		{
			m_monsterState = M_MOVE;
			m_alpha = 255;
			m_StateTime = 0.0f;
		}
		else
		{
			m_StateTime += g_ETime;
		}
		break;
	case M_DEAD:
		if (m_alpha - 10 <= 0)
		{

			m_isDead = true;

		}
		break;
	}
}

void monster::attack()
{
}

void monster::bulletMove()
{
}
