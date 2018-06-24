#ifndef HASHSTR_H
#define HASHSTR_H

#include "include/hash.h"
#include "include/stack.h"
#include <math.h>

struct HashChain{
    // isEnd should be determined by hashtable
    boolean              isEnd;
    
    // so should prev and next
    struct HashChain    *prev;
    struct HashChain    *next;  

    // it can't be changed after created
    Uint32               hash;

    // data should be the index of something, it doesn't storage the raw data
    Int32               *data;

    // size
    Int32               _size;
};
typedef struct HashChain *hashcptr;

/*
* create a hashchain
* @param hash:Int32
* @return hashcptr
*/
hashcptr CreateHashChain(Uint32 hash);

/*
* free a hash chain
* @params hashchain:hashcptr
* @return void
*/
void FreeHashChain(hashcptr hashchain);

/*
* add data to a hashchian
* @params (hashchain:hashcptr, data:Int32)
* @return void
*/
void AddHashdata(hashcptr hashchain, Int32 data);

/*
* delete data
* @params (hashchain:hashcptr, data:Int32)
* @return void
*/
boolean DelHashdata(hashcptr hashchain, Int32 data);

/*
* copy element
* @params hashchain:hashcptr
* @return stack:stackptr
*/
stackptr CopyEle(hashcptr hashchain);

struct HashTable{
    // head and tail nothing special
    hashcptr    head_hashchain;
    hashcptr    tail_hashchain;
    
    // it should be a circle
    hashcptr    *index;  
    
    // it should be the num of index
    // the length of a block in index is sqrt(n)
    Int32       blocknum;

    // it's the total length of the  hashtable
    Int32       size;
};
typedef struct HashTable *hashtptr;

/*
* 
* @params chain:chainptr
* @return hashtable:hashtptr
*/
hashtptr CreateHashTable();

/*
* 
* @params hashtable:hashtptr
* @return void
*/
void FreeHashTable(hashtptr hashtable);

/*
* search hashchain (not recommanded but can be called)
* @params (hashtable:hashtptr, hash:Int32)
* @return hashchain:hashcptr
*/
hashcptr FindHash(hashtptr hashtable, Uint32 hash);

/*
* search a place to insert (not recommanded but can be called)
* @params (hashtable:hashtptr, hash:Int32)
* @return hashchain:hashcptr
*/
hashcptr FindPlace(hashtptr hashtable, Uint32 hash);

/*
* search elements
* @params (hashtable:hashtptr, hash:Int32)
* @return stack:stackptr
*/
stackptr SearchHash(hashtptr hashtable, Uint32 hash);

/*
* add element
* @params (hashtable:hashtptr, hash:Int32, data:Int32)
* @return void
*/
void AddHash(hashtptr hashtable, Uint32 hash, Int32 data);

/*
* delete element
* @params (hashtable:hashtptr, hash:Int32, data:Int32)
* @return succ(0)/fail(>=1):boolean
*/
boolean DelHash(hashtptr hashtable, Uint32 hash, Int32 data);

//------------------------------------END------------------------------------------//
#endif