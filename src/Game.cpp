#include "Game.h"

// Palette (RGB565) - prefixed to avoid M5GFX name collisions
static const uint16_t COL_INK       = 0x18E3;
static const uint16_t COL_PANEL     = 0x2945;
static const uint16_t COL_PANEL2    = 0x39A7;
static const uint16_t COL_CREAM     = 0xFFDB;
static const uint16_t COL_TEAL      = 0x04F2;
static const uint16_t COL_PLUM      = 0x6810;
static const uint16_t COL_LIME      = 0x87E0;
static const uint16_t COL_GOLD      = 0xFEA0;
static const uint16_t COL_PINK      = 0xF3B8;
static const uint16_t COL_GRASS     = 0x3D66;
static const uint16_t COL_DARKGRASS = 0x2AE4;
static const uint16_t COL_BROWN     = 0x8A03;
static const uint16_t COL_STONE     = 0x8C71;
static const uint16_t COL_NIGHT     = 0x1084;
static const uint16_t COL_SKIN      = 0xF9CB;
static const uint16_t COL_MOSS      = 0x4C8A;
static const uint16_t COL_BONE      = 0xDEFB;
static const uint16_t COL_VOID      = 0x4810;

static const char* screenName(Screen s) {
  switch(s){
    case Screen::WORLD:   return "CLEARING";
    case Screen::SHOP:    return "SHOP";
    case Screen::LAB:     return "LAB";
    case Screen::GARDEN:  return "GARDEN";
    case Screen::DEFENSE: return "KEEP";
    case Screen::BATTLE:  return "NIGHT WATCH";
    default:              return "JOURNAL";
  }
}

void Game::begin() {
  messageTitle = "A quiet morning";
  message = "The kettle is warm. Someone may visit today.";
  pickVisitor();
}

bool Game::consumeSaveRequest() {
  bool v = saveRequested;
  saveRequested = false;
  return v;
}

void Game::drawPanel(M5GFX& d, int x, int y, int w, int h, uint16_t fill) {
  d.fillRoundRect(x, y, w, h, 5, fill);
  d.drawRoundRect(x, y, w, h, 5, 0x7B6D);
}

void Game::drawButton(M5GFX& d, int x, int y, int w, int h, const char* label, uint16_t fill) {
  d.fillRoundRect(x, y, w, h, 4, fill);
  d.drawRoundRect(x, y, w, h, 4, COL_CREAM);
  d.setTextColor(COL_CREAM, fill);
  d.drawString(label, x + 5, y + (h - 8) / 2, 1);
}

// Tiny procedural visitor (roughly 14-18 px tall)
void Game::drawTinyVisitor(M5GFX& d, int cx, int cy, uint8_t icon) {
  // Real extracted sprites from the user's art sheets
  static const uint16_t* const table[] = {
    RealSprites::mara,          // 0 Mara
    RealSprites::nell,          // 1 Nell
    RealSprites::wizardtype,    // 2 Pipwick
    RealSprites::spore,         // 3 Bramble
    RealSprites::wizardtype,    // 4 Orrin
    RealSprites::whitebeard,    // 5 Rowan
    RealSprites::madamemoth,    // 6 Madame Moth
    RealSprites::quietguest,    // 7 Quiet Guest
    RealSprites::spore,         // 8 Spore
    RealSprites::bonewhisper,   // 9 Bonewhisper
    RealSprites::mossback,      // 10 Mossback
    RealSprites::ladypale,      // 11 Lady Pale
    RealSprites::plague,        // 12 Voidling
    RealSprites::wizardtype     // 13 fallback
  };
  if (icon >= 14) icon = 13;
  RealSprites::blit(d, cx - 16, cy - 20, table[icon]);
}

void Game::drawTinyMonster(M5GFX& d, int x, int y, uint8_t type) {
  RealSprites::blit(d, x - 16, y - 20, RealSprites::slime);
}



