#include "asset_manager.hpp"

bool AssetManager::load(const std::string &path, size_t &indx)
{
    if(sheet_amnt == 255) return false; // no more room

    auto newsprite = std::make_shared<olc::Sprite>();
    if(newsprite->LoadFromFile(path) == olc::rcode::OK)
    {
        indx = sheet_amnt;

        spritesheets[sheet_amnt] = std::move(newsprite);
        decs[sheet_amnt] =  std::make_unique<olc::Decal>(spritesheets[sheet_amnt].get());
        ++sheet_amnt;
        DEBUG_VAL(sheet_amnt);

        return true;
    }
    return false;
}

std::weak_ptr<olc::Decal> AssetManager::get(size_t indx)
{
    // DEBUG(decs[0]);
    // DEBUG(decs[1]);
    // DEBUG(decs[2]);
    return decs[indx];
}
