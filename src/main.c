#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include "hashtable.c"

// GLOBAL VARIABLES
clock_t timeBegin;
clock_t timeEnd;

// FUNCTIONS
FILE* AskFilePath(void);
void CountWords(FILE* fptr);
int AskPrintedWordCount();
char AskPrintedWordOrder();
void PrintProcessTime();


/**
    * Main -function
*/
int main( int argc, char *argv[] ){
    // VARIABLES
    FILE* fptr;

    printf("= = = = = = = = = = = = = = = = = = = = = = =");
    printf("\nWORD COUNTER by Toni \"tontsakaze\" Torvela");
    printf("\n- - - - - - - - - - - - - - - - - - - - - - -\n");

    /*
    * If user gives command line argument, try opening the file
    * and count the words from that file
    * User can also give number of printed top words and their order
    */
    if (argc > 1) {
        printf("Opening file: \"%s\"\n",argv[1]);

        fptr = fopen(argv[1], "r");
        if (fptr==NULL ){
            printf("-->ERROR! Couldn't open the file!\n");
        }
        else{
            int n = 100;
            char ord = '+';

            if(argc>2){
                char *ptr;
                n = strtol(argv[2], &ptr, 10);
            }
            if(argc>3){
                ord = argv[3][0];
            }

            timeBegin = clock();

            CountWords(fptr);
            fclose(fptr);
            Ht_printMostUsed(n, ord);

            timeEnd = clock();
            PrintProcessTime();
        }
    }

    /*
    * If user didn't give command line argument
    * ask user to open new file or exit the program.
    * If user wants to open file, ask its path.
    * If file's path is valid and file can be opened,
    * ask how many top words will be printed and
    * in which order
    */
    else{
        fptr = AskFilePath();

        if( fptr!=NULL ){
            printf("- - - - - - - - -\n");
            int n = 100;
            n = AskPrintedWordCount();
            char ord = '-';
            ord = AskPrintedWordOrder();


            timeBegin = clock();

            CountWords(fptr);
            fclose(fptr);
            Ht_printMostUsed(n, ord);

            timeEnd = clock();
            PrintProcessTime();
        }

    }

    printf("...");
    char c = scanf("%c", &c);

    return 0;
}// main()



void PrintProcessTime(){
    double timeSpent = (double)(timeEnd - timeBegin) / CLOCKS_PER_SEC;

    if(timeSpent>0.00005){
        printf("Counting and ordering took %.5f seconds.\n",timeSpent);

        double wordsPerSecond = (double)wordCountAll / timeSpent;
        //printf("%d.\n",wordCountAll);
        printf("--> %.1f words per second. (%d counted words)\n",wordsPerSecond, wordCountAll);
        printf("\n");

    }else{
        printf("Cannot compare execution time due its too low!\n");
    }
}



/**
    * Asks user in which order top words will be printed
    @return Char: '-' if descending  |  '+' if ascending
*/
char AskPrintedWordOrder(){
    char input='-';

    printf("Top words in ascending order from least used to most? (y/n)");
    printf("\n> ");
    scanf("%c", &input);
    fflush(stdin);

    if(input=='y' || input=='Y')
        return '+';

    return '-';

}//...AskPrintedWordOrder()


/**
    * Asks user how many top words will be printed
    @return Integer number of printed words
*/
int AskPrintedWordCount(){
    int input=100;

    printf("How many top words will be printed?");
    printf("\n> ");
    scanf("%d", &input);
    fflush(stdin);

    if(input<0)
        return 0;

    return input;

}//...AskPrintedWordCount()



/**
    * Works as a menu
    * User can open file or exit the program
    * @return Pointer to a file if it exists and can be read or NULL
*/
FILE* AskFilePath(){
    // VARIABLES
    FILE* fptr;
    char path[1024];

    while(1){
        printf("Filename:\n> ");
        scanf("%s", path);
        fflush(stdin);

        fptr = fopen(path, "r");

        if(fptr==NULL){
            printf("-->ERROR! Couldn't open the file!\n");
            printf("- - - - - - - - -\n");
        }
        else{
            printf("Opening file: \"%s\"\n",path);
            return fptr;
        }
    }

    return NULL;

}//...AskFilePath()


/**
    * Counts words from the file with the help of hashtable
    * @param Pointer to a file
*/
void CountWords(FILE* fptr){
    char tempword[2][500];

    printf("- - - - - - - - -\n");
    printf("Begin counting words from file...");

    while ( fscanf(fptr, "%499s", tempword[0]) != EOF ){
        tempword[1][0]='\0';
        sscanf(tempword[0], "%499[a-zA-Z']", tempword[1]);


        if(tempword[1][0]!='\0'){
            // turn all letters to lowercase before insertion
            for(int i = 0; tempword[1][i]; i++){
                tempword[1][i] = toupper(tempword[1][i]);
            }

            Ht_insert(tempword[1]);
        }
    }

    printf("DONE\n");
}//...CountWords()




