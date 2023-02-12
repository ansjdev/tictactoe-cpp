#include <iostream>
#include <vector>

using namespace std;

char pieces[3] = {'X', 'O', ' '};
int board[9] = {
    2, 2, 2,
    2, 2, 2,
    2, 2, 2
};


int players_wins[2] = { 0, 0 };
int current_player = 0;

bool finished = false;

void endGame();
void startGame();

// Main

int main()
{
    system("CLS");
    startGame();

    return 0;
}

// My Infos:
void printHeader()
{
    cout << string(30, '*') << endl;
    cout << "** C++ TicTacToe by: AnsjDev\n";
    cout << string(30, '*') << endl
         << endl;
}

void printGitHub()
{
    cout << "\n\n** Like this repository! \n** AnsjDev GitHub: https://github.com/ansjdev\n\n\n";
}

// Infos

void printPlayersScoreboard()
{

    cout << "** Score: \n";
    for (int i = 0; i < 2; i++)
    {
        cout << "- Total PLAYER " << i+1 << " WINS: " << players_wins[i] << endl;
    }
}

void printStartInfo()
{
    system("CLS");
    printHeader();

    cout << "Player 1: " << pieces[0] << endl;
    cout << "Player 2: " << pieces[1] << endl << endl;

    cout << "** Starting game....\n\n";

    printPlayersScoreboard();
}

// Win condition

vector<int> getWin()
{
    // Check Horizontal Win
    for (int i = 0; i < 9; i += 3)
    {
        if (board[i] == board[i + 1] && board[i + 1] == board[i + 2] && board[i] != 2)
        {
            return {i, i + 1, i + 2};
        }
    }

    // Check Vertical Win
    for (int i = 0; i < 3; i++)
    {
        if (board[i] == board[i + 3] && board[i + 3] == board[i + 6] && board[i] != 2)
        {
            return {i, i + 3, i + 6};
        }
    }

    // Check Diagonal win

    if (board[0] == board[4] && board[4] == board[8] && board[0] != 2)
    {
        return {0, 4, 8};
    }

    if (board[2] == board[4] && board[4] == board[6] && board[2] != 2)
    {
        return {2, 4, 6};
    }

    return {};
}

int check_win()
{
    return getWin().empty() ? 0 : 1;
}

// Board

void drawBoard(int fill = 1)
{
    char new_board[9];
    for (int i = 0; i < 9; i++)
    {
        if(board[i] == 2) {
            new_board[i] = fill == 1 ? i+49 : ' ';
        } else {
            new_board[i] = pieces[board[i]];
        }
    }
    
    cout << "\n     |     |     \n";
    cout << "  " << new_board[0] << "  |  " << new_board[1] << "  |  " << new_board[2] << endl;
    cout << "_____|_____|_____\n";
    cout << "     |     |     \n";
    cout << "  " << new_board[3] << "  |  " << new_board[4] << "  |  " << new_board[5] << endl;
    cout << "_____|_____|_____\n";
    cout << "     |     |     \n";
    cout << "  " << new_board[6] << "  |  " << new_board[7] << "  |  " << new_board[8] << endl;
    cout << "     |     |     \n\n";
}

void drawWinBoard()
{
    vector<int> win = getWin();
    if(win.empty()) return;

    for (int &i : board) i = 2;

    for (int i = 0; i < 3; i++)
    {
        board[win[i]] = current_player;
    }

    drawBoard(0);
}

// Checks 

int checkValidInput(int input)
{
    if (input < 1 || input > 9 || cin.fail())
    {
        while (true) {
            if (cin.fail() || input < 1 || input > 9) {
                cin.clear();
                cin.ignore(1000, '\n');
                cout << "Your input isn't valid." << endl;
                cout << "Select number between 1 and 9: ";
                cin >> input;
            } else {
                return input;
            }
        }
    }
    return input;
}

void checkValidSlot(int slot)
{
    if (board[slot - 1] != 2) 
    {
        while (true) {
            if (board[slot - 1] != 2) {
                cin.clear();
                cin.ignore(1000, '\n');
                cout << "That slot isn't empty.\n";
                cout << "Select an empty slot: ";
                cin >> slot;
            } else {
                break;
            }
        }
    }
}

// Game

void runGame()
{
    cout << "\nCurrent player turn: PLAYER " << current_player + 1 << " [ " << pieces[current_player] << " ]" << endl
         << endl;

    int input;
    cout << "Select number between 1 and 9: ";
    cin >> input;
    
    int slot = checkValidInput(input);
    checkValidSlot(slot);

    board[slot-1] = current_player;

    drawBoard();
    
    if (check_win())
    {
        players_wins[current_player]+=1;

        cout << "\n\n** PLAYER " << current_player + 1 << " WIN!\n";

        drawWinBoard();

        printPlayersScoreboard();

        finished = true;
        return;
    }

    current_player = current_player == 0 ? 1 : 0;
}

void startGame()
{

    finished = false;

    printHeader();
    printStartInfo();

    drawBoard();

    while (!finished)
    {
        runGame();
    }

    endGame();
}

void endGame()
{
    string input;
    cout << "\n\n** Continue the game? (yes) or (no): ";
    cin >> input;

    if (input == "yes")
    {
        for (int &i : board) i = 2;
        startGame();
    } else {
        cout << "\n\n** Thanks for playing :)";
        printGitHub();
    }
}