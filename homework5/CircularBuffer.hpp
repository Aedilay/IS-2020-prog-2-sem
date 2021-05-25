#pragma once
#include <string>
#include <sstream>

using namespace std;

template<typename T>
class CircularBuffer {
public:
    size_t head{};
    size_t tail{};
    size_t size = 0;
    size_t capacity{};
    T *data;

    class customIterator{
    private:
        T *myPointer;
        T *buffer;
        size_t tailIndex;
        size_t index;
        size_t bufCapacity;
    public:
        using iterator_category [[maybe_unused]] = std::random_access_iterator_tag;
        using value_type [[maybe_unused]] = T;
        using difference_type = int;
        using pointer [[maybe_unused]] = T *;
        using reference = T &;

        explicit customIterator(T *givenPointer, T *someBuff, size_t someHead, size_t number = 0, size_t someCapacity = 0) : myPointer(givenPointer), buffer(someBuff), tailIndex(someHead), index(number), bufCapacity(someCapacity){}
        bool operator!=(customIterator givenIterator){
            return myPointer != givenIterator.myPointer;
        }
        customIterator &operator++(){
            ++myPointer;
            ++index;
            return *this;
        }
        reference operator*(){
            return buffer[(tailIndex + index) % bufCapacity];
        }
        difference_type operator-(customIterator someIterator){
            return myPointer - someIterator.myPointer;
        }
        customIterator operator-(difference_type someDiff){
            return customIterator(myPointer - someDiff, buffer, tailIndex, index - someDiff, bufCapacity);
        }
        customIterator operator+(difference_type someDiff){
            return customIterator(myPointer + someDiff, buffer, tailIndex, index + someDiff, bufCapacity);
        }
        difference_type operator+(customIterator someIterator){
            return myPointer + someIterator.myPointer;
        }
        bool operator==(customIterator someIterator){
            return myPointer == someIterator.myPointer;
        }
        bool operator<(customIterator someIterator){
            return myPointer < someIterator.myPointer;
        }
        bool operator>(customIterator someIterator){
            return myPointer > someIterator.myPointer;
        }
        customIterator &operator--(){
            --myPointer;
            --index;
            return *this;
        }
    };


public:
    explicit CircularBuffer(size_t givenSize) : head(givenSize - 1), tail(givenSize - 1), capacity(givenSize),
                                                data(new T[capacity]) {}

    void addFirst(T someData) {
        data[tail] = someData;
        if (size < capacity)
            size++;
        else if (head == 0)
            head = capacity - 1;
        else head--;
        if (tail == 0)
            tail = capacity - 1;
        else tail--;
    }

    void addLast(T someData) {
        if (size != capacity) {
            size++;
            if (head == capacity - 1) {
                head = 0;
            } else head++;
        }
        data[head] = someData;
    }

    T first() {
        if (size == 0)
            throw out_of_range("Error: buffer is empty");
        if (tail == capacity - 1)
            return data[0];
        else return data[tail + 1];
    }

    T last() {
        if (size == 0)
            throw out_of_range("Error: buffer is empty");
        return data[head];
    }

    void delFirst() {
        size--;
        if (tail == capacity - 1)
            tail = 0;
        else tail++;
    }

    void delLast() {
        size--;
        if (head == 0)
            head = capacity - 1;
        else head--;
    }

    void changeCapacity(size_t newCapacity) {
        if (newCapacity < capacity)
            throw bad_alloc();
        T *newData = new T[newCapacity];
        int temp;
        int tail_ = tail;
        int i = capacity;
        if (head != capacity - 1){
            temp = head;
            while (temp >= 0){
                newData[i] = data[temp];
                i--;
                temp--;
            }
            temp = capacity - 1;
            while (temp > tail_){
                newData[i] = data[temp];
                i--;
                temp--;
            }
        }
        else if (tail == head){
            temp = capacity - 1;
            while (temp >= 0){
                newData[i] = data[temp];
                i--;
                temp--;
            }
        }
        else {
            temp = capacity - 1;
            while (temp > tail_) {
                newData[i] = data[i - 1];
                i--;
                temp--;
            }
        }
        head = newCapacity - 1;
        tail = newCapacity - size - 1;
        capacity = newCapacity;
        delete[] data;
        data = newData;
    }

    customIterator begin() const {
        return customIterator(&data[capacity - size], data, tail + 1, 0, capacity);
    }

    customIterator end() const {
        return customIterator(&data[capacity], data, tail + 1, capacity - 1, capacity);
    }

    T operator[](size_t position) const {
        if (position < 0)
            throw out_of_range("Error: index can't be negative");
        if (size == 0)
            throw out_of_range("Error: buffer is empty");
        if (position >= size) {
        	//todo use only string
            stringstream ss;
            ss << "Error: index out of range (asking for " << position << ", max index " << size - 1 << ")";
            string str = ss.str();
            const char* err = str.c_str();
            throw out_of_range(err);
    }
        return data[(tail + position + 1) % capacity];
    }

    T &operator[](size_t position) {
        if (position < 0)
            throw out_of_range("Error: index can't be negative");
        if (size == 0)
            throw out_of_range("Error: buffer is empty");
        if (position >= size){
            stringstream ss;
            ss << "Error: index out of range (asking for " << position << ", max index " << size - 1 << ")";
            string str = ss.str();
            const char* err = str.c_str();
            throw out_of_range(err);
        }
        return data[(tail + position + 1) % capacity];
    }
};