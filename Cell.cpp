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
	return mCards.back();
}
void Cell::Draw(CDC & dc)
{
	dc.Rectangle(mLeft, mTop, mRight, mBottom);
	for (unsigned int i = 0; i < mCards.size(); i++)
	{
		DrawCard(dc, mLeft+CELL_MARGIN, mTop+CELL_MARGIN + CARD_STAGGER*i, mCards[i], mSelected);
	}
}
bool Cell::IsClicked(int x, int y)
{
	if (x >= mLeft && x <= mRight && y >= mTop && y <= mBottom)
		return true;
	else
		return false;
}

bool EndCell::CanRemoveCard() {
	return false;
}
bool Cell::CanRemoveCard() {
	if (mCards.size() >= 1) {
		return true;
	}
	else {
		return false;
	}
}
bool StartCell::CanAddCard() {

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