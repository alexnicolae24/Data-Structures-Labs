#ifndef __HUFFMAN_H__
#define __HUFFMAN_H__

#include <string.h>

typedef struct {
    unsigned char value;
    int left, right;
} HuffmanNode;

#define Item int

// Including below so `Item` is defined.
#include "heap.h"

void computeFreqs(char *text, int size, int freqs[256]) {
    //initializare cu 0
    for(int i = 0; i < 256 ; i ++){
        freqs[i] = 0;
    }
    //pt fiecare caracter din text, se incrementeaza aparitia lui in freqs
    for(int i = 0; i < size ; i ++){
        freqs[(int)text[i]] ++;
    }
}

HuffmanNode *makeTree(int freqs[256], int *size) {
   //aloc memorie pt arbore
    HuffmanNode *huffman = calloc(512, sizeof(HuffmanNode));
    //creez minheap
    APriQueue minHeap = makeQueue(256);
    *size = 0;
    //construiesc frunzele, le adaug in heap si arbore
    for(int i = 0; i < 256; i++){
        if(freqs[i] != 0){
            //creez nod de tip Item pt heap
            ItemType node;
            //frecventa caracter
            node.prior = freqs[i];
            //nr noduri
            node.content = *size;
            //adaug nod in heap
            insert(minHeap, node);
            //creez nod de tip HuffmanNode, value = caracterul
            huffman[*size].value = (char) i;
            //pun -1 pe ambele ramuri
            huffman[*size].left = -1;
            huffman[*size].right = -1;
            (*size)++;
        }
    }
    //un singur nod in heap
    if(minHeap->size == 1){
        ItemType x = getMin(minHeap);
        huffman[*size].left = x.content;
        huffman[*size].right = -1;
        huffman[*size].value = '\0';
        (*size)++;
    }
    //cel putin 2 noduri
    else{
        while(minHeap->size > 1){
            //scot 2 noduri din heap
            ItemType node1, node2, parent;
            node1 = getMin(minHeap); 
            removeMin(minHeap);
            node2 = getMin(minHeap); 
            removeMin(minHeap);
            //creez parintele celor 2 noduri
            //left si right iau valorile pozitiilor nodurilor scoase din heap
            huffman[*size].left = node1.content;
            huffman[*size].right = node2.content;
            huffman[*size].value = '\0';
            //content = pozitia nodului
            parent.content = *size;
            //prior = suma frecventelor
            parent.prior = node1.prior + node2.prior;
            insert(minHeap,parent);
            (*size)++;
        }
    }
    return huffman;
}

void makeCodes(int index, HuffmanNode *nodes, char **codes, char *code) {
    if(nodes[index].value == '\0'){
        //sunt pe nod ce are elementele pe stanga
        //concatenez la code '0'
        strcat(code,"0");
        //apelez recursiv pentru stanga
        makeCodes(nodes[index].left, nodes, codes, code);
        //am terminat partea stanga
        //scot caracterul '0' de la finalul lui code
        code[strlen(code) - 1] = '\0';
        //sunt pe nod ce are elementele pe dreapta
        //concatenez la code '1'
        strcat(code, "1");
        //apelez recursiv pentru dreapta
        makeCodes(nodes[index].right, nodes, codes , code);
        //scot caracterul '1' de la finalul lui code
        code[strlen(code) -1] = '\0';
    }
    //daca am ajuns la frunza =>s-a construit codul pt caracterul din frunza
    //poate fi adaugat in codes
    else{
        codes[index] = calloc((strlen(code)+1), sizeof(char));
        strcpy(codes[index], code);
    }
}


char *compress(char *text, int textSize, HuffmanNode *nodes, int numNodes) {
    //aloc memorie pt vectorul in care retin sirul comprimat
    char *compressed = calloc(256, sizeof(char));
    int index[256], k = 0;
    if(textSize == 0){
        //nu avem ce comprima
        char *empty = calloc(2, sizeof(char));
        empty[0] = '/';
        return empty;
    }
    //retin indexul fiecarei litere si calculez nr de coduri
    for(int i = 0; i < numNodes && nodes[i].value != '\0'; i++){
        index[(int)nodes[i].value] = k;
        k++;
    }
    //aloc memorie pt codes, unde retin codurile
    char **codes = calloc(k, sizeof(char*));
    compressed[0] = '\0';
    //apelez fct pt a obtine codurile care indica exact codificarea fiecarui caracter
    //primul parametru = indexul radacinii
    makeCodes(numNodes -1, nodes, codes, compressed);
    //am codurile, parcurg textul pt fiecare caracter
    //iau codificarea din codes si o adaug la sirul unde va fi comprimat
    for(int i = 0; i < textSize; i++){
        int index2 = index[(int)text[i]];
        strcat(compressed, codes[index2]);
    }
    return compressed;
}

char *decompress(char *text, int textSize, HuffmanNode *nodes, int numNodes) {
    //aloc memorie pt vectorul unde voi retine sirul decomprimat
    char *decompressed = calloc(256, sizeof(char));
    decompressed[0] = '\0';
    if(textSize == 0){
        //nu am ce decomprima
        return decompressed;
    }
    //index initial pus pe indexul radacinii
    int index = numNodes - 1, size = 0;
    //pentru fiecare caracter din text
    for(int i = 0; i < textSize; i++){
        //index se muta pe indexul nodului din stanga
        if(text[i] == '0'){
            index = nodes[index].left;
        }
        //index se muta pe indexul nodului din dreapta
        else if (text[i] == '1'){
            index = nodes[index].right;
        }
        //nodul la care am ajuns e frunza=> gata decompresia
        //caract gasit in frunza se adauga in decompressed
        //index se reseetaza la indexul radacinii pt a incepe codul pt un nou caracter
        if(nodes[index].value != '\0'){
            decompressed[size++] = nodes[index].value;
            index = numNodes -1;
        }
    }
    decompressed[size] = '\0';
    return decompressed;
}

#endif

