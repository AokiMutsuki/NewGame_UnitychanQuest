#pragma once

class UI;
class Enemy;
class Sword;
class Player : public IGameObject
{
public:
	Player();
	~Player();
	void Move();
	void Rotation();
	void PlayAnimation();
	void ManageState();
	void Update();
	void Render(RenderContext& renderContext);
	bool IsDead() const { return m_isDead; }
	
	

	Vector3 m_position;
	ModelRender m_modelRender;
	Player* m_player;
	
	
public:
	void TakeDamage(int amount) {
		m_hp -= amount;
		if (m_hp < 0) m_hp = 0;
		if (m_hp == 0) m_isDead = true;


	}


	int GetHP() const { return m_hp; }
	int GetMaxHP() const { return m_maxHp; }

	int m_hp = 50;
	int m_maxHp = 50;

	

	constexpr static float kDamageRange = 1000.0f;  // 攻撃範囲

	//誤差範囲
	const float kEpsilon = 0.1f;

	enum EnAnimationClip {		//アニメーション。
		enAnimationClip_Idle,
		enAnimationClip_Walk,
		enAnimationClip_Jump,
		enAnimationClip_Run,
		enAnimationClip_Num



	};
	AnimationClip m_animationClips[enAnimationClip_Num];		//アニメーションクリップ。


	CharacterController characterController;
	Vector3 m_moveSpeed;
	Quaternion rotation;
	int m_playerState = 0;
	int m_PlayerHP = 100;


	bool shouldDelete = false;


	FontRender m_fontRender;
	Vector3 nDoubleJumped;
	bool canDoubleJump = false;
	bool hasDoubleJumped = false;
	bool isDashing = false;
	float DishSpeedMultiplier = 3.0f;

	Vector3 initialPosition;
	bool returnedToStart = false;
	Vector3 GetPosition() const;
	int BossCount = 0;
	
	

	SpriteRender m_gameClearSprite;
	int totalBossCount = 1; //ボス
	bool gameClearTriggered = false;


	
	int playerState = 0;
	int itemCount = 0;
	int recoveryItemCount = 1;



	

	enum KeyCode {
		// ...
		Key_Input_Z = 0x5A
	};








};
