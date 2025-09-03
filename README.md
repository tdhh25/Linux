## 环境搭建

### ubuntu
下载地址：https://mirrors.aliyun.com/ubuntu-releases/

版本：ubuntu-18.04.6-desktop-amd64

![步骤1](image/step1.png)

![步骤2](image/step2.png)

![步骤3](image/step3.png)

![步骤4](image/step4.png)

![步骤5](image/step5.png)

![步骤6](image/step6.png)

![步骤7](image/step7.png)

![步骤8](image/step8.png)

![步骤9](image/step9.png)

![步骤10](image/step10.png)

![步骤11](image/step11.png)

一路下一步到finish

![步骤12](image/step12.png)

![步骤13](image/step13.png)

![步骤14](image/step14.png)

![步骤15](image/step15.png)

![步骤16](image/step16.png)

![步骤17](image/step17.png)

一路继续，直到安装完成

### ssh
获取最新的软件源信息：apt update

安装ssh：apt install openssh-server

启动ssh服务：systemctl start ssh

开机自启ssh：systemctl enable ssh

检查ssh服务状态：systemctl status ssh

### 配置网络
安装网络工具：sudo apt install net-tools

## 创建Source_Insight工程

点击Project ---> New Project
![步骤1](image/source_insight_1.png)

![步骤2](image/source_insight_2.png)

![步骤3](image/source_insight_3.png)

Project ---> Synchronize Files
![步骤4](image/source_insight_4.png)
