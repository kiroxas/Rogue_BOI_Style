#include "CharacterAnimation.h"
#include <fstream>

CharacterAnimation::CharacterAnimation(const KiroGame::Image& sprite_sheet, 
                                       const AnimationState a):
m_etat(a)
{
    if(!m_texture.loadFromImage(sprite_sheet.image))
    {
    	//Handle Eror
    	infos::log(RENDERING_PATH,"Texture not loaded");
    }
    m_sprite.setTexture(m_texture);
    std::ifstream info_file(sprite_sheet.info_path.c_str());
    
    if(info_file.fail())
    {
    	infos::log(RENDERING_PATH,"Infos path not found : " + sprite_sheet.info_path);
    }
    std::string item,item2;
    
    std::getline(info_file,item, ' ');
    std::getline(info_file,item2);
    
    infos::log(RENDERING_PATH,"Creating Sprite : " + item + ", " + item2);
    m_sprite_size = std::make_pair(std::stoi(item),std::stoi(item2));
    m_sprite.setTextureRect(sf::IntRect(0,0,m_sprite_size.first,m_sprite_size.second));
}

CharacterAnimation& CharacterAnimation::operator++()
{
	
}

sf::Sprite CharacterAnimation::getSprite() const
{
    return m_sprite;
}
