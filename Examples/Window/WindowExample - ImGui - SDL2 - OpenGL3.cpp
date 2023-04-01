#include <GL/glew.h>
#include <SDL.h>
#include <SDL_opengl.h>

#include <fstream>
#include <iostream>

#include "imgui.h"
#include "imgui_impl_opengl3.h"
#include "imgui_impl_sdl2.h"

// OpenGL 3.0 or higher
const char* glsl_version = "#version 130";

void scaleImGuiStyle(float scaleFactor = 2.5f) {
    ImGuiStyle& style = ImGui::GetStyle();
    style.ScaleAllSizes(scaleFactor);

    ImGuiIO& io        = ImGui::GetIO();
    io.FontGlobalScale = scaleFactor;
}

void setupImGui(SDL_Window* window, SDL_GLContext context) {
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGui::StyleColorsDark();
    ImGui_ImplSDL2_InitForOpenGL(window, context);
    ImGui_ImplOpenGL3_Init(glsl_version);
}

int main(int, char**) {
    std::ofstream file;
    file.open("log.txt");
    std::streambuf* sbuf = std::cout.rdbuf();
    std::cout.rdbuf(file.rdbuf());

    int monitor_index = 0;
    SDL_Init(SDL_INIT_VIDEO);
    SDL_DisplayMode DM;
    SDL_GetDesktopDisplayMode(monitor_index, &DM);
    int true_screen_width  = DM.w;
    int true_screen_height = DM.h;
    std::cout << "Screen width: " << true_screen_width << std::endl;

    SDL_Window* window = SDL_CreateWindow(
        "ImGui Transparent OpenGL Window Example", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        true_screen_width - 1, true_screen_height - 1, SDL_WINDOW_OPENGL | SDL_WINDOW_ALLOW_HIGHDPI
    );
    std::cout << "Window created" << std::endl;

    if (!window) {
        std::cout << "Failed to create SDL window!" << std::endl;
        return -1;
    }

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
    SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

    SDL_GLContext gl_context = SDL_GL_CreateContext(window);
    std::cout << "GL context created" << std::endl;

    GLenum err = glewInit();
    if (err != GLEW_OK) {
        std::cout << "Failed to initialize GLEW!" << std::endl;
        return -1;
    }

    setupImGui(window, gl_context);
    scaleImGuiStyle();

    ImVec4 clear_color = ImVec4(0.0f, 0.0f, 0.0f, 0.0f);  // Set clear color to transparent

    bool readyToClose = false;
    while (!readyToClose) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            ImGui_ImplSDL2_ProcessEvent(&event);
            if (event.type == SDL_QUIT) {
                readyToClose = true;
            }
        }

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplSDL2_NewFrame(window);
        ImGui::NewFrame();

        ImGui::Begin("Sample Window");
        if (ImGui::BeginTabBar("MyTabBar")) {
            if (ImGui::BeginTabItem("Button")) {
                if (ImGui::Button("Click me!")) readyToClose = true;
                ImGui::EndTabItem();
                if (ImGui::BeginTabItem("Text Box")) {
                    static char buf[256] = "";
                    ImGui::InputText("Enter some text", buf, IM_ARRAYSIZE(buf));
                    ImGui::Text("You entered: %s", buf);
                    ImGui::EndTabItem();
                }
                ImGui::EndTabBar();
            }
            ImGui::End();

            ImGui::Render();
            int display_w, display_h;
            SDL_GetWindowSize(window, &display_w, &display_h);
            glViewport(0, 0, display_w, display_h);
            glClearColor(clear_color.x, clear_color.y, clear_color.z, clear_color.w);
            glClear(GL_COLOR_BUFFER_BIT);

            ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
            SDL_GL_SwapWindow(window);
        }
    }

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplSDL2_Shutdown();
    ImGui::DestroyContext();

    SDL_GL_DeleteContext(gl_context);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
