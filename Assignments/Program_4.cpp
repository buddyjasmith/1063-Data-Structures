/**
* @ProgramName: Program-4
* @Author: Buddy Smith
* @Description:
*     	Game of life uses a dynamic 2d array to create the game, Game of Life.
*       The rules that apply for determining whether a cell lives of dies is as follows.
*
*	     Any live cell with fewer than two live neighbours dies.
*		 Any live cell with two or three live neighbours lives on to the next generation.
*		 Any live cell with more than three live neighbours dies.
*		 Any dead cell with exactly three live neighbours becomes a live cell.

* @Course: 1063 Data Structures
* @Semester: Spring 2017
* @Date: 01 05 2017
*/

#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>
#include <conio.h>
#include <time.h>
#include <unistd.h>

using namespace std;
/**
	* @ClassName: GameOfLife
	* @Description:
	*     Creates the structures necessary for Game of Life.
	* @Params:
	*    Constructors are overloaded.  2 variations are available
	*    string filename - imports the .txt file for initial load
	*    int row and columns, determines the size of the array/game board
	* @Returns:
	*    void
	*/
class GameOfLife{
private:
    int **Board;
    int **Board2;
    int Rows;
    int Cols;
    void Pause(int MilliSeconds){
        clock_t t;
        t = clock();
        int sum = 0;
        while((clock()-t)< MilliSeconds){
            sum++;
        }
    }
    bool Stable;
public:
/**
	* @MethodName: GameOfLife
	* @Description:
	*     Creates the structures necessary for Game of Life given a text file
	*     supplied by the user or program.
	* @Params:
	*    string: determines file name to be opened
	* @Returns:
	*    void
	*/
    GameOfLife(string filename){
        string line;
        char ch;
        ifstream fin;
        fin.open(filename.c_str());
        fin >> Rows >> Cols;
        InitBoardArray(Board);
        InitBoardArray(Board2);
        for (int i = 0; i < Rows; i++){
            for (int j = 0; j < Cols; j++){
                fin.get(ch);
                if (ch == 10){
                    continue;
                }
                Board[i][j] = int(ch) - 48;
            }
        }

    }
/**
    * @MethodName: GameOfLife
	* @Description:
	*     Creates the structures necessary for Game of Life to the dimensions
	*     specified by the user
	* @Params:
	*    int r and c: rows and columns of 2d array
	* @Returns:
	*    void
	*/
      GameOfLife(int r, int c){
        Rows = r;
        Cols = c;
        InitBoardArray(Board);
        InitBoardArray(Board2);
        PrintBoard();
    }
/**
    * @MethodName: MakeGun
	* @Description:
	*    supplies the necessary coodinates for a Glider/Gun System
	* @Params:
	*    Game of life instance
	* @Returns:
	*    void
	*/
    void MakeGun(GameOfLife instance) {
		// Left Block
		instance.SetCell(5, 1, 1);
		instance.SetCell(5, 2, 1);
		instance.SetCell(6, 1, 1);
		instance.SetCell(6, 2, 1);
		instance.SetCell(3, 35, 1);
		instance.SetCell(4, 35, 1);
		instance.SetCell(3, 36, 1);
		instance.SetCell(4, 35, 1);
		instance.SetCell(5, 11, 1);
		instance.SetCell(6, 11, 1);
		instance.SetCell(7, 11, 1);
		instance.SetCell(4, 12, 1);
		instance.SetCell(8, 12, 1);
		instance.SetCell(3, 13, 1);
		instance.SetCell(9, 13, 1);
		instance.SetCell(3, 14, 1);
		instance.SetCell(9, 14, 1);
		instance.SetCell(6, 15, 1);
		instance.SetCell(4, 16, 1);
		instance.SetCell(8, 16, 1);
		instance.SetCell(5, 17, 1);
		instance.SetCell(6, 17, 1);
		instance.SetCell(7, 17, 1);
		instance.SetCell(6, 18, 1);
		instance.SetCell(3, 21, 1);
		instance.SetCell(4, 21, 1);
		instance.SetCell(5, 21, 1);
		instance.SetCell(3, 22, 1);
		instance.SetCell(4, 22, 1);
		instance.SetCell(5, 22, 1);
		instance.SetCell(2, 23, 1);
		instance.SetCell(6, 23, 1);
		instance.SetCell(1, 25, 1);
		instance.SetCell(2, 25, 1);
		instance.SetCell(6, 25, 1);
		instance.SetCell(7, 25, 1);


	}

/**
    * @MethodName: InitBoardArray
	* @Description:
	*    initializes entries of 2d array
	* @Params:
	*    int **&b
	* @Returns:
	*    void
	*/

