#include <SFML/Graphics.hpp>
#include<iostream>
#include<fstream>
using namespace std;
using namespace sf;

int main()
{
    RenderWindow window(sf::VideoMode(790, 490), "BEJEWELED BLITZ GAME");

    Texture images[21], empty_texture; // Array to hold textures

    //// Load images into the array
    if (!images[0].loadFromFile("C:\\Users\\DELL\\OneDrive\\Pictures\\Saved Pictures\\Bejeweled_blue_gem_promotional.png") ||
        !images[1].loadFromFile("C:\\Users\\DELL\\OneDrive\\Pictures\\Saved Pictures\\Bejeweled_green_gem_promotional.png") ||
        !images[2].loadFromFile("C:\\Users\\DELL\\OneDrive\\Pictures\\Saved Pictures\\Bejeweled_orange_gem_promotional.png") ||
        !images[3].loadFromFile("C:\\Users\\DELL\\OneDrive\\Pictures\\Saved Pictures\\Bejeweled_purple_gem_promotional.png") ||
        !images[4].loadFromFile("C:\\Users\\DELL\\OneDrive\\Pictures\\Saved Pictures\\Bejeweled_red_gem_promotional.png") ||
        !images[5].loadFromFile("C:\\Users\\DELL\\OneDrive\\Pictures\\Saved Pictures\\Bejeweled_white_gem_promotional.png") ||
        !images[6].loadFromFile("C:\\Users\\DELL\\OneDrive\\Pictures\\Saved Pictures\\Bejeweled_yellow_gem_promotional.png") ||
        !images[7].loadFromFile("C:\\Users\\DELL\\OneDrive\\Pictures\\Saved Pictures\\imagefire0.png") ||
        !images[8].loadFromFile("C:\\Users\\DELL\\OneDrive\\Pictures\\Saved Pictures\\imagefire1.png") ||
        !images[9].loadFromFile("C:\\Users\\DELL\\OneDrive\\Pictures\\Saved Pictures\\imagefire2.png") ||
        !images[10].loadFromFile("C:\\Users\\DELL\\OneDrive\\Pictures\\Saved Pictures\\imagefire3.png") ||
        !images[11].loadFromFile("C:\\Users\\DELL\\OneDrive\\Pictures\\Saved Pictures\\imagefire4.png") ||
        !images[12].loadFromFile("C:\\Users\\DELL\\OneDrive\\Pictures\\Saved Pictures\\imagefire5.png") ||
        !images[13].loadFromFile("C:\\Users\\DELL\\OneDrive\\Pictures\\Saved Pictures\\imagefire6.png") ||
        !images[14].loadFromFile("C:\\Users\\DELL\\OneDrive\\Pictures\\Saved Pictures\\imageeffect0.png") ||
        !images[15].loadFromFile("C:\\Users\\DELL\\OneDrive\\Pictures\\Saved Pictures\\imageeffect1.png") ||
        !images[16].loadFromFile("C:\\Users\\DELL\\OneDrive\\Pictures\\Saved Pictures\\imageeffect2.png") ||
        !images[17].loadFromFile("C:\\Users\\DELL\\OneDrive\\Pictures\\Saved Pictures\\imageeffect3.png") ||
        !images[18].loadFromFile("C:\\Users\\DELL\\OneDrive\\Pictures\\Saved Pictures\\imageeffect4.png") ||
        !images[19].loadFromFile("C:\\Users\\DELL\\OneDrive\\Pictures\\Saved Pictures\\imageeffect5.png") ||
        !images[20].loadFromFile("C:\\Users\\DELL\\OneDrive\\Pictures\\Saved Pictures\\imageeffect6.png"))

    {
        // Handle loading failure
        return -1;
    }
   Texture background_texture;
    if (!background_texture.loadFromFile("C:\\Users\\DELL\\OneDrive\\Pictures\\Saved Pictures\\game_background.jpg"))
    {
        // Handle loading failure
        return -1;
    }
    Clock gameClock;
    Font font;
    if (!font.loadFromFile("C:\\Users\\DELL\\OneDrive\\Pictures\\Saved Pictures\\font.ttf"))
    {
        return -1;
    }
    int score = 0, score_3_matches = 250, score_4_matches = 500, score_5_matches = 1000, score_4_special = 1050, score_5_special = 4000,high_score;

    Text startText;
    startText.setFont(font);
    startText.setCharacterSize(25);
    startText.setFillColor(sf::Color::Black);
    startText.setPosition(530.f, 360.f);
    int gameTimeLimit = 60; // Time limit in seconds
    Text scoreText;
    scoreText.setFont(font); 
    scoreText.setCharacterSize(25);
    scoreText.setFillColor(sf::Color::Black); 
    scoreText.setPosition(530.f,400.f);
    scoreText.setString("Score: " + std::to_string(score));
    ifstream infile("high_score.txt");
    infile >> high_score;
    if (infile.is_open())
    {
        infile >> high_score; // Read high score from the file
        infile.close();
    }
    bool isGameRunning = true;

    Sprite backgroundSprite(background_texture);
    Sprite sprites[8][8]; // 2D array to hold sprites
    int num = 0, highlighted_row = 3, highlighted_col = 3;
    float gemSize = 55.f, scale = 0.15f, off_setX = 51.f, off_setY = 35.f;
    bool enter_key_pressed = false, swap_triggered = false, isGemEmpty[8][8] = { false }, match_found = false;
    // Assign textures to sprites in a loop
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            num = rand() % 7;
            if (j == 7)
            {
                sprites[i][j].setTexture(images[num]);
            }
            else
            {
                sprites[i][j].setTexture(images[num % 7]);
            }
            sprites[i][j].setScale(0.15f, 0.15f);
            sprites[i][j].setPosition((j * 55.f) + off_setX, (i * 55.f) + off_setY);
        }
    }
    bool matchFiveUp = false;
    bool matchFourUp = false;
    bool destroyUp = false;

    bool matchFiveDown = false;
    bool matchFourDown = false;
    bool destroyDown = false;

    bool matchFiveRight = false;
    bool matchFourRight = false;
    bool destroyRight = false;

    bool matchFiveLeft = false;
    bool matchFourLeft = false;
    bool destroyLeft = false;

    bool specialFourUp1 = false;
    bool specialFourUp2 = false;
    bool specialFourUp3 = false;
    bool specialFourUp4 = false;
    bool specialFourUp5 = false;
    bool specialFourUp6 = false;
    bool specialRealFourUp = false;

    bool specialFourDown1 = false;
    bool specialFourDown2 = false;
    bool specialFourDown3 = false;
    bool specialFourDown4 = false;
    bool specialFourDown5 = false;
    bool specialFourDown6 = false;
    bool specialRealFourDown = false;

    bool specialFourLeft1 = false;
    bool specialFourLeft2 = false;
    bool specialFourLeft3 = false;
    bool specialFourLeft4 = false;
    bool specialFourLeft5 = false;
    bool specialFourLeft6 = false;
    bool specialRealFourLeft = false;

    bool specialFourRight1 = false;
    bool specialFourRight2 = false;
    bool specialFourRight3 = false;
    bool specialFourRight4 = false;
    bool specialFourRight5 = false;
    bool specialFourRight6 = false;
    bool specialRealFourRight = false;

    bool specialFive = false;
    int specialRow = 0;
    int specialCol = 0;


    Sprite tempSprites[8][8];
    int indexUp1 = 0;
    int indexUp2 = 0;
    int indexDown1 = 0;
    int indexDown2 = 0;
    int indexRight1 = 0;
    int indexRight2 = 0;
    int indexLeft1 = 0;
    int indexLeft2 = 0;


    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            match_found = false;
            if (event.type == Event::Closed)
            {
                window.close();
            }
                

            if (event.type == Event::KeyPressed)
            {
                   if (event.key.code == Keyboard::Up && highlighted_row > 0)
                   {
                      if (enter_key_pressed && swap_triggered)
                      {
                        //FIVE MATCHES
                        if (sprites[highlighted_row][highlighted_col].getTexture() == sprites[highlighted_row - 1][highlighted_col - 1].getTexture() &&
                            sprites[highlighted_row][highlighted_col].getTexture() == sprites[highlighted_row - 1][highlighted_col - 2].getTexture() &&
                            sprites[highlighted_row][highlighted_col].getTexture() == sprites[highlighted_row - 1][highlighted_col + 1].getTexture() &&
                            sprites[highlighted_row][highlighted_col].getTexture() == sprites[highlighted_row - 1][highlighted_col + 2].getTexture())
                        {
                            // storing indexes of the above position
                            indexUp1 = highlighted_row - 1;
                            indexUp2 = highlighted_col;

                            const sf::Texture* texture = sprites[highlighted_row][highlighted_col].getTexture();
                            tempSprites[indexUp1][indexUp2].setTexture(*texture);

                            matchFiveUp = true;

                            Sprite temp = sprites[highlighted_row - 1][highlighted_col];
                            sprites[highlighted_row][highlighted_col] = sprites[highlighted_row - 1][highlighted_col];
                            sprites[highlighted_row - 1][highlighted_col] = temp;
                            // Update positions after swapping
                            sprites[highlighted_row][highlighted_col].setPosition((highlighted_col * gemSize) + off_setX, (highlighted_row * gemSize) + off_setY);
                            sprites[highlighted_row - 1][highlighted_col].setPosition((highlighted_col * gemSize) + off_setX, ((highlighted_row - 1) * gemSize) + off_setY);
                            score = score + score_5_matches;
                            scoreText.setString("Score: " + std::to_string(score));

                        }
                        //FOUR MATCHES
                        else if ((sprites[highlighted_row][highlighted_col].getTexture() == sprites[highlighted_row - 1][highlighted_col - 1].getTexture() &&
                                  sprites[highlighted_row][highlighted_col].getTexture() == sprites[highlighted_row - 1][highlighted_col - 2].getTexture() &&
                                  sprites[highlighted_row][highlighted_col].getTexture() == sprites[highlighted_row - 1][highlighted_col + 1].getTexture()) ||
                                 (sprites[highlighted_row][highlighted_col].getTexture() == sprites[highlighted_row - 1][highlighted_col - 1].getTexture() &&
                                  sprites[highlighted_row][highlighted_col].getTexture() == sprites[highlighted_row - 1][highlighted_col + 1].getTexture() &&
                                  sprites[highlighted_row][highlighted_col].getTexture() == sprites[highlighted_row - 1][highlighted_col + 2].getTexture()))
                        {

                            // storing indexes of the above position
                            indexUp1 = highlighted_row - 1;
                            indexUp2 = highlighted_col;

                            // storing the texture to temporary sprite
                            const Texture* texturePtr = sprites[highlighted_row][highlighted_col].getTexture();
                            tempSprites[indexUp1][indexUp2].setTexture(*texturePtr);

                            matchFourUp = true;

                            Sprite temp = sprites[highlighted_row][highlighted_col];
                            sprites[highlighted_row][highlighted_col] = sprites[highlighted_row - 1][highlighted_col];
                            sprites[highlighted_row - 1][highlighted_col] = temp;

                            // Update positions after swapping
                            sprites[highlighted_row][highlighted_col].setPosition((highlighted_col * gemSize) + off_setX, (highlighted_row * gemSize) + off_setY);
                            sprites[highlighted_row - 1][highlighted_col].setPosition((highlighted_col * gemSize) + off_setX, ((highlighted_row - 1) * gemSize) + off_setY);
                            score = score + score_4_matches;
                            scoreText.setString("Score: " + std::to_string(score));
                        }
                        //ELBOW
                        else if (sprites[highlighted_row][highlighted_col].getTexture() == sprites[highlighted_row - 1][highlighted_col - 1].getTexture() &&
                            sprites[highlighted_row][highlighted_col].getTexture() == sprites[highlighted_row - 1][highlighted_col - 2].getTexture() &&
                            sprites[highlighted_row][highlighted_col].getTexture() == sprites[highlighted_row - 2][highlighted_col].getTexture() &&
                            sprites[highlighted_row][highlighted_col].getTexture() == sprites[highlighted_row - 3][highlighted_col].getTexture() ||
                            sprites[highlighted_row][highlighted_col].getTexture() == sprites[highlighted_row - 1][highlighted_col + 1].getTexture() &&
                            sprites[highlighted_row][highlighted_col].getTexture() == sprites[highlighted_row - 1][highlighted_col + 2].getTexture() &&
                            sprites[highlighted_row][highlighted_col].getTexture() == sprites[highlighted_row - 2][highlighted_col].getTexture() &&
                            sprites[highlighted_row][highlighted_col].getTexture() == sprites[highlighted_row - 3][highlighted_col].getTexture())
                        {
                            // storing indexes of the above position
                            indexUp1 = highlighted_row - 1;
                            indexUp2 = highlighted_col;

                            // storing the texture to temporary sprite
                            const Texture* texturePtr = sprites[highlighted_row][highlighted_col].getTexture();
                            tempSprites[indexUp1][indexUp2].setTexture(*texturePtr);

                            destroyUp = true;

                            Sprite temp = sprites[highlighted_row][highlighted_col];
                            sprites[highlighted_row][highlighted_col] = sprites[highlighted_row - 1][highlighted_col];
                            sprites[highlighted_row - 1][highlighted_col] = temp;
                            // Update positions after swapping
                            sprites[highlighted_row][highlighted_col].setPosition((highlighted_col * gemSize) + off_setX, (highlighted_row * gemSize) + off_setY);
                            sprites[highlighted_row - 1][highlighted_col].setPosition((highlighted_col * gemSize) + off_setX, ((highlighted_row - 1) * gemSize) + off_setY);
                            score = score + score_5_matches;
                            scoreText.setString("Score: " + std::to_string(score));
                        }

                        else if (sprites[highlighted_row][highlighted_col].getTexture() == sprites[highlighted_row - 1][highlighted_col - 1].getTexture() &&
                            sprites[highlighted_row][highlighted_col].getTexture() == sprites[highlighted_row - 1][highlighted_col + 1].getTexture())
                        {
                            Sprite temp = sprites[highlighted_row][highlighted_col];
                            sprites[highlighted_row][highlighted_col] = sprites[highlighted_row - 1][highlighted_col];
                            sprites[highlighted_row - 1][highlighted_col] = temp;
                            // Update positions after swapping
                            sprites[highlighted_row][highlighted_col].setPosition((highlighted_col * gemSize) + off_setX, (highlighted_row * gemSize) + off_setY);
                            sprites[highlighted_row - 1][highlighted_col].setPosition((highlighted_col * gemSize) + off_setX, ((highlighted_row - 1) * gemSize) + off_setY);
                            score = score + score_3_matches;
                            scoreText.setString("Score: " + std::to_string(score));
                        }
                        //THREE MATCHES IN ROW
                        else if (sprites[highlighted_row][highlighted_col].getTexture() == sprites[highlighted_row - 1][highlighted_col - 1].getTexture() &&
                            sprites[highlighted_row][highlighted_col].getTexture() == sprites[highlighted_row - 1][highlighted_col - 2].getTexture())
                        {
                            Sprite temp = sprites[highlighted_row][highlighted_col];
                            sprites[highlighted_row][highlighted_col] = sprites[highlighted_row - 1][highlighted_col];
                            sprites[highlighted_row - 1][highlighted_col] = temp;
                            // Update positions after swapping
                            sprites[highlighted_row][highlighted_col].setPosition((highlighted_col * gemSize) + off_setX, (highlighted_row * gemSize) + off_setY);
                            sprites[highlighted_row - 1][highlighted_col].setPosition((highlighted_col * gemSize) + off_setX, ((highlighted_row - 1) * gemSize) + off_setY);
                            score = score + score_3_matches;
                            scoreText.setString("Score: " + std::to_string(score));
                        }

                        else if (sprites[highlighted_row][highlighted_col].getTexture() == sprites[highlighted_row - 1][highlighted_col + 1].getTexture() &&
                            sprites[highlighted_row][highlighted_col].getTexture() == sprites[highlighted_row - 1][highlighted_col + 2].getTexture())
                        {
                            Sprite temp = sprites[highlighted_row][highlighted_col];
                            sprites[highlighted_row][highlighted_col] = sprites[highlighted_row - 1][highlighted_col];
                            sprites[highlighted_row - 1][highlighted_col] = temp;
                            // Update positions after swapping
                            sprites[highlighted_row][highlighted_col].setPosition((highlighted_col * gemSize) + off_setX, (highlighted_row * gemSize) + off_setY);
                            sprites[highlighted_row - 1][highlighted_col].setPosition((highlighted_col * gemSize) + off_setX, ((highlighted_row - 1) * gemSize) + off_setY);
                            score = score + score_3_matches;
                            scoreText.setString("Score: " + std::to_string(score));
                        }
                        //THREE MATCHES IN COLUMN
                        else if (sprites[highlighted_row][highlighted_col].getTexture() == sprites[highlighted_row - 2][highlighted_col].getTexture() &&
                            sprites[highlighted_row][highlighted_col].getTexture() == sprites[highlighted_row - 3][highlighted_col].getTexture())
                        {
                            Sprite temp = sprites[highlighted_row][highlighted_col];
                            sprites[highlighted_row][highlighted_col] = sprites[highlighted_row - 1][highlighted_col];
                            sprites[highlighted_row - 1][highlighted_col] = temp;
                            // Update positions after swapping
                            sprites[highlighted_row][highlighted_col].setPosition((highlighted_col * gemSize) + off_setX, (highlighted_row * gemSize) + off_setY);
                            sprites[highlighted_row - 1][highlighted_col].setPosition((highlighted_col * gemSize) + off_setX, ((highlighted_row - 1) * gemSize) + off_setY);
                            score = score + score_3_matches;
                            scoreText.setString("Score: " + std::to_string(score));
                        }
                       // SPECIAL FOUR SWAPPING WHEN THREE MATCHES ARE FOUND
                        else if (sprites[highlighted_row][highlighted_col].getTexture() == &images[0] &&
                            sprites[highlighted_row - 1][highlighted_col - 1].getTexture() == &images[0] &&
                            sprites[highlighted_row - 1][highlighted_col - 2].getTexture() == &images[7] ||
                            sprites[highlighted_row][highlighted_col].getTexture() == &images[1] &&
                            sprites[highlighted_row - 1][highlighted_col - 1].getTexture() == &images[1] &&
                            sprites[highlighted_row - 1][highlighted_col - 2].getTexture() == &images[8] ||
                            sprites[highlighted_row][highlighted_col].getTexture() == &images[2] &&
                            sprites[highlighted_row - 1][highlighted_col - 1].getTexture() == &images[2] &&
                            sprites[highlighted_row - 1][highlighted_col - 2].getTexture() == &images[9] ||
                            sprites[highlighted_row][highlighted_col].getTexture() == &images[3] &&
                            sprites[highlighted_row - 1][highlighted_col - 1].getTexture() == &images[3] &&
                            sprites[highlighted_row - 1][highlighted_col - 2].getTexture() == &images[10] ||
                            sprites[highlighted_row][highlighted_col].getTexture() == &images[4] &&
                            sprites[highlighted_row - 1][highlighted_col - 1].getTexture() == &images[4] &&
                            sprites[highlighted_row - 1][highlighted_col - 2].getTexture() == &images[11] ||
                            sprites[highlighted_row][highlighted_col].getTexture() == &images[5] &&
                            sprites[highlighted_row - 1][highlighted_col - 1].getTexture() == &images[5] &&
                            sprites[highlighted_row - 1][highlighted_col - 2].getTexture() == &images[12] ||
                            sprites[highlighted_row][highlighted_col].getTexture() == &images[6] &&
                            sprites[highlighted_row - 1][highlighted_col - 1].getTexture() == &images[6] &&
                            sprites[highlighted_row - 1][highlighted_col - 2].getTexture() == &images[13])
                        {
                            Sprite temp = sprites[highlighted_row][highlighted_col];
                            sprites[highlighted_row][highlighted_col] = sprites[highlighted_row - 1][highlighted_col];
                            sprites[highlighted_row - 1][highlighted_col] = temp;
                            // Update positions after swapping
                            sprites[highlighted_row][highlighted_col].setPosition((highlighted_col * gemSize) + off_setX, (highlighted_row * gemSize) + off_setY);
                            sprites[highlighted_row - 1][highlighted_col].setPosition((highlighted_col * gemSize) + off_setX, ((highlighted_row - 1) * gemSize) + off_setY);
                            score = score + score_4_special;
                            scoreText.setString("Score: " + std::to_string(score));
                            specialFourUp1 = true;
                        }

                        else if (sprites[highlighted_row][highlighted_col].getTexture() == &images[0] &&
                            sprites[highlighted_row - 1][highlighted_col - 1].getTexture() == &images[7] &&
                            sprites[highlighted_row - 1][highlighted_col - 2].getTexture() == &images[0] ||
                            sprites[highlighted_row][highlighted_col].getTexture() == &images[1] &&
                            sprites[highlighted_row - 1][highlighted_col - 1].getTexture() == &images[8] &&
                            sprites[highlighted_row - 1][highlighted_col - 2].getTexture() == &images[1] ||
                            sprites[highlighted_row][highlighted_col].getTexture() == &images[2] &&
                            sprites[highlighted_row - 1][highlighted_col - 1].getTexture() == &images[9] &&
                            sprites[highlighted_row - 1][highlighted_col - 2].getTexture() == &images[2] ||
                            sprites[highlighted_row][highlighted_col].getTexture() == &images[3] &&
                            sprites[highlighted_row - 1][highlighted_col - 1].getTexture() == &images[10] &&
                            sprites[highlighted_row - 1][highlighted_col - 2].getTexture() == &images[3] ||
                            sprites[highlighted_row][highlighted_col].getTexture() == &images[4] &&
                            sprites[highlighted_row - 1][highlighted_col - 1].getTexture() == &images[11] &&
                            sprites[highlighted_row - 1][highlighted_col - 2].getTexture() == &images[4] ||
                            sprites[highlighted_row][highlighted_col].getTexture() == &images[5] &&
                            sprites[highlighted_row - 1][highlighted_col - 1].getTexture() == &images[12] &&
                            sprites[highlighted_row - 1][highlighted_col - 2].getTexture() == &images[5] ||
                            sprites[highlighted_row][highlighted_col].getTexture() == &images[6] &&
                            sprites[highlighted_row - 1][highlighted_col - 1].getTexture() == &images[13] &&
                            sprites[highlighted_row - 1][highlighted_col - 2].getTexture() == &images[6])
                        {
                            Sprite temp = sprites[highlighted_row][highlighted_col];
                            sprites[highlighted_row][highlighted_col] = sprites[highlighted_row - 1][highlighted_col];
                            sprites[highlighted_row - 1][highlighted_col] = temp;
                            // Update positions after swapping
                            sprites[highlighted_row][highlighted_col].setPosition((highlighted_col * gemSize) + off_setX, (highlighted_row * gemSize) + off_setY);
                            sprites[highlighted_row - 1][highlighted_col].setPosition((highlighted_col * gemSize) + off_setX, ((highlighted_row - 1) * gemSize) + off_setY);
                            score = score + score_4_special;
                            scoreText.setString("Score: " + std::to_string(score));
                            specialFourUp2 = true;
                        }

                        else if (sprites[highlighted_row][highlighted_col].getTexture() == &images[0] &&
                            sprites[highlighted_row - 1][highlighted_col + 1].getTexture() == &images[0] &&
                            sprites[highlighted_row - 1][highlighted_col + 2].getTexture() == &images[7] ||
                            sprites[highlighted_row][highlighted_col].getTexture() == &images[1] &&
                            sprites[highlighted_row - 1][highlighted_col + 1].getTexture() == &images[1] &&
                            sprites[highlighted_row - 1][highlighted_col + 2].getTexture() == &images[8] ||
                            sprites[highlighted_row][highlighted_col].getTexture() == &images[2] &&
                            sprites[highlighted_row - 1][highlighted_col + 1].getTexture() == &images[2] &&
                            sprites[highlighted_row - 1][highlighted_col + 2].getTexture() == &images[9] ||
                            sprites[highlighted_row][highlighted_col].getTexture() == &images[3] &&
                            sprites[highlighted_row - 1][highlighted_col + 1].getTexture() == &images[3] &&
                            sprites[highlighted_row - 1][highlighted_col + 2].getTexture() == &images[10] ||
                            sprites[highlighted_row][highlighted_col].getTexture() == &images[4] &&
                            sprites[highlighted_row - 1][highlighted_col + 1].getTexture() == &images[4] &&
                            sprites[highlighted_row - 1][highlighted_col + 2].getTexture() == &images[11] ||
                            sprites[highlighted_row][highlighted_col].getTexture() == &images[5] &&
                            sprites[highlighted_row - 1][highlighted_col + 1].getTexture() == &images[5] &&
                            sprites[highlighted_row - 1][highlighted_col + 2].getTexture() == &images[12] ||
                            sprites[highlighted_row][highlighted_col].getTexture() == &images[6] &&
                            sprites[highlighted_row - 1][highlighted_col + 1].getTexture() == &images[6] &&
                            sprites[highlighted_row - 1][highlighted_col + 2].getTexture() == &images[13])
                        {
                            Sprite temp = sprites[highlighted_row][highlighted_col];
                            sprites[highlighted_row][highlighted_col] = sprites[highlighted_row - 1][highlighted_col];
                            sprites[highlighted_row - 1][highlighted_col] = temp;
                            // Update positions after swapping
                            sprites[highlighted_row][highlighted_col].setPosition((highlighted_col * gemSize) + off_setX, (highlighted_row * gemSize) + off_setY);
                            sprites[highlighted_row - 1][highlighted_col].setPosition((highlighted_col * gemSize) + off_setX, ((highlighted_row - 1) * gemSize) + off_setY);
                            score = score + score_4_special;
                            scoreText.setString("Score: " + std::to_string(score));
                            specialFourUp3 = true;
                        }

                        else if (sprites[highlighted_row][highlighted_col].getTexture() == &images[0] &&
                            sprites[highlighted_row - 1][highlighted_col + 1].getTexture() == &images[7] &&
                            sprites[highlighted_row - 1][highlighted_col + 2].getTexture() == &images[0] ||
                            sprites[highlighted_row][highlighted_col].getTexture() == &images[1] &&
                            sprites[highlighted_row - 1][highlighted_col + 1].getTexture() == &images[8] &&
                            sprites[highlighted_row - 1][highlighted_col + 2].getTexture() == &images[1] ||
                            sprites[highlighted_row][highlighted_col].getTexture() == &images[2] &&
                            sprites[highlighted_row - 1][highlighted_col + 1].getTexture() == &images[9] &&
                            sprites[highlighted_row - 1][highlighted_col + 2].getTexture() == &images[2] ||
                            sprites[highlighted_row][highlighted_col].getTexture() == &images[3] &&
                            sprites[highlighted_row - 1][highlighted_col + 1].getTexture() == &images[10] &&
                            sprites[highlighted_row - 1][highlighted_col + 2].getTexture() == &images[3] ||
                            sprites[highlighted_row][highlighted_col].getTexture() == &images[4] &&
                            sprites[highlighted_row - 1][highlighted_col + 1].getTexture() == &images[11] &&
                            sprites[highlighted_row - 1][highlighted_col + 2].getTexture() == &images[4] ||
                            sprites[highlighted_row][highlighted_col].getTexture() == &images[5] &&
                            sprites[highlighted_row - 1][highlighted_col + 1].getTexture() == &images[12] &&
                            sprites[highlighted_row - 1][highlighted_col + 2].getTexture() == &images[5] ||
                            sprites[highlighted_row][highlighted_col].getTexture() == &images[6] &&
                            sprites[highlighted_row - 1][highlighted_col + 1].getTexture() == &images[13] &&
                            sprites[highlighted_row - 1][highlighted_col + 2].getTexture() == &images[6])
                        {
                            Sprite temp = sprites[highlighted_row][highlighted_col];
                            sprites[highlighted_row][highlighted_col] = sprites[highlighted_row - 1][highlighted_col];
                            sprites[highlighted_row - 1][highlighted_col] = temp;
                            // Update positions after swapping
                            sprites[highlighted_row][highlighted_col].setPosition((highlighted_col * gemSize) + off_setX, (highlighted_row * gemSize) + off_setY);
                            sprites[highlighted_row - 1][highlighted_col].setPosition((highlighted_col * gemSize) + off_setX, ((highlighted_row - 1) * gemSize) + off_setY);
                            score = score + score_4_special;
                            scoreText.setString("Score: " + std::to_string(score));
                            specialFourUp4 = true;
                        }

                        else if (sprites[highlighted_row][highlighted_col].getTexture() == &images[0] &&
                            sprites[highlighted_row - 1][highlighted_col + 1].getTexture() == &images[7] &&
                            sprites[highlighted_row - 1][highlighted_col - 1].getTexture() == &images[0] ||
                            sprites[highlighted_row][highlighted_col].getTexture() == &images[1] &&
                            sprites[highlighted_row - 1][highlighted_col + 1].getTexture() == &images[8] &&
                            sprites[highlighted_row - 1][highlighted_col - 1].getTexture() == &images[1] ||
                            sprites[highlighted_row][highlighted_col].getTexture() == &images[2] &&
                            sprites[highlighted_row - 1][highlighted_col + 1].getTexture() == &images[9] &&
                            sprites[highlighted_row - 1][highlighted_col - 1].getTexture() == &images[2] ||
                            sprites[highlighted_row][highlighted_col].getTexture() == &images[3] &&
                            sprites[highlighted_row - 1][highlighted_col + 1].getTexture() == &images[10] &&
                            sprites[highlighted_row - 1][highlighted_col - 1].getTexture() == &images[3] ||
                            sprites[highlighted_row][highlighted_col].getTexture() == &images[4] &&
                            sprites[highlighted_row - 1][highlighted_col + 1].getTexture() == &images[11] &&
                            sprites[highlighted_row - 1][highlighted_col - 1].getTexture() == &images[4] ||
                            sprites[highlighted_row][highlighted_col].getTexture() == &images[5] &&
                            sprites[highlighted_row - 1][highlighted_col + 1].getTexture() == &images[12] &&
                            sprites[highlighted_row - 1][highlighted_col - 1].getTexture() == &images[5] ||
                            sprites[highlighted_row][highlighted_col].getTexture() == &images[6] &&
                            sprites[highlighted_row - 1][highlighted_col + 1].getTexture() == &images[13] &&
                            sprites[highlighted_row - 1][highlighted_col - 1].getTexture() == &images[6])
                        {
                            Sprite temp = sprites[highlighted_row][highlighted_col];
                            sprites[highlighted_row][highlighted_col] = sprites[highlighted_row - 1][highlighted_col];
                            sprites[highlighted_row - 1][highlighted_col] = temp;
                            // Update positions after swapping
                            sprites[highlighted_row][highlighted_col].setPosition((highlighted_col * gemSize) + off_setX, (highlighted_row * gemSize) + off_setY);
                            sprites[highlighted_row - 1][highlighted_col].setPosition((highlighted_col * gemSize) + off_setX, ((highlighted_row - 1) * gemSize) + off_setY);
                            score = score + score_4_special;
                            scoreText.setString("Score: " + std::to_string(score));
                            specialFourUp5 = true;
                        }

                        else if (sprites[highlighted_row][highlighted_col].getTexture() == &images[0] &&
                            sprites[highlighted_row - 1][highlighted_col + 1].getTexture() == &images[0] &&
                            sprites[highlighted_row - 1][highlighted_col - 1].getTexture() == &images[7] ||
                            sprites[highlighted_row][highlighted_col].getTexture() == &images[1] &&
                            sprites[highlighted_row - 1][highlighted_col + 1].getTexture() == &images[1] &&
                            sprites[highlighted_row - 1][highlighted_col - 1].getTexture() == &images[8] ||
                            sprites[highlighted_row][highlighted_col].getTexture() == &images[2] &&
                            sprites[highlighted_row - 1][highlighted_col + 1].getTexture() == &images[2] &&
                            sprites[highlighted_row - 1][highlighted_col - 1].getTexture() == &images[9] ||
                            sprites[highlighted_row][highlighted_col].getTexture() == &images[3] &&
                            sprites[highlighted_row - 1][highlighted_col + 1].getTexture() == &images[3] &&
                            sprites[highlighted_row - 1][highlighted_col - 1].getTexture() == &images[10] ||
                            sprites[highlighted_row][highlighted_col].getTexture() == &images[4] &&
                            sprites[highlighted_row - 1][highlighted_col + 1].getTexture() == &images[4] &&
                            sprites[highlighted_row - 1][highlighted_col - 1].getTexture() == &images[11] ||
                            sprites[highlighted_row][highlighted_col].getTexture() == &images[5] &&
                            sprites[highlighted_row - 1][highlighted_col + 1].getTexture() == &images[5] &&
                            sprites[highlighted_row - 1][highlighted_col - 1].getTexture() == &images[12] ||
                            sprites[highlighted_row][highlighted_col].getTexture() == &images[6] &&
                            sprites[highlighted_row - 1][highlighted_col + 1].getTexture() == &images[6] &&
                            sprites[highlighted_row - 1][highlighted_col - 1].getTexture() == &images[13])
                        {
                            Sprite temp = sprites[highlighted_row][highlighted_col];
                            sprites[highlighted_row][highlighted_col] = sprites[highlighted_row - 1][highlighted_col];
                            sprites[highlighted_row - 1][highlighted_col] = temp;
                            // Update positions after swapping
                            sprites[highlighted_row][highlighted_col].setPosition((highlighted_col * gemSize) + off_setX, (highlighted_row * gemSize) + off_setY);
                            sprites[highlighted_row - 1][highlighted_col].setPosition((highlighted_col * gemSize) + off_setX, ((highlighted_row - 1) * gemSize) + off_setY);
                            score = score + score_4_special;
                            scoreText.setString("Score: " + std::to_string(score));
                            specialFourUp6 = true;
                        }


                        else if (sprites[highlighted_row][highlighted_col].getTexture() == &images[7] &&
                            sprites[highlighted_row - 1][highlighted_col + 1].getTexture() == &images[0] &&
                            sprites[highlighted_row - 1][highlighted_col + 2].getTexture() == &images[0] ||
                            sprites[highlighted_row][highlighted_col].getTexture() == &images[8] &&
                            sprites[highlighted_row - 1][highlighted_col + 1].getTexture() == &images[1] &&
                            sprites[highlighted_row - 1][highlighted_col + 2].getTexture() == &images[1] ||
                            sprites[highlighted_row][highlighted_col].getTexture() == &images[9] &&
                            sprites[highlighted_row - 1][highlighted_col + 1].getTexture() == &images[2] &&
                            sprites[highlighted_row - 1][highlighted_col + 2].getTexture() == &images[2] ||
                            sprites[highlighted_row][highlighted_col].getTexture() == &images[10] &&
                            sprites[highlighted_row - 1][highlighted_col + 1].getTexture() == &images[3] &&
                            sprites[highlighted_row - 1][highlighted_col + 2].getTexture() == &images[3] ||
                            sprites[highlighted_row][highlighted_col].getTexture() == &images[11] &&
                            sprites[highlighted_row - 1][highlighted_col + 1].getTexture() == &images[4] &&
                            sprites[highlighted_row - 1][highlighted_col + 2].getTexture() == &images[4] ||
                            sprites[highlighted_row][highlighted_col].getTexture() == &images[12] &&
                            sprites[highlighted_row - 1][highlighted_col + 1].getTexture() == &images[5] &&
                            sprites[highlighted_row - 1][highlighted_col + 2].getTexture() == &images[5] ||
                            sprites[highlighted_row][highlighted_col].getTexture() == &images[13] &&
                            sprites[highlighted_row - 1][highlighted_col + 1].getTexture() == &images[6] &&
                            sprites[highlighted_row - 1][highlighted_col + 2].getTexture() == &images[6])
                        {
                            Sprite temp = sprites[highlighted_row][highlighted_col];
                            sprites[highlighted_row][highlighted_col] = sprites[highlighted_row - 1][highlighted_col];
                            sprites[highlighted_row - 1][highlighted_col] = temp;
                            // Update positions after swapping
                            sprites[highlighted_row][highlighted_col].setPosition((highlighted_col * gemSize) + off_setX, (highlighted_row * gemSize) + off_setY);
                            sprites[highlighted_row - 1][highlighted_col].setPosition((highlighted_col * gemSize) + off_setX, ((highlighted_row - 1) * gemSize) + off_setY);
                            score = score + score_4_special;
                            scoreText.setString("Score: " + std::to_string(score));
                            specialRealFourUp = true;
                        }

                        else if (sprites[highlighted_row][highlighted_col].getTexture() == &images[7] &&
                            sprites[highlighted_row - 1][highlighted_col - 1].getTexture() == &images[0] &&
                            sprites[highlighted_row - 1][highlighted_col - 2].getTexture() == &images[0] ||
                            sprites[highlighted_row][highlighted_col].getTexture() == &images[8] &&
                            sprites[highlighted_row - 1][highlighted_col - 1].getTexture() == &images[1] &&
                            sprites[highlighted_row - 1][highlighted_col - 2].getTexture() == &images[1] ||
                            sprites[highlighted_row][highlighted_col].getTexture() == &images[9] &&
                            sprites[highlighted_row - 1][highlighted_col - 1].getTexture() == &images[2] &&
                            sprites[highlighted_row - 1][highlighted_col - 2].getTexture() == &images[2] ||
                            sprites[highlighted_row][highlighted_col].getTexture() == &images[10] &&
                            sprites[highlighted_row - 1][highlighted_col - 1].getTexture() == &images[3] &&
                            sprites[highlighted_row - 1][highlighted_col - 2].getTexture() == &images[3] ||
                            sprites[highlighted_row][highlighted_col].getTexture() == &images[11] &&
                            sprites[highlighted_row - 1][highlighted_col - 1].getTexture() == &images[4] &&
                            sprites[highlighted_row - 1][highlighted_col - 2].getTexture() == &images[4] ||
                            sprites[highlighted_row][highlighted_col].getTexture() == &images[12] &&
                            sprites[highlighted_row - 1][highlighted_col - 1].getTexture() == &images[5] &&
                            sprites[highlighted_row - 1][highlighted_col - 2].getTexture() == &images[5] ||
                            sprites[highlighted_row][highlighted_col].getTexture() == &images[13] &&
                            sprites[highlighted_row - 1][highlighted_col - 1].getTexture() == &images[6] &&
                            sprites[highlighted_row - 1][highlighted_col - 2].getTexture() == &images[6])
                        {
                            Sprite temp = sprites[highlighted_row][highlighted_col];
                            sprites[highlighted_row][highlighted_col] = sprites[highlighted_row - 1][highlighted_col];
                            sprites[highlighted_row - 1][highlighted_col] = temp;
                            // Update positions after swapping
                            sprites[highlighted_row][highlighted_col].setPosition((highlighted_col * gemSize) + off_setX, (highlighted_row * gemSize) + off_setY);
                            sprites[highlighted_row - 1][highlighted_col].setPosition((highlighted_col * gemSize) + off_setX, ((highlighted_row - 1) * gemSize) + off_setY);
                            score = score + score_4_special;
                            scoreText.setString("Score: " + std::to_string(score));
                            specialRealFourUp = true;
                        }

                        else if (sprites[highlighted_row][highlighted_col].getTexture() == &images[7] &&
                            sprites[highlighted_row - 1][highlighted_col - 1].getTexture() == &images[0] &&
                            sprites[highlighted_row - 1][highlighted_col + 1].getTexture() == &images[0] ||
                            sprites[highlighted_row][highlighted_col].getTexture() == &images[8] &&
                            sprites[highlighted_row - 1][highlighted_col - 1].getTexture() == &images[1] &&
                            sprites[highlighted_row - 1][highlighted_col + 1].getTexture() == &images[1] ||
                            sprites[highlighted_row][highlighted_col].getTexture() == &images[9] &&
                            sprites[highlighted_row - 1][highlighted_col - 1].getTexture() == &images[2] &&
                            sprites[highlighted_row - 1][highlighted_col + 1].getTexture() == &images[2] ||
                            sprites[highlighted_row][highlighted_col].getTexture() == &images[10] &&
                            sprites[highlighted_row - 1][highlighted_col - 1].getTexture() == &images[3] &&
                            sprites[highlighted_row - 1][highlighted_col + 1].getTexture() == &images[3] ||
                            sprites[highlighted_row][highlighted_col].getTexture() == &images[11] &&
                            sprites[highlighted_row - 1][highlighted_col - 1].getTexture() == &images[4] &&
                            sprites[highlighted_row - 1][highlighted_col + 1].getTexture() == &images[4] ||
                            sprites[highlighted_row][highlighted_col].getTexture() == &images[12] &&
                            sprites[highlighted_row - 1][highlighted_col - 1].getTexture() == &images[5] &&
                            sprites[highlighted_row - 1][highlighted_col + 1].getTexture() == &images[5] ||
                            sprites[highlighted_row][highlighted_col].getTexture() == &images[13] &&
                            sprites[highlighted_row - 1][highlighted_col - 1].getTexture() == &images[6] &&
                            sprites[highlighted_row - 1][highlighted_col + 1].getTexture() == &images[6])
                        {
                            Sprite temp = sprites[highlighted_row][highlighted_col];
                            sprites[highlighted_row][highlighted_col] = sprites[highlighted_row - 1][highlighted_col];
                            sprites[highlighted_row - 1][highlighted_col] = temp;
                            // Update positions after swapping
                            sprites[highlighted_row][highlighted_col].setPosition((highlighted_col * gemSize) + off_setX, (highlighted_row * gemSize) + off_setY);
                            sprites[highlighted_row - 1][highlighted_col].setPosition((highlighted_col * gemSize) + off_setX, ((highlighted_row - 1) * gemSize) + off_setY);
                            score = score + score_4_special;
                            scoreText.setString("Score: " + std::to_string(score));
                            specialRealFourUp = true;
                        }
                        //IN COLUMN
                        else if (sprites[highlighted_row][highlighted_col].getTexture() == &images[7] &&
                            sprites[highlighted_row - 2][highlighted_col].getTexture() == &images[0] &&
                            sprites[highlighted_row - 3][highlighted_col].getTexture() == &images[0] ||
                            sprites[highlighted_row][highlighted_col].getTexture() == &images[8] &&
                            sprites[highlighted_row - 2][highlighted_col].getTexture() == &images[1] &&
                            sprites[highlighted_row - 3][highlighted_col].getTexture() == &images[1] ||
                            sprites[highlighted_row][highlighted_col].getTexture() == &images[9] &&
                            sprites[highlighted_row - 2][highlighted_col].getTexture() == &images[2] &&
                            sprites[highlighted_row - 3][highlighted_col].getTexture() == &images[2] ||
                            sprites[highlighted_row][highlighted_col].getTexture() == &images[10] &&
                            sprites[highlighted_row - 2][highlighted_col].getTexture() == &images[3] &&
                            sprites[highlighted_row - 3][highlighted_col].getTexture() == &images[3] ||
                            sprites[highlighted_row][highlighted_col].getTexture() == &images[11] &&
                            sprites[highlighted_row - 2][highlighted_col].getTexture() == &images[4] &&
                            sprites[highlighted_row - 3][highlighted_col].getTexture() == &images[4] ||
                            sprites[highlighted_row][highlighted_col].getTexture() == &images[12] &&
                            sprites[highlighted_row - 2][highlighted_col].getTexture() == &images[5] &&
                            sprites[highlighted_row - 3][highlighted_col].getTexture() == &images[5] ||
                            sprites[highlighted_row][highlighted_col].getTexture() == &images[13] &&
                            sprites[highlighted_row - 2][highlighted_col].getTexture() == &images[6] &&
                            sprites[highlighted_row - 3][highlighted_col].getTexture() == &images[6])
                        {
                            Sprite temp = sprites[highlighted_row][highlighted_col];
                            sprites[highlighted_row][highlighted_col] = sprites[highlighted_row - 1][highlighted_col];
                            sprites[highlighted_row - 1][highlighted_col] = temp;
                            // Update positions after swapping
                            sprites[highlighted_row][highlighted_col].setPosition((highlighted_col * gemSize) + off_setX, (highlighted_row * gemSize) + off_setY);
                            sprites[highlighted_row - 1][highlighted_col].setPosition((highlighted_col * gemSize) + off_setX, ((highlighted_row - 1) * gemSize) + off_setY);
                            score = score + score_4_special;
                            scoreText.setString("Score: " + std::to_string(score));
                            specialRealFourUp = true;
                        }
                        //FOR FIVE GEMS
                        else if (sprites[highlighted_row][highlighted_col].getTexture() == &images[0] &&
                            sprites[highlighted_row - 1][highlighted_col - 1].getTexture() == &images[0] &&
                            sprites[highlighted_row - 1][highlighted_col - 2].getTexture() == &images[14] ||
                            sprites[highlighted_row][highlighted_col].getTexture() == &images[1] &&
                            sprites[highlighted_row - 1][highlighted_col - 1].getTexture() == &images[1] &&
                            sprites[highlighted_row - 1][highlighted_col - 2].getTexture() == &images[15] ||
                            sprites[highlighted_row][highlighted_col].getTexture() == &images[2] &&
                            sprites[highlighted_row - 1][highlighted_col - 1].getTexture() == &images[2] &&
                            sprites[highlighted_row - 1][highlighted_col - 2].getTexture() == &images[16] ||
                            sprites[highlighted_row][highlighted_col].getTexture() == &images[3] &&
                            sprites[highlighted_row - 1][highlighted_col - 1].getTexture() == &images[3] &&
                            sprites[highlighted_row - 1][highlighted_col - 2].getTexture() == &images[17] ||
                            sprites[highlighted_row][highlighted_col].getTexture() == &images[4] &&
                            sprites[highlighted_row - 1][highlighted_col - 1].getTexture() == &images[4] &&
                            sprites[highlighted_row - 1][highlighted_col - 2].getTexture() == &images[18] ||
                            sprites[highlighted_row][highlighted_col].getTexture() == &images[5] &&
                            sprites[highlighted_row - 1][highlighted_col - 1].getTexture() == &images[5] &&
                            sprites[highlighted_row - 1][highlighted_col - 2].getTexture() == &images[19] ||
                            sprites[highlighted_row][highlighted_col].getTexture() == &images[6] &&
                            sprites[highlighted_row - 1][highlighted_col - 1].getTexture() == &images[6] &&
                            sprites[highlighted_row - 1][highlighted_col - 2].getTexture() == &images[20])
                        {
                            specialRow = highlighted_row - 1;
                            specialCol = highlighted_col - 2;
                            Sprite temp = sprites[highlighted_row][highlighted_col];
                            sprites[highlighted_row][highlighted_col] = sprites[highlighted_row - 1][highlighted_col];
                            sprites[highlighted_row - 1][highlighted_col] = temp;
                            // Update positions after swapping
                            sprites[highlighted_row][highlighted_col].setPosition((highlighted_col * gemSize) + off_setX, (highlighted_row * gemSize) + off_setY);
                            sprites[highlighted_row - 1][highlighted_col].setPosition((highlighted_col * gemSize) + off_setX, ((highlighted_row - 1) * gemSize) + off_setY);
                            score = score + score_5_special;
                            scoreText.setString("Score: " + std::to_string(score));
                            specialFive = true;
                        }

                        else if (sprites[highlighted_row][highlighted_col].getTexture() == &images[0] &&
                            sprites[highlighted_row - 1][highlighted_col - 1].getTexture() == &images[14] &&
                            sprites[highlighted_row - 1][highlighted_col - 2].getTexture() == &images[0] ||
                            sprites[highlighted_row][highlighted_col].getTexture() == &images[1] &&
                            sprites[highlighted_row - 1][highlighted_col - 1].getTexture() == &images[15] &&
                            sprites[highlighted_row - 1][highlighted_col - 2].getTexture() == &images[1] ||
                            sprites[highlighted_row][highlighted_col].getTexture() == &images[2] &&
                            sprites[highlighted_row - 1][highlighted_col - 1].getTexture() == &images[16] &&
                            sprites[highlighted_row - 1][highlighted_col - 2].getTexture() == &images[2] ||
                            sprites[highlighted_row][highlighted_col].getTexture() == &images[3] &&
                            sprites[highlighted_row - 1][highlighted_col - 1].getTexture() == &images[17] &&
                            sprites[highlighted_row - 1][highlighted_col - 2].getTexture() == &images[3] ||
                            sprites[highlighted_row][highlighted_col].getTexture() == &images[4] &&
                            sprites[highlighted_row - 1][highlighted_col - 1].getTexture() == &images[18] &&
                            sprites[highlighted_row - 1][highlighted_col - 2].getTexture() == &images[4] ||
                            sprites[highlighted_row][highlighted_col].getTexture() == &images[5] &&
                            sprites[highlighted_row - 1][highlighted_col - 1].getTexture() == &images[19] &&
                            sprites[highlighted_row - 1][highlighted_col - 2].getTexture() == &images[5] ||
                            sprites[highlighted_row][highlighted_col].getTexture() == &images[6] &&
                            sprites[highlighted_row - 1][highlighted_col - 1].getTexture() == &images[20] &&
                            sprites[highlighted_row - 1][highlighted_col - 2].getTexture() == &images[6])
                        {
                            specialRow = highlighted_row - 1;
                            specialCol = highlighted_col - 1;


                            Sprite temp = sprites[highlighted_row][highlighted_col];
                            sprites[highlighted_row][highlighted_col] = sprites[highlighted_row - 1][highlighted_col];
                            sprites[highlighted_row - 1][highlighted_col] = temp;
                            // Update positions after swapping
                            sprites[highlighted_row][highlighted_col].setPosition((highlighted_col * gemSize) + off_setX, (highlighted_row * gemSize) + off_setY);
                            sprites[highlighted_row - 1][highlighted_col].setPosition((highlighted_col * gemSize) + off_setX, ((highlighted_row - 1) * gemSize) + off_setY);
                            score = score + score_5_special;
                            scoreText.setString("Score: " + std::to_string(score));
                            specialFive = true;
                        }

                        else if (sprites[highlighted_row][highlighted_col].getTexture() == &images[0] &&
                            sprites[highlighted_row - 1][highlighted_col + 1].getTexture() == &images[0] &&
                            sprites[highlighted_row - 1][highlighted_col + 2].getTexture() == &images[14] ||
                            sprites[highlighted_row][highlighted_col].getTexture() == &images[1] &&
                            sprites[highlighted_row - 1][highlighted_col + 1].getTexture() == &images[1] &&
                            sprites[highlighted_row - 1][highlighted_col + 2].getTexture() == &images[15] ||
                            sprites[highlighted_row][highlighted_col].getTexture() == &images[2] &&
                            sprites[highlighted_row - 1][highlighted_col + 1].getTexture() == &images[2] &&
                            sprites[highlighted_row - 1][highlighted_col + 2].getTexture() == &images[16] ||
                            sprites[highlighted_row][highlighted_col].getTexture() == &images[3] &&
                            sprites[highlighted_row - 1][highlighted_col + 1].getTexture() == &images[3] &&
                            sprites[highlighted_row - 1][highlighted_col + 2].getTexture() == &images[17] ||
                            sprites[highlighted_row][highlighted_col].getTexture() == &images[4] &&
                            sprites[highlighted_row - 1][highlighted_col + 1].getTexture() == &images[4] &&
                            sprites[highlighted_row - 1][highlighted_col + 2].getTexture() == &images[18] ||
                            sprites[highlighted_row][highlighted_col].getTexture() == &images[5] &&
                            sprites[highlighted_row - 1][highlighted_col + 1].getTexture() == &images[5] &&
                            sprites[highlighted_row - 1][highlighted_col + 2].getTexture() == &images[19] ||
                            sprites[highlighted_row][highlighted_col].getTexture() == &images[6] &&
                            sprites[highlighted_row - 1][highlighted_col + 1].getTexture() == &images[6] &&
                            sprites[highlighted_row - 1][highlighted_col + 2].getTexture() == &images[20])
                        {
                            specialRow = highlighted_row - 1;
                            specialCol = highlighted_col + 2;


                            Sprite temp = sprites[highlighted_row][highlighted_col];
                            sprites[highlighted_row][highlighted_col] = sprites[highlighted_row - 1][highlighted_col];
                            sprites[highlighted_row - 1][highlighted_col] = temp;
                            // Update positions after swapping
                            sprites[highlighted_row][highlighted_col].setPosition((highlighted_col * gemSize) + off_setX, (highlighted_row * gemSize) + off_setY);
                            sprites[highlighted_row - 1][highlighted_col].setPosition((highlighted_col * gemSize) + off_setX, ((highlighted_row - 1) * gemSize) + off_setY);
                            score = score + score_5_special;
                            scoreText.setString("Score: " + std::to_string(score));
                            specialFive = true;
                        }

                        else if (sprites[highlighted_row][highlighted_col].getTexture() == &images[0] &&
                            sprites[highlighted_row - 1][highlighted_col + 1].getTexture() == &images[14] &&
                            sprites[highlighted_row - 1][highlighted_col + 2].getTexture() == &images[0] ||
                            sprites[highlighted_row][highlighted_col].getTexture() == &images[1] &&
                            sprites[highlighted_row - 1][highlighted_col + 1].getTexture() == &images[15] &&
                            sprites[highlighted_row - 1][highlighted_col + 2].getTexture() == &images[1] ||
                            sprites[highlighted_row][highlighted_col].getTexture() == &images[2] &&
                            sprites[highlighted_row - 1][highlighted_col + 1].getTexture() == &images[16] &&
                            sprites[highlighted_row - 1][highlighted_col + 2].getTexture() == &images[2] ||
                            sprites[highlighted_row][highlighted_col].getTexture() == &images[3] &&
                            sprites[highlighted_row - 1][highlighted_col + 1].getTexture() == &images[17] &&
                            sprites[highlighted_row - 1][highlighted_col + 2].getTexture() == &images[3] ||
                            sprites[highlighted_row][highlighted_col].getTexture() == &images[4] &&
                            sprites[highlighted_row - 1][highlighted_col + 1].getTexture() == &images[18] &&
                            sprites[highlighted_row - 1][highlighted_col + 2].getTexture() == &images[4] ||
                            sprites[highlighted_row][highlighted_col].getTexture() == &images[5] &&
                            sprites[highlighted_row - 1][highlighted_col + 1].getTexture() == &images[19] &&
                            sprites[highlighted_row - 1][highlighted_col + 2].getTexture() == &images[5] ||
                            sprites[highlighted_row][highlighted_col].getTexture() == &images[6] &&
                            sprites[highlighted_row - 1][highlighted_col + 1].getTexture() == &images[20] &&
                            sprites[highlighted_row - 1][highlighted_col + 2].getTexture() == &images[6])
                        {
                            specialRow = highlighted_row - 1;
                            specialCol = highlighted_col + 1;


                            Sprite temp = sprites[highlighted_row][highlighted_col];
                            sprites[highlighted_row][highlighted_col] = sprites[highlighted_row - 1][highlighted_col];
                            sprites[highlighted_row - 1][highlighted_col] = temp;
                            // Update positions after swapping
                            sprites[highlighted_row][highlighted_col].setPosition((highlighted_col * gemSize) + off_setX, (highlighted_row * gemSize) + off_setY);
                            sprites[highlighted_row - 1][highlighted_col].setPosition((highlighted_col * gemSize) + off_setX, ((highlighted_row - 1) * gemSize) + off_setY);
                            score = score + score_5_special;
                            scoreText.setString("Score: " + std::to_string(score));
                            specialFive = true;
                        }

                        else if (sprites[highlighted_row][highlighted_col].getTexture() == &images[0] &&
                            sprites[highlighted_row - 1][highlighted_col + 1].getTexture() == &images[14] &&
                            sprites[highlighted_row - 1][highlighted_col - 1].getTexture() == &images[0] ||
                            sprites[highlighted_row][highlighted_col].getTexture() == &images[1] &&
                            sprites[highlighted_row - 1][highlighted_col + 1].getTexture() == &images[15] &&
                            sprites[highlighted_row - 1][highlighted_col - 1].getTexture() == &images[1] ||
                            sprites[highlighted_row][highlighted_col].getTexture() == &images[2] &&
                            sprites[highlighted_row - 1][highlighted_col + 1].getTexture() == &images[16] &&
                            sprites[highlighted_row - 1][highlighted_col - 1].getTexture() == &images[2] ||
                            sprites[highlighted_row][highlighted_col].getTexture() == &images[3] &&
                            sprites[highlighted_row - 1][highlighted_col + 1].getTexture() == &images[17] &&
                            sprites[highlighted_row - 1][highlighted_col - 1].getTexture() == &images[3] ||
                            sprites[highlighted_row][highlighted_col].getTexture() == &images[4] &&
                            sprites[highlighted_row - 1][highlighted_col + 1].getTexture() == &images[18] &&
                            sprites[highlighted_row - 1][highlighted_col - 1].getTexture() == &images[4] ||
                            sprites[highlighted_row][highlighted_col].getTexture() == &images[5] &&
                            sprites[highlighted_row - 1][highlighted_col + 1].getTexture() == &images[19] &&
                            sprites[highlighted_row - 1][highlighted_col - 1].getTexture() == &images[5] ||
                            sprites[highlighted_row][highlighted_col].getTexture() == &images[6] &&
                            sprites[highlighted_row - 1][highlighted_col + 1].getTexture() == &images[20] &&
                            sprites[highlighted_row - 1][highlighted_col - 1].getTexture() == &images[6])
                        {
                            specialRow = highlighted_row - 1;
                            specialCol = highlighted_col + 1;



                            Sprite temp = sprites[highlighted_row][highlighted_col];
                            sprites[highlighted_row][highlighted_col] = sprites[highlighted_row - 1][highlighted_col];
                            sprites[highlighted_row - 1][highlighted_col] = temp;
                            // Update positions after swapping
                            sprites[highlighted_row][highlighted_col].setPosition((highlighted_col * gemSize) + off_setX, (highlighted_row * gemSize) + off_setY);
                            sprites[highlighted_row - 1][highlighted_col].setPosition((highlighted_col * gemSize) + off_setX, ((highlighted_row - 1) * gemSize) + off_setY);
                            score = score + score_5_special;
                            scoreText.setString("Score: " + std::to_string(score));
                            specialFive = true;
                        }

                        else if (sprites[highlighted_row][highlighted_col].getTexture() == &images[0] &&
                            sprites[highlighted_row - 1][highlighted_col + 1].getTexture() == &images[0] &&
                            sprites[highlighted_row - 1][highlighted_col - 1].getTexture() == &images[14] ||
                            sprites[highlighted_row][highlighted_col].getTexture() == &images[1] &&
                            sprites[highlighted_row - 1][highlighted_col + 1].getTexture() == &images[1] &&
                            sprites[highlighted_row - 1][highlighted_col - 1].getTexture() == &images[15] ||
                            sprites[highlighted_row][highlighted_col].getTexture() == &images[2] &&
                            sprites[highlighted_row - 1][highlighted_col + 1].getTexture() == &images[2] &&
                            sprites[highlighted_row - 1][highlighted_col - 1].getTexture() == &images[16] ||
                            sprites[highlighted_row][highlighted_col].getTexture() == &images[3] &&
                            sprites[highlighted_row - 1][highlighted_col + 1].getTexture() == &images[3] &&
                            sprites[highlighted_row - 1][highlighted_col - 1].getTexture() == &images[17] ||
                            sprites[highlighted_row][highlighted_col].getTexture() == &images[4] &&
                            sprites[highlighted_row - 1][highlighted_col + 1].getTexture() == &images[4] &&
                            sprites[highlighted_row - 1][highlighted_col - 1].getTexture() == &images[18] ||
                            sprites[highlighted_row][highlighted_col].getTexture() == &images[5] &&
                            sprites[highlighted_row - 1][highlighted_col + 1].getTexture() == &images[5] &&
                            sprites[highlighted_row - 1][highlighted_col - 1].getTexture() == &images[19] ||
                            sprites[highlighted_row][highlighted_col].getTexture() == &images[6] &&
                            sprites[highlighted_row - 1][highlighted_col + 1].getTexture() == &images[6] &&
                            sprites[highlighted_row - 1][highlighted_col - 1].getTexture() == &images[20])
                        {
                            specialRow = highlighted_row - 1;
                            specialCol = highlighted_col;


                            Sprite temp = sprites[highlighted_row][highlighted_col];
                            sprites[highlighted_row][highlighted_col] = sprites[highlighted_row - 1][highlighted_col];
                            sprites[highlighted_row - 1][highlighted_col] = temp;
                            // Update positions after swapping
                            sprites[highlighted_row][highlighted_col].setPosition((highlighted_col * gemSize) + off_setX, (highlighted_row * gemSize) + off_setY);
                            sprites[highlighted_row - 1][highlighted_col].setPosition((highlighted_col * gemSize) + off_setX, ((highlighted_row - 1) * gemSize) + off_setY);
                            score = score + score_5_special;
                            scoreText.setString("Score: " + std::to_string(score));
                            specialFive = true;
                        }


                        else if (sprites[highlighted_row][highlighted_col].getTexture() == &images[14] &&
                            sprites[highlighted_row - 1][highlighted_col + 1].getTexture() == &images[0] &&
                            sprites[highlighted_row - 1][highlighted_col + 2].getTexture() == &images[0] ||
                            sprites[highlighted_row][highlighted_col].getTexture() == &images[15] &&
                            sprites[highlighted_row - 1][highlighted_col + 1].getTexture() == &images[1] &&
                            sprites[highlighted_row - 1][highlighted_col + 2].getTexture() == &images[1] ||
                            sprites[highlighted_row][highlighted_col].getTexture() == &images[16] &&
                            sprites[highlighted_row - 1][highlighted_col + 1].getTexture() == &images[2] &&
                            sprites[highlighted_row - 1][highlighted_col + 2].getTexture() == &images[2] ||
                            sprites[highlighted_row][highlighted_col].getTexture() == &images[17] &&
                            sprites[highlighted_row - 1][highlighted_col + 1].getTexture() == &images[3] &&
                            sprites[highlighted_row - 1][highlighted_col + 2].getTexture() == &images[3] ||
                            sprites[highlighted_row][highlighted_col].getTexture() == &images[18] &&
                            sprites[highlighted_row - 1][highlighted_col + 1].getTexture() == &images[4] &&
                            sprites[highlighted_row - 1][highlighted_col + 2].getTexture() == &images[4] ||
                            sprites[highlighted_row][highlighted_col].getTexture() == &images[19] &&
                            sprites[highlighted_row - 1][highlighted_col + 1].getTexture() == &images[5] &&
                            sprites[highlighted_row - 1][highlighted_col + 2].getTexture() == &images[5] ||
                            sprites[highlighted_row][highlighted_col].getTexture() == &images[20] &&
                            sprites[highlighted_row - 1][highlighted_col + 1].getTexture() == &images[6] &&
                            sprites[highlighted_row - 1][highlighted_col + 2].getTexture() == &images[6])
                        {
                            specialRow = highlighted_row - 1;
                            specialCol = highlighted_col;


                            Sprite temp = sprites[highlighted_row][highlighted_col];
                            sprites[highlighted_row][highlighted_col] = sprites[highlighted_row - 1][highlighted_col];
                            sprites[highlighted_row - 1][highlighted_col] = temp;
                            // Update positions after swapping
                            sprites[highlighted_row][highlighted_col].setPosition((highlighted_col * gemSize) + off_setX, (highlighted_row * gemSize) + off_setY);
                            sprites[highlighted_row - 1][highlighted_col].setPosition((highlighted_col * gemSize) + off_setX, ((highlighted_row - 1) * gemSize) + off_setY);
                            score = score + score_5_special;
                            scoreText.setString("Score: " + std::to_string(score));
                            specialFive = true;
                        }

                        else if (sprites[highlighted_row][highlighted_col].getTexture() == &images[14] &&
                            sprites[highlighted_row - 1][highlighted_col - 1].getTexture() == &images[0] &&
                            sprites[highlighted_row - 1][highlighted_col - 2].getTexture() == &images[0] ||
                            sprites[highlighted_row][highlighted_col].getTexture() == &images[15] &&
                            sprites[highlighted_row - 1][highlighted_col - 1].getTexture() == &images[1] &&
                            sprites[highlighted_row - 1][highlighted_col - 2].getTexture() == &images[1] ||
                            sprites[highlighted_row][highlighted_col].getTexture() == &images[16] &&
                            sprites[highlighted_row - 1][highlighted_col - 1].getTexture() == &images[2] &&
                            sprites[highlighted_row - 1][highlighted_col - 2].getTexture() == &images[2] ||
                            sprites[highlighted_row][highlighted_col].getTexture() == &images[17] &&
                            sprites[highlighted_row - 1][highlighted_col - 1].getTexture() == &images[3] &&
                            sprites[highlighted_row - 1][highlighted_col - 2].getTexture() == &images[3] ||
                            sprites[highlighted_row][highlighted_col].getTexture() == &images[18] &&
                            sprites[highlighted_row - 1][highlighted_col - 1].getTexture() == &images[4] &&
                            sprites[highlighted_row - 1][highlighted_col - 2].getTexture() == &images[4] ||
                            sprites[highlighted_row][highlighted_col].getTexture() == &images[19] &&
                            sprites[highlighted_row - 1][highlighted_col - 1].getTexture() == &images[5] &&
                            sprites[highlighted_row - 1][highlighted_col - 2].getTexture() == &images[5] ||
                            sprites[highlighted_row][highlighted_col].getTexture() == &images[20] &&
                            sprites[highlighted_row - 1][highlighted_col - 1].getTexture() == &images[6] &&
                            sprites[highlighted_row - 1][highlighted_col - 2].getTexture() == &images[6])
                        {
                            specialRow = highlighted_row - 1;
                            specialCol = highlighted_col;



                            Sprite temp = sprites[highlighted_row][highlighted_col];
                            sprites[highlighted_row][highlighted_col] = sprites[highlighted_row - 1][highlighted_col];
                            sprites[highlighted_row - 1][highlighted_col] = temp;
                            // Update positions after swapping
                            sprites[highlighted_row][highlighted_col].setPosition((highlighted_col * gemSize) + off_setX, (highlighted_row * gemSize) + off_setY);
                            sprites[highlighted_row - 1][highlighted_col].setPosition((highlighted_col * gemSize) + off_setX, ((highlighted_row - 1) * gemSize) + off_setY);
                            score = score + score_5_special;
                            scoreText.setString("Score: " + std::to_string(score));
                            specialFive = true;
                        }

                        else if (sprites[highlighted_row][highlighted_col].getTexture() == &images[14] &&
                            sprites[highlighted_row - 1][highlighted_col - 1].getTexture() == &images[0] &&
                            sprites[highlighted_row - 1][highlighted_col + 1].getTexture() == &images[0] ||
                            sprites[highlighted_row][highlighted_col].getTexture() == &images[15] &&
                            sprites[highlighted_row - 1][highlighted_col - 1].getTexture() == &images[1] &&
                            sprites[highlighted_row - 1][highlighted_col + 1].getTexture() == &images[1] ||
                            sprites[highlighted_row][highlighted_col].getTexture() == &images[16] &&
                            sprites[highlighted_row - 1][highlighted_col - 1].getTexture() == &images[2] &&
                            sprites[highlighted_row - 1][highlighted_col + 1].getTexture() == &images[2] ||
                            sprites[highlighted_row][highlighted_col].getTexture() == &images[17] &&
                            sprites[highlighted_row - 1][highlighted_col - 1].getTexture() == &images[3] &&
                            sprites[highlighted_row - 1][highlighted_col + 1].getTexture() == &images[3] ||
                            sprites[highlighted_row][highlighted_col].getTexture() == &images[18] &&
                            sprites[highlighted_row - 1][highlighted_col - 1].getTexture() == &images[4] &&
                            sprites[highlighted_row - 1][highlighted_col + 1].getTexture() == &images[4] ||
                            sprites[highlighted_row][highlighted_col].getTexture() == &images[19] &&
                            sprites[highlighted_row - 1][highlighted_col - 1].getTexture() == &images[5] &&
                            sprites[highlighted_row - 1][highlighted_col + 1].getTexture() == &images[5] ||
                            sprites[highlighted_row][highlighted_col].getTexture() == &images[20] &&
                            sprites[highlighted_row - 1][highlighted_col - 1].getTexture() == &images[6] &&
                            sprites[highlighted_row - 1][highlighted_col + 1].getTexture() == &images[6])
                        {
                            specialRow = highlighted_row - 1;
                            specialCol = highlighted_col;



                            Sprite temp = sprites[highlighted_row][highlighted_col];
                            sprites[highlighted_row][highlighted_col] = sprites[highlighted_row - 1][highlighted_col];
                            sprites[highlighted_row - 1][highlighted_col] = temp;
                            // Update positions after swapping
                            sprites[highlighted_row][highlighted_col].setPosition((highlighted_col * gemSize) + off_setX, (highlighted_row * gemSize) + off_setY);
                            sprites[highlighted_row - 1][highlighted_col].setPosition((highlighted_col * gemSize) + off_setX, ((highlighted_row - 1) * gemSize) + off_setY);
                            score = score + score_5_special;
                            scoreText.setString("Score: " + std::to_string(score));
                            specialFive = true;
                        }

                        else if (sprites[highlighted_row][highlighted_col].getTexture() == &images[14] &&
                            sprites[highlighted_row - 2][highlighted_col].getTexture() == &images[0] &&
                            sprites[highlighted_row - 3][highlighted_col].getTexture() == &images[0] ||
                            sprites[highlighted_row][highlighted_col].getTexture() == &images[15] &&
                            sprites[highlighted_row - 2][highlighted_col].getTexture() == &images[1] &&
                            sprites[highlighted_row - 3][highlighted_col].getTexture() == &images[1] ||
                            sprites[highlighted_row][highlighted_col].getTexture() == &images[16] &&
                            sprites[highlighted_row - 2][highlighted_col].getTexture() == &images[2] &&
                            sprites[highlighted_row - 3][highlighted_col].getTexture() == &images[2] ||
                            sprites[highlighted_row][highlighted_col].getTexture() == &images[17] &&
                            sprites[highlighted_row - 2][highlighted_col].getTexture() == &images[3] &&
                            sprites[highlighted_row - 3][highlighted_col].getTexture() == &images[3] ||
                            sprites[highlighted_row][highlighted_col].getTexture() == &images[18] &&
                            sprites[highlighted_row - 2][highlighted_col].getTexture() == &images[4] &&
                            sprites[highlighted_row - 3][highlighted_col].getTexture() == &images[4] ||
                            sprites[highlighted_row][highlighted_col].getTexture() == &images[19] &&
                            sprites[highlighted_row - 2][highlighted_col].getTexture() == &images[5] &&
                            sprites[highlighted_row - 3][highlighted_col].getTexture() == &images[5] ||
                            sprites[highlighted_row][highlighted_col].getTexture() == &images[20] &&
                            sprites[highlighted_row - 2][highlighted_col].getTexture() == &images[6] &&
                            sprites[highlighted_row - 3][highlighted_col].getTexture() == &images[6])
                        {
                            specialRow = highlighted_row - 1;
                            specialCol = highlighted_col;



                            Sprite temp = sprites[highlighted_row][highlighted_col];
                            sprites[highlighted_row][highlighted_col] = sprites[highlighted_row - 1][highlighted_col];
                            sprites[highlighted_row - 1][highlighted_col] = temp;
                            // Update positions after swapping
                            sprites[highlighted_row][highlighted_col].setPosition((highlighted_col * gemSize) + off_setX, (highlighted_row * gemSize) + off_setY);
                            sprites[highlighted_row - 1][highlighted_col].setPosition((highlighted_col * gemSize) + off_setX, ((highlighted_row - 1) * gemSize) + off_setY);
                            score = score + score_5_special;
                            scoreText.setString("Score: " + std::to_string(score));
                            specialFive = true;
                        }

                    }
                    highlighted_row--;
                    enter_key_pressed = false;
                    swap_triggered = false;
                }

                else if (event.key.code == Keyboard::Down && highlighted_row < 7)
                {
                    if (enter_key_pressed && swap_triggered)
                    {//FOR FIVE MATCHES
                        if (sprites[highlighted_row][highlighted_col].getTexture() == sprites[highlighted_row + 1][highlighted_col - 1].getTexture() &&
                            sprites[highlighted_row][highlighted_col].getTexture() == sprites[highlighted_row + 1][highlighted_col - 2].getTexture() &&
                            sprites[highlighted_row][highlighted_col].getTexture() == sprites[highlighted_row + 1][highlighted_col + 1].getTexture() &&
                            sprites[highlighted_row][highlighted_col].getTexture() == sprites[highlighted_row + 1][highlighted_col + 2].getTexture())
                        {
                            // storing indexes of the above position
                            indexDown1 = highlighted_row + 1;
                            indexDown2 = highlighted_col;

                            // storing the texture to temporary sprite
                            const Texture* texturePtr = sprites[highlighted_row][highlighted_col].getTexture();
                            tempSprites[indexDown1][indexDown2].setTexture(*texturePtr);

                            matchFiveDown = true;
                            score = score + score_5_matches;
                            scoreText.setString("Score: " + std::to_string(score));
                            Sprite temp = sprites[highlighted_row][highlighted_col];
                            sprites[highlighted_row][highlighted_col] = sprites[highlighted_row + 1][highlighted_col];
                            sprites[highlighted_row + 1][highlighted_col] = temp;
                            // Update positions after swapping
                            sprites[highlighted_row][highlighted_col].setPosition((highlighted_col * gemSize) + off_setX, (highlighted_row * gemSize) + off_setY);
                            sprites[highlighted_row + 1][highlighted_col].setPosition((highlighted_col * gemSize) + off_setX, ((highlighted_row + 1) * gemSize) + off_setY);
                        }
                        //FOR FOUR MATCHES
                        else if ((sprites[highlighted_row][highlighted_col].getTexture() == sprites[highlighted_row + 1][highlighted_col - 1].getTexture() &&
                                  sprites[highlighted_row][highlighted_col].getTexture() == sprites[highlighted_row + 1][highlighted_col - 2].getTexture() &&
                                  sprites[highlighted_row][highlighted_col].getTexture() == sprites[highlighted_row + 1][highlighted_col + 1].getTexture()) ||
                                 (sprites[highlighted_row][highlighted_col].getTexture() == sprites[highlighted_row + 1][highlighted_col - 1].getTexture() &&
                                  sprites[highlighted_row][highlighted_col].getTexture() == sprites[highlighted_row + 1][highlighted_col + 1].getTexture() &&
                                  sprites[highlighted_row][highlighted_col].getTexture() == sprites[highlighted_row + 1][highlighted_col + 2].getTexture()))
                        {
                            // storing indexes of the above position
                            indexDown1 = highlighted_row + 1;
                            indexDown2 = highlighted_col;

                            // storing the texture to temporary sprite
                            const Texture* texturePtr = sprites[highlighted_row][highlighted_col].getTexture();
                            tempSprites[indexDown1][indexDown2].setTexture(*texturePtr);

                            matchFourDown = true;
                            score = score + score_4_matches;
                            scoreText.setString("Score: " + std::to_string(score));
                           Sprite temp = sprites[highlighted_row][highlighted_col];
                            sprites[highlighted_row][highlighted_col] = sprites[highlighted_row + 1][highlighted_col];
                            sprites[highlighted_row + 1][highlighted_col] = temp;
                            // Update positions after swapping
                            sprites[highlighted_row][highlighted_col].setPosition((highlighted_col * gemSize) + off_setX, (highlighted_row * gemSize) + off_setY);
                            sprites[highlighted_row + 1][highlighted_col].setPosition((highlighted_col * gemSize) + off_setX, ((highlighted_row + 1) * gemSize) + off_setY);
                        }
                        //FOR ELBOW
                        else if (sprites[highlighted_row][highlighted_col].getTexture() == sprites[highlighted_row + 1][highlighted_col - 1].getTexture() &&
                            sprites[highlighted_row][highlighted_col].getTexture() == sprites[highlighted_row + 1][highlighted_col - 2].getTexture() &&
                            sprites[highlighted_row][highlighted_col].getTexture() == sprites[highlighted_row + 2][highlighted_col].getTexture() &&
                            sprites[highlighted_row][highlighted_col].getTexture() == sprites[highlighted_row + 3][highlighted_col].getTexture() ||
                            sprites[highlighted_row][highlighted_col].getTexture() == sprites[highlighted_row + 1][highlighted_col + 1].getTexture() &&
                            sprites[highlighted_row][highlighted_col].getTexture() == sprites[highlighted_row + 1][highlighted_col + 2].getTexture() &&
                            sprites[highlighted_row][highlighted_col].getTexture() == sprites[highlighted_row + 2][highlighted_col].getTexture() &&
                            sprites[highlighted_row][highlighted_col].getTexture() == sprites[highlighted_row + 3][highlighted_col].getTexture())
                        {
                            // storing indexes of the above position
                            indexDown1 = highlighted_row + 1;
                            indexDown2 = highlighted_col;

                            // storing the texture to temporary sprite
                            const Texture* texturePtr = sprites[highlighted_row][highlighted_col].getTexture();
                            tempSprites[indexDown1][indexDown2].setTexture(*texturePtr);

                            destroyDown = true;
                            score = score + score_5_matches;
                            scoreText.setString("Score: " + std::to_string(score));
                            Sprite temp = sprites[highlighted_row][highlighted_col];
                            sprites[highlighted_row][highlighted_col] = sprites[highlighted_row + 1][highlighted_col];
                            sprites[highlighted_row + 1][highlighted_col] = temp;
                            // Update positions after swapping
                            sprites[highlighted_row][highlighted_col].setPosition((highlighted_col * gemSize) + off_setX, (highlighted_row * gemSize) + off_setY);
                            sprites[highlighted_row + 1][highlighted_col].setPosition((highlighted_col * gemSize) + off_setX, ((highlighted_row + 1) * gemSize) + off_setY);
                        }

                        //FOR THREE MATCHES
                        else if (sprites[highlighted_row][highlighted_col].getTexture() == sprites[highlighted_row + 1][highlighted_col - 1].getTexture() &&
                            sprites[highlighted_row][highlighted_col].getTexture() == sprites[highlighted_row + 1][highlighted_col + 1].getTexture())
                        {
                            Sprite temp = sprites[highlighted_row][highlighted_col];
                            sprites[highlighted_row][highlighted_col] = sprites[highlighted_row + 1][highlighted_col];
                            sprites[highlighted_row + 1][highlighted_col] = temp;
                            // Update positions after swapping
                            sprites[highlighted_row][highlighted_col].setPosition((highlighted_col * gemSize) + off_setX, (highlighted_row * gemSize) + off_setY);
                            sprites[highlighted_row + 1][highlighted_col].setPosition((highlighted_col * gemSize) + off_setX, ((highlighted_row + 1) * gemSize) + off_setY);
                            score = score + score_3_matches;
                            scoreText.setString("Score: " + std::to_string(score));
                       }

                        else if (sprites[highlighted_row][highlighted_col].getTexture() == sprites[highlighted_row + 1][highlighted_col + 1].getTexture() &&
                            sprites[highlighted_row][highlighted_col].getTexture() == sprites[highlighted_row + 1][highlighted_col + 2].getTexture())
                        {
                            Sprite temp = sprites[highlighted_row][highlighted_col];
                            sprites[highlighted_row][highlighted_col] = sprites[highlighted_row + 1][highlighted_col];
                            sprites[highlighted_row + 1][highlighted_col] = temp;
                            // Update positions after swapping
                            sprites[highlighted_row][highlighted_col].setPosition((highlighted_col * gemSize) + off_setX, (highlighted_row * gemSize) + off_setY);
                            sprites[highlighted_row + 1][highlighted_col].setPosition((highlighted_col * gemSize) + off_setX, ((highlighted_row + 1) * gemSize) + off_setY);
                            score = score + score_3_matches;
                            scoreText.setString("Score: " + std::to_string(score));
                        }

                        else if (sprites[highlighted_row][highlighted_col].getTexture() == sprites[highlighted_row + 1][highlighted_col - 1].getTexture() &&
                            sprites[highlighted_row][highlighted_col].getTexture() == sprites[highlighted_row + 1][highlighted_col - 2].getTexture())
                        {
                            Sprite temp = sprites[highlighted_row][highlighted_col];
                            sprites[highlighted_row][highlighted_col] = sprites[highlighted_row + 1][highlighted_col];
                            sprites[highlighted_row + 1][highlighted_col] = temp;
                            // Update positions after swapping
                            sprites[highlighted_row][highlighted_col].setPosition((highlighted_col * gemSize) + off_setX, (highlighted_row * gemSize) + off_setY);
                            sprites[highlighted_row + 1][highlighted_col].setPosition((highlighted_col * gemSize) + off_setX, ((highlighted_row + 1) * gemSize) + off_setY);
                            score = score + score_3_matches;
                            scoreText.setString("Score: " + std::to_string(score));
                       }

                        else if (sprites[highlighted_row][highlighted_col].getTexture() == sprites[highlighted_row + 2][highlighted_col].getTexture() &&
                            sprites[highlighted_row][highlighted_col].getTexture() == sprites[highlighted_row + 3][highlighted_col].getTexture())
                        {
                            Sprite temp = sprites[highlighted_row][highlighted_col];
                            sprites[highlighted_row][highlighted_col] = sprites[highlighted_row + 1][highlighted_col];
                            sprites[highlighted_row + 1][highlighted_col] = temp;
                            // Update positions after swapping
                            sprites[highlighted_row][highlighted_col].setPosition((highlighted_col * gemSize) + off_setX, (highlighted_row * gemSize) + off_setY);
                            sprites[highlighted_row + 1][highlighted_col].setPosition((highlighted_col * gemSize) + off_setX, ((highlighted_row + 1) * gemSize) + off_setY);
                            score = score + score_3_matches;
                            scoreText.setString("Score: " + std::to_string(score));
                       }

                        else if (sprites[highlighted_row][highlighted_col].getTexture() == &images[0] &&
                            sprites[highlighted_row + 1][highlighted_col - 1].getTexture() == &images[0] &&
                            sprites[highlighted_row + 1][highlighted_col - 2].getTexture() == &images[7] ||
                            sprites[highlighted_row][highlighted_col].getTexture() == &images[1] &&
                            sprites[highlighted_row + 1][highlighted_col - 1].getTexture() == &images[1] &&
                            sprites[highlighted_row + 1][highlighted_col - 2].getTexture() == &images[8] ||
                            sprites[highlighted_row][highlighted_col].getTexture() == &images[2] &&
                            sprites[highlighted_row + 1][highlighted_col - 1].getTexture() == &images[2] &&
                            sprites[highlighted_row + 1][highlighted_col - 2].getTexture() == &images[9] ||
                            sprites[highlighted_row][highlighted_col].getTexture() == &images[3] &&
                            sprites[highlighted_row + 1][highlighted_col - 1].getTexture() == &images[3] &&
                            sprites[highlighted_row + 1][highlighted_col - 2].getTexture() == &images[10] ||
                            sprites[highlighted_row][highlighted_col].getTexture() == &images[4] &&
                            sprites[highlighted_row + 1][highlighted_col - 1].getTexture() == &images[4] &&
                            sprites[highlighted_row + 1][highlighted_col - 2].getTexture() == &images[11] ||
                            sprites[highlighted_row][highlighted_col].getTexture() == &images[5] &&
                            sprites[highlighted_row + 1][highlighted_col - 1].getTexture() == &images[5] &&
                            sprites[highlighted_row + 1][highlighted_col - 2].getTexture() == &images[12] ||
                            sprites[highlighted_row][highlighted_col].getTexture() == &images[6] &&
                            sprites[highlighted_row + 1][highlighted_col - 1].getTexture() == &images[6] &&
                            sprites[highlighted_row + 1][highlighted_col - 2].getTexture() == &images[13])
                        {
                            Sprite temp = sprites[highlighted_row][highlighted_col];
                            sprites[highlighted_row][highlighted_col] = sprites[highlighted_row + 1][highlighted_col];
                            sprites[highlighted_row + 1][highlighted_col] = temp;
                            // Update positions after swapping
                            sprites[highlighted_row][highlighted_col].setPosition((highlighted_col * gemSize) + off_setX, (highlighted_row * gemSize) + off_setY);
                            sprites[highlighted_row + 1][highlighted_col].setPosition((highlighted_col * gemSize) + off_setX, ((highlighted_row + 1) * gemSize) + off_setY);
                            score = score + score_4_special;
                            scoreText.setString("Score: " + std::to_string(score));
                           specialFourDown1 = true;
                        }

                        else if (sprites[highlighted_row][highlighted_col].getTexture() == &images[0] &&
                            sprites[highlighted_row + 1][highlighted_col - 1].getTexture() == &images[7] &&
                            sprites[highlighted_row + 1][highlighted_col - 2].getTexture() == &images[0] ||
                            sprites[highlighted_row][highlighted_col].getTexture() == &images[1] &&
                            sprites[highlighted_row + 1][highlighted_col - 1].getTexture() == &images[8] &&
                            sprites[highlighted_row + 1][highlighted_col - 2].getTexture() == &images[1] ||
                            sprites[highlighted_row][highlighted_col].getTexture() == &images[2] &&
                            sprites[highlighted_row + 1][highlighted_col - 1].getTexture() == &images[9] &&
                            sprites[highlighted_row + 1][highlighted_col - 2].getTexture() == &images[2] ||
                            sprites[highlighted_row][highlighted_col].getTexture() == &images[3] &&
                            sprites[highlighted_row + 1][highlighted_col - 1].getTexture() == &images[10] &&
                            sprites[highlighted_row + 1][highlighted_col - 2].getTexture() == &images[3] ||
                            sprites[highlighted_row][highlighted_col].getTexture() == &images[4] &&
                            sprites[highlighted_row + 1][highlighted_col - 1].getTexture() == &images[11] &&
                            sprites[highlighted_row + 1][highlighted_col - 2].getTexture() == &images[4] ||
                            sprites[highlighted_row][highlighted_col].getTexture() == &images[5] &&
                            sprites[highlighted_row + 1][highlighted_col - 1].getTexture() == &images[12] &&
                            sprites[highlighted_row + 1][highlighted_col - 2].getTexture() == &images[5] ||
                            sprites[highlighted_row][highlighted_col].getTexture() == &images[6] &&
                            sprites[highlighted_row + 1][highlighted_col - 1].getTexture() == &images[13] &&
                            sprites[highlighted_row + 1][highlighted_col - 2].getTexture() == &images[6])
                        {
                            Sprite temp = sprites[highlighted_row][highlighted_col];
                            sprites[highlighted_row][highlighted_col] = sprites[highlighted_row + 1][highlighted_col];
                            sprites[highlighted_row + 1][highlighted_col] = temp;
                            // Update positions after swapping
                            sprites[highlighted_row][highlighted_col].setPosition((highlighted_col * gemSize) + off_setX, (highlighted_row * gemSize) + off_setY);
                            sprites[highlighted_row + 1][highlighted_col].setPosition((highlighted_col * gemSize) + off_setX, ((highlighted_row + 1) * gemSize) + off_setY);
                            score = score + score_4_special;
                            scoreText.setString("Score: " + std::to_string(score));
                            specialFourDown2 = true;
                        }

                        else if (sprites[highlighted_row][highlighted_col].getTexture() == &images[0] &&
                            sprites[highlighted_row + 1][highlighted_col + 1].getTexture() == &images[7] &&
                            sprites[highlighted_row + 1][highlighted_col + 2].getTexture() == &images[0] ||
                            sprites[highlighted_row][highlighted_col].getTexture() == &images[1] &&
                            sprites[highlighted_row + 1][highlighted_col + 1].getTexture() == &images[8] &&
                            sprites[highlighted_row + 1][highlighted_col + 2].getTexture() == &images[1] ||
                            sprites[highlighted_row][highlighted_col].getTexture() == &images[2] &&
                            sprites[highlighted_row + 1][highlighted_col + 1].getTexture() == &images[9] &&
                            sprites[highlighted_row + 1][highlighted_col + 2].getTexture() == &images[2] ||
                            sprites[highlighted_row][highlighted_col].getTexture() == &images[3] &&
                            sprites[highlighted_row + 1][highlighted_col + 1].getTexture() == &images[10] &&
                            sprites[highlighted_row + 1][highlighted_col + 2].getTexture() == &images[3] ||
                            sprites[highlighted_row][highlighted_col].getTexture() == &images[4] &&
                            sprites[highlighted_row + 1][highlighted_col + 1].getTexture() == &images[11] &&
                            sprites[highlighted_row + 1][highlighted_col + 2].getTexture() == &images[4] ||
                            sprites[highlighted_row][highlighted_col].getTexture() == &images[5] &&
                            sprites[highlighted_row + 1][highlighted_col + 1].getTexture() == &images[12] &&
                            sprites[highlighted_row + 1][highlighted_col + 2].getTexture() == &images[5] ||
                            sprites[highlighted_row][highlighted_col].getTexture() == &images[6] &&
                            sprites[highlighted_row + 1][highlighted_col + 1].getTexture() == &images[13] &&
                            sprites[highlighted_row + 1][highlighted_col + 2].getTexture() == &images[6])
                        {
                            Sprite temp = sprites[highlighted_row][highlighted_col];
                            sprites[highlighted_row][highlighted_col] = sprites[highlighted_row + 1][highlighted_col];
                            sprites[highlighted_row + 1][highlighted_col] = temp;
                            // Update positions after swapping
                            sprites[highlighted_row][highlighted_col].setPosition((highlighted_col * gemSize) + off_setX, (highlighted_row * gemSize) + off_setY);
                            sprites[highlighted_row + 1][highlighted_col].setPosition((highlighted_col * gemSize) + off_setX, ((highlighted_row + 1) * gemSize) + off_setY);
                            score = score + score_4_special;
                            scoreText.setString("Score: " + std::to_string(score));
                            specialFourDown3 = true;
                        }

                        else if (sprites[highlighted_row][highlighted_col].getTexture() == &images[0] &&
                            sprites[highlighted_row + 1][highlighted_col + 1].getTexture() == &images[0] &&
                            sprites[highlighted_row + 1][highlighted_col + 2].getTexture() == &images[7] ||
                            sprites[highlighted_row][highlighted_col].getTexture() == &images[1] &&
                            sprites[highlighted_row + 1][highlighted_col + 1].getTexture() == &images[1] &&
                            sprites[highlighted_row + 1][highlighted_col + 2].getTexture() == &images[8] ||
                            sprites[highlighted_row][highlighted_col].getTexture() == &images[2] &&
                            sprites[highlighted_row + 1][highlighted_col + 1].getTexture() == &images[2] &&
                            sprites[highlighted_row + 1][highlighted_col + 2].getTexture() == &images[9] ||
                            sprites[highlighted_row][highlighted_col].getTexture() == &images[3] &&
                            sprites[highlighted_row + 1][highlighted_col + 1].getTexture() == &images[3] &&
                            sprites[highlighted_row + 1][highlighted_col + 2].getTexture() == &images[10] ||
                            sprites[highlighted_row][highlighted_col].getTexture() == &images[4] &&
                            sprites[highlighted_row + 1][highlighted_col + 1].getTexture() == &images[4] &&
                            sprites[highlighted_row + 1][highlighted_col + 2].getTexture() == &images[11] ||
                            sprites[highlighted_row][highlighted_col].getTexture() == &images[5] &&
                            sprites[highlighted_row + 1][highlighted_col + 1].getTexture() == &images[5] &&
                            sprites[highlighted_row + 1][highlighted_col + 2].getTexture() == &images[12] ||
                            sprites[highlighted_row][highlighted_col].getTexture() == &images[6] &&
                            sprites[highlighted_row + 1][highlighted_col + 1].getTexture() == &images[6] &&
                            sprites[highlighted_row + 1][highlighted_col + 2].getTexture() == &images[13])
                        {
                            Sprite temp = sprites[highlighted_row][highlighted_col];
                            sprites[highlighted_row][highlighted_col] = sprites[highlighted_row + 1][highlighted_col];
                            sprites[highlighted_row + 1][highlighted_col] = temp;
                            // Update positions after swapping
                            sprites[highlighted_row][highlighted_col].setPosition((highlighted_col * gemSize) + off_setX, (highlighted_row * gemSize) + off_setY);
                            sprites[highlighted_row + 1][highlighted_col].setPosition((highlighted_col * gemSize) + off_setX, ((highlighted_row + 1) * gemSize) + off_setY);
                            score = score + score_4_special;
                            scoreText.setString("Score: " + std::to_string(score));
                            specialFourDown4 = true;
                        }

                        else if (sprites[highlighted_row][highlighted_col].getTexture() == &images[0] &&
                            sprites[highlighted_row + 1][highlighted_col + 1].getTexture() == &images[7] &&
                            sprites[highlighted_row + 1][highlighted_col - 1].getTexture() == &images[0] ||
                            sprites[highlighted_row][highlighted_col].getTexture() == &images[1] &&
                            sprites[highlighted_row + 1][highlighted_col + 1].getTexture() == &images[8] &&
                            sprites[highlighted_row + 1][highlighted_col - 1].getTexture() == &images[1] ||
                            sprites[highlighted_row][highlighted_col].getTexture() == &images[2] &&
                            sprites[highlighted_row + 1][highlighted_col + 1].getTexture() == &images[9] &&
                            sprites[highlighted_row + 1][highlighted_col - 1].getTexture() == &images[2] ||
                            sprites[highlighted_row][highlighted_col].getTexture() == &images[3] &&
                            sprites[highlighted_row + 1][highlighted_col + 1].getTexture() == &images[10] &&
                            sprites[highlighted_row + 1][highlighted_col - 1].getTexture() == &images[3] ||
                            sprites[highlighted_row][highlighted_col].getTexture() == &images[4] &&
                            sprites[highlighted_row + 1][highlighted_col + 1].getTexture() == &images[11] &&
                            sprites[highlighted_row + 1][highlighted_col - 1].getTexture() == &images[4] ||
                            sprites[highlighted_row][highlighted_col].getTexture() == &images[5] &&
                            sprites[highlighted_row + 1][highlighted_col + 1].getTexture() == &images[12] &&
                            sprites[highlighted_row + 1][highlighted_col - 1].getTexture() == &images[5] ||
                            sprites[highlighted_row][highlighted_col].getTexture() == &images[6] &&
                            sprites[highlighted_row + 1][highlighted_col + 1].getTexture() == &images[13] &&
                            sprites[highlighted_row + 1][highlighted_col - 1].getTexture() == &images[6])
                        {
                            Sprite temp = sprites[highlighted_row][highlighted_col];
                            sprites[highlighted_row][highlighted_col] = sprites[highlighted_row + 1][highlighted_col];
                            sprites[highlighted_row + 1][highlighted_col] = temp;
                            // Update positions after swapping
                            sprites[highlighted_row][highlighted_col].setPosition((highlighted_col * gemSize) + off_setX, (highlighted_row * gemSize) + off_setY);
                            sprites[highlighted_row + 1][highlighted_col].setPosition((highlighted_col * gemSize) + off_setX, ((highlighted_row + 1) * gemSize) + off_setY);
                            score = score + score_4_special;
                            scoreText.setString("Score: " + std::to_string(score));
                            specialFourDown5 = true;
                        }

                        else if (sprites[highlighted_row][highlighted_col].getTexture() == &images[0] &&
                            sprites[highlighted_row + 1][highlighted_col + 1].getTexture() == &images[0] &&
                            sprites[highlighted_row + 1][highlighted_col - 1].getTexture() == &images[7] ||
                            sprites[highlighted_row][highlighted_col].getTexture() == &images[1] &&
                            sprites[highlighted_row + 1][highlighted_col + 1].getTexture() == &images[1] &&
                            sprites[highlighted_row + 1][highlighted_col - 1].getTexture() == &images[8] ||
                            sprites[highlighted_row][highlighted_col].getTexture() == &images[2] &&
                            sprites[highlighted_row + 1][highlighted_col + 1].getTexture() == &images[2] &&
                            sprites[highlighted_row + 1][highlighted_col - 1].getTexture() == &images[9] ||
                            sprites[highlighted_row][highlighted_col].getTexture() == &images[3] &&
                            sprites[highlighted_row + 1][highlighted_col + 1].getTexture() == &images[3] &&
                            sprites[highlighted_row + 1][highlighted_col - 1].getTexture() == &images[10] ||
                            sprites[highlighted_row][highlighted_col].getTexture() == &images[4] &&
                            sprites[highlighted_row + 1][highlighted_col + 1].getTexture() == &images[4] &&
                            sprites[highlighted_row + 1][highlighted_col - 1].getTexture() == &images[11] ||
                            sprites[highlighted_row][highlighted_col].getTexture() == &images[5] &&
                            sprites[highlighted_row + 1][highlighted_col + 1].getTexture() == &images[5] &&
                            sprites[highlighted_row + 1][highlighted_col - 1].getTexture() == &images[12] ||
                            sprites[highlighted_row][highlighted_col].getTexture() == &images[6] &&
                            sprites[highlighted_row + 1][highlighted_col + 1].getTexture() == &images[6] &&
                            sprites[highlighted_row + 1][highlighted_col - 1].getTexture() == &images[13])
                        {
                            Sprite temp = sprites[highlighted_row][highlighted_col];
                            sprites[highlighted_row][highlighted_col] = sprites[highlighted_row + 1][highlighted_col];
                            sprites[highlighted_row + 1][highlighted_col] = temp;
                            // Update positions after swapping
                            sprites[highlighted_row][highlighted_col].setPosition((highlighted_col * gemSize) + off_setX, (highlighted_row * gemSize) + off_setY);
                            sprites[highlighted_row + 1][highlighted_col].setPosition((highlighted_col * gemSize) + off_setX, ((highlighted_row + 1) * gemSize) + off_setY);
                            score = score + score_4_special;
                            scoreText.setString("Score: " + std::to_string(score));
                            specialFourDown6 = true;
                        }

                        else if (sprites[highlighted_row][highlighted_col].getTexture() == &images[7] &&
                            sprites[highlighted_row + 1][highlighted_col + 1].getTexture() == &images[0] &&
                            sprites[highlighted_row + 1][highlighted_col + 2].getTexture() == &images[0] ||
                            sprites[highlighted_row][highlighted_col].getTexture() == &images[8] &&
                            sprites[highlighted_row + 1][highlighted_col + 1].getTexture() == &images[1] &&
                            sprites[highlighted_row + 1][highlighted_col + 2].getTexture() == &images[1] ||
                            sprites[highlighted_row][highlighted_col].getTexture() == &images[9] &&
                            sprites[highlighted_row + 1][highlighted_col + 1].getTexture() == &images[2] &&
                            sprites[highlighted_row + 1][highlighted_col + 2].getTexture() == &images[2] ||
                            sprites[highlighted_row][highlighted_col].getTexture() == &images[10] &&
                            sprites[highlighted_row + 1][highlighted_col + 1].getTexture() == &images[3] &&
                            sprites[highlighted_row + 1][highlighted_col + 2].getTexture() == &images[3] ||
                            sprites[highlighted_row][highlighted_col].getTexture() == &images[11] &&
                            sprites[highlighted_row + 1][highlighted_col + 1].getTexture() == &images[4] &&
                            sprites[highlighted_row + 1][highlighted_col + 2].getTexture() == &images[4] ||
                            sprites[highlighted_row][highlighted_col].getTexture() == &images[12] &&
                            sprites[highlighted_row + 1][highlighted_col + 1].getTexture() == &images[5] &&
                            sprites[highlighted_row + 1][highlighted_col + 2].getTexture() == &images[5] ||
                            sprites[highlighted_row][highlighted_col].getTexture() == &images[13] &&
                            sprites[highlighted_row + 1][highlighted_col + 1].getTexture() == &images[6] &&
                            sprites[highlighted_row + 1][highlighted_col + 2].getTexture() == &images[6])
                        {
                            Sprite temp = sprites[highlighted_row][highlighted_col];
                            sprites[highlighted_row][highlighted_col] = sprites[highlighted_row + 1][highlighted_col];
                            sprites[highlighted_row + 1][highlighted_col] = temp;
                            // Update positions after swapping
                            sprites[highlighted_row][highlighted_col].setPosition((highlighted_col * gemSize) + off_setX, (highlighted_row * gemSize) + off_setY);
                            sprites[highlighted_row + 1][highlighted_col].setPosition((highlighted_col * gemSize) + off_setX, ((highlighted_row + 1) * gemSize) + off_setY);
                            score = score + score_4_special;
                            scoreText.setString("Score: " + std::to_string(score));
                            specialRealFourDown = true;
                        }

                        else if (sprites[highlighted_row][highlighted_col].getTexture() == &images[7] &&
                            sprites[highlighted_row + 1][highlighted_col - 1].getTexture() == &images[0] &&
                            sprites[highlighted_row + 1][highlighted_col - 2].getTexture() == &images[0] ||
                            sprites[highlighted_row][highlighted_col].getTexture() == &images[8] &&
                            sprites[highlighted_row + 1][highlighted_col - 1].getTexture() == &images[1] &&
                            sprites[highlighted_row + 1][highlighted_col - 2].getTexture() == &images[1] ||
                            sprites[highlighted_row][highlighted_col].getTexture() == &images[9] &&
                            sprites[highlighted_row + 1][highlighted_col - 1].getTexture() == &images[2] &&
                            sprites[highlighted_row + 1][highlighted_col - 2].getTexture() == &images[2] ||
                            sprites[highlighted_row][highlighted_col].getTexture() == &images[10] &&
                            sprites[highlighted_row + 1][highlighted_col - 1].getTexture() == &images[3] &&
                            sprites[highlighted_row + 1][highlighted_col - 2].getTexture() == &images[3] ||
                            sprites[highlighted_row][highlighted_col].getTexture() == &images[11] &&
                            sprites[highlighted_row + 1][highlighted_col - 1].getTexture() == &images[4] &&
                            sprites[highlighted_row + 1][highlighted_col - 2].getTexture() == &images[4] ||
                            sprites[highlighted_row][highlighted_col].getTexture() == &images[12] &&
                            sprites[highlighted_row + 1][highlighted_col - 1].getTexture() == &images[5] &&
                            sprites[highlighted_row + 1][highlighted_col - 2].getTexture() == &images[5] ||
                            sprites[highlighted_row][highlighted_col].getTexture() == &images[13] &&
                            sprites[highlighted_row + 1][highlighted_col - 1].getTexture() == &images[6] &&
                            sprites[highlighted_row + 1][highlighted_col - 2].getTexture() == &images[6])
                        {
                            Sprite temp = sprites[highlighted_row][highlighted_col];
                            sprites[highlighted_row][highlighted_col] = sprites[highlighted_row + 1][highlighted_col];
                            sprites[highlighted_row + 1][highlighted_col] = temp;
                            // Update positions after swapping
                            sprites[highlighted_row][highlighted_col].setPosition((highlighted_col * gemSize) + off_setX, (highlighted_row * gemSize) + off_setY);
                            sprites[highlighted_row + 1][highlighted_col].setPosition((highlighted_col * gemSize) + off_setX, ((highlighted_row + 1) * gemSize) + off_setY);
                            score = score + score_4_special;
                            scoreText.setString("Score: " + std::to_string(score));
                            specialRealFourDown = true;
                        }

                        else if (sprites[highlighted_row][highlighted_col].getTexture() == &images[7] &&
                            sprites[highlighted_row + 1][highlighted_col - 1].getTexture() == &images[0] &&
                            sprites[highlighted_row + 1][highlighted_col + 1].getTexture() == &images[0] ||
                            sprites[highlighted_row][highlighted_col].getTexture() == &images[8] &&
                            sprites[highlighted_row + 1][highlighted_col - 1].getTexture() == &images[1] &&
                            sprites[highlighted_row + 1][highlighted_col + 1].getTexture() == &images[1] ||
                            sprites[highlighted_row][highlighted_col].getTexture() == &images[9] &&
                            sprites[highlighted_row + 1][highlighted_col - 1].getTexture() == &images[2] &&
                            sprites[highlighted_row + 1][highlighted_col + 1].getTexture() == &images[2] ||
                            sprites[highlighted_row][highlighted_col].getTexture() == &images[10] &&
                            sprites[highlighted_row + 1][highlighted_col - 1].getTexture() == &images[3] &&
                            sprites[highlighted_row + 1][highlighted_col + 1].getTexture() == &images[3] ||
                            sprites[highlighted_row][highlighted_col].getTexture() == &images[11] &&
                            sprites[highlighted_row + 1][highlighted_col - 1].getTexture() == &images[4] &&
                            sprites[highlighted_row + 1][highlighted_col + 1].getTexture() == &images[4] ||
                            sprites[highlighted_row][highlighted_col].getTexture() == &images[12] &&
                            sprites[highlighted_row + 1][highlighted_col - 1].getTexture() == &images[5] &&
                            sprites[highlighted_row + 1][highlighted_col + 1].getTexture() == &images[5] ||
                            sprites[highlighted_row][highlighted_col].getTexture() == &images[13] &&
                            sprites[highlighted_row + 1][highlighted_col - 1].getTexture() == &images[6] &&
                            sprites[highlighted_row + 1][highlighted_col + 1].getTexture() == &images[6])
                        {
                            Sprite temp = sprites[highlighted_row][highlighted_col];
                            sprites[highlighted_row][highlighted_col] = sprites[highlighted_row + 1][highlighted_col];
                            sprites[highlighted_row + 1][highlighted_col] = temp;
                            // Update positions after swapping
                            sprites[highlighted_row][highlighted_col].setPosition((highlighted_col * gemSize) + off_setX, (highlighted_row * gemSize) + off_setY);
                            sprites[highlighted_row + 1][highlighted_col].setPosition((highlighted_col * gemSize) + off_setX, ((highlighted_row + 1) * gemSize) + off_setY);
                            score = score + score_4_special;
                            scoreText.setString("Score: " + std::to_string(score));
                            specialRealFourDown = true;
                        }

                        else if (sprites[highlighted_row][highlighted_col].getTexture() == &images[7] &&
                            sprites[highlighted_row + 2][highlighted_col].getTexture() == &images[0] &&
                            sprites[highlighted_row + 3][highlighted_col].getTexture() == &images[0] ||
                            sprites[highlighted_row][highlighted_col].getTexture() == &images[8] &&
                            sprites[highlighted_row + 2][highlighted_col].getTexture() == &images[1] &&
                            sprites[highlighted_row + 3][highlighted_col].getTexture() == &images[1] ||
                            sprites[highlighted_row][highlighted_col].getTexture() == &images[9] &&
                            sprites[highlighted_row + 2][highlighted_col].getTexture() == &images[2] &&
                            sprites[highlighted_row + 3][highlighted_col].getTexture() == &images[2] ||
                            sprites[highlighted_row][highlighted_col].getTexture() == &images[10] &&
                            sprites[highlighted_row + 2][highlighted_col].getTexture() == &images[3] &&
                            sprites[highlighted_row + 3][highlighted_col].getTexture() == &images[3] ||
                            sprites[highlighted_row][highlighted_col].getTexture() == &images[11] &&
                            sprites[highlighted_row + 2][highlighted_col].getTexture() == &images[4] &&
                            sprites[highlighted_row + 3][highlighted_col].getTexture() == &images[4] ||
                            sprites[highlighted_row][highlighted_col].getTexture() == &images[12] &&
                            sprites[highlighted_row + 2][highlighted_col].getTexture() == &images[5] &&
                            sprites[highlighted_row + 3][highlighted_col].getTexture() == &images[5] ||
                            sprites[highlighted_row][highlighted_col].getTexture() == &images[13] &&
                            sprites[highlighted_row + 2][highlighted_col].getTexture() == &images[6] &&
                            sprites[highlighted_row + 3][highlighted_col].getTexture() == &images[6])
                        {
                            Sprite temp = sprites[highlighted_row][highlighted_col];
                            sprites[highlighted_row][highlighted_col] = sprites[highlighted_row + 1][highlighted_col];
                            sprites[highlighted_row + 1][highlighted_col] = temp;
                            // Update positions after swapping
                            sprites[highlighted_row][highlighted_col].setPosition((highlighted_col * gemSize) + off_setX, (highlighted_row * gemSize) + off_setY);
                            sprites[highlighted_row + 1][highlighted_col].setPosition((highlighted_col * gemSize) + off_setX, ((highlighted_row + 1) * gemSize) + off_setY);
                            score = score + score_4_special;
                            scoreText.setString("Score: " + std::to_string(score));
                            specialRealFourUp = true;
                        }

                        else if (sprites[highlighted_row][highlighted_col].getTexture() == &images[0] &&
                            sprites[highlighted_row + 1][highlighted_col - 1].getTexture() == &images[0] &&
                            sprites[highlighted_row + 1][highlighted_col - 2].getTexture() == &images[14] ||
                            sprites[highlighted_row][highlighted_col].getTexture() == &images[1] &&
                            sprites[highlighted_row + 1][highlighted_col - 1].getTexture() == &images[1] &&
                            sprites[highlighted_row + 1][highlighted_col - 2].getTexture() == &images[15] ||
                            sprites[highlighted_row][highlighted_col].getTexture() == &images[2] &&
                            sprites[highlighted_row + 1][highlighted_col - 1].getTexture() == &images[2] &&
                            sprites[highlighted_row + 1][highlighted_col - 2].getTexture() == &images[16] ||
                            sprites[highlighted_row][highlighted_col].getTexture() == &images[3] &&
                            sprites[highlighted_row + 1][highlighted_col - 1].getTexture() == &images[3] &&
                            sprites[highlighted_row + 1][highlighted_col - 2].getTexture() == &images[17] ||
                            sprites[highlighted_row][highlighted_col].getTexture() == &images[4] &&
                            sprites[highlighted_row + 1][highlighted_col - 1].getTexture() == &images[4] &&
                            sprites[highlighted_row + 1][highlighted_col - 2].getTexture() == &images[18] ||
                            sprites[highlighted_row][highlighted_col].getTexture() == &images[5] &&
                            sprites[highlighted_row + 1][highlighted_col - 1].getTexture() == &images[5] &&
                            sprites[highlighted_row + 1][highlighted_col - 2].getTexture() == &images[19] ||
                            sprites[highlighted_row][highlighted_col].getTexture() == &images[6] &&
                            sprites[highlighted_row + 1][highlighted_col - 1].getTexture() == &images[6] &&
                            sprites[highlighted_row + 1][highlighted_col - 2].getTexture() == &images[20])
                        {
                            specialRow = highlighted_row + 1;
                            specialCol = highlighted_col - 2;



                            Sprite temp = sprites[highlighted_row][highlighted_col];
                            sprites[highlighted_row][highlighted_col] = sprites[highlighted_row + 1][highlighted_col];
                            sprites[highlighted_row + 1][highlighted_col] = temp;
                            // Update positions after swapping
                            sprites[highlighted_row][highlighted_col].setPosition((highlighted_col * gemSize) + off_setX, (highlighted_row * gemSize) + off_setY);
                            sprites[highlighted_row + 1][highlighted_col].setPosition((highlighted_col * gemSize) + off_setX, ((highlighted_row + 1) * gemSize) + off_setY);
                            score = score + score_5_special;
                            scoreText.setString("Score: " + std::to_string(score));
                            specialFive = true;
                        }

                        else if (sprites[highlighted_row][highlighted_col].getTexture() == &images[0] &&
                            sprites[highlighted_row + 1][highlighted_col - 1].getTexture() == &images[14] &&
                            sprites[highlighted_row + 1][highlighted_col - 2].getTexture() == &images[0] ||
                            sprites[highlighted_row][highlighted_col].getTexture() == &images[1] &&
                            sprites[highlighted_row + 1][highlighted_col - 1].getTexture() == &images[15] &&
                            sprites[highlighted_row + 1][highlighted_col - 2].getTexture() == &images[1] ||
                            sprites[highlighted_row][highlighted_col].getTexture() == &images[2] &&
                            sprites[highlighted_row + 1][highlighted_col - 1].getTexture() == &images[16] &&
                            sprites[highlighted_row + 1][highlighted_col - 2].getTexture() == &images[2] ||
                            sprites[highlighted_row][highlighted_col].getTexture() == &images[3] &&
                            sprites[highlighted_row + 1][highlighted_col - 1].getTexture() == &images[17] &&
                            sprites[highlighted_row + 1][highlighted_col - 2].getTexture() == &images[3] ||
                            sprites[highlighted_row][highlighted_col].getTexture() == &images[4] &&
                            sprites[highlighted_row + 1][highlighted_col - 1].getTexture() == &images[18] &&
                            sprites[highlighted_row + 1][highlighted_col - 2].getTexture() == &images[4] ||
                            sprites[highlighted_row][highlighted_col].getTexture() == &images[5] &&
                            sprites[highlighted_row + 1][highlighted_col - 1].getTexture() == &images[19] &&
                            sprites[highlighted_row + 1][highlighted_col - 2].getTexture() == &images[5] ||
                            sprites[highlighted_row][highlighted_col].getTexture() == &images[6] &&
                            sprites[highlighted_row + 1][highlighted_col - 1].getTexture() == &images[20] &&
                            sprites[highlighted_row + 1][highlighted_col - 2].getTexture() == &images[6])
                        {
                            specialRow = highlighted_row + 1;
                            specialCol = highlighted_col - 1;


                            Sprite temp = sprites[highlighted_row][highlighted_col];
                            sprites[highlighted_row][highlighted_col] = sprites[highlighted_row + 1][highlighted_col];
                            sprites[highlighted_row + 1][highlighted_col] = temp;
                            // Update positions after swapping
                            sprites[highlighted_row][highlighted_col].setPosition((highlighted_col * gemSize) + off_setX, (highlighted_row * gemSize) + off_setY);
                            sprites[highlighted_row + 1][highlighted_col].setPosition((highlighted_col * gemSize) + off_setX, ((highlighted_row + 1) * gemSize) + off_setY);
                            score = score + score_5_special;
                            scoreText.setString("Score: " + std::to_string(score));
                            specialFive = true;
                        }

                        else if (sprites[highlighted_row][highlighted_col].getTexture() == &images[0] &&
                            sprites[highlighted_row + 1][highlighted_col + 1].getTexture() == &images[14] &&
                            sprites[highlighted_row + 1][highlighted_col + 2].getTexture() == &images[0] ||
                            sprites[highlighted_row][highlighted_col].getTexture() == &images[1] &&
                            sprites[highlighted_row + 1][highlighted_col + 1].getTexture() == &images[15] &&
                            sprites[highlighted_row + 1][highlighted_col + 2].getTexture() == &images[1] ||
                            sprites[highlighted_row][highlighted_col].getTexture() == &images[2] &&
                            sprites[highlighted_row + 1][highlighted_col + 1].getTexture() == &images[16] &&
                            sprites[highlighted_row + 1][highlighted_col + 2].getTexture() == &images[2] ||
                            sprites[highlighted_row][highlighted_col].getTexture() == &images[3] &&
                            sprites[highlighted_row + 1][highlighted_col + 1].getTexture() == &images[17] &&
                            sprites[highlighted_row + 1][highlighted_col + 2].getTexture() == &images[3] ||
                            sprites[highlighted_row][highlighted_col].getTexture() == &images[4] &&
                            sprites[highlighted_row + 1][highlighted_col + 1].getTexture() == &images[18] &&
                            sprites[highlighted_row + 1][highlighted_col + 2].getTexture() == &images[4] ||
                            sprites[highlighted_row][highlighted_col].getTexture() == &images[5] &&
                            sprites[highlighted_row + 1][highlighted_col + 1].getTexture() == &images[19] &&
                            sprites[highlighted_row + 1][highlighted_col + 2].getTexture() == &images[5] ||
                            sprites[highlighted_row][highlighted_col].getTexture() == &images[6] &&
                            sprites[highlighted_row + 1][highlighted_col + 1].getTexture() == &images[20] &&
                            sprites[highlighted_row + 1][highlighted_col + 2].getTexture() == &images[6])
                        {
                            specialRow = highlighted_row + 1;
                            specialCol = highlighted_col + 1;


                            Sprite temp = sprites[highlighted_row][highlighted_col];
                            sprites[highlighted_row][highlighted_col] = sprites[highlighted_row + 1][highlighted_col];
                            sprites[highlighted_row + 1][highlighted_col] = temp;
                            // Update positions after swapping
                            sprites[highlighted_row][highlighted_col].setPosition((highlighted_col * gemSize) + off_setX, (highlighted_row * gemSize) + off_setY);
                            sprites[highlighted_row + 1][highlighted_col].setPosition((highlighted_col * gemSize) + off_setX, ((highlighted_row + 1) * gemSize) + off_setY);
                            score = score + score_5_special;
                            scoreText.setString("Score: " + std::to_string(score));
                            specialFive = true;
                        }

                        else if (sprites[highlighted_row][highlighted_col].getTexture() == &images[0] &&
                            sprites[highlighted_row + 1][highlighted_col + 1].getTexture() == &images[0] &&
                            sprites[highlighted_row + 1][highlighted_col + 2].getTexture() == &images[14] ||
                            sprites[highlighted_row][highlighted_col].getTexture() == &images[1] &&
                            sprites[highlighted_row + 1][highlighted_col + 1].getTexture() == &images[1] &&
                            sprites[highlighted_row + 1][highlighted_col + 2].getTexture() == &images[15] ||
                            sprites[highlighted_row][highlighted_col].getTexture() == &images[2] &&
                            sprites[highlighted_row + 1][highlighted_col + 1].getTexture() == &images[2] &&
                            sprites[highlighted_row + 1][highlighted_col + 2].getTexture() == &images[16] ||
                            sprites[highlighted_row][highlighted_col].getTexture() == &images[3] &&
                            sprites[highlighted_row + 1][highlighted_col + 1].getTexture() == &images[3] &&
                            sprites[highlighted_row + 1][highlighted_col + 2].getTexture() == &images[17] ||
                            sprites[highlighted_row][highlighted_col].getTexture() == &images[4] &&
                            sprites[highlighted_row + 1][highlighted_col + 1].getTexture() == &images[4] &&
                            sprites[highlighted_row + 1][highlighted_col + 2].getTexture() == &images[18] ||
                            sprites[highlighted_row][highlighted_col].getTexture() == &images[5] &&
                            sprites[highlighted_row + 1][highlighted_col + 1].getTexture() == &images[5] &&
                            sprites[highlighted_row + 1][highlighted_col + 2].getTexture() == &images[19] ||
                            sprites[highlighted_row][highlighted_col].getTexture() == &images[6] &&
                            sprites[highlighted_row + 1][highlighted_col + 1].getTexture() == &images[6] &&
                            sprites[highlighted_row + 1][highlighted_col + 2].getTexture() == &images[20])
                        {
                            specialRow = highlighted_row + 1;
                            specialCol = highlighted_col + 2;


                            Sprite temp = sprites[highlighted_row][highlighted_col];
                            sprites[highlighted_row][highlighted_col] = sprites[highlighted_row + 1][highlighted_col];
                            sprites[highlighted_row + 1][highlighted_col] = temp;
                            // Update positions after swapping
                            sprites[highlighted_row][highlighted_col].setPosition((highlighted_col * gemSize) + off_setX, (highlighted_row * gemSize) + off_setY);
                            sprites[highlighted_row + 1][highlighted_col].setPosition((highlighted_col * gemSize) + off_setX, ((highlighted_row + 1) * gemSize) + off_setY);
                            score = score + score_5_special;
                            scoreText.setString("Score: " + std::to_string(score));
                            specialFive = true;
                        }

                        else if (sprites[highlighted_row][highlighted_col].getTexture() == &images[0] &&
                            sprites[highlighted_row + 1][highlighted_col + 1].getTexture() == &images[14] &&
                            sprites[highlighted_row + 1][highlighted_col - 1].getTexture() == &images[0] ||
                            sprites[highlighted_row][highlighted_col].getTexture() == &images[1] &&
                            sprites[highlighted_row + 1][highlighted_col + 1].getTexture() == &images[15] &&
                            sprites[highlighted_row + 1][highlighted_col - 1].getTexture() == &images[1] ||
                            sprites[highlighted_row][highlighted_col].getTexture() == &images[2] &&
                            sprites[highlighted_row + 1][highlighted_col + 1].getTexture() == &images[16] &&
                            sprites[highlighted_row + 1][highlighted_col - 1].getTexture() == &images[2] ||
                            sprites[highlighted_row][highlighted_col].getTexture() == &images[3] &&
                            sprites[highlighted_row + 1][highlighted_col + 1].getTexture() == &images[17] &&
                            sprites[highlighted_row + 1][highlighted_col - 1].getTexture() == &images[3] ||
                            sprites[highlighted_row][highlighted_col].getTexture() == &images[4] &&
                            sprites[highlighted_row + 1][highlighted_col + 1].getTexture() == &images[18] &&
                            sprites[highlighted_row + 1][highlighted_col - 1].getTexture() == &images[4] ||
                            sprites[highlighted_row][highlighted_col].getTexture() == &images[5] &&
                            sprites[highlighted_row + 1][highlighted_col + 1].getTexture() == &images[19] &&
                            sprites[highlighted_row + 1][highlighted_col - 1].getTexture() == &images[5] ||
                            sprites[highlighted_row][highlighted_col].getTexture() == &images[6] &&
                            sprites[highlighted_row + 1][highlighted_col + 1].getTexture() == &images[20] &&
                            sprites[highlighted_row + 1][highlighted_col - 1].getTexture() == &images[6])
                        {
                            specialRow = highlighted_row + 1;
                            specialCol = highlighted_col + 1;


                            Sprite temp = sprites[highlighted_row][highlighted_col];
                            sprites[highlighted_row][highlighted_col] = sprites[highlighted_row + 1][highlighted_col];
                            sprites[highlighted_row + 1][highlighted_col] = temp;
                            // Update positions after swapping
                            sprites[highlighted_row][highlighted_col].setPosition((highlighted_col * gemSize) + off_setX, (highlighted_row * gemSize) + off_setY);
                            sprites[highlighted_row + 1][highlighted_col].setPosition((highlighted_col * gemSize) + off_setX, ((highlighted_row + 1) * gemSize) + off_setY);
                            score = score + score_5_special;
                            scoreText.setString("Score: " + std::to_string(score));
                            specialFive = true;
                        }

                        else if (sprites[highlighted_row][highlighted_col].getTexture() == &images[0] &&
                            sprites[highlighted_row + 1][highlighted_col + 1].getTexture() == &images[0] &&
                            sprites[highlighted_row + 1][highlighted_col - 1].getTexture() == &images[14] ||
                            sprites[highlighted_row][highlighted_col].getTexture() == &images[1] &&
                            sprites[highlighted_row + 1][highlighted_col + 1].getTexture() == &images[1] &&
                            sprites[highlighted_row + 1][highlighted_col - 1].getTexture() == &images[15] ||
                            sprites[highlighted_row][highlighted_col].getTexture() == &images[2] &&
                            sprites[highlighted_row + 1][highlighted_col + 1].getTexture() == &images[2] &&
                            sprites[highlighted_row + 1][highlighted_col - 1].getTexture() == &images[16] ||
                            sprites[highlighted_row][highlighted_col].getTexture() == &images[3] &&
                            sprites[highlighted_row + 1][highlighted_col + 1].getTexture() == &images[3] &&
                            sprites[highlighted_row + 1][highlighted_col - 1].getTexture() == &images[17] ||
                            sprites[highlighted_row][highlighted_col].getTexture() == &images[4] &&
                            sprites[highlighted_row + 1][highlighted_col + 1].getTexture() == &images[4] &&
                            sprites[highlighted_row + 1][highlighted_col - 1].getTexture() == &images[18] ||
                            sprites[highlighted_row][highlighted_col].getTexture() == &images[5] &&
                            sprites[highlighted_row + 1][highlighted_col + 1].getTexture() == &images[5] &&
                            sprites[highlighted_row + 1][highlighted_col - 1].getTexture() == &images[19] ||
                            sprites[highlighted_row][highlighted_col].getTexture() == &images[6] &&
                            sprites[highlighted_row + 1][highlighted_col + 1].getTexture() == &images[6] &&
                            sprites[highlighted_row + 1][highlighted_col - 1].getTexture() == &images[20])
                        {
                            specialRow = highlighted_row + 1;
                            specialCol = highlighted_col - 1;


                            Sprite temp = sprites[highlighted_row][highlighted_col];
                            sprites[highlighted_row][highlighted_col] = sprites[highlighted_row + 1][highlighted_col];
                            sprites[highlighted_row + 1][highlighted_col] = temp;
                            // Update positions after swapping
                            sprites[highlighted_row][highlighted_col].setPosition((highlighted_col * gemSize) + off_setX, (highlighted_row * gemSize) + off_setY);
                            sprites[highlighted_row + 1][highlighted_col].setPosition((highlighted_col * gemSize) + off_setX, ((highlighted_row + 1) * gemSize) + off_setY);
                            score = score + score_5_special;
                            scoreText.setString("Score: " + std::to_string(score));
                            specialFive = true;
                        }

                        else if (sprites[highlighted_row][highlighted_col].getTexture() == &images[14] &&
                            sprites[highlighted_row + 1][highlighted_col + 1].getTexture() == &images[0] &&
                            sprites[highlighted_row + 1][highlighted_col + 2].getTexture() == &images[0] ||
                            sprites[highlighted_row][highlighted_col].getTexture() == &images[15] &&
                            sprites[highlighted_row + 1][highlighted_col + 1].getTexture() == &images[1] &&
                            sprites[highlighted_row + 1][highlighted_col + 2].getTexture() == &images[1] ||
                            sprites[highlighted_row][highlighted_col].getTexture() == &images[16] &&
                            sprites[highlighted_row + 1][highlighted_col + 1].getTexture() == &images[2] &&
                            sprites[highlighted_row + 1][highlighted_col + 2].getTexture() == &images[2] ||
                            sprites[highlighted_row][highlighted_col].getTexture() == &images[17] &&
                            sprites[highlighted_row + 1][highlighted_col + 1].getTexture() == &images[3] &&
                            sprites[highlighted_row + 1][highlighted_col + 2].getTexture() == &images[3] ||
                            sprites[highlighted_row][highlighted_col].getTexture() == &images[18] &&
                            sprites[highlighted_row + 1][highlighted_col + 1].getTexture() == &images[4] &&
                            sprites[highlighted_row + 1][highlighted_col + 2].getTexture() == &images[4] ||
                            sprites[highlighted_row][highlighted_col].getTexture() == &images[19] &&
                            sprites[highlighted_row + 1][highlighted_col + 1].getTexture() == &images[5] &&
                            sprites[highlighted_row + 1][highlighted_col + 2].getTexture() == &images[5] ||
                            sprites[highlighted_row][highlighted_col].getTexture() == &images[20] &&
                            sprites[highlighted_row + 1][highlighted_col + 1].getTexture() == &images[6] &&
                            sprites[highlighted_row + 1][highlighted_col + 2].getTexture() == &images[6])
                        {
                            specialRow = highlighted_row + 1;
                            specialCol = highlighted_col;


                            Sprite temp = sprites[highlighted_row][highlighted_col];
                            sprites[highlighted_row][highlighted_col] = sprites[highlighted_row + 1][highlighted_col];
                            sprites[highlighted_row + 1][highlighted_col] = temp;
                            // Update positions after swapping
                            sprites[highlighted_row][highlighted_col].setPosition((highlighted_col * gemSize) + off_setX, (highlighted_row * gemSize) + off_setY);
                            sprites[highlighted_row + 1][highlighted_col].setPosition((highlighted_col * gemSize) + off_setX, ((highlighted_row + 1) * gemSize) + off_setY);
                            score = score + score_5_special;
                            scoreText.setString("Score: " + std::to_string(score));
                            specialFive = true;
                        }

                        else if (sprites[highlighted_row][highlighted_col].getTexture() == &images[14] &&
                            sprites[highlighted_row + 1][highlighted_col - 1].getTexture() == &images[0] &&
                            sprites[highlighted_row + 1][highlighted_col - 2].getTexture() == &images[0] ||
                            sprites[highlighted_row][highlighted_col].getTexture() == &images[15] &&
                            sprites[highlighted_row + 1][highlighted_col - 1].getTexture() == &images[1] &&
                            sprites[highlighted_row + 1][highlighted_col - 2].getTexture() == &images[1] ||
                            sprites[highlighted_row][highlighted_col].getTexture() == &images[16] &&
                            sprites[highlighted_row + 1][highlighted_col - 1].getTexture() == &images[2] &&
                            sprites[highlighted_row + 1][highlighted_col - 2].getTexture() == &images[2] ||
                            sprites[highlighted_row][highlighted_col].getTexture() == &images[17] &&
                            sprites[highlighted_row + 1][highlighted_col - 1].getTexture() == &images[3] &&
                            sprites[highlighted_row + 1][highlighted_col - 2].getTexture() == &images[3] ||
                            sprites[highlighted_row][highlighted_col].getTexture() == &images[18] &&
                            sprites[highlighted_row + 1][highlighted_col - 1].getTexture() == &images[4] &&
                            sprites[highlighted_row + 1][highlighted_col - 2].getTexture() == &images[4] ||
                            sprites[highlighted_row][highlighted_col].getTexture() == &images[19] &&
                            sprites[highlighted_row + 1][highlighted_col - 1].getTexture() == &images[5] &&
                            sprites[highlighted_row + 1][highlighted_col - 2].getTexture() == &images[5] ||
                            sprites[highlighted_row][highlighted_col].getTexture() == &images[20] &&
                            sprites[highlighted_row + 1][highlighted_col - 1].getTexture() == &images[6] &&
                            sprites[highlighted_row + 1][highlighted_col - 2].getTexture() == &images[6])
                        {
                            specialRow = highlighted_row + 1;
                            specialCol = highlighted_col;


                            Sprite temp = sprites[highlighted_row][highlighted_col];
                            sprites[highlighted_row][highlighted_col] = sprites[highlighted_row + 1][highlighted_col];
                            sprites[highlighted_row + 1][highlighted_col] = temp;
                            // Update positions after swapping
                            sprites[highlighted_row][highlighted_col].setPosition((highlighted_col * gemSize) + off_setX, (highlighted_row * gemSize) + off_setY);
                            sprites[highlighted_row + 1][highlighted_col].setPosition((highlighted_col * gemSize) + off_setX, ((highlighted_row + 1) * gemSize) + off_setY);
                            score = score + score_5_special;
                            scoreText.setString("Score: " + std::to_string(score));
                            specialFive = true;
                        }

                        else if (sprites[highlighted_row][highlighted_col].getTexture() == &images[14] &&
                            sprites[highlighted_row + 1][highlighted_col - 1].getTexture() == &images[0] &&
                            sprites[highlighted_row + 1][highlighted_col + 1].getTexture() == &images[0] ||
                            sprites[highlighted_row][highlighted_col].getTexture() == &images[15] &&
                            sprites[highlighted_row + 1][highlighted_col - 1].getTexture() == &images[1] &&
                            sprites[highlighted_row + 1][highlighted_col + 1].getTexture() == &images[1] ||
                            sprites[highlighted_row][highlighted_col].getTexture() == &images[16] &&
                            sprites[highlighted_row + 1][highlighted_col - 1].getTexture() == &images[2] &&
                            sprites[highlighted_row + 1][highlighted_col + 1].getTexture() == &images[2] ||
                            sprites[highlighted_row][highlighted_col].getTexture() == &images[17] &&
                            sprites[highlighted_row + 1][highlighted_col - 1].getTexture() == &images[3] &&
                            sprites[highlighted_row + 1][highlighted_col + 1].getTexture() == &images[3] ||
                            sprites[highlighted_row][highlighted_col].getTexture() == &images[18] &&
                            sprites[highlighted_row + 1][highlighted_col - 1].getTexture() == &images[4] &&
                            sprites[highlighted_row + 1][highlighted_col + 1].getTexture() == &images[4] ||
                            sprites[highlighted_row][highlighted_col].getTexture() == &images[19] &&
                            sprites[highlighted_row + 1][highlighted_col - 1].getTexture() == &images[5] &&
                            sprites[highlighted_row + 1][highlighted_col + 1].getTexture() == &images[5] ||
                            sprites[highlighted_row][highlighted_col].getTexture() == &images[20] &&
                            sprites[highlighted_row + 1][highlighted_col - 1].getTexture() == &images[6] &&
                            sprites[highlighted_row + 1][highlighted_col + 1].getTexture() == &images[6])
                        {
                            specialRow = highlighted_row + 1;
                            specialCol = highlighted_col;

                            Sprite temp = sprites[highlighted_row][highlighted_col];
                            sprites[highlighted_row][highlighted_col] = sprites[highlighted_row + 1][highlighted_col];
                            sprites[highlighted_row + 1][highlighted_col] = temp;
                            // Update positions after swapping
                            sprites[highlighted_row][highlighted_col].setPosition((highlighted_col * gemSize) + off_setX, (highlighted_row * gemSize) + off_setY);
                            sprites[highlighted_row + 1][highlighted_col].setPosition((highlighted_col * gemSize) + off_setX, ((highlighted_row + 1) * gemSize) + off_setY);
                            score = score + score_5_special;
                            scoreText.setString("Score: " + std::to_string(score));
                            specialFive = true;
                        }

                        else if (sprites[highlighted_row][highlighted_col].getTexture() == &images[14] &&
                            sprites[highlighted_row + 2][highlighted_col].getTexture() == &images[0] &&
                            sprites[highlighted_row + 3][highlighted_col].getTexture() == &images[0] ||
                            sprites[highlighted_row][highlighted_col].getTexture() == &images[15] &&
                            sprites[highlighted_row + 2][highlighted_col].getTexture() == &images[1] &&
                            sprites[highlighted_row + 3][highlighted_col].getTexture() == &images[1] ||
                            sprites[highlighted_row][highlighted_col].getTexture() == &images[16] &&
                            sprites[highlighted_row + 2][highlighted_col].getTexture() == &images[2] &&
                            sprites[highlighted_row + 3][highlighted_col].getTexture() == &images[2] ||
                            sprites[highlighted_row][highlighted_col].getTexture() == &images[17] &&
                            sprites[highlighted_row + 2][highlighted_col].getTexture() == &images[3] &&
                            sprites[highlighted_row + 3][highlighted_col].getTexture() == &images[3] ||
                            sprites[highlighted_row][highlighted_col].getTexture() == &images[18] &&
                            sprites[highlighted_row + 2][highlighted_col].getTexture() == &images[4] &&
                            sprites[highlighted_row + 3][highlighted_col].getTexture() == &images[4] ||
                            sprites[highlighted_row][highlighted_col].getTexture() == &images[19] &&
                            sprites[highlighted_row + 2][highlighted_col].getTexture() == &images[5] &&
                            sprites[highlighted_row + 3][highlighted_col].getTexture() == &images[5] ||
                            sprites[highlighted_row][highlighted_col].getTexture() == &images[20] &&
                            sprites[highlighted_row + 2][highlighted_col].getTexture() == &images[6] &&
                            sprites[highlighted_row + 3][highlighted_col].getTexture() == &images[6])
                        {
                            specialRow = highlighted_row + 1;
                            specialCol = highlighted_col;


                            Sprite temp = sprites[highlighted_row][highlighted_col];
                            sprites[highlighted_row][highlighted_col] = sprites[highlighted_row + 1][highlighted_col];
                            sprites[highlighted_row + 1][highlighted_col] = temp;
                            // Update positions after swapping
                            sprites[highlighted_row][highlighted_col].setPosition((highlighted_col * gemSize) + off_setX, (highlighted_row * gemSize) + off_setY);
                            sprites[highlighted_row + 1][highlighted_col].setPosition((highlighted_col * gemSize) + off_setX, ((highlighted_row + 1) * gemSize) + off_setY);
                            score = score + score_5_special;
                            scoreText.setString("Score: " + std::to_string(score));
                            specialFive = true;
                        }

                    }

                    highlighted_row++;
                    enter_key_pressed = false;
                    swap_triggered = false;
                }

                else if (event.key.code == Keyboard::Left && highlighted_col > 0)
                {
                    if (enter_key_pressed && swap_triggered)
                    {//FIVE MATCHES
                        if (sprites[highlighted_row][highlighted_col].getTexture() == sprites[highlighted_row - 1][highlighted_col - 1].getTexture() &&
                            sprites[highlighted_row][highlighted_col].getTexture() == sprites[highlighted_row - 2][highlighted_col - 1].getTexture() &&
                            sprites[highlighted_row][highlighted_col].getTexture() == sprites[highlighted_row + 1][highlighted_col - 1].getTexture() &&
                            sprites[highlighted_row][highlighted_col].getTexture() == sprites[highlighted_row + 2][highlighted_col - 1].getTexture())
                        {
                            // storing indexes of the above position
                            indexLeft1 = highlighted_row;
                            indexLeft2 = highlighted_col - 1;

                            // storing the texture to temporary sprite
                            const Texture* texturePtr = sprites[highlighted_row][highlighted_col].getTexture();
                            tempSprites[indexLeft1][indexLeft2].setTexture(*texturePtr);

                            matchFiveLeft = true;

                            Sprite temp = sprites[highlighted_row][highlighted_col];
                            sprites[highlighted_row][highlighted_col] = sprites[highlighted_row][highlighted_col - 1];
                            sprites[highlighted_row][highlighted_col - 1] = temp;
                            // Update positions after swapping
                            sprites[highlighted_row][highlighted_col].setPosition((highlighted_col * gemSize) + off_setX, (highlighted_row * gemSize) + off_setY);
                            sprites[highlighted_row][highlighted_col - 1].setPosition(((highlighted_col - 1) * gemSize) + off_setX, ((highlighted_row)*gemSize) + off_setY);
                            score = score + score_5_matches;
                            scoreText.setString("Score: " + std::to_string(score));
                        }
                        //FOR FOUR MATCHES
                        else if ((sprites[highlighted_row][highlighted_col].getTexture() == sprites[highlighted_row - 1][highlighted_col - 1].getTexture() &&
                                  sprites[highlighted_row][highlighted_col].getTexture() == sprites[highlighted_row - 2][highlighted_col - 1].getTexture() &&
                                  sprites[highlighted_row][highlighted_col].getTexture() == sprites[highlighted_row + 1][highlighted_col - 1].getTexture()) ||
                                 (sprites[highlighted_row][highlighted_col].getTexture() == sprites[highlighted_row - 1][highlighted_col - 1].getTexture() &&
                                  sprites[highlighted_row][highlighted_col].getTexture() == sprites[highlighted_row + 1][highlighted_col - 1].getTexture() &&
                                  sprites[highlighted_row][highlighted_col].getTexture() == sprites[highlighted_row + 2][highlighted_col - 1].getTexture()))
                        {
                            // storing indexes of the above position
                            indexLeft1 = highlighted_row;
                            indexLeft2 = highlighted_col - 1;

                            // storing the texture to temporary sprite
                            const Texture* texturePtr = sprites[highlighted_row][highlighted_col].getTexture();
                            tempSprites[indexLeft1][indexLeft2].setTexture(*texturePtr);

                            matchFourLeft = true;
                            score = score + score_4_matches;
                            scoreText.setString("Score: " + std::to_string(score));
                            Sprite temp = sprites[highlighted_row][highlighted_col];
                            sprites[highlighted_row][highlighted_col] = sprites[highlighted_row][highlighted_col - 1];
                            sprites[highlighted_row][highlighted_col - 1] = temp;
                            // Update positions after swapping
                            sprites[highlighted_row][highlighted_col].setPosition((highlighted_col * gemSize) + off_setX, (highlighted_row * gemSize) + off_setY);
                            sprites[highlighted_row][highlighted_col - 1].setPosition(((highlighted_col - 1) * gemSize) + off_setX, ((highlighted_row)*gemSize) + off_setY);
                        }
                        //for elbow
                        else if (sprites[highlighted_row][highlighted_col].getTexture() == sprites[highlighted_row - 1][highlighted_col - 1].getTexture() &&
                            sprites[highlighted_row][highlighted_col].getTexture() == sprites[highlighted_row - 2][highlighted_col - 1].getTexture() &&
                            sprites[highlighted_row][highlighted_col].getTexture() == sprites[highlighted_row][highlighted_col - 2].getTexture() &&
                            sprites[highlighted_row][highlighted_col].getTexture() == sprites[highlighted_row][highlighted_col - 3].getTexture() ||
                            sprites[highlighted_row][highlighted_col].getTexture() == sprites[highlighted_row + 1][highlighted_col - 1].getTexture() &&
                            sprites[highlighted_row][highlighted_col].getTexture() == sprites[highlighted_row + 2][highlighted_col - 1].getTexture() &&
                            sprites[highlighted_row][highlighted_col].getTexture() == sprites[highlighted_row][highlighted_col - 2].getTexture() &&
                            sprites[highlighted_row][highlighted_col].getTexture() == sprites[highlighted_row][highlighted_col - 3].getTexture())
                        {
                            // storing indexes of the above position
                            indexLeft1 = highlighted_row;
                            indexLeft2 = highlighted_col - 1;

                            // storing the texture to temporary sprite
                            const Texture* texturePtr = sprites[highlighted_row][highlighted_col].getTexture();
                            tempSprites[indexLeft1][indexLeft2].setTexture(*texturePtr);

                            destroyLeft = true;
                            score = score + score_5_matches;
                            scoreText.setString("Score: " + std::to_string(score));
                            Sprite temp = sprites[highlighted_row][highlighted_col];
                            sprites[highlighted_row][highlighted_col] = sprites[highlighted_row][highlighted_col - 1];
                            sprites[highlighted_row][highlighted_col - 1] = temp;
                            // Update positions after swapping
                            sprites[highlighted_row][highlighted_col].setPosition((highlighted_col * gemSize) + off_setX, (highlighted_row * gemSize) + off_setY);
                            sprites[highlighted_row][highlighted_col - 1].setPosition(((highlighted_col - 1) * gemSize) + off_setX, ((highlighted_row)*gemSize) + off_setY);
                        }
                        else if (sprites[highlighted_row][highlighted_col].getTexture() == sprites[highlighted_row - 1][highlighted_col - 1].getTexture() &&
                            sprites[highlighted_row][highlighted_col].getTexture() == sprites[highlighted_row + 1][highlighted_col - 1].getTexture())
                        {
                            Sprite temp = sprites[highlighted_row][highlighted_col];
                            sprites[highlighted_row][highlighted_col] = sprites[highlighted_row][highlighted_col - 1];
                            sprites[highlighted_row][highlighted_col - 1] = temp;
                            // Update positions after swapping
                            sprites[highlighted_row][highlighted_col].setPosition((highlighted_col * gemSize) + off_setX, (highlighted_row * gemSize) + off_setY);
                            sprites[highlighted_row][highlighted_col - 1].setPosition(((highlighted_col - 1) * gemSize) + off_setX, ((highlighted_row)*gemSize) + off_setY);
                            score = score + score_3_matches;
                            scoreText.setString("Score: " + std::to_string(score));
                        }

                        else if (sprites[highlighted_row][highlighted_col].getTexture() == sprites[highlighted_row + 1][highlighted_col - 1].getTexture() &&
                            sprites[highlighted_row][highlighted_col].getTexture() == sprites[highlighted_row + 2][highlighted_col - 1].getTexture())
                        {
                            Sprite temp = sprites[highlighted_row][highlighted_col];
                            sprites[highlighted_row][highlighted_col] = sprites[highlighted_row][highlighted_col - 1];
                            sprites[highlighted_row][highlighted_col - 1] = temp;
                            // Update positions after swapping
                            sprites[highlighted_row][highlighted_col].setPosition((highlighted_col * gemSize) + off_setX, (highlighted_row * gemSize) + off_setY);
                            sprites[highlighted_row][highlighted_col - 1].setPosition(((highlighted_col - 1) * gemSize) + off_setX, ((highlighted_row)*gemSize) + off_setY);
                            score = score + score_3_matches;
                            scoreText.setString("Score: " + std::to_string(score));
                        }
                        else if (sprites[highlighted_row][highlighted_col].getTexture() == sprites[highlighted_row - 1][highlighted_col - 1].getTexture() &&
                            sprites[highlighted_row][highlighted_col].getTexture() == sprites[highlighted_row - 2][highlighted_col - 1].getTexture())
                        {
                            Sprite temp = sprites[highlighted_row][highlighted_col];
                            sprites[highlighted_row][highlighted_col] = sprites[highlighted_row][highlighted_col - 1];
                            sprites[highlighted_row][highlighted_col - 1] = temp;
                            // Update positions after swapping
                            sprites[highlighted_row][highlighted_col].setPosition((highlighted_col * gemSize) + off_setX, (highlighted_row * gemSize) + off_setY);
                            sprites[highlighted_row][highlighted_col - 1].setPosition(((highlighted_col - 1) * gemSize) + off_setX, ((highlighted_row)*gemSize) + off_setY);
                            score = score + score_3_matches;
                            scoreText.setString("Score: " + std::to_string(score));
                        }

                        else if (sprites[highlighted_row][highlighted_col].getTexture() == sprites[highlighted_row][highlighted_col - 2].getTexture() &&
                            sprites[highlighted_row][highlighted_col].getTexture() == sprites[highlighted_row][highlighted_col - 3].getTexture())
                        {
                            Sprite temp = sprites[highlighted_row][highlighted_col];
                            sprites[highlighted_row][highlighted_col] = sprites[highlighted_row][highlighted_col - 1];
                            sprites[highlighted_row][highlighted_col - 1] = temp;
                            // Update positions after swapping
                            sprites[highlighted_row][highlighted_col].setPosition((highlighted_col * gemSize) + off_setX, (highlighted_row * gemSize) + off_setY);
                            sprites[highlighted_row][highlighted_col - 1].setPosition(((highlighted_col - 1) * gemSize) + off_setX, ((highlighted_row)*gemSize) + off_setY);
                            score = score + score_3_matches;
                            scoreText.setString("Score: " + std::to_string(score));
                        }

                        else if ((sprites[highlighted_row][highlighted_col].getTexture() == &images[0] &&
                            sprites[highlighted_row - 1][highlighted_col - 1].getTexture() == &images[7] &&
                            sprites[highlighted_row - 2][highlighted_col - 1].getTexture() == &images[0]) ||
                            (sprites[highlighted_row][highlighted_col].getTexture() == &images[1] &&
                                sprites[highlighted_row - 1][highlighted_col - 1].getTexture() == &images[8] &&
                                sprites[highlighted_row - 2][highlighted_col - 1].getTexture() == &images[1]) ||
                            (sprites[highlighted_row][highlighted_col].getTexture() == &images[2] &&
                                sprites[highlighted_row - 1][highlighted_col - 1].getTexture() == &images[9] &&
                                (sprites[highlighted_row - 2][highlighted_col - 1].getTexture() == &images[2]) ||
                                sprites[highlighted_row][highlighted_col].getTexture() == &images[3] &&
                                sprites[highlighted_row - 1][highlighted_col - 1].getTexture() == &images[10] &&
                                sprites[highlighted_row - 2][highlighted_col - 1].getTexture() == &images[3]) ||
                            (sprites[highlighted_row][highlighted_col].getTexture() == &images[4] &&
                                sprites[highlighted_row - 1][highlighted_col - 1].getTexture() == &images[11] &&
                                sprites[highlighted_row - 2][highlighted_col - 1].getTexture() == &images[4]) ||
                            (sprites[highlighted_row][highlighted_col].getTexture() == &images[5] &&
                                sprites[highlighted_row - 1][highlighted_col - 1].getTexture() == &images[12] &&
                                sprites[highlighted_row - 2][highlighted_col - 1].getTexture() == &images[5]) ||
                            (sprites[highlighted_row][highlighted_col].getTexture() == &images[6] &&
                                sprites[highlighted_row - 1][highlighted_col - 1].getTexture() == &images[13] &&
                                sprites[highlighted_row - 2][highlighted_col - 1].getTexture() == &images[6]))
                        {
                            Sprite temp = sprites[highlighted_row][highlighted_col];
                            sprites[highlighted_row][highlighted_col] = sprites[highlighted_row][highlighted_col - 1];
                            sprites[highlighted_row][highlighted_col - 1] = temp;
                            // Update positions after swapping
                            sprites[highlighted_row][highlighted_col].setPosition((highlighted_col * gemSize) + off_setX, (highlighted_row * gemSize) + off_setY);
                            sprites[highlighted_row][highlighted_col - 1].setPosition(((highlighted_col - 1) * gemSize) + off_setX, ((highlighted_row)*gemSize) + off_setY);
                            score = score + score_4_special;
                            scoreText.setString("Score: " + std::to_string(score));
                            specialFourLeft1 = true;
                        }

                        else if ((sprites[highlighted_row][highlighted_col].getTexture() == &images[0] &&
                            sprites[highlighted_row - 1][highlighted_col - 1].getTexture() == &images[0] &&
                            sprites[highlighted_row - 2][highlighted_col - 1].getTexture() == &images[7]) ||
                            (sprites[highlighted_row][highlighted_col].getTexture() == &images[1] &&
                                sprites[highlighted_row - 1][highlighted_col - 1].getTexture() == &images[1] &&
                                sprites[highlighted_row - 2][highlighted_col - 1].getTexture() == &images[8]) ||
                            (sprites[highlighted_row][highlighted_col].getTexture() == &images[2] &&
                                sprites[highlighted_row - 1][highlighted_col - 1].getTexture() == &images[2] &&
                                (sprites[highlighted_row - 2][highlighted_col - 1].getTexture() == &images[9]) ||
                                sprites[highlighted_row][highlighted_col].getTexture() == &images[3] &&
                                sprites[highlighted_row - 1][highlighted_col - 1].getTexture() == &images[3] &&
                                sprites[highlighted_row - 2][highlighted_col - 1].getTexture() == &images[10]) ||
                            (sprites[highlighted_row][highlighted_col].getTexture() == &images[4] &&
                                sprites[highlighted_row - 1][highlighted_col - 1].getTexture() == &images[4] &&
                                sprites[highlighted_row - 2][highlighted_col - 1].getTexture() == &images[11]) ||
                            (sprites[highlighted_row][highlighted_col].getTexture() == &images[5] &&
                                sprites[highlighted_row - 1][highlighted_col - 1].getTexture() == &images[5] &&
                                sprites[highlighted_row - 2][highlighted_col - 1].getTexture() == &images[12]) ||
                            (sprites[highlighted_row][highlighted_col].getTexture() == &images[6] &&
                                sprites[highlighted_row - 1][highlighted_col - 1].getTexture() == &images[6] &&
                                sprites[highlighted_row - 2][highlighted_col - 1].getTexture() == &images[13]))
                        {
                            Sprite temp = sprites[highlighted_row][highlighted_col];
                            sprites[highlighted_row][highlighted_col] = sprites[highlighted_row][highlighted_col - 1];
                            sprites[highlighted_row][highlighted_col - 1] = temp;
                            // Update positions after swapping
                            sprites[highlighted_row][highlighted_col].setPosition((highlighted_col * gemSize) + off_setX, (highlighted_row * gemSize) + off_setY);
                            sprites[highlighted_row][highlighted_col - 1].setPosition(((highlighted_col - 1) * gemSize) + off_setX, ((highlighted_row)*gemSize) + off_setY);
                            score = score + score_4_special;
                            scoreText.setString("Score: " + std::to_string(score));
                            specialFourLeft2 = true;
                        }

                        else if ((sprites[highlighted_row][highlighted_col].getTexture() == &images[0] &&
                            sprites[highlighted_row + 1][highlighted_col - 1].getTexture() == &images[7] &&
                            sprites[highlighted_row + 2][highlighted_col - 1].getTexture() == &images[0]) ||
                            (sprites[highlighted_row][highlighted_col].getTexture() == &images[1] &&
                                sprites[highlighted_row + 1][highlighted_col - 1].getTexture() == &images[8] &&
                                sprites[highlighted_row + 2][highlighted_col - 1].getTexture() == &images[1]) ||
                            (sprites[highlighted_row][highlighted_col].getTexture() == &images[2] &&
                                sprites[highlighted_row + 1][highlighted_col - 1].getTexture() == &images[9] &&
                                (sprites[highlighted_row + 2][highlighted_col - 1].getTexture() == &images[2]) ||
                                sprites[highlighted_row][highlighted_col].getTexture() == &images[3] &&
                                sprites[highlighted_row + 1][highlighted_col - 1].getTexture() == &images[10] &&
                                sprites[highlighted_row + 2][highlighted_col - 1].getTexture() == &images[3]) ||
                            (sprites[highlighted_row][highlighted_col].getTexture() == &images[4] &&
                                sprites[highlighted_row + 1][highlighted_col - 1].getTexture() == &images[11] &&
                                sprites[highlighted_row + 2][highlighted_col - 1].getTexture() == &images[4]) ||
                            (sprites[highlighted_row][highlighted_col].getTexture() == &images[5] &&
                                sprites[highlighted_row + 1][highlighted_col - 1].getTexture() == &images[12] &&
                                sprites[highlighted_row + 2][highlighted_col - 1].getTexture() == &images[5]) ||
                            (sprites[highlighted_row][highlighted_col].getTexture() == &images[6] &&
                                sprites[highlighted_row + 1][highlighted_col - 1].getTexture() == &images[13] &&
                                sprites[highlighted_row + 2][highlighted_col - 1].getTexture() == &images[6]))
                        {
                            Sprite temp = sprites[highlighted_row][highlighted_col];
                            sprites[highlighted_row][highlighted_col] = sprites[highlighted_row][highlighted_col - 1];
                            sprites[highlighted_row][highlighted_col - 1] = temp;
                            // Update positions after swapping
                            sprites[highlighted_row][highlighted_col].setPosition((highlighted_col * gemSize) + off_setX, (highlighted_row * gemSize) + off_setY);
                            sprites[highlighted_row][highlighted_col - 1].setPosition(((highlighted_col - 1) * gemSize) + off_setX, ((highlighted_row)*gemSize) + off_setY);
                            score = score + score_4_special;
                            scoreText.setString("Score: " + std::to_string(score));
                            specialFourLeft3 = true;
                        }

                        else if ((sprites[highlighted_row][highlighted_col].getTexture() == &images[0] &&
                            sprites[highlighted_row + 1][highlighted_col - 1].getTexture() == &images[0] &&
                            sprites[highlighted_row + 2][highlighted_col - 1].getTexture() == &images[7]) ||
                            (sprites[highlighted_row][highlighted_col].getTexture() == &images[1] &&
                                sprites[highlighted_row + 1][highlighted_col - 1].getTexture() == &images[1] &&
                                sprites[highlighted_row + 2][highlighted_col - 1].getTexture() == &images[8]) ||
                            (sprites[highlighted_row][highlighted_col].getTexture() == &images[2] &&
                                sprites[highlighted_row + 1][highlighted_col - 1].getTexture() == &images[2] &&
                                (sprites[highlighted_row + 2][highlighted_col - 1].getTexture() == &images[9]) ||
                                sprites[highlighted_row][highlighted_col].getTexture() == &images[3] &&
                                sprites[highlighted_row + 1][highlighted_col - 1].getTexture() == &images[3] &&
                                sprites[highlighted_row + 2][highlighted_col - 1].getTexture() == &images[10]) ||
                            (sprites[highlighted_row][highlighted_col].getTexture() == &images[4] &&
                                sprites[highlighted_row + 1][highlighted_col - 1].getTexture() == &images[4] &&
                                sprites[highlighted_row + 2][highlighted_col - 1].getTexture() == &images[11]) ||
                            (sprites[highlighted_row][highlighted_col].getTexture() == &images[5] &&
                                sprites[highlighted_row + 1][highlighted_col - 1].getTexture() == &images[5] &&
                                sprites[highlighted_row + 2][highlighted_col - 1].getTexture() == &images[12]) ||
                            (sprites[highlighted_row][highlighted_col].getTexture() == &images[6] &&
                                sprites[highlighted_row + 1][highlighted_col - 1].getTexture() == &images[6] &&
                                sprites[highlighted_row + 2][highlighted_col - 1].getTexture() == &images[13]))
                        {
                            Sprite temp = sprites[highlighted_row][highlighted_col];
                            sprites[highlighted_row][highlighted_col] = sprites[highlighted_row][highlighted_col - 1];
                            sprites[highlighted_row][highlighted_col - 1] = temp;
                            // Update positions after swapping
                            sprites[highlighted_row][highlighted_col].setPosition((highlighted_col * gemSize) + off_setX, (highlighted_row * gemSize) + off_setY);
                            sprites[highlighted_row][highlighted_col - 1].setPosition(((highlighted_col - 1) * gemSize) + off_setX, ((highlighted_row)*gemSize) + off_setY);
                            score = score + score_4_special;
                            scoreText.setString("Score: " + std::to_string(score));
                            specialFourLeft4 = true;
                        }

                        else if ((sprites[highlighted_row][highlighted_col].getTexture() == &images[0] &&
                            sprites[highlighted_row + 1][highlighted_col - 1].getTexture() == &images[0] &&
                            sprites[highlighted_row - 1][highlighted_col - 1].getTexture() == &images[7]) ||
                            (sprites[highlighted_row][highlighted_col].getTexture() == &images[1] &&
                                sprites[highlighted_row + 1][highlighted_col - 1].getTexture() == &images[1] &&
                                sprites[highlighted_row - 1][highlighted_col - 1].getTexture() == &images[8]) ||
                            (sprites[highlighted_row][highlighted_col].getTexture() == &images[2] &&
                                sprites[highlighted_row + 1][highlighted_col - 1].getTexture() == &images[2] &&
                                (sprites[highlighted_row - 1][highlighted_col - 1].getTexture() == &images[9]) ||
                                sprites[highlighted_row][highlighted_col].getTexture() == &images[3] &&
                                sprites[highlighted_row + 1][highlighted_col - 1].getTexture() == &images[3] &&
                                sprites[highlighted_row - 1][highlighted_col - 1].getTexture() == &images[10]) ||
                            (sprites[highlighted_row][highlighted_col].getTexture() == &images[4] &&
                                sprites[highlighted_row + 1][highlighted_col - 1].getTexture() == &images[4] &&
                                sprites[highlighted_row - 1][highlighted_col - 1].getTexture() == &images[11]) ||
                            (sprites[highlighted_row][highlighted_col].getTexture() == &images[5] &&
                                sprites[highlighted_row + 1][highlighted_col - 1].getTexture() == &images[5] &&
                                sprites[highlighted_row - 1][highlighted_col - 1].getTexture() == &images[12]) ||
                            (sprites[highlighted_row][highlighted_col].getTexture() == &images[6] &&
                                sprites[highlighted_row + 1][highlighted_col - 1].getTexture() == &images[6] &&
                                sprites[highlighted_row - 1][highlighted_col - 1].getTexture() == &images[13]))
                        {
                            Sprite temp = sprites[highlighted_row][highlighted_col];
                            sprites[highlighted_row][highlighted_col] = sprites[highlighted_row][highlighted_col - 1];
                            sprites[highlighted_row][highlighted_col - 1] = temp;
                            // Update positions after swapping
                            sprites[highlighted_row][highlighted_col].setPosition((highlighted_col * gemSize) + off_setX, (highlighted_row * gemSize) + off_setY);
                            sprites[highlighted_row][highlighted_col - 1].setPosition(((highlighted_col - 1) * gemSize) + off_setX, ((highlighted_row)*gemSize) + off_setY);
                            score = score + score_4_special;
                            scoreText.setString("Score: " + std::to_string(score));
                            specialFourLeft5 = true;
                        }

                        else if ((sprites[highlighted_row][highlighted_col].getTexture() == &images[0] &&
                            sprites[highlighted_row + 1][highlighted_col - 1].getTexture() == &images[7] &&
                            sprites[highlighted_row - 1][highlighted_col - 1].getTexture() == &images[0]) ||
                            (sprites[highlighted_row][highlighted_col].getTexture() == &images[1] &&
                                sprites[highlighted_row + 1][highlighted_col - 1].getTexture() == &images[8] &&
                                sprites[highlighted_row - 1][highlighted_col - 1].getTexture() == &images[1]) ||
                            (sprites[highlighted_row][highlighted_col].getTexture() == &images[2] &&
                                sprites[highlighted_row + 1][highlighted_col - 1].getTexture() == &images[9] &&
                                (sprites[highlighted_row - 1][highlighted_col - 1].getTexture() == &images[2]) ||
                                sprites[highlighted_row][highlighted_col].getTexture() == &images[3] &&
                                sprites[highlighted_row + 1][highlighted_col - 1].getTexture() == &images[10] &&
                                sprites[highlighted_row - 1][highlighted_col - 1].getTexture() == &images[3]) ||
                            (sprites[highlighted_row][highlighted_col].getTexture() == &images[4] &&
                                sprites[highlighted_row + 1][highlighted_col - 1].getTexture() == &images[11] &&
                                sprites[highlighted_row - 1][highlighted_col - 1].getTexture() == &images[4]) ||
                            (sprites[highlighted_row][highlighted_col].getTexture() == &images[5] &&
                                sprites[highlighted_row + 1][highlighted_col - 1].getTexture() == &images[12] &&
                                sprites[highlighted_row - 1][highlighted_col - 1].getTexture() == &images[5]) ||
                            (sprites[highlighted_row][highlighted_col].getTexture() == &images[6] &&
                                sprites[highlighted_row + 1][highlighted_col - 1].getTexture() == &images[13] &&
                                sprites[highlighted_row - 1][highlighted_col - 1].getTexture() == &images[6]))
                        {
                            Sprite temp = sprites[highlighted_row][highlighted_col];
                            sprites[highlighted_row][highlighted_col] = sprites[highlighted_row][highlighted_col - 1];
                            sprites[highlighted_row][highlighted_col - 1] = temp;
                            // Update positions after swapping
                            sprites[highlighted_row][highlighted_col].setPosition((highlighted_col * gemSize) + off_setX, (highlighted_row * gemSize) + off_setY);
                            sprites[highlighted_row][highlighted_col - 1].setPosition(((highlighted_col - 1) * gemSize) + off_setX, ((highlighted_row)*gemSize) + off_setY);
                            score = score + score_4_special;
                            scoreText.setString("Score: " + std::to_string(score));
                            specialFourLeft6 = true;
                        }

                        else if ((sprites[highlighted_row][highlighted_col].getTexture() == &images[7] &&
                            sprites[highlighted_row - 1][highlighted_col - 1].getTexture() == &images[0] &&
                            sprites[highlighted_row - 2][highlighted_col - 1].getTexture() == &images[0]) ||
                            (sprites[highlighted_row][highlighted_col].getTexture() == &images[8] &&
                                sprites[highlighted_row - 1][highlighted_col - 1].getTexture() == &images[1] &&
                                sprites[highlighted_row - 2][highlighted_col - 1].getTexture() == &images[1]) ||
                            (sprites[highlighted_row][highlighted_col].getTexture() == &images[9] &&
                                sprites[highlighted_row - 1][highlighted_col - 1].getTexture() == &images[2] &&
                                (sprites[highlighted_row - 2][highlighted_col - 1].getTexture() == &images[2]) ||
                                sprites[highlighted_row][highlighted_col].getTexture() == &images[10] &&
                                sprites[highlighted_row - 1][highlighted_col - 1].getTexture() == &images[3] &&
                                sprites[highlighted_row - 2][highlighted_col - 1].getTexture() == &images[3]) ||
                            (sprites[highlighted_row][highlighted_col].getTexture() == &images[11] &&
                                sprites[highlighted_row - 1][highlighted_col - 1].getTexture() == &images[4] &&
                                sprites[highlighted_row - 2][highlighted_col - 1].getTexture() == &images[4]) ||
                            (sprites[highlighted_row][highlighted_col].getTexture() == &images[12] &&
                                sprites[highlighted_row - 1][highlighted_col - 1].getTexture() == &images[5] &&
                                sprites[highlighted_row - 2][highlighted_col - 1].getTexture() == &images[5]) ||
                            (sprites[highlighted_row][highlighted_col].getTexture() == &images[13] &&
                                sprites[highlighted_row - 1][highlighted_col - 1].getTexture() == &images[6] &&
                                sprites[highlighted_row - 2][highlighted_col - 1].getTexture() == &images[6]))
                        {
                            Sprite temp = sprites[highlighted_row][highlighted_col];
                            sprites[highlighted_row][highlighted_col] = sprites[highlighted_row][highlighted_col - 1];
                            sprites[highlighted_row][highlighted_col - 1] = temp;
                            // Update positions after swapping
                            sprites[highlighted_row][highlighted_col].setPosition((highlighted_col * gemSize) + off_setX, (highlighted_row * gemSize) + off_setY);
                            sprites[highlighted_row][highlighted_col - 1].setPosition(((highlighted_col - 1) * gemSize) + off_setX, ((highlighted_row)*gemSize) + off_setY);
                            score = score + score_4_special;
                            scoreText.setString("Score: " + std::to_string(score));
                            specialRealFourLeft = true;
                        }

                        else if ((sprites[highlighted_row][highlighted_col].getTexture() == &images[7] &&
                            sprites[highlighted_row + 1][highlighted_col - 1].getTexture() == &images[0] &&
                            sprites[highlighted_row + 2][highlighted_col - 1].getTexture() == &images[0]) ||
                            (sprites[highlighted_row][highlighted_col].getTexture() == &images[8] &&
                                sprites[highlighted_row + 1][highlighted_col - 1].getTexture() == &images[1] &&
                                sprites[highlighted_row + 2][highlighted_col - 1].getTexture() == &images[1]) ||
                            (sprites[highlighted_row][highlighted_col].getTexture() == &images[9] &&
                                sprites[highlighted_row + 1][highlighted_col - 1].getTexture() == &images[2] &&
                                (sprites[highlighted_row + 2][highlighted_col - 1].getTexture() == &images[2]) ||
                                sprites[highlighted_row][highlighted_col].getTexture() == &images[10] &&
                                sprites[highlighted_row + 1][highlighted_col - 1].getTexture() == &images[3] &&
                                sprites[highlighted_row + 2][highlighted_col - 1].getTexture() == &images[3]) ||
                            (sprites[highlighted_row][highlighted_col].getTexture() == &images[11] &&
                                sprites[highlighted_row + 1][highlighted_col - 1].getTexture() == &images[4] &&
                                sprites[highlighted_row + 2][highlighted_col - 1].getTexture() == &images[4]) ||
                            (sprites[highlighted_row][highlighted_col].getTexture() == &images[12] &&
                                sprites[highlighted_row + 1][highlighted_col - 1].getTexture() == &images[5] &&
                                sprites[highlighted_row + 2][highlighted_col - 1].getTexture() == &images[5]) ||
                            (sprites[highlighted_row][highlighted_col].getTexture() == &images[13] &&
                                sprites[highlighted_row + 1][highlighted_col - 1].getTexture() == &images[6] &&
                                sprites[highlighted_row + 2][highlighted_col - 1].getTexture() == &images[6]))
                        {
                            Sprite temp = sprites[highlighted_row][highlighted_col];
                            sprites[highlighted_row][highlighted_col] = sprites[highlighted_row][highlighted_col - 1];
                            sprites[highlighted_row][highlighted_col - 1] = temp;
                            // Update positions after swapping
                            sprites[highlighted_row][highlighted_col].setPosition((highlighted_col * gemSize) + off_setX, (highlighted_row * gemSize) + off_setY);
                            sprites[highlighted_row][highlighted_col - 1].setPosition(((highlighted_col - 1) * gemSize) + off_setX, ((highlighted_row)*gemSize) + off_setY);
                            score = score + score_4_special;
                            scoreText.setString("Score: " + std::to_string(score));
                            specialRealFourLeft = true;
                        }


                        else if ((sprites[highlighted_row][highlighted_col].getTexture() == &images[7] &&
                            sprites[highlighted_row + 1][highlighted_col - 1].getTexture() == &images[0] &&
                            sprites[highlighted_row - 1][highlighted_col - 1].getTexture() == &images[0]) ||
                            (sprites[highlighted_row][highlighted_col].getTexture() == &images[8] &&
                                sprites[highlighted_row + 1][highlighted_col - 1].getTexture() == &images[1] &&
                                sprites[highlighted_row - 1][highlighted_col - 1].getTexture() == &images[1]) ||
                            (sprites[highlighted_row][highlighted_col].getTexture() == &images[9] &&
                                sprites[highlighted_row + 1][highlighted_col - 1].getTexture() == &images[2] &&
                                (sprites[highlighted_row - 1][highlighted_col - 1].getTexture() == &images[2]) ||
                                sprites[highlighted_row][highlighted_col].getTexture() == &images[10] &&
                                sprites[highlighted_row + 1][highlighted_col - 1].getTexture() == &images[3] &&
                                sprites[highlighted_row - 1][highlighted_col - 1].getTexture() == &images[3]) ||
                            (sprites[highlighted_row][highlighted_col].getTexture() == &images[11] &&
                                sprites[highlighted_row + 1][highlighted_col - 1].getTexture() == &images[4] &&
                                sprites[highlighted_row - 1][highlighted_col - 1].getTexture() == &images[4]) ||
                            (sprites[highlighted_row][highlighted_col].getTexture() == &images[12] &&
                                sprites[highlighted_row + 1][highlighted_col - 1].getTexture() == &images[5] &&
                                sprites[highlighted_row - 1][highlighted_col - 1].getTexture() == &images[5]) ||
                            (sprites[highlighted_row][highlighted_col].getTexture() == &images[13] &&
                                sprites[highlighted_row + 1][highlighted_col - 1].getTexture() == &images[6] &&
                                sprites[highlighted_row - 1][highlighted_col - 1].getTexture() == &images[6]))
                        {
                            Sprite temp = sprites[highlighted_row][highlighted_col];
                            sprites[highlighted_row][highlighted_col] = sprites[highlighted_row][highlighted_col - 1];
                            sprites[highlighted_row][highlighted_col - 1] = temp;
                            // Update positions after swapping
                            sprites[highlighted_row][highlighted_col].setPosition((highlighted_col * gemSize) + off_setX, (highlighted_row * gemSize) + off_setY);
                            sprites[highlighted_row][highlighted_col - 1].setPosition(((highlighted_col - 1) * gemSize) + off_setX, ((highlighted_row)*gemSize) + off_setY);
                            score = score + score_4_special;
                            scoreText.setString("Score: " + std::to_string(score));
                            specialRealFourLeft = true;
                        }

                        else if ((sprites[highlighted_row][highlighted_col].getTexture() == &images[7] &&
                                  sprites[highlighted_row][highlighted_col - 2].getTexture() == &images[0] &&
                                  sprites[highlighted_row][highlighted_col - 3].getTexture() == &images[0]) ||
                                 (sprites[highlighted_row][highlighted_col].getTexture() == &images[8] &&
                                  sprites[highlighted_row][highlighted_col - 2].getTexture() == &images[1] &&
                                  sprites[highlighted_row][highlighted_col - 3].getTexture() == &images[1]) ||
                                 (sprites[highlighted_row][highlighted_col].getTexture() == &images[9] &&
                                  sprites[highlighted_row][highlighted_col - 2].getTexture() == &images[2] &&
                                 (sprites[highlighted_row][highlighted_col - 3].getTexture() == &images[2]) ||
                                  sprites[highlighted_row][highlighted_col].getTexture() == &images[10] &&
                                  sprites[highlighted_row][highlighted_col - 2].getTexture() == &images[3] &&
                                  sprites[highlighted_row][highlighted_col - 3].getTexture() == &images[3]) ||
                                 (sprites[highlighted_row][highlighted_col].getTexture() == &images[11] &&
                                  sprites[highlighted_row][highlighted_col - 2].getTexture() == &images[4] &&
                                  sprites[highlighted_row][highlighted_col - 3].getTexture() == &images[4]) ||
                                 (sprites[highlighted_row][highlighted_col].getTexture() == &images[12] &&
                                  sprites[highlighted_row][highlighted_col - 2].getTexture() == &images[5] &&
                                  sprites[highlighted_row][highlighted_col - 3].getTexture() == &images[5]) ||
                                 (sprites[highlighted_row][highlighted_col].getTexture() == &images[13] &&
                                  sprites[highlighted_row][highlighted_col - 2].getTexture() == &images[6] &&
                                  sprites[highlighted_row][highlighted_col - 3].getTexture() == &images[6]))
                        {
                            Sprite temp = sprites[highlighted_row][highlighted_col];
                            sprites[highlighted_row][highlighted_col] = sprites[highlighted_row][highlighted_col - 1];
                            sprites[highlighted_row][highlighted_col - 1] = temp;
                            // Update positions after swapping
                            sprites[highlighted_row][highlighted_col].setPosition((highlighted_col * gemSize) + off_setX, (highlighted_row * gemSize) + off_setY);
                            sprites[highlighted_row][highlighted_col - 1].setPosition(((highlighted_col - 1) * gemSize) + off_setX, ((highlighted_row)*gemSize) + off_setY);
                            score = score + score_4_special;
                            scoreText.setString("Score: " + std::to_string(score));
                            specialRealFourLeft = true;
                        }
                        //five effect
                        else if ((sprites[highlighted_row][highlighted_col].getTexture() == &images[0] &&
                                  sprites[highlighted_row - 1][highlighted_col - 1].getTexture() == &images[14] &&
                                  sprites[highlighted_row - 2][highlighted_col - 1].getTexture() == &images[0]) ||
                                 (sprites[highlighted_row][highlighted_col].getTexture() == &images[1] &&
                                  sprites[highlighted_row - 1][highlighted_col - 1].getTexture() == &images[15] &&
                                  sprites[highlighted_row - 2][highlighted_col - 1].getTexture() == &images[1]) ||
                                 (sprites[highlighted_row][highlighted_col].getTexture() == &images[2] &&
                                  sprites[highlighted_row - 1][highlighted_col - 1].getTexture() == &images[16] &&
                                 (sprites[highlighted_row - 2][highlighted_col - 1].getTexture() == &images[2]) ||
                                  sprites[highlighted_row][highlighted_col].getTexture() == &images[3] &&
                                  sprites[highlighted_row - 1][highlighted_col - 1].getTexture() == &images[17] &&
                                  sprites[highlighted_row - 2][highlighted_col - 1].getTexture() == &images[3]) ||
                                 (sprites[highlighted_row][highlighted_col].getTexture() == &images[4] &&
                                  sprites[highlighted_row - 1][highlighted_col - 1].getTexture() == &images[18] &&
                                  sprites[highlighted_row - 2][highlighted_col - 1].getTexture() == &images[4]) ||
                                 (sprites[highlighted_row][highlighted_col].getTexture() == &images[5] &&
                                  sprites[highlighted_row - 1][highlighted_col - 1].getTexture() == &images[19] &&
                                  sprites[highlighted_row - 2][highlighted_col - 1].getTexture() == &images[5]) ||
                                 (sprites[highlighted_row][highlighted_col].getTexture() == &images[6] &&
                                  sprites[highlighted_row - 1][highlighted_col - 1].getTexture() == &images[20] &&
                                  sprites[highlighted_row - 2][highlighted_col - 1].getTexture() == &images[6]))
                        {
                            specialRow = highlighted_row - 1;
                            specialCol = highlighted_col - 1;


                            Sprite temp = sprites[highlighted_row][highlighted_col];
                            sprites[highlighted_row][highlighted_col] = sprites[highlighted_row][highlighted_col - 1];
                            sprites[highlighted_row][highlighted_col - 1] = temp;
                            // Update positions after swapping
                            sprites[highlighted_row][highlighted_col].setPosition((highlighted_col * gemSize) + off_setX, (highlighted_row * gemSize) + off_setY);
                            sprites[highlighted_row][highlighted_col - 1].setPosition(((highlighted_col - 1) * gemSize) + off_setX, ((highlighted_row)*gemSize) + off_setY);
                            score = score + score_5_special;
                            scoreText.setString("Score: " + std::to_string(score));
                            specialFive = true;
                        }

                        else if ((sprites[highlighted_row][highlighted_col].getTexture() == &images[0] &&
                                  sprites[highlighted_row - 1][highlighted_col - 1].getTexture() == &images[0] &&
                                  sprites[highlighted_row - 2][highlighted_col - 1].getTexture() == &images[14]) ||
                                 (sprites[highlighted_row][highlighted_col].getTexture() == &images[1] &&
                                  sprites[highlighted_row - 1][highlighted_col - 1].getTexture() == &images[1] &&
                                  sprites[highlighted_row - 2][highlighted_col - 1].getTexture() == &images[15]) ||
                                 (sprites[highlighted_row][highlighted_col].getTexture() == &images[2] &&
                                  sprites[highlighted_row - 1][highlighted_col - 1].getTexture() == &images[2] &&
                                 (sprites[highlighted_row - 2][highlighted_col - 1].getTexture() == &images[16]) ||
                                  sprites[highlighted_row][highlighted_col].getTexture() == &images[3] &&
                                  sprites[highlighted_row - 1][highlighted_col - 1].getTexture() == &images[3] &&
                                  sprites[highlighted_row - 2][highlighted_col - 1].getTexture() == &images[17]) ||
                                 (sprites[highlighted_row][highlighted_col].getTexture() == &images[4] &&
                                  sprites[highlighted_row - 1][highlighted_col - 1].getTexture() == &images[4] &&
                                  sprites[highlighted_row - 2][highlighted_col - 1].getTexture() == &images[18]) ||
                                 (sprites[highlighted_row][highlighted_col].getTexture() == &images[5] &&
                                  sprites[highlighted_row - 1][highlighted_col - 1].getTexture() == &images[5] &&
                                  sprites[highlighted_row - 2][highlighted_col - 1].getTexture() == &images[19]) ||
                                 (sprites[highlighted_row][highlighted_col].getTexture() == &images[6] &&
                                  sprites[highlighted_row - 1][highlighted_col - 1].getTexture() == &images[6] &&
                                  sprites[highlighted_row - 2][highlighted_col - 1].getTexture() == &images[20]))
                        {
                            specialRow = highlighted_row - 2;
                            specialCol = highlighted_col - 1;


                            Sprite temp = sprites[highlighted_row][highlighted_col];
                            sprites[highlighted_row][highlighted_col] = sprites[highlighted_row][highlighted_col - 1];
                            sprites[highlighted_row][highlighted_col - 1] = temp;
                            // Update positions after swapping
                            sprites[highlighted_row][highlighted_col].setPosition((highlighted_col * gemSize) + off_setX, (highlighted_row * gemSize) + off_setY);
                            sprites[highlighted_row][highlighted_col - 1].setPosition(((highlighted_col - 1) * gemSize) + off_setX, ((highlighted_row)*gemSize) + off_setY);
                            score = score + score_5_special;
                            scoreText.setString("Score: " + std::to_string(score));
                            specialFive = true;
                        }

                        else if ((sprites[highlighted_row][highlighted_col].getTexture() == &images[0] &&
                            sprites[highlighted_row + 1][highlighted_col - 1].getTexture() == &images[14] &&
                            sprites[highlighted_row + 2][highlighted_col - 1].getTexture() == &images[0]) ||
                            (sprites[highlighted_row][highlighted_col].getTexture() == &images[1] &&
                                sprites[highlighted_row + 1][highlighted_col - 1].getTexture() == &images[15] &&
                                sprites[highlighted_row + 2][highlighted_col - 1].getTexture() == &images[1]) ||
                            (sprites[highlighted_row][highlighted_col].getTexture() == &images[2] &&
                                sprites[highlighted_row + 1][highlighted_col - 1].getTexture() == &images[16] &&
                                (sprites[highlighted_row + 2][highlighted_col - 1].getTexture() == &images[2]) ||
                                sprites[highlighted_row][highlighted_col].getTexture() == &images[3] &&
                                sprites[highlighted_row + 1][highlighted_col - 1].getTexture() == &images[17] &&
                                sprites[highlighted_row + 2][highlighted_col - 1].getTexture() == &images[3]) ||
                            (sprites[highlighted_row][highlighted_col].getTexture() == &images[4] &&
                                sprites[highlighted_row + 1][highlighted_col - 1].getTexture() == &images[18] &&
                                sprites[highlighted_row + 2][highlighted_col - 1].getTexture() == &images[4]) ||
                            (sprites[highlighted_row][highlighted_col].getTexture() == &images[5] &&
                                sprites[highlighted_row + 1][highlighted_col - 1].getTexture() == &images[19] &&
                                sprites[highlighted_row + 2][highlighted_col - 1].getTexture() == &images[5]) ||
                            (sprites[highlighted_row][highlighted_col].getTexture() == &images[6] &&
                                sprites[highlighted_row + 1][highlighted_col - 1].getTexture() == &images[20] &&
                                sprites[highlighted_row + 2][highlighted_col - 1].getTexture() == &images[6]))
                        {
                            specialRow = highlighted_row + 1;
                            specialCol = highlighted_col - 1;


                            Sprite temp = sprites[highlighted_row][highlighted_col];
                            sprites[highlighted_row][highlighted_col] = sprites[highlighted_row][highlighted_col - 1];
                            sprites[highlighted_row][highlighted_col - 1] = temp;
                            // Update positions after swapping
                            sprites[highlighted_row][highlighted_col].setPosition((highlighted_col * gemSize) + off_setX, (highlighted_row * gemSize) + off_setY);
                            sprites[highlighted_row][highlighted_col - 1].setPosition(((highlighted_col - 1) * gemSize) + off_setX, ((highlighted_row)*gemSize) + off_setY);
                            score = score + score_5_special;
                            scoreText.setString("Score: " + std::to_string(score));
                            specialFive = true;
                        }

                        else if ((sprites[highlighted_row][highlighted_col].getTexture() == &images[0] &&
                            sprites[highlighted_row + 1][highlighted_col - 1].getTexture() == &images[0] &&
                            sprites[highlighted_row + 2][highlighted_col - 1].getTexture() == &images[14]) ||
                            (sprites[highlighted_row][highlighted_col].getTexture() == &images[1] &&
                                sprites[highlighted_row + 1][highlighted_col - 1].getTexture() == &images[1] &&
                                sprites[highlighted_row + 2][highlighted_col - 1].getTexture() == &images[15]) ||
                            (sprites[highlighted_row][highlighted_col].getTexture() == &images[2] &&
                                sprites[highlighted_row + 1][highlighted_col - 1].getTexture() == &images[2] &&
                                (sprites[highlighted_row + 2][highlighted_col - 1].getTexture() == &images[16]) ||
                                sprites[highlighted_row][highlighted_col].getTexture() == &images[3] &&
                                sprites[highlighted_row + 1][highlighted_col - 1].getTexture() == &images[3] &&
                                sprites[highlighted_row + 2][highlighted_col - 1].getTexture() == &images[17]) ||
                            (sprites[highlighted_row][highlighted_col].getTexture() == &images[4] &&
                                sprites[highlighted_row + 1][highlighted_col - 1].getTexture() == &images[4] &&
                                sprites[highlighted_row + 2][highlighted_col - 1].getTexture() == &images[18]) ||
                            (sprites[highlighted_row][highlighted_col].getTexture() == &images[5] &&
                                sprites[highlighted_row + 1][highlighted_col - 1].getTexture() == &images[5] &&
                                sprites[highlighted_row + 2][highlighted_col - 1].getTexture() == &images[19]) ||
                            (sprites[highlighted_row][highlighted_col].getTexture() == &images[6] &&
                                sprites[highlighted_row + 1][highlighted_col - 1].getTexture() == &images[6] &&
                                sprites[highlighted_row + 2][highlighted_col - 1].getTexture() == &images[20]))
                        {
                            specialRow = highlighted_row + 2;
                            specialCol = highlighted_col - 1;


                            Sprite temp = sprites[highlighted_row][highlighted_col];
                            sprites[highlighted_row][highlighted_col] = sprites[highlighted_row][highlighted_col - 1];
                            sprites[highlighted_row][highlighted_col - 1] = temp;
                            // Update positions after swapping
                            sprites[highlighted_row][highlighted_col].setPosition((highlighted_col * gemSize) + off_setX, (highlighted_row * gemSize) + off_setY);
                            sprites[highlighted_row][highlighted_col - 1].setPosition(((highlighted_col - 1) * gemSize) + off_setX, ((highlighted_row)*gemSize) + off_setY);
                            score = score + score_5_special;
                            scoreText.setString("Score: " + std::to_string(score));
                            specialFive = true;
                        }

                        else if ((sprites[highlighted_row][highlighted_col].getTexture() == &images[0] &&
                                  sprites[highlighted_row + 1][highlighted_col - 1].getTexture() == &images[0] &&
                                  sprites[highlighted_row - 1][highlighted_col - 1].getTexture() == &images[14]) ||
                                 (sprites[highlighted_row][highlighted_col].getTexture() == &images[1] &&
                                  sprites[highlighted_row + 1][highlighted_col - 1].getTexture() == &images[1] &&
                                  sprites[highlighted_row - 1][highlighted_col - 1].getTexture() == &images[15]) ||
                                 (sprites[highlighted_row][highlighted_col].getTexture() == &images[2] &&
                                  sprites[highlighted_row + 1][highlighted_col - 1].getTexture() == &images[2] &&
                                 (sprites[highlighted_row - 1][highlighted_col - 1].getTexture() == &images[16]) ||
                                  sprites[highlighted_row][highlighted_col].getTexture() == &images[3] &&
                                  sprites[highlighted_row + 1][highlighted_col - 1].getTexture() == &images[3] &&
                                  sprites[highlighted_row - 1][highlighted_col - 1].getTexture() == &images[17]) ||
                                 (sprites[highlighted_row][highlighted_col].getTexture() == &images[4] &&
                                  sprites[highlighted_row + 1][highlighted_col - 1].getTexture() == &images[4] &&
                                  sprites[highlighted_row - 1][highlighted_col - 1].getTexture() == &images[18]) ||
                                 (sprites[highlighted_row][highlighted_col].getTexture() == &images[5] &&
                                  sprites[highlighted_row + 1][highlighted_col - 1].getTexture() == &images[5] &&
                                  sprites[highlighted_row - 1][highlighted_col - 1].getTexture() == &images[19]) ||
                                 (sprites[highlighted_row][highlighted_col].getTexture() == &images[6] &&
                                  sprites[highlighted_row + 1][highlighted_col - 1].getTexture() == &images[6] &&
                                  sprites[highlighted_row - 1][highlighted_col - 1].getTexture() == &images[20]))
                        {
                            specialRow = highlighted_row - 1;
                            specialCol = highlighted_col - 1;


                            Sprite temp = sprites[highlighted_row][highlighted_col];
                            sprites[highlighted_row][highlighted_col] = sprites[highlighted_row][highlighted_col - 1];
                            sprites[highlighted_row][highlighted_col - 1] = temp;
                            // Update positions after swapping
                            sprites[highlighted_row][highlighted_col].setPosition((highlighted_col * gemSize) + off_setX, (highlighted_row * gemSize) + off_setY);
                            sprites[highlighted_row][highlighted_col - 1].setPosition(((highlighted_col - 1) * gemSize) + off_setX, ((highlighted_row)*gemSize) + off_setY);
                            score = score + score_5_special;
                            scoreText.setString("Score: " + std::to_string(score));
                            specialFive = true;
                        }

                        else if ((sprites[highlighted_row][highlighted_col].getTexture() == &images[0] &&
                            sprites[highlighted_row + 1][highlighted_col - 1].getTexture() == &images[14] &&
                            sprites[highlighted_row - 1][highlighted_col - 1].getTexture() == &images[0]) ||
                            (sprites[highlighted_row][highlighted_col].getTexture() == &images[1] &&
                                sprites[highlighted_row + 1][highlighted_col - 1].getTexture() == &images[15] &&
                                sprites[highlighted_row - 1][highlighted_col - 1].getTexture() == &images[1]) ||
                            (sprites[highlighted_row][highlighted_col].getTexture() == &images[2] &&
                                sprites[highlighted_row + 1][highlighted_col - 1].getTexture() == &images[16] &&
                                (sprites[highlighted_row - 1][highlighted_col - 1].getTexture() == &images[2]) ||
                                sprites[highlighted_row][highlighted_col].getTexture() == &images[3] &&
                                sprites[highlighted_row + 1][highlighted_col - 1].getTexture() == &images[17] &&
                                sprites[highlighted_row - 1][highlighted_col - 1].getTexture() == &images[3]) ||
                            (sprites[highlighted_row][highlighted_col].getTexture() == &images[4] &&
                                sprites[highlighted_row + 1][highlighted_col - 1].getTexture() == &images[18] &&
                                sprites[highlighted_row - 1][highlighted_col - 1].getTexture() == &images[4]) ||
                            (sprites[highlighted_row][highlighted_col].getTexture() == &images[5] &&
                                sprites[highlighted_row + 1][highlighted_col - 1].getTexture() == &images[19] &&
                                sprites[highlighted_row - 1][highlighted_col - 1].getTexture() == &images[5]) ||
                            (sprites[highlighted_row][highlighted_col].getTexture() == &images[6] &&
                                sprites[highlighted_row + 1][highlighted_col - 1].getTexture() == &images[20] &&
                                sprites[highlighted_row - 1][highlighted_col - 1].getTexture() == &images[6]))
                        {
                            specialRow = highlighted_row + 1;
                            specialCol = highlighted_col - 1;


                            Sprite temp = sprites[highlighted_row][highlighted_col];
                            sprites[highlighted_row][highlighted_col] = sprites[highlighted_row][highlighted_col - 1];
                            sprites[highlighted_row][highlighted_col - 1] = temp;
                            // Update positions after swapping
                            sprites[highlighted_row][highlighted_col].setPosition((highlighted_col * gemSize) + off_setX, (highlighted_row * gemSize) + off_setY);
                            sprites[highlighted_row][highlighted_col - 1].setPosition(((highlighted_col - 1) * gemSize) + off_setX, ((highlighted_row)*gemSize) + off_setY);
                            score = score + score_5_special;
                            scoreText.setString("Score: " + std::to_string(score));
                            specialFive = true;
                        }

                        else if ((sprites[highlighted_row][highlighted_col].getTexture() == &images[14] &&
                                  sprites[highlighted_row - 1][highlighted_col - 1].getTexture() == &images[0] &&
                                  sprites[highlighted_row - 2][highlighted_col - 1].getTexture() == &images[0]) ||
                                 (sprites[highlighted_row][highlighted_col].getTexture() == &images[15] &&
                                  sprites[highlighted_row - 1][highlighted_col - 1].getTexture() == &images[1] &&
                                  sprites[highlighted_row - 2][highlighted_col - 1].getTexture() == &images[1]) ||
                                 (sprites[highlighted_row][highlighted_col].getTexture() == &images[16] &&
                                  sprites[highlighted_row - 1][highlighted_col - 1].getTexture() == &images[2] &&
                                 (sprites[highlighted_row - 2][highlighted_col - 1].getTexture() == &images[2]) ||
                                sprites[highlighted_row][highlighted_col].getTexture() == &images[17] &&
                                sprites[highlighted_row - 1][highlighted_col - 1].getTexture() == &images[3] &&
                                sprites[highlighted_row - 2][highlighted_col - 1].getTexture() == &images[3]) ||
                            (sprites[highlighted_row][highlighted_col].getTexture() == &images[18] &&
                                sprites[highlighted_row - 1][highlighted_col - 1].getTexture() == &images[4] &&
                                sprites[highlighted_row - 2][highlighted_col - 1].getTexture() == &images[4]) ||
                            (sprites[highlighted_row][highlighted_col].getTexture() == &images[19] &&
                                sprites[highlighted_row - 1][highlighted_col - 1].getTexture() == &images[5] &&
                                sprites[highlighted_row - 2][highlighted_col - 1].getTexture() == &images[5]) ||
                            (sprites[highlighted_row][highlighted_col].getTexture() == &images[20] &&
                                sprites[highlighted_row - 1][highlighted_col - 1].getTexture() == &images[6] &&
                                sprites[highlighted_row - 2][highlighted_col - 1].getTexture() == &images[6]))
                        {
                            specialRow = highlighted_row;
                            specialCol = highlighted_col - 1;


                            Sprite temp = sprites[highlighted_row][highlighted_col];
                            sprites[highlighted_row][highlighted_col] = sprites[highlighted_row][highlighted_col - 1];
                            sprites[highlighted_row][highlighted_col - 1] = temp;
                            // Update positions after swapping
                            sprites[highlighted_row][highlighted_col].setPosition((highlighted_col * gemSize) + off_setX, (highlighted_row * gemSize) + off_setY);
                            sprites[highlighted_row][highlighted_col - 1].setPosition(((highlighted_col - 1) * gemSize) + off_setX, ((highlighted_row)*gemSize) + off_setY);
                            score = score + score_5_special;
                            scoreText.setString("Score: " + std::to_string(score));
                            specialFive = true;
                        }

                        else if ((sprites[highlighted_row][highlighted_col].getTexture() == &images[14] &&
                            sprites[highlighted_row + 1][highlighted_col - 1].getTexture() == &images[0] &&
                            sprites[highlighted_row + 2][highlighted_col - 1].getTexture() == &images[0]) ||
                            (sprites[highlighted_row][highlighted_col].getTexture() == &images[15] &&
                                sprites[highlighted_row + 1][highlighted_col - 1].getTexture() == &images[1] &&
                                sprites[highlighted_row + 2][highlighted_col - 1].getTexture() == &images[1]) ||
                            (sprites[highlighted_row][highlighted_col].getTexture() == &images[16] &&
                                sprites[highlighted_row + 1][highlighted_col - 1].getTexture() == &images[2] &&
                                (sprites[highlighted_row + 2][highlighted_col - 1].getTexture() == &images[2]) ||
                                sprites[highlighted_row][highlighted_col].getTexture() == &images[17] &&
                                sprites[highlighted_row + 1][highlighted_col - 1].getTexture() == &images[3] &&
                                sprites[highlighted_row + 2][highlighted_col - 1].getTexture() == &images[3]) ||
                            (sprites[highlighted_row][highlighted_col].getTexture() == &images[18] &&
                                sprites[highlighted_row + 1][highlighted_col - 1].getTexture() == &images[4] &&
                                sprites[highlighted_row + 2][highlighted_col - 1].getTexture() == &images[4]) ||
                            (sprites[highlighted_row][highlighted_col].getTexture() == &images[19] &&
                                sprites[highlighted_row + 1][highlighted_col - 1].getTexture() == &images[5] &&
                                sprites[highlighted_row + 2][highlighted_col - 1].getTexture() == &images[5]) ||
                            (sprites[highlighted_row][highlighted_col].getTexture() == &images[20] &&
                                sprites[highlighted_row + 1][highlighted_col - 1].getTexture() == &images[6] &&
                                sprites[highlighted_row + 2][highlighted_col - 1].getTexture() == &images[6]))
                        {
                            specialRow = highlighted_row;
                            specialCol = highlighted_col - 1;


                            Sprite temp = sprites[highlighted_row][highlighted_col];
                            sprites[highlighted_row][highlighted_col] = sprites[highlighted_row][highlighted_col - 1];
                            sprites[highlighted_row][highlighted_col - 1] = temp;
                            // Update positions after swapping
                            sprites[highlighted_row][highlighted_col].setPosition((highlighted_col * gemSize) + off_setX, (highlighted_row * gemSize) + off_setY);
                            sprites[highlighted_row][highlighted_col - 1].setPosition(((highlighted_col - 1) * gemSize) + off_setX, ((highlighted_row)*gemSize) + off_setY);
                            score = score + score_5_special;
                            scoreText.setString("Score: " + std::to_string(score));
                            specialFive = true;
                        }


                        else if ((sprites[highlighted_row][highlighted_col].getTexture() == &images[14] &&
                            sprites[highlighted_row + 1][highlighted_col - 1].getTexture() == &images[0] &&
                            sprites[highlighted_row - 1][highlighted_col - 1].getTexture() == &images[0]) ||
                            (sprites[highlighted_row][highlighted_col].getTexture() == &images[15] &&
                                sprites[highlighted_row + 1][highlighted_col - 1].getTexture() == &images[1] &&
                                sprites[highlighted_row - 1][highlighted_col - 1].getTexture() == &images[1]) ||
                            (sprites[highlighted_row][highlighted_col].getTexture() == &images[16] &&
                                sprites[highlighted_row + 1][highlighted_col - 1].getTexture() == &images[2] &&
                                (sprites[highlighted_row - 1][highlighted_col - 1].getTexture() == &images[2]) ||
                                sprites[highlighted_row][highlighted_col].getTexture() == &images[17] &&
                                sprites[highlighted_row + 1][highlighted_col - 1].getTexture() == &images[3] &&
                                sprites[highlighted_row - 1][highlighted_col - 1].getTexture() == &images[3]) ||
                            (sprites[highlighted_row][highlighted_col].getTexture() == &images[18] &&
                                sprites[highlighted_row + 1][highlighted_col - 1].getTexture() == &images[4] &&
                                sprites[highlighted_row - 1][highlighted_col - 1].getTexture() == &images[4]) ||
                            (sprites[highlighted_row][highlighted_col].getTexture() == &images[19] &&
                                sprites[highlighted_row + 1][highlighted_col - 1].getTexture() == &images[5] &&
                                sprites[highlighted_row - 1][highlighted_col - 1].getTexture() == &images[5]) ||
                            (sprites[highlighted_row][highlighted_col].getTexture() == &images[20] &&
                                sprites[highlighted_row + 1][highlighted_col - 1].getTexture() == &images[6] &&
                                sprites[highlighted_row - 1][highlighted_col - 1].getTexture() == &images[6]))
                        {
                            specialRow = highlighted_row;
                            specialCol = highlighted_col - 1;


                            Sprite temp = sprites[highlighted_row][highlighted_col];
                            sprites[highlighted_row][highlighted_col] = sprites[highlighted_row][highlighted_col - 1];
                            sprites[highlighted_row][highlighted_col - 1] = temp;
                            // Update positions after swapping
                            sprites[highlighted_row][highlighted_col].setPosition((highlighted_col * gemSize) + off_setX, (highlighted_row * gemSize) + off_setY);
                            sprites[highlighted_row][highlighted_col - 1].setPosition(((highlighted_col - 1) * gemSize) + off_setX, ((highlighted_row)*gemSize) + off_setY);
                            score = score + score_5_special;
                            scoreText.setString("Score: " + std::to_string(score));
                            specialFive = true;
                        }

                        else if ((sprites[highlighted_row][highlighted_col].getTexture() == &images[14] &&
                            sprites[highlighted_row][highlighted_col - 2].getTexture() == &images[0] &&
                            sprites[highlighted_row][highlighted_col - 3].getTexture() == &images[0]) ||
                            (sprites[highlighted_row][highlighted_col].getTexture() == &images[15] &&
                                sprites[highlighted_row][highlighted_col - 2].getTexture() == &images[1] &&
                                sprites[highlighted_row][highlighted_col - 3].getTexture() == &images[1]) ||
                            (sprites[highlighted_row][highlighted_col].getTexture() == &images[16] &&
                                sprites[highlighted_row][highlighted_col - 2].getTexture() == &images[2] &&
                                (sprites[highlighted_row][highlighted_col - 3].getTexture() == &images[2]) ||
                                sprites[highlighted_row][highlighted_col].getTexture() == &images[17] &&
                                sprites[highlighted_row][highlighted_col - 2].getTexture() == &images[3] &&
                                sprites[highlighted_row][highlighted_col - 3].getTexture() == &images[3]) ||
                            (sprites[highlighted_row][highlighted_col].getTexture() == &images[18] &&
                                sprites[highlighted_row][highlighted_col - 2].getTexture() == &images[4] &&
                                sprites[highlighted_row][highlighted_col - 3].getTexture() == &images[4]) ||
                            (sprites[highlighted_row][highlighted_col].getTexture() == &images[19] &&
                                sprites[highlighted_row][highlighted_col - 2].getTexture() == &images[5] &&
                                sprites[highlighted_row][highlighted_col - 3].getTexture() == &images[5]) ||
                            (sprites[highlighted_row][highlighted_col].getTexture() == &images[20] &&
                                sprites[highlighted_row][highlighted_col - 2].getTexture() == &images[6] &&
                                sprites[highlighted_row][highlighted_col - 3].getTexture() == &images[6]))
                        {
                            specialRow = highlighted_row;
                            specialCol = highlighted_col - 1;


                            Sprite temp = sprites[highlighted_row][highlighted_col];
                            sprites[highlighted_row][highlighted_col] = sprites[highlighted_row][highlighted_col - 1];
                            sprites[highlighted_row][highlighted_col - 1] = temp;
                            // Update positions after swapping
                            sprites[highlighted_row][highlighted_col].setPosition((highlighted_col * gemSize) + off_setX, (highlighted_row * gemSize) + off_setY);
                            sprites[highlighted_row][highlighted_col - 1].setPosition(((highlighted_col - 1) * gemSize) + off_setX, ((highlighted_row)*gemSize) + off_setY);
                            score = score + score_5_special;
                            scoreText.setString("Score: " + std::to_string(score));
                            specialFive = true;
                        }

                    }

                    highlighted_col--;
                    enter_key_pressed = false;
                    swap_triggered = false;

                }

                else if (event.key.code == Keyboard::Right && highlighted_col < 7)
                {
                    if (enter_key_pressed && swap_triggered)
                    {
                       if (sprites[highlighted_row][highlighted_col].getTexture() == sprites[highlighted_row - 1][highlighted_col + 1].getTexture() &&
                            sprites[highlighted_row][highlighted_col].getTexture() == sprites[highlighted_row - 2][highlighted_col + 1].getTexture() &&
                            sprites[highlighted_row][highlighted_col].getTexture() == sprites[highlighted_row + 1][highlighted_col + 1].getTexture() &&
                            sprites[highlighted_row][highlighted_col].getTexture() == sprites[highlighted_row + 2][highlighted_col + 1].getTexture())
                        {
                            // storing indexes of the above position
                            indexRight1 = highlighted_row;
                            indexRight2 = highlighted_col + 1;

                            // storing the texture to temporary sprite
                            const Texture* texturePtr = sprites[highlighted_row][highlighted_col].getTexture();
                            tempSprites[indexRight1][indexRight2].setTexture(*texturePtr);

                            matchFiveRight = true;
                            score = score + score_5_matches;
                            scoreText.setString("Score: " + std::to_string(score));
                            Sprite temp = sprites[highlighted_row][highlighted_col];
                            sprites[highlighted_row][highlighted_col] = sprites[highlighted_row][highlighted_col + 1];
                            sprites[highlighted_row][highlighted_col + 1] = temp;
                            // Update positions after swapping
                            sprites[highlighted_row][highlighted_col].setPosition((highlighted_col * gemSize) + off_setX, (highlighted_row * gemSize) + off_setY);
                            sprites[highlighted_row][highlighted_col + 1].setPosition(((highlighted_col + 1) * gemSize) + off_setX, ((highlighted_row)*gemSize) + off_setY);
                        }

                        else if ((sprites[highlighted_row][highlighted_col].getTexture() == sprites[highlighted_row - 1][highlighted_col + 1].getTexture() &&
                            sprites[highlighted_row][highlighted_col].getTexture() == sprites[highlighted_row - 2][highlighted_col + 1].getTexture() &&
                            sprites[highlighted_row][highlighted_col].getTexture() == sprites[highlighted_row + 1][highlighted_col + 1].getTexture()) ||
                            (sprites[highlighted_row][highlighted_col].getTexture() == sprites[highlighted_row - 1][highlighted_col + 1].getTexture() &&
                                sprites[highlighted_row][highlighted_col].getTexture() == sprites[highlighted_row + 1][highlighted_col + 1].getTexture() &&
                                sprites[highlighted_row][highlighted_col].getTexture() == sprites[highlighted_row + 2][highlighted_col + 1].getTexture()))
                        {
                            // storing indexes of the above position
                            indexRight1 = highlighted_row;
                            indexRight2 = highlighted_col + 1;

                            // storing the texture to temporary sprite
                            const Texture* texturePtr = sprites[highlighted_row][highlighted_col].getTexture();
                            tempSprites[indexRight1][indexRight2].setTexture(*texturePtr);
                            score = score + score_4_matches;
                            scoreText.setString("Score: " + std::to_string(score));
                            matchFourRight = true;


                            Sprite temp = sprites[highlighted_row][highlighted_col];
                            sprites[highlighted_row][highlighted_col] = sprites[highlighted_row][highlighted_col + 1];
                            sprites[highlighted_row][highlighted_col + 1] = temp;
                            // Update positions after swapping
                            sprites[highlighted_row][highlighted_col].setPosition((highlighted_col * gemSize) + off_setX, (highlighted_row * gemSize) + off_setY);
                            sprites[highlighted_row][highlighted_col + 1].setPosition(((highlighted_col + 1) * gemSize) + off_setX, ((highlighted_row)*gemSize) + off_setY);
                        }

                        else if (sprites[highlighted_row][highlighted_col].getTexture() == sprites[highlighted_row - 1][highlighted_col + 1].getTexture() &&
                            sprites[highlighted_row][highlighted_col].getTexture() == sprites[highlighted_row - 2][highlighted_col + 1].getTexture() &&
                            sprites[highlighted_row][highlighted_col].getTexture() == sprites[highlighted_row][highlighted_col + 2].getTexture() &&
                            sprites[highlighted_row][highlighted_col].getTexture() == sprites[highlighted_row][highlighted_col + 3].getTexture() ||
                            sprites[highlighted_row][highlighted_col].getTexture() == sprites[highlighted_row + 1][highlighted_col + 1].getTexture() &&
                            sprites[highlighted_row][highlighted_col].getTexture() == sprites[highlighted_row + 2][highlighted_col + 1].getTexture() &&
                            sprites[highlighted_row][highlighted_col].getTexture() == sprites[highlighted_row][highlighted_col + 2].getTexture() &&
                            sprites[highlighted_row][highlighted_col].getTexture() == sprites[highlighted_row][highlighted_col + 3].getTexture())
                        {
                            // storing indexes of the above position
                            indexRight1 = highlighted_row;
                            indexRight2 = highlighted_col + 1;

                            // storing the texture to temporary sprite
                            const Texture* texturePtr = sprites[highlighted_row][highlighted_col].getTexture();
                            tempSprites[indexRight1][indexRight2].setTexture(*texturePtr);

                            destroyRight = true;
                            score = score + score_5_matches;
                            scoreText.setString("Score: " + std::to_string(score));
                            Sprite temp = sprites[highlighted_row][highlighted_col];
                            sprites[highlighted_row][highlighted_col] = sprites[highlighted_row][highlighted_col + 1];
                            sprites[highlighted_row][highlighted_col + 1] = temp;
                            // Update positions after swapping
                            sprites[highlighted_row][highlighted_col].setPosition((highlighted_col * gemSize) + off_setX, (highlighted_row * gemSize) + off_setY);
                            sprites[highlighted_row][highlighted_col + 1].setPosition(((highlighted_col + 1) * gemSize) + off_setX, ((highlighted_row)*gemSize) + off_setY);
                        }
                        else if (sprites[highlighted_row][highlighted_col].getTexture() == sprites[highlighted_row - 1][highlighted_col + 1].getTexture() &&
                            sprites[highlighted_row][highlighted_col].getTexture() == sprites[highlighted_row + 1][highlighted_col + 1].getTexture())
                        {
                            Sprite temp = sprites[highlighted_row][highlighted_col];
                            sprites[highlighted_row][highlighted_col] = sprites[highlighted_row][highlighted_col + 1];
                            sprites[highlighted_row][highlighted_col + 1] = temp;
                            // Update positions after swapping
                            sprites[highlighted_row][highlighted_col].setPosition((highlighted_col * gemSize) + off_setX, (highlighted_row * gemSize) + off_setY);
                            sprites[highlighted_row][highlighted_col + 1].setPosition(((highlighted_col + 1) * gemSize) + off_setX, ((highlighted_row)*gemSize) + off_setY);
                            score = score + score_3_matches;
                            scoreText.setString("Score: " + std::to_string(score));

                        }

                        else if (sprites[highlighted_row][highlighted_col].getTexture() == sprites[highlighted_row + 1][highlighted_col + 1].getTexture() &&
                            sprites[highlighted_row][highlighted_col].getTexture() == sprites[highlighted_row + 2][highlighted_col + 1].getTexture())
                        {
                            Sprite temp = sprites[highlighted_row][highlighted_col];
                            sprites[highlighted_row][highlighted_col] = sprites[highlighted_row][highlighted_col + 1];
                            sprites[highlighted_row][highlighted_col + 1] = temp;
                            // Update positions after swapping
                            sprites[highlighted_row][highlighted_col].setPosition((highlighted_col * gemSize) + off_setX, (highlighted_row * gemSize) + off_setY);
                            sprites[highlighted_row][highlighted_col + 1].setPosition(((highlighted_col + 1) * gemSize) + off_setX, ((highlighted_row)*gemSize) + off_setY);
                            score = score + score_3_matches;
                            scoreText.setString("Score: " + std::to_string(score));
                        }
                       else if (sprites[highlighted_row][highlighted_col].getTexture() == sprites[highlighted_row - 1][highlighted_col + 1].getTexture() &&
                            sprites[highlighted_row][highlighted_col].getTexture() == sprites[highlighted_row - 2][highlighted_col + 1].getTexture())
                        {
                            Sprite temp = sprites[highlighted_row][highlighted_col];
                            sprites[highlighted_row][highlighted_col] = sprites[highlighted_row][highlighted_col + 1];
                            sprites[highlighted_row][highlighted_col + 1] = temp;
                            // Update positions after swapping
                            sprites[highlighted_row][highlighted_col].setPosition((highlighted_col * gemSize) + off_setX, (highlighted_row * gemSize) + off_setY);
                            sprites[highlighted_row][highlighted_col + 1].setPosition(((highlighted_col + 1) * gemSize) + off_setX, ((highlighted_row)*gemSize) + off_setY);
                            score = score + score_3_matches;
                            scoreText.setString("Score: " + std::to_string(score));
                        }

                        else if (sprites[highlighted_row][highlighted_col].getTexture() == sprites[highlighted_row][highlighted_col + 2].getTexture() &&
                            sprites[highlighted_row][highlighted_col].getTexture() == sprites[highlighted_row][highlighted_col + 3].getTexture())
                        {
                            Sprite temp = sprites[highlighted_row][highlighted_col];
                            sprites[highlighted_row][highlighted_col] = sprites[highlighted_row][highlighted_col + 1];
                            sprites[highlighted_row][highlighted_col + 1] = temp;
                            // Update positions after swapping
                            sprites[highlighted_row][highlighted_col].setPosition((highlighted_col * gemSize) + off_setX, (highlighted_row * gemSize) + off_setY);
                            sprites[highlighted_row][highlighted_col + 1].setPosition(((highlighted_col + 1) * gemSize) + off_setX, ((highlighted_row)*gemSize) + off_setY);
                            score = score + score_3_matches;
                            scoreText.setString("Score: " + std::to_string(score));
                        }

                        else if ((sprites[highlighted_row][highlighted_col].getTexture() == &images[0] &&
                            sprites[highlighted_row - 1][highlighted_col + 1].getTexture() == &images[7] &&
                            sprites[highlighted_row - 2][highlighted_col + 1].getTexture() == &images[0]) ||
                            (sprites[highlighted_row][highlighted_col].getTexture() == &images[1] &&
                                sprites[highlighted_row - 1][highlighted_col + 1].getTexture() == &images[8] &&
                                sprites[highlighted_row - 2][highlighted_col + 1].getTexture() == &images[1]) ||
                            (sprites[highlighted_row][highlighted_col].getTexture() == &images[2] &&
                                sprites[highlighted_row - 1][highlighted_col + 1].getTexture() == &images[9] &&
                                (sprites[highlighted_row - 2][highlighted_col + 1].getTexture() == &images[2]) ||
                                sprites[highlighted_row][highlighted_col].getTexture() == &images[3] &&
                                sprites[highlighted_row - 1][highlighted_col + 1].getTexture() == &images[10] &&
                                sprites[highlighted_row - 2][highlighted_col + 1].getTexture() == &images[3]) ||
                            (sprites[highlighted_row][highlighted_col].getTexture() == &images[4] &&
                                sprites[highlighted_row - 1][highlighted_col + 1].getTexture() == &images[11] &&
                                sprites[highlighted_row - 2][highlighted_col + 1].getTexture() == &images[4]) ||
                            (sprites[highlighted_row][highlighted_col].getTexture() == &images[5] &&
                                sprites[highlighted_row - 1][highlighted_col + 1].getTexture() == &images[12] &&
                                sprites[highlighted_row - 2][highlighted_col + 1].getTexture() == &images[5]) ||
                            (sprites[highlighted_row][highlighted_col].getTexture() == &images[6] &&
                                sprites[highlighted_row - 1][highlighted_col + 1].getTexture() == &images[13] &&
                                sprites[highlighted_row - 2][highlighted_col + 1].getTexture() == &images[6]))
                        {
                            Sprite temp = sprites[highlighted_row][highlighted_col];
                            sprites[highlighted_row][highlighted_col] = sprites[highlighted_row][highlighted_col + 1];
                            sprites[highlighted_row][highlighted_col + 1] = temp;
                            // Update positions after swapping
                            sprites[highlighted_row][highlighted_col].setPosition((highlighted_col * gemSize) + off_setX, (highlighted_row * gemSize) + off_setY);
                            sprites[highlighted_row][highlighted_col + 1].setPosition(((highlighted_col + 1) * gemSize) + off_setX, ((highlighted_row)*gemSize) + off_setY);
                            score = score + score_4_special;
                            scoreText.setString("Score: " + std::to_string(score));
                            specialFourRight1 = true;
                       }

                        else if ((sprites[highlighted_row][highlighted_col].getTexture() == &images[0] &&
                            sprites[highlighted_row - 1][highlighted_col + 1].getTexture() == &images[0] &&
                            sprites[highlighted_row - 2][highlighted_col + 1].getTexture() == &images[7]) ||
                            (sprites[highlighted_row][highlighted_col].getTexture() == &images[1] &&
                                sprites[highlighted_row - 1][highlighted_col + 1].getTexture() == &images[1] &&
                                sprites[highlighted_row - 2][highlighted_col + 1].getTexture() == &images[8]) ||
                            (sprites[highlighted_row][highlighted_col].getTexture() == &images[2] &&
                                sprites[highlighted_row - 1][highlighted_col + 1].getTexture() == &images[2] &&
                                (sprites[highlighted_row - 2][highlighted_col + 1].getTexture() == &images[9]) ||
                                sprites[highlighted_row][highlighted_col].getTexture() == &images[3] &&
                                sprites[highlighted_row - 1][highlighted_col + 1].getTexture() == &images[3] &&
                                sprites[highlighted_row - 2][highlighted_col + 1].getTexture() == &images[10]) ||
                            (sprites[highlighted_row][highlighted_col].getTexture() == &images[4] &&
                                sprites[highlighted_row - 1][highlighted_col + 1].getTexture() == &images[4] &&
                                sprites[highlighted_row - 2][highlighted_col + 1].getTexture() == &images[11]) ||
                            (sprites[highlighted_row][highlighted_col].getTexture() == &images[5] &&
                                sprites[highlighted_row - 1][highlighted_col + 1].getTexture() == &images[5] &&
                                sprites[highlighted_row - 2][highlighted_col + 1].getTexture() == &images[12]) ||
                            (sprites[highlighted_row][highlighted_col].getTexture() == &images[6] &&
                                sprites[highlighted_row - 1][highlighted_col + 1].getTexture() == &images[6] &&
                                sprites[highlighted_row - 2][highlighted_col + 1].getTexture() == &images[13]))
                        {
                            Sprite temp = sprites[highlighted_row][highlighted_col];
                            sprites[highlighted_row][highlighted_col] = sprites[highlighted_row][highlighted_col + 1];
                            sprites[highlighted_row][highlighted_col + 1] = temp;
                            // Update positions after swapping
                            sprites[highlighted_row][highlighted_col].setPosition((highlighted_col * gemSize) + off_setX, (highlighted_row * gemSize) + off_setY);
                            sprites[highlighted_row][highlighted_col + 1].setPosition(((highlighted_col + 1) * gemSize) + off_setX, ((highlighted_row)*gemSize) + off_setY);
                            score = score + score_4_special;
                            scoreText.setString("Score: " + std::to_string(score));
                            specialFourRight2 = true;
                        }

                        else if ((sprites[highlighted_row][highlighted_col].getTexture() == &images[0] &&
                            sprites[highlighted_row + 1][highlighted_col + 1].getTexture() == &images[7] &&
                            sprites[highlighted_row + 2][highlighted_col + 1].getTexture() == &images[0]) ||
                            (sprites[highlighted_row][highlighted_col].getTexture() == &images[1] &&
                                sprites[highlighted_row + 1][highlighted_col + 1].getTexture() == &images[8] &&
                                sprites[highlighted_row + 2][highlighted_col + 1].getTexture() == &images[1]) ||
                            (sprites[highlighted_row][highlighted_col].getTexture() == &images[2] &&
                                sprites[highlighted_row + 1][highlighted_col + 1].getTexture() == &images[9] &&
                                (sprites[highlighted_row + 2][highlighted_col + 1].getTexture() == &images[2]) ||
                                sprites[highlighted_row][highlighted_col].getTexture() == &images[3] &&
                                sprites[highlighted_row + 1][highlighted_col + 1].getTexture() == &images[10] &&
                                sprites[highlighted_row + 2][highlighted_col + 1].getTexture() == &images[3]) ||
                            (sprites[highlighted_row][highlighted_col].getTexture() == &images[4] &&
                                sprites[highlighted_row + 1][highlighted_col + 1].getTexture() == &images[11] &&
                                sprites[highlighted_row + 2][highlighted_col + 1].getTexture() == &images[4]) ||
                            (sprites[highlighted_row][highlighted_col].getTexture() == &images[5] &&
                                sprites[highlighted_row + 1][highlighted_col + 1].getTexture() == &images[12] &&
                                sprites[highlighted_row + 2][highlighted_col + 1].getTexture() == &images[5]) ||
                            (sprites[highlighted_row][highlighted_col].getTexture() == &images[6] &&
                                sprites[highlighted_row + 1][highlighted_col + 1].getTexture() == &images[13] &&
                                sprites[highlighted_row + 2][highlighted_col + 1].getTexture() == &images[6]))
                        {
                            Sprite temp = sprites[highlighted_row][highlighted_col];
                            sprites[highlighted_row][highlighted_col] = sprites[highlighted_row][highlighted_col + 1];
                            sprites[highlighted_row][highlighted_col + 1] = temp;
                            // Update positions after swapping
                            sprites[highlighted_row][highlighted_col].setPosition((highlighted_col * gemSize) + off_setX, (highlighted_row * gemSize) + off_setY);
                            sprites[highlighted_row][highlighted_col + 1].setPosition(((highlighted_col + 1) * gemSize) + off_setX, ((highlighted_row)*gemSize) + off_setY);
                            score = score + score_4_special;
                            scoreText.setString("Score: " + std::to_string(score));
                            specialFourRight3 = true;
                        }

                        else if ((sprites[highlighted_row][highlighted_col].getTexture() == &images[0] &&
                            sprites[highlighted_row + 1][highlighted_col + 1].getTexture() == &images[0] &&
                            sprites[highlighted_row + 2][highlighted_col + 1].getTexture() == &images[7]) ||
                            (sprites[highlighted_row][highlighted_col].getTexture() == &images[1] &&
                                sprites[highlighted_row + 1][highlighted_col + 1].getTexture() == &images[1] &&
                                sprites[highlighted_row + 2][highlighted_col + 1].getTexture() == &images[8]) ||
                            (sprites[highlighted_row][highlighted_col].getTexture() == &images[2] &&
                                sprites[highlighted_row + 1][highlighted_col + 1].getTexture() == &images[2] &&
                                (sprites[highlighted_row + 2][highlighted_col + 1].getTexture() == &images[9]) ||
                                sprites[highlighted_row][highlighted_col].getTexture() == &images[3] &&
                                sprites[highlighted_row + 1][highlighted_col + 1].getTexture() == &images[3] &&
                                sprites[highlighted_row + 2][highlighted_col + 1].getTexture() == &images[10]) ||
                            (sprites[highlighted_row][highlighted_col].getTexture() == &images[4] &&
                                sprites[highlighted_row + 1][highlighted_col + 1].getTexture() == &images[4] &&
                                sprites[highlighted_row + 2][highlighted_col + 1].getTexture() == &images[11]) ||
                            (sprites[highlighted_row][highlighted_col].getTexture() == &images[5] &&
                                sprites[highlighted_row + 1][highlighted_col + 1].getTexture() == &images[5] &&
                                sprites[highlighted_row + 2][highlighted_col + 1].getTexture() == &images[12]) ||
                            (sprites[highlighted_row][highlighted_col].getTexture() == &images[6] &&
                                sprites[highlighted_row + 1][highlighted_col + 1].getTexture() == &images[6] &&
                                sprites[highlighted_row + 2][highlighted_col + 1].getTexture() == &images[13]))
                        {
                            Sprite temp = sprites[highlighted_row][highlighted_col];
                            sprites[highlighted_row][highlighted_col] = sprites[highlighted_row][highlighted_col + 1];
                            sprites[highlighted_row][highlighted_col + 1] = temp;
                            // Update positions after swapping
                            sprites[highlighted_row][highlighted_col].setPosition((highlighted_col * gemSize) + off_setX, (highlighted_row * gemSize) + off_setY);
                            sprites[highlighted_row][highlighted_col + 1].setPosition(((highlighted_col + 1) * gemSize) + off_setX, ((highlighted_row)*gemSize) + off_setY);
                            score = score + score_4_special;
                            scoreText.setString("Score: " + std::to_string(score));
                            specialFourRight4 = true;
                        }

                        else if ((sprites[highlighted_row][highlighted_col].getTexture() == &images[0] &&
                            sprites[highlighted_row + 1][highlighted_col + 1].getTexture() == &images[0] &&
                            sprites[highlighted_row - 1][highlighted_col + 1].getTexture() == &images[7]) ||
                            (sprites[highlighted_row][highlighted_col].getTexture() == &images[1] &&
                                sprites[highlighted_row + 1][highlighted_col + 1].getTexture() == &images[1] &&
                                sprites[highlighted_row - 1][highlighted_col + 1].getTexture() == &images[8]) ||
                            (sprites[highlighted_row][highlighted_col].getTexture() == &images[2] &&
                                sprites[highlighted_row + 1][highlighted_col + 1].getTexture() == &images[2] &&
                                (sprites[highlighted_row - 1][highlighted_col + 1].getTexture() == &images[9]) ||
                                sprites[highlighted_row][highlighted_col].getTexture() == &images[3] &&
                                sprites[highlighted_row + 1][highlighted_col + 1].getTexture() == &images[3] &&
                                sprites[highlighted_row - 1][highlighted_col + 1].getTexture() == &images[10]) ||
                            (sprites[highlighted_row][highlighted_col].getTexture() == &images[4] &&
                                sprites[highlighted_row + 1][highlighted_col + 1].getTexture() == &images[4] &&
                                sprites[highlighted_row - 1][highlighted_col + 1].getTexture() == &images[11]) ||
                            (sprites[highlighted_row][highlighted_col].getTexture() == &images[5] &&
                                sprites[highlighted_row + 1][highlighted_col + 1].getTexture() == &images[5] &&
                                sprites[highlighted_row - 1][highlighted_col + 1].getTexture() == &images[12]) ||
                            (sprites[highlighted_row][highlighted_col].getTexture() == &images[6] &&
                                sprites[highlighted_row + 1][highlighted_col + 1].getTexture() == &images[6] &&
                                sprites[highlighted_row - 1][highlighted_col + 1].getTexture() == &images[13]))
                        {
                            Sprite temp = sprites[highlighted_row][highlighted_col];
                            sprites[highlighted_row][highlighted_col] = sprites[highlighted_row][highlighted_col + 1];
                            sprites[highlighted_row][highlighted_col + 1] = temp;
                            // Update positions after swapping
                            sprites[highlighted_row][highlighted_col].setPosition((highlighted_col * gemSize) + off_setX, (highlighted_row * gemSize) + off_setY);
                            sprites[highlighted_row][highlighted_col + 1].setPosition(((highlighted_col + 1) * gemSize) + off_setX, ((highlighted_row)*gemSize) + off_setY);;
                            score = score + score_4_special;
                            scoreText.setString("Score: " + std::to_string(score));
                            specialFourRight5 = true;
                        }

                        else if ((sprites[highlighted_row][highlighted_col].getTexture() == &images[0] &&
                            sprites[highlighted_row + 1][highlighted_col + 1].getTexture() == &images[7] &&
                            sprites[highlighted_row - 1][highlighted_col + 1].getTexture() == &images[0]) ||
                            (sprites[highlighted_row][highlighted_col].getTexture() == &images[1] &&
                                sprites[highlighted_row + 1][highlighted_col + 1].getTexture() == &images[8] &&
                                sprites[highlighted_row - 1][highlighted_col + 1].getTexture() == &images[1]) ||
                            (sprites[highlighted_row][highlighted_col].getTexture() == &images[2] &&
                                sprites[highlighted_row + 1][highlighted_col + 1].getTexture() == &images[9] &&
                                (sprites[highlighted_row - 1][highlighted_col + 1].getTexture() == &images[2]) ||
                                sprites[highlighted_row][highlighted_col].getTexture() == &images[3] &&
                                sprites[highlighted_row + 1][highlighted_col + 1].getTexture() == &images[10] &&
                                sprites[highlighted_row - 1][highlighted_col + 1].getTexture() == &images[3]) ||
                            (sprites[highlighted_row][highlighted_col].getTexture() == &images[4] &&
                                sprites[highlighted_row + 1][highlighted_col + 1].getTexture() == &images[11] &&
                                sprites[highlighted_row - 1][highlighted_col + 1].getTexture() == &images[4]) ||
                            (sprites[highlighted_row][highlighted_col].getTexture() == &images[5] &&
                                sprites[highlighted_row + 1][highlighted_col + 1].getTexture() == &images[12] &&
                                sprites[highlighted_row - 1][highlighted_col + 1].getTexture() == &images[5]) ||
                            (sprites[highlighted_row][highlighted_col].getTexture() == &images[6] &&
                                sprites[highlighted_row + 1][highlighted_col + 1].getTexture() == &images[13] &&
                                sprites[highlighted_row - 1][highlighted_col + 1].getTexture() == &images[6]))
                        {
                            Sprite temp = sprites[highlighted_row][highlighted_col];
                            sprites[highlighted_row][highlighted_col] = sprites[highlighted_row][highlighted_col + 1];
                            sprites[highlighted_row][highlighted_col + 1] = temp;
                            // Update positions after swapping
                            sprites[highlighted_row][highlighted_col].setPosition((highlighted_col * gemSize) + off_setX, (highlighted_row * gemSize) + off_setY);
                            sprites[highlighted_row][highlighted_col + 1].setPosition(((highlighted_col + 1) * gemSize) + off_setX, ((highlighted_row)*gemSize) + off_setY);
                            score = score + score_4_special;
                            scoreText.setString("Score: " + std::to_string(score));
                            specialFourRight6 = true;
                        }

                        else if ((sprites[highlighted_row][highlighted_col].getTexture() == &images[7] &&
                            sprites[highlighted_row - 1][highlighted_col + 1].getTexture() == &images[0] &&
                            sprites[highlighted_row - 2][highlighted_col + 1].getTexture() == &images[0]) ||
                            (sprites[highlighted_row][highlighted_col].getTexture() == &images[8] &&
                                sprites[highlighted_row - 1][highlighted_col + 1].getTexture() == &images[1] &&
                                sprites[highlighted_row - 2][highlighted_col + 1].getTexture() == &images[1]) ||
                            (sprites[highlighted_row][highlighted_col].getTexture() == &images[9] &&
                                sprites[highlighted_row - 1][highlighted_col + 1].getTexture() == &images[2] &&
                                (sprites[highlighted_row - 2][highlighted_col + 1].getTexture() == &images[2]) ||
                                sprites[highlighted_row][highlighted_col].getTexture() == &images[10] &&
                                sprites[highlighted_row - 1][highlighted_col + 1].getTexture() == &images[3] &&
                                sprites[highlighted_row - 2][highlighted_col + 1].getTexture() == &images[3]) ||
                            (sprites[highlighted_row][highlighted_col].getTexture() == &images[11] &&
                                sprites[highlighted_row - 1][highlighted_col + 1].getTexture() == &images[4] &&
                                sprites[highlighted_row - 2][highlighted_col + 1].getTexture() == &images[4]) ||
                            (sprites[highlighted_row][highlighted_col].getTexture() == &images[12] &&
                                sprites[highlighted_row - 1][highlighted_col + 1].getTexture() == &images[5] &&
                                sprites[highlighted_row - 2][highlighted_col + 1].getTexture() == &images[5]) ||
                            (sprites[highlighted_row][highlighted_col].getTexture() == &images[13] &&
                                sprites[highlighted_row - 1][highlighted_col + 1].getTexture() == &images[6] &&
                                sprites[highlighted_row - 2][highlighted_col + 1].getTexture() == &images[6]))
                        {
                            Sprite temp = sprites[highlighted_row][highlighted_col];
                            sprites[highlighted_row][highlighted_col] = sprites[highlighted_row][highlighted_col + 1];
                            sprites[highlighted_row][highlighted_col + 1] = temp;
                            // Update positions after swapping
                            sprites[highlighted_row][highlighted_col].setPosition((highlighted_col * gemSize) + off_setX, (highlighted_row * gemSize) + off_setY);
                            sprites[highlighted_row][highlighted_col + 1].setPosition(((highlighted_col + 1) * gemSize) + off_setX, ((highlighted_row)*gemSize) + off_setY);
                            score = score + score_4_special;
                            scoreText.setString("Score: " + std::to_string(score));
                            specialRealFourRight = true;
                        }

                        else if ((sprites[highlighted_row][highlighted_col].getTexture() == &images[7] &&
                            sprites[highlighted_row + 1][highlighted_col + 1].getTexture() == &images[0] &&
                            sprites[highlighted_row + 2][highlighted_col + 1].getTexture() == &images[0]) ||
                            (sprites[highlighted_row][highlighted_col].getTexture() == &images[8] &&
                                sprites[highlighted_row + 1][highlighted_col + 1].getTexture() == &images[1] &&
                                sprites[highlighted_row + 2][highlighted_col + 1].getTexture() == &images[1]) ||
                            (sprites[highlighted_row][highlighted_col].getTexture() == &images[9] &&
                                sprites[highlighted_row + 1][highlighted_col + 1].getTexture() == &images[2] &&
                                (sprites[highlighted_row + 2][highlighted_col + 1].getTexture() == &images[2]) ||
                                sprites[highlighted_row][highlighted_col].getTexture() == &images[10] &&
                                sprites[highlighted_row + 1][highlighted_col + 1].getTexture() == &images[3] &&
                                sprites[highlighted_row + 2][highlighted_col + 1].getTexture() == &images[3]) ||
                            (sprites[highlighted_row][highlighted_col].getTexture() == &images[11] &&
                                sprites[highlighted_row + 1][highlighted_col + 1].getTexture() == &images[4] &&
                                sprites[highlighted_row + 2][highlighted_col + 1].getTexture() == &images[4]) ||
                            (sprites[highlighted_row][highlighted_col].getTexture() == &images[12] &&
                                sprites[highlighted_row + 1][highlighted_col + 1].getTexture() == &images[5] &&
                                sprites[highlighted_row + 2][highlighted_col + 1].getTexture() == &images[5]) ||
                            (sprites[highlighted_row][highlighted_col].getTexture() == &images[13] &&
                                sprites[highlighted_row + 1][highlighted_col + 1].getTexture() == &images[6] &&
                                sprites[highlighted_row + 2][highlighted_col + 1].getTexture() == &images[6]))
                        {
                            Sprite temp = sprites[highlighted_row][highlighted_col];
                            sprites[highlighted_row][highlighted_col] = sprites[highlighted_row][highlighted_col + 1];
                            sprites[highlighted_row][highlighted_col + 1] = temp;
                            // Update positions after swapping
                            sprites[highlighted_row][highlighted_col].setPosition((highlighted_col * gemSize) + off_setX, (highlighted_row * gemSize) + off_setY);
                            sprites[highlighted_row][highlighted_col + 1].setPosition(((highlighted_col + 1) * gemSize) + off_setX, ((highlighted_row)*gemSize) + off_setY);
                            score = score + score_4_special;
                            scoreText.setString("Score: " + std::to_string(score));
                            specialRealFourRight = true;
                        }


                        else if ((sprites[highlighted_row][highlighted_col].getTexture() == &images[7] &&
                            sprites[highlighted_row + 1][highlighted_col + 1].getTexture() == &images[0] &&
                            sprites[highlighted_row - 1][highlighted_col + 1].getTexture() == &images[0]) ||
                            (sprites[highlighted_row][highlighted_col].getTexture() == &images[8] &&
                                sprites[highlighted_row + 1][highlighted_col + 1].getTexture() == &images[1] &&
                                sprites[highlighted_row - 1][highlighted_col + 1].getTexture() == &images[1]) ||
                            (sprites[highlighted_row][highlighted_col].getTexture() == &images[9] &&
                                sprites[highlighted_row + 1][highlighted_col + 1].getTexture() == &images[2] &&
                                (sprites[highlighted_row - 1][highlighted_col + 1].getTexture() == &images[2]) ||
                                sprites[highlighted_row][highlighted_col].getTexture() == &images[10] &&
                                sprites[highlighted_row + 1][highlighted_col + 1].getTexture() == &images[3] &&
                                sprites[highlighted_row - 1][highlighted_col + 1].getTexture() == &images[3]) ||
                            (sprites[highlighted_row][highlighted_col].getTexture() == &images[11] &&
                                sprites[highlighted_row + 1][highlighted_col + 1].getTexture() == &images[4] &&
                                sprites[highlighted_row - 1][highlighted_col + 1].getTexture() == &images[4]) ||
                            (sprites[highlighted_row][highlighted_col].getTexture() == &images[12] &&
                                sprites[highlighted_row + 1][highlighted_col + 1].getTexture() == &images[5] &&
                                sprites[highlighted_row - 1][highlighted_col + 1].getTexture() == &images[5]) ||
                            (sprites[highlighted_row][highlighted_col].getTexture() == &images[13] &&
                                sprites[highlighted_row + 1][highlighted_col + 1].getTexture() == &images[6] &&
                                sprites[highlighted_row - 1][highlighted_col + 1].getTexture() == &images[6]))
                        {
                            Sprite temp = sprites[highlighted_row][highlighted_col];
                            sprites[highlighted_row][highlighted_col] = sprites[highlighted_row][highlighted_col + 1];
                            sprites[highlighted_row][highlighted_col + 1] = temp;
                            // Update positions after swapping
                            sprites[highlighted_row][highlighted_col].setPosition((highlighted_col * gemSize) + off_setX, (highlighted_row * gemSize) + off_setY);
                            sprites[highlighted_row][highlighted_col + 1].setPosition(((highlighted_col + 1) * gemSize) + off_setX, ((highlighted_row)*gemSize) + off_setY);
                            score = score + score_4_special;
                            scoreText.setString("Score: " + std::to_string(score));
                            specialRealFourRight = true;
                        }

                        else if ((sprites[highlighted_row][highlighted_col].getTexture() == &images[7] &&
                            sprites[highlighted_row][highlighted_col + 2].getTexture() == &images[0] &&
                            sprites[highlighted_row][highlighted_col + 3].getTexture() == &images[0]) ||
                            (sprites[highlighted_row][highlighted_col].getTexture() == &images[8] &&
                                sprites[highlighted_row][highlighted_col + 2].getTexture() == &images[1] &&
                                sprites[highlighted_row][highlighted_col + 3].getTexture() == &images[1]) ||
                            (sprites[highlighted_row][highlighted_col].getTexture() == &images[9] &&
                                sprites[highlighted_row][highlighted_col + 2].getTexture() == &images[2] &&
                                (sprites[highlighted_row][highlighted_col + 3].getTexture() == &images[2]) ||
                                sprites[highlighted_row][highlighted_col].getTexture() == &images[10] &&
                                sprites[highlighted_row][highlighted_col + 2].getTexture() == &images[3] &&
                                sprites[highlighted_row][highlighted_col + 3].getTexture() == &images[3]) ||
                            (sprites[highlighted_row][highlighted_col].getTexture() == &images[11] &&
                                sprites[highlighted_row][highlighted_col + 2].getTexture() == &images[4] &&
                                sprites[highlighted_row][highlighted_col + 3].getTexture() == &images[4]) ||
                            (sprites[highlighted_row][highlighted_col].getTexture() == &images[12] &&
                                sprites[highlighted_row][highlighted_col + 2].getTexture() == &images[5] &&
                                sprites[highlighted_row][highlighted_col + 3].getTexture() == &images[5]) ||
                            (sprites[highlighted_row][highlighted_col].getTexture() == &images[13] &&
                                sprites[highlighted_row][highlighted_col + 2].getTexture() == &images[6] &&
                                sprites[highlighted_row][highlighted_col + 3].getTexture() == &images[6]))
                        {
                            Sprite temp = sprites[highlighted_row][highlighted_col];
                            sprites[highlighted_row][highlighted_col] = sprites[highlighted_row][highlighted_col + 1];
                            sprites[highlighted_row][highlighted_col + 1] = temp;
                            // Update positions after swapping
                            sprites[highlighted_row][highlighted_col].setPosition((highlighted_col * gemSize) + off_setX, (highlighted_row * gemSize) + off_setY);
                            sprites[highlighted_row][highlighted_col + 1].setPosition(((highlighted_col + 1) * gemSize) + off_setX, ((highlighted_row)*gemSize) + off_setY);
                            score = score + score_4_special;
                            scoreText.setString("Score: " + std::to_string(score));
                            specialRealFourRight = true;
                        }

                        else if ((sprites[highlighted_row][highlighted_col].getTexture() == &images[0] &&
                            sprites[highlighted_row - 1][highlighted_col + 1].getTexture() == &images[14] &&
                            sprites[highlighted_row - 2][highlighted_col + 1].getTexture() == &images[0]) ||
                            (sprites[highlighted_row][highlighted_col].getTexture() == &images[1] &&
                                sprites[highlighted_row - 1][highlighted_col + 1].getTexture() == &images[15] &&
                                sprites[highlighted_row - 2][highlighted_col + 1].getTexture() == &images[1]) ||
                            (sprites[highlighted_row][highlighted_col].getTexture() == &images[2] &&
                                sprites[highlighted_row - 1][highlighted_col + 1].getTexture() == &images[16] &&
                                (sprites[highlighted_row - 2][highlighted_col + 1].getTexture() == &images[2]) ||
                                sprites[highlighted_row][highlighted_col].getTexture() == &images[3] &&
                                sprites[highlighted_row - 1][highlighted_col + 1].getTexture() == &images[17] &&
                                sprites[highlighted_row - 2][highlighted_col + 1].getTexture() == &images[3]) ||
                            (sprites[highlighted_row][highlighted_col].getTexture() == &images[4] &&
                                sprites[highlighted_row - 1][highlighted_col + 1].getTexture() == &images[18] &&
                                sprites[highlighted_row - 2][highlighted_col + 1].getTexture() == &images[4]) ||
                            (sprites[highlighted_row][highlighted_col].getTexture() == &images[5] &&
                                sprites[highlighted_row - 1][highlighted_col + 1].getTexture() == &images[19] &&
                                sprites[highlighted_row - 2][highlighted_col + 1].getTexture() == &images[5]) ||
                            (sprites[highlighted_row][highlighted_col].getTexture() == &images[6] &&
                                sprites[highlighted_row - 1][highlighted_col + 1].getTexture() == &images[20] &&
                                sprites[highlighted_row - 2][highlighted_col + 1].getTexture() == &images[6]))
                        {
                            specialRow = highlighted_row - 1;
                            specialCol = highlighted_col + 1;


                            Sprite temp = sprites[highlighted_row][highlighted_col];
                            sprites[highlighted_row][highlighted_col] = sprites[highlighted_row][highlighted_col + 1];
                            sprites[highlighted_row][highlighted_col + 1] = temp;
                            // Update positions after swapping
                            sprites[highlighted_row][highlighted_col].setPosition((highlighted_col * gemSize) + off_setX, (highlighted_row * gemSize) + off_setY);
                            sprites[highlighted_row][highlighted_col + 1].setPosition(((highlighted_col + 1) * gemSize) + off_setX, ((highlighted_row)*gemSize) + off_setY);
                            score = score + score_5_special;
                            scoreText.setString("Score: " + std::to_string(score));
                            specialFive = true;

                        }

                        else if ((sprites[highlighted_row][highlighted_col].getTexture() == &images[0] &&
                            sprites[highlighted_row - 1][highlighted_col + 1].getTexture() == &images[0] &&
                            sprites[highlighted_row - 2][highlighted_col + 1].getTexture() == &images[14]) ||
                            (sprites[highlighted_row][highlighted_col].getTexture() == &images[1] &&
                                sprites[highlighted_row - 1][highlighted_col + 1].getTexture() == &images[1] &&
                                sprites[highlighted_row - 2][highlighted_col + 1].getTexture() == &images[15]) ||
                            (sprites[highlighted_row][highlighted_col].getTexture() == &images[2] &&
                                sprites[highlighted_row - 1][highlighted_col + 1].getTexture() == &images[2] &&
                                (sprites[highlighted_row - 2][highlighted_col + 1].getTexture() == &images[16]) ||
                                sprites[highlighted_row][highlighted_col].getTexture() == &images[3] &&
                                sprites[highlighted_row - 1][highlighted_col + 1].getTexture() == &images[3] &&
                                sprites[highlighted_row - 2][highlighted_col + 1].getTexture() == &images[17]) ||
                            (sprites[highlighted_row][highlighted_col].getTexture() == &images[4] &&
                                sprites[highlighted_row - 1][highlighted_col + 1].getTexture() == &images[4] &&
                                sprites[highlighted_row - 2][highlighted_col + 1].getTexture() == &images[18]) ||
                            (sprites[highlighted_row][highlighted_col].getTexture() == &images[5] &&
                                sprites[highlighted_row - 1][highlighted_col + 1].getTexture() == &images[5] &&
                                sprites[highlighted_row - 2][highlighted_col + 1].getTexture() == &images[19]) ||
                            (sprites[highlighted_row][highlighted_col].getTexture() == &images[6] &&
                                sprites[highlighted_row - 1][highlighted_col + 1].getTexture() == &images[6] &&
                                sprites[highlighted_row - 2][highlighted_col + 1].getTexture() == &images[20]))
                        {
                            specialRow = highlighted_row - 2;
                            specialCol = highlighted_col + 1;


                            Sprite temp = sprites[highlighted_row][highlighted_col];
                            sprites[highlighted_row][highlighted_col] = sprites[highlighted_row][highlighted_col + 1];
                            sprites[highlighted_row][highlighted_col + 1] = temp;
                            // Update positions after swapping
                            sprites[highlighted_row][highlighted_col].setPosition((highlighted_col * gemSize) + off_setX, (highlighted_row * gemSize) + off_setY);
                            sprites[highlighted_row][highlighted_col + 1].setPosition(((highlighted_col + 1) * gemSize) + off_setX, ((highlighted_row)*gemSize) + off_setY);
                            score = score + score_5_special;
                            scoreText.setString("Score: " + std::to_string(score));
                            specialFive = true;
                        }

                        else if ((sprites[highlighted_row][highlighted_col].getTexture() == &images[0] &&
                            sprites[highlighted_row + 1][highlighted_col + 1].getTexture() == &images[14] &&
                            sprites[highlighted_row + 2][highlighted_col + 1].getTexture() == &images[0]) ||
                            (sprites[highlighted_row][highlighted_col].getTexture() == &images[1] &&
                                sprites[highlighted_row + 1][highlighted_col + 1].getTexture() == &images[15] &&
                                sprites[highlighted_row + 2][highlighted_col + 1].getTexture() == &images[1]) ||
                            (sprites[highlighted_row][highlighted_col].getTexture() == &images[2] &&
                                sprites[highlighted_row + 1][highlighted_col + 1].getTexture() == &images[16] &&
                                (sprites[highlighted_row + 2][highlighted_col + 1].getTexture() == &images[2]) ||
                                sprites[highlighted_row][highlighted_col].getTexture() == &images[3] &&
                                sprites[highlighted_row + 1][highlighted_col + 1].getTexture() == &images[17] &&
                                sprites[highlighted_row + 2][highlighted_col + 1].getTexture() == &images[3]) ||
                            (sprites[highlighted_row][highlighted_col].getTexture() == &images[4] &&
                                sprites[highlighted_row + 1][highlighted_col + 1].getTexture() == &images[18] &&
                                sprites[highlighted_row + 2][highlighted_col + 1].getTexture() == &images[4]) ||
                            (sprites[highlighted_row][highlighted_col].getTexture() == &images[5] &&
                                sprites[highlighted_row + 1][highlighted_col + 1].getTexture() == &images[19] &&
                                sprites[highlighted_row + 2][highlighted_col + 1].getTexture() == &images[5]) ||
                            (sprites[highlighted_row][highlighted_col].getTexture() == &images[6] &&
                                sprites[highlighted_row + 1][highlighted_col + 1].getTexture() == &images[20] &&
                                sprites[highlighted_row + 2][highlighted_col + 1].getTexture() == &images[6]))
                        {
                            specialRow = highlighted_row + 1;
                            specialCol = highlighted_col + 1;


                            Sprite temp = sprites[highlighted_row][highlighted_col];
                            sprites[highlighted_row][highlighted_col] = sprites[highlighted_row][highlighted_col + 1];
                            sprites[highlighted_row][highlighted_col + 1] = temp;
                            // Update positions after swapping
                            sprites[highlighted_row][highlighted_col].setPosition((highlighted_col * gemSize) + off_setX, (highlighted_row * gemSize) + off_setY);
                            sprites[highlighted_row][highlighted_col + 1].setPosition(((highlighted_col + 1) * gemSize) + off_setX, ((highlighted_row)*gemSize) + off_setY);
                            score = score + score_5_special;
                            scoreText.setString("Score: " + std::to_string(score));
                            specialFive = true;
                        }

                        else if ((sprites[highlighted_row][highlighted_col].getTexture() == &images[0] &&
                            sprites[highlighted_row + 1][highlighted_col + 1].getTexture() == &images[0] &&
                            sprites[highlighted_row + 2][highlighted_col + 1].getTexture() == &images[14]) ||
                            (sprites[highlighted_row][highlighted_col].getTexture() == &images[1] &&
                                sprites[highlighted_row + 1][highlighted_col + 1].getTexture() == &images[1] &&
                                sprites[highlighted_row + 2][highlighted_col + 1].getTexture() == &images[15]) ||
                            (sprites[highlighted_row][highlighted_col].getTexture() == &images[2] &&
                                sprites[highlighted_row + 1][highlighted_col + 1].getTexture() == &images[2] &&
                                (sprites[highlighted_row + 2][highlighted_col + 1].getTexture() == &images[16]) ||
                                sprites[highlighted_row][highlighted_col].getTexture() == &images[3] &&
                                sprites[highlighted_row + 1][highlighted_col + 1].getTexture() == &images[3] &&
                                sprites[highlighted_row + 2][highlighted_col + 1].getTexture() == &images[17]) ||
                            (sprites[highlighted_row][highlighted_col].getTexture() == &images[4] &&
                                sprites[highlighted_row + 1][highlighted_col + 1].getTexture() == &images[4] &&
                                sprites[highlighted_row + 2][highlighted_col + 1].getTexture() == &images[18]) ||
                            (sprites[highlighted_row][highlighted_col].getTexture() == &images[5] &&
                                sprites[highlighted_row + 1][highlighted_col + 1].getTexture() == &images[5] &&
                                sprites[highlighted_row + 2][highlighted_col + 1].getTexture() == &images[19]) ||
                            (sprites[highlighted_row][highlighted_col].getTexture() == &images[6] &&
                                sprites[highlighted_row + 1][highlighted_col + 1].getTexture() == &images[6] &&
                                sprites[highlighted_row + 2][highlighted_col + 1].getTexture() == &images[20]))
                        {
                            specialRow = highlighted_row + 2;
                            specialCol = highlighted_col + 1;


                            Sprite temp = sprites[highlighted_row][highlighted_col];
                            sprites[highlighted_row][highlighted_col] = sprites[highlighted_row][highlighted_col + 1];
                            sprites[highlighted_row][highlighted_col + 1] = temp;
                            // Update positions after swapping
                            sprites[highlighted_row][highlighted_col].setPosition((highlighted_col * gemSize) + off_setX, (highlighted_row * gemSize) + off_setY);
                            sprites[highlighted_row][highlighted_col + 1].setPosition(((highlighted_col + 1) * gemSize) + off_setX, ((highlighted_row)*gemSize) + off_setY);
                            score = score + score_5_special;
                            scoreText.setString("Score: " + std::to_string(score));
                            specialFive = true;
                        }

                        else if ((sprites[highlighted_row][highlighted_col].getTexture() == &images[0] &&
                            sprites[highlighted_row + 1][highlighted_col + 1].getTexture() == &images[0] &&
                            sprites[highlighted_row - 1][highlighted_col + 1].getTexture() == &images[14]) ||
                            (sprites[highlighted_row][highlighted_col].getTexture() == &images[1] &&
                                sprites[highlighted_row + 1][highlighted_col + 1].getTexture() == &images[1] &&
                                sprites[highlighted_row - 1][highlighted_col + 1].getTexture() == &images[15]) ||
                            (sprites[highlighted_row][highlighted_col].getTexture() == &images[2] &&
                                sprites[highlighted_row + 1][highlighted_col + 1].getTexture() == &images[2] &&
                                (sprites[highlighted_row - 1][highlighted_col + 1].getTexture() == &images[16]) ||
                                sprites[highlighted_row][highlighted_col].getTexture() == &images[3] &&
                                sprites[highlighted_row + 1][highlighted_col + 1].getTexture() == &images[3] &&
                                sprites[highlighted_row - 1][highlighted_col + 1].getTexture() == &images[17]) ||
                            (sprites[highlighted_row][highlighted_col].getTexture() == &images[4] &&
                                sprites[highlighted_row + 1][highlighted_col + 1].getTexture() == &images[4] &&
                                sprites[highlighted_row - 1][highlighted_col + 1].getTexture() == &images[18]) ||
                            (sprites[highlighted_row][highlighted_col].getTexture() == &images[5] &&
                                sprites[highlighted_row + 1][highlighted_col + 1].getTexture() == &images[5] &&
                                sprites[highlighted_row - 1][highlighted_col + 1].getTexture() == &images[19]) ||
                            (sprites[highlighted_row][highlighted_col].getTexture() == &images[6] &&
                                sprites[highlighted_row + 1][highlighted_col + 1].getTexture() == &images[6] &&
                                sprites[highlighted_row - 1][highlighted_col + 1].getTexture() == &images[20]))
                        {
                            specialRow = highlighted_row - 1;
                            specialCol = highlighted_col + 1;


                            Sprite temp = sprites[highlighted_row][highlighted_col];
                            sprites[highlighted_row][highlighted_col] = sprites[highlighted_row][highlighted_col + 1];
                            sprites[highlighted_row][highlighted_col + 1] = temp;
                            // Update positions after swapping
                            sprites[highlighted_row][highlighted_col].setPosition((highlighted_col * gemSize) + off_setX, (highlighted_row * gemSize) + off_setY);
                            sprites[highlighted_row][highlighted_col + 1].setPosition(((highlighted_col + 1) * gemSize) + off_setX, ((highlighted_row)*gemSize) + off_setY);;
                            score = score + score_5_special;
                            scoreText.setString("Score: " + std::to_string(score));
                            specialFive = true;
                        }

                        else if ((sprites[highlighted_row][highlighted_col].getTexture() == &images[0] &&
                            sprites[highlighted_row + 1][highlighted_col + 1].getTexture() == &images[14] &&
                            sprites[highlighted_row - 1][highlighted_col + 1].getTexture() == &images[0]) ||
                            (sprites[highlighted_row][highlighted_col].getTexture() == &images[1] &&
                                sprites[highlighted_row + 1][highlighted_col + 1].getTexture() == &images[15] &&
                                sprites[highlighted_row - 1][highlighted_col + 1].getTexture() == &images[1]) ||
                            (sprites[highlighted_row][highlighted_col].getTexture() == &images[2] &&
                                sprites[highlighted_row + 1][highlighted_col + 1].getTexture() == &images[16] &&
                                (sprites[highlighted_row - 1][highlighted_col + 1].getTexture() == &images[2]) ||
                                sprites[highlighted_row][highlighted_col].getTexture() == &images[3] &&
                                sprites[highlighted_row + 1][highlighted_col + 1].getTexture() == &images[17] &&
                                sprites[highlighted_row - 1][highlighted_col + 1].getTexture() == &images[3]) ||
                            (sprites[highlighted_row][highlighted_col].getTexture() == &images[4] &&
                                sprites[highlighted_row + 1][highlighted_col + 1].getTexture() == &images[18] &&
                                sprites[highlighted_row - 1][highlighted_col + 1].getTexture() == &images[4]) ||
                            (sprites[highlighted_row][highlighted_col].getTexture() == &images[5] &&
                                sprites[highlighted_row + 1][highlighted_col + 1].getTexture() == &images[19] &&
                                sprites[highlighted_row - 1][highlighted_col + 1].getTexture() == &images[5]) ||
                            (sprites[highlighted_row][highlighted_col].getTexture() == &images[6] &&
                                sprites[highlighted_row + 1][highlighted_col + 1].getTexture() == &images[20] &&
                                sprites[highlighted_row - 1][highlighted_col + 1].getTexture() == &images[6]))
                        {
                            specialRow = highlighted_row + 1;
                            specialCol = highlighted_col + 1;


                            Sprite temp = sprites[highlighted_row][highlighted_col];
                            sprites[highlighted_row][highlighted_col] = sprites[highlighted_row][highlighted_col + 1];
                            sprites[highlighted_row][highlighted_col + 1] = temp;
                            // Update positions after swapping
                            sprites[highlighted_row][highlighted_col].setPosition((highlighted_col * gemSize) + off_setX, (highlighted_row * gemSize) + off_setY);
                            sprites[highlighted_row][highlighted_col + 1].setPosition(((highlighted_col + 1) * gemSize) + off_setX, ((highlighted_row)*gemSize) + off_setY);
                            score = score + score_5_special;
                            scoreText.setString("Score: " + std::to_string(score));
                            specialFive = true;
                        }

                        else if ((sprites[highlighted_row][highlighted_col].getTexture() == &images[14] &&
                            sprites[highlighted_row - 1][highlighted_col + 1].getTexture() == &images[0] &&
                            sprites[highlighted_row - 2][highlighted_col + 1].getTexture() == &images[0]) ||
                            (sprites[highlighted_row][highlighted_col].getTexture() == &images[15] &&
                                sprites[highlighted_row - 1][highlighted_col + 1].getTexture() == &images[1] &&
                                sprites[highlighted_row - 2][highlighted_col + 1].getTexture() == &images[1]) ||
                            (sprites[highlighted_row][highlighted_col].getTexture() == &images[16] &&
                                sprites[highlighted_row - 1][highlighted_col + 1].getTexture() == &images[2] &&
                                (sprites[highlighted_row - 2][highlighted_col + 1].getTexture() == &images[2]) ||
                                sprites[highlighted_row][highlighted_col].getTexture() == &images[17] &&
                                sprites[highlighted_row - 1][highlighted_col + 1].getTexture() == &images[3] &&
                                sprites[highlighted_row - 2][highlighted_col + 1].getTexture() == &images[3]) ||
                            (sprites[highlighted_row][highlighted_col].getTexture() == &images[18] &&
                                sprites[highlighted_row - 1][highlighted_col + 1].getTexture() == &images[4] &&
                                sprites[highlighted_row - 2][highlighted_col + 1].getTexture() == &images[4]) ||
                            (sprites[highlighted_row][highlighted_col].getTexture() == &images[19] &&
                                sprites[highlighted_row - 1][highlighted_col + 1].getTexture() == &images[5] &&
                                sprites[highlighted_row - 2][highlighted_col + 1].getTexture() == &images[5]) ||
                            (sprites[highlighted_row][highlighted_col].getTexture() == &images[20] &&
                                sprites[highlighted_row - 1][highlighted_col + 1].getTexture() == &images[6] &&
                                sprites[highlighted_row - 2][highlighted_col + 1].getTexture() == &images[6]))
                        {
                            specialRow = highlighted_row;
                            specialCol = highlighted_col + 1;


                            Sprite temp = sprites[highlighted_row][highlighted_col];
                            sprites[highlighted_row][highlighted_col] = sprites[highlighted_row][highlighted_col + 1];
                            sprites[highlighted_row][highlighted_col + 1] = temp;
                            // Update positions after swapping
                            sprites[highlighted_row][highlighted_col].setPosition((highlighted_col * gemSize) + off_setX, (highlighted_row * gemSize) + off_setY);
                            sprites[highlighted_row][highlighted_col + 1].setPosition(((highlighted_col + 1) * gemSize) + off_setX, ((highlighted_row)*gemSize) + off_setY);
                            score = score + score_5_special;
                            scoreText.setString("Score: " + std::to_string(score));
                            specialFive = true;
                        }

                        else if ((sprites[highlighted_row][highlighted_col].getTexture() == &images[14] &&
                            sprites[highlighted_row + 1][highlighted_col + 1].getTexture() == &images[0] &&
                            sprites[highlighted_row + 2][highlighted_col + 1].getTexture() == &images[0]) ||
                            (sprites[highlighted_row][highlighted_col].getTexture() == &images[15] &&
                                sprites[highlighted_row + 1][highlighted_col + 1].getTexture() == &images[1] &&
                                sprites[highlighted_row + 2][highlighted_col + 1].getTexture() == &images[1]) ||
                            (sprites[highlighted_row][highlighted_col].getTexture() == &images[16] &&
                                sprites[highlighted_row + 1][highlighted_col + 1].getTexture() == &images[2] &&
                                (sprites[highlighted_row + 2][highlighted_col + 1].getTexture() == &images[2]) ||
                                sprites[highlighted_row][highlighted_col].getTexture() == &images[17] &&
                                sprites[highlighted_row + 1][highlighted_col + 1].getTexture() == &images[3] &&
                                sprites[highlighted_row + 2][highlighted_col + 1].getTexture() == &images[3]) ||
                            (sprites[highlighted_row][highlighted_col].getTexture() == &images[18] &&
                                sprites[highlighted_row + 1][highlighted_col + 1].getTexture() == &images[4] &&
                                sprites[highlighted_row + 2][highlighted_col + 1].getTexture() == &images[4]) ||
                            (sprites[highlighted_row][highlighted_col].getTexture() == &images[19] &&
                                sprites[highlighted_row + 1][highlighted_col + 1].getTexture() == &images[5] &&
                                sprites[highlighted_row + 2][highlighted_col + 1].getTexture() == &images[5]) ||
                            (sprites[highlighted_row][highlighted_col].getTexture() == &images[20] &&
                                sprites[highlighted_row + 1][highlighted_col + 1].getTexture() == &images[6] &&
                                sprites[highlighted_row + 2][highlighted_col + 1].getTexture() == &images[6]))
                        {
                            specialRow = highlighted_row;
                            specialCol = highlighted_col + 1;


                            Sprite temp = sprites[highlighted_row][highlighted_col];
                            sprites[highlighted_row][highlighted_col] = sprites[highlighted_row][highlighted_col + 1];
                            sprites[highlighted_row][highlighted_col + 1] = temp;
                            // Update positions after swapping
                            sprites[highlighted_row][highlighted_col].setPosition((highlighted_col * gemSize) + off_setX, (highlighted_row * gemSize) + off_setY);
                            sprites[highlighted_row][highlighted_col + 1].setPosition(((highlighted_col + 1) * gemSize) + off_setX, ((highlighted_row)*gemSize) + off_setY);
                            score = score + score_5_special;
                            scoreText.setString("Score: " + std::to_string(score));
                            specialFive = true;
                        }


                        else if ((sprites[highlighted_row][highlighted_col].getTexture() == &images[14] &&
                            sprites[highlighted_row + 1][highlighted_col + 1].getTexture() == &images[0] &&
                            sprites[highlighted_row - 1][highlighted_col + 1].getTexture() == &images[0]) ||
                            (sprites[highlighted_row][highlighted_col].getTexture() == &images[15] &&
                                sprites[highlighted_row + 1][highlighted_col + 1].getTexture() == &images[1] &&
                                sprites[highlighted_row - 1][highlighted_col + 1].getTexture() == &images[1]) ||
                            (sprites[highlighted_row][highlighted_col].getTexture() == &images[16] &&
                                sprites[highlighted_row + 1][highlighted_col + 1].getTexture() == &images[2] &&
                                (sprites[highlighted_row - 1][highlighted_col + 1].getTexture() == &images[2]) ||
                                sprites[highlighted_row][highlighted_col].getTexture() == &images[17] &&
                                sprites[highlighted_row + 1][highlighted_col + 1].getTexture() == &images[3] &&
                                sprites[highlighted_row - 1][highlighted_col + 1].getTexture() == &images[3]) ||
                            (sprites[highlighted_row][highlighted_col].getTexture() == &images[18] &&
                                sprites[highlighted_row + 1][highlighted_col + 1].getTexture() == &images[4] &&
                                sprites[highlighted_row - 1][highlighted_col + 1].getTexture() == &images[4]) ||
                            (sprites[highlighted_row][highlighted_col].getTexture() == &images[19] &&
                                sprites[highlighted_row + 1][highlighted_col + 1].getTexture() == &images[5] &&
                                sprites[highlighted_row - 1][highlighted_col + 1].getTexture() == &images[5]) ||
                            (sprites[highlighted_row][highlighted_col].getTexture() == &images[20] &&
                                sprites[highlighted_row + 1][highlighted_col + 1].getTexture() == &images[6] &&
                                sprites[highlighted_row - 1][highlighted_col + 1].getTexture() == &images[6]))
                        {
                            specialRow = highlighted_row;
                            specialCol = highlighted_col + 1;

                            Sprite temp = sprites[highlighted_row][highlighted_col];
                            sprites[highlighted_row][highlighted_col] = sprites[highlighted_row][highlighted_col + 1];
                            sprites[highlighted_row][highlighted_col + 1] = temp;
                            // Update positions after swapping
                            sprites[highlighted_row][highlighted_col].setPosition((highlighted_col * gemSize) + off_setX, (highlighted_row * gemSize) + off_setY);
                            sprites[highlighted_row][highlighted_col + 1].setPosition(((highlighted_col + 1) * gemSize) + off_setX, ((highlighted_row)*gemSize) + off_setY);
                            score = score + score_5_special;
                            scoreText.setString("Score: " + std::to_string(score));
                            specialFive = true;
                        }

                        else if ((sprites[highlighted_row][highlighted_col].getTexture() == &images[14] &&
                            sprites[highlighted_row][highlighted_col + 2].getTexture() == &images[0] &&
                            sprites[highlighted_row][highlighted_col + 3].getTexture() == &images[0]) ||
                            (sprites[highlighted_row][highlighted_col].getTexture() == &images[15] &&
                                sprites[highlighted_row][highlighted_col + 2].getTexture() == &images[1] &&
                                sprites[highlighted_row][highlighted_col + 3].getTexture() == &images[1]) ||
                            (sprites[highlighted_row][highlighted_col].getTexture() == &images[16] &&
                                sprites[highlighted_row][highlighted_col + 2].getTexture() == &images[2] &&
                                (sprites[highlighted_row][highlighted_col + 3].getTexture() == &images[2]) ||
                                sprites[highlighted_row][highlighted_col].getTexture() == &images[17] &&
                                sprites[highlighted_row][highlighted_col + 2].getTexture() == &images[3] &&
                                sprites[highlighted_row][highlighted_col + 3].getTexture() == &images[3]) ||
                            (sprites[highlighted_row][highlighted_col].getTexture() == &images[18] &&
                                sprites[highlighted_row][highlighted_col + 2].getTexture() == &images[4] &&
                                sprites[highlighted_row][highlighted_col + 3].getTexture() == &images[4]) ||
                            (sprites[highlighted_row][highlighted_col].getTexture() == &images[19] &&
                                sprites[highlighted_row][highlighted_col + 2].getTexture() == &images[5] &&
                                sprites[highlighted_row][highlighted_col + 3].getTexture() == &images[5]) ||
                            (sprites[highlighted_row][highlighted_col].getTexture() == &images[20] &&
                                sprites[highlighted_row][highlighted_col + 2].getTexture() == &images[6] &&
                                sprites[highlighted_row][highlighted_col + 3].getTexture() == &images[6]))
                        {
                            specialRow = highlighted_row;
                            specialCol = highlighted_col + 1;



                            Sprite temp = sprites[highlighted_row][highlighted_col];
                            sprites[highlighted_row][highlighted_col] = sprites[highlighted_row][highlighted_col + 1];
                            sprites[highlighted_row][highlighted_col + 1] = temp;
                            // Update positions after swapping
                            sprites[highlighted_row][highlighted_col].setPosition((highlighted_col * gemSize) + off_setX, (highlighted_row * gemSize) + off_setY);
                            sprites[highlighted_row][highlighted_col + 1].setPosition(((highlighted_col + 1) * gemSize) + off_setX, ((highlighted_row)*gemSize) + off_setY);
                            score = score + score_5_special;
                            scoreText.setString("Score: " + std::to_string(score));
                            specialFive = true;
                        }



                    }
                    highlighted_col++;
                    enter_key_pressed = false;
                    swap_triggered = false;
                }
                    if (event.key.code == Keyboard::R)
                    {
                       for (int i = 0; i < 8; i++)
                       {
                            for (int j = 0; j < 8; j++)
                            {
                            sprites[i][j].setTexture(images[rand() % 7]);
                            }
                       }
                    }
            }
        }
        if (isGameRunning) {
            // Time logic: Update timer
            sf::Time elapsed = gameClock.getElapsedTime();
            int remainingSeconds = gameTimeLimit - static_cast<int>(elapsed.asSeconds());

            if (remainingSeconds <= 0) {
                remainingSeconds = 0;
                isGameRunning = false; // Trigger game-over logic or other actions when time runs out
                window.close();
                RenderWindow gameOverWindow(sf::VideoMode(790, 490), "SCORE");
                Text gameOverText;
                gameOverText.setFont(font);
                gameOverText.setCharacterSize(30);
                gameOverText.setFillColor(sf::Color::Red);
                gameOverText.setString("Game Over\nYour Score: 100"); // Replace 100 with actual score
                gameOverText.setPosition(50.f, 50.f);
            }

            // Update timer text
            startText.setString("Time: " + std::to_string(remainingSeconds) + " seconds");
        }



        for (int i = 0; i < 8; i++)
        {
            for (int j = 0; j < 6; j++) // Check until the 6th column to avoid accessing j+2
            {
                if ((sprites[i][j].getTexture() == sprites[i][j + 1].getTexture()) &&
                    (sprites[i][j + 1].getTexture() == sprites[i][j + 2].getTexture()))
                {
                    isGemEmpty[i][j] = true;
                    isGemEmpty[i][j + 1] = true;
                    isGemEmpty[i][j + 2] = true;
                    //match_found = true;
                }
            }
        }

        for (int i = 0; i < 6; i++)
        {
            for (int j = 0; j < 8; j++)
            {
                if ((sprites[i][j].getTexture() == sprites[i + 1][j].getTexture()) &&
                    (sprites[i + 1][j].getTexture() == sprites[i + 2][j].getTexture()))
                {
                    isGemEmpty[i][j] = true;
                    isGemEmpty[i + 1][j] = true;
                    isGemEmpty[i + 2][j] = true;
                 
                }
            }
        }

        empty_texture.create(50, 50);
        for (int i = 0; i < 8; i++)
        {
            for (int j = 0; j < 8; j++)
            {
                if (isGemEmpty[i][j])
                {
                    // Remove the gems
                    sprites[i][j].setTexture(empty_texture);
                }
            }
        }

        for (int i = 0; i < 8; i++)
        {
            for (int j = 0; j < 8; j++)
            {
                if (isGemEmpty[i][j])
                {
                    // Refill the spot with a new gem
                    sprites[i][j].setTexture(images[rand() % 7]);
                    // Assuming 7 types of gems
                }

            }
        }

        // Clear the gem removal flags
        for (int i = 0; i < 8; i++)
        {
            for (int j = 0; j < 8; j++)
            {
                isGemEmpty[i][j] = false;
            }
        }

        if (matchFiveUp)
        {
            if (tempSprites[indexUp1][indexUp2].getTexture() == &images[0])
            {
                sprites[highlighted_row][highlighted_col].setTexture(images[14]);
            }

            else if (tempSprites[indexUp1][indexUp2].getTexture() == &images[1])
            {
                sprites[highlighted_row][highlighted_col].setTexture(images[15]);
            }

            else if (tempSprites[indexUp1][indexUp2].getTexture() == &images[2])
            {
                sprites[highlighted_row][highlighted_col].setTexture(images[16]);
            }

            else if (tempSprites[indexUp1][indexUp2].getTexture() == &images[3])
            {
                sprites[highlighted_row][highlighted_col].setTexture(images[17]);
            }

            else if (tempSprites[indexUp1][indexUp2].getTexture() == &images[4])
            {
                sprites[highlighted_row][highlighted_col].setTexture(images[18]);
            }

            else if (tempSprites[indexUp1][indexUp2].getTexture() == &images[5])
            {
                sprites[highlighted_row][highlighted_col].setTexture(images[19]);
            }

            else if (tempSprites[indexUp1][indexUp2].getTexture() == &images[6])
            {
                sprites[highlighted_row][highlighted_col].setTexture(images[20]);
            }

            matchFiveUp = false;
        }

        if (matchFourUp)
        {
            if (tempSprites[indexUp1][indexUp2].getTexture() == &images[0])
            {
                sprites[highlighted_row][highlighted_col].setTexture(images[7]);
            }

            else if (tempSprites[indexUp1][indexUp2].getTexture() == &images[1])
            {
                sprites[highlighted_row][highlighted_col].setTexture(images[8]);
            }

            else if (tempSprites[indexUp1][indexUp2].getTexture() == &images[2])
            {
                sprites[highlighted_row][highlighted_col].setTexture(images[9]);

            }

            else if (tempSprites[indexUp1][indexUp2].getTexture() == &images[3])
            {
                sprites[highlighted_row][highlighted_col].setTexture(images[10]);

            }

            else if (tempSprites[indexUp1][indexUp2].getTexture() == &images[4])
            {
                sprites[highlighted_row][highlighted_col].setTexture(images[11]);

            }

            else if (tempSprites[indexUp1][indexUp2].getTexture() == &images[5])
            {
                sprites[highlighted_row][highlighted_col].setTexture(images[12]);

            }

            else if (tempSprites[indexUp1][indexUp2].getTexture() == &images[6])
            {
                sprites[highlighted_row][highlighted_col].setTexture(images[13]);

            }

            matchFourUp = false;
        }

        if (matchFiveDown)
        {
            if (tempSprites[indexDown1][indexDown2].getTexture() == &images[0])
            {
                sprites[highlighted_row][highlighted_col].setTexture(images[14]);
            }

            else if (tempSprites[indexDown1][indexDown2].getTexture() == &images[1])
            {
                sprites[highlighted_row][highlighted_col].setTexture(images[15]);
            }

            else if (tempSprites[indexDown1][indexDown2].getTexture() == &images[2])
            {
                sprites[highlighted_row][highlighted_col].setTexture(images[16]);
            }

            else if (tempSprites[indexDown1][indexDown2].getTexture() == &images[3])
            {
                sprites[highlighted_row][highlighted_col].setTexture(images[17]);
            }

            else if (tempSprites[indexDown1][indexDown2].getTexture() == &images[4])
            {
                sprites[highlighted_row][highlighted_col].setTexture(images[18]);
            }

            else if (tempSprites[indexDown1][indexDown2].getTexture() == &images[5])
            {
                sprites[highlighted_row][highlighted_col].setTexture(images[19]);
            }

            else if (tempSprites[indexDown1][indexDown2].getTexture() == &images[6])
            {
                sprites[highlighted_row][highlighted_col].setTexture(images[20]);
            }

            matchFiveDown = false;
        }

        if (matchFourDown)
        {
            if (tempSprites[indexDown1][indexDown2].getTexture() == &images[0])
            {
                sprites[highlighted_row][highlighted_col].setTexture(images[7]);
            }

            else if (tempSprites[indexDown1][indexDown2].getTexture() == &images[1])
            {
                sprites[highlighted_row][highlighted_col].setTexture(images[8]);
            }

            else if (tempSprites[indexDown1][indexDown2].getTexture() == &images[2])
            {
                sprites[highlighted_row][highlighted_col].setTexture(images[9]);
            }

            else if (tempSprites[indexDown1][indexDown2].getTexture() == &images[3])
            {
                sprites[highlighted_row][highlighted_col].setTexture(images[10]);
            }

            else if (tempSprites[indexDown1][indexDown2].getTexture() == &images[4])
            {
                sprites[highlighted_row][highlighted_col].setTexture(images[11]);
            }

            else if (tempSprites[indexDown1][indexDown2].getTexture() == &images[5])
            {
                sprites[highlighted_row][highlighted_col].setTexture(images[12]);
            }

            else if (tempSprites[indexDown1][indexDown2].getTexture() == &images[6])
            {
                sprites[highlighted_row][highlighted_col].setTexture(images[13]);
            }

            matchFourDown = false;
        }

        if (matchFiveLeft)
        {
            if (tempSprites[indexLeft1][indexLeft2].getTexture() == &images[0])
            {
                sprites[highlighted_row][highlighted_col].setTexture(images[14]);
            }

            else if (tempSprites[indexLeft1][indexLeft2].getTexture() == &images[1])
            {
                sprites[highlighted_row][highlighted_col].setTexture(images[15]);
            }

            else if (tempSprites[indexLeft1][indexLeft2].getTexture() == &images[2])
            {
                sprites[highlighted_row][highlighted_col].setTexture(images[16]);
            }

            else if (tempSprites[indexLeft1][indexLeft2].getTexture() == &images[3])
            {
                sprites[highlighted_row][highlighted_col].setTexture(images[17]);
            }

            else if (tempSprites[indexLeft1][indexLeft2].getTexture() == &images[4])
            {
                sprites[highlighted_row][highlighted_col].setTexture(images[18]);
            }

            else if (tempSprites[indexLeft1][indexLeft2].getTexture() == &images[5])
            {
                sprites[highlighted_row][highlighted_col].setTexture(images[19]);
            }

            else if (tempSprites[indexLeft1][indexLeft2].getTexture() == &images[6])
            {
                sprites[highlighted_row][highlighted_col].setTexture(images[20]);
            }

            matchFiveLeft = false;
        }

        if (matchFourLeft)
        {
            if (tempSprites[indexLeft1][indexLeft2].getTexture() == &images[0])
            {
                sprites[highlighted_row][highlighted_col].setTexture(images[7]);
            }

            else if (tempSprites[indexLeft1][indexLeft2].getTexture() == &images[1])
            {
                sprites[highlighted_row][highlighted_col].setTexture(images[8]);
            }

            else if (tempSprites[indexLeft1][indexLeft2].getTexture() == &images[2])
            {
                sprites[highlighted_row][highlighted_col].setTexture(images[9]);
            }

            else if (tempSprites[indexLeft1][indexLeft2].getTexture() == &images[3])
            {
                sprites[highlighted_row][highlighted_col].setTexture(images[10]);
            }

            else if (tempSprites[indexLeft1][indexLeft2].getTexture() == &images[4])
            {
                sprites[highlighted_row][highlighted_col].setTexture(images[11]);
            }

            else if (tempSprites[indexLeft1][indexLeft2].getTexture() == &images[5])
            {
                sprites[highlighted_row][highlighted_col].setTexture(images[12]);
            }

            else if (tempSprites[indexLeft1][indexLeft2].getTexture() == &images[6])
            {
                sprites[highlighted_row][highlighted_col].setTexture(images[13]);
            }

            matchFourLeft = false;
        }

        if (matchFiveRight)
        {
            if (tempSprites[indexRight1][indexRight2].getTexture() == &images[0])
            {
                sprites[highlighted_row][highlighted_col].setTexture(images[14]);
            }

            else if (tempSprites[indexRight1][indexRight2].getTexture() == &images[1])
            {
                sprites[highlighted_row][highlighted_col].setTexture(images[15]);
            }

            else if (tempSprites[indexRight1][indexRight2].getTexture() == &images[2])
            {
                sprites[highlighted_row][highlighted_col].setTexture(images[16]);
            }

            else if (tempSprites[indexRight1][indexRight2].getTexture() == &images[3])
            {
                sprites[highlighted_row][highlighted_col].setTexture(images[17]);
            }

            else if (tempSprites[indexRight1][indexRight2].getTexture() == &images[4])
            {
                sprites[highlighted_row][highlighted_col].setTexture(images[18]);
            }

            else if (tempSprites[indexRight1][indexRight2].getTexture() == &images[5])
            {
                sprites[highlighted_row][highlighted_col].setTexture(images[19]);
            }

            else if (tempSprites[indexRight1][indexRight2].getTexture() == &images[6])
            {
                sprites[highlighted_row][highlighted_col].setTexture(images[20]);
            }

            matchFiveRight = false;
        }

        if (matchFourRight)
        {
            if (tempSprites[indexRight1][indexRight2].getTexture() == &images[0])
            {
                sprites[highlighted_row][highlighted_col].setTexture(images[7]);
            }

            else if (tempSprites[indexRight1][indexRight2].getTexture() == &images[1])
            {
                sprites[highlighted_row][highlighted_col].setTexture(images[8]);
            }

            else if (tempSprites[indexRight1][indexRight2].getTexture() == &images[2])
            {
                sprites[highlighted_row][highlighted_col].setTexture(images[9]);
            }

            else if (tempSprites[indexRight1][indexRight2].getTexture() == &images[3])
            {
                sprites[highlighted_row][highlighted_col].setTexture(images[10]);
            }

            else if (tempSprites[indexRight1][indexRight2].getTexture() == &images[4])
            {
                sprites[highlighted_row][highlighted_col].setTexture(images[11]);
            }

            else if (tempSprites[indexRight1][indexRight2].getTexture() == &images[5])
            {
                sprites[highlighted_row][highlighted_col].setTexture(images[12]);
            }

            else if (tempSprites[indexRight1][indexRight2].getTexture() == &images[6])
            {
                sprites[highlighted_row][highlighted_col].setTexture(images[13]);
            }

            matchFourRight = false;
        }

        if (destroyUp)
        {
            if (tempSprites[indexUp1][indexUp2].getTexture() == &images[0])
            {
                sprites[highlighted_row][highlighted_col].setTexture(images[14]);
            }

            else if (tempSprites[indexUp1][indexUp2].getTexture() == &images[1])
            {
                sprites[highlighted_row][highlighted_col].setTexture(images[15]);
            }

            else if (tempSprites[indexUp1][indexUp2].getTexture() == &images[2])
            {
                sprites[highlighted_row][highlighted_col].setTexture(images[16]);
            }

            else if (tempSprites[indexUp1][indexUp2].getTexture() == &images[3])
            {
                sprites[highlighted_row][highlighted_col].setTexture(images[17]);
            }

            else if (tempSprites[indexUp1][indexUp2].getTexture() == &images[4])
            {
                sprites[highlighted_row][highlighted_col].setTexture(images[18]);
            }

            else if (tempSprites[indexUp1][indexUp2].getTexture() == &images[5])
            {
                sprites[highlighted_row][highlighted_col].setTexture(images[19]);
            }

            else if (tempSprites[indexUp1][indexUp2].getTexture() == &images[6])
            {
                sprites[highlighted_row][highlighted_col].setTexture(images[20]);
            }

            destroyUp = false;
        }

        if (destroyDown)
        {
            if (tempSprites[indexDown1][indexDown2].getTexture() == &images[0])
            {
                sprites[highlighted_row][highlighted_col].setTexture(images[14]);
            }

            else if (tempSprites[indexDown1][indexDown2].getTexture() == &images[1])
            {
                sprites[highlighted_row][highlighted_col].setTexture(images[15]);
            }

            else if (tempSprites[indexDown1][indexDown2].getTexture() == &images[2])
            {
                sprites[highlighted_row][highlighted_col].setTexture(images[16]);
            }

            else if (tempSprites[indexDown1][indexDown2].getTexture() == &images[3])
            {
                sprites[highlighted_row][highlighted_col].setTexture(images[17]);
            }

            else if (tempSprites[indexDown1][indexDown2].getTexture() == &images[4])
            {
                sprites[highlighted_row][highlighted_col].setTexture(images[18]);
            }

            else if (tempSprites[indexDown1][indexDown2].getTexture() == &images[5])
            {
                sprites[highlighted_row][highlighted_col].setTexture(images[19]);
            }

            else if (tempSprites[indexDown1][indexDown2].getTexture() == &images[6])
            {
                sprites[highlighted_row][highlighted_col].setTexture(images[20]);
            }

            destroyDown = false;
        }

        if (destroyLeft)
        {
            if (tempSprites[indexLeft1][indexLeft2].getTexture() == &images[0])
            {
                sprites[highlighted_row][highlighted_col].setTexture(images[14]);
            }

            else if (tempSprites[indexLeft1][indexLeft2].getTexture() == &images[1])
            {
                sprites[highlighted_row][highlighted_col].setTexture(images[15]);
            }

            else if (tempSprites[indexLeft1][indexLeft2].getTexture() == &images[2])
            {
                sprites[highlighted_row][highlighted_col].setTexture(images[16]);
            }

            else if (tempSprites[indexLeft1][indexLeft2].getTexture() == &images[3])
            {
                sprites[highlighted_row][highlighted_col].setTexture(images[17]);
            }

            else if (tempSprites[indexLeft1][indexLeft2].getTexture() == &images[4])
            {
                sprites[highlighted_row][highlighted_col].setTexture(images[18]);
            }

            else if (tempSprites[indexLeft1][indexLeft2].getTexture() == &images[5])
            {
                sprites[highlighted_row][highlighted_col].setTexture(images[19]);
            }

            else if (tempSprites[indexLeft1][indexLeft2].getTexture() == &images[6])
            {
                sprites[highlighted_row][highlighted_col].setTexture(images[20]);
            }

            destroyLeft = false;
        }

        if (destroyRight)
        {
            if (tempSprites[indexRight1][indexRight2].getTexture() == &images[0])
            {
                sprites[highlighted_row][highlighted_col].setTexture(images[14]);
            }

            else if (tempSprites[indexRight1][indexRight2].getTexture() == &images[1])
            {
                sprites[highlighted_row][highlighted_col].setTexture(images[15]);
            }

            else if (tempSprites[indexRight1][indexRight2].getTexture() == &images[2])
            {
                sprites[highlighted_row][highlighted_col].setTexture(images[16]);
            }

            else if (tempSprites[indexRight1][indexRight2].getTexture() == &images[3])
            {
                sprites[highlighted_row][highlighted_col].setTexture(images[17]);
            }

            else if (tempSprites[indexRight1][indexRight2].getTexture() == &images[4])
            {
                sprites[highlighted_row][highlighted_col].setTexture(images[18]);
            }

            else if (tempSprites[indexRight1][indexRight2].getTexture() == &images[5])
            {
                sprites[highlighted_row][highlighted_col].setTexture(images[19]);
            }

            else if (tempSprites[indexRight1][indexRight2].getTexture() == &images[6])
            {
                sprites[highlighted_row][highlighted_col].setTexture(images[20]);
            }

            destroyRight = false;

        }

        if (specialFourUp1)
        {
            sprites[highlighted_row][highlighted_col].setTexture(images[rand() % 7]);
            sprites[highlighted_row][highlighted_col - 1].setTexture(images[rand() % 7]);
            sprites[highlighted_row][highlighted_col - 2].setTexture(images[rand() % 7]);
            sprites[highlighted_row][highlighted_col - 3].setTexture(images[rand() % 7]);
            sprites[highlighted_row + 1][highlighted_col - 2].setTexture(images[rand() % 7]);
            sprites[highlighted_row - 1][highlighted_col - 2].setTexture(images[rand() % 7]);

            specialFourUp1 = false;
        }

        if (specialFourUp2)
        {
            sprites[highlighted_row][highlighted_col].setTexture(images[rand() % 7]);
            sprites[highlighted_row][highlighted_col - 1].setTexture(images[rand() % 7]);
            sprites[highlighted_row][highlighted_col - 2].setTexture(images[rand() % 7]);
            sprites[highlighted_row + 1][highlighted_col - 1].setTexture(images[rand() % 7]);
            sprites[highlighted_row - 1][highlighted_col - 1].setTexture(images[rand() % 7]);
            //sprites[highlighted_row - 1][highlighted_col - 2].setTexture(images[rand() % 7]);

            specialFourUp2 = false;
        }

        if (specialFourUp3)
        {
            sprites[highlighted_row][highlighted_col].setTexture(images[rand() % 7]);
            sprites[highlighted_row][highlighted_col + 1].setTexture(images[rand() % 7]);
            sprites[highlighted_row][highlighted_col + 2].setTexture(images[rand() % 7]);
            sprites[highlighted_row][highlighted_col + 3].setTexture(images[rand() % 7]);
            sprites[highlighted_row + 1][highlighted_col + 2].setTexture(images[rand() % 7]);
            sprites[highlighted_row - 1][highlighted_col + 2].setTexture(images[rand() % 7]);

            specialFourUp3 = false;
        }

        if (specialFourUp4)
        {
            sprites[highlighted_row][highlighted_col].setTexture(images[rand() % 7]);
            sprites[highlighted_row][highlighted_col + 1].setTexture(images[rand() % 7]);
            sprites[highlighted_row][highlighted_col + 2].setTexture(images[rand() % 7]);
            //sprites[highlighted_row][highlighted_col + 3].setTexture(images[rand() % 7]);
            sprites[highlighted_row + 1][highlighted_col + 1].setTexture(images[rand() % 7]);
            sprites[highlighted_row - 1][highlighted_col + 1].setTexture(images[rand() % 7]);

            specialFourUp4 = false;
        }

        if (specialFourUp5)
        {
            sprites[highlighted_row][highlighted_col].setTexture(images[rand() % 7]);
            sprites[highlighted_row][highlighted_col - 1].setTexture(images[rand() % 7]);
            sprites[highlighted_row][highlighted_col + 1].setTexture(images[rand() % 7]);
            sprites[highlighted_row][highlighted_col + 2].setTexture(images[rand() % 7]);
            sprites[highlighted_row - 1][highlighted_col + 1].setTexture(images[rand() % 7]);
            sprites[highlighted_row + 1][highlighted_col + 1].setTexture(images[rand() % 7]);

            specialFourUp5 = false;
        }

        if (specialFourUp6)
        {
            sprites[highlighted_row][highlighted_col].setTexture(images[rand() % 7]);
            sprites[highlighted_row][highlighted_col - 1].setTexture(images[rand() % 7]);
            sprites[highlighted_row][highlighted_col + 1].setTexture(images[rand() % 7]);
            sprites[highlighted_row][highlighted_col - 2].setTexture(images[rand() % 7]);
            sprites[highlighted_row - 1][highlighted_col - 1].setTexture(images[rand() % 7]);
            sprites[highlighted_row + 1][highlighted_col - 1].setTexture(images[rand() % 7]);

            specialFourUp6 = false;
        }

        if (specialRealFourUp)
        {
            sprites[highlighted_row][highlighted_col].setTexture(images[rand() % 7]);
            sprites[highlighted_row][highlighted_col - 1].setTexture(images[rand() % 7]);
            sprites[highlighted_row][highlighted_col + 1].setTexture(images[rand() % 7]);
            sprites[highlighted_row + 1][highlighted_col].setTexture(images[rand() % 7]);
            sprites[highlighted_row - 1][highlighted_col].setTexture(images[rand() % 7]);

            specialRealFourUp = false;
        }

        if (specialFourDown1)
        {
            sprites[highlighted_row][highlighted_col].setTexture(images[rand() % 7]);
            sprites[highlighted_row][highlighted_col - 1].setTexture(images[rand() % 7]);
            sprites[highlighted_row][highlighted_col - 2].setTexture(images[rand() % 7]);
            sprites[highlighted_row][highlighted_col - 3].setTexture(images[rand() % 7]);
            sprites[highlighted_row + 1][highlighted_col - 2].setTexture(images[rand() % 7]);
            sprites[highlighted_row - 1][highlighted_col - 2].setTexture(images[rand() % 7]);

            specialFourDown1 = false;
        }

        if (specialFourDown2)
        {
            sprites[highlighted_row][highlighted_col].setTexture(images[rand() % 7]);
            sprites[highlighted_row][highlighted_col - 1].setTexture(images[rand() % 7]);
            sprites[highlighted_row][highlighted_col - 2].setTexture(images[rand() % 7]);
            sprites[highlighted_row + 1][highlighted_col - 1].setTexture(images[rand() % 7]);
            sprites[highlighted_row - 1][highlighted_col - 1].setTexture(images[rand() % 7]);
            //sprites[highlighted_row - 1][highlighted_col - 2].setTexture(images[rand() % 7]);

            specialFourDown2 = false;
        }

        if (specialFourDown3)
        {
            sprites[highlighted_row][highlighted_col].setTexture(images[rand() % 7]);
            sprites[highlighted_row][highlighted_col + 1].setTexture(images[rand() % 7]);
            sprites[highlighted_row][highlighted_col + 2].setTexture(images[rand() % 7]);
            //sprites[highlighted_row][highlighted_col + 3].setTexture(images[rand() % 7]);
            sprites[highlighted_row + 1][highlighted_col + 1].setTexture(images[rand() % 7]);
            sprites[highlighted_row - 1][highlighted_col + 1].setTexture(images[rand() % 7]);

            specialFourDown3 = false;
        }

        if (specialFourDown4)
        {
            sprites[highlighted_row][highlighted_col].setTexture(images[rand() % 7]);
            sprites[highlighted_row][highlighted_col + 1].setTexture(images[rand() % 7]);
            sprites[highlighted_row][highlighted_col + 2].setTexture(images[rand() % 7]);
            sprites[highlighted_row][highlighted_col + 3].setTexture(images[rand() % 7]);
            sprites[highlighted_row + 1][highlighted_col + 2].setTexture(images[rand() % 7]);
            sprites[highlighted_row - 1][highlighted_col + 2].setTexture(images[rand() % 7]);

            specialFourDown4 = false;
        }

        if (specialFourDown5)
        {
            sprites[highlighted_row][highlighted_col].setTexture(images[rand() % 7]);
            sprites[highlighted_row][highlighted_col - 1].setTexture(images[rand() % 7]);
            sprites[highlighted_row][highlighted_col + 1].setTexture(images[rand() % 7]);
            sprites[highlighted_row][highlighted_col + 2].setTexture(images[rand() % 7]);
            sprites[highlighted_row - 1][highlighted_col + 1].setTexture(images[rand() % 7]);
            sprites[highlighted_row + 1][highlighted_col + 1].setTexture(images[rand() % 7]);

            specialFourDown5 = false;
        }

        if (specialFourDown6)
        {
            sprites[highlighted_row][highlighted_col].setTexture(images[rand() % 7]);
            sprites[highlighted_row][highlighted_col - 1].setTexture(images[rand() % 7]);
            sprites[highlighted_row][highlighted_col + 1].setTexture(images[rand() % 7]);
            sprites[highlighted_row][highlighted_col - 2].setTexture(images[rand() % 7]);
            sprites[highlighted_row - 1][highlighted_col - 1].setTexture(images[rand() % 7]);
            sprites[highlighted_row + 1][highlighted_col - 1].setTexture(images[rand() % 7]);

            specialFourDown6 = false;
        }

        if (specialRealFourDown)
        {
            sprites[highlighted_row][highlighted_col].setTexture(images[rand() % 7]);
            sprites[highlighted_row][highlighted_col - 1].setTexture(images[rand() % 7]);
            sprites[highlighted_row][highlighted_col + 1].setTexture(images[rand() % 7]);
            sprites[highlighted_row + 1][highlighted_col].setTexture(images[rand() % 7]);
            sprites[highlighted_row - 1][highlighted_col].setTexture(images[rand() % 7]);

            specialRealFourDown = false;
        }

        if (specialFourLeft1)
        {
            sprites[highlighted_row][highlighted_col].setTexture(images[rand() % 7]);
            sprites[highlighted_row - 1][highlighted_col].setTexture(images[rand() % 7]);
            sprites[highlighted_row - 2][highlighted_col].setTexture(images[rand() % 7]);
            sprites[highlighted_row - 1][highlighted_col + 1].setTexture(images[rand() % 7]);
            sprites[highlighted_row - 1][highlighted_col - 1].setTexture(images[rand() % 7]);

            specialFourLeft1 = false;
        }

        if (specialFourLeft2)
        {
            sprites[highlighted_row][highlighted_col].setTexture(images[rand() % 7]);
            sprites[highlighted_row - 1][highlighted_col].setTexture(images[rand() % 7]);
            sprites[highlighted_row - 2][highlighted_col].setTexture(images[rand() % 7]);
            sprites[highlighted_row - 3][highlighted_col].setTexture(images[rand() % 7]);
            sprites[highlighted_row - 2][highlighted_col + 1].setTexture(images[rand() % 7]);
            sprites[highlighted_row - 2][highlighted_col - 1].setTexture(images[rand() % 7]);

            specialFourLeft2 = false;
        }

        if (specialFourLeft3)
        {
            sprites[highlighted_row][highlighted_col].setTexture(images[rand() % 7]);
            sprites[highlighted_row + 1][highlighted_col].setTexture(images[rand() % 7]);
            sprites[highlighted_row + 2][highlighted_col].setTexture(images[rand() % 7]);
            sprites[highlighted_row + 1][highlighted_col + 1].setTexture(images[rand() % 7]);
            sprites[highlighted_row + 1][highlighted_col - 1].setTexture(images[rand() % 7]);

            specialFourLeft3 = false;
        }

        if (specialFourLeft4)
        {
            sprites[highlighted_row][highlighted_col].setTexture(images[rand() % 7]);
            sprites[highlighted_row + 1][highlighted_col].setTexture(images[rand() % 7]);
            sprites[highlighted_row + 2][highlighted_col].setTexture(images[rand() % 7]);
            sprites[highlighted_row + 3][highlighted_col].setTexture(images[rand() % 7]);
            sprites[highlighted_row + 2][highlighted_col + 1].setTexture(images[rand() % 7]);
            sprites[highlighted_row + 2][highlighted_col - 1].setTexture(images[rand() % 7]);

            specialFourLeft4 = false;
        }

        if (specialFourLeft5)
        {
            sprites[highlighted_row][highlighted_col].setTexture(images[rand() % 7]);
            sprites[highlighted_row - 1][highlighted_col].setTexture(images[rand() % 7]);
            sprites[highlighted_row - 2][highlighted_col].setTexture(images[rand() % 7]);
            sprites[highlighted_row + 1][highlighted_col].setTexture(images[rand() % 7]);
            sprites[highlighted_row - 1][highlighted_col + 1].setTexture(images[rand() % 7]);
            sprites[highlighted_row - 1][highlighted_col - 1].setTexture(images[rand() % 7]);

            specialFourLeft5 = false;
        }

        if (specialFourLeft6)
        {
            sprites[highlighted_row][highlighted_col].setTexture(images[rand() % 7]);
            sprites[highlighted_row - 1][highlighted_col].setTexture(images[rand() % 7]);
            sprites[highlighted_row + 2][highlighted_col].setTexture(images[rand() % 7]);
            sprites[highlighted_row + 1][highlighted_col].setTexture(images[rand() % 7]);
            sprites[highlighted_row + 1][highlighted_col + 1].setTexture(images[rand() % 7]);
            sprites[highlighted_row + 1][highlighted_col - 1].setTexture(images[rand() % 7]);

            specialFourLeft6 = false;
        }

        if (specialRealFourLeft)
        {
            sprites[highlighted_row][highlighted_col].setTexture(images[rand() % 7]);
            sprites[highlighted_row - 1][highlighted_col].setTexture(images[rand() % 7]);
            sprites[highlighted_row + 1][highlighted_col].setTexture(images[rand() % 7]);
            sprites[highlighted_row][highlighted_col + 1].setTexture(images[rand() % 7]);
            sprites[highlighted_row][highlighted_col - 1].setTexture(images[rand() % 7]);

            specialRealFourLeft = false;
        }

        if (specialFourRight1)
        {
            sprites[highlighted_row][highlighted_col].setTexture(images[rand() % 7]);
            sprites[highlighted_row - 1][highlighted_col].setTexture(images[rand() % 7]);
            sprites[highlighted_row - 2][highlighted_col].setTexture(images[rand() % 7]);
            sprites[highlighted_row - 1][highlighted_col + 1].setTexture(images[rand() % 7]);
            sprites[highlighted_row - 1][highlighted_col - 1].setTexture(images[rand() % 7]);


            specialFourRight1 = false;
        }

        if (specialFourRight2)
        {
            sprites[highlighted_row][highlighted_col].setTexture(images[rand() % 7]);
            sprites[highlighted_row - 1][highlighted_col].setTexture(images[rand() % 7]);
            sprites[highlighted_row - 2][highlighted_col].setTexture(images[rand() % 7]);
            sprites[highlighted_row - 3][highlighted_col].setTexture(images[rand() % 7]);
            sprites[highlighted_row - 2][highlighted_col + 1].setTexture(images[rand() % 7]);
            sprites[highlighted_row - 2][highlighted_col - 1].setTexture(images[rand() % 7]);

            specialFourRight2 = false;
        }

        if (specialFourRight3)
        {
            sprites[highlighted_row][highlighted_col].setTexture(images[rand() % 7]);
            sprites[highlighted_row + 1][highlighted_col].setTexture(images[rand() % 7]);
            sprites[highlighted_row + 2][highlighted_col].setTexture(images[rand() % 7]);
            sprites[highlighted_row + 1][highlighted_col + 1].setTexture(images[rand() % 7]);
            sprites[highlighted_row + 1][highlighted_col - 1].setTexture(images[rand() % 7]);


            specialFourRight3 = false;
        }

        if (specialFourRight4)
        {
            sprites[highlighted_row][highlighted_col].setTexture(images[rand() % 7]);
            sprites[highlighted_row + 1][highlighted_col].setTexture(images[rand() % 7]);
            sprites[highlighted_row + 2][highlighted_col].setTexture(images[rand() % 7]);
            sprites[highlighted_row + 3][highlighted_col].setTexture(images[rand() % 7]);
            sprites[highlighted_row + 2][highlighted_col + 1].setTexture(images[rand() % 7]);
            sprites[highlighted_row + 2][highlighted_col - 1].setTexture(images[rand() % 7]);


            specialFourRight4 = false;
        }

        if (specialFourRight5)
        {
            sprites[highlighted_row][highlighted_col].setTexture(images[rand() % 7]);
            sprites[highlighted_row - 1][highlighted_col].setTexture(images[rand() % 7]);
            sprites[highlighted_row - 2][highlighted_col].setTexture(images[rand() % 7]);
            sprites[highlighted_row + 1][highlighted_col].setTexture(images[rand() % 7]);
            sprites[highlighted_row - 1][highlighted_col + 1].setTexture(images[rand() % 7]);
            sprites[highlighted_row - 1][highlighted_col - 1].setTexture(images[rand() % 7]);


            specialFourRight5 = false;
        }

        if (specialFourRight6)
        {
            sprites[highlighted_row][highlighted_col].setTexture(images[rand() % 7]);
            sprites[highlighted_row - 1][highlighted_col].setTexture(images[rand() % 7]);
            sprites[highlighted_row + 2][highlighted_col].setTexture(images[rand() % 7]);
            sprites[highlighted_row + 1][highlighted_col].setTexture(images[rand() % 7]);
            sprites[highlighted_row + 1][highlighted_col + 1].setTexture(images[rand() % 7]);
            sprites[highlighted_row + 1][highlighted_col - 1].setTexture(images[rand() % 7]);


            specialFourRight6 = false;
        }

        if (specialRealFourRight)
        {
            sprites[highlighted_row][highlighted_col].setTexture(images[rand() % 7]);
            sprites[highlighted_row - 1][highlighted_col].setTexture(images[rand() % 7]);
            sprites[highlighted_row + 1][highlighted_col].setTexture(images[rand() % 7]);
            sprites[highlighted_row][highlighted_col + 1].setTexture(images[rand() % 7]);
            sprites[highlighted_row][highlighted_col - 1].setTexture(images[rand() % 7]);


            specialRealFourRight = false;
        }

        if (specialFive)
        {
            for (int j = 0; j < 8; j++)
            {
                sprites[specialRow][j].setTexture(images[rand() % 7]);
            }

            for (int i = 0; i < 8; i++)
            {
                sprites[i][specialCol].setTexture(images[rand() % 7]);
            }

            specialFive = false;
        }
        if (isGameRunning) {
            // Time logic: Update timer
            sf::Time elapsed = gameClock.getElapsedTime();
            int remainingSeconds = gameTimeLimit - static_cast<int>(elapsed.asSeconds());

            if (remainingSeconds <= 0) {
                remainingSeconds = 0;
                isGameRunning = false; // Trigger game-over logic or other actions when time runs out
                window.close();
            }

            // Update timer text
            startText.setString("Time: " + std::to_string(remainingSeconds) + "s");
        }

        window.clear();
        window.draw(backgroundSprite);

        RectangleShape rectangle;
        rectangle.setSize(Vector2f(gemSize, gemSize));
        rectangle.setOutlineColor(Color::Red);
        // Enter key to select a gem
        if (event.key.code == Keyboard::Enter)
        {
            enter_key_pressed = true;
            swap_triggered = true;
            rectangle.setFillColor(Color::Green);
        }
        else
        {
            rectangle.setFillColor(Color::Magenta);
        }

        rectangle.setOutlineThickness(4.f);
        rectangle.setScale(0.75f, 0.75f);
        rectangle.setPosition((highlighted_col * gemSize) + off_setX - 1, (highlighted_row * gemSize) + off_setY - 2);
        window.draw(rectangle);
        for (int i = 0; i < 8; i++)
        {
            for (int j = 0; j < 8; j++)
            {
                {
                    // Draw the gem itself
                    window.draw(sprites[i][j]);
                }
            }
        }
        window.draw(startText);
        window.draw(scoreText);
        window.display();
        if (!isGameRunning)
        {
            sf::RenderWindow gameOverWindow(sf::VideoMode(790, 490), "SCORE");
            sf::Text gameOverText;
            gameOverText.setFont(font);
            gameOverText.setCharacterSize(30);
            gameOverText.setFillColor(sf::Color::Red);
            gameOverText.setPosition(50.f, 50.f);
            gameOverText.setString("Game Over\nYour Score: " + std::to_string(score));
            if (score > high_score)
            {
                high_score = score; // Update high score
                // Update the high score in the file
                ofstream outfile("high_score.txt");
                if (outfile.is_open())
                {
                    outfile << high_score;

                }
                gameOverText.setString("Game Over\nYour Score: " + std::to_string(score) + "\nNew High Score");
            }
            else 
            {
                gameOverText.setString("Game Over\nYour Score: " + std::to_string(score));
            }
            while (gameOverWindow.isOpen())
            {
                sf::Event gameOverEvent;
                while (gameOverWindow.pollEvent(gameOverEvent))
                {
                    if (gameOverEvent.type == sf::Event::Closed)
                        gameOverWindow.close();
                }

                gameOverWindow.clear();
                gameOverWindow.draw(gameOverText); // Draw game-over text
                gameOverWindow.display();
            }
        }

    }
    return 0;
}