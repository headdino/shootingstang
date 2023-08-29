#include "stdafx.h"
#include "boss.h"

boss::boss()
{
	ZeroMemory(&m_monster, sizeof(m_monster));
	ZeroMemory(&m_Bbullet, sizeof(m_Bbullet));
}


boss::~boss()
{
}

HRESULT boss::init()
{
	m_attackType = BOSS_ATTACK;
	m_moveType = BOSS_MOVE;
	m_monsterState = B_MOVE;

	m_monster.pt = PointMake(WINSIZEX + 100.0f, WINSIZEY / 2.0f);
	m_monster.rc = { m_monster.pt.x,m_monster.pt.y + 20.0f,
					m_monster.pt.x + 90.0f, m_monster.pt.y + 90.0f };
	m_monster.damage = 40;
	m_monster.hp = 6000;
	m_monster.moveSpeed = 140.0f;

	for (int i = 0; i < BOSSBULLETMAX; i++)
	{
		m_Bbullet[i].moveSpeed = 200.0f;
		m_Bbullet[i].isfire = false;
	}

	m_time = 0.0f;
	m_frameCount = 1.0f / 3;
	m_frameX = 0;
	m_frameY = 0;
	m_alpha = 255;

	m_StateTime = 0.0f;
	m_HitTime = 1.8f;
	m_isDead = false;

	m_canAttack = false;
	m_attackTime = 0.0f;
	m_attackDelay = 1.2f;

	m_bossPattan = FIRST;
	m_isHalfHp = false;
	m_bossAttackTimer = 0.0f;
	m_isCharge = false;

	m_beforeCharge = PointMake(WINSIZEX, WINSIZEY);

	m_bossMovePoint[0] = PointMake(500.0f, 300.0f);
	m_bossMovePoint[1] = PointMake(600.0f, -10.0f);
	m_bossMovePoint[2] = PointMake(350.0f, 100.0f);
	m_bossMovePoint[3] = PointMake(850.0f, 100.0f);

	return S_OK;
}

void boss::release()
{
}

void boss::update()
{
	SwitchState();
	frameMove();
	bulletMove();

	//if (KEYMANAGER->StayKeyDown('Q'))
	//{
	//	m_monster.pt.x -= m_monster.moveSpeed * g_ETime;
	//}
	//if (KEYMANAGER->StayKeyDown('W'))
	//{
	//	m_monster.pt.x += m_monster.moveSpeed * g_ETime;
	//}
	//if (KEYMANAGER->StayKeyDown('E'))
	//{
	//	m_monster.pt.y -= m_monster.moveSpeed * g_ETime;
	//}
	//if (KEYMANAGER->StayKeyDown('R'))
	//{
	//	m_monster.pt.y += m_monster.moveSpeed * g_ETime;
	//}

	/*cout << "보스 x : " << m_monster.pt.x << "보스 y : " << m_monster.pt.y << endl;

	if (KEYMANAGER->isKeyDown('J'))
	{
		m_monsterState = B_MOVE;
	}
	if (KEYMANAGER->isKeyDown('K'))
	{
		m_monsterState = B_ATTACK;
	}
	if (KEYMANAGER->isKeyDown('L'))
	{
		m_monsterState = B_DEAD;
	}*/

	if (m_monster.hp <= 0) m_monsterState = B_DEAD;// cout << m_monster.hp << endl;
	if (m_monster.rc.right < -100) m_monsterState = B_DEAD;

	if (m_canAttack && m_monsterState != B_DEAD && m_bossPattan == SHOOT_PATTAN) attack();
	else
	{
		if (m_attackTime > m_attackDelay)
		{
			m_attackTime = 0.0f;
			m_canAttack = true;
		}
		else
		{
			m_attackTime += g_ETime;
		}
	}

	m_monster.rc = { m_monster.pt.x + 30.0f,m_monster.pt.y + 120.0f,
					m_monster.pt.x + 300.0f, m_monster.pt.y + 270.0f };
	m_hornRc = { m_monster.pt.x + 120.0f, m_monster.pt.y + 30.0f,
					m_monster.pt.x + 200.0f, m_monster.pt.y + 150.0f };

	if (m_monster.hp < 3000) m_isHalfHp = true;
	if (m_monster.hp < 0) m_monster.hp = 0;
}

