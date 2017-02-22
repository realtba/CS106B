// This is a .cpp file you will edit and turn in.
// We have provided a skeleton for you,
// but you must finish it as described in the spec.
// Also remove these comments here and add your own.
// TODO: remove this comment header

#include "Boggle.h"

// letters on all 6 sides of every cube
static string CUBES[16] = {
    "AAEEGN", "ABBJOO", "ACHOPS", "AFFKPS",
    "AOOTTW", "CIMOTU", "DEILRX", "DELRVY",
    "DISTTY", "EEGHNW", "EEINSU", "EHRTVW",
    "EIOSST", "ELRTTY", "HIMNQU", "HLNNRZ"
};

// letters on every cube in 5x5 "Big Boggle" version (extension)
static string BIG_BOGGLE_CUBES[25] = {
   "AAAFRS", "AAEEEE", "AAFIRS", "ADENNN", "AEEEEM",
   "AEEGMU", "AEGMNN", "AFIRSY", "BJKQXZ", "CCNSTW",
   "CEIILT", "CEILPT", "CEIPST", "DDLNOR", "DDHNOT",
   "DHHLOR", "DHLNOR", "EIIITT", "EMOTTT", "ENSSSU",
   "FIPRSY", "GORRVW", "HIPRRY", "NOOTUW", "OOOTTU"
};


Boggle::Boggle(Lexicon& dict, string boardText)
    : dictionary(dict) , cubes(4,4), humanScore(0), computerScore(0)
{
    if(boardText.size() == 0){

        for(int row =0; row<cubes.height();row++){
            for(int col=0; col<cubes.height(); col++){
                this->cubes[row][col] = CUBES[4*row+col];
            }
        }

        this->shuffleCubes();
    }

    for(int row =0; row<cubes.height();row++){
        for(int col=0; col<cubes.height(); col++){
           BoggleGUI::labelCube(row, col, cubes.get(row,col).getLetterUp(),false);
        }
    }


}

void Boggle::shuffleCubes(){

    Vector<Cube> shuffle;

    for(Cube cube : this->cubes){
        shuffle.add(cube);
    }

    int length = shuffle.size();

    for(int i = 0; i < length;i++){
        // shuffle the postion of the 16 cubes
        int r = randomInteger(i,length-1);
        Cube switchCube =shuffle[i];
        shuffle[i] = shuffle[r];
        shuffle[r] = switchCube;
        shuffle[i].rollCube();
    }

    int height = this->cubes.height();

    for(int i=0; i< length; i++){
        this->cubes[i%height][(i-i%height)/height] = shuffle[i];
    }
}

char Boggle::getLetter(Cell cell){
    return this->cubes[cell.row][cell.col].getLetterUp();
}

bool Boggle::checkPath(Cell cell, string &word, Vector<Cell> &positions){


    char c = this->getLetter(cell);
    // if the current letter is at the correct postion within word and there are unchecked neighbours we continue the search
    if(word[positions.size()] == c && this->hasUncheckedNeighbor(cell)){

        // add the current point to the solution
        positions.add(cell);

        if(word.size()==positions.size())  return true;

        // check the current cube
        this->cubes[cell.row][cell.col].setChecked(true);

        for(DIRECTIONS dir= NORTH; dir <= NORTHEAST; dir++){
            if(this->IsValidDirection(cell, dir)){
                Cell neighbour =cell.GetNeighbour(dir);
                // If this point is checked we move with the next direction
                if(this->cubes[neighbour.row][neighbour.col].getChecked()){
                    continue;
                }
                //One Step in direction dir
                if(this->checkPath(neighbour, word, positions)){
                    // uncheck the current cube
                    this->cubes[cell.row][cell.col].setChecked(false);
                    return true;
                }
            }

        }
        // uncheck the current cube
        this->cubes[cell.row][cell.col].setChecked(false);
        // remove the current cube
        positions.remove(positions.size()-1);

    }
    return false;
}


