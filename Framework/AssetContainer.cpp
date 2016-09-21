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

#include "AssetContainer.h"

M2DKITENGINE_NAMESPACE_BEGIN

CAssetContainer::CAssetContainer()
{
}

CAssetContainer::~CAssetContainer()
{

}

bool CAssetContainer::Init()
{
    return true;
}

void CAssetContainer::Destroy()
{
    for (TAssetMap::iterator iter = m_AssetMap.begin(); iter != m_AssetMap.end(); iter++)
    {
        if (iter->second)
        {
            IwAssertMsg(2DENGINE, false, ("The resource with hash %d has not been unloaded during unload.", iter->first));
            delete iter->second;
            iter->second = NULL;
        }
    }

    m_AssetMap.clear();
}

bool CAssetContainer::ReleaseAsset(uint32 assetHash)
{
    TAssetMap::iterator iter = m_AssetMap.find(assetHash);

    if (iter != m_AssetMap.end())
    {
        iter->second->DecreaseRefCount();

        if (iter->second->GetRefCount() == 0)
        {
            delete iter->second;
            iter->second = NULL;
            m_AssetMap.erase(iter);
        }

        return true;
    }

    IwAssertMsg(2DENGINE, false, ("Unable to find asset with hash %d for unloading", assetHash));
    return false;
}

bool CAssetContainer::HasAsset(uint32 assetHash)
{
    TAssetMap::iterator iter = m_AssetMap.find(assetHash);

    return (iter != m_AssetMap.end());
}

M2DKITENGINE_NAMESPACE_END