void Game::drawHeader(M5GFX& d) {
  d.fillRect(0, 0, 320, 24, COL_INK);
  d.setTextColor(COL_CREAM, COL_INK);
  char buf[48];
  snprintf(buf, sizeof(buf), "WIZARD'S KEEP  /  DAY %u", day);
  d.drawString(buf, 5, 5, 1);
  snprintf(buf, sizeof(buf), "%luG  H:%u W:%u M:%u P:%u", (unsigned long)gold, herbs, wood, mushrooms, potions);
  d.setTextColor(COL_GOLD, COL_INK);
  d.drawString(buf, 175, 5, 1);
}

void Game::drawTabs(M5GFX& d) {
  const char* names[] = {"WOODS", "SHOP", "LAB", "GARDEN", "KEEP", "BOOK"};
  Screen ids[] = {Screen::WORLD, Screen::SHOP, Screen::LAB, Screen::GARDEN, Screen::DEFENSE, Screen::JOURNAL};
  for (int i = 0; i < 6; i++) {
    uint16_t c = (screen == ids[i]) ? COL_PLUM : COL_PANEL;
    drawButton(d, i * 53 + 2, 211, 50, 26, names[i], c);
  }
}

void Game::drawWorld(M5GFX& d) {
  d.fillScreen(COL_GRASS);
  // soft tile variation
  for (int y = 27; y < 204; y += 16)
    for (int x = 0; x < 320; x += 16) {
      uint16_t c = ((x / 16 + y / 16) % 3 == 0) ? COL_DARKGRASS : COL_GRASS;
      d.fillRect(x, y, 16, 16, c);
      if (((x * 7 + y * 3) % 13) == 0) d.drawPixel(x + 7, y + 8, COL_PINK);
    }

  // forest edge – denser
  for (int x = 0; x < 320; x += 28) {
    d.fillCircle(x + 10, 44, 13, 0x1D84);
    d.fillCircle(x + 20, 40, 10, 0x2D05);
    d.fillRect(x + 12, 44, 6, 14, COL_BROWN);
  }

  // tower – a bit more character
  d.fillRect(22, 72, 76, 95, COL_STONE);
  d.fillRect(16, 64, 88, 14, COL_PLUM);
  d.fillTriangle(16, 64, 60, 28, 104, 64, COL_PLUM);
  d.fillRect(46, 110, 24, 57, COL_BROWN);          // door
  d.fillRect(33, 88, 14, 18, COL_GOLD);            // window
  d.fillRect(71, 88, 14, 18, COL_GOLD);
  d.fillRect(48, 128, 20, 36, COL_INK);
  d.drawRect(48, 128, 20, 36, COL_CREAM);
  // little flag
  d.fillTriangle(60, 28, 78, 22, 60, 34, COL_TEAL);

  // garden plots with stage
  for (int i = 0; i < 3; i++) {
    int x = 130 + i * 42;
    d.fillRoundRect(x, 118, 34, 36, 3, COL_BROWN);
    if (gardenStage >= 1) {
      for (int j = 0; j < 3; j++) {
        d.drawFastVLine(x + 7 + j * 9, 126, 14 + gardenStage * 2, COL_LIME);
        if (gardenStage >= 2) d.fillCircle(x + 7 + j * 9, 126, 2 + gardenStage, (gardenStage >= 3) ? COL_PINK : 0xAFC0);
      }
    }
  }

  // path
  for (int x = 92; x < 128; x += 11) d.fillRect(x, 152, 9, 9, 0xC5B0);

  // player wizard – slightly better
  d.fillCircle(110, 176, 7, COL_SKIN);
  d.fillTriangle(102, 170, 110, 154, 118, 170, COL_PLUM);
  d.fillRect(104, 176, 13, 16, COL_PLUM);
  d.drawFastVLine(122, 166, 26, COL_BROWN);
  d.fillCircle(122, 163, 3, COL_TEAL);

  drawPanel(d, 5, 28, 118, 34, COL_PANEL);
  d.setTextColor(COL_CREAM, COL_PANEL);
  d.drawString("Your little corner", 12, 34, 1);
  d.setTextColor(0xBDF7, COL_PANEL);
  d.drawString("of the peculiar woods.", 12, 46, 1);

  drawPanel(d, 172, 28, 142, 48, COL_PANEL);
  d.setTextColor(COL_CREAM, COL_PANEL);
  d.drawString("TODAY", 180, 34, 1);
  d.setTextColor(COL_GOLD, COL_PANEL);
  char task[40];
  if (reputation < 4)       strcpy(task, "Gather & meet locals");
  else if (reputation < 9)  strcpy(task, "Stranger visitors...");
  else                      strcpy(task, "The woods watch you");
  d.drawString(task, 180, 48, 1);

  drawButton(d, 180, 86, 130, 28, "BEGIN NIGHT", 0x3810);
  drawButton(d, 180, 158, 130, 36, "OPEN THE SHOP", COL_PLUM);
}

