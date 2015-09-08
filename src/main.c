#include <stdio.h>
#include <stdlib.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "lib/util.h"

//Global variables
GLuint program;
GLuint vao;
GLuint drawTri;

// Print out any errors
void error_callback(int error, const char *description) {
  fputs(description, stderr);
}

// Exit the program when escape is pressed
void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods) {
  if (action == GLFW_PRESS) {
    if (key == GLFW_KEY_ENTER) {
      if (drawTri == GL_TRUE) {
        drawTri = GL_FALSE;
      } else {
        drawTri = GL_TRUE;
      }
    } else if (key == GLFW_KEY_ESCAPE) {
      glfwSetWindowShouldClose(window, GL_TRUE);
    }
  }
}

void mouse_button_callback(GLFWwindow *window, int button, int action, int mods) {
  if (action == GLFW_PRESS) {
    if (button == GLFW_MOUSE_BUTTON_LEFT) {
      if (drawTri == GL_TRUE) {
        drawTri = GL_FALSE;
      } else {
        drawTri = GL_TRUE;
      }
    }
  }
}

int main() {
  
  drawTri = GL_TRUE;
  
  // Set the error callback
  glfwSetErrorCallback(error_callback);
  
  // Initialize GLFW and respond to an error
  if (!glfwInit()) {
    fprintf(stderr, "Failed initialize GLFW.");
    exit(EXIT_FAILURE);
  }
  
  // Set options for OpenGL, version 4.1
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);
  
  // Create a context window
  
  /*          Fullscreen option
  GLFWmonitor *monitor = glfwGetPrimaryMonitor();
  const GLFWvidmode *mode = glfwGetVideoMode(monitor);
  glfwWindowHint(GLFW_RED_BITS, mode->redBits);
  glfwWindowHint(GLFW_GREEN_BITS, mode->greenBits);
  glfwWindowHint(GLFW_BLUE_BITS, mode->blueBits);
  glfwWindowHint(GLFW_REFRESH_RATE, mode->refreshRate);
  
  GLFWwindow *window = glfwCreateWindow(mode->width, mode->height, "Triangle", monitor, NULL);
  */
  
  GLFWwindow *window = glfwCreateWindow(800, 600, "Triangle", NULL, NULL);
  
  // Handle window error
  if (!window) {
    fprintf(stderr, "Failed to create GLFW window.");
    glfwTerminate();
    exit(EXIT_FAILURE);
  }
  
  // Set the window as an OpenGL context with the key listener
  glfwMakeContextCurrent(window);
  glfwSetKeyCallback(window, key_callback);
  glfwSetMouseButtonCallback(window, mouse_button_callback);
  
  // Initialize Glew
  glewExperimental = GL_TRUE;
  glewInit();
  
  // Create a new OpenGL program
  program = glCreateProgram();
  
  // Attach fragment shader
  
  char *fs_source = convertFileToBuffer("shaders/fragment.shader");
  GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fs, 1, &fs_source, NULL);
  glCompileShader(fs);
  
  char *vs_source = convertFileToBuffer("shaders/vertex.shader");
  GLuint vs = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vs, 1, &vs_source, NULL);
  glCompileShader(vs);
  
  glAttachShader(program, vs);
  glAttachShader(program, fs);
  
  glLinkProgram(program);
  
  glDeleteShader(vs);
  glDeleteShader(fs);
  
  // Generate vertex arrays for the program
  glGenVertexArrays(1, &vao);
  glBindVertexArray(vao);
  
  // Use the program
  glUseProgram(program);
  
  // Loop to render pixels for image until program exits
  while (!glfwWindowShouldClose(window)) {
    
    // Set a background color and fill the buffer with it
    static const GLfloat green[] = { 0.0f, 0.25f, 0.0f, 1.0f };
    glClearBufferfv(GL_COLOR, 0, green);
    
    if (drawTri == GL_TRUE) {
      // Draw triangles
      glDrawArrays(GL_TRIANGLES, 0, 3);
    }
    
    // Swap buffers to display pixels
    glfwSwapBuffers(window);
    glfwPollEvents();
    
  }
  
  // Clean up when program should exit
  glDeleteVertexArrays(1, &vao);
  glDeleteProgram(program);
  
}
