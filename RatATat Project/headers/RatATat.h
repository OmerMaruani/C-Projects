#ifndef _RATATAT_H_
#define _RATATAT_H_

#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
#define new DBG_NEW


#include <exception>
#include <string>
#include <iostream>
using namespace std;


#include "Card.h"
#include "Player.h"
#include "Pile.h"


	

//need to check for template in the new box
//need to check for cunstrcutor calling the new box

//need to check in function add_player if i need to roll 4 new cards and then allocate memory for player
//so i dont need cunstcrutor for player with string only


class RatATat {


	private:

		unsigned m_number_players;
		Player** m_players;//arr of pointers to players, to handle poly
		unsigned m_curr_player;
		//Pile m_draw_pile;

		//in this order, pile destructor will call draw pile first
		Pile m_discard_pile;
		Pile m_draw_pile;
		
		

		static const unsigned total_cards;


	public:

		RatATat(unsigned number_players, const string *players_names);
		RatATat(unsigned number_players=1 );
		//RatATat(unsigned number_players);
		~RatATat();

		bool add_player(const string& name);
		void play();

		//all function cant be const , called from play

		//can be const
		void print_discard() const ;
		bool call_end() const;
		void find_win() ;
		
		

		//some function of the game
	    const  Card* top_discard_pile() ;
		void push_card_discard_pile(Card* new_card);
		Card* take_card_draw_pile();
		void peek_card(int player_number, int card_number) const;
		void swap_cards_two_players(int p_n1, int p_n2, int c_n1, int c_n2);
		void replace_player_card_discard(int player_number, int card_number, Card* new_card);

		

		//getters


		int get_m_number_players() const;
		int get_m_curr_player() const;
		static int get_total_cards_game();


		//friend void Play_card::use(Player** players, int curr_player, RatATat& rat); //let access to rat members
		// void Swap_card::use(Player** players, int curr_player, RatATat& rat);
		//friend void Peek_card::use(Player** players, int curr_player, RatATat& rat);
		//friend void Draw2_card::use(Player** players, int curr_player, RatATat& rat);


		void set_m_curr_player( int num);


	//only on ratatat function member i use it, no outside
	protected:
		void print_all_cards_player(int i) const;
		void discarding_special_cards(int i);
		void find_winner_sum_cards(int i,int& sum,int & player_win) const;
		void play_with_the_card(int i,Card *card);
		void draw2_now_playing(int& i, int& end_i, int& draw2_playing,bool &game) const;

};















#endif