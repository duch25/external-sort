#include "ExternalSort.h"

string getFileName(int fileCount) {
    string fileName = "file_" + fileCount;
    fileName += ".csv";
    return fileName;
}

int preProcessing(string inputFile, int memLimit) {
    ifstream fin;
    fin.open(inputFile);

    if (!fin.is_open()) {
        cout << inputFile << " is not found!\n\n";
        exit(1);
    }

    cout << "Pre-processing file input: " << inputFile << "...\n\n";

    ofstream fout;
    vector<string> data;
    long long fileCount = 0, sumMem = 0;

    // read title of large file.
    string rowContent;
    getline(fin, rowContent);

    while (!fin.eof()) {
        getline(fin, rowContent);
        if (sumMem + rowContent.size() < memLimit) {
            // include newline character '\n'
            sumMem += rowContent.size() + 1;
            data.push_back(rowContent);
        }
        else {
            // sort data fit on memory limit.
            quickSort(data, 0, data.size() - 1);

            ++fileCount;

            fout.open(getFileName(fileCount));

            int dataSize = data.size();
            for (int i = 0; i < dataSize - 1; ++i)
                fout << data[i] << endl;

            // check in case size of a rowContent greater than memory limit.
            if (dataSize > 0)
                fout << data[dataSize - 1];
            else {
                cout << "The size of content of a row during reading exceeds the allowed memory.\n\n";
                exit(1);
            }

            fout.close();
            data.clear();

            sumMem = rowContent.size();
            data.push_back(rowContent);
        }
    }

    // last chunk file of input file.
    if (data.size() > 0) {
        quickSort(data, 0, data.size() - 1);

        ++fileCount;
        fout.open(getFileName(fileCount));

        int dataSize = data.size();
        for (int i = 0; i < dataSize - 1; ++i)
            fout << data[i] << endl;
        fout << data[dataSize - 1];

        fin.close();
        fout.close();
    }
    else
        fin.close();

    cout << "Pre-process is done!\n\n";

    return fileCount;
}

void mergeChunksFile(int left, int right, int pos)
{

    int fileCount = right - left + 1;

    vector<ifstream> fin(fileCount);
    for (int i = 0; i < fileCount; ++i)
        fin[i].open(getFileName(left + i));

    // merge process using min heap.
    MinHeap minHeap;

    for (int i = 0; i < fileCount; ++i)
    {
        string rowContent;
        if (!fin[i].eof())
        {
            getline(fin[i], rowContent);
            minHeap.push(HeapNode(rowContent, i));
        }
    }

    cout << "Merging chunks from file_" << left << " to file_" << right << " into file_" << pos << "\n\n";

    ofstream fout;
    fout.open(getFileName(pos));

    while (!minHeap.empty())
    {
        string rowContent = minHeap.top().getContent();
        int index = minHeap.top().getIndex();
        minHeap.pop();

        fout << rowContent << endl;

        if (!fin[index].eof())
        {
            getline(fin[index], rowContent);
            minHeap.push(HeapNode(rowContent, index));
        }
    }

    cout << "Merge above chunks file done!\n\n";

    for (int i = 0; i < fileCount; ++i)
        fin[i].close();
    fout.close();
}

void mergeTotalFile(int fileCount, string outputFile, int memLimit)
{

    int left = 1;
    int right = fileCount;

    // set gap make sure data fit on RAM.
    int gap = (memLimit / sizeof(HeapNode)) - 1;

    while (left < right)
    {
        int pos = right;

        while (left <= right)
        {
            int p = min(left + gap, right);

            ++pos;
            mergeChunksFile(left, p, pos);
            left = p + 1;
        }

        right = pos;
    }

    cout << "Merge total file done!\n\n";

    // rename last file to match output file.
    if (!rename(getFileName(right).c_str(), outputFile.c_str()))
        cout << "Rename file done!";
    else
        cout << "Rename file failed!";


    // remove chunks file.
    for (int i = 1; i < right; ++i)
    {
        string fileName = getFileName(i);
        if (remove(fileName.c_str()))
        {
            cout << "Remove " << fileName << " failed\n\n";
        }
    }
}