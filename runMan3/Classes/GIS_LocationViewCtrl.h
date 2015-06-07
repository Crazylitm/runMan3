//
//  GIS_LocationViewCtrl.h
//  runManTest
//
//  Created by crazywork on 14-2-26.
//
//

#import <UIKit/UIKit.h>
#import <Foundation/Foundation.h>
#import <CoreLocation/CoreLocation.h>


@interface GIS_LocationViewCtrl : UIViewController <CLLocationManagerDelegate>{
    CLLocationManager *man;
    // 取得经纬度
    CLLocationCoordinate2D coordinate ;
    CLLocationDegrees latitude ;
    CLLocationDegrees longitude ;
    // 取得精度
    CLLocationAccuracy horizontal ;
    CLLocationAccuracy vertical ;
    // 取得高度
    CLLocationDistance altitude ;
    // 取得时刻
    NSTimeInterval timestamp ;
    BOOL hadLoadlocationManagerFunFlag;
    
}
@property(nonatomic, retain) CLLocationManager *man;


-(BOOL) getFlag;
-(CLLocationDegrees) getLatitude;
-(CLLocationDegrees) getLongitude;
-(CLLocationAccuracy) getHorizontal;
-(CLLocationAccuracy) getVertical;
-(CLLocationAccuracy) getAltitude;
-(NSTimeInterval) getTime1970;
+(GIS_LocationViewCtrl *) sharedEngine;



//+( GIS_LocationViewCtrl * ) sharedEngineFun;
@end
