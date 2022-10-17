#include"Viewer.h"
void Viewer::SetColor(int color)
{
	HANDLE hConsole;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, color);
}

void Viewer::showBoard(const vector<Piece*>& chess, int current_player, int check) {
	system("cls");
	if (current_player == 1) {
		cout << "white's turn\n";
	}
	else if (current_player == 0) {
		cout << "black's turn\n";
	}
	else {
		cout << endl;
	}
	cout << "投降請輸入 surrender" << endl << "跳出此局遊戲請輸入 exit" << endl;
	if (check != 0) {
		cout << "將軍!!\n";
	}
	cout << " \\x ０１２３４５６７\n";
	cout << "y   ----------------\n";

	char board[8][8];
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			board[i][j] = ' ';
		}
	}
	for (int i = 0; i < chess.size(); i++) {
		//白棋
		if (chess[i]->getFirstMove()) {
			if (chess[i]->getType() == 1) {
				if (check == 1) {
					board[chess[i]->getPos().x][chess[i]->getPos().y] = 'G';
				}
				else {
					board[chess[i]->getPos().x][chess[i]->getPos().y] = 'K';
				}
			}
			else if (chess[i]->getType() == 2) {
				board[chess[i]->getPos().x][chess[i]->getPos().y] = 'Q';
			}
			else if (chess[i]->getType() == 3) {

				board[chess[i]->getPos().x][chess[i]->getPos().y] = 'B';
			}
			else if (chess[i]->getType() == 4) {
				board[chess[i]->getPos().x][chess[i]->getPos().y] = 'R';
			}
			else if (chess[i]->getType() == 5) {
				board[chess[i]->getPos().x][chess[i]->getPos().y] = 'N';
			}
			else if (chess[i]->getType() == 6) {
				board[chess[i]->getPos().x][chess[i]->getPos().y] = 'P';

			}

		}
		//黑棋
		else {
			if (chess[i]->getType() == 1) {
				if (check == -1) {
					board[chess[i]->getPos().x][chess[i]->getPos().y] = 'g';
				}
				else {
					board[chess[i]->getPos().x][chess[i]->getPos().y] = 'k';
				}
			}
			else if (chess[i]->getType() == 2) {
				board[chess[i]->getPos().x][chess[i]->getPos().y] = 'q';
			}
			else if (chess[i]->getType() == 3) {

				board[chess[i]->getPos().x][chess[i]->getPos().y] = 'b';
			}
			else if (chess[i]->getType() == 4) {
				board[chess[i]->getPos().x][chess[i]->getPos().y] = 'r';
			}
			else if (chess[i]->getType() == 5) {
				board[chess[i]->getPos().x][chess[i]->getPos().y] = 'n';
			}
			else if (chess[i]->getType() == 6) {
				board[chess[i]->getPos().x][chess[i]->getPos().y] = 'p';

			}
		}
	}
	for (int i = 0; i < 8; i++) {
		cout << i << "|  ";
		for (int j = 0; j < 8; j++) {
			if (board[j][i] == 'g') {
				SetColor(192);
				cout << "王";
			}
			else if (board[j][i] == 'G') {
				SetColor(207);
				cout << "王";
			}
			else if (board[j][i] == ' ') {
				if ((j + i) % 2 == 0) {
					SetColor(111);
				}
				else {
					SetColor(143);
				}
				cout << "  ";
			}
			else if (board[j][i] >= 'A' && board[j][i] <= 'Z') {
				if ((j + i) % 2 == 0) {
					SetColor(111);
				}
				else {
					SetColor(143);
				}
				if (board[j][i] == 'K') {
					cout << "王";
				}
				else if (board[j][i] == 'Q') {
					cout << "后";
				}
				else if (board[j][i] == 'B') {
					cout << "主";
				}
				else if (board[j][i] == 'N') {
					cout << "騎";
				}
				else if (board[j][i] == 'R') {
					cout << "城";
				}
				else if (board[j][i] == 'P') {
					cout << "兵";
				}
			}
			else {
				if ((j + i) % 2 == 0) {
					SetColor(96);
				}
				else {
					SetColor(128);
				}
				if (board[j][i] == 'k') {
					cout << "王";
				}
				else if (board[j][i] == 'q') {
					cout << "后";
				}
				else if (board[j][i] == 'b') {
					cout << "主";
				}
				else if (board[j][i] == 'n') {
					cout << "騎";
				}
				else if (board[j][i] == 'r') {
					cout << "城";
				}
				else if (board[j][i] == 'p') {
					cout << "兵";
				}
			}
		}
		SetColor(7);
		cout << endl;
	}
	SetColor(7);
}

