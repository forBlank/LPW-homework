# 飞机大战游戏设计

## 游戏策划

#### 楔子(Setting)：

233333年，在星际间漂泊的我偶遇星盗劫掠，面对数倍于自己的敌人，我毫不畏惧，单枪匹马横扫整个星盗团，并击毁其巨型母舰，在遍地残骸中飘向下一个星系……

#### 玩法(Gameplay)：

玩家射死母舰，四艘护卫舰和六艘攻击舰，任务完成。玩家死亡，任务失败。玩家使用方向键避让飞来的紫色光弹和敌人，并点击鼠标左键发射蓝色光弹…… 

#### 人设与道具（Game Sprites）：

我舰：有20点生命值，可以抵抗紫色光弹的射击，但与敌人触碰则直接死亡。点击鼠标左键发射向鼠标指向发射蓝色光弹，伤害1。

母舰：有30点生命值，可以抵抗蓝色光弹的射击，会向我舰发射单枚紫色光弹，伤害1，双联紫色光弹，伤害2，三联紫色光弹，伤害3。

护卫舰：护卫在母舰旁边，有10点生命值，可以抵抗蓝色光弹的射击，会向我舰发射单枚紫色光弹，伤害1。

攻击舰：游离在地图周围，有10点生命值，可以抵抗蓝色光弹的射击，会向我舰发射单枚紫色光弹，伤害1。

## 游戏设计

1

Object Name : 我舰

Attributes : 图片，位置，生命值

Collaborator : 精灵

Events & Actions : 单击鼠标左键 & 生成蓝色光弹；与单枚紫色光弹碰撞 & 生命值-1；与双联紫色光弹碰撞 & 生命值-2；与三联紫色光弹碰撞 & 生命值-3；与母舰、护卫舰、攻击舰碰撞 & 摧毁；生命值<=0 & 摧毁


2

Object Name : 母舰

Attributes : 图片，位置，生命值

Collaborator : 精灵

Events & Actions : 在地图中、在地图外 & 指向我舰；每四秒 & 生成单枚紫色光弹；每六秒 & 生成双联紫色光弹；每九秒 & 生成三联紫色光弹；与蓝色光弹碰撞 & 生命值-1；生命值<=0 & 摧毁


3

Object Name : 护卫舰

Attributes : 图片，位置，生命值

Collaborator : 精灵

Events & Actions : 在地图中、在地图外 & 指向我舰；每四秒 & 生成单枚紫色光弹；与蓝色光弹碰撞 & 生命值-1；生命值<=0 & 摧毁


4

Object Name : 攻击舰

Attributes : 图片，位置，生命值

Collaborator : 精灵

Events & Actions : 在地图中、在地图外 & 指向我舰；每四秒 & 生成单枚紫色光弹；与蓝色光弹碰撞 & 生命值-1；生命值<=0 & 摧毁


5

Object Name : 蓝色光弹

Attributes : 图片，位置

Collaborator : 精灵

Events & Actions : 与母舰、护卫舰、攻击舰碰撞 & 生成爆炸，摧毁


6

Object Name : 单枚紫色光弹

Attributes : 图片，位置

Collaborator : 精灵

Events & Actions : 与我舰碰撞 & 生成爆炸，摧毁


7

Object Name : 双联紫色光弹

Attributes : 图片，位置

Collaborator : 精灵

Events & Actions : 与我舰碰撞 & 生成爆炸，摧毁


8

Object Name : 三联紫色光弹

Attributes : 图片，位置

Collaborator : 精灵

Events & Actions : 与我舰碰撞 & 生成爆炸，摧毁


9

Object Name : 爆炸

Attributes : 图片，位置

Collaborator : 精灵

Events & Actions : 无


效果图如下

![](http://m.qpic.cn/psb?/V10TtYkp2MvHv1/C*7j1Lcdv6dQDNE1A4lY.8KTlBbhNGiLmvpqDRLPbm8!/b/dDABAAAAAAAA&bo=SASUAgAAAAACl2k!&rf=viewer_4)


