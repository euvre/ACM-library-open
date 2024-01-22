// manacher模板
module;
#include<string>
#include<string_view>
#include<vector>

export module manacher;
namespace ACM {
export class manacher;
class manacher {
public:
    manacher() = default;
    explicit manacher(std::string_view _Str_) {
        init(_Str_);
        int r = 0, mid;
        for (int i = 1; i < now_.length(); ++i) {
            // l = 2 * mid - i;   l 为左端点
            PSR_[i] = i < r ? std::min(PSR_[2 * mid - i], PSR_[mid] + mid - i) : 1;// 用到了中点公式
            while (now_[i + PSR_[i]] == now_[i - PSR_[i]]) {
                // 如果以 i 为中心，以 PSR[i] 为回文半径的左右字符相等，则回文半径加 1
                ++PSR_[i];
            }
            ans_ = std::max(ans_, PSR_[i]);
            if (PSR_[i] + i > r) {
                r = PSR_[i] + i;// 扩容到新的边界
                mid = i;// 记录中心（当前的 i )
            }
        }
        --ans_;
    }
    int ans_{ 1 };

private:
    void init(std::string_view _Str_) {
        int n = _Str_.length();
        now_.resize(n * 2 + 2, '~');
        PSR_.resize(n * 2 + 2);
        for (int i = 0; i < n; ++i) {
            now_[i * 2 + 2] = _Str_[i];
        }
    }

    std::string now_;
    std::vector<int> PSR_;//Palindrome Substring Radius
};
};
