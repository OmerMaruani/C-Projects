
#include "RatATat.h"


const unsigned Pile::total_cards = 54;





Pile::Pile(const string & type): m_i(-1), m_type(type)
{
	

	//for draw_pile
	if (type == "draw")
		this->new_pile();


	//for discard_pile
	else if (type == "discard")
	{
		this->m_cards = new Card * [Pile::total_cards];
	}
	

}
Pile::~Pile()
{

	//int len = this->get_len();
	//int len = this->m_i;

	//i want only the draw pile to delete all the cards, discard pile dont need to do that


	if (this->m_type == "draw")
		for (int i = 0; i < Pile::total_cards ; i++)
			if (this->m_cards[i])
			{
				delete this->m_cards[i];
				this->m_cards[i] = nullptr;
			}


	if (this->m_cards)
	{
		delete [] this->m_cards;
		this->m_cards = nullptr;
	}

}





bool Pile:: push_back(Card* card)
{
	if (this->m_i < this->get_len())
	{
		this->m_i++;
		this->m_cards[this->m_i] = card;
		//this->m_i++;
		return true;
	}
	else
		return false;
}
Card* Pile:: pop()
{
	
	Card* card = this->m_cards[this->m_i];	


	try
	{
		if (this->m_i >= 0)
		{
			Card* card = this->m_cards[this->m_i];
			this->m_i--;
			return card;
		}

		else
		{
			throw string("The Pile card is empty, nullptr returned");
			return nullptr;
		}
	}
	catch (const string& s) { cout << s << endl; }

	
	
}

int Pile::size() const
{
	return this->m_i + 1;

}
bool Pile::empty() const
{
	if (this->m_i == -1)
		return true;
	else
		return false;
}
bool Pile::full() const
{
	if (this->m_i == this->get_len() - 1)
		return true;
	else
		return false;

}
const Card* Pile:: top() const
{
	return this->m_cards[this->m_i];
}
int Pile::get_len()
{
	return Pile::total_cards;

}
int Pile::get_curr_i() const
{
	return this->m_i;

}




void Pile::new_pile()
{
	//need to delete all cards aswell
	
	if (this->m_cards)
		delete this;
	

	this->m_cards = new Card * [Pile::total_cards];

	//hard to send a class type to function

	if (this->m_cards)

	{
		for (int i = 0; i < Swap_card::get_total_cards(); i++)
			this->push_back(new Swap_card);


		for (int i = 0; i < Peek_card::get_total_cards(); i++)
			this->push_back(new Peek_card);


		for (int i = 0; i < Draw2_card::get_total_cards(); i++)
			this->push_back(new Draw2_card);

		for (int i = 0; i < Cat_card::get_total_cards(); i++)
			this->push_back(new Cat_card);

	
		for (int i = 0; i < Rat_card::get_total_cards(); i++)
			this->push_back(new Rat_card);

	}

	/*
	int arr[10] = { 0 };
	for (int i = 0; i < 54; i++)
		arr[this->m_cards[i]->get_val()]++;
	*/
}
void Pile::shuffle()
{
	// Seed the random number generator with current time
	//if not , getting the same output everytime

	srand(static_cast<unsigned int>(time(nullptr)));

	int n;
	for(int all= 0 ; all <100 ; all++)
		for (int i = 0; i < Pile::total_cards; i++)
		{
			n = rand() % Pile::total_cards;
			my_swap(this->m_cards[i], this->m_cards[n]);
		}
		

}

void Pile:: print_last_card() const
{
	cout << *(this->m_cards[this->m_i]) << endl;

}


