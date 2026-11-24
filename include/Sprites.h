#pragma once
#include <Arduino.h>
#include <M5GFX.h>

// Tiny 12x16 sprites (RGB565, 0x0000 = transparent)
// Stored in PROGMEM to keep RAM free.

namespace Sprites {

// Common palette helpers (must match COL_ values in Game.cpp)
constexpr uint16_t T  = 0x0000; // transparent
constexpr uint16_t K  = 0x18E3; // ink / dark
constexpr uint16_t C  = 0xFFDB; // cream
constexpr uint16_t G  = 0xFEA0; // gold
constexpr uint16_t P  = 0x6810; // plum
constexpr uint16_t L  = 0x87E0; // lime
constexpr uint16_t E  = 0x04F2; // teal
constexpr uint16_t S  = 0xF9CB; // skin
constexpr uint16_t B  = 0x8A03; // brown
constexpr uint16_t M  = 0x4C8A; // moss
constexpr uint16_t O  = 0xDEFB; // bone
constexpr uint16_t V  = 0x4810; // void purple
constexpr uint16_t R  = 0xF800; // red accent
constexpr uint16_t W  = 0xFFFF; // white
constexpr uint16_t D  = 0x4208; // dark gray
constexpr uint16_t H  = 0x07E0; // bright green (fungus)

// 12 wide x 16 tall
constexpr int SW = 12;
constexpr int SH = 16;

// --- Visitor sprites (front-facing, readable at 12x16) ---

// 0: Mara / normal herbalist (green tunic + hat)
const uint16_t mara[SW*SH] PROGMEM = {
  T,T,T,P,P,P,P,P,T,T,T,T,
  T,T,P,P,P,P,P,P,P,T,T,T,
  T,T,T,S,S,S,S,S,T,T,T,T,
  T,T,S,S,K,S,K,S,S,T,T,T,
  T,T,S,S,S,S,S,S,S,T,T,T,
  T,T,T,S,S,S,S,S,T,T,T,T,
  T,T,L,L,L,L,L,L,L,T,T,T,
  T,L,L,L,L,L,L,L,L,L,T,T,
  T,L,L,L,L,L,L,L,L,L,T,T,
  T,T,L,L,L,L,L,L,L,T,T,T,
  T,T,B,B,T,T,B,B,T,T,T,T,
  T,T,B,B,T,T,B,B,T,T,T,T,
  T,T,B,B,T,T,B,B,T,T,T,T,
  T,T,T,T,T,T,T,T,T,T,T,T,
  T,T,T,T,T,T,T,T,T,T,T,T,
  T,T,T,T,T,T,T,T,T,T,T,T,
};

// 1: Nell baker (apron)
const uint16_t nell[SW*SH] PROGMEM = {
  T,T,T,B,B,B,B,B,T,T,T,T,
  T,T,B,B,B,B,B,B,B,T,T,T,
  T,T,T,S,S,S,S,S,T,T,T,T,
  T,T,S,S,K,S,K,S,S,T,T,T,
  T,T,S,S,S,S,S,S,S,T,T,T,
  T,T,C,C,C,C,C,C,C,T,T,T,
  T,C,C,C,C,C,C,C,C,C,T,T,
  T,C,C,C,C,C,C,C,C,C,T,T,
  T,T,C,C,C,C,C,C,C,T,T,T,
  T,T,B,B,T,T,B,B,T,T,T,T,
  T,T,B,B,T,T,B,B,T,T,T,T,
  T,T,B,B,T,T,B,B,T,T,T,T,
  T,T,T,T,T,T,T,T,T,T,T,T,
  T,T,T,T,T,T,T,T,T,T,T,T,
  T,T,T,T,T,T,T,T,T,T,T,T,
  T,T,T,T,T,T,T,T,T,T,T,T,
};

// 2: Pipwick peddler (coat + goggles)
const uint16_t pipwick[SW*SH] PROGMEM = {
  T,T,T,B,B,B,B,B,T,T,T,T,
  T,T,B,B,B,B,B,B,B,T,T,T,
  T,T,T,S,S,S,S,S,T,T,T,T,
  T,T,G,G,K,S,K,G,G,T,T,T,
  T,T,S,S,S,S,S,S,S,T,T,T,
  T,T,B,B,B,B,B,B,B,T,T,T,
  T,B,B,B,B,B,B,B,B,B,T,T,
  T,B,B,G,B,B,B,G,B,B,T,T,
  T,T,B,B,B,B,B,B,B,T,T,T,
  T,T,B,B,T,T,B,B,T,T,T,T,
  T,T,B,B,T,T,B,B,T,T,T,T,
  T,T,B,B,T,T,B,B,T,T,T,T,
  T,T,T,T,T,T,T,T,T,T,T,T,
  T,T,T,T,T,T,T,T,T,T,T,T,
  T,T,T,T,T,T,T,T,T,T,T,T,
  T,T,T,T,T,T,T,T,T,T,T,T,
};

// 3: Bramble / mushroom gatherer
const uint16_t bramble[SW*SH] PROGMEM = {
  T,T,T,R,R,R,R,R,T,T,T,T,
  T,T,R,R,R,R,R,R,R,T,T,T,
  T,R,R,R,R,R,R,R,R,R,T,T,
  T,T,T,S,S,S,S,S,T,T,T,T,
  T,T,S,S,K,S,K,S,S,T,T,T,
  T,T,S,S,S,S,S,S,S,T,T,T,
  T,T,M,M,M,M,M,M,M,T,T,T,
  T,M,M,M,M,M,M,M,M,M,T,T,
  T,M,M,M,M,M,M,M,M,M,T,T,
  T,T,M,M,M,M,M,M,M,T,T,T,
  T,T,B,B,T,T,B,B,T,T,T,T,
  T,T,B,B,T,T,B,B,T,T,T,T,
  T,T,B,B,T,T,B,B,T,T,T,T,
  T,T,T,T,T,T,T,T,T,T,T,T,
  T,T,T,T,T,T,T,T,T,T,T,T,
  T,T,T,T,T,T,T,T,T,T,T,T,
};

// 4: Orrin tinkerer
const uint16_t orrin[SW*SH] PROGMEM = {
  T,T,T,D,D,D,D,D,T,T,T,T,
  T,T,D,D,D,D,D,D,D,T,T,T,
  T,T,T,S,S,S,S,S,T,T,T,T,
  T,T,G,G,K,S,K,G,G,T,T,T,
  T,T,S,S,S,S,S,S,S,T,T,T,
  T,T,B,B,B,B,B,B,B,T,T,T,
  T,B,B,G,B,B,B,G,B,B,T,T,
  T,B,B,B,B,B,B,B,B,B,T,T,
  T,T,B,B,B,B,B,B,B,T,T,T,
  T,T,B,B,T,T,B,B,T,T,T,T,
  T,T,B,B,T,T,B,B,T,T,T,T,
  T,T,B,B,T,T,B,B,T,T,T,T,
  T,T,T,T,T,T,T,T,T,T,T,T,
  T,T,T,T,T,T,T,T,T,T,T,T,
  T,T,T,T,T,T,T,T,T,T,T,T,
  T,T,T,T,T,T,T,T,T,T,T,T,
};

// 5: Sir Rowan
const uint16_t rowan[SW*SH] PROGMEM = {
  T,T,T,D,D,D,D,D,T,T,T,T,
  T,T,D,D,D,D,D,D,D,T,T,T,
  T,T,T,S,S,S,S,S,T,T,T,T,
  T,T,S,S,K,S,K,S,S,T,T,T,
  T,T,S,S,S,S,S,S,S,T,T,T,
  T,T,D,D,D,D,D,D,D,T,T,T,
  T,D,D,D,D,D,D,D,D,D,T,T,
  T,D,D,G,D,D,D,G,D,D,T,T,
  T,T,D,D,D,D,D,D,D,T,T,T,
  T,T,D,D,T,T,D,D,T,T,T,T,
  T,T,D,D,T,T,D,D,T,T,T,T,
  T,T,D,D,T,T,D,D,T,T,T,T,
  T,T,T,T,T,T,T,T,T,T,T,T,
  T,T,T,T,T,T,T,T,T,T,T,T,
  T,T,T,T,T,T,T,T,T,T,T,T,
  T,T,T,T,T,T,T,T,T,T,T,T,
};

// 6: Madame Moth (witch)
const uint16_t moth[SW*SH] PROGMEM = {
  T,T,T,P,P,P,P,P,T,T,T,T,
  T,T,P,P,P,P,P,P,P,T,T,T,
  T,P,P,P,P,P,P,P,P,P,T,T,
  T,T,T,S,S,S,S,S,T,T,T,T,
  T,T,S,S,K,S,K,S,S,T,T,T,
  T,T,S,S,S,S,S,S,S,T,T,T,
  T,T,P,P,P,P,P,P,P,T,T,T,
  T,P,P,P,P,P,P,P,P,P,T,T,
  T,P,P,P,P,P,P,P,P,P,T,T,
  T,T,P,P,P,P,P,P,P,T,T,T,
  T,T,P,P,T,T,P,P,T,T,T,T,
  T,T,P,P,T,T,P,P,T,T,T,T,
  T,T,P,P,T,T,P,P,T,T,T,T,
  T,T,T,T,T,T,T,T,T,T,T,T,
  T,T,T,T,T,T,T,T,T,T,T,T,
  T,T,T,T,T,T,T,T,T,T,T,T,
};

// 7: Quiet Guest (hooded)
const uint16_t quiet[SW*SH] PROGMEM = {
  T,T,T,D,D,D,D,D,T,T,T,T,
  T,T,D,D,D,D,D,D,D,T,T,T,
  T,D,D,D,D,D,D,D,D,D,T,T,
  T,D,D,K,K,K,K,K,D,D,T,T,
  T,D,D,K,K,K,K,K,D,D,T,T,
  T,T,D,D,D,D,D,D,D,T,T,T,
  T,T,D,D,D,D,D,D,D,T,T,T,
  T,D,D,D,D,D,D,D,D,D,T,T,
  T,D,D,D,D,D,D,D,D,D,T,T,
  T,T,D,D,D,D,D,D,D,T,T,T,
  T,T,D,D,T,T,D,D,T,T,T,T,
  T,T,D,D,T,T,D,D,T,T,T,T,
  T,T,D,D,T,T,D,D,T,T,T,T,
  T,T,T,T,T,T,T,T,T,T,T,T,
  T,T,T,T,T,T,T,T,T,T,T,T,
  T,T,T,T,T,T,T,T,T,T,T,T,
};

// 8: Spore (fungus herbalist)
const uint16_t spore[SW*SH] PROGMEM = {
  T,T,H,H,H,H,H,H,H,T,T,T,
  T,H,H,H,H,H,H,H,H,H,T,T,
  H,H,H,L,H,H,H,L,H,H,H,T,
  T,H,H,H,H,H,H,H,H,H,T,T,
  T,T,H,H,H,H,H,H,H,T,T,T,
  T,T,T,H,K,H,K,H,T,T,T,T,
  T,T,T,H,H,H,H,H,T,T,T,T,
  T,T,M,M,M,M,M,M,M,T,T,T,
  T,M,M,M,M,M,M,M,M,M,T,T,
  T,M,M,M,M,M,M,M,M,M,T,T,
  T,T,M,M,M,M,M,M,M,T,T,T,
  T,T,M,M,T,T,M,M,T,T,T,T,
  T,T,M,M,T,T,M,M,T,T,T,T,
  T,T,M,M,T,T,M,M,T,T,T,T,
  T,T,T,T,T,T,T,T,T,T,T,T,
  T,T,T,T,T,T,T,T,T,T,T,T,
};

// 9: Bonewhisper (skeleton mage)
const uint16_t bone[SW*SH] PROGMEM = {
  T,T,T,P,P,P,P,P,T,T,T,T,
  T,T,P,P,P,P,P,P,P,T,T,T,
  T,P,P,P,P,P,P,P,P,P,T,T,
  T,T,T,O,O,O,O,O,T,T,T,T,
  T,T,O,E,O,O,E,O,O,T,T,T,
  T,T,O,O,O,O,O,O,O,T,T,T,
  T,T,P,P,P,P,P,P,P,T,T,T,
  T,P,P,P,P,P,P,P,P,P,T,T,
  T,P,P,P,P,P,P,P,P,P,T,T,
  T,T,P,P,P,P,P,P,P,T,T,T,
  T,T,O,O,T,T,O,O,T,T,T,T,
  T,T,O,O,T,T,O,O,T,T,T,T,
  T,T,O,O,T,T,O,O,T,T,T,T,
  T,T,T,T,T,T,T,T,T,T,T,T,
  T,T,T,T,T,T,T,T,T,T,T,T,
  T,T,T,T,T,T,T,T,T,T,T,T,
};

// 10: Mossback treant
const uint16_t mossback[SW*SH] PROGMEM = {
  T,T,T,M,M,M,M,M,T,T,T,T,
  T,T,M,M,L,M,L,M,M,T,T,T,
  T,M,M,M,M,M,M,M,M,M,T,T,
  T,T,B,B,B,B,B,B,B,T,T,T,
  T,T,B,K,B,B,K,B,B,T,T,T,
  T,T,B,B,B,B,B,B,B,T,T,T,
  T,T,B,B,B,B,B,B,B,T,T,T,
  T,B,B,B,B,B,B,B,B,B,T,T,
  T,B,B,B,B,B,B,B,B,B,T,T,
  T,T,B,B,B,B,B,B,B,T,T,T,
  T,T,B,B,T,T,B,B,T,T,T,T,
  T,T,B,B,T,T,B,B,T,T,T,T,
  T,T,B,B,T,T,B,B,T,T,T,T,
  T,T,T,T,T,T,T,T,T,T,T,T,
  T,T,T,T,T,T,T,T,T,T,T,T,
  T,T,T,T,T,T,T,T,T,T,T,T,
};

// 11: Lady Pale (ghost)
const uint16_t pale[SW*SH] PROGMEM = {
  T,T,T,E,E,E,E,E,T,T,T,T,
  T,T,E,E,E,E,E,E,E,T,T,T,
  T,T,T,C,C,C,C,C,T,T,T,T,
  T,T,C,C,K,C,K,C,C,T,T,T,
  T,T,C,C,C,C,C,C,C,T,T,T,
  T,T,E,E,E,E,E,E,E,T,T,T,
  T,E,E,E,E,E,E,E,E,E,T,T,
  T,E,E,E,E,E,E,E,E,E,T,T,
  T,T,E,E,E,E,E,E,E,T,T,T,
  T,T,E,E,T,T,E,E,T,T,T,T,
  T,T,E,E,T,T,E,E,T,T,T,T,
  T,T,E,E,T,T,E,E,T,T,T,T,
  T,T,T,T,T,T,T,T,T,T,T,T,
  T,T,T,T,T,T,T,T,T,T,T,T,
  T,T,T,T,T,T,T,T,T,T,T,T,
  T,T,T,T,T,T,T,T,T,T,T,T,
};

// 12: Voidling
const uint16_t voidling[SW*SH] PROGMEM = {
  T,T,T,V,V,V,V,V,T,T,T,T,
  T,T,V,V,V,V,V,V,V,T,T,T,
  T,V,V,V,V,V,V,V,V,V,T,T,
  T,T,T,K,K,K,K,K,T,T,T,T,
  T,T,K,R,K,K,R,K,K,T,T,T,
  T,T,K,K,K,K,K,K,K,T,T,T,
  T,T,V,V,V,V,V,V,V,T,T,T,
  T,V,V,V,V,V,V,V,V,V,T,T,
  T,V,V,V,V,V,V,V,V,V,T,T,
  T,T,V,V,V,V,V,V,V,T,T,T,
  T,T,V,V,T,T,V,V,T,T,T,T,
  T,T,V,V,T,T,V,V,T,T,T,T,
  T,T,V,V,T,T,V,V,T,T,T,T,
  T,T,T,T,T,T,T,T,T,T,T,T,
  T,T,T,T,T,T,T,T,T,T,T,T,
  T,T,T,T,T,T,T,T,T,T,T,T,
};

// 13: fallback / last regular
const uint16_t regular[SW*SH] PROGMEM = {
  T,T,T,P,P,P,P,P,T,T,T,T,
  T,T,P,P,P,P,P,P,P,T,T,T,
  T,T,T,S,S,S,S,S,T,T,T,T,
  T,T,S,S,K,S,K,S,S,T,T,T,
  T,T,S,S,S,S,S,S,S,T,T,T,
  T,T,B,B,B,B,B,B,B,T,T,T,
  T,B,B,B,B,B,B,B,B,B,T,T,
  T,B,B,B,B,B,B,B,B,B,T,T,
  T,T,B,B,B,B,B,B,B,T,T,T,
  T,T,B,B,T,T,B,B,T,T,T,T,
  T,T,B,B,T,T,B,B,T,T,T,T,
  T,T,B,B,T,T,B,B,T,T,T,T,
  T,T,T,T,T,T,T,T,T,T,T,T,
  T,T,T,T,T,T,T,T,T,T,T,T,
  T,T,T,T,T,T,T,T,T,T,T,T,
  T,T,T,T,T,T,T,T,T,T,T,T,
};

// --- Monsters (simpler 10x10-ish but same 12x16 cell) ---

const uint16_t slime[SW*SH] PROGMEM = {
  T,T,T,T,T,T,T,T,T,T,T,T,
  T,T,T,T,T,T,T,T,T,T,T,T,
  T,T,T,L,L,L,L,L,T,T,T,T,
  T,T,L,L,L,L,L,L,L,T,T,T,
  T,L,L,K,L,L,L,K,L,L,T,T,
  T,L,L,L,L,L,L,L,L,L,T,T,
  T,L,L,L,L,L,L,L,L,L,T,T,
  T,T,L,L,L,L,L,L,L,T,T,T,
  T,T,T,L,L,L,L,L,T,T,T,T,
  T,T,T,T,T,T,T,T,T,T,T,T,
  T,T,T,T,T,T,T,T,T,T,T,T,
  T,T,T,T,T,T,T,T,T,T,T,T,
  T,T,T,T,T,T,T,T,T,T,T,T,
  T,T,T,T,T,T,T,T,T,T,T,T,
  T,T,T,T,T,T,T,T,T,T,T,T,
  T,T,T,T,T,T,T,T,T,T,T,T,
};

const uint16_t skull[SW*SH] PROGMEM = {
  T,T,T,T,T,T,T,T,T,T,T,T,
  T,T,T,O,O,O,O,O,T,T,T,T,
  T,T,O,O,O,O,O,O,O,T,T,T,
  T,O,E,O,O,O,O,E,O,O,T,T,
  T,O,O,O,O,O,O,O,O,O,T,T,
  T,T,O,O,O,O,O,O,O,T,T,T,
  T,T,T,O,T,T,O,T,T,T,T,T,
  T,T,T,T,T,T,T,T,T,T,T,T,
  T,T,T,T,T,T,T,T,T,T,T,T,
  T,T,T,T,T,T,T,T,T,T,T,T,
  T,T,T,T,T,T,T,T,T,T,T,T,
  T,T,T,T,T,T,T,T,T,T,T,T,
  T,T,T,T,T,T,T,T,T,T,T,T,
  T,T,T,T,T,T,T,T,T,T,T,T,
  T,T,T,T,T,T,T,T,T,T,T,T,
  T,T,T,T,T,T,T,T,T,T,T,T,
};

const uint16_t shadow[SW*SH] PROGMEM = {
  T,T,T,T,T,T,T,T,T,T,T,T,
  T,T,T,V,V,V,V,V,T,T,T,T,
  T,T,V,V,V,V,V,V,V,T,T,T,
  T,V,R,V,V,V,V,R,V,V,T,T,
  T,V,V,V,V,V,V,V,V,V,T,T,
  T,T,V,V,V,V,V,V,V,T,T,T,
  T,T,T,V,T,T,V,T,T,T,T,T,
  T,T,T,T,T,T,T,T,T,T,T,T,
  T,T,T,T,T,T,T,T,T,T,T,T,
  T,T,T,T,T,T,T,T,T,T,T,T,
  T,T,T,T,T,T,T,T,T,T,T,T,
  T,T,T,T,T,T,T,T,T,T,T,T,
  T,T,T,T,T,T,T,T,T,T,T,T,
  T,T,T,T,T,T,T,T,T,T,T,T,
  T,T,T,T,T,T,T,T,T,T,T,T,
  T,T,T,T,T,T,T,T,T,T,T,T,
};

// Lookup tables
const uint16_t* const visitorSprites[] PROGMEM = {
  mara, nell, pipwick, bramble, orrin, rowan, moth, quiet,
  spore, bone, mossback, pale, voidling, regular
};

const uint16_t* const monsterSprites[] PROGMEM = {
  slime, skull, shadow
};

// Draw a 12x16 sprite with transparency (0x0000 skipped)
inline void blit(M5GFX& d, int x, int y, const uint16_t* src) {
  for (int row = 0; row < SH; row++) {
    for (int col = 0; col < SW; col++) {
      uint16_t c = pgm_read_word(&src[row * SW + col]);
      if (c != 0x0000) {
        d.drawPixel(x + col, y + row, c);
      }
    }
  }
}

} // namespace Sprites
