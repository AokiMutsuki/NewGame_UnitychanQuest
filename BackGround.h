#pragma once
class BackGround : public IGameObject
{
public:
	BackGround();
	~BackGround();
	void Update();
	void Render(RenderContext& rc);

private:

	ModelRender m_modelRender;
	PhysicsStaticObject physicsStaticObject;
	Vector3 m_position;
};

