#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdint.h>

typedef struct Pair {
    int key;
    int value;
    struct Pair *next;
} Pair;

typedef struct Hashmap {
    Pair** buckets;
    size_t size;
    size_t count;
} Hashmap;

int hash(Hashmap *hashmap, int key) {
    // 更高效的哈希函数，减少冲突
    key = ((key >> 16) ^ key) * 0x45d9f3b;
    key = ((key >> 16) ^ key) * 0x45d9f3b;
    key = (key >> 16) ^ key;
    return (unsigned int)key % hashmap->size;
}

int init_hashmap(Hashmap** hashmap_ptr, size_t size) {
    if (size == 0) {
        printf("Error: hashmap size must be positive\n");
        return -1;
    }
    
    *hashmap_ptr = (Hashmap*)malloc(sizeof(Hashmap));
    if (*hashmap_ptr == NULL) {
        printf("Error: failed to allocate hashmap memory\n");
        return -1;
    }
    
    (*hashmap_ptr)->size = size;
    (*hashmap_ptr)->count = 0;
    (*hashmap_ptr)->buckets = (Pair**)calloc(size, sizeof(Pair*));
    if ((*hashmap_ptr)->buckets == NULL) {
        printf("Error: failed to allocate buckets memory\n");
        free(*hashmap_ptr);
        *hashmap_ptr = NULL;
        return -1;
    }
    
    return 0;
}

void free_hashmap(Hashmap* hashmap) {
    if (hashmap == NULL) {
        return;
    }
    
    for (size_t i = 0; i < hashmap->size; i++) {
        Pair* curr = hashmap->buckets[i];
        while (curr != NULL) {
            Pair* next = curr->next;
            free(curr);
            curr = next;
        }
    }
    
    free(hashmap->buckets);
    free(hashmap);
}

int insert(Hashmap *hashmap, int key, int value) {
    if (hashmap == NULL) {
        printf("Error: hashmap is NULL\n");
        return -1;
    }
    
    int index = hash(hashmap, key);
    Pair *curr = hashmap->buckets[index];
    
    while (curr != NULL) {
        if (curr->key == key) {
            curr->value = value;
            return 0;
        }
        curr = curr->next;
    }
    
    Pair *tmp = (Pair*)malloc(sizeof(Pair));
    if (tmp == NULL) {
        printf("Error: failed to allocate pair memory\n");
        return -1;
    }
    
    tmp->key = key;
    tmp->value = value;
    tmp->next = hashmap->buckets[index];
    hashmap->buckets[index] = tmp;
    hashmap->count++;
    
    return 0;
}

int find(Hashmap *hashmap, int key, int *value) {
    if (hashmap == NULL || value == NULL) {
        printf("Error: invalid arguments\n");
        return -1;
    }
    
    int index = hash(hashmap, key);
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
    int* result = (int*)malloc(sizeof(int) * *returnSize);
    if (result == NULL) {
        printf("Error: failed to allocate result memory\n");
        *returnSize = 0;
        return NULL;
    }
    
    Hashmap *map;
    if (init_hashmap(&map, numsSize) != 0) {
        printf("Error: failed to initialize hashmap\n");
        *returnSize = 0;
        free(result);
        return NULL;
    }
    
    for (int i = 0; i < numsSize; i++) {
        int complement = target - nums[i];
        int get = 0;
        if (find(map, complement, &get) == 0) {
            result[0] = get;
            result[1] = i;
            free_hashmap(map);
            return result;
        }
        insert(map, nums[i], i);
    }
    
    // 如果没有找到，返回 NULL
    free_hashmap(map);
    free(result);
    *returnSize = 0;
    return NULL;
}