void boss::render()
{
	//보스 체력바 렌더
	IMGMANAGER->render("HPBarBottom", g_MemDC, 300.0f,30.0f, 600, 50);
	IMGMANAGER->render("HPBarTop", g_MemDC, 300.0f,30.0f, m_monster.hp / 10, 50);
	IMGMANAGER->render("Boss_head", g_MemDC, 250.0f, 30.0f, 50, 50);

	//충돌박스 렌더
	//DrawfRect(g_MemDC, m_monster.rc);
	//DrawfRect(g_MemDC, m_hornRc);
	switch (m_monsterState)
	{
	case B_MOVE:
		IMGMANAGER->frameRender("Boss_move", g_MemDC, m_frameX, m_frameY,
			m_monster.pt.x, m_monster.pt.y, 300, 300);
		break;
	case B_ATTACK:
		IMGMANAGER->frameAlphaRender("Boss_attack", g_MemDC, m_alpha,m_frameX, m_frameY,
			m_monster.pt.x, m_monster.pt.y, 300, 300);
		break;
	case B_DEAD:
		IMGMANAGER->frameAlphaRender("Boss_dead", g_MemDC, m_alpha, m_frameX, m_frameY,
			m_monster.pt.x, m_monster.pt.y, 300, 300);
		break;
	}

	for (int i = 0; i < BOSSBULLETMAX; i++)
	{
		if (m_Bbullet[i].isfire)
		{
			//DrawfCircle(g_MemDC, m_Bbullet[i].cc);
			//IMGMANAGER->rotateRender("Boss_bullet", g_MemDC, m_Bbullet[i].imageRotateRadian, false,
			//	1.0f, m_Bbullet[i].pt.x - m_Bbullet[i].cc.r, m_Bbullet[i].pt.y - m_Bbullet[i].cc.r);
			IMGMANAGER->render("Boss_bullet", g_MemDC, m_Bbullet[i].pt.x - m_Bbullet[i].cc.r
				, m_Bbullet[i].pt.y - m_Bbullet[i].cc.r);
		}

	}
}

void boss::frameMove()
{
	if (m_time > m_frameCount)
	{
		m_time -= m_frameCount;
		switch (m_monsterState)
		{
		case B_MOVE:
			m_frameY = 0;
			if (m_frameX >= 5)
			{
				m_frameX = 0;
			}
			else
			{
				m_frameX++;
			}
			break;
		case B_ATTACK:
			m_frameY = 0;
			if (m_frameX >= 5) m_frameX = 0;
			else m_frameX++;

			break;
		case B_DEAD:
			m_frameY = 0;
			if (m_frameX >= 2)
			{
				m_frameX = 0;
			}
			else
			{
				m_frameX++;
			}
			if (m_alpha - 10 > 0)
			{
				m_alpha -= 10;
			}
			break;
		}

	}
	else
	{
		m_time += g_ETime;
	}
}

