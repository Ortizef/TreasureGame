//Christian Rodriguez
//Efrain Ortiz
#include <iostream>
#include <iomanip>

const int ROWS = 10;
const int COLS = 10;
const int SIZE = 5;


int userRow= 0;
int userCol= 0;
double userWon = 0.00;

struct TreasureChest {
    std::string chestName;
    int row;
    int cols;
    double lootAmount = 0.00;
    bool available = true;
};

void fillTreasureArray(TreasureChest[]);
void fillGrid(char[][COLS],char);
bool checkValid(int);
void printGrid(char[][COLS]);
void outputIntro();
void endGrid(char[][COLS],char);
double chestFound(TreasureChest[],int,int,char,char[][COLS]);


int main() {
    const char SYM = '-';
    const char TSYM = 'T';
    char grid[ROWS][COLS];
    TreasureChest treasure[SIZE];
    char reply = ' ';
    int counter = 0;
    const int Ncounter = 3;

    outputIntro();
    std::cout << std::endl;

    fillTreasureArray(treasure);
    fillGrid(grid,SYM);
    std:: cout << std::fixed << std::setprecision(2);
    do {
        printGrid(grid);
        std::cout << "Enter the row #: ";
        std::cin >> userRow;
        std::cout << std::endl;
        while (checkValid(userRow) == false) {
            std::cin >> userRow;
        }
        std::cout << "Enter the column #: ";
        std::cin >> userCol;
        std::cout << std::endl;
        while (checkValid(userCol) == false) {
            std::cin >> userCol;
        }
        chestFound(treasure,userRow,userCol,SYM,grid);
        std::cout << "Would you like to play again (Y or N)? \n";
        std::cin >> reply;
        std::cout << std::endl;
        counter++;
    } while (counter != Ncounter && (toupper(reply) == 'Y'));
    endGrid(grid,TSYM);

}

void fillTreasureArray(TreasureChest tr[]) {

    tr[0] = {"Pirate's Chest", 2, 4, 145.90, true};
    tr[1] = {"Dragon's Chest", 5, 8, 258.24, true};
    tr[2] = {"Troll's Chest", 3, 1, 203.71, true};
    tr[3] = {"Queen's Chest", 8, 0, 190.15, true};
    tr[4] = {"Thief's Chest", 1, 9, 98.95, true};

}

void fillGrid(char arr[][COLS],const char SYM) {
    for (int r = 0; r < ROWS; r++) {
        for (int c = 0; c < COLS; c++) {
            arr[r][c] = SYM;
        }
    }
}

bool checkValid(int userInput) {
    while (userInput > 9 || userInput < 0 || std::cin.fail()) {
        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore();
        }
        std::cout << "That entry is invalid. Please enter a valid integer based on the grid size: " << std::endl;
        return false;
    }
    return true;
}

void printGrid (char arr[][COLS]) {
    std::cout << "  0 1 2 3 4 5 6 7 8 9\n";
    for (int r = 0; r < ROWS; r++) {
        std::cout << r << ' ';
        for (int c = 0; c < COLS; c++) {
            std::cout << arr[r][c] << ' ';
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
    std::cout << "Legend: - (Unknown); E (Empty); T (Treasure)\n";
    std::cout << std::endl;
}

void outputIntro(){
    std::cout << "This is a treasure hunt game.\n";
    std::cout << "You have 3 attempts to find the 5 treasure chests hidden in the grid below.\n";
}

double chestFound(TreasureChest tr[], const int rows, const int cols,char SYM, char arr[][COLS]) {
    double amountLooted = 0.0;
    for(int i = 0; i < SIZE; i++) {
        if(arr[rows][cols] != SYM && !tr[i].available) {
            std::cout << "You already found the treasure at this location. "
                      << "Your stupidity has cost you a guess.\n"<< std::endl;
            arr[rows][cols] = 'E';
            return amountLooted;
        }else if(rows == tr[i].row && cols == tr[i].cols) {
            std::cout << "You have found the " << tr[i].chestName << "!\n"
                      << "Inside you find $" << tr[i].lootAmount << " worth of valuables.\n" << std::endl;
            arr[rows][cols] = 'T';
            amountLooted += tr[i].lootAmount;
            tr[i].available = false;
            userWon = userWon + amountLooted;
            return amountLooted;
        }
    }
    arr[rows][cols] = 'E';
    std::cout << "Sorry, there is no treasure at those coordinates." << std::endl;
    return amountLooted;
}

void endGrid(char arr[][COLS],const char TSYM) {
    std:: cout <<"The game is now over. You looted $" << userWon << " worth of valuables from chests." << std:: endl;
    std:: cout <<"The grid below shows the position of all treasure chests: " << std:: endl;
    std:: cout << std:: endl;
    std::cout << "  0 1 2 3 4 5 6 7 8 9\n";
    for (int r = 0; r < ROWS; r++) {
        std::cout << r << ' ';
        for (int c = 0; c < COLS; c++) {
            std::cout << arr[r][c] << ' ';
            arr[2][4] = TSYM;
            arr[5][8] = TSYM;
            arr[3][1] = TSYM;
            arr[8][0] = TSYM;
            arr[1][9] = TSYM;
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
    std::cout << "Legend: - (Unknown); E (Empty); T (Treasure)\n";
    std::cout << std::endl;
}
