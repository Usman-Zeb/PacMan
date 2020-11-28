#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include<stdio.h>
#include<fstream>
#include<ctime>
#include<vector>
#include<stdlib.h>
#include<Windows.h>
using namespace :: std;
 

sf::RenderWindow window(sf::VideoMode(800, 600), "PacMan Ver 1.0 Alpha!");  //This line renders the main game loop
const int rect_sum = 63; //the total number of maze blocks
sf::RectangleShape rectangles[rect_sum]; //this declares the maze type for the game
sf::Texture for_rec; //texture for the maze blocks

ofstream scorefile; //used to output the score into a file

//This is the main menu class
class menu 
{
private:
	sf::RectangleShape menu_background;
	sf::RectangleShape Play;
	sf::RectangleShape HighScore;
	sf::RectangleShape Quit;
	sf::Texture menu_texture;
	sf::Text Play_text;
	sf::Text HighScore_text;
	sf::Text Quit_text;
	sf::Font font;
	sf::Texture button_texture;


public:

	menu()
	{
		if (!font.loadFromFile("OpenSans.ttf")) //Initialize font and check for error when loading it
		{
			cout << "Error!" << endl;
		}
		if (!button_texture.loadFromFile("menu_button.jpg")) //Initialize texture for buttons and check for errors
		{
			cout << "Error! Unsuccessful button texture load" << endl;
		}

		if (!menu_texture.loadFromFile("menubg.jpg"))
		{
			cout << "Error! Unsuccessful menu texture load" << endl;
		}

		menu_background.setSize(sf::Vector2f(800.0f, 600.0f)); //set main menu background size to 800x600
		Play.setSize(sf::Vector2f(200.0f, 50.0f));
		Quit.setSize(sf::Vector2f(200.0f, 50.0f));
		HighScore.setSize(sf::Vector2f(200.0f, 50.0f));
		

		Play.setOutlineColor(sf::Color::White);
		Quit.setOutlineColor(sf::Color::White);
		HighScore.setOutlineColor(sf::Color::White);

		Play.setOutlineThickness(2);
		Quit.setOutlineThickness(2);
		HighScore.setOutlineThickness(2);


		Play.setPosition(sf::Vector2f(25.0f, 220.0f));
		HighScore.setPosition(sf::Vector2f(25.0f, 280.0f));
		Quit.setPosition(sf::Vector2f(25.0f, 340.0f));
		
	
		menu_background.setTexture(&menu_texture);
		Play.setTexture(&button_texture);
		HighScore.setTexture(&button_texture);
		Quit.setTexture(&button_texture);

		Play_text.setFont(font);
		Play_text.setString("PLAY");

		HighScore_text.setFont(font);
		HighScore_text.setString("HIGHSCORE");

		Quit_text.setFont(font);
		Quit_text.setString("QUIT");

		Play_text.setPosition(sf::Vector2f(90.0f, 230.0f));
		HighScore_text.setPosition(sf::Vector2f(50.0f, 290.0f));
		Quit_text.setPosition(sf::Vector2f(90.0f, 350.0f));

		Play_text.setCharacterSize(24);
		HighScore_text.setCharacterSize(24);
		Quit_text.setCharacterSize(24);

								   
		Play_text.setFillColor(sf::Color::Red);
		HighScore_text.setFillColor(sf::Color::Red);
		Quit_text.setFillColor(sf::Color::Red);

		Play_text.setStyle(sf::Text::Bold);
		HighScore_text.setStyle(sf::Text::Bold);
		Quit_text.setStyle(sf::Text::Bold);


	}

	void draw_menu() //This draws the menu items (it won't automatically appear in window, since it just loads it in a buffer) for appearance windows.display() is used
	{
		window.draw(menu_background);
		window.draw(Play);
		window.draw(Quit);
		window.draw(HighScore);
		window.draw(Play_text);
		window.draw(HighScore_text);
		window.draw(Quit_text);
		
	}

