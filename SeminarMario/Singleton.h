#include "EntitiesPool.h"
#include "SlimeEntity.h"
#include "LiveEntity.h"
#include <opencv2/opencv.hpp>
#include "AppleEntities.h"
#include "HeroEntity.h"
#include "CoinEntity.h"
#include"WallEntity.h"
using namespace cv;
class Singleton {
private:
    Singleton()
    {

    }  // Private constructor to prevent direct instantiation

    static EntitiesPoolPtr slimePool;  // Static member variable to hold the single instance
    static LiveEntityPtr heart;
    static HeroEntityPtr hero;
    //Mat background = imread(R"(../Animations/background.png)", IMREAD_UNCHANGED);
    //Mat canvas = background.clone();
    static Mat background;
    static Mat canvas;
    static AppleEntityPtr apple;
    static cv::Point heroPlace;
    static EntitiesPoolPtr coinPool;
    static EntitiesPoolPtr wallPool;
    static EntityPtr  currentWall;
    static bool isWall1;
    static bool isJamp;
    static bool isFall;
    static int numCurrntWall;
    //static std::vector<EntityPtr> wallU

public:
    static Mat getCanvas();
    static AppleEntityPtr getApple();
    static Mat getBackground();
    static EntitiesPoolPtr getSlimePool();
    static EntitiesPoolPtr getCoinPool();
    static EntitiesPoolPtr getWallPool();

    static LiveEntityPtr getHeart();
    static cv::Point getHeroPlace();
    static void setHeroPlace(cv::Point& p);
    static bool getIsFall();
    static void setIsFall(bool is);
    static HeroEntityPtr getHeroEntity();
    static void setHeroEntity(HeroEntityPtr p);
    static EntityPtr getCurrentWall();
    static void setCurrentWall(EntityPtr& p);
    static bool getIsWall1();
    static void setIsWall1(bool p);
    static bool getIsJamp();
    static void setIsJamp(bool p);

    static int getNumCurrntWall();
    static void setNumCurrntWall(int p);
};