void Boggle::highlightPositions(Vector<Cell> &pos){

    BoggleGUI::setAnimationDelay(400);


    for(int i=0; i< pos.size();i++)
    {
        BoggleGUI::setHighlighted(pos[i].row, pos[i].col, true);
    }

    pause(800);

    for(int i=0; i< pos.size();i++)
    {
        BoggleGUI::setHighlighted(pos[i].row, pos[i].col, false);

    }


}

bool Boggle::humanWordSearch(string word) {

    Vector<Cell> positions;

    for(int i=0; i<4; i++){
        for(int j=0; j<4; j++){
            if(checkPath(Cell(i,j),word, positions)){
                BoggleGUI::setStatusMessage( "You found the word" + word);
                this->highlightPositions(positions);
                this->humanScore+= word.length();
                return true;
            }
        }
    }

    return false;
}

bool Boggle::IsValidDirection(Cell cell, DIRECTIONS dir){

   Cell neighbour = cell.GetNeighbour(dir);

   if(neighbour.row < 0 || neighbour.row >3 || neighbour.col>3 || neighbour.col <0 )
       return false;

   return true;
}

bool Boggle::hasUncheckedNeighbor(Cell cell) {

    for(DIRECTIONS dir= NORTH; dir <= NORTHEAST; dir++){
        if(this->IsValidDirection(cell, dir) && !this->cubes[cell.row][cell.col].getChecked())
            return true;
    }

    return false;
}

void Boggle::Uncheck(){
    for(int i=0; i<cubes.height(); i++){
        for(int j=0; j<cubes.height(); j++){
           this->cubes[i][j].setChecked(false);
        }
    }

}


int Boggle::getScoreHuman() {
    return this->humanScore;
}

void Boggle::computerWordSearch( Set<string> &usedWords) {

    Map< string, Vector< Cell> > foundWords;
    for(int i = 0; i <4; i++){
        for( int j = 0; j<4; j++){
            Vector< Cell> pos;
            this-> findPath("", pos, Cell(i,j), foundWords, usedWords, dictionary);
        }
    }

    for(string key : foundWords){
        BoggleGUI::setStatusMessage("The computer found the word " + toLowerCase(key));
        BoggleGUI::recordWord(key, BoggleGUI::COMPUTER);
        computerScore += key.size();
        BoggleGUI::setScore(computerScore, BoggleGUI::COMPUTER);
        Vector<Cell> pos = foundWords.get(key);
        this->highlightPositions(pos);
    }
}




void Boggle::findPath(string word, Vector<Cell> pos, Cell cell, Map<string, Vector<Cell> > &foundWords, Set<string> &usedWords, Lexicon &lexicon){

    if(!lexicon.containsPrefix(word)) return;

    this->cubes[cell.row][cell.col].setChecked(true);
    pos.add(cell);

    if( (lexicon.contains(word+cubes[cell.row][cell.col].getLetterUp()))
        && (!usedWords.contains(toLowerCase(word+cubes[cell.row][cell.col].getLetterUp())))
        && (word.size() > 2)){
        foundWords.add(word+cubes[cell.row][cell.col].getLetterUp(), pos);
    }

    for(DIRECTIONS dir= NORTH; dir <= NORTHEAST; dir++){
        if(this->IsValidDirection(cell, dir)){
            Cell neighbour = cell.GetNeighbour(dir);
            // If this point is checked we move with the next direction
            if(this->cubes[neighbour.row][neighbour.col].getChecked()){
                continue;
            }

            this->findPath(word+this->cubes[cell.row][cell.col].getLetterUp(), pos, neighbour, foundWords,usedWords,lexicon);

        }
    }
    this->cubes[cell.row][cell.col].setChecked(false);

}

int Boggle::getScoreComputer() {
    return this->computerScore;
}

ostream& operator<<(ostream& out, Boggle& boggle) {
    // TODO: implement
    return out;
}
