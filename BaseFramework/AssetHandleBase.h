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

#ifndef _ASSET_HANDLE_BASE_H_
#define _ASSET_HANDLE_BASE_H_

#include "EngineDefines.h"

M2DKITENGINE_NAMESPACE_BEGIN

class CAssetHandleBase
{
public:
    CAssetHandleBase() 
        : m_Refcount(0)
    {}
    virtual ~CAssetHandleBase() {};

    const int GetRefCount() const { return m_Refcount; };

    void IncreaseRefCount() { m_Refcount++; };
    void DecreaseRefCount() { m_Refcount--; };

private:
    int m_Refcount;
};

M2DKITENGINE_NAMESPACE_END

#endif