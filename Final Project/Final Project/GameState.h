#pragma once
static enum GameState
{
    MENU,
    GAME,
    PAUSED
};

struct State
{
public:
    static GameState GetCurrentState() 
    {
        return currentState;
    }

    static void SetCurrentState(GameState state)
    {
        currentState = state;
    }

  
private:

     static GameState currentState;
};
