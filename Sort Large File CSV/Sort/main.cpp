#include "ExternalSort.h"

string INPUT_FILE = "Books_rating.csv";
string OUTPUT_FILE = "sorted_books_rating.csv";
long long INTERNAL_MEMORY_LIMIT = 204800000;

int main()
{
    int fileCount = preProcessing(INPUT_FILE, INTERNAL_MEMORY_LIMIT);

    cout << "Merging " << fileCount << " files into file " << OUTPUT_FILE << "\n\n";

    mergeTotalFile(fileCount, OUTPUT_FILE, INTERNAL_MEMORY_LIMIT);

    return 0;
}