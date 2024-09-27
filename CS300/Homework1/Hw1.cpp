#include <iostream>
#include "Stack.cpp"
#include <random>
#include <fstream> //for file creation
#include <algorithm>
#include <string>

using namespace std;

struct Tuple{ //for storing the cells coordinates
    int x;
    int y;
    explicit Tuple(int x = 0, int y = 0)
            : x(x), y(y){}
};

ostream & operator << (ostream &out, const Tuple &T)
{
    out << "("<<T.x << "," << T.y <<")";
    return out;
}

void ResetMaze(std::vector<std::vector<std::vector<int>>>& maze, int rowSize, int columnSize,
               std::vector<std::vector<std::vector<std::vector<int>>>>& mazeCollection
) {
    mazeCollection.push_back(maze);
    for (int i = 0; i < rowSize; ++i) {
        for (int j = 0; j < columnSize; ++j) {
            for (int k = 0; k < 5; ++k) {
                maze[i][j][k] = 1;
            }
        }
    }
}

void ResetVisited(std::vector<std::vector<std::vector<int>>>& maze, int rowSize, int columnSize) {
    for (int i = 0; i < rowSize; ++i) {
        for (int j = 0; j < columnSize; ++j) {
            maze[i][j][0] = 1;
        }
    }
}


void CreateMaze(int row, int column, Stack<Tuple> * S, std::vector<std::vector<std::vector<int>>>& maze, std::mt19937 gen){
    while (!S->isEmpty()) {
        Tuple current = S->top();
        maze[current.x][current.y][0] = false;

        std::vector<int> directions = {1, 2, 3, 4}; // 1: Left 2: Right 3: Up 4: Down
        std::shuffle(directions.begin(), directions.end(), gen); // Shuffle the directions

        bool moved = false;
        for (int wayToGo : directions) {
            switch (wayToGo) {
                case 1:
                    // Move left (x, y-)
                    if(current.y - 1 >= 0){
                        Tuple temp = current;
                        temp.y -= 1;
                        if (maze[temp.x][temp.y][0]) {
                            maze[current.x][current.y][1] = 0;
                            maze[temp.x][temp.y][2] = 0;
                            S->push(temp);
                            moved = true;
                        }
                    }
                    break;
                case 2:
                    // Move right (x, y+)
                    if(current.y + 1 < column){
                        Tuple temp = current;
                        temp.y += 1;
                        if (maze[temp.x][temp.y][0]) {
                            maze[current.x][current.y][2] = 0;
                            maze[temp.x][temp.y][1] = 0;
                            S->push(temp);
                            moved = true;
                        }
                    }
                    break;
                case 3:
                    // Move up (x+, y)
                    if(current.x + 1 < row){
                        Tuple temp = current;
                        temp.x += 1;
                        if (maze[temp.x][temp.y][0]) {
                            maze[current.x][current.y][3] = 0;
                            maze[temp.x][temp.y][4] = 0;
                            S->push(temp);
                            moved = true;
                        }
                    }
                    break;
                case 4:
                    // Move down (x-, y)
                    if(current.x - 1 >= 0){
                        Tuple temp = current;
                        temp.x -= 1;
                        if (maze[temp.x][temp.y][0]) {
                            maze[current.x][current.y][4] = 0;
                            maze[temp.x][temp.y][3] = 0;
                            S->push(temp);
                            moved = true;
                        }
                    }
                    break;

            }
            if (moved) {
                break; // If we have moved, break the loop
            }
        }

        if (!moved) {
            S->pop(); // If we haven't moved, pop the stack
        }
    }
}


void PrintMaze(std::vector<std::vector<std::vector<int>>>& maze, int a){
    std::string mazeFile = "maze_" + std::to_string(a) + ".txt";
    std::ofstream file(mazeFile);

    // x is the column and y is the row (so they are switched)
    file << maze.size() << " " << maze[0].size() << std::endl;
    for (int row = 0; row < maze.size(); ++row) {
        for (int column = 0; column < maze[row].size(); ++column) {
            file << "x=" << column << " y=" << row <<
                 " l=" << maze[row][column][1]  << " r=" << maze[row][column][2] <<
                 " u=" << maze[row][column][3] << " d=" << maze[row][column][4] << std::endl;
        }
    }
    file.close();
}


void StartCreatingMaze(int mazeCount ,int row, int column, Stack<Tuple> * Stack, std::vector<std::vector<std::vector<int>>>& maze,
                       std::vector<std::vector<std::vector<std::vector<int>>>>& mazeCollection
)  {
    Tuple temp = Tuple(0,0);
    for (int i = 0; i < mazeCount; ++i) {
        //For true randomness https://en.cppreference.com/w/cpp/numeric/random/uniform_int_distribution
        std::random_device rd;
        std::mt19937 gen(rd()); // Mersenne Twister RNG, seeded with rd

        Stack->push(temp);
        CreateMaze(row, column, Stack, maze, gen); //gen for seed, creates the maze
        PrintMaze(maze, (i+1));
        ResetMaze(maze, row, column, mazeCollection); //sets all values to 0
    }

}

