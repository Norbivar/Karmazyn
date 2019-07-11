#pragma once
#include <stack>
#include <memory>
#include <exception>
#include <string>

namespace Karmazyn
{
	// Helper class, providing a safer top() behaviour, that is guaranteed to return a valid reference.
	class IGameState; class Engine;

	class InvalidStateMachineTransitionException : public std::exception
	{
	public:
		InvalidStateMachineTransitionException(const std::string& message) : m_Message(message) { }
		const char* what() const throw ()
		{
			return m_Message.c_str();
		}
	private:
		std::string m_Message;
	};

	class GameStateMachine
	{
	public:
		GameStateMachine(Engine& engine);
		~GameStateMachine();

		// Instantiates a new state of the type TargetState. The TargetState will be constructed with forwarded arguments ('args').
		// Then it swaps the CurrentState with the new state and pushes the old state to the top of the History stack.
		template<typename TargetState, typename... ConstructorArgs>
		void transition(ConstructorArgs&&... args)
		{
			static_assert(std::is_base_of_v<IGameState, TargetState>, "GameStateMachine::transition were called with a class that does not inherit from IGameState.");

			if(m_CurrentState)
				m_CurrentState->beforeTransitionedOut();

			std::unique_ptr<IGameState> holder = std::make_unique<TargetState>(theEngine, std::forward<ConstructorArgs>(args)...);
			m_CurrentState.swap(holder);
			if(holder)
				m_HitStates.emplace(std::move(holder));

			m_CurrentState->afterTransitionedIn();
		}

		// Creates a new TargetState and jumps to it (assigns it to CurrentState). This will never save the old state. I did it this way because I don't know whether variadic arguments
		// support optional parameters after them. Probably not. 
		template<typename TargetState, typename... ConstructorArgs>
		void jump(ConstructorArgs&&... args)
		{
			std::unique_ptr<IGameState> holder = std::make_unique<TargetState>(theEngine, std::forward<ConstructorArgs>(args)...);
			m_CurrentState.swap(holder);
		}

		// Pops the top of the stack and restores it to being the CurrentState. 
		// This will also discard the old CurrentState.
		void transitionBack();

		// Clears the History stack.
		void clearHistory();

		// Returns the GameState that is currently in "focus".
		IGameState& current() { return *m_CurrentState; }
	private:
		Engine& theEngine;

		std::unique_ptr<IGameState> m_CurrentState;
		std::stack<std::unique_ptr<IGameState>> m_HitStates;
	};
}