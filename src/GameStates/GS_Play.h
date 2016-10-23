#ifndef __GS_Play_H__
#define __GS_Play_H__

#include "GameStatesBase/GameStates.h"
#include <memory>
#include "Button.h"

namespace m2dkit
{
	namespace engine
	{
		class CGameManager;
	};
};

/**
 * Class defining the state which holds the main menu.
 * All tests are accessible from this state.
 */
class GS_Play : public gs::GameState
{
public:
    

    /** 
     * Constructor
     */
	GS_Play(std::weak_ptr<m2dkit::engine::CGameManager> gamePtr, std::string levelName);

    /**
     * Destructor
     */
	~GS_Play();

    /**
     * Update method.
     *
     * @param dt The Delta time elapsed since the last update.
     */ 
	void Update(float dt) override;

    /**
     * Render method.
     */
	void Render() override;

    /**
     * Create method. Initializations should be done here.
     *
     * @return True if state was created successful, false otherwise.
     */
	int	Create() override;

    /**
     * Release method. Free memory here.
     */
	void Release() override;

    /**
     * Pause method.
     */
	void Pause() override;

    /**
     * Resume method. Called each time the StatesStack comes back to this state.
     */
	void Resume() override;

	bool Load() override;

	
private:

	int m_sceneId; /// The scenes unique Id
	int m_loadingSceneId;
	std::weak_ptr<m2dkit::engine::CGameManager> m_gameWeakPtr;
	std::string m_levelName;
	int m_loadingProgress;


	enum class PlayerMove
	{
		IDLE,
		LEFT,
		RIGHT,
		FORWARD,
		BACKWARD,
	};

	PlayerMove m_playerMove;

	m2dkit::core::CAnimationInstance* m_animPlayerShipTurnLeft;
	m2dkit::core::CAnimationInstance* m_animPlayerShipReleaseLeft;

	m2dkit::core::CAnimationInstance* m_animPlayerShipTurnRight;
	m2dkit::core::CAnimationInstance* m_animPlayerShipReleaseRight;

	m2dkit::core::CAnimationInstance* m_animPlayerShipIdle;

	m2dkit::shared_ptr<m2dkit::core::CSprite> m_playerShip;

	int m_posX;
	int m_posY;
};

#endif //__GS_Play_H__