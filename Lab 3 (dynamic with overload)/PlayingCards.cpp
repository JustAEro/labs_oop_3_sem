#include <iostream>
#include <random>
#include <utility>
#include <algorithm>
#include <stdexcept>
#include <limits>
#include "PlayingCards.h"


Card generate_random_card()
{
	std::random_device rd;
	std::mt19937 mersenne(rd());

	Suits suit = static_cast<Suits>( mersenne() % static_cast<unsigned int>(Suits::Count) );
    Ranks rank = static_cast<Ranks>( mersenne() % static_cast<unsigned int>(Ranks::Count) );

	return { suit, rank };
}


bool operator== (const Card& card_1, const Card& card_2)
{
	return (card_1.rank == card_2.rank) && (card_1.suit == card_2.suit);
}


std::wostream& operator<< (std::wostream& wos, const Ranks& rank)
{
	if (rank <= Ranks::Ten)
	{
		wos << (static_cast<int>(rank) + 2) << L" ";
	}
	else
	{
		switch (rank)
		{
		case Ranks::Jack:
			wos << L"J ";
			break;

		case Ranks::Queen:
			wos << L"Q ";
			break;

		case Ranks::King:
			wos << L"K ";
			break;

		case Ranks::Ace:
			wos << L"A ";
			break;

		default:
			break;
		}
	}

	return wos;
}


std::wostream& operator<< (std::wostream& wos, const Suits& suit)
{
	switch (suit)
	{
	case Suits::Diamonds:
		wos << L'\u2666';
		break;

	case Suits::Hearts:
		wos << L'\u2665';
		break;

	case Suits::Clubs:
		wos << L'\u2663';
		break;

	case Suits::Spades:
		wos << L'\u2660';
		break;

	default:
		break;
	}

	return wos;
}


std::wostream& operator<< (std::wostream& wos, const Card& card)
{
	wos << card.rank << card.suit << std::endl;

	return wos;
}


void PlayingCards::copy_deck(const Card* src, Card* dest, size_t src_len)
{
	if (src == nullptr)
	{
		return;
	}

	for (size_t i = 0; i < src_len; ++i)
	{
		dest[i] = src[i];
	}
}

PlayingCards::PlayingCards() : current_count{ 0 }, cards { new Card[MAX_SIZE] }, capacity { MAX_SIZE }
{
	size_t suits_count = static_cast<size_t>(Suits::Count);
	size_t ranks_count = static_cast<size_t>(Ranks::Count);

	bool flag_exit = false;

	for (size_t i = 0; i < suits_count; ++i)
	{
		if (flag_exit) 
		{
			break;
		}

		for (size_t j = 0; j < ranks_count; ++j)
		{
			if (current_count < MAX_SIZE)
			{
				cards[current_count].rank = static_cast<Ranks>(j);
				cards[current_count].suit = static_cast<Suits>(i);
				++current_count;
			}
			else
			{
				break;
				flag_exit = true;
			}
		}
	}
}


PlayingCards::PlayingCards(int count): current_count{ 0 }, cards { nullptr }, capacity { 0 }
{
	if (count < 0 || static_cast<size_t>(count) > MAX_SIZE)
	{
		throw std::logic_error("count of random cards can't be larger than max size or negative");
	}

	for (int i = 0; i < count; ++i)
	{
		PlayingCards::addNewRandomCard();
	}
}


PlayingCards::PlayingCards(Card card_init) : current_count{ 1 }, cards{ new Card[QUOTA] }, capacity{ QUOTA }
{
	cards[0] = card_init;
}


PlayingCards::PlayingCards(const PlayingCards& playing_cards): current_count{ playing_cards.current_count }, cards{ nullptr }, capacity { playing_cards.capacity }
{
	std::wcout << L"Copy constructor" << std::endl;

	if (current_count != 0)
	{
		cards = new Card[capacity];
	}
	
	copy_deck(playing_cards.cards, cards, current_count);
}


PlayingCards::PlayingCards(PlayingCards&& playing_cards) noexcept: current_count{ playing_cards.current_count }, cards{ playing_cards.cards }, capacity{ playing_cards.capacity }
{
	std::wcout << L"Moving constructor" << std::endl;

	playing_cards.cards = nullptr;
}


