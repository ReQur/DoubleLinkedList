#pragma once
#include <stdio.h>
#include <iterator>
#include <cstddef>

template<typename  T>
struct node
{
    T data;
    node* next, * prev;
    node() = default;
    node(const T& val) : data(val), next(nullptr), prev(nullptr) {}
};

template<typename T>
class dl_list
{
    node<T>* head, *tail;
    size_t count;

    node<T>* getNode(const size_t&);

	public:
    dl_list();
    dl_list(std::initializer_list<T>);
    ~dl_list();
    void push_front(const T&);
    void push_back(const T&);
    T pop_front();
    T pop_back();
    void insert(const size_t&, const T&);
    void append(const dl_list<T>&);
    T& front();
    T& back();
	


	struct Iterator
	{
        using iterator_category = std::forward_iterator_tag;
        using difference_type = std::ptrdiff_t;
        using value_type = T;
        using pointer = node<T>*;
        using reference = T&;

		Iterator(pointer ptr) : m_ptr(ptr) {}

        reference operator*() const { return (*m_ptr).data; }
        pointer operator->() { return m_ptr; }
        Iterator& operator++() { m_ptr = m_ptr->next; return *this; }
        Iterator operator++(T) { Iterator tmp = *this; (*this)->next; return tmp; }
        friend bool operator== (const Iterator& a, const Iterator& b) { return a.m_ptr == b.m_ptr; }
        friend bool operator!= (const Iterator& a, const Iterator& b) { return a.m_ptr != b.m_ptr; }

    private:
        pointer m_ptr;
	};

    Iterator begin() { return Iterator(head); }
    Iterator end() { return Iterator(nullptr); }

    template<typename T>
    friend std::ostream& operator<< (std::ostream& output, const dl_list<T>& value);

    
    //dl_list<T>& operator = (const dl_list<T>& value);

	
    T& operator[] (const size_t& index);
	
   /* template<typename T>
    friend std::istream& operator>> (std::istream& in, const dl_list<T>& value);*/
};

template<typename T>
dl_list<T>::dl_list() : head(nullptr), tail(nullptr), count(0)
{
}

template<typename T>
dl_list<T>::dl_list(std::initializer_list<T> l)
{
	for (T element : l) push_back(element);
}

template <typename T>
T& dl_list<T>::front()
{
    return head->data;
}

template <typename T>
T& dl_list<T>::back()
{
    return tail->data;
}



template<typename T>
dl_list<T>::~dl_list()
{
    while (head != nullptr)
    {        node<T>* tmpNewHead = head->next;
        delete head;
        head = tmpNewHead;
    }
    tail = nullptr;
    count = 0;
}

template<typename T>
void dl_list<T>::push_front(const T &val)
{
    node<T>* newNode = new(std::nothrow) node<T>(val);
    if (newNode != nullptr)
    {
        if (head == nullptr)
        {
            head = tail = newNode;
            head->next = tail;
            tail->next = nullptr;
            head->prev = nullptr;
        }
        else
        {
            newNode->next = head;
            head->prev = newNode;
            head = newNode;
        }
    }
    ++count;
}

template<typename T>
void dl_list<T>::push_back(const T& val)
{
    node<T>* newNode = new(std::nothrow) node<T>(val);
    if (newNode != nullptr)
    {
        if (head == nullptr)
        {
            head = tail = newNode;
            head->next = tail;
            tail->next = nullptr;
            head->prev = nullptr;
        }
        else
        {
            newNode->prev = tail;
            tail->next = newNode;
            tail = newNode;
        }
    }
    ++count;
}


template<typename T>
T dl_list<T>::pop_front()
{
    node<T>* headNode = head;
    T data;
    if (headNode != nullptr) 
    {
        head = head->next;
        if (head) head->prev = nullptr;
        
        if (headNode == tail) tail = nullptr;
        
        data = headNode->data;
        delete headNode;

        --count;
        return data;
    }

    return {};
}

template<typename T>
T dl_list<T>::pop_back()
{
    node<T>* tailNode = tail;
    T data;
    if (tailNode != nullptr)
    {
        tail = tail->prev;
        if (tail) tail->next = nullptr;
        
        if (tailNode == head) head = nullptr;
        
        data = tailNode->data;
        delete tailNode;

        --count;
        return data;
    }

    return {};
}

template<typename T>
void dl_list<T>::insert(const size_t& pos, const T& val)
{
    if (head == nullptr || pos < 0 || pos > count + 1) return;
    if (pos == 0) push_front(val);
    if (pos == count + 1) push_back(val);

    node<T>* tmp = (node<T>*)getNode(pos);
    node<T>* newNode = new node<T>(val);

    tmp->prev->next = newNode;
    newNode->next = tmp;
    newNode->prev = tmp->prev;
    tmp->prev = newNode;
    ++count;

}

template<typename T>
node<T>* dl_list<T>::getNode(const size_t& index)
{
    node<T>* tmp = nullptr;
    size_t i;

    if (index < count / 2)
    {
        i = 0;
        tmp = head;
        while (tmp && i < index)
        {
            tmp = tmp->next;
            i++;
        }
    }
    else
    {
        i = count - 1;
        tmp = tail;
        while (tmp && i > index)
        {
            tmp = tmp->prev;
            i--;
        }
    }

    return tmp;
}


template <typename T>
void dl_list<T>::append(const dl_list<T>& aplist)
{
    tail->next = aplist.head;
    tail->next->prev = tail;
    tail = aplist.tail;
    count += aplist.count;
}




template<typename T>
std::ostream& operator<<(std::ostream& output, const dl_list<T>& value)
{
    if (value.head == nullptr) return output;
	
    /*auto tmp = value.head;
    while (tmp != nullptr)
    {
        output << tmp->data << " ";
        tmp = tmp->next;
    }*/

    for (auto element: value)
    {
        output << element->data << " ";
    }
	
    std::cout << std::endl;
    return output;
}

template<typename T>
T& dl_list<T>::operator[] (const size_t& index)
{
    return ((node<T>*)getNode(index))->data;
}

//template <typename T>
//dl_list<T>& dl_list<T>::operator=(const dl_list<T>& value)
//{
//    if (this == &value) return *this;
//	for (auto element : &value)
//	{
//        push_back(element);
//	}
//    return *this;
//}