	bool IsPlay() //checks if the play button is pressed or not
	{
		int x = 0; int y = 0;
		x=sf::Mouse::getPosition(window).x;
		y = sf::Mouse::getPosition(window).y;

		for (int x_pixels = 23; x_pixels <= 225; x_pixels++)
		{
			for (int y_pixels = 217; y_pixels <= 268; y_pixels++)
			{
				if (x == x_pixels && y == y_pixels)
				{
					return true;
				}
			}
		}

		return false;
		
	}

	bool IsHighScore() //checks if the highscore button is pressed or not
	{
		int x = 0; int y = 0;
		x = sf::Mouse::getPosition(window).x;
		y = sf::Mouse::getPosition(window).y;

		for (int x_pixels = 23; x_pixels <= 225; x_pixels++)
		{
			for (int y_pixels = 280; y_pixels <= 325; y_pixels++)
			{
				if (x == x_pixels && y == y_pixels)
				{
					return true;
				}
			}
		}

		return false;
	}

	bool isQuit() //checks if the quit button is pressed or not
	{
		int x = 0; int y = 0;
		x = sf::Mouse::getPosition(window).x;
		y = sf::Mouse::getPosition(window).y;

		for (int x_pixels = 23; x_pixels <= 225; x_pixels++)
		{
			for (int y_pixels = 337; y_pixels <= 389; y_pixels++)
			{
				if (x == x_pixels && y == y_pixels)
				{
					return true;
				}
			}
		}

		return false;
	}


};

//This is the highscore menu class
class highscore
{
private:
	sf::Texture highscore_texture;
	sf::RectangleShape highscore_bg;
	sf::Text Title;
	sf::Text Back;
	sf::RectangleShape Back_button;
	sf::Texture back_texture;
	sf::Text highscore_text;
	sf::Font font;

	int gethighscore() //This returns the highest score saved in the text file. Note it is in the private scope since it is just a utility function
	{
		int temp[3] = {0};
		ifstream getscore;
		getscore.open("score.txt");
		vector<int> check;
		int get = 0;
		while (!getscore.eof())
		{
			getscore >> get;
			check.push_back(get);
		}
		get = check[0];
		for (unsigned int i = 0; i < check.size(); i++)
		{
			if (check[i] > get)
			{
				get = check[i];
			}
			i++;
		}

		getscore.close();

		return get;
	}

public:

	int displayhigh()
	{
		return gethighscore();
	}

	highscore() //highscore menu's constructor
	{
		if (!font.loadFromFile("OpenSans.ttf"))
		{
			cout << "Error!" << endl;
		}

		if (!back_texture.loadFromFile("menu_button.jpg"))
		{
			cout << "Error! Unsuccessful button texture load" << endl;
		}

		if (!highscore_texture.loadFromFile("bg_else.jpg"))
		{
			cout << "Error! Unsuccessful highscore texture load" << endl;
		}

		highscore_text.setString(to_string(gethighscore())); //it converts the integer highscore value to string and then puts it in highscore_text for later display


		Back_button.setTexture(&back_texture);
		highscore_bg.setTexture(&highscore_texture);
		highscore_bg.setSize(sf::Vector2f(800.0f, 600.0f));

		Back.setFont(font);
		Title.setFont(font);
		highscore_text.setFont(font);
		Title.setString("HIGH SCORE");
		Back_button.setSize(sf::Vector2f(200.0f, 50.0f));
		Back_button.setPosition(sf::Vector2f(570.0f, 280.0f));
		Title.setPosition(sf::Vector2f(250.0f, 50.0f));
		highscore_text.setPosition(sf::Vector2f(360.0f, 150.0f));
		Back.setString("BACK");
		Title.setCharacterSize(50);
		highscore_text.setCharacterSize(40);
		Back.setCharacterSize(24);

		Back.setPosition(sf::Vector2f(640.0f, 290.0f));

		Title.setFillColor(sf::Color::Red);
		highscore_text.setFillColor(sf::Color::Red);
		Back.setFillColor(sf::Color::Red);

		Title.setStyle(sf::Text::Bold | sf::Text::Underlined);
		Back.setStyle(sf::Text::Bold);


	}

