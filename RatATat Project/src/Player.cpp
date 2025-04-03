

#include "RatATat.h"


const unsigned Player::total_cards_player = 4;


unsigned Human_player::number_players = 0;



Player::Player(const string& name, Card* cards_player[], RatATat* ptrgame):m_name(name),ptrgame(ptrgame)
{
	this->m_cards = new Card* [4];

	//fill cards
	for (int i = 0; i < this->total_cards_player; i++)
		this->m_cards[i] = cards_player[i];
}
Player::Player(const string& name) :m_name(name)
{

	//delete only the arr, cards left to delete by pile
		

	delete[] this->m_cards;

}
Player::~Player()
{
	//dont delete here, its getting delete when the draw pile delete
	//if(this->m_cards)
		//delete[] this->m_cards;


	//delete only the arr, cards left to delete by pile
	delete[] this->m_cards;
	
}
string Player::get_name() const
{
	return this->m_name;
}
Card* Player::get_card(int i) const
{
	return this->m_cards[i];
}
void Player::set_card(Card* card, int i)
{
	this->m_cards[i] = card;
}
int Player::get_total_cards()
{
	return Player::total_cards_player;
}

Card* Player::swap_cards(int card_index,  Card* new_card)
{
	// this represent the player, cards of the player

	Card* swap_with_card_player = new_card;
	my_swap(swap_with_card_player, this->m_cards[card_index]);
	
	//after swap, swap_with_card_player will be return, to discard
	return swap_with_card_player;
}

ostream& operator<<(ostream& os, const Player& p)
{
	p.print(os);
	return os;
}
bool Player::turn() const
{
	cout << "Choose option:" << endl;
	cout << "1. Take a card from draw pile" << endl;

	//check if there is play card in the top of the discard pile
	if (this->ptrgame->top_discard_pile()->get_val() != -1)
	{
		cout << "2. Take a card from discard pile" << endl;
		return true;
		
	}
	else
	{
		cout << "Discard pile top car is special card, 1 is only option" << endl;
		cout << 1 << endl;
		return false;
	}
}







//Human Player


Human_player::Human_player(const string& name, Card* cards_player[], RatATat* ptrgame):Player(name,cards_player,ptrgame)
{
	Human_player::number_players++;
	curr_player_number = Human_player::number_players; // to show human1, human2
}
Human_player::~Human_player()
{

}
int Human_player::get_action_number(int max_actions) const

{
	int c;
	cin >> c;
	try 
	{
		if (max_actions == 2 )
		{

			if (c > 0 && c < 3) //1,2 options for special cards use
				return c;
			else
				throw string("U have 2 options, 1,2");

		}
		else if (max_actions <= 4)
		{

			if (c > 0 && c < 5) //1,2,3,4 options for special cards use
				return c;
			else
				throw string("U have 4 options, 1,2,3,4");
		}
			
	}
	catch (const string& s) { cout << s << endl; }

		
	return -1;
}

bool Human_player::turn() const
{

	cout << "It's " <<this->get_name()  << " turn:" << endl;

	//same like computer
	return Player::turn();
	
}
void Human_player::card_drown(Card* card) const
{
	cout << "Card drown: " << *card <<endl;
}
void Human_player::print(ostream& os) const
{
	Human_player::number_players++;
	os << "Human"<< this->curr_player_number << endl;
	os <<"   "<< * (this->m_cards[0]) << "    " << "hidden card" << "  " << "hidden card" << "    ";
	os << *(this->m_cards[this->get_total_cards()-1]) << endl;
	
}
ostream& operator<<(ostream& os, const Human_player p)
{
	p.print(os); 
	return os;
}





//Ai player






Ai_player::Ai_player(const string& name, Card* cards_player[], RatATat* ptrgame) :Player(name, cards_player,ptrgame)
{
	
}
Ai_player::~Ai_player()
{

}
int Ai_player::get_action_number(int max_actions) const
{
	//need to change by action number
	int c = 1+ rand() % max_actions;
	cout << c << endl;
	return c;
}

void Ai_player::print(ostream& os) const
{
	/*
	os << "Computer" << endl;
	os << "   "<< * (this->m_cards[0]) << "    " << "hidden card" << "  " << "hidden card" << "    ";
	os << *(this->m_cards[this->get_total_cards() - 1]) << endl;
	*/
}
ostream& operator<<(ostream& os, const Ai_player p)
{
	p.print(os);
	return os;
}
bool Ai_player::turn() const
{

	cout << "It's Computer" << " turn:" << endl;
	

	//same like computer
	return Player::turn();
}
void Ai_player:: card_drown(Card* card) const
{

}
