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
GS_Play::GS_Play(std::weak_ptr<engine::CGameManager> gamePtr, std::string levelName)
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
	auto game = m_gameWeakPtr.lock();
	if (!game)
	{
		return;
	}

	core::CSceneContainer* sc = game->GetSceneContainer();


	int32 leftKeyState = s3eKeyboardGetState(s3eKeyLeft);
	int32 rightKeyState = s3eKeyboardGetState(s3eKeyRight);
	int32 upKeyState = s3eKeyboardGetState(s3eKeyUp);
	int32 downKeyState = s3eKeyboardGetState(s3eKeyDown);

	shared_ptr<core::CSprite> playerShip = sc->GetNode<core::CSprite>(m_sceneId, "Scene.PlayerShip");
	IwAssertMsg(2DENGINE, playerShip != 0, ("%s not found", "Scene.PlayerShip"));

	if (rightKeyState & S3E_KEY_STATE_PRESSED)
	{
		m2dkit::core::CAnimationInstance* currentAnim = playerShip->GetAnimationContainer().SetCurrentAnimation("assets2/ship1.anim/TurnRight");
		currentAnim->SetEventCallback(std::bind(&GS_Play::AnimationCallback, this, std::placeholders::_1, std::placeholders::_2));
		currentAnim->SetPlaybackDirection(core::Animation::ePlaybackDirection::PlaybackDirectionForward);
		currentAnim->SetRepeatCount(1);
		currentAnim->Play(NULL);
	}
	else if (leftKeyState & S3E_KEY_STATE_PRESSED)
	{
		m2dkit::core::CAnimationInstance* currentAnim = playerShip->GetAnimationContainer().SetCurrentAnimation("assets2/ship1.anim/TurnLeft");
		currentAnim->SetEventCallback(std::bind(&GS_Play::AnimationCallback, this, std::placeholders::_1, std::placeholders::_2));
		currentAnim->SetPlaybackDirection(core::Animation::ePlaybackDirection::PlaybackDirectionForward);
		currentAnim->SetRepeatCount(1);
		currentAnim->Play(NULL);
	}
	else if (rightKeyState & S3E_KEY_STATE_RELEASED)
	{
		m2dkit::core::CAnimationInstance* currentAnim = playerShip->GetAnimationContainer().SetCurrentAnimation("assets2/ship1.anim/TurnRight");
		currentAnim->SetEventCallback(std::bind(&GS_Play::AnimationCallback, this, std::placeholders::_1, std::placeholders::_2));
		currentAnim->SetPlaybackDirection(core::Animation::ePlaybackDirection::PlaybackDirectionReverse);
		currentAnim->SetRepeatCount(1);
		currentAnim->Play(NULL);
	}
	else if (leftKeyState & S3E_KEY_STATE_RELEASED)
	{
		m2dkit::core::CAnimationInstance* currentAnim = playerShip->GetAnimationContainer().SetCurrentAnimation("assets2/ship1.anim/TurnLeft");
		currentAnim->SetEventCallback(std::bind(&GS_Play::AnimationCallback, this, std::placeholders::_1, std::placeholders::_2));
		currentAnim->SetPlaybackDirection(core::Animation::ePlaybackDirection::PlaybackDirectionReverse);
		currentAnim->SetRepeatCount(1);
		currentAnim->Play(NULL);
	}
	else if (!(rightKeyState & S3E_KEY_STATE_DOWN) && !(leftKeyState & S3E_KEY_STATE_DOWN))
	{
		//m2dkit::core::CAnimationInstance* currentAnim = playerShip->GetAnimationContainer().SetCurrentAnimation("assets2/ship1.anim/normal");
		//currentAnim->SetPlaybackDirection(core::Animation::ePlaybackDirection::PlaybackDirectionForward);
		//currentAnim->SetRepeatCount(1);
		//currentAnim->Play(NULL);
	}

	if (rightKeyState & S3E_KEY_STATE_DOWN)
	{
		m_playerMove = PlayerMove::RIGHT;
		m_posX += 10;
	}
	else if (leftKeyState & S3E_KEY_STATE_DOWN)
	{
		m_playerMove = PlayerMove::LEFT;
		m_posX -= 10;
	}
	else if (upKeyState & S3E_KEY_STATE_DOWN)
	{
		m_playerMove = PlayerMove::FORWARD;
		m_posY += 5;
	}
	else if (downKeyState & S3E_KEY_STATE_DOWN)
	{
		m_playerMove = PlayerMove::BACKWARD;
		m_posY -= 5;
	}
	else
	{
		m_playerMove = PlayerMove::IDLE;
	}


	playerShip->SetPosition(CIwFVec2(m_posX, m_posY));
}

void GS_Play::AnimationCallback(core::Animation::ePlaybackEvent event, core::CAnimationInstance* source)
{
	int a = 0;
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
			m2dkit::shared_ptr<core::CSprite> playerShip = dfp::CreateDFPNode("PlayerShip", "assets2/ship1.anim", sc, m_sceneId, "Scene");
			playerShip->SetScale(CIwFVec2(2, 2));
			playerShip->SetPosition(CIwFVec2(m_posX, m_posY));
			m2dkit::core::CAnimationInstance* currentAnim = playerShip->GetAnimationContainer().SetCurrentAnimation("assets2/ship1.anim/normal");
			currentAnim->SetEventCallback(std::bind(&GS_Play::AnimationCallback, this, std::placeholders::_1, std::placeholders::_2));
			currentAnim->SetPlaybackDirection(core::Animation::ePlaybackDirection::PlaybackDirectionForward);
			currentAnim->SetRepeatCount(1);
			currentAnim->Play(NULL);
			

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

