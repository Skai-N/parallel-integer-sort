#include <stdio.h>
#include <cmath>
#include <vector>
#include <iostream>
#include <ctime>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <thread>


int digitAtPlace(int num, int place);
int countingSort(std::vector<int> *nums, int start, int end, int place);
void serialRadixSort(std::vector<int> *nums);
std::vector<std::vector<int>> oldcountingSort(std::vector<int> nums, int place);
void radixSort(std::vector<int> *nums, int start, int end, int place);
void radixDriver(std::vector<int> *nums);

int main() {
    std::vector<int> nums;
    nums.reserve(1000000);
    
    int num;

    while (scanf("%d", &num) == 1) {
        nums.push_back(num ^ (uint32_t) 0x80000000);
    }

    radixDriver(&nums);
    // serialRadixSort(&nums);
    
    for (int i = 0; i < nums.size(); i++) {
        printf("%d\n", nums[i] ^ (uint32_t) 0x80000000);
    }
    
    return 0;
}

void radixDriver(std::vector<int> *nums) {
    for (int i = 0; i < 12; i++) {
        countingSort(nums, 0, (*nums).size() - 1, i);
    }
    radixSort(nums, 0, (*nums).size() - 1, 31);
}

void radixSort(std::vector<int> *nums, int start, int end, int place) {
    int zero_count = countingSort(nums, start, end, place);
    
    int left_start = start;
    int left_end = start + zero_count - 1;
    int left_size = left_end - left_start + 1;
    
    int right_start = start + zero_count;
    int right_end = end;
    int right_size = right_end - right_start + 1;
    int split = 12;

    if (place >= split) {
        if (left_size > 0 && right_size > 0) {
            if (place > 20) {
                std::thread t1(radixSort, nums, left_start, left_end, place - 1);
                radixSort(nums, right_start, right_end, place - 1);
                t1.join();
            } else {
                radixSort(nums, left_start, left_end, place - 1);
                radixSort(nums, right_start, right_end, place - 1);
            }
        }
        else if (right_size > 0) {
            radixSort(nums, right_start, right_end, place - 1);
        } else if (left_size > 0){
            radixSort(nums, left_start, left_end, place - 1);
        }
    }

}

void serialRadixSort(std::vector<int> *nums) {
    for (int i = 0; i < 32; i++) {
        countingSort(nums, 0, (*nums).size() - 1, i);
    }
}

int countingSort(std::vector<int> *nums, int start, int end, int place) {
    int countArray[2] = {0, 0};

    std::vector<int> nums_ref;
    nums_ref.assign((*nums).begin() + start, (*nums).begin() + end + 1);

    for (int i = 0; i < nums_ref.size(); i++) {
        countArray[digitAtPlace(nums_ref[i], place)]++;
    }

    countArray[1] += countArray[0];

    int zero_count = countArray[0];
    
    for (int i = nums_ref.size() - 1; i >= 0; i--) {
        int digit = digitAtPlace(nums_ref[i], place);
        countArray[digit]--;

        (*nums)[countArray[digit] + start] = nums_ref[i];
    }

    return zero_count;
}


int digitAtPlace(int num, int place) {
    return (uint32_t) (num & (1 << place)) >> place;
}