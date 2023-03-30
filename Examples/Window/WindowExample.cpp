#include <GL/gl3w.h>
#include <GLFW/glfw3.h>
#include <Windows.h>

#include <fstream>
#include <iostream>

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

// OpenGL 3.0 or higher
const char* glsl_version = "#version 130";

void setupImGui(GLFWwindow* window) {
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init(glsl_version);
}

void GetMonitorRealResolution(HMONITOR monitor, int* pixelsWidth, int* pixelsHeight) {
    MONITORINFOEX info = {sizeof(MONITORINFOEX)};
    GetMonitorInfo(monitor, &info);
    DEVMODE devmode = {};
    devmode.dmSize  = sizeof(DEVMODE);
    EnumDisplaySettings(info.szDevice, ENUM_CURRENT_SETTINGS, &devmode);
    *pixelsWidth  = devmode.dmPelsWidth;
    *pixelsHeight = devmode.dmPelsHeight;
}

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
    std::ofstream file;
    file.open("log.txt");
    std::streambuf* sbuf = std::cout.rdbuf();
    std::cout.rdbuf(file.rdbuf());

    HMONITOR primary_monitor = MonitorFromPoint({0, 0}, MONITOR_DEFAULTTOPRIMARY);
    int*     pixelsWidth     = new int;
    int*     pixelsHeight    = new int;
    GetMonitorRealResolution(primary_monitor, pixelsWidth, pixelsHeight);
    int true_screen_width  = *pixelsWidth;
    int true_screen_height = *pixelsHeight;
    std::cout << "Screen width: " << true_screen_width << std::endl;

    if (!glfwInit()) {
        fprintf(stderr, "Failed to initialize GLFW\n");
        return 1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_TRANSPARENT_FRAMEBUFFER, GLFW_TRUE);  // Enable transparency
    glfwWindowHint(GLFW_DECORATED, GLFW_FALSE);               // No title bar
    // glfwWindowHint(GLFW_MOUSE_PASSTHROUGH , GLFW_TRUE);

    GLFWwindow* window = glfwCreateWindow(
        true_screen_width - 1, true_screen_height - 1, "ImGui Transparent OpenGL Window Example",
        nullptr, nullptr
    );
    if (window == nullptr) {
        fprintf(stderr, "Failed to create GLFW window\n");
        glfwTerminate();
        return 1;
    }

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);  // Enable vsync

    if (gl3wInit() != 0) {
        fprintf(stderr, "Failed to initialize OpenGL loader!\n");
        return 1;
    }

    setupImGui(window);

    ImVec4 clear_color = ImVec4(0.0f, 0.0f, 0.0f, 0.0f);  // Set clear color to transparent

    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        ImGui::Begin("Sample Window");

        if (ImGui::Button("Click me!")) {
            printf("Button clicked!\n");
        }

        ImGui::End();

        ImGui::Render();
        int display_w, display_h;
        glfwGetFramebufferSize(window, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);
        glClearColor(clear_color.x, clear_color.y, clear_color.z, clear_color.w);
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(window);
    }

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
