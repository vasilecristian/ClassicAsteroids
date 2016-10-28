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

#ifndef _EVENTCALLBACK_H_
#define _EVENTCALLBACK_H_

#include "CoreDefines.h"
#include <map>

M2DKITCORE_NAMESPACE_BEGIN

/**
 * @addtogroup m2dkitcoregroup
 * @{
 */

/**
 * @defgroup eventsgroup  Event Notification
 * Many core objects utilise a subscription based event notification system. This system allows objects such as
 * nodes to notify users of the object when certain events occur, such as when the node was touched by the user.
 * Objects that use this subscription based events model carry an events map (CEventMap) which stores a map of
 * event types (such as NODE_EVENT_TOUCH) with their callbacks. When an event is raised the map is searched and
 * if the event type is present then the corresponding callback is called, which in turn notifies the user of
 * the event.
 *
 */

/**
 * @addtogroup eventsgroup
 * @{
 */

/**
 * Defines an event source. The event source is the original object that raised the event.
 */
typedef void* CEventSource;

/**
 * Base event args structure that all event arguments derive from. This structure provides additional
 * information about the raised event.
 */
struct CEventArgs
{
    /**
     * @fn  CEventArgs(CEventSource* source)
     *
     * Constructs an events arg structure with source.
     *
     * @param   source  If non-null, source of the event.
     */
    CEventArgs(CEventSource* source):
        m_Source(source),
        m_UserData(0)
    {}

    /**
     * @fn  CEventArgs(CEventSource* source, void* userData)
     *
     * Constructs an events arg structure with source and user data.
     *
     * @param   source      If non-null, source of the event.
     * @param   userData    If non-null, user data supplied by event subscriber.
     */
    CEventArgs(CEventSource* source, void* userData) :
        m_Source(source),
        m_UserData(userData)
    {}

    /**
     * Object that is the source of the event.
     */
    CEventSource*   m_Source;

    /**
     * User data supplied by the event subscriber.
     */
    void*           m_UserData;
};

/**
 * Defines a callback that event subscribers supply when subscribing to events. This callback will be called
 * when the event is raised.
 */
typedef std::function<void(CEventArgs*)> CEventCallback;

/**
 * An events map which stores a map of event types (such as NODE_EVENT_TOUCH) with their callbacks. When an
 * event is raised the map is searched and if the event type is present then the corresponding callback is called,
 * which in turn notifies the user of the event.
 *
 */
class CEventMap
{
public:
    /**
     * Subscribers to an event.
     *
     * @param   eventNameHash   The event name as a string hash.
     * @param   callback        The callback to be called when the event occurs.
     */
    void Subscribe(uint32 eventNameHash, CEventCallback callback);

    /**
     * Un-subscribes from an event.
     *
     * @param   eventNameHash   The event name as a string hash.
     */
    void Unsubscribe(uint32 eventNameHash);

    /**
     * Notifies subscribers of an event occurring by searching the events map for the specified event then calling its
     * callback if present.
     *
     * @param   eventNameHash   The event name as a string hash.
     * @param   args            If non-null, the events arguments.
     */
    void Notify(uint32 eventNameHash, CEventArgs* args);
private:
    std::map<uint32, CEventCallback> m_Callbacks;
};

M2DKITCORE_NAMESPACE_END

/** @}*/

/** @}*/

#endif
