// COMP710 GP Framework 2021
#ifndef __SCENECARD_H__
#define __SCENECARD_H__
// Local includes:
#include "sprite.h"
#include "renderer.h"
#include <vector>
// Forward declarations:
class Sprite;
class Renderer;
// Class declaration:

enum CardType {
	ACE,
	TWO,
	THREE,
	FOUR,
	FIVE,
	SIX,
	SEVEN,
	EIGHT,
	NINE,
	TEN,
	JACK,
	QUEEN,
	KING
};

enum SuitType {
	HEARTS,
	DIAMONDS,
	SPADES,
	CLUBS
};

class Card
{
	// Member methods:
public:
	Card(int suitType, int cardType);
	virtual ~Card();
	virtual void Initialise(Renderer& renderer);
	virtual bool GetHidden();
	virtual const int GetSuitType();
	virtual const int GetCardType();
	virtual void SetHidden(bool hidden);
	virtual void Render(Renderer& renderer, const int posX, const int posY);
protected:
private:
	Card(const Card& card);
	Card& operator=(const Card& card);
	// Member data:
public:
protected:
private:
	Sprite* m_cardText;
	int m_suitType;
	int m_cardType;
	bool m_hidden;
};
#endif // __SCENECARD_H__