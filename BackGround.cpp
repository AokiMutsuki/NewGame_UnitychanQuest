#include "stdafx.h"
#include "BackGround.h"

BackGround::BackGround()
{
	m_modelRender.Init("Assets/modelData/ground2.tkm");
	m_modelRender.Update();
	physicsStaticObject.CreateFromModel(m_modelRender.GetModel(), m_modelRender.GetModel().GetWorldMatrix());
	//“–‚½‚è”»’è‚ð‰ÂŽ‹‰»‚·‚éB

	//PhysicsWorld::GetInstance()->EnableDrawDebugWireFrame();
}

BackGround::~BackGround()
{

}

void BackGround::Update()
{

}

void BackGround::Render(RenderContext& rc)
{
	m_modelRender.Draw(rc);
}

