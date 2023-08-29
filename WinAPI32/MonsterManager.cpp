#include "stdafx.h"
#include "MonsterManager.h"


MonsterManager::MonsterManager()
{
}


MonsterManager::~MonsterManager()
{
}

HRESULT MonsterManager::init()
{
	m_isBird = false;
	m_isGagail = false;
	m_isSeagull = false;
	m_isStop = false;
	m_isBoss = false;
	return S_OK;
}

void MonsterManager::release()
{
	mvBird.clear();
	mvBird.shrink_to_fit();

	mvGagail.clear();
	mvGagail.shrink_to_fit();

	mvSeagull.clear();
	mvSeagull.shrink_to_fit();

	mvBoss.clear();
	mvBoss.shrink_to_fit();

	mvHeal.clear();
	mvHeal.shrink_to_fit();

	mvLazor.clear();
	mvLazor.shrink_to_fit();

	mvBonusStat.clear();
	mvBonusStat.shrink_to_fit();
}

void MonsterManager::update()
{
	Spawn();
	//if (KEYMANAGER->isKeyDown('Z'))
	//{
	//	//mBird = new bird;
	//	//mBird->init();
	//	//mvBird.emplace_back(*mBird);

	//	mSeagull = new seagull;
	//	mSeagull->init();
	//	mvSeagull.emplace_back(*mSeagull);
	//}

	//if (KEYMANAGER->isKeyDown('X'))
	//{
	//	mGagail = new gagail;
	//	mGagail->init();
	//	mvGagail.emplace_back(*mGagail);
	//}

	//if (KEYMANAGER->isKeyDown('A'))
	//{
	//	mBoss = new boss;
	//	mBoss->init();
	//	mvBoss.emplace_back(*mBoss);
	//}

	//if (KEYMANAGER->isKeyDown('C'))
	//{
	//	mBonusStat = new BonusStat;
	//	mBonusStat->init(PointMake(300, 300), 4);
	//	mvBonusStat.emplace_back(*mBonusStat);
	//}

	//if (KEYMANAGER->isKeyDown('V'))
	//{
	//	mLazor = new Lazor;
	//	mLazor->init();
	//	mvLazor.emplace_back(*mLazor);
	//}

	

	for (mviBird = mvBird.begin(); mviBird != mvBird.end(); mviBird++)
	{
		(*mviBird).update();
	}

	for (mviGagail = mvGagail.begin(); mviGagail != mvGagail.end(); mviGagail++)
	{
		(*mviGagail).update();
	}

	for (mviSeagull = mvSeagull.begin(); mviSeagull != mvSeagull.end(); mviSeagull++)
	{
		(*mviSeagull).update();
		(*mviSeagull).SetPlayerPT(m_player->GetPlayerPT());
	}

	for (mviBoss = mvBoss.begin(); mviBoss != mvBoss.end(); mviBoss++)
	{
		(*mviBoss).update();
		(*mviBoss).SetPlayerPT(m_player->GetPlayerPT());
	}

	for (mviHeal = mvHeal.begin(); mviHeal != mvHeal.end(); mviHeal++)
	{
		(*mviHeal).update();
	}

	for (mviLazor = mvLazor.begin(); mviLazor != mvLazor.end(); mviLazor++)
	{
		(*mviLazor).update();
	}

	for (mviBonusStat = mvBonusStat.begin(); mviBonusStat != mvBonusStat.end(); mviBonusStat++)
	{
		(*mviBonusStat).update();
	}
	//cout << m_player->GetPlayerRect().left << endl;

	CheckInter();
	CheckErase();
}

