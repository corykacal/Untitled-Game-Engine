--Untitled Game Engine--

Making an OpenGL game engine in c++ that will feature extensive abstraction from the OpenGL API and many procedural features.

Current features I am working on from most important to least:
 - Dynamic buffer allocation and arrangement
   - the ability to just send in models and delete models and the renderer will take care of everything
 - Chunk generation using perlin noise
 - Increasing efficiency of code by using multi-threading for CPU side buffer building code
 - Implementing procedural tree generation using space colonization algorithm. 
 - Implementing normal maps and voxel-izing them

Things I want to do and make sense but am kicking down the road:
 - Actual game loop
 - Actual game things like collision
 - Any kind of gameplay at all


Some hills with funny squares:

![picture of perlin noise hills](readmeResources/funnyhills.png)