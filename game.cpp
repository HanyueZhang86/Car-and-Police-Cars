#include "game.h"
#include "random.h"
#include "constants.h"
#include <iostream>
#include "car.h"
using namespace std;
#include "system.h"


Game::Game():sidebar(WORK_PANEL, SIDE_BAR)

{
    done=true;
    window.create(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Car Vs Cops");
    //VideoMode class has functions to detect screen size etc.
    //RenderWindow constructor has a third argumnet to set style
    //of the window: resize, fullscreen etc.
    clock.restart();
    system = System();
    window.setFramerateLimit(60);

    mouseIn = true;
    window.setKeyRepeatEnabled(true);
    end.setKeyRepeatEnabled(true);
    start=false;

    mousePoint = sf::CircleShape();
    mousePoint.setRadius(5.0);
    mousePoint.setFillColor(sf::Color::Red);

    //--- FONT ----------
    //font file must be in the "working directory:
    //      debug folder
    //Make sure working directory is where it should be and not
    //  inside the app file:
    //  Project->RUN->Working Folder
    //
    //font must be a member of the class.
    //  Will not work with a local declaration
    if (!font.loadFromFile("arial.ttf")){
        cout<<"Game() CTOR: Font failed to load"<<endl;
        cin.get();
        exit(-1);
    }

    myTextLabel = sf::Text("Initial String for myTextLabel", font);
    myTextLabel.setCharacterSize(12);
    myTextLabel.setStyle(sf::Text::Bold);
    myTextLabel.setColor(sf::Color::Red);
    myTextLabel.setPosition(sf::Vector2f(10, SCREEN_HEIGHT-myTextLabel.getLocalBounds().height-5));

    end.setPosition(sf::Vector2i(SCREEN_WIDTH/3,SCREEN_HEIGHT/3));


    restart.setSize(sf::Vector2f(SCREEN_WIDTH/9,SCREEN_HEIGHT/13));
    restart.setPosition(sf::Vector2f(150,100));
    restart.setFillColor(sf::Color::Black);
    restart.setOutlineThickness(20);


    restartbutton=sf::Text("RESTART" ,font);
    restartbutton.setFillColor(sf::Color::Red);
    restartbutton.setStyle(sf::Text::Bold);
    restartbutton.setCharacterSize(30);
    restartbutton.setPosition(restart.getPosition());
}

void Game::Draw(){
    //Look at the data and based on the data, draw shapes on window object.
    system.Draw(window);
    if (mouseIn){
        window.draw(mousePoint);
    }

    sidebar.draw(window);

    //- - - - - - - - - - - - - - - - - - -
    //getPosition() gives you screen coords, getPosition(window) gives you window coords
    //cout<<"mosue pos: "<<sf::Mouse::getPosition(window).x<<", "<<sf::Mouse::getPosition(window).y<<endl;
    //- - - - - - - - - - - - - - - - - - -

}

void Game::update(){
    //cause changes to the data for the next frame
    if(system.Getlife()>0)
        system.Step(command,mouse);
        system.Gettime(clock);
    command = 0;
    if (mouseIn){
        //mousePoint red dot:
        mousePoint.setPosition(sf::Mouse::getPosition(window).x-5,
                               sf::Mouse::getPosition(window).y-5);

        //mouse location text for sidebar:
        string s;
        s= "(" +
            to_string(sf::Mouse::getPosition(window).x) +
            ", " +
            to_string(sf::Mouse::getPosition(window).y) +
            ")";

        sidebar[0] = s;
        if(system.GetScore()>=0)
            sidebar[1]="Score:"+to_string(system.GetScore());
        if(system.Getlife()>=0)
            sidebar[2]="life:"+to_string(system.Getlife());
        if(system.Getlife()==0&&done){
            score=sf::Text("        Game Over!!!!\n         Score: "+to_string(system.GetScore()),font);
            score.setFillColor(sf::Color::Red);
            score.setStyle(sf::Text::Bold);
            score.setCharacterSize(30);
            end.create(sf::VideoMode(SCREEN_WIDTH/3,SCREEN_HEIGHT/3),"End game");
            end.clear(sf::Color::White);
            end.draw(score);
            end.draw(restart);
            end.draw(restartbutton);
            end.display();
            done=false;

        }
//        else
//            exit(1);
    }
}
void Game::render(){
       window.clear();

       Draw();
       window.display();
}



void Game::processEvents()
{
   sf::Event event;
   float mouseX, mouseY;
   while (window.pollEvent(event))//or waitEvent
       {
       // check the type of the event...
       command = 0;
           switch (event.type)
           {
           // window closed
           case sf::Event::Closed:
               window.close();
               break;

           // key pressed
           case sf::Event::KeyPressed:
               switch(event.key.code){
               case sf::Keyboard::A:
                  command = 1;
                  break;
              case sf::Keyboard::D:
                   command = 2;
                  break;
               case sf::Keyboard::W:
                  command = 3;
                  break;
              case sf::Keyboard::S:
                   command = 4;
                  break;
              case sf::Keyboard::Q:
                   command = 5;
                   break;
               case sf::Keyboard::E:
                    command = 6;
                   break;
               case sf::Keyboard::Z:
                    command = 7;
                   break;
               case sf::Keyboard::X:
                    command = 8;
                   break;
               case sf::Keyboard::Escape:
                   window.close();
                break;
               }

               break;
           case sf::Event::MouseEntered:
               mouseIn = true;
               break;

           case sf::Event::MouseLeft:
               mouseIn = false;
               break;

           case sf::Event::MouseMoved:
                start=true;
                mouse.x = event.mouseMove.x;
                mouse.y = event.mouseMove.y;
                //Do something with it if you need to...
               break;
           case sf::Event::MouseButtonReleased:
                   if (event.mouseButton.button == sf::Mouse::Right)
                   {
                       std::cout << "Right Button: (" << event.mouseButton.x << ", "
                                        << event.mouseButton.y << ")"<<std::endl;
                       mouse.x = event.mouseButton.x;
                       mouse.y = event.mouseButton.y;

                        if(inrange(mouse))
                            cout<<"in range";
                   }
                   else
                       std::cout<<"left button?"<<std::endl;
                   break;

               default:
                   break;
           }
       }
}
void Game::run()
{
   while (window.isOpen())
   {
//       int w=SCREEN_WIDTH,h=SCREEN_HEIGHT;
//       sf::Time a=clock.getElapsedTime();
//       int stop=5;
//       while(a.asSeconds()>stop){
//           w-=50;
//           h-=50;
//           window.setSize(sf::Vector2u(w,h));
//           stop+=5;
//       }
//       cout<<stop<<endl;

       endEvent();
       processEvents();
       if(start)
           update();
           render(); //clear/draw/display
   }
}
bool Game::inrange(sf::Vector2f mouse){
    if(mouse.x>restart.getPosition().x&&
            mouse.x<(restart.getSize().x+restart.getPosition().x)&&
            mouse.y>restart.getPosition().y&&
            mouse.y<(restart.getSize().y+restart.getPosition().y))
        return true;
    return false;
}
void Game::endEvent(){
    sf::Event event;
    sf::Vector2f mou;
    while (end.pollEvent(event)) {
        switch (event.type) {
        case sf::Event::Closed:
            end.close();
            window.close();
            break;

//        case sf::Event::MouseMoved:
//             mou.x = event.mouseMove.x;
//             mou.y = event.mouseMove.y;

             //Do something with it if you need to...
            //break;
        case sf::Event::MouseButtonReleased:
            if (event.mouseButton.button == sf::Mouse::Left)
            {
                mou.x = event.mouseButton.x;
                mou.y = event.mouseButton.y;
                    if(inrange(mou))
                    std::cout<<"in rang";
                    window.close();
                    end.close();
                    Random r;
                    r.Seed();

                    Game game;
                    game.run();

            }
            else
            {
                std::cout<<"not";
            }
            break;
        default:
            break;
        }
    }
}
