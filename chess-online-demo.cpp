#include <iostream>
#include <array>
#include <stdexcept>
#include <sstream>

namespace chess {
    enum class castle {
        long_castle,
        short_castle
    };
    enum class color {
        white,
        black
    };
    class chess {
        protected:
            std::array<std::array<char, 8>, 8> square;
        public:
            bool validate(color color, int x1, int y1, int x2, int y2);
            bool validate(color color, castle castle_type);
            bool move(color color, int x1, int y1, int x2, int y2, bool force = false);
            bool move(color color, std::string query);
            bool move(color color);
            chess();
            void reset();
            void show();
            std::array<std::array<char, 8>, 8> state();
            void play();
    };
}

using namespace std;

namespace chess {

    // This function checks if castling is possible
    bool chess::validate(color color, castle castle_type) {
        int rank, rook_pos;
        char king, rook;

        // Set the color of king and rook
        if (color == color::white) {
            rank = 0;
            king = 'K';
            rook = 'R';
        } else {
            rank = 7;
            king = 'k';
            rook = 'r';
        }

        // Check if king is in correct place
        if (square[rank][4] != king) {
            return false;
        }

        // Set the value of rook_pos variable, containing rook's current position
        if (castle_type == castle::long_castle) {
            rook_pos = 0;
        } else {
            rook_pos = 7;
        }

        // Check if rook is in correct place
        if (square[rank][rook_pos] == rook) {

            // Check if every squares between king and rook is empty, return false if not
            for (int i = 5; i < rook_pos; i++) {
                if (square[rank][i] != ' ') {
                    return false;
                }
            }
        }

        // All tests passed, so castling is legal
        return true;
    }

    // This function checks if move is valid (except castling)
    bool chess::validate(color color, int x1, int y1, int x2, int y2) {

        // Declare some needed variables
        bool valid = false, correct_piece, capture_own_piece;

        // Check if square is in range
        if ((x1 >= 0 && x1 < 8) && (y1 >= 0 && y1 < 8) && (x2 >= 0 && x2 < 8) && (y2 >= 0 && y2 < 8)) {

            // Check if the square from where piece will be moved is not empty
            if (square[y1][x1] != ' ') {

                // Prepare for checking if the player is moving his own piece
                if (color == color::white) {
                    correct_piece = square[y1][x1] != tolower(square[y1][x1]);
                } else {
                    correct_piece = square[y1][x1] != toupper(square[y1][x1]);
                }

                // Check if the player is moving his own piece
                if (correct_piece) {

                    // Check if two squares, from where piece will move and where piece will placed, are not same
                    if (y1 != y2 || x1 != x2) {

                        // Prepare for checking if player is capturing his own piece
                        if (color == color::white) {
                            capture_own_piece = square[y2][x2] != tolower(square[y2][x2]);
                        } else {
                            capture_own_piece = square[y2][x2] != toupper(square[y2][x2]);
                        }

                        // Check if player is capturing his own piece
                        if (!capture_own_piece) {
                            valid = true;
                        }
                    }
                }
            }
        }
        return valid;
    }

    // This function works with the board directly
    bool chess::move(color color, int x1, int y1, int x2, int y2, bool force) {

        // Do an essensial test, check if move is forced, if yes, check if square is out of range
        // Program will fail if skipped this test, and square is out of range
        if (force) {
            for (int value : {x1, y1, x2, y2}) {
                if (value > 7 || value < 0) {
                    throw invalid_argument("Square is out of range!"); // Throw exception
                }
            }
        }

        // Check if move is either forced or valid
        if (force || validate(color, x1, y1, x2, y2)) {
                square[y2][x2] = square[y1][x1];
                square[y1][x1] = ' ';
        } else {
            return false;
        }

        // Moved successfully, inform it
        return true;
    }

