// kmp 模板
module;
#include <atomic>
#include <execution>
#include <span>
#include <string>
#include <string_view>
#include <thread>
#include <type_traits>
#include <vector>

export module kmp;
import acm_except;
import acm_concept;

namespace ACM {
// 已知缺陷：当 std::is_floating_v<std::remove_cvref_v<_Ty>> == true 时，程序可能无法达到预期的效果。
export
template<execution_policy_concept _Op, kmp_string_concept _Ty1, kmp_string_concept _Ty2>
    // requires std::is_same_v<_Ty1, _Ty2>
class kmp {
    using kmp_elem = std::ranges::range_value_t<_Ty1>;
    using kmp_elem_remove_cvref = std::remove_cvref_t<kmp_elem>;
public:
    constexpr kmp(const _Op& _Exec_, const _Ty1& _T_, const _Ty2& _P_) requires string_view_concept<_Ty1> {
        // std::cout << "#string_view\n";// 是否考虑用宏来控制调试？
        init(_Exec_, _T_, _P_);
    }

    constexpr kmp(const _Op& _Exec_, const _Ty1& _T_, const _Ty2& _P_) requires span_concept<_Ty1> {
        // std::cout << "#span\n";
        init(_Exec_, _T_, _P_);
    }

    constexpr kmp(const _Ty1& _T_, const _Ty2& _P_) requires string_view_concept<_Ty1> :kmp(std::execution::seq, _T_, _P_) {}

    constexpr kmp(const _Ty1& _T_, const _Ty2& _P_) requires span_concept<_Ty1> : kmp(std::execution::seq, _T_, _P_) {}

    // @brief 获得 nxt 数组的视图
    constexpr auto nxt() const -> std::span<const std::size_t> {
        return nxt_;
    }

    // @brief 获得 f 数组的视图
    constexpr auto f() const -> std::span<const std::size_t> {
        return f_;
    }

private:
    template<typename _Uy1, typename _Uy2>
    constexpr void init(const _Op& _Exec_, const _Uy1& _T_, const _Uy2& _P_) {
        static_assert(std::is_same_v<std::ranges::range_value_t<_Ty1>, std::ranges::range_value_t<_Ty2>>, "kmp类要求两范围中，值的类型相同。");
        std::size_t T_len = _T_.size(), P_len = _P_.size();
        if constexpr (std::is_same_v<_Op, std::execution::parallel_policy>) {
            f_.resize(T_len);
            nxt_.resize(P_len);
            std::jthread t1{ &kmp::cacl_nxt_mult, this, _P_ };
            std::jthread t2{ &kmp::cacl_f_mult, this ,_T_, _P_ };
        } else {
            nxt_.resize(P_len);
            f_.resize(T_len);
            cacl_nxt(_P_);
            cacl_f(_T_, _P_);
        }
    }

    // @brief 计算 nxt 数组
    // @param T：文本串；P：模式串
    // @return 无
    constexpr void cacl_nxt(const _Ty2& _P_) {
        std::size_t P_len = _P_.size();
        // nxt_[0] = 0;
        for (std::size_t i = 1, j = 0; i <= P_len - 1; ++i) {
            while (j > 0 && _P_[i] != _P_[j]) {
                j = nxt_[j - 1];
            }
            if (_P_[i] == _P_[j]) {
                ++j;
            }
            nxt_[i] = j;
        }
    }

    // @brief KMP 工作函数
    // @param T：文本串；P：模式串
    // @return 无
    constexpr void cacl_f(const _Ty1& _T_, const _Ty2& _P_) {
        std::size_t T_len = _T_.size(), P_len = _P_.size();
        for (std::size_t i = 0, j = 0; i <= T_len - 1; ++i) {
            while (j > 0 && (j == P_len || _T_[i] != _P_[j])) {
                j = nxt_[j - 1];
            }
            if (_T_[i] == _P_[j]) {
                ++j;
            }
            f_[i] = j;
        }
    }

