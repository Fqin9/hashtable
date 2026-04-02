#include <math.h>
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>

typedef struct Pair {
    size_t key;
    size_t value;
    struct Pair *next;
} Pair;
typedef struct Hashmap {
    Pair* *buckets;
    size_t size;
    size_t count;
 } Hashmap;

int Hash(Hashmap *hashmap, size_t key) {
    return key % hashmap->size;
}
int inithashmap(Hashmap** retrn, size_t size) /*双指针传递地址*/{
    //动态分配内存
    *(retrn) = (Hashmap*)malloc(sizeof(Hashmap));
    (*retrn)->size = size;
    (*retrn)->count = 0;
    (*retrn)->buckets = (Pair**)malloc(sizeof(Pair*) * size);
    for (int i = 0; i < size; i++) {
        (*retrn)->buckets[i] = (Pair*)malloc(sizeof(Pair));
    }
    return 0;
}
int insert(Hashmap *hashmap, size_t key, size_t value) {
    if (hashmap == NULL) {
        printf("Hashmap is NULL\n");
        return -1;
    }
    int index = Hash(hashmap, key);
    //判断头节点
    Pair *curr = hashmap->buckets[index];
    while (curr != NULL) {
        if (curr->key == key) {
            curr->value = value;//将节点的值进行更新
            return 0;
        }
        curr = curr->next;//节点指向下一个
    }
    Pair *tmp = (Pair*)malloc(sizeof(Pair));
    if (tmp == NULL) {
        printf("Pair is NULL\n");
        return -1;
    }

}
int main(void) {

    return 0;
}