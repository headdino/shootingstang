#pragma once
#include "monster.h"

class gagail : protected monster
{
private:

public:
	gagail();
	~gagail()override;

	HRESULT init() override;
	void release() override;
	void update() override;
	void render() override;

	void frameMove() override;

	void attack() override;
	void bulletMove() override;

	FRECT GetRect() { return m_monster.rc; }
	FPOINT GetPoint() { return m_monster.pt; }
	int GetDamage() { return m_monster.damage; }
	MONSTER_STATE GetMonsterState() { return m_monsterState; }
	TAGMBULLET GetMonsterBullet(int i) { return m_bullet[i]; }
	void SetMonsterBulletFire(int i, bool fire) { m_bullet[i].isfire = fire; }
	bool GetIsDead() { return m_isDead; }

	void Dammaged(int damage) override;
};

