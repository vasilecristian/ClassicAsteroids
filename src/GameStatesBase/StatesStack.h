
#ifndef _STATES_STACK_H_
#define _STATES_STACK_H_



#include "GameStates.h"

#include <queue>
#include <mutex>
#include <array>

#define GAME_STATES_STACK_SIZE	512


namespace gs
{
    class GameState;
	class StateStackDeleter;

	class StateStack 
	{
		friend class StateStackDeleter;
    private:

        /** Update - the game state stack.
        * @param timestamp is float, the time*/
		void Update(long timestamp);

		std::queue<GameState*>	m_pStatePushed;
		std::vector<GameState*>	m_pStatePoped;

	public:

        /** InitStateStack - initialize the state stack. */
		void InitStateStack() { m_stateIndex = -1; m_stateCountToDelete = 0; }

        /** ChangeState - process the change of the state.
        * @param pState is a pointer to GameState, that is the new state to be put on stack.
        * @param destroyPrevious is a boolean (optional), if true (default) the previous state will be destroyed. */
		void ChangeState(GameState* pState, bool destroyPrevious = true);

        /** PushState - set the state to be pushed.
        * @param pState is a pointer to GameState, that will be the value for m_pStatePushed. */
		void PushState(GameState* pState);

        /** PopState - pop the state from stack, (set the m_pStatePoped).
        * @param bResume is a boolean (optional), unused. */
		void PopState(bool bResume = true);

        /** ClearStateStack - clear the state stack. */
		void ClearStateStack();

        /** MarkStateToDelete - put the state in the m_pStateStackToDelete.
        * @param pState is a pointer to GameState, the state to be deleted. */
		void MarkStateToDelete( GameState* pState );

        /** DeleteStatesList - delete m_pStateStackToDelete */
		void DeleteStatesList();
				
        /** CurrentState - get the current state.
        * @return a pointer to GameState, if a state is on the stack or NULL. */
		GameState* CurrentState();

        /** PreviousState - get the previous state.
        * @return a pointer to GameState, that is the previous state. */
		GameState* PreviousState() { return m_pPreviousState; };
				
        /** GetStateNo - return the number of states in the stack.
        * @returns an integer, m_stateIndex .*/
		inline int GetStateNo(){ return m_stateIndex; };

        /** ResetTouch - not implemented */
		void ResetTouch();

        /** IsStateOnStack - check if a kind of state is on the stack.
        * @param stateKind is an int, representing the type of state to look after in the stack.
        * @return a boolean that is true if that type of state is on the stack, else return false . */
		bool IsStateOnStack(int stateKind) const;

	private:

		mutable std::recursive_mutex m_pStateStackMutex;
		std::array<GameState*, GAME_STATES_STACK_SIZE> m_pStateStack;
		GameState*	m_pPreviousState;
		int				m_stateIndex;

		std::array<GameState*, GAME_STATES_STACK_SIZE> m_pStateStackToDelete;
		int				m_stateCountToDelete;


	public:
		

	public:
		/** Use this to get the single instance for the Platform. This function will fail if the
		* previous instance is not deleted => You cannot have two different instances at a same time.
		* @return a shared_ptr for Platform */
		static std::shared_ptr<StateStack> CreateSingleInstance();

	protected:
		StateStack();
	
		virtual ~StateStack();

	protected:

	private:
		static std::weak_ptr<StateStack> s_instance;
		static std::mutex s_mutex;
	};	

	/** This deleter class is a helper to allow the shared_ptr to access private destructors */
	class StateStackDeleter
	{
	public:
		void operator()(StateStack* p);
	};
} //namespace gll


#endif //_STATES_STACH_H_