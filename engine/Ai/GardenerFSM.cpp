#include "pch.h"
#include "GardenerFSM.h"

void HBSoft::GardenerFSM::onEvent(Event event)
{
    switch (currentState)
    {
    case State::Idle:
        if (event == Event::GooseClose)
        {
            // 여기다 행동
            currentState = State::Pushing;
        }
        else if (event == Event::GooseStoleItem)
        {
            // 여기다 행동
            currentState = State::Chasing;
        }
        break;

    case State::Pushing:
        if (event == Event::GooseFar)
        {
            // 여기다 행동
            currentState = State::Idle;
        }
        else if (event == Event::GooseStoleItem)
        {
            // 여기다 행동

            currentState = State::Chasing;
        }
        break;
    }
}
