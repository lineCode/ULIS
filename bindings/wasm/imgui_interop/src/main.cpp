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

bool g_done = false;
SDL_Window* g_window;
SDL_GLContext g_glcontext;

int g_width;
int g_height;
GLuint g_texture;
bool InitTexture()
{
    // Load from file
    int image_width = 256;
    int image_height = 256;
    unsigned char* image_data = new unsigned char[ image_width * image_height * 4 ];
    for( int i = 0; i < 256 * 256 * 4; ++i ) {
        image_data[i] = 255;
    }

    // Create a OpenGL texture identifier
    GLuint image_texture;
    glGenTextures(1, &image_texture);
    glBindTexture(GL_TEXTURE_2D, image_texture);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image_width, image_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image_data);
    glGenerateMipmap(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 0);

    g_texture = image_texture;
    g_width = image_width;
    g_height = image_height;

    delete [] image_data;

    return true;
}

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

    ImGui::SetNextWindowPos(ImVec2(0,0));
    ImGui::Begin("OpenGL Texture Test");
    ImGui::Text("size = %d x %d", g_width, g_height);
    ImGui::Image((void*)(intptr_t)g_texture, ImVec2(256, 256));
    ImGui::End();

    int w, h;
    SDL_GL_GetDrawableSize(g_window, &w, &h);
    glViewport(0, 0, w, h);
    glClearColor(0.2, 0.2, 0.2, 1.0f);
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

    InitTexture();
    runMainLoop();

    destroySDL();

    return EXIT_SUCCESS;
}
