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

struct VectorOfCards
{
	Card* vector;
	size_t size;
};

Card generate_random_card();


bool operator== (const Card& card_1, const Card& card_2);

std::wostream& operator<< (std::wostream& wos, const Suits& suit);
std::wostream& operator<< (std::wostream& wos, const Ranks& rank);

std::wostream& operator<< (std::wostream& wos, const Card& card);


std::wostream& operator<< (std::wostream& wos, const VectorOfCards& vec_of_cards);


class PlayingCards
{
public:
	PlayingCards();
	PlayingCards(int count);
	PlayingCards(Card card_init);

	~PlayingCards();

	//getters
	const size_t getMaxSize() const noexcept { return MAX_SIZE; }
	size_t getCurrentCount() const noexcept { return current_count; }
	Ranks getRank(int i) const;
	Suits getSuit(int i) const;

	PlayingCards& addNewCard(Card card);
	PlayingCards& addNewRandomCard();

	PlayingCards& sort();

	int findCard(const Card& card) const;

	VectorOfCards subGroupOfSameSuit(Suits suit);
	
	friend std::wostream& operator<< (std::wostream& wos, const PlayingCards& playing_cards);


private:
	static const size_t MAX_SIZE = 52;
	size_t current_count;
	Card cards[MAX_SIZE];
};

