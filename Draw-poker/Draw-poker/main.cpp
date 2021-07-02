#include <iostream>

//структура отвечающая за одну карту
struct card {
	char* suit_card;
	char* nomanal_card;
};

int main() {
	const char* suit[] = { "Hearts", "Diamond", "Spades", "Club" }; //указатели на названия масти карт
	const char* nominal[] = { "Two", "Three", "Four", "Five", "Six", "Seven", "Eight", "Nine", "Ten",
							  "Jack", "Queen", "King", "Ace" }; //указатели на номиналы карт


	return 0;
}