

#include "RatATat.h"


 const unsigned RatATat::total_cards =54;

RatATat::RatATat(unsigned number_players, const string* players_names) :m_draw_pile("draw"),m_discard_pile("discard")
{
	
	this->m_curr_player = 0;
	this->m_draw_pile.shuffle();

	this->m_number_players = number_players;
	this->m_players = new Player*[this->m_number_players];



	//now enter names and get cards, draw pile is ready
	Card *cards [4];
	int num_cards = this->m_players[0]->get_total_cards();

	for (int i = 0; i < this->m_number_players; i++)
	{
		for (int i = 0; i < num_cards; i++)
			cards[i] = this->m_draw_pile.pop();

		if( (players_names[i]).substr(0,6) == string("Player") )
			this->m_players[i] = new Human_player(players_names[i], cards,this);
		else
			this->m_players[i] = new Ai_player(players_names[i], cards, this);
	}


}
RatATat::RatATat(unsigned number_players ): m_discard_pile("discard"),m_draw_pile("draw")
{

	this->m_curr_player = 0;
	this->m_draw_pile.shuffle();

	this->m_number_players = number_players;
	this->m_players = new Player * [this->m_number_players];

	

	//now enter names and get cards, draw pile is ready
	Card* cards[4];
	int num_cards = this->m_players[0]->get_total_cards();
	
	for (int i = 0; i < num_cards; i++)
		cards[i] = this->m_draw_pile.pop();


	this->m_players[0] = new Ai_player(("Computer"), cards, this);
	

}

RatATat::~RatATat()
{
	
	for (int i = 0; i < this->m_number_players; i++)
		if (this->m_players[i])
			delete this->m_players[i];
	
	if (this->m_players)
		delete[] this->m_players;

	
}

bool RatATat::add_player(const string& name)
{
	

	
	//copy the players
	Player** p1 = new Player * [this->m_number_players];

	for (int i = 0; i < this->m_number_players; i++)
		p1[i] = this->m_players[i]; //handle the address
	

	//delete only the arr, not the address 
	if (this->m_players)
		delete [] this->m_players;


	//resize
	this->m_number_players++;
	this->m_players = new Player * [this->m_number_players];


	//copy

	for (int i = 0; i < this->m_number_players-1; i++)
		 this->m_players[i]= p1[i]; //handle the address


	//get his cards from the draw pile 
	Card* card[4];
	for (int i = 0; i < 4; i++)
		card[i] = this->m_draw_pile.pop();

	this->m_players[this->m_number_players - 1] = new Human_player(name,card,this);


	delete[] p1;
	
	
	return true;

}
void RatATat::play()
{

	//first show the players left right crads
	for (int i = 0; i < this->m_number_players; i++)
		cout << *(this->m_players[i]); //cout the player hisself
		


	//first get discard with one card
	this->m_discard_pile.push_back(this->m_draw_pile.pop());

	int a = 0;
	Card* card;
	int num_card_replace = 0;
	bool game = true;
	int end_i = 0;
	int draw2_playing = 0;
	bool draw_discard = false;
	int use_special_card = 0;

	for (int i = 0; i < this->m_number_players; i++)
	{
		this->m_curr_player = i;

		//when someone called ratatat , every player get more 1 turn
		if (game == false && i == end_i) break;

		//print discard pile
		this->print_discard();

		draw_discard = this->m_players[i]->turn();

		if (draw_discard == true) //there is 2 options to choose, no special card in discard 
			a = this->m_players[i]->get_action_number(2);

		else
			a = 1;

		
		//draw pile
		if (a == 1)
		{
			card = this->m_draw_pile.pop();
			this->m_players[i]->card_drown(card);
		}
		//discard pile
		else
			card = this->m_discard_pile.pop();


		//play with the card
		this->play_with_the_card(i, card);
		

		//manage how to keep draw 2 if someone took, find win, let computer play
		//when someone get draw2 card 
		this->draw2_now_playing(i, end_i, draw2_playing, game);

		if (i == this->m_number_players - 1) i = -1;//next time start again



	}

	this->find_win();

}

