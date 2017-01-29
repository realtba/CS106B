// This is the CPP file you will edit and turn in.
// Also remove these comments here and add your own, along with
// comments on every function and on complex code sections.
// TODO: remove this comment header

#include "encoding.h"
#include "pqueue.h"
#include "foreach.h"


void getCodeFromTree(string code, HuffmanNode* current, Map<int, string> &encodingMap);


Map<int, int> buildFrequencyTable(istream& input) {

    Map<int, int> freqTable;

    char ch;

    while(input.get(ch)){
      if(!freqTable.containsKey((int)ch))
          freqTable.add((int)ch,1);
      else
          freqTable.add((int)ch,freqTable.get((int)ch)+1);
    }
    // add EOF
    freqTable.add(256,1);

    return freqTable;
}

HuffmanNode* buildEncodingTree(const Map<int, int>& freqTable) {

    PriorityQueue<HuffmanNode*> pqueue;

    // Build the inital  PriorityQueue
    foreach(int key in freqTable){

        int value = freqTable.get(key);

        HuffmanNode* newNode = new HuffmanNode(key,value);

        pqueue.add(newNode,value);
    }

    while(pqueue.size() > 1){
        HuffmanNode *left = pqueue.dequeue();
        HuffmanNode *right= pqueue.dequeue();

        HuffmanNode *newNode = new HuffmanNode(NOT_A_CHAR,right->count+left->count, left, right);
        pqueue.add(newNode,newNode->count);
    }

    HuffmanNode *root = pqueue.dequeue();
    return root;  
}

Map<int, string> buildEncodingMap(HuffmanNode* encodingTree) {

    Map<int, string> encodingMap;   

    getCodeFromTree("", encodingTree,encodingMap);

    return encodingMap;      
}

void getCodeFromTree(string code, HuffmanNode* current, Map<int, string> &encodingMap){

    // if the current node is a leaf add the data to the map
    if(current->isLeaf()){
        encodingMap.add(current->character, code);
    }

    else{
        // move along the left branch
        getCodeFromTree(code+"0",current->zero, encodingMap );
        // move along right branch
        getCodeFromTree(code+"1",current->one, encodingMap );

    }
}

void encodeData(istream& input, const Map<int, string>& encodingMap, obitstream& output) {



    char ch;

    while(input.get(ch)){
        string code = encodingMap.get((int)ch);
        for(int i=0; i < code.length(); i++){
             output.writeBit(code[i] == '1' ? 1 : 0);
        }
    }
    /*
    string code = encodingMap.get(256);
    cout << code << endl;
    for(int i=0; i < code.length(); i++){
         output.writeBit(code[i] == '1' ? 1 : 0);
    }
    */
}

void decodeData(ibitstream& input, HuffmanNode* encodingTree, ostream& output) {

    int bit= input.readBit();

    HuffmanNode* currentNode = encodingTree;

    while( bit  != -1){

        if(currentNode->isLeaf()){
            output.put((char)currentNode->character);
            currentNode = encodingTree;
        }

        if(bit == 0){
            currentNode = currentNode->zero;
        }

        else if(bit == 1){
            currentNode = currentNode->one;
        }

        bit= input.readBit();

    }

}

void compress(istream& input, obitstream& output) {

    Map<int, int> freqTable = buildFrequencyTable(input);

    HuffmanNode* root = buildEncodingTree(freqTable);

    Map<int, string> encodeMap = buildEncodingMap(root);


    if (!freqTable.containsKey(256)) {
        error("No PSEUDO_EOF defined.");
    }

    output << freqTable.size() - 1 << ' ';

    for (int ch : freqTable) {
        if (ch == 256) continue;
        output << char(ch) << freqTable[ch] << ' ';
    }

    input.clear();
    input.seekg(0, ios::beg);

    encodeData(input, encodeMap, output);
}

void decompress(ibitstream& input, ostream& output) {

    Map<int, int> freqTable;

    int length;
    input >> length;

    input.get();

    for (int i = 0; i < length; i++) {
        int ch = input.get();

        int frequency;
        input >> frequency;

        input.get();

        freqTable[ch] = frequency;
    }

    freqTable[256] = 1;

    HuffmanNode* root = buildEncodingTree(freqTable);
    decodeData(input, root, output);

}

void freeTree(HuffmanNode* node) {

    if(node->isLeaf()){
        delete node;
        return;
    }
    freeTree(node->one);
    freeTree(node->zero);
    delete node;
}
