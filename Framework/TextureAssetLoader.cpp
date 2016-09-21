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

#include "TextureAssetLoader.h"
#include "AssetHandle.h"

#include "IwTexture.h"

M2DKITENGINE_NAMESPACE_BEGIN

CTextureAssetLoader::CTextureAssetLoader(const std::string& filePath)
    : m_FilePath(filePath)
{

}

CTextureAssetLoader::~CTextureAssetLoader()
{

}

CAssetHandleBase* CTextureAssetLoader::Load() const
{
    if (m_FilePath.length() == 0)
    {
        return NULL;
    }

    // Load the image
    s3eFile* file = s3eFileOpen(m_FilePath.c_str(), "rb");
    if (file == 0)
    {
        s3eFileClose(file);
        return NULL;
    }
    else
    {
        CIwImage image;
        image.ReadFile(file);
        s3eFileClose(file);

        CIwTexture* texture = new CIwTexture();
        texture->SetImage(&image);
        texture->Upload();

        CAssetHandle<CIwTexture>* assetHandle = new CAssetHandle<CIwTexture>(texture);

        return assetHandle;
    }
}

M2DKITENGINE_NAMESPACE_END
