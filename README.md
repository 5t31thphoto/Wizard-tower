# presented by:

```
 __      __      ___            
|__) /\ (_  /\ |  |             
|__)/--\__)/--\|__|             
                                
 __ __  _____     __  __     __ 
(_ /  \|_  | |  |/  \|__)|_/(_  
__)\__/|   | |/\|\__/| \ | \__) 
                                
```

a new game called

```
 +-++-++-++-++-++-+ +-++-++-++-+
 |W||I||Z||A||R||D| |K||E||E||P|
 +-++-++-++-++-++-+ +-++-++-++-+
```

**M5Stack Core2 · Native ESP32**

A cozy top-down woodland wizard RPG with a character-driven shop loop by day and a compact keep-defense encounter by night.

## Current checkpoint (0.2.0)
Playable and noticeably more alive. Includes:
- Full day/night loop with shop, lab, garden, keep upgrades and journal.
- 14 visitors with reputation-gated progression (locals → weirdos → skeleton mage, fungus herbalist, void client…).
- Specific request types, better rewards, and tiny procedural character sprites.
- Growing garden stages, stronger night scaling, richer flavor text.
- Persistent save of all core stats + garden stage.
- Native M5Unified 320×240 rendering, touch + A/B/C buttons.
- Still using smart procedural drawing (real sprite atlases are next).

## Controls
- Touch the six bottom tabs to move between areas.
- Woods: tap the clearing to gather; tap `OPEN THE SHOP` to visit the shop.
- Shop: tap `TRADE / HELP` to serve the visitor.
- Lab: brew a potion or research.
- Garden: plant or harvest.
- Keep: buy walls or ward turrets.
- Button A: Woods / cast ward; B: Shop / end night; C: Lab / end night.
- The clearing advances to night automatically after a period of play. You can also use C in the clearing to begin a raid.

## Build
Install PlatformIO Core and run:
```bash
pio run -e m5stack-core2
```
The CI workflow builds and merges firmware. No PlatformIO installation is bundled.

## Firmware layout
- Bootloader: `0x1000`
- Partition table: `0x8000`
- `boot_app0.bin`: `0xE000`
- Application: `0x10000`
- Merged image: `0x0`

## Art
`art/reference/` contains the supplied/generated visual direction sheets. They are concept references, not runtime atlases. The current game draws placeholder pixel-art scenery procedurally so the game logic can be exercised before the production atlas is sliced and normalized.

## Brand
Basalt Softworks · Mantis palette accents · cozy woodland magic.
