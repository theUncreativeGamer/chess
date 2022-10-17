#pragma once
#include"Player.h"
#include"Viewer.h"
#include"Chess.h"
#include<vector>
using namespace std;
class GameManager {
public:
	GameManager() {
		current_player = 1;
		chess.clear();
	}
	//bool keepPlay();	//提供玩家選擇是否在玩一把
	int showMenu();	//顯示主選單
	void showBoard();	//將棋盤顯示出來
	//vector<pos> showPath(Board board,int current_player, struct pos p);	//檢查可移動路徑
	//void update();	//更新棋盤
	//void setBoard();	//建立棋盤
	int isOver();	//檢查遊戲是否結束 //3 白被將軍 2黑被將軍 1和局 0未結束
	void setChess();	//將旗子位置初始化
	int findWhichChess(pos p);	//找輸入位置的旗子是哪個
	int findWhichChess(pos p, int a);
	int moveChess();	//動旗子
	void whichNeedPromote();	//找有沒有旗子需要promote
	bool isNumber(string input);
	int getCurrent_player() { return current_player; }
	int  getCheck() { return check; }
	void setCheck(int _check) { check = _check; }
	int findOtherChess(pos p);
	void setCurrent_player(int current_player) { this->current_player = current_player; }


private:
	Player* player[2];
	int current_player;
	Viewer viewer;
	vector<Piece*> chess;
	int check = 0;	//1 白被將軍 -1黑被將軍
	vector<vector<pos>>allChessWalk;
};
