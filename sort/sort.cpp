#include <stdio.h>
#include <cmath>
#include <vector>
#include <iostream>


int digitAtPlace(int num, int place);
std::vector<std::vector<int>> countingSort(std::vector<int> nums, int place);
std::vector<int> radixSort(std::vector<int> nums, int place);

int main() {
    std::vector<int> pos = std::vector<int>();
    std::vector<int> neg = std::vector<int>();


    int counter = 0;
    char in[100];
    while (scanf("%s", in)) {
        int num;
        if (strcmp(in, "a") == 0) {
            break;
        }
        
        sscanf(in, "%d", &num);
        if (num > 0) {
            pos.push_back(num);
        }
        else {
            neg.push_back(num);
        }
    }
    
    
    std::vector<int> pos_res = radixSort(pos, 31);
    std::vector<int> neg_res = radixSort(neg, 31);

    for (int i = neg_res.size() - 1; i >= 0; i--) {
        printf("%d\n", neg_res[i]);
    }
    printf("hello");

    for (int i = 0; i < pos_res.size(); i++) {
        printf("%d\n", pos_res[i]);
    }
    
    return 0;
}

int digitAtPlace(int num, int place) {
    return (num & (1 << place)) >> place;
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

std::vector<std::vector<int>> countingSort(std::vector<int> nums, int place) {
    // Counting sort
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

