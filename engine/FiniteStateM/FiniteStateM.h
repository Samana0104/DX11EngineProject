#pragma once
#include "Transition.h"

namespace HBSoft
{
#define TEMPLATE_SE template <typename S, typename E>

    template <typename S, typename E>
    class FiniteStateM
    {
    private:
        std::map<S, std::shared_ptr<MyFiniteState<S, E>>> mFSM;

    public:
        FiniteStateM() = default;

        bool    AddEventTransition(const S _inState, const E _event, const S _outState);
        const S GetTransition(const S _inState, const E _event) const;

        const MyFiniteState<S, E>& operator[](const S _inState) const;
    };

    TEMPLATE_SE
    inline bool FiniteStateM<S, E>::AddEventTransition(const S _inState, const E _event,
                                                       const S _outState)
    {
        if (mFSM.contains(_inState))
        {
            return mFSM[_inState]->AddEventTransition(_event, _outState);
        }
        else
        {
            auto state = std::make_shared<MyFiniteState<S, E>>();
            state->AddEventTransition(_event, _outState);
            return mFSM.insert(std::make_pair(_inState, state)).second;
        }
    }

    TEMPLATE_SE
    inline const S FiniteStateM<S, E>::GetTransition(const S _inState, const E _event) const
    {
        if (mFSM.contains(_inState))
        {
            return mFSM[_inState]->GetTransition(_event);
        }
        else
        {
            MessageBoxA(NULL, "Not exist id", "[FSM id error]", MB_OK);
            return NULL;
        }
    }

    TEMPLATE_SE
    inline const MyFiniteState<S, E>& FiniteStateM<S, E>::operator[](const S _inState) const
    {
        return *mFSM.at(_inState);
    }
}  // namespace HBSoft
