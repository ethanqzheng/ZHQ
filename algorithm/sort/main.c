#include <stdio.h>
#include "sort.h"

void test();

void test() {
    int a[] = {0,3,2,4,5,1,6,7,9,8};
    int size = sizeof(a)/sizeof(a[0]);

//    insert_sort(a,size);		// size is the length of array
//    shell_sort(a, size);
//    bubble_sort(a,size);
//    select_sort(a,size);
//    heap_sort(a,size);
//    quick_sort(a,0,size-1);	//size - 1 is the index of last element
    merge_sort(a,0,size-1);

    for (int i = 0; i < size; ++i) {
        printf("%d ",a[i]);
    }
    printf("\n");
}

int main() {
    test();
    return 0;
}