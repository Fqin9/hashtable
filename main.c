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
    if (size < 0) {
        printf("init hashmap with size -1\n");
        return -1;
    }
    *(retrn) = (Hashmap*)malloc(sizeof(Hashmap));
    if (*(retrn) == NULL) {
        printf("fuck clang in init 1\n");
        return -1;
    }
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
    //头插法
    tmp->key = key;
    tmp->value = value;
    tmp->next = hashmap->buckets[index];
    hashmap->buckets[index] = tmp;
    hashmap->count++;
    return 0;
}
int find(Hashmap *hashmap, size_t key,int *value) {
    if (hashmap == NULL || value == NULL) {
        printf("Hashmap is NULL\n");
        return -1;
    }
    int index = Hash(hashmap, key);
    Pair *curr = hashmap->buckets[index];
    while (curr != NULL) {
        if (curr->key == key) {
            *value = curr->value;
            return 0;
        }
        curr = curr->next;
    }
    return 1;
}
int* twoSum(int* nums, int numsSize, int target, int* returnSize) {
    *returnSize = 2;
    int* back = (int*)malloc(sizeof(int) * *returnSize);
    if (back == NULL) {  // 补充malloc失败检查
        printf("malloc back failed\n");
        *returnSize = 0;
        return NULL;
    }
    back[0] = 0; back[1] = 0;
    Hashmap *map;
    inithashmap(&map,numsSize);
    for (size_t i =0; i < numsSize; i++) {
        int get = 0; // fuck clang
        if (find(map,target - nums[i],&get) == 0) {
            back[0] = get;
            back[1] = i;
            break;
        }
        insert(map,nums[i],i);
    }
    return back;
}