#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
void setRoads(std::vector<sf::VertexArray>, std::vector<int>);

int main() {

	int INF = INT_MAX;
	const int Width = 1200;					//��������� ������
	const int Height = 1000;

	float circleRadius = 20;				// ��������� �����
	float circleThickness = 3;

	bool isDrawing = false;					//���������� � ��������� ���������� ��� �������� ��������� ������
	sf::Vector2f BPoint;					//��� ��������� 


	std::vector<sf::CircleShape> Vertex;	//�������, ��� ����� ������� ���� ������� � ������
	std::vector<sf::VertexArray> Roads;

	sf::Font font;
	font.loadFromFile("AGENCYR.ttf");

	sf::Text text;
	text.setFont(font);
	text.setCharacterSize(30);
	text.setFillColor(sf::Color::Black);

	setlocale(LC_ALL, "RUS");

	sf::RenderWindow window(sf::VideoMode(Width, Height), "The best kursach ever"); //������� ����
	window.setPosition(sf::Vector2i(10, 50));
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) window.close();		//��������

			if (event.key.code == sf::Keyboard::Escape) {				//����������
				Vertex.clear();
				Roads.clear();
			}

			if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Middle) {
				
				sf::Vector2f DelPoint = sf::Vector2f(event.mouseButton.x, event.mouseButton.y);
				for (int i = 0; i < Vertex.size(); i++) {
					if
						(
							std::pow((Vertex[i].getPosition().x - DelPoint.x + circleRadius),2) + std::pow((Vertex[i].getPosition().y - DelPoint.y + circleRadius), 2) <= std::pow(circleRadius,2)
						)

					{
						DelPoint.x = Vertex[i].getPosition().x;
						DelPoint.y = Vertex[i].getPosition().y;
						Vertex.erase(Vertex.begin() + i);
						Roads.clear();
					}
				}
			} //��������� �������� ������


			//���������� �������
			if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
				sf::CircleShape node(circleRadius);
				node.setPosition(sf::Mouse::getPosition(window).x - circleRadius, \
				sf::Mouse::getPosition(window).y - circleRadius);
				node.setFillColor(sf::Color::Blue);
				node.setOutlineColor(sf::Color::Red);
				node.setOutlineThickness(circleThickness);
				Vertex.push_back(node);
			}

			if (event.key.code == sf::Keyboard::C) {
				Roads.clear();
			}

			if (event.key.code == sf::Keyboard::F) {
				if (Vertex.size() > 1) {
					Roads.clear();
					for (int i = 0; i < Vertex.size(); i++) {
						for (int j = 0; j < Vertex.size(); j++) {
							sf::VertexArray line(sf::Lines, 2);
							line[0].position.x = Vertex[i].getPosition().x + circleRadius;
							line[0].position.y = Vertex[i].getPosition().y + circleRadius;
							line[1].position.x = Vertex[j].getPosition().x + circleRadius;
							line[1].position.y = Vertex[j].getPosition().y + circleRadius;
							Roads.push_back(line);
						}
					}
				}
			}

			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::G && Vertex.size() > 1) {
				Roads.clear();
				// ���������� ��������� ������ ���������� �����
				std::vector<std::vector<int>> CM(Vertex.size()); // ������ ��������� �����
				std::vector<bool> visited(Vertex.size(), false); // ����� ��������� ������
				std::vector<int> dist(Vertex.size(), INT_MAX); // ���������� �� ������
				std::vector<int> parent(Vertex.size(), -1); // ������������ �������
					
				dist[0] = 0; // ��������� ���������� �� ������ ������� ����� 0

				for (int i = 0; i < Vertex.size() - 1; i++) {
					int u = -1;
					int minDist = INT_MAX;
					// ���� ��������� ������������ �������
					for (int j = 0; j < Vertex.size(); j++) {
						if (!visited[j] && dist[j] < minDist) {
							u = j;
							minDist = dist[j];
						}
					}
					visited[u] = true; // �������� ������� ��� ����������
					// ��������� ���������� �� �������� ������
					for (int v = 0; v < Vertex.size(); v++) {
						int weight = std::sqrt(std::pow(Vertex[u].getPosition().x - Vertex[v].getPosition().x, 2) + std::pow(Vertex[u].getPosition().y - Vertex[v].getPosition().y, 2))/* ��������� ��� ����� ����� ��������� u � v */;
						if (!visited[v] && weight < dist[v]) {
							dist[v] = weight;
							parent[v] = u;
						}
					}
				}

				// ��������� ������ ��������� ������� �����
				for (int u = 0; u < Vertex.size(); u++) {
					if (parent[u] != -1) {
						CM[u].push_back(parent[u]);
						CM[parent[u]].push_back(u);
					}
				}
				// ��������� ����� ��������� ������
				sf::VertexArray line(sf::Lines, 2);
				for (int i = 0; i < Vertex.size(); i++) {
					for (int j = 0; j < CM[i].size(); j++) {
						int v = CM[i][j];
						line[0].position.x = Vertex[i].getPosition().x + circleRadius;
						line[0].position.y = Vertex[i].getPosition().y + circleRadius;
						line[1].position.x = Vertex[v].getPosition().x + circleRadius;
						line[1].position.y = Vertex[v].getPosition().y + circleRadius;
						Roads.push_back(line);
					}
				}
			}



			if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Right) {  //���������� ������
				BPoint = sf::Vector2f(event.mouseButton.x, event.mouseButton.y);
				isDrawing = true;
			}

			if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Right) {
				sf::Vector2f EPoint(event.mouseButton.x, event.mouseButton.y);
				isDrawing = false;
				sf::VertexArray line(sf::Lines, 2); 
				line[0].position = BPoint;
				line[1].position = EPoint;
				bool pointer1 = false;
				bool pointer2 = false;
				if (!Vertex.empty()) {
					for (int i = 0; i < Vertex.size(); i++) {
						if (
							(BPoint.x <= Vertex[i].getPosition().x + 2 * circleRadius + circleThickness && \
								BPoint.x >= Vertex[i].getPosition().x - 2 * circleRadius - circleThickness && \
								BPoint.y <= Vertex[i].getPosition().y + 2 * circleRadius + circleThickness && \
								BPoint.y >= Vertex[i].getPosition().y - 2 * circleRadius - circleThickness)
							) pointer1 = true;

						for (int j = 0; j < Vertex.size(); j++) {
							if
								(
									EPoint.x <= Vertex[j].getPosition().x + 2 * circleRadius + circleThickness && \
									EPoint.x >= Vertex[j].getPosition().x - 2 * circleRadius - circleThickness && \
									EPoint.y <= Vertex[j].getPosition().y + 2 * circleRadius + circleThickness && \
									EPoint.y >= Vertex[j].getPosition().y - 2 * circleRadius - circleThickness
									) pointer2 = true;
							if (pointer1 && pointer2) break;
						}
						if (pointer1 && pointer2) break;
					}
					if (pointer1 && pointer2) Roads.push_back(line);
				}
			}
		}


		window.clear(sf::Color::White);

		for (int i = 0; i < Roads.size(); i++)
		{
			Roads[i][0].color = Roads[i][1].color = sf::Color::Red;
			window.draw(Roads[i]);
		}

		if (isDrawing) {
			sf::Vector2i mousePos = sf::Mouse::getPosition(window);
			sf::VertexArray line(sf::Lines, 2);
			line[0].color = line[1].color = sf::Color::Black;
			line[0].position = BPoint;
			line[1].position = sf::Vector2f(mousePos.x, mousePos.y);

			window.draw(line);
		}

		for (unsigned int i = 0; i < Vertex.size(); i++) window.draw(Vertex[i]);

		text.setString("Add vertex - left mouse button");
		text.setPosition(10, 10);
		window.draw(text);

		text.setString("Add road  - right mouse button");
		text.setPosition(10, 40);
		window.draw(text);

		text.setString("Delete vertex  - middle mouse button");
		text.setPosition(10, 70);
		window.draw(text);

		text.setString("Clear screen  - escape");
		text.setPosition(10, 100);
		window.draw(text);

		text.setString("Set Full roads  - F");
		text.setPosition(10, 130);
		window.draw(text);

		text.setString("Clear Roads  - C");
		text.setPosition(10, 160);
		window.draw(text);

		text.setString("Ostonov tree  - G");
		text.setPosition(10, 190);
		window.draw(text);

		window.display();
	}
	return 0;
}