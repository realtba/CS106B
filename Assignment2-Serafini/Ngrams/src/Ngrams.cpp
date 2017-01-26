/*
 * This program uses a k-order Markov model to create random texts from a given text.
 *
 * This exercise was part of Assignment 2 of the Stanford course CS106B from 2013. For more information visits
 * https://web.stanford.edu/class/archive/cs/cs106b/cs106b.1136/ or https://github.com/realtba/CS106B
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
void createData(int length, ifstream &file,  Map<string,int > &frequencies, Map< Vector<string> , Vector<string> > &prefixesToSuffixes);

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
    int order, words;

    cout << "This program creates a random text using an order k Markov model for an existing text" << endl;

    while(true){

        cout << "Please enter the filename of the text. Press -1 to exit" << endl;

        cin >> filename;

        if(filename == "-1") return 0;

        // Open the file
        ifstream infile;
        infile.open(filename);
        if (infile.fail()){ cout << "Could open the file " << filename << endl; continue;}

        cout << "Please enter the order of the Markov model:" << endl;
        cin >> order;
        cout << "Please enter the number of random words to create" << endl;
        cin >> words;

        // frequencies maps strings of length order to their frequencies in infile i.e frequencies["aaa"] denotes the number of "aaa" in infile
        Map<string,int > frequencies;

        // followingChars maps strings to a vectors of the characters following the string
        // i.e followingChars["aaa"] is a vector containing all characters following the string "aaa" in infile
        Map< Vector<string> , Vector<string> >  prefixesToSuffixes;
        // create the frequencies map and followingChars map with respect to strings in infile of length order
        createData(order,infile,frequencies, prefixesToSuffixes );



        // close the file
        infile.close();

        string output;

       createRandomText(output, prefixesToSuffixes, words);

       cout << "The random " << order << " Markov model text for the original text: " << filename << endl;
       cout << output << endl << endl;

    }



    return 0;
}

void createData(int order, ifstream &file,  Map<string,int > &frequencies, Map< Vector<string> , Vector<string> > &prefixesToSuffixes){



    string text;
    string line;
    Vector<string> window;
    while(getline(file, line)){
        text += line +"\n";
    }

    TokenScanner scanner(text);

    while(scanner.hasMoreTokens()){
        if(window.size() < order-1){
            string next = scanner.nextToken();
            if(next ==" ") {
                continue;
            }

            window.add(scanner.nextToken());
            continue;
        }

        string suffix=scanner.nextToken();
        if(suffix == " "){
            continue;
        }
        if(!prefixesToSuffixes.containsKey(window)){
            Vector<string> vec;
            vec.add(suffix);
            prefixesToSuffixes.add(window, vec);

        }
        else{
            prefixesToSuffixes.get(window).add(suffix);
        }

        window= window.subList(1, window.size()-1);
        window.add(suffix);
    }


}

void createRandomText(string &text, Map< Vector<string> , Vector<string> > &prefixesToSuffixes, int words){
    int start = randomInteger(0, prefixesToSuffixes.size()-1);
    int i=0;
    Vector<string> window;

    for(Vector<string> key : prefixesToSuffixes){
        if(start==i){
             window = key; break;
        }
        i++;
    }

    for(string prefix : window){
        text += prefix;
        if(prefix != "\n"){
            text += " ";
        }

    }
    for(int i=0; i < words; i++){
        cout << window << endl;
        Vector<string>suffixes = prefixesToSuffixes.get(window);
        cout << suffixes << endl;
        string suffix = suffixes[randomInteger(0,suffixes.size()-1)];
        cout << suffix << endl;
        text+=suffix;

        if(suffix != "\n"){
            text += " ";
        }

        window = window.subList(1, window.size()-1);
        window.add(suffix);
    }

}
