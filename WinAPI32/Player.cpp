#include "stdafx.h"
#include "Player.h"


Player::Player()
	: m_time(NULL), m_frameCount(NULL), m_frameX(NULL), m_frameY(NULL), m_alpha(NULL),
	m_life(NULL), m_lifeFrameX(NULL), m_StateTime(NULL)
{
	ZeroMemory(&m_player, sizeof(m_player));
	ZeroMemory(m_bullet, sizeof(m_bullet));
	ZeroMemory(m_lazor, sizeof(m_lazor));
}


Player::~Player()
{
}

HRESULT Player::init()
{
	m_playerState = MOVE;
	m_player.pt = PointMake(100.0f, WINSIZEY / 2.0f);
	//임의로 만든 충돌박스
	m_player.rc = { m_player.pt.x,m_player.pt.y + 20.0f,
					m_player.pt.x + 90.0f, m_player.pt.y + 80.0f };
	m_player.maxHp = 100;
	m_player.hp = m_player.maxHp;
	m_player.damage = 80;
	m_player.moveSpeed = 100.0f;

	for (int i = 0; i < BULLETMAX; i++)
	{
		m_bullet[i].moveSpeed = 300.0f;
		m_bullet[i].radian = 10;
		m_bullet[i].isfire = false;
		//m_bullet[i].isuseble = true;
	}

	for (int i = 0; i < 10; i++)
	{
		m_lazor[i].isfire = false;
		m_lazor[i].lazorTime = 0.0f;
		m_lazor[i].lazorDelay = 3.4f;
	}
	



	m_time = 0.0f;
	m_frameCount = 1.0f / 10;
	m_frameX = 5;
	m_frameY = 0;
	m_alpha = 255;

	m_life = 3;
	m_lifeFrameX = 0;
	m_HitTime = 2.5f;

	m_canAttack = true;
	m_attackTime = 0.0f;
	m_attackDelay = 0.35f;

	m_haveLazor = 3;

	m_OnGame = true;

	return S_OK;
}

void Player::release()
{
}

void Player::update()
{
	frameMove();

	//기본 키움직임
	if (KEYMANAGER->StayKeyDown(VK_LEFT) && m_player.rc.left >= 0 && m_playerState != DEAD)
	{
		m_player.pt.x -= m_player.moveSpeed / 2.0f * g_ETime;
	}
	if (KEYMANAGER->StayKeyDown(VK_RIGHT) && m_player.rc.right <= WINSIZEX && m_playerState != DEAD)
	{
		m_player.pt.x += m_player.moveSpeed * g_ETime;
	}
	if (KEYMANAGER->StayKeyDown(VK_UP) && m_player.rc.top >= 0 && m_playerState != DEAD)
	{
		m_player.pt.y -= m_player.moveSpeed * 2.0f * g_ETime;
	}
	if (KEYMANAGER->StayKeyDown(VK_DOWN) && m_player.rc.bottom <= WINSIZEY && m_playerState != DEAD)
	{
		m_player.pt.y += m_player.moveSpeed * 2.0f * g_ETime;
	}

	if (KEYMANAGER->StayKeyDown(VK_SPACE) && m_playerState != DEAD)
	{
		//cout << "발사함" << endl;
		fire();
	}

	if (KEYMANAGER->isKeyDown('Z') && m_haveLazor > 0)
	{
		fireLazor();
	}

	//공격한뒤 공격딜레이만큼 시간이 지나야 다시 공격가능
	if (!m_canAttack)
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

	if (m_player.hp <= 0)
	{
		m_playerState = DEAD;
	}

	bulletMove();
	lazorDelete();
	SwitchState();


//	if (KEYMANAGER->isKeyDown('Q'))
//	{
//		m_playerState = MOVE;
//	}
//	if (KEYMANAGER->isKeyDown('W'))
//	{
//		m_playerState = HIT;
//	}
	if (KEYMANAGER->isKeyDown('E'))
	{
		//m_playerState = DEAD;
		m_OnGame = false;
	}
//	if (KEYMANAGER->StayKeyDown('R'))
//	{
//		m_player.hp -= 1;
//	}

	m_player.rc = { m_player.pt.x,m_player.pt.y + 20.0f,
				m_player.pt.x + 90.0f, m_player.pt.y + 80.0f };

	if (m_player.hp > m_player.maxHp) m_player.hp = m_player.maxHp;
	if (m_player.hp < 0) m_player.hp = 0;
}

