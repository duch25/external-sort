#ifndef _EXTERNAL_SORT_
#define _EXTERNAL_SORT_

#include "config.h"
#include "InternalSort.h"
#include "MinHeap.h"

int preProcessing(string inputFile, int memLimit);

void mergeChunksFile(string outputFile, int left, int right, int pos, bool done);

void mergeTotalFile(int fileCount, string outputFile, int memLimit);

#endif // !_EXTERNAL_SORT_