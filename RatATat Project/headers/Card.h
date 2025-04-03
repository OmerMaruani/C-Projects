#ifndef _CARD_H_
#define _CARD_H_



#define rat_diff_cardstype 4 //must use those defines, so in private rat_card i can give size to static int* cards_left
#define cat_diff_cardstype 6



//problem with the headers files, this class forward declare not allow me to get the real class
class Player;
class RatATat;


class Card {


private:
		int m_value;
		string m_text;
		static const unsigned total_card;
		

	public:

		//use default?
		Card(int val=0, const string& txt="none");
		virtual ~Card(); //allow derived class to use their destructor poly


		//getter,setter
		int get_val() const;
		const string get_text() const; 
		static unsigned get_total_cards();

		void set_val(int& val);
		void set_text(const string& text);


		
		virtual void print(ostream& os) const {};


		//pure virtual
		virtual void use(Player** players, int curr_player, RatATat&rat) = 0;
		virtual void print_card_action_menu() const = 0;
		virtual int get_card_action_menu_max_num() const = 0;



		
		


};


ostream& operator<<(ostream& os, const Card& c);






class Play_card: public Card
{
	private:
		static const unsigned action_menu;


	public:
		Play_card(const unsigned val,const string & txt);
		~Play_card();

		
		void print(ostream& os) const;
		void use(Player** players, int curr_player, RatATat& rat) ;
		void print_card_action_menu() const;
		int get_card_action_menu_max_num() const; //could be static
		

};

ostream& operator<<(ostream& os, const Play_card& play_card);















class Rat_card : public Play_card
{
	private:
		static unsigned num_cards;
		static int cards_left[rat_diff_cardstype]; //arr[0]- num6 card, arr[3]- num9 card 
		//static int rat_diff_cardstype;
		


	public:
		Rat_card(const unsigned val = Rat_card::toss_val());
		~Rat_card();
		
		

		static int get_total_cards();
		static int toss_val();

};







//need to check for destructor if to num_cards-- , seems not because this always using in the discard pile

class Cat_card : public Play_card
{

	private:
		static unsigned num_cards;
		static int cards_left[cat_diff_cardstype]; //arr[0]- num0 card, arr[5]- num6 card 



		

	public:
		Cat_card(const unsigned val = Cat_card::toss_val());
		~Cat_card();


		static int get_total_cards();
		static int toss_val();


};













class Speical_card : public Card
{

	private:
		static const unsigned action_menu;
	 



	public:
		Speical_card(const string & txt);
		~Speical_card();


		void print(ostream& os) const;


		virtual void use(Player** players, int curr_player, RatATat& rat) =0;
		void print_card_action_menu() const ; 
		int get_card_action_menu_max_num() const;
		


};


ostream& operator<<(ostream& os, const Speical_card& speical_card);




//need to check if can do template to that

class Swap_card : public Speical_card
{

	private:
		static unsigned num_cards;



	public:
		Swap_card();
		~Swap_card();

	
		void use(Player** players, int curr_player, RatATat& rat) ;
		static unsigned get_total_cards();

};




class Peek_card : public Speical_card
{

	private:
		static unsigned num_cards;


	public:
		Peek_card();
		~Peek_card();

		
		void use(Player** players, int curr_player, RatATat& rat);
		static unsigned get_total_cards();


};




class Draw2_card: public Speical_card
{

	private:
		static unsigned num_cards;


	public:
		Draw2_card();
		~Draw2_card();

		
		void use(Player** players, int curr_player, RatATat& rat);
		static unsigned get_total_cards();


};



#endif