GORN
====

![Gorn Creature from Star Trek](http://upload.wikimedia.org/wikipedia/en/a/a0/StarTrek-Gorn.jpg)

Gorn is a simple C++11 OpenGL 2.0 multiplatform renderer

Its main goals are:

* simplicity
* performance
* reusability
* draw call batching
* multithreading
* support for Linux, Windows, Android and iOS


## Examples

Easy to use C++ classes to wrap around the standard OpenGL API.

```c++
auto vsh = std::make_shared<Shader>(R"(
)"), ShaderType::Vertex);

auto fsh = std::make_shared<Shader>(R"(
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


