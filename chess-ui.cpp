#include "chess.h"

using namespace std;

int main() {

    // Declare and set necessary variables
    bool play = true;
    string command = "";
    chess::chess chess;

    // Show the board
    chess.show();

    // Prompt user what to do, until he commands to exit
    while (play) {

        // Show the prompt
        cout << ">>> " << flush;

        // Get command
        getline(cin, command);

        // Check and do what to do
        if (command == "move") {
            if (chess.move(chess::color::white)) {
                chess.show();
                while (!chess.move(chess::color::black)) {
                    cout << "You must move, otherwise you'll lose your chance" << endl;
                }
                chess.show();
            }
        } else if (command == "play") {
            chess.show();
            chess.play();
        } else if (command == "reset") {
            chess.reset();
            chess.show();
        } else if (command == "exit") {
            play = false;
        } else if (command == "show") {
            chess.show();
        } else if (command == "") {
            continue;
        } else {
            cout << "Unknown command" << endl;
        }
    }
    return 0;
}
