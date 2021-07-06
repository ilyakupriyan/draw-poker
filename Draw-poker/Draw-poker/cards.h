#ifndef CARDS_H
#define CARDS_H

//структура для замены карт игрока
struct changeC {
	int card = 0;
	changeC* next_card = NULL;
};

void printCards(int const cards[][2]);
void testPrintCards();
void deckInit(int deck[][2]);
int testDeckInit();
void deckShuffle(int deck[][2]);
int testDeckShuffle();
void deal(int deck[][2], int players_card[][2], int* issued_cards);
void changeCard(int deck[][2], int players_card[][2], int* issued_cards, changeC player);
int addChange(std::string number, changeC* head, changeC* new_card);
void testChooseChange();
void deleteChange(changeC* head);

#endif