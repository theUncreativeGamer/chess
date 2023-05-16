#include"ViewManager.h"
void ViewManager::SetColor(int color)
{
	HANDLE hConsole;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, color);
}

void ViewManager::showBoard(const vector<Piece*>& chess, int current_player, int check) {
	system("cls");
	if (current_player == 1) {
		cout << "�դ�^�X\n";
	}
	else if (current_player == 0) {
		cout << "�¤�^�X\n";
	}
	else {
		cout << endl;
	}
	cout << "�뭰�п�J surrender" << endl << "���X�����C���п�J exit" << endl;
	if (check != 0) {
		cout << "�N�x!!\n";
	}
	cout << "\\ x ���������\n";
	cout << "y   ----------------\n";

	char board[8][8];
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			board[i][j] = ' ';
		}
	}
	for (int i = 0; i < chess.size(); i++) {
		//�մ�
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
		//�´�
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
				cout << "��";
			}
			else if (board[j][i] == 'G') {
				SetColor(207);
				cout << "��";
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
					cout << "��";
				}
				else if (board[j][i] == 'Q') {
					cout << "�Z";
				}
				else if (board[j][i] == 'B') {
					cout << "�D";
				}
				else if (board[j][i] == 'N') {
					cout << "�M";
				}
				else if (board[j][i] == 'R') {
					cout << "��";
				}
				else if (board[j][i] == 'P') {
					cout << "�L";
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
					cout << "��";
				}
				else if (board[j][i] == 'q') {
					cout << "�Z";
				}
				else if (board[j][i] == 'b') {
					cout << "�D";
				}
				else if (board[j][i] == 'n') {
					cout << "�M";
				}
				else if (board[j][i] == 'r') {
					cout << "��";
				}
				else if (board[j][i] == 'p') {
					cout << "�L";
				}
			}
		}
		SetColor(7);
		cout << endl;
	}
	SetColor(7);
}

void ViewManager::showAllPath(vector<Piece*> chess, const vector<Vector2i>& posssible) {
	system("cls");
	cout << "�i�������|:\n" << "�뭰�п�J surrender" << endl << "���X�����C���п�J exit" << endl << endl;
	cout << "\\ x ���������\n";
	cout << "y   ----------------\n";

	char board[8][8];
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			board[i][j] = ' ';
		}
	}

	for (int i = 0; i < chess.size(); i++) {
		//�մ�
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
		//�´�
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

	//�[�J�i����|
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
				cout << "��";
			}
			else if (board[j][i] >= '1' && board[j][i] <= '6') {
				SetColor(207);
				if (board[j][i] == '1') {
					cout << "��";
				}
				else if (board[j][i] == '2') {
					cout << "�Z";
				}
				else if (board[j][i] == '3') {
					cout << "�D";
				}
				else if (board[j][i] == '4') {
					cout << "��";
				}
				else if (board[j][i] == '5') {
					cout << "�M";
				}
				else if (board[j][i] == '6') {
					cout << "�L";
				}
			}
			//�մ�
			else if (board[j][i] >= 'A' && board[j][i] <= 'Z') {
				if ((j + i) % 2 == 0) {
					SetColor(111);
				}
				else {
					SetColor(143);
				}
				if (board[j][i] == 'K') {
					cout << "��";
				}
				else if (board[j][i] == 'Q') {
					cout << "�Z";
				}
				else if (board[j][i] == 'B') {
					cout << "�D";
				}
				else if (board[j][i] == 'N') {
					cout << "�M";
				}
				else if (board[j][i] == 'R') {
					cout << "��";
				}
				else if (board[j][i] == 'P') {
					cout << "�L";
				}
			}
			//�´�
			else {
				if ((j + i) % 2 == 0) {
					SetColor(96);
				}
				else {
					SetColor(128);
				}
				if (board[j][i] == 'k') {
					cout << "��";
				}
				else if (board[j][i] == 'q') {
					cout << "�Z";
				}
				else if (board[j][i] == 'b') {
					cout << "�D";
				}
				else if (board[j][i] == 'n') {
					cout << "�M";
				}
				else if (board[j][i] == 'r') {
					cout << "��";
				}
				else if (board[j][i] == 'p') {
					cout << "�L";
				}
			}
		}
		SetColor(7);
		cout << endl;
	}
	SetColor(7);

}

void ViewManager::showPromoteBoard(const vector<Piece*>& chess, int target) {
	system("cls");
	cout << endl << "�i�������|:\n" << "�뭰�п�J surrender" << endl << "���X�����C���п�J exit" << endl << endl;
	cout << "\\ x ����������\n";
	cout << "y   ----------------\n";

	char board[8][8];
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			board[i][j] = ' ';
		}
	}
	for (int i = 0; i < chess.size(); i++) {
		//�ɶ�
		if (i == target) {
			board[chess[i]->getPos().x][chess[i]->getPos().y] = 'm';
		}
		//�մ�
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
		//�´�
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
				cout << "�L";
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
					cout << "��";
				}
				else if (board[j][i] == 'Q') {
					cout << "�Z";
				}
				else if (board[j][i] == 'B') {
					cout << "�D";
				}
				else if (board[j][i] == 'N') {
					cout << "�M";
				}
				else if (board[j][i] == 'R') {
					cout << "��";
				}
				else if (board[j][i] == 'P') {
					cout << "�L";
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
					cout << "��";
				}
				else if (board[j][i] == 'q') {
					cout << "�Z";
				}
				else if (board[j][i] == 'b') {
					cout << "�D";
				}
				else if (board[j][i] == 'n') {
					cout << "�M";
				}
				else if (board[j][i] == 'r') {
					cout << "��";
				}
				else if (board[j][i] == 'p') {
					cout << "�L";
				}
			}
		}
		SetColor(7);
		cout << endl;
	}
	SetColor(7);
	cout << "��ܭn�ɶ������Ѥl:\n"
		<< "1: �ӦZ\n"
		<< "2: �D��\n"
		<< "3: ����\n"
		<< "4: �M�h\n";
}

void ViewManager::showBoard(const vector<Piece*>& chess, int current_player) {
	char tmp;
	system("cls");
	if (current_player == 1) {
		cout << "�դ�^�X\n";
	}
	else if (current_player == 0) {
		cout << "�¤�^�X\n";
	}
	else {
		cout << endl;
	}
	cout << "�뭰�п�J surrender" << endl << "���X�����C���п�J exit" << endl << endl;
	cout << "\\ x ���������\n";
	cout << "y   ----------------\n";

	char board[8][8];
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			board[i][j] = ' ';
		}
	}
	for (int i = 0; i < chess.size(); i++) {
		//�մ�
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
		//�´�
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
					cout << "��";
				}
				else if (board[j][i] == 'Q') {
					cout << "�Z";
				}
				else if (board[j][i] == 'B') {
					cout << "�D";
				}
				else if (board[j][i] == 'N') {
					cout << "�M";
				}
				else if (board[j][i] == 'R') {
					cout << "��";
				}
				else if (board[j][i] == 'P') {
					cout << "�L";
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
					cout << "��";
				}
				else if (board[j][i] == 'q') {
					cout << "�Z";
				}
				else if (board[j][i] == 'b') {
					cout << "�D";
				}
				else if (board[j][i] == 'n') {
					cout << "�M";
				}
				else if (board[j][i] == 'r') {
					cout << "��";
				}
				else if (board[j][i] == 'p') {
					cout << "�L";
				}
			}
		}
		SetColor(7);
		cout << endl;
	}
	SetColor(7);
}