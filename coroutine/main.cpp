#include <coroutine>
#include <iostream>
#include <memory>

template<typename T>
struct MyFuture
{
	MyFuture(std::shared_ptr<T> p): value(p) {}
	~MyFuture(){}
	
	T get()
	{
		return *value;
	}
	
	std::shared_ptr<T> value;
	
	struct promise_type
	{
		~promise_type(){}
		
		MyFuture<T> get_return_object()
		{
			return ptr;
		}
		
		void return_value(T v)
		{
			*ptr = v;
		}
		
		std::suspend_never initial_suspend()
		{
			return {};
		}
		
		std::suspend_never final_suspend() noexcept
		{
			return {};
		}
		
		void unhandled_exception()
		{
			std::exit(1);
		}
		
		std::shared_ptr<T> ptr = std::make_shared<T>();		
	};
};

MyFuture<int> createFuture()
{
	co_return 2021;
}

int main()
{
	std::cout << std::endl;
	
	auto fut = createFuture();
	std::cout << "fut.get():" << fut.get() << std::endl;
	
	std::cout << std::endl;

}