module;
#include <execution>
#include <span>
#include <string>
#include <string_view>
#include <type_traits>

export module acm_concept;

namespace ACM {
export
template<typename _Ty>
concept kmp_string_concept = std::ranges::sized_range<_Ty> && std::ranges::contiguous_range<_Ty> && !std::is_pointer_v<std::ranges::range_value_t<_Ty>>;// 还需要有 operator==

export
template<typename _Ty>
concept execution_policy_concept = std::is_execution_policy_v<std::remove_cvref_t<_Ty>>;

export
template<typename _Ty>
concept char_concept = std::is_same_v<_Ty, char> || std::is_same_v<_Ty, wchar_t> || std::is_same_v<_Ty, char8_t> || std::is_same_v<_Ty, char16_t> || std::is_same_v<_Ty, char32_t>;

export
template<typename _Ty>
concept string_view_concept = std::is_same_v<_Ty, std::string_view> || std::is_same_v<_Ty, std::wstring_view> || std::is_same_v<_Ty, std::u8string_view> || std::is_same_v<_Ty, std::u16string_view> || std::is_same_v<_Ty, std::u32string_view>;

export
template<typename _Ty>
concept span_concept = std::is_same_v<std::span<std::ranges::range_value_t<_Ty>>, _Ty>;

export
template<typename _Ty>
concept not_char_concept = !char_concept<_Ty>;
}
