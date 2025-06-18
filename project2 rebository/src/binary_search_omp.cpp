#include <iostream>
#include <omp.h>
#include <chrono>
#include <vector>
#include <atomic>

using namespace std;
using namespace chrono;

const int SIZE = 100000000;
int arr[SIZE];
atomic<int> resultIndex(-1); // Atomic to ensure thread safety
int target;

int binarySearch(int start, int end, int target, atomic<int>& resultIndex) {
    while (start <= end && resultIndex == -1) {
        int mid = start + (end - start) / 2;

        if (arr[mid] == target) {
            return mid;
        } else if (arr[mid] < target) {
            start = mid + 1;
        } else {
            end = mid - 1;
        }
    }
    return -1;
}

int main() {
    // Fill sorted array
    for (int i = 0; i < SIZE; i++) arr[i] = i;

    target = rand() % SIZE;
    int thread_counts[] = {1, 2, 4, 8};

    cout << "Target: " << target << endl;

    for (int threads : thread_counts) {
        double total_time = 0;

        for (int trial = 0; trial < 5; trial++) {
            resultIndex = -1;
            int chunkSize = SIZE / threads;
            auto start_time = high_resolution_clock::now();

            #pragma omp parallel num_threads(threads) shared(resultIndex)
            {
                int tid = omp_get_thread_num();
                int local_start = tid * chunkSize;
                int local_end = (tid == threads - 1) ? SIZE - 1 : (tid + 1) * chunkSize - 1;

                int local_result = binarySearch(local_start, local_end, target, resultIndex);

                #pragma omp critical
                if (local_result != -1) {
                    resultIndex = local_result;
                }
            }

            auto end_time = high_resolution_clock::now();
            total_time += duration_cast<microseconds>(end_time - start_time).count();
        }

        double avg_time = total_time / 5.0;

        cout << "Threads: " << threads << "\n";
        if (resultIndex != -1)
            cout << "Result index: " << resultIndex << "\n";
        else
            cout << "Not found\n";
        cout << "Average time: " << avg_time << " microseconds\n\n";
    }

    return 0;
}
