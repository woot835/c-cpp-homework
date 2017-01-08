#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <math.h>
#include <chrono>
#include <thread>

const int rows = 16;
const int columns = 16;

const int windowWidth = 800;
const int windowHeight = 800;

void createStatesArr(int states[rows][columns]);
void evolveCellStates(int states[rows][columns]);
int aliveNeighborsCount(int states[rows][columns], int x, int y);

// Press F to start the actual game

int main()
{
	int tileWidth = windowWidth / columns;
	int tileHeight = windowHeight / rows;
	sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "A Game of Life and Things and Stuff", sf::Style::Titlebar | sf::Style::Close);
	sf::RectangleShape cell(sf::Vector2f(tileWidth, tileHeight));
	cell.setFillColor(sf::Color::Cyan);
	cell.setOutlineThickness(1.0f);
	cell.setOutlineColor(sf::Color::Black);
	sf::Event windowEvent;

	int states[rows][columns];
	createStatesArr(states);
	bool started = false;

	while (window.isOpen())
	{
		while (window.pollEvent(windowEvent))
		{
			if (!started && windowEvent.type == sf::Event::MouseButtonPressed)
			{
				int clickX = (windowEvent.mouseButton.x/tileWidth);
				int clickY = (windowEvent.mouseButton.y/tileHeight);
				printf("%d %d \n", clickX, clickY);
				states[clickY][clickX] = states[clickY][clickX] == 1 ? 0 : 1;
			}
			else if (windowEvent.type == sf::Event::KeyPressed && windowEvent.key.code == sf::Keyboard::F) {
				printf("Has started \n");
				started = true;
			}
		}
		
		if (started) {
			evolveCellStates(states);
			std::this_thread::sleep_for(std::chrono::milliseconds(1000));
		}

		window.clear();
		for (size_t rowIndex = 0; rowIndex < rows; rowIndex++)
		{
			for (size_t columnIndex = 0; columnIndex < columns; columnIndex++)
			{
				int state = states[rowIndex][columnIndex];
				if (state == 1) {
					cell.setFillColor(sf::Color::Cyan);
				}
				else if (state == 0) {
					cell.setFillColor(sf::Color::Blue);
				}

				cell.setPosition((columnIndex * tileWidth), (rowIndex * tileHeight));
				window.draw(cell);
			}
		}
		
		
	

		
		
		window.display();
	}

	return 0;
}

void evolveCellStates(int states[rows][columns]) {
	int newStates[rows][columns];
	for (size_t rowIndex = 0; rowIndex < rows; rowIndex++)
	{
		for (size_t columnIndex = 0; columnIndex < columns; columnIndex++)
		{
			int state = states[rowIndex][columnIndex];
			int aliveNeighbors = aliveNeighborsCount(states, rowIndex, columnIndex);
			if (state == 0) { // Cell is dead
				if (aliveNeighbors == 3) {
					state = 1;
				}
			}
			else if (state == 1) { // Cell is alive
				if (aliveNeighbors < 2) {
					state = 0;
				}
				
				if (aliveNeighbors > 5) {
					state = 0;
				}
			}

			newStates[rowIndex][columnIndex] = state;
		}
	}

	// Replace old cell states with new states
	for (size_t rowIndex = 0; rowIndex < rows; rowIndex++)
	{
		for (size_t columnIndex = 0; columnIndex < columns; columnIndex++)
		{
			states[rowIndex][columnIndex] = newStates[rowIndex][columnIndex];
		}
	}
}

int aliveNeighborsCount(int states[rows][columns], int x, int y) {
	int fromX = std::max(0, x - 1);
	int fromY = std::max(0, y - 1);
	int toX = std::min(rows - 1, x + 1);
	int toY = std::min(columns - 1, y + 1);
	int aliveNeighbors = 0;

	for (size_t i = fromX; i <= toX; i++)
	{
		for (size_t j = fromY; j <= toY; j++)
		{
			if (states[i][j] == 1) {
				aliveNeighbors++;
			}
		}
	}

	if (states[x][y] == 1) aliveNeighbors--;

	return aliveNeighbors;
}

void createStatesArr(int states[rows][columns]) {
	for (size_t rowIndex = 0; rowIndex < rows; rowIndex++)
	{
		for (size_t columnIndex = 0; columnIndex < columns; columnIndex++)
		{
			states[rowIndex][columnIndex] = 1;
		}
	}
}
