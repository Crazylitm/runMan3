//
//  HelloCocosBuilder.cpp
//  runManTest
//
//  Created by crazywork on 14-2-22.
//
//

#include "HelloCocosBuilder.h"



CCScene* HelloCocosBuilder::scene(){
    CCScene *scene = CCScene::create();
    
    CCNodeLoaderLibrary *lib = CCNodeLoaderLibrary::newDefaultCCNodeLoaderLibrary();
    
    CCBReader *reader = new CCBReader(lib);
    
    CCNode *node = reader->readNodeGraphFromFile("MainScene.ccbi",scene);
    
    reader->release();
    
    if (node != NULL) {
        scene->addChild(node);
    }
    return scene;
};