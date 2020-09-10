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

    enum ITERATOR_EXCEPTIONS {
        NO_LIST,
        NO_NEXT,
        OUT_OF_LIST
    };

    Node *head;
    Node *tail;
    int size;

    void increaseSize();

    void nullify();

    bool hasIndex(int index = 0);

    static const char *PARSE_ITERATOR_EXCEPTION(int exception);

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

        void operator++(int);

        bool hasNext();

        bool hasList();

        bool inList();

        Node *operator*();

        Data getData();

        void setData(Data data = Data());

        void toHead();

        void toTail();
    };

    class rIterator {
        List<Data> *list;
        Node *node;

    public:
        explicit rIterator(List<Data> *list = nullptr);

        void setList(List<Data> *list = nullptr);

        void next();

        void operator++(int);

        bool hasNext();

        bool hasList();

        bool inList();

        Node *operator*();

        Data getData();

        void setData(Data data = Data());

        void toHead();

        void toTail();
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
        index = indexOf(data);
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
    if (this->isEmpty())
        throw runtime_error("List is empty"); // FIXME: exception type
    Node *node = head;
    for (int index = 0; node != nullptr; index++) {
        if (node->getData() == data)
            return index;
        node = node->getNext();
    }
    return -1;
}

template<class Data>
bool List<Data>::hasIndex(int index) {
    if (index >= 0) {
        if (index >= this->size)
            return false;
        else return true;
    } else {
        if (this->size + index + 1 < 0)
            return false;
        else return true;
    }
}

