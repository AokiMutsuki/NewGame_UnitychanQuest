#include "stdafx.h"
#include "GameClear.h"
#include "Title.h"
#include "Game.h"


GameClear::GameClear()
{
	m_spriteRender.Init("Assets/sprite/GameClear.DDS", 1920.0f, 1080.0f);
}

GameClear::~GameClear()
{

}

void GameClear::Update()
{
	//Yボタンが押されたら。
	if (!g_pad.empty() && g_pad[0] != nullptr && g_pad[0]->IsTrigger(enButtonY))
	{
		//タイトルのオブジェクトを作る。
		NewGO<Title>(0, "Title");
		//自身を削除する。
		DeleteGO(this);
	}
}

void GameClear::Render(RenderContext& rc)
{
	m_spriteRender.Draw(rc);
}