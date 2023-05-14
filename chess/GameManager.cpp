#pragma once
#include"GameManager.h"
#include<iostream>
#include<vector>
#include<string>
using namespace std;

// �o�Ӫ������ӬO�ΨӺ޲zen passent�v����
// �C��pair���Ĥ@�ӭȬ���@������檺�p�L����m�A�ĤG�ӭȫh���o�Ӧ�m������Υk��C
// �ڤ���o�쥻�g�o�qcode���H�O������H���ê�A���L�ƨ�p���ڤ]�i�o�פF
vector<pair<Vector2i, Vector2i>> thunder;

int GameManager::showMenu() {
	system("cls");
	int choice = 0;
	cout << "��ܼҦ�\n"
		<< "1:���a�缾�a\n"
		<< "2:���a��q��\n"
		<< "3:���}�C��\n";
	cin >> choice;
	while (choice < 1 || choice > 3) {
		system("cls");
		cout << "���~�ﶵ\n";
		system("pause");
		system("cls");
		cout << "��ܼҦ�\n"
			<< "1:���a�缾�a\n"
			<< "2:���a��q��\n"
			<< "3:���}�C��\n";
		cin >> choice;
	}
	return choice;
}

void GameManager::showBoard() {
	if (check != 0) {
		this->viewer.showBoard(chess, current_player, check);
	}
	else {
		this->viewer.showBoard(chess, current_player);
	}
}

