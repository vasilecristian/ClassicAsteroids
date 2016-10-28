
#include "StatesStack.h"
#include "GameStates.h"
#include "IwDebug.h"

namespace gs
{
	
	StatesStack::~StatesStack()
	{
		
	}

	StatesStack::StatesStack() 
		: m_stateIndex(-1)
		, m_pPreviousState(NULL)
		, m_stateCountToDelete(0)
	{
		std::lock_guard<std::recursive_mutex> lockGuard(m_pStateStackMutex);
	}

	void StatesStack::ChangeState(std::shared_ptr<GameState> pState, bool destroyPrevious)
	{
		// PopState
		std::lock_guard<std::recursive_mutex> lockGuard(m_pStateStackMutex);
		

		IwAssertMsg(2DENGINE, m_stateIndex >= 0, ("m_stateIndex=%d have wrong value!", m_stateIndex));

		m_pPreviousState = m_pStateStack[m_stateIndex];

		m_pPreviousState->Pause();
		m_pPreviousState->Release();
		m_pPreviousState->SetReady(false);
		m_stateIndex--;

		if (destroyPrevious)
		{
			MarkStateToDelete(m_pPreviousState);
		}

		IwAssertMsg(2DENGINE, pState != nullptr, ("Tried to add a NULL state !!!"));
		if (pState == nullptr)
		{
			ClearStateStack();
		}

		// PushState
		IwAssertMsg(2DENGINE, m_stateIndex < GAME_STATES_STACK_SIZE, ("m_stateIndex = %d < %d ", m_stateIndex, GAME_STATES_STACK_SIZE));

		pState->SetParent(m_pPreviousState->GetParent());

		m_stateIndex++;
		m_pStateStack[m_stateIndex] = pState;

		int result = pState->Create();
		IwAssertMsg(2DENGINE, result >= 0, ("Failed to create the current state!!!!"));
		if (result < 0)
		{
			ClearStateStack();
		}
		else
		{
			pState->SetReady(true);
			pState->Resume();
			pState->SetLoading(true);
		}

		ResetTouch();
	}


	void StatesStack::Update(float timestamp)
	{
		std::lock_guard<std::recursive_mutex> lockGuard(m_pStateStackMutex);

		for (auto it = m_pStatePoped.begin(); it != m_pStatePoped.end(); ++it)
			//for(GameState *pState : m_pStatePoped)
		{
			std::shared_ptr<GameState> pState = (*it);
			pState->Pause();
			pState->Release();
			pState->SetReady(false);

			m_stateIndex--;

			MarkStateToDelete(pState);

			if (/*bResume*/true && m_stateIndex >= 0)
			{
				std::lock_guard<std::recursive_mutex> lockGuard(m_pStateStackMutex);
				m_pStateStack[m_stateIndex]->Resume();
			}

			ResetTouch();

			if (CurrentState())
			{
				CurrentState()->ResetControls();
			}
		}
		m_pStatePoped.clear();
		

		
		
		if (!m_pStatePushed.empty())
		{
			std::shared_ptr<GameState> pState = m_pStatePushed.front();
			m_pStatePushed.pop();

			if (CurrentState())
			{
				CurrentState()->ResetControls();
			}

			IwAssertMsg(2DENGINE, pState != nullptr, ("Tried to add a NULL state !!!"));
			if (pState == nullptr)
			{
				ClearStateStack();
			}

			IwAssertMsg(2DENGINE, m_stateIndex < GAME_STATES_STACK_SIZE, ("m_stateIndex = %d < %d ", m_stateIndex, GAME_STATES_STACK_SIZE));

			std::shared_ptr<GameState> oldState = CurrentState();
			if (oldState)
				oldState->Pause();

			pState->SetParent(CurrentState());

			m_stateIndex++;
			m_pStateStack[m_stateIndex] = pState;

			int createResult = pState->Create();

			IwAssertMsg(2DENGINE, createResult >= 0, ("Failed to create the current state!!!"));
			
			if (createResult < 0)
			{
				ClearStateStack();
			}
			else
			{
				pState->SetReady(true);
				pState->Resume();
				pState->SetLoading(true);
			}
			ResetTouch();
		}
		
		

		DeleteStatesList();

		if (m_stateIndex == -1)
		{
			return;
		}

		if (m_pStateStack[m_stateIndex]->IsLoading())
		{
			m_pStateStack[m_stateIndex]->SetLoading(m_pStateStack[m_stateIndex]->Load());
		}
		else
		{
			m_pStateStack[m_stateIndex]->Update(timestamp);
		}
	}


	void StatesStack::PushState(std::shared_ptr<GameState> pState)
	{
		std::lock_guard<std::recursive_mutex> lockGuard(m_pStateStackMutex);

		m_pStatePushed.push(pState);
	}



	void StatesStack::PopState(bool bResume)
	{
		std::lock_guard<std::recursive_mutex> lockGuard(m_pStateStackMutex);

		IwAssertMsg(2DENGINE, m_stateIndex - m_pStatePoped.size() >= 0, (""));
	
		m_pStatePoped.push_back(m_pStateStack[m_stateIndex - m_pStatePoped.size()]);
	}



	void StatesStack::ClearStateStack()
	{
		std::lock_guard<std::recursive_mutex> lockGuard(m_pStateStackMutex);

		while (m_stateIndex >= 0)
		{
			std::shared_ptr<GameState> pState = m_pStateStack[m_stateIndex];

			pState->Pause();
			pState->Release();
			pState->SetReady(false);
			MarkStateToDelete(pState);

			m_stateIndex--;
		}

		ResetTouch();

		
		while (!m_pStatePushed.empty())
		{
			m_pStatePushed.pop();
		}
		

		m_pStatePoped.clear();

		// Update must be called because all the states marked to be deleted,
		// will be deleted actually on the next update call. 
		Update(0);
	}

	void StatesStack::MarkStateToDelete(std::shared_ptr<GameState> pState)
	{
		std::lock_guard<std::recursive_mutex> lockGuard(m_pStateStackMutex);

		m_pStateStackToDelete[m_stateCountToDelete] = pState;
		m_stateCountToDelete++;
	}

	void StatesStack::DeleteStatesList()
	{
		std::lock_guard<std::recursive_mutex> lockGuard(m_pStateStackMutex);

		while (m_stateCountToDelete)
		{
			m_stateCountToDelete--;
			//delete m_pStateStackToDelete[m_stateCountToDelete];
			m_pStateStackToDelete[m_stateCountToDelete] = nullptr;
		}
	}



	bool StatesStack::IsStateOnStack(int stateKind) const
	{
		std::lock_guard<std::recursive_mutex> lockGuard(m_pStateStackMutex);

		for (int i = 0; i <= m_stateIndex; i++)
		{
			if (m_pStateStack[i]->isKindOf(stateKind))
				return true;
		}

		return false;
	}



	std::shared_ptr<GameState> StatesStack::CurrentState()
	{
		std::lock_guard<std::recursive_mutex> lockGuard(m_pStateStackMutex);

		return (m_stateIndex >= 0) ? m_pStateStack[m_stateIndex] : nullptr;
	}



	void StatesStack::ResetTouch()
	{

	}

}

