#include "main.hpp"
#include "GlobalNamespace/MainMenuViewController.hpp"
#include "UnityEngine/UI/Button.hpp"
#include "UnityEngine/GameObject.hpp"
#include "GlobalNamespace/StandardLevelDetailView.hpp"


static ModInfo modInfo; // Stores the ID and version of our mod, and is sent to the modloader upon startup

// Loads the config from disk using our modInfo, then returns it for use
// other config tools such as config-utils don't use this config, so it can be removed if those are in use
Configuration& getConfig() {
    static Configuration config(modInfo);
    return config;
}

// Returns a logger, useful for printing debug messages
Logger& getLogger() {
    static Logger* logger = new Logger(modInfo);
    return *logger;
}

MAKE_HOOK_MATCH(FuckSoloButton, &GlobalNamespace::MainMenuViewController::DidActivate, void, GlobalNamespace::MainMenuViewController
*self, bool firstActivation, bool addedToHierarchy, bool screenSystemEnabling) {

    FuckSoloButton(self, firstActivation, addedToHierarchy, screenSystemEnabling); 
    
    UnityEngine::UI::Button *soloMenuButton = self->dyn__soloButton();
    UnityEngine::GameObject *gameObject = soloMenuButton->get_gameObject();
    
    gameObject->SetActive(false);
}

MAKE_HOOK_MATCH(FuckOnlineButton, &GlobalNamespace::MainMenuViewController::DidActivate, void, GlobalNamespace::MainMenuViewController
*self, bool firstActivation, bool addedToHierarchy, bool screenSystemEnabling) {

    FuckOnlineButton(self, firstActivation, addedToHierarchy, screenSystemEnabling); 
    
    UnityEngine::UI::Button *onlineMenuButton = self->dyn__multiplayerButton();
    UnityEngine::GameObject *gameObject = onlineMenuButton->get_gameObject();
    
    gameObject->SetActive(false);
}

MAKE_HOOK_MATCH(FuckAdvertisementButton, &GlobalNamespace::MainMenuViewController::DidActivate, void, GlobalNamespace::MainMenuViewController
*self, bool firstActivation, bool addedToHierarchy, bool screenSystemEnabling) {

    FuckAdvertisementButton(self, firstActivation, addedToHierarchy, screenSystemEnabling); 
    
UnityEngine::UI::Button*PromotionButton = self->dyn__musicPackPromoButton();
    UnityEngine::GameObject *gameObject = PromotionButton->get_gameObject();
    
    gameObject->SetActive(false);
}

MAKE_HOOK_MATCH(FuckPartyButton, &GlobalNamespace::MainMenuViewController::DidActivate, void, GlobalNamespace::MainMenuViewController
*self, bool firstActivation, bool addedToHierarchy, bool screenSystemEnabling) {

    FuckPartyButton(self, firstActivation, addedToHierarchy, screenSystemEnabling); 
    
    UnityEngine::UI::Button *partyMenuButton = self->dyn__partyButton();
    UnityEngine::GameObject *gameObject = partyMenuButton->get_gameObject();
    
    gameObject->SetActive(false);
}

MAKE_HOOK_MATCH(FuckCampaignButton, &GlobalNamespace::MainMenuViewController::DidActivate, void, GlobalNamespace::MainMenuViewController
*self, bool firstActivation, bool addedToHierarchy, bool screenSystemEnabling) {

    FuckCampaignButton(self, firstActivation, addedToHierarchy, screenSystemEnabling); 
    
    UnityEngine::UI::Button *campaignMenuButton = self->dyn__campaignButton();
    UnityEngine::GameObject *gameObject = campaignMenuButton->get_gameObject();
    
    gameObject->SetActive(false);
}


// Called at the early stages of game loading
extern "C" void setup(ModInfo& info) {
    info.id = MOD_ID;
    info.version = VERSION;
    modInfo = info;
	
    getConfig().Load();
    getLogger().info("Completed setup!");
}

// Called later on in the game loading - a good time to install function hooks
extern "C" void load() {
    il2cpp_functions::Init();

    getLogger().info("Installing hooks...");
    INSTALL_HOOK(getLogger(), FuckSoloButton);
    getLogger().info("threw away the solo button");
    INSTALL_HOOK(getLogger(), FuckPartyButton);
    getLogger().info("threw away the party button");
    INSTALL_HOOK(getLogger(), FuckOnlineButton);
    getLogger().info("threw away the multiplayer button");
    INSTALL_HOOK(getLogger(), FuckAdvertisementButton);
    getLogger().info("threw away the advertisement");
    INSTALL_HOOK(getLogger(), FuckCampaignButton);
    getLogger().info("threw away the campaign button");
    getLogger().info("Youre welcome!");
}