#include "InternalSort.h"

string getLineID(const string& line)
{
    stringstream s(line);
    string ID;
    getline(s, ID, ',');
    return ID;
}

int partition(vector<string>& data, int left, int right)
{
    int i = left - 1, j = right;
    string pivot = data[right];
    for (;;)
    {
        while (getLineID(data[++i]) < getLineID(pivot));
        while (getLineID(pivot) < getLineID(data[--j]))
            if (j == left) break;
        if (i >= j) break;
        swap(data[i], data[j]);
    }
    swap(data[i], data[right]);
    return i;
}

// Quick Sort without recursion
void quickSort(vector<string>& data, int left, int right)
{
    stack<pair<int, int>> st;
    st.push(make_pair(left, right));

    while (!st.empty())
    {
        pair<int, int> top = st.top();
        st.pop();

        int l = top.first, r = top.second;
        int p = partition(data, l, r);
        if (l < p - 1)
            st.push(make_pair(l, p - 1));
        if (p + 1 < r)
            st.push(make_pair(p + 1, r));
    }
}