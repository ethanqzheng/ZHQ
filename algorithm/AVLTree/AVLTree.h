//
// Created by 郑红强 on 2021/4/22.
//

#ifndef AVLTREE_AVLTREE_H
#define AVLTREE_AVLTREE_H

#include <stdio.h>
#include <stdlib.h>

typedef struct AVLnode *AVLTree;

struct AVLnode {
    int value;
    struct AVLnode *left;
    struct AVLnode *right;
    int height;
};

AVLTree single_transfer_left(AVLTree T);

AVLTree single_transfer_right(AVLTree T);

AVLTree duoble_transfer_left(AVLTree T);

AVLTree duoble_transfer_right(AVLTree T);

int height_tree(AVLTree T);

int Max(int a, int b);

void printAVLTree(AVLTree T);

AVLTree insert_node(int x, AVLTree T) {
    if (T == NULL) {
        T = (AVLTree) malloc(sizeof(struct AVLnode));
        if (T) {
            T->value = x;
            T->height = 0;
            T->left = NULL;
            T->right = NULL;
        } else {
            printf("out of space !!!\n");
        }
    } else if (x < T->value) {
        T->left = insert_node(x, T->left);
        if ((height_tree(T->left) - height_tree(T->right)) == 2) {
            if (x < T->left->value) {
                T = single_transfer_left(T);
            } else {
                T = duoble_transfer_left(T);
            }
        }
    } else if (x > T->value) {
        T->right = insert_node(x, T->right);
        if ((height_tree(T->right) - height_tree(T->left)) == 2) {
            if (x > T->right->value) {
                T = single_transfer_right(T);
            } else {
                T = duoble_transfer_right(T);
            }
        }
    }
    T->height = Max(height_tree(T->left), height_tree(T->right)) + 1;
    return T;
}

AVLTree duoble_transfer_right(AVLTree T) {
    T->right = single_transfer_left(T->right);
    return single_transfer_right(T);
}

AVLTree duoble_transfer_left(AVLTree T) {
    T->left = single_transfer_right(T->left);
    return single_transfer_left(T);
}

AVLTree single_transfer_right(AVLTree T) {
    AVLTree K;
    K = T->right;
    T->right = K->left;
    K->left = T;
    T->height = Max(height_tree(T->left), height_tree(T->right)) + 1;
    K->height = Max(T->height, height_tree(K->right)) + 1;
    return K;
}

AVLTree single_transfer_left(AVLTree T) {
    AVLTree K;
    K = T->left;
    T->left = K->right;
    K->right = T;
    T->height = Max(height_tree(T->left), height_tree(T->right)) + 1;
    K->height = Max(height_tree(K->left), T->height) + 1;
    return K;
}

int Max(int a, int b) {
    return a > b ? a : b;
}

int height_tree(AVLTree T) {
    if (T) {
        return T->height;
    }
    return -1;
}

void printAVLTree(AVLTree T) {
    if (T != NULL) {
        printAVLTree(T->left);
        printf(" %d ", T->value);
        printAVLTree(T->right);
    }
}

#endif //AVLTREE_AVLTREE_H
