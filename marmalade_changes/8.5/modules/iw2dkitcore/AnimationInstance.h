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

#ifndef _ANIMATION_INSTANCE_H_
#define _ANIMATION_INSTANCE_H_

#include "HashString.h"
#include "AnimationEnums.h"

#include "AnimationSchema.h"
#include "NodeEvents.h"

#include <vector>
#include <map>
#include <algorithm>

M2DKITCORE_NAMESPACE_BEGIN

class CTweenBase;
class CNode;

/**
 * @addtogroup m2dkitcoregroup
 * @{
 */

/**
 * @defgroup animationgroup  Animation
 *
 * The m2dkit core has a powerful key frame based animation system at its core which can be used to create complex animation
 * hierarchies. The animation system supports the following features:
 * - Animation definition using animation schemas.
 * - Key frame based animation with easing.
 * - Hierarchal child animation.  
 * - Timeline marking using animation labels.
 * - Playback direction.
 * - Playback looping.
 */

/**
 * @addtogroup animationgroup
 * @{
 */

/**
 * <h1>Introduction</h1>
 * The m2dkit core has a powerful key frame based animation system at its core which can be used to create complex animation
 * hierarchies. The animation system supports the following features:
 * - Animation definition using animation schemas.
 * - Key frame based animation with easing.
 * - Hierarchal child animation.
 * - Timeline marking using animation labels.
 * - Playback direction.
 * - Playback looping.
 *
 * @anchor animation_definition
 * <h1>Animation creation</h1>
 * An animation schema (CAnimationSchema) is a resource that represents an hierarchical animation. The schema is built
 * up from animation tracks (CAnimationTrack) with each track representing some value of a property that varies over time.
 * Animation tracks are built up from key frames (CKeyFrame), where each key frame represents the value of a property at
 * a specific point in time. Using animation schemas enable animations to be created and shared across multiple nodes by
 * creating an animation instance from a schema then adding the instance to a node via the nodes animation instance container
 * (CAnimationInstanceContainer). When an animation instance is played back on a node, key frames will be smoothly
 * interpolated between individual key frames using easing based tweening (CTween). See @ref node_animation "Node animation"
 * for more information about node animation. Animation schemas are created and managed by the scene via
 * CScene::CreateAnimationSchema().
 * 
 * The example below shows how to create a basic animation schema with a single animation track:
 * 
 * @code
 *      // Create a schema to hold the animation data
 *      TAnimationSchemaPtr schema = scene->CreateAnimationSchema("RotationAnim");
 *      CAnimationSchemaNode& root = schema->GetRoot();
 *
 *      // Create an animation track to hold key frames which targets the Rotation property
 *      shared_ptr<CAnimationTrack<float>> rotationTrack = root.RequestNewAnimationTrack<float>("Rotation");
 *
 *      // Create key frames and add them to the animation track
 *      CKeyFrame<float> rotationKeyFrame1(0.0f, 0.0f, ExpIn, 2.0f, AbsoluteKeyFrameType);
 *      rotationTrack->GetKeyFrames().push_back(rotationKeyFrame1);
 *      CKeyFrame<float> rotationKeyFrame2(2.0f, 180.0f, ExpOut, 2.0f, AbsoluteKeyFrameType);
 *      rotationTrack->GetKeyFrames().push_back(rotationKeyFrame2);
 * @endcode
 *
 * The above example creates an animation schema called RotationAnim that is automatically added to the scenes resources.
 * Next an animation track is created that targets the Rotation property of the object that an instance of the animation
 * targets then a number of key frames that represent how the value changes over time are created and added to the animation
 * track.
 *
 * @anchor animation_instances
 * <h1>Animation instances</h1>
 * An animation instance is a discrete instance of an animation schema which can be attached to nodes to make them animate.
 * An animation instance is created automatically by adding a schema to a nodes animation instance container
 * (CAnimationInstanceContainer), e.g.:
 * 
 * @code
 *      // Add a new instance of the animation schema to a node
 *      node->GetAnimationContainer().AddAnimation(schema, "SpinMe");
 * @endcode
 *
 * @anchor animation_keyframes
 * <h1>Animation key frames</h1>
 * Animations are built up from key frames, each key frame represents a properties value at a specific point in time. During
 * animation playback, the actual value of a property will be smoothly tweened between one key frame and the next applying
 * an easing function and easing value. Easing enables the animation system to apply different formulas to time to produce useful
 * effects such as elastic and bounce. For a full list of easing types see eEasing. Key frames are used by the tweening system,
 * animation instances animation tracks.
 *
 * @anchor animation_modification
 * <h1>Animation modification</h1>
 * Once an animation has been instanced it can be controlled via its instance, for example to play the animation call Play()
 * and to rewind the animation call Rewind(). An animation instance has the following features:
 * - Playback time scale - The speed which an animation plays back can be adjusted to speed up or slow down the animation playback.
 * - Playback looping - Animations can be set to loop indefinitely or a set number of times.
 * - Playback direction - Animations can play forwards, backwards or forwards then backwards.
 * - Label playback - Play back any portion of the animation marked by a label.
 * 
 * @anchor animation_labels
 * <h1>Animation labels</h1>
 * Animation labels enable sections of the animation timeline to be marked and played back as an individual animation, which is
 * useful when creating animations that are built up of many sub animations. For example a single animation schema can represent
 * all 4 state animations of a button. To play an animation label call Play(const char* label). Note that animation labels are
 * persistent, this means that if an animation label is played then the start point of the animation will be limited to the labels
 * start time and the end time to the start of the next label in time or the end of the animation if the label is the last label
 * in the animation.
 *
 * @anchor animation_events
 * <h1>Animation events</h1>
 * As with nodes, animations can raise events to notify the user that something has changed within the animation.
 * The following events are supported:
 * - Animation has started playing.
 * - Animation has resumed playing.
 * - Animation was paused.
 * - Animation has repeated.  
 * - Animation has stopped playing.  
 *
 * The user can assign a callback for the animation instance that is called in response to an event being raised. The example below
 * shows how to set up a callback to respond to animation playback events:
 *
 * @code
 *      // Create an animation event callback
 *      void AnimationPlaybackChangedCallback(CEventArgs* args)
 *      {
 *          CAnimationInstanceEventPlaybackChangedArgs* _args = (CAnimationInstanceEventPlaybackChangedArgs*)args;
 *          CAnimationInstance* inst = (CAnimationInstance*)_args->m_Source;
 *          switch (_args->m_PlaybackEvent)
 *          {
 *          case Animation::PlaybackEventStarted:
 *              s3eDebugTracePrintf("Animation %s has started", inst->GetName().GetString().c_str());
 *              break;
 *          case Animation::PlaybackEventResumed:
 *              s3eDebugTracePrintf("Animation %s has resumed", inst->GetName().GetString().c_str());
 *              break;
 *          case Animation::PlaybackEventPaused:
 *              s3eDebugTracePrintf("Animation %s has paused", inst->GetName().GetString().c_str());
 *              break;
 *          case Animation::PlaybackEventRepeated:
 *              s3eDebugTracePrintf("Animation %s has repeated", inst->GetName().GetString().c_str());
 *              break;
 *          case Animation::PlaybackEventStopped:
 *              s3eDebugTracePrintf("Animation %s has stopped", inst->GetName().GetString().c_str());
 *              break;
 *          }
 *      }
 *
 *      // Find the animation instance
 *      CAnimationInstance* anim = node->GetAnimationContainer().GetAnimation("SpinMe");
 *
 *      // Subscribe to the animation playback event
 *      anim->SubscribeEvent(ANIMATION_INSTANCE_EVENT_PLAYBACK_CHANGED, AnimationPlaybackChangedCallback);
 * @endcode
 *
 */
