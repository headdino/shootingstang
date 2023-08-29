#pragma once
#include "Player.h"
#include "bird.h"
#include "gagail.h"
#include "seagull.h"
#include "boss.h"
#include "Heal.h"
#include "Lazor.h"
#include "BonusStat.h"

class MonsterManager : public GameNode
{
private:
	Player* m_player;
	bird* mBird;
	vector<bird> mvBird;
	vector<bird>::iterator mviBird;

	gagail* mGagail;
	vector<gagail> mvGagail;
	vector<gagail>::iterator mviGagail;

	seagull* mSeagull;
	vector<seagull> mvSeagull;
	vector<seagull>::iterator mviSeagull;

	boss* mBoss;
	vector<boss> mvBoss;
	vector<boss>::iterator mviBoss;

	Heal* mHeal;
	vector<Heal> mvHeal;
	vector<Heal>::iterator mviHeal;

	Lazor* mLazor;
	vector<Lazor> mvLazor;
	vector<Lazor>::iterator mviLazor;

	BonusStat* mBonusStat;
	vector<BonusStat> mvBonusStat;
	vector<BonusStat>::iterator mviBonusStat;

	float m_lazorCheckTime = 0.0f;


	float m_bossSpawnTime = 0.0f;
	bool m_isBird;
	bool m_isGagail;
	bool m_isSeagull;
	bool m_isStop;
	bool m_isBoss;

	float m_BirdTime = 0.0f;
	float m_GagailTime = 0.0f;
	float m_SeagullTime = 0.0f;
	
	float m_ItemTime = 0.0f;

	bool m_OnGame = true;

public:
	MonsterManager();
	~MonsterManager()override;

	HRESULT init() override;
	void release() override;
	void update() override;
	void render() override;

	void Spawn();

	//충돌을 위해서 플레이어를 가져오는 함수
	void givePlayer(Player* player) { m_player = player; }
	void CheckInter();
	void CheckErase();
	bool CheckTime(float delay);

	bool GetOngame() { return m_OnGame; }
};

