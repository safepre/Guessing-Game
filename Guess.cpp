#include <iostream>
using namespace std;
const int MAXGUESS = 1000;  // range is [0,MAXGUESS]
// Polymorphic classes
class Player {

public:
    virtual int getGuess() = 0;
    void update(bool lowOrhigh, int guess) {

        if (lowOrhigh && (high > guess)) {
            high = guess;
        }
        else if (!lowOrhigh &&  (low < guess)) {
            low = guess;
        }

    }

protected:
    int high = 1000;
    int low = 0;
};

class HumanPlayer : public Player {
    //The implementation of HumanPlayer::getGuess() 
    //should prompt the user to enter a number and return the value entered from the keyboard.
public:
    int getGuess() {
        int number;
        cout << "Guess a number: ";
        cin >> number;
        return number;
    }
};

class ComputerPlayer : public Player {
    //The implementation of ComputerPlayer::getGuess() 
    //should randomly select a number from 0 to MAXGUESS.
public:
    int getGuess() {
        int selectNumber;
  
        selectNumber = rand() % MAXGUESS + 1; // 1 to 1000

        cout << "The computer guess is " << selectNumber << endl;

        return selectNumber;
    }
};

class SmartComputerPlayer : public ComputerPlayer {
public:

    int getGuess() {
        int behavesAI;
        cout << "The computer guess is ";
        behavesAI = ((high - low) / 2) + low; //sort of similar to how a  binary search behaves.
        cout << behavesAI << endl;
        return behavesAI;
    }

};

bool checkForWin(int guess, int answer, Player& player1, Player& player2) {
    if (answer == guess) {
        cout << "You're right! You win!" << endl;
        return true;
    }
    else if (answer < guess) {
        cout << "Your guess is too high." << endl;
        player1.update(true,  guess); //If player 1 or player 2 is true that we will update the function that it is too high (that way we can succesfully do the AI)
        player2.update(true, guess);
    }
    else {
        cout << "Your guess is too low." << endl;
        player1.update(false, guess);//If player 1 or player 2 is false that we will update the function that it is too low (that way we can succesfully do the AI)
        player2.update(false, guess);
    }
    return  false;
}

int play(Player& player1, Player& player2) {  // do not change this line
    // change anything you like below this line
    bool win = false;
    int answer = 0, guess = 0;
    int notifyRound = 1;
    int numGuesses = 0;
    answer = rand() % MAXGUESS + 1; // 0 - 999 with  + 1 it will be 1 - 1000

    while (!win) {
        cout << endl;
        cout << "********- Round " << notifyRound << "-********" << endl
            << endl;
        cout << "Player 1's turn to guess." << endl;
        guess = player1.getGuess();
        numGuesses++;
        win = checkForWin(guess, answer,player1,player2);
        if (win) break;

        cout << "\nPlayer 2's turn to guess." << endl;

        guess = player2.getGuess();

        numGuesses++;

        win = checkForWin(guess, answer, player2 ,player1);
        notifyRound++;
    }
    return numGuesses;
}

Player* getPlayer() {
    int selectnum = 0;
    cout << "Please make a selection for Player 1" << endl;
    cout << "1. Human Player" << endl;
    cout << "2. Computer Player" << endl;
    cout << "3. Smart Computer Player" << endl;
    cout << "4. Quit The Program" << endl;
    cout << "----------------------------" << endl;
    cout << "Please enter a number between 1 and 4: ";
    cin >> selectnum;
    while (selectnum < 1 || selectnum > 4) {
        cout << "Error! The number you entered was out of range " << endl;
        cout << "Please enter a number between 1 and 4: ";
        cin >> selectnum;
    }
    if (selectnum == 1) {
        Player* hp = new HumanPlayer();
        return hp;
    }
    if (selectnum == 2) {
        Player* cp = new ComputerPlayer();
        return cp;
    }
    if (selectnum == 3) {
        Player* sp = new SmartComputerPlayer();
        return sp;
    }
    if (selectnum == 4)
    {
        exit(0);
    }
}
int main() {
    srand(time(NULL));
    Player* p1 = getPlayer();
    Player* p2 = getPlayer();
    play(*p1, *p2);

}
