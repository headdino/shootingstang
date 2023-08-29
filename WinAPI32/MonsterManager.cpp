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

	//���� �÷��̾�� �浹
	for (mviBird = mvBird.begin(); mviBird != mvBird.end(); mviBird++)
	{
		//������� �÷��̾� ������ �浹
		if (IntersectRect((*mviBird).GetRect(), m_player->GetPlayerRect()) &&
			(*mviBird).GetMonsterState() != M_DEAD)
		{
			m_player->Dammaged((*mviBird).GetDamage());
			SOUNDMANAGER->play("Bird", 0.3f);
			SOUNDMANAGER->play("Playerhit", 0.4f);
		}


		
		for (int i = 0; i < BULLETMAX; i++)
		{
			//������� �÷��̾� �Ѿ��� �浹
			if (IntersectRectCircle((*mviBird).GetRect(), m_player->GetBullet(i).cc) && 
				(*mviBird).GetMonsterState() != M_DEAD && m_player->GetBullet(i).isfire)
			{
				//�浹ó���ɶ� �߻�Ǿ��ִ� ��� �Ѿ��� �浹ó���� �������� ����
				(*mviBird).Dammaged(m_player->GetDamage());
				m_player->SetBulletFire(i, false);
				SOUNDMANAGER->play("Bird", 0.3f);
				//cout << "�浹�ƴ�" << endl;
				break;
			}

			for (int j = 0; j < 10; j++)
			{
				//�� ����� �÷��̾� �������� �浹
				if (IntersectRect((*mviBird).GetRect(), m_player->GetLazor(j).rc) &&
					m_player->GetLazor(j).isfire)
				{
					if (CheckTime(0.2f))
					{
						//ƽ�� 20������ ������ (���ݷ� 80����)
						(*mviBird).Dammaged(m_player->GetDamage() / 4);
						SOUNDMANAGER->play("Bird", 0.3f);
					}

				}
			}
		}
		
	}


	//������ �浹
	for (mviGagail = mvGagail.begin(); mviGagail != mvGagail.end(); mviGagail++)
	{
		//������ ����� �÷��̾� ������ �浹
		if (IntersectRect((*mviGagail).GetRect(), m_player->GetPlayerRect()) &&
			(*mviGagail).GetMonsterState() != M_DEAD)
		{
			m_player->Dammaged((*mviGagail).GetDamage());
			SOUNDMANAGER->play("Playerhit", 0.4f);
		}

		


		for (int i = 0; i < BULLETMAX; i++)
		{
			//������ �Ѿ˰� �÷��̾� ������ �浹
			if (IntersectRectCircle(m_player->GetPlayerRect(), (*mviGagail).GetMonsterBullet(i).cc) &&
				(*mviGagail).GetMonsterBullet(i).isfire)
			{
				m_player->Dammaged((*mviGagail).GetDamage());
				(*mviGagail).SetMonsterBulletFire(i, false);
				SOUNDMANAGER->play("Playerhit", 0.4f);
			}

			//������ ����� �÷��̾� �Ѿ��� �浹
			if (IntersectRectCircle((*mviGagail).GetRect(), m_player->GetBullet(i).cc) &&
				(*mviGagail).GetMonsterState() != M_DEAD && m_player->GetBullet(i).isfire)
			{
				//�浹ó���ɶ� �߻�Ǿ��ִ� ��� �Ѿ��� �浹ó���� �������� ����
				(*mviGagail).Dammaged(m_player->GetDamage());
				m_player->SetBulletFire(i, false);
			}

			for (int j = 0; j < 10; j++)
			{
				//������ ����� �÷��̾� �������� �浹
				if (IntersectRect((*mviGagail).GetRect(), m_player->GetLazor(j).rc) &&
					(*mviGagail).GetMonsterState() != M_DEAD && m_player->GetLazor(j).isfire)
				{
					if (CheckTime(0.2f))
					{
						//ƽ�� 20������ ������ (���ݷ� 80����)
						(*mviGagail).Dammaged(m_player->GetDamage() / 4);
					}
				}
			}
			
		}
	}

	//���ű� �浹
	for (mviSeagull = mvSeagull.begin(); mviSeagull != mvSeagull.end(); mviSeagull++)
	{
		//���ű� ����� �÷��̾� ������ �浹
		if (IntersectRect((*mviSeagull).GetRect(), m_player->GetPlayerRect()) &&
			(*mviSeagull).GetMonsterState() != M_DEAD)
		{
			m_player->Dammaged((*mviSeagull).GetDamage());
			SOUNDMANAGER->play("Seagull", 0.3f);
			SOUNDMANAGER->play("Playerhit", 0.4f);
		}




		for (int i = 0; i < BULLETMAX; i++)
		{
			//���ű� �Ѿ˰� �÷��̾� ������ �浹
			if (IntersectRectCircle(m_player->GetPlayerRect(), (*mviSeagull).GetMonsterBullet(i).cc) &&
				(*mviSeagull).GetMonsterBullet(i).isfire)
			{
				m_player->Dammaged((*mviSeagull).GetDamage());
				(*mviSeagull).SetMonsterBulletFire(i, false);
				SOUNDMANAGER->play("Playerhit", 0.4f);
			}

			//���ű� ����� �÷��̾� �Ѿ��� �浹
			if (IntersectRectCircle((*mviSeagull).GetRect(), m_player->GetBullet(i).cc) &&
				(*mviSeagull).GetMonsterState() != M_DEAD && m_player->GetBullet(i).isfire)
			{
				//�浹ó���ɶ� �߻�Ǿ��ִ� ��� �Ѿ��� �浹ó���� �������� ����
				(*mviSeagull).Dammaged(m_player->GetDamage());
				m_player->SetBulletFire(i, false);
				SOUNDMANAGER->play("Seagull", 0.3f);
			}

			for (int j = 0; j < 10; j++)
			{
				//���ű� ����� �÷��̾� �������� �浹
				if (IntersectRect((*mviSeagull).GetRect(), m_player->GetLazor(j).rc) &&
					(*mviSeagull).GetMonsterState() != M_DEAD && m_player->GetLazor(j).isfire)
				{
					if (CheckTime(0.2f))
					{
						//ƽ�� 80������ ������ (���ݷ� 80����)
						(*mviSeagull).Dammaged(m_player->GetDamage());
						SOUNDMANAGER->play("Seagull", 0.3f);
					}
				}
			}
		}
	}

	//���� �浹
	for (mviBoss = mvBoss.begin(); mviBoss != mvBoss.end(); mviBoss++)
	{
		//���� ����� �÷��̾� ������ �浹
		if (IntersectRect((*mviBoss).GetRect(), m_player->GetPlayerRect()) &&
			(*mviBoss).GetMonsterState() != B_DEAD)
		{
			m_player->Dammaged((*mviBoss).GetDamage());
			SOUNDMANAGER->play("Playerhit", 0.4f);
		}

		//���� �԰� �÷��̾� ������ �浹
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
				//���� �Ѿ˰� �÷��̾� ������ �浹
				if (IntersectRectCircle(m_player->GetPlayerRect(), (*mviBoss).GetMonsterBullet(j).cc) &&
					(*mviBoss).GetMonsterBullet(j).isfire)
				{
					m_player->Dammaged((*mviBoss).GetDamage());
					(*mviBoss).SetMonsterBulletFire(j, false);
					SOUNDMANAGER->play("Playerhit", 0.4f);
				}

				//���� �Ѿ˰� �÷��̾� �Ѿ��� �浹
				//�÷��̾�� ������� �������� ������ �ٲ� ������ ����
			}

			//���� ����� �÷��̾� �Ѿ��� �浹
			if (IntersectRectCircle((*mviBoss).GetRect(), m_player->GetBullet(i).cc) &&
				(*mviBoss).GetMonsterState() != B_DEAD && m_player->GetBullet(i).isfire)
			{
				//�浹ó���ɶ� �߻�Ǿ��ִ� ��� �Ѿ��� �浹ó���� �������� ����
				(*mviBoss).Dammaged(m_player->GetDamage());
				m_player->SetBulletFire(i, false);
			}

			//���� �Ӹ��� �÷��̾� �Ѿ��� �浹
			if (IntersectRectCircle((*mviBoss).GetHornRect(), m_player->GetBullet(i).cc) &&
				(*mviBoss).GetMonsterState() != B_DEAD && m_player->GetBullet(i).isfire)
			{
				//�浹ó���ɶ� �߻�Ǿ��ִ� ��� �Ѿ��� �浹ó���� �������� ����
				(*mviBoss).Dammaged(m_player->GetDamage() * 2);
				m_player->SetBulletFire(i, false);
			}


			for (int j = 0; j < 10; j++)
			{
				//���� ����� �÷��̾� �������� �浹
				if (IntersectRect((*mviBoss).GetRect(), m_player->GetLazor(j).rc) &&
					(*mviBoss).GetMonsterState() != B_DEAD && m_player->GetLazor(j).isfire)
				{
					if (CheckTime(1.0f))
					{
						//ƽ�� 20������ ������ (���ݷ� 80����)
						(*mviBoss).Dammaged(m_player->GetDamage() / 10);
					}
				}
			}

		}
	}


	//�� �����۰� �÷��̾� �浹
	for (mviHeal = mvHeal.begin(); mviHeal != mvHeal.end();)
	{
		//�÷��̾�� �浹�ϸ� �ٷ� ������ ������ ȿ���ߵ����ش�.
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

	//������ �����۰� �÷��̾� �浹
	for (mviLazor = mvLazor.begin(); mviLazor != mvLazor.end();)
	{
		//�÷��̾�� �浹�ϸ� �ٷ� ������ ������ ȿ���ߵ����ش�.
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

	//���ʽ� ���� �����۰� �÷��̾� �浹
	for (mviBonusStat = mvBonusStat.begin(); mviBonusStat != mvBonusStat.end();)
	{
		//�÷��̾�� �浹�ϸ� �ٷ� ������ ������ ȿ���ߵ����ش�.
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

	//���� ���� �������ϱ� �����ش�.
	for (mviBird = mvBird.begin(); mviBird != mvBird.end();)
	{
		if ((*mviBird).GetIsDead())
		{
			//���� ������ 50% Ȯ���� ȸ�������۶���
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

	//���� �������� �����������̴ϱ� �����ش�.
	for (mviGagail = mvGagail.begin(); mviGagail != mvGagail.end();)
	{
		if ((*mviGagail).GetIsDead())
		{
			//�������� ������ 50% Ȯ���� ȸ�������۶���
			if (GetInt(51) < 25)
			{
				mHeal = new Heal;
				mHeal->init((*mviGagail).GetPoint(),1);
				mvHeal.emplace_back(*mHeal);
			}
			//25% Ȯ���� ������ ������ ����
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

	//���ű�� ����������̴ϱ� �����ش�.
	for (mviSeagull = mvSeagull.begin(); mviSeagull != mvSeagull.end();)
	{
		if ((*mviSeagull).GetIsDead())
		{
			//�������� ������ 50% Ȯ���� ȸ�������۶���
			if (GetInt(51) < 25)
			{
				mHeal = new Heal;
				mHeal->init((*mviSeagull).GetPoint(),2);
				mvHeal.emplace_back(*mHeal);
			}
			//40% Ȯ���� ������ ������ ����
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

	//����� ���̾�!
	//������ ��������!
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

	//�÷��̾�� �浹���ϰ� ������ ������ ������
	//�׷� �����ۿ��� ������
	for (mviHeal = mvHeal.begin(); mviHeal != mvHeal.end();)
	{
		if ((*mviHeal).GetMonsterState() == M_DEAD)
		{
			(*mviHeal).release();
			mviHeal = mvHeal.erase(mviHeal);
			//cout << "��ģ �� ����" << endl;
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
