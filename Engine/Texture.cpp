#include "pch.h"
#include "Engine.h"
#include "Texture.h"

namespace nu
{
    Texture::~Texture()
    {
        // if texture exists, destroy texture
        if (/*TODO: m_texture is not null*/m_texture != nullptr) SDL_DestroyTexture(m_texture);
    }

    bool Texture::Load(const std::string& filename, Renderer& renderer)
    {
        // load image onto surface
        SDL_Surface* surface = IMG_Load("Textures/LoLHealthPotion.jpg");
        if (/*TODO: surface is null*/surface == nullptr)
        {
            std::cerr << "Could not load image: " << filename << std::endl;
            return false;
        }

        // create texture from surface, texture is a friend class of renderer
        m_texture = SDL_CreateTextureFromSurface(/*TODO: renderer, surface*/  renderer.m_renderer, surface);
        // once texture is created, surface can be freed up
        SDL_DestroySurface(surface);
        if (/*TODO: m_texture is null*/ m_texture == nullptr)
        {
            std::cerr << "Could not create texture: " << filename << std::endl;
            return false;
        }

        return true;
    }

    Vector2 Texture::GetSize()
    {
        Vector2 v;
        // https://wiki.libsdl.org/SDL3/SDL_GetTextureSize
        // TODO: SDL_GetTextureSize
        SDL_GetTextureSize(m_texture, &v.x, &v.y);
        return v;
    }
}