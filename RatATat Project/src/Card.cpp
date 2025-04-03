
#include "RatATat.h"

#include <cstdlib>  // rand()


const unsigned Card::total_card = 54;

unsigned Rat_card::num_cards= 21;
unsigned Cat_card::num_cards = 24;

int Rat_card::cards_left[rat_diff_cardstype] = {4,4,4,9}; 
int Cat_card::cards_left[cat_diff_cardstype] = {4,4,4,4,4,4};

unsigned Swap_card::num_cards =3 ;
unsigned Peek_card::num_cards = 3;
unsigned Draw2_card::num_cards = 3;


const unsigned Play_card::action_menu= 2;
const unsigned Speical_card::action_menu = 4;



//Card

Card::Card(int val, const string& txt):m_value(val),m_text(txt)
{
	//deep copy
}
Card::~Card()
{
	
	// No need to manually delete m_text
	// The destructor of std::string will handle it

}

//getters
int Card::get_val() const
{
	return m_value;

}
const string Card::get_text() const
{
	return m_text;
}
unsigned  Card::get_total_cards()
{
	return Card::total_card;

}

//setters
void Card::set_val(int& val)
{
	m_value = val;

}
void Card::set_text(const string& text)
{
	m_text = text;

}


ostream& operator<<(ostream& os, const Card& c)
{
	c.print(os);
	return os;
}





//Play_card



	
Play_card::Play_card(const unsigned val , const string & txt):Card(val,txt)
{
	//base class
	
}
Play_card:: ~Play_card()
{


}
void Play_card::print_card_action_menu() const
{
	cout << "Choose option:" << endl;


	cout << "1. Discard" << endl;
	cout << "2. Replace with one of my cards" << endl;



}
int Play_card::get_card_action_menu_max_num() const
{
	return Play_card::action_menu;

}


void Play_card::print(ostream& os) const
{
	cout << this->get_text() << ", " << this->get_val()<< "   ";
	

}
ostream& operator<<(ostream& os, const Play_card& play_card)
{
	play_card.print(os);
	return os;
}
void Play_card:: use(Player** players, int curr_player, RatATat& rat)
{	
	int number_card = 0;


	//replace with one of my cards
	cout << "Which card do you want to replace? 1...4 from left to right" << endl;
	number_card = players[rat.get_m_curr_player()]->get_action_number(4) - 1;

	// number_ card of the one thats will go discard
	rat.replace_player_card_discard(rat.get_m_curr_player(), number_card, this);

	
	
}
 





//Rat card


Rat_card::Rat_card(const unsigned val) :Play_card(val, "Rat")
{
	//example , rat can get val 6 -9 , and cards_left getting val 6 in index 0
	//using this later when i take random number from rat, get random val, and depend how many i have from this type in the pile


	
	try
	{

		if (val >= 6 && val <= 9)
		{
			this->cards_left[val - 6]--; //go class to know why 6-val
		}

		else throw string("Cards left got empty, and u try get more of him???");
	}
	catch (const string & s) { cout << s <<endl; }

}
Rat_card::~Rat_card()
{
	
}
int Rat_card::get_total_cards()
{
	return  Rat_card::num_cards;
}
int Rat_card::toss_val()
{
	

	
	double each_prob_card = (1.0 / Rat_card::get_total_cards() ) *100;

	//now lets give val prob for every one of the options, 6,7,8,9
	//need to check how many cards left from this number, total 4 of same number, only 9 with 9 cards


	double prob[rat_diff_cardstype] = { 0 };

	for (int i = 0; i < rat_diff_cardstype; i++)
	{
		//if( i == 3) prob[i] = (5+  Rat_card::cards_left[i]) * each_prob_card; //this one is diff has 9 cards of number 9
		prob[i] = Rat_card::cards_left[i] * each_prob_card;
	}

	
	

	//every number get his own area
	for (int i = 1; i < rat_diff_cardstype; i++)
		prob[i] += prob[i - 1];


	//exa,6 take 0-30, 7 take 30-50, 8 take 50-60, 9 take 60-100
	//if one of them is 0 then it will not take him, its a number



	int max_rand = int(prob[rat_diff_cardstype - 1]);
	int n = rand() % max_rand; 


	//check which number
	for (int i = 0; i < rat_diff_cardstype; i++)
		if (n < prob[i] || i == rat_diff_cardstype- 1) return i + 6; // return i+6, back to the relevant number of card
	 //n=4
	//0 0 0, 4.5

}












//Cat card


