#pragma once
#include"Chess.h"
#include<ctime>
#include"Viewer.h"
class Player {
public:
	// p為目標位置
	bool onMove(vector<Piece*>& chesses, const vector<Vector2i>& possibilities, Vector2i p, Piece* chess) {

		for (const Vector2i& pos : possibilities) {
			if (p == pos) {

				//若要移動到的位置有棋子 則吃掉
				for (Piece*& it : chesses)
				{
					if (it->getPos() == p)
					{
						chesses.erase(find(chesses.begin(), chesses.end(), it));
						break;
					}
				}
				chess->setPos(p);
				chess->hasMoved = true;
				return true;
			}
		}

		return false; //非法移動
	}
	void onPromote(vector<Piece*>& chess, int index, Type option)
	{
		Vector2i _pos = chess[index]->getPos();
		chess.erase(chess.begin() + index);
		Piece* tmp;
		switch (option)
		{
		case Type::bishop:
			//主教的建構式

			tmp = new Bishop(_pos, chess[index]->getFirstMove());
			chess.push_back(tmp);
			break;
		case Type::rook:
			tmp = new Rook(_pos, chess[index]->getFirstMove());
			chess.push_back(tmp);
			break;
		case Type::queen:
			tmp = new Queen(_pos, chess[index]->getFirstMove());
			chess.push_back(tmp);
			break;
		case Type::knight:
			tmp = new Knight(_pos, chess[index]->getFirstMove());
			chess.push_back(tmp);
			break;
		}
	}
private:
	Viewer viewer;
};