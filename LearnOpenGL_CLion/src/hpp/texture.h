//
//  texture.hpp
//  OpenGL Practice
//
//  Created by Thomas Buffard on 7/1/20.
//

#ifndef TEXTURE_H
#define TEXTURE_H

#include <stdio.h>

#include <string>
#include <glad/glad.h>

class Texture
{
public:
	GLuint m_texture;

    Texture(const std::string& fileName);
    
    void bind();
    
    virtual ~Texture();
    
private:
    Texture(const Texture& texture) {}
    void operator=(const Texture& texture) {}
};

#endif /* texture_h */
