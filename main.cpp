#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glad/gl.h>
#include <stdexcept>
#include <iostream>

/** Error callback
 * @param error
 * @param description
 */
void ErrorCallback(int error, const char* description) {
    std::string errorMessage = "There is some error with your OpenGL instance: ";
    errorMessage += description;
    throw std::runtime_error(errorMessage);
}

/** key press callback
 * @param window the window instance
 * @param key
 * @param scancode
 * @param action
 * @param mods
 */
void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GLFW_TRUE);
}

/** Resize window handler
 * @param window
 */
void ResizeWindow(GLFWwindow* window) {
    int width, height;
    glfwGetFramebufferSize(window, &width, &height);
    glViewport(0, 0, width, height);
}

/** Method that starts OpenGL
 *
 */
void StartOpenGL() {
    // Calling the glfw init method
    if (!glfwInit()) {
        throw std::runtime_error("Cannot start OpenGL instance");
    }

    // Defining the minimum version of OpenGL
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

    // Defining the other parameters of GLFW
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Setting the error callback
    glfwSetErrorCallback(ErrorCallback);
}

/** Method that create a new window
 * @return the window instance
 */
GLFWwindow* StartWindow() {
    // Creating the vidMode for fullscreen/windowed
    GLFWmonitor* primary = glfwGetPrimaryMonitor();
    const GLFWvidmode* mode = glfwGetVideoMode(primary);

    // Defining the windowHints
    glfwWindowHint(GLFW_RED_BITS, mode->redBits);
    glfwWindowHint(GLFW_GREEN_BITS, mode->greenBits);
    glfwWindowHint(GLFW_BLUE_BITS, mode->blueBits);
    glfwWindowHint(GLFW_REFRESH_RATE, mode->refreshRate);
    glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);

    // Creating the window
    GLFWwindow* window = glfwCreateWindow((int) (mode->width / 1.5), (int) (mode->height / 1.5), "OpenGL", nullptr, nullptr);

    // If window is null, then throw error
    if (!window) {
        throw std::runtime_error("Cannot start ");
    }

    // Defining OpenGL context
    glfwMakeContextCurrent(window);
    gladLoadGL(glfwGetProcAddress);

    // Defining the KeyPress callback
    glfwSetKeyCallback(window, KeyCallback);

    // Defining the resize callback
    ResizeWindow(window);
    return window;
}

/** Method that define the window loop
 * @param window
 */
void WindowLoop(GLFWwindow* window) {
    while (!glfwWindowShouldClose(window)) {
        double time = glfwGetTime();
        glfwSwapBuffers(window);
        glfwSwapInterval(1);
        glfwPollEvents();

    }
}

/** Method that closes all instances of OpenGL and exit the app
 * @param window
 */
void DestroyApp(GLFWwindow* window = nullptr, int status = EXIT_SUCCESS) {
    // If defined window, destroy window first
    if (window)
        glfwDestroyWindow(window);

    // Destroy GLFW instance
    glfwTerminate();

    // Exit the application
    exit(status);
}

int main() {
    try {
        StartOpenGL();
        GLFWwindow* window = StartWindow();
        WindowLoop(window);
        DestroyApp(window, EXIT_SUCCESS);
    } catch (const std::runtime_error &error) {
        std::cout << error.what();
        DestroyApp(nullptr, EXIT_FAILURE);
    }
}