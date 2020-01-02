//
//  DemoViewController.m
//  LearnOpenGLES
//
//  Created by erpapa on 2018/2/7.
//  Copyright © 2018年 erpapa. All rights reserved.
//

#import "DemoViewController.h"

@interface DemoViewController () <UITableViewDataSource, UITableViewDelegate>

@property (nonatomic, strong) UITableView *tableView;
@property (nonatomic, strong) NSArray *dataArray;

@end

@implementation DemoViewController

- (void)viewDidLoad
{
    [super viewDidLoad];
    // Do any additional setup after loading the view, typically from a nib.
    
    self.title = @"DEMO";
    self.view.backgroundColor = [UIColor whiteColor];
    self.navigationController.interactivePopGestureRecognizer.enabled = NO;

    self.dataArray = @[@{@"title":@"0.三角形",@"class":@"DemoViewController0"},
                       @{@"title":@"1.颜色",@"class":@"DemoViewController1"},
                       @{@"title":@"2.贴图",@"class":@"DemoViewController2"},
                       @{@"title":@"3.裁剪",@"class":@"DemoViewController3"},
                       @{@"title":@"4.变换",@"class":@"DemoViewController4"},
                       @{@"title":@"5.GLKit",@"class":@"DemoViewController5"},
                       @{@"title":@"6.3D字体",@"class":@"DemoViewController6"},
                       @{@"title":@"7.太阳、地球、月亮",@"class":@"DemoViewController7"},
                       @{@"title":@"8.CUBE_BOX（立方体盒）",@"class":@"DemoViewController8"},
                       @{@"title":@"9.SKY_BOX（天空盒）",@"class":@"DemoViewController9"},
                       @{@"title":@"10.DEPTH_TEST（深度测试）",@"class":@"DemoViewController10"},
                       @{@"title":@"11.STENCIL_TEST（模板测试）",@"class":@"DemoViewController11"},
                       @{@"title":@"12.SCISSOR_TEST（裁剪测试）",@"class":@"DemoViewController12"},
                       @{@"title":@"13.ALPHA_TEST（透明度测试）",@"class":@"DemoViewController13"},
                       @{@"title":@"14.BLEND（颜色混合）",@"class":@"DemoViewController14"},
                       @{@"title":@"15.CULL_FACE（面剔除）",@"class":@"DemoViewController15"},
                       @{@"title":@"16.Effects（滤镜特效）",@"class":@"DemoViewController16"},
                       @{@"title":@"17.Split Screen（分屏特效）",@"class":@"DemoViewController17"},
                       @{@"title":@"18.Ambient（环境光）",@"class":@"DemoViewController18"},
                       @{@"title":@"19.Diffuse（漫反射光）",@"class":@"DemoViewController19"},
                       @{@"title":@"20.Specular（镜面高光）",@"class":@"DemoViewController20"},
                       @{@"title":@"21.Material（材质）",@"class":@"DemoViewController21"},
                       @{@"title":@"22.Diffuse Map（漫反射贴图）",@"class":@"DemoViewController22"},
                       @{@"title":@"23.Specular Map（镜面光贴图）",@"class":@"DemoViewController23"},
                       @{@"title":@"24.Directional Light（方向光）",@"class":@"DemoViewController24"},
                       @{@"title":@"25.Point Light（点光源）",@"class":@"DemoViewController25"},
                       @{@"title":@"26.Spot Light（聚光灯）",@"class":@"DemoViewController26"},
                       @{@"title":@"27.Multiple Lights（多光源）",@"class":@"DemoViewController27"},
                       @{@"title":@"28.Fluid Simulation（流体模拟）",@"class":@"DemoViewController28"}];
    self.tableView = [[UITableView alloc] initWithFrame:self.view.bounds style:UITableViewStylePlain];
    self.tableView.showsVerticalScrollIndicator = NO;
    self.tableView.showsHorizontalScrollIndicator = NO;
    self.tableView.autoresizingMask = UIViewAutoresizingFlexibleWidth | UIViewAutoresizingFlexibleHeight;
    self.tableView.tableFooterView = [UIView new];
    self.tableView.rowHeight = 56.0;
    self.tableView.dataSource = self;
    self.tableView.delegate = self;
    [self.view addSubview:self.tableView];
    
}

#pragma mark - UITableViewDataSource

- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section
{
    return self.dataArray.count;
}

- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath
{
    static NSString *kResueIdentfier = @"kTableViewCellResueIdentfier";
    UITableViewCell *cell = [tableView dequeueReusableCellWithIdentifier:kResueIdentfier];
    if (cell == nil) {
        cell = [[UITableViewCell alloc] initWithStyle:UITableViewCellStyleDefault reuseIdentifier:kResueIdentfier];
        cell.selectionStyle = UITableViewCellSelectionStyleNone;
        cell.accessoryType = UITableViewCellAccessoryDisclosureIndicator;
        cell.textLabel.textColor = [UIColor colorWithRed:0.2 green:0.2 blue:0.2 alpha:1.0];
    }
    if (indexPath.row < self.dataArray.count) {
        NSDictionary *dict = [self.dataArray objectAtIndex:indexPath.row];
        cell.textLabel.text = [dict objectForKey:@"title"];
    }
    return cell;
}

- (void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath
{
    [tableView deselectRowAtIndexPath:indexPath animated:NO];

    if (indexPath.row < self.dataArray.count) {
        NSDictionary *dict = [self.dataArray objectAtIndex:indexPath.row];
        NSString *classString = [dict objectForKey:@"class"];
        Class class = NSClassFromString(classString);
        if (class != NULL) {
            UIViewController *vc = (UIViewController *)[[class alloc] init];
            vc.title = [dict objectForKey:@"title"];
            [self.navigationController pushViewController:vc animated:YES];
        }
    }
}

@end

