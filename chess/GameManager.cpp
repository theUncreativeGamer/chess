#pragma once
#include"GameManager.h"
#include<iostream>
#include<vector>
#include<string>
using namespace std;

// 這個物件應該是用來管理en passent權限的
// 每個pair中第一個值為剛一次走兩格的小兵的位置，第二個值則為這個位置的左邊或右邊。
// 我不曉得原本寫這段code的人是有什麼人格障礙，不過事到如今我也懶得修了
vector<pair<Vector2i, Vector2i>> thunder;

int GameManager::showMenu() {
	system("cls");
	int choice = 0;
	cout << "選擇模式\n"
		<< "1:玩家對玩家\n"
		<< "2:玩家對電腦\n"
		<< "3:離開遊戲\n";
	cin >> choice;
	while (choice < 1 || choice > 3) {
		system("cls");
		cout << "錯誤選項\n";
		system("pause");
		system("cls");
		cout << "選擇模式\n"
			<< "1:玩家對玩家\n"
			<< "2:玩家對電腦\n"
			<< "3:離開遊戲\n";
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
	// 一、將死
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

	// 二、棋數過少
	if (chess.size() < 5)
	{
		// king 0, queem 1, bishop 2, rook 3, knight 4, pawn 5
		vector<int> countType(6, 0);
		for (auto it : chess)
		{
			countType[it->getType() - 1] += 1;
		}

		// 1) 一王對一王
		if (chess.size() == 2)
		{
			return 1;
		}
		// 2) 一王對一王一騎士  or   3) 一王對一王一主教
		else if (chess.size() == 3)
		{
			if (countType[Type::knight - 1] == 1 || countType[Type::bishop - 1] == 1)
			{
				return 1;
			}
		}
		// 4) 一王一主教對一王一主教，且兩方主教在相同顏色的棋格上(座標相加之和 偶數為白 基數為黑)。
		else if (chess.size() == 4 && countType[Type::bishop - 1] == 2)
		{
			// bool Exist, bool onBlackSquare; 
			pair<bool, bool> white, black{ false,false };
			for (auto it : chess)
			{
				if (it->getType() == Type::bishop)
				{
					//先手為白方主教
					if (it->getFirstMove() == true)
					{
						white.first = true;
						white.second = (it->getPos().x + it->getPos().y) % 2;
					}
					//黑方主教
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

	// 三、無子可動

	 //將全部可移動的步數重新統計 
	allChessWalk.resize(chess.size());
	int wKing = 0;
	int bKing = 0;
	for (int i = 0; i < chess.size(); i++)
	{
		//國王額外做
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
	//國王放到最後做
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
			//不同陣營
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


	//白  收集完國王的要把有可能會自殺的步數去掉
	for (int i = 0; i < allChessWalk[wKing].size(); i++)
	{
		for (int j = 0; j < allChessWalk.size(); j++)
		{
			for (int k = 0; k < allChessWalk[j].size(); k++)
			{
				// 陣營不同 且 符合位置 則 
				if (chess[wKing]->getFirstMove() != chess[j]->getFirstMove() &&
					allChessWalk[wKing][i].x == allChessWalk[j][k].x && allChessWalk[wKing][i].y == allChessWalk[j][k].y)
				{
					//表示國王可能自殺 去掉 並跳代i那 繼續檢查
					allChessWalk[wKing].erase(allChessWalk[wKing].begin() + i);
					i--;
					j = allChessWalk.size();
					break;
				}
			}
		}
	}

	// 黑  收集完國王的要把有可能會自殺的步數去掉
	for (int i = 0; i < allChessWalk[bKing].size(); i++)
	{
		for (int j = 0; j < allChessWalk.size(); j++)
		{
			for (int k = 0; k < allChessWalk[j].size(); k++)
			{
				//  陣營不同 且 符合位置 則 
				if (chess[bKing]->getFirstMove() != chess[j]->getFirstMove() &&
					allChessWalk[bKing][i].x == allChessWalk[j][k].x && allChessWalk[bKing][i].y == allChessWalk[j][k].y)
				{
					//表示國王可能自殺 去掉 並跳代i那 繼續檢查
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

	// 步驟1 將棋子放在對應的位置上
	Vector2i nextPiecePosition(0, 0);
	while (input >> nextChar)
	{
		// 進入下一個步驟
		if (nextChar == ' ')
		{
			break;
		}

		// 切換到下一行
		if (nextChar == '/')
		{
			nextPiecePosition.y += 1;
			nextPiecePosition.x = 0;
			continue;
		}

		// 保留空格
		if (nextChar >= '1' && nextChar <= '8')
		{
			nextPiecePosition.x += (nextChar - '0');
			continue;
		}

		// 格式錯誤
		if (nextPiecePosition.x > 8 || nextPiecePosition.y > 8)
		{
			SetChessSyntaxError();
			return;
		}

		// 生成棋子
		switch (nextChar)
		{
		case 'P':
			// 白色 小兵
			chess.push_back(new Pawn(nextPiecePosition, 1));
			break;
		case 'R':
			// 白色 城堡
			chess.push_back(new Rook(nextPiecePosition, 1));
			break;
		case 'N':
			// 白色 騎士
			chess.push_back(new Knight(nextPiecePosition, 1));
			break;
		case 'B':
			// 白色 主教
			chess.push_back(new Bishop(nextPiecePosition, 1));
			break;
		case 'Q':
			// 白色 皇后
			chess.push_back(new Queen(nextPiecePosition, 1));
			break;
		case 'K':
			// 白色 國王
			chess.push_back(new King(nextPiecePosition, 1));
			break;
		case 'p':
			// 黑色 小兵
			chess.push_back(new Pawn(nextPiecePosition, 0));
			break;
		case 'r':
			// 黑色 城堡
			chess.push_back(new Rook(nextPiecePosition, 0));
			break;
		case 'n':
			// 黑色 騎士
			chess.push_back(new Knight(nextPiecePosition, 0));
			break;
		case 'b':
			// 黑色 主教
			chess.push_back(new Bishop(nextPiecePosition, 0));
			break;
		case 'q':
			// 黑色 皇后
			chess.push_back(new Queen(nextPiecePosition, 0));
			break;
		case 'k':
			// 黑色 國王
			chess.push_back(new King(nextPiecePosition, 0));
			break;
		default:
			SetChessSyntaxError();
			return;
		}
		/*
		cout << "生成了一個" << chess.back()->getType() << "號在位置"
			<< "(" << chess.back()->getPos().x << "," << chess.back()->getPos().y << ")\n";
		*/
		nextPiecePosition.x += 1;
	}

	// 步驟2 決定當前為哪一個玩家的回合
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
	

	// 步驟3 決定入堡權限
	{
		Piece* wqr = GetChessPiece({ 0,0 }); // 白色 靠近皇后的 城堡
		Piece* wkr = GetChessPiece({ 7,0 }); // 白色 靠近國王的 城堡
		Piece* bqr = GetChessPiece({ 0,7 }); // 黑色 靠近皇后的 城堡
		Piece* bkr = GetChessPiece({ 7,7 }); // 黑色 靠近國王的 城堡

		// 若找到的棋子不是對應顏色的城堡則忽略
		if (wqr != nullptr && (!(wqr->getType() == Type::rook) || !(wqr->getFirstMove() == 1)))
			wqr = nullptr;
		if (wkr != nullptr && (!(wkr->getType() == Type::rook) || !(wkr->getFirstMove() == 1)))
			wkr = nullptr;
		if (bqr != nullptr && (!(bqr->getType() == Type::rook) || !(bqr->getFirstMove() == 0)))
			bqr = nullptr;
		if (bkr != nullptr && (!(bkr->getType() == Type::rook) || !(bkr->getFirstMove() == 0)))
			bkr = nullptr;

		// 將找到的城堡設為「已經移動過」（即「無法入堡」）
		if (wqr != nullptr) wqr->hasMoved = true;
		if (wkr != nullptr) wkr->hasMoved = true;
		if (bqr != nullptr) bqr->hasMoved = true;
		if (bkr != nullptr) bkr->hasMoved = true;

		// 把對應的城堡設為「可以」
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
	
	// 步驟4 決定En Passent權限
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

	// 這裡本來應該還要載入「距離上次有意義之操作的回合數」作為判定平局的依據，可是原始碼好像沒做到這一塊，就先不做了。
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

	for (int i = 0; i < 8; i++) {	//加入白棋
		chess[i] = new Pawn(Vector2i{ 0,0 }, 1);
	}
	for (int i = 16; i < 24; i++) {	//加入黑棋
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
	cout << "FEN代碼格式有誤。將使用預設值生成盤面。\n";
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
	bool flag = 0; //看有沒有選到下隻小兵


	cout << "which chess you want to move (x,y)\n";
	while (cin >> option) {
		if (option == "surrender") { //投降
			return 1;
		}
		else if (option == "exit") { //跳出遊戲
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
			//吃過路兵
			possible = allChessWalk[target];

			if (chess[target]->getFirstMove()) //白棋
			{
				for (int i = 0; i < thunder.size(); i++)
				{
					if (from.x == thunder[i].second.x && from.y == thunder[i].second.y) //第二個為可以用吃過路兵的棋子 第一個為被吃棋子的紀錄
					{
						flag = 1;
						Vector2i EnPassant;
						EnPassant.x = thunder[i].first.x;
						EnPassant.y = thunder[i].first.y - 1;
						possible.push_back(EnPassant);
					}
				}
			}
			else if (!chess[target]->getFirstMove()) //黑棋
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


			//沒有可移動的地方
			if (possible.size() == 0) {
				cout << "棋子沒地方走\n";
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
		if (chess[target]->getType() == Type::pawn) //如果選的是小兵
		{
			if (abs(to.y - from.y) == 2) //如果在前進兩隔的情況 
			{
				Vector2i temp = to;
				temp.x = temp.x + 1; //右邊
				if (temp.x > -1 && temp.x < 8 && temp.y > -1 && temp.y < 8)
				{
					target2 = findOtherChess(temp);
					if (target2 != -1)
					{
						if (chess[target2]->getType() == Type::pawn && chess[target]->getFirstMove() != chess[target2]->getFirstMove()) //如果右邊是小兵且兩者顏色不同
						{
							pair<Vector2i, Vector2i> En;
							En.first = to;
							En.second = temp;
							thunder.push_back(En);
						}
					}
				}

				Vector2i temp2 = to;
				temp2.x = temp2.x - 1; //左邊
				if (temp2.x > -1 && temp2.x < 8 && temp2.y > -1 && temp2.y < 8)
				{
					target3 = findOtherChess(temp2);
					if (target3 != -1)
					{
						if (chess[target3]->getType() == Type::pawn && chess[target]->getFirstMove() != chess[target3]->getFirstMove()) //如果右邊是小兵且兩者顏色不同
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
				if (chess[target]->getFirstMove()) //白色
				{
					for (int i = 0; i < possible.size(); i++)
					{
						if (to.x == possible[i].x && to.y == possible[i].y) //找到吃過路兵的位置
						{
							Vector2i temp;
							temp.x = possible[i].x;
							temp.y = possible[i].y + 1;
							int kill = findOtherChess(temp);
							chess.erase(chess.begin() + kill);
						}
					}
				}
				else if (!chess[target]->getFirstMove()) //黑色
				{
					for (int i = 0; i < possible.size(); i++)
					{
						if (to.x == possible[i].x && to.y == possible[i].y) //找到吃過路兵的位置
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
			cout << "悔棋嗎? (y/n)\n";
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
				//交換玩家
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
		// 為小兵 且 (白方兵至底線 或 黑方兵 至底線)
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

