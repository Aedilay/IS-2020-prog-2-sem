#pragma once

template<typename T>
class CircularBuffer {
public:
    size_t head{};
    size_t tail{};
    size_t size = 0;
    size_t capacity{};
    T *data;

    class customIterator {
    public:
        T *myPointer;
        T *ptrBegin;
        T *ptrEnd;
        T *arrayEnd;
        T *arrayStart;
        int difference = 0;
        int diff = 1;
        int negativeDiff = 0;
    public:
        using iterator_category [[maybe_unused]] = std::random_access_iterator_tag;
        using value_type [[maybe_unused]] = T;
        using difference_type [[maybe_unused]] = ptrdiff_t;
        using pointer [[maybe_unused]] = T *;
        using reference = T &;

        explicit customIterator(T *givenPointer, T *startingPoint, T *endingPoint, T *endOfArray, T *startOfArray) : myPointer(givenPointer),
                                                                                     ptrEnd(endingPoint),
                                                                                     ptrBegin(startingPoint),
                                                                                     arrayEnd(endOfArray),
                                                                                     arrayStart(startOfArray){
            if (myPointer > arrayStart)
                negativeDiff++;
        }

        bool operator!=(customIterator givenIterator) {
            return myPointer != givenIterator.myPointer;
        }

        bool operator==(customIterator someIterator) {
            return myPointer == someIterator.myPointer;
        }

        bool operator<(customIterator someIterator) {
            return myPointer < someIterator.myPointer;
        }

        bool operator>(customIterator someIterator) {
            return myPointer > someIterator.myPointer;
        }

        customIterator &operator--() {
            myPointer--;
            return *this;
        }

        difference_type operator+(customIterator someIterator) {
            return myPointer + someIterator.myPointer;
        }

        difference_type operator-(customIterator someIterator) {
            return myPointer - someIterator.myPointer;
        }

        customIterator operator-(difference_type someIterator) {
            return customIterator(myPointer - someIterator, ptrBegin, ptrEnd, arrayEnd, arrayStart);
        }

        customIterator operator+(difference_type someIterator) {
            return customIterator(myPointer + someIterator, ptrBegin, ptrEnd, arrayEnd, arrayStart);
        }

        customIterator &operator++() {
            ++myPointer;
            if (ptrBegin + diff < arrayEnd)
                diff++;
            else {
                negativeDiff++;
                diff++;
            }
            return *this;
        }

        reference operator*() {
            if (ptrBegin + diff < arrayEnd && myPointer < arrayEnd)
            return * (ptrBegin + diff);
            else return * (arrayStart + negativeDiff);
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
            throw std::out_of_range("Error: out of range");
        if (tail == capacity - 1)
            return data[0];
        else return data[tail + 1];
    }

    T last() {
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
        T *newData = new T[newCapacity];
        int temp;
        int i = capacity;
        if (head != capacity - 1){
            temp = head;
            while (temp >= 0){
                newData[i] = data[temp];
                i--;
                temp--;
            }
            temp = capacity - 1;
            while (temp > tail){
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
            while (temp > tail) {
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
        if (tail != capacity - 1)
            return customIterator(&data[capacity - size], &data[head], &data[tail + 1], &(data[capacity]), data);
        else return customIterator(&data[capacity - size], &data[head], &data[0], &(data[capacity]), data);
    }

    customIterator end() const {
        return customIterator(&(data[capacity]), &data[head], &data[tail + 1], &(data[capacity]), data);
    }

    T &operator[](size_t position) const {
        if (position < 0 || position >= size)
            throw std::out_of_range("Error: out of range");
        return data[(tail + position + 1) % capacity];
    }
};