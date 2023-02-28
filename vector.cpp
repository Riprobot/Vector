#include <algorithm>
#include "vector.h"

Vector::Vector() {
    size_ = 0;
    capacity_ = 0;
    start_ = nullptr;
}

Vector::Vector(size_t size) {
    size_ = size;
    capacity_ = size;
    start_ = new ValueType[capacity_ + 1];
    for (size_t i = 0; i < size_; ++i) {
        start_[i] = 0;
    }
}

Vector::Vector(std::initializer_list<ValueType> list) {
    size_ = list.size();
    capacity_ = list.size();
    start_ = nullptr;
    if (size_ != 0) {
        start_ = new ValueType[capacity_ + 1];
        size_t i = 0;
        for (auto it = list.begin(); it != list.end(); ++it) {
            start_[i++] = *it;
        }
    }
}
Vector::~Vector() {
    size_ = 0;
    capacity_ = 0;
    delete[] start_;
}

Vector::Vector(const Vector &other) {
    size_ = other.size_;
    capacity_ = other.capacity_;
    start_ = new ValueType[capacity_ + 1];
    for (size_t i = 0; i < other.size_; ++i) {
        start_[i] = other.start_[i];
    }
}

Vector &Vector::operator=(const Vector &other) {
    Vector::~Vector();
    size_ = other.size_;
    capacity_ = other.capacity_;
    start_ = new ValueType[capacity_ + 1];
    for (size_t i = 0; i < other.size_; ++i) {
        start_[i] = other.start_[i];
    }
    return *this;
}

Vector::SizeType Vector::Size() const {
    return size_;
}

Vector::SizeType Vector::Capacity() const {
    return capacity_;
}

const Vector::ValueType *Vector::Data() const {
    return start_;
}

bool Vector::operator==(const Vector &other) const {
    if (size_ != other.size_) {
        return false;
    }
    for (size_t i = 0; i < size_; ++i) {
        if (start_[i] != other.start_[i]) {
            return false;
        }
    }
    return true;
}

bool Vector::operator!=(const Vector &other) const {
    return !(*this == other);
}

std::strong_ordering Vector::operator<=>(const Vector &other) const {
    for (size_t i = 0; i < std::min(size_, other.size_); ++i) {
        if (start_[i] <=> other.start_[i] != 0) {
            return start_[i] <=> other.start_[i];
        }
    }
    return size_ <=> other.size_;
}

Vector::ValueType &Vector::operator[](size_t position) {
    return start_[position];
}

Vector::ValueType Vector::operator[](size_t position) const {
    return start_[position];
}

void Vector::Reserve(SizeType new_capacity) {
    if (capacity_ >= new_capacity) {
        return;
    }
    ValueType *new_start = new ValueType[new_capacity + 1];
    SizeType new_size = size_;
    for (size_t i = 0; i < size_; ++i) {
        new_start[i] = start_[i];
    }
    Vector::~Vector();
    start_ = new_start;
    size_ = new_size;
    capacity_ = new_capacity;
}

void Vector::Clear() {
    size_ = 0;
}

void Vector::PushBack(const ValueType &new_element) {
    if (size_ == capacity_) {
        if (capacity_ != 0) {
            Reserve(capacity_ * 2);
        } else {
            Reserve(1);
        }
    }
    start_[size_++] = new_element;
}

void Vector::PopBack() {
    if (size_ > 0) {
        size_--;
    }
}

void Vector::Swap(Vector &other) {
    std::swap(size_, other.size_);
    std::swap(capacity_, other.capacity_);
    int *tmp = other.start_;
    other.start_ = start_;
    start_ = tmp;
}

Vector::Iterator Vector::Begin() {
    return Iterator(start_);
}

Vector::Iterator Vector::End() {
    return Iterator(start_ + size_);
}

Vector::Iterator Vector::begin() {
    return Begin();
}

Vector::Iterator Vector::end() {
    return End();
}

Vector::Iterator::Iterator() {
    current_ = nullptr;
}

Vector::Iterator::Iterator(ValueType *pointer) {
    current_ = pointer;
}

Vector::ValueType &Vector::Iterator::operator*() const {
    return *current_;
}

Vector::ValueType *Vector::Iterator::operator->() const {
    return current_;
}

Vector::Iterator &Vector::Iterator::operator=(Iterator other) {
    if (this != &other) {
        current_ = other.current_;
    }
    return *this;
}

Vector::Iterator &Vector::Iterator::operator++() {
    ++current_;
    return *this;
}

Vector::Iterator Vector::Iterator::operator++(int) {
    Iterator tmp(current_);
    ++current_;
    return tmp;
}

Vector::Iterator &Vector::Iterator::operator--() {
    --current_;
    return *this;
}

Vector::Iterator Vector::Iterator::operator--(int) {
    Iterator tmp(current_);
    --current_;
    return tmp;
}

Vector::Iterator Vector::Iterator::operator+(DifferenceType shift) {
    Iterator tmp = Iterator(current_ + shift);
    return tmp;
}

Vector::DifferenceType Vector::Iterator::operator-(Iterator other) {
    return current_ - other.current_;
}

Vector::Iterator &Vector::Iterator::operator+=(DifferenceType shift) {
    *this = *this + shift;
    return *this;
}

Vector::Iterator &Vector::Iterator::operator-=(DifferenceType shift) {
    current_ -= shift;
    return *this;
}

bool Vector::Iterator::operator==(const Iterator &other) const {
    return current_ == other.current_;
}

bool Vector::Iterator::operator!=(const Iterator &other) const {
    return !(*this == other);
}

std::strong_ordering Vector::Iterator::operator<=>(const Iterator &other) const {
    return current_ <=> other.current_;
}