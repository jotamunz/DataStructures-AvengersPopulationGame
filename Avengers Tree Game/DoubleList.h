#ifndef DOUBLELIST_H
#define DOUBLELIST_H
#include <Person.h>
#include <QDebug>

struct Node
{
    Node *next, *previous;
    Person* person;

    Node(Person* _person)
    {
        this->next = this->previous = nullptr;
        this->person = _person;
    }
};

struct DoubleList
{
    Node *first, *last;
    int size;

    DoubleList()
    {
        this->first = this->last = nullptr;
        this->size = 0;
    }

    bool isEmpty() { return this->first == nullptr; }

    void insertLast(Person* person)
    {
        if (this->isEmpty()) this->last = this->first = new Node(person);
        else
        {
            this->last->next = new Node(person);
            this->last->next->previous = this->last;
            this->last = this->last->next;
        }
        this->size++;
    }

    void insertFirst(Person* person)
    {
        if (this->isEmpty()) this->last = this->first = new Node(person);
        else
        {
            this->first->previous = new Node(person);
            this->first->previous->next = this->first;
            this->first = this->first->previous;
        }
        this->size++;
    }

    void insertOrdered(Person* person)
    {
        if (this->isEmpty() || person->id <= this->first->person->id)
            insertFirst(person);
        else
        {
            Node* temp = this->first;
            while (temp->next != nullptr && person->id > temp->next->person->id)
                temp = temp->next;
            insertAfter(person, temp);
        }
    }

    void insertAfter(Person* person, Node* index)
    {
        if (index == last)
            return insertLast(person);
        else
        {
            Node* temp = new Node(person);
            temp->previous = index;
            temp->next = index->next;
            index->next->previous = temp;
            index->next = temp;
            this->size++;
        }
    }

    Node* getPosition(int position)
    {
       Node* temp = this->first;
       if (position < this->size)
       {
           for (int i = 0; i < position; i++)
               temp = temp->next;
           return temp;
       }
       return nullptr;
    }

    void print()
    {
        Node* temp = this->first;
        QString str = "";
        int count = 0;
        while(temp != nullptr)
        {
            count++;
            str += QVariant(temp->person->id).toString() + " ";
            temp = temp->next;
        }
        qDebug().noquote() << str;
        qDebug().noquote() << "Total:" << count;
    }
};

#endif // DOUBLELIST_H