void MonsterManager::render()
{
	for (mviBird = mvBird.begin(); mviBird != mvBird.end(); mviBird++)
	{
		(*mviBird).render();
	}

	for (mviGagail = mvGagail.begin(); mviGagail != mvGagail.end(); mviGagail++)
	{
		(*mviGagail).render();
	}

	for (mviSeagull = mvSeagull.begin(); mviSeagull != mvSeagull.end(); mviSeagull++)
	{
		(*mviSeagull).render();
	}

	for (mviBoss = mvBoss.begin(); mviBoss != mvBoss.end(); mviBoss++)
	{
		(*mviBoss).render();
	}

	for (mviHeal = mvHeal.begin(); mviHeal != mvHeal.end(); mviHeal++)
	{
		(*mviHeal).render();
	}

	for (mviLazor = mvLazor.begin(); mviLazor != mvLazor.end(); mviLazor++)
	{
		(*mviLazor).render();
	}

	for (mviBonusStat = mvBonusStat.begin(); mviBonusStat != mvBonusStat.end(); mviBonusStat++)
	{
		(*mviBonusStat).render();
	}

}

void MonsterManager::Spawn()
{
	if (!m_isStop)
	{
		m_bossSpawnTime += g_ETime;
	}

	if (m_bossSpawnTime >= 2.0f)
	{
		m_isBird = true;
	}
	if (m_bossSpawnTime >= 12.0f)
	{
		m_isGagail = true;
	}
	if (m_bossSpawnTime >= 22.0f)
	{
		m_isSeagull = true;
	}
	if (m_bossSpawnTime >= 37.0f)
	{
		m_isStop = true;
	}

	if (m_isBird)
	{
		if (m_BirdTime >= 2.2f)
		{
			m_BirdTime = 0.0f;
			mBird = new bird;
			mBird->init();
			mvBird.emplace_back(*mBird);
		}
		else
		{
			m_BirdTime += g_ETime;
		}
	}

	if (m_isGagail)
	{
		if (m_GagailTime >= 3.6f)
		{
			m_GagailTime = 0.0f;
			mGagail = new gagail;
			mGagail->init();
			mvGagail.emplace_back(*mGagail);
		}
		else
		{
			m_GagailTime += g_ETime;
		}
	}

	if (m_isSeagull)
	{
		if (m_SeagullTime >= 4.2f)
		{
			m_SeagullTime = 0.0f;
			mSeagull = new seagull;
			mSeagull->init();
			mvSeagull.emplace_back(*mSeagull);
		}
		else
		{
			m_SeagullTime += g_ETime;
		}
	}

	if (m_isStop && !m_isBoss)
	{
		mBoss = new boss;
		mBoss->init();
		mvBoss.emplace_back(*mBoss);
		m_isBoss = true;
	}
		
		
	if (m_ItemTime >= 10.0f)
	{
		mBonusStat = new BonusStat;
		mBonusStat->init(GetInt(6), 1 + GetInt(4));
		mvBonusStat.emplace_back(*mBonusStat);
		m_ItemTime = 0.0f;
	}
	else
	{
		m_ItemTime += g_ETime;
	}

}

