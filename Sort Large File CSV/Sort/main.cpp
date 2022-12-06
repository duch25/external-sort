#include "ExternalSort.h"

string INPUT_FILE = "Books_rating.csv";
string OUTPUT_FILE = "sorted_books_rating.csv";
long long INTERNAL_MEMORY_LIMIT = 204800000; // 200MB

const clock_t timeBegin = clock();

// run program on mode "Release" in Visual Studio (version current: 2022)

int main()
{
    int fileCount = preProcessing(INPUT_FILE, INTERNAL_MEMORY_LIMIT);

    cout << "Time for preprocessing: " << double(clock() - timeBegin) / CLOCKS_PER_SEC * 1000 << "miliseconds\n\n";

    cout << "Merging " << fileCount << " files into file " << OUTPUT_FILE << "\n\n";

    mergeTotalFile(fileCount, OUTPUT_FILE, INTERNAL_MEMORY_LIMIT);

    cout << "Time total of propram: " << double(clock() - timeBegin) / CLOCKS_PER_SEC * 1000 << "miliseconds\n\n";
    return 0;
}