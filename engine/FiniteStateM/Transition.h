#pragma once
#include "CoreAPI.h"

namespace HBSoft
{
#define TEMPLATE_SE template <typename S, typename E>

    template <typename S, typename E>
    class Transition
    {
    private:
        std::map<E, S> m_finiteState;

    public:
        Transition() = default;

        bool    Add(const E event, const S outState);
        const S Get(const E event) const;
        const S operator[](const E _event) const;
    };

    TEMPLATE_SE
    inline bool Transition<S, E>::Add(const E event, const S outState)
    {
        return m_finiteState.insert(std::make_pair(event, outState)).second;
    }

    TEMPLATE_SE
    inline const S Transition<S, E>::Get(const E event) const
    {
        if (m_finiteState.contains(event))
        {
            return m_finiteState[event];
        }
        else
        {
            MessageBoxA(NULL, "Not exist id", "[FiniteState id error]", MB_OK);
            return NULL;
        }
    }

    TEMPLATE_SE
    inline const S Transition<S, E>::operator[](const E event) const
    {
        return m_finiteState.at(event);
    }
}  // namespace HBSoft
