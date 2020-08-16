#include "chess.h"
#include <cstdio>
#include <sstream>
#include <vector>
#include <fstream>

using namespace std;

int main(int argc, char** argv) {

    // Declare and set necessary variables
    bool play = true;
    string command;
    vector<string> cmd_argv;

    // Intialize chess board object
    chess::chess* board;

    // Check if a file was given to load
    if (argc > 1) {

        // Prepare for loading the file
        ifstream data(argv[1]);
        if (!data.is_open()) {
            perror("Can't open file");
            return 1;
        }

        // Convert file contents to string
        string line, state = "";
        for (int i = 0; i < 8; i++) {
            getline(data, line);
            for (int x = 0; x < 8; x++){
                state += line[x];
            }
            state += '\n';
        }

        // Close the file
        data.close();

        // Try to setup board
        try {
            chess::chess setup(state);
            board = &setup;

        // Catch exception, eg. invalid pieces in file
        } catch (logic_error &error) {
            cout << "Error: " << error.what() << endl;
            return 1;
        }
    } else {
        chess::chess setup;
        board = &setup;
    }


    chess::chess chess = *board;

    // Show the board
    chess.show();

    // Prompt user what to do, until he commands to exit
    while (play) {

        cmd_argv.clear();

        // Show the prompt
        cout << ">>> " << flush;

        // Get command
        getline(cin, command);

        // Prepare before processing
        stringstream cmd_arg(command);
        string arg;
        while (cmd_arg >> arg) {
            cmd_argv.push_back(arg);
        }

        // Check if user entered empty input
        if (command == "") continue;

        // Check if user wants just one move for both colors
        if (cmd_argv[0] == "move") {
            if (chess.move(chess::color::white)) {
                chess.show();
                while (!chess.move(chess::color::black)) {
                    cout << "You must move, otherwise you'll lose your chance" << endl;
                }
                chess.show();
            }

        // Check if user wants to enter playing mode
        } else if (cmd_argv[0] == "play") {
            chess.show();
            chess.play();

        // Check if user wants to reset the board
        } else if (cmd_argv[0] == "reset") {
            chess.reset();
            chess.show();

        // Check if user wants to see the board
        } else if (cmd_argv[0] == "show") {
            chess.show();

        // Check if user wants to load board state from another file
        } else if (cmd_argv[0] == "load") {

            // Check if argument is given
            if (cmd_argv.size() < 2) {
                cout << "Missing file name" << endl;
                continue;
            }

            // Prepare for loading the file
            string filename = string(command.begin() + 5, command.end());

            // Open file
            ifstream data(filename);

            // Check if file is opened
            if (!data.is_open()) {
                perror("Can't open file");
                continue;
            } else {

                // Convert file contents to string
                string line, state = "";
                for (int i = 0; i < 8; i++) {
                    getline(data, line);
                    for (int x = 0; x < 8; x++){
                        state += line[x];
                    }
                    state += '\n';
                }

                // Close the file
                data.close();

                // Try to setup board
                try {
                    chess.load(state);

                // Catch logic_error, eg. invalid piece in input
                } catch (std::logic_error &error) {
                    cout << "Error: " << error.what() << endl;
                    continue;
                }
            }

            // Show the board
            chess.show();

        // Check if user wants to save board state to another file
        } else if (cmd_argv[0] == "save") {

            // Check if argument is given
            if (cmd_argv.size() < 2) {
                cout << "Missing file name" << endl;
                continue;
            }

            // Prepare for writing state to file
            std::array<std::array<char, 8>, 8> state = chess.state();

            // Prepare for loading the file
            string filename = string(command.begin() + 5, command.end());

            // Open the file
            ofstream file(filename);

            // Check if file opened
            if (!file.is_open()) {
                perror("Can't access/create file");
                continue;
            }

            // Write to file
            for (int y = 7; y >= 0; y--) {
                for (int x = 0; x < 8; x++) {
                    file << state[y][x];
                }
                file << '\n';
            }

            // Close the file
            file.close();

        // Check if user wants to exit
        } else if (cmd_argv[0] == "exit" || cmd_argv[0] == "q") {
            play = false;

        // Inform user that his command is incorrect
        } else {
            cout << "Unknown command" << endl;
        }
    }
    return 0;
}
