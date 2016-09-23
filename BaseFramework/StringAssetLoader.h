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

#ifndef _STRING_ASSET_LOADER_H_
#define _STRING_ASSET_LOADER_H_

#include "AssetLoaderBase.h"
#include <string>

M2DKITENGINE_NAMESPACE_BEGIN

class CStringAssetLoader : public CAssetLoaderBase
{
public:
    CStringAssetLoader(const std::string& filePath);
    virtual ~CStringAssetLoader();

    virtual CAssetHandleBase* Load() const;

private:
    std::string m_FilePath;
};

M2DKITENGINE_NAMESPACE_END

#endif