	void draw_highscore() //draws the highscore menu
	{
		window.draw(highscore_bg);
		window.draw(highscore_text);
		window.draw(Title);
		window.draw(Back_button);
		window.draw(Back);
	}

	bool IsBack() //checks if the Back button is clicked or not
	{
		int x = 0; int y = 0;
		x = sf::Mouse::getPosition(window).x;
		y = sf::Mouse::getPosition(window).y;

		for (int x_pixels = 570; x_pixels <= 768; x_pixels++)
		{
			for (int y_pixels = 280; y_pixels <= 324; y_pixels++)
			{
				if (x == x_pixels && y == y_pixels)
				{
					return true;
				}
			}
		}
		return false;
	}
	
};


class ghost_class //This is the class that implements the ghost
{

private:

	int x;
	int y;
	friend class pac_class;
	sf::Sprite ghost;
	sf::Texture texture;

public:
	ghost_class()
	{

		if (!texture.loadFromFile("ghost.png")) //load the ghost image
		{
			cout << "Error! PacMan texture not loaded properly!" << endl;
		}

		ghost.setTexture(texture); //set the ghost's sprite (entity) texture to its image
		
		ghost.setPosition(sf::Vector2f(float(360), float(210))); //set the initial position of the ghost

		ghost.setScale(sf::Vector2f(0.0615f, 0.0615f)); //set the size of the ghost in ratio  (original size/needed size) 
		
		texture.setSmooth(true); //set the texture smooth

	}

	void respawn_ghost()
	{
		ghost.setPosition(sf::Vector2f(float(360), float(210)));
	}

	void ghost_draw() //draws the ghost sprite
	{
		window.draw(ghost);
	}

	sf::FloatRect getghost() //it returns the bounds of the ghost sprite
	{
		return ghost.getGlobalBounds();
	}

	
	void ghost_dir() //This is a small algorithm used to prevent using complex algorithms like A*/Djikstra pathfinding which are generally parts of Data structure
	{
		int rand_num = 0; //Used to assign 4 different random directions to the ghost
		srand(time(NULL));
		bool flag = true;
		while (flag)
		{
			rand_num = rand() % 4;
			if (rand_num == 0)
			{
				ghost.move(sf::Vector2f(-2.0f, 0));
			}

			else if (rand_num == 1)
			{
				ghost.move(sf::Vector2f(2.0f, 0));
			}

			else if (rand_num == 2)
			{
				ghost.move(sf::Vector2f(0, -2.0f));
			}

			else if (rand_num == 3)
			{
				ghost.move(sf::Vector2f(0, 2.0f));
			}

			for (int i = 0; i < rect_sum; i++)
			{
				if (ghost.getGlobalBounds().intersects(rectangles[i].getGlobalBounds())) //It checks if the ghost intersects with the maze boundaries in its next move.
				{                                                                        //If it does, it moves back and by hit and trial, checks again for a free block.
					if (rand_num == 0)
					{
						ghost.move(sf::Vector2f(2.0f, 0));
					}

					else if (rand_num == 1)
					{
						ghost.move(sf::Vector2f(-2.0f, 0));
					}

					else if (rand_num == 2)
					{
						ghost.move(sf::Vector2f(0, 2.0f));
					}

					else if (rand_num == 3)
					{
						ghost.move(sf::Vector2f(0, -2.0f));
					}
					flag = true;
				}
				else flag = false;


			}
		}
	}

};



class pacman_class //This class implements the pacman which the player moves to collect points/fruits aswell as some contains additional functions
{

private:
	int x;
	int y;
	int points;
	int fruits;
	sf::Sprite pac; //the pacman entity
	sf::RectangleShape game_bg; //The game menu background shape
	sf::Texture bg_texture; //Game menu background's texture
	friend class ghost_class;


