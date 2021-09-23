#include "pch.h"
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

std::wostream& operator<< (std::wostream& wos, const Card& card)
{
	if (card.rank <= Ranks::Ten)
	{
		wos << (static_cast<int>(card.rank) + 2) << L" ";
	}
	else
	{
		switch (card.rank)
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

	switch (card.suit)
	{
	case Suits::Diamonds:
		wos << L"\u2666";
		break;

	case Suits::Hearts:
		wos << L"\u2665";
		break;

	case Suits::Clubs:
		wos << L"\u2663";
		break;

	case Suits::Spades:
		wos << L"\u2660";
		break;

	default:
		break;
	}

	wos << std::endl;
	return wos;
}



PlayingCards::PlayingCards()
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
			if (count_of_written < SIZE)
			{
				cards[count_of_written].rank = static_cast<Ranks>(j);
				cards[count_of_written].suit = static_cast<Suits>(i);
				++count_of_written;
			}
			else
			{
				break;
				flag_exit = true;
			}
		}
	}
}


PlayingCards::PlayingCards(size_t count)
{
	if (count > SIZE)
	{
		throw std::exception("count of random cards can't be larger than max size");
	}

	for (size_t i = 0; i < count; ++i)
	{
		Card new_card;
		int find;

		do {
			new_card = generate_random_card();
			find = this->findCard(new_card, count_of_written);
		} while (find != -1);

		cards[count_of_written] = new_card;
		++count_of_written;
	}
}


PlayingCards::PlayingCards(Suits suit_init, Ranks rank_init)
{
	cards[0] = { suit_init, rank_init };
	++count_of_written;

	for (size_t i = 1; i < SIZE; ++i)
	{
		Card new_card;
		int find;

		do {
			new_card = generate_random_card();
			find = this->findCard(new_card, count_of_written);
		} while (find != -1);

		cards[count_of_written] = new_card;
		++count_of_written;
	}
}


std::wostream& operator<<(std::wostream& wos, const PlayingCards& playing_cards)
{
	if (playing_cards.count_of_written == 0)
	{
		wos << "The deck is empty" << std::endl;
	}

	for (size_t i = 0; i < playing_cards.count_of_written; ++i)
	{
		wos << playing_cards.cards[i];
	}
	return wos;
}

Ranks PlayingCards::getRank(size_t i) const
{
	if (i < 0 || i >= SIZE)
	{
		throw std::exception("invalid index");
	}
	return cards[i].rank;
}

Suits PlayingCards::getSuit(size_t i) const
{
	if (i < 0 || i >= SIZE)
	{
		throw std::exception("invalid index");
	}
	return cards[i].suit;
}

int PlayingCards::findCard(const Card& card, size_t count) const
{
	for (size_t i = 0; i < count; ++i)
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
	if (count_of_written == SIZE)
	{
		throw std::exception("deck is full");
	}

	if (PlayingCards::findCard(card, count_of_written) != -1)
	{
		throw std::exception("card already exists");
	}

	cards[count_of_written] = card;
	++count_of_written;

	return *this;
}


PlayingCards& PlayingCards::sort()
{
	std::sort(cards, cards + count_of_written,
		[](const Card& card_1, const Card& card_2) { return card_1.suit < card_2.suit; });


	
	size_t index_start_of_one_suit = 0, index_end_of_one_suit = 1;

	size_t count_of_suits = static_cast<size_t>(Suits::Count);
	for (size_t i = 0; i < count_of_suits; ++i)
	{
		for (size_t j = index_end_of_one_suit; j < count_of_written; ++j)
		{
			if (cards[j].suit != cards[j - 1].suit)
			{
				index_end_of_one_suit = j;
				break;
			}

			if (j == count_of_written - 1)
			{
				index_end_of_one_suit = count_of_written;
				break;
			}
		}

		std::sort(cards + index_start_of_one_suit, cards + index_end_of_one_suit,
			[](const Card& card_1, const Card& card_2) { return card_1.rank > card_2.rank; });


		index_start_of_one_suit = index_end_of_one_suit;
		++index_end_of_one_suit;
	}

	return *this;
}

PlayingCards::~PlayingCards()
{

}
