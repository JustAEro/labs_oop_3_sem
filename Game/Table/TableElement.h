#pragma once
#include <array>
#include <vector>
#include <utility>
#include <map>
#include "../Ships/Ship.h"

//std::array <char, 6> Aliases = { 'A', 'B', 'C', '1', '2', '3' };

class TableIterator
{
private:

	std::map<int, Ship*>::iterator cur;

public:
	TableIterator() : cur()
	{}

	TableIterator(const std::map<int, Ship*>::iterator& elPtr) : cur(elPtr)
	{}

	std::pair<int, Ship*> operator* ()  { return *cur; }

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

};


class ConstTableIterator
{
private:

	std::map<int, Ship*>::const_iterator cur;

public:
	ConstTableIterator() : cur()
	{}

	ConstTableIterator(const std::map<int, Ship*>::const_iterator& elPtr) : cur(elPtr)
	{}

	std::pair<int, Ship*> operator* () { return *cur; }

	bool operator== (const ConstTableIterator& it) const { return (it.cur == cur); }
	bool operator!= (const ConstTableIterator& it) const { return (it.cur != cur); }

	ConstTableIterator& operator++()
	{
		++cur;
		return *this;
	}

	ConstTableIterator operator++(int)
	{
		ConstTableIterator prev(*this);
		cur++;
		return prev;
	}

	ConstTableIterator& operator--()
	{
		--cur;
		return *this;
	}

	ConstTableIterator operator--(int)
	{
		ConstTableIterator prev(*this);
		cur--;
		return prev;
	}

};


class Table
{
	friend class TableIterator;
	friend class ConstTableIterator;

	using iterator = TableIterator;
	using const_iterator = ConstTableIterator;

private:
	std::map<int, Ship*> tableElements;

public:
	Table() : tableElements{}
	{}

	Table(const std::map<int, Ship*>& elements_) : tableElements(elements_)
	{}

	Ship* getShipByID(int id) const;
	int getCountOfShips() const;

	int addShip(Ship* ship_);
	int removeShip(int id);

	TableIterator begin() noexcept { return TableIterator(tableElements.begin()); }
	TableIterator end() noexcept { return TableIterator(tableElements.end()); }

	ConstTableIterator cbegin() const noexcept { return ConstTableIterator(tableElements.cbegin()); }
	ConstTableIterator cend() const noexcept { return ConstTableIterator(tableElements.cend()); }

	~Table();
};



