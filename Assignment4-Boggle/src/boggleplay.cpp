// This is a .cpp file you will edit and turn in.
// We have provided a skeleton for you,
// but you must finish it as described in the spec.
// Also remove these comments here and add your own.
// TODO: remove this comment header

#include "lexicon.h"
#include "simpio.h"
#include "Boggle.h"

void playOneGame(Lexicon& dictionary) {

    BoggleGUI::initialize(4,4);

    Set<string> words;
    Boggle boggle(dictionary);

    while(true){
         string input = getLine();

         if(input =="") break;

         if(input.size()< 4){

             BoggleGUI::setStatusMessage("The word " + input + " is to short. Words must be at least 4 charackers long.");
             continue;
         }

         if(!dictionary.contains(toLowerCase(input))){
            BoggleGUI::setStatusMessage(input+ " is not a valid word.");

             continue;
         }

         if(words.contains(input)){
             BoggleGUI::setStatusMessage("You allready entered " + input);
             continue;
         }


         Vector<Cell> pos;

         if( boggle.humanWordSearch(toUpperCase(input)) ){
             BoggleGUI::recordWord(toLowerCase(input), BoggleGUI::HUMAN);
             BoggleGUI::setScore(boggle.getScoreHuman(),BoggleGUI::HUMAN );
             words.add(toLowerCase(input));
         }
         else{
             BoggleGUI::setStatusMessage(input + " is not in the current board.");
         }
    }

   boggle.computerWordSearch(words);

   if(boggle.getScoreComputer() > boggle.getScoreHuman())
       BoggleGUI::setStatusMessage("I beat you! HAHAHAHA silly human!");
   else
       BoggleGUI::setStatusMessage("Oh mighty human! You beat me!");


}
