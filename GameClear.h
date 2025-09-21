#pragma once
class GameClear : public IGameObject
{
public:
	GameClear();
	~GameClear();
	void Update();
	void Render(RenderContext& renderContext);

	SpriteRender m_spriteRender;
};

