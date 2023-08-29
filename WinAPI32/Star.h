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
	FPOINT p;			//�߽���ǥ
	FRECT rc;			//�浹�ڽ�
	float hp;			//hp
	float angle;		//�߻�Ǵ� ����
	int frame;			//�׷��� �̹���
};


class Star :public GameNode
{
private:
	FRECT		m_rcWall;		//�� �浹ü
	ST_PLAYER	m_pl[2];		//�÷��̾� ����ü
	TURN		m_turn;


	FRECT		m_rcEgg;		//�� �浹ü
	float		m_gravity;		//�߷°�
	float		m_power;		//�����


public:
	Star();
	~Star() override;
	HRESULT init() override;
	void release() override;
	void update() override;
	void render() override;
};

