//
//  ViewController.m
//  LearnOpenGLES
//
//  Created by erpapa on 2018/2/7.
//  Copyright © 2018年 erpapa. All rights reserved.
//

#import "ViewController.h"

@interface ViewController () <UITableViewDataSource, UITableViewDelegate>

@property (nonatomic, strong) UITableView *tableView;
@property (nonatomic, strong) NSArray *dataArray;

@end

@implementation ViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view, typically from a nib.
    
    self.title = @"DEMO";
    self.view.backgroundColor = [UIColor whiteColor];
    
    self.dataArray = @[@{@"title":@"三角形",@"class":@"DemoViewController0"},
                       @{@"title":@"颜色",@"class":@"DemoViewController1"},
                       @{@"title":@"贴图",@"class":@"DemoViewController2"},
                       @{@"title":@"裁剪",@"class":@"DemoViewController3"},
                       @{@"title":@"平移、旋转、缩放",@"class":@"DemoViewController4"},
                       @{@"title":@"GLKBaseEffect",@"class":@"DemoViewController5"},
                       @{@"title":@"3D字体",@"class":@"DemoViewController6"},
                       @{@"title":@"立方体盒子",@"class":@"DemoViewController7"},
                       @{@"title":@"太阳、地球、月亮",@"class":@"DemoViewController8"},
                       @{@"title":@"天空盒",@"class":@"DemoViewController9"},
                       @{@"title":@"深度测试",@"class":@"DemoViewController10"},
                       @{@"title":@"模板测试",@"class":@"DemoViewController11"},
                       @{@"title":@"裁剪测试",@"class":@"DemoViewController12"},
                       @{@"title":@"alpha测试",@"class":@"DemoViewController13"},
                       @{@"title":@"blend混合",@"class":@"DemoViewController14"},
                       @{@"title":@"面剔除",@"class":@"DemoViewController15"},
                       @{@"title":@"光照",@"class":@"DemoViewController16"}];
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

