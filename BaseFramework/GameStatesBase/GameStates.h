
#ifndef _GAME_STATES_H_
#define _GAME_STATES_H_

#include <memory>

////////////////////////////////////////////////////////////////////////////////////////////////////
//	Base class for all game states
namespace gs
{
	class GameState 
	{
        friend class StatesStack;
	public:
        /** Constructor */
        GameState();
			
        /** Destructor. To be over-ride by a derived class. */
		virtual ~GameState();

        /** isKindOf - return  state type. * To be over-ride by a derived class.
        * @param is an int.
        * @return a boolean.*/
		virtual bool isKindOf(int);

        /** Create - init resources relevant to this state. Is is called each time you enter this state.
        * To be over-ride by a derived class.
        * @return an int, 0 .*/
		virtual int Create();

        /** Release - release resources relevant to this state. Is is called each time you leave the state.
        * To be over-ride by a derived class. */
		virtual void Release();				
			
        /** Update - updates the game state.  To be implemented by a derived class.
        * @param long is the time passed from the last call. */
		virtual void Update(float) = 0;

        /** Render - draw the game state.
        * To be implemented by a derived class.*/
		virtual void Render() = 0;  

        /** Pause - pause this state from an interrupt or when coming back from a state.
        * To be over-ride by a derived class. */
		virtual void Pause();

        /** Release - resumes this state from an interrupt or when coming back from a state.
        * To be over-ride by a derived class. */
		virtual void Resume();
			
        /** OnEvent - receive events if this instance was registered as a event listener.
        * To be over-ride by a derived class.
        * @param event is a reference to a glf::CoreEvent.
        * @return a boolean. */
		//virtual bool OnEvent(const glf::CoreEvent& event) override;

        /** SwitchOrientation - switch the orientation.
        * To be over-ride by a derived class.*/
		virtual void SwitchOrientation();

        /** OnVirtualKeyboardClosed - 
        * To be over-ride by a derived class. */
		virtual void OnVirtualKeyboardClosed();

        /** SetParent - set the parent of the game state.
        * @param parent is a pointer to GameState, is the parent to be set to game state.*/
        void SetParent(std::shared_ptr<GameState>	parent)	{ m_pParent = parent;};

        /** GetParent - get the parent of the GameState.
        * @param level is an integer representing the parent level 
        * @return a pointer to the parent GameState, if it exists, else return NULL.*/
		std::shared_ptr<GameState> GetParent( int level = 0) ;

        /** ResetControls - reset the controls */
		void ResetControls();

        /** Load - this function is called when a state is initialized. 
        * This function will be called each frame until returns false.
        * To be over-ride by a derived class.
        * @return a boolean  true if loading is in progress; false if the loading ends. */
		virtual bool Load();

        /** IsLoading
		* @return a boolean, true if state is loading, false if is not. */
		bool IsLoading() {return m_bStateLoading; };

        /** SetLoading - set the m_bStateLoading. 
        * @param loading is a boolean that will set m_bStateLoading. */
		void SetLoading( bool loading ) { m_bStateLoading = loading; };


        /** Return true if the Create function was called with success.
        *  All the stuff (pointers, values, etc...) needed by this state must be initialised on Create.
        *  Do not load anything on Create. For loading, use Load() function.
        * Return false if this state was popped and Release() function was called.
        * @return true or false depending of m_bReady member. */
        inline bool IsReady() { return m_bReady; };


    protected:
		
		std::shared_ptr<GameState> m_pParent;

		bool m_bStateLoading;


    private:
        /** Used to specify if this state is initialized and can be used. */
        bool m_bReady;

        /** Used internally to set if this state is ready or not.
        * @param true or false. */
        inline void SetReady(bool ready) { m_bReady = ready; };

	};
}

////////////////////////////////////////////////////////////////////////////////////////////////////

#endif	//_GAME_STATES_H_