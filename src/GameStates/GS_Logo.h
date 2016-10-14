#ifndef __GS_LOGO_H__
#define __GS_LOGO_H__


#include "GameStatesBase/GameStates.h"
#include <memory>

namespace m2dkit
{
	namespace engine
	{
		class CGameManager;
	};
};

/**
 * Class which represents the Gameloft Logo that first shows up
 * when opening the game. It uses a timer to keep the logo on screen
 * for a period of time, and then it loads the game menu.
 */
class GS_Logo : public gs::GameState
{
public:
    /**
     * Constructor
     */
	GS_Logo(std::weak_ptr<m2dkit::engine::CGameManager> gamePtr);

    /**
     * Destructor
     */
	~GS_Logo();

    /**
     * Update method.
     *
     * @param dt The Delta time elapsed since the last update.
     */
	void Update(long dt) override;

    /**
     * Render method.
     */
	void Render() override;
    
    /**
     * Create method. Initializations should be done here.
     *
     * @return True if state was created successful, false otherwise.
     */
	int  Create() override;

    /**
     * Release method. Free memory here.
     */
	void Release() override;

    /**
     * Resume method. Called each time the StatesStack comes back to this state.
     */
	void Resume() override;

    
private:
	int           m_timer; ///< Timer that gets decremented each tick.

};

#endif //__GS_LOGO_H__