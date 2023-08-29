#pragma once
#include "GameNode.h"

enum MONSTER_STATE
{
	M_MOVE,
	M_HIT,
	M_DEAD,
	B_MOVE,
	B_ATTACK,
	B_DEAD
};

enum MOVE_TYPE
{
	ONLYX,
	XANDY,
	BOSS_MOVE
};

enum ATTACK_TYPE
{
	BASIC,
	BULLET,
	MOVE_BULLET,
	BOSS_ATTACK
};

struct TAGMONSTER
{
	FPOINT pt;	//위치잡아주는 점
	FRECT rc;	//충돌체렉트
	int hp;
	int damage;
	float moveSpeed;
};

struct TAGMBULLET
{
	FPOINT pt;
	FCIRCLE cc;
	float moveSpeed;
	float degree;
	float imageRotateRadian;
	bool isfire;
};

class monster : public GameNode
{
protected:
	TAGMONSTER m_monster;
	TAGMBULLET m_bullet[BULLETMAX];

	ATTACK_TYPE m_attackType;
	MOVE_TYPE m_moveType;
	MONSTER_STATE m_monsterState;

	float m_time;
	float m_frameCount;
	int m_frameX;
	int m_frameY;
	BYTE m_alpha;

	float m_StateTime;
	float m_HitTime;

	bool m_canAttack;
	float m_attackTime;
	float m_attackDelay;

	bool m_isDead;
	bool m_isUp = GetInt(2);
public:
	monster();
	~monster() override;

	HRESULT init() override;
	void release() override;
	void update() override;
	void render() override;

	virtual void SwitchState();

	virtual void frameMove() = 0;

	virtual void attack();
	virtual void bulletMove();
	

	virtual FRECT GetRect() { return m_monster.rc; }
	virtual FPOINT GetPoint() { return m_monster.pt; }
	virtual int GetDamage() { return m_monster.damage; }
	virtual bool GetIsDead() { return m_isDead; }
	virtual MONSTER_STATE GetMonsterState() { return m_monsterState; }
	virtual TAGMBULLET GetMonsterBullet(int i) { return m_bullet[i]; }
	virtual void SetMonsterBulletFire(int i, bool fire) { m_bullet[i].isfire = fire; }
	virtual void Dammaged(int damage) = 0;
};

