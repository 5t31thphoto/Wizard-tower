# Asset pipeline notes

The generated sheets in `art/reference/` are visual references, not sliced runtime atlases.
Before shipping them as in-game art:
1. Confirm each sprite's cell bounds and remove checkerboard/background pixels to alpha.
2. Normalize character frames to a shared baseline and frame size.
3. Split terrain into 16x16 autotile families and props into transparent objects.
4. Export RGB565 or indexed PNG/BMP assets with a manifest describing dimensions, anchors and animation frame order.
5. Keep source PNGs in the repo; generate compact device assets as a reproducible build step.

The current firmware intentionally uses native primitive drawing as a playable placeholder while the asset slicing rules are established.