void PrintPath(Stack<Tuple> * S, int mazeID,
               int entryX, int entryY, int exitX, int exitY){

    std::string pathFile = "maze_" + std::to_string(mazeID) + "_path_" + std::to_string(entryX) + "_"
                           + std::to_string(entryY) + "_" + std::to_string(exitX) + "_" + std::to_string(exitY) +".txt";
    std::ofstream file(pathFile);

    std::vector<Tuple> pathVector;
    int stackCount = S->returnStackCount();

    for (int i = 0; i < stackCount ; ++i) {
        Tuple t = S->top();
        cout << t << endl;
        pathVector.push_back(t);
        S->pop();
    }
    for (int i = stackCount-1; i >= 0 ; --i) {
        file << pathVector[i].y << " " << pathVector[i].x << endl;
    }
}

void SolveMaze(Stack<Tuple> * S, std::vector<std::vector<std::vector<int>>>& maze, int mazeID,
               int entryX, int entryY, int exitX, int exitY){

    std::random_device rd;
    std::mt19937 gen(rd()); // Mersenne Twister RNG, seeded with rd

    Tuple startingPoint = Tuple(entryX, entryY);
    Tuple endingPoint = Tuple(exitX, exitY);
    S->push(startingPoint);
    Tuple current = S->top();

    while((current.x != endingPoint.x) || (current.y != endingPoint.y)) {
        maze[current.x][current.y][0] = 1;

        std::vector<int> directions = {1, 2, 3, 4}; // 1: Left 2: Right 3: Up 4: Down
        std::shuffle(directions.begin(), directions.end(), gen); // Shuffle the directions

        bool moved = false; //To break from the loop
        for (int wayToGo : directions) {
            current = S->top();
            if((current.x == endingPoint.x) && (current.y == endingPoint.y)){
                break;
            }
            Tuple temp = current;
            switch (wayToGo) {
                case 1:
                    // Move left (x, y-)
                    if(current.y - 1 >= 0){
                        temp.y -= 1;
                        if (!maze[temp.x][temp.y][0] && !maze[current.x][current.y][1] && !maze[temp.x][temp.y][2]) {
                            S->push(temp);
                            moved = true;
                        }
                    }
                    break;
                case 2:
                    // Move right (x, y+)
                    if(current.y + 1 < maze[0].size()){
                        temp.y += 1;
                        if (!maze[temp.x][temp.y][0] && !maze[current.x][current.y][2] && !maze[temp.x][temp.y][1]) {
                            S->push(temp);
                            moved = true;
                        }
                    }
                    break;
                case 3:
                    // Move up (x+, y)
                    if(current.x + 1 < maze.size()){
                        temp.x += 1;
                        if (!maze[temp.x][temp.y][0] && !maze[current.x][current.y][3] && !maze[temp.x][temp.y][4]) {
                            S->push(temp);
                            moved = true;
                        }
                    }
                    break;

                case 4:
                    // Move down (x-, y)
                    if(current.x - 1 >= 0){
                        temp.x -= 1;
                        if (!maze[temp.x][temp.y][0] && !maze[current.x][current.y][4] && !maze[temp.x][temp.y][3]) {
                            S->push(temp);
                            moved = true;
                        }
                    }
                    break;
            }
            if (moved) {
                break; // If we have moved, break the loop
            }
        }
        if (!moved) {
            S->pop(); // If we haven't moved, pop the stack
        }
    }
    S->push(endingPoint);

    PrintPath(S, mazeID, entryX, entryY, exitX, exitY);
}


int main() {
    std::vector<std::vector<std::vector<std::vector<int>>>> mazeCollection;

    //PART 1 ------------------------------------------------------------------------------------
    //Inputs
    int numberOfMazes;
    int rowSize;
    int columnSize;
    cout << "Enter the number of mazes: ";
    cin >> numberOfMazes;
    cout << "Enter the number of rows and columns (M and N): ";
    cin >> rowSize >> columnSize;

    //A 3d vector that contains a maze, 0th element if 1 = not visited, if 0 = visited,
    //other elements in this order: l, r, u, d, all set to 1 at the start
    std::vector<std::vector<std::vector<int>>> maze
            (rowSize, std::vector<std::vector<int>>(columnSize, std::vector<int>(5, 1)));

    //Maze Generator
    Stack<Tuple> *S1 = new Stack<Tuple>();
    StartCreatingMaze(numberOfMazes, rowSize, columnSize, S1, maze,mazeCollection);
    cout << "\nAll mazes are generated.\n\n";
    //PART 1 ------------------------------------------------------------------------------------

    //PART 2 ------------------------------------------------------------------------------------
    ResetVisited(maze, rowSize, columnSize);
    int mazeID, entryX, entryY, exitX, exitY;
    cout << " Enter a maze ID between 1 to 5 inclusive to find a path: ";
    cin >> mazeID;
    cout << " Enter x and y coordinates of the entry points (x,y) or (column,row): ";
    cin >> entryY >> entryX;
    cout << " Enter x and y coordinates of the exit points (x,y) or (column,row): ";
    cin >> exitY >> exitX;



    Stack<Tuple> *S2 = new Stack<Tuple>();
    SolveMaze(S2, mazeCollection[mazeID-1], mazeID, entryX, entryY, exitX, exitY);

    //PART 2 ------------------------------------------------------------------------------------

    return 0;
}
