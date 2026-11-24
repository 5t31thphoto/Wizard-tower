#include <M5Unified.h>
#include <Preferences.h>
#include "Game.h"

Game game;
Preferences prefs;

void loadGame() {
  prefs.begin("wizardskeep", true);
  game.day = prefs.getUShort("day", 1);
  game.gold = prefs.getUInt("gold", 22);
  game.herbs = prefs.getUShort("herbs", 4);
  game.wood = prefs.getUShort("wood", 5);
  game.mushrooms = prefs.getUShort("mush", 3);
  game.potions = prefs.getUShort("pots", 0);
  game.seeds = prefs.getUShort("seeds", 3);
  game.wallLevel = prefs.getUChar("wall", 0);
  game.turretLevel = prefs.getUChar("turret", 0);
  game.reputation = prefs.getUShort("rep", 0);
  game.gardenStage = prefs.getUChar("garden", 0);
  prefs.end();
}
void saveGame() {
  prefs.begin("wizardskeep", false);
  prefs.putUShort("day", game.day);
  prefs.putUInt("gold", game.gold);
  prefs.putUShort("herbs", game.herbs);
  prefs.putUShort("wood", game.wood);
  prefs.putUShort("mush", game.mushrooms);
  prefs.putUShort("pots", game.potions);
  prefs.putUShort("seeds", game.seeds);
  prefs.putUChar("wall", game.wallLevel);
  prefs.putUChar("turret", game.turretLevel);
  prefs.putUShort("rep", game.reputation);
  prefs.putUChar("garden", game.gardenStage);
  prefs.end();
}
void setup() {
  auto cfg = M5.config();
  cfg.clear_display = true;
  M5.begin(cfg);
  M5.Display.setRotation(0);
  M5.Display.setBrightness(180);
  M5.Display.setTextSize(1);
  loadGame();
  game.begin();
}
void loop() {
  M5.update();
  game.update();
  game.draw(M5.Display);
  if (game.consumeSaveRequest()) saveGame();
  delay(25);
}
