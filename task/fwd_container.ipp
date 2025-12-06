#include <stdexcept>

template <typename T>
fwd_container<T>::iterator::iterator() : base_ptr_(nullptr) {}

template <typename T> fwd_container<T>::iterator::~iterator() {
  delete base_ptr_;
}

template <typename T>
fwd_container<T>::iterator::iterator(const iterator &other)
    : base_ptr_(other.base_ptr_ ? other.base_ptr_->clone() : nullptr) {}

template <typename T>
fwd_container<T>::iterator::iterator(iterator &&other) noexcept
    : base_ptr_(other.base_ptr_) {
  other.base_ptr_ = nullptr;
}

template <typename T>
typename fwd_container<T>::iterator &
fwd_container<T>::iterator::operator=(const iterator &other) {
  if (this != &other) {
    delete base_ptr_;
    base_ptr_ = other.base_ptr_ ? other.base_ptr_->clone() : nullptr;
  }
  return *this;
}

template <typename T>
typename fwd_container<T>::iterator &
fwd_container<T>::iterator::operator=(iterator &&other) noexcept {
  if (this != &other) {
    delete base_ptr_;
    base_ptr_ = other.base_ptr_;
    other.base_ptr_ = nullptr;
  }
  return *this;
}

template <typename T>
fwd_container<T>::iterator::iterator(iterator_base *ptr) : base_ptr_(ptr) {}

template <typename T>
typename fwd_container<T>::iterator::reference
fwd_container<T>::iterator::operator*() const {
  if (!base_ptr_)
    throw std::runtime_error("Dereferencing null iterator");
  return base_ptr_->operator*();
}

template <typename T>
typename fwd_container<T>::iterator::pointer
fwd_container<T>::iterator::operator->() const {
  if (!base_ptr_)
    throw std::runtime_error("Dereferencing null iterator");
  return base_ptr_->operator->();
}

template <typename T>
typename fwd_container<T>::iterator &fwd_container<T>::iterator::operator++() {
  if (!base_ptr_)
    throw std::runtime_error("Incrementing null iterator");
  base_ptr_->operator++();
  return *this;
}

template <typename T>
typename fwd_container<T>::iterator
fwd_container<T>::iterator::operator++(int) {
  iterator temp = *this;
  ++(*this);
  return temp;
}

// const_iterator implementation
template <typename T>
fwd_container<T>::const_iterator::const_iterator() : base_ptr_(nullptr) {}

template <typename T> fwd_container<T>::const_iterator::~const_iterator() {
  delete base_ptr_;
}

template <typename T>
fwd_container<T>::const_iterator::const_iterator(const const_iterator &other)
    : base_ptr_(other.base_ptr_ ? other.base_ptr_->clone() : nullptr) {}

template <typename T>
fwd_container<T>::const_iterator::const_iterator(
    const_iterator &&other) noexcept
    : base_ptr_(other.base_ptr_) {
  other.base_ptr_ = nullptr;
}

template <typename T>
fwd_container<T>::const_iterator::const_iterator(const iterator &other)
    : base_ptr_(other.base_ptr_ ? other.base_ptr_->clone() : nullptr) {}

template <typename T>
typename fwd_container<T>::const_iterator &
fwd_container<T>::const_iterator::operator=(const const_iterator &other) {
  if (this != &other) {
    delete base_ptr_;
    base_ptr_ = other.base_ptr_ ? other.base_ptr_->clone() : nullptr;
  }
  return *this;
}

template <typename T>
typename fwd_container<T>::const_iterator &
fwd_container<T>::const_iterator::operator=(const_iterator &&other) noexcept {
  if (this != &other) {
    delete base_ptr_;
    base_ptr_ = other.base_ptr_;
    other.base_ptr_ = nullptr;
  }
  return *this;
}

template <typename T>
typename fwd_container<T>::const_iterator &
fwd_container<T>::const_iterator::operator=(const iterator &other) {
  delete base_ptr_;
  base_ptr_ = other.base_ptr_ ? other.base_ptr_->clone() : nullptr;
  return *this;
}

template <typename T>
fwd_container<T>::const_iterator::const_iterator(const_iterator_base *ptr)
    : base_ptr_(ptr) {}

template <typename T>
typename fwd_container<T>::const_iterator::reference
fwd_container<T>::const_iterator::operator*() const {
  if (!base_ptr_)
    throw std::runtime_error("Dereferencing null const_iterator");
  return base_ptr_->operator*();
}

template <typename T>
typename fwd_container<T>::const_iterator::pointer
fwd_container<T>::const_iterator::operator->() const {
  if (!base_ptr_)
    throw std::runtime_error("Dereferencing null const_iterator");
  return base_ptr_->operator->();
}

template <typename T>
typename fwd_container<T>::const_iterator &
fwd_container<T>::const_iterator::operator++() {
  if (!base_ptr_)
    throw std::runtime_error("Incrementing null const_iterator");
  base_ptr_->operator++();
  return *this;
}

template <typename T>
typename fwd_container<T>::const_iterator
fwd_container<T>::const_iterator::operator++(int) {
  const_iterator temp = *this;
  ++(*this);
  return temp;
}

// Stream operators
template <typename T>
std::ostream &operator<<(std::ostream &os, const fwd_container<T> &container) {
  for (const auto &item : container) {
    os << item << " ";
  }
  return os;
}

template <typename T>
std::istream &operator>>(std::istream &is, fwd_container<T> &container) {
  T value;
  while (is >> value) {
    container.push(value);
  }
  return is;
}
