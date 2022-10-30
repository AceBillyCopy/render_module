module;
#include <concepts>
#include <vector>
#include "GLFW/glfw3.h"
// ace concepts;
export module common.aconcepts;

template<typename...Argus>
struct Tuple{};

template<typename Func>
struct GetFuncArguments;
template<typename ReturnType, typename... Argus>
struct GetFuncArguments<ReturnType(*)(Argus...)> {
    using arguments = Tuple<Argus...>;
};

template<typename Func, typename...Argus>
concept Callable_simple = requires (Func func, Argus...argus) {
    func(argus...);
};
template<typename Func, typename...Argus>
requires Callable_simple<Func, Argus...>
void CallableType_impl(Func,Tuple<Argus...> tuple)
{};

export
template<typename Func>
concept CallableType = requires(Func func) {
    CallableType_impl(std::forward<Func>(func), typename GetFuncArguments<Func>::arguments{});
};



template<typename T, size_t N>
concept CStrLiteralType = std::same_as<T, const char*> || std::same_as<T, const char[N]>;

template<typename T>
concept CStringLiteralType_v0 = std::same_as<T, const char*>;

export
template<typename T>
concept CValidationLayerNameType = CStringLiteralType_v0<T>;

export
template<typename T>
concept CExtensionNameType = CStringLiteralType_v0<T>;
// todo: add container type constraint
export
template<typename Container>
concept CExtensionNameContainerType = requires {
    typename Container::value_type;
    requires CExtensionNameType<typename Container::value_type>; //  standard container named requirements
};

export
template<typename T>
concept CWindowHandleType = std::same_as<T, GLFWwindow>;


