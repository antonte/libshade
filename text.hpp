#pragma once
#include <memory>
#include <sdlpp/sdlpp.hpp>
#include <shade/array_buffer.hpp>

class Library;
class Text
{
public:
  Text(Library &, const std::string &fontTexture, int aspectWidth, int aspectHeight);
  void setText(const std::string &);
  void draw();

private:
  sdl::Texture *texture;
  int aspectWidth;
  int aspectHeight;
  std::unique_ptr<ArrayBuffer> vertices;
  std::unique_ptr<ArrayBuffer> uvs;
  int n;
};
