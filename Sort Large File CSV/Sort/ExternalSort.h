#ifndef _EXTERNAL_SORT_
#define _EXTERNAL_SORT_

#include "config.h"
#include "InternalSort.h"
#include "MinHeap.h"

string getFileName(int fileCount);

int preProcessing(string inputFile, int memLimit);

void mergeChunksFile(int left, int right, int pos);

void mergeTotalFile(int fileCount, string outputFile, int memLimit);

#endif // !_EXTERNAL_SORT_