class CAnimationInstance
{
public:
    /**
     * An animation instance callback.
     */
	typedef std::function<void(Animation::ePlaybackEvent event, CAnimationInstance* source)> CAnimationInstanceCallback;

    /**
     * Constructs an instance of an animation instance from an animation schema. See @ref animation_definition
     * "Animation creation" for more details.
     *
     * @param   animationSchema The animation schema from which to create an animation instance.
     */
    CAnimationInstance(TAnimationSchemaPtr animationSchema);
    ~CAnimationInstance();

    /**
     * Sets the name of the animation instance.
     *
     * @param   name    The animation instance name.
     */
    void                        SetName(const char* name);

    /**
     * Gets the name of the animation instance.
     *
     * @return  The animation instance name.
     */
    const CHashString&          GetName() const;

    /**
     * Sets animation instance time scale, time scale values of greater than 1.0 will increase the rate at which the
     * animation is played back, values of less than 1.0f will slow down the rate at which the animation is played
     * back.
     *
     * @param   scale   The time scale value.
     */
    void                        SetTimeScale(float scale);

    /**
     * Gets the animation instance time scale.
     *
     * @return  The time scale value.
     */
    float                       GetTimeScale() const;

    /**
     * Sets the animations time value, with 0 representing the start of the animation. Setting the animations time
     * value directly will adjust all properties within the instance to match the value at the specified time.
     *
     * @param   time    The new time in seconds.
     */
    void                        SetTime(float time);

