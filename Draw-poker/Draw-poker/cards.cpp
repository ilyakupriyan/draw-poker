#include <iostream>
#include <time.h>
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
const char* nominal[] = { "Deuce", "Three", "Four", "Five", "Six", "Seven", "Eight", "Nine", "Ten",
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
	cout << "Test printCards is running" << endl;
	cout << "There should be: three of hearts, five of diamond, six of spades, eight, jack of club, ace of spades" << endl;

	int cards[5][2] = { {1, 0}, {3, 1}, {4, 2}, {9, 3}, {12, 2} }; //тройка черви, пять бубны, шесть пики, валет крести, туз пики
	printCards(cards);

	cout << "Enter any key to continue";
	_getch();
}

//функция инициализации колоды в -1 для дальнейшего тасования
void deckInit(int deck[][2]) {
	for (int card = 0; card <= 51; card++) {
		deck[card][0] = -1;
		deck[card][1] = -1;
	}
}

//функция перемешивания колоды карт из 52 карт
void deckShuffle(int deck[][2]) {
	srand(time(NULL));

	int suit = 0, nom = 0;

	for (int card = 0; card <= 51; card++) {
		suit = rand() % 3;
		nom = rand() % 12;

		while (deck[card][0] == nom || deck[card][1] == suit) {
			suit = rand() % 3;
			nom = rand() % 12;
		}
		deck[card][0] = nom;
		deck[card][1] = suit;
	}
}

//функция теста deckShuffle()
int testDeckShuffle() {

	//инициализация и тасование колоды карт
	int deck[52][2];
	
	for (int crd = 0; crd <= 51; crd++) {
		deck[crd][0] = -2;
		deck[crd][1] = -2;
	}

	deckShuffle(deck);

	for (int i = 0; i <= 51; i++) {
		if (deck[i][0] == -2 || deck[i][1] == -2)
			return -1;
	}
	return 0;
}
