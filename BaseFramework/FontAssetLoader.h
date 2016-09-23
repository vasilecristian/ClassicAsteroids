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

#ifndef _FONT_ASSET_LOADER_H_
#define _FONT_ASSET_LOADER_H_

#include "AssetLoaderBase.h"
#include <string>

M2DKITENGINE_NAMESPACE_BEGIN

class  CFontAssetLoader : public CAssetLoaderBase
{
public:
    CFontAssetLoader(const std::string& filePath, uint32 fontSize);
    virtual ~CFontAssetLoader();

    virtual CAssetHandleBase* Load() const;

private:
    std::string m_FilePath;
    uint32      m_FontSize;
};

M2DKITENGINE_NAMESPACE_END

#endif