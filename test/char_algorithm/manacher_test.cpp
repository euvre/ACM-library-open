// manacher测试
import manacher;

#include "gtest/gtest.h"
#include <print>

TEST(manacherTEST, test0) {
    std::string str{"asasasa"};
    ACM::manacher m_manacher{ str };
    std::println("{}", m_manacher.ans_);
    ASSERT_EQ(7, m_manacher.ans_);
}