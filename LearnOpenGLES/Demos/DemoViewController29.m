//
//  DemoViewController29.m
//  LearnOpenGLES
//
//  Created by apple on 2020/10/23.
//  Copyright © 2020 erpapa. All rights reserved.
//

#import "DemoViewController29.h"
#import "DawnView.h"

@interface DemoViewController29 ()

@property (nonatomic, strong) DawnView *dawnView;

@end

@implementation DemoViewController29

- (void)viewDidLoad
{
    [super viewDidLoad];
    // Do any additional setup after loading the view.
    self.view.backgroundColor = [UIColor colorWithRed:0.95 green:0.95 blue:0.95 alpha:1.0];
    self.dawnView = [[DawnView alloc] initWithFrame:CGRectMake(0, (CGRectGetHeight(self.view.bounds) - CGRectGetWidth(self.view.bounds)) * 0.5, CGRectGetWidth(self.view.bounds), CGRectGetWidth(self.view.bounds))];
    [self.view addSubview:self.dawnView];
    
    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(onAppEnterForeground) name:UIApplicationWillEnterForegroundNotification object:nil];
    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(onAppEnterBackground) name:UIApplicationDidEnterBackgroundNotification object:nil];
}

- (void)viewWillDisappear:(BOOL)animated
{
    [super viewWillDisappear:animated];
    [self.dawnView pause];
    [self.dawnView destory];
}

- (void)onAppEnterForeground
{
    [self.dawnView pause];
}

- (void)onAppEnterBackground
{
    [self.dawnView resume];
}

- (void)dealloc
{
    [[NSNotificationCenter defaultCenter] removeObserver:self];
}

@end
