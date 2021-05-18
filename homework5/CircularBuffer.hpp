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
    private:
        T *arrayStart;
        T *arrayEnd;
        T *myPointer;
        T* countPointer;
        int difference;
    public:
        using iterator_category [[maybe_unused]] = std::random_access_iterator_tag;
        using value_type [[maybe_unused]] = T;
        using difference_type [[maybe_unused]] = int;
        using pointer [[maybe_unused]] = T *;
        using reference = T &;

        explicit customIterator(T *startOfArray, T *endOfArray, T *ptr, T* counter, difference_type diff) : arrayStart(startOfArray),
                                                                          arrayEnd(endOfArray),
                                                                          myPointer(ptr),
                                                                          countPointer(counter),
                                                                          difference(diff){}

        bool operator!=(customIterator givenIterator) {
            return countPointer != givenIterator.countPointer;
        }

        bool operator==(customIterator someIterator) {
            return myPointer == someIterator.myPointer;
        }

        bool operator<(customIterator someIterator) {
            return difference < someIterator.difference;
        }

        bool operator>(customIterator someIterator) {
            return difference > someIterator.difference;
        }

        customIterator &operator--() {
            myPointer--;
            difference--;
            countPointer--;
            return *this;
        }

        difference_type operator+(customIterator someIterator) {
            return difference + someIterator.difference;
        }

        difference_type operator-(customIterator someIterator) {
            return difference - someIterator.difference;
        }

        customIterator operator-(difference_type someDiffer) {
            difference_type tempDiffer = difference - someDiffer;
            if (myPointer - someDiffer < arrayStart){
                difference_type temp = myPointer - arrayStart;
                someDiffer -= temp;
                return customIterator(arrayStart, arrayEnd, arrayEnd - someDiffer, countPointer, tempDiffer);
            }
            else return customIterator(arrayStart, arrayEnd, myPointer - someDiffer, countPointer, tempDiffer);
        }

        customIterator operator+(difference_type someDiffer) {
            difference_type tempDiffer = difference + someDiffer;
            if (myPointer + someDiffer > arrayEnd){
                difference_type temp = arrayEnd - myPointer;
                someDiffer -= temp;
                return customIterator(arrayStart, arrayEnd, arrayEnd + someDiffer, countPointer, tempDiffer);
            }
            else return customIterator(arrayStart, arrayEnd, myPointer + someDiffer, countPointer, tempDiffer);
        }

        customIterator &operator++() {
            ++countPointer;
            ++difference;
            if(myPointer == arrayEnd - 1){
                myPointer = arrayStart;
                return *this;
            } else {
                ++myPointer;
                return *this;
            }
        }

        reference operator*() {
            return *myPointer;
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
            return customIterator(data, &data[capacity], &data[tail + 1], &data[capacity - size], 0);
        else return customIterator(data, &data[capacity], &data[0], &data[capacity - size], 0);
    }

    customIterator end() const {
        return customIterator(data, &data[capacity], &data[head], &data[capacity], size);
    }

    T &operator[](size_t position) const {
        if (position < 0 || position >= size)
            throw std::out_of_range("Error: out of range");
        return data[(tail + position + 1) % capacity];
    }
};