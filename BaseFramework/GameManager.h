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

#ifndef _GAMEMANAGER_H_
#define _GAMEMANAGER_H_

#include <list>
#include <memory>
#include "IwGx.h"
#include "Node.h"
#include "SceneContainer.h"
#include "AssetContainer.h"
#include "GameStatesBase/StatesStack.h"

M2DKITENGINE_NAMESPACE_BEGIN

class CInputManager;

class CGameManager
{
public:
    CGameManager();
    virtual ~CGameManager();

    void                    Init();
    void                    Run();
    void                    RunOneFrame();
	void					SetCustomUpdateFunction(std::function<void(float)> customUpdateCallback);

    static CGameManager*    GetInstance();
    core::CSceneContainer*  GetSceneContainer() const;
    CInputManager*          GetInputManager() const;
    CAssetContainer&        GetAssetContainer();
	std::weak_ptr<gs::StatesStack> GetStateStack();

    void                    SetClearColour(uint8 r, uint8 g, uint8 b, uint8 a);

    // Events
    void                    SubscribeEvent(uint32 eventNameHash, core::CEventCallback callback);
    void                    UnsubscribeEvent(uint32 eventNameHash);

    static CIwTexture*      LoadTexture(const char* filePath);
    static CIwGxFont*       LoadFont(const char* filePath, uint32 size);
    static const char*      LoadString(const char* filePath);
    static void             UnloadTexture(const char* filePath);
    static void             UnloadFont(const char* filePath, uint32 size);
    static void             UnloadString(const char* filePath);

protected:
    
    void                    Update(float dt);
    void                    Draw();

    void                    UpdateTouchEvents();

    static CGameManager*    s_Instance;             ///< Static instance of game manager

    CInputManager*          m_Input;                ///< Input manager
    CAssetContainer         m_AssetContainer;       ///< Asset container
    core::CSceneContainer*  m_SceneContainer;       ///< Scene manager

    uint64                  m_PrevTime;             ///< Previous frames time
    CIwColour               m_ClearColour;          ///< Background clear colour

    CIwVec2                 m_DisplaySize;          ///< Device display size in pixels
    core::CEventMap*        m_EventsMap;            // Events map

	std::shared_ptr<gs::StatesStack> m_stateStack;

	std::function<void(float)> m_customUpdateCallback;
};

M2DKITENGINE_NAMESPACE_END

#endif
