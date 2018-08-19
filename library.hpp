#pragma once
#include "sdlpp/sdlpp.hpp"
#include <unordered_map>
#include <memory>

class Obj;

class Library
{
public:
  Library(SDL_Renderer *renderer);
  ~Library();
  sdl::Texture *getTexture(const std::string &fileName);
  Obj *getObj(const std::string &objFileName, const std::string &texFileName = std::string());

private:
  SDL_Renderer *rend;
  std::unordered_map<std::string, std::unique_ptr<sdl::Texture>> textures;
  std::unordered_map<std::string, std::unique_ptr<Obj>> objs;
};
