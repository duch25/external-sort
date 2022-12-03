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
    string pivot = getLineID(data[right]);

    int i = left - 1;
    for (int j = left; j < right; ++j)
    {
        if (getLineID(data[j]) < pivot)
        {
            ++i;
            swap(data[i], data[j]);
        }
    }
    swap(data[i + 1], data[right]);
    return i + 1;
}

void quickSort(vector<string>& data, int left, int right)
{
    if (left >= right)
        return;
    int p = partition(data, left, right);
    quickSort(data, left, p - 1);
    quickSort(data, p + 1, right);
}