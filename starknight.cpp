#include <iostream>
#include <string>
#include <algorithm>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <time.h>
#include <list>
#include <stdlib.h> 
#include <math.h>
#include <cstring>
#include "Entity.h"
#include "Button.h"
#include "Actor.h"
#include "Character.h"
#include "Enemy.h"
#include "DarkFighter.h"
#include "Bullets.h"
#include "Game.h"
#include "State.h"
#include "MenuState.h"
#include "HubState.h"
#include "PlayState.h"
#include "ShopState.h"
#include "Attachment.h"

using namespace sf;
using namespace std;
float DEGTORAD = 0.017453f;
const int screenW = sf::VideoMode::getDesktopMode().width;//1920;
const int screenH = sf::VideoMode::getDesktopMode().height;//1080;
    
sf::Text source;
sf::Font mainGameFont;

int main() {

    srand(time(NULL));
    std::vector<State*> stateList;
    Game *game = new Game;
    int state = 0;
    
    RenderWindow app(VideoMode(screenW, screenH), "Starknight!", sf::Style::Fullscreen);
    sf::View view(sf::Vector2f(screenW/2, screenH/2), sf::Vector2f(screenW, screenH));
    view.setViewport(sf::FloatRect(0.f, 0.f, 1.f, 1.f));
    app.setView(view);
    app.setFramerateLimit(60);
    mainGameFont.loadFromFile("futura.ttf");
    source.setFont(mainGameFont);
    
    game->startGame(screenW, screenH, source, mainGameFont);
    
    MenuState *menuState = new MenuState;
    menuState -> createState(game);
    stateList.push_back(menuState);
    
    HubState *hubState = new HubState;
    hubState -> createState(game);
    stateList.push_back(hubState);
    
    PlayState *playState = new PlayState;
    playState -> createState(game);
    stateList.push_back(playState);
    
    ShopState *shopState = new ShopState;
    shopState -> createState(game);
    stateList.push_back(shopState);
    
    game->stateList = stateList;
    
    sf::Music music;
    if (!music.openFromFile("sounds/starknightTheme.wav"))
        return -1; // error
    music.play();
    music.setPlayingOffset(sf::seconds(.2f));
    music.setLoop(true);
    
    while (state >= 0)
    {
        state = stateList[state]->Run(app);
        music.stop();
    }

    return 0;
}