int GameManager::isOver()
{
	int victory = 0;
	// �@�B�N��
	int countKing = 0;

	for (int i = 0; i < chess.size(); i++)
	{
		if (chess[i]->getType() == Type::king && chess[i]->getFirstMove())
		{
			countKing += 1;
			victory = 3;
		}
		if (chess[i]->getType() == Type::king && !chess[i]->getFirstMove())
		{
			victory = 2;
			countKing += 1;
		}
	}
	if (countKing != 2)
	{
		return victory;
	}

	// �G�B�ѼƹL��
	if (chess.size() < 5)
	{
		// king 0, queem 1, bishop 2, rook 3, knight 4, pawn 5
		vector<int> countType(6, 0);
		for (auto it : chess)
		{
			countType[it->getType() - 1] += 1;
		}

		// 1) �@����@��
		if (chess.size() == 2)
		{
			return 1;
		}
		// 2) �@����@���@�M�h  or   3) �@����@���@�D��
		else if (chess.size() == 3)
		{
			if (countType[Type::knight - 1] == 1 || countType[Type::bishop - 1] == 1)
			{
				return 1;
			}
		}
		// 4) �@���@�D�й�@���@�D�СA�B���D�Цb�ۦP�C�⪺�Ѯ�W(�y�Ьۥ[���M ���Ƭ��� ��Ƭ���)�C
		else if (chess.size() == 4 && countType[Type::bishop - 1] == 2)
		{
			// bool Exist, bool onBlackSquare; 
			pair<bool, bool> white, black{ false,false };
			for (auto it : chess)
			{
				if (it->getType() == Type::bishop)
				{
					//���⬰�դ�D��
					if (it->getFirstMove() == true)
					{
						white.first = true;
						white.second = (it->getPos().x + it->getPos().y) % 2;
					}
					//�¤�D��
					else
					{
						black.first = true;
						black.second = (it->getPos().x + it->getPos().y) % 2;
					}

				}
			}
			if (white.first && black.first && white.second == black.second)
			{
				return 1;
			}
		}
	}

	// �T�B�L�l�i��

	 //�N�����i���ʪ��B�ƭ��s�έp 
	allChessWalk.resize(chess.size());
	int wKing = 0;
	int bKing = 0;
	for (int i = 0; i < chess.size(); i++)
	{
		//����B�~��
		if (chess[i]->getType() == Type::king && chess[i]->getFirstMove() == true)
		{
			wKing = i;
			continue;
		}
		if (chess[i]->getType() == Type::king && chess[i]->getFirstMove() == false)
		{
			bKing = i;
			continue;
		}
		vector<Vector2i> tmp = chess[i]->collectWalk(chess, i);
		allChessWalk[i] = tmp;
	}
	//������̫ᰵ
	allChessWalk[wKing] = chess[wKing]->collectWalk(chess, wKing);
	allChessWalk[bKing] = chess[bKing]->collectWalk(chess, bKing);

	//*********************************************************
	//if (check == 1 &&)
	//{

	//}
	//else if (check)
	//{

	//}

	/************************************************************/

	{
		check = 0;
		int curKingIndex = 0;
		Vector2i kingPos;
		if (this->current_player)
		{
			kingPos = chess[wKing]->getPos();
			curKingIndex = wKing;
		}
		else
		{
			kingPos = chess[bKing]->getPos();
			curKingIndex = bKing;
		}
		for (int i = 0; i < allChessWalk.size(); i++)
		{
			//���P�}��
			if (chess[i]->getFirstMove() != chess[curKingIndex]->getFirstMove())
			{
				for (int j = 0; j < allChessWalk[i].size(); j++)
				{
					if (allChessWalk[i][j].x == kingPos.x && allChessWalk[i][j].y == kingPos.y)
					{
						check = pow(-1, (1 + this->current_player));
						i = allChessWalk.size();
						break;
					}
				}
			}
		}
	}


	//��  ������������n�⦳�i��|�۱����B�ƥh��
	for (int i = 0; i < allChessWalk[wKing].size(); i++)
	{
		for (int j = 0; j < allChessWalk.size(); j++)
		{
			for (int k = 0; k < allChessWalk[j].size(); k++)
			{
				// �}�礣�P �B �ŦX��m �h 
				if (chess[wKing]->getFirstMove() != chess[j]->getFirstMove() &&
					allChessWalk[wKing][i].x == allChessWalk[j][k].x && allChessWalk[wKing][i].y == allChessWalk[j][k].y)
				{
					//��ܰ���i��۱� �h�� �ø��Ni�� �~���ˬd
					allChessWalk[wKing].erase(allChessWalk[wKing].begin() + i);
					i--;
					j = allChessWalk.size();
					break;
				}
			}
		}
	}

	// ��  ������������n�⦳�i��|�۱����B�ƥh��
	for (int i = 0; i < allChessWalk[bKing].size(); i++)
	{
		for (int j = 0; j < allChessWalk.size(); j++)
		{
			for (int k = 0; k < allChessWalk[j].size(); k++)
			{
				//  �}�礣�P �B �ŦX��m �h 
				if (chess[bKing]->getFirstMove() != chess[j]->getFirstMove() &&
					allChessWalk[bKing][i].x == allChessWalk[j][k].x && allChessWalk[bKing][i].y == allChessWalk[j][k].y)
				{
					//��ܰ���i��۱� �h�� �ø��Ni�� �~���ˬd
					allChessWalk[bKing].erase(allChessWalk[bKing].begin() + i);
					i--;
					j = allChessWalk.size();
					break;
				}
			}
		}
	}

	bool couldWalk = false;
	for (vector<Vector2i> it : allChessWalk)
	{
		if (it.size() != 0)
		{
			couldWalk = true;
			break;
		}
	}
	// isnt over
	if (couldWalk)
	{
		return 0;
	}
	// is over
	else
	{
		return 1;
	}
}

