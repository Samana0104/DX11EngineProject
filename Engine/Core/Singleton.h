#pragma once

namespace MyProject
{
	/*
		파생클래스에서 반드시 선언할 것
	private:
		friend class Singleton<T>;
		T() = default;
	*/
	template < typename T >
	class Singleton
	{
	private:
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

