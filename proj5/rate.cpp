//
//  rate.cpp
//  rate
//
//  Created by Haley Kim on 11/8/18.
//  Copyright © 2018 CS31. All rights reserved.
//

#include <iostream>
#include <cstring>
#include <cctype>
#include <cassert>
using namespace std;

const int MAX_WORD_LENGTH = 20;
const int MAX_DOC_LENGTH = 250;

int makeProper(char word1[][MAX_WORD_LENGTH+1], char word2[][MAX_WORD_LENGTH+1], int separation[], int nPatterns)
{
    // CHECKING IF ALL SEPARATIONS ARE POSITIVE
    // if nPatterns is negative, treat it as zero
    if (nPatterns < 0)
        nPatterns = 0;
    // looping through every integer of array
    for (int k = 0; k < nPatterns; k++)
    {
        // if the integer is negative, move everything after it up one space, overriding the negative integer
        if ((separation[k] < 0) && (k != nPatterns-1))
        {
            for (int i = k+1; i < nPatterns; i++)
            {
                separation[i-1] = separation[i];
                // looping through every column of word arrays
                for (int j = 0; j < MAX_WORD_LENGTH; j++)
                {
                    // move letter beneath letter of negative separation row to its position, override
                    word1[i-1][j] = word1[i][j];
                    word2[i-1][j] = word2[i][j];
                }
            }
            k--;
            nPatterns--;
        }
        // if it is the last element of the array that is negative, leave it be and add one to counter
        else if ((separation[k] < 0) && (k == nPatterns-1))
            nPatterns--;
    }
    // CHECKING WHETHER ALL STRINGS ONLY CONSIST OF LETTERS
    // looping through every word of word1 array
    for (int k = 0; k < nPatterns; k++)
    {
        // looping through every character
        for (int t = 0; t < strlen(word1[k]); t++)
        {
            // if a character is a not a letter
            if (!isalpha(word1[k][t]) && (k != nPatterns-1))
            {
                // move every word from row behind up one row for both word 1 and word2
                for (int i = k+1; i < nPatterns; i++)
                {
                    separation [i-1] = separation[i];
                    for (int j = 0; j < MAX_WORD_LENGTH; j++)
                    {
                        word1[i-1][j] = word1[i][j];
                        word2[i-1][j] = word2[i][j];
                    }
                    // When you move one up, because you increment k by 1, you may skip an element. To prevent this, you subtract 1 from k before k is incremented by 1
                }
                // since one faulty element has been removed from all arrays, nPatterns is decreased by 1
                k--;
                nPatterns--;
            }
            else if (!isalpha(word1[k][t]) && (k == nPatterns-1))
                nPatterns--;
        }
    }
    // same thing for word2 array
    for (int k = 0; k < nPatterns; k++)
    {
        for (int t = 0; t < strlen(word2[k]); t++)
        {
            if (!isalpha(word2[k][t]) && (k != nPatterns-1))
            {
                for (int i = k+1; i < nPatterns; i++)
                {
                    separation [i-1] = separation[i];
                    for (int j = 0; j < MAX_WORD_LENGTH; j++)
                    {
                        word1[i-1][j] = word1[i][j];
                        word2[i-1][j] = word2[i][j];
                    }
                }
                k--;
                nPatterns--;
            }
            else if (!isalpha(word2[k][t]) && (k == nPatterns-1))
                nPatterns--;
        }
    }
    // CHECKING FOR EMPTY STRINGS
    // looping through every word of word1 array
    for (int k = 0; k < nPatterns; k++)
    {
        // if any word is empty
        if ((strlen(word1[k]) == 0) && (k != nPatterns-1))
        {
            separation[k] = separation[k+1];
            // same process of overriding it with the next word
            for (int i = k+1; i < nPatterns; i++)
            {
                for (int j = 0; j < MAX_WORD_LENGTH; j++)
                {
                    word1[i-1][j] = word1[i][j];
                    word2[i-1][j] = word2[i][j];
                }
            }
            k--;
            nPatterns--;
        }
        else if ((strlen(word1[k]) == 0) && (k == nPatterns-1))
            nPatterns--;
    }
    // same process for word2 array
    for (int k = 0; k < nPatterns; k++)
    {
        if ((strlen(word2[k]) < 1) && (k != nPatterns-1))
        {
            separation[k] = separation[k+1];
            for (int i = k+1; i < nPatterns; i++)
            {
                for (int j = 0; j < MAX_WORD_LENGTH; j++)
                {
                    word1[i-1][j] = word1[i][j];
                    word2[i-1][j] = word2[i][j];
                }
            }
            k--;
            nPatterns--;
        }
        else if ((strlen(word2[k]) < 1) && (k == nPatterns-1))
            nPatterns--;
    }
    // CHECKING FOR TWO PATTERNS OF THE SAME WORDS
    // looping through every word
    for (int k = 0; k < nPatterns; k++)
    {
        //looping through every word
        for (int i = 0; i < nPatterns; i++)
        {
            // of course, a word will equal itself
            if (k == i)
                continue;
            // if two patterns are identical or consist of the same words in reverse ofder
            if (((strcmp(word1[k],word1[i]) == 0) && (strcmp(word2[k],word2[i]) == 0)) || ((strcmp(word1[k],word2[i]) == 0) && (strcmp(word2[k],word1[i]) == 0)))
            {
                // if separation of word[k] is lesser than or equal to that of word[i]
                if ((separation[k] <= separation[i]) && (k != nPatterns-1))
                {
                    // override word[k] and its equivalent position in all three arrays
                    for (int y = k+1; y < nPatterns; y++)
                    {
                        separation [y-1] = separation[y];
                        for (int j = 0; j < MAX_WORD_LENGTH; j++)
                        {
                            word1[y-1][j] = word1[y][j];
                            word2[y-1][j] = word2[y][j];
                        }
                    }
                    k--;
                    nPatterns--;
                }
                else if ((separation[k] <= separation[i]) && (k == nPatterns-1))
                    nPatterns--;
                // if separation of word[i] is lesser than that of word[k]
                if ((separation[i] < separation[k]) && (i != nPatterns-1))
                {
                    // override word[i] and its equivalent position in all three arrays
                    for (int z = i+1; z < nPatterns; z++)
                    {
                        separation [z-1] = separation[z];
                        for (int x = 0; x < MAX_WORD_LENGTH; x++)
                        {
                            word1[z-1][x] = word1[z][x];
                            word2[z-1][x] = word2[z][x];
                        }
                    }
                    k--;
                    nPatterns--;
                }
                else if ((separation[i] < separation[k]) && (i == nPatterns-1))
                    nPatterns--;
            }
        }
    }
    // now turn everything into lowercase letters!
    for (int k = 0; k < nPatterns; k++)
    {
        for (int i = 0; i < strlen(word1[k]); i++)
        {
            word1[k][i] = tolower(word1[k][i]);
            word2[k][i] = tolower(word2[k][i]);
        }
    }
    return nPatterns;
}

