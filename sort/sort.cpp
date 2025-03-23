#include <stdio.h>
#include <cmath>
#include <vector>
#include <iostream>
#include <ctime>

int digitAtPlace(int num, int place);
std::vector<std::vector<int>> countingSort(std::vector<int> nums, int place);
std::vector<int> serialRadixSort(std::vector<int> nums, int place);
std::vector<int> radixSort(std::vector<int> nums, int place);

int main() {
    std::vector<int> nums;
    nums.reserve(1000000);
    
    int num;
    while (std::cin >> num) {
        nums.push_back(num ^ (uint32_t) 0x80000000);
    }

    std::vector<int> sorted = radixSort(nums, 31);

    for (int i = 0; i < sorted.size(); i++) {
        printf("%d\n", sorted[i] ^ (uint32_t) 0x80000000);
    }
    
    return 0;
}

std::vector<int> radixSort(std::vector<int> nums, int place) {
    std::vector<std::vector<int>> buff = countingSort(nums, place);
    std::vector<int> left = buff[0];
    std::vector<int> right = buff[1];
    
    if (place > 0) {
        if (left.size() > 0) {
            left = radixSort(left, place - 1);
        }
        
        if (right.size() > 0) {
            right = radixSort(right, place - 1);
        }
    }
    
    std::vector<int> combine;
    combine.reserve( left.size() + right.size() );
    combine.insert( combine.end(), left.begin(), left.end() );
    combine.insert( combine.end(), right.begin(), right.end() );
    return combine;
}

std::vector<int> serialRadixSort(std::vector<int> nums, int place) {
    for (int i = 0; i < 32; i++) {
        std::vector<std::vector<int>> buff = countingSort(nums, i);
        std::vector<int> left = buff[0];
        std::vector<int> right = buff[1];

        std::vector<int> combine;
        combine.reserve( left.size() + right.size() );
        combine.insert( combine.end(), left.begin(), left.end() );
        combine.insert( combine.end(), right.begin(), right.end() );

        nums = combine;
    }

    return nums;
}

std::vector<std::vector<int>> countingSort(std::vector<int> nums, int place) {
    int countArray[2] = {0, 0};

    for (int i = 0; i < nums.size(); i++) {
        countArray[digitAtPlace(nums[i], place)]++;
    }

    std::vector<int> sorted_left(countArray[0]);
    std::vector<int> sorted_right(countArray[1]);
    std::vector<std::vector<int>> result = {sorted_left, sorted_right};
    
    for (int i = nums.size() - 1; i >= 0; i--) {
        int digit = digitAtPlace(nums[i], place);
        countArray[digit]--;

        result[digit][countArray[digit]] = nums[i];
    }

    return result;
}


int digitAtPlace(int num, int place) {
    return (uint32_t) (num & (1 << place)) >> place;
}