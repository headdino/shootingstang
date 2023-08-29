#pragma once
#include "monster.h"

class Lazor : protected monster
{
public:
	Lazor();
	~Lazor()override;

	HRESULT init() override;
	//아이템이 떨어지는 지점을 정해주는 초기화
	HRESULT init(FPOINT startpt);
	void release() override;
	void update() override;
	void render() override;

	void frameMove() override;

	FRECT GetRect() { return m_monster.rc; }
	int GetDamage() { return m_monster.damage; }
	MONSTER_STATE GetMonsterState() { return m_monsterState; }
	bool GetIsDead() { return m_isDead; }

	//??
	virtual void Dammaged(int damage) { int a = damage; }
};

