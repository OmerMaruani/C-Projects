#ifndef _PLAYER_H_
#define _PLAYER_H_



//#include "Card.h"
//#include "RatATat.h"

//get access from human_player to m_cards

//need to check how to poly the operator <<, i cant declare as virtual on this function
//because this isnt member function, when calling opeator<< , only the one of the players is called
//need to diff human and ai

//this solve header problem, when i use #include "RatATat" getting error


//why using friend funciton ratatat::play dont give accesss, only friend class give


//class RatATat;


class Player {


	protected:
		static const unsigned total_cards_player;
		const string m_name;
		RatATat* ptrgame;
		Card** m_cards;

	


	

	public:
		Player(const string& name, Card* cards_player[],RatATat* ptrgame);
		Player(const string& name);// will set the cards later
		~Player();

		

		//getters

		string get_name() const;
		Card* get_card(int i) const;
		static int get_total_cards();
		virtual int get_action_number( int max_actions) const { return 0; };
		

		//setter
		void set_card(Card* card, int i);

		
		
	

		//got a problem to overload operator << in poly, only the base class called
		//trying to use it with virtual print thats will be called by operator<<

		// Virtual function to print card details
		virtual void print(ostream& os) const {};
		friend ostream& operator<<(ostream& os, const Player& p);

		virtual bool turn() const ;
		virtual void card_drown(Card *card) const =0; //print only card drown for human


		Card* swap_cards(int card_index,  Card* new_card);


		//friend void RatATat::play(); // to let this function access  *RatATat 
		//friend RatATat;

		//friend void Play_card::use(Player** players, int curr_player, RatATat& rat); //let access to player members
		//friend void Swap_card::use(Player** players, int curr_player, RatATat& rat);
		//friend void Peek_card::use(Player** players, int curr_player, RatATat& rat);
		//friend void Draw2_card::use(Player** players, int curr_player, RatATat& rat);
		
};


ostream& operator<<(ostream& os, const Player& p);









class Human_player : public Player
{

	private:
		static unsigned number_players;
		unsigned curr_player_number; // to show human1, human2

	public:

	
		Human_player(const string& name, Card* cards_player[], RatATat* ptrgame);
		~Human_player();

		//getter
		int get_action_number(int max_actions) const ;


		void print(ostream& os) const;

		//no need because i access this in print function
		//friend ostream& operator<<(ostream& os, const Human_player& p);

		bool turn() const ;
		void card_drown(Card* card) const;
};


ostream& operator<<(ostream& os, const Human_player& p);







class Ai_player : public Player
{

	private:

		
	public:


		Ai_player(const string& name, Card* cards_player[], RatATat* ptrgame);
		~Ai_player();


		int get_action_number(int max_actions) const;
		void print(ostream& os) const;

		bool turn() const ;
		void card_drown(Card* card) const;
};


ostream& operator<<(ostream& os, const Ai_player& p);




#endif