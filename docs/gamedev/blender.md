# Blender

Blender is an open source 3D modeling and animation software. It is free to download and use for any purpose.

Blender is a powerful tool for creating 3D models, animations, visual effects, and more. It is widely used in the film, gaming, and design industries. Here I'll be covering the basics of Blender to get you started. 

Modes:
	- object mode: move, rotate and scale objects
		- Shift + A to add an object
	- edit mode: lets you modify the geometry of a single object
		- can edit via verticies, edges or faces
	- TAB switches between object and edit mode
Viewport shading:
	- wireframe
	- solid (default)
	- material preview
	- rendered
	
Modeling
1. Mesh anatomy and common terminology
	 - add menu Shift + a
	 - edit mode is where we can modify shapes
	 - a mesh object is made of 3 elements: verticies, edges, faces(polygon)
		- a face made out of:
			- 3 verticies - tri
			- 4 verticies - quad
			- 4< - ngon
	- low poly vs high poly: how many faces/ polygons a model has. The more faces a model has the more detail you can create
	- topology: the wireframe of a mesh
	- artefact: an inconsistency or unwanted behavior
	- everything's a triangle!
	- normals: the direction of a face or vertex.
		- faces: every face has two sides - outside and inside normals
		- vertex: the average of the angle two adjecent faces make
		- keep your outside normals in the direction of the rendering
Drivers: used to get one obj to affect another obj
	- example: an obj location can affect another obj's rotation
Modifiers: affects that you can add to your models that change the way they look
	- using modifiers is a non-destructive workflow because you retain the original mesh for editing
	
	- displace: moves verticies up/down. Adding texture/image  can affect what verticies get moved and to what extent which is actually what changes the mesh.