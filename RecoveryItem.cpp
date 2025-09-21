#include "stdafx.h"
#include "RecoveryItem.h"
#include "Player.h"
#include "sound/SoundSource.h"
#include "sound/SoundEngine.h"

RecoveryItem::RecoveryItem()
{
	m_modelRender.Init("Assets/modelData/recoveryitem.tkm");
	
	m_player = FindGO<Player>("player");

	g_soundEngine->ResistWaveFileBank(0, "Assets/sound/AS_1084571_itemGet.wav");
}

RecoveryItem::~RecoveryItem()
{

}

void RecoveryItem::Update()
{

	if (m_isDead) {
		return; // 生存フラグ
	}


	Move();

	Rotation();

	m_modelRender.Update();

	SetPosition(m_position);

	Move();

	Rotation();

	m_modelRender.Update();

	// 毎回取得することで安全性を高める
	auto player = FindGO<Player>("player");
	if (player == nullptr) {
		return; // プレイヤーが存在しないなら処理しない
	}


	Vector3 PlayerPos = player->m_position;

	Vector3 diff = PlayerPos - m_position;

	if (diff.Length() <= 120.0f)
	{

		SoundSource* se = NewGO<SoundSource>(0);

		se->Init(0);

		se->Play(false);

		se->SetVolume(3.5f);

		player->recoveryItemCount += 1;

		// プレイヤーの体力を2回復（最大値を超えないように制限）
		player->m_hp += 3;
		if (player->m_hp > player->m_maxHp) {
			player->m_hp = player->m_maxHp;
		}

		m_isDead = true; // 削除フラグを立てる
		DeleteGO(this);// 次のフレームで安全に削除される
	}


	}





void RecoveryItem::Move()
{
	m_modelRender.SetPosition(m_position);
}

void RecoveryItem::Rotation()
{
	rotation.AddRotationDegY(2.0f);

	m_modelRender.SetRotation(rotation);
}

void RecoveryItem::SetPosition(const Vector3& pos)
{
	m_position = pos;
	m_modelRender.SetPosition(m_position);
}
void RecoveryItem::Render(RenderContext& rc)
{
	m_modelRender.Draw(rc);
}