#include<easyx.h>
#include<graphics.h>
void PlayBGM() {
	//1.�����֣����ý��ӿڷ���һ��string������ָ��
	//·����ĳĳ����
	//mciSendString("open  C:\\Users\\ling\\Music/bgm1.mp3 alias BGM", 0, 0, 0);
	////2.��������
	//mciSendString("play  BGM", 0, 0, 0);
	//3.�ر�����
	//Sleep(30000);
	//mciSendString("close  BGM", 0, 0, 0);

}

IMAGE img;

void CalculatorInit() {
	//��׼����ͼƬ��Դ��
	//1����ͼƬ����
	//setbkcolor(YELLOW);
	//cleardevice();

	//2 ��ͼƬ�Ž�������load��ȥ
	//loadimage(&img, "C:/Users/ling/Pictures/everGarden.jpg");
	//���ͼƬ
	putimage(0, 0, &img);

}
void MouseControl() {
	//����Ƿ������
	if (MouseHit) {
		MOUSEMSG msg = GetMouseMsg();
	}
}