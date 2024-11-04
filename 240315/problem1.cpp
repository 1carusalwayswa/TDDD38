#include <type_traits>

// TODO: implement extract_type
template <size_t N, typename T, typename... Args>
struct extract_type {
    using type = extract_type<N - 1, Args...>::type;
};

template <typename T, typename... Args>
struct extract_type<0, T, Args...> {
    using type = T;
};

template <typename Ret, typename... Args>
struct callable_info_base
{
    using return_type = Ret;

    template <std::size_t N>
    using parameter_type = typename extract_type<N, Args...>::type;

    static constexpr std::size_t parameter_count { sizeof...(Args) };
};

template <typename Callable>
struct callable_info_helper {};

// #1: extract information from a function
template <typename Ret, typename... Args>
struct callable_info_helper<Ret(Args...)>
    : public callable_info_base<Ret, Args...> {};

// #2: extract information from a function pointer
template <typename Ret, typename... Args>
struct callable_info_helper<Ret(*)(Args...)>
    : public callable_info_base<Ret, Args...> {};

// #3: extract info from a non-const member function
template <typename Callable, typename Ret, typename... Args>
struct callable_info_helper<Ret (Callable::*)(Args...)>
    : public callable_info_base<Ret, Args...> {};

// #4: extract info from a const member function
template <typename Callable, typename Ret, typename... Args>
struct callable_info_helper<Ret (Callable::*)(Args...) const>
    : public callable_info_base<Ret, Args...> {};

// TODO: Implement get_callable_info
template <typename T>
callable_info_helper<decltype(&T::operator())> get_callable_info(int);

template <typename T>
callable_info_helper<T> get_callable_info(float);

template <typename T>
using callable_info = decltype(get_callable_info<T>(0));

/*** testcases ***/

void fun(int, float);

struct X
{
    int operator()(X&);
};

struct Y
{
    Y& operator()(char, float) const;
};

int main()
{
    using function_t = callable_info<decltype( fun )>;
    static_assert( std::is_same_v< function_t::return_type, void > );
    static_assert( std::is_same_v< function_t::parameter_type<0>, int > );
    static_assert( std::is_same_v< function_t::parameter_type<1>, float > );
    static_assert( function_t::parameter_count == 2 );

    using functor_t = callable_info<X>;
    static_assert( std::is_same_v< functor_t::return_type, int > );
    static_assert( std::is_same_v< functor_t::parameter_type<0>, X& > );
    static_assert( functor_t::parameter_count == 1 );
    
    using const_functor_t = callable_info<Y>;
    static_assert( std::is_same_v< const_functor_t::return_type, Y& > );
    static_assert( std::is_same_v< const_functor_t::parameter_type<0>, char > );
    static_assert( std::is_same_v< const_functor_t::parameter_type<1>, float > );
    static_assert( const_functor_t::parameter_count == 2 );

    auto lambda = [](int, int, int) { return 0; };
    using lambda_t = callable_info< decltype( lambda ) >;
    static_assert( std::is_same_v< lambda_t::return_type, int > );
    static_assert( std::is_same_v< lambda_t::parameter_type<0>, int > );
    static_assert( std::is_same_v< lambda_t::parameter_type<1>, int > );
    static_assert( std::is_same_v< lambda_t::parameter_type<2>, int > );
    static_assert( lambda_t::parameter_count == 3 );
}