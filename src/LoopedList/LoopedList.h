#ifndef LOOPEDLIST_H
#define LOOPEDLIST_H

#include <QVector>
#include <iostream>

template <typename T>
class LoopedList {
public:
    explicit LoopedList(int capacity) : capacity(capacity) {}

    void prepend(const T& value) {
        if (data.size() == capacity) {
            data.pop_back(); // Удаляем последний элемент, если достигли предела
        }
        data.prepend(value); // Вставляем новый элемент в начало
        this->size = data.size();
    }

    const QVector<T>& getData() const {
        return data;
    }

    const int getCapacity() const {
        return capacity;
    }

    const int getSize() const {
        return size;
    }

    void print() const {
        for (const auto& item : data) {
            std::cout << item << " ";
        }
        std::cout << std::endl;
    }

private:
    int capacity;
    int size;
    QVector<T> data;
};

#endif // LOOPEDLIST_HS
