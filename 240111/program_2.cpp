#include <type_traits>
template <typename... Args>
struct Pack {};

template <typename T, typename... Args>
struct Contains {};

template <typename T, typename... Args>
struct Contains<T, Pack<Args...>> {
    constexpr static bool value = (std::is_same_v<T, Args> || ...); 
};

template <typename Pack1, typename Pack2>
struct Is_Subset {};

template <typename... Args1, typename... Args2>
struct Is_Subset<Pack<Args1...>, Pack<Args2...>> {
    constexpr static bool value = (Contains<Args1, Pack<Args2...>>::value && ...);
};

template <typename Pack1, typename Pack2>
struct Are_Equal {};

template <typename... Args1, typename... Args2>
struct Are_Equal<Pack<Args1...>, Pack<Args2...>> {
    constexpr static bool value = (Is_Subset<Pack<Args1...>, Pack<Args2...>>::value 
                                        && Is_Subset<Pack<Args2...>, Pack<Args1...>>::value);
};




int main()
{
    using List = Pack<char, double, bool, int, bool, char>;

    static_assert( Contains<int, List>::value );
    static_assert( !Contains<unsigned, List>::value );

    static_assert( Is_Subset<Pack<int, char>, List>::value );
    static_assert( !Is_Subset<Pack<int, char, float>, List>::value );

    static_assert( Are_Equal<List, List>::value );
    static_assert( !Are_Equal<Pack<int, char>, List>::value );
}