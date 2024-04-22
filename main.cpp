#include <algorithm>
#include <iostream>
#include <stdexcept>

class smart_array {
public:
    smart_array(size_t size) : array_(new int[size]), size_(0), capacity_(size) {
    }

    smart_array(const smart_array& other) : array_(new int[other.capacity_]), size_(0), capacity_(other.capacity_) {
        copy(other);
    }
    smart_array& operator=(const smart_array& other) {
        if (this == &other) {
            return *this;
        }

        smart_array temp(other.capacity_);
        temp.copy(other);
        swap(temp);
        return *this;
    }

    ~smart_array() {
        clear();
    }

    void add_element(int value) {
        if (size_ == capacity_) {
            throw std::out_of_range("add_element error: array if full");
        }
        array_[size_] = value;
        ++size_;
    }

    int get_element(size_t idx) const {
        if (idx >= size_) {
            throw std::out_of_range("idx is more than array size");
        }
        return array_[idx];
    }

    int& get_element(size_t idx) {
        if (idx >= size_) {
            throw std::out_of_range("idx is more than array size");
        }
        return array_[idx];
    }

    size_t size() const {
        return size_;
    }

    size_t capacity() const {
        return capacity_;
    }

    void swap(smart_array& other) {
        std::swap(array_, other.array_);
        std::swap(size_, other.size_);
        std::swap(capacity_, other.capacity_);
    }

private:
    int* array_ = nullptr;
    size_t size_ = 0;
    size_t capacity_ = 0;


    void clear() {
        delete[] array_;
        array_ = nullptr;
        size_ = 0;
        capacity_ = 0;
    }

    void copy(const smart_array& other) {
        for (size_t i = 0; i < other.size_; ++i) {
            array_[i] = other.array_[i];
        }
        size_ = other.size_;
    }
};

void print_smart_array(const smart_array& array) {
    std::cout << "array";
    for (size_t i = 0; i < array.size(); ++i) {
        std::cout << " " << array.get_element(i);
    }
    std::cout << std::endl;
}

int main() {
    try {
        smart_array arr(2);
        arr.add_element(44);
        arr.add_element(34);

        std::cout << "arr ";
        print_smart_array(arr);

        smart_array new_array(5);
        new_array.add_element(1);
        new_array.add_element(4);
        new_array.add_element(155);


        std::cout << "new_array ";
        print_smart_array(new_array);

        std::cout << "swap" << std::endl;
        arr.swap(new_array);
        std::cout << "arr ";
        print_smart_array(arr);
        std::cout << "new_array ";
        print_smart_array(new_array);

        std::cout << "copy operator=" << std::endl;
        arr = new_array;
        std::cout << "arr ";
        print_smart_array(arr);
        std::cout << "new_array ";
        print_smart_array(new_array);

    }
    catch (const std::exception& ex) {
        std::cout << ex.what() << std::endl;
    }
}
