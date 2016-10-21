
#include "GameStates.h"
#include "StatesStack.h"
#include "IwDebug.h"

namespace gs
{

	bool	GameState::isKindOf(int) { return false; }

	int		GameState::Create()	{ return 0; }

	void	GameState::Release()	{}

	void	GameState::Pause()	{}

	void	GameState::Resume()	{}

	//bool	GameState::OnEvent(const glf::CoreEvent& event){ return false; }

	void	GameState::OnVirtualKeyboardClosed()	{}

	void	GameState::SwitchOrientation()	{}

	bool	GameState::Load()	{ return 0; }

	GameState::GameState() 
		: m_pParent(nullptr)
		, m_bReady(false)
		, m_bStateLoading(false)
	{

	}

	GameState::~GameState()
	{
		m_pParent = nullptr;
	}

	std::shared_ptr<GameState> GameState::GetParent(int level)
	{
		IwAssertMsg(2DENGINE, level >= 0 && level <= GAME_STATES_STACK_SIZE, ("level %d invalid", level));

		std::shared_ptr<GameState> parent = m_pParent;

		for (int i = 0; i < level; i++)
		{
			if (parent->m_pParent)
			{
				parent = parent->m_pParent;
			}
			else
			{
				parent = nullptr;
				break;
			}
		}
		return parent;
	}


	void GameState::ResetControls()
	{
	}

} //namespace gll

