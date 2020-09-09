//
// Created by danil on 05.09.2020.
//

#ifndef LAB1_LIST_H
#define LAB1_LIST_H

#include <ctime>
#include <iostream>

using namespace std;

typedef int DEFAULT_TYPE;

template<class Data = DEFAULT_TYPE>
class List {
private:
    class Node {
    private:
        Data data;
        Node *next;
        Node *prev;
    public:
        explicit Node(Data data = Data(), Node *next = nullptr, Node *prev = nullptr);

        Data getData();

        void setData(Data data = Data());

        Node *getNext();

        void setNext(Node *next = nullptr);

        Node *getPrev();

        void setPrev(Node *prev = nullptr);
    };

    Node *head;
    Node *tail;
    int size;

    void increaseSize();

public:
    explicit List(int size = 0);

    List(const List<Data> &list);

    ~List();

    Node *getHead() const;

    Node *getTail() const;

    int getSize() const;

    bool isEmpty() const;

    void clear();

    void push(Data data = Data(), int index = -1);

    Data pop(int index = 0);

    bool contains(Data data = Data());

    void print();

    Node *operator[](int index) const;

    class Iterator {
        List<Data> *list;
        Node *node;

        explicit Iterator(const List<Data> &list = nullptr);

        void setList(const List<Data> &list = nullptr);

        void next();

        bool hasNext();

        void operator++(int);

        Data getData();

        void setData(Data data = Data());

        void toHead();

        bool hasList();

        Data &operator*();
    };

    class rIterator {
        List<Data> *list;
        Node *node;

        explicit rIterator(const List<Data> &list = nullptr);

        void setList(const List<Data> &list = nullptr);
    };

    friend class Iterator;

    friend class rIterator;

    Iterator begin();

    Iterator end();

    rIterator rbegin();

    rIterator rend();

};

template<class Data>
List<Data>::Node::Node(Data data, Node *next, Node *prev) {
    this->data = data;
    this->next = next;
    this->prev = prev;
}

template<class Data>
Data List<Data>::Node::getData() { return this->data; }

template<class Data>
void List<Data>::Node::setData(Data data) { this->data = data; }

template<class Data>
typename List<Data>::Node *List<Data>::Node::getNext() { return this->next; }

template<class Data>
void List<Data>::Node::setNext(Node *next) { this->next = next; }

template<class Data>
typename List<Data>::Node *List<Data>::Node::getPrev() { return this->prev; }

template<class Data>
void List<Data>::Node::setPrev(Node *prev) { this->prev = prev; }

template<class Data>
void List<Data>::increaseSize() { this->size++; }

template<class Data>
List<Data>::List(int size) {
    this->size = 0;
    if (size > 0) {
        this->head = this->tail = nullptr;
        for (int i = 0; i < size; ++i) {
            this->push(Data(rand() % 201 - 100));
        }
    } else if (size == 0) {
        this->head = this->tail = nullptr;
    } else {
        throw invalid_argument("List size must be non-negative");
    }
}

template<class Data>
List<Data>::List(const List<Data> &list) {
    this->head = this->tail = nullptr;
    int k = list.getSize();
    for (int i = 0; i < k; i++) {
        this->push(list[i]->getData());
    }
}

template<class Data>
List<Data>::~List() {
    this->clear();
}

template<class Data>
typename List<Data>::Node *List<Data>::getHead() const {
    return this->head;
}

template<class Data>
typename List<Data>::Node *List<Data>::getTail() const {
    return this->tail;
}

template<class Data>
int List<Data>::getSize() const {
    return this->size;
}

template<class Data>
bool List<Data>::isEmpty() const {
    return this->size == 0;
}

template<class Data>
void List<Data>::clear() {
    if (!this->isEmpty()) {
        Node *node = this->head;
        while (node) {
            Node *nodeToRemove = node;
            node = node->getNext();
            delete nodeToRemove;
        }
        this->head = this->tail = nullptr;
    }
}

