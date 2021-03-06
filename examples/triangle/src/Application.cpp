#include <gorn/gorn.hpp>
#include <cmath>
#include <iostream>
#if GORN_PLATFORM_ANDROID
#include <android/log.h>
#endif

class TriangleApplication : public gorn::Application
{
    gorn::Context _ctx;
    gorn::VertexArray _vao;
    double _time;

public:

    TriangleApplication();

    void load() override;
    void update(double dt) override;
    void draw() override;
    void touch(const glm::vec2& p) override;
};

namespace gorn
{
    std::unique_ptr<Application> main()
    {
        return std::unique_ptr<Application>(new TriangleApplication());
    }
}

TriangleApplication::TriangleApplication():
_time(0.0f)
{
}

void TriangleApplication::load()
{
#if GORN_PLATFORM_LINUX || GORN_PLATFORM_WINDOWS
    _ctx.getFiles()
        .makeDefaultLoader<gorn::LocalFileLoader>("../assets/%s");
#elif GORN_PLATFORM_ANDROID
    _ctx.getFiles()
        .makeDefaultLoader<gorn::AssetFileLoader>("%s");
#elif GORN_PLATFORM_IOS
    _ctx.getFiles()
        .makeDefaultLoader<gorn::BundleFileLoader>("%s");
#endif

    _vao.setProgram(_ctx.getPrograms().load("shader"));

    auto vbo = std::make_shared<gorn::VertexBuffer>(buffer{
     //  Position     Color 
         0.0f,  0.5f, 1.0f, 0.0f, 0.0f, // Vertex 1: Red
         0.5f, -0.5f, 0.0f, 1.0f, 0.0f, // Vertex 2: Green
        -0.5f, -0.5f, 0.0f, 0.0f, 1.0f  // Vertex 3: Blue
    }, gorn::VertexBuffer::Usage::StaticDraw);

    _vao.setAttribute(vbo, gorn::VertexAttributeDefinition("position")
        .withBasicType(gorn::BasicType::Float)
        .withCount(2)
        .withStride(5, gorn::BasicType::Float));
        
    _vao.setAttribute(vbo, gorn::VertexAttributeDefinition("color")
        .withBasicType(gorn::BasicType::Float)
        .withCount(3)
        .withStride(5, gorn::BasicType::Float)
        .withOffset(2, gorn::BasicType::Float));
}

void TriangleApplication::touch(const glm::vec2& p)
{
    std::cout << "touch " << p.x << " " << p.y << std::endl;
#if GORN_PLATFORM_ANDROID
    __android_log_print(ANDROID_LOG_VERBOSE, "gorn_triangle",
        "touch %f %f", p.x, p.y);
#endif
     _vao.getProgram()->setUniformValue("touchPos", p);
}

void TriangleApplication::update(double dt)
{
    _time += dt;
}

void TriangleApplication::draw()
{
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    _vao.getProgram()->setUniformValue("timeSin", (float)sin(_time));
    _vao.draw(3);
}

