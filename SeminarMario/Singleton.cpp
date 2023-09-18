#include "Singleton.h"

Mat Singleton::getCanvas()
{
   if(background.empty())
       background =getBackground();
   canvas = background.clone();
   return canvas;
}

AppleEntityPtr Singleton::getApple()
{
    if (apple==nullptr)
       apple=std::make_shared< AppleEntities>();    
    return apple;
}

Mat Singleton::getBackground()
{
    if (background.empty())
    {
        background = imread(R"(../Animations/background.png)", IMREAD_UNCHANGED);
        cv::resize(background, background, cv::Size(1200, 730));   
    }
    return background;
}

EntitiesPoolPtr Singleton::getSlimePool() {

    if (slimePool == nullptr) {
        slimePool = (std::make_shared<EntitiesPool>());
        int n = slimePool->getPool().size();
        for (int i = 0; i < n; i++)
        {
            slimePool->insert(createSlime(R"(../Animations/SlimeOrange)"), i);
        }
    }
    return slimePool;
}
EntitiesPoolPtr Singleton::getCoinPool()
{
    if (coinPool == nullptr) {
        coinPool = (std::make_shared<EntitiesPool>());
        int n = coinPool->getPool().size();
        for (int i = 0; i < n; i++)
        {
            coinPool->insert(createCoin(R"(../Animations/coin)"), i);
        }
    }
    return coinPool;
}
EntitiesPoolPtr Singleton::getWallPool()
{
    if (wallPool == nullptr) {
        wallPool = (std::make_shared<EntitiesPool>());
        int n = wallPool->getPool().size();
        for (int i = 0; i < n; i++)
        {
            wallPool->insert(createWall(R"(../Animations/wall)"), i);
        }
    }
    return wallPool;
}
LiveEntityPtr Singleton::getHeart() {
    if (heart == nullptr)
        heart = (std::make_shared<LiveEntity>());
    return heart;
}

cv::Point Singleton::getHeroPlace()
{
    if (heroPlace== cv::Point())
        heroPlace = cv::Point();
    return heroPlace;
}

void Singleton::setHeroPlace(cv::Point& p)
{
    heroPlace = p;
}

bool Singleton::getIsFall()
{
    return isFall;
}

void  Singleton::setIsFall(bool is)
{
     isFall=is;
}

HeroEntityPtr Singleton::getHeroEntity()
{
  /*  if (hero == nullptr)
        hero = (std::make_shared<HeroEntity>());*/
    return hero;
}

void Singleton::setHeroEntity(HeroEntityPtr p)
{
    hero = p;
}

EntityPtr Singleton::getCurrentWall()
{
    if(currentWall==nullptr)
        currentWall= (createWall(R"(../Animations/wall)"));
    return currentWall;
}

void Singleton::setCurrentWall(EntityPtr& p)
{
    currentWall = p;
}

bool Singleton::getIsWall1()
{
    return isWall1;
}

void Singleton::setIsWall1(bool p)
{
    isWall1 = p;
}

bool Singleton::getIsJamp()
{
    return isJamp;
}

void Singleton::setIsJamp(bool p)
{
    isJamp=p;
}

int Singleton::getNumCurrntWall()
{
    return numCurrntWall;
}

void Singleton::setNumCurrntWall(int p)
{
    numCurrntWall = p;
}


