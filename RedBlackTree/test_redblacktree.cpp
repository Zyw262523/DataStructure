#include "redblacktree.hpp"
#include <gtest/gtest.h>

// 测试插入单个值并获取顶部节点
TEST(RedBlackTreeTest, InsertSingleValue) {
    RedBlackTree<int, std::string> tree;
    tree.insert(10, "Alice");

    auto top = tree.getTop();
    EXPECT_EQ(top.first, 10);
    EXPECT_EQ(top.second, "Alice");
}

// 测试插入多个值并验证顶部节点
TEST(RedBlackTreeTest, InsertMultipleValues) {
    RedBlackTree<int, std::string> tree;
    tree.insert(20, "Bob");
    tree.insert(10, "Alice");
    tree.insert(30, "Charlie");

    auto top = tree.getTop();
    EXPECT_EQ(top.first, 20); // 根节点应为第一个插入的值
    EXPECT_EQ(top.second, "Bob");
}

// 测试插入重复值
TEST(RedBlackTreeTest, InsertDuplicateValue) {
    RedBlackTree<int, std::string> tree;
    tree.insert(10, "Alice");
    tree.insert(10, "Bob"); // 重复值应被忽略

    auto top = tree.getTop();
    EXPECT_EQ(top.first, 10);
    EXPECT_EQ(top.second, "Alice"); // 第一个插入的值应保留
}

// 测试空树时获取顶部节点抛出异常
TEST(RedBlackTreeTest, EmptyTreeThrowsException) {
    RedBlackTree<int, std::string> tree;

    EXPECT_THROW({
        tree.getTop();
    }, std::runtime_error);
}

// 测试插入大量数据并验证顶部节点
TEST(RedBlackTreeTest, InsertLargeDataset) {
    RedBlackTree<int, std::string> tree;

    // 插入 1000 个值
    for (int i = 1; i <= 1000; ++i) {
        tree.insert(i, "User" + std::to_string(i));
    }

    // 验证中序遍历结果是否有序
    auto traversalResult = tree.inOrderTraversal();
    for (size_t i = 1; i < traversalResult.size(); ++i) {
        EXPECT_LT(traversalResult[i - 1].first, traversalResult[i].first);
    }

    // 验证树的大小是否正确
    EXPECT_EQ(traversalResult.size(), 1000);
}

// 测试插入逆序数据并验证顶部节点
TEST(RedBlackTreeTest, InsertReverseOrder) {
    RedBlackTree<int, std::string> tree;

    // 逆序插入 100 个值
    for (int i = 100; i >= 1; --i) {
        tree.insert(i, "User" + std::to_string(i));
    }

    // 验证中序遍历结果是否有序
    auto traversalResult = tree.inOrderTraversal();
    for (size_t i = 1; i < traversalResult.size(); ++i) {
        EXPECT_LT(traversalResult[i - 1].first, traversalResult[i].first);
    }

    // 验证树的大小是否正确
    EXPECT_EQ(traversalResult.size(), 100);

    // 打印根节点的值（仅用于调试）
    auto top = tree.getTop();
    std::cout << "Root node: (" << top.first << ", " << top.second << ")\n";
}

// 测试插入随机数据并验证顶部节点
TEST(RedBlackTreeTest, InsertRandomOrder) {
    RedBlackTree<int, std::string> tree;
    tree.insert(50, "User50");
    tree.insert(30, "User30");
    tree.insert(70, "User70");
    tree.insert(20, "User20");
    tree.insert(40, "User40");
    tree.insert(60, "User60");
    tree.insert(80, "User80");

    auto top = tree.getTop();
    EXPECT_EQ(top.first, 50); // 第一个插入的值应为根节点
    EXPECT_EQ(top.second, "User50");
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}