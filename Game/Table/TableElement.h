#pragma once
#include <array>
#include <vector>
#include "../Ships/Ship.h"

//std::array <char, 6> Aliases = { 'A', 'B', 'C', '1', '2', '3' };

class TableElement
{
private:
	Ship* ship;
	int id;

public:
	TableElement() : ship(nullptr), id(0) 
	{}

	TableElement(Ship* ship_, int id_) : ship(ship_), id(id_)
	{}
	
};

class TableIterator
{
private:
	TableElement* cur;

public:
	TableIterator() : cur(nullptr)
	{}

	TableIterator(TableElement* elPtr) : cur(elPtr)
	{}

	TableElement& operator* () const { return *cur; }

	bool operator== (const TableIterator& it) const { return (it.cur == cur); }
	bool operator!= (const TableIterator& it) const { return (it.cur != cur); }

	TableIterator& operator++()
	{
		++cur;
		return *this;
	}

	TableIterator operator++(int)
	{
		TableIterator prev(*this);
		cur++;
		return prev;
	}

	TableIterator& operator--()
	{
		--cur;
		return *this;
	}

	TableIterator operator--(int)
	{
		TableIterator prev(*this);
		cur--;
		return prev;
	}


	TableIterator& operator+(int n)
	{
		cur += n;
		return *this;
	}

	TableIterator& operator-(int n)
	{
		cur -= n;
		return *this;
	}
};


class Table
{
	friend class TableIterator;

private:
	std::vector <TableElement> tableElements;

public:
	Table() : tableElements()
	{}

	Table(std::vector <TableElement>& elements) : tableElements(elements)
	{}



	Ship* getShipByID(int id) const;
	int getCountOfShips() const;

	Table& addShip();
	Table& removeShip();

	TableIterator begin() { return TableIterator(&tableElements[0]); }
	TableIterator end() { return TableIterator(&tableElements[0] + tableElements.size()); }
};



