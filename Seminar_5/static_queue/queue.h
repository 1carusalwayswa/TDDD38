#ifndef __QUEUE_H__
#define __QUEUE_H__

#include <vector>
#include <iostream>
#include <cassert>
#include <stdexcept>

class queue_error : public std::runtime_error {
public:
    // let the base class constructor do the work, rather explicit call it.
    using std::runtime_error::runtime_error;
};

template <typename T, int N>
class Queue {
public:
    static_assert(N > 0, "Queue should have one element at least");

    bool full() const {
        return size == N; 
    }

    bool empty() const {
        return size == 0;
    }

    void enqueue(T value) {
        //std::cout << "head: " << head << " trail: " << trail << " size: " << size << std::endl;
        if (full()) {
            throw queue_error {"enqueue values into an already full queue."};
        }
        data[trail] = value;
        trail = (trail + 1) % N;
        size++;
    }

    T dequeue() {
        //std::cout << "head: " << head << " trail: " << trail << " size: " << size << std::endl;
        if (empty()) {
            throw queue_error {"dequeue a value from an empty queue."};
        }
        T res = data[head];
        head = (head + 1) % N;
        size--;
        return res;
    }

    T& front() {
        // use static_cast let this ptr convert to const this ptr
        // so we can call the const front(), or we just call ourself
        // then use const_cast remove the const of result. 
        return const_cast<T&>(static_cast<Queue<T, N> const *>(this)->front());
    }

    const T& front() const {
        if (empty()) {
            throw queue_error {"access the front of an empty queue."};
        }
        return data[head];
    }

    void clear() {
        head = trail = 0;
        size = 0;
    }

    template <int M = 0>
    Queue<T, N + M> copy_and_expand() {
        Queue<T, N + M> que;

        for (int i = 0; i < N; i++) {
            que.enqueue(data[i]);
        }

        return que;
    }

private:
    T data[N] { };
    int size { };
    int head { };
    int trail { };
};

#endif /* __QUEUE_H__ */

/*
    Remeber, cause constructor is member func of class, so some func like A::A(A& other)
    can get the private val in other.
*/