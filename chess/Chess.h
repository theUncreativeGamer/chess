#pragma once
#include<iostream>
#include<vector>
#include "Vector2i.h"

using namespace std;

enum Type {
	none = 0,
	king = 1,
	queen = 2,
	bishop = 3,
	rook = 4,
	knight = 5,
	pawn = 6
};

class Piece
{
public:
	Piece() { type = Type::none; position = { -1,-1 }; firstMove = false; }
	Piece(Vector2i _pos, bool _firstmove) { position = _pos; firstMove = _firstmove; }

	//set
	void setType(int _type) { type = _type; }
	void setPos(Vector2i _pos) { position = _pos; }
	void setFirstMove(bool _firstMove) { firstMove = _firstMove; }

	//get
	int getType() { return type; }
	Vector2i getPos() { return position; }
	bool getFirstMove() { return firstMove; }

	/**********************************************************************************/
	//收集棋盤上某隻棋 所有可位移的position   index表示為哪一個旗子
	virtual vector<Vector2i> collectWalk(vector<Piece*> allChess, int index) { vector<Vector2i>a; return a; }

	//判斷是否為邊界或上面有旗子  無棋2 有棋為己方棋0 有棋為敵方棋1
	int posCouldWalk(vector<Piece*>allChess, Vector2i checkPos, bool firstmove)
	{
		for (auto it : allChess)
		{
			Vector2i tmp = it->getPos();
			//此位置有棋子
			if (tmp.x == checkPos.x && tmp.y == checkPos.y)
			{
				//為己方棋
				if (firstmove == it->getFirstMove())
				{
					return 0;
				}
				//為敵方棋
				else
				{
					return 1;
				}
			}
		}
		//無棋子
		return 2;
	}
	/***************************************************************************************/
	//~Piece();
private:
	int type = Type::none;
	Vector2i position;
	bool firstMove;
};

class Bishop :public Piece
{
public:
	Bishop() : Piece()
	{
	}
	Bishop(Vector2i _pos, bool _firstmove) : Piece(_pos, _firstmove)
	{
		this->setType(Type::bishop);
	}
	vector<Vector2i> collectWalk(vector<Piece*> allChess, int index) override
	{
		vector<Vector2i>validPos;
		Vector2i _pos = allChess[index]->getPos();

		// lu ld ru rd
		vector<Vector2i> dirBase;
		Vector2i dir = { -1,-1 };
		dirBase.push_back(dir);
		dir = { -1, 1 };
		dirBase.push_back(dir);
		dir = { 1, -1 };
		dirBase.push_back(dir);
		dir = { 1, 1 };
		dirBase.push_back(dir);

		//collect all possible walk
		for (int i = 0; i < 8; i++)
		{
			bool yetDone = false;
			for (int j = 0; j < dirBase.size(); j++)
			{
				Vector2i tmp;
				tmp.x = _pos.x + (i + 1) * dirBase[j].x;
				tmp.y = _pos.y + (i + 1) * dirBase[j].y;

				//於地圖內
				if (tmp.x > -1 && tmp.x < 8 && tmp.y > -1 && tmp.y < 8)
				{
					// 有棋為己方棋0 有棋為敵方棋1 無棋2
					int infoPos = posCouldWalk(allChess, tmp, allChess[index]->getFirstMove());

					//無棋2
					if (infoPos == 2)
					{
						validPos.push_back(tmp);
						yetDone = true;
						continue;
					}
					//有棋為敵方棋1
					else if (infoPos == 1)
					{
						validPos.push_back(tmp);
						yetDone = true;
					}
				}
				dirBase.erase(dirBase.begin() + j);
				j--;
			}
			if (!yetDone)
			{
				break;
			}
		}
		return validPos;
	}

private:

};

