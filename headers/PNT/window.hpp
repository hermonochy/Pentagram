#pragma once

#include <string>
#include <vector>
#include <chrono>
#include <imgui.h>
#include <glad/gl.h>
#include <GLFW/glfw3.h>

struct GLFWmonitor;
struct GLFWwindow;
struct GLFWimage;
struct ImGuiContext;
struct ImGuiIO;
struct GladGLContext;

namespace PNT {
    class Window;
    struct windowEvent;

    void monitorCallback(GLFWmonitor*, int);

    enum class eventTypes {
        KEYBOARD,
        CHAR,
        DROP,
        SCROLL,
        CURSORPOS,
        WINDOWPOS,
        WINDOWSIZE,
        CURSORENTER,
        MOUSEBUTTON,
        WINDOWFOCUS,
        ICONIFY
    };

    enum class vsyncModes {
        ADAPTIVE = -1,
        OFF,
        ON,
    };

    class callbackManagers {
    private:
        friend class Window;

        static void keyCallbackManager(GLFWwindow*, int, int, int, int);
        static void charCallbackManager(GLFWwindow*, unsigned int);
        static void dropCallbackManager(GLFWwindow*, int, const char**);
        static void scrollCallbackManager(GLFWwindow*, double, double);
        static void cursorPosCallbackManager(GLFWwindow*, double, double);
        static void windowposCallbackManager(GLFWwindow*, int, int);
        static void windowsizeCallbackManager(GLFWwindow*, int, int);
        static void cursorEnterCallback(GLFWwindow*, int);
        static void mousebuttonCallbackManager(GLFWwindow*, int, int, int);
        static void windowFocusCallback(GLFWwindow*, int);
        static void iconifyCallbackManager(GLFWwindow*, int);
    };

    struct windowData {
        void(*eventCallback)(Window*, windowEvent);
        std::string title;
        int width, height, xpos, ypos;
        ImGuiConfigFlags ImGuiFlags;
        bool focused;
        bool hidden;
        bool iconified;
        vsyncModes vsyncMode;
        float clearColor[4];
        void* userPointer;

        windowData() : eventCallback(nullptr), title{0}, width(128), height(128), xpos(GLFW_DONT_CARE), ypos(GLFW_DONT_CARE), ImGuiFlags(0), focused(false), hidden(false), iconified(false), vsyncMode(vsyncModes::OFF), clearColor{0.0f, 0.0f, 0.0f, 1.0f}, userPointer(nullptr) {
        }
    };

    class Window {
    private:
        friend class callbackManagers;
        friend void deinit();
        friend void processEvents();

        static inline int m_instances;
        static inline std::vector<Window*> m_instancesList;
        GLFWwindow* m_window = nullptr;
        GladGLContext* m_openglContext;
        bool m_closed;
        bool m_frame;
        windowData m_data;
        std::vector<windowEvent> m_eventQueue;
        ImGuiContext* m_ImContext;
        ImGuiIO* m_IO;

        std::chrono::steady_clock::time_point newframe;
        std::chrono::steady_clock::time_point endframe;
        std::chrono::duration<double> deltaTime;

        void createWindowIntern(const std::string& title, int width, int height, int xpos, int ypos, ImGuiConfigFlags ImGuiFlags);
    public:
        /// @brief Window object empty default constuctor, can be used later with "createWindow()" method.
        Window();

        /// @brief Window object constructor.
        /// @param title The desired title.
        /// @param width The desired width.
        /// @param height The desired height.
        /// @param xpos The desired x position.
        /// @param ypos The desired y position.
        /// @param ImGuiFlags The desired imgui configuration flags.
        Window(const std::string& title, int width, int height, int xpos, int ypos, ImGuiConfigFlags ImGuiFlags);

        /// @brief Window object constuctor.
        /// @param data The desired "windowData" object for the window.
        Window(const windowData& data);

        ~Window();

        /// @brief Creates the window, you can use this in conjunction with the "Window()" constructor that tskes no arguments to create the window on screen later.
        /// @param title The desired title.
        /// @param width The desired width.
        /// @param height The desired height.
        /// @param xpos The desired x position.
        /// @param ypos The desired y position.
        /// @param ImGuiFlags The desired imgui configuration flags.
        void createWindow(const std::string& title, int width, int height, int xpos, int ypos, ImGuiConfigFlags ImGuiFlags = 0);

        /// @brief Creates the window, you can use this in conjunction with the "Window()" constructor that tskes no arguments to create the window on screen later.
        /// @param data The desired "windowData" object for the window.
        void createWindow(const windowData& data);

