#include <iostream>
#include <string>
using namespace std;

struct File {
    string name;
    long size; 
    long timeSto; 

    
    File(string n, long s, long t) : name(n), size(s), timeSto(t) {}
};

// Ham sap xep dung luong & thoi gian luu su dung selection sort
void sortFiles(File files[], int count) {
    for (int i = 0; i < count - 1; ++i) {
        int minIndex = i;
        for (int j = i + 1; j < count; ++j) {
            if (files[j].size < files[minIndex].size ||
                (files[j].size == files[minIndex].size && files[j].timeSto < files[minIndex].timeSto)) {
                minIndex = j;
            }
        }
        // Hoan doi 2 files[i] & files[minIndex]
        if (minIndex != i) {
            File temp = files[i];
            files[i] = files[minIndex];
            files[minIndex] = temp;
        }
    }
}

// Ham xoa file co dung luong be nhat & thoi gian luu lau nhat
void deleteSmallestFiles(File files[], int& count, int deleteCount) {
    for (int i = 0; i < deleteCount && i < count; ++i) {
        cout << "Deleting file: " << files[i].name << " (Size: " << files[i].size << " bytes)" << endl;
    }

    // Dich chuyen nhung file con lai ve phia ben trai
    for (int i = deleteCount; i < count; ++i) {
        files[i - deleteCount] = files[i];
    }
    count -= deleteCount;
}

int main() {
    File files[4] = {
        File("file1.txt", 500, 10000), // dung luong, thoi gian luu "simulated"
        File("file2.txt", 300, 20000),
        File("file3.txt", 700, 5000),
        File("file4.txt", 300, 30000)
    };
    int fileCount = 4;

   
    sortFiles(files, fileCount);

    cout << "Files sorted by size:" << endl;
    for (int i = 0; i < fileCount; ++i) {
        cout << files[i].name << " (Size: " << files[i].size << " bytes)" << endl;
    }

  
    deleteSmallestFiles(files, fileCount, 2);

    cout << "Remaining files:" << endl;
    for (int i = 0; i < fileCount; ++i) {
        cout << files[i].name << " (Size: " << files[i].size << " bytes)" << endl;
    }

    return 0;
}