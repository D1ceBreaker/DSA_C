#include "tree.h"

void add(Tree* data, char* key, unsigned int value){
    Info* i = calloc(1, sizeof(Info));
    i->value = value;
    i->release = 1;
    Node* new = calloc(1, sizeof(Node));
    new->key = key;
    new->list = i;
    if (data->root == NULL){
        data->root = new;
    }
    else{
        int result = push(data->root, new);
    }
}

int push(Node* cur, Node* new){
    int dif = strcmp(new->key, cur->key);
    if (dif > 0){
        if (cur->right){
            return push(cur->right, new);
        }
        else {
            new->parent = cur;
            cur->right = new;
            return 0;
        }
    }
    else if (dif < 0){
        if (cur->left){
            return push(cur->left, new);
        }
        else {
            new->parent = cur;
            cur->left = new;
            return 0;
        }
    }
    else{
        unsigned int rel = cur->list->release;
        new->list->next = cur->list;
        cur->list = new->list;
        new->list->release = rel + 1;

        free(new->key);
        free(new);
        return 1;
    }
}

int delete(Tree* data, char* key, unsigned int rel){
    Node* delete = search(data->root, key);
    if (!delete) return 1;
    delete_list(delete, rel);
    if (delete->list == NULL){
        del(data, delete);
    }
    return 0;
}

int delete_list(Node* host, unsigned int rel){
    Info* ptr = host->list;
    Info* prev = NULL;
    while (ptr){
        if (ptr->release == rel) break;
        prev = ptr;
        ptr = ptr->next;
    }
    if (ptr == NULL) return 1;
    if (ptr == host->list) {
        host->list = ptr->next;
        free(ptr);
        return 0;
    }
    if (prev){
        prev->next = ptr->next;
    }
    free(ptr);
    return 0;
}

int del(Tree* data, Node* delete){
    if (!delete) return 1;
    Node* child = NULL;
    Node* parent = NULL;
    if (delete->right && delete->left){
        Node* replace = findMin(delete->right);
        child = replace->right;
        parent = replace->parent;
        if (child) child->parent = parent;
        int d = position(replace);
        if (d > 0){
            parent->right = child;
        }
        else if (d < 0) parent->left = child;

        replace->parent = delete->parent;
        if (delete->parent == NULL) data->root = replace;
        else{
            int pos = position(delete);
            if (pos > 0){
                delete->parent->right = replace;
            } else if (pos < 0) delete->parent->left = replace;
        }

        if (replace != delete->right) replace->right = delete->right;
        replace->left = delete->left;
        if (delete->right) delete->right->parent = replace;
        delete->left->parent = replace;
        free_node(delete);
        return 0;
    }
    else if (delete->left && delete->right == NULL){
        child = delete->left;
        parent = delete->parent;
        child->parent = parent;
    }
    else if (delete->right && delete->left == NULL){
        child = delete->right;
        parent = delete->parent;
        child->parent = parent;
    }
    else if (delete->right == NULL && delete->left == NULL){
        child = NULL;
        parent = delete->parent;
    }
    if (parent == NULL) data->root = child;
    else{
        int pos = position(delete);
        if (pos > 0){
            parent->right = child;
        } else if (pos < 0) parent->left = child;
    }
    free_node(delete);
    return 0;
}

void free_node(Node* node){
    free(node->key);
    Info* ptr = node->list;
    Info* prev = NULL;
    while (ptr){
        prev = ptr;
        ptr = ptr->next;
        free(prev);
    }
    free(node);
}

Node* search(Node* cur, char* key){
    if (cur){
        int dif = strcmp(key, cur->key);
        if (dif < 0){
            return search(cur->left, key);
        }
        else if (dif > 0){
            return search(cur->right, key);
        }
        else{
            return cur;
        }
    }
    else return NULL;
}

Node* findMin(Node* cur){
    if (cur->left){
        return findMin(cur->left);
    }
    else return cur;
}

void inOrder(Node* cur, FILE* file){
    if (cur){
        inOrder(cur->right, file);
        fprintf(file,"%s\n", cur->key);
        inOrder(cur->left, file);
    }
}

void tree_delete(Node* cur){
    if (cur){
        tree_delete(cur->left);
        tree_delete(cur->right);
        free_node(cur);
    }
}

void ascetic(Tree* data, Node* cur) {
    if (cur) {
        ascetic(data, cur->right);
        int height = 0;
        int q = find(data->root, cur->key, &height);

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

        printf("%s: ", cur->key);
        Info* ptr = cur->list;
        while (ptr){
            printf("%u ", ptr->value);
            ptr = ptr->next;
        }
        printf("\n");
        ascetic(data, cur->left);
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