void Game::drawShop(M5GFX& d) {
  d.fillScreen(0x31A8);
  for (int y = 27; y < 207; y += 16)
    for (int x = 0; x < 320; x += 16)
      d.drawRect(x, y, 16, 16, 0x5A08);

  d.fillRect(0, 27, 320, 22, 0x5A08);
  d.fillRect(10, 55, 300, 7, COL_BROWN);

  // shelves with more bottles
  for (int i = 0; i < 7; i++) {
    int x = 18 + i * 42;
    d.fillRect(x, 66, 34, 38, COL_BROWN);
    d.fillRect(x + 4, 76, 9, 16, COL_TEAL);
    d.fillRect(x + 20, 73, 9, 19, COL_PINK);
    d.fillRect(x + 4, 73, 9, 3, COL_GOLD);
    d.fillRect(x + 20, 70, 9, 3, COL_GOLD);
    if (i % 2) d.fillCircle(x + 12, 92, 3, COL_LIME);
  }

  // counter
  d.fillRect(60, 142, 200, 24, COL_BROWN);
  d.fillRect(68, 134, 184, 9, 0xD6B2);

  // the visitor – now with personality
  drawTinyVisitor(d, 160, 112, visitors[visitorIndex].icon);

  drawPanel(d, 6, 30, 150, 38, COL_PANEL);
  d.setTextColor(COL_CREAM, COL_PANEL);
  d.drawString("A visitor has arrived", 12, 36, 1);
  d.setTextColor(COL_GOLD, COL_PANEL);
  d.drawString(visitors[visitorIndex].name, 12, 50, 1);

  drawPanel(d, 6, 170, 308, 36, COL_PANEL);
  d.setTextColor(COL_CREAM, COL_PANEL);
  d.drawString(visitors[visitorIndex].greeting, 12, 176, 1);
  d.setTextColor(0xBDF7, COL_PANEL);
  d.drawString(visitors[visitorIndex].request, 12, 190, 1);

  drawButton(d, 168, 108, 140, 30, "TRADE / HELP", COL_PLUM);
}

void Game::drawLab(M5GFX& d) {
  d.fillScreen(0x18E3);
  for (int y = 27; y < 210; y += 16)
    for (int x = 0; x < 320; x += 16)
      d.drawRect(x, y, 16, 16, 0x39A7);

  // shelf of reagents
  d.fillRect(16, 48, 288, 8, COL_BROWN);
  for (int i = 0; i < 7; i++) {
    int x = 24 + i * 40;
    d.fillRect(x, 26, 14, 24, 0x7E9F);
    d.fillRect(x + 3, 22, 8, 5, COL_GOLD);
    if (i % 3 == 0) d.fillCircle(x + 7, 38, 3, COL_PINK);
  }

  // bench + cauldron
  d.fillRect(55, 120, 210, 20, COL_BROWN);
  d.fillRect(70, 140, 14, 55, COL_BROWN);
  d.fillRect(236, 140, 14, 55, COL_BROWN);
  d.fillRoundRect(125, 78, 70, 55, 14, 0x6B4D);
  d.fillRect(135, 68, 50, 16, 0x9D13);
  d.fillCircle(160, 105, 16, COL_TEAL);
  d.fillCircle(160, 105, 8, COL_LIME);
  // bubbles
  d.fillCircle(152, 96, 2, COL_CREAM);
  d.fillCircle(168, 98, 3, COL_CREAM);

  drawPanel(d, 6, 30, 150, 38, COL_PANEL);
  d.setTextColor(COL_CREAM, COL_PANEL);
  d.drawString("ALCHEMY BENCH", 12, 36, 1);
  d.setTextColor(COL_GOLD, COL_PANEL);
  d.drawString("Moonroot & more", 12, 50, 1);

  drawButton(d, 10, 162, 145, 34, "BREW POTION", COL_PLUM);
  drawButton(d, 165, 162, 145, 34, "RESEARCH", COL_TEAL);

  d.setTextColor(COL_CREAM, 0x18E3);
  char b[48];
  snprintf(b, sizeof(b), "Potions:%u  Herbs:%u  Mush:%u", potions, herbs, mushrooms);
  d.drawString(b, 12, 202, 1);
}

