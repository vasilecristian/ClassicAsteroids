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

#include "InputManager.h"
#include "GameManager.h"
#include "InputHandler.h"

M2DKITCORE_USE_NAMESPACE

M2DKITENGINE_NAMESPACE_BEGIN

void CInputManager::TouchButtonCB(s3ePointerEvent* event, void* userData)
{
    CInputManager* input = (CInputManager*)userData;
    CInputHandler& inputHandler = input->m_Parent->GetSceneContainer()->GetInputHandler();

    inputHandler.ProcessTouchInput(event, 0);
}

void CInputManager::TouchMotionCB(s3ePointerMotionEvent* event, void* userData)
{
    CInputManager* input = (CInputManager*)userData;
    CInputHandler& inputHandler = input->m_Parent->GetSceneContainer()->GetInputHandler();

    inputHandler.ProcessMotionInput(event, 0);
}

void CInputManager::MultiTouchButtonCB(s3ePointerTouchEvent* event, void* userData)
{
    CInputManager* input = (CInputManager*)userData;
    CInputHandler& inputHandler = input->m_Parent->GetSceneContainer()->GetInputHandler();
    
    inputHandler.ProcessMultiTouchInput(event, 0);
}

void CInputManager::MultiTouchMotionCB(s3ePointerTouchMotionEvent* event, void* userData)
{
    CInputManager* input = (CInputManager*)userData;
    CInputHandler& inputHandler = input->m_Parent->GetSceneContainer()->GetInputHandler();

    inputHandler.ProcessMultiTouchMotion(event, 0);
}

CInputManager::CInputManager(CGameManager* parent)
{
    m_Parent = parent;

    // Set touch event callback handlers, single and multi-touch devices have different callbacks assigned
    if (s3ePointerGetInt(S3E_POINTER_MULTI_TOUCH_AVAILABLE) != 0)
    {
        s3ePointerRegister(S3E_POINTER_TOUCH_EVENT, (s3eCallback)MultiTouchButtonCB, this);
        s3ePointerRegister(S3E_POINTER_TOUCH_MOTION_EVENT, (s3eCallback)MultiTouchMotionCB, this);
    }
    else
    {
        s3ePointerRegister(S3E_POINTER_BUTTON_EVENT, (s3eCallback)TouchButtonCB, this);
        s3ePointerRegister(S3E_POINTER_MOTION_EVENT, (s3eCallback)TouchMotionCB, this);
    }
}

void CInputManager::Update()
{
    s3ePointerUpdate();
}

CGameManager* CInputManager::GetGameManager() const
{
    return m_Parent;
}

M2DKITENGINE_NAMESPACE_END
