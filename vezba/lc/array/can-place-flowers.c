/*
 * Problem:
 * You have a long flowerbed in which some of the plots are planted, and some are not.
 * However, flowers cannot be planted in adjacent plots.
 *
 * Given an integer array flowerbed containing 0's and 1's,
 * where 0 means empty and 1 means not empty, and an integer n,
 * return true if n new flowers can be planted in the flowerbed without violating the no-adjacent-flowers rule
 * and false otherwise.
 */

#include <stdio.h>

enum is_planted {
    FALSE,
    TRUE
};

enum plot_status {
    EMPTY = 0,
    PLANTED = 1
};

int canPlantAtPosition(const int *flowerbed, const int size, const int position) {
    const int is_current_empty = flowerbed[position] == EMPTY;
    // for left position - if first empty position is beginning of the array, we need one place
    const int is_left_empty = position == 0 || flowerbed[position - 1] == EMPTY;
    // for right position - if last empty position is an end of the array, we need one place
    const int is_right_empty = position == size - 1 || flowerbed[position + 1] == EMPTY;

    return is_current_empty && is_left_empty && is_right_empty;
}

int canPlaceFlowers(int *flowerbed, int flowerbedSize, int n) {
    if (n == 0) return TRUE;

    for (int i = 0; i < flowerbedSize; i++) {
        if (canPlantAtPosition(flowerbed, flowerbedSize, i)) {
            flowerbed[i] = PLANTED;

            if (--n == 0) return TRUE;
        }
    }

    return FALSE;
}

int main() {
    int flowerbed[] = {1, 0, 0, 0, 1};
    int n = 1;
    printf("%d\n", canPlaceFlowers(flowerbed, 5, n));

    int n2 = 2;
    printf("%d\n", canPlaceFlowers(flowerbed, 5, n2));
}