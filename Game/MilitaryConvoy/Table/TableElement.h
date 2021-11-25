#pragma once
#include <array>
#include <vector>
#include <utility>
//#include <map>
#include "../CustomMap.h"
#include "../Ships/Ship.h"

//std::array <char, 6> Aliases = { 'A', 'B', 'C', '1', '2', '3' };

class TableIterator
{
private:

	CustomMap<int, Ship*>::iterator cur;

public:
	TableIterator() : cur()
	{}

	TableIterator(const CustomMap<int, Ship*>::iterator& elPtr) : cur(elPtr)
	{}

	std::pair<int, Ship*> operator* ()  { return *cur; }

	friend bool operator== (const TableIterator& it_1, const TableIterator& it_2)  { return (it_1.cur == it_2.cur); }
	friend bool operator!= (const TableIterator& it_1, const TableIterator& it_2) { return !(it_1.cur == it_2.cur); }
	//bool operator!= (const TableIterator& it) const { return (it != cur); }

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

	CustomMap<int, Ship*>::const_iterator cur;

public:
	ConstTableIterator() : cur()
	{}

	ConstTableIterator(const CustomMap<int, Ship*>::const_iterator& elPtr) : cur(elPtr)
	{}

	std::pair<int, Ship*> operator* () { return *cur; }

	friend bool operator== (const ConstTableIterator& it_1, const ConstTableIterator& it_2) { return (it_1.cur == it_2.cur); }
	friend bool operator!= (const ConstTableIterator& it_1, const ConstTableIterator& it_2) { return !(it_1.cur == it_2.cur); }
	//bool operator== (const ConstTableIterator& it) const { return (it == cur); }
	//bool operator!= (const ConstTableIterator& it) const { return !(it == cur); }

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


class TableReverseIterator 
{
private:
	CustomMap<int, Ship*>::reverse_iterator cur;

public:
	TableReverseIterator() : cur()
	{}

	TableReverseIterator(const CustomMap<int, Ship*>::reverse_iterator& elPtr) : cur(elPtr)
	{}

	std::pair<int, Ship*> operator* () { return *cur; }

	friend bool operator== (const TableReverseIterator& it_1, const TableReverseIterator& it_2) { return (it_1.cur == it_2.cur); }
	friend bool operator!= (const TableReverseIterator& it_1, const TableReverseIterator& it_2) { return !(it_1.cur == it_2.cur); }

	//bool operator== (const TableReverseIterator& it) const { return (it == cur); }
	//bool operator!= (const TableReverseIterator& it) const { return (it != cur); }

	TableReverseIterator& operator++()
	{
		++cur;
		return *this;
	}

	TableReverseIterator operator++(int)
	{
		TableReverseIterator prev(*this);
		cur++;
		return prev;
	}

	TableReverseIterator& operator--()
	{
		--cur;
		return *this;
	}

	TableReverseIterator operator--(int)
	{
		TableReverseIterator prev(*this);
		cur--;
		return prev;
	}
};


class ConstTableReverseIterator
{
private:
	CustomMap<int, Ship*>::const_reverse_iterator cur;

public:
	ConstTableReverseIterator() = delete;  //? maybe =delete
	

	ConstTableReverseIterator(const CustomMap<int, Ship*>::const_reverse_iterator& elPtr) : cur(elPtr)
	{}

	std::pair<int, Ship*> operator* () { return *cur; }

	friend bool operator== (const ConstTableReverseIterator& it_1, const ConstTableReverseIterator& it_2) { return (it_1.cur == it_2.cur); }
	friend bool operator!= (const ConstTableReverseIterator& it_1, const ConstTableReverseIterator& it_2) { return !(it_1.cur == it_2.cur); }

	//bool operator== (const ConstTableReverseIterator& it) const { return (it == cur); }
	//bool operator!= (const ConstTableReverseIterator& it) const { return (it != cur); }

	ConstTableReverseIterator& operator++()
	{
		++cur;
		return *this;
	}

	ConstTableReverseIterator operator++(int)
	{
		ConstTableReverseIterator prev(*this);
		cur++;
		return prev;
	}

	ConstTableReverseIterator& operator--()
	{
		--cur;
		return *this;
	}

	ConstTableReverseIterator operator--(int)
	{
		ConstTableReverseIterator prev(*this);
		cur--;
		return prev;
	}
};


class Table
{
	friend class TableIterator;
	friend class ConstTableIterator;
	friend class TableReverseIterator;
	friend class ConstTableReverseIterator;

private:
	CustomMap<int, Ship*> tableElements;

public:
	using iterator = TableIterator;
	using const_iterator = ConstTableIterator;
	using reverse_iterator = TableReverseIterator;
	using const_reverse_iterator = ConstTableReverseIterator;

	Table() : tableElements{}
	{}

	Table(const CustomMap<int, Ship*>& elements_) : tableElements(elements_)
	{}

	Ship* getShipByID(int id) const;
	int getCountOfShips() const;

	int addShip(Ship* ship_);
	int removeShip(int id);

	TableIterator begin() noexcept { return TableIterator(tableElements.begin()); }
	TableIterator end() noexcept { return TableIterator(tableElements.end()); }

	ConstTableIterator cbegin() const noexcept { return ConstTableIterator(tableElements.cbegin()); }
	ConstTableIterator cend() const noexcept { return ConstTableIterator(tableElements.cend()); }

	TableReverseIterator rbegin() noexcept { return TableReverseIterator(tableElements.rbegin()); }
	TableReverseIterator rend() noexcept { return TableReverseIterator(tableElements.rend()); }

	ConstTableReverseIterator crbegin() const noexcept { return ConstTableReverseIterator(tableElements.crbegin()); }
	ConstTableReverseIterator crend() const noexcept { return ConstTableReverseIterator(tableElements.crend()); }


	~Table();
};



