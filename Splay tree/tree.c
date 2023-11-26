#include "tree.h"
#include <string.h>

static Node* splay(Splay* data, Node* cur, char* key){
    if (cur == NULL) return cur;

    int d = strcmp(key, cur->key);
    if (d == 0) return cur;

    else if (d < 0){
        if (cur->left == NULL) return cur;
        int cmp = strcmp(key, cur->left->key);

        if (cmp < 0){
            cur->left->left = splay(data, cur->left->left, key);
            cur = rightRotate(data, cur);
        }
        else if (cmp > 0){
            cur->left->right = splay(data, cur->left->right, key);
            if (cur->left->right != NULL){
                cur->left = leftRotate(data, cur->left);
            }
        }
        if (cur->left == NULL){
            return cur;
        }
        else return rightRotate(data, cur);
    }
    else {
        if (cur->right == NULL) return cur;
        int cmp = strcmp(key, cur->right->key);

        if (cmp < 0) {
            cur->right->left = splay(data, cur->right->left, key);
            if (cur->right->left != NULL) {
                cur->right = rightRotate(data, cur->right);
            }
        } else if (cmp > 0) {
            cur->right->right = splay(data, cur->right->right, key);
            cur = leftRotate(data, cur);

        }
        if (cur->right == NULL) {
            return cur;
        }
        else return leftRotate(data, cur);
    }

}

int search(Splay* data, char* key){
    if (data->root){
        splay(data, data->root, key);
        int d = strcmp(data->root->key, key);
        if (d == 0) return 0;
    }
    return 1;
}

Node* make(char* key, unsigned int value){
    Node* n = calloc(1, sizeof(Node));
    n->key = key;
    n->value = value;
    return n;
}

int push(Splay* data, char* key, unsigned int value){
    Node* new = make(key, value);
    if (data->root){
        if (insert(data->root, new) == 0){
            return search(data, key);
        }
        else return 1;
    }
    else {
        data->root = new;
        return 0;
    }

}

static int insert(Node* cur, Node* new){
    int d = strcmp(new->key, cur->key);
    if (d > 0){
        if (cur->right){
            return insert(cur->right, new);
        }
        else{
            cur->right = new;
            new->parent = cur->right;
            return 0;
        }
    }
    else if (d < 0){
        if (cur->left){
            return insert(cur->left, new);
        }
        else{
            cur->left = new;
            new->parent = cur->left;
            return 0;
        }
    }
    else{
        free(new->key);
        free(new);
        return 1;
    }
}

Splay* delete(Splay* data, char* key){
    int res = search(data, key);
    if (res == 0){
        Node* right = data->root->right;
        Node* left = data->root->left;
        free(data->root->key);
        data->root->right = NULL;
        data->root->left = NULL;
        free(data->root);

        if (left == NULL && right == NULL){

        }
        else if (left == NULL){
            right->parent = NULL;
            data->root = right;
        }
        else{
            left->parent = NULL;
            data->root = left;
            char* max = findMax(data->root);
            search(data, max);
            if (right) right->parent = data->root;
            data->root->right = right;
        }
        return data;
    }
    else return data;
}

char* findMax(Node* cur){
    if (cur->right){
        return findMax(cur->right);
    }
    else return cur->key;
}

static Node* rightRotate(Splay* data, Node* x){
    Node* y = x->left;
    x->left = y->right;
    if (y->right){
        y->right->parent = x;
    }
    y->parent = x->parent;
    if (x->parent == NULL){
        data->root = y;
    }

    y->right = x;
    x->parent = y;
    return y;
}

static Node* leftRotate(Splay* data, Node* x){
    Node* y = x->right;
    x->right = y->left;
    if (y->left){
        y->left->parent = x;
    }
    y->parent = x->parent;
    if (x->parent == NULL){
        data->root = y;
    }

    y->left = x;
    x->parent = y;
    return y;
}

void inOrder(Node* cur, FILE* file){
    if (cur){
        fprintf(file, "Key: %s | value: %u\n", cur->key, cur->value);
        inOrder(cur->left, file);
        inOrder(cur->right,file);
    }
}

int searchMax(Splay* data, char* string){
    if (data->root == NULL) return 1;
    char** max = NULL;
    char* min = "'/0'";
    max = &min;
    search_max(data->root, string, max);
    if (max != NULL) {
        splay(data, data->root, *max);
        return 0;
    }
    return 1;
}

void search_max(Node* cur, char* string, char** max){
    if (cur){
        int d = strcmp(cur->key, *max);
        int l = strcmp(cur->key, string);
        if (l < 0 && d > 0){
            *max = cur->key;
        }
        search_max(cur->right, string, max);
        search_max(cur->left, string, max);
    }
}

void free_tree(Node* cur){
    if (cur){
        free_tree(cur->left);
        free_tree(cur->right);
        free(cur->key);
        free(cur);
    }
}

static int position(Node* cur){
    if (cur->parent != NULL){
        return strcmp(cur->key, cur->parent->key);
    }
    else return 0;
}

static int isZigZag(Node* cur){
    int a = position(cur);
    if (a != 0){
        int b = position(cur->parent);
        if (b >= 0 && a < 0) return 1;
        if (b <= 0 && a > 0) return 1;
        return 0;
    }
    return 0;
}

static int find(Node* cur, char* key, int* height){
    if (cur){
        (*height) += 1;
        int dif = strcmp(key, cur->key);
        if (dif < 0){
            return find(cur->left, key, height);
        }
        else if (dif > 0){
            return find(cur->right, key, height);
        }
        else{
            return 1;
        }
    }
    else return 0;
}

void ascetic(Splay* data, Node* cur) {
    if (cur) {
        ascetic(data, cur->right);
        int height = 0;
        find(data->root, cur->key, &height);

        int zz = isZigZag(cur);
        int branch = 0;

        if (zz == 1){
            find(data->root, cur->parent->key, &branch);
        }
        for (int i = 0; i < height - 1; i++){
            if (branch != 0 && branch - 2 == i){
                printf("     |");
            }
            else printf("      ");
        }

        int pos = position(cur);
        if (pos > 0){
            printf("/--->");
        }
        else if (pos < 0) {
            printf("\\--->");
        }
        else{
            printf("|--->");
        }

        printf("%s\n", cur->key);
        ascetic(data, cur->left);
    }
}