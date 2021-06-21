#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <cmath>
#include <random>
#include <ctime>
#include <list>
#include <algorithm>
#include <iterator>
#include <regex>
#include <map>
#include <string>

float PlayerDMG=0, PlayerSpeed=0, PlayerIncome=0;
float CastleHealth=100000;
float CastleHealthB=100000;
bool EndingA=false;
bool EndingB=false;

//###################################################################################################################################################

class Jednostka: public sf::Sprite
{
public:
    Jednostka(float hp, float dmg, float speed, int ID):sf::Sprite(), hp_(hp), dmg_(dmg), speed_(speed), ID_(ID)
    {
        this->setPosition(-32.0, 460.0);
    };
    ~Jednostka(){};
    float hp(){ return hp_; }
    float dmg(){ return dmg_; }
    float speed(){ return speed_; }
    int ID(){ return ID_; }
    float hp_;
    float dmg_;
    float speed_;
    int walktimer=0;
    int fighttimer=0;
    int ID_;
    void Oof(float ile)
    {
            this->hp_=this->hp_-(ile);
    }
    void ruch(sf::Time elapsed)
    {
        int elapsed2=elapsed.asMicroseconds();
        this->move((speed_+PlayerSpeed)*0.000001*elapsed2, 0);
    }
};

class Jednostka1: public Jednostka
{
public:
    Jednostka1():Jednostka(10000,1,30, 1)
    {};
    ~Jednostka1(){};
};

class Jednostka2: public Jednostka
{
public:
    Jednostka2():Jednostka(12500,2,20, 2){  };
    ~Jednostka2(){};
};

class Jednostka3: public Jednostka
{
public:
    Jednostka3():Jednostka(10000,3,25, 3){  };
    ~Jednostka3(){};
};

class Jednostka4: public Jednostka
{
public:
    Jednostka4():Jednostka(15000,3,20, 4){  };
    ~Jednostka4(){};
};

class Jednostka5: public Jednostka
{
public:
    Jednostka5():Jednostka(20000,5,20, 5){  };
    ~Jednostka5(){};
};

//###################################################################################################################################################

class JednostkaB: public sf::Sprite
{
public:
    JednostkaB(float hp, float dmg, float speed, int ID):sf::Sprite(), hp_(hp), dmg_(dmg), speed_(speed), ID_(ID)
    {
        this->setPosition(1440.0, 460.0);
    };
    ~JednostkaB(){};
    float hp(){ return hp_; }
    float dmg(){ return dmg_; }
    float speed(){ return speed_; }
    int ID(){ return ID_; }
    float hp_;
    float dmg_;
    float speed_;
    int ID_;
    int walktimer=0;
    int fighttimer=0;
    void Oof(float ile)
    {
            this->hp_=this->hp_-(ile);
    }
    void ruch(sf::Time elapsed)
    {
        int elapsed2=elapsed.asMicroseconds();
        this->move((speed_)*0.000001*elapsed2, 0);
    }
};


class Jednostka1B: public JednostkaB
{
public:
    Jednostka1B():JednostkaB(12000,1,-30, 1){};
    ~Jednostka1B(){};
};

class Jednostka2B: public JednostkaB
{
public:
    Jednostka2B():JednostkaB(14000,2,-20, 2){ };
    ~Jednostka2B(){};
};

class Jednostka3B: public JednostkaB
{
public:
    Jednostka3B():JednostkaB(11500,3,-25, 3){ };
    ~Jednostka3B(){};
};

class Jednostka4B: public JednostkaB
{
public:
    Jednostka4B():JednostkaB(15000,3,-20, 4){ };
    ~Jednostka4B(){};
};

class Jednostka5B: public JednostkaB
{
public:
    Jednostka5B():JednostkaB(19000,4,-20, 5){ };
    ~Jednostka5B(){};
};

//###################################################################################################################################################

std::vector<Jednostka> Przegrupowanie(std::vector<Jednostka> a)
{
    a.erase(a.begin());
    return a;
}

std::vector<JednostkaB> PrzegrupowanieB(std::vector<JednostkaB> a)
{
    a.erase(a.begin());
    return a;
}