std::wostream& operator<<(std::wostream& wos, const PlayingCards& playing_cards)
{
	if (playing_cards.current_count == 0)
	{
		wos << "The deck is empty" << std::endl;
	}

	for (size_t i = 0; i < playing_cards.current_count; ++i)
	{
		wos << playing_cards.cards[i];
	}
	return wos;
}


int PlayingCards::findCard(const Card& card) const
{
	for (size_t i = 0; i < current_count; ++i)
	{
		if (cards[i] == card)
		{
			return static_cast<int>(i);
		}
	}
	return -1;
}


PlayingCards& PlayingCards::addNewRandomCard()
{
	if (current_count == MAX_SIZE)
	{
		throw std::logic_error("deck is full");
	}

	Card new_card;
	int find = 0;

	do {
		new_card = generate_random_card();
		find = PlayingCards::findCard(new_card);
	} while (find != -1);

	if (capacity == current_count)
	{
		if (capacity + QUOTA > MAX_SIZE)
		{
			capacity = MAX_SIZE;
		}
		else
		{
			capacity += QUOTA;
		}
		Card* cards_new = new Card[capacity];
		copy_deck(cards, cards_new, current_count);
		delete[] cards;
		cards = cards_new;
	}

	cards[current_count] = new_card;
	++current_count;

	return *this;
}


PlayingCards& PlayingCards::sort()
{
	std::sort(cards, cards + current_count,
		[](const Card& card_1, const Card& card_2) {		if (card_1.suit == card_2.suit)
															{
																return card_1.rank > card_2.rank;
															}

															return card_1.suit < card_2.suit;
												   });


	return *this;
}

PlayingCards PlayingCards::subGroupOfSameSuit(Suits suit) const noexcept
{
	PlayingCards result(0);
	for (size_t i = 0; i < current_count; ++i)
	{
		if (cards[i].suit == suit)
		{
			result += cards[i];
		}
	}
	return result;
}


PlayingCards& PlayingCards::operator= (const PlayingCards& playing_cards)
{
	std::wcout << L"Copying =" << std::endl;

	if (this == &playing_cards)
	{
		return *this;
	}

	if (cards != nullptr)
	{
		delete[] cards;
	}

	current_count = playing_cards.current_count;
	capacity = playing_cards.capacity;
	cards = new Card[capacity];
	
	copy_deck(playing_cards.cards, cards, current_count);

	return *this;
}


PlayingCards& PlayingCards::operator= (PlayingCards&& playing_cards) noexcept
{
	std::wcout << L"Moving =" << std::endl;

	if (this == &playing_cards)
	{
		return *this;
	}

	if (cards != nullptr)
	{
		delete[] cards;
	}

	current_count = playing_cards.current_count;
	cards = playing_cards.cards;
	capacity = playing_cards.capacity;

	playing_cards.cards = nullptr;
	return *this;
}


const Card& PlayingCards::operator[] (int i) const
{
	if (i < 0 || i >= static_cast<int>(current_count))
	{
		throw std::range_error("invalid index");
	}

	return cards[i];
}


PlayingCards& PlayingCards::operator+= (Card card)
{
	if (current_count == MAX_SIZE)
	{
		throw std::logic_error("deck is full");
	}

	if (PlayingCards::findCard(card) != -1)
	{
		throw std::logic_error("card already exists");
	}

	if (capacity == current_count)
	{
		if (capacity + QUOTA > MAX_SIZE)
		{
			capacity = MAX_SIZE;
		}
		else
		{
			capacity += QUOTA;
		}
		Card* cards_new = new Card[capacity];
		copy_deck(cards, cards_new, current_count);
		delete[] cards;
		cards = cards_new;
	}

	cards[current_count] = card;
	++current_count;

	return *this;
}


PlayingCards& PlayingCards::operator++()
{
	PlayingCards::addNewRandomCard();
	return *this;
}


const PlayingCards PlayingCards::operator++(int)
{
	PlayingCards prev(*this);
	PlayingCards::addNewRandomCard();
	return prev;
}


PlayingCards::~PlayingCards()
{
	std::wcout << L"Destructor" << std::endl;
	delete[] cards;
}
