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

#include "GameManager.h"
#include "IwGx.h"
#include "IwGxFont.h"
#include "InputManager.h"

#include "GameManagerEvents.h"
#include "FontAssetLoader.h"
#include "TextureAssetLoader.h"
#include "StringAssetLoader.h"

#include <sstream>

M2DKITCORE_USE_NAMESPACE

M2DKITENGINE_NAMESPACE_BEGIN

CGameManager* CGameManager::s_Instance = 0;

CGameManager::CGameManager()
    : m_Input(0)
    , m_AssetContainer()
    , m_SceneContainer(0)
    , m_PrevTime(0)
    , m_ClearColour()
    , m_DisplaySize(CIwVec2::g_Zero)
    , m_EventsMap(0)
{
    s_Instance = this;
    SetClearColour(0, 0, 0, 255);
}

CGameManager::~CGameManager()
{
    delete m_Input;
    delete m_EventsMap;
    delete m_SceneContainer;

    m_AssetContainer.Destroy();

    IwGxFontTerminate();
    IwGxTerminate();
}

CGameManager* CGameManager::GetInstance()
{
    return s_Instance;
}

CSceneContainer* CGameManager::GetSceneContainer() const
{
    return m_SceneContainer;
}

CInputManager* CGameManager::GetInputManager() const
{
    return m_Input;
}

CAssetContainer& CGameManager::GetAssetContainer()
{
    return m_AssetContainer;
}

void CGameManager::SetClearColour(uint8 r, uint8 g, uint8 b, uint8 a)
{
    m_ClearColour.r = r;
    m_ClearColour.g = g;
    m_ClearColour.b = b;
    m_ClearColour.a = a;
}

void CGameManager::Init()
{
    // Initialise the 2D graphics system
    IwGxInit();
    IwGxFontInit();
    m_Input = new CInputManager(this);
    m_AssetContainer.Init();

    m_SceneContainer = new CSceneContainer();
    m_EventsMap = new CEventMap();

    m_DisplaySize.x = IwGxGetScreenWidth();
    m_DisplaySize.y = IwGxGetScreenHeight();
    m_SceneContainer->RegisterTextureLoadCallback(LoadTexture);
    m_SceneContainer->RegisterFontLoadCallback(LoadFont);
    m_SceneContainer->RegisterTextureUnloadCallback(UnloadTexture);
    m_SceneContainer->RegisterFontUnloadCallback(UnloadFont);
    m_SceneContainer->RegisterStringLoadCallback(LoadString);
    m_SceneContainer->RegisterStringUnloadCallback(UnloadString);
}

void CGameManager::SubscribeEvent(uint32 eventNameHash, CEventCallback callback)
{
    m_EventsMap->Subscribe(eventNameHash, callback);
}

void CGameManager::UnsubscribeEvent(uint32 eventNameHash)
{
    m_EventsMap->Unsubscribe(eventNameHash);
}

CIwTexture* CGameManager::LoadTexture(const char* filePath)
{
    const uint32 assetHash = IwHashString(filePath);

    CAssetContainer& AssetContainer = CGameManager::GetInstance()->GetAssetContainer();
    const CTextureAssetLoader loader = CTextureAssetLoader(filePath);
    CIwTexture* texture = AssetContainer.AquireAsset<CIwTexture>(assetHash, loader);

    return texture;
}

CIwGxFont* CGameManager::LoadFont(const char* filePath, uint32 size)
{
    std::stringstream hashString;
    hashString << filePath << size;
    const uint32 assetHash = IwHashString(hashString.str().c_str());

    CAssetContainer& AssetContainer = CGameManager::GetInstance()->GetAssetContainer();
    const CFontAssetLoader loader = CFontAssetLoader(filePath, size);
    CIwGxFont* font = AssetContainer.AquireAsset<CIwGxFont>(assetHash, loader);

    return font;
}

const char* CGameManager::LoadString(const char* filePath)
{
    const uint32 assetHash = IwHashString(filePath);

    CAssetContainer& AssetContainer = CGameManager::GetInstance()->GetAssetContainer();
    const CStringAssetLoader loader = CStringAssetLoader(filePath);
    const char* string = AssetContainer.AquireAsset<std::string>(assetHash, loader)->c_str();

    return string;
}

void CGameManager::UnloadTexture(const char* filePath)
{
    const uint32 assetHash = IwHashString(filePath);

    CAssetContainer& AssetContainer = CGameManager::GetInstance()->GetAssetContainer();
    AssetContainer.ReleaseAsset(assetHash);
}

void CGameManager::UnloadFont(const char* filePath, uint32 size)
{
    std::stringstream hashString;
    hashString << filePath << size;
    const uint32 assetHash = IwHashString(hashString.str().c_str());

    CAssetContainer& AssetContainer = CGameManager::GetInstance()->GetAssetContainer();
    AssetContainer.ReleaseAsset(assetHash);
}

void CGameManager::UnloadString(const char* filePath)
{
    const uint32 assetHash = IwHashString(filePath);

    CAssetContainer& AssetContainer = CGameManager::GetInstance()->GetAssetContainer();
    AssetContainer.ReleaseAsset(assetHash);
}

void CGameManager::Update(float dt)
{
    // Check for display size changes
    if (m_DisplaySize.x != (int)IwGxGetScreenWidth() || m_DisplaySize.y != (int)IwGxGetScreenHeight())
    {
        m_DisplaySize.x = IwGxGetScreenWidth();
        m_DisplaySize.y = IwGxGetScreenHeight();
        // Inform scene container that display size changed
        m_SceneContainer->NotifyDisplaySizeChanged(m_DisplaySize);
    }

    // Update scenes
    m_SceneContainer->Update(dt);
}

void CGameManager::Draw()
{
    m_SceneContainer->DrawAllScenes();
}

void CGameManager::Run()
{
    while (!s3eDeviceCheckQuitRequest())
    {
        RunOneFrame();
    }

}

void CGameManager::RunOneFrame()
{
    if (m_PrevTime == 0)
    {
        m_PrevTime = s3eTimerGetMs();
    }

    // Calculate update speed
    uint64 new_time = s3eTimerGetMs();
    float dt = (new_time - m_PrevTime) / 1000.0f;
    
    if (dt > 0.1f)
    {
        dt = 0.1f;
    }

    // Update input
    m_Input->Update();

    // Inform user that an update is about to take place
    CGameManagerUpdateArgs args((CEventSource*)this);
    args.m_DeltaTime = dt;
    m_EventsMap->Notify(GAMEMANAGER_EVENT_UPDATE, &args);

    // Update game
    Update(dt);
	if (m_customUpdateCallback)
	{
		m_customUpdateCallback(dt);
	}

    // Draw game
    IwGxSetColClear(m_ClearColour.r, m_ClearColour.g, m_ClearColour.b, m_ClearColour.a);
    IwGxClear(IW_GX_COLOUR_BUFFER_F | IW_GX_DEPTH_BUFFER_F);
    Draw();
    IwGxFlush();
    IwGxSwapBuffers();

    // Yield to OS
    s3eDeviceYield(0);

    m_PrevTime = new_time;
}

void CGameManager::SetCustomUpdateFunction(std::function<void(float)> customUpdateCallback)
{
	m_customUpdateCallback = customUpdateCallback;
}

M2DKITENGINE_NAMESPACE_END
