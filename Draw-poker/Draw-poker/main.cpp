#include <iostream>
#include <string>
#include "cards.h"

//функция для удаления подстроки из строки
std::string removeAll(std::string str, const std::string& from) {
	size_t start_pos = 0;
	while ((start_pos = str.find(from)) != std::string::npos) {
		str.erase(start_pos, from.length());
	}
	return str;
}

int main() {
	testChooseChange();
	std::string comb, cont = "Yes";

	int deck[52][2]; //первый индекс - номер карты, второй: 0 - масть, 1 - номинал
	int user[5][2]; //карты пользователя
	int*** card_bots; //указатель на карты ботов
	int num_bot, issued_cards; //количество ботов и счетчик выданных карт

	while (cont != "NO") {

		//инициализация и тасование колоды карт
		deckInit(deck);
		deckShuffle(deck);

		issued_cards = 0;

		//ввод количества ботов
		std::cout << "Number of bots (>=4 and <=1): ";
		std::cin >> num_bot;
		std::cin.clear();
		std::cin.ignore(std::cin.rdbuf()->in_avail());
		while (num_bot < 1 || num_bot > 4) {
			std::cout << "Enter the correct number" << std::endl;
			std::cin >> num_bot;
			std::cin.clear();
			std::cin.ignore(std::cin.rdbuf()->in_avail());
		}

		//создание ботов
		card_bots = new int** [num_bot];
		for (int bot = 0; bot < num_bot; bot++) {
			card_bots[bot] = new int* [5];
			for (int cards = 0; cards < 5; cards++)
				card_bots[bot][cards] = new int[2];
		}

		std::cout << "Game draw-poker has started" << std::endl;

		//раздача карт игрокам
		deal(deck, user, &issued_cards);
		for (int bot = 0; bot < num_bot; bot++) {
			int tmp_bot_card[5][2]; //буферный массив для раздачи карт ботам 
			deal(deck, tmp_bot_card, &issued_cards);
			for (int i = 0; i < 5; i++) {
				card_bots[bot][i][0] = tmp_bot_card[i][0];
				card_bots[bot][i][1] = tmp_bot_card[i][1];
			}
		}

		//круг замены карт у игроков
		changeC *player_change = new changeC;
		std::string numbers = ""; //строка для хранения вводимых значений
		//вывод карт пользователя на текущий момент
		std::cout << "    Your cards" << std::endl;
		printCards(user);
		std::cout << std::endl << "Numbers of the cards that you want to change separate by a space (key \"enter\" is the end of input): ";
		getline(std::cin, numbers, '\n');
		for (int card = 1; card <= 5 && numbers != ""; card++) {
			std::string buf; //буферная строка для выделения отдельных чисел
			changeC* new_card; //адрес на новый номер карты для замены

			//отыскиваем пробелы в строке
			int pos = numbers.find(" ");
			if (pos == -1) { //если пробелов нет
				if (numbers == "")
					break;
				buf = numbers;
				numbers.clear();
			}
			else {
				buf.assign(numbers, 0, pos);
				numbers.erase(0, pos + 1);
			}
			if (numbers == "")
				new_card = NULL;
			else
				new_card = new changeC;
			if (addChange(buf, player_change, new_card) == -1) {
				std::cout << "Please, enter the correct numbers of card." << std::endl;
				deleteChange(player_change);
				card = 1;
				getline(std::cin, numbers, '\n');
			}
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