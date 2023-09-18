#include "Animation.h"
#include <opencv2/opencv.hpp>
#include "Timer.h"
#include "HeroEntity.h"
#include "Config.h"
#include "SlimeEntity.h"
#include "EntitiesPool.h"
#include "Singleton.h"
#include "LiveEntity.h"
#include"AppleEntities.h"
using namespace cv;
EntitiesPoolPtr Singleton::slimePool = nullptr;
EntitiesPoolPtr Singleton::coinPool = nullptr;
EntitiesPoolPtr Singleton::wallPool = nullptr;
LiveEntityPtr Singleton::heart = nullptr;
HeroEntityPtr Singleton::hero = nullptr;
Mat Singleton::canvas = cv::Mat();
Mat Singleton::background = cv::Mat();
AppleEntityPtr Singleton::apple=nullptr;
EntityPtr Singleton::currentWall = nullptr;
cv::Point Singleton::heroPlace = cv::Point();
bool Singleton :: isFall = false;
bool Singleton::isWall1 = false;
bool Singleton::isJamp = false;
int Singleton::numCurrntWall = -1;

int main()
{
	Singleton* singlenton;
	Singleton::getSlimePool();
	Mat background =Singleton::getBackground();
	int screen_width = 1280;
	int screen_height = 720;
	cv::resize(background, background, cv::Size(screen_width, screen_height));


	Singleton* slimePool;
	EntityPtr slime = slimePool->getSlimePool()->getNext();
	slime->reset(Point(background.size().width * 2 / 4.5-300, background.size().height * 4 / 5));
	
	Singleton* coinS;
	EntityPtr coin = coinS->getCoinPool()->getNext();
	coin->reset(Point(background.size().width * 2 / 2.5-600, background.size().height * 3/ 5));

	Singleton* wallS;
	EntityPtr wall = wallS->getWallPool()->getNext();
	wall->reset(Point(background.size().width * 2 / 2.5-600, background.size().height * 3 / 5+100));

	//Singleton* wallS;
	//EntityPtr wall1 = wallS->getWall1();
	//wallS->setWall1((createWall(R"(../Animations/wall)")));

	//wall1->reset(Point(background.size().width  - 300, background.size().height- 150));

	
	EntityPtr coin2 = singlenton->getCoinPool()->getNext();
	coin2->reset(Point(background.size().width * 2 / 2.5 - 250, background.size().height * 3 / 5 -150));

	EntityPtr wall2 = singlenton->getWallPool()->getNext();
	wall2->reset(Point(background.size().width * 2 / 2.5 - 250, background.size().height * 3 / 5-50));


	EntityPtr wall3 = singlenton->getWallPool()->getNext();
	wall3->reset(Point(background.size().width -300, background.size().height -110));


	exampleOfPutText(background);

	Singleton* hearts;

	HeroEntityPtr hero = std::make_shared<HeroEntity>(R"(../Animations/Hero)", background.size().height * 2 / 3, screen_width);
	hero->reset(Point(background.size().width / 80+10, background.size().height * 2 / 3-10));
	singlenton->setHeroEntity(hero);
	std::shared_ptr<AppleEntities> apple = singlenton->getApple();

	Timer timer(/*freq. ms=*/100);
	timer.Register(slime);
	timer.Register(singlenton->getHeroEntity());
	//timer.Register(singlenton->getApple());
	//apple->reset(Point(hero->getState()->getPhysics()->getTL().x + 50, hero->getState()->getPhysics()->getTL().y));
	timer.Register(apple);
	timer.Register(coin);
	//timer.Register(wall1);

	bool isToExit = false;

	while (false == isToExit)
	{
		hero->getState()->Register(hero);
		hero->getState()->Register(hearts->getHeart());
		apple->getState()->Register(hearts->getHeart());
		//צריך לרשום את הלבבות שיאזינו לילדה
		//coin->getState()->Register();
		Mat canvas = background.clone();
		timer.tick();
		int lenSlime = singlenton->getSlimePool()->getPool().size() - 1;
		for (int i = 0; i < lenSlime; i++)
		{
			if (singlenton->getSlimePool()->getIsInUse()[i])
			{
				singlenton->getSlimePool()->getPool()[i]->draw(canvas);
			}
		}
		int lenCoin = singlenton->getCoinPool()->getPool().size() - 1;
		for (int i = 0; i < lenCoin; i++)
		{
			if (singlenton->getCoinPool()->getIsInUse()[i])
			{
				singlenton->getCoinPool()->getPool()[i]->draw(canvas);
			}
		}
		int lenWall = singlenton->getWallPool()->getPool().size() - 1;
		for (int i = 0; i < lenCoin; i++)
		{
			if (singlenton->getWallPool()->getIsInUse()[i])
			{
				singlenton->getWallPool()->getPool()[i]->draw(canvas);
			}
		}
		hearts->getHeart()->getState()->getGraphics()->draw(canvas, Point(1080, 50));
		hero->draw(canvas);
		apple->draw(canvas);
		cv::Point p = hero->getState()->getPhysics()->getTL();
		singlenton->setHeroPlace(p);
		singlenton->setHeroEntity(hero);
		imshow("test", canvas);
	}

	return 0;
}
