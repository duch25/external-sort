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