class Rook :public Piece
{
public:
	Rook() : Piece()
	{
	}
	Rook(Vector2i _pos, bool _firstmove) : Piece(_pos, _firstmove)
	{
		this->setType(Type::rook);
	}
	vector<Vector2i> collectWalk(vector<Piece*> allChess, int index) override
	{
		vector<Vector2i>validPos;
		Vector2i _pos = allChess[index]->getPos();

		// l r u d
		vector<Vector2i> dirBase;
		Vector2i dir = { -1,0 };
		dirBase.push_back(dir);
		dir = { 1, 0 };
		dirBase.push_back(dir);
		dir = { 0, -1 };
		dirBase.push_back(dir);
		dir = { 0, 1 };
		dirBase.push_back(dir);


		//collect all possible walk
		for (int i = 0; i < 8; i++)
		{
			bool yetDone = false;
			for (int j = 0; j < dirBase.size(); j++)
			{
				Vector2i tmp;
				tmp.x = _pos.x + (i + 1) * dirBase[j].x;
				tmp.y = _pos.y + (i + 1) * dirBase[j].y;

				//於地圖內
				if (tmp.x > -1 && tmp.x < 8 && tmp.y > -1 && tmp.y < 8)
				{
					// 有棋為己方棋0 有棋為敵方棋1 無棋2
					int infoPos = posCouldWalk(allChess, tmp, allChess[index]->getFirstMove());

					//無棋2
					if (infoPos == 2)
					{
						validPos.push_back(tmp);
						yetDone = true;
						continue;
					}
					//有棋為敵方棋1
					else if (infoPos == 1)
					{
						validPos.push_back(tmp);
						yetDone = true;
					}
				}
				dirBase.erase(dirBase.begin() + j);
				j--;
			}
			if (!yetDone)
			{
				break;
			}
		}
		return validPos;
	}


private:

};

class Knight :public Piece
{
private:
public:
	Knight(Vector2i _pos, bool _firstmove) : Piece(_pos, _firstmove)
	{
		this->setType(Type::knight);
	}

	vector<Vector2i> collectWalk(vector<Piece*> allChess, int index) override
	{
		vector<Vector2i> validPos;
		Vector2i position = this->getPos(); //目前旗子位置
		//八個可能的位置
		Vector2i Base[8] = { {1,2 }, { 1,-2 },{-1,-2 },{-1,2},{2,1},{2,-1},{-2,1},{-2,-1} };

		for (int i = 0; i < 8; i++)
		{
			Vector2i tmp;
			tmp.x = position.x + Base[i].x;
			tmp.y = position.y + Base[i].y;

			//於地圖內
			if (tmp.x > -1 && tmp.x < 8 && tmp.y > -1 && tmp.y < 8)
			{
				//且此地為空 或 有棋但非己方棋 
				if (posCouldWalk(allChess, tmp, allChess[index]->getFirstMove()))
				{
					validPos.push_back(tmp);
				}
			}
		}
		return validPos; //最後將容器回傳回去
	}

};

class Queen :public Piece
{
public:
	Queen() : Piece()
	{
	}
	Queen(Vector2i _pos, bool _firstmove) : Piece(_pos, _firstmove)
	{
		this->setType(Type::queen);
	}
	vector<Vector2i> collectWalk(vector<Piece*> allChess, int index) override
	{
		vector<Vector2i>validPos;
		Vector2i _pos = allChess[index]->getPos();

		//lu ld ru rd   l r u d
		vector<Vector2i> dirBase;
		Vector2i dir = { -1,-1 };
		dirBase.push_back(dir);
		dir = { -1, 1 };
		dirBase.push_back(dir);
		dir = { 1, -1 };
		dirBase.push_back(dir);
		dir = { 1, 1 };
		dirBase.push_back(dir);

		dir = { -1,0 };
		dirBase.push_back(dir);
		dir = { 1, 0 };
		dirBase.push_back(dir);
		dir = { 0, -1 };
		dirBase.push_back(dir);
		dir = { 0, 1 };
		dirBase.push_back(dir);


		//collect all possible walk
		for (int i = 0; i < 8; i++)
		{
			bool yetDone = false;
			for (int j = 0; j < dirBase.size(); j++)
			{
				Vector2i tmp;
				tmp.x = _pos.x + (i + 1) * dirBase[j].x;
				tmp.y = _pos.y + (i + 1) * dirBase[j].y;

				//於地圖內
				if (tmp.x > -1 && tmp.x < 8 && tmp.y > -1 && tmp.y < 8)
				{
					// 有棋為己方棋0 有棋為敵方棋1 無棋2
					int infoPos = posCouldWalk(allChess, tmp, allChess[index]->getFirstMove());

					//無棋2
					if (infoPos == 2)
					{
						validPos.push_back(tmp);
						yetDone = true;
						continue;
					}
					//有棋為敵方棋1
					else if (infoPos == 1)
					{
						validPos.push_back(tmp);
						yetDone = true;
					}
				}
				dirBase.erase(dirBase.begin() + j);
				j--;
			}
			if (!yetDone)
			{
				break;
			}
		}
		return validPos;
	}

private:

};

//須包含吃過路兵  但吃過路兵是選擇性的，若要進行，就要在對方走棋後的下一步馬上進行，否則就失去機會。
//只能吃斜的 直得不能被擋
class Pawn :public Piece
{
private:
	/*bool En_passant = 0;
	pos eatPass;*/
public:

