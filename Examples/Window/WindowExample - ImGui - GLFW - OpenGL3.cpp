#include <GLFW/glfw3.h>
#include <Windows.h>

#include <fstream>
#include <iostream>

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

// OpenGL 3.0 or higher
const char* glsl_version = "#version 130";

void scaleImGuiStyle(float scaleFactor = 2.5f) {
    ImGuiStyle& style = ImGui::GetStyle();
    style.ScaleAllSizes(scaleFactor);

    ImGuiIO& io        = ImGui::GetIO();
    io.FontGlobalScale = scaleFactor;
}

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
    std::cout << "GLFW initialized" << std::endl;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_TRANSPARENT_FRAMEBUFFER, GLFW_TRUE);  // Enable transparency
    glfwWindowHint(GLFW_DECORATED, GLFW_FALSE);               // No title bar
    // glfwWindowHint(GLFW_MOUSE_PASSTHROUGH, GLFW_TRUE);
    // glfwWindowHint(0x0002000D, GLFW_TRUE);

    GLFWwindow* window = glfwCreateWindow(
        true_screen_width - 1, true_screen_height - 1, "ImGui Transparent OpenGL Window Example",
        nullptr, nullptr
    );
    std::cout << "Window created" << std::endl;
    if (window == nullptr) {
        fprintf(stderr, "Failed to create GLFW window\n");
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return 1;
    }

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);  // Enable vsync

    setupImGui(window);
    scaleImGuiStyle();

    ImVec4 clear_color = ImVec4(0.0f, 0.0f, 0.0f, 0.0f);  // Set clear color to transparent

    bool readyToClose = false;
    while (!readyToClose && !glfwWindowShouldClose(window)) {
        glfwPollEvents();
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
        ImGui::Begin("Sample Window");
        if (ImGui::BeginTabBar("MyTabBar")) {
            if (ImGui::BeginTabItem("Button")) {
                if (ImGui::Button("Click me!")) readyToClose = true;
                ImGui::EndTabItem();
            }
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
