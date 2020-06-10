#include <imgui.h>
#include "imgui_impl_sdl.h"

#include <SDL.h>
#ifdef __APPLE__
#include <OpenGL/gl.h>
#include <OpenGL/glext.h>
#define glGenVertexArrays glGenVertexArraysAPPLE
#define glBindVertexArrays glBindVertexArraysAPPLE
#define glGenVertexArray glGenVertexArrayAPPLE
#define glBindVertexArray glBindVertexArrayAPPLE
#else
#include <SDL_opengles2.h>
#endif

#include <emscripten.h>
#include <GLES3/gl3.h>

#include <math.h>
#include <iostream>
#include <array>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

uint32_t g_shaderProgram;
int32_t g_attribLocationPosition;
int32_t g_colorUniformLocation;
uint32_t g_vbo, g_vao;
std::array<float,9> g_vertices = {
    -0.5f, -0.5f, 0.0f, // left
    0.5f, -0.5f, 0.0f, // right
    0.0f,  0.5f, 0.0f  // top
};
bool g_done = false;
SDL_Window* g_window;
SDL_GLContext g_glcontext;

void main_loop()
{
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        ImGui_ImplSdl_ProcessEvent(&event);
        if (event.type == SDL_QUIT)
            g_done = true;
    }

    ImGui_ImplSdl_NewFrame(g_window);

    ImGui::SetNextWindowPos(ImVec2(10,10));
    ImGui::Begin("Demo", nullptr, ImGuiWindowFlags_AlwaysAutoResize);
    ImGui::Text("Just a WebAssembly demo.");
    ImGui::SameLine();
    if(ImGui::Button("View on Github"))
    {
        emscripten_run_script( "window.location.href = 'https://github.com/schteppe/imgui-wasm';" );
    }

    static glm::vec3 color(0.7f, 0.3f, 0.2f);
    static glm::vec3 bgcolor(0.2f);
    ImGui::ColorEdit3( "Triangle", glm::value_ptr(color) );
    ImGui::ColorEdit3( "Background", glm::value_ptr(bgcolor) );
    ImGui::End();

    static bool g_show_test_window = true;
    ImGui::ShowDemoWindow(&g_show_test_window);

    int w, h;
    SDL_GL_GetDrawableSize(g_window, &w, &h);
    glViewport(0, 0, w, h);
    glClearColor(bgcolor.x, bgcolor.y, bgcolor.z, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    ImGui::Render();
    SDL_GL_SwapWindow(g_window);
}

bool initSDL()
{
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        std::cerr << "Error: %s\n" << SDL_GetError() << '\n';
        return false;
    }

    // Setup window
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
    SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
    SDL_DisplayMode current;
    SDL_GetCurrentDisplayMode(0, &current);
    g_window = SDL_CreateWindow(
        "ImGUI / WASM / WebGL demo", // title
        SDL_WINDOWPOS_CENTERED, // x
        SDL_WINDOWPOS_CENTERED, // y
        1280, 720, // width, height
        SDL_WINDOW_OPENGL|SDL_WINDOW_RESIZABLE|SDL_WINDOW_ALLOW_HIGHDPI // flags
    );
    g_glcontext = SDL_GL_CreateContext(g_window);

    ImGui_ImplSdl_Init(g_window);

    return true;
}

void destroySDL()
{
    ImGui_ImplSdl_Shutdown();
    SDL_GL_DeleteContext(g_glcontext);
    SDL_DestroyWindow(g_window);
    SDL_Quit();
}

void runMainLoop()
{
    emscripten_set_main_loop(main_loop, 0, 1);
}

int main(int, char**)
{
    if(!initSDL())
    {
        return EXIT_FAILURE;
    }

    runMainLoop();

    destroySDL();

    return EXIT_SUCCESS;
}
