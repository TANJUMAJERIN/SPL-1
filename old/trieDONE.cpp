#include<bits/stdc++.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
using namespace std;

int CHAR_TO_INDEX(char c) {
    if (c >= 'a' && c <= 'z') {
        return (int)c - (int)'a';
    } else {
        return (int)c - (int)'1' + 26;
    }
}


struct TrieNode
{
    struct TrieNode *children[36];


    bool isEndOfWord;
};


struct TrieNode *getNode(void)
{
    struct TrieNode *pNode = NULL;

    pNode = (struct TrieNode *)malloc(sizeof(struct TrieNode));

    if (pNode)
    {
        int i;

        pNode->isEndOfWord = false;

        for (i = 0; i < 36; i++)
            pNode->children[i] = NULL;
    }

    return pNode;
}


void insert(struct TrieNode *root, const char *key)
{
    int level;
    int length = strlen(key);
    int index;

    struct TrieNode *pCrawl = root;

    for (level = 0; level < length; level++)
    {
        index = CHAR_TO_INDEX(key[level]);
        if (!pCrawl->children[index])
            pCrawl->children[index] = getNode();

        pCrawl = pCrawl->children[index];
    }


    pCrawl->isEndOfWord = true;
}


bool search(struct TrieNode *root, const char *key)
{
    int level;
    int length = strlen(key);
    int index;
    struct TrieNode *pCrawl = root;

    for (level = 0; level < length; level++)
    {
        index = CHAR_TO_INDEX(key[level]);

        if (!pCrawl->children[index])
            return false;

        pCrawl = pCrawl->children[index];
    }

    return (pCrawl->isEndOfWord);
}


int main()
{

    char keys[200][65];
    int count = 0;

    FILE *fp = fopen("hash.txt", "r");
    if (fp == NULL) {
        printf("Error opening file\n");
        return 1;
    }

    while (fscanf(fp, "%s", keys[count]) != EOF) {
    count++;
}

fclose(fp);
    for (int i = 0; i < count; i++) {
        printf("%s\n", keys[i]);
    }

    struct TrieNode *root = getNode();


    int i;
    for (i = 0; i < count; i++)
        insert(root, keys[i]);


    if(search(root, "f78a74f5cdea8c55468cd275d7614b6a3e448a24e5da2dc979ac063e60490eb3"))
        cout<<"present in trie"<<endl;
    else
        cout<<"not present in trie"<<endl;
   /* printf("%s --- %s\n", "these", output[search(root, "ahjkshjku")] );
    printf("%s --- %s\n", "hash3", output[search(root, "77eea820a47d140f881ab34dc2b46b4984ae56729fa11155c4fb3115f49547a8")] );
    printf("%s --- %s\n", "thaw", output[search(root, "nhby67hjyaf")] );*/

    return 0;
}

