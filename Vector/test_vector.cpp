#include "Vector.hpp"
#include <gtest/gtest.h>
#include <string>

// 测试默认构造函数
TEST(KVectorTest, DefaultConstructor) {
    KVector<int> vec;
    EXPECT_EQ(vec.getSize(), 0);
    EXPECT_EQ(vec.getCapacity(), 0);
    EXPECT_TRUE(vec.empty());
}

// 测试初始化列表构造函数
TEST(KVectorTest, InitializerListConstructor) {
    KVector<int> vec = {1, 2, 3, 4, 5};
    EXPECT_EQ(vec.getSize(), 5);
    EXPECT_EQ(vec.getCapacity(), 7);
    EXPECT_EQ(vec[0], 1);
    EXPECT_EQ(vec[4], 5);
}

// 测试拷贝构造函数
TEST(KVectorTest, CopyConstructor) {
    KVector<int> vec1 = {1, 2, 3};
    KVector<int> vec2(vec1);
    EXPECT_EQ(vec2.getSize(), 3);
    EXPECT_EQ(vec2[0], 1);
    EXPECT_EQ(vec2[2], 3);
}

// 测试移动构造函数
TEST(KVectorTest, MoveConstructor) {
    KVector<int> vec1 = {1, 2, 3};
    KVector<int> vec2(std::move(vec1));
    EXPECT_EQ(vec2.getSize(), 3);
    EXPECT_EQ(vec2[0], 1);
    EXPECT_EQ(vec2[2], 3);
    EXPECT_EQ(vec1.getSize(), 0); // vec1 应该被移动
}

// 测试拷贝赋值运算符
TEST(KVectorTest, CopyAssignment) {
    KVector<int> vec1 = {1, 2, 3};
    KVector<int> vec2;
    vec2 = vec1;
    EXPECT_EQ(vec2.getSize(), 3);
    EXPECT_EQ(vec2[0], 1);
    EXPECT_EQ(vec2[2], 3);
}

// 测试移动赋值运算符
TEST(KVectorTest, MoveAssignment) {
    KVector<int> vec1 = {1, 2, 3};
    KVector<int> vec2;
    vec2 = std::move(vec1);
    EXPECT_EQ(vec2.getSize(), 3);
    EXPECT_EQ(vec2[0], 1);
    EXPECT_EQ(vec2[2], 3);
    EXPECT_EQ(vec1.getSize(), 0); // vec1 应该被移动
}

// 测试 push_back
TEST(KVectorTest, PushBack) {
    KVector<int> vec;
    vec.push_back(1);
    vec.push_back(2);
    vec.push_back(3);
    EXPECT_EQ(vec.getSize(), 3);
    EXPECT_EQ(vec[0], 1);
    EXPECT_EQ(vec[2], 3);
}

// 测试 pop_back
TEST(KVectorTest, PopBack) {
    KVector<int> vec = {1, 2, 3};
    vec.pop_back();
    EXPECT_EQ(vec.getSize(), 2);
    EXPECT_EQ(vec.back(), 2);
}

// 测试 at 方法
TEST(KVectorTest, AtMethod) {
    KVector<int> vec = {1, 2, 3};
    EXPECT_EQ(vec.at(0), 1);
    EXPECT_EQ(vec.at(2), 3);
    EXPECT_THROW(vec.at(3), std::out_of_range); // 测试越界访问
}

// 测试 front 和 back 方法
TEST(KVectorTest, FrontAndBack) {
    KVector<int> vec = {1, 2, 3};
    EXPECT_EQ(vec.front(), 1);
    EXPECT_EQ(vec.back(), 3);
    vec.clear();
    EXPECT_THROW(vec.front(), std::underflow_error); // 测试空向量
    EXPECT_THROW(vec.back(), std::underflow_error);  // 测试空向量
}

// 测试 operator[]
TEST(KVectorTest, SubscriptOperator) {
    KVector<int> vec = {1, 2, 3};
    EXPECT_EQ(vec[0], 1);
    EXPECT_EQ(vec[2], 3);
    EXPECT_THROW(vec[3], std::out_of_range); // 测试越界访问
}

// 测试 clear 方法
TEST(KVectorTest, ClearMethod) {
    KVector<int> vec = {1, 2, 3};
    vec.clear();
    EXPECT_EQ(vec.getSize(), 0);
    EXPECT_TRUE(vec.empty());
}

// 测试 erase 方法
TEST(KVectorTest, EraseMethod) {
    KVector<int> vec = {1, 2, 3, 4, 5};
    vec.erase(2); // 删除第三个元素（值为 3）
    EXPECT_EQ(vec.getSize(), 4);
    EXPECT_EQ(vec[2], 4);
    EXPECT_THROW(vec.erase(10), std::out_of_range); // 测试越界删除
}

// 测试 insert 方法
TEST(KVectorTest, InsertMethod) {
    KVector<int> vec = {1, 2, 4, 5};
    vec.insert(2, 3); // 在索引 2 处插入 3
    EXPECT_EQ(vec.getSize(), 5);
    EXPECT_EQ(vec[2], 3);
    EXPECT_THROW(vec.insert(10, 6), std::out_of_range); // 测试越界插入
}

// 测试 assign 方法
TEST(KVectorTest, AssignMethod) {
    KVector<int> vec = {1, 2, 3};
    vec.assign({4, 5, 6, 7});
    EXPECT_EQ(vec.getSize(), 4);
    EXPECT_EQ(vec[0], 4);
    EXPECT_EQ(vec[3], 7);
}

// 测试迭代器
TEST(KVectorTest, Iterator) {
    KVector<int> vec = {1, 2, 3};
    int sum = 0;
    for (auto it = vec.begin(); it != vec.end(); ++it) {
        sum += *it;
    }
    EXPECT_EQ(sum, 6);
}

// 测试空向量
TEST(KVectorTest, EmptyVector) {
    KVector<int> vec;
    EXPECT_TRUE(vec.empty());
    EXPECT_THROW(vec.pop_back(), std::underflow_error);
    EXPECT_THROW(vec.front(), std::underflow_error);
    EXPECT_THROW(vec.back(), std::underflow_error);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}