template<class Data>
void List<Data>::push(Data data, int index) {
    if (this->isEmpty()) {
        // DOC: add first node
        Node *node = new Node(data);
        this->head = this->tail = node;
        this->increaseSize();
    } else if (index == 0) {
        // DOC: add node to head
        Node *node = new Node(data, this->head, nullptr);
        this->head->setPrev(node);
        this->head = node;
        this->increaseSize();
    } else if (index == -1) {
        // DOC: add node to tail
        Node *node = new Node(data, nullptr, this->tail);
        this->tail->setNext(node);
        this->tail = node;
        this->increaseSize();
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
        this->increaseSize();
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
    if (!hasIndex(index))
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
    for (auto it = this->begin(); it.inList(); it++) {
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
    for (auto it = this->begin(); it.inList(); it++) {
        cout << it.getData() << " ";
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
    Iterator iterator(this);
    iterator.toHead();
    return iterator;
}

template<class Data>
typename List<Data>::Iterator List<Data>::end() {
    Iterator iterator(this);
    iterator.toTail();
    return iterator;
}

template<class Data>
typename List<Data>::rIterator List<Data>::rbegin() {
    rIterator iterator(this);
    iterator.toTail();
    return iterator;
}

template<class Data>
typename List<Data>::rIterator List<Data>::rend() {
    rIterator iterator(this);
    iterator.toHead();
    return iterator;
}

template<class Data>
const char *List<Data>::PARSE_ITERATOR_EXCEPTION(int exception) {
    switch (exception) {
        case ITERATOR_EXCEPTIONS::NO_LIST:
            return "ERROR: iterator has no list";
        case ITERATOR_EXCEPTIONS::NO_NEXT:
            return "ERROR: iterator has no next node";
        case ITERATOR_EXCEPTIONS::OUT_OF_LIST:
            return "ERROR: iterator is out of the list";
        default:
            return "ERROR: iterator error";
    }
}

template<class Data>
void List<Data>::nullify() {
    this->head = this->tail = nullptr;
    this->size = 0;
}

template<class Data>
Data List<Data>::getAt(int index) {
    // TODO: realize like push method + add exceptions
    return this->operator[](index)->getData();
}

template<class Data>
void List<Data>::setAt(Data data, int index) {
    // TODO: realize like push method + add exceptions
    return this->operator[](index)->setData(data);
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
    if (!this->hasList()) {
        throw runtime_error(PARSE_ITERATOR_EXCEPTION(ITERATOR_EXCEPTIONS::NO_LIST));
    }
    if (!this->inList()) {
        throw runtime_error(PARSE_ITERATOR_EXCEPTION(ITERATOR_EXCEPTIONS::OUT_OF_LIST));
    }
    this->node = this->node->getNext();
}

template<class Data>
bool List<Data>::Iterator::hasNext() {
    if (!this->hasList()) {
        throw runtime_error(PARSE_ITERATOR_EXCEPTION(ITERATOR_EXCEPTIONS::NO_LIST));
    }
    if (!this->inList()) {
        throw runtime_error(PARSE_ITERATOR_EXCEPTION(ITERATOR_EXCEPTIONS::OUT_OF_LIST));
    }
    return this->node->getNext() != nullptr;
}

template<class Data>
bool List<Data>::Iterator::hasList() {
    return this->list != nullptr;
}

template<class Data>
Data List<Data>::Iterator::getData() {
    if (!this->hasList()) {
        throw runtime_error(PARSE_ITERATOR_EXCEPTION(ITERATOR_EXCEPTIONS::NO_LIST));
    }
    if (!this->inList()) {
        throw runtime_error(PARSE_ITERATOR_EXCEPTION(ITERATOR_EXCEPTIONS::OUT_OF_LIST));
    }
    return this->node->getData();
}

template<class Data>
void List<Data>::Iterator::toHead() {
    if (!this->hasList()) {
        throw runtime_error(PARSE_ITERATOR_EXCEPTION(ITERATOR_EXCEPTIONS::NO_LIST));
    }
    this->node = this->list->getHead();
}

template<class Data>
void List<Data>::Iterator::toTail() {
    if (!this->hasList()) {
        throw runtime_error(PARSE_ITERATOR_EXCEPTION(ITERATOR_EXCEPTIONS::NO_LIST));
    }
    this->node = this->list->getTail();
}

template<class Data>
void List<Data>::Iterator::setData(Data data) {
    if (!this->hasList()) {
        throw runtime_error(PARSE_ITERATOR_EXCEPTION(ITERATOR_EXCEPTIONS::NO_LIST));
    }
    if (!this->inList()) {
        throw runtime_error(PARSE_ITERATOR_EXCEPTION(ITERATOR_EXCEPTIONS::OUT_OF_LIST));
    }
    this->node->setData(data);
}

template<class Data>
void List<Data>::Iterator::operator++(int) {
    this->next();
}

template<class Data>
bool List<Data>::Iterator::inList() {
    return this->node != nullptr;
}

template<class Data>
typename List<Data>::Node *List<Data>::Iterator::operator*() {
    if (!this->inList()) {
        throw runtime_error(PARSE_ITERATOR_EXCEPTION(ITERATOR_EXCEPTIONS::OUT_OF_LIST));
    }
    return this->node;
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
        throw runtime_error(PARSE_ITERATOR_EXCEPTION(ITERATOR_EXCEPTIONS::NO_LIST));
    }
    if (!this->inList()) {
        throw runtime_error(PARSE_ITERATOR_EXCEPTION(ITERATOR_EXCEPTIONS::OUT_OF_LIST));
    }
    this->node = this->node->getPrev();
}

template<class Data>
bool List<Data>::rIterator::hasNext() {
    if (!this->hasList()) {
        throw runtime_error(PARSE_ITERATOR_EXCEPTION(ITERATOR_EXCEPTIONS::NO_LIST));
    }
    if (!this->inList()) {
        throw runtime_error(PARSE_ITERATOR_EXCEPTION(ITERATOR_EXCEPTIONS::OUT_OF_LIST));
    }
    return this->node->getPrev() != nullptr;
}

template<class Data>
bool List<Data>::rIterator::hasList() {
    return this->list != nullptr;
}

template<class Data>
Data List<Data>::rIterator::getData() {
    if (!this->hasList()) {
        throw runtime_error(PARSE_ITERATOR_EXCEPTION(ITERATOR_EXCEPTIONS::NO_LIST));
    }
    if (!this->inList()) {
        throw runtime_error(PARSE_ITERATOR_EXCEPTION(ITERATOR_EXCEPTIONS::OUT_OF_LIST));
    }
    return this->node->getData();
}

template<class Data>
void List<Data>::rIterator::toHead() {
    if (!this->hasList()) {
        throw runtime_error(PARSE_ITERATOR_EXCEPTION(ITERATOR_EXCEPTIONS::NO_LIST));
    }
    this->node = this->list->getHead();
}

template<class Data>
void List<Data>::rIterator::toTail() {
    if (!this->hasList()) {
        throw runtime_error(PARSE_ITERATOR_EXCEPTION(ITERATOR_EXCEPTIONS::NO_LIST));
    }
    this->node = this->list->getTail();
}

template<class Data>
void List<Data>::rIterator::setData(Data data) {
    if (!this->hasList()) {
        throw runtime_error(PARSE_ITERATOR_EXCEPTION(ITERATOR_EXCEPTIONS::NO_LIST));
    }
    if (!this->inList()) {
        throw runtime_error(PARSE_ITERATOR_EXCEPTION(ITERATOR_EXCEPTIONS::OUT_OF_LIST));
    }
    this->node->setData(data);
}

template<class Data>
void List<Data>::rIterator::operator++(int) {
    this->next();
}

template<class Data>
bool List<Data>::rIterator::inList() {
    return this->node != nullptr;
}

template<class Data>
typename List<Data>::Node *List<Data>::rIterator::operator*() {
    if (!this->inList()) {
        throw runtime_error(PARSE_ITERATOR_EXCEPTION(ITERATOR_EXCEPTIONS::OUT_OF_LIST));
    }
    return this->node;
}

#endif //LAB1_LIST_H
