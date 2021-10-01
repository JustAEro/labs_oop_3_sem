#pragma once

//functions to organize the dialog, if EOF they return -1 and if they work correctly they return 0

int	D_PlayingCards_New(PlayingCards*& pc);   //construct new deck

int D_Show_Deck(PlayingCards*& pc);      //print the current deck

int D_Add_New_Random_Card(PlayingCards*& pc); //add new random card to deck

int D_Get_Suit(PlayingCards*& pc);
int D_Get_Rank(PlayingCards*& pc);
int D_Sort(PlayingCards*& pc);

int D_Subgroup_Of_Same_Suit(PlayingCards*& pc);


int D_Delete(PlayingCards*& pc);					//delete deck


int choose_suit();


void start_menu_for_playing_cards(PlayingCards*& pc);			//function to start menu in application program


int dialog(const char* msgs[], int);	//function to select the number of alternative


template <typename T> int get_T(T& x)		//get argument of T type from std::cin
{
	std::wcin >> x;
	while (!std::wcin.good())
	{
		if (std::wcin.eof() || std::wcin.bad())
		{
			return -1;   //eof or fatal error
		}


		std::wcin.clear();
		std::wcin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		std::wcin.clear();
		//ignore incorrect input until the end of the stream or until the end of the line and clear flag of errors


		std::wcout << L"You are wrong! Please, repeat input from incorrect token." << std::endl;
		std::wcin >> x;

	}
	return 0;  //ok
}