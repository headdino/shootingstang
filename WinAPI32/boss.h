#pragma once
#include "monster.h"

enum BOSS_PATTAN
{
	FIRST,
	MENU_PATTAN,
	CHARGE_PATTAN,
	SHOOT_PATTAN,
	MOVE_MENU_PATTAN,
	MOVE_TO_0,
	MOVE_TO_1,
	MOVE_TO_2,
	MOVE_TO_3
};

class boss : protected monster
{
private:
	FPOINT m_playerPT;
	TAGMBULLET m_Bbullet[BOSSBULLETMAX];

	FPOINT m_beforeCharge;
	bool m_isCharge;

	bool m_isHalfHp;

	int m_bossMovePattan;

	float m_bossAttackTime;
	float m_bossAttackTimer;

	BOSS_PATTAN m_bossPattan;
	FPOINT m_bossMovePoint[4];

	FRECT m_hornRc;
public:
	boss();
	~boss()override;

	HRESULT init() override;
	void release() override;
	void update() override;
	void render() override;

	void frameMove() override;

	void SwitchState() override;

	void attack() override;
	void bulletMove() override;

	FRECT GetRect() { return m_monster.rc; }
	FRECT GetHornRect() { return m_hornRc; }
	FPOINT GetPoint() { return m_monster.pt; }
	int GetDamage() { return m_monster.damage; }
	MONSTER_STATE GetMonsterState() { return m_monsterState; }
	TAGMBULLET GetMonsterBullet(int i) { return m_Bbullet[i]; }
	void SetMonsterBulletFire(int i, bool fire) { m_Bbullet[i].isfire = fire; }
	bool GetIsDead() { return m_isDead; }

	void Dammaged(int damage) override;

	void SetPlayerPT(FPOINT playerPT) { m_playerPT = playerPT; }
};
