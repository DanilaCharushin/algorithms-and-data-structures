//
// Created by danil on 05.09.2020.
//
//TODO: Iterator back steps

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

    enum class EXCEPTIONS {
        EMPTY_LIST,
        INVALID_DATA,
        INVALID_INDEX,
        INVALID_LIST_SIZE,
        ITERATOR_HAS_NO_LIST,
        ITERATOR_HAS_NO_NODE,
    };

    Node *head;
    Node *tail;
    int size;

    void nullify();

    int calcIndex(int index = 0);

    static const char *PARSE_EXCEPTION(EXCEPTIONS exception);

    void checkEmptyListException();

    void checkListSizeException(int size);

    void checkInvalidDataException(Data data);

    void checkInvalidIndexException(int index);

    Node *getNodeAt(int &counter, int index);

public:
    explicit List(int size = 0);

    List(const List<Data> &list);

    ~List();

    Node *getHead();

    Node *getTail();

    int getSize();

    bool isEmpty();

    void clear();

    void push(int &counter, Data data = Data(), int index = -1);

    Data pop(int &counter, int index = 0);

    bool contains(int &counter, Data data = Data());

    void print();

    Data getAt(int &counter, int index = 0);

    void setAt(int &counter, Data data = Data(), int index = 0);

    int indexOf(Data data = Data());

    void remove(int &counter, Data data = Data());

    Node *operator[](int index);

    class Iterator {
        List<Data> *list;
        Node *node;

    public:
        explicit Iterator(List<Data> *list = nullptr);

        void setList(List<Data> *list = nullptr);

        void next();

        void prev();

        void operator++(int);

        void operator--(int);

        bool hasList();

        bool hasNode();

        Node *operator*();

        Data getData();

        void setData(Data data = Data());

        void toHead();

        void toTail();

        void checkNoListException();

        void checkNoNodeException();

        void checkAllExceptions();
    };

    class rIterator {
        List<Data> *list;
        Node *node;

    public:
        explicit rIterator(List<Data> *list = nullptr);

        void setList(List<Data> *list = nullptr);

        void next();

        void prev();

        void operator++(int);

        void operator--(int);

        bool hasList();

        bool hasNode();

        Node *operator*();

        Data getData();

        void setData(Data data = Data());

        void toHead();

        void toTail();

        void checkNoListException();

        void checkNoNodeException();

        void checkAllExceptions();
    };

    friend class Iterator;

    friend class rIterator;

    Iterator begin();

    Iterator end();

    rIterator rbegin();

    rIterator rend();
};

// #####################################################
//                        Node
// #####################################################

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

// #####################################################
//                        List
// #####################################################

template<class Data>
List<Data>::List(int size) {
    this->checkListSizeException(size);
    this->nullify();
    int foo = 0;
    for (int i = 0; i < size; ++i) {
        this->push(foo, Data(rand() % 201 - 100));
    }
}

template<class Data>
List<Data>::List(const List<Data> &list) {
    this->nullify();
    int foo = 0;
    for (int i = 0; i < list.getSize(); i++) {
        this->push(foo, list[i]->getData());
    }
}

template<class Data>
List<Data>::~List() {
    this->clear();
}

template<class Data>
typename List<Data>::Node *List<Data>::getHead() {
    return this->head;
}

template<class Data>
typename List<Data>::Node *List<Data>::getTail() {
    return this->tail;
}

template<class Data>
int List<Data>::getSize() {
    return this->size;
}

template<class Data>
bool List<Data>::isEmpty() {
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
        this->nullify();
    }
}

template<class Data>
void List<Data>::remove(int &counter, Data data) {
    this->checkEmptyListException();
    this->checkInvalidDataException(data);
    this->pop(counter, this->indexOf(data));
}

template<class Data>
int List<Data>::indexOf(Data data) {
    this->checkEmptyListException();
    int index = 0;
    for (auto it = this->begin(); it.hasNode(); it++) {
        if (it.getData() == data) {
            return index;
        }
        index++;
    }
    return -1;
}

template<class Data>
int List<Data>::calcIndex(int index) {
    if (index < -this->size || index >= this->size) {
        return -1;
    }
    if (index < 0) {
        index += this->size;
    }
    return index;
}

