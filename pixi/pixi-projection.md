# pixi-projection

pixi-projection is a plugin for Pixi.js that adds support for 2D projections. It allows you to create 3D-like effects in your 2D games and applications. The way it achieves this is by adding a new `ProjectionSprite` class that extends the regular `Sprite` class. This new class has additional properties and methods that allow you to manipulate the sprite in 3D space.

### Camera3d

The camera is the main component of the projection system. It defines the perspective and the view of the scene. The `Camera3d` class allows you to set the position, rotation, and field of view of the camera. You can also use it to convert between screen coordinates and world coordinates.

- `position`: The position of the camera in 3D space.
- `setPlanes(fov, near, far)`: Sets the **field of view** and the **near** and **far** clipping planes. The field of view is the angle of the camera's view, while the near and far planes define the range of distances that will be rendered. Anything outside of this range will not be visible (below near and above far).
- `euler`: The rotation of the camera in Euler angles (x, y, z). This allows you to rotate the camera around its axes. x is the rotation around the horizontal axis, y is the rotation around the vertical axis, and z is the rotation around the depth axis.

### Managing the layer order of 3D objects

One of the ways to manipulate what is in front and what is behind is to add the objects according to their desired order (first added = behind, last added = in front).

A maybe better way is to enable the `camera.sortableChildren` property which will allow us to set the `zIndex` of each object and manioulate them this way
