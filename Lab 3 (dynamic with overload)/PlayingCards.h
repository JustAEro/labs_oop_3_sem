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

std::wostream& operator<< (std::wostream& wos, const Suits& suit);
std::wostream& operator<< (std::wostream& wos, const Ranks& rank);

std::wostream& operator<< (std::wostream& wos, const Card& card);


class PlayingCards
{
public:
	PlayingCards();
	explicit PlayingCards(int count);
	explicit PlayingCards(Card card_init);
	PlayingCards(const PlayingCards& playing_cards);
	PlayingCards(PlayingCards&& playing_cards) noexcept;

	~PlayingCards();

	//getters
	size_t getMaxSize() const noexcept { return MAX_SIZE; }
	size_t getCurrentCount() const noexcept { return current_count; }
	
	PlayingCards& addNewRandomCard();

	PlayingCards& sort();

	int findCard(const Card& card) const;

	PlayingCards subGroupOfSameSuit(Suits suit) const noexcept;
	
	PlayingCards& operator= (const PlayingCards& playing_cards);
	PlayingCards& operator= (PlayingCards&& playing_cards) noexcept;

	const Card& operator[] (int i) const;


	PlayingCards& operator+= (Card card);

	PlayingCards& operator++();
	const PlayingCards operator++(int);


	friend std::wostream& operator<< (std::wostream& wos, const PlayingCards& playing_cards);


private:
	static const size_t MAX_SIZE = 52;
	static const size_t QUOTA = MAX_SIZE / (static_cast<size_t>(Suits::Count));
	size_t capacity;
	size_t current_count;
	Card* cards;

	static void copy_deck(const Card* src, Card* dest, size_t len);
};

