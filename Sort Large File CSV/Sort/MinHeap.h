#ifndef _MIN_HEAP_
#define _MIN_HEAP_

#include "config.h"

class HeapNode
{
private:
    string rowContent;
    int index;
public:
    HeapNode(string rowContent, int index);

    string getID();

    string getContent();

    int getIndex();
};

class MinHeap
{
private:
    vector<HeapNode> data;

public:
    void minHeapify(int i);

    HeapNode top();

    void push(HeapNode value);

    void pop();

    bool empty();
};

#endif // !_MIN_HEAP_