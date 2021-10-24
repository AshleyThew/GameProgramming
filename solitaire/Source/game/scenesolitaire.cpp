// COMP710 GP Framework 2021
// This include:
#include "scenesolitaire.h"
// Local includes:
#include "renderer.h"
#include "animatedsprite.h"
#include "sprite.h"
#include "board.h"
#include "logmanager.h"
#include "card.h"
#include "game.h"
#include "xboxcontroller.h"
#include "imgui/imgui.h"
// Library includes:
#include <cassert>
#include <string>
SceneSolitaire::SceneSolitaire()
	: m_board(0)
{
}
SceneSolitaire::~SceneSolitaire()
{
	delete m_cardFace;
	m_cardFace = 0;
	delete m_cardBacking;
	m_cardBacking = 0;
	if (m_board != 0)
	{
		delete m_board;
	}
	m_board = 0;
	m_mousePosition = 0;
}

bool
SceneSolitaire::Initialise(Renderer& renderer)
{
	//m_cardBacking = renderer.CreateSprite("sprites\\solitaire\\cardback.png");
	m_cardFace = renderer.CreateSprite("sprites\\solitaire\\cardface.png");

	m_cardBacking = renderer.CreateAnimatedSprite("sprites\\solitaire\\cardback_animated.png");
	m_cardBacking->Animate();
	m_cardBacking->SetupFrames(80, 100);
	m_cardBacking->SetFrameDuration(0.4f);
	m_cardBacking->SetLooping(true);

	//const int SCREEN_WIDTH = renderer.GetWidth();
	//const int SCREEN_HEIGHT = renderer.GetHeight();
	//m_cardBacking->SetX(SCREEN_WIDTH / 2);
	m_cardBacking->SetY(m_cardBacking->GetHeight() / 2);

	renderer.SetClearColour(18, 117, 5);
	CreateGame(renderer);

	return true;
}

void SceneSolitaire::CreateGame(Renderer& renderer)
{
	if (m_board != 0)
	{
		delete m_board;
	}
	m_board = 0;
	m_board = new Board();
	m_board->Initialise(renderer);
}

void
SceneSolitaire::Process(float deltaTime)
{
	m_cardBacking->Process(deltaTime);
}

