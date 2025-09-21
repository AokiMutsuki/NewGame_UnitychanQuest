#include "stdafx.h"
#include "UI.h"
#include "Player.h"
#include "Enemy.h"
#include "Game.h"
#include "Boss.h"



UI::UI()
{
  
   
    


    constexpr float kPlayerHpBarWidth = 80.0f;
    constexpr float kPlayerHpBarHeight = -80.0f;

    constexpr float kEnemyHpBarWidth = 70.0f;
    constexpr float kEnemyHpBarHeight = -70.0f;

    constexpr float kBossHpBarWidth = 75.0f;
    constexpr float kBossHpBarHeight= -75.0f;

    m_playerHpBar.Init("Assets/Sprite/red.png", kPlayerHpBarWidth, kPlayerHpBarHeight);
    m_enemyHpBar.Init("Assets/Sprite/White.png", kEnemyHpBarWidth, kEnemyHpBarHeight);
    m_bossHpBar.Init("Assets/Sprite/While.png", kBossHpBarWidth, kBossHpBarHeight);

    // プレイヤーHPテキストの位置（画面左上）
    m_playerHpTexts.SetPosition(Vector3(-500.0f, 300.0f,0.0f)); // X: 左へ, Y: 上へ

    // 敵HPテキストの位置（画面右上）
    m_enemyHpTexts.SetPosition(Vector3(300.0f, 300.0f,0.0f)); // X: 右へ, Y: 上へ

    //ボスHPテキストの位置（画面右上）
    m_bossHpTexts.SetPosition(Vector3(-100.0f, 300.0f,0.0f)); // X: 右へ、Y: 上へ

   
}




UI::~UI()
{

}

void UI::Update()
{

    auto player = FindGO<Player>("player");
    auto enemy1 = FindGO<Enemy>("enemy1");
    auto boss = FindGO<Boss>("boss");




    // HP表示用のフォーマットとバッファサイズ
    constexpr size_t kHpTextBufferSize = 150;
    constexpr const char* kHpFormat = "%d / %d";

    // マルチバイト文字列 → ワイド文字列変換用バッファ
    char hpText[kHpTextBufferSize];
    wchar_t whpText[kHpTextBufferSize];


    if (player) {
        // プレイヤーのHPを文字列に変換
        sprintf(hpText, kHpFormat, player->GetHP(), player->GetMaxHP());
        // ワイド文字列に変換してUIに表示（SetTextは wchar_t* を要求）
        size_t converted = 0;
        mbstowcs_s(&converted, whpText, kHpTextBufferSize, hpText, _TRUNCATE);
        m_playerHpTexts.SetText(whpText);

        //  HPが25以下なら赤色にする
        if (player->GetHP() <= 25) {
            m_playerHpTexts.SetColor(Vector4(1, 0, 0, 1)); // 赤
        }
        else {
            m_playerHpTexts.SetColor(Vector4(1, 1, 1, 1)); // 通常は白
        }


        if (player && enemy1) {
           //プレイヤーとエネミーの距離計算
            float distance = (enemy1->GetPosition() - player->GetPosition()).Length();
            //もしプレイヤーがエネミーに近づいたら
            if (distance <= kHpBarDisplayRange) {
                // エネミーのHPバー表示
                ShowEnemyHp(enemy1);
            }
            else {
                //エネミーのHPバーを非表示
                HideEnemyHp();
            }
        }

        if (player && boss) {
            //プレイヤーとボスの距離計算
            float distance = (boss->GetPosition() - player->GetPosition()).Length();
            //もしプレイヤーがボスに近づいたら
            if (distance <= kHpBarDisplayRange) {
                //ボスのHPバーを表示
                ShowBossHp(boss);
            }
            else {
                // ボスのHPバーを非表示
                HideBossHp();
            }
        }


        // HPが0なら GameOver 表示に切り替え
        if (player->GetHP() <= 0)
        {
            // GameOverメッセージを生成
            Vector3 pos = player->GetPosition();
            sprintf(hpText, "GameOver: HP=%d Pos=(%.1f, %.1f, %.1f)", player->GetHP(), pos.x, pos.y, pos.z);

            // ワイド文字列に変換して赤色で表示
            mbstowcs_s(&converted, whpText, kHpTextBufferSize, hpText, _TRUNCATE);

            m_playerHpTexts.SetText(whpText);

            m_playerHpTexts.SetColor(Vector4(1, 0, 0, 1)); // 赤色で強調


        }
    }

    if (enemy1) {


        size_t converted = 0;
 

        // 敵のHPが0なら kill 表示に切り替え
        if (enemy1->GetHP() == 0)
        {
            //エネミーの座標を取得
            Vector3 pos = enemy1->GetPosition();

            //撃破メッセージ
            sprintf(hpText, "Kill: HP=%d Pos=(%.1f,%.1f,%.1f)", enemy1->GetHP(), pos.x, pos.y, pos.z);

            //マルチバイドの文字列をワイド文字列に変換
            mbstowcs_s(&converted, whpText, kHpTextBufferSize, hpText, _TRUNCATE);

            //撃破メッセージをUIに表示
            m_enemyHpTexts.SetText(whpText);
            m_enemyHpTexts.SetColor(Vector4(1, 0, 0, 1)); // 赤色で強調



            DeleteGO(enemy1);


        }
    }
        if (boss)
        {
            size_t converted = 0;

            // ボスのHPが0なら kill Hey!!!! 表示に切り替え
            if (boss->GetHP() == 0)
            {
                //ボスの座標の取得
                Vector3 pos = boss->GetPosition();

                //撃破メッセージ
                sprintf(hpText, "Kill Hey!!!!: HP=%d Pos=(%.1f,%.1f,%.1f)", boss->GetHP(), pos.x, pos.y, pos.z);

                //マルチバイドの文字列をワイド文字列に変換
                mbstowcs_s(&converted, whpText, kHpTextBufferSize, hpText, _TRUNCATE);

                //撃破メッセージをUIに表示
                m_enemyHpTexts.SetText(whpText);
                m_enemyHpTexts.SetColor(Vector4(1, 0, 0, 1)); // 赤色で強調

                DeleteGO(boss);
            }
        }


    
}

