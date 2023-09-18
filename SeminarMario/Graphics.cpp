#include "Graphics.h"
#include <algorithm>

using namespace cv;
using namespace std;

//////////////////////////////////////////////////

SingleAnimationGraphics::SingleAnimationGraphics(AnimationPtr animPtr, bool isCyclic)
    :_animation(animPtr), _currFrameIdx(0)
    , _isCyclic(isCyclic)
{
}


cv::Mat SingleAnimationGraphics::getCollisionMask()
{
    return _animation->getFrame(_currFrameIdx).mask;
}

void SingleAnimationGraphics::draw(cv::Mat& canvas, cv::Point const& topLeft)
{
    drawFrame(_animation->getFrame(_currFrameIdx), canvas, topLeft);
}

void SingleAnimationGraphics::reset(int code)
{
    _currFrameIdx = 0;
}

bool SingleAnimationGraphics::update()
{
    bool hasFinished = (_currFrameIdx == _animation->numFrames() - 1);
    if (_isCyclic)
        _currFrameIdx = (_currFrameIdx + 1) % _animation->numFrames();
    else
        _currFrameIdx = min<int>(_currFrameIdx + 1, (int)_animation->numFrames() - 1);

    return hasFinished;
}


//////////////////////////////////////////////////

void exampleOfPutText(cv::Mat back)
{
    string text = "score: ";
    int score = 465;
    string moreText = to_string(score);
    text = text + moreText;
    Point topLeft(50, 50);
    int fontFace = FONT_HERSHEY_SIMPLEX; // normal size sans - serif font
    // other options for fontFace:
    FONT_HERSHEY_PLAIN;// small size sans - serif font
    FONT_HERSHEY_DUPLEX;// normal size sans - serif font(more complex than FONT_HERSHEY_SIMPLEX)
    FONT_HERSHEY_COMPLEX; // normal size serif font
    FONT_HERSHEY_TRIPLEX; //normal size serif font(more complex than FONT_HERSHEY_COMPLEX)
    FONT_HERSHEY_COMPLEX_SMALL; //smaller version of FONT_HERSHEY_COMPLEX
    FONT_HERSHEY_SCRIPT_SIMPLEX; //hand - writing style font
    FONT_HERSHEY_SCRIPT_COMPLEX;// more complex variant of FONT_HERSHEY_SCRIPT_SIMPLEX
    double fontScale = 2; // Font scale factor that is multiplied by the font-specific base size.
    Scalar color(/*Blue between 0...255 =*/0,/*Green between 0...255 =*/0,/*Red between 0...255 =*/255);
    int thickness = 2;
    int lineType = LINE_AA;
    // other options for line type:
    LINE_4; LINE_8; LINE_AA;

    // finally:
    putText(back, text, topLeft, fontFace, fontScale, color, thickness, lineType);

    imshow("test", back);
}

LivesGraphics::LivesGraphics() :_singleLife(Frame(R"(../Animations/heart.png)")), _livesCount(4)
{
}

cv::Mat LivesGraphics::getCollisionMask()
{
    return _singleLife.mask;
}

void LivesGraphics::draw(cv::Mat& canvas, cv::Point const& topLeft)
{
    cv::Point curr = topLeft;
    for (int i = 0; i < _livesCount; i++)
    {
        drawFrame(_singleLife, canvas, curr);
        curr.x -= 100;
    }
}


void LivesGraphics::reset(int code)
{
    _livesCount+=code;
}

bool LivesGraphics::update()
{
    return false;
}


ScoresGraphics::ScoresGraphics(float _fontScale, int _score, int _fontFace) :_fontScale(_fontScale), _score(_score), _fontFace(_fontFace) {

}

cv::Mat ScoresGraphics::getCollisionMask()
{
    return cv::Mat();
}

void ScoresGraphics::draw(cv::Mat& canvas, cv::Point const& topLeft)
{
}

void ScoresGraphics::reset(int code)
{
    _score = code;
}

bool ScoresGraphics::update()
{
    return false;
}

AppleGraphics::AppleGraphics() :_singleLife(Frame(R"(../Animations/apple_360.png)"))
,_isDraw(false),_appleCount(5)
{
}

cv::Mat AppleGraphics::getCollisionMask()
{
    return _singleLife.mask;
}

void AppleGraphics::draw(cv::Mat& canvas, cv::Point const& topLeft)
{
    if (_isDraw && _appleCount > 0)
        drawFrame(_singleLife, canvas, topLeft);
}

void AppleGraphics::reset(int code)
{
    _appleCount--;
    _isDraw = !_isDraw;
}

bool AppleGraphics::update()
{
    //_isDraw = !_isDraw;
    //_isDraw = true;
    return false;
}

//
//CoinGraphics::CoinGraphics() :_singleLife(Frame(R"(../Animations/coin_360.png)")), _coinsCount(4)
//{
//}
//
//cv::Mat CoinGraphics::getCollisionMask()
//{
//    return _singleLife.mask;
//}
//
//void CoinGraphics::draw(cv::Mat& canvas, cv::Point const& topLeft)
//{
//    //cv::Point curr = topLeft;
//    //for (int i = 0; i < _livesCount; i++)
//    //{
//    //    drawFrame(_singleLife, canvas, curr);
//    //    curr.x -= 100;
//    //}
//}
//
//
//void CoinGraphics::reset(int code)
//{
//}
//
//bool CoinGraphics::update()
//{
//    return false;
//}
//
