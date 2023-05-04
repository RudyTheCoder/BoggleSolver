
#include "Dictionary.h"
#include "Boggle.h"

// Your code here


// This function is done.
Dictionary Boggle::GetDictionary() {
    return dict;
}

// This function is done.
Dictionary Boggle::WordsFound() {
    return wordsFound;
}

Boggle::Boggle() {
    dict.LoadDictionaryFile("dictionary.txt");
    for(int i= 0 ; i<BOARD_SIZE; i++){
        for(int j=0; j<BOARD_SIZE; j++){
            board[i][j] = "";
            visited[i][j] = 0;
        }
    }

}

Boggle::Boggle(string filename) {
    dict.LoadDictionaryFile(filename);
    for(int i= 0 ; i<BOARD_SIZE; i++){
        for(int j=0; j<BOARD_SIZE; j++){
            board[i][j] = "";
            visited[i][j] = 0;
        }
    }
}

void Boggle::SetBoard(string board[BOARD_SIZE][BOARD_SIZE]) {
    for(int i=0; i < BOARD_SIZE ; i++){
        for(int j = 0; j < BOARD_SIZE; j++){
            this->board[i][j] = board[i][j];
        }
    }

}

void Boggle::PrintBoard(ostream &output) {


    output << "Number of Words: " << WordsFound().WordCount() << endl;


    for(int i=0; i < BOARD_SIZE ; i++){   // this print out the first line of board and visited
        if(visited[0][i]!= 0)
            output << " '" << board[0][i] << "' ";
        else
            output << "  " << board[0][i] << "  ";

    }
    output << "\t";
    for(int i=0; i < BOARD_SIZE ; i++){
        output << "  " << visited[0][i] << "  ";
    }
    output << endl;


    for(int i=0; i < BOARD_SIZE ; i++){  // this print out the second line of board and visited
        if(visited[1][i]!= 0)
            output << " '" << board[1][i] << "' ";
        else
            output << "  " << board[1][i] << "  ";

    }
    output << "\t";
    for(int i=0; i < BOARD_SIZE ; i++){
        output << "  " << visited[1][i] << "  ";
    }
    output << endl;


    for(int i=0; i < BOARD_SIZE ; i++){  // this print out the third line of board and visited
        if(visited[2][i]!= 0)
            output << " '" << board[2][i] << "' ";
        else
            output << "  " << board[2][i] << "  ";

    }
    output << "\t";

    for(int i=0; i < BOARD_SIZE ; i++){
        output << "  " << visited[2][i] << "  ";
    }
    output << endl;

    for(int i=0; i < BOARD_SIZE ; i++){   // this print out the fourth line of board and visited
        if(visited[3][i]!=0)
            output << " '" << board[3][i] << "' ";
        else
            output << "  " << board[3][i] << "  ";

    }
    output << "\t";
    for(int i=0; i < BOARD_SIZE ; i++){
        output << "  " << visited[3][i] << "  ";
    }
    output << endl;

}

void Boggle::SaveSolve(string filename) {

    wordsFound.SaveDictionaryFile(filename);
}

void Boggle::SolveBoard(bool printBoard, ostream &output) {

   wordsFound.MakeEmpty(); // Does this reset the words properly?
   int current = 0;


   for(int row = 0; row < BOARD_SIZE; row++){
       for(int col = 0; col < BOARD_SIZE; col++){
            string prefix = ""; //To hold a string
            //visited[row][col]=0;
            SolveBoardHelper(row, col, board, prefix,output, printBoard, current); // calls SolveBoardHelper 16 times
       }
   }
}
void Boggle::SolveBoardHelper(int row, int col, string board[BOARD_SIZE][BOARD_SIZE], string pre, ostream &output, bool printBoard, int current) {

    if(row < 0 || col < 0 || row >= BOARD_SIZE || col  >= BOARD_SIZE) //  a base case
        return;


    if(visited[row][col] != 0)
        return;


    if(!dict.IsPrefix(pre + board[row][col]))  // string pre = ""; string containing a possible prefix from the matrix
        return;

    if(dict.IsWord(pre + board[row][col]) && !wordsFound.IsWord(pre + board[row][col]) && printBoard){

        output << "Word: " << pre + board[row][col]<< endl;
        wordsFound.AddWord(pre + board[row][col] );
        PrintBoard(output); //I dont know what to pass into PrintBoard?
        visited[row][col] = 0;

    }
    if(dict.IsWord(pre + board[row][col]) && !wordsFound.IsWord(pre + board[row][col]) && !printBoard){

           wordsFound.AddWord(pre + board[row][col]);
           if(visited[row][col]!=pre.length())
               visited[row][col] = 0;

           output <<wordsFound.WordCount() << "\t"<< pre + board[row][col] <<endl;

    }

    pre += board[row][col];

    visited[row][col] = pre.length();

    SolveBoardHelper(row - 1,col,board, pre, output, printBoard,current);  // North
    SolveBoardHelper(row - 1,col + 1,board,pre, output, printBoard,current);  // Northeast
    SolveBoardHelper(row ,col + 1,board,pre, output, printBoard,current);  // East
    SolveBoardHelper(row + 1,col + 1,board,pre,output, printBoard,current);  // Southeast
    SolveBoardHelper(row + 1,col,board,pre,output, printBoard,current);  // South
    SolveBoardHelper(row + 1,col - 1,board,pre,output, printBoard,current);  // Southwest
    SolveBoardHelper(row ,col -1,board,pre,output, printBoard,current );  // West
    SolveBoardHelper(row - 1,col - 1,board,pre,output, printBoard,current);  // Northwest

    visited[row][col] = 0;

}

