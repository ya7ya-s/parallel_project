#include <iostream>
#include <chrono>
#include <ctime>
#include <sys/time.h>

using namespace std;
using namespace std::chrono;

const int SIZE = 1000000;  // 1 million 
int arr[SIZE];
int target;  // Example target
int resultIndex = -1;


void binarySearch(int left, int right) {
    while (left <= right) {
        int mid = left + (right - left) / 2;

        if (arr[mid] == target) {
            resultIndex = mid;
            return;
        } else if (arr[mid] < target) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
}

int main() {
    srand(time(0));
    target = rand() % SIZE;

    cout << "Filling array with values..." << endl;
    for (int i = 0; i < SIZE; i++) {
        arr[i] = i;
    }

    cout << "Target to find: " << target << endl;

    
    auto startTime = high_resolution_clock::now();

    binarySearch(0, SIZE - 1);

    
    auto endTime = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(endTime - startTime);

    if (resultIndex != -1)
        cout << "Element found at index: " << resultIndex << endl;
    else
        cout << "Element not found." << endl;

    cout << "Elapsed time: " << duration.count() << " microseconds" << endl;
    

    return 0;
}
