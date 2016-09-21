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

#ifndef _ENGINEDEFINES_H_
#define _ENGINEDEFINES_H_

#include "CoreDefines.h"

#define ENGINE_NAMESPACE_BEGIN \
    namespace engine {

#define ENGINE_NAMESPACE_END \
    }

#define M2DKITENGINE_NAMESPACE_BEGIN \
    M2DKIT_NAMESPACE_BEGIN \
    ENGINE_NAMESPACE_BEGIN

#define M2DKITENGINE_NAMESPACE_END \
    ENGINE_NAMESPACE_END \
    M2DKIT_NAMESPACE_END

#define M2DKITENGINE_USE_NAMESPACE \
    using namespace m2dkit::engine;

#endif
