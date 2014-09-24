#include <stdlib.h>
#include <string.h>
#include "types.h"
#include "hashmap.h"

/* Next primes > powers of two */
static const size_t prime_sizes[] =
{
    1033, 2053, 4099, 8209, 16411, 32771, 65537, 131101,
    262147, 524309, 1048583, 2097169, 4194319, 8388617,
    16777259, 33554467, 67108879, 134217757, 268435459
    /*536870923, 1073741827, 2147483659, 4294967291*/
};

/* Get the next prime greater than n from table */
inline static const size_t next_prime(const size_t n)
{
    size_t i = 0;
    while (n >= prime_sizes[i]) ++i;
    return prime_sizes[i];
}

/* Compare two keys. If the lengths are not the same, then return
 * non-zero value. We need to compare keys and not hash values to be
 * sure we don't return duplicates that the user doesn't ask for */
static int hashmap_keycmp(const void *key1, const size_t key1_len,
                          const void *key2, const size_t key2_len)
{
    if (key1_len != key2_len) 
        return 1;

    return memcmp(key1, key2, key1_len);
}

/* Create the hashmap with an initial capacity */
hashmap* hashmap_create(const size_t init_cap)
{
    hashmap *h = malloc(sizeof(hashmap));
    h->bucket_count = next_prime(init_cap);
    h->buckets = calloc(h->bucket_count, sizeof(hnode*));
    h->size    = 0;
    return h;
}

/* Resize the hashmap to a load factor of 0.33 then reinsert
 * all the elements into the hashmap */
static void hashmap_rehash(hashmap *h)
{
    size_t new_bucket_count = next_prime(h->bucket_count);
    hnode **new_buckets = calloc(new_bucket_count, sizeof(hnode*));

    /* For each current element in hashmap, get a new index for this new size
     * and store it in the new bucket set */
    size_t i;
    for (i = 0; i < h->bucket_count; ++i) {
        hnode *entry = h->buckets[i];
        while (entry != NULL) {
            hnode *next = entry->next;
            size_t index = entry->hash % new_bucket_count;
            entry->next = new_buckets[index];
            new_buckets[index] = entry;
            entry = next;
        }
    }

    /* Remove the old buckets and insert the new buckets */
    free(h->buckets);
    h->buckets = new_buckets;
    h->bucket_count = new_bucket_count;
}

/* Return a value which indexes a bucket in our hashmap */
static int hashmap_hashfn(const void *key, const size_t len)
{
    char *ckey = (char*)key;
    int hash   = 0;

    size_t i;
    for (i = 0; i < len; ++i) {
        hash += ckey[i];
        hash += (hash << 10);
        hash ^= (hash >> 6);
    }

    hash += (hash << 3);
    hash ^= (hash >> 11);
    hash += (hash << 15);

    return hash;
}

/* Insert a data, key pair into our hashmap */
void hashmap_put(hashmap *h, void *data, void *key, const size_t len)
{
    /* Rehash and resize hashmap if load factor > 0.75 */
    if (h->bucket_count * 3 / 4 <= h->size)
        hashmap_rehash(h);

    /* Create a hnode to insert into bucket */
    hnode *n = malloc(sizeof(hnode));
    n->data = data;
    n->key  = key;
    n->len  = len;
    n->hash = hashmap_hashfn(key, len);
    n->next = NULL;

    /* Calculate the index we need to insert into */
    size_t index = n->hash % h->bucket_count;
    hnode *cur = h->buckets[index];

    /* If there exist some values in this bucket already, traverse it */
    if (cur != NULL) {
        /* Check for head of list being the same first */
        if (hashmap_keycmp(cur->key, cur->len, key, len)) {
            cur->data = n->data;
            free(n);
        }
        /* Else it may exist elewhere in this chain */
        else {
            /* Loop until we match keys */
            while (cur->next != NULL 
                    && hashmap_keycmp(cur->next->key, cur->next->len, key, len))
                cur = cur->next;

            /* We found a matching key, so replace data */
            if (cur->next) {
                cur->next->data = n->data;
                free(n);
            }
            /* End of chain, so put n as new value in this chain */
            else {
                cur->next = n;
                h->size++;
            }
        }
    }
    /* We do not have a value for this bucket so insert straight on */
    else {
        h->buckets[index] = n;
        h->size++;
    }
}

/* Return the data associated with a key. Keep the data in the hashmap */
void* hashmap_get(hashmap *h, const void *key, const size_t len)
{
    size_t index = hashmap_hashfn(key, len) % h->bucket_count;
    hnode *cur = h->buckets[index];

    /* Loop until we match keys or fail to find */
    while (cur != NULL && hashmap_keycmp(cur->key, cur->len, key, len))
        cur = cur->next;

    return cur ? cur->data : NULL;
}

/* Return the data associated with key. Remove the data at the same time */
void* hashmap_remove(hashmap *h, const void *key, const size_t len)
{
    size_t index = hashmap_hashfn(key, len) % h->bucket_count;
    void  *data;
    hnode *cur = h->buckets[index];

    /* If the bucket is not empty, traverse to find element */
    if (cur != NULL) {
        /* If head element matches */
        if (hashmap_keycmp(cur->key, cur->len, key, len)) {
            h->buckets[index] = cur->next;
            data = cur->data;
            free(cur);
            h->size--;
        }
        else {
            while (cur->next != NULL 
                    && hashmap_keycmp(cur->next->key, cur->next->len, key, len))
                cur = cur->next;

            /* We found an element which matches our key */
            if (cur->next) {
                data = cur->next->data;
                hnode *tmp = cur->next;
                cur->next = tmp->next;
                free(tmp);
                h->size--;
            }
            /* Else we didn't find it */
            else {
                data = NULL;
            }
        }
    }
    /* Else it doesn't exist in this chain */
    else {
        data = NULL;
    }

    return data;
}

/* Free all individual bucket chains */
void hashmap_clear(hashmap *h)
{
    size_t i;
    for (i = 0; i < h->bucket_count; ++i) {
        hnode *cur = h->buckets[i];
        while (cur != NULL) {
            hnode *tmp = cur->next;
            free(cur);
            cur = tmp;
        }
    }
    free(h->buckets);
    free(h);
}

#include <stdio.h>

int main(void)
{
    char *keys[]  = { "Key1", "Key2", "Key3", "Key4" };
    ull_t data[] = { 0x4124, 0x5152, 0x4124, 0x4f23 };

    hashmap *h = hashmap_create(0);

    size_t i;
    for (i = 0; i < 4; ++i)
        hashmap_put(h, &data[i], keys[i], strlen(keys[i]));

    void *v;

    v = hashmap_get(h, "Key1", strlen("Key1"));
    printf(v ? "Key1 - 0x%llx\n" : "Key1 - No entry\n", *((ull_t*)v));

    v = hashmap_get(h, "Key2", strlen("Key2"));
    printf(v ? "Key2 - 0x%llx\n" : "Key2 - No entry\n", *((ull_t*)v));

    v = hashmap_remove(h, "Key3", strlen("Key3"));
    printf(v ? "Key3 - 0x%llx\n" : "Key3 - No entry\n", *((ull_t*)v));

    return 0;
}