        void destroyWindow();

        /// @brief Starts the opengl and imgui frame for the window.
        void startFrame();

        /// @brief Hides the window, returns the sdl error code (0 is success).
        void endFrame();

        /// @brief Sets the event callback of the window that will be call every time there is an event.
        /// @param newEventCallback The desired function pointer for the event callback with signature "PNT::Window*, PNT::windowEvent" (use nullptr to clear callback).
        void setEventCallback(void(*newEventCallback)(Window*, windowEvent));

        /// @brief Pushes an event to the event stack.
        /// @param event The desired event to push, you can create events with the numerous "create...Event(...);" functions.
        /// @warning glfw has no event queue manipulation that I know of, so all custom events push by this function will be proccesed before glfw events.
        void pushEvent(windowEvent event);

        /// @brief Sets a pointer for the window that can be retrived later.
        /// @param pointer The desired user defined pointer for the window.
        void setUserPointer(void* pointer);

        /// @brief Sets the data struct of the window.
        /// @param newData The desired PNT::windowData for the window.
        void setWindowData(windowData newData);

        /// @brief Sets the window title.
        /// @param title The desired window title.
        void setTitle(const std::string& title);

        /// @brief Sets the window icon.
        /// @param image The desired PNT::image for the window icon.
        void setIcon(const GLFWimage& image);

        /// @brief Sets the dimentions of the window.
        /// @param width The desired window width.
        /// @param height The desired window height.
        void setDimentions(int width, int height);

        /// @brief Focuses the window.
        void setFocused();

        /// @brief Sets the position of the window.
        /// @param xpos The desired x window position.
        /// @param ypos The desired y window position.
        void setPosition(int xpos, int ypos);

        /// @brief Hides the window.
        void hide();

        /// @brief Shows the window.
        void show();

        /// @brief Minimises the window.
        void minimize();

        /// @brief Maximises the window.
        void maximize();

        /// @brief Sets the vsync mode for the window.
        /// @param vsyncMode The desired vsync mode for the windowof type "vsyncModes".
        void setVsyncMode(vsyncModes vsyncMode);

        /// @brief Sets the opengl clear color for the window.
        /// @param red The desired red channel.
        /// @param green The desired green channel.
        /// @param blue The desired blue channel.
        /// @param alpha The desired alpha channel.
        void setClearColor(float red, float green, float blue, float alpha);

        /// @brief Sets the should close status of the window (can be obtained with the "shouldClose();" method).
        /// @param shouldClose The desired should close status of the window.
        void setShouldClose(bool shouldClose);

        /// @brief Sets the required aspect ratio of the window.
        /// @param numerator The desired aspect ratio numerator (-1 for anything).
        /// @param denominator The desired aspect ratio denominator (-1 for anything).
        void setAspectRatio(int numerator, int denominator);

        /// @brief Gets the time to calculate the last frame.
        /// @return The time in nanoseconds between the last newframe and endframe pair.
        std::chrono::duration<double> getDeltaTime() const;

        /// @brief Retrives the user pointer set by the "setUserPointer()" method.
        /// @return A raw pointer set by the user.
        void* getUserPointer() const;

        /// @brief Gets the window data.
        /// @return Returns the underlying data struct of the window.
        windowData getWindowData() const;

        /// @brief Gets the window title.
        /// @return The window title.
        std::string getTitle() const;

        /// @brief Gets the width of the window.
        /// @return The window width.
        int getWidth() const;

        /// @brief Gets the height of the window.
        /// @return The window height.
        int getHeight() const;

        /// @brief Gets the window focus.
        /// @return The focus of the window, true if focused and false if not focused.
        bool getFocus() const;

        /// @brief Gets the X position of the window.
        /// @return The window X position.
        int getXPos() const;

        /// @brief Gets the Y position of the window.
        /// @return The window Y position.
        int getYPos() const;

        /// @brief Gets the hidden state of the window.
        /// @return True if the window is hidden (not on screen of on taskbar), and false if otherwise.
        bool getHidden() const;

        /// @brief Gets the iconified state of the window.
        /// @return True if the window is minimised (on the taskbar), and false if otherwise.
        bool getIconified() const;

        /// @brief Gets the OpenGL context.
        /// @return The opengl context pointer.
        const GladGLContext* getGL() const;

        /// @brief Check if the currect window should close.
        /// @return True if the window should close.
        bool shouldClose() const;

        /// @brief Gets the glfw window.
        /// @return A pointer to the internal glfw window (BE CAREFUL).
        const GLFWwindow* getGLFWWindow() const;
    };
}