int rate(const char document[], const char word1[][MAX_WORD_LENGTH+1], const char word2[][MAX_WORD_LENGTH+1], const int separation[], int nPatterns)
{
    if (nPatterns <= 0)
        return 0;
    // initialize a dummy document that is max 250 characters long
    char copy[MAX_DOC_LENGTH+1] = {0};
    // put everything from document into copy, now we have an array we can alter
    for (int k = 0; k < strlen(document); k++)
    {
        copy[k] = document[k];
    }
    // override any non-letter characters and delete the last character that is duplicated
    for (int k = 0; k < strlen(copy); k++)
    {
        if ((!isalpha(copy[k])) && (copy[k] != ' '))
        {
            for (int i = k+1; i < strlen(copy); i++)
            {
                copy[i-1] = copy[i];
            }
            copy[strlen(copy)-1] = '\0';
            k--;
        }
    }
    // reducing multiple spaces to one space (just for aesthetics and to make it easier to maneuver through)
    for (int k = 0; k < strlen(copy)-1; k++)
    {
        if ((copy[k] == ' ') && (copy[k+1] == ' '))
        {
            for (int i = k+1; i < strlen(copy); i++)
            {
                copy[i] = copy[i+1];
            }
            k--;
        }
    }
    // turning everything into lowercase
    for (int k = 0; k < strlen(copy); k++)
    {
        copy[k] = tolower(copy[k]);
    }
    // now breaking up one c-string copy of document into 2d-array of words
    char sentenceToWords[MAX_DOC_LENGTH+1][MAX_DOC_LENGTH+1] = {};
    for (int i = 0, k = 0, j = 0; copy[k] != '\0';)
    {
        if (isspace(copy[k]))
        {
            k++;
            while (isspace(copy[k]))
            {
                k++;
            }
            i++;
            j = 0;
        }
        if (isalpha(copy[k]))
        {
            sentenceToWords[i][j] = copy[k];
            k++;
            j++;
            if (j < MAX_DOC_LENGTH+1)
            {
                sentenceToWords[i][j+1] = '\0';
            }
            else
            {
                sentenceToWords[i][j] = '\0';
            }
        }
        
    }
    // actually checking for the rating of the document! yay formatting is DONE
    // rating set to 0
    int rating = 0;
    // looping through every word of pattern arrays
    for (int k = 0; k != nPatterns; k++)
    {
        // reset foundPattern to 0 with every new pattern word
        int foundPattern = 0;
        // looping through every word of 2d-array
        for (int i = 0; i < MAX_DOC_LENGTH; i++)
        {
            // if element of word1 is found in 2d-array
            if (strcmp(word1[k], sentenceToWords[i]) == 0)
            {
                if (separation[k] == 0)
                {
                    if (i != 0)
                    {
                        // if element of word2 at the same position is found in 2d-array
                        if ((strcmp(word2[k], sentenceToWords[i-1]) == 0) || (strcmp(word2[k], sentenceToWords[i+1]) == 0))
                        {
                            foundPattern = 1; // used to avoid counting the same pattern twice
                            // add 1 to rating
                            rating++;
                        }
                    }
                    if (i == 0)
                    {
                        if (strcmp(word2[k], sentenceToWords[i+1]) == 0)
                        {
                            foundPattern = 1;
                            rating++;
                        }
                    }
                }
                else
                {
                    // finding element of word2 within the separation limit in 2d-array
                    for (int j = 1; j != separation[k] + 2; j++)
                    {
                        if (i-j >= 0)
                        {
                            if ((strcmp(word2[k], sentenceToWords[i-j]) == 0) && (foundPattern == 0))
                            {
                                foundPattern = 1;
                                rating++;
                            }
                        }
                        if (i+j < MAX_DOC_LENGTH+1)
                        {
                            if ((strcmp(word2[k], sentenceToWords[i+j]) == 0) && (foundPattern == 0) && (i+j < MAX_DOC_LENGTH+1))
                            {
                                foundPattern = 1;
                                rating++;
                            }
                        }
                    }
                }
            }
        }
    }
    return rating;
}