    /**
     * Gets the animations current time.
     *
     * @return  The current time in seconds.
     */
    float                       GetTime() const;

    /**
     * Sets the number of times that the animation should loop. Passing a value of 0 will cause the animation to
     * loop forever.
     *
     * @param   count   Number of times to loop.
     */
    void                        SetRepeatCount(int count);

    /**
     * Sets the animations playback direction.
     *
     * @param   direction   The playback direction.
     */
    void                        SetPlaybackDirection(Animation::ePlaybackDirection direction);

    /**
     * Sets the animations event callback which is called in response to certain events taking place within the
     * animation. See @ref animation_events "Animation events" for more information.
     * Deprecated, please subscribe to events using SubscribeEvent().
     *
     * @param   callback    The callback to call.
     */
    M2DKIT_DEPRECATED void      SetEventCallback(CAnimationInstanceCallback callback);

    /**
     * Subscribe to the specified event. The animation instance can call back user provided callbacks in response to
     * a number of different events.
     *
     * @param   eventNameHash   The event name as a string hash.
     * @param   callback        The callback that will be called to handle the event.
     */
    void                        SubscribeEvent(uint32 eventNameHash, CEventCallback callback);

    /**
     * Unsubscribe from the specified event.
     *
     * @param   eventNameHash   The event name as a string hash.
     */
    void                        UnsubscribeEvent(uint32 eventNameHash);

    /**
     * Gets animation instance playback state.
     *
     * @return  The current playback state.
     */
    Animation::ePlaybackState   GetPlaybackState() const;

    /**
     * Gets animation instance playback length in seconds.
     *
     * @return  The playback length.
     */
    float                       GetPlaybackLength() const;

    /**
     * Gets animation schema that this animation was instanced from.
     *
     * @return  The associated animation schema.
     */
    const TAnimationSchemaPtr   GetAnimationSchema() const;

    /**
     * Adds a tween to the animation.
     *
     * @param tween   If non-null, the tween to add.
     */
    void                        AddTween(CTweenBase* tween);

    /**
     * Adds a map of animation labels to this animation.
     *
     * @param   labelsMap   A map of labels.
     */
    void                        AddLabels(const CAnimationSchema::TLabelsMap& labelsMap);

    /**
     * Updates the animation instance. This method is called by the instances animation instance container update method
     * CAnimationInstanceContainer::Update().
     *
     * @param   dt  Delta time in seconds.
     *
     * @return  true if the animation is still playing, false if it is not.
     */
    bool                        Update(float dt);

