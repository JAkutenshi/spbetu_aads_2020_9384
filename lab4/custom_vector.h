#pragma once
#include <iostream>
#include <algorithm>

template <class T>
class custom_vector
{
private:
    T* vector=nullptr;
    int allocated_size = 10;
    int current_size = 0;

public:
    class iterator {
    public:
        typedef iterator self_type;
        typedef T value_type;
        typedef T& reference;
        typedef T* pointer;
        typedef std::forward_iterator_tag iterator_category;
        typedef int difference_type;
        iterator(T* ptr) : ptr_(ptr) { }
        bool operator<(const self_type& rhs) { return ptr_ < rhs.ptr_; }
        self_type operator+(int junk) { self_type i = *this; return ptr_+junk; }
        self_type operator-(int junk) { self_type i = *this;  return ptr_-junk; }
        self_type operator++() { self_type i = *this; ptr_++; return i; }
        self_type operator++(int junk) { ptr_++; return *this; }
        reference operator*() { return *ptr_; }
        pointer operator->() { return ptr_; }
        bool operator==(const self_type& rhs) { return ptr_ == rhs.ptr_; }
        bool operator!=(const self_type& rhs) { return ptr_ != rhs.ptr_; }
    private:
        pointer ptr_;
    };


    custom_vector() {
        this->vector = new T[allocated_size];
    };

    custom_vector(std::initializer_list<T> c) {
        this->vector = new T[c.size()];
        allocated_size = c.size();
        for(auto it = c.begin(); it!=c.end(); it++) {
            this->push_back((*it));
        }
    };

    // move
    custom_vector<T>(custom_vector&& other) {
        vector = other.vector;
	other.vector = nullptr;
        current_size = other.size();
        allocated_size = other.allocated_size;
    }

    // move
    custom_vector<T>& operator=(custom_vector<T>&& other) {
        if (&other == this) return *this;
        if(vector) {
            delete []vector;
        }
        vector = other.vector;
        other.vector = nullptr;
        current_size = other.size();
        allocated_size = other.allocated_size;
        return *this;
    }

    ~custom_vector() {
        if(this->vector) {
            delete []this->vector;
            this->vector = nullptr;
        }
    };

    int size() {
        return this->current_size;
    }

    void push_back(T data) {
        if(this->current_size == this->allocated_size) {
            this->resize(allocated_size*2);
        }
        this->vector[this->current_size++] = data;
    };

    void resize(int n) {
        this->allocated_size = n;
        T* buffer = new T[n];
        if(this->vector) {
            std::copy_n(this->vector, this->size(), buffer);
            delete []this->vector;
        }
        this->vector = buffer;
    }

    iterator begin() {
        return iterator(this->vector);
    }

    iterator end() {
        return iterator(this->vector+this->current_size);
    }

    T operator[](int index) const { 
        return this->vector[index];
    }

    void print() {
        for(iterator it = this->begin(); it!=this->end(); it++) {
            std::cout << (*it) << " ";
        }
        std::cout << "\n";
    }

    void print(iterator first, iterator last) {
        for(iterator it = first; it!=last; it++) {
            std::cout << (*it) << " ";
        }
        std::cout << "\n";
    }



    //NaturalMergeSort 
    void sort() {
        std::cout << "NaturalMergeSort\n";
        std::cout << "List: ";
        this->print();
        *this = this->split(this->begin(), this->end());
    }

    custom_vector<T> split(iterator begin, iterator end) {
        if(begin == end) return {};
        iterator first_sequence_end = find_end_of_sequence(begin, end);
        iterator second_sequence_end = find_end_of_sequence(first_sequence_end, end);
        custom_vector<T> first_part = merge(begin, first_sequence_end, first_sequence_end, second_sequence_end);

        std::cout << "AFTER MERGE: ";
        first_part.print();

        custom_vector<T> second_part = split(second_sequence_end, end);
        return merge(first_part.begin(), first_part.end(), second_part.begin(), second_part.end());
    }

    iterator find_end_of_sequence(iterator begin, iterator end) {
        if(begin == end) return end;
        
        std::cout << "COMPARE: \n";

        for(begin; begin!=(end-1); begin++) {
            if(*begin > *(begin+1)) {

                std::cout << (*begin) << " > " << *(begin+1) << std::endl;
                std::cout << "RETURN " << *(begin+1) << std::endl;

                return begin+1;
            }
            std::cout << (*begin) << " <= " << *(begin+1) << std::endl;
        }
        return end;
    }

    custom_vector<T> merge(iterator first_start, iterator first_end, iterator second_start, iterator second_end) {
        std::cout << "MERGE\n";
        std::cout << "FIRST SEQUENCE: ";
        this->print(first_start, first_end);
        std::cout << "SECOND SEQUENCE: ";
        this->print(second_start, second_end);

        custom_vector<T> merged_seq;
        while(first_start < (first_end) && second_start < second_end) {
            iterator& tmp = *first_start <= *second_start? first_start : second_start;
            merged_seq.push_back(*tmp);
            tmp++;
        }

        iterator it_start = first_start == first_end? second_start: first_start;
        iterator it_end = first_start == first_end? second_end: first_end;

        for(it_start; it_start!=it_end; it_start++) {
            merged_seq.push_back(*it_start);
        }
        return merged_seq;
    }
};
