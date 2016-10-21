#ifndef __GS_MenuMain_H__
#define __GS_MenuMain_H__

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
class GS_MenuMain : public gs::GameState
{
public:
    /**
     * Enum defining all items that can be found
     * in the menu.
     */
	enum ITEM_IDS
	{
		ITEM_GLITCH = 0,
		ITEM_VOX,
		ITEM_GAMESWF,
		ITEM_ONLINE,
		ITEM_MISC,
		ITEM_PUSH,
		ITEM_IAP,
		ITEM_INFO,
		ITEM_QUIT,
	};

    /** 
     * Constructor
     */
	GS_MenuMain(std::weak_ptr<m2dkit::engine::CGameManager> gamePtr);

    /**
     * Destructor
     */
	~GS_MenuMain();

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

	bool Load();

	void ButtonReleasedCallback1(m2dkit::core::CEventArgs* args);
	
private:

	int m_sceneId; /// The scenes unique Id
	std::weak_ptr<m2dkit::engine::CGameManager> m_gameWeakPtr;
};

#endif //_GS_MenuMain_H_