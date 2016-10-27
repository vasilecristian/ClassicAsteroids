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

#ifndef _ANIMATION_INSTANCE_CONTAINER_H_
#define _ANIMATION_INSTANCE_CONTAINER_H_

#include "AnimationSchema.h"
#include "AnimationTrack.h"
#include "Tween.h"

#include "shared_ptr.hpp"
#include <vector>

M2DKITCORE_NAMESPACE_BEGIN

class CNode;
class CAnimationInstance;

/**
 * @addtogroup m2dkitcoregroup
 * @{
 */

/**
 * @addtogroup animationgroup
 * @{
 */

/**
 * An animation instance container is container for animation instances (CAnimationInstance). The animation
 * instance container enables a collection of animations to be grouped and updated / controlled using a single
 * interface. For more information about animations see CAnimationInstance. Nodes each have their own animation
 * instance container.
 *
 */
class CAnimationInstanceContainer
{
public:

    /**
     * @fn  CAnimationInstanceContainer::CAnimationInstanceContainer();
     *
     * Constructs an animation instance container.
     */
    CAnimationInstanceContainer();
    ~CAnimationInstanceContainer();

    /**
     * Creates an animation instance from an animation schema then adds the animation instance to the animation
     * instance container.
     *
     * @param   animationSchema The animation schema.
     * @param   animationName   (optional) The name of the animation.
     *
     * @return  If non-null, then a pointer to the created animation instance.
     */
    CAnimationInstance*             AddAnimation(TAnimationSchemaPtr animationSchema, const char* animationName = 0);

    /**
     * Gets the named animation instance.
     *
     * @param   name    The name of the animation instance.
     *
     * @return  If non-null the found animation instance.
     */
    CAnimationInstance*             GetAnimation(const char* name);


	CAnimationInstance*				GetCurrentAnimation();

	CAnimationInstance*				SetCurrentAnimation(const char* name);

	CAnimationInstance*				SetCurrentAnimation(int index);

    /**
     * Updates this animation instance container. The container node will call this to update its animations.
     *
     * @param   dt  Delta time in seconds.
     */
    void                            Update(float dt);

    /**
     * Play all animation instances.
     */
    void                            PlayAll();

    /**
     * Stop all animation instances.
     */
    void                            StopAll();

    /**
     * Pause all animation instances.
     */
    void                            PauseAll();

    /**
     * Reset all animation instances.
     */
    void                            ResetAll();

    /**
     * Rewind all animation instances.
     */
    void                            RewindAll();

    /**
     * Query if any of the contained animations are playing.
     *
     * @return  true if any animations are playing, false if not.
     */
    bool                            HasAnimations() const;

    /**
     * Copies this animation instance container to the supplied animation instance container.
     *
     * @param   destination The destination animation instance container.
     */
    void                            CopyTo(CAnimationInstanceContainer& destination) const;
private:

    typedef std::vector<CAnimationInstance*> TAnimationVec;

    //only friend the node in order to restict the setting of the owner.
    //This helps us avoid a C4355 warning.
    friend class CNode;

    void                            SetOwner(CNode* owner);
    void                            PopulateAnimationInstance(const CAnimationSchemaNode& schemaNode, CAnimationInstance* animationInstance);
    void                            PopulateAnimationInstanceRecursive(CNode* node, const CAnimationSchemaNode& schemaNode, CAnimationInstance* animationInstance);
    
    const std::string               GetAnimationLabelFromPath(const std::string& animPath) const;

    CNode*                          m_Owner;              // Owner of the animation container
    TAnimationVec                   m_Animations;         // Animation container
	int								m_currentAnimationIndex;
};

/** @}*/

/** @}*/

M2DKITCORE_NAMESPACE_END

#endif
