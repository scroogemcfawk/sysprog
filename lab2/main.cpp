//
// Created by scroo on 3/3/2023.
//

#include <iostream>
using namespace std;


void bubbleSort(int* arr, int len) {
    long max = 0;
    asm(
            "mov %1, %%rax;"
            "mov %2, %%rbx;"
            "sub $1, %%ebx;"
            "cmp $0, %%ebx;"
            "jle bout;"

            "bouter:"
                "mov $1, %%ecx;"
                "binner:"
                    "mov (%%rax, %%rcx, 4), %%r9d;"
                    "dec %%ecx;"
                    "mov (%%rax, %%rcx, 4), %%r8d;"
                    "cmp %%r9d, %%r8d;"
                    "jle bnext;"
                    "mov %%r9d, (%%rax, %%rcx, 4);"
                    "inc %%ecx;"
                    "mov %%r8d, (%%rax, %%rcx, 4);"


                    "bnext:"
                    "inc %%ecx;"
                    "cmp %%ebx, %%ecx;"
                "jle binner;"

                "dec %%ebx;"
                "cmp $0, %%ebx;"
            "jg bouter;"
            "bout:"
            "mov %%r8d, %0;"
            : "=m"(max)
            : "m"(arr), "m"(len)
            );
}



void selectionSort(int* arr, int len) {
    long max = 0;
    asm(
        "mov %1, %%rax;"
        "mov %2, %%rbx;"
        "sub $1, %%ebx;"
        "cmp $0, %%ebx;"
        "jle out;"

        "outer:"
            "mov $0, %%edx;"
            "mov (%%rax, %%rdx, 4), %%r8d;"
            "mov $1, %%ecx;"
            "inner:"
                "mov (%%rax, %%rcx, 4), %%r9d;"
                "cmp %%r9d, %%r8d;"
                "jge next;"

                "mov %%ecx, %%edx;"
                "mov %%r9d, %%r8d;"

                "next:"
                "inc %%ecx;"
                "cmp %%ebx, %%ecx;"
            "jle inner;"

            "dec %%ecx;"
            "mov (%%rax, %%rcx, 4), %%r9d;"
            "mov %%r8d, (%%rax, %%rcx, 4);"
            "mov %%r9d, (%%rax, %%rdx, 4);"

            "skipswap:"
            "dec %%ebx;"
            "cmp $0, %%ebx;"
        "jg outer;"
        "out:"
        "mov %%r8d, %0;"
        : "=m"(max)
        : "m"(arr), "m"(len)
        );
}

int main(int argc, char**argv) {
    int len = 10;
    int* arr = new int[]{9,8,7,6,5,4,3,2,1,0};

    bubbleSort(arr, len);

    for (int i = 0; i < len; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;

    return 0;
}
