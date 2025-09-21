#include "stdafx.h"
#include "Game.h"
#include "Player.h"
#include "GameCamera.h"
#include "BackGround.h"
#include "sound/SoundEngine.h"
#include "Enemy.h"
#include "UI.h"
#include "Title.h"
#include "Boss.h"
#include "GameClear.h"
#include "GameOver.h"
#include "RecoveryItem.h"



Game::Game()
{

	

	m_player = NewGO<Player>(0, "player");

	m_gameCamera = NewGO<GameCamera>(0, "gameCamera");

	m_backGround = NewGO<BackGround>(0, "ground2");

    m_ui = NewGO<UI>(0, "ui");

	Boss* boss = NewGO<Boss>(0, "boss");
	


	Enemy* enemy1 = NewGO<Enemy>(0, "enemy1");
	enemy1->SetPosition({ -6333.0f, 0.0f, -8337.3f });
    
    Enemy* enemy2 = NewGO<Enemy>(0, "enemy2");
	enemy2->SetPosition({ -3415.0f,0.0f,-4994.0f });

	Enemy* enemy3 = NewGO<Enemy>(0, "enemy3");
	enemy3->SetPosition({ -12322.0f,0.0f,949.0f });

	Enemy* enemy4 = NewGO<Enemy>(0, "enemy4");
	enemy4->SetPosition({ -22629.7f,0.0f,-6076.3f });

	Enemy* enemy5 = NewGO<Enemy>(0, "enemy5");
	enemy5->SetPosition({ 7399.8f,0.0f,-11914.3f });
	
	RecoveryItem* recoveryitem = NewGO<RecoveryItem>(0, "recoveryitem");
	recoveryitem->SetPosition({ 6030.0f,0.0f,-22032.0f });


	

}

Game::~Game()
{
	
	//エネミーを削除する。
	DeleteGO(FindGO<Enemy>("enemy1"));
	DeleteGO(FindGO<Enemy>("enemy2"));
	DeleteGO(FindGO<Enemy>("enemy3"));
	DeleteGO(FindGO<Enemy>("enemy4"));
	DeleteGO(FindGO<Enemy>("enemy5"));
	DeleteGO(FindGO<RecoveryItem>("recoveryitem"));
	DeleteGO(FindGO<Boss>("boss"));

	//BGMを削除する
	DeleteGO(m_bgm);

	//プレイヤーを削除する
	DeleteGO(m_player);

	//ステージを削除する
	DeleteGO(m_backGround);

    //カメラを削除する
    DeleteGO(m_gameCamera);

	//UIを削除する
	DeleteGO(m_ui);

}

	
void Game::Update()
{

    auto bosses = FindGOs<Boss>("boss");

    // ボス+敵を倒したらクリア
    if (m_player->BossCount == 1 && m_player->EnemyCount >= 5)
    {
        NewGO<GameClear>(0, "GameClear");
        DeleteGO(this);
        return;
    }

    if (m_player->GetPosition().y <= -1500.0f || m_player->GetHP() <= 0)
    {
        NewGO<GameOver>(0, "GameOver");  // 
        DeleteGO(m_player);    // プレイヤー削除（任意）
        DeleteGO(this);



        for (auto boss : bosses)
        {
            DeleteGO(boss);

        }


    }
   


}



void Game::Render(RenderContext& rc)
{
	m_fontRender.Draw(rc);
}