template<class Data>
void List<Data>::push(Data data, int index) {
    if (this->isEmpty()) {
        // add first node
        Node *node = new Node(data);
        this->head = this->tail = node;
        this->increaseSize();
    } else if (index == 0) {
        // add node to head
        Node *node = new Node(data, this->head, nullptr);
        this->head->setPrev(node);
        this->head = node;
        this->increaseSize();
    } else if (index == -1) {
        // add node to tail
        Node *node = new Node(data, nullptr, this->tail);
        this->tail->setNext(node);
        this->tail = node;
        this->increaseSize();
    } else if (index > 0) {
        // add node to head + index
        if (index >= this->size) {
            this->push(data);
            if (index > this->size)
                cout << "INFO: index > list size, => index = size" << endl;
            return;
        }
        Node *nodeAfter = this->head;
        for (int i = 0; i < index; ++i) {
            nodeAfter = nodeAfter->getNext();
        }
        Node *node = new Node(data, nodeAfter, nodeAfter->getPrev());
        nodeAfter->getPrev()->setNext(node);
        nodeAfter->setPrev(node);
        this->increaseSize();
    } else {
        // add node to tail + index (tail - abs(index))
        if (abs(index) >= this->size + 1) {
            this->push(data, 0);
            if (abs(index) > this->size + 1)
                cout << "INFO: abs(index) > list size + 1, => index = 0" << endl;
            return;
        }
        this->push(data, this->size + 1 + index);
    }
}

template<class Data>
Data List<Data>::pop(int index) {
    // TODO: Do pop
    // test
}


template<class Data>
bool List<Data>::contains(Data data) {
    auto it = this->begin();
    while (it.hasNext()) { // FIXME: wtf
        if (*it == data) { // FIXME: wtf
            return true;
        }
        it++; // FIXME: wtf
    }
    return false;
}

template<class Data>
void List<Data>::print() {
    if (this->isEmpty()) {
        cout << "<empty list>" << endl;
        return;
    }
    Node *node = this->head;
    while (node) {
        cout << node->getData() << " ";
        node = node->getNext();
    }
    cout << endl;
}

template<class Data>
typename List<Data>::Node *List<Data>::operator[](int index) const {
    // TODO: Do exceptions
    if (this->size == 0) {
        cout << "INFO: list is empty, cannot get node by index" << endl;
        return nullptr;
    }
    Node *node = this->head;
    for (int i = 0; i < index; i++) {
        node = node->getNext();
    }
    return node;
}

template<class Data>
typename List<Data>::Iterator List<Data>::begin() {
    return List::Iterator(*this); // FIXME: wtf
}

template<class Data>
typename List<Data>::Iterator List<Data>::end() {
    return List::Iterator(this);
}

template<class Data>
typename List<Data>::rIterator List<Data>::rbegin() {
    return List::rIterator(this);
}

template<class Data>
typename List<Data>::rIterator List<Data>::rend() {
    return List::rIterator(this);
}

template<class Data>
List<Data>::Iterator::Iterator(const List<Data> &list) {
    this->list = list;
    this->node = list.getHead();
}

template<class Data>
void List<Data>::Iterator::setList(const List<Data> &list) {
    this->list = list;
    this->node = list.getHead();
}

template<class Data>
void List<Data>::Iterator::next() {
    // TODO: add some exceptions
    this->node = this->node->getNext();
}

template<class Data>
Data &List<Data>::Iterator::operator*() {
    return this->node->data;
}

template<class Data>
bool List<Data>::Iterator::hasNext() {
    // README: в таком стиле предлагаю кидать исключения
    if (this->hasList()) {
        return this->node->getNext() != nullptr;
    } else {
        throw runtime_error("Iterator is out of the list!");
    }

}

template<class Data>
void List<Data>::Iterator::operator++(int) {
    this->next();
}

template<class Data>
bool List<Data>::Iterator::hasList() {
    return this->list != nullptr;
}

template<class Data>
List<Data>::rIterator::rIterator(const List<Data> &list) {
    this->list = list;
    this->node = list.getTail();
}

template<class Data>
void List<Data>::rIterator::setList(const List<Data> &list) {
    this->list = list;
    this->node = list.getTail();
}


#endif //LAB1_LIST_H
