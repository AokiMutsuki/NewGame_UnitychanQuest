#pragma once
#include "sound/SoundSource.h"

class Player;
class RecoveryItem : public IGameObject
{
public:
	RecoveryItem();
	~RecoveryItem();
	void Update();
	void Move();
	void Rotation();
	void Render(RenderContext& renderContext);
	void SetPosition(const Vector3& pos);
	
	bool m_isDead = false; // RecoveryItem ‚Ìƒƒ“ƒo•Ï”‚Æ‚µ‚Ä’Ç‰Á



	int recoveryItemCount;
	Vector3 m_position;
	Player* m_player;
	ModelRender m_modelRender;
	Quaternion rotation;
	SoundSource* se;
};

