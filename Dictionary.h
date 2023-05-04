#ifndef BOGGLE_DICTIONARY_H
#define BOGGLE_DICTIONARY_H

#include <iostream>
#include <fstream>
#include <string>
using namespace std;


const int NUM_CHARS = 26;

class DictionaryError{
public:
    explicit DictionaryError(string msg) {
        this->msg = msg;
    }
    string Msg(){
        return msg;  // returns king of flavor
    }
private:
    string msg;
};

class Dictionary
{

public:

/*Function: Initializes the private variables.
*
* Precondition: None
*
* Post-condition: Private variables will be set to default values.
*/
    Dictionary();


/*Function: Destroys the nodes containing arrays.
 *
 * Precondition: Must have a functional destroyHelper function.
 *
 * Post-condition: Destroys the branches then destroys the node.
 */
    ~Dictionary();  // I will not require this

/*Function: This will copy the contents of otherDict to this.
*
* Precondition: Must have a functional copyOther function.
*
* Post-condition: Copies the words to this.
*/
    Dictionary(const Dictionary& otherDict);    // copy constructor


/*Function: This will establish a root node and load a dictionary.
 *
 * Precondition: Must have a functional LoadDictionaryFile(filename) method.
 *
 * Post-condition: Establishes a root node and loads a dictionary.
 */
    explicit Dictionary(string filename);       // The keyword explicit is used to tell the compiler
                                                // that this is not a conversion constructor.


/*Function: Copies the contents of otherDict to this.
 *
* Precondition: This instance must not have the address of otherDict. A functional copyOther is required.
 *
* Post-condition: Copies the contents of otherDict.
*/
    Dictionary& operator=(const Dictionary& otherDict);

/*Function: Loads the words from filename.
 *
* Precondition: The filename must contain a dictionary to read from. Must have a functional AddWord function.
 *
* Post-condition: Loads words from filename.
*/
    void LoadDictionaryFile(string filename);


/*Function: Saves words from the tree and stores them in a file.
 *
 * Precondition: Must have a functional SaveDictionaryHelper function. Filename must exist.
 *
 * Post-condition: Saves words from the tree and stores them in a file.
 */
    void SaveDictionaryFile(string filename);

/*Function: Adds words to the tree.
 *
 * Precondition: Must have a root node established.
 *
 * Post-condition: Creates a path to the word and adds the new word to the tree.
 */
    void AddWord(string word);

/*Function: Destroys all nodes and sets numWords to zero.
 *
* Precondition: Must have a functional destroyHelper function.
 *
* Post-condition: All the nodes will be destroyed and root will not have any branches.
*/
    void MakeEmpty();

/*Function: Determines whether a word is in the tree.
 *
 * Precondition: Establish the root node.
 *
 * Post-condition: Return true if word exists otherwise it returns false.
 */
    bool IsWord(string word);

/*Function: Determines whether prefix is valid.
 *
* Precondition: Must have a root note established.
 *
* Post-condition: Returns true if prefix leads to a word, false otherwise.
*/
    bool IsPrefix(string word);

/*Function: Returns the number of words.
 *
* Precondition: N/A
 *
* Post-condition: Returns the number of words.
*/
    int WordCount();

private:

    class Node {
    public:

        struct Node *ptr[NUM_CHARS];
        bool isWord;
        Node(){
            isWord = false;
            for(int i=0; i <NUM_CHARS; i++){
                ptr[i]= nullptr;
            }
        }

        // Your node structure here.
        // You can also use a struct if you like.

        // It is strongly recommended you create a constructor
        // to set default values
    };

    Node* root;
    int numWords;

    // This function is used by the
    // copy constructor and the assignment operator.

/*Function: This function copies the contents of otherDict to this.
 *
* Precondition: Must have a functional copyHelper function.
 *
* Post-condition: The content of otherDict will be copies to this.
*/
    void copyOther(const Dictionary& otherDict);

    // Any private methods you need/want
    // You may change these helpers if you want, but you don't need to.

/*Function: Destroys all nodes.
 *
* Precondition: N/A
 *
* Post-condition: Destroys all branches, then destroys the node.
*/

    void destroyHelper(Node* thisTree);

/*Function: Copies the content from otherTree.
 *
* Precondition: Other tree must have content to copy.
 *
* Post-condition: Content from otherTree will be copied to thisTree.
*/
    void copyHelper(Node*& thisTree, Node* otherTree);


/*Function: Function to find every word in the tree and save it to a file
 *
* Precondition: A base case for a recursive call is required.
 *
* Post-condition: Saves into a file all words in tree.
*/
    void SaveDictionaryHelper(Node* curr, string currPrefix, ofstream& outFile);
};

#endif //BOGGLE_DICTIONARY_H
