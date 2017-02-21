/*
 * This program uses Ngrams to create random texts from a given text.
 *
 * This exercise was part of Assignment 2 of the Stanford course CS106B from 2016. For more information visits
 * http://web.stanford.edu/class/archive/cs/cs106b/cs106b.1172 or https://github.com/realtba/CS106B
 * The Assignment can be found here http://web.stanford.edu/class/archive/cs/cs106b/cs106b.1172/assn/serafini.html
 *
 * created by B. Jost
 *
 */

#include <iostream>
#include <fstream>
#include<cctype>
#include "console.h"
#include "vector.h"
#include "set.h"
#include "foreach.h"
#include "queue.h"

using namespace std;


/*  WordLadder
 *  Returns a word ladder from start to end using words from lexicon or "No ladder found" if there is no word ladder
 */
Vector<string> WordLadder(string start, string end,const Set<string> &lexicon);


/* IsOneCharAway
 * Returns true if word1 and word2 differ only by one character and false otherwise 
 */
bool IsOneCharAway(string word1, string word2);

/* WordsOneCharAway
 * Return the set of all words from lexicon which are only character away from input 
 */
Set<string> WordsOneCharAway(string input, const Set<string> &lexicon);

/* WordsWithLength
 * Returns the set of all words with length equal to length from lexicon
 */
Set<string> WordsWithLength(int length, const Set <string> & lexicon);


int main() {

    cout << endl << "Finds words with the same length that differ by one character. Does not distinguish between lower and uppercase" << endl << "Type -1 to stop!" << endl;
    // open dictionary.txt
    Set<string> lexicon;
    ifstream infile;
    infile.open("dictionary.txt");
    if (infile.fail()) error("Can't open dictionary.txt");

    // read words.txt line for line
    string word;
    while (getline(infile, word)) {
        lexicon.add(word);
    }

    infile.close();

    string start;
    string end;


    while(true){
        cout << "Please enter the start of the ladder!" << endl;
        cin >> start;
        if(start == "-1") break;
        else if(!lexicon.contains(start)){
            cout << start << "is not part of our dictionary." << endl;
            continue;
        }
        cout << "Please enter the end of the ladder!" << endl;
        cin >> end;
        if(end == "-1") break;
        else if(!lexicon.contains(start)){
            cout << end << "is not part of our dictionary." << endl;
            continue;
        }
        else if(start.length() != end.length()){
            cout << "The lendth of" + start + " and " + end + " does not match" << endl;
            continue;
        }
        cout <<  WordLadder(start, end, WordsWithLength(start.length(), lexicon)) << endl;


    }
    return 0;
}

Vector<string> WordLadder(string start, string end, const Set<string> &lexicon){


    Set<string> usedWords;
    // add the start to the used words
    usedWords.add(start);

    Queue< Vector<string> > wordLadders;
    Vector<string> startLadder;

    // add the start of the Ladder
    startLadder.add(start);
    wordLadders.add(startLadder);

    // repeat as long as the queue is not empty
    while(!wordLadders.isEmpty()){

        // dequeue the first ladder in the queue
        Vector<string> firstLadder= wordLadders.dequeue();

        // if the last word of firstLadder is the wanted end we are done. return the ladder.
        if (firstLadder[firstLadder.size()-1] == end) return firstLadder;

        // create the set of all words in the lexicon a char away form the last word in the ladder firstLadder
        Set<string> wordsCharAway(WordsOneCharAway(firstLadder[firstLadder.size()-1], lexicon));

        // Check for each word in wordsCharAway if we have not already used the word in order to prevent infinite loops
        // If so, create a copy firstLadder, add the word and add the new ladder to the queue
        foreach(string word in wordsCharAway)
            if(!usedWords.contains(word)){
                Vector<string> newCopy(firstLadder);
                newCopy.add(word);
                wordLadders.add(newCopy);
            }
    }

    // The queue is empty but we have not found a ladder
    Vector<string> result;
    result.add(string("No ladder found"));
    return result;
}

Set<string> WordsWithLength(int length, const Set <string> & lexicon){
    Set<string> words;
    // loop trough all words in lexicon
    foreach (string word in lexicon) {
        // add the words with the given length to the set
        if(word.length()==length) words.add(word);
    }
    return words;
}

Set<string> WordsOneCharAway(string input, const Set<string> &lexicon){
    Set<string> allWordsCharAway;
    // loop trough all words in the lexicon
    foreach(string word in lexicon){
        //check if they are one character away from the input. If so add them to the set
        if(IsOneCharAway(word, input)) allWordsCharAway.add(word);
    }

    return allWordsCharAway;
}

bool IsOneCharAway(string word1, string word2){
    int difference = 0;
    // loop trough all characters of word1
    for(int i = 0; i< word1.length() ; i++ ){
        // check if the current position in the string do not coincide, if so increase the difference
        if( tolower((word1[i])) !=  tolower(word2[i])) difference++;
        // if the difference is greater then 1 the words are more then one character away form each other
        if(difference > 1 ) return false;
    }
    // if the difference is 1 the words are one character away from each other
    if(difference == 1) return true;

    return true;
}
