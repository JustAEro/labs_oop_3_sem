#include "gtest/gtest.h"
#include "PlayingCards.h"


#if defined(_MSC_VER) && !defined(__INTEL_COMPILER)

//-----includes for debugging memory leaks in VS-----/
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
//---------------------------------------------------/

#endif


TEST(DefaultConstructor, TestingDefaultConstructor)
{
	PlayingCards playing_cards;


	ASSERT_EQ(playing_cards.getCurrentCount(), playing_cards.getMaxSize());


	size_t suits_count = static_cast<size_t>(Suits::Count);
	size_t ranks_count = static_cast<size_t>(Ranks::Count);

	bool flag_exit = false;

	size_t index = 0;
	size_t current_count = playing_cards.getCurrentCount();

	for (size_t i = 0; i < suits_count; ++i)
	{
		if (flag_exit)
		{
			break;
		}

		for (size_t j = 0; j < ranks_count; ++j)
		{
			if (index < current_count)
			{
				ASSERT_EQ(static_cast<Ranks>(j), playing_cards.getRank(index));
				ASSERT_EQ(static_cast<Suits>(i), playing_cards.getSuit(index));
				
				++index;
			}
			else
			{
				break;
				flag_exit = true;
			}
		}
	}
}

TEST(DefaultConstructor, DefaultConstructorArray)
{
	size_t count = 5;
	PlayingCards* playing_cards_array = new PlayingCards[5];


	for (size_t k = 0; k < count; ++k)
	{
		ASSERT_EQ(playing_cards_array[k].getCurrentCount(), playing_cards_array[k].getMaxSize());


		size_t suits_count = static_cast<size_t>(Suits::Count);
		size_t ranks_count = static_cast<size_t>(Ranks::Count);

		bool flag_exit = false;

		size_t index = 0;
		size_t current_count = playing_cards_array[k].getCurrentCount();

		for (size_t i = 0; i < suits_count; ++i)
		{
			if (flag_exit)
			{
				break;
			}

			for (size_t j = 0; j < ranks_count; ++j)
			{
				if (index < current_count)
				{
					ASSERT_EQ(static_cast<Ranks>(j), playing_cards_array[k].getRank(index));
					ASSERT_EQ(static_cast<Suits>(i), playing_cards_array[k].getSuit(index));

					++index;
				}
				else
				{
					break;
					flag_exit = true;
				}
			}
		}
	}

	delete[] playing_cards_array;
}


TEST(InitCountConstructor, TestingInitCountConstructor)
{
	size_t count = 20;
	PlayingCards playing_cards(20);

	ASSERT_EQ(count, playing_cards.getCurrentCount());
	
	for (size_t i = 0; i < count; ++i)
	{
		Card card_1 = { playing_cards.getSuit(i), playing_cards.getRank(i) };
		
		for (size_t j = 0; j < count; ++j)
		{
			if (i != j)
			{
				Card card_2 = { playing_cards.getSuit(j), playing_cards.getRank(j) };
				ASSERT_FALSE(card_1 == card_2);
			}
		}
	}
}


TEST(InitCountConstructorThrow, TestingInitCountConstructor)
{
	ASSERT_ANY_THROW(PlayingCards(53));
	ASSERT_ANY_THROW(PlayingCards(-1));
}


TEST(InitCardConstructor, TestingInitCardConstructor)
{
	Card card_init = { Suits::Clubs, Ranks::Ace };

	PlayingCards playing_cards(card_init);

	ASSERT_EQ(1, playing_cards.getCurrentCount());

	Card first_card = { playing_cards.getSuit(0), playing_cards.getRank(0) };
	ASSERT_EQ(card_init, first_card);
}


TEST(CopyConstuctor, TestingCopyConstructor)
{
	PlayingCards playing_cards;

	PlayingCards pc_copy(playing_cards);

	ASSERT_EQ(pc_copy.getCurrentCount(), playing_cards.getCurrentCount());

	size_t n = playing_cards.getCurrentCount();
	
	for (size_t i = 0; i < n; ++i)
	{
		ASSERT_EQ(playing_cards[i], pc_copy[i]);
	}


	PlayingCards pc_2(0);
	PlayingCards pc_2_copy(pc_2);
	ASSERT_EQ(pc_2.getCurrentCount(), 0);
	ASSERT_EQ(pc_2_copy.getCurrentCount(), 0);
}


