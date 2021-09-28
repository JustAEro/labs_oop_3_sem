#include "Menu.h"


int D_PlayingCards_New(PlayingCards*& pc)
{
	std::wcout << "Creating a new deck" << std::endl;

	if (pc != nullptr)
	{
		std::wcout << L"The deck is not empty! The new one will be created and the old one will be deleted" << std::endl;
	}

	std::wcout << L"Enter the number of cards in deck" << std::endl;

	int n;
	int status = get_T(n);

	if (status == -1)
	{
		return -1; //eof
	}

	PlayingCards* pc_new = nullptr;
	try
	{
		pc_new = new PlayingCards(n);
	}

	catch (std::exception& ex)
	{
		std::wcout << ex.what() << std::endl;
		std::wcout << L"Deck with this configuration doesn't exist! The previous deck is saved!" << std::endl;
		delete pc_new;   
		return 0;
	}

	delete pc;
	pc = pc_new;

	return 0;
}


int D_Sort(PlayingCards*& pc)
{
	if (pc == nullptr)
	{
		std::wcout << L"The deck is empty! Create new deck to operate with it" << std::endl;
		return 0;
	}

	else
	{
		pc->sort();
	}

	std::wcout << L"The deck has been sorted" << std::endl;
	return 0;
}


int D_Get_Rank(PlayingCards*& pc)
{
	if (pc == nullptr)
	{
		std::wcout << L"The deck is empty! Create new deck to operate with it" << std::endl;
		return 0;
	}

	std::wcout << L"Enter the index of the card: ";
	int index;
	int status = get_T(index);;

	if (status == -1)
	{
		return -1; //eof
	}

	Ranks rank;
	try
	{
		rank = pc->getRank(index);
	}

	catch (std::exception& ex)
	{
		std::wcout << ex.what() << std::endl;
		return 0;
	}

	std::wcout << L"The rank is: " << rank << std::endl;

	return 0;
}


int D_Get_Suit(PlayingCards*& pc)
{
	if (pc == nullptr)
	{
		std::wcout << L"The deck is empty! Create new deck to operate with it" << std::endl;
		return 0;
	}

	std::wcout << L"Enter the index of the card: ";
	int index;
	int status = get_T(index);;
	
	if (status == -1)
	{
		return -1; //eof
	}

	Suits suit;
	try
	{
		suit = pc->getSuit(index);
	}

	catch (std::exception& ex)
	{
		std::wcout << ex.what() << std::endl;
		return 0;
	}

	std::wcout << L"The suit is: " << suit << std::endl;

	return 0;
}


int D_Subgroup_Of_Same_Suit(PlayingCards*& pc)
{
	if (pc == nullptr)
	{
		std::wcout << L"The deck is empty! Create new deck to operate with it" << std::endl;
	}

	else
	{
		int number_of_suit = choose_suit();
		if (number_of_suit < 0)
		{
			std::wcout << L"You have exited the function" << std::endl;
			return 0;
		}

		Suits suit = static_cast<Suits>(number_of_suit);
		VectorOfCards vec_of_cards = pc->subGroupOfSameSuit(suit);
		
		std::wcout << vec_of_cards;

		delete[] vec_of_cards.vector;
	}
	return 0;
}


int D_Show_Deck(PlayingCards*& pc)
{
	if (pc == nullptr)
	{
		std::wcout << L"The deck is empty! Create new deck to operate with it" << std::endl;
		return 0;
	}

	std::wcout << L"The deck is:" << std::endl;
	std::wcout << (*pc);
	return 0;
}


int D_Delete(PlayingCards*& pc)
{
	if (pc == nullptr)
	{
		std::wcout << L"Nothing to delete. The deck is empty." << std::endl;
	}

	delete pc;
	pc = nullptr;

	return 0;
}


int D_Add_New_Random_Card(PlayingCards*& pc)
{
	if (pc == nullptr)
	{
		std::wcout << L"The deck is empty! Create new deck to operate with it" << std::endl;
		return 0;
	}

	try
	{
		pc->addNewRandomCard();
	}

	catch (std::exception& ex)
	{
		std::wcout << ex.what() << std::endl;
		return 0;
	}

	std::wcout << L"Random card has been added" << std::endl;
	return 0;
}


int dialog(const char* msgs[], int size)
{
	const char* errmsg = "";
	int number_of_altenative;


	do {
		std::wcout << errmsg << std::endl;
		errmsg = "You are wrong. Repeat, please!";

		//print the list of alternatives
		std::wcout << "Choose the number from alternatives or press 0 or Ctrl+Z to quit" << std::endl << std::endl;
		for (int i = 0; i < size; ++i)
		{
			std::wcout << msgs[i] << std::endl;
		}

		std::wcout << std::endl;
		std::wcout << "Make your choice:  --> " << std::endl;

		int n = get_T(number_of_altenative); //input the number of alternative

		if (n == -1) 
		{
			number_of_altenative = 0;
		}

	} while (number_of_altenative < 0 || number_of_altenative >= size);

	return number_of_altenative;
}


int choose_suit()
{
	const char* msgs[] = {
		"0. Quit",
		"1. Diamonds",
		"2. Hearts",
		"3. Clubs",
		"4. Spades"
	};

	//the number of alternatives
	const int menu_size = sizeof(msgs) / sizeof(msgs[0]);

	return (dialog(msgs, menu_size) - 1);
	
}


void start_menu_for_playing_cards(PlayingCards*& pc)
{
	int (*dialog_functions[])(PlayingCards * &pc) = { nullptr, D_PlayingCards_New,

															D_Show_Deck,

															D_Add_New_Random_Card,

															D_Get_Suit,
															D_Get_Rank,
															D_Sort,

															D_Subgroup_Of_Same_Suit,


															D_Delete 
													};


	//Alternatives for a dialog
	//the list of alternatives
	const char* msgs[] = { "0. Quit",   "1. Create new deck", "2. Show deck" ,

										"3. Add new random card", 

										"4. Get suit of card", "5. Get rank of card",

										"6. Sort the deck", "7. Select subgroup with suit", "8. Delete deck",

	};


	//the number of alternatives
	const int menu_size = sizeof(msgs) / sizeof(msgs[0]);

	int number_of_alternative;
	while ((number_of_alternative = dialog(msgs, menu_size)))
	{
		if (dialog_functions[number_of_alternative](pc) == -1)
		{
			break;
		}
	}

	std::wcout << L"That's all. Bye!" << std::endl;
}
