#include "pch.h"
#include "Cell.h"
#include "WindowsCards.h"

Cell::Cell(int left, int top, int right, int bottom)
{
	mLeft = left;
	mTop = top;
	mRight = right;
	mBottom = bottom;
	mSelected = false;
}
void Cell::AddCard(int index)
{
	mCards.push_back(index);
}
int Cell::RemoveCard()
{
	int top = GetTopCard();
	mCards.pop_back();
	return top;
}
void Cell::SelectCell(bool s)
{
	mSelected = s;
}
int Cell::GetTopCard()
{
	if (mCards.size() >= 1){
		return mCards.back();
	}
	else {
		return false;
	}
	
}
void StartCell::Draw(CDC& dc) {
	// Draw cell background
	CBrush cellBackground(RGB(2, 112, 19));
	dc.SelectObject(cellBackground);
	dc.Rectangle(mLeft, mTop, mRight, mBottom);

	// Draw the cards in the cell
	if (mCards.size() > 0) {
		for (unsigned int i = 0; i < mCards.size() - 1; i++)
		{
			DrawCard(dc, mLeft + CELL_MARGIN, mTop + CELL_MARGIN + CARD_STAGGER * i, mCards[i], false);
		}
		DrawCard(dc, mLeft + CELL_MARGIN, mTop + CELL_MARGIN + CARD_STAGGER * mCards.size() - CARD_STAGGER, mCards[mCards.size() - 1], mSelected);
	}
}
void Cell::Draw(CDC & dc)
{
	// Draw cell background
	CBrush cellBackground(RGB(2, 112, 19));
	dc.SelectObject(cellBackground);
	dc.Rectangle(mLeft, mTop, mRight, mBottom);

	// Draw the top card in the cell
	if (mCards.size() > 0){
		DrawCard(dc, mLeft + CELL_MARGIN, mTop + CELL_MARGIN, GetTopCard(), mSelected);
	}
	
}
bool Cell::IsClicked(int x, int y)
{
	if (x >= mLeft && x <= mRight && y >= mTop && y <= mBottom)
		return true;
	else
		return false;
}
// Base implementation for a cell
bool Cell::CanRemoveCard() {
	if (mCards.size() >= 1) {
		return true;
	}
	else {
		return false;
	}
}
// EndCells cannot remove any cards
bool EndCell::CanRemoveCard() {
	return false;
}

bool StartCell::CanAddCard(int index) {
	int selectedRank = index / 4;
	int selectedSuit = index % 4;
	if (mCards.size() > 0) {
		int topRank = GetTopCard() / 4;
		int topSuit = GetTopCard() % 4;
		int rankDifference = topRank - selectedRank;
		bool goodSuit = false;
		if (selectedSuit == 0) {
			if (topSuit == 1 || topSuit == 2) {
				goodSuit = true;
			}
			else {
				goodSuit = false;
			}
		}
		if (selectedSuit == 1) {
			if (topSuit == 0 || topSuit == 3) {
				goodSuit = true;
			}
			else {
				goodSuit = false;
			}
		}
		if (selectedSuit == 2) {
			if (topSuit == 0 || topSuit == 3) {
				goodSuit = true;
			}
			else {
				goodSuit = false;
			}
		}
		if (selectedSuit == 3) {
			if (topSuit == 1 || topSuit == 2) {
				goodSuit = true;
			}
			else {
				goodSuit = false;
			}
		}
		if (goodSuit == true && rankDifference == 1) {
			return true;
		}
		else {
			return false;
		}
	}
	else {
		return true;
	}
}
bool FreeCell::CanAddCard(int index) {
	if (mCards.size() == 0) {
		return true;
	}
	else {
		return false;
	}
}
bool EndCell::CanAddCard(int index) {
	int newrank = index / 4;
	int newsuit = index % 4;
	if (mCards.size() > 0) {
		int oldrank = GetTopCard() / 4;
		int oldsuit = GetTopCard() % 4;

		return newsuit == oldsuit && newrank == oldrank + 1;
	}
	else {
		return newrank == 0; 
	}
}