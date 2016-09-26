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
#include "IwDebug.h"

using namespace Iw2DSceneGraphCore;
using namespace Iw2DSceneGraph;

// The 2D engine lives in the Iw2DEngine namespace
using namespace m2dkit;
using namespace m2dkit::core;
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

void ButtonReleasedCallback(CEventArgs* args)
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

	// Import the scene and its associated resources
	CSceneContainer* sc = g_Game->GetSceneContainer();
	const int zIndex = 0;
	if (sc->LoadSceneFromDisk("Scene.json", "Scene.resources", zIndex, &s_SceneId))
	{

		// Attach pressed and released event callbacks to button
		shared_ptr<CButton> btn = sc->GetNode<CButton>(s_SceneId, "Scene.ButtonPlay");
		IwAssertMsg(2DENGINE, btn != 0, ("%s not found", "Scene.ButtonPlay"));
		btn->SubscribeEvent(BUTTON_EVENT_RELEASED, ButtonReleasedCallback);

		// Run the game
		g_Game->Run();


		sc->DestroyScene(s_SceneId);
	}

	// Destroy the game manager
	delete g_Game;


    // Return
    return 0;
}