void GameManager::setChess(const string& inputText) {
	
	if (inputText == "")
	{
		OriginalSetChess();
		return;
	}

	stringstream input(inputText);
	input >> std::noskipws; // don't skip whitespace
	char nextChar = '\0';

	// �B�J1 �N�Ѥl��b��������m�W
	Vector2i nextPiecePosition(0, 0);
	while (input >> nextChar)
	{
		// �i�J�U�@�ӨB�J
		if (nextChar == ' ')
		{
			break;
		}

		// ������U�@��
		if (nextChar == '/')
		{
			nextPiecePosition.y += 1;
			nextPiecePosition.x = 0;
			continue;
		}

		// �O�d�Ů�
		if (nextChar >= '1' && nextChar <= '8')
		{
			nextPiecePosition.x += (nextChar - '0');
			continue;
		}

		// �榡���~
		if (nextPiecePosition.x > 8 || nextPiecePosition.y > 8)
		{
			SetChessSyntaxError();
			return;
		}

		// �ͦ��Ѥl
		switch (nextChar)
		{
		case 'P':
			// �զ� �p�L
			chess.push_back(new Pawn(nextPiecePosition, 1));
			break;
		case 'R':
			// �զ� ����
			chess.push_back(new Rook(nextPiecePosition, 1));
			break;
		case 'N':
			// �զ� �M�h
			chess.push_back(new Knight(nextPiecePosition, 1));
			break;
		case 'B':
			// �զ� �D��
			chess.push_back(new Bishop(nextPiecePosition, 1));
			break;
		case 'Q':
			// �զ� �ӦZ
			chess.push_back(new Queen(nextPiecePosition, 1));
			break;
		case 'K':
			// �զ� ���
			chess.push_back(new King(nextPiecePosition, 1));
			break;
		case 'p':
			// �¦� �p�L
			chess.push_back(new Pawn(nextPiecePosition, 0));
			break;
		case 'r':
			// �¦� ����
			chess.push_back(new Rook(nextPiecePosition, 0));
			break;
		case 'n':
			// �¦� �M�h
			chess.push_back(new Knight(nextPiecePosition, 0));
			break;
		case 'b':
			// �¦� �D��
			chess.push_back(new Bishop(nextPiecePosition, 0));
			break;
		case 'q':
			// �¦� �ӦZ
			chess.push_back(new Queen(nextPiecePosition, 0));
			break;
		case 'k':
			// �¦� ���
			chess.push_back(new King(nextPiecePosition, 0));
			break;
		default:
			SetChessSyntaxError();
			return;
		}
		/*
		cout << "�ͦ��F�@��" << chess.back()->getType() << "���b��m"
			<< "(" << chess.back()->getPos().x << "," << chess.back()->getPos().y << ")\n";
		*/
		nextPiecePosition.x += 1;
	}

	// �B�J2 �M�w��e�����@�Ӫ��a���^�X
	{
		input >> nextChar;
		switch (nextChar)
		{
		case 'b':
			current_player = 0;
			break;
		case 'w':
			current_player = 1;
			break;
		default:
			SetChessSyntaxError();
			return;
		}
		input.ignore();
	}
	

	// �B�J3 �M�w�J���v��
	{
		Piece* wqr = GetChessPiece({ 0,0 }); // �զ� �a��ӦZ�� ����
		Piece* wkr = GetChessPiece({ 7,0 }); // �զ� �a������ ����
		Piece* bqr = GetChessPiece({ 0,7 }); // �¦� �a��ӦZ�� ����
		Piece* bkr = GetChessPiece({ 7,7 }); // �¦� �a������ ����

		// �Y��쪺�Ѥl���O�����C�⪺�����h����
		if (wqr != nullptr && (!(wqr->getType() == Type::rook) || !(wqr->getFirstMove() == 1)))
			wqr = nullptr;
		if (wkr != nullptr && (!(wkr->getType() == Type::rook) || !(wkr->getFirstMove() == 1)))
			wkr = nullptr;
		if (bqr != nullptr && (!(bqr->getType() == Type::rook) || !(bqr->getFirstMove() == 0)))
			bqr = nullptr;
		if (bkr != nullptr && (!(bkr->getType() == Type::rook) || !(bkr->getFirstMove() == 0)))
			bkr = nullptr;

		// �N��쪺�����]���u�w�g���ʹL�v�]�Y�u�L�k�J���v�^
		if (wqr != nullptr) wqr->hasMoved = true;
		if (wkr != nullptr) wkr->hasMoved = true;
		if (bqr != nullptr) bqr->hasMoved = true;
		if (bkr != nullptr) bkr->hasMoved = true;

		// ������������]���u�i�H�v
		for (bool endLoop = false; input >> nextChar;)
		{
			switch (nextChar)
			{
			case ' ':
			case '-':
				endLoop = true;
				break;
			case 'Q':
				if (wqr != nullptr) wqr->hasMoved = false;
				break;
			case 'K':
				if (wkr != nullptr) wkr->hasMoved = false;
				break;
			case 'q':
				if (bqr != nullptr) bqr->hasMoved = false;
				break;
			case 'k':
				if (bkr != nullptr) bkr->hasMoved = false;
				break;
			default:
				SetChessSyntaxError();
				return;
			}
			if (endLoop) break;
		}

		if (input.peek() == ' ')input.ignore();
	}
	
	// �B�J4 �M�wEn Passent�v��
	input >> nextChar;
	if (!nextChar == '-')
	{
		char tempChar;
		input >> tempChar;
		if (nextChar < 'a' || nextChar>'h' || !(tempChar == '3' || tempChar == '6'))
		{
			SetChessSyntaxError();
			return;
		}
		Vector2i enPassentPosition(nextChar - 'a', tempChar - '1');
		if (enPassentPosition.y == 2) enPassentPosition.y += 1;
		else enPassentPosition.y -= 1;
		thunder.push_back(pair<Vector2i, Vector2i>(enPassentPosition, Vector2i(enPassentPosition.x + 1, enPassentPosition.y)));
		thunder.push_back(pair<Vector2i, Vector2i>(enPassentPosition, Vector2i(enPassentPosition.x - 1, enPassentPosition.y)));
	}

	// �o�̥��������٭n���J�u�Z���W�����N�q���ާ@���^�X�ơv�@���P�w�������̾ڡA�i�O��l�X�n���S����o�@���A�N�������F�C
}