void MonsterManager::CheckInter()
{

	//새와 플레이어와 충돌
	for (mviBird = mvBird.begin(); mviBird != mvBird.end(); mviBird++)
	{
		//새몸통과 플레이어 몸통의 충돌
		if (IntersectRect((*mviBird).GetRect(), m_player->GetPlayerRect()) &&
			(*mviBird).GetMonsterState() != M_DEAD)
		{
			m_player->Dammaged((*mviBird).GetDamage());
			SOUNDMANAGER->play("Bird", 0.3f);
			SOUNDMANAGER->play("Playerhit", 0.4f);
		}


		
		for (int i = 0; i < BULLETMAX; i++)
		{
			//새몸통과 플레이어 총알의 충돌
			if (IntersectRectCircle((*mviBird).GetRect(), m_player->GetBullet(i).cc) && 
				(*mviBird).GetMonsterState() != M_DEAD && m_player->GetBullet(i).isfire)
			{
				//충돌처리될때 발사되어있는 모든 총알이 충돌처리가 없어져서 문제
				(*mviBird).Dammaged(m_player->GetDamage());
				m_player->SetBulletFire(i, false);
				SOUNDMANAGER->play("Bird", 0.3f);
				//cout << "충돌됐다" << endl;
				break;
			}

			for (int j = 0; j < 10; j++)
			{
				//새 몸통과 플레이어 레이저의 충돌
				if (IntersectRect((*mviBird).GetRect(), m_player->GetLazor(j).rc) &&
					m_player->GetLazor(j).isfire)
				{
					if (CheckTime(0.2f))
					{
						//틱당 20정도의 데미지 (공격력 80기준)
						(*mviBird).Dammaged(m_player->GetDamage() / 4);
						SOUNDMANAGER->play("Bird", 0.3f);
					}

				}
			}
		}
		
	}


	//가고일 충돌
	for (mviGagail = mvGagail.begin(); mviGagail != mvGagail.end(); mviGagail++)
	{
		//가고일 몸통과 플레이어 몸통의 충돌
		if (IntersectRect((*mviGagail).GetRect(), m_player->GetPlayerRect()) &&
			(*mviGagail).GetMonsterState() != M_DEAD)
		{
			m_player->Dammaged((*mviGagail).GetDamage());
			SOUNDMANAGER->play("Playerhit", 0.4f);
		}

		


		for (int i = 0; i < BULLETMAX; i++)
		{
			//가고일 총알과 플레이어 몸통의 충돌
			if (IntersectRectCircle(m_player->GetPlayerRect(), (*mviGagail).GetMonsterBullet(i).cc) &&
				(*mviGagail).GetMonsterBullet(i).isfire)
			{
				m_player->Dammaged((*mviGagail).GetDamage());
				(*mviGagail).SetMonsterBulletFire(i, false);
				SOUNDMANAGER->play("Playerhit", 0.4f);
			}

			//가고일 몸통과 플레이어 총알의 충돌
			if (IntersectRectCircle((*mviGagail).GetRect(), m_player->GetBullet(i).cc) &&
				(*mviGagail).GetMonsterState() != M_DEAD && m_player->GetBullet(i).isfire)
			{
				//충돌처리될때 발사되어있는 모든 총알이 충돌처리가 없어져서 문제
				(*mviGagail).Dammaged(m_player->GetDamage());
				m_player->SetBulletFire(i, false);
			}

			for (int j = 0; j < 10; j++)
			{
				//가고일 몸통과 플레이어 레이저의 충돌
				if (IntersectRect((*mviGagail).GetRect(), m_player->GetLazor(j).rc) &&
					(*mviGagail).GetMonsterState() != M_DEAD && m_player->GetLazor(j).isfire)
				{
					if (CheckTime(0.2f))
					{
						//틱당 20정도의 데미지 (공격력 80기준)
						(*mviGagail).Dammaged(m_player->GetDamage() / 4);
					}
				}
			}
			
		}
	}

	//갈매기 충돌
	for (mviSeagull = mvSeagull.begin(); mviSeagull != mvSeagull.end(); mviSeagull++)
	{
		//갈매기 몸통과 플레이어 몸통의 충돌
		if (IntersectRect((*mviSeagull).GetRect(), m_player->GetPlayerRect()) &&
			(*mviSeagull).GetMonsterState() != M_DEAD)
		{
			m_player->Dammaged((*mviSeagull).GetDamage());
			SOUNDMANAGER->play("Seagull", 0.3f);
			SOUNDMANAGER->play("Playerhit", 0.4f);
		}




		for (int i = 0; i < BULLETMAX; i++)
		{
			//갈매기 총알과 플레이어 몸통의 충돌
			if (IntersectRectCircle(m_player->GetPlayerRect(), (*mviSeagull).GetMonsterBullet(i).cc) &&
				(*mviSeagull).GetMonsterBullet(i).isfire)
			{
				m_player->Dammaged((*mviSeagull).GetDamage());
				(*mviSeagull).SetMonsterBulletFire(i, false);
				SOUNDMANAGER->play("Playerhit", 0.4f);
			}

			//갈매기 몸통과 플레이어 총알의 충돌
			if (IntersectRectCircle((*mviSeagull).GetRect(), m_player->GetBullet(i).cc) &&
				(*mviSeagull).GetMonsterState() != M_DEAD && m_player->GetBullet(i).isfire)
			{
				//충돌처리될때 발사되어있는 모든 총알이 충돌처리가 없어져서 문제
				(*mviSeagull).Dammaged(m_player->GetDamage());
				m_player->SetBulletFire(i, false);
				SOUNDMANAGER->play("Seagull", 0.3f);
			}

			for (int j = 0; j < 10; j++)
			{
				//갈매기 몸통과 플레이어 레이저의 충돌
				if (IntersectRect((*mviSeagull).GetRect(), m_player->GetLazor(j).rc) &&
					(*mviSeagull).GetMonsterState() != M_DEAD && m_player->GetLazor(j).isfire)
				{
					if (CheckTime(0.2f))
					{
						//틱당 80정도의 데미지 (공격력 80기준)
						(*mviSeagull).Dammaged(m_player->GetDamage());
						SOUNDMANAGER->play("Seagull", 0.3f);
					}
				}
			}
		}
	}

	//보스 충돌
	for (mviBoss = mvBoss.begin(); mviBoss != mvBoss.end(); mviBoss++)
	{
		//보스 몸통과 플레이어 몸통의 충돌
		if (IntersectRect((*mviBoss).GetRect(), m_player->GetPlayerRect()) &&
			(*mviBoss).GetMonsterState() != B_DEAD)
		{
			m_player->Dammaged((*mviBoss).GetDamage());
			SOUNDMANAGER->play("Playerhit", 0.4f);
		}

		//보스 뿔과 플레이어 몸통의 충돌
		if (IntersectRect((*mviBoss).GetHornRect(), m_player->GetPlayerRect()) &&
			(*mviBoss).GetMonsterState() != B_DEAD)
		{
			m_player->Dammaged((*mviBoss).GetDamage());
			SOUNDMANAGER->play("Playerhit", 0.4f);
		}


		for (int i = 0; i < BULLETMAX; i++)
		{
			for (int j = 0; j < BOSSBULLETMAX; j++)
			{
				//보스 총알과 플레이어 몸통의 충돌
				if (IntersectRectCircle(m_player->GetPlayerRect(), (*mviBoss).GetMonsterBullet(j).cc) &&
					(*mviBoss).GetMonsterBullet(j).isfire)
				{
					m_player->Dammaged((*mviBoss).GetDamage());
					(*mviBoss).SetMonsterBulletFire(j, false);
					SOUNDMANAGER->play("Playerhit", 0.4f);
				}

				//보스 총알과 플레이어 총알의 충돌
				//플레이어꺼는 사라지고 보스꺼는 각도가 바뀜 지렁이 마냥
			}

			//보스 몸통과 플레이어 총알의 충돌
			if (IntersectRectCircle((*mviBoss).GetRect(), m_player->GetBullet(i).cc) &&
				(*mviBoss).GetMonsterState() != B_DEAD && m_player->GetBullet(i).isfire)
			{
				//충돌처리될때 발사되어있는 모든 총알이 충돌처리가 없어져서 문제
				(*mviBoss).Dammaged(m_player->GetDamage());
				m_player->SetBulletFire(i, false);
			}

			//보스 머리와 플레이어 총알의 충돌
			if (IntersectRectCircle((*mviBoss).GetHornRect(), m_player->GetBullet(i).cc) &&
				(*mviBoss).GetMonsterState() != B_DEAD && m_player->GetBullet(i).isfire)
			{
				//충돌처리될때 발사되어있는 모든 총알이 충돌처리가 없어져서 문제
				(*mviBoss).Dammaged(m_player->GetDamage() * 2);
				m_player->SetBulletFire(i, false);
			}


			for (int j = 0; j < 10; j++)
			{
				//보스 몸통과 플레이어 레이저의 충돌
				if (IntersectRect((*mviBoss).GetRect(), m_player->GetLazor(j).rc) &&
					(*mviBoss).GetMonsterState() != B_DEAD && m_player->GetLazor(j).isfire)
				{
					if (CheckTime(1.0f))
					{
						//틱당 20정도의 데미지 (공격력 80기준)
						(*mviBoss).Dammaged(m_player->GetDamage() / 10);
					}
				}
			}

		}
	}


	//힐 아이템과 플레이어 충돌
	for (mviHeal = mvHeal.begin(); mviHeal != mvHeal.end();)
	{
		//플레이어랑 충돌하면 바로 아이템 삭제랑 효과발동해준다.
		if (IntersectRect(m_player->GetPlayerRect(), (*mviHeal).GetRect()))
		{
			m_player->HealPlayer((*mviHeal).GetDamage());
			(*mviHeal).release();
			mviHeal = mvHeal.erase(mviHeal);
			SOUNDMANAGER->play("Item", 0.5f);
		}
		else
		{
			mviHeal++;
		}
	}

	//레이저 아이템과 플레이어 충돌
	for (mviLazor = mvLazor.begin(); mviLazor != mvLazor.end();)
	{
		//플레이어랑 충돌하면 바로 아이템 삭제랑 효과발동해준다.
		if (IntersectRect(m_player->GetPlayerRect(), (*mviLazor).GetRect()))
		{
			m_player->PlusLazor(1);
			(*mviLazor).release();
			mviLazor = mvLazor.erase(mviLazor);
			SOUNDMANAGER->play("Item", 0.5f);
		}
		else
		{
			mviLazor++;
		}
	}

	//보너스 스텟 아이템과 플레이어 충돌
	for (mviBonusStat = mvBonusStat.begin(); mviBonusStat != mvBonusStat.end();)
	{
		//플레이어랑 충돌하면 바로 아이템 삭제랑 효과발동해준다.
		if (IntersectRect(m_player->GetPlayerRect(), (*mviBonusStat).GetRect()))
		{
			switch ((*mviBonusStat).GetItemType())
			{
			case ATTSPD:
				m_player->PlusAttackSpeed((*mviBonusStat).GetFloatNum());
				break;
			case DMG:
				m_player->PlusDamage((*mviBonusStat).GetIntNum());
				break;
			case MHP:
				m_player->PlusMaxHp((*mviBonusStat).GetIntNum());
				break;
			case MVSPD:
				m_player->PlusMovementSpeed((*mviBonusStat).GetFloatNum());
				break;
			}
			(*mviBonusStat).release();
			mviBonusStat = mvBonusStat.erase(mviBonusStat);
			SOUNDMANAGER->play("Item", 0.5f);
		}
		else
		{
			mviBonusStat++;
		}
	}

}

