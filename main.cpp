#include "SDL2/SDL.h"
#include "OpenGL/gl3.h"

#include "shader_compiler.h"

int main(int argc, char** argv){
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window* window = SDL_CreateWindow("OpenGL", 100, 100, 400, 500, SDL_WINDOW_OPENGL);
    SDL_GLContext context = SDL_GL_CreateContext(window);

    long vertFileSize, fragFileSize;
    char* vertexData = readFileToCharArray("vertex_shader.glsl", &vertFileSize);
    char* fragData = readFileToCharArray("fragment_shader.glsl", &fragFileSize);
    unsigned int shader = compileShaderVF(vertexData, fragData);
    glUseProgram(shader);
    int postionId = glGetAttribLocation(shader, "position");

    float verts[] = {
        -0.8, -0.8,
        0.0, 0.8,
        0.8, -0.8,
    };


    unsigned int vao, vbo;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(verts), verts, GL_STATIC_DRAW);

    glVertexAttribPointer(postionId, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), 0);
    glEnableVertexAttribArray(postionId);

    glClearColor(1, 1, 0, 1);

    SDL_Event event;
    bool isRunning = true;
    while(isRunning){
        while(SDL_PollEvent(&event)){
            switch(event.type){
                case SDL_QUIT:{
                    isRunning = false;
                    break;
                }
                case SDL_KEYDOWN :{
                    if(event.key.keysym.sym == SDLK_ESCAPE){
                        isRunning = false;
                    }
                    break;
                }
            }
        }
        glClear(GL_COLOR_BUFFER_BIT);

        glDrawArrays(GL_TRIANGLES, 0, 3);

        SDL_GL_SwapWindow(window);
    }

    SDL_DestroyWindow(window);
    return 0;
}