void boss::SwitchState()
{
	//움직이는 타입에 따라서
	if (m_monsterState != B_DEAD)
	{
		switch (m_bossPattan)
		{
		case FIRST:
			if (m_monster.pt.x > WINSIZEX / 2)
			{
				m_monster.pt.x -= m_monster.moveSpeed * g_ETime;
			}
			else
			{
				m_bossPattan = MENU_PATTAN;
			}
			break;
		case MENU_PATTAN:
			switch (GetInt(3))
			{
			case 0: m_bossPattan = SHOOT_PATTAN;
				break;
			case 1: m_bossPattan = MOVE_MENU_PATTAN;
				break;
			case 2:
				if (m_isHalfHp)
				{
					m_bossPattan = CHARGE_PATTAN;
					m_beforeCharge.x = m_monster.pt.x;
					m_beforeCharge.y = m_monster.pt.y;
					m_isCharge = true;
				}
				else
				{
					m_bossPattan = MOVE_MENU_PATTAN;
				}
				break;
			}
			break;
		case CHARGE_PATTAN:
			if (GetDistance(m_monster.pt.x, m_monster.pt.y, m_beforeCharge.x - 250.0f, m_beforeCharge.y) > 10 &&
				m_isCharge)
			{
				m_monster.pt.x -= m_monster.moveSpeed * 4.0f  * g_ETime;
			}
			if (GetDistance(m_monster.pt.x, m_monster.pt.y, m_beforeCharge.x - 250.0f, m_beforeCharge.y) <= 10
				|| m_monster.pt.x < 0)
			{
				m_isCharge = false;
			}

			if (!m_isCharge)
			{
				m_monster.pt.x += m_monster.moveSpeed / 2.0f * g_ETime;
				if (GetDistance(m_monster.pt.x, m_monster.pt.y, m_beforeCharge.x, m_beforeCharge.y) <= 50
					|| m_monster.pt.x > WINSIZEX)
				{
					m_bossPattan = MENU_PATTAN;
				}
			}
			break;
		case SHOOT_PATTAN:
			m_monsterState = B_ATTACK;
			if (m_bossAttackTimer >= m_bossAttackTime)
			{
				m_bossAttackTimer = 0.0f;
				m_bossPattan = MENU_PATTAN;
				m_monsterState = B_MOVE;
			}
			else
			{
				m_bossAttackTimer += g_ETime;
			}

			break;
		case MOVE_MENU_PATTAN:
			m_bossMovePattan = GetInt(4);
			m_bossAttackTime = 1.4f + GetFloat(2.4f);
			switch (m_bossMovePattan)
			{
			case 0: m_bossPattan = MOVE_TO_0;
				break;
			case 1: m_bossPattan = MOVE_TO_1;
				break;
			case 2: m_bossPattan = MOVE_TO_2;
				break;
			case 3: m_bossPattan = MOVE_TO_3;
				break;
			}
			break;
		case MOVE_TO_0:
			if (GetDistance(m_monster.pt.x, m_monster.pt.y, m_bossMovePoint[0].x, m_bossMovePoint[0].y) > 10)
			{
				m_monster.pt.x += cosf(GetRadian(m_monster.pt.x, m_monster.pt.y,
					m_bossMovePoint[0].x, m_bossMovePoint[0].y)) * m_monster.moveSpeed  * g_ETime;
				m_monster.pt.y -= sinf(GetRadian(m_monster.pt.x, m_monster.pt.y,
					m_bossMovePoint[0].x, m_bossMovePoint[0].y)) * m_monster.moveSpeed  * g_ETime;
			}
			if (GetDistance(m_monster.pt.x, m_monster.pt.y, m_bossMovePoint[0].x, m_bossMovePoint[0].y) <= 10)
			{
				m_bossPattan = MENU_PATTAN;
			}

			break;
		case MOVE_TO_1:
			if (GetDistance(m_monster.pt.x, m_monster.pt.y, m_bossMovePoint[1].x, m_bossMovePoint[1].y) > 10)
			{
				m_monster.pt.x += cosf(GetRadian(m_monster.pt.x, m_monster.pt.y,
					m_bossMovePoint[1].x, m_bossMovePoint[1].y)) * m_monster.moveSpeed  * g_ETime;
				m_monster.pt.y -= sinf(GetRadian(m_monster.pt.x, m_monster.pt.y,
					m_bossMovePoint[1].x, m_bossMovePoint[1].y)) * m_monster.moveSpeed  * g_ETime;
			}
			if (GetDistance(m_monster.pt.x, m_monster.pt.y, m_bossMovePoint[1].x, m_bossMovePoint[1].y) <= 10)
			{
				m_bossPattan = MENU_PATTAN;
			}

			break;
		case MOVE_TO_2:
			if (GetDistance(m_monster.pt.x, m_monster.pt.y, m_bossMovePoint[2].x, m_bossMovePoint[2].y) > 10)
			{
				m_monster.pt.x += cosf(GetRadian(m_monster.pt.x, m_monster.pt.y,
					m_bossMovePoint[2].x, m_bossMovePoint[2].y)) * m_monster.moveSpeed  * g_ETime;
				m_monster.pt.y -= sinf(GetRadian(m_monster.pt.x, m_monster.pt.y,
					m_bossMovePoint[2].x, m_bossMovePoint[2].y)) * m_monster.moveSpeed  * g_ETime;
			}
			if (GetDistance(m_monster.pt.x, m_monster.pt.y, m_bossMovePoint[2].x, m_bossMovePoint[2].y) <= 10)
			{
				m_bossPattan = MENU_PATTAN;
			}

			break;
		case MOVE_TO_3:
			if (GetDistance(m_monster.pt.x, m_monster.pt.y, m_bossMovePoint[3].x, m_bossMovePoint[3].y) > 10)
			{
				m_monster.pt.x += cosf(GetRadian(m_monster.pt.x, m_monster.pt.y,
					m_bossMovePoint[3].x, m_bossMovePoint[3].y)) * m_monster.moveSpeed  * g_ETime;
				m_monster.pt.y -= sinf(GetRadian(m_monster.pt.x, m_monster.pt.y,
					m_bossMovePoint[3].x, m_bossMovePoint[3].y)) * m_monster.moveSpeed  * g_ETime;
			}
			if (GetDistance(m_monster.pt.x, m_monster.pt.y, m_bossMovePoint[3].x, m_bossMovePoint[3].y) <= 10)
			{
				m_bossPattan = MENU_PATTAN;
			}

			break;
		}
	}
	


	switch (m_monsterState)
	{
		//움직이는 상태일때
	case B_MOVE:
		

		break;
	case B_ATTACK:
		/*if (m_StateTime >= m_HitTime)
		{
			m_monsterState = M_MOVE;
			m_alpha = 255;
			m_StateTime = 0.0f;
		}
		else
		{
			m_StateTime += g_ETime;
		}*/
		break;
	case B_DEAD:
		if (m_alpha - 10 <= 0)
		{

			m_isDead = true;

		}
		break;
	}
	
}

