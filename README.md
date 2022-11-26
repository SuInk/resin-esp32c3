# esp32c3 实现显示原神树脂功能（支持天暗息屏）
## 效果展示
![IMG_1292.jpeg](https://s2.loli.net/2022/07/01/Do2lySqEmLNHrf1.jpg)
## 需要材料：
* 合宙esp32c3开发板 https://m.tb.cn/h.fEFFM5V
* 1.8寸tft屏幕（建议买管脚焊好的），可以在合宙店里买 https://m.tb.cn/h.fvxt3IQ
* 光敏传感器（可选）
* 杜邦线若干（至少9根母对母）
* 电焊笔一支
* typec数据线一条

## 安装步骤
1. 下载arduino IDE
* 打开微软商店(microsoft store) ,下载arduino IDE
![image.png](https://s2.loli.net/2022/06/30/M9FryCj8WEoSZvH.png)
 *  打开arduino，点击 文件->首选项->附加开发板管理器地址 输入 `https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_dev_index.json` 点击好
![image.png](https://s2.loli.net/2022/06/30/KvNjeGPFMl1x2fZ.png) 
* 点击 工具 开发板选择ESP32C3 Dev Module , Flash Mode选DIO，端口可以在控制面板->设备和打印机查看（随便选一个能编译成功的也可），现在arduino IDE就配置好了。
![image.png](https://s2.loli.net/2022/07/01/K2h6YsqCQS5UwnJ.png)

2. 将esp32c3通过数据线连接电脑，屏幕通过杜邦线连接esp32c3，光敏传感器连接esp32c3
	按图连接
![IMG_1337.jpeg](https://s2.loli.net/2022/07/01/AXvs9GzB5Rgi37Z.jpg)
![IMG_1335.jpeg](https://s2.loli.net/2022/07/01/arqiT5F2EcJIX1o.jpg)


3. 打开https://github.com/SuInk/resin-esp32c3 复制代码
![image.png](https://s2.loli.net/2022/07/01/AZdBSav31Jtz7WG.png)


4. 打开arduino新建工程

* 把复制的代码粘贴到arduino中，填入

``` bash
2.4G WiFi的账号、密码
原神uid
服务器
cookie信息
```
*  点击 工具->管理库 安装所声明的库
*  点击编译、上传（即arduino左边的对号和向右的箭头）
![image.png](https://s2.loli.net/2022/07/01/96CfwlWKtvqATQB.png)
![image.png](https://s2.loli.net/2022/07/01/1aQnXrZLeKBRzS3.png)
5. 进阶(需要安装python3环境)
* 将光敏传感器DO口连接开发板的IO05  
* VCC连接esp32c3开发板3.3V接口  
* GND连接esp32c3开发板GND  
* 安装PYTHON3环境  
* 根据此[教程](https://b23.tv/sDdGMto)解锁esp32c3 IO11   
屏幕即可在晚上自动关闭  
6. enjoy it！十分欢迎大家提pr增加中文显示、ui美化等功能
