#include "stdafx.h"
#include "MainGame.h"


MainGame::MainGame()
	:m_pRect(nullptr), m_pStar(nullptr)
{
}


MainGame::~MainGame()
{
	//싱글톤 해제
	KEYMANAGER->ReleaseSingleton();
	TIMEMANAGER->ReleaseSingleton();
	//이미지매니저 삭제되기전에 모든 이미지 전체삭제
	IMGMANAGER->deleteAll();
	IMGMANAGER->ReleaseSingleton();
}

HRESULT MainGame::init()
{
	//윈도우가 시작되서 지금까지 흐른 시간을 1/1000초 단위로
	//DWORD형을 리턴하는 함수다
	srand(GetTickCount());
	////////////////////////////////////////////////////

	

	m_pRect = new RectA;
	m_pRect->init();


	m_pStar = new Star;
	m_pStar->init();

	IMGMANAGER->addImage("BG", _T("images/배경 화면.bmp"), 228, 193);
	//키값은 중복 불가
	//IMGMANAGER->addImage("BG", _T("images/배경 화면.bmp"), WINSIZEX, WINSIZEY);
	IMGMANAGER->addImage("Apple", _T("images/apple.bmp"), 124, 162,true);
	IMGMANAGER->addImage("Ball", _T("images/ball.bmp"), 100, 100,true);
	IMGMANAGER->addImage("Apple2", _T("images/ap.bmp"), 900, 900);

	IMGMANAGER->addImage("록맨", _T("images/록맨.bmp"), 480, 100,10,2,true);

	IMGMANAGER->addImage("Yoshi", _T("images/요시.bmp"), 400, 120, 4, 1, true);
	IMGMANAGER->addImage("Egg", _T("images/알.bmp"), 50, 50, true);
	IMGMANAGER->addImage("Wall", _T("images/벽.bmp"), 200, 356, true);

	IMGMANAGER->addImage("구름", _T("images/cloud.bmp"), WINSIZEX, WINSIZEY);
	IMGMANAGER->addImage("바닥", _T("images/ground.bmp"), 2080, 1560, true);

	addImage();

	m_gameState = MENU;

	m_pMenu = new Menu;
	m_pMenu->init();

	m_pExplane = new Explane;
	m_pExplane->init();

	m_pGame = new PlayGame;
	m_pGame->init();


	//IMGMANAGER->addImage("록맨", _T("images/록맨.bmp"), 480, 100, 10, 2);
	

	////////////////////////////////////////////////////
	return S_OK;
}

void MainGame::release()
{
	////////////////////////////////////////////////////

	m_pRect->release();
	SAFE_DELETE(m_pRect);

	m_pStar->release();
	SAFE_DELETE(m_pStar);

	m_pMenu->release();
	SAFE_DELETE(m_pMenu);

	m_pExplane->release();
	SAFE_DELETE(m_pExplane);

	m_pGame->release();
	SAFE_DELETE(m_pGame);


	////////////////////////////////////////////////////
}

void MainGame::update()
{
	//InvalidateRect(g_hwnd, NULL, false);
	////////////////////////////////////////////////////

	//m_pStar->update();
	m_pRect->update();

	switch (m_gameState)
	{
	case MENU:
		m_pMenu->update();
		m_pExplane->SetGameState(m_pMenu->GetGameState());
		//m_pGame->SetGameState(m_pMenu->GetGameState());
		//m_pGameover->SetGameState(m_pMenu->GetGameState());
		m_gameState = m_pMenu->GetGameState();
		break;
	case INGAME:
		m_pGame->update();
		//m_pMenu->SetGameState(m_pGame->GetGameState());
		//m_gameState = m_pGame->GetGameState();
		break;
	case EXPLAN:
		m_pExplane->update();
		m_pMenu->SetGameState(m_pExplane->GetGameState());
		m_gameState = m_pExplane->GetGameState();
		break;
	}
	

	////////////////////////////////////////////////////
}

void MainGame::render()
{
	//패턴을 출력하는 함수(dc에 선택되어있는 브러시 색상을 그대로출력 ,WHITENESS ->그냥 하얀색으로출력)
	PatBlt(IMGMANAGER->getMemDC(), 0, 0, WINSIZEX, WINSIZEY, WHITENESS);
	////////////////////////////////////////////////////
	m_pRect->render();
	//m_pStar->render();
	
	switch (m_gameState)
	{
	case MENU:
		m_pMenu->render();
		break;
	case INGAME:
		m_pGame->render();
		break;
	case EXPLAN:
		m_pExplane->render();
		break;
	}

	////////////////////////////////////////////////////
	TIMEMANAGER->render();
	//고속복사 백dc에 그릴내용을 프론트에 복사하여 출력
	BitBlt(IMGMANAGER->getHDC(), 0, 0, WINSIZEX, WINSIZEY, IMGMANAGER->getMemDC(), 0, 0, SRCCOPY);

}

