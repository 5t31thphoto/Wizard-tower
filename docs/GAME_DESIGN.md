# Wizard's Keep — game design checkpoint

## Pillars
1. The shop's visiting cast is the narrative center.
2. Cozy, readable top-down pixel art: approachable scale and clear silhouettes.
3. Daytime choices feed nighttime defense.
4. Small world, expanding systems; no sprawling menu maze.

## Core loop
Gather → cultivate → craft → serve visitors → invest in defenses → survive a raid → recover unusual materials → unlock more recipes and visitors.

## Visitor model
Each visitor is a recurring identity with a role, greeting, request, reward and a future relationship/story hook. Current checkpoint has eight data-defined visitors. Planned next: persistent affinity, schedules, multi-visit story arcs, cross-character references, special commissions and visitor-specific unlocks.

## Systems in this checkpoint
- Resources: gold, herbs, wood, mushrooms, seeds, potions.
- Crafting: moonroot tonic.
- Garden: planting and harvesting.
- Shop: fulfill requests or make a small fallback sale.
- Defense: walls and ward turrets.
- Night: active ward casting and survival timer.
- Persistence: day, inventory, reputation and defense upgrades.

## Next implementation targets
- Replace procedural placeholder shapes with normalized 16x16 / 16x24 tile and sprite atlases.
- Split visitor portraits and NPC animation frames from supplied concept sheets.
- Add dialogue choice trees and persistent character affinity.
- Add real-time shop visitor queue and commissions.
- Add spatial garden plots and growth stages.
- Add multiple enemy types, lanes, traps and wave composition.
- Add recipe discovery, automation, save versioning and SD-card export.
