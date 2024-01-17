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
    explicit acm_exception(std::string_view msg) : std::runtime_error(msg.data()), type_(acm_exception_type::INVALID) {}

    acm_exception(acm_exception_type type, std::string_view msg) : std::runtime_error(msg.data()), type_(type) {}

private:
    acm_exception_type type_;
};
}
