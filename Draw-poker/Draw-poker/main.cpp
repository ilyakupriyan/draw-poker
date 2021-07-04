#include <iostream>
#include <windows.h>
#include "cards.h"

int main() {
	std::string comb, cont = "Yes";

	//определение колоды карт
	int deck[52][2]; //первый индекс - номер карты, второй: 0 - масть, 1 - номинал

	int user[5][2]; //карты пользователя
	int*** card_bots; //указатель на карты ботов
	int num_bot;

	while (cont != "NO") {
		//инициализация и тасование колоды карт
		deckInit(deck);
		deckShuffle(deck);

		//ввод количества ботов
		std::cout << "Number of bots: ";
		std::cin >> num_bot;
		while (num_bot < 1 || num_bot > 4) {
			std::cout << "Number of bots should be between 1 and 4" << std::endl;
			std::cin >> num_bot;
		}

		//создание ботов
		card_bots = new int**[num_bot];
		for (int bot = 0; bot < num_bot; bot++) {
			card_bots[bot] = new int* [5];
			for (int cards = 0; cards < 5; cards++)
				card_bots[bot][cards] = new int[2];
		}




		//освобождение памяти, выделенную под ботов, после окончание игры
		for (int bot = 0; bot < num_bot; bot++) {
			for (int cards = 0; cards < 5; cards++)
				delete card_bots[bot][cards];
			delete card_bots[bot];
		}
	}
	
	return 0;
}