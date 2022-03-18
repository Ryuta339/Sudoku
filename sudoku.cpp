#include <iostream>
#include <stack>

struct board {
	int board[9][9];
	int r;
	int c;
};

bool check_row(board *b, int r) {
	if (r<0 || r>=9) {
		return true;
	}
	bool flags[] = {false, false, false, false, false, false, false, false, false};
	for (int c=0; c<9; c++) {
		if (b->board[c][r] != 0 ) {
			if (flags[b->board[c][r]-1]) {
				return false;
			} else {
				flags[b->board[c][r]-1] = true;
			}
		} 
	}
	return true;
}

bool check_column(board *b, int c) {
	if (c<0 || c>=9) {
		return true;
	}
	bool flags[] = {false, false, false, false, false, false, false, false, false};
	for (int r=0; r<9; r++) {
		if (b->board[c][r] != 0 ) {
			if (flags[b->board[c][r]-1]) {
				return false;
			} else {
				flags[b->board[c][r]-1] = true;
			}
		} 
	}
	return true;
}

bool check_block(board *b, int c, int r) {
	int bc = (c / 3) * 3;
	int br = (r / 3) * 3;
	bool flags[] = {false, false, false, false, false, false, false, false, false};
	for (int i=0; i<3; i++) {
		for (int j=0; j<3; j++) {
			if (b->board[bc+i][br+j] != 0) {
				if (flags[b->board[bc+i][br+j]-1]) {
					return false;
				} else {
					flags[b->board[bc+i][br+j]-1] = true;
				}
			}
		}
	}
	return true;
}

bool check(board *b) {
	for (int c=0; c<9; c++) {
		if (!check_column(b, c)) {
			return false;
		}
	}
	for (int r=0; r<9; r++) {
		if (!check_row(b, r)) {
			return false;
		}
	}
	for (int c=0; c<9; c+=3) {
		for (int r=0; r<9; r+=3){
			if (!check_block(b, c, r)) {
				return false;
			}
		}
	}
	return true;
}

void visualize_board(board *b) {
	std::cout << "-------------" << std::endl;
	for (int c=0; c<9; c++) {
		std::cout << "|";
		for (int r=0; r<9; r++) {
			bool flag = b->board[c][r] == 0;
			if (flag)
				std::cout << " ";
			else 
				std::cout << b->board[c][r];
			if (r%3 == 2)
				std::cout << "|";
		}
		std::cout << std::endl;
		if (c%3 == 2)
			std::cout << "-------------" << std::endl;
	}
	std::cout << std::endl;
}

int main() {
	std::stack<board> s;
	board b;
	for (int c=0; c<9; c++) {
		for (int r=0; r<9; r++) {
			b.board[c][r] = 0;
		}
	}
	b.board[0][2] = 5;
	b.board[0][3] = 3;
	b.board[1][0] = 8;
	b.board[1][7] = 2;
	b.board[2][1] = 7;
	b.board[2][4] = 1;
	b.board[2][6] = 5;
	b.board[3][0] = 4;
	b.board[3][5] = 5;
	b.board[3][6] = 3;
	b.board[4][1] = 1;
	b.board[4][4] = 7;
	b.board[4][8] = 6;
	b.board[5][2] = 3;
	b.board[5][3] = 2;
	b.board[5][7] = 8;
	b.board[6][1] = 6;
	b.board[6][3] = 5;
	b.board[6][8] = 9;
	b.board[7][2] = 4;
	b.board[7][7] = 3;
	b.board[8][5] = 9;
	b.board[8][6] = 7;
	b.r = 0;
	b.c = 0;

	// visualize_board(&b);
	s.push(b);
	int cnt = 0;
	while(!s.empty()) {
		board b = s.top();
		s.pop();
		if (check(&b)) {
			std::cout << "no. " << cnt << std::endl;
			cnt ++;
			visualize_board(&b);
			if (b.c == 9) {
				std::cout << "ANSWER" << std::endl;
				visualize_board(&b);
				return 0;
			} else if (b.board[b.c][b.r] != 0){
				if (b.r == 8) {
					b.r = 0;
					b.c++;
				} else {
					b.r ++;
				}
				s.push(b);
			} else {
				for (int i=1; i<=9; i++) {
					board bb;
					for (int c=0; c<9; c++) {
						for (int r=0; r<9; r++) {
							bb.board[c][r] = b.board[c][r];
						}
					}
					bb.board[b.c][b.r] = i;
					if (b.r == 8) {
						bb.r = 0;
						bb.c = b.c + 1;
					} else {
						bb.r = b.r + 1;
						bb.c = b.c;
					}
					s.push(bb);
				}
			}
		}
	}

	return 0;
}
