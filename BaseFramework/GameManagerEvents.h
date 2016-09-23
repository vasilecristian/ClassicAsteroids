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

#ifndef _GAMEMANAGEREVENTS_H_
#define _GAMEMANAGEREVENTS_H_

#include "IwHashString.h"
#include "EventCallback.h"

M2DKITENGINE_NAMESPACE_BEGIN

struct CGameManagerUpdateArgs : public core::CEventArgs
{
    CGameManagerUpdateArgs(core::CEventSource* source) : core::CEventArgs(source) {}
    float   m_DeltaTime;
};

const uint32 GAMEMANAGER_EVENT_UPDATE = IwHashString("update");

M2DKITENGINE_NAMESPACE_END

#endif