	vector<sf::CircleShape> point; //shape for implementing the coins/points
	vector<sf::RectangleShape> fruit; //shape for implementing the fruits/bonuses
	sf::Texture texture; //texture for pacman
	sf::Text scoreval; //Text to show the score on scoreboard
	sf::Text score; //Text to show the word "Score"
	sf::Font font; //Font used for the scoreboard

public:


	void generate_fruit(char map[][12]) //This function generates the fruits/bonuses in the maze randomly in a total of 4.
	{
		sf::RectangleShape temp;
		srand(time(NULL));
		int i = 0;
		int offsetx = 0;
		int offsety = 0;
		int rand_num = 0;
		for (int row = 0; row < 11; row++)
		{
			offsetx = 0;
			for (int col = 0; col < 11; col++)
			{
				offsetx = 0;
				for (int row = 0; row < 11; row++)
				{

					if (map[row][col] == '0') //This checks if the level map has a 0 aswell as if the empty space
					{                                                                               //is not the spawn points of pacman and ghost, then it will spawn it
						rand_num = rand() % 5;

						if (rand_num == 1)
						{
							temp.setFillColor(sf::Color::Red);
							temp.setSize(sf::Vector2f(10, 10));
							temp.setOrigin(sf::Vector2f(float(-215), float(-65)));
							temp.setPosition(float(0 + offsetx), float(0 + offsety));
							fruit.push_back(temp);

							for (unsigned int j = 0; j < point.size(); j++)
							{
								if (fruit[i].getGlobalBounds().intersects(point[j].getGlobalBounds()))
								{
									point.erase(point.begin() + j);
								}

							}
							i++;
							if (i == 5) return;
						}

					}
					offsetx = offsetx + 40;

				}
				offsety = offsety + 40;
			}
		}

		for (unsigned int i = 0; i < fruit.size(); i++)
		{
			if (pac.getGlobalBounds().intersects(fruit[i].getGlobalBounds()))
			{
				fruit.erase(fruit.begin() + i);
			}
		}
	}

	bool IsAllTaken()
	{
		if (fruit.size() == NULL && point.size() == NULL)
		{
			return true;
		}

		else
		{
			return false;
		}
	}

	void draw_fruit() //draws the fruits, and sets it in buffer
	{
		for (unsigned int i = 0; i < fruit.size(); i++)
		{
			window.draw(fruit[i]);
		}
	}

	void isFruit_taken() //Checks if the fruit is taken by the pacman. If so, it increments the score by 6
	{
		for (unsigned int i = 0; i < fruit.size(); i++)
		{
			if (pac.getGlobalBounds().intersects(fruit[i].getGlobalBounds())) {
				fruit.erase(fruit.begin() + (i));
				points += 6;
			}
		}
	}

	void generate_points(char map[][12]) //This function generations the points/coins on the map
	{
		sf::CircleShape temp;
		int i = 0;
		int offsetx = 0;
		int offsety = 0;
		for (int col = 0; col < 11; col++)
		{
			offsetx = 0;
			for (int row = 0; row < 11; row++)
			{

				if (map[row][col] == '0') //This condition has same functionality as for generate fruit above
				{

					temp.setFillColor(sf::Color::Yellow);
					temp.setRadius(5.0f);
					temp.setOrigin(sf::Vector2f(float(-215), float(-65)));
					temp.setPosition(float(0 + offsetx), float(0 + offsety));
					point.push_back(temp);
					i++;


				}
				offsetx = offsetx + 40;
			}
			offsety = offsety + 40;
		}

		for (unsigned int i = 0; i < point.size(); i++)
		{
			if (pac.getGlobalBounds().intersects(point[i].getGlobalBounds()))
			{
				point.erase(point.begin() + i);

			}
		}

	}

	void draw_points() //draws the points and sets it in buffer
	{
		for (unsigned int i = 0; i < point.size(); i++)
		{
			window.draw(point[i]);
		}

	}

