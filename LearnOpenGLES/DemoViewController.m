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

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view, typically from a nib.
    
    self.title = @"DEMO";
    self.view.backgroundColor = [UIColor whiteColor];
    
    self.dataArray = @[@{@"title":@"三角形",@"class":@"DemoViewController0"},
                       @{@"title":@"颜色",@"class":@"DemoViewController1"},
                       @{@"title":@"贴图",@"class":@"DemoViewController2"},
                       @{@"title":@"裁剪",@"class":@"DemoViewController3"},
                       @{@"title":@"变换",@"class":@"DemoViewController4"},
                       @{@"title":@"GLKit",@"class":@"DemoViewController5"},
                       @{@"title":@"3D字体",@"class":@"DemoViewController6"},
                       @{@"title":@"太阳、地球、月亮",@"class":@"DemoViewController7"},
                       @{@"title":@"CUBE_BOX（立方体盒）",@"class":@"DemoViewController8"},
                       @{@"title":@"SKY_BOX（天空盒）",@"class":@"DemoViewController9"},
                       @{@"title":@"DEPTH_TEST（深度测试）",@"class":@"DemoViewController10"},
                       @{@"title":@"STENCIL_TEST（模板测试）",@"class":@"DemoViewController11"},
                       @{@"title":@"SCISSOR_TEST（裁剪测试）",@"class":@"DemoViewController12"},
                       @{@"title":@"ALPHA_TEST（透明度测试）",@"class":@"DemoViewController13"},
                       @{@"title":@"BLEND（颜色混合）",@"class":@"DemoViewController14"},
                       @{@"title":@"CULL_FACE（面剔除）",@"class":@"DemoViewController15"},
                       @{@"title":@"Effects（滤镜特效）",@"class":@"DemoViewController16"},
                       @{@"title":@"Screens（分屏特效）",@"class":@"DemoViewController17"},
                       @{@"title":@"Ambient（环境光）",@"class":@"DemoViewController18"},
                       @{@"title":@"Diffuse（漫反射光）",@"class":@"DemoViewController19"},
                       @{@"title":@"Specular（镜面高光）",@"class":@"DemoViewController20"}];
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