    // @brief 计算 nxt 数组，并发版本
    // @param T：文本串；P：模式串
    // @return 无
    constexpr void cacl_nxt_mult(const _Ty2& _P_) {
        std::size_t P_len = _P_.size();
        // nxt_[0] = 0;
        for (std::size_t i = 1, j = 0; i <= P_len - 1; ++i) {
            while (j > 0 && _P_[i] != _P_[j]) {
                j = nxt_[j - 1];
            }
            if (_P_[i] == _P_[j]) {
                ++j;
            }
            nxt_[i] = j;
            nxt_cnt_.fetch_add(1, std::memory_order_release);// A
        }
    }

    // @brief 计算 f 数组，并发版本
    // @param T：文本串；P：模式串
    // @return 无
    constexpr void cacl_f_mult(const _Ty1& _T_, const _Ty2& _P_) {
        // 在高代数intel（12代+）处理器上，似乎有劣化的迹象；在低代数intel处理器上，优化效果立竿见影。
        std::size_t T_len = _T_.size(), P_len = _P_.size();
        for (std::size_t i = 0, j = 0; i <= T_len - 1; ++i) {
            while (j > 0 && (j == P_len || _T_[i] != _P_[j])) {
                while (j - 1 > nxt_cnt_.load(std::memory_order_acquire));// B
                j = nxt_[j - 1];
            }
            if (_T_[i] == _P_[j]) {
                ++j;
            }
            f_[i] = j;
        }
    }

    std::vector<std::size_t> f_, nxt_;
    std::atomic<std::size_t> nxt_cnt_{ 0 };
};

template<typename _Ty1, typename _Ty2>
kmp(std::basic_string<_Ty1>, std::basic_string<_Ty2>) -> kmp<std::execution::sequenced_policy, std::basic_string_view<_Ty1>, std::basic_string_view<_Ty2>>;

template<execution_policy_concept _Op, typename _Ty1, typename _Ty2>
kmp(_Op, std::basic_string<_Ty1>, std::basic_string<_Ty2>) -> kmp<_Op, std::basic_string_view<_Ty1>, std::basic_string_view<_Ty2>>;

template<std::ranges::contiguous_range _Ty1, std::ranges::contiguous_range _Ty2>
kmp(_Ty1, _Ty2) -> kmp<std::execution::sequenced_policy, std::span<std::ranges::range_value_t<_Ty1>>, std::span<std::ranges::range_value_t<_Ty2>>>;

template<execution_policy_concept _Op, std::ranges::contiguous_range _Ty1, std::ranges::contiguous_range _Ty2>
kmp(_Op, _Ty1, _Ty2) -> kmp<_Op, std::span<std::ranges::range_value_t<_Ty1>>, std::span<std::ranges::range_value_t<_Ty2>>>;

template<char_concept _Ty1, std::size_t N1, char_concept _Ty2, std::size_t N2>
kmp(const _Ty1(&arr1)[N1], const _Ty2(&arr2)[N2]) -> kmp<std::execution::sequenced_policy, std::basic_string_view<_Ty1>, std::basic_string_view<_Ty2>>;

template<execution_policy_concept _Op, char_concept _Ty1, std::size_t N1, char_concept _Ty2, std::size_t N2>
kmp(_Op, const _Ty1(&arr1)[N1], const _Ty2(&arr2)[N2]) -> kmp<_Op, std::basic_string_view<_Ty1>, std::basic_string_view<_Ty2>>;

template<not_char_concept _Ty1, std::size_t N1, not_char_concept _Ty2, std::size_t N2>
kmp(const _Ty1(&arr1)[N1], const _Ty2(&arr2)[N2]) -> kmp<std::execution::sequenced_policy, std::span<_Ty1>, std::span<_Ty2>>;

template<execution_policy_concept _Op, not_char_concept _Ty1, std::size_t N1, not_char_concept _Ty2, std::size_t N2>
kmp(_Op, const _Ty1(&arr1)[N1], const _Ty2(&arr2)[N2]) -> kmp<_Op, std::span<_Ty1>, std::span<_Ty2>>;
}
