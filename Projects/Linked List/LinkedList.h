#pragma once
#include <iostream>
#include <vector>

using namespace std;

template<typename T> class LinkedList
{
public:

    struct Node
    {
    public:
        Node* next;
        Node* prev;
        T data;
    };

    unsigned int size;
    Node* headPointer;
    Node* tailPointer;

    //Behaviors
    //*****
    void PrintForward() const
    {
        Node* tempPtr = headPointer;
        while(tempPtr != nullptr)
        {
            cout << tempPtr->data << endl;
            tempPtr = tempPtr->next;
        }
    };

    //*******
    void PrintReverse() const
    {
        Node* tempPtr = tailPointer;
        while(tempPtr != nullptr)
        {
            cout << tempPtr->data << endl;
            tempPtr = tempPtr->prev;
        }
    };

    void PrintForwardRecursive(const Node* node) const
    {
        if (node != nullptr)
        {
            cout << node->data << endl;
            PrintForwardRecursive(node->next);
        }
        else
        {
            return;
        }
    };

    void PrintReverseRecursive(const Node* node) const
    {
        if (node != nullptr)
        {
            cout << node->data << endl;
            PrintReverseRecursive(node->prev);
        }
        else
        {
            return;
        }
    };

    const Node* Find(const T& _data) const
    {
        Node* tempPtr = headPointer;
        while(tempPtr != nullptr)
        {
            //Possible error with comparison
            if(tempPtr->data == _data)
            {
                return tempPtr;
            }
            tempPtr = tempPtr->next;
        }
        return nullptr;
    };

    Node* Find(const T& _data)
    {
        Node* tempPtr = headPointer;
        while(tempPtr != nullptr)
        {
            //Possible error with comparison
            if(tempPtr->data == _data)
            {
                return tempPtr;
            }
            tempPtr = tempPtr->next;
        }
        return nullptr;
    };

    void FindAll(vector<Node*>& outData, const T& _value) const
    {
        Node* tempPtr = headPointer;
        while(tempPtr != nullptr)
        {
            if (tempPtr->data == _value)
            {
                outData.push_back(tempPtr);
            }
            tempPtr = tempPtr->next;
        }
    };

    void Clear()
    {
        Node *tempPtr = headPointer;
        while(tempPtr != nullptr) {
            if (tempPtr->next == nullptr) {
                delete tempPtr->prev;
                delete tempPtr;
                tempPtr = nullptr;
            } else {
                delete tempPtr->prev;
                tempPtr = tempPtr->next;
            }
        }
        this->headPointer = nullptr;
        this->tailPointer = nullptr;
        this->size = 0;
    };

    bool RemoveHead()
    {
        //Make Temp Pointer to hold the second in list and then set it to headPointer and delte;
        //Likely a bug in the logic here. May need have duplicate????

        if(this->headPointer == nullptr)
        {
            return false;
        }
        else if(this->headPointer->next == nullptr)
        {
            delete this->headPointer;
            this->headPointer = nullptr;
            this->tailPointer = nullptr;
            this->size -= 1;
            return true;
        }
        else {
            Node *tempPtr = this->headPointer->next;
            tempPtr->prev = nullptr;
            delete this->headPointer;
            this->headPointer = tempPtr;
            this->size -= 1;
            return true;
        }
        return false;
    };

    bool RemoveTail()
    {
        if(this->tailPointer == nullptr)
        {
            return false;
        }
        else if(this->tailPointer->prev == nullptr)
        {
            delete this->tailPointer;
            this->headPointer = nullptr;
            this->tailPointer = nullptr;
            this->size -= 1;
            return true;
        }
        else {
            Node *tempPtr = this->tailPointer->prev;
            tempPtr->next = nullptr;
            delete this->tailPointer;
            this->tailPointer = tempPtr;
            this->size -= 1;
            return true;
        }

    };

    bool RemoveAt(unsigned int index)
    {
        if(index >= size)
        {
            return false;
        }

        Node* tempPtr = GetNode(index);

        if (tempPtr->next == nullptr)
        {
            RemoveTail();
            return true;
        }
        else if (tempPtr->prev == nullptr)
        {
            RemoveHead();
            return true;
        }
        else{
            Node* a = tempPtr->next;
            tempPtr->next->prev = tempPtr->prev;
            tempPtr->prev->next = tempPtr->next;
            delete tempPtr;
            tempPtr=a;
            this->size-=1;
        }
        return false;
    }

    unsigned int Remove(const T& _data)
    {
        unsigned int nodesRemoved = 0;
        Node* tempPtr = headPointer;
        while(tempPtr != nullptr)
        {

            if(tempPtr->data == _data)
            {
                if (tempPtr->prev == nullptr){
                    RemoveHead();
                    nodesRemoved += 1;
                }
                else if(tempPtr->next == nullptr)
                {
                    RemoveTail();
                    nodesRemoved += 1;
                }
                else{
                    //delete tempPtr->next->prev;
                    Node* a = tempPtr->next;
                    tempPtr->next->prev = tempPtr->prev;
                    tempPtr->prev->next = tempPtr->next;
                    nodesRemoved += 1;
                    delete tempPtr;
                    tempPtr=a;
                    this->size-=1;
                }
            }
            tempPtr=tempPtr->next;
        }
        delete tempPtr;
        return nodesRemoved;
    };

    //Accessors
    //******
    unsigned int NodeCount() const
    {
        return this->size;
    };


    //Insertion
    //****
    void AddHead(const T& _data)
    {
        Node* temp = new Node;
        temp->data = _data;
        if(headPointer == nullptr && tailPointer == nullptr)
        {
            headPointer = temp;
            tailPointer = temp;
            temp->next = nullptr;
            temp->next = nullptr;
        }
        else if(headPointer->next == nullptr && tailPointer->prev == nullptr)
        {
            temp->prev = nullptr;
            temp->next = headPointer;
            tailPointer = headPointer;
            tailPointer->prev = temp;
            headPointer = temp;
        }
        else
        {
            temp->next = this->headPointer;
            temp->prev = nullptr;
            headPointer->prev = temp;
            headPointer = temp;
        }
        size++;
    };

    //******
    void AddTail(const T& _data)
    {
        Node* temp = new Node;
        temp->data = _data;

        if(headPointer == nullptr && tailPointer == nullptr) {
            headPointer = temp;
            tailPointer = temp;
            temp->prev = nullptr;
            temp->next = nullptr;
        }
        else if(headPointer->next == nullptr && tailPointer->prev == nullptr)
        {
            temp->prev = headPointer;
            temp->next = nullptr;
            headPointer->next = temp;
            tailPointer = temp;
        }
        else
        {
            temp->next = nullptr;
            temp->prev = this->tailPointer;
            tailPointer->next = temp;
            tailPointer = temp;
        }
        size++;
    };
    //*****
    void AddNodesHead(const T* data, unsigned int count)
    {
        for (unsigned int i = count - 1; i >= 0 && i < count; i--)
        {
            this->AddHead(data[i]);
        }
    };
    //******
    void AddNodesTail(const T* data, unsigned int count)
    {
        for(unsigned int i = 0; i < count; i++)
        {
            this->AddTail(data[i]);
        }
    };

    Node* Head()
    {
        return this->headPointer;
    };

    const Node* Head() const
    {
        return this->headPointer;
    };

    Node* Tail()
    {
        return this->tailPointer;
    };

    const Node* Tail() const
    {
        return this->tailPointer;
    };

    T& operator[](unsigned int index)
    {
        if (index >= size)
        {
            throw out_of_range("The index is out of range\n");
        }
        unsigned int count = 0;
        Node* tempPtr = headPointer;
        while(tempPtr != nullptr)
        {
            if(count == index)
            {
                return tempPtr->data;
            }
            count += 1;
            tempPtr = tempPtr->next;
        }
    };

    void InsertAfter(Node* node, const T& _data)
    {
        if(node->next == nullptr)
        {
            AddTail(_data);
        }
        else {
            Node* temp = new Node;
            temp->data = _data;
            node->next->prev = temp;
            temp->next = node->next;
            temp->prev = node;
            node->next = temp;
            size += 1;
        }
    };


    void InsertBefore(Node* node, const T& _data)
    {
        if(node->prev == nullptr)
        {
            AddHead(_data);
        }
        else {
            Node* temp = new Node;
            temp->data = _data;
            node->prev->next = temp;
            temp->prev = node->prev;
            temp->next = node;
            node->prev = temp;
            size += 1;
        }
    };


    void InsertAt(const T& _data, unsigned int index)
    {
        if(index < size) {
            Node *tempPtr = this->GetNode(index);
            this->InsertBefore(tempPtr, _data);
        }
        else
        {
            AddTail(_data);
        }
    };

    bool operator==(const LinkedList<T>& rhs)
    {
        Node* tempPtr = headPointer;
        Node* tempRhs = rhs.headPointer;
        if (this->size == rhs.size)
        {
            while(tempPtr != nullptr)
            {
                if(tempPtr->data != tempRhs->data)
                {
                    return false;
                }
                tempPtr = tempPtr->next;
                tempRhs = tempRhs->next;
            }
            return true;
        }
        return false;
    };


    const T& operator[](unsigned int index) const
    {
        if (index >= size)
        {
            throw out_of_range("The index is out of range\n");
        }
        unsigned int count = 0;
        Node* tempPtr = headPointer;
        while(tempPtr != nullptr)
        {
            if(count == index)
            {
                return tempPtr->data;
            }
            count += 1;
            tempPtr = tempPtr->next;
        }
    };

    const Node* GetNode(unsigned int index) const
    {
        if (index >= size)
        {
            throw out_of_range("The index is out of range\n");
        }
        unsigned int count = 0;
        Node* tempPtr = headPointer;
        while(tempPtr != nullptr)
        {
            if(count == index)
            {
                return tempPtr;
            }
            count += 1;
            tempPtr = tempPtr->next;
        }
        return nullptr;
    };

    Node* GetNode(unsigned int index)
    {
        if (index >= size)
        {
            throw out_of_range("The index is out of range\n");
        }
        unsigned int count = 0;
        Node* tempPtr = headPointer;
        while(tempPtr != nullptr)
        {
            if(count == index)
            {
                return tempPtr;
            }
            count += 1;
            tempPtr = tempPtr->next;
        }
        return nullptr;
    };

    //Construction Destruction
    //******

    LinkedList<T>& operator=(const LinkedList<T>& rhs)
    {
        Node* tempPtr = this->headPointer->next;
        while(tempPtr != nullptr)
        {
            if(tempPtr->next == nullptr)
            {
                delete tempPtr->prev;
                delete tempPtr;
                tempPtr = nullptr;
            }
            else
            {
                delete tempPtr->prev;
                tempPtr = tempPtr->next;
            }
        }
        this->headPointer = nullptr;
        this->tailPointer = nullptr;
        this->size = 0;

        Node* tempptr = rhs.headPointer;
        while(tempptr != nullptr)
        {
            this->AddTail(tempptr->data);
            tempptr = tempptr->next;
        }
        return *this;
    };

    LinkedList()
    {
        this->headPointer = nullptr;
        this->tailPointer = nullptr;
        this->size = 0;
    };

    LinkedList(const LinkedList<T>& list)
    {
        this->headPointer = nullptr;
        this->tailPointer = nullptr;
        this->size = 0;
        Node* tempPtr = list.headPointer;
        while(tempPtr != nullptr)
        {
            this->AddTail(tempPtr->data);
            tempPtr = tempPtr->next;
        }
    };

    //******
    ~LinkedList() {
        Node *tempPtr = headPointer;
        while(tempPtr != nullptr) {
            if (tempPtr->next == nullptr) {
                delete tempPtr->prev;
                delete tempPtr;
                tempPtr = nullptr;
            } else {
                delete tempPtr->prev;
                tempPtr = tempPtr->next;
            }
        }

        headPointer = nullptr;
        tailPointer = nullptr;

//
//    while(RemoveHead){
//    }

    };
};