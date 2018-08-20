#include "text.hpp"
#include "array_buffer.hpp"
#include "library.hpp"
#include "gl_check_error.hpp"
#include <vector>

Text::Text(Library &library, const std::string &fontTexture, int aAspectWidth, int aAspectHeight)
  : texture(library.getTexture(fontTexture)), aspectWidth(aAspectWidth), aspectHeight(aAspectHeight)

{
}

void Text::setText(const std::string &text)
{
  std::vector<glm::vec3> tmpVertices;
  std::vector<glm::vec2> tmpUvs;
  auto x = 0.0f;
  for (auto ch : text)
  {
    tmpVertices.emplace_back(x, 0.0f, 0.0f);
    tmpVertices.emplace_back(x + 1.0f, 0.0f, 0.0f);
    tmpVertices.emplace_back(x + 1.0f, 1.0f * aspectHeight / aspectWidth, 0.0f);

    tmpVertices.emplace_back(x, 0.0f, 0.0f);
    tmpVertices.emplace_back(x + 1.0f, 1.0f * aspectHeight / aspectWidth, 0.0f);
    tmpVertices.emplace_back(x, 1.0f * aspectHeight / aspectWidth, 0.0f);
    auto chX = 1.0f * (ch % 16) / 16.0f;
    auto chY = 1.0f * std::max(0, std::min(6, ch / 16 - 2)) / 6.0f;
    tmpUvs.emplace_back(chX, chY);
    tmpUvs.emplace_back(chX + 1.0f / 16.0f, chY);
    tmpUvs.emplace_back(chX + 1.0f / 16.0f, chY + 1.0f / 6.0f);

    tmpUvs.emplace_back(chX, chY);
    tmpUvs.emplace_back(chX + 1.0f / 16.0f, chY + 1.0f / 6.0f);
    tmpUvs.emplace_back(chX, chY + 1.0f / 6.0f);
    x += 1.0f;
  }
  n = tmpVertices.size();
  vertices = std::make_unique<ArrayBuffer>(tmpVertices.data(), tmpVertices.size(), 0);
  uvs = std::make_unique<ArrayBuffer>(tmpUvs.data(), tmpUvs.size(), 1);
}

void Text::draw()
{
  if (!vertices || !uvs || !texture)
    return;
  vertices->activate();
  uvs->activate();
  texture->glBind(nullptr, nullptr);
  glDrawArrays(GL_TRIANGLES, 0, n);
  GL_CHECK_ERROR("glDrawArrays()");
}