    // This function take the move as std::string and moves
    bool chess::move(color color, string query) {

        // Prepare for checking if move is castling
        int rank;
        if (color == color::white) {
            rank = 0;
        } else {
            rank = 7;
        }

        // Check if move is castling
        if (query == "O-O" || query == "o-o" || query == "0-0") { // Check if move is short castling
            if (!validate(color, castle::short_castle)) {
                return false;
            }
            move(color, 4, rank, 6, rank, true);
            move(color, 7, rank, 5, rank, true);
            return true;
        } else if (query == "O-O-O" || query == "o-o-o" || query == "0-0-0") { // Check if move is long castling
            if (!validate(color, castle::long_castle)) {
                return false;
            }
            move(color, 4, rank, 2, rank, true);
            move(color, 0, rank, 3, rank, true);
            return true;
        }

        // Declare two strings and a stringstream to extract square information
        stringstream squares(query);
        string src, dest;

        // Extract square information from string
        squares >> src >> dest;
        int x1 = tolower(src[0])-'a';
        int y1 = src[1]-'1';
        int x2 = tolower(dest[0])-'a';
        int y2 = dest[1]-'1';

        // Call move function with all informations, and return the value it returned
        return move(color, x1, y1, x2, y2);
    }

    // This function takes input input from user with standard input and moves
    bool chess::move(color color) {

        // Declare string where move query will be stored
        string query = "";
        int i = 0;

        // Ask for move until move is valid
        do {

            // Show that move was invalid
            if (i && query != "") {
                cout << "Invaild move!" << endl;
            }
            i++;

            // Show prompt
            if (color == color::white) {
                cout << "white >>> ";
            } else {
                cout << "black >>> ";
            }

            // Get move
            getline(cin, query);

            // Return false if user entered exit
            if (query == "exit") {
                return false;
            }
        } while (!move(color, query));
        return true;
    }

    // Constructor
    chess::chess() {
        reset();
    }

    // This function will reset the board
    void chess::reset() {

        // Place white piece, except pawns
        square[0][0] = square[0][7] = 'R';
        square[0][1] = square[0][6] = 'N';
        square[0][2] = square[0][5] = 'B';
        square[0][3] = 'Q';
        square[0][4] = 'K';

        // Place black piece, except pawns
        square[7][0] = square[7][7] = 'r';
        square[7][1] = square[7][6] = 'n';
        square[7][2] = square[7][5] = 'b';
        square[7][3] = 'q';
        square[7][4] = 'k';

        // Place pawns of both colors
        char pawn;
        for (int y : {1, 6}) {

            // Change pawn color, when y = 1, pawn is while, black otherwise
            if (y == 1) {
                pawn = 'P';
            } else {
                pawn = 'p';
            }
            for (int x = 0; x < 8; x++) {
                square[y][x] = pawn;
            }
        }

        // Clear all other squares
        for (int x = 2; x < 6; x++) {
            for (int y = 0; y < 8; y++) {
                square[x][y] = ' ';
            }
        }
    }

    // This function show the state of board, directly to terminal
    void chess::show() {
        cout << "  +---+---+---+---+---+---+---+---+" << endl;
        for (int x = 7; x >= 0; x--) {
            cout << x+1 << " | ";
            for (int y = 0; y < 8; y++) {
                cout << square[x][y] << " | ";
            }
            cout << endl << "  +---+---+---+---+---+---+---+---+" << endl;
        }
        cout << "    a   b   c   d   e   f   g   h  " << endl;
    }

    // This function will return the array containing board state
    std::array<std::array<char, 8>, 8> chess::state() {
        return square;
    }

    // This function will ask for move infinitely, until user types exit on prompt
    void chess::play() {

        // Declare variable containing if move should be asked again
        bool again = true;

        // Ask moves, until user exits
        while (again) {

            // Ask for move to white, and store return value to again
            again = move(color::white);

            // Check if white moved, if yes, ask for move
            if (again) {

                // Show the board
                show();

                // Black must move, otherwise he will lose his chance
                while (!move(color::black)) {
                    cout << "You must move, otherwise you'll lose your chance" << endl;
                }

                // Show the board
                show();
            }
        }
    }
}

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
