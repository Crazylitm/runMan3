#include "AccelerometerTest.h"
//#include "../testResource.h"
#include "cocos2d.h"
#include <iostream>
#include <string>

USING_NS_CC;

#define FIX_POS(_pos, _min, _max) \
    if (_pos < _min)        \
    _pos = _min;        \
else if (_pos > _max)   \
    _pos = _max;        \

//------------------------------------------------------------------
//
// AccelerometerTest
//
//------------------------------------------------------------------
AccelerometerTest::AccelerometerTest(void)
: m_fLastTime(0.0)
{
    oldP.timestamp =0.0;
    MaxP.timestamp =0.0;
    oldV =0.0;
    oldA =0.0;
    CurA =0.0;
    CurV =0.0;
}


AccelerometerTest::~AccelerometerTest(void)
{
    m_pBall->release();
}

CCScene* AccelerometerTest::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    AccelerometerTest *layer = AccelerometerTest::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}
std::string AccelerometerTest::title()
{
    return "加速器";
}

bool AccelerometerTest::init()
{
   // CCLayer::onEnter();
    if ( !CCLayer::init() )
    {
        return false;
    }
    
    setAccelerometerEnabled(true);
    visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    origin = CCDirector::sharedDirector()->getVisibleOrigin();
    CCLog("visibleSize.width=%f,visibleSize.height=%f,origin.x=%f,origin.y=%f",visibleSize.width,visibleSize.height,origin.x,origin.y);

    label = CCLabelTTF::create(title().c_str(), "Arial", 32);
    addChild(label, 1);
    label->setPosition( ccp(visibleSize.width/2, visibleSize.height/2+100) );
    
    oldlabel = CCLabelTTF::create(title().c_str(), "Arial", 32);
    addChild(oldlabel, 1);
    oldlabel->setPosition( ccp(visibleSize.width/2, visibleSize.height/2+130) );
    
    maxlabel = CCLabelTTF::create(title().c_str(), "Arial", 32);
    addChild(maxlabel, 1);
    maxlabel->setPosition( ccp(visibleSize.width/2, visibleSize.height/2+160) );
    
    m_pBall = CCSprite::create("ball.png");
    
    m_pBall->setPosition(ccp(visibleSize.width/2, visibleSize.height/2));
    addChild(m_pBall);

    m_pBall->retain();
    
   // mygis.init();//初始化定位
    return true;
}

