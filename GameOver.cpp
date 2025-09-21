#include "stdafx.h"
#include "GameOver.h"
#include "Title.h"
#include "Game.h"
#include "Player.h"
#include "Enemy.h"
#include "Boss.h"

GameOver::GameOver()
{
	m_spriteRender.Init("Assets/sprite/GameOver.DDS", 1980.0f, 1080.0f);
}

GameOver::~GameOver()
{

}

void GameOver::Update()
{
    // Yボタンでタイトル画面に戻る
    if (g_pad[0]->IsTrigger(enButtonY)) {
        NewGO<Title>(0, "Title");    // Titleクラスを生成
        DeleteGO(this);              // GameOver画面を削除
        return;
    }
    //}

    if (m_player == nullptr) {
        m_player = FindGO<Player>("player");
        if (m_player == nullptr) return;
    }
}
void GameOver::Render(RenderContext&rc)
{
	m_spriteRender.Draw(rc);
}