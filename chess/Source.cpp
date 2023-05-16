#include "GameManager.h"
#include<vector>
#include<iostream>
#include<string>
using namespace std;
int showRecord(vector<GameManager> record, vector<string> file_name);

int battleMenu();

int main() {
	Vector2i from, to;
	GameManager gm;
	int option, file_number, current_game, choice;
	vector<GameManager> record;
	vector<string>  record_name;
	string tmp;

	record.clear();

	while (1) {
		option = gm.showMenu();
		if (option == 1 || option == 2) {
			while (1) {
				option = battleMenu();
				if (option == 1) {	//�s�C��
					record.push_back(gm);
					record_name.push_back(tmp);
					current_game = record.size() - 1;
					record[record.size() - 1].setChess();
					system("cls");
					cout << "��ܶ©Υե���\n"
						<< "1: �¥�\n"
						<< "2: �ե�\n";
					cin >> option;
					if (option == 1) {
						record[current_game].setCurrent_player(0);
					}
					break;
				}
				else if (option == 2) {	//���J�C��
					
					if (record.size() == 0) {
						system("cls");
						cout<<"�ثe�L�C�����\n"
							<<"�жi��s�C��\n"
							<< "��J���N����H�~��......\n";
						getchar();
						getchar();
						continue;
					}
					current_game = showRecord(record, record_name) - 1;
					
					
					
				}
				else if (option == 3)
				{
					cout << "�п�JFEN�N�X\n";
					string fen;
					getline(cin, fen);
					getline(cin, fen);
					record.push_back(gm);
					record_name.push_back(tmp);
					current_game = record.size() - 1;
					record[record.size() - 1].setChess(fen);

					break;
				}
			}
		}
		else if (option == 3) {
			break;
		}
		record[current_game].showBoard();
		while (record[current_game ].isOver() == 0) {
			choice = record[current_game].moveChess();
			if (choice == 1) {	//�뭰
				system("cls");
				if (record[current_game].getCurrent_player() == 1) {
					cout << "�¤����!!\n"
						<< "��J���N����H�~��......\n";
					getchar();
					getchar();
					record.erase(record.begin() + current_game, record.begin() + current_game + 1);	//�R�������C��
					record_name.erase(record_name.begin() + current_game, record_name.begin() + current_game + 1);
					break;
				}
				else {
					cout << "�դ����!!\n"
						<< "��J���N����H�~��......\n";
					getchar();
					getchar();
					record.erase(record.begin() + current_game, record.begin() + current_game + 1);	//�R�������C��
					record_name.erase(record_name.begin() + current_game, record_name.begin() + current_game + 1);
					break;
				}
			}
			else if (choice == 2) {	//�� game
				system("cls");
				cout << "��J�C�����x�s���ɦW:\n";
				getchar();
				getline(cin, tmp);
				//cin >> tmp;
				record_name[current_game] = tmp;
				break;
			}
			if (record[current_game].isOver() == 2) {
				cout << "�¤����!!\n"
					<< "��J���N����H�~��......\n";
				getchar();
				getchar();
				record.erase(record.begin() + current_game, record.begin() + current_game + 1);	//�R�������C��
				record_name.erase(record_name.begin() + current_game, record_name.begin() + current_game + 1);
				break;
			}
			else if (record[current_game].isOver() == 3) {
				cout << "�դ����!!\n"
					<< "��J���N����H�~��......\n";
				getchar();
				getchar();
				record.erase(record.begin() + current_game, record.begin() + current_game + 1);	//�R�������C��
				record_name.erase(record_name.begin() + current_game, record_name.begin() + current_game + 1);
				break;
			}
			else if (record[current_game].isOver() == 1) {
				cout << "����!!\n"
					<< "��J���N����H�~��......\n";
				getchar();
				getchar();
				record.erase(record.begin() + current_game, record.begin() + current_game + 1);	//�R�������C��
				record_name.erase(record_name.begin() + current_game, record_name.begin() + current_game + 1);
				break;
			}
			record[current_game].whichNeedPromote();
			record[current_game].showBoard();
		}
	}
}

int showRecord(vector<GameManager> record,vector<string> file_name) {
	system("cls");
	cout << "��ܧA�n���J���C��\n";
	for (int i = 0; i < record.size(); i++) {
		cout << i + 1 <<"."<<file_name[i] << endl;
	}
	
	int option;
	cin >> option;
	while (1) {
		if (option >= 1 || option <= record.size()) {
			return option;
		}
	}
}

int battleMenu() {
	system("cls");
	cout << "�аݭn�i��s�C���άO���J�C������?\n"
		<< "1: �s�C��\n"
		<< "2: ���J�C��\n"
		<< "3: ���JFEN�N�X\n";

	int option;
	cin >> option;
	return option;
}

int whoFirst() {
	system("cls");
	cout << "�֥��� ?\n"
		<< "1: �¤�\n"
		<< "2: �դ�\n";
	int option;
	cin >> option;
	return option;
}