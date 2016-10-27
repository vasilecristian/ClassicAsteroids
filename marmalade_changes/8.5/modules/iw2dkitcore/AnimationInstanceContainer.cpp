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

#include "AnimationInstanceContainer.h"

#include "AnimationInstance.h"
#include "Node.h"

M2DKITCORE_NAMESPACE_BEGIN

CAnimationInstanceContainer::CAnimationInstanceContainer()
    : m_Owner(0)
    , m_Animations()
	, m_currentAnimationIndex(-1)
{

}

CAnimationInstanceContainer::~CAnimationInstanceContainer()
{
    for (TAnimationVec::iterator iter = m_Animations.begin(); iter != m_Animations.end(); ++iter)
    {
        if (*iter)
        {
            delete *iter;
            *iter = NULL;
        }
    }

    m_Animations.clear();
}

void CAnimationInstanceContainer::SetOwner(CNode* owner)
{
    m_Owner = owner;
}

CAnimationInstance* CAnimationInstanceContainer::AddAnimation(TAnimationSchemaPtr animationSchema, const char* animationName)
{
    CAnimationInstance* animationInstance = new CAnimationInstance(animationSchema);
    if (animationName)
    {
        animationInstance->SetName(animationName);
    }
    const CAnimationSchemaNode& root = animationSchema->GetRoot();

    if (animationSchema->GetLoop())
    {
        animationInstance->SetRepeatCount(0);
    }
    else
    {
        animationInstance->SetRepeatCount(1);
    }
    animationInstance->SetPlaybackDirection(animationSchema->GetPlaybackDirection());

    PopulateAnimationInstance(root, animationInstance);

    animationInstance->AddLabels(animationSchema->GetLabels());

    m_Animations.push_back(animationInstance);

    const std::string label = GetAnimationLabelFromPath(animationSchema->GetName());
    if (label.empty())
    {
        animationInstance->Play();
    }
    else
    {
        animationInstance->Play(label.c_str());
    }

    return animationInstance;
}

CAnimationInstance* CAnimationInstanceContainer::GetAnimation(const char* name)
{
    unsigned int nameHash = IwHashString(name);
    for (TAnimationVec::iterator iter = m_Animations.begin(); iter != m_Animations.end(); ++iter)
    {
        if ((*iter)->GetName().GetHash() == nameHash)
        {
            return *iter;
        }
    }

    return 0;
}

CAnimationInstance* CAnimationInstanceContainer::GetCurrentAnimation()
{
	if (m_currentAnimationIndex >= 0 && m_currentAnimationIndex < m_Animations.size())
	{
		return m_Animations[m_currentAnimationIndex];
	}

	return 0;
}

CAnimationInstance* CAnimationInstanceContainer::SetCurrentAnimation(const char* name)
{
	unsigned int nameHash = IwHashString(name);
	for (unsigned int i=0; i < m_Animations.size(); ++i)
	{
		if (m_Animations[i]->GetName().GetHash() == nameHash)
		{
			m_currentAnimationIndex = i;
			return m_Animations[i];
		}
	}

	m_currentAnimationIndex = -1;
	return 0;
}

CAnimationInstance* CAnimationInstanceContainer::SetCurrentAnimation(int index)
{
	if (index >= 0 && index < m_Animations.size())
	{
		m_currentAnimationIndex = index;
		return m_Animations[index];
	}
	
	m_currentAnimationIndex = -1;
	return 0;
}

void CAnimationInstanceContainer::Update(float dt)
{
	/// when there is current animation, will be updated, else, will beupdated all animations
	if (m_currentAnimationIndex >= 0 && m_currentAnimationIndex < m_Animations.size())
	{
		m_Animations[m_currentAnimationIndex]->Update(dt);
	}
	else
	{
		for (TAnimationVec::iterator animIter = m_Animations.begin(); animIter != m_Animations.end(); ++animIter)
		{
			(*animIter)->Update(dt);
		}
	}
}

void CAnimationInstanceContainer::PopulateAnimationInstance(const CAnimationSchemaNode& schemaNode, CAnimationInstance* animationInstance)
{
    PopulateAnimationInstanceRecursive(m_Owner, schemaNode, animationInstance);
}

void CAnimationInstanceContainer::PopulateAnimationInstanceRecursive(CNode* node, const CAnimationSchemaNode& schemaNode, CAnimationInstance* animationInstance)
{
    const CAnimationSchemaNode::TTrackMap& track_map = schemaNode.GetTracks();

    for (CAnimationSchemaNode::TTrackMap::const_iterator iter = track_map.begin(); iter != track_map.end(); ++iter)
    {
        const uint32 propertyNameHash = iter->first;
        node->AddTween(propertyNameHash, iter->second, animationInstance);
    }

    const CAnimationSchemaNode::TChildVector& m_Children = schemaNode.GetChildren();

    for (CAnimationSchemaNode::TChildVector::const_iterator iter = m_Children.begin(); iter != m_Children.end(); ++iter)
    {
        TNodePtr nodeChild = node->FindChildByName(iter->GetName().GetString().c_str());
        if (nodeChild)
        {
            PopulateAnimationInstanceRecursive(nodeChild.get(), *iter, animationInstance);
        }
    }
}

const std::string CAnimationInstanceContainer::GetAnimationLabelFromPath(const std::string& animPath) const
{
    std::string label = "";
    const size_t dotPos = animPath.find_first_of('.');
    const size_t lastSlashPos = animPath.find_last_of('/');
    if (dotPos == std::string::npos || lastSlashPos == std::string::npos)
    {
        return label;
    }
    if (lastSlashPos > dotPos)
    {
        label = animPath.substr(lastSlashPos + 1, animPath.length() - lastSlashPos - 1);
    }

    return label;
}

void CAnimationInstanceContainer::PlayAll()
{
    for (TAnimationVec::iterator animIter = m_Animations.begin(); animIter != m_Animations.end(); ++animIter)
    {
        (*animIter)->Play();
    }
}

void CAnimationInstanceContainer::StopAll()
{
    for (TAnimationVec::iterator animIter = m_Animations.begin(); animIter != m_Animations.end(); ++animIter)
    {
        (*animIter)->Stop();
    }
}

void CAnimationInstanceContainer::PauseAll()
{
    for (TAnimationVec::iterator animIter = m_Animations.begin(); animIter != m_Animations.end(); ++animIter)
    {
        (*animIter)->Pause();
    }
}

void CAnimationInstanceContainer::ResetAll()
{
    for (TAnimationVec::iterator animIter = m_Animations.begin(); animIter != m_Animations.end(); ++animIter)
    {
        (*animIter)->Reset();
    }
}

void CAnimationInstanceContainer::RewindAll()
{
    for (TAnimationVec::iterator animIter = m_Animations.begin(); animIter != m_Animations.end(); ++animIter)
    {
        (*animIter)->Rewind();
    }
}

bool CAnimationInstanceContainer::HasAnimations() const
{
    return !m_Animations.empty();
}

void CAnimationInstanceContainer::CopyTo(CAnimationInstanceContainer& destination) const
{
    for (TAnimationVec::const_iterator animIter = m_Animations.begin(); animIter != m_Animations.end(); ++animIter)
    {
        destination.AddAnimation((*animIter)->GetAnimationSchema(), (*animIter)->GetName().GetString().c_str())->Stop();
    }
}

M2DKITCORE_NAMESPACE_END
