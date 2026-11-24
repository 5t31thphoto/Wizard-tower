#pragma once
#include <M5Unified.h>

enum class Screen : uint8_t { WORLD, SHOP, LAB, GARDEN, DEFENSE, BATTLE, JOURNAL };
struct Visitor {
  const char* name;
  const char* role;
  const char* greeting;
  const char* request;
  uint16_t reward;
  uint8_t icon;
};

class Game {
public:
  uint16_t day=1, herbs=3, wood=4, mushrooms=2, potions=0, seeds=2, reputation=0;
  uint32_t gold=18;
  uint8_t wallLevel=0, turretLevel=0;
  void begin();
  void update();
  void draw(M5GFX &display);
  bool consumeSaveRequest();
private:
  Screen screen=Screen::WORLD;
  bool saveRequested=false, dialogue=false, night=false, battleWon=false;
  uint8_t visitorIndex=0, selectedAction=0, wave=1, monsterHp=0, wizardHp=5;
  uint16_t dayTick=0;
  int lastTouchX=-1,lastTouchY=-1;
  const char* message="The kettle is warm. Someone may visit today.";
  const char* messageTitle="A quiet morning";
  Visitor visitors[8] = {
    {"Mara Moss","Herbalist","Smells like rain today. Lovely.","Bring me 2 moon herbs.",12,0},
    {"Pipwick","Traveling peddler","I trade in things that squeak, glow, or bite.","A potion for my journey, please.",20,1},
    {"Sir Rowan","Retired adventurer","I heard your tower has become quite reputable.","I need a healing draught.",16,2},
    {"Madame Moth","Wandering witch","Darling, your aura is looking slightly flammable.","Show me your finest potion.",24,3},
    {"Bramble","Mushroom gatherer","The little ones are singing again.","I'll pay for 3 mushrooms.",14,4},
    {"The Quiet Guest","Unknown","May I stand by the fire for a moment?","A curious little request.",8,5},
    {"Nell Thistle","Village baker","I have a pie cooling in my basket.","Could you spare a moon herb?",10,6},
    {"Orrin Gearleaf","Tinkerer","I can make that cauldron stop rattling.","I need a little wood.",18,7}
  };
  void handleTap(int x,int y);
  void advanceDay();
  void startNight();
  void resolveBattle();
  void drawHeader(M5GFX &d);
  void drawTabs(M5GFX &d);
  void drawWorld(M5GFX &d);
  void drawShop(M5GFX &d);
  void drawLab(M5GFX &d);
  void drawGarden(M5GFX &d);
  void drawDefense(M5GFX &d);
  void drawBattle(M5GFX &d);
  void drawJournal(M5GFX &d);
  void drawButton(M5GFX &d,int x,int y,int w,int h,const char* label,uint16_t fill);
  void drawPanel(M5GFX &d,int x,int y,int w,int h,uint16_t fill);
};
