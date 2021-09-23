#pragma once

enum class Suits
{
	Diamonds,
	Hearts,
	Clubs,
	Spades,

	Count
};

enum class Ranks 
{
	Two, Three, Four, Five, Six, Seven, Eight, Nine, Ten, 
	Jack, Queen, King, Ace,

	Count
};

struct Card
{
	Suits suit;
	Ranks rank;
};


Card generate_random_card();


bool operator== (const Card& card_1, const Card& card_2);
std::wostream& operator<< (std::wostream& wos, const Card& card);



class PlayingCards
{
public:
	PlayingCards();
	PlayingCards(size_t count);
	PlayingCards(Suits suit_init, Ranks rank_init);

	~PlayingCards();

	//getters
	Ranks getRank(size_t i) const;
	Suits getSuit(size_t i) const;

	PlayingCards& addNewCard(Card card);

	PlayingCards& sort();
	
	friend std::wostream& operator<< (std::wostream& wos, const PlayingCards& playing_cards);


private:
	static const size_t SIZE = 52;
	size_t count_of_written = 0;
	Card cards[SIZE];

	int findCard(const Card& card,  size_t length) const;
};

