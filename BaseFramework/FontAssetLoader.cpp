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

#include "FontAssetLoader.h"
#include "AssetHandle.h"

#include "IwGxFont.h"

M2DKITENGINE_NAMESPACE_BEGIN

CFontAssetLoader::CFontAssetLoader(const std::string& filePath, uint32 fontSize)
    : m_FilePath(filePath)
    , m_FontSize(fontSize)
{

}

CFontAssetLoader::~CFontAssetLoader()
{

}

CAssetHandleBase* CFontAssetLoader::Load() const
{
    const uint32 dpi = 72;
    CIwGxFont* font = IwGxFontCreateTTFont(m_FilePath.c_str(), static_cast<float>(m_FontSize), dpi);

    return new CAssetHandle<CIwGxFont>(font);
}

M2DKITENGINE_NAMESPACE_END
