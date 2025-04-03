#ifndef _PILE_H_
#define _PILE_H_

//#include "Card.h"
//#include "RatATat.h"

#include <ctime>     // For time()


//need to check for template in the new box
//need to check for cunstrcutor calling the new box

class Pile {


	private:

		Card** m_cards;
		int m_i; 

		string m_type; // to let destructor delete cards only by draw pile
		static const unsigned total_cards; 


	public:

		Pile(const string &type);
		~Pile();
	

	
		static int get_len();
		int get_curr_i() const;

		bool push_back(  Card* card);
		Card* pop();
		const Card* top() const;
		int size() const;
		bool empty() const;
		bool full() const;

		void print_last_card() const;

		void new_pile();
		void shuffle();

		
		

		//template <class T>
		//friend void get_cards(Pile& p, const T& type_card, int size);
		
};




template <class T>
void my_swap(T& a, T& b)
{
	T t = a;
	a = b;
	b = t;
}











//
//
//template <class T>
//void get_cards(Pile &p ,const T &type_card,int size)
//{
//	Card* card = nullptr;
//	for (int i = 0; i < size; i++)
//	{ 
//		card = new T;
//		p.
//		
//		
//
//}

#endif