#include "shade/array_buffer.hpp"

ArrayBuffer::ArrayBuffer(const GLfloat *data, int size, int aAttribute) : attribute(aAttribute), cNum(1), type(GL_FLOAT)
{
  glGenBuffers(1, &id);
  glBindBuffer(GL_ARRAY_BUFFER, id);
  glBufferData(GL_ARRAY_BUFFER, size * sizeof(*data), data, GL_STATIC_DRAW);
}


ArrayBuffer::ArrayBuffer(const glm::vec3 *data, int size, int aAttribute) :
  attribute(aAttribute), cNum(3), type(GL_FLOAT)
{
  glGenBuffers(1, &id);
  glBindBuffer(GL_ARRAY_BUFFER, id);
  glBufferData(GL_ARRAY_BUFFER, size * sizeof(*data), data, GL_STATIC_DRAW);
}

ArrayBuffer::ArrayBuffer(const glm::vec2 *data, int size, int aAttribute) :
  attribute(aAttribute), cNum(2), type(GL_FLOAT)
{
  glGenBuffers(1, &id);
  glBindBuffer(GL_ARRAY_BUFFER, id);
  glBufferData(GL_ARRAY_BUFFER, size * sizeof(*data), data, GL_STATIC_DRAW);
}


ArrayBuffer::ArrayBuffer(const GLint *data, int size, int aAttribute) : attribute(aAttribute), cNum(1), type(GL_INT)
{
  glGenBuffers(1, &id);
  glBindBuffer(GL_ARRAY_BUFFER, id);
  glBufferData(GL_ARRAY_BUFFER, size * sizeof(*data), data, GL_STATIC_DRAW);
}

ArrayBuffer::~ArrayBuffer()
{
  glDeleteBuffers(1, &id);
}

void ArrayBuffer::activate()
{
  glBindBuffer(GL_ARRAY_BUFFER, id);
  glEnableVertexAttribArray(attribute);
  glVertexAttribPointer(attribute,
                        cNum,     // size
                        type,     // type
                        GL_FALSE, // normalized?
                        0,        // stride
                        (void *)0 // array buffer offset
  );
}
