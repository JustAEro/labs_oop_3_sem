#include "TableElement.h"
#include <stdexcept>

int Table::getCountOfShips() const
{
	return tableElements.size();
}

int Table::addShip(Ship* ship_)
{
	int id;
	if (tableElements.empty())
	{
		id = 0;
	}
	else
	{
		id = (*tableElements.rbegin()).first + 1;
	} //id = [ 0 -> 1 -> 2 -> ... ]

	bool resultOfInsert = tableElements.insert(std::make_pair(id, ship_)).second;  //true=success or false=fail

	//[0,1,2]. we delete 1 -> [0,2]. size = 2 (already exists)

	if (resultOfInsert == false)
	{
		throw std::runtime_error("Error! Can't insert ship with unique id.");
	}

	return id;
}

int Table::removeShip(int id)
{
	CustomMap<int, Ship*>::iterator it = tableElements.find(id);

	if (Table::iterator(it) == tableElements.end())
	{
		return -1;  //not found
	}

	delete (*it).second;
	tableElements.erase(id);
	return 0;  //ok, found and deleted
}

Ship* Table::getShipByID(int id) const
{
	CustomMap<int, Ship*>::const_iterator it = tableElements.find(id);

	if (Table::const_iterator(it) == Table::cend())
	{
		return nullptr;
	}

	return (*it).second;
}


Table::~Table()
{
	for (Table::iterator it = Table::begin(); it != Table::end(); ++it)
	{
		delete (*it).second;
	}
}