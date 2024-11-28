/*
   Gates of Hades - Open Source Game  
   Copyright (c) 2024 Arda Koyuncu  

   Permission is hereby granted, free of charge, to any person obtaining a copy
   of this software and associated documentation files (the "Software"), to deal
   in the Software without restriction, including without limitation the rights
   to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
   copies of the Software, and to permit persons to whom the Software is
   furnished to do so, subject to the following conditions:

   The above copyright notice and this permission notice shall be included in all
   copies or substantial portions of the Software.

   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
   IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
   FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
   AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
   LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
   OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
   SOFTWARE.
*/

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <string>
#include <thread>
#include <chrono>
#include <stdlib.h>
#include <cstdlib>
#include <csignal>
#include <time.h>


#define repeat(a) for (int i = 0 ; i < a ; i++)
using namespace std; using namespace sf;

VideoMode Windowed(1466, 768);
RenderWindow Hades(Windowed,"Gates of Hades");
View view(FloatRect(0, 0, 1466, 768)); Clock cooldownClock;


const string itchUrl = "https://ardaonlyprojects.itch.io/";
const string ytUrl = "https://www.youtube.com/@onlyarda";
/*
YOU CAN'T CHANGE THE LINKS
*/


string exeFile = "Gates of Hades ALPHA";


Event events; Font font; Texture BackGroundTexture; Texture DarkTexture;
Texture doorTexture; Texture doorOpenTexture; Texture cursorTexture; Texture grapTexture;
Texture handTexture; Music ambient; Music DoorOpen; Music DoorClose;
Texture OutsideTexture; Texture SlotTexture; Texture SlotCookieTexture;
Texture ScoutTexture; Music error; Texture ScaryScout; Texture redTexture;
Music collect; Music laugh; Music scoutSound; Texture cookieTexture; Texture red2;
Music scoutJumpscareSound; Texture EyebornTexture; Texture EyebornHandTexture1; Texture EyebornHandTexture2;
Music EyebornTalk; Texture button1Texture; Texture button2Texture; Texture buttonbackgroundTexture;
Texture moneyTexture; Texture shopBackgroundTexture; Texture batteryTexture; Texture batterySlot;
Texture heart1; Texture heart2; Texture heart3; Texture heart4; Texture button3Texture;
Texture sussyTexture; Texture topSecretTexture; Texture backgorund3Texture; Texture demonManTexture;
Music demonManSound1; Music demonManSound2; Music demonManSound3; Music demonManSound4; Music demonManSound5; 
Texture MysteryCaseTexture; Texture CoinTexture; Texture playDoorTexture; Texture settingsDoorTexture; Texture playDoorOpenTexture;
Texture settingsDoorOpenTexture; Texture gameIconTexture; Texture menuBackgroundTexture; Texture ardaonlyTexture;
Texture itchTexture; Texture ytTexture; Texture demonKidTexture; Music burp; Texture characterIcon; Texture nullTexture;
Music put; Texture madebyArdaKoyuncuTexture; Texture CancelTexture; Texture buyButtonTexture; Texture snowmanTexture; Texture caseBag;
Music take; Music heartBreak; Text HoursSurvived; Music door, door2; Music doorBreak; Texture AlphaTexture;

string object=""; string text="";

bool isFullscreen = false; bool f11Pressed = false;
short int CursorStyle=1; bool doorisOpen=false; bool playerCanOpenTheDoor=true;
bool close=0; bool touching=false; bool showInfo=true; bool mouseClicked = false;
bool firstTime=true; bool green=false; bool dragging=false; bool playerCanOpenTheTelevision = true;
bool TelevisionMouseClicked = false; bool TelevisionIsOpen = false; bool errMessage = false;
bool scoutisHorror = true; bool red=false; bool mouseClicked2 = false; bool playerCanClick = true;
bool butPlayerCanUseTheslot = false; bool playerCanGiveTheCookie = false; bool didPlayerGiveTheCookieToScout = false;
short int whichButtonIsTouchingCursor=0; bool badMessage = false; bool playerIsIntheShop = true;
bool button3Clicked = false; bool button4Clicked = false; bool game = false; bool cantClickOnTheMenu = false;
bool gasIsStarted = false; bool startGas = false; bool ClickingToCancel = false; bool mouseReleased = true; bool heartAnimationStarted = false;
bool stopped = false;

RectangleShape redScreen(Vector2f(100,100));
float alpha = 50.f;
bool healing = false;
bool increasing = true;


int playermoney = 0; short int shopPage = 1; short int health = 100; short int theGivedMoneyToPlayer = 0; short int randomThing = 0;
int hoursSurvived = 0;

Color moneyColor(255,177,0); Color heartColor(255,0,0); 

Vector2f scoutxy(830,200); Vector2f eyebornxy(865,168); Vector2f EyebornHand1xy(800,400);
Vector2f EyebornHand2xy(1600,400);

const Vector2f origScoutxy(830,200); const Vector2f origEyebornxy(865,168); const Vector2f origEyebornHand1xy(800,400);
const Vector2f origEyebornHand2xy(1600,400);

int getFirstEmptySlot(string inventory[], int size); void setRandomPrices();

/*

    ! EKLENECEKLER

    kurabiye'ye sağ tıklayınca can doldurma

    kardan adam

    ölünce animasyon


*/

short int prices[5]={
    0,0,0,0,0
};

bool showlist[20]={
    false,    // scout
    false,  // cookie
    false,  // red jumpscare background
    false, // jumpscare scout
    false, // Eyeborn
    false, // Eyeborn hand 1
    false, // Eyeborn hand 2
    false, // Eyeborn message
    false, // button1
    false, // button2
    false, // button background
    false, // text
    false, // background
    false, // shop all
    false, // demon man      number: 14
    false, // demon man offer text
    false, // demon kid number: 16
    false, // which Character is will come icon
    false, // snowman

};

string inventory[5] = {
    // is starting from 1 not 0
    "NULL"


};
string errorMessage=""; string whoIsIntheDoor=""; string whatPlayerIsDragging="";
string EyebornMessage=""; string demonManTalk = "";

void batteryGiven(){
    if (whoIsIntheDoor == "scout"){ characterIcon = ScoutTexture; }
    if (whoIsIntheDoor == "eyeborn"){ characterIcon = EyebornTexture; }
    if (whoIsIntheDoor == "demonkid"){ characterIcon = demonKidTexture; }
    if (whoIsIntheDoor == "demonman"){ characterIcon = demonManTexture; }
    if (whoIsIntheDoor == "snowman"){ characterIcon = snowmanTexture; }
    showlist[17] = true; put.stop(); put.play();
    this_thread::sleep_for(chrono::seconds(5));
    showlist[17] = false;
    characterIcon = nullTexture;
}

void demonKidGas(RenderWindow& window) {
    srand(time(0));
    gasIsStarted = true;
    repeat(rand() % 5){
        burp.stop(); burp.play();
        health -= 20;
        if (close == 1){return;}
        Texture greenTexture;
        if (!greenTexture.loadFromFile("Assets/green.png")) {
            return;
        }

        vector<Sprite> sprites(50);
        for (auto& sprite : sprites) {
            sprite.setTexture(greenTexture);
            sprite.setScale(3.0f,3.0f);
            sprite.setPosition(rand() % window.getSize().x, rand() % window.getSize().y);
            sprite.setColor(Color(255, 255, 255, 0));
        }

        Clock clock;
        float fadeTime = 1.0f;
        bool fadingOut = false;

        while (window.isOpen()) {

            Event event;
            while (window.pollEvent(event)) {
                if (event.type == Event::Closed) {
                    window.close();
                }
            }

            float elapsed = clock.getElapsedTime().asSeconds();

            if (elapsed <= fadeTime) {
                for (auto& sprite : sprites) {
                    int alpha = static_cast<int>(255 * (elapsed / fadeTime));
                    sprite.setColor(Color(255, 255, 255, alpha));
                }
            } else if (!fadingOut) {
                fadingOut = true;
                clock.restart();
            } else if (elapsed <= fadeTime) {
                for (auto& sprite : sprites) {
                    int alpha = static_cast<int>(255 * (1 - (elapsed / fadeTime)));
                    sprite.setColor(Color(255, 255, 255, alpha));
                }
            } else {
                break;
            }

            window.clear(Color::Black);
            for (const auto& sprite : sprites) {
                if (close == 1){return;}
                window.draw(sprite);
            }
            window.display();
        }
    }
    gasIsStarted = false;
}

