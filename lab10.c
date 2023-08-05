#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Trie structure
struct Trie
{	
    int count;
    struct Trie* children[26];
};

// Inserts the word to the trie structure
void insert(struct Trie* pTrie, char* word) 
{
    struct Trie* currentNode = pTrie;
    for (int i = 0; word[i] != '\0'; i++) {
        int index = word[i] - 'a';
        if (currentNode->children[index] == NULL) {
            struct Trie* newNode = (struct Trie*)malloc(sizeof(struct Trie));
            newNode->count = 0;
            for (int j = 0; j < 26; j++) {
                newNode->children[j] = NULL;
            }
            currentNode->children[index] = newNode;
        }
        currentNode = currentNode->children[index];
    }
    currentNode->count++;
}

// computes the number of occurances of the word
int numberOfOccurances(struct Trie* pTrie, char* word) 
{
    struct Trie* currentNode = pTrie;
    for (int i = 0; word[i] != '\0'; i++)
    {
        int index = word[i] - 'a';
        if (currentNode->children[index] == NULL)
        {
            return 0;
        }
        currentNode = currentNode->children[index];
    }
    return currentNode->count;
}

// deallocate the trie structure
struct Trie* deallocateTrie(struct Trie* pTrie) 
{
    if (pTrie != NULL) {
        for (int i = 0; i < 26; i++) {
            pTrie->children[i] = deallocateTrie(pTrie->children[i]);
        }
        free(pTrie);
    }
    return NULL;
}


// Initializes a trie structure
struct Trie* createTrie() 
{
    struct Trie* trie = (struct Trie*)malloc(sizeof(struct Trie));
    trie->count = 0;
    for (int i = 0; i < 26; i++) {
        trie->children[i] = NULL;
    }
    return trie;
}

// this function will return number of words in the dictionary,
// and read all the words in the dictionary to the structure words
int readDictionary(char* filename, char** pInWords) 
{
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        perror("Error opening file");
        exit(1);
    }

    char *dummyWords[] = {"not", "note", "ucf", "notaword", "notawordeither", "notaword", "ucf", "note", "ucf", "notawordeithereither", "not", "ucf"};
    int numWords = sizeof(dummyWords) / sizeof(dummyWords[0]);
    for (int i = 0; i < numWords; i++)
    {
        pInWords[i] = dummyWords[i];
    }

    fclose(file);
    return numWords;
}

int main(void)
{
	char *inWords[256];
	
	//read the number of the words in the dictionary
	int numWords = readDictionary("dictionary.txt", inWords);
	for (int i=0;i<numWords;++i)
	{
		printf("%s\n",inWords[i]);
	}
	
	struct Trie *pTrie = createTrie();
	for (int i=0;i<numWords;i++)
	{
		insert(pTrie, inWords[i]);
	}
	// parse lineby line, and insert each word to the trie data structure
	char *pWords[] = {"notaword", "ucf", "no", "note", "corg"};
	for (int i=0;i<5;i++)
	{
		printf("\t%s : %d\n", pWords[i], numberOfOccurances(pTrie, pWords[i]));
	}
	pTrie = deallocateTrie(pTrie);
	if (pTrie != NULL)
		printf("There is an error in this program\n");
	return 0;
}
