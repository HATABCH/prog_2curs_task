#include "gtest/gtest.h"
#include "stack.h"
#include "queue.h"
#include <string>
#include <sstream>
#include <vector>

TEST(StackIntTest, IsEmptyInitially) {
    stack<int> s;
    ASSERT_TRUE(s.is_empty());
    ASSERT_EQ(s.size(), 0u);
}

TEST(StackIntTest, PushAndGetFront) {
    stack<int> s;
    s.push(10);
    ASSERT_FALSE(s.is_empty());
    ASSERT_EQ(s.size(), 1u);
    ASSERT_EQ(s.get_front(), 10);

    s.push(20);
    ASSERT_EQ(s.size(), 2u);
    ASSERT_EQ(s.get_front(), 20);
}

TEST(StackIntTest, Pop) {
    stack<int> s;
    s.push(10);
    s.push(20);
    ASSERT_EQ(s.pop(), 20);
    ASSERT_EQ(s.size(), 1u);
    ASSERT_EQ(s.get_front(), 10);
    ASSERT_EQ(s.pop(), 10);
    ASSERT_TRUE(s.is_empty());
}

TEST(StackIntTest, PopFromEmpty) {
    stack<int> s;
    ASSERT_THROW(s.pop(), std::out_of_range);
}

TEST(StackIntTest, Iterator) {
    stack<int> s;
    s.push(10);
    s.push(20);
    s.push(30);
    
    std::vector<int> expected = {30, 20, 10};
    std::vector<int> actual;
    for(const auto& item : s) {
        actual.push_back(item);
    }
    ASSERT_EQ(actual, expected);
}

TEST(StackIntTest, CopyConstructor) {
    stack<int> s1;
    s1.push(1);
    s1.push(2);
    stack<int> s2 = s1;
    
    ASSERT_EQ(s1.size(), 2u);
    ASSERT_EQ(s2.size(), 2u);
    ASSERT_EQ(s1.pop(), 2);
    ASSERT_EQ(s2.pop(), 2);
    ASSERT_EQ(s1.pop(), 1);
    ASSERT_EQ(s2.pop(), 1);
}

TEST(StackIntTest, MoveConstructor) {
    stack<int> s1;
    s1.push(1);
    s1.push(2);
    stack<int> s2 = std::move(s1);
    
    ASSERT_TRUE(s1.is_empty());
    ASSERT_EQ(s2.size(), 2u);
    ASSERT_EQ(s2.pop(), 2);
}

TEST(StackIntTest, StreamOutput) {
    stack<int> s;
    s.push(1);
    s.push(2);
    s.push(3);
    std::stringstream ss;
    ss << s;
    ASSERT_EQ(ss.str(), "3 2 1 ");
}

TEST(QueueIntTest, IsEmptyInitially) {
    queue<int> q;
    ASSERT_TRUE(q.is_empty());
    ASSERT_EQ(q.size(), 0u);
}

TEST(QueueIntTest, PushAndGetFront) {
    queue<int> q;
    q.push(10);
    ASSERT_FALSE(q.is_empty());
    ASSERT_EQ(q.size(), 1u);
    ASSERT_EQ(q.get_front(), 10);

    q.push(20);
    ASSERT_EQ(q.size(), 2u);
    ASSERT_EQ(q.get_front(), 10);
}

TEST(QueueIntTest, Pop) {
    queue<int> q;
    q.push(10);
    q.push(20);
    ASSERT_EQ(q.pop(), 10);
    ASSERT_EQ(q.size(), 1u);
    ASSERT_EQ(q.get_front(), 20);
    ASSERT_EQ(q.pop(), 20);
    ASSERT_TRUE(q.is_empty());
}

TEST(QueueIntTest, PopFromEmpty) {
    queue<int> q;
    ASSERT_THROW(q.pop(), std::out_of_range);
}

TEST(QueueIntTest, Iterator) {
    queue<int> q;
    q.push(10);
    q.push(20);
    q.push(30);
    
    std::vector<int> expected = {10, 20, 30};
    std::vector<int> actual;
    for(const auto& item : q) {
        actual.push_back(item);
    }
    ASSERT_EQ(actual, expected);
}

TEST(QueueIntTest, CopyAssignment) {
    queue<int> q1;
    q1.push(1);
    q1.push(2);
    queue<int> q2;
    q2.push(3);
    q2 = q1;
    
    ASSERT_EQ(q1.size(), 2u);
    ASSERT_EQ(q2.size(), 2u);
    ASSERT_EQ(q1.pop(), 1);
    ASSERT_EQ(q2.pop(), 1);
}

TEST(QueueIntTest, MoveAssignment) {
    queue<int> q1;
    q1.push(1);
    q1.push(2);
    queue<int> q2;
    q2 = std::move(q1);
    
    ASSERT_TRUE(q1.is_empty());
    ASSERT_EQ(q2.size(), 2u);
    ASSERT_EQ(q2.pop(), 1);
}

TEST(QueueIntTest, StreamOutput) {
    queue<int> q;
    q.push(1);
    q.push(2);
    q.push(3);
    std::stringstream ss;
    ss << q;
    ASSERT_EQ(ss.str(), "1 2 3 ");
}