void Viewer::showAllPath(vector<Piece*> chess, const vector<pos>& posssible) {
	system("cls");
	cout << "possible path:\n" << "投降請輸入 surrender" << endl << "跳出此局遊戲請輸入 exit" << endl << endl;
	cout << " \\x ０１２３４５６７\n";
	cout << "y   ----------------\n";

	char board[8][8];
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			board[i][j] = ' ';
		}
	}

	for (int i = 0; i < chess.size(); i++) {
		//白棋
		if (chess[i]->getFirstMove()) {
			if (chess[i]->getType() == 1) {
				board[chess[i]->getPos().x][chess[i]->getPos().y] = 'K';
			}
			else if (chess[i]->getType() == 2) {
				board[chess[i]->getPos().x][chess[i]->getPos().y] = 'Q';
			}
			else if (chess[i]->getType() == 3) {

				board[chess[i]->getPos().x][chess[i]->getPos().y] = 'B';
			}
			else if (chess[i]->getType() == 4) {
				board[chess[i]->getPos().x][chess[i]->getPos().y] = 'R';
			}
			else if (chess[i]->getType() == 5) {
				board[chess[i]->getPos().x][chess[i]->getPos().y] = 'N';
			}
			else if (chess[i]->getType() == 6) {
				board[chess[i]->getPos().x][chess[i]->getPos().y] = 'P';

			}

		}
		//黑棋
		else {
			if (chess[i]->getType() == 1) {
				board[chess[i]->getPos().x][chess[i]->getPos().y] = 'k';
			}
			else if (chess[i]->getType() == 2) {
				board[chess[i]->getPos().x][chess[i]->getPos().y] = 'q';
			}
			else if (chess[i]->getType() == 3) {

				board[chess[i]->getPos().x][chess[i]->getPos().y] = 'b';
			}
			else if (chess[i]->getType() == 4) {
				board[chess[i]->getPos().x][chess[i]->getPos().y] = 'r';
			}
			else if (chess[i]->getType() == 5) {
				board[chess[i]->getPos().x][chess[i]->getPos().y] = 'n';
			}
			else if (chess[i]->getType() == 6) {
				board[chess[i]->getPos().x][chess[i]->getPos().y] = 'p';

			}
		}
	}

	//加入可能路徑
	for (int i = 0; i < posssible.size(); i++) {
		if (board[posssible[i].x][posssible[i].y] == ' ') {
			board[posssible[i].x][posssible[i].y] = '*';
		}
		else if (board[posssible[i].x][posssible[i].y] == 'K' || board[posssible[i].x][posssible[i].y] == 'k') {
			board[posssible[i].x][posssible[i].y] = '1';
		}
		else if (board[posssible[i].x][posssible[i].y] == 'Q' || board[posssible[i].x][posssible[i].y] == 'q') {
			board[posssible[i].x][posssible[i].y] = '2';
		}
		else if (board[posssible[i].x][posssible[i].y] == 'B' || board[posssible[i].x][posssible[i].y] == 'b') {
			board[posssible[i].x][posssible[i].y] = '3';
		}
		else if (board[posssible[i].x][posssible[i].y] == 'R' || board[posssible[i].x][posssible[i].y] == 'r') {
			board[posssible[i].x][posssible[i].y] = '4';
		}
		else if (board[posssible[i].x][posssible[i].y] == 'N' || board[posssible[i].x][posssible[i].y] == 'n') {
			board[posssible[i].x][posssible[i].y] = '5';
		}
		else if (board[posssible[i].x][posssible[i].y] == 'P' || board[posssible[i].x][posssible[i].y] == 'p') {
			board[posssible[i].x][posssible[i].y] = '6';
		}
	}

	for (int i = 0; i < 8; i++) {
		cout << i << "|  ";
		for (int j = 0; j < 8; j++) {
			if (board[j][i] == ' ') {
				if ((j + i) % 2 == 0) {
					SetColor(111);
				}
				else {
					SetColor(143);
				}
				cout << "  ";
			}
			else if (board[j][i] == '*') {
				SetColor(238);
				cout << "路";
			}
			else if (board[j][i] >= '1' && board[j][i] <= '6') {
				SetColor(207);
				if (board[j][i] == '1') {
					cout << "王";
				}
				else if (board[j][i] == '2') {
					cout << "后";
				}
				else if (board[j][i] == '3') {
					cout << "主";
				}
				else if (board[j][i] == '4') {
					cout << "城";
				}
				else if (board[j][i] == '5') {
					cout << "騎";
				}
				else if (board[j][i] == '6') {
					cout << "兵";
				}
			}
			//白棋
			else if (board[j][i] >= 'A' && board[j][i] <= 'Z') {
				if ((j + i) % 2 == 0) {
					SetColor(111);
				}
				else {
					SetColor(143);
				}
				if (board[j][i] == 'K') {
					cout << "王";
				}
				else if (board[j][i] == 'Q') {
					cout << "后";
				}
				else if (board[j][i] == 'B') {
					cout << "主";
				}
				else if (board[j][i] == 'N') {
					cout << "騎";
				}
				else if (board[j][i] == 'R') {
					cout << "城";
				}
				else if (board[j][i] == 'P') {
					cout << "兵";
				}
			}
			//黑棋
			else {
				if ((j + i) % 2 == 0) {
					SetColor(96);
				}
				else {
					SetColor(128);
				}
				if (board[j][i] == 'k') {
					cout << "王";
				}
				else if (board[j][i] == 'q') {
					cout << "后";
				}
				else if (board[j][i] == 'b') {
					cout << "主";
				}
				else if (board[j][i] == 'n') {
					cout << "騎";
				}
				else if (board[j][i] == 'r') {
					cout << "城";
				}
				else if (board[j][i] == 'p') {
					cout << "兵";
				}
			}
		}
		SetColor(7);
		cout << endl;
	}
	SetColor(7);

}

