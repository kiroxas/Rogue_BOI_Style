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
    
    
    
    std::ifstream info_file(sprite_sheet.info_path.c_str());
    
    if(info_file.fail())
    {
    	infos::log(RENDERING_PATH,"Infos path not found : " + sprite_sheet.info_path);
    }
    std::string item,item2;
    
    std::getline(info_file,item, ' ');
    std::getline(info_file,item2,' ');
    
    //sprite_size = std::make_pair(boost::lexical_cast<unsigned int>(item),boost::lexical_cast<unsigned int>(item2));
}

CharacterAnimation& CharacterAnimation::operator++()
{
	
}
