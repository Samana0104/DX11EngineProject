#pragma once
#include "Transition.h"

namespace HBSoft
{
#define TEMPLATE_SE template <typename S, typename E>

    template <typename S, typename E>
    class FiniteStateM
    {
    private:
        std::map<S, std::shared_ptr<Transition<S, E>>> m_states;

    public:
        FiniteStateM() = default;

        bool    AddTransition(const S inState, const E event, const S outState);
        const S GetTransition(const S inState, const E event) const;

        const FiniteStateM<S, E>& operator[](const S _inState) const;
    };

    TEMPLATE_SE
    inline bool FiniteStateM<S, E>::AddTransition(const S inState, const E event,
                                                  const S outState)
    {
        if (m_states.contains(inState))
        {
            return m_states[inState]->AddEventTransition(event, outState);
        }
        else
        {
            auto state = std::make_shared<Transition<S, E>>();
            state->Add(event, outState);
            return m_states.insert(std::make_pair(inState, state)).second;
        }
    }

    TEMPLATE_SE
    inline const S FiniteStateM<S, E>::GetTransition(const S inState, const E event) const
    {
        if (m_states.contains(inState))
        {
            return m_states[inState]->Get(event);
        }
        else
        {
            MessageBoxA(NULL, "Not exist id", "[FiniteState id error]", MB_OK);
            return NULL;
        }
    }

    TEMPLATE_SE
    inline const FiniteStateM<S, E>& FiniteStateM<S, E>::operator[](const S inState) const
    {
        return *(m_states.at(inState));
    }
}  // namespace HBSoft
