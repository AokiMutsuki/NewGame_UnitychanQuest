#pragma once

class Player;
class GameOver : public IGameObject
{
public:
	GameOver();
	~GameOver();
	void Update();
	void Render(RenderContext& renderContext);

	SpriteRender m_spriteRender;
	Player* m_player;
};

