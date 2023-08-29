#pragma once
#include "monster.h"

class bird : protected monster
{
private:
	
public:
	bird();
	~bird() override;

	HRESULT init() override;
	void release() override;
	void update() override;
	void render() override;

	void frameMove() override;
	//void SwitchState() override;

	FRECT GetRect() { return m_monster.rc; }
	FPOINT GetPoint() { return m_monster.pt; }
	int GetDamage() { return m_monster.damage; }
	MONSTER_STATE GetMonsterState() { return m_monsterState; }
	bool GetIsDead() { return m_isDead; }

	void Dammaged(int damage) override;
};

