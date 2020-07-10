#include <iostream>
#include <sstream>

using namespace std;

namespace chess {

	char square[8][8] = {' '};

	bool move(string color) {
		string query, src, dest;
		bool valid, correct_piece, capture_own_piece;
		do {
            valid = false;
            cout << color << " >>> ";
            src = "", dest = "";
            getline(cin, query);
            if (query == "exit") {
                return false;
            }
            if (query == "O-O" || query == "o-o" || query == "0-0") {
                if (color == "white") {
                    square[0][6] = square[0][4];
                    square[0][5] = square[0][7];
                    square[0][4] = square[0][7] = ' ';
                } else {
                    square[7][6] = square[7][4];
                    square[7][5] = square[7][7];
                    square[7][4] = square[7][7] = ' ';
                }
                return true;
            } else if (query == "O-O-O" || query == "o-o-o" || query == "0-0-0") {
                if (color == "white") {
                    square[0][2] = square[0][4];
                    square[0][3] = square[0][0];
                    square[0][4] = square[0][0] = ' ';
                } else {
                    square[7][2] = square[7][4];
                    square[7][3] = square[7][0];
                    square[7][4] = square[7][0] = ' ';
                }
                return true;
            }
            stringstream cells(query);
            cells >> src >> dest;
            int x1 = tolower(src[0])-'a';
            int y1 = src[1]-'1';
            int x2 = tolower(dest[0])-'a';
            int y2 = dest[1]-'1';
            if ((x1 >= 0 && x1 < 8) && (y1 >= 0 && y1 < 8) && (x2 >= 0 && x2 < 8) && (y2 >= 0 && y2 < 8)) {
                if (square[y1][x1] != ' ') {
                    if (color == "white") {
                        correct_piece = square[y1][x1] != tolower(square[y1][x1]);
                    } else {
                        correct_piece = square[y1][x1] != toupper(square[y1][x1]);
                    }
                    if (correct_piece) {
                        if (src != dest) {
                            if (color == "white") {
                                capture_own_piece = square[y2][x2] != tolower(square[y2][x2]);
                            } else {
                                capture_own_piece = square[y2][x2] != toupper(square[y2][x2]);
                            }
                            if (!capture_own_piece) {
                                valid = true;
                            }
                        }
                    }
                }
            }
            if (valid) {
                square[y2][x2] = square[y1][x1];
                square[y1][x1] = ' ';
            } else {
                cout << "Invalid move!" << endl;
            }
        } while (!valid);
        return true;
	}

	void init() {
		square[0][0] = square[0][7] = 'R';
		square[0][1] = square[0][6] = 'N';
		square[0][2] = square[0][5] = 'B';
		square[0][3] = 'Q';
		square[0][4] = 'K';
		square[1][0] = square[1][1] = square[1][2] =
			square[1][3] = square[1][4] = square[1][5] =
			square[1][6] = square[1][7] = 'P';
		square[7][0] = square[7][7] = 'r';
		square[7][1] = square[7][6] = 'n';
		square[7][2] = square[7][5] = 'b';
		square[7][3] = 'q';
		square[7][4] = 'k';
		square[6][0] = square[6][1] = square[6][2] =
			square[6][3] = square[6][4] = square[6][5] =
			square[6][6] = square[6][7] = 'p';
		for (int x = 2; x < 6; x++) {
			for (int y = 0; y < 8; y++) {
				square[x][y] = ' ';
			}
		}
	}

	void show() {
		cout << "  +---+---+---+---+---+---+---+---+" << endl;
		for (int x = 7; x >= 0; x--) {
			cout << x+1 << " |";
			for (int y = 0; y < 8; y++) {
				cout << " " << square[x][y] << " |";
			}
			cout << endl << "  +---+---+---+---+---+---+---+---+" << endl;
		}
        cout << "    a   b   c   d   e   f   g   h  " << endl;
	}

    void play() {
        bool again = true;
        while (again) {
            again = false;
            if (move("white")) {
                show();
                if (move("black")) {
                    show();
                    again = true;
                }
            }
        }
    }

}

int main() {
	bool play = true;
	string command = "";
	chess::init();
	chess::show();
	while (play) {
		cout << ">>> ";
		getline(cin, command);
		if (command == "move") {
			if (chess::move("white")) {
                chess::show();
                if (chess::move("black")) {
                    chess::show();
                }
            }
        } else if (command == "play") {
            chess::show();
            chess::play();
        } else if (command == "reset") {
            chess::init();
            chess::show();
		} else if (command == "exit") {
            play = false;
		} else if (command == "") {
            continue;
		} else {
            cout << "Unknown command" << endl;
		}
	}
	return 0;
}
