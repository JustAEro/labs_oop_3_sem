#include "TableElement.h"

int Table::getCountOfShips() const
{
	return tableElements.size();
}

int Table::addShip(Ship* ship_)
{
	int id = tableElements.size();   //id = [ 0 -> 1 -> 2 -> ... ]
	tableElements.insert(std::make_pair(id, ship_));
	return id;
}

int Table::removeShip(int id)
{
	std::map<int, Ship*>::const_iterator it = tableElements.find(id);

	if (ConstTableIterator(it) == tableElements.cend())
	{
		return -1;  //not found
	}

	delete (*it).second;
	tableElements.erase(id);
	return 0;  //ok, found and deleted
}

Ship* Table::getShipByID(int id) const
{
	std::map<int, Ship*>::const_iterator it = tableElements.find(id);

	if (ConstTableIterator(it) == Table::cend())
	{
		return nullptr;
	}

	return (*it).second;
}


Table::~Table()
{
	for (TableIterator it = Table::begin(); it != Table::end(); ++it)
	{
		delete (*it).second;
	}
}