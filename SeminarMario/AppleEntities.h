#pragma once
#include"Entities.h"
#include "Entities.h"
#include "opencv2/opencv.hpp"
#include "Config.h"
#include <memory>
#include <filesystem>
class Singleton;  // Forward declaration of Singleton class
using namespace std;
namespace fs = std::filesystem;
//Mat Singleton::canvas = cv::Mat();

class AppleEntities :public Entity
{

public:
	AppleEntities();
	~AppleEntities();
	virtual void onNotify(Event const& e) override;
	EntityPtr createApple();

	EntityStatePtr CreateAppleState();
private:
};

typedef std::shared_ptr<AppleEntities> AppleEntityPtr;
