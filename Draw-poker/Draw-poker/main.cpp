#include <iostream>
#include <windows.h>
#include <time.h>
#include <iomanip>
#include <string>
#include "cards.h"

int main() {
	srand(time(NULL));
	COORD cursor; //для отслеживания позиции курсора
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
		for (int card = 1; card <= 5; card++) {
			std::string buf; //буферная строка для выделения отдельных чисел
			changeC* new_card; //адрес на новый номер карты для замены

			//отыскиваем пробелы в строке
			int pos = numbers.find(" ");
			if (pos == -1) { //если пробелов нет
				if (numbers == "") {
					if (replayChange(player_change) == -1) { 
						std::cout << "Please, enter the different numbers of cards!" << std::endl;
						getline(std::cin, numbers, '\n');
						card = 0;
						continue;
					}
					break;
				}
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
		changeCard(deck, user, &issued_cards, player_change); //замена карт, которые выбрал пользователь

		//вывод карт игроков
		std::cout << std::endl << std::setw(20) << "        You";
		for (int i = 1; i <= num_bot; i++) {
			std::string bot = "       Bot" + std::to_string(i);
			std::cout << std::setw(20) << bot;
		}
		std::cout << std::endl;
		cursor = getConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE)); //получение координат до вывода карт игроков
		printCards(user);
		for (int bot = 1; bot <= num_bot; bot++) {

			//смещение курсора на столбец следующего игрока
			cursor.X += 20;
			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cursor);

			//коипрование карт бота во временный массив
			int temp_card_bot[5][2];
			for (int i = 0; i < 5; i++) {
				temp_card_bot[i][0] = card_bots[bot - 1][i][0];
				temp_card_bot[i][1] = card_bots[bot - 1][i][1];
			}
			printCards(temp_card_bot);
		}

		//возвращение курсора в начало строки со спуском на строку вниз
		cursor = getConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE));
		cursor.X = 0;
		cursor.Y += 1;
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cursor);



		//освобождение памяти, выделенную под ботов, после окончание игры
		for (int bot = 0; bot < num_bot; bot++) {
			for (int cards = 0; cards < 5; cards++)
				delete card_bots[bot][cards];
			delete card_bots[bot];
		}
	}
	return 0;
}