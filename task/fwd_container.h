#pragma once

#include <iostream>
#include <iterator>
#include <memory>

template <typename T>
class fwd_container;

template <typename T>
std::ostream& operator<<(std::ostream& os, const fwd_container<T>& container);

template <typename T>
std::istream& operator>>(std::istream& is, fwd_container<T>& container);

template <typename T>
class fwd_container {
public:
    class const_iterator;

    class iterator_base {
    public:
        virtual ~iterator_base() = default;
        virtual const void* get_type_id() const = 0;
        virtual T& operator*() = 0;
        virtual T* operator->() = 0;
        virtual void operator++() = 0;
        virtual bool operator==(const iterator_base& other) const = 0;
        virtual bool operator!=(const iterator_base& other) const = 0;
        virtual iterator_base* clone() const = 0;
    };

    class const_iterator_base {
    public:
        virtual ~const_iterator_base() = default;
        virtual const void* get_type_id() const = 0;
        virtual const T& operator*() const = 0;
        virtual const T* operator->() const = 0;
        virtual void operator++() = 0;
        virtual bool operator==(const const_iterator_base& other) const = 0;
        virtual bool operator!=(const const_iterator_base& other) const = 0;
        virtual const_iterator_base* clone() const = 0;
    };

    class iterator {
    public:
        using iterator_category = std::forward_iterator_tag;
        using value_type = T;
        using difference_type = std::ptrdiff_t;
        using pointer = T*;
        using reference = T&;

        iterator();
        ~iterator();
        iterator(const iterator& other);
        iterator(iterator&& other) noexcept;
        iterator& operator=(const iterator& other);
        iterator& operator=(iterator&& other) noexcept;

        explicit iterator(iterator_base* ptr);

        reference operator*() const;
        pointer operator->() const;
        iterator& operator++();
        iterator operator++(int);

        friend bool operator==(const iterator& a, const iterator& b) {
            if (!a.base_ptr_ || !b.base_ptr_) return !a.base_ptr_ && !b.base_ptr_;
            return a.base_ptr_->operator==(*b.base_ptr_);
        }
        friend bool operator!=(const iterator& a, const iterator& b) {
            return a.base_ptr_->operator!=(*b.base_ptr_);
        }

        friend class const_iterator;

    private:
        iterator_base* base_ptr_;
    };

    class const_iterator {
    public:
        using iterator_category = std::forward_iterator_tag;
        using value_type = T;
        using difference_type = std::ptrdiff_t;
        using pointer = const T*;
        using reference = const T&;

        const_iterator();
        ~const_iterator();
        const_iterator(const const_iterator& other);
        const_iterator(const_iterator&& other) noexcept;
        const_iterator(const iterator& other); 
        const_iterator& operator=(const const_iterator& other);
        const_iterator& operator=(const_iterator&& other) noexcept;
        const_iterator& operator=(const iterator& other);

        explicit const_iterator(const_iterator_base* ptr);

        reference operator*() const;
        pointer operator->() const;
        const_iterator& operator++();
        const_iterator operator++(int);

        friend bool operator==(const const_iterator& a, const const_iterator& b) {
             if (!a.base_ptr_ || !b.base_ptr_) return !a.base_ptr_ && !b.base_ptr_;
            return a.base_ptr_->operator==(*b.base_ptr_);
        }
        friend bool operator!=(const const_iterator& a, const const_iterator& b) {
            return !(a == b);
        }

        friend class iterator;
        friend bool operator==(const iterator& a, const const_iterator& b) {
            if (!a.base_ptr_ || !b.base_ptr_) return !a.base_ptr_ && !b.base_ptr_;
            return a.base_ptr_->operator==(*b.base_ptr_);
        }
        friend bool operator!=(const iterator& a, const const_iterator& b) {
            return !(a == b);
        }

    private:
        const_iterator_base* base_ptr_;
    };

    virtual ~fwd_container() = default;

    virtual void push(const T& value) = 0;
    virtual void push(T&& value) = 0;
    virtual T pop() = 0;
    virtual T& get_front() = 0;
    virtual const T& get_front() const = 0;
    virtual bool is_empty() const = 0;
    virtual size_t size() const = 0;

    virtual iterator begin() = 0;
    virtual iterator end() = 0;
    virtual const_iterator begin() const = 0;
    virtual const_iterator end() const = 0;
    virtual const_iterator cbegin() const = 0;
    virtual const_iterator cend() const = 0;

    friend std::ostream& operator<< <>(std::ostream& os, const fwd_container<T>& container);
    friend std::istream& operator>> <>(std::istream& is, fwd_container<T>& container);
};

#include "fwd_container.ipp"
