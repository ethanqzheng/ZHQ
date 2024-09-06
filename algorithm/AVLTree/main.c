#include "AVLTree.h"

#define NODENUMBER 5

int main() {
    AVLTree T = NULL;
    for (int i = 0; i < NODENUMBER; ++i) {
        int x;
        scanf("%d", &x);
        T = insert_node(x, T);
        printAVLTree(T);
        printf("\n");
    }
    printAVLTree(T);
    return 0;
}