void RatATat::print_discard() const
{
	cout << endl<< "========================" << endl;
	cout << " Discard Pile:   ";
	this->m_discard_pile.print_last_card();
	cout  << "========================" << endl;
	
}
bool RatATat::call_end() const
{
	cout << "Call RatATat ?" << endl;
	cout << "1. No" << endl;
	cout << "2. Yes" << endl;
	int n = this->m_players[this->m_curr_player]->get_action_number(2);
	//false to end game
	if (n == 2) return false;
	else if (n ==1) return true;
}
const Card* RatATat::top_discard_pile() 
{
	return this->m_discard_pile.top();
}
void RatATat::find_win()
{
	//first check all cards are play card
	
	Card* new_card;
	int player_win = 0;
	int sum = 4*9; //max number

	for (int i = 0; i < this->m_number_players; i++)
	{
		cout << endl << this->m_players[i]->get_name() << " Cards before discarding special cards:   ";
		this->print_all_cards_player(i);
		this->discarding_special_cards(i);

		cout << endl << this->m_players[i]->get_name() << " Cards after discarding special cards:   ";
		this->print_all_cards_player(i);
		this->find_winner_sum_cards(i, sum, player_win);
	}

	cout << endl << "And the winner is: " << this->m_players[player_win]->get_name()<<endl;

}


	
//some function 

//some function of the game

void RatATat::push_card_discard_pile( Card * new_card)
{
	this->m_discard_pile.push_back(new_card);
}
Card* RatATat::take_card_draw_pile()
{
	return this->m_draw_pile.pop();
}
void RatATat::peek_card(int player_number, int card_number) const
{
	const Card* peek_card = this->m_players[player_number]->get_card(card_number);
	for (int i = 0; i < card_number; i++)
		cout << "            ";
	cout << *peek_card << endl;
}
void RatATat::swap_cards_two_players(int p_n1, int p_n2, int c_n1, int c_n2)
{
	Card* c1, *c2;
	c1 = this->m_players[p_n1]->get_card(c_n1);
	c2 = this->m_players[p_n2]->get_card(c_n2);
	my_swap(c1, c2);

	this->m_players[p_n1]->set_card(c1, c_n1);
	this->m_players[p_n2]->set_card(c2, c_n2);


}
void RatATat::replace_player_card_discard(int player_number, int card_number, Card* new_card)
{
	Card* discard_card = this->m_players[player_number]->swap_cards(card_number, new_card);
	this->m_discard_pile.push_back(discard_card);
}



void RatATat::print_all_cards_player(int i) const
{
	for (int card_number = 0; card_number < this->m_players[i]->get_total_cards(); card_number++)
		cout << *(this->m_players[i]->get_card(card_number)) << "  ";
}
void RatATat::discarding_special_cards(int i)
{
	Card* new_card;
	for (int card_number = 0; card_number < this->m_players[i]->get_total_cards(); card_number++)
		if (this->m_players[i]->get_card(card_number)->get_val() == -1)
		{
			//special card to discard pile
			this->m_discard_pile.push_back(this->m_players[i]->get_card(card_number));

			//card from pile
			new_card = this->m_draw_pile.pop();


			//keep untill u got play card
			while (new_card->get_val() == -1)
			{
				this->m_discard_pile.push_back(new_card);
				new_card = this->m_draw_pile.pop();
			}


			this->m_players[i]->set_card(new_card, card_number);


		}
}
void RatATat::find_winner_sum_cards(int i ,int& sum,int &player_win) const
{
	int cur_sum = 0;
	for (int card_number = 0; card_number < this->m_players[i]->get_total_cards(); card_number++)
	{
		cur_sum += this->m_players[i]->get_card(card_number)->get_val();
	}

	if (cur_sum < sum)
	{
		sum = cur_sum;
		player_win = i;
	}
}
void RatATat::play_with_the_card(int i,Card *card)
{
	//play with the card
	card->print_card_action_menu();
	int use_special_card = this->m_players[i]->get_action_number(2);
	if (use_special_card == 1) 
		this->push_card_discard_pile(card);
	else
		card->use(m_players, this->m_curr_player, *this);
}
void RatATat::draw2_now_playing(int& i, int& end_i, int& draw2_playing, bool& game) const
{

	if (draw2_playing == 2) draw2_playing = 0;

	if (this->m_curr_player == i && draw2_playing == 0) //no draw2 card took
	{
		//next time we ge, if one ask for end , no need ask again
		if (game == true)
		{
			//if someone called end, return false
			game = this->call_end();
			if (game == false) end_i = i;
		}
	}
	else
	{
		i--; // next one will be again because draw2
		draw2_playing++; //next one will get here again, untill draw2==2 end turn
	}



}



//getters


int  RatATat::get_m_number_players() const
{
	return this->m_number_players;
}
int  RatATat::get_m_curr_player() const
{
	return this->m_curr_player;
}
int  RatATat::get_total_cards_game()
{
	return RatATat::total_cards;
}
void RatATat::set_m_curr_player(int num)
{
	this->m_curr_player = num;
}













