/******************************************************************
 *                        sinDemo
 *
 *   1. 本Demo主要目标是为了实现在终端下实现sin函数的动态效果;
 *   2. 本Demo之前是使用shell tput和C语言实现的,这次将其改为
 *       C语言+VT100控制码的形式;
 *
 *                              2015-3-27 阴 深圳  曾剑峰
 *
 *****************************************************************/
 #include <stdio.h>
 #include <math.h>
 #include <unistd.h>
 
 /**
  * 定义圆周率的值
  */
 #define PI  3.14
 /**
  * 本Demo中假设sin曲线周期为20,幅值也是20,幅值分正负幅值,
  * 所以后面的很多地方有SIN_AMPLITUDE*2,也就是Y轴方向上的值.
  */
 #define SIN_AMPLITUDE  20      
 /**
  * 定义每次刷新图形时间间隔为100ms
  */
 #define DELAY_TIME  100000  
 /**
  * 定义圆的一周角度为360度
  */
 #define TRIANGLE  360.0   
 /**
  * 输出的时候,数字行放在哪一行,也就是输出图形中的这行数字:
  *   0123456789012345678901234567890123456789
  * 本Demo中把上面这行数字放在界面的第3行
  */
 #define Y_NUMBER_BEGIN_LINE  3
 /**
  * 在本Demo中,图形就在上面数字行的下一行,也就是输出图形中如下面的内容:
  *     0000    --------------------@--------------------> Y
  *     0001                        |-----*             
  *     0002                        |----------*        
  *     0003                        |---------------*   
  *     0004                        |------------------*
  *     0005                        |------------------*
  *     0006                        |------------------*
  *     0007                        |---------------*   
  *     0008                        |----------*        
  *     0009                        |-----*             
  *     0010                        *                   
  *     0011                  *-----|                   
  *     0012             *----------|                   
  *     0013        *---------------|                   
  *     0014     *------------------|                   
  *     0015     *------------------|                   
  *     0016     *------------------|                   
  *     0017        *---------------|                   
  *     0018             *----------|                   
  *     0019                  *-----|                   
  *     0020                        V X  
  */
 #define SIN_GRAPH_BEGIN_LINE (Y_NUMBER_BEGIN_LINE+1)
 
 int main(int argc, char* argv[]){
 
     /**
      * 局部变量说明:
      *     1. i                 : 主要用于循环计算;
      *     2. lineNumber        : 用于保存行号;
      *     3. offsetCenter      : 用于保存sin曲线上的点的相对于中心轴的偏移;
      *     4. nextInitAngle     : 保存下一屏要输出图形的初始角度制角度(如30度);
      *     5. currentInitAngle  : 当前一屏要输出的图形的初始角度制角度(如30度);
      *     6. currentInitradian : 当前一屏要输出的图形的初始弧度制弧度(如PI/6)
      *                            根据currentInitAngle换算而来,因为sin函数需要
      *                            角度制进行求值;
      *
      */
     int    i                   = 0;    
     int    lineNumber          = 0;    
     int    offsetCenter        = 0;    
     int    nextInitAngle       = 0;
     double currentInitAngle    = 0;    
     double currentInitradian   = 0;    
 
     //软件开始运行,清一次屏,保证屏幕上没有无关内容
     printf("\033[2J");
         
     //输出标题,因为这个软件名字叫: SinDemo
     printf("\033[1;1H                       | SinDemo |\t");
 
     /**
      * 这里主要是完成那一行重复的0-9,SIN_AMPLITUDE*2是因为sin曲线的
      * 最高点和最低点是2倍的幅值
      */
     printf("\033[%d;1H\t", Y_NUMBER_BEGIN_LINE);
     for (i = 0; i < SIN_AMPLITUDE*2; i++) 
         printf("%d", i%10);
     printf("\n");
 
     /**
      * while循环主要完成内容:
      *     1. 每次循环对局部变量重新初始化;
      *     2. 将下一屏图形的初始角度赋值给当前的图形初始角;              
      *     3. 将下一屏图形的初始角度加上间隔角度(TRIANGLE/SIN_AMPLITUDE),
      *        TRIANGLE/SIN_AMPLITUDE在本Demo中是360/20=18度,就相当于X轴 
      *        每格代表18度 
      *     2. 调整光标到固定的位置;
      *     3. 重新绘制整屏图形;
      */
     while(1){
 
         //重新初始化局部变量,因为每一屏图形都像一个新的开始
         i                  = 0;        
         offsetCenter       = 0;       
         lineNumber         = 0;      
         currentInitradian  = 0;     
 
         //从nextInitAngle中获取当前的初始化角度
         currentInitAngle   =  nextInitAngle;
 
         //为下一次循环提供下一次的初始化角度
         nextInitAngle     += TRIANGLE/SIN_AMPLITUDE;  
 
         //将光标移动到开始绘图的位置去
         printf("\033[%d;1H", SIN_GRAPH_BEGIN_LINE);
 
         /**
          * 根据不同的情况绘制图形, 每一次循环,就是绘制了图形中的一行
          */
         while(1){
             //判断是不是最后一行,lineNumber起始行是从0开始
             if(lineNumber == SIN_AMPLITUDE){
                 //打印最后一行前面的数字行号
                 printf("\033[%d;1H%04d\t", lineNumber+SIN_GRAPH_BEGIN_LINE, lineNumber);
                 for (i = 0; i < SIN_AMPLITUDE*2; i++)
                     /**
                      * 判断是否到达中间位置,因为中间位置要放V的箭头,同时在旁边输出一个X,
                      * 代表这是X轴方向.
                      */
                     i == SIN_AMPLITUDE ? printf("V X") : printf(" ");    
                 break;
             }
 
 
             /**
              * 对currentInitAngle角度进行修整,比如370度和10度是对应相同的sin值
              * 其实这一步可以不用,但是这里保留了,后面是将currentInitAngle角度制的值
              * 换算成对应的弧度制的值,便于sin求值.
              */
             currentInitAngle = ((int)currentInitAngle)%((int)TRIANGLE);
             currentInitradian = currentInitAngle/(TRIANGLE/2)*PI;    
 
             /**
              * 算出当前次currentInitradian对应的sin值,并乘以幅值SIN_AMPLITUDE,获取sin曲线
              * 在Y轴上相对于中心轴的偏移offsetCenter,offsetCenter可能是正值,也可能是负值,
              * 因为中心轴在中间.
              */
             offsetCenter = (int)(sin(currentInitradian)*SIN_AMPLITUDE);                
 
             /**
              * 在正确的地方输出正确的行号   :)
              */
             printf("\033[%d;1H%04d", lineNumber+SIN_GRAPH_BEGIN_LINE, lineNumber);
 
             //用一个制表符,给出行号与图形的空间距离
             printf("\t");
 
             /**
              * 第一行,和其他的行不一样,有区别,输出结果如下:
              * 0000    ------------@-------+--------------------> Y
              */
             if(lineNumber == 0){
                 for (i = 0; i < SIN_AMPLITUDE*2; i++){
                     /**
                      * 判断当前输出的字符位置是否是X,Y轴交叉的位置,如果是就输出'+',
                      * 不是就输出'-'
                      */
                     i == SIN_AMPLITUDE ? printf("+") : printf("-");
                     /**
                      * 判断当前输出的字符位置是否是sin曲线上的点对应的位置,
                      * 如果是就输出'@'
                      */
                     if(i == offsetCenter+SIN_AMPLITUDE)
                         printf("@");
                 }
                 //代表这个方向是Y轴
                 printf("-> Y\n");
             } else { 
                 for (i = 0; i < SIN_AMPLITUDE*2; i++){
                     //判断当前输出的字符位置是否是sin曲线上的点对应的位置,如果是就输出'*'
                     if(i == (offsetCenter+SIN_AMPLITUDE)){
                         printf("*");
                     //判断当前输出的字符位置是否是X轴上对应的位置,如果是就输出'|'
                     }else if(i == SIN_AMPLITUDE){
                         printf("|");
                     }else{
                         /**
                          * 这里主要是要处理一行里面除了画'*'、'|'、之外的'-'、' '
                          * 其中的SIN_AMPLITUDE到SIN_AMPLITUDE+offsetCenter正好就是需要输出'-'的地方
                          * 其他的地方输出' '
                          */
                         (((i > SIN_AMPLITUDE) && (i < SIN_AMPLITUDE+offsetCenter)) || \
                             ((i < SIN_AMPLITUDE) && (i > SIN_AMPLITUDE+offsetCenter))) \
                                 ? printf("-") : printf(" ");
                     }
                     //行尾,输出换行符
                     if(i == (SIN_AMPLITUDE*2-1)) 
                         printf("\n");
                 }
             }
 
             /**
              * 一行输出完成,为下一行输出作准备,下一行比上一行在角度上多加TRIANGLE/SIN_AMPLITUDE,
              * 在本Demo中相当于360/20=18,也就是加18度.
              */
             currentInitAngle += TRIANGLE/SIN_AMPLITUDE;      
 
             //行号加1
             lineNumber++;                                    
         }
         /**
          * 一屏图像输出完毕,最后输出一个换行符,并且延时一段时间再开始绘制下一屏图形
          */
         printf("\n");
         usleep(DELAY_TIME);
     }
 
     return 0;
 }