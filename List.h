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

    enum class EXCEPTIONS {
        ITERATOR_HAS_NO_LIST,
        ITERATOR_OUT_OF_LIST,
        ITERATOR_HAS_NO_NEXT,
    };

    Node *head;
    Node *tail;
    int size;

    void nullify();

    int calcIndex(int index = 0);

    static const char *PARSE_EXCEPTION(EXCEPTIONS exception);

    void checkForEmptyList();

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

    Data getAt(int index = 0);

    void setAt(Data data = Data(), int index = 0);

    int indexOf(Data data = Data());

    void remove(Data data = Data());

    Node *operator[](int index) const;

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

        void checkForExceptions();
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

        void checkForExceptions();
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
List<Data>::List(int size) {
    if (size < 0) {
        throw invalid_argument("List size must be non-negative");
    }
    this->nullify();
    for (int i = 0; i < size; ++i) {
        this->push(Data(rand() % 201 - 100));
    }
}

template<class Data>
List<Data>::List(const List<Data> &list) {
    this->nullify();
    for (int i = 0; i < list.getSize(); i++) {
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
        this->nullify();
    }
}

template<class Data>
void List<Data>::remove(Data data) {
    int index;
    try {
        index = this->indexOf(data);
    }
    catch (exception ex) {
        cout << ex.what();
        return;
    }
    if (index < 0) {
        cout << "Can't find data in list" << endl;
        return;
    }
    pop(index);
}

template<class Data>
int List<Data>::indexOf(Data data) {
    this->checkForExceptions();
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
void List<Data>::push(Data data, int index) {
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
        this->size++;
    } else {
        // DOC: add node to tail + index (tail - abs(index))
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
    if (this->calcIndex(index) == -1)
        throw invalid_argument("Index out of bounds");
    if (index < 0) {
        index = this->size + index;
    }
    Node *node = nullptr;
    if (index == 0) {
        node = this->head;
        this->head = this->head->getNext();
        this->head->setPrev(nullptr);
        return node->getData();
    }
    if (index == this->size - 1) {
        node = this->operator[](index);
        this->tail = node->getPrev();
        this->tail->setNext(nullptr);
        return node->getData();
    }
    if (index > 0) {
        node = this->operator[](index);
        node->getPrev()->setNext(node->getNext());
        node->getNext()->setPrev(node->getPrev());
        return node->getData();
    }
    throw runtime_error("Unknown exception"); // FIXME: correct exception type
}

template<class Data>
bool List<Data>::contains(Data data) {
    for (auto it = this->begin(); it.hasNode(); it++) {
        if (it.getData() == data) {
            return true;
        }
    }
    return false;
}

template<class Data>
void List<Data>::print() {
    if (this->isEmpty()) {
        cout << "<empty list>" << endl;
        return;
    }
    for (auto it = this->begin(); it.hasNode(); it++) {
        cout << it.getData() << " ";
    }
    cout << endl;
}

template<class Data>
typename List<Data>::Node *List<Data>::operator[](int index) const {
    // TODO: Do exceptions
    this->checkForEmptyList();
    
    Node *node = this->head;
    for (int i = 0; i < index; i++) {
        node = node->getNext();
    }
    return node;
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
    return rIterator(this);;
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
        case EXCEPTIONS::ITERATOR_OUT_OF_LIST:
            return "ERROR: iterator is out of the list";
        default:
            return "UNKNOWN ERROR: iterator error";
    }
}

template<class Data>
void List<Data>::nullify() {
    this->head = this->tail = nullptr;
    this->size = 0;
}

template<class Data>
Data List<Data>::getAt(int index) {
    this->checkForEmptyList();
    // TODO: realize like push method + add exceptions
    return this->operator[](index)->getData();
}

template<class Data>
void List<Data>::setAt(Data data, int index) {
    // TODO: realize like push method + add exceptions
    return this->operator[](index)->setData(data);
}

template<class Data>
void List<Data>::checkForEmptyList() {
    if (this->isEmpty()) {
        throw runtime_error("List is empty"); // FIXME: exception type
    }
}

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
    this->checkForExceptions();
    this->node = this->node->getNext();
}

