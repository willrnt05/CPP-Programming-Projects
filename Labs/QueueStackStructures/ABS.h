#pragma once
#include <iostream>

using namespace std;

template <typename T>
class ABS {
private:
    unsigned int capacity;
    unsigned int size;
    T* objectHolder;
public:
    ABS()
    {
        //ALso initialiize Array
        this->objectHolder = new T[1];
        this->capacity = 1;
        this->size = 0;
    };
    ABS(unsigned int capacity_)
    {
        this->objectHolder = new T[capacity_];
        this->capacity = capacity_;
        this->size = 0;
    };

    ABS(const ABS &d)
    {
        this->objectHolder = new T[d.capacity];
        this->capacity = d.capacity;
        this->size = d.size;
        for(int i = 0; i < d.size; ++i)
        {
            this->objectHolder[i] = d.objectHolder[i];
        }
    };


    ABS &operator=(const ABS &d)
    {
        this->objectHolder = new T[d.capacity];
        this->capacity = d.capacity;
        this->size = d.size;
        for(int i = 0; i < d.size; ++i)
        {
            this->objectHolder[i] = d.objectHolder[i];
        }
    };

    ~ABS()
    {
        delete[] this->objectHolder;
    };

    void push(T data)
    {
        //Check if size is at capacity
        if (size == capacity)
        {
            increaseSize();
        }
        this->objectHolder[size] = data;
        this->size++;

        //If it is not then add to size and increment
        //If size if full increase size by double
        //Otherwise call function to create new array
    };

    T pop()
    {
        //Not sure how to handle the runtime error...
        if(size == 0)
        {
            throw runtime_error("An error has occured");
        }
        T returnObject = this->objectHolder[size-1];
        this->size--;
        if ((double)size < ((double)capacity * 0.5)) {
            decreaseSize();
        }
        return returnObject;



        //get the last element
        //decrement size
        //if the size is less than half the capacity, shrink it
    };

    T peek()
    {
        if(size == 0)
        {
            throw runtime_error("An error has occured");
        }
        return this->objectHolder[size-1];
    };

    unsigned int getSize()
    {
        return this->size;
    };

    unsigned int getMaxCapacity()
    {
        return this->capacity;
    };

    T* getData()
    {
        return objectHolder;
    };

    //both of these
//create new list of size
//copy the elements
//delete the last list
//redirect the pointer

    void decreaseSize()
    {
        T* newArray = new T[this->capacity / 2];
        for(unsigned int i = 0; i < this->size; ++i)
        {
            newArray[i] = this->objectHolder[i];
        }
        delete[] objectHolder;
        this->objectHolder = newArray;
        this->capacity/=2;
    };

    void increaseSize()
    {
        T* newArray = new T[this->capacity * 2];
        for(unsigned int i = 0; i < this->size; ++i)
        {
            newArray[i] = this->objectHolder[i];
        }
        delete[] objectHolder;
        this->objectHolder = newArray;
        this->capacity*=2;
    };
};
