// kmp 测试
import kmp;
#include <chrono>
#include <execution>
#include <print>
#include <random>
#include <vector>

#include "gtest/gtest.h"

using namespace std::literals;

TEST(kmpTEST, test0) {
    ACM::kmp m_kmp0{ "asdasdasd","asd" };
    ACM::kmp m_kmp0_0{ std::execution::seq ,"asdasdasd","asd" };
    ACM::kmp m_kmp0_1{ std::execution::par ,"asdasdasd","asd" };
    ACM::kmp m_kmp0_2{ std::execution::unseq ,"asdasdasd","asd" };
    ACM::kmp m_kmp0_3{ std::execution::par_unseq ,"asdasdasd","asd" };

    std::string T1{ "asdasdasd" }, P1{ "asd" };
    ACM::kmp m_kmp1{ T1,P1 };
    ACM::kmp m_kmp1_0{ std::execution::seq, T1,P1 };
    ACM::kmp m_kmp1_1{ std::execution::par, T1,P1 };
    ACM::kmp m_kmp1_2{ std::execution::unseq, T1,P1 };
    ACM::kmp m_kmp1_3{ std::execution::par_unseq, T1,P1 };

    std::vector T2{ 1,2,3,1,2,3,1,2,3 }, P2{ 1,2,3 };
    ACM::kmp m_kmp2{ T2,P2 };
    ACM::kmp m_kmp2_0{ std::execution::seq, T2,P2 };
    ACM::kmp m_kmp2_1{ std::execution::par, T2,P2 };
    ACM::kmp m_kmp2_2{ std::execution::unseq, T2,P2 };
    ACM::kmp m_kmp2_3{ std::execution::par_unseq, T2,P2 };

    int T3[]{ 1,2,3,1,2,3,1,2,3 }, P3[]{ 1,2,3 };
    ACM::kmp m_kmp3{ T3,P3 };
    ACM::kmp m_kmp3_0{ std::execution::seq, T3,P3 };
    ACM::kmp m_kmp3_1{ std::execution::par, T3,P3 };
    ACM::kmp m_kmp3_2{ std::execution::unseq, T3,P3 };
    ACM::kmp m_kmp3_3{ std::execution::par_unseq, T3,P3 };
}

TEST(kmpTEST, test1) {
    std::string T = "asdasdasd", P = "asd";
    ACM::kmp m_kmp{ T,P };
    std::println("T = {}\nP = {}", T, P);
    auto f = m_kmp.f();// std::span<int>
    std::print("f: ");
    for (auto it = std::begin(f); it != std::end(f);) {
        std::print("{}", *it);
        std::print("{}", " \n"[++it == std::end(f)]);
    }
    std::vector<int> exp_f{ 1,2,3,1,2,3,1,2,3 };
    auto match_pair_f = std::ranges::mismatch(f, exp_f);
    ASSERT_EQ(std::end(f), match_pair_f.in1);
    ASSERT_EQ(std::end(exp_f), match_pair_f.in2);

    auto nxt = m_kmp.nxt();
    std::print("nxt: ");
    for (auto it = std::begin(nxt); it != std::end(nxt);) {
        std::print("{}", *it);
        std::print("{}", " \n"[++it == std::end(nxt)]);
    }
    std::vector<int> exp_nxt{ 0,0,0 };
    auto match_pair_nxt = std::ranges::mismatch(nxt, exp_nxt);
    ASSERT_EQ(std::end(nxt), match_pair_nxt.in1);
    ASSERT_EQ(std::end(exp_nxt), match_pair_nxt.in2);
}

TEST(kmpTEST, test2) {
    std::random_device r;
    std::default_random_engine rng(r());
    std::uniform_int_distribution uniform_dist(65, 71);// 'A'->'G'
    std::string T, P;
    int T_size = 50000000;
    int P_size = 25000000;
    T.resize(T_size);
    P.resize(P_size);
    int times = 10;
    while (times--) {
        for (char& i : T) {
            i = uniform_dist(rng);
        }
        for (char& i : P) {
            i = uniform_dist(rng);
        }

        std::chrono::time_point s{ std::chrono::steady_clock::now() };
        ACM::kmp m_kmp{ std::execution::seq,T,P };
        std::chrono::time_point e{ std::chrono::steady_clock::now() };
        std::println("非并发版本：{}", std::chrono::duration_cast<std::chrono::milliseconds>(e - s));

        std::this_thread::sleep_for(500ms);

        s = std::chrono::steady_clock::now();
        ACM::kmp m_kmp2{ std::execution::par,T,P };
        e = std::chrono::steady_clock::now();
        std::println("并发版本：{}", std::chrono::duration_cast<std::chrono::milliseconds>(e - s));
        std::println("********************************");

        auto nxt = m_kmp.nxt();
        auto nxt2 = m_kmp2.nxt();
        for (auto it = std::begin(nxt), it2 = std::begin(nxt2); it != std::end(nxt) && it2 != std::end(nxt2); ++it, ++it2) {
            ASSERT_EQ(*it, *it2);
        }

        auto f = m_kmp.f();
        auto f2 = m_kmp2.f();
        for (auto it = std::begin(f), it2 = std::begin(f2); it != std::end(f) && it2 != std::end(f2); ++it, ++it2) {
            ASSERT_EQ(*it, *it2);
        }
    }
}
