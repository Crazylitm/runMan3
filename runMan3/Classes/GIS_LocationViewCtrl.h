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
    NSDate *timestamp ;
    BOOL hadLoadlocationManagerFunFlag;
    
}
@property(nonatomic, retain) CLLocationManager *man;
@property(nonatomic) BOOL hadLoadlocationManagerFunFlag;
@property(nonatomic) CLLocationCoordinate2D coordinate ;
@property(nonatomic) CLLocationDegrees latitude ;
@property(nonatomic) CLLocationDegrees longitude ;
@property(nonatomic) CLLocationAccuracy horizontal ;
@property(nonatomic) CLLocationAccuracy vertical ;
@property(nonatomic) CLLocationDistance altitude ;
@property(nonatomic) NSDate *timestamp ;

//+( GIS_LocationViewCtrl * ) sharedEngineFun;
@end
