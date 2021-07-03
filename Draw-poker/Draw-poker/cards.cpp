#include <iostream>
#include <iomanip>
#include <conio.h>

using namespace std;

//структура отвечающая за одну карту
struct card {
	char* suit_card;
	char* nomanal_card;
	card* next_card;
};

const char* suit[] = { "Hearts", "Diamond", "Spades", "Club" }; //указатели на названия масти карт
const char* nominal[] = { "Two", "Three", "Four", "Five", "Six", "Seven", "Eight", "Nine", "Ten",
						  "Jack", "Queen", "King", "Ace" }; //указатели на номиналы карт

//функция вывода карт одного игрока
void printCards(int const cards[][2]) {
	for (int i = 0; i <= 4; i++) {
		cout << setw(7) << right << nominal[cards[i][0]] << " of "
			 << setw(9) << left << suit[cards[i][1]] << endl;
	}
}

//тест на правильный вывод карт одного игрока
void testPrintCards() {
	cout << "There should be: three of hearts, five of diamond, six of spades, eight, jack of club, ace of spades" << endl;
	int cards[5][2] = { {1, 0}, {3, 1}, {4, 2}, {9, 3}, {12, 2} }; //тройка черви, пять бубны, шесть пики, валет крести, туз пики
	printCards(cards);
	cout << "Enter any key to continue";
	_getch();
}
