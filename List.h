//
// Created by danil on 05.09.2020.
//

#ifndef LAB1_LIST_H
#define LAB1_LIST_H

#include <ctime>
#include <iostream>

using namespace std;

template<class Data = int>
class List {
private:
    class Node {
    private:
        Data data;
        Node *next;
        Node *prev;
    public:
        Node(Data data = Data(), Node *next = nullptr, Node *prev = nullptr) {
            this->data = data;
            this->next = next;
            this->prev = prev;
        }

        Data getData() {
            return this->data;
        }

        void setData(Data data) {
            this->data = data;
        }

        Node *getNext() {
            return next;
        }

        void setNext(Node *next) {
            this->next = next;
        }

        Node *getPrev() {
            return prev;
        }

        void setPrev(Node *prev) {
            this->prev = prev;
        }

        void setNextToNull() {
            this->next = nullptr;
        }

        void setPrevToNull() {
            this->prev = nullptr;
        }
    };

    Node *head;
    Node *tail;
    int size;

    void increaseSize() {
        this->size++;
    }

public:
    List(int size = 0) {
        this->size = 0;
        if (size > 0) {
            this->head = this->tail = nullptr;
            for (int i = 0; i < size; ++i) {
                this->push(Data(rand() % 201 - 100));
            }
        } else if (size < 0) {
            throw invalid_argument("List size must be non-negative");
        } else {
            this->head = this->tail = nullptr;
        }
    }

    List(const List &list) {
        // TODO: logic for creating copy of list instance
    }

    ~List() {
        if (!this->isEmpty()) {
            Node *node = this->head;
            while (node) {
                Node *nodeToRemove = node;
                node = node->getNext();
                delete nodeToRemove;
            }
        }
    }

    int getSize() {
        return size;
    }

    bool isEmpty() {
        return size == 0;
    }

    void push(Data data = Data(), int index = -1) {
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
            // TODO: logic for add node to positive index (from head node)
        } else {
            // add node to tail + index (tail - abs(index))
            // TODO: logic for add node to negative index (from tail node)
        }
    }

    void print() {
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
};


#endif //LAB1_LIST_H
