#pragma once

class Player;
class Game;
class Boss : public IGameObject
{
public:
	Boss();
	~Boss();
	void Update();
	void Move();
	void Rotation();
	void Render(RenderContext& renderContext);
	void SetPosition(const Vector3& pos);
	Vector3 GetPosition() const {
		return m_position; // 例：自機の位置を保持するメンバ変数
	}

	Vector3 m_position;
	Quaternion rotation;
	ModelRender m_modelRender;
	Player* m_player;
	Vector3 direction;
	Vector3 initialPosition;
	Vector3 DebugPrint;
	Vector3 m_moveSpeed;
	bool m_isDead = false;
	CharacterController* m_characterController = nullptr;

	bool TakeDamage(int damage)
	{
		m_hp -= damage;
		if (m_hp <= 0 && !m_isDead)
		{
			m_isDead = true;
			DeleteGO(this);
			return true;
		}

		return false;
	}

	
	void SetDead(bool dead) { m_isDead = dead; }
	



	//ボスのステータスの管理
	int GetHP() const { return m_hp; }
	int GetMaxHP() const { return m_maxHp; }

	int m_hp = 200;
	int m_maxHp = 200;

	float m_damageTime = 0.0f;
	constexpr static float kDamageInterval = 0.8f; // 0.8秒ごとにダメージ
	constexpr static float kDamageRange = 3000.0f;  // 攻撃範囲

};

