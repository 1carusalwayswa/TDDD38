#include <utility>
#include <cassert>
#include <iostream>

template <typename T>
class Function {};

template <typename Ret, typename... Args>
class Function<Ret(Args...)> {
public:
	class Base_Implementation {      
	public:
		virtual Ret perform(Args...) = 0;

		virtual ~Base_Implementation() {};
	};
	
	template <typename T>
	class Implementation : public Base_Implementation {
	public:
		T function;

		Implementation(T function_) : function(function_) {}

		Ret perform(Args... args) override {
			return function(args...);
		}

		~Implementation() {};
	};
	
	Function() = default;

	Base_Implementation *impl {nullptr};
	template <typename T>
	Function(T&& t) {
		impl = new Implementation<T>(std::forward<T>(t));
	}

	Ret operator()(Args... args) {
		return impl->perform(args...);
	}

	template <typename T>
	Base_Implementation* operator=(T&& t) {
		impl = new Implementation<T>(std::forward<T>(t));
		return impl;
	}

	~Function() {
		if (impl != nullptr) {
			delete impl;
		}
	}
};


void test()
{
    std::cout << "Function call!" << std::endl;
}

int add(int a, int b)
{
    return a + b;
}

struct Test
{
    void operator()()
    {
	std::cout << "Function object call!" << std::endl;
    }
};

struct Multiply
{
    int operator()(int a, int b)
    {
	return a * b;
    }
};

/* Expected output:

==== Testcase 1: void() ====
Function call!
Function object call!
x = 5
==== Testcase 2: int(int, int) ====
7 * 4 = 28
3 + 5 = 8
11 - 5 = 6

*/
// 定义 Function 类型别名
// template <typename Ret, typename... Args>
// using Function = Callable<Ret(Args...)>;

int main()
{

    std::cout << "==== Testcase 1: void() ====" << std::endl;
    {
	Function<void()> fun { test };
	fun();

	fun = Test{};
	fun();
	
	int x { 5 };
	fun = [&x]() { std::cout << "x = " << x << std::endl; };
	fun();
    }

    std::cout << "==== Testcase 2: int(int, int) ====" << std::endl;
    {
	Function<int(int, int)> fun;

	fun = add;
	std::cout << "3 + 5 = " << fun(3, 5) << std::endl;

	fun = [](int a, int b) { return a - b; };
	std::cout << "11 - 5 = " << fun(11, 5) << std::endl;

	fun = Multiply{};
	std::cout << "7 * 4 = " << fun(7, 4) << std::endl;
    }
}