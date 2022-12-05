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

    void minHeapify(int i)
    {
        int dataSize = data.size();
        int smallest = i;
        int left = 2 * i + 1;
        int right = 2 * i + 2;

        if (left < dataSize && data[left].getID() < data[smallest].getID())
            smallest = left;
        if (right < dataSize && data[right].getID() < data[smallest].getID())
            smallest = right;

        if (smallest != i)
        {
            swap(data[smallest], data[i]);
            minHeapify(smallest);
        }
    }

public:

    HeapNode top();

    void push(HeapNode value);

    void pop();

    bool empty();
};

#endif // !_MIN_HEAP_