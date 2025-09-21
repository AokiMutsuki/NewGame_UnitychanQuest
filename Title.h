#pragma once
#include "sound/SoundSource.h"

class Title : public IGameObject
{
public:
	Title();
	~Title();
	void Update();
	void Render(RenderContext& renderContext);

	SpriteRender spriteRender;
	SoundSource* bgm;

};

