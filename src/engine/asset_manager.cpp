#include "asset_manager.hpp"

bool AssetManager::load(const std::string &path, size_t &indx)
{
    if(sheet_amnt == 255) return false; // no more room

    auto newsprite = std::make_shared<olc::Sprite>();
    if(newsprite->LoadFromFile("assets/spritesheets/link.png") == olc::rcode::OK)
    {
        DEBUG("adding spritesheet with index");
        indx = sheet_amnt;
        DEBUG(sheet_amnt);
        spritesheets[sheet_amnt] = std::move(newsprite);
        decs[sheet_amnt] =  std::make_unique<olc::Decal>(spritesheets[sheet_amnt].get());
        ++sheet_amnt;
        return true;
    }
    return false;
}

std::weak_ptr<olc::Decal> AssetManager::get(size_t indx)
{
    return decs[indx];
}