void Player::render()
{
	//충돌박스 렌더
	//DrawfRect(g_MemDC, m_player.rc);
	IMGMANAGER->render("HPBarBottom", g_MemDC, m_player.pt.x, m_player.pt.y - 20.0f, m_player.maxHp, 10);
	IMGMANAGER->render("HPBarTop", g_MemDC, m_player.pt.x, m_player.pt.y - 20.0f, m_player.hp, 10);
	switch (m_playerState)
	{
	case MOVE:
		IMGMANAGER->frameRender("Player", g_MemDC, m_frameX, m_frameY,
			m_player.pt.x, m_player.pt.y, 100, 100);
		break;
	case HIT:
		IMGMANAGER->frameAlphaRender("Player", g_MemDC, m_alpha, m_frameX, m_frameY,
			m_player.pt.x, m_player.pt.y, 100, 100);
		break;
	case DEAD:
		IMGMANAGER->frameAlphaRender("Player", g_MemDC, m_alpha, m_frameX, m_frameY,
			m_player.pt.x, m_player.pt.y, 100, 100);
		break;
	}

	for (int i = 0; i < BULLETMAX; i++)
	{
		if (m_bullet[i].isfire)
		{
			IMGMANAGER->rotateRender("PlayerBullet1", g_MemDC, m_bullet[i].radian, false, 
				1.0f, m_bullet[i].pt.x, m_bullet[i].pt.y);
		}
			
	}

	for (int i = 0; i < 10; i++)
	{
		if (m_lazor[i].isfire)
		{
			IMGMANAGER->render("Lazor", g_MemDC, m_lazor[i].pt.x, m_lazor[i].pt.y);
			for (int j = 0; j < 5; j++)
			{
				IMGMANAGER->frameRender("LazorEffect", g_MemDC, m_lazor[i].frameX, 0,
					m_lazor[i].pt.x + j * 150, m_lazor[i].pt.y, 150, 150);
			}
		}

	}

	for (int i = 0; i < m_life; i++)
	{
		IMGMANAGER->frameRender("PlayerLife", g_MemDC, m_lifeFrameX, 0, 10.0f + i * 40.0f,
			WINSIZEY - 34.0f, 36, 34);
	}
	for (int i = 0; i < m_haveLazor; i++)
	{
		IMGMANAGER->render("Have_Lazor", g_MemDC, 20.0f + i * 35.0f, WINSIZEY - 70.0f, 30, 30);
	}
}

void Player::frameMove()
{

	if (m_time > m_frameCount)
	{
		m_time -= m_frameCount;
		switch (m_playerState)
		{
		case MOVE:
			m_frameY = 0;
			if (m_frameX <= 4)
			{
				m_frameX = 5;
			}
			else
			{
				m_frameX--;
			}
			break;
		case HIT:
			m_frameY = 1;
			m_frameX = 5;

			m_alpha = GetInt(105) + 100;
			
			break;
		case DEAD:
			m_frameY = 2;
			if (m_frameX == 0)
			{
				m_frameX = 0;
			}
			else
			{
				m_frameX--;
			}
			if (m_alpha - 10 > 0)
			{
				m_alpha -= 10;
			}
			break;
		}
		//목숨들 프레임바꿔주기
		m_lifeFrameX++;
		if (m_lifeFrameX >= 7)
		{
			m_lifeFrameX = 0;
		}
		//레이저 프레임 바꿔주기
		for (int i = 0; i < 5; i++)
		{
			if (m_lazor[i].isfire)
			{
				m_lazor[i].frameX++;
				if (m_lazor[i].frameX > 3) m_lazor[i].frameX = 0;
			}
		}
	}
	else
	{
		m_time += g_ETime;
	}


}

void Player::fire()
{
	if (m_canAttack)
	{
		for (int i = 0; i < BULLETMAX; i++)
		{
			if (/*m_bullet[i].isuseble && */!m_bullet[i].isfire)
			{
				m_bullet[i].pt = PointMake(m_player.rc.right,
					m_player.rc.top + (m_player.rc.bottom - m_player.rc.top) / 2.0f);
				//m_bullet[i].isuseble = false;
				m_bullet[i].isfire = true;
				m_canAttack = false;
				SOUNDMANAGER->play("Shoot", 0.3f);

				break;
			}
		}
	}

}

void Player::fireLazor()
{
	for (int i = 0; i < 10; i++)
	{
		if (!m_lazor[i].isfire)
		{
			m_lazor[i].pt = PointMake(m_player.rc.right,
				m_player.rc.top - 50.0f);
			m_lazor[i].rc = RectMake(m_lazor[i].pt.x, m_lazor[i].pt.y, 800, 150);
			m_lazor[i].isfire = true;
			m_haveLazor -= 1;
			SOUNDMANAGER->play("Lazor", 0.8f);

			break;
		}
	}
}

void Player::lazorDelete()
{
	for (int i = 0; i < 10; i++)
	{
		if (m_lazor[i].isfire)
		{
			if (m_lazor[i].lazorTime > m_lazor[i].lazorDelay)
			{
				m_lazor[i].lazorTime = 0.0f;
				m_lazor[i].isfire = false;
				break;
			}
			else
			{
				m_lazor[i].lazorTime += g_ETime;
			}
		}
	}
	
}

void Player::bulletMove()
{
	for (int i = 0; i < BULLETMAX; i++)
	{
		if (/*!m_bullet[i].isuseble &&*/ m_bullet[i].isfire)
		{
			m_bullet[i].pt.x += m_bullet[i].moveSpeed * g_ETime;
			m_bullet[i].cc = CircleMake(m_bullet[i].pt.x, m_bullet[i].pt.y, 15.0f);
			m_bullet[i].radian++;


			if (m_bullet[i].cc.x - m_bullet[i].cc.r > WINSIZEX)
			{
				m_bullet[i].isfire = false;
			}
		}
	}
}

void Player::SwitchState()
{
	switch (m_playerState)
	{
	case MOVE:
		break;
	case HIT:
		if (m_StateTime >= m_HitTime)
		{
			m_playerState = MOVE;
			m_alpha = 255;
			m_StateTime = 0.0f;
		}
		else
		{
			m_StateTime += g_ETime;
		}
		break;
	case DEAD:
		if (m_alpha - 10 <= 0)
		{
			if (m_life >= 1)
			{
				m_life -= 1;
				m_playerState = MOVE;
				m_player.hp = m_player.maxHp;
				m_alpha = 255;
			}
			else
			{
				m_OnGame = false;
			}
		}
		break;
	}
}

void Player::Dammaged(int damage)
{
	if (m_playerState == MOVE)
	{
		m_player.hp -= damage;
		m_playerState = HIT;
	}

}

