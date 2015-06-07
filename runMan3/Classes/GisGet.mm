#import "GIS_LocationViewCtrl.h"
#import "GisGet.h"

static GIS_LocationViewCtrl* static_init(){
    return [GIS_LocationViewCtrl sharedEngine];
}
static double static_getLatitude(){
  //  BOOL hadflg = [[GIS_LocationViewCtrl sharedEngine] hadLoadlocationManagerFunFlag];
    //if(hadflg == false)return 0.0;
    return [[GIS_LocationViewCtrl sharedEngine] latitude];
    
}
static double static_getlongitude(){
  //  BOOL hadflg = [[GIS_LocationViewCtrl sharedEngine] hadLoadlocationManagerFunFlag];
   // if(hadflg == false)return 0.0;
    return [[GIS_LocationViewCtrl sharedEngine] longitude];
    
}
static double static_getHorizontal(){
  //  BOOL hadflg = [[GIS_LocationViewCtrl sharedEngine] hadLoadlocationManagerFunFlag];
  //  if(hadflg == false)return 0.0;
    return [[GIS_LocationViewCtrl sharedEngine] horizontal];
}

static double static_getVertical(){
   // BOOL hadflg = [[GIS_LocationViewCtrl sharedEngine] hadLoadlocationManagerFunFlag];
   // if(hadflg == false)return 0.0;
    return [[GIS_LocationViewCtrl sharedEngine] vertical];
}

static double static_getTimestamp(){
   // BOOL hadflg = [[GIS_LocationViewCtrl sharedEngine] hadLoadlocationManagerFunFlag];
   // if(hadflg == false)return 0.0;
    return 0.0;
}
void CocosGis::CGisGet::init(){
   
     //[[GIS_LocationViewCtrl alloc] init];
    
     static_init();
    
    
}
double CocosGis::CGisGet::getLatitude(){

    latitude = static_getLatitude();
    return latitude;
}


double CocosGis::CGisGet::getLongitude(){

    longitude = static_getlongitude();
    return longitude;
}
double CocosGis::CGisGet::getHorizontal(){

    horizontal  =  static_getHorizontal();
    return horizontal;
}
double CocosGis::CGisGet::getVertical(){

    vertical = static_getVertical();
    return vertical;
}
double CocosGis::CGisGet::getTimestamp(){

    timestamp = static_getTimestamp();
    return timestamp;
};