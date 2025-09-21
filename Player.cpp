#include "stdafx.h"
#include "Player.h"
#include "UI.h"
#include "Enemy.h"
#include "GameClear.h"
#include "Boss.h"
#include "Game.h"




Player::Player()
{
	m_animationClips[enAnimationClip_Idle].Load("Assets/animData/idle.tka");
	m_animationClips[enAnimationClip_Idle].SetLoopFlag(true);
	m_animationClips[enAnimationClip_Walk].Load("Assets/animData/walk.tka");
	m_animationClips[enAnimationClip_Walk].SetLoopFlag(true);
	m_animationClips[enAnimationClip_Jump].Load("Assets/animData/jump.tka");
	m_animationClips[enAnimationClip_Jump].SetLoopFlag(false);
	m_animationClips[enAnimationClip_Run].Load("Assets/animData/run.tka");
	m_animationClips[enAnimationClip_Run].SetLoopFlag(false);

	m_modelRender.Init("Assets/modelData/unityChan.tkm" , m_animationClips, enAnimationClip_Num, enModelUpAxisY);

	characterController.Init(25.0f, 75.0f, m_position);

	initialPosition = m_position;
}

Player::~Player()
{

}


void Player::Update()
{
	Move();

	Rotation();

	ManageState();

	PlayAnimation();

	m_modelRender.Update();

	



	constexpr float kDamageRange = 100.0f;
	constexpr int kDamageAmount = 2;

	Enemy* enemies[] = {
		FindGO<Enemy>("enemy1"),
		FindGO<Enemy>("enemy2"),
		FindGO<Enemy>("enemy3"),
		FindGO<Enemy>("enemy4"),
		FindGO<Enemy>("enemy5")

	};

	// 敵リストを順に処理（nullptrチェック付き）
	for (Enemy* enemy : enemies) {
		if (!enemy) continue; // 敵が存在しない場合はスキップ



		// プレイヤーとの距離を計算
		float distance = (enemy->GetPosition() - GetPosition()).Length();

		// 一定距離内かつXボタンが押されたら攻撃処理
		if (distance <= kDamageRange && g_pad[0]->IsTrigger(enButtonX)) 
		{
			enemy->TakeDamage(kDamageAmount);//敵にダメージを与える
			
		//敵のHPが０になったら
			if (enemy->GetHP() == 0 ) {
		        
				enemy->SetDead(true);//敵の死亡フラグ
				EnemyCount++;
				DeleteGO(enemy);
				

			}
		}
	}
		Boss* boss = FindGO<Boss>("boss");


		if (boss) {

			//プレイヤーとの距離計算
			float distance = (boss->GetPosition() - GetPosition()).Length();

			// 一定距離内かつXボタンが押されたら攻撃処理
			if (distance <= kDamageRange && g_pad[0]->IsTrigger(enButtonX)) {


				boss->TakeDamage(2);//ボスに固定ダメージ（２ダメージ）を与える
				if (boss->GetHP() == 0) {

					boss->SetDead(true);//ボスの死亡フラグ
					BossCount++;//撃破カウント数
				    DeleteGO(boss);
					
			    }
			}
	
		}
		
		

		

}






