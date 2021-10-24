// COMP710 GP Framework 2021
// This include:
#include "card.h"
#include "board.h"
#include "time.h"
#include <algorithm>
#include <random>
// Local includes:
// Library includes:
Board::Board()
	: m_selectedColumn(-1),
	m_selectedRow(-1),
	m_deckPosition(-1),
	m_deckDragging(false)
{

}
Board::~Board()
{
	for (int column = 0; column < 7; column++)
	{
		std::vector<Card*> list = m_columns[column];
		for (Card* card : list)
		{
			delete card;
		}
		list.clear();
	}
	for (Card* card : m_deck)
	{
		delete card;
	}
	m_deck.clear();
	for (int stored = 0; stored < 4; stored++)
	{
		Card* card = m_stored[stored];
		if (card != NULL)
		{
			delete card;
		}
	}
}
bool
Board::Initialise(Renderer& renderer)
{
	for(int cardType = ACE; cardType <= KING; cardType++)
	{
		for (int suitType = HEARTS; suitType <= CLUBS; suitType++)
		{
			Card* newCard = new Card(suitType, cardType);
			newCard->Initialise(renderer);
			m_deck.push_back(newCard);
		}
	}
	srand((unsigned int)time(NULL));
	std::random_shuffle(m_deck.begin(), m_deck.end());
	for (int column = 0; column < 7; column++)
	{
		std::vector<Card*>& cardColumn = m_columns[column];
		for (int row = 0; row <= column; row++)
		{
			
			Card* card = m_deck.back();
			m_deck.pop_back();
			cardColumn.push_back(card);
			if (row != column)
			{
				card->SetHidden(true);
			}
		}
	}
	m_deck.resize(m_deck.size());
	for (int stored = 0; stored < 4; stored++)
	{
		m_stored[stored] = NULL;
	}
	return true;
}

Card** Board::GetStored()
{
	return m_stored;
}

void Board::SetSelectedRow(int row)
{
	m_selectedRow = row;
}

const int Board::GetSelectedRow()
{
	return m_selectedRow;
}

void Board::SetSelectedColumn(int column)
{
	m_selectedColumn = column;
}

const int Board::GetSelectedColumn()
{
	return m_selectedColumn;
}

void Board::SetDeckPosition(int position)
{
	m_deckPosition = position;
}

const int Board::GetDeckPosition()
{
	return m_deckPosition;
}

void Board::SetDeckDragging(int deckDragging)
{
	m_deckDragging = deckDragging;
}

const bool Board::GetDeckDragging()
{
	return m_deckDragging;
}

std::vector<Card*>& Board::GetDeck()
{
	return m_deck;
}

std::vector<Card*>* Board::GetColumns()
{
	return m_columns;
}