	void respawn_pac()
	{
		pac.setPosition(sf::Vector2f(float(520), float(410)));
	}

	pacman_class() //The constructor for the pacman class
	{
		points = 0;
		if (!texture.loadFromFile("pacman.png")) //load pacman image as png
		{
			cout << "Error! PacMan texture not loaded properly!" << endl;
		}

		if (!font.loadFromFile("OpenSans.ttf")) //load the font used for the scoreboard
		{
			cout << "Error! Font not loaded properly!" << endl;
		}

		if (!bg_texture.loadFromFile("bg_else.jpg")) //load texture for the game menu background
		{
			cout << "Error! Background image not loaded properly!" << endl;
		}

		game_bg.setSize(sf::Vector2f(800.0f, 600.0f));
		game_bg.setTexture(&bg_texture);
		pac.setTexture(texture);

		pac.setPosition(sf::Vector2f(float(520), float(410)));

		pac.setScale(sf::Vector2f(0.22f, 0.22f));


		texture.setSmooth(true);

		scoreval.setFont(font);
		score.setFont(font);
		score.setString("Score: ");
		scoreval.setString(to_string(points));
		score.setPosition(sf::Vector2f(float(620), float(100)));
		scoreval.setPosition(sf::Vector2f(float(720), float(100)));
	}

	void pac_draw() //draws the pacman and sets it in buffer
	{
		window.draw(pac);
	}