TEST(AssignmentOperator, OperatorTest)
{
	PlayingCards playing_cards;

	PlayingCards pc_2 = playing_cards;
	ASSERT_EQ(pc_2.getCurrentCount(), playing_cards.getCurrentCount());

	size_t n = playing_cards.getCurrentCount();

	for (size_t i = 0; i < n; ++i)
	{
		ASSERT_EQ(playing_cards[i], pc_2[i]);
	}


	Card card_init = { Suits::Clubs, Ranks::Ace };
	PlayingCards pc_3(card_init);

	pc_2 = pc_3;
	ASSERT_EQ(pc_2.getCurrentCount(), pc_3.getCurrentCount());
	n = pc_2.getCurrentCount();

	for (size_t i = 0; i < n; ++i)
	{
		ASSERT_EQ(pc_3[i], pc_2[i]);
	}
}


TEST(IndexingOperatorTesting, OperatorTest)
{
	PlayingCards playing_cards(20);
	ASSERT_THROW(playing_cards[21], std::range_error);
	ASSERT_THROW(playing_cards[-1], std::range_error);
}


TEST(GetterRankThrow, TestingGetters)
{
	PlayingCards playing_cards(20);
	ASSERT_ANY_THROW(playing_cards.getRank(21));
	ASSERT_ANY_THROW(playing_cards.getRank(-1));
}


TEST(GetterSuitThrow, TestingGetters)
{
	PlayingCards playing_cards(20);
	ASSERT_ANY_THROW(playing_cards.getSuit(21));
	ASSERT_ANY_THROW(playing_cards.getSuit(-1));
}


TEST(FindCard, FindingCards)
{
	PlayingCards playing_cards;

	for (size_t i = 0; i < playing_cards.getMaxSize(); ++i)
	{
		Card card = { playing_cards.getSuit(i), playing_cards.getRank(i) };

		ASSERT_FALSE(-1 == playing_cards.findCard(card));
		ASSERT_EQ(i, playing_cards.findCard(card));
	}

	
	Card card_init = { Suits::Clubs, Ranks::Ace };

	PlayingCards playing_cards_2(card_init);

	Card not_existing_card = { Suits::Diamonds, Ranks::Eight };
	ASSERT_EQ(-1, playing_cards_2.findCard(not_existing_card));
}


TEST(AddNewCard, AddingCard)
{
	Card card_init = { Suits::Clubs, Ranks::Ace };

	PlayingCards playing_cards(card_init);

	Card card_to_add = { Suits::Diamonds, Ranks::Five };
	playing_cards.addNewCard(card_to_add);

	ASSERT_EQ(2, playing_cards.getCurrentCount());

	Card card_new = { playing_cards.getSuit(1), playing_cards.getRank(1) };
	ASSERT_EQ(card_to_add, card_new);
}


TEST(AddNewCardThrowSizeException, AddingCard)
{
	PlayingCards playing_cards;
	Card card_to_add = { Suits::Clubs, Ranks::Ace };
	
	ASSERT_ANY_THROW(playing_cards.addNewCard(card_to_add));

}


TEST(AddNewCardThrowExistException, AddingCard)
{
	Card card_init = { Suits::Clubs, Ranks::Ace };

	PlayingCards playing_cards(card_init);

	ASSERT_ANY_THROW(playing_cards.addNewCard(card_init));
}


TEST(AdditionAssignmentOperatorTesting, OperatorTest)
{
	Card card_init = { Suits::Clubs, Ranks::Ace };

	PlayingCards playing_cards(card_init);

	Card card_to_add = { Suits::Diamonds, Ranks::Five };
	playing_cards += card_to_add;

	ASSERT_EQ(2, playing_cards.getCurrentCount());

	Card card_new = playing_cards[1];
	ASSERT_EQ(card_to_add, card_new);
}


TEST(AdditionAssignmentOperatorThrowsExceptionOfFullDeck, OperatorTest)
{
	PlayingCards playing_cards;
	Card card_to_add = { Suits::Clubs, Ranks::Ace };

	ASSERT_THROW(playing_cards += card_to_add, std::logic_error);
}


