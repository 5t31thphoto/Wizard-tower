# Wizard's Keep
**Basalt Softworks · M5Stack Core2 · Native ESP32 game**

A cozy top-down woodland wizard RPG with a character-driven shop loop by day and a compact keep-defense encounter by night.

## Current checkpoint
This is a playable foundation, not a finished content-complete game. It includes:
- Daytime clearing, shop, alchemy lab, garden, keep upgrades and journal screens.
- Eight recurring visitors with distinct requests and rewards.
- Resource gathering, potion crafting, planting/harvesting, sales, reputation and upgrades.
- Night raid screen with direct ward casting, turret contribution and keep HP.
- Persistent core economy/progression using ESP32 Preferences.
- Native M5Unified rendering at 320x240 with touch and A/B/C controls.
- GitHub Actions build, merged firmware artifact and Pages installer scaffold.

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
