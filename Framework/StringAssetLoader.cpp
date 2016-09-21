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

#include "StringAssetLoader.h"
#include "AssetHandle.h"

#include "IwTexture.h"

M2DKITENGINE_NAMESPACE_BEGIN

CStringAssetLoader::CStringAssetLoader(const std::string& filePath)
    : m_FilePath(filePath)
{

}

CStringAssetLoader::~CStringAssetLoader()
{

}

CAssetHandleBase* CStringAssetLoader::Load() const
{
    if (m_FilePath.length() == 0)
    {
        return NULL;
    }

    s3eFile* file = s3eFileOpen(m_FilePath.c_str(), "rb");
    if (file == 0)
    {
        s3eFileClose(file);
        return NULL;
    }
    else
    {
        const int dataLen = s3eFileGetSize(file);
        char* data = new char[dataLen + 1];
        s3eFileRead(data, 1, dataLen, file);
        s3eFileClose(file);
        data[dataLen] = 0;

        std::string* stringData = new std::string(data);

        CAssetHandle<std::string>* assetHandle = new CAssetHandle<std::string>(stringData);

        delete[] data;

        return assetHandle;
    }
}

M2DKITENGINE_NAMESPACE_END
