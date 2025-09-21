#pragma once
#include "Level3DRender/LevelRender.h"
#include "sound/SoundSource.h"


class Player;
class GameCamera;
class BackGround;
class Enemy;
class UI;
class Boss;
class GameClear;
class GameOver;
class RecoveryItem;



class Game : public IGameObject
{
public:
	Game();
	~Game();
	void Update();
	void Render(RenderContext& rc);

private:
	Vector3 m_position;
	Player* m_player;
	GameCamera* m_gameCamera;
	FontRender m_fontRender;
	BackGround* m_backGround;
	SoundSource* m_bgm;
	Enemy* m_enemy;
	SkyCube* skyCube;
	UI* m_ui;
	Boss* m_boss;
	RecoveryItem* m_recoveryitem;

	int totalEnemyCount = 3; //ìGÇÃêî
	int totalBossCount = 1; //É{ÉXÇÃêî
	bool m_gameClearTriggered = false;
};

