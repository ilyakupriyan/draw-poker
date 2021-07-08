#include <iostream>
#include <string>
#include <windows.h>
#include <iomanip>
#include <conio.h>

using namespace std;

//структура для замены карт игрока
struct changeC {
	int card = 0;
	changeC* next_card = NULL;
};

const char* suit[] = { "Hearts", "Diamond", "Spades", "Club" }; //указатели на названия масти карт
const char* nominal[] = { "Deuce", "Three", "Four", "Five", "Six", "Seven", "Eight", "Nine", "Ten",
						  "Jack", "Queen", "King", "Ace" }; //указатели на номиналы карт

//функция получения координат курсора (для printCards)
COORD getConsoleCursorPosition(HANDLE hConsoleOutput)
{
	CONSOLE_SCREEN_BUFFER_INFO cbsi;
	if (GetConsoleScreenBufferInfo(hConsoleOutput, &cbsi))
	{
		return cbsi.dwCursorPosition;
	}
	else
	{
		// The function failed. Call GetLastError() for details.
		COORD invalid = { 0, 0 };
		return invalid;
	}
}

//функция вывода карт одного игрока
void printCards(int const cards[][2]) {
	COORD cursor = getConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE));
	for (int i = 0; i <= 4; i++) {
		cout << setw(7) << right << nominal[cards[i][0]] << " of "
			 << setw(9) << left << suit[cards[i][1]];
		cursor.Y += 1;
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cursor);
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

//функиця теста deckInit()
int testDeckInit() {
	int deck[52][2];
	deckInit(deck);
	for (int cards = 0; cards <= 51; cards++) {
		if (deck[cards][0] != -1 || deck[cards][1] != -1)
			return -1;
	}
	return 0;
}

//функция перемешивания колоды карт из 52 карт
void deckShuffle(int deck[][2]) {

	int suit = 0, nom = 0;
	int shuffling[4][13] = { 0 }; //для отслеживания повторений разданных карт
	for (int card = 0; card <= 51; card++) {
		suit = rand() % 4;
		nom = rand() % 13;
		while (shuffling[suit][nom] != 0) {
			suit = rand() % 4;
			nom = rand() % 13;
		}
		shuffling[suit][nom] = 1;
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

//функция выдачи карт игроку из колоды
void deal(int deck[][2], int players_card[][2], int *issued_cards) {
	for (int i = 0; i < 5; i++, (*issued_cards)++) {
		players_card[i][0] = deck[*issued_cards][0];
		players_card[i][1] = deck[*issued_cards][1];
	}
}

//функиця добавления номера карты для замены
int addChange(std::string number, changeC* head, changeC* new_card) {
	changeC* copy = head;
	//если строка пустая, то прекратить выполнение функции
	if (number != "") {

		//ищем последний элемент списка и добавляем новый
		while (copy->next_card != NULL)
			copy = copy->next_card;
		copy->next_card = new_card;

		//проверка на ввод корректного числа
		for (int ch = 0; number[ch] != '\0'; ch++) {
			if (!isdigit(number[ch])) {
				return -1;
			}
		}

		int num = stoi(number);
		if (num > 5 || num < 1)
			return -1;
		copy->card = stoi(number);
	}
	return 0;
}

//функция теста ChooseChangeCard
void testChooseChange() {
	changeC *head;
	head = new changeC;
	//int test = chooseChange(head);
	//cout << test << endl;
	delete head;

}

//функция проверки на повторение номеров карт
int replayChange(changeC* head) {
	changeC* copy1 = head, *copy2 = head->next_card;
	while (copy1 == NULL) {
		copy2 = copy1->next_card;
		while (copy2 != NULL) {
			if (copy1->card == copy2->card) {
				return -1;
			}
			copy2 = copy2->next_card;
		}
		copy1 = copy1->next_card;
	} 
	return 0;
}

//функция замены карт
void changeCard(int deck[][2], int players_card[][2], int* issued_cards, changeC* player) {
	changeC* copy = player;
	while (copy != NULL) {
		players_card[copy->card - 1][0] = deck[*issued_cards][0];
		players_card[copy->card - 1][1] = deck[*issued_cards][1];
		(*issued_cards)++;
		copy = copy->next_card;
	}
}

//функция обнуления списка с номерами замен карт
void deleteChange(changeC* head) {
	while (head->next_card != NULL) {
		changeC* copy1 = head;
		changeC* copy2 = head;
		while (copy1->next_card != NULL)
			copy1 = copy1->next_card;
		while (copy2->next_card != copy1)
			copy2 = copy2->next_card;
		copy2->next_card = NULL;
		delete copy1;
	}
}