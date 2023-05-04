#include "Dictionary.h"

// Your code here


Dictionary::Dictionary() {
    root = new Node();
    numWords = 0;

}

Dictionary::~Dictionary() {
    destroyHelper(root);
}
void Dictionary::MakeEmpty() {
    destroyHelper(root);
    root = new Node();
    numWords = 0;
}

void Dictionary::destroyHelper(Dictionary::Node *thisTree) {
    if(thisTree== nullptr) // if emtpy, do nothing.
        return;
    for(int i= 0; i< NUM_CHARS; i++){
        destroyHelper(thisTree->ptr[i]); // deletes all the pointers in the array
    }
    delete thisTree; // deletes the node
}


Dictionary::Dictionary(string filename) {
    root = new Node();
    numWords = 0;
    LoadDictionaryFile(filename);
}



Dictionary &Dictionary::operator=(const Dictionary &otherDict) {
    MakeEmpty(); // destroys this tree before copying. Not sure if I should call makeEmpty here.
    //Avoids self reference issue.
    if(this!=&otherDict){
        copyOther(otherDict);
    }
    return *this;
}


void Dictionary::copyOther(const Dictionary &otherDict) { // code from the binaryDictionaryTree Example
    MakeEmpty(); // not sure if this belongs here
    copyHelper(root, otherDict.root);
    numWords = otherDict.numWords;
}

void Dictionary::copyHelper(Dictionary::Node *&thisTree, Dictionary::Node *otherTree) {
    if(otherTree== nullptr){
        thisTree = nullptr;
        return;
    }
    thisTree = new Node();
    thisTree->isWord = otherTree->isWord;
    for(int j = 0; j < NUM_CHARS; j++){
        copyHelper(thisTree->ptr[j], otherTree->ptr[j]);
    }
}

void Dictionary::LoadDictionaryFile(string filename) {
    string line;
    ifstream myFile;
    myFile.open(filename);
    if (myFile.fail()) {
        throw DictionaryError(" failed to open."); // The readme does not require a throw here.
    }else{
        while(!myFile.eof()){
            myFile >> line;  //read from the file word by word
            AddWord(line);  //use the add word function to add to the dictionary.

        }
    }

    myFile.close();

}

Dictionary::Dictionary(const Dictionary &otherDict) {
    root = new Node();
    numWords = 0;
    copyOther(otherDict);
}


void Dictionary::SaveDictionaryFile(string filename) {
/*ofstream dictFile;
dictFile.open(filename);

// Start with the empty string as the prefix.
SaveDictionaryHelper(root, "", dictFile);*/
ofstream myFile;
myFile.open(filename);
if (myFile.fail()) {
    throw DictionaryError("failed to open");

}else SaveDictionaryHelper(root, "", myFile);

}

void Dictionary::SaveDictionaryHelper(Dictionary::Node *curr, string currPrefix, ofstream &outFile) {
    if (curr == nullptr)
        return;

    if (curr->isWord) {
        outFile << currPrefix << endl;
    }

    for(int i=0; i< NUM_CHARS; i++)

        SaveDictionaryHelper(curr->ptr[i], currPrefix + string(1, i + (int)'a'),outFile);

}

void Dictionary::AddWord(string word) {
    //int position;
    Node* curr = root;
    for(int i=0; i < word.size(); i++){
        int position = (int)word[i] - (int)'a'; //gets the index of each character in word
        if(word[i] > (int)'z'|| word[i] < (int)'a' ) //if the character is not between 'a' and 'z'
            throw DictionaryError("Invalid character");
        if(curr->ptr[position]== nullptr){ // if the pointer is null
            curr->ptr[position] = new Node(); // creates a new node
        }

        curr = curr->ptr[position]; // moves the curr pointer
    }

    curr->isWord =true;
    numWords++; //updates the number of words in dictionary
}


bool Dictionary::IsWord(string word) {
    Node* curr = root;// sets curr to the root
    for(int i=0; i < word.size(); i++){ //
        int position = (int)word[i] - (int)'a'; //gets the index of each character in word
        if(word[i] > (int)'z'|| word[i] < (int)'a' ) //if the character is not between 'a' and 'z'
            throw DictionaryError("Invalid character");
        if(curr->ptr[position]== nullptr){ // if the pointer is null
            return false;
        }

        curr= curr->ptr[position]; // move curr to the next node

    }
    return curr->isWord;
}

bool Dictionary::IsPrefix(string word) {
    Node* curr = root;
    for(int i=0; i < word.size(); i++){
        int position = (int)word[i] - (int)'a';
        if(word[i] > (int)'z'|| word[i] < (int)'a' ) //if the character is not between 'a' and 'z'
            throw DictionaryError("Invalid character");
        if(curr->ptr[position]== nullptr){
            return false;
        }
        curr = curr->ptr[position];
    }
    return true;
}

int Dictionary::WordCount() {
    return numWords;
}



