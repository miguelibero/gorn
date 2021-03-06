GORN
====

![Gorn Creature from Star Trek](http://upload.wikimedia.org/wikipedia/en/a/a0/StarTrek-Gorn.jpg)

Gorn is a simple C++11 OpenGL multiplatform renderer

Its main goals are:

* simplicity
* performance
* reusability
* support for Linux, Android, iOS and Windows (MacOS WIP)

Some functionalities that the render queue supports:

* draw call batching
* frustum culling
* drawing in separate thread (TODO)

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

auto vbo = VertexBuffer(buffer{
    //  Position     Color
        0.0f,  0.5f, 1.0f, 0.0f, 0.0f, // Vertex 1: Red
        0.5f, -0.5f, 0.0f, 1.0f, 0.0f, // Vertex 2: Green
       -0.5f, -0.5f, 0.0f, 0.0f, 1.0f  // Vertex 3: Blue
}, VertexBuffer::Usage::StaticDraw);

vao.setAttribute(vbo, AttributeDefinition("position")
    .withType(BasicType::Float)
    .withCount(2)
    .withStride(5, BasicType::Float));

vao.setAttribute(vbo, AttributeDefinition("color")
    .withType(BasicType::Float)
    .withCount(3)
    .withStride(5, BasicType::Float)
    .withOffset(2, BasicType::Float));

vao.draw(3);
```

Very extendable file sources can be defined using
tags.

```c++
Context ctx;
ctx.getFiles()
    .makeLoader<LocalFileLoader>("sprite", "../%s.png");
ctx.getImages()
    .makeDefaultDataLoader<PngImageLoader>();

auto img = ctx.getImages().load("sprite:kitten");
```

Loading assets can be done with definitions.

```c++
Context ctx;
ctx.getFiles()
    .makeLoader<LocalFileLoader>("vsh", "../%s.vsh");
ctx.getFiles()
    .makeLoader<LocalFileLoader>("fsh", "../%s.fsh");
ctx.getPrograms().getDefinitions().get("sprite")
    .withUniform(UniformKind("texture", UniformType::DiffuseTexture))
    .withShaderFile(ShaderType::Vertex, "vsh:shader")
    .withShaderFile(ShaderType::Fragment, "fsh:shader");

auto prog = ctx.getPrograms().load("sprite");
```

Support for materials, that combine a program with a list of textures
and uniform values.

```c++
Context render;
render.getMaterials().getDefinitions().get("puppy")
    .withProgram("shader")
    .withTexture(UniformType::DiffuseTexture, "puppy.png");
```

Support for render commands that are executed afterwards.

```c++
Context ctx;

ctx.getQueue().addCommand("sprite:puppy")
    .withAttribute(AttributeType::Position, buffer{
        -0.25f,  0.25f,
         0.75f,  0.25f,
         0.75f, -0.75f,
        -0.25f, -0.75f
    })
    .withAttribute(AttributeType::TexCoords, buffer{
        0.0f, 1.0f,
        1.0f, 1.0f,
        1.0f, 0.0f,
        0.0f, 0.0f
    })
    .withElements({
        0, 1, 2,
        2, 3, 0
    });

ctx.getQueue().draw();
```