template<class Data>
void List<Data>::push(int &counter, Data data, int index) {
    if (this->isEmpty()) {
        // DOC: add first node
        Node *node = new Node(data);
        this->head = this->tail = node;
        this->size++;
    } else if (index == 0) {
        // DOC: add node to head
        Node *node = new Node(data, this->head, nullptr);
        this->head->setPrev(node);
        this->head = node;
        this->size++;
    } else if (index == -1) {
        // DOC: add node to tail
        Node *node = new Node(data, nullptr, this->tail);
        this->tail->setNext(node);
        this->tail = node;
        this->size++;
    } else if (index > 0) {
        // DOC: add node to head + index
        if (index >= this->size) {
            this->push(counter, data);
            if (index > this->size)
                cout << "INFO: index > list size, => index = size" << endl;
            return;
        }
        Node *nodeAfter = this->head;
        for (int i = 0; i < index; ++i) {
            nodeAfter = nodeAfter->getNext();
            counter++;
        }
        Node *node = new Node(data, nodeAfter, nodeAfter->getPrev());
        nodeAfter->getPrev()->setNext(node);
        nodeAfter->setPrev(node);
        this->size++;
    } else {
        // DOC: add node to tail + index (tail - abs(index))
        if (abs(index) >= this->size + 1) {
            this->push(data, 0);
            if (abs(index) > this->size + 1)
                cout << "INFO: abs(index) > list size + 1, => index = 0" << endl;
            return;
        }
        this->push(counter, data, this->size + 1 + index);
    }
}

template<class Data>
Data List<Data>::pop(int &counter, int index) {
    this->checkEmptyListException();
    index = this->calcIndex(index);
    this->checkInvalidIndexException(index);
    Node *node = nullptr;
    if (index == 0) {
        node = this->head;
        this->head = this->head->getNext();
        this->head->setPrev(nullptr);
        return node->getData();
    } else if (index == this->size - 1) {
        node = this->getNodeAt(counter, index);
        this->tail = node->getPrev();
        this->tail->setNext(nullptr);
        return node->getData();
    } else {
        node = this->getNodeAt(counter, index);
        node->getPrev()->setNext(node->getNext());
        node->getNext()->setPrev(node->getPrev());
        return node->getData();
    }
}

template<class Data>
bool List<Data>::contains(int &counter, Data data) {
    this->checkEmptyListException();
    for (auto it = this->begin(); it.hasNode(); it++) {
        if (it.getData() == data) {
            return true;
        }
        counter++;
    }
    return false;
}

template<class Data>
void List<Data>::print() {
    if (this->isEmpty()) {
        cout << "<empty list>" << endl;
    } else {
        for (auto it = this->begin(); it.hasNode(); it++) {
            cout << it.getData() << " ";
        }
        cout << endl;
    }

}

template<class Data>
typename List<Data>::Node *List<Data>::operator[](int index) {
    return this->getNodeAt(0, index);
}

template<class Data>
typename List<Data>::Iterator List<Data>::begin() {
    return Iterator(this);
}

template<class Data>
typename List<Data>::Iterator List<Data>::end() {
    Iterator iterator(this);
    iterator.toTail();
    return iterator;
}

template<class Data>
typename List<Data>::rIterator List<Data>::rbegin() {
    return rIterator(this);
}

template<class Data>
typename List<Data>::rIterator List<Data>::rend() {
    rIterator iterator(this);
    iterator.toHead();
    return iterator;
}

template<class Data>
const char *List<Data>::PARSE_EXCEPTION(EXCEPTIONS exception) {
    switch (exception) {
        case EXCEPTIONS::ITERATOR_HAS_NO_LIST:
            return "ERROR: iterator has no list";
        case EXCEPTIONS::ITERATOR_HAS_NO_NODE:
            return "ERROR: iterator is out of the list";
        case EXCEPTIONS::INVALID_DATA:
            return "ERROR: list 12doesn't contain this value";
        case EXCEPTIONS::INVALID_LIST_SIZE:
            return "ERROR: list size must be non-negative";
        case EXCEPTIONS::EMPTY_LIST:
            return "ERROR: list is empty";
        case EXCEPTIONS::INVALID_INDEX:
            return "ERROR: index out of bounds";
        default:
            return "ERROR: unknown error";
    }
}

template<class Data>
void List<Data>::nullify() {
    this->head = this->tail = nullptr;
    this->size = 0;
}

template<class Data>
Data List<Data>::getAt(int &counter, int index) {
    this->checkEmptyListException();
    index = this->calcIndex(index);
    this->checkInvalidIndexException(index);
    return this->getNodeAt(counter, index)->getData();
}

template<class Data>
void List<Data>::setAt(int &counter, Data data, int index) {
    this->checkEmptyListException();
    index = this->calcIndex(index);
    this->checkInvalidIndexException(index);
    this->getNodeAt(counter, index)->setData(data);
}

template<class Data>
void List<Data>::checkEmptyListException() {
    if (this->isEmpty()) {
        throw runtime_error(PARSE_EXCEPTION(EXCEPTIONS::EMPTY_LIST));
    }
}

template<class Data>
void List<Data>::checkListSizeException(int size) {
    if (size < 0) {
        throw runtime_error(PARSE_EXCEPTION(EXCEPTIONS::INVALID_LIST_SIZE));
    }
}

template<class Data>
void List<Data>::checkInvalidDataException(Data data) {
    int foo = 0;
    if (!this->contains(foo, data)) {
        throw invalid_argument(PARSE_EXCEPTION(EXCEPTIONS::INVALID_DATA));
    }
}

