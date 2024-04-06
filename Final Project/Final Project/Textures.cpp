#include "Textures.h"
#include <filesystem>

Textures& Textures::GetInstance() 
{
    static Textures instance;
    return instance;
}

// Private constructor to prevent instantiation
Textures::Textures() 
{
    SetupTextures();
}

void Textures::SetupTextures() 
{

    // World
    tilesTexture.loadFromFile((std::filesystem::current_path() / "../../tiles.png").string());
    textureMap["tiles"] = tilesTexture;

    fogTexture.loadFromFile("./assets/images/fog.png");
    textureMap["fog"] = fogTexture;

    bloodTexture.loadFromFile("./assets/images/blood.png");
    textureMap["blood"] = bloodTexture;

    sucklerTrailTexture.loadFromFile("./assets/images/suckler-trail.png");
    textureMap["suckler-trail"] = sucklerTrailTexture;

    smokeTexture.loadFromFile("./assets/images/smoke.png");
    textureMap["smoke"] = smokeTexture;

    goldParticleTexture.loadFromFile("./assets/images/gold-particle.png");
    textureMap["gold-icon"] = goldParticleTexture;

    goopTexture.loadFromFile("./assets/images/goop.png");
    textureMap["goop"] = goopTexture;

    oilDropTexture.loadFromFile("./assets/images/oil-drop.png");
    textureMap["oil-drop"] = oilDropTexture;

    sucklerHeadTexture.loadFromFile("./assets/images/suckler-head.png");
    textureMap["suckler-head"] = sucklerHeadTexture;

    sucklerTentacleTexture.loadFromFile("./assets/images/suckler-tentacle.png");
    textureMap["suckler-tentacle"] = sucklerTentacleTexture;

    arrowTexture.loadFromFile("./assets/images/arrow.png");
    textureMap["arrow"] = arrowTexture;



    // Projectiles
    blastTexture.loadFromFile("./assets/images/blast.png");
    textureMap["blast"] = blastTexture;

    blastTrailTexture.loadFromFile("./assets/images/blast-trail.png");
    textureMap["blast-trail"] = blastTrailTexture;

    spitTexture.loadFromFile("./assets/images/spit.png");
    textureMap["spit"] = spitTexture;

    shieldTexture.loadFromFile("./assets/images/shield.png");
    textureMap["shield"] = shieldTexture;

    flamingSwordTexture.loadFromFile("./assets/images/flaming-sword.png");
    textureMap["flaming-sword"] = flamingSwordTexture;

    flamingTrailTexture.loadFromFile("./assets/images/fire-trail.png");
    textureMap["fire-trail"] = flamingTrailTexture;


    // Characters
        warriorTexture.loadFromFile("./assets/images/warrior.png");
        textureMap["warrior"] = warriorTexture;

        archerTexture.loadFromFile("./assets/images/mage.png");
        textureMap["archer"] = archerTexture;

        minerTexture.loadFromFile("./assets/images/worker.png");
        textureMap["miner"] = minerTexture;

        miner2Texture.loadFromFile("./assets/images/worker2.png");
        textureMap["miner2"] = miner2Texture;

        miner3Texture.loadFromFile("./assets/images/worker3.png");
        textureMap["miner3"] = miner3Texture;

        miner4Texture.loadFromFile("./assets/images/worker4.png");
        textureMap["miner4"] = miner4Texture;

        miner5Texture.loadFromFile("./assets/images/worker5.png");
        textureMap["miner5"] = miner5Texture;

        oilManTexture.loadFromFile("./assets/images/oil-man.png");
        textureMap["oil-man"] = oilManTexture;

        hazmatManTexture.loadFromFile("./assets/images/hazmat-man.png");
        textureMap["hazmat-man"] = hazmatManTexture;

        enemyTexture.loadFromFile("./assets/images/enemy2.png");
        textureMap["enemy"] = enemyTexture;

        sucklerTexture.loadFromFile("./assets/images/suckler.png");
        textureMap["suckler"] = sucklerTexture;

        suckler2Texture.loadFromFile("./assets/images/suckler2.png");
        textureMap["suckler2"] = suckler2Texture;

        sucklerDeadTexture.loadFromFile("./assets/images/suckler-dead.png");
        textureMap["suckler-dead"] = sucklerDeadTexture;

        bigSucklerTexture.loadFromFile("./assets/images/suckler-big.png");
        textureMap["big-suckler"] = bigSucklerTexture;

        bigSucklerDeadTexture.loadFromFile("./assets/images/suckler-big-dead.png");
        textureMap["big-suckler-dead"] = bigSucklerDeadTexture;

        gumperTexture.loadFromFile("./assets/images/gumper.png");
        textureMap["gumper"] = gumperTexture;

        bigGumperTexture.loadFromFile("./assets/images/gumper-big.png");
        textureMap["big-gumper"] = bigGumperTexture;

        spaceshipsTexture.loadFromFile("./assets/images/spaceships.png");
        textureMap["spaceship"] = spaceshipsTexture;

        eggTexture.loadFromFile("./assets/images/egg.png");
        textureMap["egg"] = eggTexture;


    // Buildings
        baseTexture.loadFromFile("./assets/images/base.png");
        textureMap["hq"] = baseTexture;

        mineTexture.loadFromFile("./assets/images/mine.png");
        textureMap["mine"] = mineTexture;

        oilExtractorTexture.loadFromFile("./assets/images/oil2.png");
        textureMap["oil"] = oilExtractorTexture;

        uraniumExtractorTexture.loadFromFile("./assets/images/reactor.png");
        textureMap["uranium"] = uraniumExtractorTexture;

    // UI
        coinTexture.loadFromFile("./assets/images/coin.png");
        textureMap["coin"] = coinTexture;

        rotateTexture.loadFromFile("./assets/images/rotate.png");
        textureMap["rotate"] = rotateTexture;

        scaleTexture.loadFromFile("./assets/images/scale.png");
        textureMap["scale"] = scaleTexture;

        buildHammerTexture.loadFromFile("./assets/images/build-hammer.png");
        textureMap["build-hammer"] = buildHammerTexture;       
        
        trainUnitsTexture.loadFromFile("./assets/images/train-units.png");
        textureMap["train-units"] = trainUnitsTexture;




    // UI - Icons
        // Units
            warriorButtonIconTexture.loadFromFile("./assets/images/warrior-icon.png");
            textureMap["warrior-icon"] = warriorButtonIconTexture;

            archerButtonIconTexture.loadFromFile("./assets/images/archer-icon.png");
            textureMap["archer-icon"] = archerButtonIconTexture;

            minerButtonIconTexture.loadFromFile("./assets/images/worker-icon.png");
            textureMap["miner-icon"] = minerButtonIconTexture;

            oilManButtonIconTexture.loadFromFile("./assets/images/oil-man-icon.png");
            textureMap["oil-man-icon"] = oilManButtonIconTexture;

            hazmatManButtonIconTexture.loadFromFile("./assets/images/hazmat-man-icon.png");
            textureMap["hazmat-man-icon"] = hazmatManButtonIconTexture;

        // Buildings

            goldMineButtonIconTexture.loadFromFile("./assets/images/mine-icon.png");
            textureMap["mine-icon"] = goldMineButtonIconTexture;

            oilExtractorButtonIconTexture.loadFromFile("./assets/images/oil-icon.png");
            textureMap["oil-icon"] = oilExtractorButtonIconTexture;

            uraniumExtractorButtonIconTexture.loadFromFile("./assets/images/reactor-icon.png");
            textureMap["reactor-icon"] = uraniumExtractorButtonIconTexture;
    


    // Main Menu
       menuBackgroundTexture.loadFromFile("./assets/images/parallax-bg.png");
       textureMap["menu-bg"] = menuBackgroundTexture;

       menuMountainFarTexture.loadFromFile("./assets/images/parallax-mountain-far.png");
       textureMap["menu-mountain-far"] = menuMountainFarTexture;

       menuMountainCloseTexture.loadFromFile("./assets/images/parallax-mountain-close.png");
       textureMap["menu-mountain-close"] = menuMountainCloseTexture;

       menuTreesFarTexture.loadFromFile("./assets/images/parallax-trees-far.png");
       textureMap["menu-trees-far"] = menuTreesFarTexture;

       menuTreesCloseTexture.loadFromFile("./assets/images/parallax-trees-close.png");
       textureMap["menu-trees-close"] = menuTreesCloseTexture;
}

sf::Texture& Textures::GetTexture(const std::string& textureName) 
{
    return textureMap[textureName];
}
