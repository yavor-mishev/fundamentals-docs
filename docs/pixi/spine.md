# Spine

[Spine](http://esotericsoftware.com/) is a 2D **skeletal animation** tool made by Esoteric Software. Instead of drawing every frame of an animation by hand (like a traditional sprite sheet), you attach images to a hierarchy of _bones_, and then animate the bones. The runtime interpolates between keyframes, so a single "walk" animation plays back smoothly at any frame rate and can be retargeted, blended, or mixed with other animations on the fly.

This gives us a few big wins over plain sprites:

- **Smaller assets** — one set of images reused across many animations, instead of a frame for every pose.
- **Smooth, runtime-driven motion** — animations are interpolated, not flipped frame-by-frame.
- **Blending and mixing** — you can crossfade from `walk` to `run`, or layer animations on separate tracks.
- **Skins** — swap the images on a skeleton (e.g. different outfits) without re-animating.
- **Meshes** — deform images with weighted vertices for soft, organic motion.

To use Spine inside Pixi.js we use the **`pixi-spine`** runtime, which knows how to load Spine exports and render them as Pixi display objects.

## Spine assets vs static assets

This is the most important thing to understand before loading anything.

A **static asset** is simple: one image file → one WebGL texture → one `Sprite`. That is the flow described in the [Pixi.js](pixijs.md) assets section.

A **Spine asset is not a single file** — it is a _set_ of files exported together from the Spine editor that only make sense as a group:

- **`*.json`** or **`*.skel`** — the **skeleton data**: the bones, slots, attachments, skins, and animations. The `.json` form is human-readable; the `.skel` form is a smaller binary equivalent. You export one or the other, not both.
- **`*.atlas`** — a text file (a **texture atlas**) describing how all the individual region images were packed onto one or more large page images: their names, positions, sizes, and rotations.
- **`*.png`** — one or more **atlas page images** holding the actual packed pixels. The `.atlas` file references these page images _by filename_.

So a single character might ship as:

```text
hero.json     # skeleton: bones, slots, animations, skins
hero.atlas    # which regions live where on the page image(s)
hero.png      # the packed image atlas
```

Two rules follow from this:

1. **They must stay together and keep their names.** The skeleton points at the `.atlas`, and the `.atlas` points at the `.png` page(s) by name. Renaming or separating them breaks the chain.
2. **You load the skeleton, not the images directly.** You hand the loader the `.json`/`.skel`, and it pulls in the `.atlas` and pages for you (see below).

## Installing pixi-spine

Install the runtime alongside Pixi.js:

```bash
npm install pixi-spine
```

```typescript
import * as PIXI from "pixi.js";
import { Spine } from "pixi-spine";
```

> **Match the runtime to your export version.** Spine's data format changes between major editor versions (3.7, 3.8, 4.0, 4.1, …). The umbrella `pixi-spine` package bundles support for recent versions automatically. If you want to keep your bundle small and you know exactly which version your project exports, you can install just the matching runtime instead, e.g. `@pixi-spine/runtime-4.1`. If a skeleton fails to load with a version error, this mismatch is almost always the cause.

Importing from `pixi-spine` also **registers a loader parser** with Pixi's Assets system as a side effect. That registration is what lets `PIXI.Assets.load()` recognise a Spine skeleton and resolve its atlas and pages — so make sure the import runs before you load any Spine assets.

## Loading Spine assets

Loading uses the same v7 [Assets API](pixijs.md) you already use for textures — you just point it at the skeleton file:

```typescript
// Loading the .json (or .skel) is enough — the loader follows it to the
// .atlas and the page image(s) automatically, because pixi-spine registered
// itself when we imported it.
await PIXI.Assets.load("assets/hero.json");
```

This is the key difference from a plain texture: **one `load` call resolves a whole multi-file skeleton**, not a single image. With a static asset you load each `.png` you need; with Spine you load the skeleton and the runtime handles the rest.

For several skeletons, use a bundle/manifest just like with sprites:

```typescript
PIXI.Assets.addBundle("characters", {
	hero: "assets/hero.json",
	enemy: "assets/enemy.json",
});

await PIXI.Assets.loadBundle("characters");
```

## Displaying a Spine object

Once loaded, the resource carries a `spineData` object. You build a `Spine` display object from it and add it to the stage like any other Pixi container:

```typescript
const resource = PIXI.Assets.get("assets/hero.json");
const hero = new Spine(resource.spineData);

hero.position.set(400, 500);
app.stage.addChild(hero);
```

A `Spine` object _is_ a Pixi display object, so the usual properties work: `position`, `scale`, `rotation`, `alpha`, `visible`, and it can be added to any `Container`.

> **Origin is different from a sprite.** A sprite defaults to an anchor at its top-left, but a Spine skeleton is positioned by its **root bone in the setup pose** — which the artist often places at the character's feet or hips, not the top-left of an image. So a freshly-added Spine object usually needs its `position` set to where that root bone should sit, and there is no `anchor` to offset it.

## Playing animations

A `Spine` object has an **AnimationState** (`hero.state`) built around numbered **tracks**. Each track plays one animation at a time; multiple tracks let you layer animations (e.g. body on track 0, facial expression on track 1).

```typescript
// setAnimation(trackIndex, animationName, loop)
hero.state.setAnimation(0, "walk", true);
```

You can queue an animation to play after the current one finishes with `addAnimation`:

```typescript
// addAnimation(trackIndex, animationName, loop, delay)
// delay 0 means "start when the previous animation on this track ends"
hero.state.setAnimation(0, "jump", false);
hero.state.addAnimation(0, "walk", true, 0);
```

### Mixing (crossfades)

By default switching animations snaps instantly. Set a **mix duration** to crossfade between two named animations:

```typescript
// Blend over 0.2s when going from walk -> run
hero.stateData.setMix("walk", "run", 0.2);

// Or a default applied to every transition that has no explicit mix:
hero.stateData.defaultMix = 0.2;
```

### Listening for animation events

Spine fires lifecycle callbacks, plus any custom **events** the artist keyed into the timeline (handy for footstep sounds, hit frames, etc.):

```typescript
hero.state.addListener({
	start: (entry) => {},
	complete: (entry) => {
		console.log(`${entry.animation.name} finished`);
	},
	event: (entry, event) => {
		console.log(`custom event: ${event.data.name}`);
	},
});
```

## Skins and attachments

A **skin** is a named set of attachments — the images bound to each slot. Skins let one skeleton wear different looks (outfits, color variants) without separate animations:

```typescript
hero.skeleton.setSkinByName("blue");
// Re-apply the setup pose so the new attachments take effect cleanly:
hero.skeleton.setSlotsToSetupPose();
```

You can also build a combined skin at runtime from several source skins (e.g. base body + hat + weapon) using `Skin.addSkin`, then apply that. This is how you mix-and-match equipment on one character.

## Configuring / common tweaks

**Scaling.** Spine art is often authored large; scale it like any container:

```typescript
hero.scale.set(0.5);
```

**Update mode.** By default a Spine object advances itself every frame (`hero.autoUpdate = true`). If you want to drive it manually — for slow-motion, pausing, or syncing to your own clock — turn that off and update it yourself from the [ticker](pixijs.md):

```typescript
hero.autoUpdate = false;

app.ticker.add((delta) => {
	// delta is in frames; Spine expects seconds
	hero.update(delta / 60);
});
```

**Bounds.** Because the origin sits on the root bone, use the bounds to lay a skeleton out or size a hit area:

```typescript
const bounds = hero.getBounds(); // axis-aligned bounds in Pixi space
```

**Debug rendering.** While rigging or debugging, you can turn on visualisation of bones, slots, and meshes:

```typescript
hero.drawDebug = true;
```

## Resources

- [Spine official site & user guide](http://esotericsoftware.com/spine-user-guide)
- [pixi-spine on GitHub](https://github.com/pixijs/spine)
- [Pixi.js Assets API](pixijs.md) — the same loader used here for static assets
