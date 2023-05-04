#ifndef BOGGLE_BOGGLE_H
#define BOGGLE_BOGGLE_H

#include <iostream>
#include <string>
#include <fstream>
#include "Dictionary.h"

using namespace std;

const int BOARD_SIZE = 4;

class BoardNotInitialized {};

class Boggle {
public:

/*Function: Initializes the private variables.
 *
 * Precondition: LoadDictionaryFile function or AddWord function required.
 *
 * Post-condition:Initializes dict with words from dictionary.txt.
 */
    Boggle();  // load "dictionary.txt" into dict

/*Function: Initializes the private variables.
 *
 * Precondition: N/A
 *
 * Post-Condition: Private variables are set to default values.
 */
    explicit Boggle(string filename);  // load filename into dict


/*Function: Copies the content from Board to this.
 *
* Precondition: N/A
 *
* Post-condition:Copies content from board to this.
*/

    void SetBoard(string board[BOARD_SIZE][BOARD_SIZE]);

/*Function: This method finds all the words on the current board stored by `board` and
 *          saves these words to the `wordsFound` dictionary.
 *
 *Precondition: SolveBoardHelper method must work properly.
 *
 * Post-condition: Words will be saved from the current board.
 */

    void SolveBoard(bool printBoard, ostream& output);

/*Function: Saves the words found.
 *
 * Precondition: Have a functional SaveDictionaryFile.
 *
 * Post-condition: Words found will be saves into filename.
 */

    void SaveSolve(string filename);   // Saves all the words from the last solve.

    Dictionary GetDictionary();
    Dictionary WordsFound();

private:
    Dictionary dict;
    Dictionary wordsFound;
    string board[BOARD_SIZE][BOARD_SIZE];
    int visited[BOARD_SIZE][BOARD_SIZE];

/*Function: Prints out a display to either an output file or the console.
 *
 * Precondition: N/A
 *
 * Post-condition: The game board will be displayed.
 */
    void PrintBoard(ostream& output);

/*Function: Finds all the words on the board.
 *
* Precondition: A recursive call.
 *
* Post-condition: Finds all the words on the board.
*/
void SolveBoardHelper(int row, int col, string board[BOARD_SIZE][BOARD_SIZE], string pre, ostream &output, bool printBoard, int current);

};

#endif //BOGGLE_BOGGLE_H
