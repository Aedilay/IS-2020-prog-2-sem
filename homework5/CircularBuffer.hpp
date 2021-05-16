#pragma once

template <typename T>
class CircularBuffer{
    private:
        size_t size = 0;
        size_t capacity;
        T* data;

        class customIterator{
            private:
                T *myPointer;
            public:
                using iterator_category = std::random_access_iterator_tag;
                using value_type = T;
                using difference_type = int;
                using pointer = T *;
                using reference = T &;

                explicit customIterator(T *givenPointer): myPointer(givenPointer){}
                bool operator!=(customIterator givenIterator){
                    return myPointer != givenIterator.myPointer;
                }
                customIterator &operator++(){
                    ++myPointer;
                    return *this;
                }
                reference operator*(){
                    return *myPointer;
                }
                difference_type operator-(customIterator someIterator){
                    return myPointer - someIterator.myPointer;
                }
                customIterator operator-(difference_type someIterator){
                    return customIterator(myPointer - someIterator);
                }
                customIterator operator+(difference_type someIterator){
                    return customIterator(myPointer + someIterator);
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
                    return *this;
                }
        };

    public:
        explicit CircularBuffer(size_t givenSize): capacity(givenSize), data(new T[capacity]){}

        void addFirst(T someData) {
            for (int i = size; i > 0; i--)
                data[i] = data[i - 1];
            data[0] = someData;
            if (size < capacity)
                size++;
        }

        void addLast(T someData) {
            if (size < capacity){
                data[size] = someData;
                size++;
            } else
                data[size - 1] = someData;
        }

        T first() {
            if (size == 0)
                throw std::out_of_range("Error: out of range");
            return data[0];
        }

        T last() {
            return data[size - 1];
        }

        void delFirst(){
            for (size_t i = 0; i < capacity - 1; i--)
                data[i] =  data[i + 1];
            size--;
        }

        void delLast(){
            size--;
        }

        void changeCapacity(size_t newCapacity){
            T *newData = new T[newCapacity];
            for (size_t i = 0; i < size; i++)
                newData[i] = data[i];
            capacity = newCapacity;
            delete[] data;
            data = newData;
        }

        customIterator begin() const{
            return customIterator(data);
        }

        customIterator end() const{
            return customIterator(&(data[size]));
        }

        T &operator[] (size_t position) const{
            if (position < 0 || position >= size)
                throw std::out_of_range("Error: out of range");
            return data[position];
        }
};