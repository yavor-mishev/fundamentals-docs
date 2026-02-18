# Pixi layers

Pixi v7 or lower. Pixi v8 has a built in layer system via the RenderLayer class!

Pixi Layers is a pixi plugin that provides an advanced display list management system through a layer-based approach that separates rendering order from scene hierarchy. It allows you to create multiple layers that can be rendered independently, giving you more control over the rendering process and enabling features like parallax scrolling, depth sorting, and more.

By default PIxi renders objects in the order they were added to the stage. With Pixi Layers, you can create multiple layers and assign display objects to specific layers, allowing you to control the rendering order without changing the scene hierarchy. This is particularly useful for complex scenes where you want to manage different types of objects (e.g., background, characters, UI) separately.

Its important to remember that groups are basically just tags/labels that you can assing to display objects. You need layers to actually render the objects with the group's tag. You can also have multiple layers in a group. Or you can ommit the group all together and just use layers, but with groups the render order seems to be more predictable and easier to manage plus we get more flexibility with the zIndex and sorting options.

```ts
import * as PIXI_DISPLAY from "@pixi/layers";

// creating a group with a custom zIndex
const group = new PIXI_DISPLAY.Group(1, true);

// creating a layer for the group
const layer = new PIXI_DISPLAY.Layer(group);
```
