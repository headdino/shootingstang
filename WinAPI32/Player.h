#pragma once
#include "GameNode.h"

enum PLAYER_STATE
{
	MOVE,
	HIT,
	DEAD
};

struct TAGPLAYER
{
	FPOINT pt;	//위치잡아주는 점
	FRECT rc;	//충돌체렉트
	int hp;
	int maxHp;
	int damage;
	float moveSpeed;
};

struct TAGBULLET
{
	FPOINT pt;
	FCIRCLE cc;
	float moveSpeed;
	float radian;
	//bool isuseble;
	bool isfire;
};

struct TAGLAZOR
{
	FPOINT pt;
	FRECT rc;
	int frameX;
	bool isfire;
	float lazorTime;
	float lazorDelay;
};

class Player : public GameNode
{
private:
	TAGPLAYER m_player;
	PLAYER_STATE m_playerState;
	TAGBULLET m_bullet[BULLETMAX];

	int m_haveLazor;
	TAGLAZOR m_lazor[10];

	float m_time;
	float m_frameCount;
	int m_frameX;
	int m_frameY;
	BYTE m_alpha;

	int m_life;
	float m_lifeFrameX;

	float m_StateTime;
	float m_HitTime;

	bool m_canAttack;
	float m_attackTime;
	float m_attackDelay;

	bool m_OnGame;

public:
	Player();
	~Player() override;

	HRESULT init() override;
	void release() override;
	void update() override;
	void render() override;

	void frameMove();
	void fire();
	void fireLazor();
	void lazorDelete();
	void bulletMove();
	void SwitchState();
	void Dammaged(int damage);

	bool GetOngame() { return m_OnGame; }

	TAGBULLET GetBullet(int i) { return m_bullet[i]; }
	void SetBulletFire(int i, bool fire) { m_bullet[i].isfire = fire; }
	TAGLAZOR GetLazor(int i) { return m_lazor[i]; }
	int GetDamage() { return m_player.damage; }
	void HealPlayer(int heal) { m_player.hp += heal; }
	void PlusLazor(int num) { m_haveLazor += num; }

	void PlusDamage(int damage) { m_player.damage += damage; }
	void PlusMaxHp(int hp) { m_player.maxHp += hp; }
	void PlusAttackSpeed(float speed) { m_attackDelay -= speed; }
	void PlusMovementSpeed(float speed) { m_player.moveSpeed += speed; }

	FRECT GetPlayerRect() { return m_player.rc; }
	FPOINT GetPlayerPT() { return m_player.pt; }

};

