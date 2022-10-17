#pragma once
#include"Chess.h"
#include<iostream>
#include<Windows.h>
using namespace std;
class Viewer {
public:
	//顯示棋盤 包含將軍
	void showBoard(const vector<Piece*>& chess, int current_player, int check);
	//顯示棋盤 
	void showBoard(const vector<Piece*>& chess, int current_player);
	//顯示所有可能路徑
	void showAllPath(vector<Piece*> chess, const vector<pos>& posssible);
	//Promote時顯示的畫面
	void showPromoteBoard(const vector<Piece*>& chess, int target);
	//顯示動畫
	//void showWalkAni(char board[8][8],)
private:
	//設定輸出顏色
	void SetColor(int color);
};


