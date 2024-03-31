面向对象程序设计基础大作业报告
罗天蔚   2023010732  15213511510   luotw23@mails.tsinghua.edu.cn
项目主题：
4.48语音转文字应用：实现一个简单的语音转文字应用，支持用户录入语音，并将语音内容转换为文字，支持文字编辑和保存功能。 
项目描述：
该项目分为两个分区，录音区和转换区。录音区支持用户录入音频，并选择.wav文件的名称及存储位置。转换区支持用户选择.wav文件，并离线将其转换为英文。该项目的核心转换部分依赖外部pocketsphinx库，该库支持离线地将.wav文件转换为英文文本。用户编辑文本并将其以.txt文件的形式保存在指定位置。
App文件夹下有可以直接运行的.exe文件。如果需要重新编译，则须采用MSVC2019编译（MinGW会出现问题），编译文件夹在DirectTransferer文件夹同级目录下（shadow build）。
运行环境：
Windows 11   64位；   Qt Creator；   
代码构架、思路：
Main.cpp: 主程序
widget.h/.cpp: 主窗口程序。包括一些信号函数、槽函数、初始化等。
tdialoglogin.h/.cpp: 进入窗口的程序
external_functions.h/.cpp: 主要实现了调用pocketsphinx库的语音转换函数。
subthread.h/.cpp: 由于pocketsphinx库转换语音的速度较慢，若将转换过程直接放置在主线程，则会导致在转换较长语音时，程序陷入“无法响应”的局面。因此，创建子线程，将语音转换的过程放置在子线程中执行。
.ui文件为图形界面设计的文件。
注意事项：
请务必确保.exe文件在与DirectTransfer文件夹同级的文件夹之下，以防程序中相对路径错误的问题（正确的为../DirectTransfer/…….）。如果运行的过程中出现任何问题，恳请助教与我联系！
Github仓库地址：llltttwww/DirectTransferer: OOP big HW (github.com)
主要参考资料：
.raw生成.wav文件的函数直接借鉴了Qt之实现录音播https://blog.csdn.net/lmhuanying1012/article/details/78242967放及raw（pcm）转wav格式_raw pcm file-CSDN   博客的内容。
Qt6的学习主要参考了《Qt6 c++开发指南》。
