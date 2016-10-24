////////////////////////////////////////////////////////////////////////////////////////////////////
//


#include "GameStates/GS_Play.h"
#include "GameManager.h"
#include "GameStatesBase/StatesStack.h"
#include "DFPAnimedSprite/DFPAnimedSprite.h"
#include <functional>

#include "s3eKeyboard.h"
#include "IwDebug.h"


using namespace m2dkit;

////////////////////////////////////////////////////////////////////////////////////////////////////
//
GS_Play::GS_Play(std::weak_ptr<m2dkit::engine::CGameManager> gamePtr, std::string levelName)
	: m_gameWeakPtr(gamePtr)
	, m_sceneId(-1)
	, m_loadingSceneId(-1)
	, m_levelName(levelName)
	, m_loadingProgress(0)
	, m_playerMove(PlayerMove::IDLE)
	, m_animPlayerShipTurnLeft(0)
	, m_animPlayerShipTurnRight(0)
	, m_animPlayerShipReleaseLeft(0)
	, m_animPlayerShipReleaseRight(0)
	, m_animPlayerShipIdle(0)
	, m_posX(100)
	, m_posY(100)
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
	int32 leftKeyState = s3eKeyboardGetState(s3eKeyLeft);
	int32 rightKeyState = s3eKeyboardGetState(s3eKeyRight);
	int32 upKeyState = s3eKeyboardGetState(s3eKeyUp);
	int32 downKeyState = s3eKeyboardGetState(s3eKeyDown);


	if (rightKeyState & S3E_KEY_STATE_PRESSED)
	{
		m_animPlayerShipTurnRight->Play();
	}

	if (leftKeyState & S3E_KEY_STATE_PRESSED)
	{
		m_animPlayerShipTurnLeft->Play();
	}

	if (rightKeyState & S3E_KEY_STATE_DOWN)
	{
		m_playerMove = PlayerMove::RIGHT;
	}
	else if (leftKeyState & S3E_KEY_STATE_DOWN)
	{
		m_playerMove = PlayerMove::LEFT;
	}
	else if (upKeyState & S3E_KEY_STATE_DOWN)
	{
		m_playerMove = PlayerMove::FORWARD;
	}
	else if (downKeyState & S3E_KEY_STATE_DOWN)
	{
		m_playerMove = PlayerMove::BACKWARD;
	}
	else
	{
		m_playerMove = PlayerMove::IDLE;
	}


	if (m_playerMove == PlayerMove::IDLE)
	{
		//m_animPlayerShipIdle->Play();
	}
	else if (m_playerMove == PlayerMove::RIGHT)
	{
		
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

		if (m_loadingProgress == 0)
		{
			const int zIndex = 0;
			bool sceneLoadedOK = sc->LoadSceneFromDisk("Loading.json", "Loading.resources", zIndex, true, &m_loadingSceneId);
			IwAssertMsg(2DENGINE, sceneLoadedOK, ("%s not found!", "Loading.json or Loading.resources"));
			m_loadingProgress = 10;
			return true;
		}
		else if (m_loadingProgress == 10)
		{
			std::string sceneJson = m_levelName + ".json";
			std::string sceneResources = m_levelName + ".resources";

			const int zIndex = 0;
			bool sceneLoadedOK = sc->LoadSceneFromDisk(sceneJson.c_str(), sceneResources.c_str(), zIndex, false, &m_sceneId);
			IwAssertMsg(2DENGINE, sceneLoadedOK, ("%s or %s not found!", sceneJson.c_str(), sceneResources.c_str()));
			
			m_loadingProgress = 70;
			return true;
		}
		else if (m_loadingProgress == 70)
		{
			//shared_ptr<core::CSprite> dfpSprite = dfp::CreateDFPNode("omulet", "assets2/n69yj7.anim", sc, m_sceneId, "Scene");

			m2dkit::shared_ptr<core::CSprite> playerShip = dfp::CreateDFPNode("PlayerShip", "assets2/ship1.anim", sc, m_sceneId, "Scene");

			m_animPlayerShipIdle = playerShip->GetAnimationContainer().SetCurrentAnimation("assets2/ship1.anim/normal");

			m_animPlayerShipTurnRight = playerShip->GetAnimationContainer().SetCurrentAnimation("assets2/ship1.anim/TurnRight");
			m_animPlayerShipTurnRight->SetPlaybackDirection(core::Animation::ePlaybackDirection::PlaybackDirectionForward);
			m_animPlayerShipTurnRight->SetRepeatCount(1);
			m_animPlayerShipReleaseRight = playerShip->GetAnimationContainer().SetCurrentAnimation("assets2/ship1.anim/TurnRight");
			m_animPlayerShipTurnRight->SetPlaybackDirection(core::Animation::ePlaybackDirection::PlaybackDirectionReverse);
			m_animPlayerShipTurnRight->SetRepeatCount(1);
			

			m_animPlayerShipTurnLeft = playerShip->GetAnimationContainer().SetCurrentAnimation("assets2/ship1.anim/TurnLeft");
			m_animPlayerShipTurnLeft->SetPlaybackDirection(core::Animation::ePlaybackDirection::PlaybackDirectionForward);
			m_animPlayerShipTurnLeft->SetRepeatCount(1);
			m_animPlayerShipReleaseLeft = playerShip->GetAnimationContainer().SetCurrentAnimation("assets2/ship1.anim/TurnLeft");
			m_animPlayerShipReleaseLeft->SetPlaybackDirection(core::Animation::ePlaybackDirection::PlaybackDirectionReverse);
			m_animPlayerShipReleaseLeft->SetRepeatCount(1);
			

			m_loadingProgress = 100;
			return true;
		}
		else if (m_loadingProgress == 100)
		{
			sc->SetSceneActive(m_sceneId, true);
			sc->SetSceneVisible(m_sceneId, true);

			sc->DestroyScene(m_loadingSceneId);//destroy the loading screen

			return false;
		}
	}

	return true;
}

