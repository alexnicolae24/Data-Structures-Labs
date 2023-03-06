#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef char* Key;
typedef int Value;
typedef long(*HashFunction)(Key, long);

typedef struct Element {
  Key key;
  Value value;
  struct Element *next;
} Element;

typedef struct HashTable {
  Element** elements;
  long size;
  HashFunction hashFunction;
} HashTable;

void initHashTable(HashTable **h, long size, HashFunction f) {
  // Cerinta 1
    (*h) = (HashTable *) malloc(sizeof(HashTable));
    (*h) -> size = size;
    (*h) -> hashFunction = f;
    (*h) -> elements = (Element **)calloc(size, sizeof(Element *));
    int i;
    for(i = 0; i < size; i++) {
        (*h) -> elements[i] == NULL;  
    } 
}

int exists(HashTable *hashTable, Key key) {
  // Cerinta 1
    long indx = hashTable -> hashFunction(key, hashTable -> size);
    Element *el = hashTable -> elements[indx];
    while(el != NULL) {
        if(strcmp(key, el -> key) == 0)
            return 1;
      el = el -> next;
    }
    return 0;
}

Value get(HashTable *hashTable, Key key) {
  // Cerinta 1
   unsigned int h = hashTable -> hashFunction(key,hashTable -> size) % hashTable -> size;
	 Element *el = hashTable -> elements[h];
	 while(el != NULL) {
	 	    if(!strcmp(el->key, key))
	 		     return el -> value;
	 	el = el -> next;
	  }
    return (Value)0;
}

void put(HashTable *hashTable, Key key, Value value) {
  // Cerinta 1
    long indx = hashTable -> hashFunction(key, hashTable -> size);
    Element *el = hashTable -> elements[indx];
    while(el != NULL) {
         if(strcmp(key, el -> key) == 0) {
             el -> value = value;
             return;
         }
       el = el -> next;
    }
    el = (Element *) malloc(sizeof(Element));
    el -> key = strdup(key);
    el -> value = value;
    el -> next = hashTable -> elements[indx];
    hashTable -> elements[indx] = el;
}

void deleteKey(HashTable *hashTable, Key key) {
  // Cerinta 1
    int i  = hashTable -> hashFunction(key,hashTable -> size);
	  if(hashTable -> elements[i] -> value == 0)
         return;
	  else {
		       hashTable -> elements[i] -> key = 0;
		       hashTable -> elements[i] -> value = 0;
		       hashTable -> size--;
	  }
}

void print(HashTable *hashTable) {
  // Cerinta 1
    long i;
    for( i = 0; i < hashTable -> size; i++) {
        Element *el = hashTable -> elements[i];
        if(el != NULL)
        printf("%ld:\n", i);  
        while(el != NULL) {
               printf("     %s : %d \n", el -> key, el -> value);
               el = el -> next;
        }
    }
}

void freeHashTable(HashTable *hashTable) {
  // Cerinta 1
    for(int i = 0; i < hashTable -> size; i++) {
        Element *el = hashTable -> elements[i];
        if (el != NULL) {
            free(el -> key);
            el -> value = 0;
            free(el);
        }
    }
    free(hashTable -> elements);
    free(hashTable);
}


long hash1(Key word, long size) {
  // Cerinta 2
    int i = 0;
    long h = 0;
    while(word[i] != '\0') {
          h = 17 * h + word[i];
          i++;
    }
    return h % size;
}

int main(int argc, char* argv[]) {
  HashTable *hashTable;
  FILE *f1, *f2;
  char word[256];
  long hashSize, common ;

  hashSize = atoi(argv[1]);
  f1 = fopen(argv[2], "r");
  f2 = fopen(argv[3], "r");

  initHashTable(&hashTable, hashSize, &hash1);

  // Cerinta 3
  while(fscanf(f1,"%s",word) != EOF) {
        if(exists(hashTable,word)) {
            put(hashTable, word, get(hashTable,word) + 1);
        }
        else {
               put(hashTable, word, 1);
        }
  }
  print(hashTable);
  Key key;
  
  // ...
  HashTable *hashTable1;
  char word1[256];
  initHashTable(&hashTable1, hashSize, &hash1);
  // Cerinta 4
  while(fscanf(f2,"%s",word1) != EOF) {
        if(exists(hashTable1,word1)) {
            put(hashTable1, word1, get(hashTable1,word1) + 1);
        }
        else {
               put(hashTable1, word1, 1);
        }
  }
  for(int i = 0; i < hashSize; i++) {
    if((exists(hashTable,hashTable -> elements[i] -> key) != 0) && (exists(hashTable1,hashTable1 -> elements[i] -> key) != 0))
            common++;
  }


  // ...

  printf("Common words: %ld\n", common);

  fclose(f1);
  fclose(f2);
  return 0;
}
