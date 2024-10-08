#pragma once

namespace HBSoft
{
	/*
		�Ļ�Ŭ�������� �ݵ�� ������ ��
	private:
		friend class Singleton<T>;
		T() = default;
	*/
	template < typename T >
	class Singleton
	{
	private:
		static inline T*	singleton	  = nullptr;
		static inline bool	isConstructed = false; // template���� �����Ǵ� static�� �ٸ�

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

