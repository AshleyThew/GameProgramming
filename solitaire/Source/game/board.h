// COMP710 GP Framework 2021
#ifndef __SCENEBOARD_H__
#define __SCENEBOARD_H__
// Local includes:
#include "card.h"
#include "renderer.h"
#include <list>
#include <vector>
// Forward declarations:
class Renderer;
// Class declaration:
class Board
{
	// Member methods:
public:
	Board();
	virtual ~Board();
	virtual bool Initialise(Renderer& renderer);
	virtual const int GetSelectedRow();
	virtual void SetSelectedRow(int row);
	virtual const int GetSelectedColumn();
	virtual void SetSelectedColumn(int column);
	virtual const int GetDeckPosition();
	virtual void SetDeckPosition(int position);
	virtual const bool GetDeckDragging();
	virtual void SetDeckDragging(int deckDragging);
	virtual std::vector<Card*>& GetDeck();
	virtual std::vector<Card*>* GetColumns();
	virtual Card** GetStored();
protected:
private:
	Board(const Board& board);
	Board& operator=(const Board& board);
	// Member data:
public:
protected:
private:
	int m_selectedRow;
	int m_selectedColumn;
	int m_deckPosition;
	bool m_deckDragging;
	std::vector<Card*> m_deck;
	std::vector<Card*> m_columns[7];
	Card* m_stored[4];
};
#endif // __SCENEBOARD_H__