void
SceneSolitaire::Draw(Renderer& renderer)
{
	std::vector<Card*>* columns = m_board->GetColumns();

	int selectedRow = m_board->GetSelectedRow();
	int selectedColumn = m_board->GetSelectedColumn();

	int posX = m_cardBacking->GetWidth();
	for (int width = 0; width < 7; width++)
	{
		std::vector<Card*> column = columns[width];
		int posY = m_cardBacking->GetHeight() / 2;
		for (size_t row = 0; row < column.size(); row++)
		{
			if (selectedColumn != -1 && width == selectedColumn && row == selectedRow)
			{
				break;
			}

			int realY = 200 + posY * (row + 1);
			
			Card* card = column[row];
			if (!card->GetHidden())
			{
				m_cardFace->SetX(posX);
				m_cardFace->SetY(realY);
				m_cardFace->Draw(renderer);
				card->Render(renderer, posX, realY);
			}
			else
			{
				m_cardBacking->SetX(posX);
				m_cardBacking->SetY(realY);
				m_cardBacking->Draw(renderer);
			}
		}
		posX += m_cardBacking->GetWidth() * 2;
	}

	if (selectedColumn >= 0 && selectedRow >= 0) 
	{
		std::vector<Card*> column = columns[selectedColumn];
		int posY = m_cardBacking->GetHeight() / 2;
		for (size_t row = selectedRow; row < column.size(); row++)
		{
			float realY = m_mousePosition->y + posY * (row + 1 - selectedRow);
			Card* card = column[row];
			m_cardFace->SetX((int)m_mousePosition->x);
			m_cardFace->SetY((int)realY);
			m_cardFace->Draw(renderer);
			card->Render(renderer, (int)m_mousePosition->x, (int)realY);
		}
	}

	Card** store = m_board->GetStored();
	for (int col = 0; col < 4; col++)
	{
		Card* stored = store[col];
		int posY = 20 + m_cardBacking->GetHeight() / 2;
		int posX = m_cardBacking->GetWidth() + (col + 3) * m_cardBacking->GetWidth() * 2;
		if (stored == NULL)
		{
			m_cardBacking->SetX(posX);
			m_cardBacking->SetY(posY);
			m_cardBacking->Draw(renderer);
		}
		else
		{
			m_cardFace->SetX(posX);
			m_cardFace->SetY(posY);
			m_cardFace->Draw(renderer);
			stored->Render(renderer, posX, posY);
		}
	}

	std::vector<Card*> deck = m_board->GetDeck();
	int pos = m_board->GetDeckPosition();
	if (pos >=0 && pos < (int)deck.size())
	{
		int x = m_cardBacking->GetWidth();
		int y = 20 + m_cardBacking->GetHeight() / 2;
		Card* card = deck[pos];
		if (pos > 0)
		{
			Card* behind = deck[pos-1];
			m_cardFace->SetX(x);
			m_cardFace->SetY(y);
			m_cardFace->Draw(renderer);
			behind->Render(renderer, x, y);
		}
		else
		{
			m_cardBacking->SetX(x);
			m_cardBacking->SetY(y);
			m_cardBacking->Draw(renderer);
		}
		
		Card* display = deck[pos];

		if (m_board->GetDeckDragging())
		{
			m_cardFace->SetX((int)m_mousePosition->x);
			m_cardFace->SetY((int)m_mousePosition->y);
			m_cardFace->Draw(renderer);
			display->Render(renderer, (int)m_mousePosition->x, (int)m_mousePosition->y);
		}
		else
		{
			x = x + x / 2;
			m_cardFace->SetX(x);
			m_cardFace->SetY(y);
			m_cardFace->Draw(renderer);
			display->Render(renderer, x, y);
		}


	}
	else if (deck.size() > 0)
	{
		int x = m_cardBacking->GetWidth();
		m_cardBacking->SetX(x);
		m_cardBacking->SetY(20 + m_cardBacking->GetHeight() / 2);
		m_cardBacking->Draw(renderer);
	}
}

