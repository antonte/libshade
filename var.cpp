#include "shade/var.hpp"
#include "shade/gl_check_error.hpp"

BaseVar::BaseVar(const char *aName) : name(aName) {}

void BaseVar::updateLocation(GLuint programId)
{
  location = glGetUniformLocation(programId, name);
  GL_CHECK_ERROR("update location", programId, name);
}

namespace Internal
{
  template <>
  void uniform<float>(GLint location, const float &value)
  {
    glUniform1f(location, value);
    GL_CHECK_ERROR("set float uniform value", location, value);
  }

  template <>
  void uniform<int>(GLint location, const int &value)
  {
    glUniform1i(location, value);
    GL_CHECK_ERROR("set int uniform value", location, value);
  }

  template <>
  void uniform<glm::mat4>(GLint location, const glm::mat4 &value)
  {
    glUniformMatrix4fv(location, 1, GL_FALSE, &value[0][0]);
    GL_CHECK_ERROR("set mat4 uniform value, location: ", location);
  }

  template <>
  std::string type<float>()
  {
    return "float";
  }

  template <int>
  std::string type()
  {
    return "int";
  }

  template <>
  std::string type<glm::mat4>()
  {
    return "mat4";
  }
} // namespace Internal
