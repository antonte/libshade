#pragma once
#include "array_buffer.hpp"
#include "sdlpp/sdlpp.hpp"
#include "library.hpp"
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <memory>
#include <string>
#include <vector>

class ObjData;

class Obj
{
public:
  Obj(Library &library,
      const std::string &objFileName,
      const std::string &textureFileName = std::string());
  void draw();
  ~Obj();

private:
  sdl::Texture* texture;
  std::unique_ptr<ObjData> objData;
  ArrayBuffer vertices;
  ArrayBuffer uvs;
  ArrayBuffer normals;
  int n;
};
