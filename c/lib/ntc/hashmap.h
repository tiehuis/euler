#ifndef _HASHMAP_H_
#define _HASHMAP_H_

typedef struct hnode hnode;
typedef struct hashmap hashmap;

struct hnode {
    void  *key;     /* The key we use to access the data */
    size_t len;     /* The length of the key in bytes to calc the hash and also cmp */
    void  *data;    /* The data that is stored with the associated key */
    int    hash;    /* The hash of the data */
    hnode *next;    /* The next element int this buckets chain */
};

struct hashmap {
    hnode **buckets;      /* All the current buckets */
    size_t  bucket_count; /* How many buckets we currently have */
    size_t  size;         /* The number of buckets that are utilized */
};

hashmap* hashmap_create (const size_t init_cap);
void     hashmap_clear  (hashmap *h);
void     hashmap_put    (hashmap *h, void *data, void *key, const size_t len);
void*    hashmap_get    (hashmap *h, const void *key, const size_t len);
void*    hashmap_remove (hashmap *h, const void *key, const size_t len);

#endif
