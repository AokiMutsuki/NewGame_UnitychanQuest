#include "stdafx.h"
#include "Boss.h"
#include "Player.h"
#include "Game.h"
#include "Enemy.h"


Boss::Boss()
{
	m_modelRender.Init("Assets/modelData/boss.tkm");
	m_position.Set(18329.4f, 0.0f, -17381.2f);
	m_modelRender.SetPosition(m_position);
}

Boss::~Boss()
{

}


void Boss::Update()
{
	//生存フラグ
	if (m_isDead) return;

	// 毎回取得することで安全性を高める
	m_player = FindGO<Player>("player"); // ← メンバー変数に代入
	if (m_player == nullptr) {
		return; // プレイヤーが存在しないなら処理しない

	}

	Move();

	Rotation();

	SetPosition(m_position);

	m_modelRender.Update();


	//プレイヤーとの距離計算
	Vector3 PlayerPos = m_player->m_position;

	Vector3 diff = PlayerPos - m_position;

	Player* player = FindGO<Player>("player");
	if (!player) return;

	float distance = (player->GetPosition() - GetPosition()).Length();

	if (distance <= kDamageRange)
	{
		m_damageTime += GameTime().GetFrameDeltaTime(); // 毎フレーム加算

		if (m_damageTime >= kDamageInterval)
		{
			player->TakeDamage(2); // プレイヤーのHPを2減らす
			m_damageTime = 0.0f;  // タイマーリセット
		}
	}
	else
	{
		m_damageTime = 0.0f; // 範囲外ならタイマーリセット
	}
}

void Boss::Move()
{
	if (m_player == nullptr) return;



	//プレイヤーの方向へ移動
	Vector3 direction = m_position - m_player->m_position;

	if (direction.Length() < 2000.0f) {
		//方向ベクトルを正規化
		direction.Normalize();
		m_position -= direction * 20.0f;

		//プレイヤーの方向を向く
		rotation.SetRotationYFromDirectionXZ(direction);
		m_modelRender.SetRotation(rotation);

		SetPosition(m_position);
		m_modelRender.Update();

		m_moveSpeed.y = -10.5f;

	}
}

void Boss::Rotation()
{
	if (m_player == nullptr) return;



	rotation.SetRotationYFromDirectionXZ(m_player->GetPosition() - m_position);
	m_modelRender.SetRotation(rotation);
}
void Boss::SetPosition(const Vector3& pos)
{
	m_position = pos;
	m_modelRender.SetPosition(m_position);
}

void Boss::Render(RenderContext& rc)
{
	m_modelRender.Draw(rc);
}