void startGame(){
    this_thread::sleep_for(chrono::seconds(2));
    game = 1;
}

void openURL(const string& url) {
    #ifdef _WIN32
        system(("start " + url).c_str()); // Windows
    #elif __APPLE__
        system(("open " + url).c_str()); // macOS
    #elif __linux__
        system(("xdg-open " + url).c_str()); // Linux
    #else
        cerr << "Error" << endl;
    #endif
}

void giveRandomItems() {
    int random = rand() % 2 + 1;
    int emptySlot = getFirstEmptySlot(inventory, 5);
    if (emptySlot != -1) {
        if (random == 1)
            inventory[emptySlot] = "cookie";
        else if (random == 2)
            inventory[emptySlot] = "battery";
    } else {
        cout << "No empty slots available in inventory\n";
    }
}

void setRandomPrices(){
    srand(time(0));
    prices[0] = rand()% 30 + 10;
    prices[1] = rand()% 40 + 20;

}

void giveMoney(int number){
    repeat(number){
        playermoney++;
        this_thread::sleep_for(chrono::milliseconds(100));
    }
}
void unGiveMoney(int number){
    repeat(number){
        playermoney--;
        this_thread::sleep_for(chrono::milliseconds(100));
    }
}

void eyebornTalk(){
        srand(time(0));
        string whatGonnaSay="";
        if (!(whoIsIntheDoor == "eyeborn") || (close == 1)){ return; }
        this_thread::sleep_for(chrono::seconds(2));
        EyebornMessage = "";
        int random = rand() % 5 + 1;
        if (!badMessage == 1){
            if (random == 1){
                whatGonnaSay = "I'm selling best stuffs";
            }if (random == 2){
                whatGonnaSay = "Do you want to buy something?";
            }if (random == 3){
                whatGonnaSay = "Selling cheap stuffs";
            }if (random == 4){
                whatGonnaSay = "I'm here to sell cheap stuffs";
            }if (random == 5){
                whatGonnaSay = "I'm not selling dreams wanna buy\n something?";
            }
        }else if (badMessage == 1){
            random = rand() % 4 + 1;
            if (random == 1){
                whatGonnaSay = "Dumb";
            }if (random == 2){
                whatGonnaSay = "Fuck off";
            }if (random == 3){
                whatGonnaSay = "You will can't buy items again";
            }if (random == 4){
                whatGonnaSay = "What a jerk";
            }
        }
        for (int i = 0 ; i < whatGonnaSay.length() ; i++){
            EyebornTalk.stop();
            EyebornTalk.play();
            EyebornMessage = EyebornMessage + whatGonnaSay[i];
            this_thread::sleep_for(std::chrono::milliseconds(100));
        }
}

int getFirstEmptySlot(string inventory[], int size) {
    for (int i = 0; i < size; ++i) {
        if ((inventory[i].empty()) || (inventory[i] == "")  && !(inventory[i] == "NULL")) {
            return i;
        }
    }
    return -1;
}

int isHave(const string inventory[], int size, const string& item) {
    for (int i = 0; i < size; ++i) {
        if (inventory[i] == item) {
            return 1;
        }
    }
    return -1;
}

int whichSlotIsHave(const string inventory[], int size, const string& item) {
    for (int i = 0; i < size; ++i) {
        if (inventory[i] == item) {
            return i;
        }
    }
    return -1;
}

void scoutJumpscare(){
    showlist[2] = true; showlist[3] = true;
    scoutJumpscareSound.stop(); scoutJumpscareSound.play();
}

void heal(){
    srand(time(0));
    healing = true;
    repeat(rand() % 70 + 30){
        if (health <= 100){
            health++;
            this_thread::sleep_for(chrono::milliseconds(100));
        }
    }
    healing = false;
}

string prevCharacter = ""; short int randomNumber = 0;

struct SelectRandomCharacter {
    static void starterCharacters() {
        int randomNumber;
        do {
            randomNumber = rand() % 10 + 1; // 1 ile 10 arasında rastgele bir sayı
            if (randomNumber <= 2) {       // %20 ihtimalle Demonman
                whoIsIntheDoor = "demonman";
            } else if (randomNumber <= 5) { // %30 ihtimalle Eyeborn
                whoIsIntheDoor = "eyeborn";
            } else {                        // %50 ihtimalle Snowman
                whoIsIntheDoor = "snowman";
            }
        } while (prevCharacter == whoIsIntheDoor); // Aynı karakter seçildiyse yeniden dene
        prevCharacter = whoIsIntheDoor; // Önceki karakteri güncelle
    }
    static void allCharacters() {
        int randomNumber;
        do {
            randomNumber = rand() % 10 + 1; // 1 ile 10 arasında rastgele bir sayı
            if (randomNumber == 1) {       // %10 ihtimalle Demonman
                whoIsIntheDoor = "demonman";
            } else if (randomNumber <= 3) { // %20 ihtimalle Eyeborn
                whoIsIntheDoor = "eyeborn";
            } else if (randomNumber <= 6) { // %30 ihtimalle Snowman
                whoIsIntheDoor = "snowman";
            } else if (randomNumber <= 8) { // %20 ihtimalle Demonkid
                whoIsIntheDoor = "demonkid";
            } else {                        // %20 ihtimalle Scout
                whoIsIntheDoor = "scout";
            }
        } while (prevCharacter == whoIsIntheDoor); // Aynı karakter seçildiyse yeniden dene
        prevCharacter = whoIsIntheDoor; // Önceki karakteri güncelle
    }
};


void charactersDoorAI() {
    srand(time(0));
    while (true) {
        if (game) {
            this_thread::sleep_for(chrono::seconds(rand() % 40 + 5));
            if (whoIsIntheDoor == "") { // eğer kapıda kimse yoksa
                if (hoursSurvived <= 1) { // eğer hayattaa kalma süresi 1'den fazlaysa
                   SelectRandomCharacter::starterCharacters(); // başlangıç karakterlerini çağır
                }else{
                    SelectRandomCharacter::allCharacters(); // değilse çağırma
                }

                if (!doorisOpen){ // eğer kapı kapalıysa
                    randomNumber = rand()% 2 + 1; // rastgele sayı seç
                    door2.stop(); door2.play(); // oyuncu kapı sesini gerçek zannetmemesi için ilk başta gerçekci olmayan kapı sesi
                    if (randomNumber == 1){
                        door.stop(); door.play();
                    }if (randomNumber == 2){
                        door2.stop(); door2.play();
                    }
                    repeat(40){
                        this_thread::sleep_for(chrono::milliseconds(100));
                        if (doorisOpen){
                            break;
                        }
                    }
                    /*
                        40 defa tekrarladığı sırada bekliyor ve eğer kapı açılırsa bu döngüden
                        çıkıyor
                    */
                }
                if (!doorisOpen){
                    randomNumber = rand()% 5 + 1;
                    if (randomNumber == 1){
                        doorBreak.stop(); doorBreak.play();
                        doorisOpen = true;
                    }else{
                        whoIsIntheDoor = "";
                    }
                }
                /*
                    eğer kapı tıklanmasına rağmen açılmadıysa bir şans olarak 
                    kapı kırılabilir ve karakter gelir ama bu şans tutturulamazsa
                    kapı kırılmaz ve karakter kapıdan gider
                */


            }
        }
    }
}






