#include <stdio.h>

/*
 * Problem:
 * Given an integer array nums, move all 0's to the end of it while maintaining the relative order of the non-zero
 * elements. Note that you must do this in-place without making a copy of the array.
 */

/*void moveZeroes(int* nums, int numsSize) {
    int zero_pointer = 0;
    int num_pointer = 0;

    while (num_pointer < numsSize - 1) {
        /* find first zero #1#
        while (nums[zero_pointer] != 0 && zero_pointer < numsSize - 1) {zero_pointer++;}
        if (zero_pointer == numsSize - 1 && nums[zero_pointer] != 0) break;

        /* find first nonzero #1#
        num_pointer = zero_pointer;
        while (nums[num_pointer] == 0 && num_pointer < numsSize - 1) {num_pointer++;}

        nums[zero_pointer] = nums[num_pointer];
        nums[num_pointer] = 0;
    }
}*/

void moveZeroes(int* nums, int numsSize) {
    int zero_pointer = 0;

    for (int num_pointer = 0; num_pointer < numsSize; num_pointer++) {
        if (nums[num_pointer]) {
            int temp = nums[zero_pointer];
            nums[zero_pointer] = nums[num_pointer];
            nums[num_pointer] = temp;
            zero_pointer++;
        }
    }
}

int main() {
    int nums[] = {4, 2, 4, 0, 0, 3, 0, 5, 1, 0}; // {0, 1, 0, 3, 12}; // {4, 2, 4, 0, 0, 3, 0, 5, 1, 0}; // {2, 1}; // {0, 1, 0, 3, 12};

    moveZeroes(nums, 10);

    printf("After move:\n");
    for (int i = 0; i < 10; i++) {
        printf("%d ", nums[i]);
    }
    return 0;
}
