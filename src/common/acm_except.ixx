module;
#include <stdexcept>
#include <string_view>

export module acm_except;

namespace ACM {
export
enum class acm_exception_type {
    INVALID = 0,
    NOT_IMPLEMENTED,
};

export
class acm_exception : public std::runtime_error {
public:
    explicit acm_exception(std::string_view _Msg_) : std::runtime_error(_Msg_.data()), type_(acm_exception_type::INVALID) {}

    acm_exception(acm_exception_type _Type_, std::string_view _Msg_) : std::runtime_error(_Msg_.data()), type_(_Type_) {}

private:
    acm_exception_type type_;
};
}
