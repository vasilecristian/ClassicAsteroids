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

#ifndef _ASSET_CONTAINER_H_
#define _ASSET_CONTAINER_H_

#include <map>
#include "IwDebug.h"

#include "AssetHandleBase.h"
#include "AssetHandle.h"

#include "AssetLoaderBase.h"

M2DKITENGINE_NAMESPACE_BEGIN

class GameManager;
class FontCache;

class CAssetContainer
{
public:
    CAssetContainer();
    ~CAssetContainer();

    bool Init();
    void Destroy();

    template<typename T>
    T* AquireAsset(uint32 assetHash, const CAssetLoaderBase& assetLoader);
    bool ReleaseAsset(uint32 assetHash);

    bool HasAsset(uint32 assetHash);

private:
    typedef std::map<uint32, CAssetHandleBase*> TAssetMap;

    TAssetMap m_AssetMap;
};

template<typename T>
T* CAssetContainer::AquireAsset(uint32 assetHash, const CAssetLoaderBase& assetLoader)
{
    TAssetMap::iterator iter = m_AssetMap.find(assetHash);

    if (iter != m_AssetMap.end())
    {
        CAssetHandle<T>* handle = dynamic_cast<CAssetHandle<T>*>(iter->second);

        if (handle)
        {
            handle->IncreaseRefCount();
            return handle->GetAsset();
        }
        else
        {
            IwAssertMsg(2DENGINE, false, ("The requesed resource type does not match the type of the loaded asset with hash %d", assetHash));
            return NULL;
        }
    }
    else
    {
        CAssetHandleBase* handle = assetLoader.Load();
        if (handle)
        {
            CAssetHandle<T>* typedHandle = dynamic_cast<CAssetHandle<T>*>(handle);

            if (typedHandle)
            {
                m_AssetMap.insert(std::make_pair(assetHash, typedHandle));
                typedHandle->IncreaseRefCount();
                return typedHandle->GetAsset();
            }
            else
            {
                IwAssertMsg(2DENGINE, false, ("Unable to load resource with the requested type and hash %d", assetHash));
                delete handle;
                return NULL;
            }
        }
        else
        {
            IwAssertMsg(2DENGINE, false, ("Unable to load resource with the hash %d", assetHash));
            return NULL;
        }
    }
}

M2DKITENGINE_NAMESPACE_END

#endif
