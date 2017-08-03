#pragma once

#include <vector>
#include <GL/glew.h>

#include "Utils/UtilCollection.h"


class Timer {
public:
    Timer();

    /**
     * \brief current destructor workaround
     */
    void del();

    /**
     * \brief starts the GPU timer
     */
    void start();

    /**
     * \brief stops the GPU timer
     */
    void stop();

    /**
     * \brief draws an imgui window with the frametime and a graph
     * \param window 
     */
    void drawGuiWindow(GLFWwindow* window);

private:
    std::vector<float> m_ftimes;
    GLuint m_query;
    GLuint m_elapsedTime;
    int m_done = false;
};