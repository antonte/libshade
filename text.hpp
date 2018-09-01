#pragma once
#include <memory>
#include <sdlpp/sdlpp.hpp>
#include <shade/array_buffer.hpp>

class Library;
class Text
{
public:
  Text(Library &, const std::string &fontTexture);
  void setText(const std::string &);
  void draw();

private:
  sdl::Texture *texture;
  std::unique_ptr<ArrayBuffer> vertices;
  std::unique_ptr<ArrayBuffer> uvs;
  int n;
  std::vector<std::tuple<int, int, int, int>> coords;
  int width;
  int height;
};
