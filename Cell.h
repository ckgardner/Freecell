#pragma once
#include <vector>

const int CELL_MARGIN = 2;
const int CARD_STAGGER = 20;
const int MAX_CARDS_PER_CELL = 7 + 12;

class Cell
{
public:
	Cell(int left, int top, int right, int bottom);
	void AddCard(int index);
	int RemoveCard();
	void SelectCell(bool s);
	int GetTopCard();
	bool IsClicked(int x, int y);
	virtual void Draw(CDC& dc);
	virtual bool CanRemoveCard();
	virtual bool CanAddCard(int index)=0;

protected:
	int mLeft, mTop, mRight, mBottom;
	std::vector<int> mCards;
	bool mSelected;
};

class StartCell : public Cell {
public:
	StartCell(int left, int top, int right, int bottom) :
		Cell(left, top, right, bottom) {}
	virtual bool CanAddCard(int index) = 0;
};

class FreeCell : public Cell {
public:
	FreeCell(int left, int top, int right, int bottom):
		Cell(left, top, right, bottom){}
	virtual bool CanAddCard(int index) = 0;
};

class EndCell : public Cell {
public:
	EndCell(int left, int top, int right, int bottom) :
		Cell(left, top, right, bottom) {}
	virtual bool CanRemoveCard();
	virtual bool CanAddCard(int index) = 0;
};