    /**
     * Determines if this animation will be updated this frame.
     *
     * @return  true if the animation will be updated this frame, false if not.
     */
    bool                        WillUpdate();

    /**
     * Starts playing the animation, or continues playing the animation if it was paused. If the animation was previously
     * stopped then the animation will be rewound then played.
     */
    void                        Play();

    /**
     * Sets the animations current animation label and starts playing the animation from the label, or continues playing
     * the animation if it was paused. If the animation was previously stopped then the animation will be rewound to the
     * start of the label then played. Note that once you play a label all future Play(), Rewind() calls will work with
     * that label. To cancel the label pass NULL to the label parameter.
     *
     * @param   label   The animation label to play, pass NULL to cancel the label.
     */
    void                        Play(const char* label);

    /**
     * Pauses playback of the animation.
     */
    void                        Pause();

    /**
     * Stops playback of the animation.
     */
    void                        Stop();

    /**
     * Rewinds the animation to its start.
     */
    void                        Rewind();

    /**
     * Resets this animation. Resetting the animation will rewind the animation and set the animation and stop the animation.
     */
    void                        Reset();

private:

    /**
     * An animation label structure. See @ref animation_labels "Animation labels" for more information.
     */
    struct CAnimationLabel
    {
        /**
         * @fn  CAnimationLabel(uint32 hash, float timeStamp)
         *
         * Constructs an animation label.
         *
         * @param   hash        The string hash name of the animation label.
         * @param   timeStamp   The time at which the label should be placed in seconds.
         */
        CAnimationLabel(uint32 hash, float timeStamp)
            : m_Hash(hash)
            , m_TimeStamp(timeStamp)
        {

        }

        /**
         * The name hash of the label.
         */
        uint32 m_Hash;

        /**
         * The time at which the label resides in seconds.
         */
        float m_TimeStamp;
    };

    struct CFindLabelWithHash : public std::unary_function<CAnimationLabel, bool>
    {
        CFindLabelWithHash(uint32 hash)
            : m_Hash(hash)
        {

        }

        bool operator() (const CAnimationLabel& label)
        {
            return m_Hash == label.m_Hash;
        }

        uint32 m_Hash;
    };

    struct CSortWithTimeStamp
    {
        bool operator() (const CAnimationLabel& first, const CAnimationLabel& second) const
        {
            return first.m_TimeStamp < second.m_TimeStamp;
        }
    };

    /**
     * A vector of tweens.
     */
    typedef std::vector<CTweenBase*> TweenVector;

    /**
     * A vector of animation labels.
     */
    typedef std::vector<CAnimationLabel> TAnimationLabelsVec;

    TweenVector                     m_Tweens;               // Active tweens
    TAnimationLabelsVec             m_Labels;               // Animation labels
    Animation::ePlaybackState       m_PlaybackState;        // Play back state
    Animation::ePlaybackDirection   m_PlaybackDirection;    // Direction of playback
    float                           m_Time;                 // Current time offset
    float                           m_TimeScale;            // Amount to scale delta time
    CAnimationInstanceCallback      m_EventCallback;        // Event that is called when something in the tween collection changes
    CHashString                     m_Name;                 // Name of animation
    int                             m_RepeatCount;          // Number of times to repeat the tween collection
    int                             m_Plays;                // Total number of plays
    float                           m_PlaybackLength;       // Total length of playback in seconds
    bool                            m_Reverse;              // If true then playing animation in reverse
    unsigned int                    m_CurrentLabel;         // Current label that is being played
    float                           m_LabelStartTime;       // Current label start time
    float                           m_LabelEndTime;         // Current label end time

    TAnimationSchemaPtr             m_AnimationSchema;      // Animation schema
    CEventMap                       m_EventsMap;            // Events map

    bool                            HasFinished() const;
    void                            UpdateLabelStartEndTime(unsigned int labelHash);
};

/** @}*/

/** @}*/

M2DKITCORE_NAMESPACE_END

#endif
