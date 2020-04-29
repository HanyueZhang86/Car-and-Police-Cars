#include "sidebar.h"
#include "constants.h"
Sidebar::Sidebar(){

}

Sidebar::Sidebar(float left, float width):_left(left), _width(width){
    items.reserve(50);

    rect.setFillColor(sf::Color(105,105,105)); //(192,192,192)); //silver

    rect.setPosition(sf::Vector2f(left, 0));
    rect.setSize(sf::Vector2f(width, SCREEN_HEIGHT));

    //the font file must be in the "working directory"
    // check projects->run->working directory [Make sure it's not pointing to the app file]
    if (!font.loadFromFile("Roboto-Thin.ttf")){
        cout<<"Sidebar() CTOR: Font failed to load"<<endl;
        cin.get();
        exit(-1);
    }
    text = sf::Text("Init Text", font);
    text.setCharacterSize(24);
    text.setStyle(sf::Text::Bold);
    text.setColor(sf::Color::Yellow);

    for (int i=0 ; i<30; i++){
        items.push_back("");
    }

}

void Sidebar::draw(sf::RenderWindow& window){
    window.draw(rect);

    float height = 10;
    for (vector<string>::iterator it = items.begin();
         it!= items.end(); it++){
        text.setString(it->c_str());
        text.setPosition(sf::Vector2f(_left+10, height));
        height += text.getLocalBounds().height+5;
        window.draw(text);

    }

}

string& Sidebar::operator [](int index){
    return items[index];
}