template<class Data>
bool List<Data>::Iterator::hasList() {
    return this->list != nullptr;
}

template<class Data>
Data List<Data>::Iterator::getData() {
    if (!this->hasList()) {
        throw runtime_error(PARSE_EXCEPTION(EXCEPTIONS::ITERATOR_HAS_NO_LIST));
    }
    if (!this->hasNode()) {
        throw runtime_error(PARSE_EXCEPTION(EXCEPTIONS::ITERATOR_OUT_OF_LIST));
    }
    return this->node->getData();
}

template<class Data>
void List<Data>::Iterator::toHead() {
    if (!this->hasList()) {
        throw runtime_error(PARSE_EXCEPTION(EXCEPTIONS::ITERATOR_HAS_NO_LIST));
    }
    this->node = this->list->getHead();
}

template<class Data>
void List<Data>::Iterator::toTail() {
    if (!this->hasList()) {
        throw runtime_error(PARSE_EXCEPTION(EXCEPTIONS::ITERATOR_HAS_NO_LIST));
    }
    this->node = this->list->getTail();
}

template<class Data>
void List<Data>::Iterator::setData(Data data) {
    if (!this->hasList()) {
        throw runtime_error(PARSE_EXCEPTION(EXCEPTIONS::ITERATOR_HAS_NO_LIST));
    }
    if (!this->hasNode()) {
        throw runtime_error(PARSE_EXCEPTION(EXCEPTIONS::ITERATOR_OUT_OF_LIST));
    }
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
    this->checkForExceptions();
    return this->node;
}

template<class Data>
void List<Data>::Iterator::checkForExceptions() {
    if (!this->hasList()) {
        throw runtime_error(PARSE_EXCEPTION(EXCEPTIONS::ITERATOR_HAS_NO_LIST));
    }
    if (!this->hasNode()) {
        throw runtime_error(PARSE_EXCEPTION(EXCEPTIONS::ITERATOR_OUT_NO_NODE));
    }
}

template<class Data>
void List<Data>::Iterator::prev() {
    this->checkForExceptions();
    this->node = this->node->getPrev();
}

template<class Data>
void List<Data>::Iterator::operator--(int) {
    this->prev()
}

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
    if (!this->hasList()) {
        throw runtime_error(PARSE_EXCEPTION(EXCEPTIONS::ITERATOR_HAS_NO_LIST));
    }
    if (!this->hasNode()) {
        throw runtime_error(PARSE_EXCEPTION(EXCEPTIONS::ITERATOR_OUT_OF_LIST));
    }
    this->node = this->node->getPrev();
}

template<class Data>
bool List<Data>::rIterator::hasList() {
    return this->list != nullptr;
}

template<class Data>
Data List<Data>::rIterator::getData() {
    if (!this->hasList()) {
        throw runtime_error(PARSE_EXCEPTION(EXCEPTIONS::ITERATOR_HAS_NO_LIST));
    }
    if (!this->hasNode()) {
        throw runtime_error(PARSE_EXCEPTION(EXCEPTIONS::ITERATOR_OUT_OF_LIST));
    }
    return this->node->getData();
}

template<class Data>
void List<Data>::rIterator::toHead() {
    if (!this->hasList()) {
        throw runtime_error(PARSE_EXCEPTION(EXCEPTIONS::ITERATOR_HAS_NO_LIST));
    }
    this->node = this->list->getHead();
}

template<class Data>
void List<Data>::rIterator::toTail() {
    if (!this->hasList()) {
        throw runtime_error(PARSE_EXCEPTION(EXCEPTIONS::ITERATOR_HAS_NO_LIST));
    }
    this->node = this->list->getTail();
}

template<class Data>
void List<Data>::rIterator::setData(Data data) {
    this->checkForExceptions();
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
    this->checkForExceptions();
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
void List<Data>::rIterator::checkForExceptions() {
    if (!this->hasList()) {
        throw runtime_error(PARSE_EXCEPTION(EXCEPTIONS::ITERATOR_HAS_NO_LIST));
    }
    if (!this->hasNode()) {
        throw runtime_error(PARSE_EXCEPTION(EXCEPTIONS::ITERATOR_OUT_OF_LIST));
    }
}

#endif //LAB1_LIST_H
