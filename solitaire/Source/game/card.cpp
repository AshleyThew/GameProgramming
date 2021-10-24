// COMP710 GP Framework 2021
// This include:
#include "card.h"
#include "renderer.h"
#include "sprite.h"
// Local includes:
#include <string>
// Library includes:
Card::Card(int suitType, int cardType)
	: m_hidden(false)
{
	m_suitType = suitType;
	m_cardType = cardType;

}
Card::~Card()
{
	delete m_cardText;
	m_cardText = 0;
}

void Card::Initialise(Renderer& renderer)
{
	std::string cardValue;
	switch (m_cardType)
	{
	case ACE:
		cardValue.append("A");
		break;
	case TEN:
		cardValue.append("X");
		break;
	case JACK:
		cardValue.append("J");
		break;
	case QUEEN:
		cardValue.append("Q");
		break;
	case KING:
		cardValue.append("K");
		break;
	default:
		cardValue.append(std::to_string(m_cardType + 1));
		break;
	}
	int red = 0;
	switch (m_suitType)
	{
	case HEARTS:
		red = 255;
		cardValue.append("H");
		break;
	case DIAMONDS:
		red = 255;
		cardValue.append("D");
		break;
	case SPADES:
		cardValue.append("S");
		break;
	case CLUBS:
		cardValue.append("C");
		break;
	default:
		return;
	}

	const char* value = cardValue.c_str();
	m_cardText = renderer.CreateStaticText(value, 30);
	m_cardText->SetRedTint((float)red);
	m_cardText->SetGreenTint(0);
	m_cardText->SetBlueTint(0);
}


void Card::Render(Renderer& renderer, const int posX, const int posY)
{
	m_cardText->SetX(posX);
	m_cardText->SetY(posY);
	m_cardText->Draw(renderer);
}

bool Card::GetHidden()
{
	return m_hidden;
}

const int Card::GetSuitType()
{
	return m_suitType;
}

const int Card::GetCardType()
{
	return m_cardType;
}

void Card::SetHidden(bool hidden)
{
	m_hidden = hidden;
}