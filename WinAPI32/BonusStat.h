#pragma once
#include "monster.h"

enum BONUS_STAT
{
	ATTSPD = 1,
	DMG,
	MHP,
	MVSPD
};

class BonusStat : protected monster
{
private:
	int m_itemType;
	int m_intNum;
	float m_floatNum;
public:
	BonusStat();
	~BonusStat() override;

	HRESULT init() override;
	//아이템이 떨어지는 지점을 정해주는 초기화
	HRESULT init(FPOINT startpt, int type);
	//0~5 사이의 수를 startpt에 넣으면 특정위치에 아이템을 뿌려주는 초기화
	HRESULT init(int startpt, int type);
	void release() override;
	void update() override;
	void render() override;

	void frameMove() override;

	int GetItemType() { return m_itemType; }
	int GetIntNum() { return m_intNum; }
	float GetFloatNum() { return m_floatNum; }

	FRECT GetRect() { return m_monster.rc; }
	int GetDamage() { return m_monster.damage; }
	MONSTER_STATE GetMonsterState() { return m_monsterState; }
	bool GetIsDead() { return m_isDead; }

	//??
	virtual void Dammaged(int damage) { int a = damage; }
};