void ai() {
    srand(time(0));
    short int random = 0, get = 0;
    Clock clock;
    Time deltaTime = clock.restart();

    thread charactersDoor(charactersDoorAI); charactersDoor.detach();
    for (;;) {   
        if (close) { return; }
        if ((whoIsIntheDoor == "snowman") && (doorisOpen)){
            showlist[18] = true; playerCanClick = false; playerCanOpenTheDoor = false;
            this_thread::sleep_for(chrono::seconds(2));
            heal();
            this_thread::sleep_for(chrono::seconds(1));
            whoIsIntheDoor = "";
            DoorClose.stop(); DoorClose.play();
            showlist[18] = false; playerCanClick = true; playerCanOpenTheDoor = true; doorisOpen = false;
        }
        if ((whoIsIntheDoor == "demonkid") && (doorisOpen)){
            showlist[16] = true; playerCanClick = false; playerCanOpenTheDoor = false;
            this_thread::sleep_for(chrono::seconds(2));
            cout <<"Gas is started\n";
            gasIsStarted = true;
            this_thread::sleep_for(chrono::seconds(6));
            showlist[16] = false; playerCanClick = true; playerCanOpenTheDoor = true;
            doorisOpen = false;
            whoIsIntheDoor = "";
            DoorClose.stop(); DoorClose.play();
        }
        if ((whoIsIntheDoor == "demonman") && (doorisOpen)){
            showlist[14] = true; playerCanClick = false; playerCanOpenTheDoor = false;
            demonManTalk = "";
            this_thread::sleep_for(chrono::seconds(2));
            string TemporyDemonManTalk = "Do you choose the mystery \ncase or the money?";
            for (int i  = 0 ; i < TemporyDemonManTalk.length() ; i++){
                int randomVoice = rand() % 5 + 1;
                if (randomVoice == 1){demonManSound1.stop();demonManSound1.play();}
                if (randomVoice == 2){demonManSound2.stop();demonManSound2.play();}
                if (randomVoice == 3){demonManSound3.stop();demonManSound3.play();}
                if (randomVoice == 4){demonManSound4.stop();demonManSound4.play();}
                if (randomVoice == 5){demonManSound5.stop();demonManSound5.play();}
                demonManTalk = demonManTalk + TemporyDemonManTalk[i];
                this_thread::sleep_for(std::chrono::milliseconds(50));
            }
            this_thread::sleep_for(chrono::seconds(2));
            showlist[12] = true; showlist[15] = true; demonManTalk = ""; showInfo = false;
            stopped = true;
            while (showlist[15] == 1){if (close == 1){return;}}
            stopped = false;
            showlist[12] = false;
            this_thread::sleep_for(chrono::seconds(2));
            TemporyDemonManTalk = "Good choice!";
            for (int i  = 0 ; i < TemporyDemonManTalk.length() ; i++){
                int randomVoice = rand() % 5 + 1;
                if (randomVoice == 1){demonManSound1.stop();demonManSound1.play();}
                if (randomVoice == 2){demonManSound2.stop();demonManSound2.play();}
                if (randomVoice == 3){demonManSound3.stop();demonManSound3.play();}
                if (randomVoice == 4){demonManSound4.stop();demonManSound4.play();}
                if (randomVoice == 5){demonManSound5.stop();demonManSound5.play();}
                demonManTalk = demonManTalk + TemporyDemonManTalk[i];
                this_thread::sleep_for(std::chrono::milliseconds(50));
            }
            this_thread::sleep_for(chrono::seconds(1));
            DoorClose.stop(); DoorClose.play();
            doorisOpen = false;
            playerCanClick = true; playerCanOpenTheDoor = true;
            whoIsIntheDoor = ""; showlist[14] = false;

        }
        if ((whoIsIntheDoor == "eyeborn") && (doorisOpen)){
            ClickingToCancel = false;
            shopPage = 1;
            EyebornMessage = "";
            badMessage = false;
            showlist[4] = true; showlist[5] = true; showlist[6] = true; showlist[7] = true;
            playerCanClick = false; playerCanOpenTheDoor = false;
            setRandomPrices();
            eyebornTalk();
            this_thread::sleep_for(chrono::seconds(1));
            showlist[8] = true; showlist[9] = true; showlist[10] = true; showlist[11] = true;
            showInfo = false;
            stopped = true;
            this_thread::sleep_for(chrono::seconds(1));
            while (true){
                if (close) { return; }
                if (Mouse::isButtonPressed(Mouse::Left)){
                    if (whichButtonIsTouchingCursor == 1){
                        showlist[8] = false; showlist[9] = false; showlist[10] = false; showlist[11] = false;
                        showlist[12] = true; showlist[13] = true;
                        while (showlist[13] = true){
                            if (close == 1){return;}
                            if (ClickingToCancel){
                                showlist[12] = false; showlist[13] = false; showlist[13] = false;
                                this_thread::sleep_for(chrono::seconds(2));
                                playerCanClick = true; playerCanOpenTheDoor = true; doorisOpen = false;
                                showlist[4] = false; showlist[5] = false; showlist[6] = false; showlist[7] = false;
                                stopped = false;
                                whoIsIntheDoor = "";
                                DoorClose.stop(); DoorClose.play();
                                break; continue;
                            }

                        }
                    }else if (whichButtonIsTouchingCursor == 2){
                        stopped = false;
                        showlist[8] = false; showlist[9] = false; showlist[10] = false; showlist[11] = false;
                        badMessage = true;
                        eyebornTalk();
                        this_thread::sleep_for(chrono::seconds(1));
                        whoIsIntheDoor = "";
                        doorisOpen = false;
                        DoorClose.stop(); DoorClose.play();
                        playerCanClick = true; playerCanOpenTheDoor = true; showInfo = true;
                        showlist[4] = false; showlist[5] = false; showlist[6] = false; showlist[7] = false;
                        break;
                    }
                }
            }
        }
        if ((whoIsIntheDoor == "scout") && (doorisOpen)) {
            didPlayerGiveTheCookieToScout = false;
            random = rand() % 5 + 1;
            showlist[0] = true;
            playerCanOpenTheDoor = false;
            scoutisHorror = false;
            if (random == 1) {
                scoutisHorror = true;
                playerCanGiveTheCookie = true;
                butPlayerCanUseTheslot = true;
                playerCanClick = false;
                red = true;
                scoutSound.stop();
                scoutSound.play();
                repeat(4){
                    this_thread::sleep_for(chrono::seconds(1));
                    if (didPlayerGiveTheCookieToScout){break;}
                }
                if (!didPlayerGiveTheCookieToScout){
                    playerCanGiveTheCookie = false;
                    butPlayerCanUseTheslot = false;
                    scoutJumpscare();
                    this_thread::sleep_for(chrono::seconds(4));
                    DoorClose.stop();
                    DoorClose.play();
                    doorisOpen = 0;
                    whoIsIntheDoor = "";
                    playerCanOpenTheDoor = true;
                    showlist[0] = false;
                    playerCanGiveTheCookie = false;
                    playerCanClick = true;
                    showlist[2] = false; showlist[3] = false;
                    red = 0;
                    health = 0;
                    return;
                }else{
                    scoutisHorror = false;
                    red = false;
                    laugh.stop();
                    scoutSound.stop();
                    laugh.play();
                    butPlayerCanUseTheslot = false;
                    this_thread::sleep_for(chrono::seconds(10));
                    DoorClose.stop();
                    DoorClose.play();
                    doorisOpen = 0;
                    whoIsIntheDoor = "";
                    health = 0;
                    showlist[0] = false;
                    playerCanGiveTheCookie = false;
                }
            } else {
                scoutisHorror = false;
                red = false;
                laugh.stop();
                laugh.play();
                this_thread::sleep_for(chrono::seconds(2));
                int slot = getFirstEmptySlot(inventory, 5);
                if (slot != -1) {
                    inventory[slot] = "cookie";
                } else {
                    cout << "Inventory is full!" << endl;
                }
                collect.stop();
                collect.play();
                this_thread::sleep_for(chrono::seconds(8));
                DoorClose.stop();
                DoorClose.play();
                doorisOpen = 0;
                whoIsIntheDoor = "";
                playerCanOpenTheDoor = true;
                showlist[0] = false;
            }
            //while ((whoIsIntheDoor == "scout") && (doorisOpen)) { if (close) { return; } }
        }
    }
}

