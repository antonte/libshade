#include "text.hpp"
#include "array_buffer.hpp"
#include "gl_check_error.hpp"
#include "library.hpp"
#include <cpptoml/cpptoml.h>
#include <log/log.hpp>
#include <vector>

Text::Text(Library &library, const std::string &fontTexture)
  : texture(library.getTexture(fontTexture))
{
  texture->glBind(nullptr, nullptr);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
  glGenerateMipmap(GL_TEXTURE_2D);
  try
  {
    auto &&conf = cpptoml::parse_file("data/" + fontTexture + ".toml");
    auto &&charCoords = conf->get_array_of<cpptoml::array>("CharCoords");
    if (!charCoords)
      throw std::runtime_error("Invalid file format: " + fontTexture);
    width = *conf->get_as<int64_t>("width");
    height = *conf->get_as<int64_t>("height");
    for (auto &&ch : *charCoords)
    {
      auto &&ints = ch->get_array_of<int64_t>();
      if (!ints || ints->size() != 4)
        throw std::runtime_error("Invalid file format, expected 4 ints: " + fontTexture);
      coords.push_back(std::make_tuple((*ints)[0], (*ints)[1], (*ints)[2], (*ints)[3]));
    }
  }
  catch (std::runtime_error &e)
  {
    LOG(e.what());
  }
  if (!coords.empty())
    return;
  for (int ch = ' '; ch <= '~'; ++ch)
    coords.push_back(std::make_tuple(
      (ch - ' ') % 16 * width / 16, (ch - ' ') / 16 * height / 6, width / 16, height / 6));
}

void Text::setText(const std::string &text)
{
  std::vector<glm::vec3> tmpVertices;
  std::vector<glm::vec2> tmpUvs;
  auto x = 0.0f;
  for (auto ch : text)
  {
    auto idx = ch - ' ';
    if (idx >= static_cast<int>(coords.size()))
      continue;
    auto &&crd = coords[idx];
    auto normWidth = 1.0f * std::get<2>(crd) / std::get<3>(crd);
    tmpVertices.emplace_back(x, 0.0f, 0.0f);
    tmpVertices.emplace_back(x + normWidth, 0.0f, 0.0f);
    tmpVertices.emplace_back(x + normWidth, 1.0f, 0.0f);

    tmpVertices.emplace_back(x, 0.0f, 0.0f);
    tmpVertices.emplace_back(x + normWidth, 1.0f, 0.0f);
    tmpVertices.emplace_back(x, 1.0f, 0.0f);
    auto chX = 1.0f * std::get<0>(crd) / width;
    auto chY = 1.0f * std::get<1>(crd) / height;
    auto chW = 1.0f * std::get<2>(crd) / width;
    auto chH = 1.0f * std::get<3>(crd) / height;
    tmpUvs.emplace_back(chX, chY);
    tmpUvs.emplace_back(chX + chW, chY);
    tmpUvs.emplace_back(chX + chW, chY + chH);

    tmpUvs.emplace_back(chX, chY);
    tmpUvs.emplace_back(chX + chW, chY + chH);
    tmpUvs.emplace_back(chX, chY + chH);
    x += normWidth - 27.0f / std::get<3>(crd);
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
