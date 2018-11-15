# 洗衣机算法设计

### “自顶向下，逐步求精”的编程方法

![](http://m.qpic.cn/psb?/V10TtYkp2MvHv1/TOfyYKXdXnZPzK2d7zofMFcVwBqGMEO5ighxCBvlDaQ!/b/dDABAAAAAAAA&bo=2QS4AgAAAAADF1U!&rf=viewer_4)

自顶向下是一种逐步求精的设计程序的过程和方法。对要完成的任务进行分解，先对最高层次中的问题进行定义、设计、编程和测试，而将其中未解决的问题作为一个子任务放到下一层次中去解决。这样逐层、逐个地进行定义、设计、编程和测试，直到所有层次上的问题均由实用程序来解决，就能设计出具有层次结构的程序

将复杂的大问题分解为相对简单的小问题，找出每个问题的关键、重点所在，然后用精确的思维定性、定量地去描述问题。其核心本质是"分解"

按自顶向下的方法设计时,首先对所设计的系统要有一个全面的理解.然后从顶层开始,连续地逐层向下分解,起到系统的所有模块都小到便于掌握为止，可直接实现


### 以我观察的洗衣机为案例，用伪代码描述的控制程序设计

#### 要完成的任务：设计洗衣机“正常洗衣”程序

主函数

```
set StandardVolume to 标准体积
set StandardTime to 标准时间
set StandardSoakTime to 标准浸泡时间
set RunFrequency to 运行频率
set StandardRunTime to 标准运行时间

注水：注水(StandardVolume,StandardTime)

浸泡：wait(StandardSoakTime)

洗衣：rollerrunning(RunFrequency,StandardRunTime)

排水：排水(StandardTime)

脱水：rollerrunning(RunFrequency,StandardRunTime)

停机：halt(success)
```

#### 分解主函数“正常洗衣”程序的各个功能，如下

注水：往滚筒中注入一定量的水

浸泡：让洗衣机等待一段时间，使衣服在滚桶中浸泡

洗衣：让滚筒以一定次数按一定方向旋转

排水：将滚筒中的水排出

脱水：让滚筒以一定次数按一定方向旋转

停机：程序结束，停止运行标志

#### 用伪代码对主函数每个功能进行子函数实现

子函数

注水

```
注水(volume,timeout) {
    repeat
        water_in_switch(open)
    until (get_water_volume() > volume)

    water_in_switch(close)

    if (time_counter() > timeout) 
        halt(success)
}
```

浸泡

```
wait(time) {
    repeat
        soaking
    until (time_counter() > time)
}
```

洗衣、脱水

```
rollerrunning(frequency，time) {

    for n from 1 to frequency
    repeat
        motor_run(left)
    until (time_counter() > time)
    repeat
        motor_run(right)
    until (time_counter() > time)
    motor_run(stop)
}
```

排水

```
排水(timeout) {
    repeat
        water_out_switch(open)
    until (get_water_volume() <= 0)

    water_out_switch(close)

    if (time_counter() > timeout) 
        halt(success)
}
```

停机

```
halt(success)
```

#### 用伪代码对每个子函数中的功能进行基本函数实现

基本函数

```
water_in_switch(open_close) {
    控制注水开关，open 打开注水开关，close关闭
} 
```

```
water_out_switch(open_close) {
    控制排水开关，open 打开排水开关，close关闭
} 
```

```
get_water_volume() {
    从传感器获得洗衣机内部水的高度，并返回其值
} 
```

```
motor_run(direction) {
    控制电机转动，left左转，right右转，stop停
} 
```

```
time_counter() {
    以秒为单位返回当前时间计数
} 
```

```
halt(returncode) {
    停机操作，返回 success 成功，failure 失败
}  
```

#### 最后洗衣机“正常洗衣”程序如下

```
rollerrunning(frequency,time)
wait(time)
注水(volume,timeout)
排水(timeout)

set StandardVolume to 标准体积
set StandardTime to 标准时间
set StandardSoakTime to 标准浸泡时间
set RunFrequency to 运行频率
set StandardRunTime to 标准运行时间


注水(StandardVolume,StandardTime)

wait(StandardSoakTime)

rollerrunning(RunFrequency,StandardRunTime)

排水(StandardTime)

rollerrunning(RunFrequency,StandardRunTime)

halt(success)


rollerrunning(frequency,time) {

    for n from 1 to frequency
    repeat
        motor_run(left)
    until (time_counter() > time)
    repeat
        motor_run(right)
    until (time_counter() > time)
    motor_run(stop)
}

wait(time) {
    repeat
        soaking
    until (time_counter() > time)
}

注水(volume,timeout) {
    repeat
        water_in_switch(open)
    until (get_water_volume() > volume)

    water_in_switch(close)

    if (time_counter() > timeout) 
        halt(success)
}

排水(timeout) {
    repeat
        water_out_switch(open)
    until (get_water_volume() <= 0)

    water_out_switch(close)

    if (time_counter() > timeout) 
        halt(success)
}

```