void hours(){
    for (;;){
        if (game){
        repeat(100){
            this_thread::sleep_for(chrono::seconds(1));
            if (stopped){
                while (stopped);
            }
        }
            hoursSurvived++;
        }
    }
}

void errorMessageShow() {
    for (;;) {
        if (close) { return; }
        if (errMessage) {
            errMessage = false;
            errorMessage = "You Don't have Battery";
            this_thread::sleep_for(chrono::seconds(1));
            errorMessage = "";
        }
    }
}

void beginner(){

    /*
    int state=1;
    for (;;){
        if (state == 1){
            text = "Use 'A' and 'D' buttons to move camera";
            this_thread::sleep_for(chrono::seconds(3));
            if (Keyboard::isKeyPressed(Keyboard::A) || Keyboard::isKeyPressed(Keyboard::D)){
                green=true;
                this_thread::sleep_for(chrono::seconds(4));
                state = 2;
                green=false;
            }
        }else if (state == 2){
            text = "Click to Door for open the Door";
            if (doorisOpen){
                green=true;
                this_thread::sleep_for(chrono::seconds(4));
                green=false;
                text = "All Theese Informations is enought \n\t\tto play the game :D";
                this_thread::sleep_for(chrono::seconds(4));
                text="";
                return;
            }
        }
        if (close){return;}
    }
    */
}

short int asset = 1;

void heartWait(){
    Listener::setGlobalVolume(0);
    this_thread::sleep_for(chrono::seconds(2));
    asset = 2;
    this_thread::sleep_for(chrono::seconds(2));
    asset = 3;
    this_thread::sleep_for(chrono::seconds(2));
    asset = 4;
    this_thread::sleep_for(chrono::seconds(2));
    asset = 5;
    this_thread::sleep_for(chrono::seconds(5));
    asset = 6;
    this_thread::sleep_for(chrono::seconds(1));
    asset = 7;
    
}

