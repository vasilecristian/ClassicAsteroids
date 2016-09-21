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

#ifndef _ASSET_HANDLE_H_
#define _ASSET_HANDLE_H_

#include "AssetHandleBase.h"

M2DKITENGINE_NAMESPACE_BEGIN

template<typename T>
class CAssetHandle : public CAssetHandleBase
{
public:
    CAssetHandle(T* asset)
        : m_Asset(asset)
    {
    }

    virtual ~CAssetHandle() 
    {
        if (m_Asset)
        {
            delete m_Asset;
            m_Asset = NULL;
        }
    };

    T* GetAsset() 
    {
        return m_Asset; 
    };

private:
    T* m_Asset;
};

M2DKITENGINE_NAMESPACE_END

#endif
