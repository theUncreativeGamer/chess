#pragma once
#include"Chess.h"
#include<iostream>
#include<Windows.h>
using namespace std;
class Viewer {
public:
	//��ܴѽL �]�t�N�x
	void showBoard(const vector<Piece*>& chess, int current_player, int check);
	//��ܴѽL 
	void showBoard(const vector<Piece*>& chess, int current_player);
	//��ܩҦ��i����|
	void showAllPath(vector<Piece*> chess, const vector<Vector2i>& posssible);
	//Promote����ܪ��e��
	void showPromoteBoard(const vector<Piece*>& chess, int target);
	//��ܰʵe
	//void showWalkAni(char board[8][8],)
private:
	//�]�w��X�C��
	void SetColor(int color);
};


