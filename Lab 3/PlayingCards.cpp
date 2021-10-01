#include <iostream>
#include <random>
#include <utility>
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


std::wostream& operator<< (std::wostream& wos, const VectorOfCards& vec_of_cards)
{
	if (vec_of_cards.size == 0)
	{
		wos << L"No cards of this suit";
	}

	else
	{
		wos << L"The cards of this suit:" << std::endl;
	}
	

	size_t n = vec_of_cards.size;
	for (size_t i = 0; i < n; ++i)
	{
		wos << vec_of_cards.vector[i];
	}

	return wos;
}


PlayingCards::PlayingCards() : current_count{ 0 }, cards {} 
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


PlayingCards::PlayingCards(int count): current_count{ 0 }
{
	if (count < 0 || count > MAX_SIZE)
	{
		throw std::exception("count of random cards can't be larger than max size or negative");
	}

	count = static_cast<size_t>(count);

	for (size_t i = 0; i < count; ++i)
	{
		PlayingCards::addNewRandomCard();
	}
}


PlayingCards::PlayingCards(Card card_init): current_count{ 0 }
{
	cards[0] = card_init;
	++current_count;
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


Ranks PlayingCards::getRank(int i) const
{
	if (i < 0 || i >= current_count)
	{
		throw std::exception("invalid index");
	}

	i = static_cast<size_t>(i);
	return cards[i].rank;
}


Suits PlayingCards::getSuit(int i) const
{
	if (i < 0 || i >= current_count)
	{
		throw std::exception("invalid index");
	}

	i = static_cast<size_t>(i);
	return cards[i].suit;
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


PlayingCards& PlayingCards::addNewCard(Card card)
{
	if (current_count == MAX_SIZE)
	{
		throw std::exception("deck is full");
	}

	if (PlayingCards::findCard(card) != -1)
	{
		throw std::exception("card already exists");
	}

	cards[current_count] = card;
	++current_count;

	return *this;
}


PlayingCards& PlayingCards::addNewRandomCard()
{
	if (current_count == MAX_SIZE)
	{
		throw std::exception("deck is full");
	}

	Card new_card;
	int find;

	do {
		new_card = generate_random_card();
		find = PlayingCards::findCard(new_card);
	} while (find != -1);


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


VectorOfCards PlayingCards::subGroupOfSameSuit(Suits suit) const noexcept
{
	VectorOfCards result = { nullptr, 0 };
	for (size_t i = 0; i < current_count; ++i)
	{
		if (cards[i].suit == suit)
		{
			Card* vector_new = new Card[result.size + 1];

			for (size_t j = 0; j < result.size; ++j) 
			{
				vector_new[j] = result.vector[j];
			}

			vector_new[result.size] = cards[i];

			delete[] result.vector;
			result.vector = vector_new;
			++result.size;
		}
	}
	return result;
}


PlayingCards::~PlayingCards()
{

}