void UI::ShowEnemyHp(Enemy* enemy) {
    char hpText[150];// 整形用の文字列バッファ（マルチバイト）
    wchar_t whpText[150];  // 表示用のワイド文字列バッファ

    //ボスの現在HPと最大HPを"xx/yy"式（例：20/20)で文字列に変換する
    sprintf(hpText, "%d / %d", enemy->GetHP(), enemy->GetMaxHP());
    size_t converted = 0;

    //マルチバイドの文字列をワイド文字列に変換
    mbstowcs_s(&converted, whpText, 150, hpText, _TRUNCATE);
    m_enemyHpTexts.SetText(whpText);
    
}

void UI::HideEnemyHp() {
    //空文字列をセットすることでHPバーを非表示にする
    m_enemyHpTexts.SetText(L"");
}

void UI::ShowBossHp(Boss* boss)
{
    char hpText[150];// 整形用の文字列バッファ（マルチバイト）
    wchar_t whpText[150];  // 表示用のワイド文字列バッファ


    //ボスの現在HPと最大HPを"xx/yy"式で文字列に変換する
    sprintf(hpText, "%d / %d", boss->GetHP(), boss->GetMaxHP());
    size_t converted = 0;
 
    //マルチバイトの文字列をワイド文字列に変換
    mbstowcs_s(&converted, whpText, 150, hpText, _TRUNCATE);
    m_bossHpTexts.SetText(whpText);//ボスのHPテキストをUIに表示
   
}


void UI::HideBossHp() {

    //空文字列をセットすることでHPバーを非表示にする
    m_bossHpTexts.SetText(L"");
}


void UI::MoveState()
{

}

void UI::Render(RenderContext& rc)
{
    
  
    m_playerHpTexts.Draw(rc);
    
    m_enemyHpTexts.Draw(rc);

    m_bossHpTexts.Draw(rc);

}