template<class Data>
void List<Data>::checkInvalidIndexException(int index) {
    if (index == -1) {
        throw out_of_range(PARSE_EXCEPTION(EXCEPTIONS::INVALID_INDEX));
    }
}

template<class Data>
typename List<Data>::Node *List<Data>::getNodeAt(int &counter, int index) {
    Node *node = this->head;
    for (int i = 0; i < index; i++, counter++) {
        node = node->getNext();
    }
    return node;
}

// #####################################################
//                       Iterator
// #####################################################

template<class Data>
List<Data>::Iterator::Iterator(List<Data> *list) {
    this->setList(list);
}

template<class Data>
void List<Data>::Iterator::setList(List<Data> *list) {
    this->list = list;
    this->node = nullptr;
    if (list) {
        this->node = list->getHead();
    }
}

template<class Data>
void List<Data>::Iterator::next() {
    this->checkAllExceptions();
    this->node = this->node->getNext();
}

template<class Data>
bool List<Data>::Iterator::hasList() {
    return this->list != nullptr;
}

template<class Data>
Data List<Data>::Iterator::getData() {
    this->checkAllExceptions();
    return this->node->getData();
}

template<class Data>
void List<Data>::Iterator::toHead() {
    this->checkNoListException();
    this->node = this->list->getHead();
}

template<class Data>
void List<Data>::Iterator::toTail() {
    this->checkNoListException();
    this->node = this->list->getTail();
}

template<class Data>
void List<Data>::Iterator::setData(Data data) {
    this->checkAllExceptions();
    this->node->setData(data);
}

template<class Data>
void List<Data>::Iterator::operator++(int) {
    this->next();
}

template<class Data>
bool List<Data>::Iterator::hasNode() {
    return this->node != nullptr;
}

template<class Data>
typename List<Data>::Node *List<Data>::Iterator::operator*() {
    this->checkAllExceptions();
    return this->node;
}

template<class Data>
void List<Data>::Iterator::prev() {
    this->checkAllExceptions();
    this->node = this->node->getPrev();
}

template<class Data>
void List<Data>::Iterator::operator--(int) {
    this->prev();
}

template<class Data>
void List<Data>::Iterator::checkNoListException() {
    if (!this->hasList()) {
        throw runtime_error(PARSE_EXCEPTION(EXCEPTIONS::ITERATOR_HAS_NO_LIST));
    }
}

template<class Data>
void List<Data>::Iterator::checkNoNodeException() {
    if (!this->hasNode()) {
        throw runtime_error(PARSE_EXCEPTION(EXCEPTIONS::ITERATOR_HAS_NO_NODE));
    }
}

template<class Data>
void List<Data>::Iterator::checkAllExceptions() {
    this->checkNoListException();
    this->checkNoNodeException();
}

// #####################################################
//                       rIterator
// #####################################################

template<class Data>
List<Data>::rIterator::rIterator(List<Data> *list) {
    this->setList(list);
}

template<class Data>
void List<Data>::rIterator::setList(List<Data> *list) {
    this->list = list;
    this->node = nullptr;
    if (list) {
        this->node = list->getTail();
    }
}

template<class Data>
void List<Data>::rIterator::next() {
    this->checkAllExceptions();
    this->node = this->node->getPrev();
}

template<class Data>
bool List<Data>::rIterator::hasList() {
    return this->list != nullptr;
}

template<class Data>
Data List<Data>::rIterator::getData() {
    this->checkAllExceptions();
    return this->node->getData();
}

template<class Data>
void List<Data>::rIterator::toHead() {
    this->checkNoListException();
    this->node = this->list->getHead();
}

template<class Data>
void List<Data>::rIterator::toTail() {
    this->checkNoListException();
    this->node = this->list->getTail();
}

template<class Data>
void List<Data>::rIterator::setData(Data data) {
    this->checkAllExceptions();
    this->node->setData(data);
}

template<class Data>
void List<Data>::rIterator::operator++(int) {
    this->next();
}

template<class Data>
bool List<Data>::rIterator::hasNode() {
    return this->node != nullptr;
}

template<class Data>
typename List<Data>::Node *List<Data>::rIterator::operator*() {
    this->checkAllExceptions();
    return this->node;
}

template<class Data>
void List<Data>::rIterator::operator--(int) {
    this->prev();
}

template<class Data>
void List<Data>::rIterator::prev() {
    this->prev();
}

template<class Data>
void List<Data>::rIterator::checkNoListException() {
    if (!this->hasList()) {
        throw runtime_error(PARSE_EXCEPTION(EXCEPTIONS::ITERATOR_HAS_NO_LIST));
    }
}

template<class Data>
void List<Data>::rIterator::checkNoNodeException() {
    if (!this->hasNode()) {
        throw runtime_error(PARSE_EXCEPTION(EXCEPTIONS::ITERATOR_HAS_NO_NODE));
    }
}

template<class Data>
void List<Data>::rIterator::checkAllExceptions() {
    this->checkNoListException();
    this->checkNoNodeException();
}

#endif //LAB1_LIST_H
