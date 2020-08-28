#include <iostream>
#include <vector>
#include <thread>
#include <atomic>


static long sumS = 0;
static std::atomic<long> sumT(0);

void findSum(const std::vector<int> &toSum, int i, int j) {
    for (int inx = i; inx < j; inx++) {
        sumT += toSum[inx];
        //*
        sumT -= toSum[inx];
        sumT += toSum[inx];
        sumT -= toSum[inx];
        sumT += toSum[inx];
        sumT -= toSum[inx];
        sumT += toSum[inx];
        sumT -= toSum[inx];
        sumT += toSum[inx];//*/
    }
}


int main() {
    srand(time(NULL));

    std::vector<int> toSum;
    int N = 3000000;
    int threadsCount = 32;
    std::vector<std::thread> threads;
    int step = N / threadsCount;

    for (int i = 0; i < N; ++i) {
        toSum.push_back((rand() / 100000000) - 10);
    }
    for (int inx = 0; inx < N; inx++)
        sumS += toSum[inx];
    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
    for (int inx = 0; inx < threadsCount; inx++) {
        threads.push_back(std::thread(findSum, toSum, (inx * step), (inx * step + step)));
    }
    for (int inx = 0; inx < threadsCount; inx++)
        if (threads[inx].joinable())
            threads[inx].join();
    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();

    std::cout << "Threads: " << threadsCount << "\n";
    std::cout << "Def_sum: " << sumS << "\n";
    std::cout << "Thr_sum: " << sumT << "\n";
    std::cout << "Time res: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count()
              << " milliseconds\n";
    sumT = 0;
    return 0;
}