void Player::Move()
{
	constexpr float isDashSpeed = 360.0f;
	constexpr float isWalkSpeed = 120.0f;
	constexpr float isJumpPower = 1000.0f;
	constexpr float isGravity = 30.5f;
	constexpr float isDeltaTime = 10.5f / 60.0f;
	constexpr float isMovementThreshold = 0.001f;
	


	//座標を絵描きさんに教える。

	m_moveSpeed.x = 0.0f;
	m_moveSpeed.z = 0.0f;

	Vector3 stickL;
	stickL.x = g_pad[0]->GetLStickXF();
	stickL.y = g_pad[0]->GetLStickYF();

	Vector3 forward = g_camera3D->GetForward();
	Vector3 right = g_camera3D->GetRight();

	forward.y = 0.0f;
	right.y = 0.0f;

	isDashing = g_pad[0]->IsPress(enButtonY);

	float moveSpeedBase = isDashing ? 360.0f : 120.0f;  /// ダッシュ中は移動速度を360、通常時は120に設定（カメラ方向ベースの移動速度）

	right *= stickL.x * moveSpeedBase;
	forward *= stickL.y * moveSpeedBase;

	m_moveSpeed += right + forward;

	if (characterController.IsOnGround())
	{

		// 地面にいる場合：ジャンプ可能状態にリセット
		m_moveSpeed.y = 0.0f;
		hasDoubleJumped = false;
		canDoubleJump = true;

		// Aボタンが押されたら通常ジャンプ（ジャンプ力 : 900）
		if (canDoubleJump && !hasDoubleJumped && g_pad[0]->IsTrigger(enButtonA))
		{
			m_moveSpeed.y = 900.0f;

		}

	}

	else
	{
		// 空中にいる場合：重力を適用（加速度：-30.5）
		m_moveSpeed.y -= 30.5f;

		// ダブルジャンプ可能なら、Aボタンで空中ジャンプ（ジャンプ力：900）
		if (canDoubleJump && !hasDoubleJumped && g_pad[0]->IsTrigger(enButtonA))
		{
			m_moveSpeed.y = 900.0f;
			hasDoubleJumped = true;
			canDoubleJump = false;

		}

	}
	m_position = characterController.Execute(m_moveSpeed, 10.5f / 60.0f);

	m_modelRender.SetPosition(m_position);
}
void Player::Rotation()
{
	if (fabsf(m_moveSpeed.x) >= 0.001f || fabsf(m_moveSpeed.z) >= 0.001f)
	{
		rotation.SetRotationYFromDirectionXZ(m_moveSpeed);
		m_modelRender.SetRotation(rotation);
	}
}

void Player::ManageState()
{
	//地面に付いていなかったら。
	if (characterController.IsOnGround() == false)
	{
		//ステートを1(ジャンプ中)にする。
		m_playerState = 1;
	}
	if (characterController.IsOnGround() == false)
	{
		m_playerState = 4;

		if (!characterController.IsOnGround())
		{
			m_playerState = hasDoubleJumped ? 3 : 1;
			return;
		}

		if (fabsf(m_moveSpeed.x) >= 0.001f || fabsf(m_moveSpeed.z) >= 0.001f)
		{
			m_playerState = isDashing ? 4 : 2;
		}
		else
		{
			m_playerState = 0;
		}


	}

	//地面に付いていたら。
	//xかzの移動速度があったら(スティックの入力があったら)。
	if (fabsf(m_moveSpeed.x) >= 0.001f || fabsf(m_moveSpeed.z) >= 0.001f)
	{
		//ステートを2(歩き)にする。
		m_playerState = 2;
	}
	//xとzの移動速度が無かったら(スティックの入力が無かったら)。
	else
	{
		//ステートを0(待機)にする。
		m_playerState = 0;
	}
}

//アニメーションの再生。
void Player::PlayAnimation()
{
	//switch文。
	switch (m_playerState) {
		//プレイヤーステートが0(待機)だったら。
	case 0:
		//待機アニメーションを再生する。
		m_modelRender.PlayAnimation(enAnimationClip_Idle);
		break;
		//プレイヤーステートが1(ジャンプ中)だったら。
	case 1:
		//ジャンプアニメーションを再生する。
		m_modelRender.PlayAnimation(enAnimationClip_Jump);
		break;
		//プレイヤーステートが2(歩き)だったら。
	case 2:
		//歩きアニメーションを再生する。
		m_modelRender.PlayAnimation(enAnimationClip_Walk);
		break;
	case 3:
		// 二段ジャンプアニメーション（別途用意していれば）
		m_modelRender.PlayAnimation(enAnimationClip_Jump);
		break;
	case 4:
		m_modelRender.PlayAnimation(enAnimationClip_Run);
		break;




	}
}

Vector3 Player::GetPosition() const {
	return m_position;
}



void Player::Render(RenderContext& rc)
{
	m_modelRender.Draw(rc);
	//表示する座標を設定する。
	wchar_t bu[129];
	constexpr size_t kFontBufferSize = 129;
	m_fontRender.SetPosition({ -600.0f,100.0f,0.0f });
	//表示する色を設定する。
	m_fontRender.SetColor(g_vec4White);
	// プレイヤーの座標を取得
	Vector3 pos = m_position;
	// 座標を文字列に変換   
	swprintf(bu, 129, L"Player Pos: X=%.1f Y=%.1f Z=%.1f", pos.x, pos.y, pos.z);
	// テキストをセット
	m_fontRender.SetText(bu);
	// フォント描画
	m_fontRender.Draw(rc);
}