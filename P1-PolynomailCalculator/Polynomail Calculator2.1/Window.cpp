#include<easyx.h>
#include<graphics.h>
void PlayBGM() {
	//1.打开音乐，向多媒体接口发送一个string，代表指令
	//路径、某某参数
	//mciSendString("open  C:\\Users\\ling\\Music/bgm1.mp3 alias BGM", 0, 0, 0);
	////2.播放音乐
	//mciSendString("play  BGM", 0, 0, 0);
	//3.关闭音乐
	//Sleep(30000);
	//mciSendString("close  BGM", 0, 0, 0);

}

IMAGE img;

void CalculatorInit() {
	//先准备好图片资源到
	//1定义图片变量
	//setbkcolor(YELLOW);
	//cleardevice();

	//2 把图片放进变量，load进去
	//loadimage(&img, "C:/Users/ling/Pictures/everGarden.jpg");
	//输出图片
	putimage(0, 0, &img);

}
void MouseControl() {
	//检测是否有鼠标
	if (MouseHit) {
		MOUSEMSG msg = GetMouseMsg();
	}
}