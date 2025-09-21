#pragma once

class Player;
class Enemy;
class Game;
class Boss;

class UI : public IGameObject
{
public:
	UI();
	~UI();
	void Update();
	void MoveState();
	void Render(RenderContext&rc);
	void ShowEnemyHp(Enemy* enemy);
	void HideEnemyHp();
	void ShowBossHp(Boss* boss);
	void HideBossHp();
	

private:
	
	//プレイヤーのUI管理
	SpriteRender m_playerHpBar;
	FontRender m_playerHpTexts;
    Vector2 m_playerHpBarPos = { 50, 50 };
	const float kHpBarDisplayRange = 300.0f; // 近づいたら表示


	float GetdeltaTime;

	Vector2 m_position;
	Vector2 m_player;
	SpriteRender m_spriteRender;
	
    //エネミーのUI管理
	SpriteRender m_enemyHpBar;
	FontRender m_enemyHpTexts;
	Vector2 m_enemyHpBarPos = { 50, 100 };

	float m_killDisplayTimer = -1.0f; // -1なら非表示状態


	//ボスのUI管理
	SpriteRender m_bossHpBar;
	FontRender m_bossHpTexts;
	Vector2 m_bossHpBarPos = { 40, 100 };

	


	


	


};