Cat_card::Cat_card(const unsigned val) :Play_card(val, "Cat")
{
	
	
	try
	{
		if (this->cards_left[val] > 0)
			this->cards_left[val]--;

		else throw string("Cards left got empty, and u try get more of him???");
	}
	catch (const string& s) { cout << s << endl; }

	

	
}
Cat_card::~Cat_card()
{
	
}
int Cat_card::get_total_cards()
{
	return  Cat_card::num_cards;
}
int Cat_card::toss_val()
{



	double each_prob_card = (1.0 / Cat_card::get_total_cards()) * 100;

	//now lets give val prob for every one of the options, 6,7,8,9
	//need to check how many cards left from this number, total 4 of same number, only 9 with 9 cards


	double prob[cat_diff_cardstype] = { 0 };

	for (int i = 0; i < cat_diff_cardstype; i++)
	{
		 prob[i] = Cat_card::cards_left[i] * each_prob_card;
	}

	

	//every number get his own area
	for (int i = 1; i < cat_diff_cardstype; i++)
		prob[i] += prob[i - 1];


	//i want the rand to get value from 0- high(prob distance)
	//thats mean for exa if here prob[last_one] = 66, then rand%66

	int max_rand = int(prob[cat_diff_cardstype - 1]);
	int n =  rand() % max_rand; //take down the prob 0
	

	//check which number
	
	for (int i = 0; i < cat_diff_cardstype; i++)
		if (n < prob[i] || i == cat_diff_cardstype -1) return i ; 



}












//Speical card



Speical_card::Speical_card( const string& txt) :Card(-1, txt)
{
	//base class

}
Speical_card::~Speical_card()
{


}
void Speical_card ::print_card_action_menu() const
{
	cout << "choose opetion:" << endl;


	cout << "1. Discard without use" << endl;
	cout << "2. Use special card" << endl;


}
int Speical_card::get_card_action_menu_max_num() const
{
	return Speical_card::action_menu;

}


void Speical_card::print(ostream& os) const
{
	cout << " "<<this->get_text()<<"    ";


}
ostream& operator<<(ostream& os, const Speical_card& speical_card)
{
	speical_card.print(os);
	return os;
}





//Swap card

Swap_card::Swap_card() :Speical_card("Swap")
{
	

}
Swap_card::~Swap_card()
{


}

void Swap_card:: use(Player** players, int curr_player, RatATat& rat)
{
	//Speical_card::print_card_action_menu();
	//this->print_card_action_menu();
	
	int number_card = 0;
	int number_card_player_swap;
	int num_player_swap = 0;

	

	
	// use speical card
	
	cout << "Which player u want to swap cards with, options:"<<endl;
	for (int i = 0; i < rat.get_m_number_players(); i++)
		if (i != rat.get_m_curr_player()) cout << " " << i + 1<<endl;

	num_player_swap = players[rat.get_m_curr_player()]->get_action_number( rat.get_m_number_players() )  - 1;



	if (num_player_swap >= 0 && num_player_swap < rat.get_m_number_players())
	{
		cout << "Which card do you want to swap from your cards ? 1...4 from left to right" << endl;
		number_card = players[rat.get_m_curr_player()]->get_action_number(4) - 1 ;


		cout << "Which card do you want to swap from the player cards ? 1...4 from left to right" << endl;
		number_card_player_swap = players[rat.get_m_curr_player()]->get_action_number(4) - 1;

		// first player: rat.get_m_curr_player(), and number_card to swap
		//second player: num_player_swap, number_card_player_swap
		rat.swap_cards_two_players(rat.get_m_curr_player(), num_player_swap, number_card, number_card_player_swap);

	}


	else
		cout << "no player number:"<<num_player_swap <<endl;
		//error

	
	
}
unsigned Swap_card::get_total_cards()
{
	return Swap_card::num_cards;
}



//Peek card

Peek_card::Peek_card() :Speical_card ("Peek")
{
	

}
Peek_card::~Peek_card()
{


}

void Peek_card::use(Player** players, int curr_player, RatATat& rat)
{
	//Speical_card::print_card_action_menu();
	int number_card = 0;

	// use speical card
	
	cout << "Which card do you want to peek? 1...4 from left to right" << endl;
	number_card = players[rat.get_m_curr_player()]->get_action_number(4) - 1;
	rat.peek_card(rat.get_m_curr_player(), number_card);

}
unsigned Peek_card::get_total_cards()
{
	return Peek_card::num_cards;
}



//Draw2 card

Draw2_card::Draw2_card() :Speical_card("Draw2")
{
	

}
Draw2_card::~Draw2_card()
{


}

void Draw2_card::use(Player** players, int curr_player, RatATat& rat)
{
	//Speical_card::print_card_action_menu();
	// 
	// use speical card
	rat.set_m_curr_player(rat.get_m_curr_player() - 1);
}
unsigned Draw2_card::get_total_cards()
{
	return Draw2_card::num_cards;
}

