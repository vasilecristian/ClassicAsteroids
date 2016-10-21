////////////////////////////////////////////////////////////////////////////////////////////////////
//


#include "GameStates/GS_MenuMain.h"
#include "GameManager.h"
#include "GameStatesBase/StatesStack.h"
#include "DFPAnimedSprite/DFPAnimedSprite.h"
#include <functional>




using namespace m2dkit;

////////////////////////////////////////////////////////////////////////////////////////////////////
//
GS_MenuMain::GS_MenuMain(std::weak_ptr<m2dkit::engine::CGameManager> gamePtr)
	: m_gameWeakPtr(gamePtr), m_sceneId(-1)
{

}
////////////////////////////////////////////////////////////////////////////////////////////////////
//
GS_MenuMain::~GS_MenuMain()
{
}
//
int GS_MenuMain::Create()
{
	if (auto game = m_gameWeakPtr.lock())
	{
		core::CSceneContainer* sc = game->GetSceneContainer();
		const int zIndex = 0;
		sc->LoadSceneFromDisk("Loading.json", "Loading.resources", zIndex, true, &m_sceneId);
	}

	return true ;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
//
void GS_MenuMain::Pause()
{
	
}

////////////////////////////////////////////////////////////////////////////////////////////////////
//
void GS_MenuMain::Resume()
{
	
}

////////////////////////////////////////////////////////////////////////////////////////////////////
//
void GS_MenuMain::Release()
{
	
}


////////////////////////////////////////////////////////////////////////////////////////////////////
void GS_MenuMain::Update(float dt)
{
	
}

////////////////////////////////////////////////////////////////////////////////////////////////////
//
void GS_MenuMain::Render()
{
	
}

bool GS_MenuMain::Load()
{
	if (auto game = m_gameWeakPtr.lock())
	{

		core::CSceneContainer* sc = game->GetSceneContainer();

		int loadingSceneID = m_sceneId;
		

		const int zIndex = 0;
		sc->LoadSceneFromDisk("Scene.json", "Scene.resources", zIndex, true, &m_sceneId);


		sc->DestroyScene(loadingSceneID);//destroy the loading screen


		shared_ptr<core::CSprite> dfpSprite = dfp::CreateDFPNode("omulet", "assets2/n69yj7.anim", sc, m_sceneId, "Scene");

		shared_ptr<core::CSprite> ship1 = dfp::CreateDFPNode("ship1", "assets2/ship1.anim", sc, m_sceneId, "Scene");


		// Attach pressed and released event callbacks to button
		shared_ptr<core::CButton> btn1 = sc->GetNode<core::CButton>(m_sceneId, "Scene.ButtonPlay");
		IwAssertMsg(2DENGINE, btn1 != 0, ("%s not found", "Scene.ButtonPlay"));
		btn1->SubscribeEvent(core::BUTTON_EVENT_RELEASED, std::bind(&GS_MenuMain::ButtonReleasedCallback1, this, std::placeholders::_1));

		return false;
	}

	return true;
}

void GS_MenuMain::ButtonReleasedCallback1(m2dkit::core::CEventArgs* args)
{
	if (auto game = m_gameWeakPtr.lock())
	{
		core::CSceneContainer* sc = game->GetSceneContainer();

		shared_ptr<core::CSprite> dfpSprite = sc->GetNode<core::CSprite>(m_sceneId, "Scene.omulet");
		IwAssertMsg(2DENGINE, dfpSprite != 0, ("%s not found", "Scene.omulet"));


		if (dfpSprite)
		{
			dfpSprite->SetScale(CIwFVec2(4, 4));
			core::CAnimationInstance* anim = dfpSprite->GetAnimationContainer().SetCurrentAnimation("assets2/n69yj7.anim/WalkN");
			if (anim)
			{
				anim->Play();
			}
		}

		shared_ptr<core::CSprite> ship1 = sc->GetNode<core::CSprite>(m_sceneId, "Scene.ship1");
		IwAssertMsg(2DENGINE, ship1 != 0, ("%s not found", "Scene.ship1"));

		if (ship1)
		{
			ship1->SetScale(CIwFVec2(4, 4));
			ship1->SetPosition(CIwFVec2(300, 300));
			core::CAnimationInstance* anim = ship1->GetAnimationContainer().SetCurrentAnimation("assets2/ship1.anim/TurnLeft");
			if (anim)
			{
				anim->SetPlaybackDirection(core::Animation::ePlaybackDirection::PlaybackDirectionForward);
				anim->SetRepeatCount(1);
				anim->Play();
			}
		}
	}
}