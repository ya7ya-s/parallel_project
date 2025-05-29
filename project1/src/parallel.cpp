#include <iostream>
#include <pthread.h>
#include <chrono>
#include<ctime>
#include<sys/time.h>

using namespace std;
using namespace std::chrono;

const int THREAD_COUNT = 4;
const int SIZE = 1000000;  // 1 million 
int arr[SIZE];
int target ;  // Example target
int resultIndex = -1;

pthread_t threads[THREAD_COUNT];
pthread_mutex_t lock;

double get_time(){
timeval tv;
gettimeofday(&tv,nullptr);
return tv.tv_sec+tv.tv_usec * 1e-6;
}

struct ThreadData {
    int start;
    int end;
    int thread_id;
};

ThreadData threadData[THREAD_COUNT];  

void* binarySearchThread(void* arg) {
    ThreadData* data = (ThreadData*)arg;
    int left = data->start;
    int right = data->end;

    pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, NULL);
    pthread_setcanceltype(PTHREAD_CANCEL_ASYNCHRONOUS, NULL);

    while (left <= right) {
        pthread_testcancel();

        int mid = left + (right - left) / 2;

        if (arr[mid] == target) {
            pthread_mutex_lock(&lock);
            if (resultIndex == -1) {
                resultIndex = mid;
                for (int i = 0; i < THREAD_COUNT; ++i) {
                    if (i != data->thread_id)
                        pthread_cancel(threads[i]);
                }
            }
            pthread_mutex_unlock(&lock);
            break;
        } else if (arr[mid] < target) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }

    pthread_exit(0);
}

int main() {
srand(time(0));
target=rand()%SIZE;
    cout << "Filling array with values..." << endl;
    for (int i = 0; i < SIZE; i++) {
        arr[i] = i;
    }

    pthread_mutex_init(&lock, NULL);
    int chunkSize = SIZE / THREAD_COUNT;
    
    double st=get_time();
    cout << "Starting parallel binary search..." << endl;
    auto startTime = high_resolution_clock::now();

    for (int i = 0; i < THREAD_COUNT; i++) {
        threadData[i].start = i * chunkSize;
        threadData[i].end = (i == THREAD_COUNT - 1) ? SIZE - 1 : (i + 1) * chunkSize - 1;
        threadData[i].thread_id = i;
        pthread_create(&threads[i], NULL, binarySearchThread, (void*)&threadData[i]);
    }


    for (int i = 0; i < THREAD_COUNT; i++) {
        pthread_join(threads[i], NULL);
    }
    
    double en=get_time();
    auto endTime = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(endTime - startTime);

    if (resultIndex != -1)
        cout << "Element found at index: " << resultIndex << endl;
    else
        cout << "Element not found." << endl;

    cout << "Elapsed time: " << duration.count() << " microseconds" << endl;
    cout<<"time in double:"<<en-st<<"\n";

    pthread_mutex_destroy(&lock);

    return 0;
}
