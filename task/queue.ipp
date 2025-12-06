// queue_iterator implementation
template <typename T>
queue<T>::queue_iterator::queue_iterator(Node* ptr) : current_(ptr) {}

template <typename T>
T& queue<T>::queue_iterator::operator*() {
    if (!current_) throw std::runtime_error("Dereferencing null iterator");
    return current_->data;
}

template <typename T>
T* queue<T>::queue_iterator::operator->() {
    if (!current_) throw std::runtime_error("Dereferencing null iterator");
    return &current_->data;
}

template <typename T>
void queue<T>::queue_iterator::operator++() {
    if (!current_) throw std::runtime_error("Incrementing null iterator");
    current_ = current_->next.get();
}

template <typename T>
bool queue<T>::queue_iterator::operator==(const typename fwd_container<T>::iterator_base& other) const {
    const auto* other_ptr = dynamic_cast<const queue_iterator*>(&other);
    return other_ptr && current_ == other_ptr->current_;
}

template <typename T>
bool queue<T>::queue_iterator::operator!=(const typename fwd_container<T>::iterator_base& other) const {
    return !(*this == other);
}

template <typename T>
typename fwd_container<T>::iterator_base* queue<T>::queue_iterator::clone() const {
    return new queue_iterator(current_);
}

// const_queue_iterator implementation
template <typename T>
queue<T>::const_queue_iterator::const_queue_iterator(const Node* ptr) : current_(ptr) {}

template <typename T>
const T& queue<T>::const_queue_iterator::operator*() const {
    if (!current_) throw std::runtime_error("Dereferencing null const_iterator");
    return current_->data;
}

template <typename T>
const T* queue<T>::const_queue_iterator::operator->() const {
    if (!current_) throw std::runtime_error("Dereferencing null const_iterator");
    return &current_->data;
}

template <typename T>
void queue<T>::const_queue_iterator::operator++() {
    if (!current_) throw std::runtime_error("Incrementing null const_iterator");
    current_ = current_->next.get();
}

template <typename T>
bool queue<T>::const_queue_iterator::operator==(const typename fwd_container<T>::const_iterator_base& other) const {
    const auto* other_ptr = dynamic_cast<const const_queue_iterator*>(&other);
    return other_ptr && current_ == other_ptr->current_;
}

template <typename T>
bool queue<T>::const_queue_iterator::operator!=(const typename fwd_container<T>::const_iterator_base& other) const {
    return !(*this == other);
}

template <typename T>
typename fwd_container<T>::const_iterator_base* queue<T>::const_queue_iterator::clone() const {
    return new const_queue_iterator(current_);
}


// queue implementation
template <typename T>
queue<T>::queue() : head_(nullptr), tail_(nullptr), size_(0) {}

template <typename T>
queue<T>::~queue() {
    clear();
}

template <typename T>
void queue<T>::clear() {
    while (head_) {
        head_ = std::move(head_->next);
    }
    tail_ = nullptr;
    size_ = 0;
}

template <typename T>
queue<T>::queue(const queue& other) : head_(nullptr), tail_(nullptr), size_(0) {
    if (!other.head_) return;

    Node* other_current = other.head_.get();
    auto new_node = std::make_unique<Node>(other_current->data);
    head_ = std::move(new_node);
    tail_ = head_.get();
    size_++;

    other_current = other_current->next.get();

    while (other_current) {
        auto new_node_ptr = std::make_unique<Node>(other_current->data);
        tail_->next = std::move(new_node_ptr);
        tail_ = tail_->next.get();
        other_current = other_current->next.get();
        size_++;
    }
}

template <typename T>
queue<T>::queue(queue&& other) noexcept : head_(std::move(other.head_)), tail_(other.tail_), size_(other.size_) {
    other.tail_ = nullptr;
    other.size_ = 0;
}

template <typename T>
queue<T>& queue<T>::operator=(const queue& other) {
    if (this != &other) {
        clear();
        if (other.head_) {
            Node* other_current = other.head_.get();
            auto new_node = std::make_unique<Node>(other_current->data);
            head_ = std::move(new_node);
            tail_ = head_.get();
            size_++;

            other_current = other_current->next.get();

            while (other_current) {
                auto new_node_ptr = std::make_unique<Node>(other_current->data);
                tail_->next = std::move(new_node_ptr);
                tail_ = tail_->next.get();
                other_current = other_current->next.get();
                size_++;
            }
        }
    }
    return *this;
}

template <typename T>
queue<T>& queue<T>::operator=(queue&& other) noexcept {
    if (this != &other) {
        clear();
        head_ = std::move(other.head_);
        tail_ = other.tail_;
        size_ = other.size_;
        other.tail_ = nullptr;
        other.size_ = 0;
    }
    return *this;
}

template <typename T>
void queue<T>::push(const T& value) {
    auto new_node = std::make_unique<Node>(value);
    Node* new_node_ptr = new_node.get();
    if (is_empty()) {
        head_ = std::move(new_node);
        tail_ = head_.get();
    } else {
        tail_->next = std::move(new_node);
        tail_ = new_node_ptr;
    }
    size_++;
}

template <typename T>
void queue<T>::push(T&& value) {
    auto new_node = std::make_unique<Node>(std::move(value));
    Node* new_node_ptr = new_node.get();
    if (is_empty()) {
        head_ = std::move(new_node);
        tail_ = head_.get();
    } else {
        tail_->next = std::move(new_node);
        tail_ = new_node_ptr;
    }
    size_++;
}

template <typename T>
T queue<T>::pop() {
    if (is_empty()) {
        throw std::out_of_range("pop from empty queue");
    }
    T value = std::move(head_->data);
    head_ = std::move(head_->next);
    if (!head_) {
        tail_ = nullptr;
    }
    size_--;
    return value;
}

template <typename T>
T& queue<T>::get_front() {
    if (is_empty()) {
        throw std::out_of_range("get_front from empty queue");
    }
    return head_->data;
}

template <typename T>
const T& queue<T>::get_front() const {
    if (is_empty()) {
        throw std::out_of_range("get_front from empty queue");
    }
    return head_->data;
}

template <typename T>
bool queue<T>::is_empty() const {
    return head_ == nullptr;
}

template <typename T>
size_t queue<T>::size() const {
    return size_;
}

template <typename T>
typename queue<T>::iterator queue<T>::begin() {
    return iterator(new queue_iterator(head_.get()));
}

template <typename T>
typename queue<T>::iterator queue<T>::end() {
    return iterator(new queue_iterator(nullptr));
}

template <typename T>
typename queue<T>::const_iterator queue<T>::begin() const {
    return const_iterator(new const_queue_iterator(head_.get()));
}

template <typename T>
typename queue<T>::const_iterator queue<T>::end() const {
    return const_iterator(new const_queue_iterator(nullptr));
}

template <typename T>
typename queue<T>::const_iterator queue<T>::cbegin() const {
    return const_iterator(new const_queue_iterator(head_.get()));
}

template <typename T>
typename queue<T>::const_iterator queue<T>::cend() const {
    return const_iterator(new const_queue_iterator(nullptr));
}
