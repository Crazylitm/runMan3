#ifndef _ACCELEROMETER_TEST_H_
#define _ACCELEROMETER_TEST_H_

//#include "../testBasic.h"
#include "cocos2d.h"
#include "cocos-ext.h"
#include "GisGet.h"
USING_NS_CC;
USING_NS_CC_EXT;
using namespace std;

class AccelerometerTest: public cocos2d::CCLayer
{
protected:
    CCSprite* m_pBall;
    CCSprite* m_pRunmanlitm4;
    CCSprite* m_pRunmanlitm5;
    double    m_fLastTime;
    CCSize visibleSize ;
    CCPoint origin ;
    CCLabelTTF* label;
    CCLabelTTF* oldlabel;
    CCLabelTTF* maxlabel;
    CCLabelTTF* gislabel;
    
    CCLabelTTF* sPritelabel;
    CCLabelTTF* sPritelabellitm4;
    CCLabelTTF* sPritelabellitm5;
    CCAcceleration oldP;
    CCAcceleration MaxP;
    double oldV;
    double oldA;
    double CurV;
    double CurA;
   CocosGis::CGisGet mygis;
public:
    AccelerometerTest(void);
    ~AccelerometerTest(void);

    virtual void didAccelerate(CCAcceleration* pAccelerationValue);

    virtual std::string title();
     virtual bool init();
    CREATE_FUNC(AccelerometerTest);
    static cocos2d::CCScene* scene();
    
    //Http Response Callback
    void onHttpRequestCompleted(cocos2d::extension::CCHttpClient *sender, cocos2d::extension::CCHttpResponse *response);
    void HttpGetTest(char *sendmsg);
    
private:
    void rev_peng_peng_sprite(char *pmsgrev);
    double getCurrentTime();
    double lastTime;
};
/*
class AccelerometerTestScene : public TestScene
{
public:
    virtual void runThisTest();
};*/

#endif