void Game::drawGarden(M5GFX& d) {
  d.fillScreen(0x2AE4);
  // plots
  for (int row = 0; row < 2; row++)
    for (int col = 0; col < 4; col++) {
      int x = 18 + col * 74;
      int y = 42 + row * 58;
      d.fillRoundRect(x, y, 64, 48, 4, COL_BROWN);
      if (gardenStage > 0) {
        for (int i = 0; i < 4; i++) {
          d.drawFastVLine(x + 10 + i * 12, y + 12, 10 + gardenStage * 3, COL_LIME);
          if (gardenStage >= 2)
            d.fillCircle(x + 10 + i * 12, y + 12, 2 + gardenStage, (gardenStage >= 3) ? COL_PINK : COL_GOLD);
        }
      }
    }

  drawPanel(d, 6, 28, 180, 36, COL_PANEL);
  d.setTextColor(COL_CREAM, COL_PANEL);
  d.drawString("MOONPATCH GARDEN", 12, 34, 1);
  d.setTextColor(COL_GOLD, COL_PANEL);
  const char* stageTxt[] = {"Soil rests", "Sprouts rising", "Buds forming", "Ready to harvest!"};
  d.drawString(stageTxt[gardenStage > 3 ? 3 : gardenStage], 12, 48, 1);

  drawButton(d, 10, 162, 145, 34, "PLANT SEED", COL_PLUM);
  drawButton(d, 165, 162, 145, 34, "HARVEST", COL_TEAL);
}

void Game::drawDefense(M5GFX& d) {
  d.fillScreen(COL_NIGHT);
  for (int y = 32; y < 205; y += 16)
    for (int x = 0; x < 320; x += 16)
      d.fillRect(x, y, 16, 16, ((x + y) / 16) % 2 ? 0x10A4 : 0x18C6);

  // keep
  d.fillRect(120, 78, 80, 100, COL_STONE);
  d.fillTriangle(110, 78, 160, 38, 210, 78, COL_PLUM);
  d.fillRect(145, 130, 30, 48, COL_INK);
  d.drawRect(145, 130, 30, 48, COL_CREAM);

  // walls
  for (int i = 0; i < wallLevel && i < 6; i++)
    d.fillRect(18 + i * 16, 170, 14, 14, COL_STONE);

  // turrets
  for (int i = 0; i < turretLevel && i < 4; i++) {
    int x = 230 + i * 22;
    d.fillRect(x, 145, 12, 28, COL_BROWN);
    d.fillCircle(x + 6, 142, 8, COL_TEAL);
    d.fillCircle(x + 6, 142, 3, COL_LIME);
  }

  drawPanel(d, 6, 28, 180, 42, COL_PANEL);
  d.setTextColor(COL_CREAM, COL_PANEL);
  d.drawString("KEEP IMPROVEMENTS", 12, 34, 1);
  d.setTextColor(COL_GOLD, COL_PANEL);
  d.drawString("Walls slow them. Turrets hurt them.", 12, 50, 1);

  drawButton(d, 8, 155, 148, 36, "BUILD WALL  8G+1W", COL_PLUM);
  drawButton(d, 164, 155, 148, 36, "WARD TURRET 14G+1P", COL_TEAL);

  d.setTextColor(COL_CREAM, COL_NIGHT);
  char b[40];
  snprintf(b, sizeof(b), "Wall %u   Turret %u   Rep %u", wallLevel, turretLevel, reputation);
  d.drawString(b, 12, 198, 1);
}

