
#include "StatesStack.h"
#include "GameStates.h"
#include "IwDebug.h"

namespace gll
{
	std::shared_ptr<gll::StateStack> StateStack::CreateSingleInstance()
	{
		std::lock_guard<std::mutex> lock(s_mutex);
		if (!s_instance.expired())
			return nullptr; /// return nullptr because there is already an instance!

		std::shared_ptr<StateStack> instance = std::shared_ptr<StateStack>(new StateStack(), StateStack::deleter());
		s_instance = instance;
		return instance;
	}


	StateStack::~StateStack()
	{

	}

	void StateStack::deleter::operator()(StateStack* p)
	{
		delete p;
	}

	std::weak_ptr<StateStack> StateStack::s_instance = std::weak_ptr<StateStack>();
	std::mutex StateStack::s_mutex;

	StateStack::StateStack() 
		: m_stateIndex(-1)
		, m_pPreviousState(NULL)
		, m_stateCountToDelete(0)
	{
		std::lock_guard<std::recursive_mutex> lockGuard(m_pStateStackMutex);
	}

	void StateStack::ChangeState(GameState* pState, bool destroyPrevious)
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

		IwAssertMsg(2DENGINE, pState != NULL, ("Tried to add a NULL state !!!"));
		if (pState == NULL)
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
		}

		ResetTouch();
	}


	void StateStack::Update(long timestamp)
	{
		std::lock_guard<std::recursive_mutex> lockGuard(m_pStateStackMutex);

		for (std::vector<GameState*>::iterator it = m_pStatePoped.begin(); it != m_pStatePoped.end(); ++it)
			//for(GameState *pState : m_pStatePoped)
		{
			GameState *pState = (*it);
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
			GameState* pState = m_pStatePushed.front();
			m_pStatePushed.pop();

			if (CurrentState())
			{
				CurrentState()->ResetControls();
			}

			IwAssertMsg(2DENGINE, pState != NULL, ("Tried to add a NULL state !!!"));
			if (pState == NULL)
			{
				ClearStateStack();
			}

			IwAssertMsg(2DENGINE, m_stateIndex < GAME_STATES_STACK_SIZE, ("m_stateIndex = %d < %d ", m_stateIndex, GAME_STATES_STACK_SIZE));

			GameState* oldState = CurrentState();
			if (oldState)
				oldState->Pause();

			pState->SetParent(CurrentState());

			m_stateIndex++;
			m_pStateStack[m_stateIndex] = pState;

			IwAssertMsg(2DENGINE, pState->Create() >= 0, ("Failed to create the current state!!!"));
			if (pState->Create() < 0)
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

		if (m_pStateStack[m_stateIndex]->IsLoading())
		{
			m_pStateStack[m_stateIndex]->SetLoading(m_pStateStack[m_stateIndex]->Load());
		}
		else
		{
			m_pStateStack[m_stateIndex]->Update(timestamp);
		}
	}


	void StateStack::PushState(GameState* pState)
	{
		std::lock_guard<std::recursive_mutex> lockGuard(m_pStateStackMutex);

		m_pStatePushed.push(pState);
	}



	void StateStack::PopState(bool bResume)
	{
		std::lock_guard<std::recursive_mutex> lockGuard(m_pStateStackMutex);

		IwAssertMsg(2DENGINE, m_stateIndex - m_pStatePoped.size() >= 0, (""));
	
		m_pStatePoped.push_back(m_pStateStack[m_stateIndex - m_pStatePoped.size()]);
	}



	void StateStack::ClearStateStack()
	{
		std::lock_guard<std::recursive_mutex> lockGuard(m_pStateStackMutex);

		while (m_stateIndex >= 0)
		{
			GameState* pState = m_pStateStack[m_stateIndex];

			pState->Pause();
			pState->Release();
			pState->SetReady(false);
			MarkStateToDelete(pState);

			m_stateIndex--;
		}

		ResetTouch();

		
		while (!m_pStatePushed.empty())
			m_pStatePushed.pop();
		

		m_pStatePoped.clear();
	}

	void StateStack::MarkStateToDelete(GameState* pState)
	{
		std::lock_guard<std::recursive_mutex> lockGuard(m_pStateStackMutex);

		m_pStateStackToDelete[m_stateCountToDelete] = pState;
		m_stateCountToDelete++;
	}

	void StateStack::DeleteStatesList()
	{
		std::lock_guard<std::recursive_mutex> lockGuard(m_pStateStackMutex);

		while (m_stateCountToDelete)
		{
			m_stateCountToDelete--;
			delete m_pStateStackToDelete[m_stateCountToDelete];
			m_pStateStackToDelete[m_stateCountToDelete] = nullptr;
		}
	}



	bool StateStack::IsStateOnStack(int stateKind) const
	{
		std::lock_guard<std::recursive_mutex> lockGuard(m_pStateStackMutex);

		for (int i = 0; i <= m_stateIndex; i++)
		{
			if (m_pStateStack[i]->isKindOf(stateKind))
				return true;
		}

		return false;
	}



	GameState* StateStack::CurrentState()
	{
		std::lock_guard<std::recursive_mutex> lockGuard(m_pStateStackMutex);

		return (m_stateIndex >= 0) ? m_pStateStack[m_stateIndex] : NULL;
	}



	void StateStack::ResetTouch()
	{

	}

}