    void InitBoardArray(int **&b){
        b = new int*[Rows];
        for (int i = 0; i < Rows; i++){
            b[i] = new int[Cols];
        }
        ResetBoardArray(b);
    }

/**
    * @MethodName: ResetBoardArray
	* @Description:
	*    Clears entries of a 2d array
	* @Params:
	*    int **&b
	* @Returns:
	*    void
	*/
    void ResetBoardArray(int **&b){
        for (int i = 0; i < Rows; i++){
            for (int j = 0; j < Cols; j++){
                b[i][j] = 0;
            }
        }
    }
/**
    * @MethodName: PrintBoard
	* @Description:
	*    Prints contents of 2d array
	* @Params:
	*    none
	* @Returns:
	*    void
	*/
    void PrintBoard(){
        for(int x =0; x < Cols; x++)
            cout << "*" ;
        cout << endl;
        for (int i = 0; i < Rows; i++){
            cout << i << " ";
            for (int j = 0; j < Cols; j++){
                if (Board[i][j] == 1)
                    cout << char('X');
                else
                    cout << " ";
            }
            cout << endl;
        }
    }
/**
    * @MethodName: CountNeighbors
	* @Description:
	*    Determines life or death cycles of lifeforms in game
	* @Params:
	*    int row, col.
	* @Returns:
	*    returns number of neighbors for a given location
	*/
    int CountNeighbors(int row, int col){
        int neighbors = 0;
        if (Board[row][col] == 1){
            neighbors--;
        }
        for (int i = row - 1; i <= row + 1; i++){
            for (int j = col - 1; j <= col + 1; j++){
                if (OnBoard(i, j)){
                    neighbors += Board[(i + Rows) % Rows][(j+Cols)%Cols];
                }
            }
        }
        return neighbors;
    }
/**
    * @MethodName: OnBoard
	* @Description:
	*    Determines if entry is on the game board
	* @Params:
	*    int row, col.
	* @Returns:
	*    true or false
	*/
    bool OnBoard(int row, int col){
        return (row >= 0 && row < Rows && col >= 0 && col < Cols);
    }
/**
    * @MethodName: RandomPopulate
	* @Description:
	*   Randomly Populates game board
	* @Params:
	*    int num, number of entries to populate
	* @Returns:
	*    none
	*/
    void RandomPopulate(int num){
        int r = 0;
        int c = 0;
        for (int i = 0; i<num; i++){
            r = rand() % Rows;
            c = rand() % Cols;

            Board[r][c] = 1;
        }
        AddGens();
    }
/**
    * @MethodName: SetCell
	* @Description: Sets entry of 2d array @ given location to the value specified by user
	* @Params:
	*    int row, col, val
	* @Returns:
	*    none
	*/
    void SetCell(int r, int c, int val){
        Board[r][c] = val;
    }
/**
    * @MethodName: AddGens
	* @Description: Adds the 2 instances of the array boards to determine value of board
	* @Params:
	*   none
	* @Returns:
	*    none
	*/
    void AddGens(){
        for (int i = 0; i < Rows; i++){
            for (int j = 0; j < Cols; j++){
                Board[i][j] += Board2[i][j];
            }
        }
        ResetBoardArray(Board2);
    }
/**
    * @MethodName: clear_screen
	* @Description: clears the console directory
	* @Params:
	*    none
	* @Returns:
	*    none
	*/
    void clear_screen(){
//      for(int i=0;i<lines;i++){
//        cout<<endl;
//      }
   system("CLS");
    }
/**
    * @MethodName: checkCorner
	* @Description: checks if a value is present in the corners of the board
	* @Params:
	*    none
	* @Returns:
	*    none
	*/
    bool CheckCorner(int rows, int columns){
        return (rows == 0 && columns == 0) || (rows == (Rows - 1) && (columns == Cols - 1))
                || ((rows == 0) && columns == (Cols - 1)) || (rows == (Rows - 1) && (columns == 0));
    }
/**
    * @MethodName: Run
	* @Description: Begins comparison of the board
	* @Params:
	*    int generations: number of life cycles to complete
	* @Returns:
	*    none
	*/
    void Run(int generations){

        int neighbors = 0;
        int g = 0;
        while (g < generations){
                Stable = false;
            for (int i = 0; i < Rows; i++){
                for (int j = 0; j < Cols; j++){
                    neighbors = CountNeighbors(i, j);
                    if (Board[i][j] == 1 && (neighbors < 2 || neighbors > 3)){
                        Board2[i][j] = -1;
                        Stable = true;
                    }
                    if (Board[i][j] == 0 && neighbors == 3){
                        Board2[i][j] = 1;
                    }
                    if (CheckCorner(i, j)) {
						          Board2[i][j] = -1;
						          Stable = true;
					}
                }
            }
            AddGens();
            Pause(500);
            if(Stable==false)
                break;
            clear_screen();
            PrintBoard();
            g++;
        }

    }

};

int main(){

    int menuChoice = 0,
        num = 0,
        rows = 0,
        columns = 0,
        generations = 0;
    string textFile;
    do{
        system("CLS");
        for(int i = 0; i < 40; i++)
            cout << "*";
        cout << endl;
        cout << "\nPlease enter your choice for Spawn Type. \t\n";
        cout << "\t1.  Random Spawn (requires integer value)**Still in development" << endl;
        cout << "\t2.  Glider Gun" << endl;
        cout << "\t3.  Text File Input (Uses gen_one.txt)\n";
        cout << "\t4.  Exit  \n";

        for(int i = 0; i < 40; i++)
            cout << "*";

        cout << "\n\n\tSelection:  ";
        cin >> menuChoice;

        switch(menuChoice){
        case 1:{

            cout << "Enter the number of life forms you wish to bring to life." << endl;
            cin >> num;
            cout << "Enter the dimensions of the Game Board you would like, rows columns.\n";
            cin >> rows;
            cin >> columns;
            cout << "How many possible generations would you like to view?";
            cin >> generations;
            system("CLS");


            GameOfLife G(rows, columns);
            G.RandomPopulate(num);
            G.Run(generations);
            break;
            }
        case 2:
            {
            // Entry prompt for Glider Gun
            cout << "How many generations would you like to view?\n";
            cin >> generations;

            rows = 30;
            columns = 40;
            GameOfLife Gun(rows,columns);
            Gun.MakeGun(Gun);
            Gun.Run(generations);
//            GameOfLife Gun("text.txt");
//            Gun.Run(generations);
            break;
            }
        case 3:{
           cout << "\nEnter the name of the Text file you wish to use.\n";
           cin >> textFile;
           GameOfLife Text(textFile);
           Text.Run(1000);
        }
        case 4:
            cout << "Now Exiting.\n";
            break;
        }
    }
    while(menuChoice != 4);


    return 0;
}
