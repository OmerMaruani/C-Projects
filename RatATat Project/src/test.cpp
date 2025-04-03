

#include "RatATat.h"



#include <string>
#include <time.h>
#include <iostream>
using namespace std;

int toss_val()
{
	

	double each_prob_card = (1.0 / 20) * 100;

	//now lets give val prob for every one of the options, 6,7,8,9
	//need to check how many cards left from this number, total 4 of same number, only 9 with 9 cards

	int cards_left[4] = { 0, 2,3, 10 };
	
	double prob[4] = { 0 };

	for (int i = 0; i < rat_diff_cardstype; i++)
	{
		if (i == 3) prob[i] = (5 + cards_left[i]) * each_prob_card; //this one is diff has 9 cards of number 9
		else prob[i] = cards_left[i] * each_prob_card;
	}

	double n = 0.001 + rand() % 100; //take down the prob 0



	//every number get his own area
	for (int i = 1; i < rat_diff_cardstype; i++)
		prob[i] += prob[i - 1];


	//exa,6 take 0-30, 7 take 30-50, 8 take 50-60, 9 take 60-100
	//if one of them is 0 then it will not take him, its a number

	//check which number
	for (int i = 0; i < rat_diff_cardstype; i++)
		if (n < prob[i]) return i + 6; // return i+6, back to the relevant number of card


}

void pile()
{
	Pile p1("draw");
	//p1.new_pile();
	//p1.shuffle();

	for (int i = 0; i < 54; i++)
	{
		Card* c = p1.pop();
		cout << *c;

	}
		

}

void RatAtat()
{

	//fix memory here, in card explain

	string names[3] = { "Player1", "Player2","Player3"};
	RatATat game1(3, names);

	game1.play();
	
	//game1.add_players("omer");
		return;
}


void test_memory()
{
	Card** d = new Card* [2];

	d[0] = new Cat_card;
	d[1] = new Rat_card;

	Card* b = d[0];
	Card* c = d[1];

	Card** s = new Card * [2];

	s[0] = d[0];
	s[1] = d[1];

	s[0] = nullptr;

	

	delete[]s;

	for (int i = 0; i < 2; i++)
		delete d[i];
	delete[]d;


}

//need to check delete num_cards member
int test()
{
	srand(time(NULL));
	RatATat rat;
	rat.add_player("Human");
	rat.play();

	return 0;

	//_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF | _CRTDBG_CHECK_ALWAYS_DF);

}
void main()
{

	//pile();
	//test_memory();
	//RatAtat();
	cout << test()<<endl;

	//_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF | _CRTDBG_CHECK_ALWAYS_DF);

	_CrtDumpMemoryLeaks();
	cout << "Leaks: " << _CrtDumpMemoryLeaks() << endl;
}
