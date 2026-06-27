# Pixi.js

Here is a very cool step by step tutorial on Pixi.js. I suggest whoever is reading this have a look at this tutorial as well: [Pixi.js Elementals](https://www.pixijselementals.com/#introduction)

Pixi.js is a powerful 2D rendering library that allows you to create rich, interactive graphics for the web. It provides a fast and flexible way to render sprites, text, and other graphical elements using WebGL or Canvas.

### How to include Pixi.js in your project

1. You can include Pixi.js in your project using a CDN:

```html
<script src="https://pixijs.download/release/pixi.min.js"></script>
```

2. Install it via npm:

```bash
npm install pixi.js
```

### Basic usage

To use Pixi.js, first you need to create an application. This will set up the renderer and the main stage for you:

```javascript
const app = new PIXI.Application({
	width: 800,
	height: 600,
	backgroundColor: 0x1099bb,
});
```

Then, you can add the canvas to your HTML document:

```javascript
document.body.appendChild(app.view);
```

### The renderer

Pixi.js automatically detects whether the browser supports WebGL and falls back to Canvas if necessary. The renderer class is responsible for rendering the stage and its children. You can access it via `app.renderer`. It basically controls all the low-level rendering details, such as background color, resolution, antialiasing, the size of the canvas, and more. For example, to change the background color of the renderer, you can do:

```typescript
// Set the background color to red
app.renderer.backgroundColor = 0xff0000;
```

## Adding images to the app

Pixi uses a tree-based scene graph with the `stage` being the **root container**.Everything we want to add from now on in our app has to be added to the `stage`. We can access it using the `app.stage` property.

```typescript
app.stage;
```

The `stage` is a Pixi Container object, which means it can hold other display objects, such as sprites, graphics, text, other containers and more.

Within the parent-child relationship between objects, when a parent moves, rotates or changes alpha (transparency 0-1), all its children inhgerit those changes. This allows us to create complex scenes and animations by grouping objects together.

The render order of objects depends on the order they were added to the stage

And its important to remember that chiled positions are based on the parent container, not the stage. So if you move a container, all its children will move with it, but their local positions will remain the same.

### Sprites

What we put inside our `stage` container are special image objects called _sprites_. Sprites are just images that we can control via code. They have properties like position, scale, rotation, and more.

Pixi has a Sprite class that we can use to create sprites. There are 3 main ways to create a sprite:

- from a single image file
- from a sub-image on a tileset
- from a texture atlas

#### Assets system (loading assets)

Before you can make a sprite display an image, you need to convert an ordinary image file into a WebGL texture. For this we use the Assets API, which is a powerful and flexible way to load and manage assets in Pixi.js. It supports loading images, JSON files, audio files, and more. You can use it like this:

```typescript
await PIXI.Assets.load("path/to/image.png"); // single texture
await PIXI.Assets.load({"path/to/image.png", "path/to/image2.png"}); // multiple textures
// using a manifest file (JSON)
PIXI.Assets.addBundle("cards", {
    "card1": "path/to/card1.png",
    "card2": "path/to/card2.png",
    // ...
});
await PIXI.Assets.loadBundle("cards"); // load the bundle
```

#### Creating a sprite and adding it to the stage

To create a new sprite and add it to the app we use the `new Sprite()` call and add it to the stage.

```typescript
let player: PIXI.Sprite;
player = new PIXI.Sprite(PIXI.Assets.get("path/to/image.png" | "card1" | texture object));
```

#### Removing a sprite from the stage

To remove a sprite from the stage, you can use the `removeChild` method of the stage:

```typescript
app.stage.removeChild(player);
```

You couls also set the `visible` property of the sprite to `false` to hide it without removing it from the stage which is usually simpler and more efficient:

```typescript
player.visible = false;
```

#### Positioning sprites

To reposition a sprite, you can set its `x` and `y` properties. By default, the position of a sprite is (0, 0), which means it is located at the top-left corner of the stage. To move it to a different position, you can do:

```typescript
player.x = 100; // Move the sprite 100 pixels to the right
player.y = 150; // Move the sprite 150 pixels down

//or you can set both properties at once using the `position` property, which is a Point object:
player.position.set(100, 150);
```

#### Size and scale

To change the size of a sprite, you can set its `width` and `height` properties. However, this will stretch the image and may cause distortion. A better way to resize a sprite is to use the `scale` property, which allows you to scale the sprite proportionally without distorting it:

```typescript
player.scale.set(2); // Scale the sprite to twice its original size
player.scale.set(0.5); // Scale the sprite to half its original size
```

#### Rotation

To rotate a sprite, you can set its `rotation` property. The rotation is measured in radians, not degrees. For example, to rotate a sprite 90 degrees clockwise, you would do:

```typescript
player.rotation = Math.PI / 2; // Rotate 90 degrees clockwise
```

All rotations are based on the anchor point of the sprite, which is the point around which the sprite rotates and scales. By default, the anchor point is at the top-left corner of the sprite (0, 0). You can change the anchor point using the `anchor` property:

```typescript
player.anchor.set(0.5); // set anchor point to the middle of the sprite
player.rotation = Math.PI / 2; // Rotate 90 degrees clockwise around the anchor point
```

#### Moving sprites

We make sprites move by using a game loop (looping function). Any code we put in that function will update 60 times per second, which is the default frame rate of Pixi.js. To create a game loop, we can use the `ticker` property of the application:

```typescript
app.ticker.add((delta) => {
	// This code will run every frame
	player.x += 1 * delta; // Move the player 1 pixel to the right every frame
});
```

TODO: Velocity and acceleration, Game states, Keyboard movement

#### Grouping sprites

Like we mentioned before, we have an object called `Container` that lets you group multiple sprites together.

```typescript
const cat = new PIXI.Sprite(id["cat.png"]);
cat.position.set(16, 16);
const dog = new PIXI.Sprite(id["dog.png"]);
dog.position.set(32, 32);
const bird = new PIXI.Sprite(id["bird.png"]);
bird.position.set(64, 64);
const animals = new PIXI.Container();
animals.addChild(cat, dog, bird);
app.stage.addChild(animals);
```

Now youcan treat this container as a single unit/sprite without a texture. You can move, scale, rotate, and change the alpha of the container and all its children will be affected. Here is how you can check the sprites in a container:

```typescript
console.log(animals.children); // [cat, dog, bird]
```

#### Local and global positions

Each sprites x and y position is relative to the groups top left corner. Thats the sprites local position.

```typescript
animals.position.set(100, 100);
console.log(cat.x, cat.y); // 16, 16
console.log(animals.toGlobal(cat.position)); // 116, 116
```

TODO: ParticleContainer

### Pixi's Graphics

TODO

### Displaying text

TODO

### Colision detection

TODO

### Interactivity

[eventMode](https://pixijs.download/v7.x/docs/PIXI.DisplayObject.html#eventMode)

For the stage to accept interactivity, we need to set the `eventMode` property to one of these values: `none` | `passive` | `auto` | `static` | `dynamic`. For example:

```typeScript
app.stage.eventMode = "static";
```

Then we can listen for events on the stage or any display object:

```typescript
// mouse pointer move event
app.stage.on("pointermove", movePlayer);

function movePlayer(e: PIXI.InteractionEvent) {
	const pointerPosition = e.global;
	player.x = pointerPosition.x;
	player.y = pointerPosition.y;
}
```

Or we can move our player with the keyboard:

```typescript

```
