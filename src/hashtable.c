#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#define TABLE_SIZE 100000   // HOW MANY DIFFERENT WORDS CAN BE STORED
#define MAX_WORD_LEN 500    // MAX SIZE OF THE WORD

struct WordCount {
    int count;
    char word[MAX_WORD_LEN];
};

// GLOBAL VARIABLES
struct WordCount* hashArray[TABLE_SIZE]={NULL};
int wordCountAll = 0;
int wordCountDiff = 0;


// FUNCTIONS
unsigned int Ht_hash(char *str);
int Ht_insert(char* word);
int Ht_find(char* word);
int Ht_delete(char* word);
void Ht_printMostUsed(int topWordCount, char order);
void Sort_swap(int *a, int *b, int *A, int *B);
int Sort_partition(int (*arr)[2], int low, int high);
void Sort_quickSort(int (*arr)[2], int low, int high);




/**
    * djb2 hash-function for string
    @param Char array(string) that is hashed
    @return Unsigned integer that is hash-value
*/
unsigned int Ht_hash(char *word){
    unsigned long hash = 5381;
    int c;

    while (c = *word++)
        hash = ((hash << 5) + hash) + c;

    return hash % TABLE_SIZE;
}//...Ht_hash()



/**
    * Increases value of given word in hashtable
    * If word not found, adds it to hashtable and sets value to 1
    * otherwise, increases previous value
    @param Word that is counted
    @return 1 if value was inserted, 0 if not or -1 if hashtable overflows
*/
int Ht_insert(char* word){
    unsigned int key = Ht_hash(word);
    int i = 0;

    // find a free place for word in hashtable or find an existing one
    while ( hashArray[key]!=NULL && strcmp(hashArray[key]->word,word)!=0 ){
        key++;
        i++;
        if (key>TABLE_SIZE-1)
            key=0;

        // if all indexes have a word->cannot save any new words-> aka overflow
        if (i>TABLE_SIZE-1){
            printf("ERROR! OVERFLOW! HASHTABLE IS FULL!\n");
            return -1;
        }
    }

    // if word is not in hashtable
    if(hashArray[key]==NULL){
        struct WordCount* item = (struct WordCount*) malloc(sizeof(struct WordCount));
        strcpy(item->word, word);
        item->count = 1;

        hashArray[key]=item;
        wordCountAll++;
        wordCountDiff++;

        return 1;


    // if word already exists in the hashtable
    }else if(strcmp(hashArray[key]->word,word)==0){
        hashArray[key]->count++;
        wordCountAll++;
        return 1;
    }

    return 0;
}//...Ht_insert()



/**
    * Finds a index value of word from hashtable
    @param Word that is searched
    @return Integer greater or equal to 1 if found, -1 if word is not found
*/
int Ht_find(char* word){
    unsigned int key = Ht_hash(word);
    int i = 0;

    while( hashArray[key]!=NULL && i<TABLE_SIZE ){
        if( strcmp(hashArray[key]->word,word)==0 )
            return key;

        key++;
        i++;

        if (key>TABLE_SIZE-1)
            key=0;
    }

    return -1;
}//...Ht_find()


/**
    * Finds a index value of word from hashtable and deletes it
    @param Word that is searched
    @return Integer 1 if found&deleted, 0 if didn't found
*/
int Ht_delete(char* word){
    int key = Ht_find(word);

    if( key>=0 ){
        free(hashArray[key]);
        hashArray[key] = NULL;
        return 1;
    }

    return 0;
}//...Ht_delete()


/**
    * Swaps four integers' values
    @param Integer a (swapped with integer b)
    @param Integer b (swapped with integer a)
    @param Integer A (swapped with integer B)
    @param Integer B (swapped with integer A)
*/
void Sort_swap(int *a, int *b, int *A, int *B){
    int t1 = *a;
    int t2 = *A;

    *a = *b;
    *A = *B;

    *b = t1;
    *B = t2;
}//...Sort_swap()


/**
    * Part of quicksort -algorithm, don't call this
*/
int Sort_partition(int (*arr)[2], int low, int high){
    int i = (low - 1);
    int pivot = arr[high][0];

    for(int j=low; j<high; j++){
        if(arr[j][0] <= pivot){
            i++;
            Sort_swap(&arr[i][0], &arr[j][0], &arr[i][1], &arr[j][1]);
        }
    }

    Sort_swap(&arr[i+1][0], &arr[high][0], &arr[i+1][1], &arr[high][1]);

    return (i+1);
}//...Sort_partition()


/**
    * Sorting algorithm based on quicksort that is recursive
    @param 2D array. First array contains count/hashtable-index pair array
    @param Lowest index, usually 0 when called
    @param Highest index, number of pair indexes aka highest index.
*/
void Sort_quickSort(int (*arr)[2], int low, int high){
    if(low<high){
        int pi = Sort_partition(arr, low, high);
        Sort_quickSort(arr, low, pi-1);
        Sort_quickSort(arr, pi+1, high);
    }
}//...Sort_quickSort()


/**
    * Creates count-hashtable-index -pair array from all unique words
    * found from hashtable then sorts them and prints top 100 most used words
    * and lastly, empties hashtable freeing memory.
    @param Integer how many top words will be printed
    @param Char, if '-' then print top words in ascending order, otherwise descending
*/
void Ht_printMostUsed(int topWordCount, char order){
    /*  Create 2D array of unique words found from hashtable
    *
    *   arr[x][2]   x=size is number of unique words
    *   arr[][0]    0=index, word count is stored to this index
    *   arr[][1]    1=index, hashtable-index for specific word is stored to this index
    */
    int sortArrays[wordCountDiff][2];

    // Add word's count and that word's index in hashtable to created array
    int j = 0;
    for( int i=0; i<TABLE_SIZE; i++){
        if( hashArray[i]!=NULL ){
            sortArrays[j][0]=hashArray[i]->count;
            sortArrays[j][1]=i;
            j++;
        }
    }


    // Sort created 2D array using custom quicksort -algorithm
    printf("Begin sorting words...");
    Sort_quickSort(sortArrays,0, wordCountDiff-1);
    printf("DONE\n");
    printf("- - - - - - - - -\n");


    // Pre-prints
    printf("Total number of words = %d\n",wordCountAll);
    printf("Number of different words = %d\n",wordCountDiff);
    printf("The %d most common words:\n",topWordCount);
    printf("%-16s%-22s\n","WORD","NUMBER OF OCCURRENCIES");


    // Print top words, if not enough unique words, print all
    // Print top most used or top least used
    int topWords = topWordCount;
    if( order=='+' ){
        j = 0;
        while( j<wordCountDiff && topWords>0 ){
            printf("%-16s%-22d\n",hashArray[sortArrays[j][1]]->word,sortArrays[j][0]);
            topWords--;
            j++;
        }

    }else{
        j = wordCountDiff-1;
        while( j>0 && topWords>0 ){
            printf("%-16s%-22d\n",hashArray[sortArrays[j][1]]->word,sortArrays[j][0]);
            topWords--;
            j--;
        }
    }


    // Then remember to free memory ^__^
    for( int i=0; i<TABLE_SIZE; i++ ){
        free(hashArray[i]);
        hashArray[i]=NULL;
    }

    printf("- - - - - - - - -\n");
}//...Ht_printMostUsed()