void MainGame::addImage()
{
	IMGMANAGER->addImage("Player", "images/shoot/player.bmp", 438, 179, 6, 3, true);

	IMGMANAGER->addImage("Monster", "images/shoot/monster.bmp", 344, 126, 5, 2, true);
	IMGMANAGER->addImage("Monster2_move", "images/shoot/monster2_move.bmp", 412, 117, 4, 1, true);
	IMGMANAGER->addImage("Monster2_hit", "images/shoot/monster2_hit.bmp", 210, 96, 2, 1, true);
	IMGMANAGER->addImage("Monster2_bullet", "images/shoot/monster2_bullet.bmp", 33, 33, true);

	IMGMANAGER->addImage("Monster3_move", "images/shoot/monster3_move.bmp", 875, 91, 5, 1, true);
	IMGMANAGER->addImage("Monster3_hit", "images/shoot/monster3_hit.bmp", 153, 85, true);
	IMGMANAGER->addImage("Monster3_bullet", "images/shoot/monster3_bullet.bmp", 26, 28, true);

	IMGMANAGER->addImage("Boss_move", "images/shoot/boss_move.bmp", 302, 46, 6, 1, true);
	IMGMANAGER->addImage("Boss_dead", "images/shoot/boss_dead.bmp", 123, 45, 3, 1, true);
	IMGMANAGER->addImage("Boss_attack", "images/shoot/boss_attack.bmp", 282, 46, 6, 1, true);
	IMGMANAGER->addImage("Boss_bullet", "images/shoot/boss_bullet.bmp", 52, 26, true);
	IMGMANAGER->addImage("Boss_head", "images/shoot/boss_head.bmp", 28, 38, true);

	IMGMANAGER->addImage("PlayerBullet1", "images/shoot/rock.bmp", 31, 32, true);

	IMGMANAGER->addImage("HPBarTop", "images/shoot/hpBarTop.bmp", 53, 5);
	IMGMANAGER->addImage("HPBarBottom", "images/shoot/hpBarBottom.bmp", 53, 5);
	IMGMANAGER->addImage("PlayerLife", "images/shoot/playerLife.bmp", 288, 34, 8, 1, true);
	IMGMANAGER->addImage("Have_Lazor", "images/shoot/have_lazor.bmp", 64, 71, true);
	IMGMANAGER->addImage("Lazor", "images/shoot/lazor.bmp", 800, 150, true);
	IMGMANAGER->addImage("LazorEffect", "images/shoot/effect_electro.bmp", 156, 48, 3, 1, true);

	IMGMANAGER->addImage("GameStart", "images/shoot/menu_gameStart.bmp", 800, 200, 2, 1, true);
	IMGMANAGER->addImage("Explane", "images/shoot/menu_explane.bmp", 800, 200, 2, 1, true);

	IMGMANAGER->addImage("Sky1", "images/shoot/sky1.bmp", WINSIZEX, WINSIZEY);
	IMGMANAGER->addImage("Sky2", "images/shoot/sky2.bmp", WINSIZEX, WINSIZEY);
	IMGMANAGER->addImage("Sky3", "images/shoot/sky3.bmp", WINSIZEX, WINSIZEY);

	IMGMANAGER->addImage("Heal1", "images/shoot/heal.bmp", 35, 38, true);
	IMGMANAGER->addImage("Heal2", "images/shoot/heal2.bmp", 37, 37, true);
	
	IMGMANAGER->addImage("Bonus_dmg", "images/shoot/bonusStat_dmg.bmp", 46, 47, true);
	IMGMANAGER->addImage("Bonus_attSpd", "images/shoot/bonusStat_attSpd.bmp", 37, 49, true);
	IMGMANAGER->addImage("Bonus_mhp", "images/shoot/bonusStat_mhp.bmp", 40, 48, true);
	IMGMANAGER->addImage("Bonus_mvspd", "images/shoot/bonusStat_moveSpd.bmp", 44, 51, true);

	IMGMANAGER->addImage("Explan_1", "images/shoot/explan_playertem.bmp", 1000, 600);
	IMGMANAGER->addImage("Explan_2", "images/shoot/explan_monster.bmp", 1000, 600);

	IMGMANAGER->addImage("BackGround_lose", "images/shoot/backGround_lose.bmp", 1200, 600);
	IMGMANAGER->addImage("BackGround_win", "images/shoot/backGround_win.bmp", 1200, 600);

	IMGMANAGER->addImage("Text_lose", "images/shoot/text_Lose.bmp", 400, 1200, true);
	IMGMANAGER->addImage("Text_Win", "images/shoot/text_Win.bmp", 400, 1200, true);

	SOUNDMANAGER->addSound("BGM", "sound/Bgm.wav", true);
	SOUNDMANAGER->addSound("Shoot", "sound/gun.wav", false);
	SOUNDMANAGER->addSound("Lazor", "sound/lazor.wav", false);
	SOUNDMANAGER->addSound("Wind", "sound/wind.wav", false);
	SOUNDMANAGER->addSound("GagailBullet", "sound/gagail.wav", false);
	SOUNDMANAGER->addSound("Item", "sound/item.wav", false);
	SOUNDMANAGER->addSound("Bird", "sound/bird.wav", false);
	SOUNDMANAGER->addSound("Seagull", "sound/seagull.wav", false);
	SOUNDMANAGER->addSound("Playerhit", "sound/playerhit.wav", false);

}