void AccelerometerTest::didAccelerate(CCAcceleration* pAccelerationValue)
{
//     double fNow = pAccelerationValue->timestamp;
// 
//     if (m_fLastTime > 0.0)
//     {
//         CCPoint ptNow = convertToUI
//     }
// 
//     m_fLastTime = fNow;

    CCDirector* pDir = CCDirector::sharedDirector();

    /*FIXME: Testing on the Nexus S sometimes m_pBall is NULL */
    if ( m_pBall == NULL ) {
        return;
    }
    if(oldP.timestamp == 0.0)
    {
        oldP.x = pAccelerationValue->x;
        oldP.y = pAccelerationValue->y;
        oldP.z = pAccelerationValue->z;
        oldP.timestamp = pAccelerationValue->timestamp;

    }
    else
    {
        double jian_x,jian_y,jian_z,jian_time;
        
        jian_x = (oldP.x - pAccelerationValue->x) ;if(jian_x<0)jian_x=-jian_x;
        jian_y = (oldP.y - pAccelerationValue->y) ;if(jian_y<0)jian_y=-jian_y;
        jian_z = (oldP.z - pAccelerationValue->z) ;if(jian_z<0)jian_z=-jian_z;
        jian_time = (oldP.timestamp - pAccelerationValue->timestamp);if(jian_time<0)jian_time=-jian_time;
        
        double length;
        length = sqrt(jian_x*jian_x+jian_y*jian_y+jian_z*jian_z);
        if(length !=0 && jian_time !=0){
            CurV = length / jian_time;
        }
        if(oldV == 0.0){
            oldV = CurV;
            CurA = CurV / jian_time;
            
        }
        else{
            CurA = (CurV - oldV)/jian_time;
            
        }
        if(CurA >= 300)
        {
        CCLOG("jian_x=%f,jian_y=%f,jian_z=%f,jian_time=%f,length=%f",jian_x,jian_y,jian_z,jian_time,length);
        CCLOG("oldP.x=%f,oldP.y=%f,oldP.z=%f,oldP.timestamp=%f",oldP.x,oldP.y,oldP.z,oldP.timestamp);
        CCLOG("cur.x=%f,cur=%f,cur=%f,cur.timestamp=%f",pAccelerationValue->x,pAccelerationValue->y,pAccelerationValue->z,pAccelerationValue->timestamp);
        CCLOG("oldV=%f,CurV=%f,oldA=%f,CurA=%f",oldV,CurV,oldA,CurA);
            char msg[100];
            sprintf(msg, "timestamp=%f",pAccelerationValue->timestamp);
            HttpGetTest(msg);
            //获取地理位置
           // CCLOG("[latitude=%f,longitude=%f][horizontal=%f,vertical=%f][timestamp=%f]",mygis.getLatitude(),mygis.getLongitude(),mygis.getHorizontal(),mygis.getVertical(),mygis.getTimestamp());
            
        }
        if (MaxP.timestamp ==0.0) {
            MaxP.x = pAccelerationValue->x;
            MaxP.y = pAccelerationValue->y;
            MaxP.z = pAccelerationValue->z;
            MaxP.timestamp = pAccelerationValue->timestamp;
        }
        oldP.x = pAccelerationValue->x;
        oldP.y = pAccelerationValue->y;
        oldP.z = pAccelerationValue->z;
        oldP.timestamp = pAccelerationValue->timestamp;
    }

    CCSize ballSize  = m_pBall->getContentSize();

    CCPoint ptNow  = m_pBall->getPosition();
    CCPoint ptTemp = pDir->convertToUI(ptNow);

    ptTemp.x += pAccelerationValue->x * 9.81f;
    ptTemp.y -= pAccelerationValue->y * 9.81f;
    
    CCPoint ptNext = pDir->convertToGL(ptTemp);
    FIX_POS(ptNext.x, (origin.x+ballSize.width / 2.0), (origin.x+visibleSize.width - ballSize.width / 2.0));
    FIX_POS(ptNext.y, (origin.y+ballSize.height / 2.0), (origin.y+visibleSize.height - ballSize.height / 2.0));
    m_pBall->setPosition(ptNext);
    char str[100];
    sprintf(str,"[x=%f,y=%f,z=%f][time=%f]",pAccelerationValue->x,pAccelerationValue->y,pAccelerationValue->z,pAccelerationValue->timestamp);
    label->setString(str);
    
    oldA = CurA;//保存上次的加速度
    sprintf(str,"[curV=%f,oldV=%f,curA=%f,oldA=%f]", CurV,oldV,CurA,oldA);
    oldlabel->setString(str);
    
    sprintf(str,"[ox=%f,oy=%f,oz=%f][otime=%f]",oldP.x,oldP.y,oldP.z,oldP.timestamp);
    maxlabel->setString(str);
    
    
   
}


void AccelerometerTest::onHttpRequestCompleted(cocos2d::extension::CCHttpClient *sender, cocos2d::extension::CCHttpResponse *response){
    if (!response)
    {
        return;
    }
    
    // You can get original request type from: response->request->reqType
    if (0 != strlen(response->getHttpRequest()->getTag()))
    {
        CCLog("%s completed", response->getHttpRequest()->getTag());
    }
    
    int statusCode = response->getResponseCode();
    char statusString[64] = {};
    sprintf(statusString, "HTTP Status Code: %d, tag = %s", statusCode, response->getHttpRequest()->getTag());
    //m_labelStatusCode->setString(statusString);
    CCLog("response code: %d", statusCode);
    
    if (!response->isSucceed())
    {
        CCLog("response failed");
        CCLog("error buffer: %s", response->getErrorBuffer());
        return;
    }
    
    // dump data
    std::vector<char> *buffer = response->getResponseData();
    printf("Http Test, dump data: ");
    for (unsigned int i = 0; i < buffer->size(); i++)
    {
        printf("%c", (*buffer)[i]);
    }
    printf("\n");
}
void AccelerometerTest::HttpGetTest(char *sendmsg){
    CCHttpRequest* request = new CCHttpRequest();
    char msg[100];
    sprintf(msg, "http://litianmin.com/litm/index.php?timestamp=%s",sendmsg);
    request->setUrl(msg);
    request->setRequestType(CCHttpRequest::kHttpGet);
    request->setResponseCallback(this, httpresponse_selector(AccelerometerTest::onHttpRequestCompleted));
    
    request->setTag("GET OK");
    CCHttpClient::getInstance()->send(request);
    request->release();
    printf("Get Success!\n");
}
//------------------------------------------------------------------
//
// AccelerometerTestScene
//
//------------------------------------------------------------------
/*
void AccelerometerTestScene::runThisTest()
{
    CCLayer* pLayer = new AccelerometerTest();
    addChild(pLayer);
    pLayer->release();

    CCDirector::sharedDirector()->replaceScene(this);
}*/
