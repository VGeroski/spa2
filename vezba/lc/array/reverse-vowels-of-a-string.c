/*
 * Problem:
 * Given a string s, reverse only all the vowels in the string and return it.
 * The vowels are 'a', 'e', 'i', 'o', and 'u', and they can appear in both lower and upper cases, more than once.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int isVowel(const char c) {
    return c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u' ||
           c == 'A' || c == 'E' || c == 'I' || c == 'O' || c == 'U';
}

char *reverseVowels(char *s) {
    const int n = strlen(s);
    char *s_mod = (char *)malloc(sizeof(char) * (n + 1));
    strcpy(s_mod, s);

    int i = 0;
    int j = n - 1;
    while (i < j) {
        while (i < j && !isVowel(s_mod[i])) i++;
        while (i < j && !isVowel(s_mod[j])) j--;

        if (i < j) {
            const char temp = s_mod[i];
            s_mod[i] = s_mod[j];
            s_mod[j] = temp;
            i++;
            j--;
        }
    }
    s_mod[n] = '\0';
    return s_mod;
}

int main() {
    char *s = "IceCreAm";
    char *s_reversed = reverseVowels(s);
    printf("%s\n", s_reversed);
    free(s_reversed);

    char *s2 = "leetcode";
    char *s2_reversed = reverseVowels(s2);
    printf("%s\n", s2_reversed);
    free(s2_reversed);
}