	bool isDead(ghost_class &ghosts) //it checks if the pacman is dead by checking the intersection of the bounds of the ghost and pacman and returns a boolean
	{
		sf::FloatRect rec;
		rec = ghosts.getghost();

		if (rec.intersects(pac.getGlobalBounds()))
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	void bg_draw() //draws the background image, and sets it in buffer
	{
		window.draw(game_bg);
	}

	void resetall()
	{
		points = 0;

		point.clear();
		fruit.clear();
	}

	void score_draw() //draws the scoreboard
	{
		scoreval.setString(to_string(points));
		window.draw(score);
		window.draw(scoreval);
	}

	bool collision() //This function checks if the pacman has collided with the maze borders via bounds
	{
		for (int i = 0; i < rect_sum; i++)
		{
			if (pac.getGlobalBounds().intersects(rectangles[i].getGlobalBounds())) { return true; }
		}

		return false;
	}

	int getscore()
	{
		return points;
	}

	void isPoint_taken() //This function checks if the point/coin is taken. If so, the score is incremented by 1.
	{
		for (unsigned int i = 0; i < point.size(); i++)
		{
			if (pac.getGlobalBounds().intersects(point[i].getGlobalBounds())) {
				point.erase(point.begin() + (i));
				points++;
			}
		}


	}

	void pac_movex(float xvelocity) //This function moves the pacman in x-direction
	{
		pac.move(sf::Vector2f(xvelocity, 0));

	}

	void pac_movey(float yvelocity) //This function moves the pacman in y-direction
	{
		pac.move(sf::Vector2f(0, yvelocity));
	}

	int getx()
	{
		return x;
	}

	int gety()
	{
		return y;
	}
};


void update_all(pacman_class &pacman, ghost_class &ghost) //This is seperate function bunching up all the draw calls and use them without redundant code
{
	pacman.bg_draw();

	for (int i = 0; i < rect_sum; i++)
	{
		rectangles[i].setTexture(&for_rec);
		window.draw(rectangles[i]);
	}
	

	pacman.pac_draw();
	pacman.draw_points();
	pacman.draw_fruit();
	pacman.isFruit_taken();
	pacman.isPoint_taken();
	pacman.score_draw();
	ghost.ghost_dir();
	ghost.ghost_draw();
}

int main()
{
	scorefile.open("score.txt", ios::app); //Open the score file in append mode
	menu menu_obj;
	highscore score_menu;

	int offsety = 0;
	int offsetx = 0;
	char map[][12] = {            //This is the level map which is the driving force behind the generation of the maze
		{ "11111111111" },       //Basically the 1's represent a solid block and 0's represent a free path for movement
		{ "10000000001" },
		{ "10011111101" },
		{ "10000000001" },
		{ "10110110011" },
		{ "10011100111" },
		{ "10000000001" },
		{ "10111111101" },
		{ "10000000001" },
		{ "11111111111" }
	};

	sf::Music music;

	if (!music.openFromFile("pacman.ogg"))
	{
		cout << "Error!";
	}



	int i = 0;
	float pac_vel = 0;
	for (int col = 0; col < 11; col++)
	{
		offsetx = 0;
		for (int row = 0; row < 11; row++)
		{
			
			if (map[row][col] == '1')
			{
				rectangles[i].setSize(sf::Vector2f(40, 40));
				rectangles[i].setOrigin(sf::Vector2f(float(-200), float(-50)));
				rectangles[i].setPosition(float(0+offsetx),float(0+offsety));
				i++;
			}
			offsetx = offsetx + 40;
		}
		offsety = offsety + 40;
	}

	
	menu_obj.draw_menu();
	window.display();

	pacman_class pacman;
	ghost_class ghost;

	pacman.generate_points(map);
	pacman.generate_fruit(map);
	bool flag = true;
	window.clear();
	
	while (window.isOpen()) //This is the main game loop where all the magic happens
	{
		
		sf::Event event; //Events Basically checks the interactions with the window like hovering over it, clicking it, typing etc

		while (window.pollEvent(event)) //This stacks up all the events and handles them up
		{

			switch (event.type)
			{
			case sf::Event::Closed: //Check if the window's close button is clicked
			{
				window.close();
			    break;
			}

			case sf::Event::MouseButtonPressed: //checks if the mouse button is clicked inside the window
			{
				
				if (event.mouseButton.button == sf::Mouse::Left) //checks the left mouse button click
				{
					cout << sf::Mouse::getPosition(window).x<<endl;
					cout << sf::Mouse::getPosition(window).y << endl << endl;
					if (menu_obj.IsPlay() == true) //left click on Play button starts game
					{
						window.clear();
						if (!for_rec.loadFromFile("brick.jpg"))
						{
							cout << "Error! Unsuccessful boundary texture load" << endl;
						}

						update_all(pacman, ghost);
						flag = false;
						window.display();
						music.play();
						cout << "Play" << endl;;
					}

					else if (menu_obj.IsHighScore() == true) //left click on Highscore button gets you to highscore menu
					{
						cout << "HighScore" << endl;
						window.clear();
						score_menu.draw_highscore();
						window.display();
					}

					else if (menu_obj.isQuit() == true) //left click on quit button quits the game
					{
						cout << "Quit" << endl;
						exit(0);
					}

					else if (score_menu.IsBack()) //left click on back button in highscore menu brings you back to main menu
					{
						cout << "Back" << endl;
						window.clear();
						
						menu_obj.draw_menu();
						window.display();
					}
				}

				break;
			}

			case sf::Event::Resized: //Just a test case for resize of screen
			{
				cout << "You resized the screen!\n";
				cout << "Height: " << event.size.height << endl;
				cout << "Width: " << event.size.width << endl;
				window.display();
				break;
			}


			case sf::Event::KeyPressed: //Checks if a key is pressed

			{

				if (event.key.code == sf::Keyboard::D) //checks D press
				{
					//while (!GetAsyncKeyState('A') && !GetAsyncKeyState('W') && !GetAsyncKeyState('S')) //GetAsyncKeyState takes keyboard events while other loops 
				//	{                                                                                 //are running, hence does not stop the program in the middle for input
					                                                                                 //used for continuous movement of pacman
					if (flag == false)
					{

						pac_vel = 5;
						pacman.pac_movex(pac_vel);


						if (pacman.collision() == true)
						{
							pac_vel = -5;
							pacman.pac_movex(pac_vel);
						}

					}
						
					//}

				}
					if (event.key.code == sf::Keyboard::A) //A key event check
					{
					//	while (!GetAsyncKeyState('D') && !GetAsyncKeyState('W') && !GetAsyncKeyState('S'))
					//{
						if (flag == false)
						{

							pac_vel = -5;
							pacman.pac_movex(pac_vel);

							if (pacman.collision() == true)
							{
								pac_vel = 5;
								pacman.pac_movex(pac_vel);
							}

						}
					//	}

					}


					if (event.key.code == sf::Keyboard::W) //W key event check
					{
					//	while (!GetAsyncKeyState('A') && !GetAsyncKeyState('D') && !GetAsyncKeyState('S'))
					//	{
						
						if (flag == false)
						{

							pac_vel = -5;
							pacman.pac_movey(pac_vel);

							if (pacman.collision() == true)
							{
								pac_vel = 5;
								pacman.pac_movey(pac_vel);
							}
						}
				
				//		}
					}


					if (event.key.code == sf::Keyboard::S) //Checks S key event
					{
					//	while (!GetAsyncKeyState('A') && !GetAsyncKeyState('W') && !GetAsyncKeyState('D'))
					//	{
						if (flag == false)
						{

							pac_vel = 5;
							pacman.pac_movey(pac_vel);

							if (pacman.collision() == true)
							{
								pac_vel = -5;
								pacman.pac_movey(pac_vel);

							}
						}

					 //  }
					}

					break;
				}

			}
			}

		if (flag == false)
		{
			window.clear();

			for (int i = 0; i < rect_sum; i++)
			{
				window.draw(rectangles[i]);
			}


			if (pacman.isDead(ghost) == true)
			{
				scorefile << pacman.getscore() << endl;
				scorefile.close();
				window.clear();
				sf::Text FinalScore;
				sf::Text HighScore;
				sf::Text HighScoreText;
				sf::Text FinalScoreText;
				sf::Font Ffont;

				Ffont.loadFromFile("OpenSans.ttf");

				FinalScore.setFont(Ffont);
				FinalScore.setString(to_string(pacman.getscore()));
				FinalScore.setCharacterSize(25);
				FinalScoreText.setCharacterSize(25);
				FinalScoreText.setFillColor(sf::Color::Red);
				FinalScoreText.setPosition(sf::Vector2f(280.0f, 250.0f));

				FinalScoreText.setFont(Ffont);
				FinalScoreText.setString("Your Score: ");
				FinalScore.setFillColor(sf::Color::Red);
				FinalScore.setPosition(sf::Vector2f(415.0f, 250.0f));

				HighScore.setCharacterSize(25);
				HighScore.setFont(Ffont);
				HighScore.setString(to_string(score_menu.displayhigh()));
				HighScore.setFillColor(sf::Color::White);
				HighScore.setPosition(sf::Vector2f(415.0f, 300.0f));

				HighScoreText.setCharacterSize(25);
				HighScoreText.setFont(Ffont);
				HighScoreText.setString("High Score: ");
				HighScoreText.setFillColor(sf::Color::White);
				HighScoreText.setPosition(sf::Vector2f(280.0f, 300.0f));


				window.draw(FinalScore);
				window.draw(FinalScoreText);
				window.draw(HighScoreText);
				window.draw(HighScore);
				window.display();
				Sleep(5000);
				window.clear();
				menu_obj.draw_menu();
				flag = true;
				pacman.respawn_pac();
				ghost.respawn_ghost();
				pacman.resetall();
				pacman.generate_points(map);
				pacman.generate_fruit(map);
				
				window.display();
				
		
			}

			else {

				update_all(pacman, ghost);
				window.display();
			}
			if (pacman.IsAllTaken() == true)
			{
				pacman.generate_points(map);
				pacman.generate_fruit(map);
			}
			Sleep(6);
		}

		}

	}
	
