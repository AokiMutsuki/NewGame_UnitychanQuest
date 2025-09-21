#pragma once

class Player;
class Game;
class Enemy : public IGameObject
{
public:
	Enemy();
	~Enemy();
	void Update();
	void Move();
	void Rotation();
	void Animation();
	
	void Render(RenderContext& rc);
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
			return true;
		}

		
	}

	void SetDead(bool dead) { m_isDead = dead; }

	
		//敵のステータスの管理
		int GetHP() const { return m_hp; }
		int GetMaxHP() const { return m_maxHp; }

		int m_hp = 30;
		int m_maxHp = 30;

		float m_damageTime = 0.0f;
		constexpr static float kDamageInterval = 1.0f; // 1秒ごとにダメージ
		constexpr static float kDamageRange = 1000.0f;  // 攻撃範囲

		







	


	enum EnAnimationClip {		//アニメーション。
		enAnimationClip_Idle,
		enAnimationClip_Walk,
		enAnimationClip_Num,


	};
	AnimationClip m_animationClips[enAnimationClip_Num];		//アニメーションクリップ。

	
	






	
};

