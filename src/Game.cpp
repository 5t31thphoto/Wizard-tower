#include "Game.h"

static const uint16_t INK=0x18E3, PANEL=0x2945, PANEL2=0x39A7, CREAM=0xFFDB;
static const uint16_t TEAL=0x04F2, PLUM=0x6810, LIME=0x87E0, GOLD=0xFEA0, PINK=0xF3B8;
static const uint16_t GRASS=0x3D66, DARKGRASS=0x2AE4, BROWN=0x8A03, STONE=0x8C71, NIGHT=0x1084;
static const char* screenName(Screen s) {
  switch(s){case Screen::WORLD:return "CLEARING";case Screen::SHOP:return "SHOP";case Screen::LAB:return "LAB";case Screen::GARDEN:return "GARDEN";case Screen::DEFENSE:return "KEEP";case Screen::BATTLE:return "NIGHT WATCH";default:return "JOURNAL";}
}
void Game::begin(){ messageTitle="A quiet morning"; }
bool Game::consumeSaveRequest(){bool v=saveRequested;saveRequested=false;return v;}
void Game::drawPanel(M5GFX&d,int x,int y,int w,int h,uint16_t fill){
  d.fillRoundRect(x,y,w,h,5,fill); d.drawRoundRect(x,y,w,h,5,0x7B6D);
}
void Game::drawButton(M5GFX&d,int x,int y,int w,int h,const char*label,uint16_t fill){
  d.fillRoundRect(x,y,w,h,4,fill); d.drawRoundRect(x,y,w,h,4,CREAM); d.setTextColor(CREAM,fill); d.drawString(label,x+5,y+(h-8)/2,1);
}
void Game::drawHeader(M5GFX&d){
  d.fillRect(0,0,320,24,INK); d.setTextColor(CREAM,INK);
  char buf[48]; snprintf(buf,sizeof(buf),"WIZARD'S KEEP  /  DAY %u",day); d.drawString(buf,5,5,1);
  snprintf(buf,sizeof(buf),"%luG  H:%u  W:%u  M:%u", (unsigned long)gold,herbs,wood,mushrooms);
  d.setTextColor(GOLD,INK); d.drawString(buf,190,5,1);
}
void Game::drawTabs(M5GFX&d){
  const char* names[]={"WOODS","SHOP","LAB","GARDEN","KEEP","BOOK"};
  Screen ids[]={Screen::WORLD,Screen::SHOP,Screen::LAB,Screen::GARDEN,Screen::DEFENSE,Screen::JOURNAL};
  for(int i=0;i<6;i++){uint16_t c=(screen==ids[i])?PLUM:PANEL; drawButton(d,i*53+2,211,50,26,names[i],c);}
}
void Game::drawWorld(M5GFX&d){
  d.fillScreen(GRASS);
  // tiny woodland clearing, readable tile-like blocks
  for(int y=27;y<204;y+=16)for(int x=0;x<320;x+=16){
    uint16_t c=((x/16+y/16)%3==0)?DARKGRASS:GRASS; d.fillRect(x,y,16,16,c);
    if(((x*7+y*3)%11)==0)d.drawPixel(x+7,y+8,PINK);
  }
  // forest edge
  for(int x=0;x<320;x+=32){d.fillCircle(x+12,47,14,0x1D84);d.fillCircle(x+23,42,11,0x2D05);d.fillRect(x+14,47,7,15,BROWN);}
  // tower
  d.fillRect(24,75,72,89,STONE); d.fillRect(18,68,84,13,PLUM); d.fillTriangle(18,68,60,35,102,68,PLUM);
  d.fillRect(48,113,22,51,BROWN); d.fillRect(35,91,13,18,GOLD); d.fillRect(72,91,13,18,GOLD);
  d.fillRect(49,130,20,34,INK); d.drawRect(49,130,20,34,CREAM);
  // garden plots
  for(int i=0;i<3;i++){int x=133+i*43;d.fillRoundRect(x,118,35,37,3,BROWN);for(int j=0;j<3;j++){d.drawFastVLine(x+8+j*9,126,20,LIME);d.fillCircle(x+8+j*9,127,3,0xAFC0);}}
  // path
  for(int x=94;x<125;x+=12)d.fillRect(x,150,10,10,0xC5B0);
  // player wizard
  d.fillCircle(112,174,6,0xFBCB);d.fillTriangle(104,169,112,156,120,169,PLUM);d.fillRect(106,174,12,15,PLUM);d.drawFastVLine(123,165,24,BROWN);d.fillCircle(123,162,3,TEAL);
  drawPanel(d,5,29,119,32,PANEL);d.setTextColor(CREAM,PANEL);d.drawString("Your little corner",12,35,1);d.setTextColor(0xBDF7,PANEL);d.drawString("of the peculiar woods.",12,47,1);
  drawPanel(d,174,29,140,45,PANEL);d.setTextColor(CREAM,PANEL);d.drawString("TODAY'S TASK",182,35,1);d.setTextColor(GOLD,PANEL);d.drawString("Gather, brew, meet someone.",182,49,1);
  drawButton(d,184,82,126,28,"BEGIN NIGHT RAID",0x3810);\n  drawButton(d,184,161,126,36,"OPEN THE SHOP",PLUM);
}
void Game::drawShop(M5GFX&d){
  d.fillScreen(0x31A8); // warm timber floor
  for(int y=27;y<207;y+=16)for(int x=0;x<320;x+=16){d.drawRect(x,y,16,16,0x5A08);}
  d.fillRect(0,27,320,24,0x5A08);d.fillRect(12,57,296,8,BROWN);
  // shelves and bottles
  for(int i=0;i<7;i++){int x=20+i*41;d.fillRect(x,68,32,36,BROWN);d.fillRect(x+5,78,8,15,TEAL);d.fillRect(x+19,75,8,18,PINK);d.fillRect(x+5,75,8,3,GOLD);d.fillRect(x+19,72,8,3,GOLD);}
  d.fillRect(70,145,180,22,BROWN);d.fillRect(78,137,164,8,0xD6B2);
  // visiting customer
  d.fillCircle(160,115,9,0xF9CB);d.fillRect(151,124,18,24,0x6A0D);d.fillTriangle(148,108,160,91,172,108,PLUM);
  drawPanel(d,8,31,145,35,PANEL);d.setTextColor(CREAM,PANEL);d.drawString("A visitor has arrived!",15,37,1);d.setTextColor(GOLD,PANEL);d.drawString(visitors[visitorIndex].name,15,50,1);
  drawPanel(d,8,171,304,34,PANEL);d.setTextColor(CREAM,PANEL);d.drawString(visitors[visitorIndex].greeting,15,177,1);d.setTextColor(0xBDF7,PANEL);d.drawString(visitors[visitorIndex].request,15,190,1);
  drawButton(d,170,112,140,30,"TRADE / HELP",PLUM);
}
void Game::drawLab(M5GFX&d){
  d.fillScreen(0x18E3); for(int y=27;y<210;y+=16)for(int x=0;x<320;x+=16)d.drawRect(x,y,16,16,0x39A7);
  d.fillRect(18,50,284,8,BROWN);for(int i=0;i<6;i++){int x=30+i*45;d.fillRect(x,28,13,22,0x7E9F);d.fillRect(x+3,24,7,5,GOLD);}
  d.fillRect(65,122,190,18,BROWN);d.fillRect(75,140,12,53,BROWN);d.fillRect(235,140,12,53,BROWN);
  d.fillRoundRect(130,83,60,48,12,0x6B4D);d.fillRect(138,75,44,13,0x9D13);d.fillCircle(160,105,14,TEAL);d.fillCircle(160,105,7,LIME);
  drawPanel(d,7,31,144,36,PANEL);d.setTextColor(CREAM,PANEL);d.drawString("ALCHEMY BENCH",14,37,1);d.setTextColor(GOLD,PANEL);d.drawString("Herbs + mushrooms",14,51,1);
  drawButton(d,12,165,142,34,"BREW POTION",PLUM);drawButton(d,166,165,142,34,"RESEARCH",TEAL);
  d.setTextColor(CREAM,0x18E3);char b[40];snprintf(b,sizeof(b),"Potions: %u   Herbs: %u",potions,herbs);d.drawString(b,14,207,1);
}
void Game::drawGarden(M5GFX&d){
  d.fillScreen(0x2AE4);
  for(int y=38;y<194;y+=48)for(int x=12;x<310;x+=58){d.fillRoundRect(x,y,48,38,4,BROWN);for(int i=0;i<3;i++){d.drawFastVLine(x+12+i*12,y+12,16,LIME);d.fillCircle(x+12+i*12,y+12,4,(day%2)?PINK:GOLD);}}
  drawPanel(d,8,29,165,33,PANEL);d.setTextColor(CREAM,PANEL);d.drawString("MOONPATCH GARDEN",15,36,1);d.setTextColor(GOLD,PANEL);d.drawString("Seeds grow between days.",15,49,1);
  drawButton(d,12,163,140,35,"PLANT SEED",PLUM);drawButton(d,166,163,140,35,"HARVEST",TEAL);
}
void Game::drawDefense(M5GFX&d){
  d.fillScreen(NIGHT);for(int y=32;y<205;y+=16)for(int x=0;x<320;x+=16)d.fillRect(x,y,16,16,((x+y)/16)%2?0x10A4:0x18C6);
  d.fillRect(128,84,64,92,STONE);d.fillTriangle(120,84,160,48,200,84,PLUM);d.fillRect(147,135,26,41,INK);
  for(int i=0;i<wallLevel;i++)d.fillRect(20+i*18,176,15,12,STONE);
  for(int i=0;i<turretLevel;i++){int x=225+i*24;d.fillRect(x,150,12,26,BROWN);d.fillCircle(x+6,148,8,TEAL);}
  drawPanel(d,7,30,170,42,PANEL);d.setTextColor(CREAM,PANEL);d.drawString("KEEP IMPROVEMENTS",14,36,1);d.setTextColor(GOLD,PANEL);d.drawString("Walls & warding turrets",14,51,1);
  drawButton(d,8,155,145,39,"BUILD WALL  8G",PLUM);drawButton(d,165,155,145,39,"WARD TURRET  14G",TEAL);
  d.setTextColor(CREAM,NIGHT);char b[40];snprintf(b,sizeof(b),"Wall %u   Turret %u",wallLevel,turretLevel);d.drawString(b,12,198,1);
}
void Game::drawBattle(M5GFX&d){
  d.fillScreen(NIGHT);for(int i=0;i<18;i++){int x=(i*37+day*13)%320,y=35+(i*29)%160;d.fillCircle(x,y,1,0xFFFF);}
  d.fillRect(130,125,60,75,STONE);d.fillTriangle(124,125,160,90,196,125,PLUM);d.fillRect(148,163,24,37,INK);
  int count=wave+1;for(int i=0;i<count;i++){int x=20+i*42+(dayTick%8);int y=164-(i%2)*22;d.fillCircle(x,y,7,0xA154);d.fillCircle(x-3,y-2,2,LIME);d.fillCircle(x+3,y-2,2,LIME);}
  drawPanel(d,6,29,140,39,PANEL);d.setTextColor(CREAM,PANEL);d.drawString("NIGHT RAID",13,35,1);d.setTextColor(PINK,PANEL);char b[32];snprintf(b,sizeof(b),"Wave %u  /  Keep %u HP",wave,wizardHp);d.drawString(b,13,50,1);
  drawButton(d,8,163,145,38,"CAST WARD",TEAL);drawButton(d,166,163,145,38,"END NIGHT",PLUM);
}
void Game::drawJournal(M5GFX&d){
  d.fillScreen(0x2125);drawPanel(d,8,31,304,169,PANEL);
  d.setTextColor(CREAM,PANEL);d.drawString("THE TOWER LEDGER",17,40,1);
  d.setTextColor(GOLD,PANEL);d.drawString("Known crafts",17,62,1);
  d.setTextColor(CREAM,PANEL);d.drawString("- Moonroot tonic: 2 herbs + 1 mushroom",17,79,1);d.drawString("- Warding charm: 2 wood + 1 potion",17,96,1);
  d.drawString("- Shop reputation attracts rarer visitors.",17,113,1);d.drawString("- Stronger wards draw stranger things.",17,130,1);
  d.setTextColor(0xBDF7,PANEL);char b[60];snprintf(b,sizeof(b),"Reputation %u   Walls %u   Turrets %u",reputation,wallLevel,turretLevel);d.drawString(b,17,160,1);
  d.drawString("A small life. A very large woods.",17,181,1);
}
void Game::draw(M5GFX&d){
  switch(screen){case Screen::WORLD:drawWorld(d);break;case Screen::SHOP:drawShop(d);break;case Screen::LAB:drawLab(d);break;case Screen::GARDEN:drawGarden(d);break;case Screen::DEFENSE:drawDefense(d);break;case Screen::BATTLE:drawBattle(d);break;default:drawJournal(d);break;}
  if(screen!=Screen::BATTLE)drawTabs(d);
  drawHeader(d);
  if(dialogue){drawPanel(d,20,74,280,91,PANEL);d.setTextColor(GOLD,PANEL);d.drawString(messageTitle,30,83,1);d.setTextColor(CREAM,PANEL);d.drawString(message,30,101,1);drawButton(d,105,137,110,22,"CONTINUE",PLUM);}
}
void Game::advanceDay(){
  day++; night=false;screen=Screen::WORLD; herbs+=1;wood+=1;
  if(day%2==0)mushrooms++;
  if(seeds>0 && day%2==0)herbs++;
  visitorIndex=(visitorIndex+1+(day%3))%8;
  messageTitle="A new morning";message="The woods have left a little something at your door.";dialogue=true;saveRequested=true;
}
void Game::startNight(){
  night=true;screen=Screen::BATTLE;wave=1+(day/3);monsterHp=3+wave;wizardHp=5+wallLevel;dayTick=0;
  messageTitle="";message="";dialogue=false;
}
void Game::resolveBattle(){
  if(wizardHp>0){gold+=5+wave*2;mushrooms++;reputation++;messageTitle="The woods fall quiet";message="You survived. Something useful was left behind.";}
  else{gold+=2;messageTitle="A rough night";message="The keep stands, but the wards need attention.";}
  advanceDay();dialogue=true;saveRequested=true;
}
void Game::handleTap(int x,int y){
  if(dialogue){if(y>125){dialogue=false;saveRequested=true;}return;}
  if(screen!=Screen::BATTLE && y>=210){
    if(x<54)screen=Screen::WORLD;else if(x<107)screen=Screen::SHOP;else if(x<160)screen=Screen::LAB;else if(x<213)screen=Screen::GARDEN;else if(x<266)screen=Screen::DEFENSE;else screen=Screen::JOURNAL;return;
  }
  switch(screen){
    case Screen::WORLD:
      if(y>150 && x>170){screen=Screen::SHOP;return;}
      if(y>100){wood+=1;herbs+=1;mushrooms+=(day%2);messageTitle="Gathered";message="A few useful things from the forest floor.";dialogue=true;saveRequested=true;}
      else if(y>70){startNight();}
      break;
    case Screen::SHOP:{
      if(y>95 && x>150){
        Visitor &v=visitors[visitorIndex];
        if(v.icon==0 && herbs>=2){herbs-=2;gold+=v.reward;}
        else if(v.icon==4 && mushrooms>=3){mushrooms-=3;gold+=v.reward;}
        else if(v.icon==7 && wood>=1){wood--;gold+=v.reward;}
        else if(potions>0){potions--;gold+=v.reward;}
        else {gold+=3;message="You offer a small sample and promise to brew the rest.";messageTitle="A modest sale";dialogue=true;}
        reputation++;visitorIndex=(visitorIndex+1)%8;saveRequested=true;
      }break;}
    case Screen::LAB:
      if(y>155 && x<160){if(herbs>=2&&mushrooms>=1){herbs-=2;mushrooms--;potions++;messageTitle="Brew complete";message="One moonroot tonic bubbles into being.";}else{messageTitle="Missing ingredients";message="You need two herbs and one mushroom.";}dialogue=true;saveRequested=true;}
      else if(y>155){if(gold>=10){gold-=10;reputation++;messageTitle="A curious discovery";message="Your notes reveal a stronger warding pattern.";}else{messageTitle="Not enough gold";message="The research materials cost ten gold.";}dialogue=true;saveRequested=true;}break;
    case Screen::GARDEN:
      if(y>155&&x<160){if(seeds){seeds--;messageTitle="Seed planted";message="A moonseed settles into the soft earth.";}else{messageTitle="No seeds";message="Perhaps a visitor will bring some.";}dialogue=true;saveRequested=true;}
      else if(y>155){herbs+=2;seeds++;messageTitle="Harvest";message="You gathered moon herbs and saved a seed.";dialogue=true;saveRequested=true;}break;
    case Screen::DEFENSE:
      if(y>145&&x<160){if(gold>=8&&wood>=1){gold-=8;wood--;wallLevel++;}else{messageTitle="Need supplies";message="A wall costs 8 gold and 1 wood.";dialogue=true;}saveRequested=true;}
      else if(y>145){if(gold>=14&&potions>=1){gold-=14;potions--;turretLevel++;}else{messageTitle="Need supplies";message="A ward turret costs 14 gold and 1 potion.";dialogue=true;}saveRequested=true;}break;
    case Screen::BATTLE:
      if(y>155&&x<160){monsterHp-=2+turretLevel;if(monsterHp<=0){messageTitle="Wave repelled";message="Your ward flares and the creatures retreat.";resolveBattle();}}
      else if(y>155){resolveBattle();}break;
    default:break;
  }
}
void Game::update(){
  dayTick++;
  if(M5.BtnA.wasPressed()){if(screen==Screen::BATTLE)handleTap(70,180);else screen=Screen::WORLD;}
  if(M5.BtnB.wasPressed()){if(screen==Screen::BATTLE)handleTap(230,180);else screen=Screen::SHOP;}
  if(M5.BtnC.wasPressed()){if(screen==Screen::BATTLE)resolveBattle();else if(screen==Screen::WORLD)startNight();else screen=Screen::LAB;}
  auto t=M5.Touch.getDetail();
  if(t.wasPressed())handleTap(t.x,t.y);
  if(screen==Screen::BATTLE && dayTick%110==0){
    wizardHp-=1;
    if(wizardHp<=0)resolveBattle();
  }
  if(screen==Screen::WORLD && dayTick>1800){dayTick=0;startNight();}
}
