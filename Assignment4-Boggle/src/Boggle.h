// This is a .h file you will edit and turn in.
// We have provided a skeleton for you,
// but you must finish it as described in the spec.
// Also remove these comments here and add your own.
// TODO: remove this comment header

#ifndef _boggle_h
#define _boggle_h

#include <iostream>
#include <string>
#include "bogglegui.h"
#include "lexicon.h"
#include "grid.h"
#include "cell.h"
#include "cube.h"

using namespace std;

class Boggle {
public:
    Boggle(Lexicon& dictionary, string boardText = "");
    bool humanWordSearch(string word);
    void computerWordSearch( Set<string> &usedWords);
    int getScoreHuman();
    int getScoreComputer();
    friend ostream& operator<<(ostream& out, Boggle& boggle);

private:
    int humanScore;
    int computerScore;
    Lexicon& dictionary;
    Grid< Cube > cubes;
    char getLetter(Cell cell);
    bool checkPath(Cell cell, string &word, Vector<Cell> &positions);
    void highlightPositions(Vector<Cell> &pos);
    bool IsValidDirection(Cell cell, DIRECTIONS dir);
    bool hasUncheckedNeighbor(Cell cell);\
    void Uncheck();
    void findPath(string word, Vector<Cell> pos, Cell cell, Map<string, Vector<Cell> > &foundWords, Set<string> &usedWords, Lexicon &lexicon);
    void shuffleCubes();
};

#endif // _boggle_h
