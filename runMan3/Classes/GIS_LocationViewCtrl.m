//
//  GIS_LocationViewCtrl.m
//  runManTest
//
//  Created by crazywork on 14-2-26.
//
//

#import "GIS_LocationViewCtrl.h"

@implementation GIS_LocationViewCtrl

#import <CoreLocation/CoreLocation.h>
@synthesize man;
static GIS_LocationViewCtrl *sharedEngine = nil;
+ (GIS_LocationViewCtrl *) sharedEngine
{
    @synchronized(self)     {
        if (!sharedEngine)
            sharedEngine = [[GIS_LocationViewCtrl alloc] init];
    }
    return sharedEngine;
}
- (GIS_LocationViewCtrl*)init {
    [super viewDidLoad];
    man = [[CLLocationManager alloc] init];
    hadLoadlocationManagerFunFlag = false;
    // 如果可以利用本地服务时
    if([man locationServicesEnabled]){
        // 接收事件的实例
        man.delegate = self;
        // 发生事件的的最小距离间隔（缺省是不指定）
        man.distanceFilter = kCLDistanceFilterNone;
        // 精度 (缺省是Best)
        man.desiredAccuracy = kCLLocationAccuracyBest;
        // 开始测量
        [man startUpdatingLocation];
    }
    return man;
}

// 如果GPS测量成果以下的函数被调用
- (void)locationManager:(CLLocationManager *)manager
    didUpdateToLocation:(CLLocation *)newLocation
           fromLocation:(CLLocation *)oldLocation{
    //调用了
    hadLoadlocationManagerFunFlag = true;
    // 取得经纬度
     coordinate = newLocation.coordinate;
     latitude = coordinate.latitude;
     longitude = coordinate.longitude;
    // 取得精度
     horizontal = newLocation.horizontalAccuracy;
     vertical = newLocation.verticalAccuracy;
    // 取得高度
     altitude = newLocation.altitude;
    // 取得时刻
     timestamp = [newLocation timestamp];
    
    // 以下面的格式输出 format: <latitude>, <longitude>> +/- <accuracy>m @ <date-time>
    NSLog([newLocation description]);
    
    // 与上次测量地点的间隔距离
    if(oldLocation != nil){
        CLLocationDistance d = [newLocation getDistanceFrom:oldLocation];
        NSLog([NSString stringWithFormat:@"%f", d]);
    }
}

// 如果GPS测量失败了，下面的函数被调用
- (void)locationManager:(CLLocationManager *)manager
       didFailWithError:(NSError *)error{
    NSLog([error localizedDescription]);
}
@end
