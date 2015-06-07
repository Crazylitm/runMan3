//
//  GisGet.h
//  runManTest
//
//  Created by crazywork on 14-2-26.
//
//

#ifndef runManTest_GisGet_h
#define runManTest_GisGet_h


namespace CocosGis {
class CGisGet {
public:
    void init();
    double getLatitude();
    
    double getLongitude();
    double getHorizontal();
    double getVertical();
    double getTimestamp();
    
private:
    // 取得经纬度
    double latitude ;
    double longitude ;
    // 取得精度
    double horizontal ;
    double vertical ;
    // 取得高度
    double altitude ;
    // 取得时刻
    double timestamp ;
    //GIS_LocationViewCtrl *p_Gis;
    
};
};

#endif
