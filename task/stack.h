#pragma once

#include "fwd_container.h"
#include <memory>
#include <stdexcept>

template <typename T>
class stack : public fwd_container<T> {
private:
    struct Node {
        T data;
        std::unique_ptr<Node> next;

        Node(const T& data, std::unique_ptr<Node> next = nullptr) : data(data), next(std::move(next)) {}
        Node(T&& data, std::unique_ptr<Node> next = nullptr) : data(std::move(data)), next(std::move(next)) {}
    };

    class stack_iterator;
    class const_stack_iterator;

public:
    using iterator = typename fwd_container<T>::iterator;
    using const_iterator = typename fwd_container<T>::const_iterator;

    stack();
    ~stack() override;
    stack(const stack& other);
    stack(stack&& other) noexcept;
    stack& operator=(const stack& other);
    stack& operator=(stack&& other) noexcept;

    void push(const T& value) override;
    void push(T&& value) override;
    T pop() override;
    T& get_front() override;
    const T& get_front() const override;
    bool is_empty() const override;
    size_t size() const override;

    iterator begin() override;
    iterator end() override;
    const_iterator begin() const override;
    const_iterator end() const override;
    const_iterator cbegin() const override;
    const_iterator cend() const override;

private:
    class stack_iterator : public fwd_container<T>::iterator_base {
    public:
        explicit stack_iterator(Node* ptr);
        T& operator*() override;
        T* operator->() override;
        void operator++() override;
        bool operator==(const typename fwd_container<T>::iterator_base& other) const override;
        bool operator!=(const typename fwd_container<T>::iterator_base& other) const override;
        typename fwd_container<T>::iterator_base* clone() const override;
    private:
        Node* current_;
    };

    class const_stack_iterator : public fwd_container<T>::const_iterator_base {
    public:
        explicit const_stack_iterator(const Node* ptr);
        const T& operator*() const override;
        const T* operator->() const override;
        void operator++() override;
        bool operator==(const typename fwd_container<T>::const_iterator_base& other) const override;
        bool operator!=(const typename fwd_container<T>::const_iterator_base& other) const override;
        typename fwd_container<T>::const_iterator_base* clone() const override;
    private:
        const Node* current_;
    };

    void clear();

    std::unique_ptr<Node> head_;
    size_t size_;
};

#include "stack.ipp"
