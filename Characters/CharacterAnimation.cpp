#include "CharacterAnimation.h"
#include <fstream>
#include <random>

CharacterAnimation::CharacterAnimation(const KiroGame::Image& sprite_sheet, 
                                       const AnimationState a,
                                       const float rotation,
                                       float _scale):
m_etat(a),
in_animation(false),
m_loop(false),
angle(rotation),
scale(_scale)
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
    //m_sprite.setOrigin(m_sprite_size.first /2, m_sprite_size.second /2);
    m_sprite.setRotation(angle);
    m_sprite.setScale(scale,scale);

    for(int j = 0; j < 2; ++j)
    {
        for(int i = 0; i < 3; ++i)
        {
            std::getline(info_file,item, ' ');
             m_animation_length.push_back(std::stoi(item));
        }
        std::getline(info_file,item);
        m_animation_length.push_back(std::stoi(item));
    }
}

CharacterAnimation& CharacterAnimation::operator++()
{
    int correct_line = m_etat.state.movement * 4 + m_etat.state.dir;
    m_sprite.setTextureRect(sf::IntRect(m_etat.animation_cpt * m_sprite_size.first,correct_line * m_sprite_size.second,m_sprite_size.first,m_sprite_size.second));
    m_sprite.setRotation(angle);
    m_sprite.setScale(scale,scale);

    return *this;
}

void CharacterAnimation::animate()
{
    static std::random_device rd;
    static std::mt19937 generator(rd());
    static std::uniform_int_distribution<int> int_distribution(0,255);
    if(m_clock.getElapsedTime() >= KiroGame::elapsed_animation_time)
    {
        m_sprite.setColor(sf::Color(int_distribution(generator),int_distribution(generator),int_distribution(generator)));
        update();
        m_clock.restart();
    }
}

void CharacterAnimation::update()
{
        m_etat.animation_cpt++;
        if(m_etat.animation_cpt >= m_animation_length[m_etat.state.movement * 4 + m_etat.state.dir])
            m_etat.animation_cpt = 0;
        ++(*this);
}

void CharacterAnimation::setAnimationState(const State& a)
{
    m_etat.state = a;
    m_etat.animation_cpt = 0;
}

 void CharacterAnimation::AdjustAnimation(const State& a)
 {
    // First we need to adjust our sprite on the sprite sheet
    if(a != m_etat.state)
    {
        m_etat.state = a;
        m_etat.animation_cpt = 0;
    }
    else
    {
        if(m_clock.getElapsedTime() >= KiroGame::elapsed_animation_time)
        {
            m_etat.animation_cpt++;
            if(m_etat.animation_cpt >= m_animation_length[m_etat.state.movement * 4 + m_etat.state.dir])
                m_etat.animation_cpt = 0;
        }
    }

    if(m_clock.getElapsedTime() >= KiroGame::elapsed_animation_time)
    {
        int correct_line = m_etat.state.movement * 4 + m_etat.state.dir;
        if(m_animation_length[correct_line] == 0)
            correct_line = 0;
        m_sprite.setTextureRect(sf::IntRect(m_etat.animation_cpt * m_sprite_size.first,correct_line * m_sprite_size.second,m_sprite_size.first,m_sprite_size.second));
        m_sprite.setRotation(angle);
        m_sprite.setScale(scale,scale);
        m_clock.restart();
    }

 }

CharacterAnimation::CharacterAnimation(){}

sf::Sprite CharacterAnimation::getSprite() const
{
    return m_sprite;
}

std::pair<unsigned int, unsigned int> CharacterAnimation::getSize() const
{
    return m_sprite_size;
}
