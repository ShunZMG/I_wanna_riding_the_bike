//
// Created by 桂明谦 on 2019/12/18.
//

#include "engin/imageEntrepot.hpp"

map<string, SDL_Texture*> ImageEntrepot::images = map<string, SDL_Texture*>();

void ImageEntrepot::LoadImage(const string& filename){
    string image_name = GetNameFromFile(filename);
    auto it = images.find(image_name);
    if(it!=images.end())
        spdlog::warn("{} is exists", image_name);
    else{
        SDL_Surface* surface = IMG_Load(filename.c_str());
        if(surface==nullptr){
            spdlog::error("{} load failed", filename);
            return ;
        }
        SDL_Texture* texture = SDL_CreateTextureFromSurface(Director::GetDirector()->GetRender(), surface);
        SDL_FreeSurface(surface);
        if(texture==nullptr){
            SDL_DestroyTexture(texture);
            spdlog::error("texture {} can't create", image_name);
            return;
        }
        SDL_DestroyTexture(it->second);
        images[image_name] = texture;
    }
}

void ImageEntrepot::LoadImageStrict(string filename){
    string image_name = GetNameFromFile(filename);
    auto it = images.find(image_name);
    if(it!=images.end()) {
        spdlog::error("{} is exist", filename);
        return;
    }else{
        SDL_Surface* surface = IMG_Load(filename.c_str());
        if(surface==nullptr){
            spdlog::error("{} load failed", filename);
            return ;
        }
        SDL_Texture* texture = SDL_CreateTextureFromSurface(Director::GetDirector()->GetRender(), surface);
        SDL_FreeSurface(surface);
        if(texture==nullptr){
            SDL_DestroyTexture(texture);
            spdlog::error("texture {} can't create", image_name);
            return;
        }
        SDL_DestroyTexture(it->second);
        images[image_name] = texture;
    }
}

void ImageEntrepot::DeleteImage(string name){
    auto it = images.find(name);
    if(it!=images.end()) {
        SDL_DestroyTexture(it->second);
        images.erase(it);
    }
}

SDL_Texture* ImageEntrepot::GetImage(string name){
    auto it = images.find(name);
    if(it==images.end()){
        spdlog::warn("{} is not in entrepot", name);
        return nullptr;
    }
    return it->second;
}

void ImageEntrepot::PrintContent(){
    spdlog::info("ImageEntrepot's content:");
    for(auto i : images){
        cout<<i.first<<endl;
    }
}

void ImageEntrepot::Clear(){
    for(auto i: images){
        SDL_DestroyTexture(i.second);
    }
    images.clear();
}

string GetNameFromFile(const string& filename){
    size_t pos = filename.find_last_of('/');
    string substring;
    if(pos != filename.npos)
        substring = filename.substr(pos+1);
    else
        substring = filename;
    size_t final_pos = substring.find_first_of('.');
    if(final_pos == substring.npos)
        return substring;
    return substring.substr(0, final_pos);
}