#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;


void printcommand(int &command){
	
	cout << "***Path Finding***\n";
	cout << "*0.Quit          *\n";
	cout << "*1.One Goal      *\n";
	cout << "*2.More Goals    *\n";
	cout << "*3.Shortest Path *\n";
	cout << "******************\n";
	cout << "Input a command(0, 1, 2, 3):";
	cin >> command;
	
	while( command != 0 && command != 1 && command != 2 && command != 3 ){
	
		cout << "You enter a wrong command!\n";
		cout << "Please input a new command(0, 1, 2, 3):";
		cin >> command;
	} 
	
	return;
}



class Maze {
public:
    Maze(const std::string& filename);
    void solveMaze();
    void printMaze();
    void printVisitedPaths();

private:
    std::vector<std::vector<char> > maze;
    int cols;
    int rows;
    int goalcol;
    int goalrow;

    bool isValidMove(int col, int row);
    bool solve(int col, int row);
    void markPath(int col, int row, char mark);
};


void inputfile( ifstream inputname, int x, int y ){
	
	string num;
	cout << "\n";
	cout << "Input a file number:";
	cin >> num; 
	num = "input"+num+".txt";
	inputname.open(num);
	if(!inputname){
		cout << num << " doesn't exist!\n";
	} 
	
	 
}
Maze::Maze(const std::string& filename) {
    std::ifstream file(filename.c_str());

    if (!file.is_open()) {
        std::cerr << "Error opening file: " << filename << std::endl;
        exit(1);
    }

    file >> rows >> cols;

    maze.resize(cols, std::vector<char>(rows));

    for (int i = 0; i < cols; i++) {
        for (int j = 0; j < rows; j++) {
            file >> maze[i][j];
            if (maze[i][j] == 'G') {
                goalcol = i;
                goalrow = j;
            }
        }
    }

    file.close();
}

void Maze::printMaze() {
    for (int i = 0; i < cols; ++i) {
        for (int j = 0; j < rows; ++j) {
            std::cout << maze[i][j] << " ";
        }
        std::cout << std::endl;
    }
}


void Maze::printVisitedPaths() {
    for (int i = 0; i < cols; ++i) {
        for (int j = 0; j < rows; ++j) {
            if (maze[i][j] == 'V' || maze[i][j] == 'R') {
                std::cout << "V ";
            } else if (maze[i][j] == 'O') {
                std::cout << "O ";
            } else if (maze[i][j] == 'G') {
                std::cout << "G ";
            } else if (maze[i][j] == 'E') {
                std::cout << "E ";
            }
        }
        std::cout << std::endl;
    }
}


bool Maze::isValidMove(int col, int row) {
    return (col >= 0 && col < cols && row >= 0 && row < rows && (maze[col][row] == 'E' || maze[col][row] == 'G'));
}

bool Maze::solve(int col, int row) {
    if (col == goalcol && row == goalrow) {
        markPath(col, row, 'G'); // Mark the path with 'R'
        return true; // Reached the exit
    }

    if (isValidMove(col, row)) {
        maze[col][row] = 'V';

        // Right
        if (solve(col, row + 1)) {
            markPath(col, row, 'R'); // Mark the path with 'R'
            return true;
        }

        // Down
        if (solve(col + 1, row)) {
            markPath(col, row, 'R'); // Mark the path with 'R'
            return true;
        }

        // Left
        if (solve(col, row - 1)) {
            markPath(col, row, 'R'); // Mark the path with 'R'
            return true;
        }

        // Up
        if (solve(col - 1, row)) {
            markPath(col, row, 'R'); // Mark the path with 'R'
            return true;
        }

        maze[col][row] = 'E'; // Dead end
        return false;
    }

    return false; // Invalid move
}

void Maze::markPath(int col, int row, char mark) {
    if (maze[col][row] != 'G') {
        maze[col][row] = mark;
    }
}

void Maze::solveMaze() {
    std::cout << "Visited Paths:" << std::endl;
    if (solve(0, 0)) {
        printVisitedPaths(); // Print the visited paths
        std::cout << "Path found to goal!" << std::endl;
    } else {
        std::cout << "No path found to goal." << std::endl;
    }
}

int main() {
	
	int command;
	printcommand(command);
	
	ifstream inputname;
	int x, y;
	Maze* myMaze;
	

    std::cout << "Original Maze:" << std::endl;
    myMaze->printMaze();

    myMaze->solveMaze();

    std::cout << "Solved Maze:" << std::endl;
    myMaze->printMaze();

    return 0;
}

