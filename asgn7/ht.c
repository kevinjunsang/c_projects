#include "ht.h"
#include "node.h"
#include "salts.h"
#include "speck.h"
#include <stdio.h>
#include <inttypes.h>
#include <stdlib.h>
#include <string.h>

struct HashTable {
    uint64_t salt[2];
    uint32_t size;
    Node **slots;
};

struct HashTableIterator {
    HashTable *table;
    uint32_t slot;
};

HashTable *ht_create(uint32_t size) {
    HashTable *ht = (HashTable *) malloc(sizeof(HashTable));
    ht->size = size;
    ht->salt[0] = SALT_HASHTABLE_LO;
    ht->salt[1] = SALT_HASHTABLE_HI;
    ht->slots = (Node **) calloc(size, sizeof(Node *));
    return ht;
}

void ht_print(HashTable *ht) {
    for (uint32_t i = 0; i < ht_size(ht); i += 1) {
        node_print(ht->slots[i]);
    }
}

void ht_delete(HashTable **ht) {
    if (*ht && (*ht)->slots) {
        for (uint32_t i = 0; i < (*ht)->size; i += 1) {
            if ((*ht)->slots[i] != NULL) {
                node_delete(&(*ht)->slots[i]);
            }
        }
        free((*ht)->slots);
        free(*ht);
        *ht = NULL;
    }
    return;
}

uint32_t ht_size(HashTable *ht) {
    return ht->size;
}

Node *ht_lookup(HashTable *ht, char *word) {
    uint32_t index = hash(ht->salt, word) % ht->size;
    if (ht->slots[index] == NULL) {
        return NULL;
    } else {
        return ht->slots[index];
    }
}

Node *ht_insert(HashTable *ht, char *word) {
    uint32_t index = hash(ht->salt, word) % ht_size(ht);
    if (ht->slots[index] != NULL) {
        if (strcmp(ht->slots[index]->word, word) == 0) {
            ht->slots[index]->count += 1;
        } else {
            Node *n = NULL;
            return n;
        }
    } else {
        Node *n = node_create(word);
        ht->slots[index] = n;
    }
    return ht->slots[index];
}

HashTableIterator *hti_create(HashTable *ht) {
    HashTableIterator *hti = (HashTableIterator *) malloc(sizeof(HashTableIterator));
    hti->table = ht_create(ht->size);
    hti->table = ht;
    hti->slot = 0;
    return hti;
}

void hti_delete(HashTableIterator **hti) {
    //	for (uint32_t i = 0; i < ht_size((*hti)->table); i += 1) {
    //		if ((*hti)->table->slots[i] != NULL) {
    //			node_delete(&(*hti)->table->slots[i]);
    //		}
    //	}
    //	free((*hti)->table->slots);
    free(*hti);
    *hti = NULL;
}

Node *ht_iter(HashTableIterator *hti) {
    while (hti->slot < ht_size(hti->table) && hti->table->slots[hti->slot] == NULL) {
        hti->slot += 1;
        if (hti->slot > ht_size(hti->table)) {
            return NULL;
        }
    }
    uint32_t index = hti->slot;
    hti->slot += 1;
    return hti->table->slots[index];
}