int main()
{
    const int TEST1_NRULES = 4;
    char test1w1[TEST1_NRULES][MAX_WORD_LENGTH+1] = {
        "mad",       "deranged", "nefarious", "have"
    };
    char test1w2[TEST1_NRULES][MAX_WORD_LENGTH+1] = {
        "scientist", "robot",    "plot",      "mad"
    };
    int test1dist[TEST1_NRULES] = {
        1,           3,          0,           12
    };
    assert(makeProper(test1w1,test1w2,test1dist,TEST1_NRULES) == 4);
    char test2w1[TEST1_NRULES][MAX_WORD_LENGTH+1] = {
        "mad",       "derange.d", "nefarious", "have"
    };
    char test2w2[TEST1_NRULES][MAX_WORD_LENGTH+1] = {
        "scientist", "robot",    "plot",      "mad"
    };
    int test2dist[TEST1_NRULES] = {
        1,           3,          -2,           12
    };
    assert(makeProper(test2w1,test2w2,test2dist,TEST1_NRULES) == 2);
    char test3w1[TEST1_NRULES][MAX_WORD_LENGTH+1] = {
        "mad",       "derange.d", "nefarious", "HAve"
    };
    char test3w2[TEST1_NRULES][MAX_WORD_LENGTH+1] = {
        "scientist", "robot",    "plot",      "mad"
    };
    int test3dist[TEST1_NRULES] = {
        1,           3,          -2,           12
    };
    assert((makeProper(test3w1,test3w2,test3dist,TEST1_NRULES) == 2));
    char test4w1[TEST1_NRULES][MAX_WORD_LENGTH+1] = {
        "",       "deranged", "nefarious", "HAve"
    };
    char test4w2[TEST1_NRULES][MAX_WORD_LENGTH+1] = {
        "scientist", "robot",    "plot",      "mad"
    };
    int test4dist[TEST1_NRULES] = {
        1,           3,          2,           12
    };
    assert(makeProper(test4w1,test4w2,test4dist,TEST1_NRULES) == 3);
    char test5w1[TEST1_NRULES][MAX_WORD_LENGTH+1] = {
        "mad",       "deranged", "nefarious", "HAve"
    };
    char test5w2[TEST1_NRULES][MAX_WORD_LENGTH+1] = {
        "scientist", "robot",    "plot",      ""
    };
    int test5dist[TEST1_NRULES] = {
        1,           3,          2,           12
    };
    assert(makeProper(test5w1,test5w2,test5dist,TEST1_NRULES) == 3);
    char test6w1[3][MAX_WORD_LENGTH+1] = {
        "mad",       "deranged", "nefarious"
    };
    char test6w2[3][MAX_WORD_LENGTH+1] = {
        "scientist", "robot",    "plot"
    };
    int test6dist[3] = {
        -99,           3,          0
    };
    assert(makeProper(test6w1,test6w2,test6dist,3) == 2);
    assert(rate("The mad UCLA scientist unleashed a deranged evil giant robot.",
                test1w1, test1w2, test1dist, TEST1_NRULES) == 2);
    assert(rate("The mad UCLA scientist unleashed    a deranged robot.",
                test1w1, test1w2, test1dist, TEST1_NRULES) == 2);
    assert(rate("**** 2018 ****",
                test1w1, test1w2, test1dist, TEST1_NRULES) == 0);
    assert(rate("  That plot: NEFARIOUS!",
                test1w1, test1w2, test1dist, TEST1_NRULES) == 1);
    assert(rate("deranged deranged robot deranged robot robot",
                test1w1, test1w2, test1dist, TEST1_NRULES) == 1);
    assert(rate("That scientist said two mad scientists suffer from deranged-robot fever.",
                test1w1, test1w2, test1dist, TEST1_NRULES) == 0);
    assert(rate("Stupi!!d fri,cking mad    UCLA SCIENtiST scrEwed u::p    eVerything.",
                test1w1, test1w2, test1dist, TEST1_NRULES) == 1);
    assert(rate("mad scientist scientist mad mad scientist mad",
                test1w1, test1w2, test1dist, TEST1_NRULES) == 1);
    const int TEST7_NRULES = -1;
    char test7w1[3][MAX_WORD_LENGTH+1] = {};
    char test7w2[3][MAX_WORD_LENGTH+1] = {};
    int test7dist[3] = {};
    assert(rate("The mad UCLA scientist unleashed a deranged evil giant robot.",
                test7w1, test7w2, test7dist, TEST7_NRULES) == 0);
    char test8w1[TEST1_NRULES][MAX_WORD_LENGTH+1] = {
        "mad",       "deranged", "nefarious", "HAve"
    };
    char test8w2[TEST1_NRULES][MAX_WORD_LENGTH+1] = {
        "scientist", "robot",    "plot",      "mad"
    };
    int test8dist[TEST1_NRULES] = {
        1,           3,          2,           12
    };
    assert(rate("The mad UCLA scientist unleashed a asdlkfjashdfkasjdfhaoshdfkjasdhfkjsahdfklhslkhakldshflkashflkdshfkl deranged evil giant robot.",
                test8w1, test8w2, test8dist, TEST1_NRULES) == 2);
    cerr << "All tests succeeded" << endl;
}
