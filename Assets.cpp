#include <string>

#include "Assets.h"

std::map<std::string, Surface*> Assets::Graphics;
std::map<std::string, Animation*> Assets::Animations;
std::map<std::string, Mix_Chunk*> Assets::Sounds;

void Assets::Load() {            
    Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 4096);

    //Player
    Graphics["player"] = new Surface("assets/player/player.png");      
    Graphics["player_missile"] = new Surface("assets/player/player_missile.png");   
    Graphics["player_life"] = new Surface("assets/player/player_life.png");
    Graphics["player_flag"] = new Surface("assets/player/flag_normal.png");


    Animations["player_explode"] = new Animation("explode");
    Animations["player_explode"]->FrameTime = 0.08f;

    Sounds["player_shoot"] = Mix_LoadWAV("assets/player/player_shoot.wav");
    Sounds["player_explode"] = Mix_LoadWAV("assets/player/player_explode.wav");

    for(int i = 0; i < 4; i++) {
        std::string file = "assets/player/player_expl_" + std::to_string(i) + ".png";

        Animations["player_explode"]->AddSprite(new Surface(&file[0]));
    }

    //Invaders
    Graphics["invader_missile"] = new Surface("assets/invader/inv_missile.png");
    Animations["invader_blue_idle"] = new Animation("idle");
    Animations["invader_blue_idle"]->FrameTime = .3f;

    Animations["invader_purple_idle"] = new Animation("idle");
    Animations["invader_purple_idle"]->FrameTime = .3f;

    Animations["invader_red_idle"] = new Animation("idle");
    Animations["invader_red_idle"]->FrameTime = .3f;

    Animations["invader_commander_idle"] = new Animation("idle");
    Animations["invader_commander_idle"]->FrameTime = .3f;
    
    std::string file = "assets/invader/inv_ye_m_0.png";
    Animations["invader_commander_idle"]->AddSprite(new Surface(&file[0]));

    for(int i = 0; i < 6; i++) {
        std::string file = "assets/invader/inv_bl_m_" + std::to_string(i) + ".png";
        Animations["invader_blue_idle"]->AddSprite(new Surface(&file[0]));

        file = "assets/invader/inv_pu_m_" + std::to_string(i) + ".png";
        Animations["invader_purple_idle"]->AddSprite(new Surface(&file[0]));

        file = "assets/invader/inv_re_m_" + std::to_string(i) + ".png";
        Animations["invader_red_idle"]->AddSprite(new Surface(&file[0]));
    }

	Animations["invader_blue_explode"] = new Animation("explode");
	Animations["invader_blue_explode"]->FrameTime = .05f;

	Animations["invader_purple_explode"] = new Animation("explode");
	Animations["invader_purple_explode"]->FrameTime = .05f;

	Animations["invader_red_explode"] = new Animation("explode");
	Animations["invader_red_explode"]->FrameTime = .05f;

	Animations["invader_commander_explode"] = new Animation("explode");
	Animations["invader_commander_explode"]->FrameTime = .05f;

	for(int i = 0; i < 4; i++) {
		std::string file = "assets/invader/inv_bl_expl_" + std::to_string(i) + ".png";
		Animations["invader_blue_explode"]->AddSprite(new Surface(&file[0]));

		file = "assets/invader/inv_pu_expl_" + std::to_string(i) + ".png";
		Animations["invader_purple_explode"]->AddSprite(new Surface(&file[0]));

		file = "assets/invader/inv_re_expl_" + std::to_string(i) + ".png";
		Animations["invader_red_explode"]->AddSprite(new Surface(&file[0]));

		file = "assets/invader/inv_ye_expl_" + std::to_string(i) + ".png";
		Animations["invader_commander_explode"]->AddSprite(new Surface(&file[0]));
	}

    Sounds["invader_fly"] = Mix_LoadWAV("assets/invader/invader_fly.wav");
    Sounds["invader_shoot"] = Mix_LoadWAV("assets/invader/invader_shoot.wav");
    Sounds["invader_explode"] = Mix_LoadWAV("assets/invader/invader_explode.wav");
    Sounds["invader_idle"] = Mix_LoadWAV("assets/invader/invader_idle.wav");
    Sounds["invader_commander_shot"] = Mix_LoadWAV("assets/invader/invader_commander_shot.wav");

    //Stars
    Graphics["star_white"] = new Surface("assets/star_white.tga");
    Graphics["star_red"] = new Surface("assets/star_red.tga");
    Graphics["star_yellow"] = new Surface("assets/star_yellow.tga");
    Graphics["star_purple"] = new Surface("assets/star_purple.tga");
}