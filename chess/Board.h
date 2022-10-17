#pragma once
#include<vector>
#include"Chess.h"

using namespace std;

class Board {
public:
	Board() {	//建立空的棋盤
		for (int i = 0; i < 8; i++) {
			for (int j = 0; j < 8; j++) {
				table[i][j] = ' ';
			}
		}
	}

	void cleanBoard() {
		for (int i = 0; i < 8; i++) {
			for (int j = 0; j < 8; j++) {
				table[i][j] = ' ';
			}
		}
	}
private:
	char table[8][8];
};



