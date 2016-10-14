/*
 * (C) 2001-2012 Marmalade. All Rights Reserved.
 *
 * This document is protected by copyright, and contains information
 * proprietary to Marmalade.
 *
 * This file consists of source code released by Marmalade under
 * the terms of the accompanying End User License Agreement (EULA).
 * Please do not use this program/source code before you have read the
 * EULA and have agreed to be bound by its terms.
 */

#include "s3e.h"
#include "IwDebug.h"
#include "Iw2DSceneGraph.h"
#include "IwGx.h"
#include "s3eFacebook.h"

#include "GameManager.h"
#include "SceneImporter.h"
#include "Button.h"
#include "Label.h"
#include "Sprite.h"


#include "DFPAnimedSprite/DFPAnimedSprite.h"

using namespace Iw2DSceneGraphCore;
//using namespace Iw2DSceneGraph;

// The 2D engine lives in the Iw2DEngine namespace
using namespace m2dkit;
using namespace m2dkit::engine;

// The main game manager
static CGameManager* g_Game;

// The scenes unique Id
static int s_SceneId = -1;

// Scene root node
//CNode* g_SceneRoot = NULL;

// Replace these with your own strings from your Facebook application
// These hex numbers are displayed on the application's main page
// Also update "iphone-bundle-url-schemes" in the deployment section of s3eFacebook.mkb
const char* FACEBOOK_APP_ID = NULL;
const char* FACEBOOK_APP_SECRET = NULL;

void ButtonReleasedCallback1(core::CEventArgs* args)
{
	core::CSceneContainer* sc = g_Game->GetSceneContainer();

	shared_ptr<core::CSprite> dfpSprite = sc->GetNode<core::CSprite>(s_SceneId, "Scene.omulet");
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

	shared_ptr<core::CSprite> ship1 = sc->GetNode<core::CSprite>(s_SceneId, "Scene.ship1");
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

void ButtonReleasedCallback2(core::CEventArgs* args)
{
	core::CSceneContainer* sc = g_Game->GetSceneContainer();

	shared_ptr<core::CSprite> dfpSprite = sc->GetNode<core::CSprite>(s_SceneId, "Scene.omulet");
	IwAssertMsg(2DENGINE, dfpSprite != 0, ("%s not found", "Scene.omulet"));


	if (dfpSprite)
	{
		dfpSprite->SetScale(CIwFVec2(3, 3));
		core::CAnimationInstance* anim = dfpSprite->GetAnimationContainer().SetCurrentAnimation("assets2/n69yj7.anim/WalkS");
		if (anim)
		{
			anim->Play(NULL);
		}
	}


	shared_ptr<core::CSprite> ship1 = sc->GetNode<core::CSprite>(s_SceneId, "Scene.ship1");
	IwAssertMsg(2DENGINE, ship1 != 0, ("%s not found", "Scene.ship1"));

	if (ship1)
	{
		ship1->SetScale(CIwFVec2(4, 4));
		ship1->SetPosition(CIwFVec2(300, 300));
		core::CAnimationInstance* anim = ship1->GetAnimationContainer().SetCurrentAnimation("assets2/ship1.anim/TurnLeft");
		if (anim)
		{
			anim->SetPlaybackDirection(core::Animation::ePlaybackDirection::PlaybackDirectionReverse);
			anim->SetRepeatCount(1);
			anim->Play();
		}
	}

}

void Update(float dt)
{
	int a = 1;
}


// Main entry point for the application
int main()
{
    //Initialise graphics system(s)
    //Iw2DInit();

    // Create root node
    //g_SceneRoot = new CNode();

    // Add 2D scene graph nodes to the root node here


    if (!s3eFacebookAvailable())
    {
        IwTrace(S3EFACEBOOK, ("Facebook extension not found"));
    }
    else if (!FACEBOOK_APP_ID || !FACEBOOK_APP_SECRET)
    {
        IwTrace(S3EFACEBOOK, ("Please supply a valid Facebook App ID for FACEBOOK_APP_ID and App secret for FACEBOOK_APP_SECRET in s3eFacebook.cpp!"));
    }

	// Create and initialise the game manager
	g_Game = new CGameManager();
	g_Game->Init();
	g_Game->SetCustomUpdateFunction(Update);

	// Import the scene and its associated resources
	core::CSceneContainer* sc = g_Game->GetSceneContainer();
	const int zIndex = 0;
	if (sc->LoadSceneFromDisk("Scene.json", "Scene.resources", zIndex, &s_SceneId))
	{

		// Attach pressed and released event callbacks to button
		shared_ptr<core::CButton> btn1 = sc->GetNode<core::CButton>(s_SceneId, "Scene.ButtonPlay");
		IwAssertMsg(2DENGINE, btn1 != 0, ("%s not found", "Scene.ButtonPlay"));
		btn1->SubscribeEvent(core::BUTTON_EVENT_RELEASED, ButtonReleasedCallback1);

		// Attach pressed and released event callbacks to button
		shared_ptr<core::CButton> btn2 = sc->GetNode<core::CButton>(s_SceneId, "Scene.ButtonOptions");
		IwAssertMsg(2DENGINE, btn2 != 0, ("%s not found", "Scene.ButtonOptions"));
		btn2->SubscribeEvent(core::BUTTON_EVENT_RELEASED, ButtonReleasedCallback2);

		//shared_ptr<core::CSprite> sprite = sc->GetNode<core::CSprite>(s_SceneId, "Scene.Sprite_Asteroid");
		//IwAssertMsg(2DENGINE, sprite != 0, ("%s not found", "Scene.Sprite_Asteroid"));

		//shared_ptr<core::CSprite> shipSprite = sc->GetNode<core::CSprite>(s_SceneId, "Scene.Ship");
		//IwAssertMsg(2DENGINE, shipSprite != 0, ("%s not found", "Scene.Ship"));
		
		
		shared_ptr<core::CSprite> dfpSprite = dfp::CreateDFPNode("omulet", "assets2/n69yj7.anim", sc, s_SceneId, "Scene");

		shared_ptr<core::CSprite> ship1 = dfp::CreateDFPNode("ship1", "assets2/ship1.anim", sc, s_SceneId, "Scene");


		// Run the game
		//g_Game->Run();
		while (!s3eDeviceCheckQuitRequest())
		{
			g_Game->RunOneFrame();
		}


		sc->DestroyScene(s_SceneId);
	}

	// Destroy the game manager
	delete g_Game;


    // Return
    return 0;
}