void Viewer::showPromoteBoard(const vector<Piece*>& chess, int target) {
	system("cls");
	cout << endl << "possible path:\n" << "投降請輸入 surrender" << endl << "跳出此局遊戲請輸入 exit" << endl << endl;
	cout << " \\x ０１２３４５６７\n";
	cout << "y   ----------------\n";

	char board[8][8];
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			board[i][j] = ' ';
		}
	}
	for (int i = 0; i < chess.size(); i++) {
		//升階
		if (i == target) {
			board[chess[i]->getPos().x][chess[i]->getPos().y] = 'm';
		}
		//白棋
		else if (chess[i]->getFirstMove()) {
			if (chess[i]->getType() == 1) {
				board[chess[i]->getPos().x][chess[i]->getPos().y] = 'K';
			}
			else if (chess[i]->getType() == 2) {
				board[chess[i]->getPos().x][chess[i]->getPos().y] = 'Q';
			}
			else if (chess[i]->getType() == 3) {

				board[chess[i]->getPos().x][chess[i]->getPos().y] = 'B';
			}
			else if (chess[i]->getType() == 4) {
				board[chess[i]->getPos().x][chess[i]->getPos().y] = 'R';
			}
			else if (chess[i]->getType() == 5) {
				board[chess[i]->getPos().x][chess[i]->getPos().y] = 'N';
			}
			else if (chess[i]->getType() == 6) {
				board[chess[i]->getPos().x][chess[i]->getPos().y] = 'P';

			}

		}
		//黑棋
		else {
			if (chess[i]->getType() == 1) {
				board[chess[i]->getPos().x][chess[i]->getPos().y] = 'k';
			}
			else if (chess[i]->getType() == 2) {
				board[chess[i]->getPos().x][chess[i]->getPos().y] = 'q';
			}
			else if (chess[i]->getType() == 3) {

				board[chess[i]->getPos().x][chess[i]->getPos().y] = 'b';
			}
			else if (chess[i]->getType() == 4) {
				board[chess[i]->getPos().x][chess[i]->getPos().y] = 'r';
			}
			else if (chess[i]->getType() == 5) {
				board[chess[i]->getPos().x][chess[i]->getPos().y] = 'n';
			}
			else if (chess[i]->getType() == 6) {
				board[chess[i]->getPos().x][chess[i]->getPos().y] = 'p';

			}
		}
	}
	for (int i = 0; i < 8; i++) {
		cout << i << "|  ";
		for (int j = 0; j < 8; j++) {
			if (board[j][i] == 'm') {
				SetColor(236);
				cout << "兵";
			}
			else if (board[j][i] == ' ') {
				if ((j + i) % 2 == 0) {
					SetColor(111);
				}
				else {
					SetColor(143);
				}
				cout << "  ";
			}
			else if (board[j][i] >= 'A' && board[j][i] <= 'Z') {
				if ((j + i) % 2 == 0) {
					SetColor(111);
				}
				else {
					SetColor(143);
				}
				if (board[j][i] == 'K') {
					cout << "王";
				}
				else if (board[j][i] == 'Q') {
					cout << "后";
				}
				else if (board[j][i] == 'B') {
					cout << "主";
				}
				else if (board[j][i] == 'N') {
					cout << "騎";
				}
				else if (board[j][i] == 'R') {
					cout << "城";
				}
				else if (board[j][i] == 'P') {
					cout << "兵";
				}
			}
			else {
				if ((j + i) % 2 == 0) {
					SetColor(96);
				}
				else {
					SetColor(128);
				}
				if (board[j][i] == 'k') {
					cout << "王";
				}
				else if (board[j][i] == 'q') {
					cout << "后";
				}
				else if (board[j][i] == 'b') {
					cout << "主";
				}
				else if (board[j][i] == 'n') {
					cout << "騎";
				}
				else if (board[j][i] == 'r') {
					cout << "城";
				}
				else if (board[j][i] == 'p') {
					cout << "兵";
				}
			}
		}
		SetColor(7);
		cout << endl;
	}
	SetColor(7);
	cout << "What kind of chess you want to promote to be\n"
		<< "1 for queen\n"
		<< "2 for bishop\n"
		<< "3 for rook\n"
		<< "4 for knight\n";
}

