#pragma once
#include "MyCoreAPI.h"

namespace MyProject
{
	#define TEMPLATE_SE template < typename S, typename E >

	template < typename S, typename E >
	class MyFiniteState
	{
	private:
		std::map<E, S> mFiniteState;

	public:
		MyFiniteState() = default;

		bool AddEventTransition(const E _event, const S _outState);
		const S GetTransition(const E _event) const;
		const S operator[](const E _event) const;
	};


	TEMPLATE_SE
	inline bool MyFiniteState<S, E>::AddEventTransition(const E _event, const S _outState)
	{
		return mFiniteState.insert(std::make_pair(_event, _outState)).second;
	}

	TEMPLATE_SE
	inline const S MyFiniteState<S, E>::GetTransition(const E _event) const
	{
		if (mFiniteState.contains(_event))
		{
			return mFiniteState[_event];
		}
		else
		{
			MessageBoxA(NULL, "Not exist id", "[FiniteState id error]", MB_OK);
			return NULL;
		}
	}

	TEMPLATE_SE
	inline const S MyFiniteState<S, E>::operator[](const E _event) const
	{
		return mFiniteState.at(_event);
	}
}