//###################################################################################################################################################
int main() {

    std::cout << "Path to Victory" << std::endl;
    std::cout << "Made by Szymon Perka" << std::endl;

    // create the window
    sf::RenderWindow window(sf::VideoMode(1600, 750), "My window");

    // create some shapes

    sf::Music music;
    if (!music.openFromFile("music.ogg"))
        return -1; // error
    music.setLoop(true);
    music.setVolume(50.f);
    music.play();


//###################################################################################################################################################

    sf::RectangleShape hub(sf::Vector2f(1600.0, 150.0));
    hub.setPosition(0.0, 0.0);
    hub.setFillColor(sf::Color(81, 90, 90));
    hub.setOutlineThickness(5);
    hub.setOutlineColor(sf::Color::Black);

    sf::RectangleShape HPbar(sf::Vector2f(200.0, 20.0));
    HPbar.setPosition(20.0, 100.0);
    HPbar.setFillColor(sf::Color(199, 0, 57));

    sf::RectangleShape MaxHPbar(sf::Vector2f(206.0, 26.0));
    MaxHPbar.setPosition(17.0, 97.0);
    MaxHPbar.setFillColor(sf::Color(23, 32, 42));

    sf::RectangleShape HPbarB(sf::Vector2f(200.0, 20.0));
    HPbarB.setPosition(1380.0, 100.0);
    HPbarB.setFillColor(sf::Color(199, 0, 57));

    sf::RectangleShape MaxHPbarB(sf::Vector2f(206.0, 26.0));
    MaxHPbarB.setPosition(1377.0, 97.0);
    MaxHPbarB.setFillColor(sf::Color(23, 32, 42));

//###################################################################################################################################################

    sf::Texture terrain;
    if (!terrain.loadFromFile("terrain.png"))
    {
        std::cerr << "Could not load texture" << std::endl;
        return 1;
    }
    terrain.setRepeated(true);
    sf::Sprite podloze;
    podloze.setTexture(terrain);
    podloze.setTextureRect(sf::IntRect(0, 0, 1600, 28)); //left, top, width, height
    podloze.setScale(3.0, 3.0);
    podloze.setPosition(0.0, 666.0);

    sf::Texture background;
    if (!background.loadFromFile("background.png"))
    {
        std::cerr << "Could not load texture" << std::endl;
        return 1;
    }
    background.setRepeated(true);
    sf::Sprite tlo;
    tlo.setTexture(background);
    tlo.setTextureRect(sf::IntRect(0, 50, 1600, 750)); //left, top, width, height
    tlo.setScale(3.0, 3.0);
    tlo.setPosition(0.0, 150.0);

    sf::Texture castle;
    if (!castle.loadFromFile("walls1.png"))
    {
        std::cerr << "Could not load texture" << std::endl;
        return 1;
    }
    sf::Sprite zamek;
    zamek.setTexture(castle);
    zamek.setTextureRect(sf::IntRect(62, 0, 63, 143)); //left, top, width, height
    zamek.setScale(3.0, 3.0);
    zamek.setPosition(0.0, 150.0);

    sf::Texture castle1;
    if (!castle1.loadFromFile("walls2.png"))
    {
        std::cerr << "Could not load texture" << std::endl;
        return 1;
    }
    castle1.setRepeated(true);
    sf::Sprite zamek1;
    zamek1.setTexture(castle1);
    zamek1.setTextureRect(sf::IntRect(62, 0, 63, 70)); //left, top, width, height
    zamek1.setScale(3.0, 3.0);
    zamek1.setPosition(0.0, 570.0);

    sf::Texture gate;
    if (!gate.loadFromFile("gate.png"))
    {
        std::cerr << "Could not load texture" << std::endl;
        return 1;
    }
    sf::Sprite brama;
    brama.setTexture(gate);
    brama.setTextureRect(sf::IntRect(45, 0, 33, 78)); //left, top, width, height
    brama.setScale(4.5, 4.5);
    brama.setPosition(0.0, 354.0);



    sf::Texture castleB;
    if (!castleB.loadFromFile("walls1.png"))
    {
        std::cerr << "Could not load texture" << std::endl;
        return 1;
    }
    sf::Sprite zamekB;
    zamekB.setTexture(castleB);
    zamekB.setTextureRect(sf::IntRect(0, 0, 62, 143)); //left, top, width, height
    zamekB.setScale(3.0, 3.0);
    zamekB.setPosition(1414.0, 150.0);

    sf::Texture castleB1;
    if (!castleB1.loadFromFile("walls2.png"))
    {
        std::cerr << "Could not load texture" << std::endl;
        return 1;
    }
    castleB1.setRepeated(true);
    sf::Sprite zamekB1;
    zamekB1.setTexture(castleB1);
    zamekB1.setTextureRect(sf::IntRect(0, 0, 62, 70)); //left, top, width, height
    zamekB1.setScale(3.0, 3.0);
    zamekB1.setPosition(1414.0, 570.0);

    sf::Texture gateB;
    if (!gateB.loadFromFile("gate.png"))
    {
        std::cerr << "Could not load texture" << std::endl;
        return 1;
    }
    sf::Sprite bramaB;
    bramaB.setTexture(gateB);
    bramaB.setTextureRect(sf::IntRect(0, 0, 45, 78)); //left, top, width, height
    bramaB.setScale(4.5, 4.5);
    bramaB.setPosition(1450.0, 354.0);

//###################################################################################################################################################

    sf::Texture Postac1;
    if (!Postac1.loadFromFile("Unit1.png"))
    {
        std::cerr << "Could not load texture" << std::endl;
        return 1;
    }

    sf::Texture Postac1Atak;
    if (!Postac1Atak.loadFromFile("Unit1Atak.png"))
    {
        std::cerr << "Could not load texture" << std::endl;
        return 1;
    }

    sf::Texture Postac2;
    if (!Postac2.loadFromFile("Unit2.png"))
    {
        std::cerr << "Could not load texture" << std::endl;
        return 1;
    }

    sf::Texture Postac2Atak;
    if (!Postac2Atak.loadFromFile("Unit2Atak.png"))
    {
        std::cerr << "Could not load texture" << std::endl;
        return 1;
    }

    sf::Texture Postac3;
    if (!Postac3.loadFromFile("Unit3.png"))
    {
        std::cerr << "Could not load texture" << std::endl;
        return 1;
    }

    sf::Texture Postac3Atak;
    if (!Postac3Atak.loadFromFile("Unit3Atak.png"))
    {
        std::cerr << "Could not load texture" << std::endl;
        return 1;
    }

    sf::Texture Postac4;
    if (!Postac4.loadFromFile("Unit4.png"))
    {
        std::cerr << "Could not load texture" << std::endl;
        return 1;
    }

    sf::Texture Postac4Atak;
    if (!Postac4Atak.loadFromFile("Unit4Atak.png"))
    {
        std::cerr << "Could not load texture" << std::endl;
        return 1;
    }

    sf::Texture Postac5;
    if (!Postac5.loadFromFile("Unit5.png"))
    {
        std::cerr << "Could not load texture" << std::endl;
        return 1;
    }

    sf::Texture Postac5Atak;
    if (!Postac5Atak.loadFromFile("Unit5Atak.png"))
    {
        std::cerr << "Could not load texture" << std::endl;
        return 1;
    }

    sf::Texture Postac1B;
    if (!Postac1B.loadFromFile("Unit1B.png"))
    {
        std::cerr << "Could not load texture" << std::endl;
        return 1;
    }

    sf::Texture Postac1BAtak;
    if (!Postac1BAtak.loadFromFile("Unit1BAtak.png"))
    {
        std::cerr << "Could not load texture" << std::endl;
        return 1;
    }

    sf::Texture Postac2B;
    if (!Postac2B.loadFromFile("Unit2B.png"))
    {
        std::cerr << "Could not load texture" << std::endl;
        return 1;
    }

    sf::Texture Postac2BAtak;
    if (!Postac2BAtak.loadFromFile("Unit2BAtak.png"))
    {
        std::cerr << "Could not load texture" << std::endl;
        return 1;
    }

    sf::Texture Postac3B;
    if (!Postac3B.loadFromFile("Unit3B.png"))
    {
        std::cerr << "Could not load texture" << std::endl;
        return 1;
    }

    sf::Texture Postac3BAtak;
    if (!Postac3BAtak.loadFromFile("Unit3BAtak.png"))
    {
        std::cerr << "Could not load texture" << std::endl;
        return 1;
    }

    sf::Texture Postac4B;
    if (!Postac4B.loadFromFile("Unit4B.png"))
    {
        std::cerr << "Could not load texture" << std::endl;
        return 1;
    }

    sf::Texture Postac4BAtak;
    if (!Postac4BAtak.loadFromFile("Unit4BAtak.png"))
    {
        std::cerr << "Could not load texture" << std::endl;
        return 1;
    }

    sf::Texture Postac5B;
    if (!Postac5B.loadFromFile("Unit5B.png"))
    {
        std::cerr << "Could not load texture" << std::endl;
        return 1;
    }

    sf::Texture Postac5BAtak;
    if (!Postac5BAtak.loadFromFile("Unit5BAtak.png"))
    {
        std::cerr << "Could not load texture" << std::endl;
        return 1;
    }

//###################################################################################################################################################

    sf::RectangleShape Unit1(sf::Vector2f(50.0, 50.0));
    Unit1.setPosition(300.0, 25.0);
    Unit1.setFillColor(sf::Color(10, 0, 57));

    sf::RectangleShape Line1(sf::Vector2f(5.0, 150.0));
    Line1.setPosition(260.0, 0.0);
    Line1.setFillColor(sf::Color(3, 0, 0));

    sf::RectangleShape Unit2(sf::Vector2f(50.0, 50.0));
    Unit2.setPosition(400.0, 25.0);
    Unit2.setFillColor(sf::Color(10, 0, 57));

    sf::RectangleShape Unit3(sf::Vector2f(50.0, 50.0));
    Unit3.setPosition(500.0, 25.0);
    Unit3.setFillColor(sf::Color(10, 0, 57));

    sf::RectangleShape Unit4(sf::Vector2f(50.0, 50.0));
    Unit4.setPosition(600.0, 25.0);
    Unit4.setFillColor(sf::Color(10, 0, 57));

    sf::RectangleShape Unit5(sf::Vector2f(50.0, 50.0));
    Unit5.setPosition(700.0, 25.0);
    Unit5.setFillColor(sf::Color(10, 0, 57));

    sf::RectangleShape DmgUpgrade(sf::Vector2f(50.0, 50.0));
    DmgUpgrade.setPosition(950.0, 25.0);
    DmgUpgrade.setFillColor(sf::Color(10, 0, 57));

    sf::RectangleShape SpeedUpgrade(sf::Vector2f(50.0, 50.0));
    SpeedUpgrade.setPosition(1100.0, 25.0);
    SpeedUpgrade.setFillColor(sf::Color(10, 0, 57));

    sf::RectangleShape IncomeUpgrade(sf::Vector2f(50.0, 50.0));
    IncomeUpgrade.setPosition(1250.0, 25.0);
    IncomeUpgrade.setFillColor(sf::Color(10, 0, 57));

    sf::RectangleShape Line2(sf::Vector2f(5.0, 150.0));
    Line2.setPosition(1340.0, 0.0);
    Line2.setFillColor(sf::Color(3, 0, 0));

    sf::RectangleShape TitleBg(sf::Vector2f(160.0, 150.0));
    TitleBg.setPosition(770.0, 0.0);
    TitleBg.setFillColor(sf::Color(61, 12, 12));

    sf::RectangleShape TitleBg2(sf::Vector2f(140.0, 130.0));
    TitleBg2.setPosition(780.0, 10.0);
    TitleBg2.setFillColor(sf::Color(122, 56, 56));

//###################################################################################################################################################

    sf::Font font;
    if (!font.loadFromFile("OpenSans-Regular.ttf"))
    {
        // error...
    }

    sf::Text text;
    text.setFont(font);
    text.setString("Gold:");
    text.setCharacterSize(24); // in pixels, not points!
    text.setFillColor(sf::Color::Yellow);
    text.setOutlineThickness(2);
    text.setOutlineColor(sf::Color::Black);
    text.setPosition(15.0,15.0);

    sf::Text Health;
    Health.setFont(font);
    Health.setString("Your HEALTH:");
    Health.setCharacterSize(24); // in pixels, not points!
    Health.setFillColor(sf::Color::Red);
    Health.setOutlineThickness(3);
    Health.setOutlineColor(sf::Color::Black);
    Health.setPosition(20.0,65.0);

    sf::Text HealthB;
    HealthB.setFont(font);
    HealthB.setString("Enemy HEALTH:");
    HealthB.setCharacterSize(24); // in pixels, not points!
    HealthB.setFillColor(sf::Color::Red);
    HealthB.setOutlineThickness(3);
    HealthB.setOutlineColor(sf::Color::Black);
    HealthB.setPosition(1380.0,65.0);

    sf::Text UnitCost1;
    UnitCost1.setFont(font);
    UnitCost1.setString("10g");
    UnitCost1.setCharacterSize(16); // in pixels, not points!
    UnitCost1.setFillColor(sf::Color::Yellow);
    UnitCost1.setPosition(312.0,80.0);

    sf::Text Unit1Name;
    Unit1Name.setFont(font);
    Unit1Name.setString("Scout");
    Unit1Name.setCharacterSize(16); // in pixels, not points!
    Unit1Name.setFillColor(sf::Color::Yellow);
    Unit1Name.setPosition(303.0,100.0);

    sf::Text Unit1Label;
    Unit1Label.setFont(font);
    Unit1Label.setString("1");
    Unit1Label.setCharacterSize(24); // in pixels, not points!
    Unit1Label.setFillColor(sf::Color::White);
    Unit1Label.setOutlineThickness(1);
    Unit1Label.setOutlineColor(sf::Color::Black);
    Unit1Label.setPosition(319.0, 35.0);

    sf::Text UnitCost2;
    UnitCost2.setFont(font);
    UnitCost2.setString("15g");
    UnitCost2.setCharacterSize(16); // in pixels, not points!
    UnitCost2.setFillColor(sf::Color::Yellow);
    UnitCost2.setPosition(412.0,80.0);

    sf::Text Unit2Name;
    Unit2Name.setFont(font);
    Unit2Name.setString("Warrior");
    Unit2Name.setCharacterSize(16); // in pixels, not points!
    Unit2Name.setFillColor(sf::Color::Yellow);
    Unit2Name.setPosition(395.0,100.0);

    sf::Text Unit2Label;
    Unit2Label.setFont(font);
    Unit2Label.setString("2");
    Unit2Label.setCharacterSize(24); // in pixels, not points!
    Unit2Label.setFillColor(sf::Color::White);
    Unit2Label.setOutlineThickness(1);
    Unit2Label.setOutlineColor(sf::Color::Black);
    Unit2Label.setPosition(419.0, 35.0);

    sf::Text UnitCost3;
    UnitCost3.setFont(font);
    UnitCost3.setString("15g");
    UnitCost3.setCharacterSize(16); // in pixels, not points!
    UnitCost3.setFillColor(sf::Color::Yellow);
    UnitCost3.setPosition(512.0,80.0);

    sf::Text Unit3Name;
    Unit3Name.setFont(font);
    Unit3Name.setString("Knight");
    Unit3Name.setCharacterSize(16); // in pixels, not points!
    Unit3Name.setFillColor(sf::Color::Yellow);
    Unit3Name.setPosition(500.0,100.0);

    sf::Text Unit3Label;
    Unit3Label.setFont(font);
    Unit3Label.setString("3");
    Unit3Label.setCharacterSize(24); // in pixels, not points!
    Unit3Label.setFillColor(sf::Color::White);
    Unit3Label.setOutlineThickness(1);
    Unit3Label.setOutlineColor(sf::Color::Black);
    Unit3Label.setPosition(519.0, 35.0);

    sf::Text UnitCost4;
    UnitCost4.setFont(font);
    UnitCost4.setString("25g");
    UnitCost4.setCharacterSize(16); // in pixels, not points!
    UnitCost4.setFillColor(sf::Color::Yellow);
    UnitCost4.setPosition(612.0,80.0);

    sf::Text Unit4Name;
    Unit4Name.setFont(font);
    Unit4Name.setString("General");
    Unit4Name.setCharacterSize(16); // in pixels, not points!
    Unit4Name.setFillColor(sf::Color::Yellow);
    Unit4Name.setPosition(595.0,100.0);

    sf::Text Unit4Label;
    Unit4Label.setFont(font);
    Unit4Label.setString("4");
    Unit4Label.setCharacterSize(24); // in pixels, not points!
    Unit4Label.setFillColor(sf::Color::White);
    Unit4Label.setOutlineThickness(1);
    Unit4Label.setOutlineColor(sf::Color::Black);
    Unit4Label.setPosition(619.0, 35.0);

    sf::Text UnitCost5;
    UnitCost5.setFont(font);
    UnitCost5.setString("50g");
    UnitCost5.setCharacterSize(16); // in pixels, not points!
    UnitCost5.setFillColor(sf::Color::Yellow);
    UnitCost5.setPosition(712.0,80.0);

    sf::Text Unit5Name;
    Unit5Name.setFont(font);
    Unit5Name.setString("King");
    Unit5Name.setCharacterSize(16); // in pixels, not points!
    Unit5Name.setFillColor(sf::Color::Yellow);
    Unit5Name.setPosition(708.0,100.0);

    sf::Text Unit5Label;
    Unit5Label.setFont(font);
    Unit5Label.setString("5");
    Unit5Label.setCharacterSize(24); // in pixels, not points!
    Unit5Label.setFillColor(sf::Color::White);
    Unit5Label.setOutlineThickness(1);
    Unit5Label.setOutlineColor(sf::Color::Black);
    Unit5Label.setPosition(719.0, 35.0);

    sf::Text Title;
    Title.setFont(font);
    Title.setString("\n   Path \n     to \n Victory");
    Title.setCharacterSize(24); // in pixels, not points!
    Title.setFillColor(sf::Color::White);
    Title.setOutlineThickness(1);
    Title.setOutlineColor(sf::Color::Black);
    Title.setPosition(805.0, 0.0);

    sf::Text DmgPodpis;
    DmgPodpis.setFont(font);
    DmgPodpis.setString("Dmg Up");
    DmgPodpis.setCharacterSize(12); // in pixels, not points!
    DmgPodpis.setFillColor(sf::Color::Yellow);
    DmgPodpis.setPosition(951.0,100.0);

    sf::Text DmgLabel;
    DmgLabel.setFont(font);
    DmgLabel.setString("Q");
    DmgLabel.setCharacterSize(24); // in pixels, not points!
    DmgLabel.setFillColor(sf::Color::White);
    DmgLabel.setOutlineThickness(1);
    DmgLabel.setOutlineColor(sf::Color::Black);
    DmgLabel.setPosition(966.0, 35.0);

    sf::Text SpeedPodpis;
    SpeedPodpis.setFont(font);
    SpeedPodpis.setString("Speed Up");
    SpeedPodpis.setCharacterSize(12); // in pixels, not points!
    SpeedPodpis.setFillColor(sf::Color::Yellow);
    SpeedPodpis.setPosition(1095.0,100.0);

    sf::Text SpeedLabel;
    SpeedLabel.setFont(font);
    SpeedLabel.setString("W");
    SpeedLabel.setCharacterSize(24); // in pixels, not points!
    SpeedLabel.setFillColor(sf::Color::White);
    SpeedLabel.setOutlineThickness(1);
    SpeedLabel.setOutlineColor(sf::Color::Black);
    SpeedLabel.setPosition(1114.0, 35.0);

    sf::Text IncomePodpis;
    IncomePodpis.setFont(font);
    IncomePodpis.setString("Income Up");
    IncomePodpis.setCharacterSize(12); // in pixels, not points!
    IncomePodpis.setFillColor(sf::Color::Yellow);
    IncomePodpis.setPosition(1243.0,100.0);

    sf::Text IncomeLabel;
    IncomeLabel.setFont(font);
    IncomeLabel.setString("E");
    IncomeLabel.setCharacterSize(24); // in pixels, not points!
    IncomeLabel.setFillColor(sf::Color::White);
    IncomeLabel.setOutlineThickness(1);
    IncomeLabel.setOutlineColor(sf::Color::Black);
    IncomeLabel.setPosition(1268.0, 35.0);

    sf::Text CreditsA;
    CreditsA.setFont(font);
    CreditsA.setString("\n You have been defeated! \n Your castle has been taken over. \n Your territory has been plundered. \n You have met your end in the castle jail and await your fate...");
    CreditsA.setCharacterSize(48); // in pixels, not points!
    CreditsA.setFillColor(sf::Color::Yellow);
    CreditsA.setOutlineThickness(5);
    CreditsA.setOutlineColor(sf::Color::Black);
    CreditsA.setPosition(200.0,200.0);

    sf::Text CreditsB;
    CreditsB.setFont(font);
    CreditsB.setString("\n You have won the game and protected your kingdom! \n With this the tide of war will shift in your favor. \n Victory will soon be in your kingdom's grasp!");
    CreditsB.setCharacterSize(48); // in pixels, not points!
    CreditsB.setFillColor(sf::Color::Yellow);
    CreditsB.setOutlineThickness(5);
    CreditsB.setOutlineColor(sf::Color::Black);
    CreditsB.setPosition(200.0,200.0);

//###################################################################################################################################################

    int czasomierz=0;
    int SpawnTimer=0;
    int Rate=8500;
    int gold=15;
    float uszkodzenia=0;
    float uszkodzeniaB=0;
    int DmgCost=100;
    int SpeedCost=100;
    int IncomeCost=100;

    std::vector<Jednostka> Armia;
    std::vector<JednostkaB> ArmiaB;

    sf::Clock clock;

//###################################################################################################################################################

    // run the program as long as the window is open
    while (window.isOpen()) {

        sf::Time elapsed = clock.restart();

        //std::cout << elapsed2 << std::endl;

        czasomierz=czasomierz+elapsed.asMilliseconds();
        if ((EndingA==false) && (EndingB==false))
        {
            if (czasomierz>=500)
            {
                czasomierz=0;
                gold=gold+1+PlayerIncome;
            }
        }
        std::string zloto=std::to_string(gold);
        sf::Text text2;
        text2.setFont(font);
        text2.setString(zloto);
        text2.setCharacterSize(24); // in pixels, not points!
        text2.setFillColor(sf::Color::Yellow);
        text2.setOutlineThickness(2);
        text2.setOutlineColor(sf::Color::Black);
        text2.setPosition(75.0,15.0);

        std::string koszt1=std::to_string(DmgCost);
        sf::Text DmgCostText;
        DmgCostText.setFont(font);
        DmgCostText.setString(koszt1);
        DmgCostText.setCharacterSize(16); // in pixels, not points!
        DmgCostText.setFillColor(sf::Color::Yellow);
        DmgCostText.setPosition(960.0,80.0);

        std::string koszt2=std::to_string(SpeedCost);
        sf::Text SpeedCostText;
        SpeedCostText.setFont(font);
        SpeedCostText.setString(koszt2);
        SpeedCostText.setCharacterSize(16); // in pixels, not points!
        SpeedCostText.setFillColor(sf::Color::Yellow);
        SpeedCostText.setPosition(1110.0,80.0);

        std::string koszt3=std::to_string(IncomeCost);
        sf::Text IncomeCostText;
        IncomeCostText.setFont(font);
        IncomeCostText.setString(koszt3);
        IncomeCostText.setCharacterSize(16); // in pixels, not points!
        IncomeCostText.setFillColor(sf::Color::Yellow);
        IncomeCostText.setPosition(1260.0,80.0);

//###################################################################################################################################################
        if ((EndingA==false) && (EndingB==false))
        {
            for(int i=0; i<ArmiaB.size(); i++)
            {
                if (i==0)
                {

                    sf::FloatRect ObszarJednostki2 = ArmiaB[0].getGlobalBounds();
                    if (ObszarJednostki2.left>189)
                    {
                        if (Armia.empty())
                        {
                            ArmiaB[i].fighttimer=0;
                            if (ArmiaB[0].ID_==1)
                            {
                                ArmiaB[0].setTexture(Postac1B);
                            }
                            else if (ArmiaB[0].ID_==2)
                            {
                                ArmiaB[0].setTexture(Postac2B);
                            }
                            else if (ArmiaB[0].ID_==3)
                            {
                                ArmiaB[0].setTexture(Postac3B);
                            }
                            else if (ArmiaB[0].ID_==4)
                            {
                                ArmiaB[0].setTexture(Postac4B);
                            }
                            else if (ArmiaB[0].ID_==5)
                            {
                                ArmiaB[0].setTexture(Postac5B);
                            }
                            ArmiaB[i].walktimer=ArmiaB[i].walktimer+elapsed.asMilliseconds();
                            ArmiaB[i].ruch(elapsed);
                            if ((ArmiaB[i].walktimer<150) && (ArmiaB[i].walktimer>=0))
                            {
                                ArmiaB[i].setTextureRect(sf::IntRect(528, 240, 32, 48));
                            }
                            else if((ArmiaB[i].walktimer>=150) && (ArmiaB[i].walktimer<300))
                            {
                                ArmiaB[i].setTextureRect(sf::IntRect(464, 240, 32, 48));
                            }
                            else if((ArmiaB[i].walktimer>=300) && (ArmiaB[i].walktimer<450))
                            {
                                ArmiaB[i].setTextureRect(sf::IntRect(400, 240, 32, 48));
                            }
                            else if((ArmiaB[i].walktimer>=450) && (ArmiaB[i].walktimer<600))
                            {
                                ArmiaB[i].setTextureRect(sf::IntRect(336, 240, 32, 48));
                            }
                            else if((ArmiaB[i].walktimer>=600) && (ArmiaB[i].walktimer<750))
                            {
                                ArmiaB[i].setTextureRect(sf::IntRect(272, 240, 32, 48));
                            }
                            else if((ArmiaB[i].walktimer>=750) && (ArmiaB[i].walktimer<900))
                            {
                                ArmiaB[i].setTextureRect(sf::IntRect(208, 240, 32, 48));
                            }
                            else if((ArmiaB[i].walktimer>=900) && (ArmiaB[i].walktimer<1050))
                            {
                                ArmiaB[i].setTextureRect(sf::IntRect(144, 240, 32, 48));
                            }
                            else if(ArmiaB[i].walktimer>=1050)
                            {
                                ArmiaB[i].setTextureRect(sf::IntRect(80, 240, 32, 48));
                                ArmiaB[i].walktimer=-150;
                            }
                        }
                        else
                        {
                            sf::FloatRect ObszarJednostki = Armia[0].getGlobalBounds();
                            if (!ObszarJednostki2.intersects(ObszarJednostki))
                            {
                                ArmiaB[i].fighttimer=0;
                                if (ArmiaB[0].ID_==1)
                                {
                                    ArmiaB[0].setTexture(Postac1B);
                                }
                                else if (ArmiaB[0].ID_==2)
                                {
                                    ArmiaB[0].setTexture(Postac2B);
                                }
                                else if (ArmiaB[0].ID_==3)
                                {
                                    ArmiaB[0].setTexture(Postac3B);
                                }
                                else if (ArmiaB[0].ID_==4)
                                {
                                    ArmiaB[0].setTexture(Postac4B);
                                }
                                else if (ArmiaB[0].ID_==5)
                                {
                                    ArmiaB[0].setTexture(Postac5B);
                                }
                                ArmiaB[i].walktimer=ArmiaB[i].walktimer+elapsed.asMilliseconds();
                                ArmiaB[i].ruch(elapsed);
                                if ((ArmiaB[i].walktimer<150) && (ArmiaB[i].walktimer>=0))
                                {
                                    ArmiaB[i].setTextureRect(sf::IntRect(528, 240, 32, 48));
                                }
                                else if((ArmiaB[i].walktimer>=150) && (ArmiaB[i].walktimer<300))
                                {
                                    ArmiaB[i].setTextureRect(sf::IntRect(464, 240, 32, 48));
                                }
                                else if((ArmiaB[i].walktimer>=300) && (ArmiaB[i].walktimer<450))
                                {
                                    ArmiaB[i].setTextureRect(sf::IntRect(400, 240, 32, 48));
                                }
                                else if((ArmiaB[i].walktimer>=450) && (ArmiaB[i].walktimer<600))
                                {
                                    ArmiaB[i].setTextureRect(sf::IntRect(336, 240, 32, 48));
                                }
                                else if((ArmiaB[i].walktimer>=600) && (ArmiaB[i].walktimer<750))
                                {
                                    ArmiaB[i].setTextureRect(sf::IntRect(272, 240, 32, 48));
                                }
                                else if((ArmiaB[i].walktimer>=750) && (ArmiaB[i].walktimer<900))
                                {
                                    ArmiaB[i].setTextureRect(sf::IntRect(208, 240, 32, 48));
                                }
                                else if((ArmiaB[i].walktimer>=900) && (ArmiaB[i].walktimer<1050))
                                {
                                    ArmiaB[i].setTextureRect(sf::IntRect(144, 240, 32, 48));
                                }
                                else if(ArmiaB[i].walktimer>=1050)
                                {
                                    ArmiaB[i].setTextureRect(sf::IntRect(80, 240, 32, 48));
                                    ArmiaB[i].walktimer=-150;
                                }
                            }
                            else
                            {
                                ArmiaB[i].walktimer=0;
                                if (ArmiaB[0].ID_==1)
                                {
                                    ArmiaB[0].setTexture(Postac1BAtak);
                                }
                                else if (ArmiaB[0].ID_==2)
                                {
                                    ArmiaB[0].setTexture(Postac2BAtak);
                                }
                                else if (ArmiaB[0].ID_==3)
                                {
                                    ArmiaB[0].setTexture(Postac3BAtak);
                                }
                                else if (ArmiaB[0].ID_==4)
                                {
                                    ArmiaB[0].setTexture(Postac4BAtak);
                                }
                                else if (ArmiaB[0].ID_==5)
                                {
                                    ArmiaB[0].setTexture(Postac5BAtak);
                                }
                                ArmiaB[i].fighttimer=ArmiaB[i].fighttimer+elapsed.asMilliseconds();
                                Armia[0].Oof(ArmiaB[0].dmg_);

                                if ((ArmiaB[0].fighttimer<150) && (ArmiaB[0].fighttimer>=0))
                                {
                                    ArmiaB[0].setTextureRect(sf::IntRect(528, 48, 32, 48));
                                }
                                else if((ArmiaB[0].fighttimer>=150) && (ArmiaB[0].fighttimer<300))
                                {
                                    ArmiaB[0].setTextureRect(sf::IntRect(464, 48, 32, 48));
                                }
                                else if((ArmiaB[0].fighttimer>=300) && (ArmiaB[0].fighttimer<450))
                                {
                                    ArmiaB[0].setTextureRect(sf::IntRect(272, 144, 32, 48));
                                }
                                else if((ArmiaB[0].fighttimer>=450) && (ArmiaB[0].fighttimer<600))
                                {
                                    ArmiaB[0].setTextureRect(sf::IntRect(208, 144, 32, 48));
                                }
                                else if(ArmiaB[0].fighttimer>=600)
                                {
                                    ArmiaB[0].setTextureRect(sf::IntRect(16, 144, 32, 48));
                                }
                                if (ArmiaB[0].fighttimer>=750)
                                {
                                    ArmiaB[0].fighttimer=0;
                                }
                            }

                        }
                    }
                    if (ObszarJednostki2.left<=189)
                    {
                        CastleHealth=CastleHealth-ArmiaB[0].dmg_;
                        uszkodzenia=uszkodzenia+ArmiaB[0].dmg_;
                        if (uszkodzenia>=500)
                        {
                            sf::Vector2f Pasek=HPbar.getSize();
                            Pasek.x=Pasek.x-1;
                            HPbar.setSize(Pasek);
                            uszkodzenia=0;
                        }
                        ArmiaB[i].walktimer=0;
                        if (ArmiaB[0].ID_==1)
                        {
                            ArmiaB[0].setTexture(Postac1BAtak);
                        }
                        else if (ArmiaB[0].ID_==2)
                        {
                            ArmiaB[0].setTexture(Postac2BAtak);
                        }
                        else if (ArmiaB[0].ID_==3)
                        {
                            ArmiaB[0].setTexture(Postac3BAtak);
                        }
                        else if (ArmiaB[0].ID_==4)
                        {
                            ArmiaB[0].setTexture(Postac4BAtak);
                        }
                        else if (ArmiaB[0].ID_==5)
                        {
                            ArmiaB[0].setTexture(Postac5BAtak);
                        }
                        ArmiaB[i].fighttimer=ArmiaB[i].fighttimer+elapsed.asMilliseconds();

                        if ((ArmiaB[0].fighttimer<150) && (ArmiaB[0].fighttimer>=0))
                        {
                            ArmiaB[0].setTextureRect(sf::IntRect(528, 48, 32, 48));
                        }
                        else if((ArmiaB[0].fighttimer>=150) && (ArmiaB[0].fighttimer<300))
                        {
                            ArmiaB[0].setTextureRect(sf::IntRect(464, 48, 32, 48));
                        }
                        else if((ArmiaB[0].fighttimer>=300) && (ArmiaB[0].fighttimer<450))
                        {
                            ArmiaB[0].setTextureRect(sf::IntRect(272, 144, 32, 48));
                        }
                        else if((ArmiaB[0].fighttimer>=450) && (ArmiaB[0].fighttimer<600))
                        {
                            ArmiaB[0].setTextureRect(sf::IntRect(208, 144, 32, 48));
                        }
                        else if(ArmiaB[0].fighttimer>=600)
                        {
                            ArmiaB[0].setTextureRect(sf::IntRect(16, 144, 32, 48));
                        }
                        if (ArmiaB[0].fighttimer>=750)
                        {
                            ArmiaB[0].fighttimer=0;
                        }
                    }
                }
                else
                {
                    sf::FloatRect ObszarJednostki = ArmiaB[i].getGlobalBounds();
                    sf::FloatRect ObszarJednostki2 = ArmiaB[i-1].getGlobalBounds();
                    if (!ObszarJednostki.intersects(ObszarJednostki2))
                    {
                        ArmiaB[i].walktimer=ArmiaB[i].walktimer+elapsed.asMilliseconds();
                        ArmiaB[i].ruch(elapsed);
                        if ((ArmiaB[i].walktimer<150) && (ArmiaB[i].walktimer>=0))
                        {
                            ArmiaB[i].setTextureRect(sf::IntRect(528, 240, 32, 48));
                        }
                        else if((ArmiaB[i].walktimer>=150) && (ArmiaB[i].walktimer<300))
                        {
                            ArmiaB[i].setTextureRect(sf::IntRect(464, 240, 32, 48));
                        }
                        else if((ArmiaB[i].walktimer>=300) && (ArmiaB[i].walktimer<450))
                        {
                            ArmiaB[i].setTextureRect(sf::IntRect(400, 240, 32, 48));
                        }
                        else if((ArmiaB[i].walktimer>=450) && (ArmiaB[i].walktimer<600))
                        {
                            ArmiaB[i].setTextureRect(sf::IntRect(336, 240, 32, 48));
                        }
                        else if((ArmiaB[i].walktimer>=600) && (ArmiaB[i].walktimer<750))
                        {
                            ArmiaB[i].setTextureRect(sf::IntRect(272, 240, 32, 48));
                        }
                        else if((ArmiaB[i].walktimer>=750) && (ArmiaB[i].walktimer<900))
                        {
                            ArmiaB[i].setTextureRect(sf::IntRect(208, 240, 32, 48));
                        }
                        else if((ArmiaB[i].walktimer>=900) && (ArmiaB[i].walktimer<1050))
                        {
                            ArmiaB[i].setTextureRect(sf::IntRect(144, 240, 32, 48));
                        }
                        else if(ArmiaB[i].walktimer>=1050)
                        {
                            ArmiaB[i].setTextureRect(sf::IntRect(80, 240, 32, 48));
                            ArmiaB[i].walktimer=-150;
                        }
                    }
                }
            }

            //###################################################################################################################################################

            for(int i=0; i<Armia.size(); i++)
            {
                if (i==0)
                {
                    sf::FloatRect ObszarJednostki = Armia[0].getGlobalBounds();
                    if (ObszarJednostki.left+ObszarJednostki.width<1414)
                    {
                        if (ArmiaB.empty())
                        {
                            Armia[i].fighttimer=0;
                            if (Armia[0].ID_==1)
                            {
                                Armia[0].setTexture(Postac1);
                            }
                            else if (Armia[0].ID_==2)
                            {
                                Armia[0].setTexture(Postac2);
                            }
                            else if (Armia[0].ID_==3)
                            {
                                Armia[0].setTexture(Postac3);
                            }
                            else if (Armia[0].ID_==4)
                            {
                                Armia[0].setTexture(Postac4);
                            }
                            else if (Armia[0].ID_==5)
                            {
                                Armia[0].setTexture(Postac5);
                            }
                            Armia[i].walktimer=Armia[i].walktimer+elapsed.asMilliseconds();
                            Armia[i].ruch(elapsed);
                            if ((Armia[i].walktimer<150) && (Armia[i].walktimer>=0))
                            {
                                Armia[i].setTextureRect(sf::IntRect(16, 240, 32, 48));
                            }
                            else if((Armia[i].walktimer>=150) && (Armia[i].walktimer<300))
                            {
                                Armia[i].setTextureRect(sf::IntRect(80, 240, 32, 48));
                            }
                            else if((Armia[i].walktimer>=300) && (Armia[i].walktimer<450))
                            {
                                Armia[i].setTextureRect(sf::IntRect(144, 240, 32, 48));
                            }
                            else if((Armia[i].walktimer>=450) && (Armia[i].walktimer<600))
                            {
                                Armia[i].setTextureRect(sf::IntRect(208, 240, 32, 48));
                            }
                            else if((Armia[i].walktimer>=600) && (Armia[i].walktimer<750))
                            {
                                Armia[i].setTextureRect(sf::IntRect(272, 240, 32, 48));
                            }
                            else if((Armia[i].walktimer>=750) && (Armia[i].walktimer<900))
                            {
                                Armia[i].setTextureRect(sf::IntRect(336, 240, 32, 48));
                            }
                            else if((Armia[i].walktimer>=900) && (Armia[i].walktimer<1050))
                            {
                                Armia[i].setTextureRect(sf::IntRect(400, 240, 32, 48));
                            }
                            else if(Armia[i].walktimer>=1050)
                            {
                                Armia[i].setTextureRect(sf::IntRect(464, 240, 32, 48));
                            }
                            if (Armia[i].walktimer>=1200)
                            {
                                Armia[i].walktimer=0;
                            }
                        }
                        else
                        {
                            sf::FloatRect ObszarJednostki2 = ArmiaB[0].getGlobalBounds();
                            if (!ObszarJednostki.intersects(ObszarJednostki2))
                            {
                                Armia[i].fighttimer=0;
                                if (Armia[0].ID_==1)
                                {
                                    Armia[0].setTexture(Postac1);
                                }
                                else if (Armia[0].ID_==2)
                                {
                                    Armia[0].setTexture(Postac2);
                                }
                                else if (Armia[0].ID_==3)
                                {
                                    Armia[0].setTexture(Postac3);
                                }
                                else if (Armia[0].ID_==4)
                                {
                                    Armia[0].setTexture(Postac4);
                                }
                                else if (Armia[0].ID_==5)
                                {
                                    Armia[0].setTexture(Postac5);
                                }
                                Armia[i].walktimer=Armia[i].walktimer+elapsed.asMilliseconds();
                                Armia[i].ruch(elapsed);
                                if ((Armia[i].walktimer<150) && (Armia[i].walktimer>=0))
                                {
                                    Armia[i].setTextureRect(sf::IntRect(16, 240, 32, 48));
                                }
                                else if((Armia[i].walktimer>=150) && (Armia[i].walktimer<300))
                                {
                                    Armia[i].setTextureRect(sf::IntRect(80, 240, 32, 48));
                                }
                                else if((Armia[i].walktimer>=300) && (Armia[i].walktimer<450))
                                {
                                    Armia[i].setTextureRect(sf::IntRect(144, 240, 32, 48));
                                }
                                else if((Armia[i].walktimer>=450) && (Armia[i].walktimer<600))
                                {
                                    Armia[i].setTextureRect(sf::IntRect(208, 240, 32, 48));
                                }
                                else if((Armia[i].walktimer>=600) && (Armia[i].walktimer<750))
                                {
                                    Armia[i].setTextureRect(sf::IntRect(272, 240, 32, 48));
                                }
                                else if((Armia[i].walktimer>=750) && (Armia[i].walktimer<900))
                                {
                                    Armia[i].setTextureRect(sf::IntRect(336, 240, 32, 48));
                                }
                                else if((Armia[i].walktimer>=900) && (Armia[i].walktimer<1050))
                                {
                                    Armia[i].setTextureRect(sf::IntRect(400, 240, 32, 48));
                                }
                                else if(Armia[i].walktimer>=1050)
                                {
                                    Armia[i].setTextureRect(sf::IntRect(464, 240, 32, 48));
                                }
                                if (Armia[i].walktimer>=1200)
                                {
                                    Armia[i].walktimer=0;
                                }
                            }
                            else
                            {
                                Armia[i].walktimer=0;
                                if (Armia[0].ID_==1)
                                {
                                    Armia[0].setTexture(Postac1Atak);
                                }
                                else if (Armia[0].ID_==2)
                                {
                                    Armia[0].setTexture(Postac2Atak);
                                }
                                else if (Armia[0].ID_==3)
                                {
                                    Armia[0].setTexture(Postac3Atak);
                                }
                                else if (Armia[0].ID_==4)
                                {
                                    Armia[0].setTexture(Postac4Atak);
                                }
                                else if (Armia[0].ID_==5)
                                {
                                    Armia[0].setTexture(Postac5Atak);
                                }
                                Armia[i].fighttimer=Armia[i].fighttimer+elapsed.asMilliseconds();
                                ArmiaB[0].Oof(Armia[0].dmg_+PlayerDMG);

                                if ((Armia[0].fighttimer<150) && (Armia[0].fighttimer>=0))
                                {
                                    Armia[0].setTextureRect(sf::IntRect(16, 48, 32, 48));
                                }
                                else if((Armia[0].fighttimer>=150) && (Armia[0].fighttimer<300))
                                {
                                    Armia[0].setTextureRect(sf::IntRect(80, 48, 32, 48));
                                }
                                else if((Armia[0].fighttimer>=300) && (Armia[0].fighttimer<450))
                                {
                                    Armia[0].setTextureRect(sf::IntRect(272, 144, 32, 48));
                                }
                                else if((Armia[0].fighttimer>=450) && (Armia[0].fighttimer<600))
                                {
                                    Armia[0].setTextureRect(sf::IntRect(336, 144, 32, 48));
                                }
                                else if(Armia[0].fighttimer>=600)
                                {
                                    Armia[0].setTextureRect(sf::IntRect(528, 144, 32, 48));
                                }
                                if (Armia[0].fighttimer>=750)
                                {
                                    Armia[0].fighttimer=0;
                                }
                            }
                        }
                    }
                    if (ObszarJednostki.left+ObszarJednostki.width>=1414)
                    {
                        CastleHealthB=CastleHealthB-Armia[0].dmg_-PlayerDMG;
                        uszkodzeniaB=uszkodzeniaB+Armia[0].dmg_+PlayerDMG;
                        if (uszkodzeniaB>=500)
                        {
                            sf::Vector2f Pasek=HPbarB.getSize();
                            Pasek.x=Pasek.x-1;
                            HPbarB.setSize(Pasek);
                            uszkodzeniaB=0;
                        }
                        Armia[i].walktimer=0;
                        if (Armia[0].ID_==1)
                        {
                            Armia[0].setTexture(Postac1Atak);
                        }
                        else if (Armia[0].ID_==2)
                        {
                            Armia[0].setTexture(Postac2Atak);
                        }
                        else if (Armia[0].ID_==3)
                        {
                            Armia[0].setTexture(Postac3Atak);
                        }
                        else if (Armia[0].ID_==4)
                        {
                            Armia[0].setTexture(Postac4Atak);
                        }
                        else if (Armia[0].ID_==5)
                        {
                            Armia[0].setTexture(Postac5Atak);
                        }
                        Armia[i].fighttimer=Armia[i].fighttimer+elapsed.asMilliseconds();

                        if ((Armia[0].fighttimer<150) && (Armia[0].fighttimer>=0))
                        {
                            Armia[0].setTextureRect(sf::IntRect(16, 48, 32, 48));
                        }
                        else if((Armia[0].fighttimer>=150) && (Armia[0].fighttimer<300))
                        {
                            Armia[0].setTextureRect(sf::IntRect(80, 48, 32, 48));
                        }
                        else if((Armia[0].fighttimer>=300) && (Armia[0].fighttimer<450))
                        {
                            Armia[0].setTextureRect(sf::IntRect(272, 144, 32, 48));
                        }
                        else if((Armia[0].fighttimer>=450) && (Armia[0].fighttimer<600))
                        {
                            Armia[0].setTextureRect(sf::IntRect(336, 144, 32, 48));
                        }
                        else if(Armia[0].fighttimer>=600)
                        {
                            Armia[0].setTextureRect(sf::IntRect(528, 144, 32, 48));
                        }
                        if (Armia[0].fighttimer>=750)
                        {
                            Armia[0].fighttimer=0;
                        }
                    }
                }
                else
                {
                    sf::FloatRect ObszarJednostki = Armia[i].getGlobalBounds();
                    sf::FloatRect ObszarJednostki2 = Armia[i-1].getGlobalBounds();
                    if (!ObszarJednostki.intersects(ObszarJednostki2))
                    {
                        Armia[i].walktimer=Armia[i].walktimer+elapsed.asMilliseconds();
                        Armia[i].ruch(elapsed);
                        if ((Armia[i].walktimer<150) && (Armia[i].walktimer>=0))
                        {
                            Armia[i].setTextureRect(sf::IntRect(16, 240, 32, 48));
                        }
                        else if((Armia[i].walktimer>=150) && (Armia[i].walktimer<300))
                        {
                            Armia[i].setTextureRect(sf::IntRect(80, 240, 32, 48));
                        }
                        else if((Armia[i].walktimer>=300) && (Armia[i].walktimer<450))
                        {
                            Armia[i].setTextureRect(sf::IntRect(144, 240, 32, 48));
                        }
                        else if((Armia[i].walktimer>=450) && (Armia[i].walktimer<600))
                        {
                            Armia[i].setTextureRect(sf::IntRect(208, 240, 32, 48));
                        }
                        else if((Armia[i].walktimer>=600) && (Armia[i].walktimer<750))
                        {
                            Armia[i].setTextureRect(sf::IntRect(272, 240, 32, 48));
                        }
                        else if((Armia[i].walktimer>=750) && (Armia[i].walktimer<900))
                        {
                            Armia[i].setTextureRect(sf::IntRect(336, 240, 32, 48));
                        }
                        else if((Armia[i].walktimer>=900) && (Armia[i].walktimer<1050))
                        {
                            Armia[i].setTextureRect(sf::IntRect(400, 240, 32, 48));
                        }
                        else if(Armia[i].walktimer>=1050)
                        {
                            Armia[i].setTextureRect(sf::IntRect(464, 240, 32, 48));
                        }
                        if (Armia[i].walktimer>=1200)
                        {
                            Armia[i].walktimer=0;
                        }
                    }
                }
            }

            if (!Armia.empty())
            {
                if (Armia[0].hp_<=0)
                {
                    Armia=Przegrupowanie(Armia);
                }
            }

            //###################################################################################################################################################

            if (!ArmiaB.empty())
            {
                if (ArmiaB[0].hp_<=0)
                {
                    ArmiaB=PrzegrupowanieB(ArmiaB);
                }
            }

            //###################################################################################################################################################



            //###################################################################################################################################################

            SpawnTimer=SpawnTimer+elapsed.asMilliseconds();
            if (SpawnTimer>Rate)
            {
                int Przeciwnik=rand()% 7+1;
                if (Przeciwnik==1)
                {
                    ArmiaB.emplace_back(Jednostka1B());
                    ArmiaB[ArmiaB.size()-1].setTexture(Postac1B);
                    ArmiaB[ArmiaB.size()-1].setTextureRect(sf::IntRect(528, 0, 32, 48)); //left, top, width, height
                    ArmiaB[ArmiaB.size()-1].setScale(5.0, 5.0);
                }
                if (Przeciwnik==2)
                {
                    ArmiaB.emplace_back(Jednostka2B());
                    ArmiaB[ArmiaB.size()-1].setTexture(Postac2B);
                    ArmiaB[ArmiaB.size()-1].setTextureRect(sf::IntRect(528, 0, 32, 48)); //left, top, width, height
                    ArmiaB[ArmiaB.size()-1].setScale(5.0, 5.0);
                }
                if (Przeciwnik==3)
                {
                    ArmiaB.emplace_back(Jednostka3B());
                    ArmiaB[ArmiaB.size()-1].setTexture(Postac3B);
                    ArmiaB[ArmiaB.size()-1].setTextureRect(sf::IntRect(528, 0, 32, 48)); //left, top, width, height
                    ArmiaB[ArmiaB.size()-1].setScale(5.0, 5.0);
                }
                if (Przeciwnik==4)
                {
                    ArmiaB.emplace_back(Jednostka4B());
                    ArmiaB[ArmiaB.size()-1].setTexture(Postac4B);
                    ArmiaB[ArmiaB.size()-1].setTextureRect(sf::IntRect(528, 0, 32, 48)); //left, top, width, height
                    ArmiaB[ArmiaB.size()-1].setScale(5.0, 5.0);
                }
                if (Przeciwnik==5)
                {
                    ArmiaB.emplace_back(Jednostka5B());
                    ArmiaB[ArmiaB.size()-1].setTexture(Postac5B);
                    ArmiaB[ArmiaB.size()-1].setTextureRect(sf::IntRect(528, 0, 32, 48)); //left, top, width, height
                    ArmiaB[ArmiaB.size()-1].setScale(5.0, 5.0);
                }
                SpawnTimer=0;
            }

            //###################################################################################################################################################


            if (CastleHealth<=0)
            {
                EndingA=true;
            }
            if (CastleHealthB<=0)
            {
                EndingB=true;
            }
        }


        // check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;
        while (window.pollEvent(event))
        {
            // "close requested" event: we close the window
            if (event.type == sf::Event::Closed)
                window.close();

//###################################################################################################################################################

            if (event.type == sf::Event::MouseButtonPressed)
            {
                if ((EndingA==false) && (EndingB==false))
                {
                    if(event.mouseButton.button == sf::Mouse::Left)
                    {
                        sf::Vector2i mouse_pos = sf::Mouse::getPosition(window);
                        if ((mouse_pos.y>25) && (mouse_pos.y<75) && (mouse_pos.x>300) && (mouse_pos.x<350))
                        {
                            if (gold>=10)
                            {
                                gold=gold-10;
                                Armia.emplace_back(Jednostka1());
                                Armia[Armia.size()-1].setTexture(Postac1);
                                Armia[Armia.size()-1].setTextureRect(sf::IntRect(16, 0, 32, 48)); //left, top, width, height
                                Armia[Armia.size()-1].setScale(5.0, 5.0);
                            }
                        }
                    }

                    if(event.mouseButton.button == sf::Mouse::Left)
                    {
                        sf::Vector2i mouse_pos = sf::Mouse::getPosition(window);
                        if ((mouse_pos.y>25) && (mouse_pos.y<75) && (mouse_pos.x>400) && (mouse_pos.x<450))
                        {
                            if (gold>=15)
                            {
                                gold=gold-15;
                                Armia.emplace_back(Jednostka2());
                                Armia[Armia.size()-1].setTexture(Postac2);
                                Armia[Armia.size()-1].setTextureRect(sf::IntRect(16, 0, 32, 48)); //left, top, width, height
                                Armia[Armia.size()-1].setScale(5.0, 5.0);
                            }
                        }
                    }

                    if(event.mouseButton.button == sf::Mouse::Left)
                    {
                        sf::Vector2i mouse_pos = sf::Mouse::getPosition(window);
                        if ((mouse_pos.y>25) && (mouse_pos.y<75) && (mouse_pos.x>500) && (mouse_pos.x<550))
                        {
                            if (gold>=15)
                            {
                                gold=gold-15;
                                Armia.emplace_back(Jednostka3());
                                Armia[Armia.size()-1].setTexture(Postac3);
                                Armia[Armia.size()-1].setTextureRect(sf::IntRect(16, 0, 32, 48)); //left, top, width, height
                                Armia[Armia.size()-1].setScale(5.0, 5.0);
                            }

                        }
                    }

                    if(event.mouseButton.button == sf::Mouse::Left)
                    {
                        sf::Vector2i mouse_pos = sf::Mouse::getPosition(window);
                        if ((mouse_pos.y>25) && (mouse_pos.y<75) && (mouse_pos.x>600) && (mouse_pos.x<650))
                        {
                            if (gold>=25)
                            {
                                gold=gold-25;
                                Armia.emplace_back(Jednostka4());
                                Armia[Armia.size()-1].setTexture(Postac4);
                                Armia[Armia.size()-1].setTextureRect(sf::IntRect(16, 0, 32, 48)); //left, top, width, height
                                Armia[Armia.size()-1].setScale(5.0, 5.0);
                            }

                        }
                    }

                    if(event.mouseButton.button == sf::Mouse::Left)
                    {
                        sf::Vector2i mouse_pos = sf::Mouse::getPosition(window);
                        if ((mouse_pos.y>25) && (mouse_pos.y<75) && (mouse_pos.x>700) && (mouse_pos.x<750))
                        {
                            if (gold>=50)
                            {
                                gold=gold-50;
                                Armia.emplace_back(Jednostka5());
                                Armia[Armia.size()-1].setTexture(Postac5);
                                Armia[Armia.size()-1].setTextureRect(sf::IntRect(16, 0, 32, 48)); //left, top, width, height
                                Armia[Armia.size()-1].setScale(5.0, 5.0);
                            }

                        }
                    }

                    if(event.mouseButton.button == sf::Mouse::Left)
                    {
                        sf::Vector2i mouse_pos = sf::Mouse::getPosition(window);
                        if ((mouse_pos.y>25) && (mouse_pos.y<75) && (mouse_pos.x>950) && (mouse_pos.x<1000))
                        {
                            if (gold>=DmgCost)
                            {
                                gold=gold-DmgCost;
                                PlayerDMG=PlayerDMG+2;
                                DmgCost=DmgCost+30;
                            }

                        }
                    }

                    if(event.mouseButton.button == sf::Mouse::Left)
                    {
                        sf::Vector2i mouse_pos = sf::Mouse::getPosition(window);
                        if ((mouse_pos.y>25) && (mouse_pos.y<75) && (mouse_pos.x>1100) && (mouse_pos.x<1150))
                        {
                            if (gold>=SpeedCost)
                            {
                                gold=gold-SpeedCost;
                                PlayerSpeed=PlayerSpeed+5;
                                SpeedCost=SpeedCost+15;
                            }

                        }
                    }

                    if(event.mouseButton.button == sf::Mouse::Left)
                    {
                        sf::Vector2i mouse_pos = sf::Mouse::getPosition(window);
                        if ((mouse_pos.y>25) && (mouse_pos.y<75) && (mouse_pos.x>1250) && (mouse_pos.x<1300))
                        {
                            if (gold>=IncomeCost)
                            {
                                gold=gold-IncomeCost;
                                PlayerIncome=PlayerIncome+1;
                                IncomeCost=IncomeCost+60;
                            }

                        }
                    }
                }
            }

//###################################################################################################################################################

            if (event.type == sf::Event::KeyReleased)
            {
                if ((EndingA==false) && (EndingB==false))
                {
                    if (event.key.code == sf::Keyboard::Num1)
                    {
                        if (gold>=10)
                        {
                            gold=gold-10;
                            Armia.emplace_back(Jednostka1());
                            Armia[Armia.size()-1].setTexture(Postac1);
                            Armia[Armia.size()-1].setTextureRect(sf::IntRect(16, 0, 32, 48)); //left, top, width, height
                            Armia[Armia.size()-1].setScale(5.0, 5.0);
                        }
                    }

                    if (event.key.code == sf::Keyboard::Num2)
                    {
                        if (gold>=15)
                        {
                            gold=gold-15;
                            Armia.emplace_back(Jednostka2());
                            Armia[Armia.size()-1].setTexture(Postac2);
                            Armia[Armia.size()-1].setTextureRect(sf::IntRect(16, 0, 32, 48)); //left, top, width, height
                            Armia[Armia.size()-1].setScale(5.0, 5.0);
                        }
                    }

                    if (event.key.code == sf::Keyboard::Num3)
                    {
                        if (gold>=15)
                        {
                            gold=gold-15;
                            Armia.emplace_back(Jednostka3());
                            Armia[Armia.size()-1].setTexture(Postac3);
                            Armia[Armia.size()-1].setTextureRect(sf::IntRect(16, 0, 32, 48)); //left, top, width, height
                            Armia[Armia.size()-1].setScale(5.0, 5.0);
                        }
                    }

                    if (event.key.code == sf::Keyboard::Num4)
                    {
                        if (gold>=25)
                        {
                            gold=gold-25;
                            Armia.emplace_back(Jednostka4());
                            Armia[Armia.size()-1].setTexture(Postac4);
                            Armia[Armia.size()-1].setTextureRect(sf::IntRect(16, 0, 32, 48)); //left, top, width, height
                            Armia[Armia.size()-1].setScale(5.0, 5.0);
                        }
                    }

                    if (event.key.code == sf::Keyboard::Num5)
                    {
                        if (gold>=50)
                        {
                            gold=gold-50;
                            Armia.emplace_back(Jednostka5());
                            Armia[Armia.size()-1].setTexture(Postac5);
                            Armia[Armia.size()-1].setTextureRect(sf::IntRect(16, 0, 32, 48)); //left, top, width, height
                            Armia[Armia.size()-1].setScale(5.0, 5.0);
                        }
                    }

                    if (event.key.code == sf::Keyboard::Q)
                    {
                        if (gold>=DmgCost)
                        {
                            gold=gold-DmgCost;
                            PlayerDMG=PlayerDMG+2;
                            DmgCost=DmgCost+30;
                        }
                    }

                    if (event.key.code == sf::Keyboard::W)
                    {
                        if (gold>=SpeedCost)
                        {
                            gold=gold-SpeedCost;
                            PlayerSpeed=PlayerSpeed+5;
                            SpeedCost=SpeedCost+15;
                        }
                    }

                    if (event.key.code == sf::Keyboard::E)
                    {
                        if (gold>=IncomeCost)
                        {
                            gold=gold-IncomeCost;
                            PlayerIncome=PlayerIncome+1;
                            IncomeCost=IncomeCost+60;
                        }
                    }
                }
            }

//###################################################################################################################################################

        }

        // clear the window with black color
        window.clear(sf::Color::Black);

        // draw everything here...
        window.draw(tlo);

        window.draw(zamek);
        window.draw(zamek1);
        window.draw(brama);
        window.draw(zamekB);
        window.draw(zamekB1);
        window.draw(bramaB);
        window.draw(podloze);

        window.draw(hub);
        window.draw(MaxHPbar);
        window.draw(HPbar);
        window.draw(MaxHPbarB);
        window.draw(HPbarB);
        window.draw(Unit1);
        window.draw(Unit2);
        window.draw(Unit3);
        window.draw(Unit4);
        window.draw(Unit5);

        window.draw(text);
        window.draw(text2);

        window.draw(UnitCost1);
        window.draw(Unit1Name);
        window.draw(Unit1Label);
        window.draw(UnitCost2);
        window.draw(Unit2Name);
        window.draw(Unit2Label);
        window.draw(UnitCost3);
        window.draw(Unit3Name);
        window.draw(Unit3Label);
        window.draw(UnitCost4);
        window.draw(Unit4Name);
        window.draw(Unit4Label);
        window.draw(UnitCost5);
        window.draw(Unit5Name);
        window.draw(Unit5Label);

        window.draw(Line1);
        window.draw(Line2);

        window.draw(TitleBg);
        window.draw(TitleBg2);
        window.draw(Title);

        window.draw(DmgUpgrade);
        window.draw(SpeedUpgrade);
        window.draw(IncomeUpgrade);

        window.draw(Health);
        window.draw(HealthB);
        window.draw(DmgCostText);
        window.draw(DmgLabel);
        window.draw(SpeedCostText);
        window.draw(SpeedLabel);
        window.draw(IncomeCostText);
        window.draw(IncomeLabel);
        window.draw(DmgPodpis);
        window.draw(SpeedPodpis);
        window.draw(IncomePodpis);



        for(int i=0; i<Armia.size(); i++)
        {
            window.draw(Armia[i]);
        }

        for(int i=0; i<ArmiaB.size(); i++)
        {
            window.draw(ArmiaB[i]);
        }


        if (EndingA==true)
        {
            window.draw(CreditsA);
        }
        if (EndingB==true)
        {
            window.draw(CreditsB);
        }

        // end the current frame
        window.display();
    }

    return 0;
}