TEST(AdditionAssignmentOperatorThrowsExceptionOfExistingCard, OperatorTest)
{
	Card card_init = { Suits::Clubs, Ranks::Ace };

	PlayingCards playing_cards(card_init);

	ASSERT_THROW(playing_cards += card_init, std::logic_error);
}


TEST(AddNewRandomCard, AddingCard)
{
	Card card_init = { Suits::Clubs, Ranks::Ace };

	PlayingCards playing_cards(card_init);

	playing_cards.addNewRandomCard();

	ASSERT_EQ(2, playing_cards.getCurrentCount());

	Card card_new = { playing_cards.getSuit(1), playing_cards.getRank(1) };

	ASSERT_FALSE(card_new == card_init);
}


TEST(AddNewRandomCardThrowSizeException, AddingCard)
{
	PlayingCards playing_cards;

	ASSERT_ANY_THROW(playing_cards.addNewRandomCard());

}


TEST(IncrementPrefixOperatorTest, OperatorTest)
{
	Card card_init = { Suits::Clubs, Ranks::Ace };

	PlayingCards playing_cards(card_init);

	++playing_cards;

	ASSERT_EQ(2, playing_cards.getCurrentCount());

	Card card_new = playing_cards[1];

	ASSERT_FALSE(card_new == card_init);
}


TEST(IncrementPrefixOperatorThrowsException, AddingCard)
{
	PlayingCards playing_cards;

	ASSERT_THROW(++playing_cards, std::logic_error);

}


TEST(IncrementPostfixOperatorTest, OperatorTest)
{
	Card card_init = { Suits::Clubs, Ranks::Ace };

	PlayingCards playing_cards(card_init);

	PlayingCards pc_prev = playing_cards++;

	ASSERT_EQ(1, pc_prev.getCurrentCount());
	ASSERT_EQ(pc_prev[0], card_init);

	ASSERT_EQ(2, playing_cards.getCurrentCount());

	Card card_new = playing_cards[1];

	ASSERT_FALSE(card_new == card_init);
}


TEST(IncrementPostfixOperatorThrowsException, AddingCard)
{
	PlayingCards playing_cards;

	ASSERT_THROW(playing_cards++, std::logic_error);

}


TEST(GroupOfSameSuit, FindingTheGroupOfSameSuit)
{
	PlayingCards playing_cards;

	PlayingCards subGroup = playing_cards.subGroupOfSameSuit(Suits::Diamonds);

	int count = static_cast<int>(subGroup.getCurrentCount());
	ASSERT_EQ(13, count);

	ASSERT_EQ(52, playing_cards.getCurrentCount());

	for (int i = 0; i < count; ++i)
	{
		ASSERT_FALSE(-1 == playing_cards.findCard(subGroup[i]));
	}
}


TEST(SortOfDeck, SortingOfDeck)
{
	PlayingCards playing_cards;

	playing_cards.sort();


	size_t index_start_of_one_suit = 0, index_end_of_one_suit = 1;

	size_t count_of_suits = static_cast<size_t>(Suits::Count);
	size_t current_count = playing_cards.getCurrentCount();


	for (size_t i = 0; i < count_of_suits; ++i)
	{
		for (size_t j = index_end_of_one_suit; j < current_count; ++j)
		{
			if (playing_cards.getSuit(j) != playing_cards.getSuit(j - 1))
			{
				index_end_of_one_suit = j;
				break;
			}

			if (j == current_count - 1)
			{
				index_end_of_one_suit = current_count;
				break;
			}
		}

		Suits current_suit = playing_cards.getSuit(index_start_of_one_suit);
		for (size_t k = index_start_of_one_suit; k < index_end_of_one_suit; ++k)
		{
			ASSERT_EQ(current_suit, playing_cards.getSuit(k));
		}

		Ranks rank_prev = playing_cards.getRank(index_start_of_one_suit);
		for (size_t k = index_start_of_one_suit + 1; k < index_end_of_one_suit; ++k)
		{
			ASSERT_TRUE(playing_cards.getRank(k) < rank_prev);
			rank_prev = playing_cards.getRank(k);
		}

		index_start_of_one_suit = index_end_of_one_suit;
		++index_end_of_one_suit;
	}
}


int main(int argc, wchar_t *argv[])
{
    #if defined (_MSC_VER) && !defined (__INTEL_COMPILER)
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);   //flag to detect memory leaks in VS
	#endif

	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}