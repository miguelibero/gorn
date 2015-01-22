GORN
====

![Gorn Creature from Star Trek](http://upload.wikimedia.org/wikipedia/en/a/a0/StarTrek-Gorn.jpg)

Gorn is a simple C++11 OpenGL multiplatform renderer

Its main goals are:

* simplicity
* performance
* reusability
* draw call batching (TODO)
* drawing in separate thread (TODO)
* support for Linux, Windows, Android and iOS (TODO)

## Examples

Easy to use C++ classes to wrap around the standard OpenGL API.

```c++
auto vsh = std::make_shared<Shader>(R"(#version 100

precision highp float;

attribute vec3 color;
attribute vec2 position;

uniform float timeSin;

varying vec3 Color;

void main()
{
    Color = color;
    gl_Position = vec4(position, 0.0, 0.2*timeSin+1.0);
}
)"), ShaderType::Vertex);

auto fsh = std::make_shared<Shader>(R"(#version 100

precision highp float;

uniform float timeSin;

varying vec3 Color;

void main()
{
    gl_FragColor = vec4(Color, 1.0);
}
)"), ShaderType::Fragment);

auto vao = VertexArray()
vao.setProgram(Program(vsh, fsh));

auto vbo = VertexBuffer(Data{
    //  Position     Color 
        0.0f,  0.5f, 1.0f, 0.0f, 0.0f, // Vertex 1: Red
        0.5f, -0.5f, 0.0f, 1.0f, 0.0f, // Vertex 2: Green
       -0.5f, -0.5f, 0.0f, 0.0f, 1.0f  // Vertex 3: Blue
}, VertexBuffer::Usage::StaticDraw);

vao.setAttribute(vbo, AttributeDefinition("position")
    .withType(GL_FLOAT)
    .withCount(2)
    .withStride(5*sizeof(GLfloat)));
            
vao.setAttribute(vbo, AttributeDefinition("color")
    .withType(GL_FLOAT)
    .withCount(3)
    .withStride(5*sizeof(GLfloat))
    .withOffset(2*sizeof(GLfloat)));

vao.draw(3);
```

Very extendable file sources can be defined using
tags.

```c++
RenderContext render;
render.getFiles()
    .addLoader<LocalFileLoader>("sprite", "../%s.png");

auto img = render.getImages().load("sprite:kitten");
```

Loading assets can be done with definitions.

```c++
RenderContext render;
render.getFiles()
    .addLoader<LocalFileLoader>("vsh", "../%s.vsh");
render.getFiles()
    .addLoader<LocalFileLoader>("fsh", "../%s.fsh");
render.getPrograms().getDefinitions().get("sprite")
    .withUniform("texture", UniformKind::Texture0)
    .withShaderFile(ShaderType::Vertex, "vsh:shader")
    .withShaderFile(ShaderType::Fragment, "fsh:shader");

auto prog = render.getPrograms().load("sprite");
```

Support for materials, that combine a program with a list of textures
and uniform values.

```c++
RenderContext render;
render.getMaterials().getDefinitions().get("puppy")
    .withProgram("shader")
    .withTexture(UniformKind::Texture0, "puppy.png");
```

Support for render commands that are executed afterwards.

```c++
RenderContext render;
render.getQueue().addCommand("sprite:kitten")
    .withAttribute(AttributeKind::Position, {
        -0.75f,  0.75f,
         0.25f,  0.75f,
         0.25f, -0.25f,
        -0.75f, -0.25f,
         0.66f
    }, GL_FLOAT, 2)
    .withAttribute(AttributeKind::TexCoords, {
        0.0f, 1.0f,
        1.0f, 1.0f,
        1.0f, 0.0f,
        0.0f, 0.0f
    }, GL_FLOAT, 2)
    .withElements({
        0, 1, 2,
        2, 3, 0
    }, GL_UNSIGNED_INT, 6);

render.getQueue().addCommand("sprite:puppy")
    .withAttribute(AttributeKind::Position, {
        -0.25f,  0.25f,
         0.75f,  0.25f,
         0.75f, -0.75f,
        -0.25f, -0.75f
    }, GL_FLOAT, 2)
    .withAttribute(AttributeKind::TexCoords, {
        0.0f, 1.0f,
        1.0f, 1.0f,
        1.0f, 0.0f,
        0.0f, 0.0f
    }, GL_FLOAT, 2)
    .withElements({
        0, 1, 2,
        2, 3, 0
    }, GL_UNSIGNED_INT, 6);

render.getQueue().draw();
```