int main(){
    Hades.setFramerateLimit(10000); Hades.setView(view);
    srand(time(0));

    randomThing = rand()% 6 + 1;

    if (!font.loadFromFile("Assets/VCRosdNEUE.ttf")){return -1;} if (!BackGroundTexture.loadFromFile("Assets/Background.png")){return -1;}
    if (!DarkTexture.loadFromFile("Assets/Dark.png")){return -1;} if (!doorTexture.loadFromFile("Assets/door.png")){return -1;}
    if (!doorOpenTexture.loadFromFile("Assets/dooropen.png")){return -1;} if (!cursorTexture.loadFromFile("Assets/Arrow.png")){return -1;}
    if (!handTexture.loadFromFile("Assets/Hand.png")){return -1;} if (!ambient.openFromFile("Assets/Ambient.ogg")){return -1;}
    if (!DoorOpen.openFromFile("Assets/Door Open.ogg")){return -1;} if (!DoorClose.openFromFile("Assets/Door Close.ogg")){return -1;}
    if (!OutsideTexture.loadFromFile("Assets/Outside.png")){return -1;} if (!SlotTexture.loadFromFile("Assets/slot.png")){return -1;}
    if (!grapTexture.loadFromFile("Assets/Drag.png")){return -1;} if (!SlotCookieTexture.loadFromFile("Assets/slotcookie.png")){return -1;}
    if (!ScoutTexture.loadFromFile("Assets/scout.png")){return -1;} if (!error.openFromFile("Assets/error.ogg")){return -1;}
    if (!ScaryScout.loadFromFile("Assets/scouthorror.png")){return -1;} if (!redTexture.loadFromFile("Assets/Red.png")){return -1;}
    if (!collect.openFromFile("Assets/collect.ogg")){return -1;} if (!laugh.openFromFile("Assets/scout laugh.ogg")){return -1;}
    if (!scoutSound.openFromFile("Assets/scout.ogg")){return -1;} if (!cookieTexture.loadFromFile("Assets/cookie.png")){return -1;}
    if (!red2.loadFromFile("Assets/red2.png")){return -1;} if (!scoutJumpscareSound.openFromFile("Assets/jumpscare.ogg")){return -1;}
    if (!EyebornHandTexture1.loadFromFile("Assets/EyebornHand1.png")){return -1;} if (!EyebornHandTexture2.loadFromFile("Assets/EyebornHand2.png")){return -1;}
    if (!EyebornTexture.loadFromFile("Assets/Eyeborn.png")){return -1;} if (!EyebornTalk.openFromFile("Assets/Eyeborn Talk.ogg")){return -1;}
    if (!button1Texture.loadFromFile("Assets/button.png")){return -1;} if (!button2Texture.loadFromFile("Assets/button2.png")){return -1;}
    if (!buttonbackgroundTexture.loadFromFile("Assets/buttonbackground.png")){return -1;} if (!moneyTexture.loadFromFile("Assets/money.png")){return -1;}
    if (!shopBackgroundTexture.loadFromFile("Assets/background2.png")){return -1;} if (!batteryTexture.loadFromFile("Assets/battery.png")){return -1;}
    if (!batterySlot.loadFromFile("Assets/slotbattery.png")){return -1;} if (!heart1.loadFromFile("Assets/heart.png")){return -1;}
    if (!heart2.loadFromFile("Assets/heart2.png")){return -1;} if (!heart3.loadFromFile("Assets/heart3.png")){return -1;} 
    if (!heart4.loadFromFile("Assets/heart4.png")){return -1;} if (!button3Texture.loadFromFile("Assets/button3.png")){return -1;}
    if (!sussyTexture.loadFromFile("Assets/sussy.jpg")){return -1;} if (!topSecretTexture.loadFromFile("Assets/top secret image.png")){return -1;} 
    if (!backgorund3Texture.loadFromFile("Assets/Outside2.png")){return -1;} if (!demonManTexture.loadFromFile("Assets/demonman.png")){return -1;}
    if (!demonManSound1.openFromFile("Assets/demonManTalk1.ogg")){return -1;} if (!demonManSound2.openFromFile("Assets/demonManTalk2.ogg")){return -1;}
    if (!demonManSound3.openFromFile("Assets/demonManTalk3.ogg")){return -1;} if (!demonManSound4.openFromFile("Assets/demonManTalk4.ogg")){return -1;}
    if (!demonManSound5.openFromFile("Assets/demonManTalk5.ogg")){return -1;} if (!playDoorTexture.loadFromFile("Assets/playdoor.png")){return -1;}
    if (!settingsDoorTexture.loadFromFile("Assets/settingsdoor.png")){return -1;} if (!gameIconTexture.loadFromFile("Assets/GameIcon.png")){return -1;}
    if (!menuBackgroundTexture.loadFromFile("Assets/background3.png")){return -1;} if (!ardaonlyTexture.loadFromFile("Assets/ardaonly.png")){return -1;} 
    if (!itchTexture.loadFromFile("Assets/itch.png")){return -1;} if (!ytTexture.loadFromFile("Assets/yt.png")){return -1;}
    if (!playDoorOpenTexture.loadFromFile("Assets/dooropen3.png")){return -1;} if (!demonKidTexture.loadFromFile("Assets/demonkid.png")){return -1;}
    if (!burp.openFromFile("Assets/burp.ogg")){return -1;} if (!put.openFromFile("Assets/put.ogg")){return -1;}
    if (!madebyArdaKoyuncuTexture.loadFromFile("Assets/made by arda koyuncu.png")){return -1;} // DON'T CHANGE
    if (!CancelTexture.loadFromFile("Assets/cancel.png")){return -1;} if (!buyButtonTexture.loadFromFile("Assets/buy.png")){return -1;}
    if (!take.openFromFile("Assets/take.ogg")){return -1;} if (!heartBreak.openFromFile("Assets/heart break.ogg")){return -1;}
    if (!caseBag.loadFromFile("Assets/case.png")){return -1;} if (!snowmanTexture.loadFromFile("Assets/snowman.png")){return -1;}
    if (!door.openFromFile("Assets/Door.ogg")){return -1;} if (!door2.openFromFile("Assets/Door 2.ogg")){return -1;}
    if (!doorBreak.openFromFile("Assets/door break.ogg")){return -1;} if (!AlphaTexture.loadFromFile("Assets/alpha.png")){return -1;}

    cout <<"Game Assets loaded perfectly!\n";

    Vector2f xy(0,0); Clock clock; 
    Sprite Background(BackGroundTexture); Sprite Dark; Sprite door; 
    Sprite cursor; Sprite Outside; Sprite cookie(cookieTexture); Sprite jumpscareBackground(red2);
    Sprite scoutJumpscare(ScaryScout); Sprite Eyeborn(EyebornTexture);
    Sprite EyebornHand1; Sprite EyebornHand2; Sprite button1(button1Texture); Sprite button2(button2Texture);
    Sprite buttonBackground(buttonbackgroundTexture); Sprite money(moneyTexture); Sprite shopBackground(shopBackgroundTexture);
    Sprite shopItem; RectangleShape itemFrame(Vector2f(550,500)); Sprite playerHeart; Sprite button3(button3Texture);
    Sprite button4(button3Texture); Sprite sussy(sussyTexture); Sprite topSecretImage(topSecretTexture); 
    Sprite Outside2(backgorund3Texture); Sprite demonMan; RectangleShape option1(Vector2f(450,60)), option2(Vector2f(220,60));
    Sprite playDoor; Sprite settingsDoor; Sprite OpenPlayDoor; Sprite OpenSettingsDoor; Sprite GameIcon(gameIconTexture);
    Sprite menuBackground(menuBackgroundTexture); Sprite ardaonly(ardaonlyTexture); Sprite itch(itchTexture); Sprite yt(ytTexture);
    Sprite demonKid; Sprite character; Sprite ardaKoyuncu(madebyArdaKoyuncuTexture); Sprite cancel(CancelTexture);
    Sprite deathHeart; Sprite SnowMan(snowmanTexture); Sprite alphaSprite(AlphaTexture);

    Color gray(15, 15, 15);

    playDoor.setTexture(playDoorOpenTexture); character.setTexture(ScoutTexture); Sprite buy(buyButtonTexture);

    EyebornHand1.setTexture(EyebornHandTexture1); EyebornHand2.setTexture(EyebornHandTexture2);
    Background.setScale(5.5f,5.5f); door.setScale(5.5f,5.5f); jumpscareBackground.setScale(3.0f,3.0f);
    cookie.setScale(2.0f,2.0f); scoutJumpscare.setScale(10.0f,10.0f); scoutJumpscare.setPosition(Vector2f(75,-20));
    Eyeborn.setScale(8.0f,8.0f); EyebornHand1.setScale(3.0f,3.0f); EyebornHand2.setScale(-3.0f,3.0f); 
    buttonBackground.setPosition(Vector2f(350,200)); buttonBackground.setScale(6.0f,6.0f);
    button1.setPosition(Vector2f(380,400)); button1.setScale(2.5f,2.5f); button2.setPosition(Vector2f(770,400)); button2.setScale(2.5f,2.5f);
    money.setScale(2.0f,2.0f); money.setPosition(Vector2f(150,650)); shopBackground.scale(12.0f,12.0f); shopItem.setScale(8.0f,8.0f);
    shopItem.setPosition(Vector2f(250,90)); itemFrame.setPosition(230,100); itemFrame.setFillColor(gray); itemFrame.setOutlineThickness(6);
    playerHeart.setScale(2.0f,2.0f); playerHeart.setPosition(Vector2f(150,580)); button3.setScale(1.5f,1.5f); button3.setPosition(Vector2f(1250,500));
    button4.setScale(1.5f,1.5f); button4.setPosition(Vector2f(1250,650)); sussy.setScale(2.0f,2.0f);
    Outside2.setScale(5.5f,5.5f); demonMan.setTexture(demonManTexture); demonMan.setScale(4.5f,4.5f);
    option1.setPosition(Vector2f(300,550)); option2.setPosition(Vector2f(1000,550)); option1.setFillColor(Color::Transparent); option2.setFillColor(Color::Transparent); 
    playDoor.setTexture(playDoorTexture); settingsDoor.setTexture(settingsDoorTexture); playDoor.setScale(3.0f,3.0f); settingsDoor.setScale(3.0f,3.0f);
    playDoor.setPosition(Vector2f(800,300)); settingsDoor.setPosition(Vector2f(1100,300)); GameIcon.setPosition(Vector2f(0,100)); GameIcon.setScale(0.7f,0.7f);
    menuBackground.setScale(5.0f,5.0f); ardaonly.setScale(0.7f,0.7f); ardaonly.setPosition(Vector2f(500,400));
    itch.setScale(1.3f,1.3f); itch.setPosition(Vector2f(10,670)); yt.setScale(1.3f,1.3f); yt.setPosition(Vector2f(150,670));
    demonKid.setTexture(demonKidTexture); demonKid.setScale(4.5f,4.5f); cancel.setScale(1.0f,1.0f); cancel.setPosition(Vector2f(1400,10));
    buy.setPosition(Vector2f(500,630)); buy.setScale(1.5f,1.5f); deathHeart.setScale(4.0f,4.0f); deathHeart.setPosition(Vector2f(600,300));
    SnowMan.setScale(4.0f,4.0f); alphaSprite.setScale(1.0f,1.0f); alphaSprite.setPosition(Vector2f(100,400));

    setRandomPrices();

    // ! Slot


    Sprite slot1; Sprite slot2; Sprite slot3; Sprite slot4;
    slot2.setTexture(SlotTexture); slot3.setTexture(SlotTexture); slot4.setTexture(SlotTexture);
    // 150
    slot1.setScale(2.0f,2.0f); slot1.setPosition(Vector2f(30,90));
    slot2.setScale(2.0f,2.0f); slot2.setPosition(Vector2f(30,240));
    slot3.setScale(2.0f,2.0f); slot3.setPosition(Vector2f(30,390));
    slot4.setScale(2.0f,2.0f); slot4.setPosition(Vector2f(30,540));


    // ! Slot End

    Text info;

    info.setFont(font);
    info.setCharacterSize(50);
    info.setFillColor(Color::White);

    // ! Hitboxes

    RectangleShape TelevisionHitbox(Vector2f(300,200));
    RectangleShape DoorHitbox(Vector2f(400,700));
    TelevisionHitbox.setFillColor(Color::Transparent); DoorHitbox.setFillColor(Color::Transparent);

    // ! Hitboxes End

    ambient.setLoop(true);
    ambient.setVolume(60);
    ambient.play();

    RectangleShape rectangle(Vector2f(2000.f, 1000.f));
    rectangle.setFillColor(Color(0, 255, 0));

    HoursSurvived.setFont(font);
    HoursSurvived.setCharacterSize(40);

    Text beginnerText;
    beginnerText.setFont(font);
    beginnerText.setCharacterSize(70);

    Outside.setTexture(OutsideTexture); Outside.setScale(5.0f,5.0f);
    slot1.setTexture(SlotTexture);

    Sprite scout(ScoutTexture);
    scout.setScale(5.0f,5.0f);

    Text ErrorText;
    ErrorText.setFont(font);
    ErrorText.setPosition(Vector2f(900,680));
    ErrorText.setCharacterSize(50);

    Text eyebornText;
    eyebornText.setFont(font);
    eyebornText.setPosition(Vector2f(200,200));
    eyebornText.setCharacterSize(50);

    Text confirmText("Do you want to check \nthe Stuffs?",font,50);
    Text buttonText1("Yeah",font,65); Text buttonText2("Shut up",font,65);
    confirmText.setPosition(Vector2f(390,250)); buttonText1.setPosition(Vector2f(450,450)); buttonText2.setPosition(Vector2f(820,450));

    Text itemInfoText; Text heartText; Text itemText; Text moneyText; Text shopButtontext; Text shopButtontext2;
    Text price; Text demonMantalk; Text demonManTalkText;

    itemInfoText.setFont(font); itemInfoText.setCharacterSize(50); itemInfoText.setPosition(Vector2f(800,250));
    heartText.setFont(font); heartText.setCharacterSize(50); heartText.setPosition(Vector2f(260,610)); heartText.setFillColor(heartColor);
    itemText.setFont(font); itemText.setCharacterSize(100); itemText.setPosition(Vector2f(900,100));
    moneyText.setFont(font); moneyText.setCharacterSize(40); moneyText.setPosition(Vector2f(240,685)); moneyText.setFillColor(moneyColor);
    shopButtontext.setFont(font); shopButtontext.setCharacterSize(60); shopButtontext.setString("Next"); 
    shopButtontext.setPosition(Vector2f(1290,520)); shopButtontext2.setFont(font); shopButtontext2.setCharacterSize(40);
    shopButtontext2.setString("Previous"); shopButtontext2.setPosition(Vector2f(1260,680));
    price.setFont(font); price.setCharacterSize(50); price.setFillColor(moneyColor); price.setPosition(Vector2f(800,550));
    demonManTalkText.setFont(font); Text demonManOfferText("\t\t\t  Choose\n\n\nMystery Case\t\t\tMoney",font,70);
    demonManTalkText.setPosition(Vector2f(200,200)); demonManOfferText.setPosition(Vector2f(300,300));
    demonManTalkText.setCharacterSize(50);

    thread thing(beginner); thread thing2 (errorMessageShow); thread thing3(ai); thread hour(hours); hour.detach();

    while (Hades.isOpen()){
        if (gasIsStarted)
            demonKidGas(Hades);
        while (Hades.pollEvent(events)){
            if (events.type == Event::Closed){
                cout <<"Game is closed\n";
                close = true;
                Hades.close();
            }

            if (events.type == Event::MouseButtonPressed && events.mouseButton.button == Mouse::Left) {
            if (playerCanClick){
                if (playerCanOpenTheTelevision) {
                    if (TelevisionHitbox.getGlobalBounds().intersects(cursor.getGlobalBounds())) {
                        if (isHave(inventory, 5, "battery") == -1) {
                            if (!(slot1.getGlobalBounds().intersects(cursor.getGlobalBounds())) &&
                                !(slot2.getGlobalBounds().intersects(cursor.getGlobalBounds())) &&
                                !(slot3.getGlobalBounds().intersects(cursor.getGlobalBounds())) &&
                                !(slot4.getGlobalBounds().intersects(cursor.getGlobalBounds()))) {
                                
                                error.stop();
                                error.play();
                                errMessage = true;
                            }
                        }
                        else if (isHave(inventory, 5, "battery") == 1) {
                            thread battery(batteryGiven);
                            battery.detach();
                            inventory[whichSlotIsHave(inventory, 5, "battery")] = "";
                        }
                    }
                }
            }
        }
        if (events.type == Event::KeyPressed && events.key.code == Keyboard::F11) {
                    f11Pressed = true;
                    isFullscreen = !isFullscreen;
                    Hades.close();

                    if (isFullscreen) {
                        VideoMode desktop = VideoMode::getDesktopMode();
                        Hades.create(VideoMode(desktop.width, desktop.height), "Gates of Hades", Style::Fullscreen);
                        view.setSize(1466, 768);
                        view.setViewport(FloatRect(0, 0, 1, 1));
                    } else {
                        Hades.create(Windowed, "Gates of Hades", Style::Default);
                        view.setSize(1466, 768);
                        view.setViewport(FloatRect(0, 0, 1, 1));
                    }

                    Hades.setView(view);
            }if (events.type == Event::KeyPressed && events.key.code == Keyboard::Escape){
                isFullscreen = false;
                Hades.create(Windowed, "Gates of Hades", Style::Default);
                view.setSize(1466, 768);
                view.setViewport(FloatRect(0, 0, 1, 1));
            }
        }
        if (!Hades.hasFocus()) {
            continue;
        }

        if (events.type == Event::MouseButtonPressed && events.mouseButton.button == Mouse::Left) {
                Vector2f mousePos(events.mouseButton.x, events.mouseButton.y);

                if (yt.getGlobalBounds().contains(mousePos)) {
                    openURL(ytUrl);
                }

                if (itch.getGlobalBounds().contains(mousePos)) {
                    openURL(itchUrl);
                }
        }
        
        if (!heartAnimationStarted){
        if (game){

            if (stopped){
                HoursSurvived.setFillColor(Color::Red);
            }else{
                HoursSurvived.setFillColor(Color::White);
            }

            if (healing) {
            if (increasing) {
                alpha += 1.f;
                if (alpha >= 50.f) {
                    alpha = 50.f;
                    increasing = false;
                }
            } else {
                alpha -= 1.f;
                if (alpha <= 0.f) {
                    alpha = 0.f;
                    increasing = true;
                }
            }

            rectangle.setFillColor(sf::Color(0, 255, 0, static_cast<sf::Uint8>(alpha)));
        }

        if (health <= 0){
            if (!heartAnimationStarted){
                ambient.pause(); playerCanClick = false; playerCanOpenTheDoor = false; butPlayerCanUseTheslot = false;
                thread wait(heartWait); wait.detach();
                heartAnimationStarted = true;

            }
        }

        if (cancel.getGlobalBounds().intersects(cursor.getGlobalBounds()) && Mouse::isButtonPressed(Mouse::Left)){
            ClickingToCancel = true;
        }else{
            ClickingToCancel = false;
        }

        if (showlist[15]){
            if (option1.getGlobalBounds().intersects(cursor.getGlobalBounds())){
                if (Mouse::isButtonPressed(Mouse::Left)){
                    giveRandomItems();
                    showlist[15] = false;
                }
            }if (option2.getGlobalBounds().intersects(cursor.getGlobalBounds())){
                if (Mouse::isButtonPressed(Mouse::Left)){
                    theGivedMoneyToPlayer = rand() % 100 + 20;
                    playermoney += theGivedMoneyToPlayer;
                    showlist[15] = false;
                }
            }
        }

        Hades.setMouseCursorVisible(false);
        Time deltaTime = clock.restart();

        demonManTalkText.setString(demonManTalk);

        Background.setPosition(xy.x,xy.y);
        Dark.setPosition(xy.x,xy.y);
        door.setPosition(xy.x + 935,xy.y + 93 );
        demonManTalkText.setPosition(xy.x + 700,xy.y + 93 );
        Outside.setPosition(xy.x + 800,xy.y + -90 ); Outside2.setPosition(xy.x + 1450,xy.y + -200 );
        scout.setPosition(xy.x + scoutxy.x ,xy.y + scoutxy.y );
        Eyeborn.setPosition(xy.x + eyebornxy.x,xy.y + eyebornxy.y );
        demonMan.setPosition(xy.x + 800,xy.y + -200 );
        demonKid.setPosition(xy.x + 800,xy.y + 120 );
        SnowMan.setPosition(xy.x + 850,xy.y + -90 );
        EyebornHand1.setPosition(xy.x + EyebornHand1xy.x ,xy.y + EyebornHand1xy.y );
        EyebornHand2.setPosition(xy.x + EyebornHand2xy.x,xy.y + EyebornHand2xy.y );
        cursor.setPosition(Mouse::getPosition(Hades).x,Mouse::getPosition(Hades).y);
        TelevisionHitbox.setPosition(xy.x + 290 , xy.y + 300);
        character.setPosition(Vector2f(xy.x + 400 , xy.y + 200));
        DoorHitbox.setPosition(xy.x + 1000 , xy.y + 100);
        eyebornText.setPosition(xy.x + 900 , xy.y + 100);
        topSecretImage.setPosition(xy.x + -600, xy.y + 250);
        sussy.setPosition(xy.x + 1800, xy.y + 250);

        if (button3.getGlobalBounds().intersects(cursor.getGlobalBounds()) && !button4Clicked) {
            if (Mouse::isButtonPressed(Mouse::Left) && !button3Clicked) {
                shopPage++;
                button3Clicked = true;
            }
        } else {
            if (!Mouse::isButtonPressed(Mouse::Left)) {
                button3Clicked = false;
            }
        }

        if (button4.getGlobalBounds().intersects(cursor.getGlobalBounds()) && !button3Clicked) {
            if (Mouse::isButtonPressed(Mouse::Left) && !button4Clicked) {
                shopPage--;
                button4Clicked = true;
            }
        } else {
            if (!Mouse::isButtonPressed(Mouse::Left)) {
                button4Clicked = false;
            }
        }

        if (health >= 70){
            playerHeart.setTexture(heart1);
        }else if (health >= 50){
            playerHeart.setTexture(heart2);
        }else if (health >= 30){
            playerHeart.setTexture(heart3);
        }else if (health >= 20){
            playerHeart.setTexture(heart4);
        }

        if (shopPage == 1){ 
            shopItem.setTexture(cookieTexture); 
            itemText.setString("Cookie");
            itemInfoText.setString("You can use the cookie to \nrestore half of your health\n or give it to the scary \nscout to avoid losing half of \nyour health");
            price.setString("Price: " + to_string(prices[0]));
        }
        else if (shopPage == 2){ 
            shopItem.setTexture(batteryTexture); 
            itemText.setString("Battery"); 
            itemInfoText.setString("You can use the battery\n to use the TV you can \nsee who's coming to the\n door on the TV");
            price.setString("Price: " + to_string(prices[1]));
        }

        moneyText.setString( ": "+ to_string(playermoney)); heartText.setString( ": "+ to_string(health));

        ErrorText.setString(errorMessage); eyebornText.setString(EyebornMessage);
        ErrorText.setFillColor(Color::Red);

        if ((playerCanGiveTheCookie) && (butPlayerCanUseTheslot) && (whatPlayerIsDragging == "cookie")){
            if (!didPlayerGiveTheCookieToScout){
                if (cursor.getGlobalBounds().intersects(DoorHitbox.getGlobalBounds())){
                    if (Mouse::isButtonPressed(Mouse::Left)){
                        dragging = 0;
                        showlist[1] = false;
                        didPlayerGiveTheCookieToScout = true;
                    }
                }
            }
        }

        if (playerCanClick && !dragging){
            if (events.type == Event::MouseButtonPressed && events.mouseButton.button == Mouse::Left) {
        if (playerCanClick && !dragging) {
            for (int i = 1; i <= 4; ++i) {
                if (inventory[i] == "battery" && slot1.getGlobalBounds().intersects(cursor.getGlobalBounds())) {
                    inventory[i] = "";
                    batteryGiven();
                    break;
                }
            }
        }
        }
        }

        if ((!playerCanClick) && (butPlayerCanUseTheslot) && (playerCanGiveTheCookie)){
            if ((slot1.getGlobalBounds().intersects(cursor.getGlobalBounds())) || slot2.getGlobalBounds().intersects(cursor.getGlobalBounds()) || slot3.getGlobalBounds().intersects(cursor.getGlobalBounds()) || slot4.getGlobalBounds().intersects(cursor.getGlobalBounds())){
                if (!(dragging) && (!didPlayerGiveTheCookieToScout)){
                    if (inventory[1] == "cookie"){
                        if (slot1.getGlobalBounds().intersects(cursor.getGlobalBounds())){
                            if (Mouse::isButtonPressed(Mouse::Left)){
                                whatPlayerIsDragging = "cookie";
                                inventory[1] = "";
                                dragging = 1;
                                showlist[1] = true;
                            }
                        }
                    }if (inventory[2] == "cookie"){
                        if (slot2.getGlobalBounds().intersects(cursor.getGlobalBounds())){
                            if (Mouse::isButtonPressed(Mouse::Left)){
                                whatPlayerIsDragging = "cookie";
                                inventory[2] = "";
                                dragging = 1;
                                showlist[1] = true;
                            }
                        }
                    }if (inventory[3] == "cookie"){
                        if (slot3.getGlobalBounds().intersects(cursor.getGlobalBounds())){
                            if (Mouse::isButtonPressed(Mouse::Left)){
                                whatPlayerIsDragging = "cookie";
                                inventory[3] = "";
                                dragging = 1;
                                showlist[1] = true;
                            }
                        }
                    }if (inventory[4] == "cookie"){
                        if (slot4.getGlobalBounds().intersects(cursor.getGlobalBounds())){
                            if (Mouse::isButtonPressed(Mouse::Left)){
                                whatPlayerIsDragging = "cookie";
                                inventory[4] = "";
                                dragging = 1;
                                showlist[1] = true;
                            }
                        }
                    }
                }
            }
        }



        if (red){
            Dark.setTexture(redTexture); }else{ Dark.setTexture(DarkTexture); }

        int i = 0;
        for (i = 0 ; i <= 5 ; i++){
            if (inventory[i] == "cookie"){
                if (i == 1){ slot1.setTexture(SlotCookieTexture); }
                else if (i == 2){ slot2.setTexture(SlotCookieTexture); }
                else if (i == 3){ slot3.setTexture(SlotCookieTexture); }
                else if (i == 4){ slot4.setTexture(SlotCookieTexture); }
            }else if (inventory[i] == "battery") {
                if (i == 1){ slot1.setTexture(batterySlot); }
                else if (i == 2){ slot2.setTexture(batterySlot); }
                else if (i == 3){ slot3.setTexture(batterySlot); }
                else if (i == 4){ slot4.setTexture(batterySlot); }
            } else {
                if (i == 1){
                    slot1.setTexture(SlotTexture);
                }else if (i == 2){
                    slot2.setTexture(SlotTexture);
                }else if (i == 3){
                    slot3.setTexture(SlotTexture);
                }else if (i == 4){
                    slot4.setTexture(SlotTexture);
                }
            }
        }

        // This is a small pixel fix
        RectangleShape black(Vector2f(420,6));
        black.setFillColor(Color::Black);
        black.setPosition(xy.x + 965,xy.y + 762 );

        //info.setString(to_string(xy.x));
        if (showInfo){
            info.setString(object);
            info.setPosition(Mouse::getPosition(Hades).x + 40,Mouse::getPosition(Hades).y + -70);
        }else{
            info.setString("");
        }

        beginnerText.setString(text);
        if (green){
            beginnerText.setFillColor(Color::Green);
        }else{
            beginnerText.setFillColor(Color::White);
        }

        // Player can open the door?
        if (playerCanClick){
            if (playerCanOpenTheDoor){
                if (DoorHitbox.getGlobalBounds().intersects(cursor.getGlobalBounds())) {
                    if (Mouse::isButtonPressed(Mouse::Left)) {
                        if (!mouseClicked) {
                            if (!doorisOpen){
                                DoorOpen.stop();
                                DoorOpen.play();
                            }else{
                                DoorClose.stop();
                                DoorClose.play();
                            }
                            doorisOpen = !doorisOpen;
                            mouseClicked = true;
                        }
                    } else {
                        mouseClicked = false;
                    }
                }
            }
        }
        

        if (whoIsIntheDoor == "eyeborn"){
            if (button1.getGlobalBounds().intersects(cursor.getGlobalBounds())){
                whichButtonIsTouchingCursor = 1;
            }else if (button2.getGlobalBounds().intersects(cursor.getGlobalBounds())){
                whichButtonIsTouchingCursor = 2;
            }else{
                whichButtonIsTouchingCursor = 0;
            }
        }


        if (TelevisionHitbox.getGlobalBounds().intersects(cursor.getGlobalBounds())){
            object = "Television";
            touching = true;
        }else if (DoorHitbox.getGlobalBounds().intersects(cursor.getGlobalBounds())){
            object = "Door";
            touching = true;
        }else{
            object = "";
            touching = false;
        }

        if (playerCanClick || butPlayerCanUseTheslot){
            if (touching){
                CursorStyle = 2;
            }if (!touching && !dragging){
                CursorStyle = 1;
            }if (dragging){
                CursorStyle = 3;
            }
        }else{
            CursorStyle = 1;
        }

        if (CursorStyle == 1){
            cursor.setTexture(cursorTexture);
        }if (CursorStyle == 2){
            cursor.setTexture(handTexture);
        }if (CursorStyle == 3){
            cursor.setTexture(grapTexture);
        }

        if (doorisOpen){
            door.setTexture(doorOpenTexture);
        }else{
            door.setTexture(doorTexture);
        }
        if (Keyboard::isKeyPressed(Keyboard::A)){
            if (xy.x <= -5){
                xy.x += (500.0f * deltaTime.asSeconds());
            }
        }if (Keyboard::isKeyPressed(Keyboard::D)){
            if (xy.x > -285){
                xy.x += (-500.0f * deltaTime.asSeconds());
            }
        }

        Hades.clear(Color::Black);
        Hades.draw(Outside); Hades.draw(Outside2);
        if (showlist[0]){
            if (scoutisHorror){
                scout.setTexture(ScaryScout);
                Hades.draw(scout);
            }else{
                scout.setTexture(ScoutTexture);
                Hades.draw(scout);
            }
        }if (showlist[4]){
            Hades.draw(Eyeborn);
        }
        Hades.draw(Background);
        Hades.draw(door);
        if (showlist[18]){
            if (doorisOpen)
            Hades.draw(SnowMan);
        }
        if (showlist[16]){
            if (doorisOpen)
            Hades.draw(demonKid);
        }
        if (showlist[5]){
            if (doorisOpen)
            Hades.draw(EyebornHand1);
        }if (showlist[6]){
            if (doorisOpen)
            Hades.draw(EyebornHand2);
        }if (showlist[7]){
            if (doorisOpen)
            Hades.draw(eyebornText);
        }
        if (showlist[14]){
            if (doorisOpen)
            Hades.draw(demonMan);
        }
        Hades.draw(black);
        Hades.draw(TelevisionHitbox);
        Hades.draw(DoorHitbox);
        Hades.draw(Dark);

        if (showlist[12]){
            Hades.draw(shopBackground);
        }if (showlist[17]){
            Hades.draw(character);
        }
        Hades.draw(slot1); Hades.draw(slot2);
        Hades.draw(slot3); Hades.draw(slot4);

        if (showlist[1]){
            cookie.setPosition(Mouse::getPosition(Hades).x + -35, (Mouse::getPosition(Hades).y) + -45);
            Hades.draw(cookie);
        }

        Hades.draw(info); Hades.draw(ErrorText); 
        Hades.draw(beginnerText);
        if (showlist[2]){
            Hades.draw(jumpscareBackground);
            jumpscareBackground.setPosition(Vector2f(rand() % 100 + -100, rand() % 100 + -100));
        }
        if (showlist[3]){
            scoutJumpscare.setPosition(Vector2f(rand() % 100 + -100, rand() % 100 + -100));
            Hades.draw(scoutJumpscare);
        }if (showlist[10]){
            Hades.draw(buttonBackground);
        }if (showlist[8]){
            Hades.draw(button1);
        }if (showlist[9]){
            Hades.draw(button2);
        }if (showlist[11]){
            Hades.draw(confirmText); Hades.draw(buttonText1); Hades.draw(buttonText2);
        }if (showlist[13]){
            playerCanClick = false; showInfo = false; playerIsIntheShop = true;
            Hades.draw(itemFrame); Hades.draw(shopItem);
            Hades.draw(itemText); Hades.draw(itemInfoText);
            Hades.draw(button3); Hades.draw(button4);
            Hades.draw(shopButtontext); Hades.draw(shopButtontext2);
            Hades.draw(price); Hades.draw(cancel); Hades.draw(buy);

            if ((buy.getGlobalBounds().intersects(cursor.getGlobalBounds())) && (Mouse::isButtonPressed(Mouse::Left)) && mouseReleased) {
                mouseReleased = false;

                if ((shopPage == 1) && (prices[0] <= playermoney)) {
                    playermoney -= prices[0];
                    inventory[getFirstEmptySlot(inventory, 5)] = "cookie";
                    take.stop(); take.play();
                }else if (!(prices[0] >= playermoney)){
                    //error.stop(); error.play();
                }
                if ((shopPage == 2) && (prices[1] <= playermoney)) {
                    playermoney -= prices[1];
                    inventory[getFirstEmptySlot(inventory, 5)] = "battery";
                    take.stop(); take.play();
                }else if ((prices[1] >= playermoney)){
                    //error.stop(); error.play();
                }
            }

            if (!Mouse::isButtonPressed(Mouse::Left)) {
                mouseReleased = true;
            }
        }
        if (showlist[14]){
            if (doorisOpen)
            Hades.draw(demonManTalkText);
        }if (showlist[15]){
            if (doorisOpen)
            Hades.draw(demonManOfferText); Hades.draw(option1); Hades.draw(option2);
        }
        Hades.draw(money); Hades.draw(moneyText);
        Hades.draw(playerHeart); Hades.draw(heartText);
        Hades.draw(topSecretImage); Hades.draw(sussy);
        if (healing)
        Hades.draw(rectangle);
        Hades.draw(HoursSurvived);
        HoursSurvived.setString("Hours Survived: " + to_string(hoursSurvived));
        Hades.draw(cursor);
        Hades.display();

    }else{
        heartAnimationStarted = false;
        cursor.setPosition(Mouse::getPosition(Hades).x,Mouse::getPosition(Hades).y);
        Hades.setMouseCursorVisible(false);
        Time deltaTime = clock.restart();
        if (CursorStyle == 1){
            cursor.setTexture(cursorTexture);
        }if (CursorStyle == 2){
            cursor.setTexture(handTexture);
        }if (CursorStyle == 3){
            cursor.setTexture(grapTexture);
        }
        if (!cantClickOnTheMenu){
            if (playDoor.getGlobalBounds().intersects(cursor.getGlobalBounds())){
                CursorStyle = 2;
                if (Mouse::isButtonPressed(Mouse::Left)){
                    DoorOpen.stop(); DoorOpen.play();
                    playDoor.setTexture(playDoorOpenTexture);
                    cantClickOnTheMenu = true;
                    thread thing4(startGame);
                    thing4.detach();
                }
            }
        }
        if (!playDoor.getGlobalBounds().intersects(cursor.getGlobalBounds())){
            CursorStyle = 1;
        }

        if (Hades.pollEvent(events)){
            if (events.type == Event::Closed){
                Hades.close();
            }
        }

        Hades.clear(Color::Black);
        Hades.draw(menuBackground);
        /*Hades.draw(settingsDoor);*/ Hades.draw(playDoor); Hades.draw(ardaonly); Hades.draw(GameIcon);
        ardaKoyuncu.setScale(0.3f,0.3f); Hades.draw(ardaKoyuncu); Hades.draw(alphaSprite);
        Hades.draw(itch); Hades.draw(yt);
        Hades.draw(cursor);
        Hades.display();
    }


    }else{
        if (asset == 1){ deathHeart.setTexture(heart1); }
        if (asset == 2){ deathHeart.setTexture(heart2); }
        if (asset == 3){ deathHeart.setTexture(heart3); }
        if (asset == 4){ deathHeart.setTexture(heart4); }

        if (asset == 6){
            if (randomThing == 1)
            deathHeart.setTexture(cookieTexture);
            if (randomThing == 2)
            deathHeart.setTexture(batteryTexture);
            if (randomThing == 3)
            deathHeart.setTexture(doorTexture);
            if (randomThing == 4)
            deathHeart.setTexture(demonKidTexture);
            if (randomThing == 5)
            deathHeart.setTexture(moneyTexture);
            if (randomThing == 6)
            deathHeart.setTexture(caseBag);
        }

        if (asset == 7){
            string command;
            #ifdef _WIN32
                            command = "start " + exeFile + ".exe";
            #elif __linux__
                            command = "./" + exeFile;           
            #elif __APPLE__
                            command = "./" + exeFile;             
            #else
                    Hades.close();
            #endif

            system(command.c_str());
            Hades.close();
        }

        Hades.clear(Color::Black);
        if ((asset == 1) || (asset == 2) || (asset == 3) || (asset == 4) || (asset == 6))
            Hades.draw(deathHeart);
        Hades.display();
    }
    }
    close=1;
    thing.join(); thing2.join(); thing3.join();
    Hades.close();
    return 0;
}