void Game::drawBattle(M5GFX& d) {
  d.fillScreen(COL_NIGHT);
  // stars
  for (int i = 0; i < 22; i++) {
    int x = (i * 41 + day * 17) % 320;
    int y = 32 + (i * 31) % 150;
    d.fillCircle(x, y, 1, 0xFFFF);
  }

  // keep under siege
  d.fillRect(125, 118, 70, 80, COL_STONE);
  d.fillTriangle(118, 118, 160, 78, 202, 118, COL_PLUM);
  d.fillRect(145, 155, 30, 43, COL_INK);

  // monsters approaching
  int count = 1 + wave / 2;
  if (count > 5) count = 5;
  for (int i = 0; i < count; i++) {
    int x = 18 + i * 38 + (dayTick / 4 % 6);
    int y = 168 - (i % 2) * 18;
    uint8_t t = (wave > 3) ? 2 : (wave > 1 ? 1 : 0);
    drawTinyMonster(d, x, y, t);
  }

  drawPanel(d, 5, 28, 155, 42, COL_PANEL);
  d.setTextColor(COL_CREAM, COL_PANEL);
  d.drawString("NIGHT RAID", 12, 34, 1);
  d.setTextColor(COL_PINK, COL_PANEL);
  char b[36];
  snprintf(b, sizeof(b), "Wave %u  Keep %u HP", wave, wizardHp);
  d.drawString(b, 12, 50, 1);

  drawButton(d, 8, 162, 148, 36, "CAST WARD", COL_TEAL);
  drawButton(d, 164, 162, 148, 36, "END NIGHT", COL_PLUM);
}

void Game::drawJournal(M5GFX& d) {
  d.fillScreen(0x2125);
  drawPanel(d, 6, 28, 308, 175, COL_PANEL);

  d.setTextColor(COL_CREAM, COL_PANEL);
  d.drawString("THE TOWER LEDGER", 14, 36, 1);

  d.setTextColor(COL_GOLD, COL_PANEL);
  d.drawString("Known crafts", 14, 56, 1);
  d.setTextColor(COL_CREAM, COL_PANEL);
  d.drawString("- Moonroot tonic   (2H + 1M)", 14, 72, 1);
  d.drawString("- Stronger wards grow with research", 14, 88, 1);

  d.setTextColor(COL_GOLD, COL_PANEL);
  d.drawString("The revolving door", 14, 110, 1);
  d.setTextColor(COL_CREAM, COL_PANEL);
  char line[60];
  snprintf(line, sizeof(line), "Reputation %u  –  strangers arrive sooner", reputation);
  d.drawString(line, 14, 126, 1);
  snprintf(line, sizeof(line), "Walls %u   Turrets %u   Day %u", wallLevel, turretLevel, day);
  d.drawString(line, 14, 142, 1);

  d.setTextColor(0xBDF7, COL_PANEL);
  if (reputation < 5)
    d.drawString("Locals still trust the old paths.", 14, 168, 1);
  else if (reputation < 12)
    d.drawString("Word is spreading through the deeper woods.", 14, 168, 1);
  else
    d.drawString("Even the quiet ones have heard of you.", 14, 168, 1);
}

void Game::draw(M5GFX& d) {
  switch (screen) {
    case Screen::WORLD:   drawWorld(d);   break;
    case Screen::SHOP:    drawShop(d);    break;
    case Screen::LAB:     drawLab(d);     break;
    case Screen::GARDEN:  drawGarden(d);  break;
    case Screen::DEFENSE: drawDefense(d); break;
    case Screen::BATTLE:  drawBattle(d);  break;
    default:              drawJournal(d); break;
  }
  if (screen != Screen::BATTLE) drawTabs(d);
  drawHeader(d);

  if (dialogue) {
    drawPanel(d, 18, 70, 284, 96, COL_PANEL);
    d.setTextColor(COL_GOLD, COL_PANEL);
    d.drawString(messageTitle, 28, 80, 1);
    d.setTextColor(COL_CREAM, COL_PANEL);
    d.drawString(message, 28, 98, 1);
    drawButton(d, 100, 132, 120, 24, "CONTINUE", COL_PLUM);
  }
}