	Pawn(Vector2i _pos, bool _firstmove) : Piece(_pos, _firstmove)
	{
		this->setType(Type::pawn);
	}

	/*bool get_En()
	{
	 return this->En_passant;
	}*/

	/*void set_En(bool a)
	{
	 this->En_passant = a;
	}

	void set_eatPass(pos a)
	{
	 this->eatPass = a;
	}*/

	vector<Vector2i> collectWalk(vector<Piece*> allChess, int index) override
	{
		vector<Vector2i> validPos;
		Vector2i position = this->getPos(); //目前旗子位置

		vector<Vector2i> base;
		base.push_back({ 1,-1 });
		base.push_back({ -1,-1 });
		base.push_back({ 0,-1 });
		//兵走首步棋 考量可走二步
		if ((position.y == 1 && !this->getFirstMove()) || (position.y == 6 && this->getFirstMove()))
		{
			base.push_back({ 0,-2 });
		}
		//若為黑方 則改為往下走
		if (!this->getFirstMove())
		{
			for (auto& it : base)
			{
				it.y *= -1;
			}
		}

		Vector2i checkPos;
		//走斜 吃棋
		for (int i = 0; i < 2; i++)
		{
			checkPos.x = position.x + base[i].x;
			checkPos.y = position.y + base[i].y;
			//在地圖內
			if (checkPos.x > -1 && checkPos.x < 8 && checkPos.y > -1 && checkPos.y < 8)
			{
				//吃過路兵

				//查找所有棋子
				for (auto it : allChess)
				{
					Vector2i tmp = it->getPos();
					//是否此位置有棋子且為敵方棋可吃棋 代表可走
					if (tmp.x == checkPos.x && tmp.y == checkPos.y && it->getFirstMove() != this->getFirstMove())
					{
						validPos.push_back(checkPos);
						break;
					}
				}
			}
		}
		// 往前
		bool flag = 0; //檢查前方是否有棋子阻擋
		for (int i = 2; i < base.size(); i++)
		{
			checkPos.x = position.x + base[i].x;
			checkPos.y = position.y + base[i].y;
			//在地圖內
			if (checkPos.x > -1 && checkPos.x < 8 && checkPos.y > -1 && checkPos.y < 8)
			{
				//且此地為空 或 有敵方棋可吃 
				if (posCouldWalk(allChess, checkPos, allChess[index]->getFirstMove()) == 2)
				{
					validPos.push_back(checkPos);
				}
				else if (posCouldWalk(allChess, checkPos, allChess[index]->getFirstMove()) == 1)
				{
					if (i == 2)
					{
						flag = 1; //前方檔棋子
					}
					break;
				}
			}
			//if (this->En_passant == 1 && flag == 0)
			//{
			// if (this->getFirstMove()) //白
			// {
			//  pos temp = this->eatPass; //上個小兵的位置
			//  temp.y - 1;
			//  validPos.push_back(temp);
			// }
			// else if(!this->getFirstMove()) //黑
			// {
			//  pos temp = this->eatPass;
			//  temp.y + 1;
			//  validPos.push_back(temp);
			// }
			//}
		}



		return validPos; //最後將容器回傳回去
	}






};
class King :public Piece
{
private:

public:
	King() : Piece()
	{
	}
	King(Vector2i _pos, bool _firstmove) : Piece(_pos, _firstmove)
	{
		this->setType(Type::king);
	}

	vector<Vector2i> collectWalk(vector<Piece*> allChess, int index) override
	{
		vector<Vector2i>validPos;
		Vector2i _pos = allChess[index]->getPos();

		//lu ld ru rd l r u d
		Vector2i dirBase[8] = { {-1,-1 }, {-1, 1}, {1, -1}, {1, 1},{-1,0 }, {1, 0}, {0, -1}, {0, 1} };
		//collect all possible walk

		for (int i = 0; i < 8; i++)
		{
			Vector2i tmp;
			tmp.x = _pos.x + dirBase[i].x;
			tmp.y = _pos.y + dirBase[i].y;
			//於地圖內
			if (tmp.x > -1 && tmp.x < 8 && tmp.y > -1 && tmp.y < 8)
			{
				//且此地為空 或 有棋但非己方棋 
				if (posCouldWalk(allChess, tmp, allChess[index]->getFirstMove()))
				{
					validPos.push_back(tmp);
				}
			}
		}
		return validPos;
	}
	void Castling_Right(class Rook a)
	{
		if (this->getFirstMove() == 0 && a.getFirstMove() == 0) //如果兩個都沒移動過
		{

		}
	}
};