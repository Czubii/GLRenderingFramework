//
// Created by patry on 02/09/2024.
//

#ifndef DEBUG_H
#define DEBUG_H

namespace Debug {
    // Function to translate OpenGL error codes to readable strings
    inline const char *getGLErrorString(GLenum err) {
        switch (err) {
            case GL_NO_ERROR:
                return "No error";
            case GL_INVALID_ENUM:
                return "Invalid enum";
            case GL_INVALID_VALUE:
                return "Invalid value";
            case GL_INVALID_OPERATION:
                return "Invalid operation";
            case GL_STACK_OVERFLOW:
                return "Stack overflow";
            case GL_STACK_UNDERFLOW:
                return "Stack underflow";
            case GL_OUT_OF_MEMORY:
                return "Out of memory";
            case GL_INVALID_FRAMEBUFFER_OPERATION:
                return "Invalid framebuffer operation";
            // Add more cases as needed
            default:
                return "Unknown error";
        }
    }

    // Enhanced macro to check OpenGL errors with more detail
#define GL_CHECK_ERROR() \
do { \
GLenum err; \
while ((err = glGetError()) != GL_NO_ERROR) { \
std::cerr << "OpenGL error (" << err << "): " \
<< Debug::getGLErrorString(err) \
<< " in file " << __FILE__ \
<< " at line " << __LINE__ \
<< std::endl; \
} \
} while (0)
}

#endif //DEBUG_H