void Viewer::showBoard(const vector<Piece*>& chess, int current_player) {
	char tmp;
	system("cls");
	if (current_player == 1) {
		cout << "white's turn\n";
	}
	else if (current_player == 0) {
		cout << "black's turn\n";
	}
	else {
		cout << endl;
	}
	cout << "投降請輸入 surrender" << endl << "跳出此局遊戲請輸入 exit" << endl << endl;
	cout << " \\x ０１２３４５６７\n";
	cout << "y   ----------------\n";

	char board[8][8];
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			board[i][j] = ' ';
		}
	}
	for (int i = 0; i < chess.size(); i++) {
		//白棋
		if (chess[i]->getFirstMove()) {
			if (chess[i]->getType() == 1) {
				board[chess[i]->getPos().x][chess[i]->getPos().y] = 'K';
			}
			else if (chess[i]->getType() == 2) {
				board[chess[i]->getPos().x][chess[i]->getPos().y] = 'Q';
			}
			else if (chess[i]->getType() == 3) {

				board[chess[i]->getPos().x][chess[i]->getPos().y] = 'B';
			}
			else if (chess[i]->getType() == 4) {
				board[chess[i]->getPos().x][chess[i]->getPos().y] = 'R';
			}
			else if (chess[i]->getType() == 5) {
				board[chess[i]->getPos().x][chess[i]->getPos().y] = 'N';
			}
			else if (chess[i]->getType() == 6) {
				board[chess[i]->getPos().x][chess[i]->getPos().y] = 'P';

			}

		}
		//黑棋
		else {
			if (chess[i]->getType() == 1) {
				board[chess[i]->getPos().x][chess[i]->getPos().y] = 'k';
			}
			else if (chess[i]->getType() == 2) {
				board[chess[i]->getPos().x][chess[i]->getPos().y] = 'q';
			}
			else if (chess[i]->getType() == 3) {

				board[chess[i]->getPos().x][chess[i]->getPos().y] = 'b';
			}
			else if (chess[i]->getType() == 4) {
				board[chess[i]->getPos().x][chess[i]->getPos().y] = 'r';
			}
			else if (chess[i]->getType() == 5) {
				board[chess[i]->getPos().x][chess[i]->getPos().y] = 'n';
			}
			else if (chess[i]->getType() == 6) {
				board[chess[i]->getPos().x][chess[i]->getPos().y] = 'p';

			}
		}
	}
	for (int i = 0; i < 8; i++) {
		cout << i << "|  ";
		for (int j = 0; j < 8; j++) {
			if (board[j][i] == ' ') {
				if ((j + i) % 2 == 0) {
					SetColor(111);
				}
				else {
					SetColor(143);
				}
				cout << "  ";
			}
			else if (board[j][i] >= 'A' && board[j][i] <= 'Z') {
				if ((j + i) % 2 == 0) {
					SetColor(111);
				}
				else {
					SetColor(143);
				}
				if (board[j][i] == 'K') {
					cout << "王";
				}
				else if (board[j][i] == 'Q') {
					cout << "后";
				}
				else if (board[j][i] == 'B') {
					cout << "主";
				}
				else if (board[j][i] == 'N') {
					cout << "騎";
				}
				else if (board[j][i] == 'R') {
					cout << "城";
				}
				else if (board[j][i] == 'P') {
					cout << "兵";
				}
			}
			else {
				if ((j + i) % 2 == 0) {
					SetColor(96);
				}
				else {
					SetColor(128);
				}
				if (board[j][i] == 'k') {
					cout << "王";
				}
				else if (board[j][i] == 'q') {
					cout << "后";
				}
				else if (board[j][i] == 'b') {
					cout << "主";
				}
				else if (board[j][i] == 'n') {
					cout << "騎";
				}
				else if (board[j][i] == 'r') {
					cout << "城";
				}
				else if (board[j][i] == 'p') {
					cout << "兵";
				}
			}
		}
		SetColor(7);
		cout << endl;
	}
	SetColor(7);
}