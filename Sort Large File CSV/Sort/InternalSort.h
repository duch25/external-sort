#ifndef _INTERNAL_SORT_
#define _INTERNAL_SORT_

#include "config.h"

string getLineID(const string& line);

int partition(vector<string>& data, int left, int right);

void quickSort(vector<string>& data, int left, int right);

#endif // !_INTERNAL_SORT_