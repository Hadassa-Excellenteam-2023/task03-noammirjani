#pragma once

#include <iostream>
#include <list>
#include <exception>

template <typename T>
/*
 * @param a The first element to compare.
 * @param b The second element to compare.
 * @return A value less than zero if a < b, zero if a == b, or a value greater than zero if a > b.
*/
struct Comparator {
    T operator()(const T& a, const T& b) const {
        return a - b;
    }
};


template <typename T>
class PriorityQueue {
public:
    void push(const T&);
    T poll();
    void print() const;

private:
    std::list<T> m_data;
    Comparator<T> m_comp;
};

/*
 *
 */
template<typename T>
void PriorityQueue<T>::print() const{
    for (const auto& listIt : m_data) {
        std::cout << listIt << "\n";
    }
    std::cout << std::endl;
}

/*
 * @return The top element of the priority queue.
 * @throw std::out_of_range if the priority queue is empty.
*/
template<typename T>
T PriorityQueue<T>::poll() {
    if( m_data.begin() == m_data.end()){
        throw std::out_of_range("PriorityQueue empty!");
    }
    T front = *m_data.begin();
    m_data.pop_front();
    return front;
}


/*
* The new element is inserted into the list in the appropriate position based on the comparison function.
* @param newElement The new element to add to the priority queue.
*/
template<typename T>
void PriorityQueue<T>::push(const T& newElement) {
    auto listIt = m_data.begin();

    while (listIt != m_data.end() && m_comp(*listIt, newElement) < 0) {
        ++listIt;
    }

    m_data.insert(listIt, newElement);
}