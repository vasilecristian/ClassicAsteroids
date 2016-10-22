////////////////////////////////////////////////////////////////////////////////////////////////////
//


#include "GameStates/GS_MenuMain.h"
#include "GameStates/GS_Play.h"
#include "GameManager.h"
#include "GameStatesBase/StatesStack.h"
#include "DFPAnimedSprite/DFPAnimedSprite.h"
#include <functional>

#include "s3eKeyboard.h"


using namespace m2dkit;

////////////////////////////////////////////////////////////////////////////////////////////////////
//
GS_MenuMain::GS_MenuMain(std::weak_ptr<m2dkit::engine::CGameManager> gamePtr)
	: m_gameWeakPtr(gamePtr)
	, m_sceneId(-1)
	, m_menuAction(MenuAction::IDLE)
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
		bool sceneLoadedOK = sc->LoadSceneFromDisk("Loading.json", "Loading.resources", zIndex, true, &m_sceneId);
		IwAssertMsg(2DENGINE, sceneLoadedOK, ("%s not found!", "Loading.json or Loading.resources"));
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
	if (auto game = m_gameWeakPtr.lock())
	{
		core::CSceneContainer* sc = game->GetSceneContainer();
		sc->DestroyScene(m_sceneId);
	}
}


////////////////////////////////////////////////////////////////////////////////////////////////////
void GS_MenuMain::Update(float dt)
{
	if (m_menuAction == MenuAction::PLAY)
	{
		if (auto game = m_gameWeakPtr.lock())
		{
			auto ss = game->GetStateStack();
			auto play = std::shared_ptr<gs::GameState>(new GS_Play(game, "Level1"));
			ss->ChangeState(play);
			play = nullptr;
			m_menuAction = MenuAction::IDLE;
		}
	}
	
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
		bool sceneLoadedOK = sc->LoadSceneFromDisk("Scene.json", "Scene.resources", zIndex, true, &m_sceneId);
		IwAssertMsg(2DENGINE, sceneLoadedOK, ("%s not found!", "Scene.json or Scene.resources"));

		sc->DestroyScene(loadingSceneID);//destroy the loading screen

		// Attach pressed and released event callbacks to button
		shared_ptr<core::CButton> btn1 = sc->GetNode<core::CButton>(m_sceneId, "Scene.ButtonPlay");
		IwAssertMsg(2DENGINE, btn1 != 0, ("%s not found", "Scene.ButtonPlay"));
		btn1->SubscribeEvent(core::BUTTON_EVENT_RELEASED, std::bind(&GS_MenuMain::PlayButtonReleasedCallback, this, std::placeholders::_1));

		return false;
	}

	return true;
}

void GS_MenuMain::PlayButtonReleasedCallback(m2dkit::core::CEventArgs* args)
{
	m_menuAction = MenuAction::PLAY;
}