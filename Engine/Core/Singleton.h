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
		static inline T* singleton = nullptr;
		static inline bool isConstructed = false; // template마다 생성되는 static이 다름

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
			if (!isConstructed)
			{
				singleton = new T;
				isConstructed = true;
			}

			return *singleton;
		}

		static void Release()
		{
			if(singleton != nullptr)
				delete singleton;
		}
	};
}