int GameManager::findWhichChess(Vector2i p) {
	for (int i = 0; i < chess.size(); i++) {
		if (chess[i]->getFirstMove() == current_player && chess[i]->getPos().x == p.x && chess[i]->getPos().y == p.y) {
			return i;
		}
	}
	return -1;
}

int GameManager::findWhichChess(Vector2i p, int a) {
	for (int i = 0; i < chess.size(); i++) {
		if (chess[i]->getPos().x == p.x && chess[i]->getPos().y == p.y) {
			return i;
		}
	}
	return -1;
}

int GameManager::findOtherChess(Vector2i p)
{
	for (int i = 0; i < chess.size(); i++) {
		if (chess[i]->getFirstMove() != current_player && chess[i]->getPos().x == p.x && chess[i]->getPos().y == p.y) {
			return i;
		}
	}
	return -1;
}

void GameManager::OriginalSetChess()
{
	chess.resize(32);

	for (int i = 0; i < 8; i++) {	//�[�J�մ�
		chess[i] = new Pawn(Vector2i{ 0,0 }, 1);
	}
	for (int i = 16; i < 24; i++) {	//�[�J�´�
		chess[i] = new Pawn(Vector2i{ 0,0 }, 0);
	}

	for (int i = 0; i < 8; i++) {
		chess[i]->setType(6);
		chess[i]->setPos(Vector2i{ i,6 });
	}
	//chess[0]->setPos(pos{ 0,2 });	//test
	for (int i = 16; i < 24; i++) {
		chess[i]->setType(6);
		chess[i]->setPos(Vector2i{ i - 16,1 });
	}
	//chess[16]->setPos(pos{ 0,3 });	//test
	//chess[18]->setPos(pos{ 2,5 });

	//rook
	chess[8] = new Rook(Vector2i{ 0,0 }, 1);
	chess[9] = new Rook(Vector2i{ 0,0 }, 1);
	chess[24] = new Rook(Vector2i{ 0,0 }, 0);
	chess[25] = new Rook(Vector2i{ 0,0 }, 0);

	chess[8]->setPos(Vector2i{ 0,7 });
	chess[9]->setPos(Vector2i{ 7,7 });
	chess[24]->setPos(Vector2i{ 0,0 });
	chess[25]->setPos(Vector2i{ 7,0 });

	//chess[24]->setPos(pos{ 1,2 });

	//knight
	chess[10] = new Knight(Vector2i{ 0,0 }, 1);
	chess[11] = new Knight(Vector2i{ 0,0 }, 1);
	chess[26] = new Knight(Vector2i{ 0,0 }, 0);
	chess[27] = new Knight(Vector2i{ 0,0 }, 0);

	chess[10]->setPos(Vector2i{ 1,7 });
	chess[11]->setPos(Vector2i{ 6,7 });
	chess[26]->setPos(Vector2i{ 1,0 });
	chess[27]->setPos(Vector2i{ 6,0 });

	//bishop
	chess[12] = new Bishop(Vector2i{ 0,0 }, 1);
	chess[13] = new Bishop(Vector2i{ 0,0 }, 1);
	chess[28] = new Bishop(Vector2i{ 0,0 }, 0);
	chess[29] = new Bishop(Vector2i{ 0,0 }, 0);

	chess[12]->setPos(Vector2i{ 2,7 });
	chess[13]->setPos(Vector2i{ 5,7 });
	chess[28]->setPos(Vector2i{ 2,0 });
	chess[29]->setPos(Vector2i{ 5,0 });

	//queen
	chess[14] = new Queen(Vector2i{ 0,0 }, 1);
	chess[30] = new Queen(Vector2i{ 0,0 }, 0);

	chess[14]->setPos(Vector2i{ 3,7 });
	chess[30]->setPos(Vector2i{ 3,0 });

	//king
	chess[15] = new King(Vector2i{ 0,0 }, 1);
	chess[31] = new King(Vector2i{ 0,0 }, 0);

	chess[15]->setPos(Vector2i{ 4,7 });
	chess[31]->setPos(Vector2i{ 4,0 });

	/*chess.resize(5);
	chess[0] = new King(pos{4,1}, 1);
	chess[1] = new King(pos{7,1 }, 0);
	chess[2] = new Pawn(pos{0,5},1);
	chess[3] = new Pawn(pos{ 0,4 }, 0);
	chess[4] = new Bishop(pos{6,1},1);*/
}