void Game::pickVisitor() {
  // Prefer visitors the player has unlocked via reputation
  uint8_t candidates[VISITOR_COUNT];
  uint8_t n = 0;
  for (uint8_t i = 0; i < VISITOR_COUNT; i++) {
    if (reputation >= visitors[i].minRep) candidates[n++] = i;
  }
  if (n == 0) n = 1, candidates[0] = 0;
  visitorIndex = candidates[day % n];  // deterministic but varies
  // slight shuffle
  if (n > 2 && (day % 5 == 0)) visitorIndex = candidates[(day / 3) % n];
}

void Game::advanceDay() {
  day++;
  night = false;
  screen = Screen::WORLD;
  herbs += 1;
  wood += 1;
  if (day % 2 == 0) mushrooms++;
  if (gardenStage > 0 && gardenStage < 3) gardenStage++;
  if (gardenStage >= 3) { /* ready */ }
  pickVisitor();
  messageTitle = "A new morning";
  message = "The woods left a little something at your door.";
  dialogue = true;
  saveRequested = true;
}

void Game::startNight() {
  night = true;
  screen = Screen::BATTLE;
  wave = 1 + (day / 4);
  if (wave > 6) wave = 6;
  monsterHp = 4 + wave * 2;
  wizardHp = 6 + wallLevel * 2;
  dayTick = 0;
  messageTitle = "";
  message = "";
  dialogue = false;
}

void Game::resolveBattle() {
  if (wizardHp > 0) {
    gold += 6 + wave * 3;
    mushrooms += 1 + (wave > 2);
    reputation += 1 + (wave > 3);
    messageTitle = "The woods fall quiet";
    message = "You survived. Something useful was left behind.";
  } else {
    gold += 3;
    messageTitle = "A rough night";
    message = "The keep stands, but the wards need attention.";
  }
  advanceDay();
  dialogue = true;
  saveRequested = true;
}

