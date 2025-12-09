template <typename T>
stack<T>::stack_iterator::stack_iterator(Node* ptr) : current_(ptr) {}

template <typename T>
T& stack<T>::stack_iterator::operator*() {
    return current_->data;
}

template <typename T>
T* stack<T>::stack_iterator::operator->() {
    return &current_->data;
}

template <typename T>
void stack<T>::stack_iterator::operator++() {
    current_ = current_->next.get();
}

template <typename T>
const void* stack<T>::stack_iterator::get_type_id() const {
    static char id;
    return &id;
}

template <typename T>
bool stack<T>::stack_iterator::operator==(const typename fwd_container<T>::iterator_base& other) const {
    if (get_type_id() != other.get_type_id()) {
        return false;
    }
    const auto& other_ref = static_cast<const stack_iterator&>(other);
    return current_ == other_ref.current_;
}

template <typename T>
bool stack<T>::stack_iterator::operator!=(const typename fwd_container<T>::iterator_base& other) const {
    return !(*this == other);
}

template <typename T>
typename fwd_container<T>::iterator_base* stack<T>::stack_iterator::clone() const {
    return new stack_iterator(current_);
}

template <typename T>
stack<T>::const_stack_iterator::const_stack_iterator(const Node* ptr) : current_(ptr) {}

template <typename T>
const void* stack<T>::const_stack_iterator::get_type_id() const {
    static char id;
    return &id;
}

template <typename T>
const T& stack<T>::const_stack_iterator::operator*() const {
    return current_->data;
}

template <typename T>
const T* stack<T>::const_stack_iterator::operator->() const {
    return &current_->data;
}

template <typename T>
void stack<T>::const_stack_iterator::operator++() {
    current_ = current_->next.get();
}

template <typename T>
bool stack<T>::const_stack_iterator::operator==(const typename fwd_container<T>::const_iterator_base& other) const {
    if (get_type_id() != other.get_type_id()) {
        return false;
    }
    const auto& other_ref = static_cast<const const_stack_iterator&>(other);
    return current_ == other_ref.current_;
}

template <typename T>
bool stack<T>::const_stack_iterator::operator!=(const typename fwd_container<T>::const_iterator_base& other) const {
    return !(*this == other);
}

template <typename T>
typename fwd_container<T>::const_iterator_base* stack<T>::const_stack_iterator::clone() const {
    return new const_stack_iterator(current_);
}

template <typename T>
stack<T>::stack() : head_(nullptr), size_(0) {}

template <typename T>
stack<T>::~stack() {
    clear();
}

template <typename T>
void stack<T>::clear() {
    while (head_) {
        head_ = std::move(head_->next);
    }
    size_ = 0;
}

template <typename T>
stack<T>::stack(const stack& other) : head_(nullptr), size_(0) {
    if (!other.head_) return;

    Node* other_current = other.head_.get();
    auto new_node = std::make_unique<Node>(other_current->data);
    head_ = std::move(new_node);
    size_++;

    Node* this_current = head_.get();
    other_current = other_current->next.get();

    while (other_current) {
        new_node = std::make_unique<Node>(other_current->data);
        this_current->next = std::move(new_node);
        this_current = this_current->next.get();
        other_current = other_current->next.get();
        size_++;
    }
}

template <typename T>
stack<T>::stack(stack&& other) noexcept : head_(std::move(other.head_)), size_(other.size_) {
    other.size_ = 0;
}

template <typename T>
stack<T>& stack<T>::operator=(const stack& other) {
    if (this != &other) {
        clear();
        if (other.head_) {
             Node* other_current = other.head_.get();
            auto new_node = std::make_unique<Node>(other_current->data);
            head_ = std::move(new_node);
            size_++;

            Node* this_current = head_.get();
            other_current = other_current->next.get();

            while (other_current) {
                new_node = std::make_unique<Node>(other_current->data);
                this_current->next = std::move(new_node);
                this_current = this_current->next.get();
                other_current = other_current->next.get();
                size_++;
            }
        }
    }
    return *this;
}

template <typename T>
stack<T>& stack<T>::operator=(stack&& other) noexcept {
    if (this != &other) {
        clear();
        head_ = std::move(other.head_);
        size_ = other.size_;
        other.size_ = 0;
    }
    return *this;
}

template <typename T>
void stack<T>::push(const T& value) {
    auto new_node = std::make_unique<Node>(value, std::move(head_));
    head_ = std::move(new_node);
    size_++;
}

template <typename T>
void stack<T>::push(T&& value) {
    auto new_node = std::make_unique<Node>(std::move(value), std::move(head_));
    head_ = std::move(new_node);
    size_++;
}

template <typename T>
T stack<T>::pop() {
    if (is_empty()) {
        throw std::out_of_range("pop from empty stack");
    }
    T value = std::move(head_->data);
    head_ = std::move(head_->next);
    size_--;
    return value;
}

template <typename T>
T& stack<T>::get_front() {
    if (is_empty()) {
        throw std::out_of_range("get_front from empty stack");
    }
    return head_->data;
}

template <typename T>
const T& stack<T>::get_front() const {
    if (is_empty()) {
        throw std::out_of_range("get_front from empty stack");
    }
    return head_->data;
}

template <typename T>
bool stack<T>::is_empty() const {
    return head_ == nullptr;
}

template <typename T>
size_t stack<T>::size() const {
    return size_;
}

template <typename T>
typename stack<T>::iterator stack<T>::begin() {
    return iterator(new stack_iterator(head_.get()));
}

template <typename T>
typename stack<T>::iterator stack<T>::end() {
    return iterator(new stack_iterator(nullptr));
}

template <typename T>
typename stack<T>::const_iterator stack<T>::begin() const {
    return const_iterator(new const_stack_iterator(head_.get()));
}

template <typename T>
typename stack<T>::const_iterator stack<T>::end() const {
    return const_iterator(new const_stack_iterator(nullptr));
}

template <typename T>
typename stack<T>::const_iterator stack<T>::cbegin() const {
    return const_iterator(new const_stack_iterator(head_.get()));
}

template <typename T>
typename stack<T>::const_iterator stack<T>::cend() const {
    return const_iterator(new const_stack_iterator(nullptr));
}
