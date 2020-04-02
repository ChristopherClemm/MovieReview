/* Collaborated with:
 * Mayur Ryali
 * GITHUB: (figured out how to iterate through the hash table with an iterator
 * also refreshed my memory on how to initialize an array of lists)
 * ZYBOOKS: (hash functions)
 */
#include "HashTable.h"
#include "WordEntry.h"

/* HashTable constructor
*  input s is the size of the array
*  set s to be size
*  initialize array of lists of WordEntry
*/
HashTable::HashTable (int s) {
    size = s;
    hashTable = new list<WordEntry>[size];
}

/* computeHash
*  return an integer based on the input string
*  used for index into the array in hash table
*  be sure to use the size of the array to
*  ensure array index doesn't go out of bounds
*/
int HashTable::computeHash(const string &s) {
    int sum = 0;
    for (unsigned i = 0; i < s.size(); ++i) {
        sum += (int)s.at(i);
    }
    // hash function
    return ((sum * 2) + (size - 39)) % size;
}


/* put
*  input: string word and int score to be inserted
*  First, look to see if word already exists in hash table
*   if so, addNewAppearence with the score to the WordEntry
*   if not, create a new Entry and push it on the list at the
*   appropriate array index
*/
void HashTable::put(const string &s, int score) {
    int index = computeHash(s);

    list<WordEntry>::iterator increase;

    for (increase = hashTable[index].begin(); increase != hashTable[index].end(); ++increase) {
        if (increase->getWord() == s) {
            // creates a new appearance if the word exists already
            increase->addNewAppearance(score);
            return;
        }
    }
    // creates a new entry
    WordEntry newWord(s, score);

    hashTable[index].push_back(newWord);
}

/* getAverage
*  input: string word
*  output: the result of a call to getAverage()
*          from the WordEntry
*  Must first find the WordEntry in the hash table
*  then return the average
*  If not found, return the value 2.0 (neutral result)
*/

double HashTable::getAverage(const string &s) {
    int index = computeHash(s);

    list<WordEntry>::iterator increase;

    for (increase = hashTable[index].begin(); increase != hashTable[index].end(); ++increase) {
        if (increase->getWord() == s) {
            // gets the average of the current word once the word has been found
            return increase->getAverage();
        }
    }
    return 2.0;
}

/* contains
* input: string word
* output: true if word is in the hash table
*         false if word is not in the hash table
*/
bool HashTable::contains(const string &s) {
    int index = computeHash(s);

    list<WordEntry>::iterator increase;

    for (increase = hashTable[index].begin(); increase != hashTable[index].end(); ++increase) {
        // checks to see if the word exists withing the hash table
        if (increase->getWord() == s) {
            return true;
        }
    }
    return false;
}
