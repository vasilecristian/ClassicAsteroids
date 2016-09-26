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

#if !defined(__INPUT_MANAGER_H__)
#define __INPUT_MANAGER_H__

#include "EngineDefines.h"
#include "s3ePointer.h"
#include "s3eKeyboard.h"
#include "InputTouch.h"

M2DKITENGINE_NAMESPACE_BEGIN

class CGameManager;

/**
 * @class CInputManager
 *
 * @brief CInputManager - The Input class is responsible for handling all pointer input.
 *
 */
class CInputManager
{
protected:
    CGameManager*   m_Parent;
    CInputManager() {}

public:
    CInputManager(CGameManager* parent);

    CGameManager*   GetGameManager() const;

    void            Update();

    // Callbacks
    static void     TouchButtonCB(s3ePointerEvent* event, void* userData);
    static void     TouchMotionCB(s3ePointerMotionEvent* event, void* userData);
    static void     MultiTouchButtonCB(s3ePointerTouchEvent* event, void* userData);
    static void     MultiTouchMotionCB(s3ePointerTouchMotionEvent* event, void* userData);
};

M2DKITENGINE_NAMESPACE_END

#endif  // __INPUT_MANAGER_H__