inline void GameManager::SetChessSyntaxError()
{
	cout << "FEN�N�X�榡���~�C�N�ϥιw�]�ȥͦ��L���C\n";
	for (Piece* c : chess)
	{
		delete c;
	}
	chess.clear();
	OriginalSetChess();
	return;
}

inline Piece* GameManager::GetChessPiece(Vector2i position)
{
	for (Piece* p : chess)
	{
		if (p->getPos() == position)
			return p;
	}
	return nullptr;
}



int GameManager::moveChess() {
	Vector2i from, og, eaten;
	int target = -1, eaten_type, eat;
	int amount_before, amount_after;
	string option;
	vector<Vector2i> possible;
	possible.clear();
	Piece* tmp;
	bool flag = 0; //�ݦ��S�����U���p�L


	cout << "which chess you want to move (x,y)\n";
	while (cin >> option) {
		if (option == "surrender") { //�뭰
			return 1;
		}
		else if (option == "exit") { //���X�C��
			return 2;
		}
		else if (!isNumber(option)) {
			cout << "Invalid input\n"
				<< "enter again!!\n";
			cin >> option;
		}
		from.x = stoi(option);
		cin >> from.y;
		og.x = from.x;	og.y = from.y;	//for undo redo
		target = findWhichChess(from);
		if (target == -1) {
			cout << "wrong position\n"
				<< "enter again!!\n";
		}
		else {
			//�Y�L���L
			possible = allChessWalk[target];

			if (chess[target]->getFirstMove()) //�մ�
			{
				for (int i = 0; i < thunder.size(); i++)
				{
					if (from.x == thunder[i].second.x && from.y == thunder[i].second.y) //�ĤG�Ӭ��i�H�ΦY�L���L���Ѥl �Ĥ@�Ӭ��Q�Y�Ѥl������
					{
						flag = 1;
						Vector2i EnPassant;
						EnPassant.x = thunder[i].first.x;
						EnPassant.y = thunder[i].first.y - 1;
						possible.push_back(EnPassant);
					}
				}
			}
			else if (!chess[target]->getFirstMove()) //�´�
			{
				for (int i = 0; i < thunder.size(); i++)
				{
					if (from.x == thunder[i].second.x && from.y == thunder[i].second.y)
					{
						flag = 1;
						Vector2i EnPassant;
						EnPassant.x = thunder[i].first.x;
						EnPassant.y = thunder[i].second.y + 1;
						possible.push_back(EnPassant);
					}
				}
			}
			if (flag == 0)
			{
				thunder.clear();
			}


			//�S���i���ʪ��a��
			if (possible.size() == 0) {
				cout << "�Ѥl�S�a�訫\n";
				continue;
			}
			else {
				break;
			}
		}
	}

	this->viewer.showAllPath(chess, possible);

	cout << "Enter which position you want to the chess to (x,y)\n";
	Vector2i to;
	while (cin >> to.x >> to.y) {
		eaten.x = to.x;	eaten.y = to.y;
		amount_before = chess.size();
		eat = findWhichChess(to, 1);
		if (eat != -1) {
			eaten_type = chess[eat]->getType();
		}
		int target2, target3;
		if (chess[target]->getType() == Type::pawn) //�p�G�諸�O�p�L
		{
			if (abs(to.y - from.y) == 2) //�p�G�b�e�i��j�����p 
			{
				Vector2i temp = to;
				temp.x = temp.x + 1; //�k��
				if (temp.x > -1 && temp.x < 8 && temp.y > -1 && temp.y < 8)
				{
					target2 = findOtherChess(temp);
					if (target2 != -1)
					{
						if (chess[target2]->getType() == Type::pawn && chess[target]->getFirstMove() != chess[target2]->getFirstMove()) //�p�G�k��O�p�L�B����C�⤣�P
						{
							pair<Vector2i, Vector2i> En;
							En.first = to;
							En.second = temp;
							thunder.push_back(En);
						}
					}
				}

				Vector2i temp2 = to;
				temp2.x = temp2.x - 1; //����
				if (temp2.x > -1 && temp2.x < 8 && temp2.y > -1 && temp2.y < 8)
				{
					target3 = findOtherChess(temp2);
					if (target3 != -1)
					{
						if (chess[target3]->getType() == Type::pawn && chess[target]->getFirstMove() != chess[target3]->getFirstMove()) //�p�G�k��O�p�L�B����C�⤣�P
						{
							pair<Vector2i, Vector2i> En;
							En.first = to;
							En.second = temp2;
							thunder.push_back(En);
						}
					}
				}
			}
		}
		if (player[current_player]->onMove(chess, possible, to, chess[target])) {
			if (flag == 1)
			{
				if (chess[target]->getFirstMove()) //�զ�
				{
					for (int i = 0; i < possible.size(); i++)
					{
						if (to.x == possible[i].x && to.y == possible[i].y) //���Y�L���L����m
						{
							Vector2i temp;
							temp.x = possible[i].x;
							temp.y = possible[i].y + 1;
							int kill = findOtherChess(temp);
							chess.erase(chess.begin() + kill);
						}
					}
				}
				else if (!chess[target]->getFirstMove()) //�¦�
				{
					for (int i = 0; i < possible.size(); i++)
					{
						if (to.x == possible[i].x && to.y == possible[i].y) //���Y�L���L����m
						{
							Vector2i temp;
							temp.x = possible[i].x;
							temp.y = possible[i].y - 1;
							int kill = findOtherChess(temp);
							chess.erase(chess.begin() + kill);
						}
					}
				}
			}
			viewer.showBoard(chess, current_player);
			cout << "���Ѷ�? (y/n)\n";
			char regret;
			cin >> regret;
			if (regret == 'y') {
				if (amount_before > chess.size()) {
					if (current_player == 1) {
						current_player = 0;
					}
					else {
						current_player = 1;
					}
					if (eaten_type == 1) {
						tmp = new King(eaten, current_player);
					}
					else if (eaten_type == 2) {
						tmp = new Queen(eaten, current_player);
					}
					else if (eaten_type == 3) {
						tmp = new Bishop(eaten, current_player);
					}
					else if (eaten_type == 4) {
						tmp = new Rook(eaten, current_player);
					}
					else if (eaten_type == 5) {
						tmp = new  Knight(eaten, current_player);
					}
					else if (eaten_type == 6) {
						tmp = new Pawn(eaten, current_player);
					}
					if (current_player == 1) {
						current_player = 0;
					}
					else {
						current_player = 1;
					}
					chess.insert(chess.begin() + eat + 1, tmp);
					
				}
				chess[target]->setPos(og);
			}
			else {
				//�洫���a
				if (current_player == 1) {
					current_player = 0;
				}
				else {
					current_player = 1;
				}
			}

			return 0;
		}
		else {
			this->viewer.showAllPath(chess, possible);
			cout << "Invalid input enter again!!\n";
		}
	}

	return 0;
}

void GameManager::whichNeedPromote() {
	for (int i = 0; i < chess.size(); i++) {
		// ���p�L �B (�դ�L�ܩ��u �� �¤�L �ܩ��u)
		if (chess[i]->getType() == Type::pawn &&
			((chess[i]->getPos().y == 0 && chess[i]->getFirstMove() == true) ||
				(chess[i]->getPos().y == 7 && chess[i]->getFirstMove() == false)))
		{
			viewer.showPromoteBoard(chess, i);
			int type;
			cin >> type;
			player[current_player]->onPromote(chess, i, Type(type-1));
			return;
		}
	}
	return;
}

bool GameManager::isNumber(string input) {

	for (int i = 0; i < input.size(); i++) {
		if (input[i] < '0' || input[i]>'9') {
			return false;
		}
	}

	return true;
}