void boss::attack()
{
	m_canAttack = false;
	for (int i = 0; i < BOSSBULLETMAX; i++)
	{
		if (!m_Bbullet[i].isfire)
		{
			m_Bbullet[i].pt = PointMake(m_monster.rc.right,
				m_monster.rc.top + (m_monster.rc.bottom - m_monster.rc.top) / 2.0f);
			m_Bbullet[i].isfire = true;
			m_Bbullet[i].degree = 90.0f;
			m_canAttack = false;

			break;
		}
	}
}

void boss::bulletMove()
{
	for (int i = 0; i < BOSSBULLETMAX; i++)
	{

		if (m_Bbullet[i].isfire)
		{
			m_Bbullet[i].pt.x -= m_Bbullet[i].moveSpeed * g_ETime;
			m_Bbullet[i].pt.y -= sinf(GetRadian(m_Bbullet[i].pt.x, m_Bbullet[i].pt.y, m_playerPT.x, m_playerPT.y)) * m_Bbullet[i].moveSpeed / 4.0f * g_ETime;
			m_Bbullet[i].cc = CircleMake(m_Bbullet[i].pt.x, m_Bbullet[i].pt.y, 15.0f);
			m_Bbullet[i].imageRotateRadian = GetDegree(m_playerPT.x, m_playerPT.y, m_Bbullet[i].pt.x, m_Bbullet[i].pt.y);

			if (m_Bbullet[i].cc.x < 0)
			{
				m_Bbullet[i].isfire = false;
			}
		}
	}
}


void boss::Dammaged(int damage)
{
	m_monster.hp -= damage;
}

