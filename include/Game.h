#pragma once
#include <M5Unified.h>
#include "Sprites.h"
#include "RealSprites.h"

enum class Screen : uint8_t { WORLD, SHOP, LAB, GARDEN, DEFENSE, BATTLE, JOURNAL };

struct Visitor {
  const char* name;
  const char* role;
  const char* greeting;
  const char* request;
  uint16_t reward;
  uint8_t  reqType;   // 0=herbs,1=potion,2=mushrooms,3=wood,4=any,5=special
  uint8_t  reqAmt;
  uint8_t  minRep;    // reputation gate
  uint8_t  icon;      // visual id for tiny procedural sprite
};

class Game {
public:
  uint16_t day = 1, herbs = 4, wood = 5, mushrooms = 3, potions = 0, seeds = 3, reputation = 0;
  uint32_t gold = 22;
  uint8_t  wallLevel = 0, turretLevel = 0;
  uint8_t  gardenStage = 0;   // 0 empty → 3 ready
  uint8_t  knownVisitors = 0; // bitfield of met visitors (first 8)

  void begin();
  void update();
  void draw(M5GFX &display);
  bool consumeSaveRequest();

private:
  Screen screen = Screen::WORLD;
  bool   saveRequested = false, dialogue = false, night = false;
  uint8_t visitorIndex = 0, wave = 1, monsterHp = 0, wizardHp = 6;
  uint16_t dayTick = 0;
  const char* message = "The kettle is warm. Someone may visit today.";
  const char* messageTitle = "A quiet morning";

  // Expanded roster – early normal, mid weird, late eerie
  static const uint8_t VISITOR_COUNT = 14;
  Visitor visitors[VISITOR_COUNT] = {
    // Early (rep 0+)
    {"Mara Moss",       "Herbalist",        "Smells like rain today. Lovely.",           "Bring me 2 moon herbs.",           14, 0, 2, 0, 0},
    {"Nell Thistle",    "Village baker",    "I have a pie cooling in my basket.",        "Could you spare a moon herb?",     11, 0, 1, 0, 1},
    {"Pipwick",         "Traveling peddler","I trade in things that squeak or glow.",    "A potion for the road, please.",   22, 1, 1, 0, 2},
    {"Bramble",         "Mushroom gatherer","The little ones are singing again.",        "I'll pay well for 3 mushrooms.",   16, 2, 3, 0, 3},
    // Mid (rep 4+)
    {"Orrin Gearleaf",  "Tinkerer",         "I can stop that cauldron rattling.",        "I need a bit of good wood.",       19, 3, 2, 3, 4},
    {"Sir Rowan",       "Retired adventurer","Your tower has a growing reputation.",     "A proper healing draught.",        20, 1, 1, 4, 5},
    {"Madame Moth",     "Wandering witch",  "Darling, your aura looks slightly flammable.","Show me your finest tonic.",     28, 1, 1, 5, 6},
    {"The Quiet Guest", "Unknown",          "May I stand by the fire a moment?",         "Something small and strange.",     12, 4, 0, 6, 7},
    // Late / Strange (rep 8+)
    {"Spore",           "Fungus herbalist", "I grow where the light is softest.",        "Three mushrooms and a kind word.", 26, 2, 3, 8, 8},
    {"Bonewhisper",     "Skeleton mage",    "The bones remember your wards.",            "A potion strong enough for the dead.", 32, 1, 1, 10, 9},
    {"Mossback",        "Young treant",     "The roots are restless tonight.",           "Wood and a moon herb, please.",    24, 3, 1, 9, 10},
    {"Lady Pale",       "Ghostly noble",    "I still remember the taste of tea.",        "Anything that glows a little.",    18, 4, 0, 11, 11},
    // Very late (rep 14+)
    {"Voidling",        "Eldritch client",  "The stars inside my coat are hungry.",      "Your rarest creation.",            45, 1, 1, 14, 12},
    {"The Last Regular","Familiar stranger","You know me by now.",                       "Whatever you think I need.",       30, 4, 0, 12, 13}
  };

  void handleTap(int x, int y);
  void advanceDay();
  void startNight();
  void resolveBattle();
  void pickVisitor();
  void drawHeader(M5GFX &d);
  void drawTabs(M5GFX &d);
  void drawWorld(M5GFX &d);
  void drawShop(M5GFX &d);
  void drawLab(M5GFX &d);
  void drawGarden(M5GFX &d);
  void drawDefense(M5GFX &d);
  void drawBattle(M5GFX &d);
  void drawJournal(M5GFX &d);
  void drawButton(M5GFX &d, int x, int y, int w, int h, const char* label, uint16_t fill);
  void drawPanel(M5GFX &d, int x, int y, int w, int h, uint16_t fill);
  void drawTinyVisitor(M5GFX &d, int cx, int cy, uint8_t icon); // procedural 12-16px face/body
  void drawTinyMonster(M5GFX &d, int x, int y, uint8_t type);
};
