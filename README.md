# CS106B
This repository contains my solutions to the assignments of the fall quarters 2016 version of the Stanford university course CS106B: Programming Abstractions. 

For more information about CS106B visit: http://web.stanford.edu/class/archive/cs/cs106b/cs106b.1172/

Content:

Assignment 2: Serafini

Part A - Word Ladder:  A world ladder is a series of words from one word to another where consecutive words differ by only one letter e.g code → cade → cate → date → data. The code uses the breadth first algorithm to find a world ladder for a given start and end word.
Part B - Random Writer: The code uses Ngrams to to randomly generate texts from existing texts. By only randomly choosing words which follow the last N-1 generated words in the original text the randomly generated text has the same style as the original text.
 
Assignment 3: MetaAcademy

This assignment consists of 5 different problems which can be solved by recursion:  Calculating greatest common denominator, drawing Serpinskii fractals, a flood fill tool for a drawing program, creating personalized curriculum and generating random questions from a given grammar.

Assignment 4: Boggle

Uses recursion to play a game of boggle. The code uses recursion to check a table of letters if a certain words can be formed on the table. See https://en.wikipedia.org/wiki/Boggle for more information. 

Assignment 5: Priority queue

Three implementation of a priority queue: array based, linked lists and a binary heap.

Assignment 6: Huffman encoding

An implementation of Huffman encoding.

Assignment 7: Trailblazer

Breadth first, Dijkstras and A* algorithm to search for a on fastest route on a graph.

Note: The code in this repository needs the Stanford c++ library. To compile an assignment use qtcreator from www.qt.io/ and download an empty project from http://web.stanford.edu/class/archive/cs/cs106b/cs106b.1172//assnFiles/Blank.zip. 
Extract the zip file, delete the file source.cpp in the src folder and copy the src and res folder to your new folder. Then open the project file Blank.pro with qtcreator. 

See http://stanford.edu/~stepp/cppdoc/ for more information about the Stanford c++  library.