void
SceneSolitaire::ProcessInput(InputSystem& inputSystem)
{
	int leftResult = inputSystem.GetMouseButtonState(SDL_BUTTON_LEFT);
	int rightResult = inputSystem.GetMouseButtonState(SDL_BUTTON_RIGHT);
	int escResult = inputSystem.GetKeyState(SDL_SCANCODE_ESCAPE);
	m_mousePosition = const_cast<Vector2*>(&inputSystem.GetMousePosition());

	XboxController* controller = inputSystem.GetController(0);
	ButtonState xboxA = controller->GetButtonState(SDL_CONTROLLER_BUTTON_A);
	ButtonState xboxB = controller->GetButtonState(SDL_CONTROLLER_BUTTON_B);
	ButtonState xboxStart = controller->GetButtonState(SDL_CONTROLLER_BUTTON_START);

	if (escResult == BS_PRESSED || xboxStart == BS_PRESSED)
	{
		Game::GetInstance().StartGame();
	}

	if (leftResult == BS_PRESSED || xboxA == BS_PRESSED)
	{
		//LogManager::GetInstance().Log(std::to_string(m_mousePosition->y).c_str());
		// Game board
		if (m_mousePosition->y >= 200)
		{
			float xPos = m_mousePosition->x / (m_cardBacking->GetWidth() * 2);
			int x = (int)xPos;
			if (x >= 7 || x < 0) {
				// Out of bounds
				return;
			}
			//LogManager::GetInstance().Log(std::to_string(x).c_str());
			

			float yPos = (m_mousePosition->y - 200) / (m_cardBacking->GetHeight() / 2);
			int y = (int)yPos;
			std::vector<Card*>* columns = m_board->GetColumns();
			std::vector<Card*> column = columns[x];
			if (y >= (int)column.size())
			{
				y = column.size() - 1;
			}
			if (y == -1) {
				// Empty column
				return;
			}
			Card* card = column[y];
			if (card->GetHidden())
			{
				return;
			}

			m_board->SetSelectedColumn(x);
			m_board->SetSelectedRow(y);
		}
		else
		{
			// Top area
			// Deck
			if (m_mousePosition->x < 160)
			{
				m_board->SetDeckDragging(true);
			}
		}
	}
	else if (leftResult == BS_RELEASED || xboxA == BS_RELEASED)
	{
		if (m_board->GetSelectedColumn() >= 0 && m_board->GetSelectedRow() >= 0)
		{
			int selectedRow = m_board->GetSelectedRow();
			int selectedColumn = m_board->GetSelectedColumn();
			m_board->SetSelectedColumn(-1);
			m_board->SetSelectedRow(-1);

			if (m_mousePosition->y >= 200)
			{
				// Dropping on board
				float xPos = m_mousePosition->x / (m_cardBacking->GetWidth() * 2);
				int x = (int)xPos;
				if (x >= 7 || x < 0) {
					// Out of bounds
					return;
				}
				if (selectedColumn == x)
				{
					// Same column
					return;
				}
				//Handle drop
				std::vector<Card*>* columns = m_board->GetColumns();

				std::vector<Card*>& columnFrom = columns[selectedColumn];
				std::vector<Card*>& columnTo = columns[x];
				Card* from = columnFrom[selectedRow];
				Card* to = NULL;
				if (columnTo.size() > 0)
				{
					to = columnTo.back();
				}
				if (to == NULL)
				{
					if (from->GetCardType() != KING)
					{
						return;
					}
				}
				else
				{
					int fromType = from->GetSuitType();
					int toType = to->GetSuitType();
					if (fromType == HEARTS || fromType == DIAMONDS)
					{
						// Same type
						if (toType == HEARTS || toType == DIAMONDS)
						{
							return;
						}
					}
					// Same type
					else if (toType == SPADES || toType == CLUBS)
					{
						return;
					}
					if (to->GetCardType() == ACE)
					{
						return;
					}
					if (to->GetCardType()-1 != from->GetCardType())
					{
						// Not card after
						return;
					}
				}			
				
				int max = columnFrom.size();
				for (int index = selectedRow; index < max; index++)
				{
					Card* add = columnFrom[index];
					columnTo.push_back(add);
				}
				for (int index = selectedRow; index < max; index++)
				{
					columnFrom.pop_back();
				}
				if (columnFrom.size() > 0)
				{
					columnFrom[columnFrom.size() - 1]->SetHidden(false);
				}
				columnFrom.resize(columnFrom.size());
			}
			else
			{
				std::vector<Card*>* columns = m_board->GetColumns();

				std::vector<Card*>& columnFrom = columns[selectedColumn];
				if (selectedRow == columnFrom.size() - 1) 
				{
					Card* from = columnFrom[selectedRow];
					// Attempt store
					Card** store = m_board->GetStored();
					Card* stored = store[from->GetSuitType()];
					if (stored == NULL)
					{
						if (from->GetCardType() != ACE)
						{
							return;
						}
					}
					else
					{
						if (stored->GetCardType() + 1 != from->GetCardType())
						{
							return;
						}
					}
					store[from->GetSuitType()] = from;
					columnFrom.pop_back();
					if (columnFrom.size() > 0)
					{
						columnFrom[columnFrom.size() - 1]->SetHidden(false);
					}
					columnFrom.resize(columnFrom.size());
					CheckGameEnd();
				}
			}
		}
		else if(m_board->GetDeckDragging())
		{
			m_board->SetDeckDragging(false);
			// Top area
			// Deck
			if (m_mousePosition->y < 200)
			{
				if (m_mousePosition->x < 160)
				{
					int size = m_board->GetDeck().size();
					if (size > 0)
					{
						int next = m_board->GetDeckPosition() + 1;
						if (next >= size)
						{
							next = -1;
						}
						m_board->SetDeckPosition(next);
					}
				}
				else if(m_mousePosition->x > 400)
				{
					// Store
					Card* from = m_board->GetDeck()[m_board->GetDeckPosition()];
					// Attempt store
					Card** store = m_board->GetStored();
					Card* stored = store[from->GetSuitType()];
					if (stored == NULL)
					{
						if (from->GetCardType() != ACE)
						{
							return;
						}
					}
					else
					{
						if (stored->GetCardType() + 1 != from->GetCardType())
						{
							return;
						}
					}
					store[from->GetSuitType()] = from;
					m_board->GetDeck().erase(m_board->GetDeck().begin() + m_board->GetDeckPosition());
					m_board->SetDeckPosition(m_board->GetDeckPosition() - 1);
					CheckGameEnd();
				}
			}
			else 
			{
				// Onto board

				float xPos = m_mousePosition->x / (m_cardBacking->GetWidth() * 2);
				int x = (int)xPos;
				if (x >= 7 || x < 0) {
					// Out of bounds
					return;
				}

				std::vector<Card*>* columns = m_board->GetColumns();

				std::vector<Card*>& columnTo = columns[x];
				Card* from = m_board->GetDeck()[m_board->GetDeckPosition()];
				Card* to = NULL;
				if (columnTo.size() > 0)
				{
					to = columnTo.back();
				}
				if (to == NULL)
				{
					if (from->GetCardType() != KING)
					{
						return;
					}
				}
				else
				{
					int fromType = from->GetSuitType();
					int toType = to->GetSuitType();
					if (fromType == HEARTS || fromType == DIAMONDS)
					{
						// Same type
						if (toType == HEARTS || toType == DIAMONDS)
						{
							return;
						}
					}
					// Same type
					else if (toType == SPADES || toType == CLUBS)
					{
						return;
					}
					if (to->GetCardType() == ACE)
					{
						return;
					}
					if (to->GetCardType() - 1 != from->GetCardType())
					{
						// Not card after
						return;
					}
				}
				m_board->GetDeck().erase(m_board->GetDeck().begin() + m_board->GetDeckPosition());
				m_board->SetDeckPosition(m_board->GetDeckPosition() - 1);
				columnTo.push_back(from);
			}
		}
	}

	if (rightResult == BS_PRESSED || xboxB == BS_PRESSED)
	{
		bool accepted = false;
		do {
			accepted = false;
			std::vector<Card*>* columns = m_board->GetColumns();
			Card** store = m_board->GetStored();

			for (int column = 0; column < 7; column++)
			{
				std::vector<Card*>& cards = columns[column];
				if (cards.size() == 0)
				{
					continue;
				}
				Card* from = cards[cards.size() - 1];
				Card* stored = store[from->GetSuitType()];
				if (stored == NULL)
				{
					if (from->GetCardType() != ACE)
					{
						continue;
					}
				}
				else
				{
					if (stored->GetCardType() + 1 != from->GetCardType())
					{
						continue;
					}
				}
				accepted = true;
				store[from->GetSuitType()] = from;
				cards.pop_back();
				if (cards.size() > 0)
				{
					cards[cards.size() - 1]->SetHidden(false);
				}
				cards.resize(cards.size());
			}
			if (m_board->GetDeck().size() > 0 && m_board->GetDeckPosition() >= 0)
			{
				Card* from = m_board->GetDeck()[m_board->GetDeckPosition()];
				Card* stored = store[from->GetSuitType()];
				if (stored == NULL)
				{
					if (from->GetCardType() != ACE)
					{
						continue;
					}
				}
				else
				{
					if (stored->GetCardType() + 1 != from->GetCardType())
					{
						continue;
					}
				}
				accepted = true;
				store[from->GetSuitType()] = from;
				m_board->GetDeck().erase(m_board->GetDeck().begin() + m_board->GetDeckPosition());
				m_board->SetDeckPosition(m_board->GetDeckPosition() - 1);
			}
		} while (accepted);
		CheckGameEnd();
	}

}

void
SceneSolitaire::DebugDraw()
{

}


void SceneSolitaire::CheckGameEnd()
{
	Card** store = m_board->GetStored();
	for (int x = 0; x < 4; x++)
	{
		Card* stored = store[x];
		if (stored == NULL || stored->GetCardType() != KING)
		{
			return;
		}
	}

	// Game over all cards are KING
	Game::GetInstance().StartGame();
}