#pragma once

namespace MyProject
{
	template < typename T >
	class Singleton
	{
		Singleton(const Singleton&) = delete;
		Singleton(Singleton&&) = delete;
		Singleton& operator=(const Singleton&) = delete;
		Singleton& operator=(Singleton&&) = delete;

	protected:
		Singleton() = default;

	public:
		static T& GetInstance()
		{
			static T _singleton;
			return _singleton;
		}
	};
}