void Game::handleTap(int x, int y) {
  if (dialogue) {
    if (y > 120) { dialogue = false; saveRequested = true; }
    return;
  }

  if (screen != Screen::BATTLE && y >= 210) {
    if (x < 54) screen = Screen::WORLD;
    else if (x < 107) screen = Screen::SHOP;
    else if (x < 160) screen = Screen::LAB;
    else if (x < 213) screen = Screen::GARDEN;
    else if (x < 266) screen = Screen::DEFENSE;
    else screen = Screen::JOURNAL;
    return;
  }

  switch (screen) {
    case Screen::WORLD:
      if (y > 145 && x > 165) { screen = Screen::SHOP; return; }
      if (y > 80 && y < 120 && x > 165) { startNight(); return; }
      if (y > 140) {
        wood += 1; herbs += 1;
        if (day % 3 == 0) mushrooms++;
        messageTitle = "Gathered";
        message = "A few useful things from the forest floor.";
        dialogue = true; saveRequested = true;
      }
      break;

    case Screen::SHOP: {
      if (y > 95 && x > 150) {
        Visitor& v = visitors[visitorIndex];
        bool paid = false;
        if (v.reqType == 0 && herbs >= v.reqAmt) { herbs -= v.reqAmt; gold += v.reward; paid = true; }
        else if (v.reqType == 1 && potions >= v.reqAmt) { potions -= v.reqAmt; gold += v.reward; paid = true; }
        else if (v.reqType == 2 && mushrooms >= v.reqAmt) { mushrooms -= v.reqAmt; gold += v.reward; paid = true; }
        else if (v.reqType == 3 && wood >= v.reqAmt) { wood -= v.reqAmt; gold += v.reward; paid = true; }
        else if (v.reqType == 4) { // any / special
          if (potions > 0) { potions--; gold += v.reward; paid = true; }
          else if (herbs >= 1) { herbs--; gold += v.reward / 2; paid = true; }
        }

        if (paid) {
          reputation += 1 + (v.minRep > 5 ? 1 : 0);
          messageTitle = "Trade complete";
          message = "They leave satisfied. Word will travel.";
        } else {
          gold += 4;
          messageTitle = "A modest sale";
          message = "You offer a sample and promise more later.";
        }
        dialogue = true;
        // next visitor
        pickVisitor();
        saveRequested = true;
      }
      break;
    }

    case Screen::LAB:
      if (y > 155 && x < 160) {
        if (herbs >= 2 && mushrooms >= 1) {
          herbs -= 2; mushrooms--; potions++;
          messageTitle = "Brew complete";
          message = "One moonroot tonic bubbles into being.";
        } else {
          messageTitle = "Missing ingredients";
          message = "You need two herbs and one mushroom.";
        }
        dialogue = true; saveRequested = true;
      } else if (y > 155) {
        if (gold >= 12) {
          gold -= 12; reputation++;
          messageTitle = "Curious discovery";
          message = "Your notes reveal a stronger warding pattern.";
        } else {
          messageTitle = "Not enough gold";
          message = "Research materials cost twelve gold.";
        }
        dialogue = true; saveRequested = true;
      }
      break;

    case Screen::GARDEN:
      if (y > 155 && x < 160) {
        if (seeds > 0 && gardenStage == 0) {
          seeds--; gardenStage = 1;
          messageTitle = "Seed planted";
          message = "A moonseed settles into the soft earth.";
        } else if (gardenStage > 0) {
          messageTitle = "Already growing";
          message = "Patience. The moon does the rest.";
        } else {
          messageTitle = "No seeds";
          message = "Perhaps a visitor will bring some.";
        }
        dialogue = true; saveRequested = true;
      } else if (y > 155) {
        if (gardenStage >= 3) {
          herbs += 3; seeds += 1; gardenStage = 0;
          messageTitle = "Harvest!";
          message = "You gathered moon herbs and saved a seed.";
        } else {
          messageTitle = "Not ready";
          message = "The plants need another day or two.";
        }
        dialogue = true; saveRequested = true;
      }
      break;

    case Screen::DEFENSE:
      if (y > 145 && x < 160) {
        if (gold >= 8 && wood >= 1) {
          gold -= 8; wood--; wallLevel++;
          messageTitle = "Wall raised";
          message = "The keep feels a little safer.";
        } else {
          messageTitle = "Need supplies";
          message = "A wall costs 8 gold and 1 wood.";
        }
        dialogue = true; saveRequested = true;
      } else if (y > 145) {
        if (gold >= 14 && potions >= 1) {
          gold -= 14; potions--; turretLevel++;
          messageTitle = "Turret installed";
          message = "A soft blue light begins to hum.";
        } else {
          messageTitle = "Need supplies";
          message = "A ward turret costs 14 gold and 1 potion.";
        }
        dialogue = true; saveRequested = true;
      }
      break;

    case Screen::BATTLE:
      if (y > 155 && x < 160) {
        int dmg = 2 + turretLevel;
        monsterHp -= dmg;
        if (monsterHp <= 0) {
          messageTitle = "Wave repelled";
          message = "Your ward flares and the creatures retreat.";
          resolveBattle();
        }
      } else if (y > 155) {
        resolveBattle();
      }
      break;

    default: break;
  }
}

void Game::update() {
  dayTick++;
  if (M5.BtnA.wasPressed()) {
    if (screen == Screen::BATTLE) handleTap(70, 180);
    else screen = Screen::WORLD;
  }
  if (M5.BtnB.wasPressed()) {
    if (screen == Screen::BATTLE) handleTap(230, 180);
    else screen = Screen::SHOP;
  }
  if (M5.BtnC.wasPressed()) {
    if (screen == Screen::BATTLE) resolveBattle();
    else if (screen == Screen::WORLD) startNight();
    else screen = Screen::LAB;
  }

  auto t = M5.Touch.getDetail();
  if (t.wasPressed()) handleTap(t.x, t.y);

  if (screen == Screen::BATTLE && dayTick % 100 == 0) {
    wizardHp -= 1;
    if (wizardHp <= 0) resolveBattle();
  }
  if (screen == Screen::WORLD && dayTick > 2000) {
    dayTick = 0;
    startNight();
  }
}
