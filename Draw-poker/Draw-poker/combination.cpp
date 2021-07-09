#include <iostream>

const char* combination[] = { "High card", "Pair", "Two pairs", "Three of a kind", "Straight", "Flush", "Full house", "Four of a kind", "Straight flush", "Royal flush"}; //массив указателей на название комбинаций в порядке приоритета

//функция сортировки по возрастанию
void sortСard(int player_card[][2]) {
	int temp = 0;
	for (int i = 1; i < 5; i++) {
		for (int j = 0; j < 5 - i; j++) {
			if (player_card[j][0] > player_card[j + 1][0]) {
				temp = player_card[j + 1][1];
				player_card[j + 1][1] = player_card[j][1];
				player_card[j][1] = temp;

				temp = player_card[j + 1][0];
				player_card[j + 1][0] = player_card[j][0];
				player_card[j][0] = temp;
			}
		}
	}
}

//функция теста сортировки карт
int testSortCard() {
	int card[5][2];
	card[0][0] = 3; card[0][1] = 2;
	card[1][0] = 2; card[1][1] = 3;
	card[2][0] = 1; card[2][1] = 0;
	card[3][0] = 5; card[3][1] = 1;
	card[4][0] = 4; card[4][1] = 2;
	sortСard(card);
	for (int i = 0; i <= 4; i++) {
		if (card[i][0] != (i + 1))
			return -1;
	}
	return 0;
}

//функция определения флеш рояля
int royalFlesh(int player_card[][2], int* high_card, int* comb) {
	if (*comb == 8 && *high_card == 12)
		return 9;
	return *comb;
}

//функция определения стрит флеша
int straightFlesh(int player_card[][2], int* high_card, int* comb) {
	if (*comb == 5) {
		for (int i = 0; i <= 3; i++) {
			if (player_card[i][0] + 1 != player_card[i + 1][0])
				return *comb;
		}
		*high_card = player_card[4][0];
		return 8;
	}
	return *comb;
}

//функция определения каре
int fourKind(int player_card[][2], int* high_card, int* comb) {
	for (int i = 0; i <= 1; i++) {
		if (player_card[i][0] == player_card[i + 1][0] && player_card[i + 1][0] == player_card[i + 2][0] && player_card[i + 2][0] == player_card[i + 3][0]) {
			*high_card = player_card[i][0];
			return 7;
		}
	}
	return *comb;
}

//функция определения фулл хауса
int fullHouse(int player_card[][2], int* high_card, int* comb) {
	if (*comb == 3) {
		int count = 0;
		for (int i = 0; i <= 2; i++) {
			if (player_card[i][0] == *high_card) {
				count = i;
				break;
			}
		}
		if (count == 1) //тройка расположена посередине в сортированных картах
			return *comb;
		if (count == 0) { //тройка расположена слева в сортированных картах
			if (player_card[3][0] == player_card[4][0])
				return 6;
		}
		if (count == 2) { //тройка расположена справа
			if (player_card[0][0] == player_card[1][0])
				return 6;
		}
	}
	return *comb;
}

//функция теста fullHouse()
int testFullHouse() {
	int card[5][2], high_card = 4, comb = 3;
	card[0][0] = 1; card[0][1] = 2;
	card[1][0] = 1; card[1][1] = 3;
	card[2][0] = 4; card[2][1] = 0;
	card[3][0] = 4; card[3][1] = 1;
	card[4][0] = 4; card[4][1] = 2;
	if (fullHouse(card, &high_card, &comb) == 3)
		return -1;
	card[0][0] = 1; card[0][1] = 2;
	card[1][0] = 6; card[1][1] = 3;
	card[2][0] = 6; card[2][1] = 0;
	card[3][0] = 6; card[3][1] = 1;
	card[4][0] = 7; card[4][1] = 2;
	if (fullHouse(card, &high_card, &comb) == 6)
		return -1;
	card[0][0] = 2; card[0][1] = 2;
	card[1][0] = 2; card[1][1] = 3;
	card[2][0] = 2; card[2][1] = 0;
	card[3][0] = 6; card[3][1] = 1;
	card[4][0] = 6; card[4][1] = 2;
	if (fullHouse(card, &high_card, &comb) == 3)
		return -1;
	card[0][0] = 2; card[0][1] = 2;
	card[1][0] = 5; card[1][1] = 3;
	card[2][0] = 5; card[2][1] = 0;
	card[3][0] = 6; card[3][1] = 1;
	card[4][0] = 6; card[4][1] = 2;
	if (fullHouse(card, &high_card, &comb) == 3)
		return -1;
	return 0;
}


//функция определения стрита
int straight(int player_card[][2], int* high_card, int* comb) {
	for (int i = 0; i <= 3; i++) {
		if (player_card[i][0] + 1 != player_card[i + 1][0])
			return *comb;
	}
	*high_card = player_card[4][0];
	return 4;
}

//функция определения тройки
int threeKind(int player_card[][2], int* high_card, int* comb) {
	for (int i = 0; i <= 2; i++) {
		if (player_card[i][0] == player_card[i + 1][0] && player_card[i + 1][0] == player_card[i + 2][0]) {
			*high_card = player_card[i][0];
			return 3;
		}
	}
	return *comb;
}

