#pragma once
#include "GameNode.h"

enum TURN
{
	TURN_1p,
	TURN_1pFire,
	TURN_2p,
	TURN_2pFire,
};

struct ST_PLAYER
{
	FPOINT p;			//중심좌표
	FRECT rc;			//충돌박스
	float hp;			//hp
	float angle;		//발사되는 각도
	int frame;			//그려줄 이미지
};


class Star :public GameNode
{
private:
	FRECT		m_rcWall;		//벽 충돌체
	ST_PLAYER	m_pl[2];		//플레이어 구조체
	TURN		m_turn;


	FRECT		m_rcEgg;		//알 충돌체
	float		m_gravity;		//중력값
	float		m_power;		//쏘는힘


public:
	Star();
	~Star() override;
	HRESULT init() override;
	void release() override;
	void update() override;
	void render() override;
};

