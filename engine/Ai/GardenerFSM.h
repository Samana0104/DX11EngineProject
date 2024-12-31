#pragma once

#include "pch.h"
#include "Core.h"

namespace HBSoft
{
    enum struct State
    {
        Idle,
        Chasing,
        Pushing,
    };

    enum struct Event
    {
        GooseClose,
        GooseStoleItem,
        GooseFar,
    };

    class GardenerFSM
    {
    private:
        State currentState;

    public:
        GardenerFSM()
            : currentState(State::Idle)
        {}

        void onEvent(Event event);
    };
}  // namespace HBSoft