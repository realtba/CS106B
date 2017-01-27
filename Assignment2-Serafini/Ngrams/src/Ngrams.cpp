/*
 * This program uses Ngrams to create random texts from a given text.
 *
 * This exercise was part of Assignment 2 of the Stanford course CS106B from 2016. For more information visits
 * http://web.stanford.edu/class/archive/cs/cs106b/cs106b.1172 or https://github.com/realtba/CS106B
 *
 * created by B. Jost
 *
 */

#include <iostream>
#include <fstream>
#include <string>
#include "vector.h"
#include "map.h"
#include "console.h"
#include "gwindow.h" // for GWindow
#include "simpio.h"  // for getLine
#include "vector.h"  // for Vector
#include "foreach.h"
#include "random.h"
#include "tokenscanner.h"

using namespace std;

/*
 * createData
 * Fills the maps frequencies and followingChars according to length and file
 */
void createData(int length, ifstream &file, Map< Vector<string> , Vector<string> > &prefixesToSuffixes);

/*
 * createRandomText
 * Fills the string text with a random text according to the maps frequencies and followingChars
 */
void createRandomText(string &text, Map< Vector<string> , Vector<string> > &prefixesToSuffixes, int words);

/*
 * highestFrequency
 * returns the string with highest Frequency among all frequencies
 */
string highestFrequency(Map<string,int > &frequencies);


int main() {


    string filename;
    ifstream infile;
    int order, words;

    cout << "This program creates a random text using Ngrams for an existing text" << endl;

    while(true){

        while(true){
            cout << "Please enter the filename of the text. Press -1 to exit" << endl;

            cin >> filename;

            if(filename == "-1") {
                cout << "Have a nice day!" << endl;
                return 0;
            }
            // Open the file
            infile.open(filename);
            if(infile.fail()){
                cout << "Could open the file " << filename << endl;
                cout << "Please try again!" << endl;
            }
            else{
                break;
            }
        }
        while(true){
            cout << "Please enter the order N of the Ngrams." << endl;
            cin >> order;
            if (order <2){
                cout << "The order n needs to be at least 2." << endl;
                continue;
            }

            cout << "Please enter the number of random words to create." << endl;
            cin >> words;

            if(order >= words){
                cout << "The number of words needs to be larger then N." << endl;
                continue;
            }
            break;
         }

        Map< Vector<string> , Vector<string> >  prefixesToSuffixes;
        createData(order,infile, prefixesToSuffixes );
        // close the file
        infile.close();

        string output;
        createRandomText(output, prefixesToSuffixes, words);

        cout << "The random " << order << "gram text for the original text: " << filename << "is:" << endl;
        cout << output << endl << endl;

    }

    return 0;
}

void createData(int order, ifstream &file, Map< Vector<string> , Vector<string> > &prefixesToSuffixes){

    string word;
    Vector<string> window;

    while(file >> word ){
        if(window.size() < order-1){

            window.add(word);
            continue;
        }

        if(!prefixesToSuffixes.containsKey(window)){
            Vector<string> vec;
            vec.add(word);
            prefixesToSuffixes.add(window, vec);

        }
        else{
            Vector<string> vec = prefixesToSuffixes.get(window);
            vec.add(word);
            prefixesToSuffixes.put(window, vec);
        }

        window= window.subList(1, window.size()-1);
        window.add(word);
    }
    file.clear();

    for(int i=0; i < order; i++){
        file >> word;
        if(!prefixesToSuffixes.containsKey(window)){
            Vector<string> vec;
            vec.add(word);
            prefixesToSuffixes.add(window, vec);

        }
        else{
            Vector<string> vec = prefixesToSuffixes.get(window);
            vec.add(word);
            prefixesToSuffixes.put(window, vec);
        }

        window= window.subList(1, window.size()-1);
        window.add(word);
    }
}

void createRandomText(string &text, Map< Vector<string> , Vector<string> > &prefixesToSuffixes, int words){

    Vector< Vector<string>  > keys = prefixesToSuffixes.keys();
    int start = randomInteger(0, keys.size()-1);
    Vector<string> window = keys[start];
    text="...";
    for(string prefix : window){
        text += prefix+" ";
    }

    for(int i=0; i < words; i++){

        Vector<string>suffixes = prefixesToSuffixes.get(window);
        int random = randomInteger(0,suffixes.size()-1);
        string suffix = suffixes[random];

        text+=suffix+" ";

        window = window.subList(1, window.size()-1);
        window.add(suffix);
    }

    text +="...";
}
