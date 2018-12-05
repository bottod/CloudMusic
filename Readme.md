## CloudMusic made by Qt  
  
由于taglib的原因，window版和linux版有些许不同，就是动态库的问题  
windows上采用taglib1.10  
windows上编译步骤：  
1、  cmake -G "MinGW Makefiles" -DBUILD_SHARED_LIB=ON -DHAVE_ZLIB=0 -DW  
ITH_MP4=1 -DMAKE_TAGLIB_LIB=1  
2、 make    
3、 make install   (需要admin权限 所有步骤在cmd或powershell执行，不能在unix shell 里执行)    
  
上述已经编译好了在Source_Code/taglib里了 运行编译后的软件需要libtag.dll在taglib/bin文件夹里  
  
简单点说就是下载源码 编译 然后将Source_Code/taglib/libtag.dll置于软件同一目录下即可  
具体改动在branch---win里查看  
  
  
  
  
 这个小demo是模仿网易云音乐的界面做的音乐播放器，开发环境是ubuntu18+Qt5；  
  
 还有一点 由于程序里设置了1920*1080； 所以大于这个分辨率后的窗口就不是很理想了：）    
  
起因是：网易云音乐播放器在ubuntu18上有莫名奇妙的bug 只适配到ubuntu16，于是想着自己动手  
  
：）------------------------------------------------------------------------------------------------



#### 先上效果图：

![](./screenshoot/1.png)

![](./screenshoot/2.png)

![](./screenshoot/3.png)

![](./screenshoot/4.png)

![](./screenshoot/5.png)

![](./screenshoot/6.png)



目前只做了这么多，本地播放的功能有了，网络播放的功能还未实现；近期会去研究下网易云音乐的网络接口

争取尽快把网络部分弄出来



|---------------------------------------------------------------------------------------------------------------------

最后最后，如果觉得还行请Star！！！

ORZ ORZ