TEST(StackStringTest, IsEmptyInitially) {
    stack<std::string> s;
    ASSERT_TRUE(s.is_empty());
    ASSERT_EQ(s.size(), 0u);
}

TEST(StackStringTest, PushAndGetFront) {
    stack<std::string> s;
    s.push("hello");
    ASSERT_FALSE(s.is_empty());
    ASSERT_EQ(s.size(), 1u);
    ASSERT_EQ(s.get_front(), "hello");

    s.push("world");
    ASSERT_EQ(s.size(), 2u);
    ASSERT_EQ(s.get_front(), "world");
}

TEST(StackStringTest, Pop) {
    stack<std::string> s;
    s.push("hello");
    s.push("world");
    ASSERT_EQ(s.pop(), "world");
    ASSERT_EQ(s.size(), 1u);
    ASSERT_EQ(s.get_front(), "hello");
    ASSERT_EQ(s.pop(), "hello");
    ASSERT_TRUE(s.is_empty());
}

TEST(StackStringTest, PopFromEmpty) {
    stack<std::string> s;
    ASSERT_THROW(s.pop(), std::out_of_range);
}

TEST(StackStringTest, Iterator) {
    stack<std::string> s;
    s.push("a");
    s.push("b");
    s.push("c");
    
    std::vector<std::string> expected = {"c", "b", "a"};
    std::vector<std::string> actual;
    for(const auto& item : s) {
        actual.push_back(item);
    }
    ASSERT_EQ(actual, expected);
}

TEST(StackStringTest, CopyConstructor) {
    stack<std::string> s1;
    s1.push("first");
    s1.push("second");
    stack<std::string> s2 = s1;
    
    ASSERT_EQ(s1.size(), 2u);
    ASSERT_EQ(s2.size(), 2u);
    ASSERT_EQ(s1.pop(), "second");
    ASSERT_EQ(s2.pop(), "second");
    ASSERT_EQ(s1.pop(), "first");
    ASSERT_EQ(s2.pop(), "first");
}

TEST(StackStringTest, MoveConstructor) {
    stack<std::string> s1;
    s1.push("first");
    s1.push("second");
    stack<std::string> s2 = std::move(s1);
    
    ASSERT_TRUE(s1.is_empty());
    ASSERT_EQ(s2.size(), 2u);
    ASSERT_EQ(s2.pop(), "second");
}

TEST(StackStringTest, StreamOutput) {
    stack<std::string> s;
    s.push("one");
    s.push("two");
    s.push("three");
    std::stringstream ss;
    ss << s;
    ASSERT_EQ(ss.str(), "three two one ");
}

TEST(QueueStringTest, IsEmptyInitially) {
    queue<std::string> q;
    ASSERT_TRUE(q.is_empty());
    ASSERT_EQ(q.size(), 0u);
}

TEST(QueueStringTest, PushAndGetFront) {
    queue<std::string> q;
    q.push("hello");
    ASSERT_FALSE(q.is_empty());
    ASSERT_EQ(q.size(), 1u);
    ASSERT_EQ(q.get_front(), "hello");

    q.push("world");
    ASSERT_EQ(q.size(), 2u);
    ASSERT_EQ(q.get_front(), "hello");
}

TEST(QueueStringTest, Pop) {
    queue<std::string> q;
    q.push("hello");
    q.push("world");
    ASSERT_EQ(q.pop(), "hello");
    ASSERT_EQ(q.size(), 1u);
    ASSERT_EQ(q.get_front(), "world");
    ASSERT_EQ(q.pop(), "world");
    ASSERT_TRUE(q.is_empty());
}

TEST(QueueStringTest, PopFromEmpty) {
    queue<std::string> q;
    ASSERT_THROW(q.pop(), std::out_of_range);
}

TEST(QueueStringTest, Iterator) {
    queue<std::string> q;
    q.push("a");
    q.push("b");
    q.push("c");
    
    std::vector<std::string> expected = {"a", "b", "c"};
    std::vector<std::string> actual;
    for(const auto& item : q) {
        actual.push_back(item);
    }
    ASSERT_EQ(actual, expected);
}

TEST(QueueStringTest, CopyAssignment) {
    queue<std::string> q1;
    q1.push("first");
    q1.push("second");
    queue<std::string> q2;
    q2.push("third");
    q2 = q1;
    
    ASSERT_EQ(q1.size(), 2u);
    ASSERT_EQ(q2.size(), 2u);
    ASSERT_EQ(q1.pop(), "first");
    ASSERT_EQ(q2.pop(), "first");
}

TEST(QueueStringTest, MoveAssignment) {
    queue<std::string> q1;
    q1.push("first");
    q1.push("second");
    queue<std::string> q2;
    q2 = std::move(q1);
    
    ASSERT_TRUE(q1.is_empty());
    ASSERT_EQ(q2.size(), 2u);
    ASSERT_EQ(q2.pop(), "first");
}

TEST(QueueStringTest, StreamOutput) {
    queue<std::string> q;
    q.push("one");
    q.push("two");
    q.push("three");
    std::stringstream ss;
    ss << q;
    ASSERT_EQ(ss.str(), "one two three ");
}