//функция теста threeKind()
int testThreeKind() {
	int card[5][2], high_card = 4, comb = 0;
	card[0][0] = 1; card[0][1] = 2;
	card[1][0] = 1; card[1][1] = 3;
	card[2][0] = 1; card[2][1] = 0;
	card[3][0] = 4; card[3][1] = 1;
	card[4][0] = 7; card[4][1] = 2;
	if (threeKind(card, &high_card, &comb) != 3)
		return -1;
	card[0][0] = 0; card[0][1] = 2;
	card[1][0] = 1; card[1][1] = 3;
	card[2][0] = 1; card[2][1] = 0;
	card[3][0] = 1; card[3][1] = 1;
	card[4][0] = 7; card[4][1] = 2;
	if (threeKind(card, &high_card, &comb) != 3)
		return -1;
	card[0][0] = 0; card[0][1] = 2;
	card[1][0] = 2; card[1][1] = 3;
	card[2][0] = 4; card[2][1] = 0;
	card[3][0] = 4; card[3][1] = 1;
	card[4][0] = 4; card[4][1] = 2;
	if (threeKind(card, &high_card, &comb) != 3)
		return -1;
	card[0][0] = 1; card[0][1] = 2;
	card[1][0] = 1; card[1][1] = 3;
	card[2][0] = 4; card[2][1] = 0;
	card[3][0] = 4; card[3][1] = 1;
	card[4][0] = 7; card[4][1] = 2;
	if (threeKind(card, &high_card, &comb) != 0)
		return -1;
	return 0;
}

//функция определения количества пар
int pairs(int player_card[][2], int* high_card, int* comb) {
	int couples = 0;
	for (int i = 0; i <= 3; i++) {
		if (player_card[i][0] == player_card[i + 1][0]) {
			couples++;
			*high_card = player_card[i][0];
			i++;
		}
	}
	if (couples == 1)
		return 1;
	else if (couples == 2)
		return 2;

	return *comb;
}

//функция теста pairs()
int testPairs() {
	int card[5][2], high_card = 4, comb = 0;
	card[0][0] = 1; card[0][1] = 2;
	card[1][0] = 1; card[1][1] = 3;
	card[2][0] = 4; card[2][1] = 0;
	card[3][0] = 4; card[3][1] = 1;
	card[4][0] = 7; card[4][1] = 2;
	if (pairs(card, &high_card, &comb) != 2)
		return -1;
	card[0][0] = 1; card[0][1] = 2;
	card[1][0] = 1; card[1][1] = 3;
	card[2][0] = 4; card[2][1] = 0;
	card[3][0] = 5; card[3][1] = 1;
	card[4][0] = 7; card[4][1] = 2;
	if (pairs(card, &high_card, &comb) != 1)
		return -1;
	card[0][0] = 1; card[0][1] = 2;
	card[1][0] = 2; card[1][1] = 3;
	card[2][0] = 3; card[2][1] = 0;
	card[3][0] = 4; card[3][1] = 1;
	card[4][0] = 7; card[4][1] = 2;
	if (pairs(card, &high_card, &comb) != 0)
		return -1;
	return 0;
}

//функция определения флеша
int flesh(int player_card[][2], int* high_card, int*comb) {
	for (int i = 0; i < 4; i++) {
		if (player_card[i][1] != player_card[i + 1][1])
			return *comb;
	}
	*high_card = player_card[4][0];
	return 5;
}

//функция сравнения карт двух игроков
int compareCombination(int winner_pl[][2], int looser_pl[][2], std::string* comb) {
	int winner_high_card = 0, looser_high_card = 0, winner_comb = 0, looser_comb = 0;
	//сортируем карты
	sortСard(winner_pl);
	sortСard(looser_pl);

	//старшая карта при отсутсвии комбинации
	winner_high_card = winner_pl[4][0];
	looser_high_card = looser_pl[4][0];

	//пара и две пары
	winner_comb = pairs(winner_pl, &winner_high_card, &winner_comb);
	looser_comb = pairs(looser_pl, &looser_high_card, &looser_comb);

	//тройка
	winner_comb = threeKind(winner_pl, &winner_high_card, &winner_comb);
	looser_comb = threeKind(looser_pl, &looser_high_card, &looser_comb);

	//стрит
	winner_comb = straight(winner_pl, &winner_high_card, &winner_comb);
	looser_comb = straight(looser_pl, &looser_high_card, &looser_comb);

	//флеш
	winner_comb = flesh(winner_pl, &winner_high_card, &winner_comb);
	looser_comb = flesh(looser_pl, &looser_high_card, &looser_comb);

	//фулл хаус
	winner_comb = fullHouse(winner_pl, &winner_high_card, &winner_comb);
	looser_comb = fullHouse(looser_pl, &looser_high_card, &looser_comb);

	//каре
	winner_comb = fourKind(winner_pl, &winner_high_card, &winner_comb);
	looser_comb = fourKind(looser_pl, &looser_high_card, &looser_comb);

	//стрит флеш
	winner_comb = straightFlesh(winner_pl, &winner_high_card, &winner_comb);
	looser_comb = straightFlesh(looser_pl, &looser_high_card, &looser_comb);

	//флеш рояль
	winner_comb = royalFlesh(winner_pl, &winner_high_card, &winner_comb);
	winner_comb = royalFlesh(winner_pl, &winner_high_card, &winner_comb);

	if (winner_comb > looser_comb) {
		*comb = combination[winner_comb];
		return 1;
	}
	else if (winner_comb < looser_comb) {
		*comb = combination[looser_comb];
		return -1;
	}
	else if (winner_comb == looser_comb) {
		if (winner_high_card > looser_high_card) {
			*comb = combination[winner_comb];
			return 1;
		}
		else if (winner_high_card == looser_high_card)
			return 0;
		else if (winner_high_card < looser_high_card) {
			*comb = combination[looser_comb];
			return -1;
		}
	}
}