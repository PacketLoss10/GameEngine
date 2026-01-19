#include "Texture.h"

std::string Texture::empty = "NULLTEXTURE.png";

Texture::Texture(std::string filepath) :filepath(filepath) {}