#include "library.hpp"

#include "obj.hpp"
#include <cassert>
#include <fstream>

static bool fileExists(const std::string &fileName)
{
  return std::ifstream("data/" + fileName).good();
}

Library::Library(SDL_Renderer *aRend) : rend(aRend) {}
Library::~Library() {}

sdl::Texture *Library::getTexture(const std::string &fileName)
{
  auto it = textures.find(fileName);
  if (it == std::end(textures))
  {
    if (!fileExists(fileName + ".bmp"))
      return nullptr;
    bool tmp;
    std::tie(it, tmp) = textures.emplace(
      fileName,
      std::make_unique<sdl::Texture>(rend, sdl::Surface("data/" + fileName + ".bmp").get()));
    assert(tmp);
  }
  return it->second.get();
}

Obj *Library::getObj(const std::string &objFileName, const std::string &texFileName)
{
  auto it = objs.find(objFileName);
  if (it == std::end(objs))
  {
    if (!fileExists(objFileName + ".obj"))
      return nullptr;
    bool tmp;
    std::tie(it, tmp) =
      objs.emplace(objFileName, std::make_unique<Obj>(*this, objFileName, texFileName));
    assert(tmp);
  }
  return it->second.get();
}
