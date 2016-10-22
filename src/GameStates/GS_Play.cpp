////////////////////////////////////////////////////////////////////////////////////////////////////
//


#include "GameStates/GS_Play.h"
#include "GameManager.h"
#include "GameStatesBase/StatesStack.h"
#include "DFPAnimedSprite/DFPAnimedSprite.h"
#include <functional>

#include "s3eKeyboard.h"


using namespace m2dkit;

////////////////////////////////////////////////////////////////////////////////////////////////////
//
GS_Play::GS_Play(std::weak_ptr<m2dkit::engine::CGameManager> gamePtr, std::string levelName)
	: m_gameWeakPtr(gamePtr)
	, m_sceneId(-1)
	, m_levelName(levelName)
	, m_loadingPtogress(0)
{

}
////////////////////////////////////////////////////////////////////////////////////////////////////
//
GS_Play::~GS_Play()
{
}
//
int GS_Play::Create()
{
	return true ;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
//
void GS_Play::Pause()
{
	
}

////////////////////////////////////////////////////////////////////////////////////////////////////
//
void GS_Play::Resume()
{
	
}

////////////////////////////////////////////////////////////////////////////////////////////////////
//
void GS_Play::Release()
{
	
}


////////////////////////////////////////////////////////////////////////////////////////////////////
void GS_Play::Update(float dt)
{
	// Check current status of the Android "back" key
	int32 rightKeyState = s3eKeyboardGetState(s3eKeyRight);
	if (rightKeyState & S3E_KEY_STATE_PRESSED)
	{
		int a = 1;
	}
	else if (rightKeyState & S3E_KEY_STATE_RELEASED)
	{
		int a = 1;
	}

	if (rightKeyState & S3E_KEY_STATE_DOWN)
	{
		int a = 1;
	}
	
}

////////////////////////////////////////////////////////////////////////////////////////////////////
//
void GS_Play::Render()
{
	
}

bool GS_Play::Load()
{
	if (auto game = m_gameWeakPtr.lock())
	{
		core::CSceneContainer* sc = game->GetSceneContainer();

		if (m_loadingPtogress == 0)
		{
			const int zIndex = 0;
			bool sceneLoadedOK = sc->LoadSceneFromDisk("Loading.json", "Loading.resources", zIndex, true, &m_sceneId);
			IwAssertMsg(2DENGINE, sceneLoadedOK, ("%s not found!", "Loading.json or Loading.resources"));
			m_loadingPtogress = 10;
			return true;
		}
		else if (m_loadingPtogress == 10)
		{

			

			int loadingSceneID = m_sceneId;

			std::string sceneJson = m_levelName + ".json";
			std::string sceneResources = m_levelName + ".resources";

			const int zIndex = 0;
			bool sceneLoadedOK = sc->LoadSceneFromDisk(sceneJson.c_str(), sceneResources.c_str(), zIndex, false, &m_sceneId);
			IwAssertMsg(2DENGINE, sceneLoadedOK, ("%s or %s not found!", sceneJson.c_str(), sceneResources.c_str()));

			sc->DestroyScene(loadingSceneID);//destroy the loading screen


			shared_ptr<core::CSprite> dfpSprite = dfp::CreateDFPNode("omulet", "assets2/n69yj7.anim", sc, m_sceneId, "Scene");

			shared_ptr<core::CSprite> ship1 = dfp::CreateDFPNode("ship1", "assets2/ship1.anim", sc, m_sceneId, "Scene");
		
			m_loadingPtogress = 100;
			return true;
		}
		else if (m_loadingPtogress == 100)
		{
			sc->SetSceneActive(m_sceneId, true);
			sc->SetSceneVisible(m_sceneId, true);
			return false;
		}

		// Attach pressed and released event callbacks to button
		//shared_ptr<core::CButton> btn1 = sc->GetNode<core::CButton>(m_sceneId, "Scene.ButtonPlay");
		//IwAssertMsg(2DENGINE, btn1 != 0, ("%s not found", "Scene.ButtonPlay"));
		//btn1->SubscribeEvent(core::BUTTON_EVENT_RELEASED, std::bind(&GS_Play::ButtonReleasedCallback1, this, std::placeholders::_1));

		return false;
	}

	return true;
}

