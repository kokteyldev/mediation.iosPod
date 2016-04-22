//
//  MSMAdHandler.h
//  DP
//
//  Created by Tolga Seremet on 24/08/15.
//  Copyright (c) 2015 Masomo. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
#import "ADMAd.h"
#import "ADMBannerHelper.h"
#import "MPAdView.h"
#import "MPNativeAd.h"
#import "MPNativeAdDelegate.h"
#import <AmazonAd/AmazonAdView.h>

#define ADHANDLER_TIMEOUT 2
typedef enum {
    ADMAdHandlerBannerLocationTypeInline = 1,
    ADMAdHandlerBannerLocationTypeInterstital = 2,
    ADMAdHandlerBannerLocationTypeUndefined = 0
} ADMAdHandlerBannerLocationType;

typedef enum {
    ADMAdHandlerBannerZoneNative,
    ADMAdHandlerBannerZoneBanner
} ADMAdHandlerBannerZone;

typedef enum {
    ADMAdHandlerBannerHeightLarge,
    ADMAdHandlerBannerHeightNormal
} ADMAdHandlerBannerHeight;

@protocol ADMAdLoadedDelegate
@optional
#pragma mark - ADM Banner Delegate Methods
- (void)didReceiveAd:(id)banner
        forPlacement:(NSString*)placement;
- (void)didFailToReceiveAd:(id)banner
              forPlacement:(NSString*)placement;
- (void)didReceiveAd:(id)banner
        forIndexPath:(NSIndexPath*)indexPath;
- (void)didFailToReceiveAdForPlacement:(NSString*)placement;
- (void)didFailToReceiveAdForPlacement:(NSString*)placement sender:(id)sender;
- (void)didDismissInterstitialForPlacement:(NSString*)placement;
- (void)didReceiveInterstitial:(id)banner forPlacement:(NSString*)placement;
- (void)didFailToReceiveInterstitial:(id)banner forPlacement:(NSString*)placement;
- (void)didFailToReceiveInterstitialForPlacement:(NSString*)placement;
- (void)didFailToReceiveInterstitialForPlacement:(NSString*)placement sender:(id)sender;


- (void)didReceiveAd:(id)banner;
- (void)didFailToReceiveAdForIndexPath:(NSIndexPath*)indexPath;
- (void)didFailToReceiveAdForIndexPath:(NSIndexPath *)indexPath sender:(id)sender;
- (void)didDismissAdForIndexPath:(NSIndexPath*)indexPath;



@end

@protocol ADMInterstitialShowDelegate
@required
- (BOOL)isInterstitialLoaded;
- (void)showInterstitial;
@end

@interface ADMAdHandler : NSObject<MPAdViewDelegate,AmazonAdViewDelegate,MPNativeAdDelegate>
@property (nonatomic, weak) id<ADMAdLoadedDelegate> delegate;
#pragma mark - Initialization
- (instancetype)initWithADMZone:(NSString*)zone
                          isBig:(BOOL)isBig
                       cellType:(ADMAdCellType)cellType
             rootViewController:(UIViewController*)viewController;

- (instancetype)initWithAdmostPBK:(NSString*)pbk
                    locationType:(ADMAdHandlerBannerLocationType)locationType
                        cellType:(ADMAdCellType)cellType
              rootViewController:(UIViewController*)viewController;
#pragma mark -LoadBanner

- (void)loadBannerForPlacement:(NSString*)placement;
- (void)loadInterstitialForPlacement:(NSString*)placement;


- (void)loadADMBannerForIndexPath:(NSIndexPath*)indexPath;
- (void)loadAdmostForIndexPath:(NSIndexPath*)indexPath;
- (void)loadBannerForIndexPath:(NSIndexPath*)indexPath;


- (ADMAd*)adForIndexPath:(NSIndexPath*)indexPath;
- (void)resetBanners;
- (BOOL)showInterstitialForIndexPath:(NSIndexPath*)indexPath;
- (BOOL)showInterstitialForPlacement:(NSString*)indexPath;
+ (NSString*)deviceName;
#pragma mark - Register Nibs
+ (void)registerNibsForCollectionView:(UICollectionView*)collectionView;
+ (void)registerNibsForTableView:(UITableView*)tableView;
+ (NSString*)nibNameForCollectionViewPlaceHolder;
+ (NSString*)nibNameForTableViewPlaceHolder:(BOOL)isDarkBackground;
+ (float)defaultHeightForTableViewPlaceHolder;
#pragma mark - Collection Manipulation
+ (NSMutableArray*)addAdsToResultArray:(NSMutableArray*)resultArray
                       forCurrentCount:(NSInteger)currentCount
                        withStartIndex:(NSInteger)startIndex
                   andRecurrencyPeriod:(NSInteger)recurrencyPeriod;
+ (NSMutableArray*)addAdsToResultArray:(NSMutableArray*)resultArray
                     excludingIndexses:(NSIndexSet*)excludedIndexes
                       forCurrentCount:(NSInteger)currentCount
                        withStartIndex:(NSInteger)startIndex
                   andRecurrencyPeriod:(NSInteger)recurrencyPeriod;
#pragma mark - utilities
+ (BOOL)isInterstitialViewControllerOnTop;
+ (BOOL)isInterstitialViewControllerOnTop:(UIViewController*)viewController;
#pragma mark - Static methods
+ (id)bannerHelperForIndexPath:(NSIndexPath*)indexPath
            rootViewController:(UIViewController*)rootViewController
                  locationType:(ADMAdHandlerBannerLocationType)locationType
                      cellType:(ADMAdCellType)cellType
                    bannerType:(ADMAdHandlerBannerType)bannerType
                      adUnitID:(NSString*)adUnitID
                         isBig:(BOOL)isBig
           bannerPlacementType:(ADMAdHandlerBannerPlacementType)bannerPlacementType;
#pragma mark - Set Admost Parameters
+(void)setAdmostParameters:(NSMutableDictionary*)admostParameters;
@end
