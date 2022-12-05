#include "ExternalSort.h"

string title;

int preProcessing(string inputFile, int memLimit) {
    ifstream fin;
    fin.open(inputFile, ios::in | ios::binary);

    if (!fin.is_open()) {
        cout << inputFile << " is not found!\n\n";
        exit(1);
    }

    // get size of file input.
    fin.seekg(0, ios::end);
    long long inputSize = fin.tellg();
    fin.seekg(0, ios::beg);
    
    cout << "Pre-processing file input: " << inputFile << "...\n\n";

    ofstream fout;
    vector<string> data;
    long long fileCount = 0, sumMem = 0;

    // read title of large file.
    getline(fin, title);

    string rowContent;

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

            // use stringstream to optimize memory
            stringstream s;
            s << "file_" << fileCount << ".csv";
            fout.open(s.str(), ios::out | ios::binary);

            cout << "Writing data into " << s.str() << "\n\n";
            if (inputSize <= memLimit)
                fout << title << '\n';
         
            int dataSize = data.size();
            for (int i = 0; i < dataSize - 1; ++i)
                fout << data[i] << '\n';

            // check in case size of a rowContent greater than memory limit.
            if (dataSize > 0)
                fout << data[dataSize - 1];
            else {
                cout << "The size of content of a row during reading exceeds the allowed memory.\n\n";
                exit(1);
            }

            fout.close();
            data.clear();

            sumMem = rowContent.size() + 1;
            data.push_back(rowContent);
        }
    }

    // last chunk file of input file.
    if (data.size() > 0) {
        if (data.back() == "")
            data.pop_back();
        if (data.size() > 0) {
            quickSort(data, 0, data.size() - 1);

            ++fileCount;

            stringstream s;
            s << "file_" << fileCount << ".csv";
            fout.open(s.str(), ios::out | ios::binary);

            cout << "Writing data into " << s.str() << "\n\n";
            if (inputSize <= memLimit)
                fout << title << '\n';

            int dataSize = data.size();
            for (int i = 0; i < dataSize - 1; ++i)
                fout << data[i] << '\n';
            fout << data[dataSize - 1];
            fout.close();
        }
    }
    fin.close();

    cout << "Pre-process is done!\n\n";

    return fileCount;
}

void mergeChunksFile(string outputFile, int left, int right, int pos, bool done)
{

    int fileCount = right - left + 1;

    if (fileCount == 1) {
        stringstream s1, s2;
        s1 << "file_" << left << ".csv";
        s2 << "file_" << pos << ".csv";
        if (rename(s1.str().c_str(), s2.str().c_str())) {
            cout << "Rename file during merge processing failed!\n\n";
            exit(1);
        }
        return;
    }

    vector<ifstream> fin(fileCount);
    for (int i = 0; i < fileCount; ++i)
    {
        stringstream s;
        s << "file_" << left + i << ".csv";
        fin[i].open(s.str(), ios::in | ios::binary);
    }

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

    cout << "Merging chunks from file_" << left << " to file_" << right << " into ";

    ofstream fout;
    if (!done) {
        cout << "file_" << pos << "\n\n";
        stringstream s;
        s << "file_" << pos << ".csv";
        fout.open(s.str(), ios::out | ios::binary);
    }
    else {
        cout << outputFile << "\n\n";
        fout.open(outputFile, ios::out | ios::binary);
        fout << title << '\n';
    }

    while (!minHeap.empty())
    {
        string rowContent = minHeap.top().getContent();
        int index = minHeap.top().getIndex();
        minHeap.pop();

        fout << rowContent;

        if (!fin[index].eof())
        {
            getline(fin[index], rowContent);
            minHeap.push(HeapNode(rowContent, index));
        }
        if (!minHeap.empty())
            fout << '\n';
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

    if (fileCount == 1) {
        stringstream s;
        s << "file_1.csv";
        if (rename(s.str().c_str(), outputFile.c_str())) {
            cout << "Rename file failed!\n\n";
        }
        return;
    }
    // set gap make sure data fit on RAM.
    int gap = (memLimit / sizeof(HeapNode));

    if (gap == 1) {
        cout << "Not enough internal memory to merge files.\n\n";
        return;
    }
    while (left < right)
    {
        int pos = right;

        while (left < right)
        {
            int p = min(left + gap, right);

            ++pos;

            // check merge process is done or not to write title of file.
            bool done = false;
            if (p + 1 >= right && p + 1 >= pos)
                done = true;
            mergeChunksFile(outputFile, left, p, pos, done);
            left = p + 1;
        }

        right = pos;
    }

    cout << "Merge total file done!\n\n";

    // remove chunks file.
    for (int i = 1; i < right; ++i)
    {
        stringstream s;
        s << "file_" << i << ".csv";
        if (remove(s.str().c_str()))
        {
            cout << "Remove " << s.str() << " failed\n\n";
        }
    }
}