void MonsterManager::CheckErase()
{

	//죽은 새는 좋은새니까 지워준다.
	for (mviBird = mvBird.begin(); mviBird != mvBird.end();)
	{
		if ((*mviBird).GetIsDead())
		{
			//새가 죽을떄 50% 확률로 회복아이템떨굼
			if (GetInt(2) == 1)
			{
				mHeal = new Heal;
				mHeal->init((*mviBird).GetPoint(),1);
				mvHeal.emplace_back(*mHeal);
			}
			
			(*mviBird).release();
			mviBird = mvBird.erase(mviBird);
		}
		else
		{
			mviBird++;
		}
	}

	//죽은 가고일은 좋은가고일이니까 지워준다.
	for (mviGagail = mvGagail.begin(); mviGagail != mvGagail.end();)
	{
		if ((*mviGagail).GetIsDead())
		{
			//가고일이 죽을떄 50% 확률로 회복아이템떨굼
			if (GetInt(51) < 25)
			{
				mHeal = new Heal;
				mHeal->init((*mviGagail).GetPoint(),1);
				mvHeal.emplace_back(*mHeal);
			}
			//25% 확률로 레이저 아이템 떨굼
			if (GetInt(101) < 25)
			{
				mLazor = new Lazor;
				mLazor->init((*mviGagail).GetPoint());
				mvLazor.emplace_back(*mLazor);
			}

			(*mviGagail).release();
			mviGagail = mvGagail.erase(mviGagail);
		}
		else
		{
			mviGagail++;
		}
	}

	//갈매기는 새우깡도둑이니까 지워준다.
	for (mviSeagull = mvSeagull.begin(); mviSeagull != mvSeagull.end();)
	{
		if ((*mviSeagull).GetIsDead())
		{
			//가고일이 죽을떄 50% 확률로 회복아이템떨굼
			if (GetInt(51) < 25)
			{
				mHeal = new Heal;
				mHeal->init((*mviSeagull).GetPoint(),2);
				mvHeal.emplace_back(*mHeal);
			}
			//40% 확률로 레이저 아이템 떨굼
			if (GetInt(101) < 25)
			{
				mLazor = new Lazor;
				mLazor->init((*mviSeagull).GetPoint());
				mvLazor.emplace_back(*mLazor);
			}

			(*mviSeagull).release();
			mviSeagull = mvSeagull.erase(mviSeagull);
		}
		else
		{
			mviSeagull++;
		}
	}

	//당신은 신이야!
	//보스를 지워버려!
	for (mviBoss = mvBoss.begin(); mviBoss != mvBoss.end();)
	{
		if ((*mviBoss).GetIsDead())
		{
			for (int i = 0; i < 100; i++)
			{
				mHeal = new Heal;
				mHeal->init((*mviBoss).GetPoint(), 2);
				mvHeal.emplace_back(*mHeal);

				mLazor = new Lazor;
				mLazor->init((*mviBoss).GetPoint());
				mvLazor.emplace_back(*mLazor);
			}
			
			

			(*mviBoss).release();
			mviBoss = mvBoss.erase(mviBoss);
			m_OnGame = false;
		}
		else
		{
			mviBoss++;
		}
	}

	if(KEYMANAGER->isKeyDown('7')) m_OnGame = false;

	//플레이어랑 충돌안하고 끝까지 가버린 아이템
	//그런 아이템에겐 죽음뿐
	for (mviHeal = mvHeal.begin(); mviHeal != mvHeal.end();)
	{
		if ((*mviHeal).GetMonsterState() == M_DEAD)
		{
			(*mviHeal).release();
			mviHeal = mvHeal.erase(mviHeal);
			//cout << "놓친 힐 삭제" << endl;
		}
		else
		{
			mviHeal++;
		}
	}

	for (mviLazor = mvLazor.begin(); mviLazor != mvLazor.end();)
	{
		if ((*mviLazor).GetMonsterState() == M_DEAD)
		{
			(*mviLazor).release();
			mviLazor = mvLazor.erase(mviLazor);
		}
		else
		{
			mviLazor++;
		}
	}

	for (mviBonusStat = mvBonusStat.begin(); mviBonusStat != mvBonusStat.end();)
	{
		if ((*mviBonusStat).GetMonsterState() == M_DEAD)
		{
			(*mviBonusStat).release();
			mviBonusStat = mvBonusStat.erase(mviBonusStat);
		}
		else
		{
			mviBonusStat++;
		}
	}


}

bool MonsterManager::CheckTime(float delay)
{
	if (m_lazorCheckTime >= delay)
	{
		m_lazorCheckTime = 0.0f;
		return true;
	}
	else
	{
		m_lazorCheckTime += g_ETime;
		return false;
	}
}
