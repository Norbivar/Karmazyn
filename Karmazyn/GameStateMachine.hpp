#pragma once
#include <stack>
#include <memory>

namespace Karmazyn
{
	// Helper class, providing a safer top() behaviour, that is guaranteed to return a valid reference.
	class IGameState; class GameEngine;

	class GameStateMachine
	{
	public:
		GameStateMachine(GameEngine& engine);
		~GameStateMachine();

		// Instantiates a new state of the type TargetState with forwarded construction arguments. 
		// Then it swaps the CurrentState with the new state and pushes the old state to the top of the History stack.
		template<typename TargetState, typename... ConstructorArgs>
		void transition(ConstructorArgs&&... args)
		{
			std::unique_ptr<IGameState> holder = std::make_unique<TargetState>(theEngine, std::forward<ConstructorArgs>(args)...);
			m_CurrentState.swap(holder);
			if(holder)
				m_HitStates.emplace(std::move(holder));
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

		IGameState& current() { return *m_CurrentState; }
	private:
		GameEngine& theEngine;

		std::unique_ptr<IGameState> m_CurrentState;
		std::stack<std::unique_ptr<IGameState>> m_HitStates;
	};
}