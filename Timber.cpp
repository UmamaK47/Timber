//TIMBER!!! project code
// Timber.cpp : 
#include<SFML/Graphics.hpp>  
#include<sstream>
#include<SFML/Audio.hpp>

using namespace sf;

void updateBranches(int seed);

const int NUM_BRANCHES = 6;
Sprite branches[NUM_BRANCHES];

enum class side{LEFT, RIGHT, NONE};
side branchPosition[NUM_BRANCHES];


int main()
{
    VideoMode vm(960, 540);
   // VideoMode vm(1920, 1080); //VideoMode Object 1366 * 768
   // RenderWindow window(vm, "Timber!!!", Style::Fullscreen); //Creating and opening a window for the game
    RenderWindow window(vm, "Timber!!!");
    View view(sf::FloatRect(0, 0, 1920, 1080));
    window.setView(view);
    //***An object that's made from the Sprite class needs an object made from the Texture class in order to display itself as an image.
    
    //We created a texture to hold the graphics on the gpu
    Texture textureBackground;
    //load the graphic
    textureBackground.loadFromFile("Graphics/background.png");
    //create a sprite
    Sprite spriteBackground;
    //Now we'll attact texture to the sprite
    spriteBackground.setTexture(textureBackground);
    spriteBackground.setPosition(0, 0); //covers the screen

    //Tree sprite
    Texture textureTree;
    textureTree.loadFromFile("Graphics/tree.png");
    Sprite spriteTree;
    spriteTree.setTexture(textureTree);
    spriteTree.setPosition(810, 0);

    //More background trees
    Texture textureTreeBG;
    textureTreeBG.loadFromFile("Graphics/tree3.png");
    
    Sprite spriteTreeBG1;
    spriteTreeBG1.setTexture(textureTreeBG);
    spriteTreeBG1.setPosition(20, 0);

    Sprite spriteTreeBG2;
    spriteTreeBG2.setTexture(textureTreeBG);
    spriteTreeBG2.setPosition(300, -1200);

    Sprite spriteTreeBG3;
    spriteTreeBG3.setTexture(textureTreeBG);
    spriteTreeBG3.setPosition(1200, -1200);

    Sprite spriteTreeBG4;
    spriteTreeBG4.setTexture(textureTreeBG);
    spriteTreeBG4.setPosition(1500, -1270);

    //Bee sprite
    Texture textureBee;
    textureBee.loadFromFile("Graphics/bee.png");
    Sprite spriteBee;
    spriteBee.setTexture(textureBee);
    spriteBee.setPosition(0, 800);

    bool beeActive = false; //checks if bee is currently moving

    float beeSpeed = 0.0f; //speed of bee

    //Cloud Sprite
    Texture textureCloud;
    textureCloud.loadFromFile("Graphics/cloud.png");
    //create 3 sprites for cloud
    Sprite spriteCloud1;
    Sprite spriteCloud2;
    Sprite spriteCloud3;
    
    spriteCloud1.setTexture(textureCloud);
    spriteCloud2.setTexture(textureCloud);
    spriteCloud3.setTexture(textureCloud);

    spriteCloud1.setPosition(0, 0);
    spriteCloud2.setPosition(0, 150);
    spriteCloud3.setPosition(0, 300);

    bool cloud1Active = false;
    bool cloud2Active = false;
    bool cloud3Active = false;

    float cloud1Speed = 0.0f;
    float cloud2Speed = 0.0f;
    float cloud3Speed = 0.0f;

    Clock clock;

    //Time Bar
    RectangleShape timeBar;
    float timeBarStartWidth = 400;
    float timeBarHeight = 80;
    timeBar.setSize(Vector2f(timeBarStartWidth, timeBarHeight));
    timeBar.setFillColor(Color::Red);
    timeBar.setOutlineThickness(5);
    timeBar.setOutlineColor(Color::Yellow);
    timeBar.setPosition((1920 / 2) - timeBarStartWidth / 2, 980);

    //transparent rectangle
    RectangleShape rectangle;
    rectangle.setSize(Vector2f(650, 85));
    rectangle.setFillColor(Color(0,0,0,128));  
    rectangle.setPosition(10, 40);

    RectangleShape rectangle2;
    rectangle2.setSize(Vector2f(1200, 200));
    rectangle2.setFillColor(Color(0, 0, 0, 128));
    rectangle2.setPosition(340, 440);

    Time gameTimeTotal;
    float timeRemaining = 6.0f;
    float timeBarWidthPerSecond = timeBarStartWidth / timeRemaining;

    // Track whether the game is running
    bool paused = true;
    //create text
    int score = 0;
    Text textMessage;
    Text scoreText;
    //choose font
    Font font;
    font.loadFromFile("Font/KOMIKAP_.ttf");
    //set the selected font to our textmessages
    textMessage.setFont(font);
    scoreText.setFont(font);
    //assign a message to our text object
    textMessage.setString("Press Enter to Start Game! \n\t\t Esc to Quit");
    scoreText.setString("Score = 0");
    //set size of your strings
    textMessage.setCharacterSize(75);
    scoreText.setCharacterSize(100);
    //set a color
    textMessage.setFillColor(Color::White);
    scoreText.setFillColor(Color::White);
    //position the text
    FloatRect textRect = textMessage.getLocalBounds();
    textMessage.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
    textMessage.setPosition(1920 / 2.0f, 1080 / 2.0f);
    scoreText.setPosition(20, 20);

    //setting up 6 branches
    Texture textureBranch;
    textureBranch.loadFromFile("Graphics/branch.png");
    for (int i = 0; i < NUM_BRANCHES;i++) {
        branches[i].setTexture(textureBranch);
        branches[i].setPosition(-2000, -2000);
        branches[i].setOrigin(220, 20);
    }
    //Setting up player sprite
    Texture texturePlayer;
    texturePlayer.loadFromFile("Graphics/player.png");
    Sprite spritePlayer;
    spritePlayer.setTexture(texturePlayer);
    spritePlayer.setPosition(580, 720);

    side playerSide = side::LEFT;

    //setting gravestone sprite
    Texture textureRIP;
    textureRIP.loadFromFile("Graphics/rip.png");
    Sprite spriteRIP;
    spriteRIP.setTexture(textureRIP);
    spriteRIP.setPosition(675, 2000);

    //setting axe sprite
    Texture textureAxe;
    textureAxe.loadFromFile("Graphics/axe.png");
    Sprite spriteAxe;
    spriteAxe.setTexture(textureAxe);
    spriteAxe.setPosition(700, 830);

    //positioning axe with tree
    const float AXE_POSITION_LEFT = 700;
    const float AXE_POSITION_RIGHT = 1075;

    //setting flying log
    Texture textureLog;
    textureLog.loadFromFile("Graphics/log.png");
    Sprite spriteLog;
    spriteLog.setTexture(textureLog);
    spriteLog.setPosition(810, 720);

    bool logActive = false;
    float logSpeedX = 1000;
    float logSpeedY = -1500;
    //control player input
    bool acceptInput = false;

    //setting up sounds
    //1. Chop sound
    SoundBuffer chopBuffer;
    chopBuffer.loadFromFile("Sounds/chop2.wav");
    Sound chopSound;
    chopSound.setBuffer(chopBuffer);
    //2. Death sound
    SoundBuffer deathBuffer;
    deathBuffer.loadFromFile("Sounds/gameOver.wav");
    Sound deathSound;
    deathSound.setBuffer(deathBuffer);
    //3. Out of time sound
    SoundBuffer outOfTimeBuffer;
    outOfTimeBuffer.loadFromFile("Sounds/out_of_time.wav");
    Sound outOfTimeSound;
    outOfTimeSound.setBuffer(outOfTimeBuffer);

    //GAME LOOP STARTS HERE
    while (window.isOpen()) {
        //handle user input
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::KeyReleased && !paused) {
                acceptInput = true;
                spriteAxe.setPosition(2000, spriteAxe.getPosition().y); //hide axe
            }
        }
        if (Keyboard::isKeyPressed(Keyboard::Escape)) {
            window.close();
        }
        //start game when enter key is pressed(return and enter are the same)
        if (Keyboard::isKeyPressed(Keyboard::Return)) {
            paused = false;
            score = 0;
            timeRemaining = 6;
            for (int i = 1;i < NUM_BRANCHES;i++) {
                branchPosition[i] = side::NONE;
            }
            spriteRIP.setPosition(675, 2000); //hide gravestone
            spritePlayer.setPosition(580, 720); //show player
            acceptInput = true;
        } 
        if (acceptInput) {
            if (Keyboard::isKeyPressed(Keyboard::Right)||Keyboard::isKeyPressed(Keyboard::D)) {
                playerSide = side::RIGHT;
                score++;
                //add time to remaining time
                timeRemaining += (2 / score) + .15;
                //positon player and axe
                spriteAxe.setPosition(AXE_POSITION_RIGHT, spriteAxe.getPosition().y);
                spritePlayer.setPosition(1200, 720);
                //update branches
                updateBranches(score);
                //log flies to the left
                spriteLog.setPosition(810, 720);
                logSpeedX = -5000;
                logActive = true;
                acceptInput = false;
                //play sound
                chopSound.play();
            }
            if (Keyboard::isKeyPressed(Keyboard::Left) || Keyboard::isKeyPressed(Keyboard::A)) {
                playerSide = side::LEFT;
                score++;
                timeRemaining += (2 / score) + .15;
                spriteAxe.setPosition(AXE_POSITION_LEFT, spriteAxe.getPosition().y);
                spritePlayer.setPosition(580, 720);
                updateBranches(score);
                spriteLog.setPosition(810, 720);
                logSpeedX = 5000;
                logActive = true;
                acceptInput = false;
                chopSound.play();
            }
        }
        if (Keyboard::isKeyPressed(Keyboard::BackSpace)) {
            paused = true;
            textMessage.setString("Press Enter to Continue!");
            FloatRect textRect = textMessage.getLocalBounds();
            textMessage.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
            textMessage.setPosition(1920 / 2.0f, 1080 / 2.0f);
        }

        Time dt = clock.restart();

        //Setting up the bee
        if (!beeActive) {
            //speed of bee
            srand((int)time(0));
            beeSpeed = (rand() % 200) + 200;

            //height of bee
            srand((int)time(0) * 10);
            float height = (rand() % 500) + 500;
            spriteBee.setPosition(2000, height);
            beeActive = true;
        }
        //move bee
        else {
            spriteBee.setPosition(spriteBee.getPosition().x - (beeSpeed * dt.asSeconds()), spriteBee.getPosition().y);
            //bee goes off screen
            if (spriteBee.getPosition().x < -100) {
                beeActive = false;
            }
        }

        //setting cloud1
        if (!cloud1Active) {
            //speed of cloud
            srand((int)time(0) * 10);
            cloud1Speed = (rand() % 200);
            //height of cloud
            srand((int)time(0) * 10);
            float height = (rand() % 150);
            spriteCloud1.setPosition(-200, height);
            cloud1Active = true;
        }
        //move cloud
        else {
            spriteCloud1.setPosition(spriteCloud1.getPosition().x + (cloud1Speed * dt.asSeconds()), spriteCloud1.getPosition().y);
            if (spriteCloud1.getPosition().x > 1920) {
                cloud1Active = false;
            }
        }
        //setting cloud2
        if (!cloud2Active) {
            //speed of cloud
            srand((int)time(0) * 20);
            cloud2Speed = (rand() % 200);
            //height of cloud
            srand((int)time(0) * 20);
            float height = (rand() % 300) - 150;
            spriteCloud2.setPosition(-200, height);
            cloud2Active = true;
        }
        //move cloud
        else {
            spriteCloud2.setPosition(spriteCloud2.getPosition().x + (cloud2Speed * dt.asSeconds()), spriteCloud2.getPosition().y);
            if (spriteCloud2.getPosition().x > 1920) {
                cloud2Active = false;
            }
        }
        //setting cloud3
        if (!cloud3Active) {
            //speed of cloud
            srand((int)time(0) * 30);
            cloud3Speed = (rand() % 200);
            //height of cloud
            srand((int)time(0) * 30);
            float height = (rand() % 450) - 150;
            spriteCloud3.setPosition(-200, height);
            cloud3Active = true;
        }
        //move cloud
        else {
            spriteCloud3.setPosition(spriteCloud3.getPosition().x + (cloud3Speed * dt.asSeconds()), spriteCloud3.getPosition().y);
            if (spriteCloud3.getPosition().x > 1920) {
                cloud3Active = false;
            }
        }

        //update scene
        if (!paused) {
            
            
            //time bar resizing
            timeRemaining -= dt.asSeconds();
            timeBar.setSize(Vector2f(timeBarWidthPerSecond * timeRemaining, timeBarHeight));
            if (timeRemaining <= 0.0f) {
                paused = true;
                textMessage.setString("Out of time!!");
                FloatRect textRect = textMessage.getLocalBounds();
                textMessage.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
                textMessage.setPosition(1920 / 2.0f, 1080 / 2.0f);
                outOfTimeSound.play();
            }
           
            
            std::stringstream ss;
            ss << "Score = " << score;
            scoreText.setString(ss.str());
            //update the branches
            for (int i = 0;i < NUM_BRANCHES;i++) {
                float height = i * 150;
                if (branchPosition[i] == side::LEFT) {
                    branches[i].setPosition(610, height);
                    branches[i].setRotation(180);
                }
                else if (branchPosition[i] == side::RIGHT) {
                    branches[i].setPosition(1330, height);
                    branches[i].setRotation(0);
                }
                else {
                    //hide branch
                    branches[i].setPosition(3000, height);
                }
            }
            //animate flying log
            if (logActive) {
                spriteLog.setPosition(spriteLog.getPosition().x + (logSpeedX * dt.asSeconds()), spriteLog.getPosition().y + (logSpeedY * dt.asSeconds()));
                if (spriteLog.getPosition().x < -100 || spriteLog.getPosition().x>2000) {
                    logActive = false;
                    spriteLog.setPosition(810, 720);
                }
                if (branchPosition[5] == playerSide) {
                    paused = true;
                    acceptInput = false;
                    spriteRIP.setPosition(525, 760);
                    spriteAxe.setPosition(2000, 830);
                    spritePlayer.setPosition(2000, 660);
                    textMessage.setString("SQUISHED!!");
                    FloatRect textRect = textMessage.getLocalBounds();
                    textMessage.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
                    textMessage.setPosition(1920 / 2.0, 1080 / 2.0f);
                    deathSound.play();
                }
            }
        }

        //draw scene

        //clear everything from last scene
        window.clear();

        //draw game scene here
        //draw background
        window.draw(spriteBackground);

        //draw clouds
        window.draw(spriteCloud1);
        window.draw(spriteCloud2);
        window.draw(spriteCloud3);
        //draw bg trees
        window.draw(spriteTreeBG1);
        window.draw(spriteTreeBG2);
        window.draw(spriteTreeBG3);
        window.draw(spriteTreeBG4);

        for (int i = 0;i < NUM_BRANCHES;i++) {
            window.draw(branches[i]);
        }

        //draw tree
        window.draw(spriteTree);
        
        //draw player
        window.draw(spritePlayer);
        //darw axe
        window.draw(spriteAxe);
        //draw log
        window.draw(spriteLog);
        // draw gravestone
        window.draw(spriteRIP);
        //draw bee
        window.draw(spriteBee);
        //bg rect
        window.draw(rectangle);
        //draw score
        window.draw(scoreText);
        //draw timebar
        window.draw(timeBar);
        //draw text message
        if (paused) {
            window.draw(rectangle2);
            window.draw(textMessage);
        }
        //show everything
        window.display();
    }

    return 0;
}

//Moving the branches
void updateBranches(int seed) {
    for (int j = NUM_BRANCHES - 1;j > 0;j--) {
        branchPosition[j] = branchPosition[j - 1];
    }
    srand((int)time(0) + seed);
    int r = (rand() % 5);
    switch (r) {
    case 0:
        branchPosition[0] = side::LEFT;
        break;
    case 1:
        branchPosition[0] = side::RIGHT;
        break;
    default:
        branchPosition[0] = side::NONE;
        break;
    }
}