#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<windows.h> 
#include<string.h>
#include<conio.h>
#include<math.h>
//定义全局变量
int map[20][40]; 
int length=3, score=0;//length的作用就跟《城池》这个游戏中的count一样，所以注意length要减一 
char oldDir='d', newDir;//防止默认取值使新旧方向相同 
int snake[10][2];  //如郭宇瑶学姐所言：【2】中0表示y坐标1表示x坐标  
int food[2]={10,20};
int poison[2]={5,30};

void printGame(void);//打印游戏 
void startSnake(void);//初始化蛇 
void direction(void);//控制方向的函数
void movement(void);//蛇运动的函数
void creatfood(void);//生成食物的函数
void poisonfood(void);//吃毒草，少一个 
void gameover(void);//结束游戏的函数 ，也就是蛇死掉***用0和1判断死或生 
void colorchange(void);//颜色改变 
void printGame()
{//Y坐标在前，横坐标在后，此处要小心 ,而且是倒
	int i, j;  //打印边界          
	for(i=0;i<20;i++){    
	    map[i][0]=4;        
	    map[i][39]=4;       
	}                     
	for(j=0;j<40;j++){     
		map[0][j]=4;      
	    map[19][j]=4;       
	}
	map[food[0]][food[1]]=2;//让新区域为食物
	map[poison[0]][poison[1]]=3;//让新区域为du
	for(i=0;i<length;i++){//打印蛇 
		map[snake[i][0]][snake[i][1]]=1;
	}
	for(i=0;i<20;i++){//正式打印 
	    
		for(j=0;j<40;j++){
			
			if(map[i][j]==0)//0表示打印空白 
		    printf("  ");
		    else if(map[i][j]==1)//1表示此处为蛇 
			printf("■");
			else if(map[i][j]==2)//2表示此处为食物
			printf("￥");
			else if(map[i][j]==3)//3表示此处为毒草
			printf("!!");
			else if(map[i][j]==4)//4表示此处为边界 
			printf("##"); 
		}
		if(i==5)
		printf("您的小蛇长度：   %d", length);
		else if(i==15){
		printf("您的得分：     %d", score);
        }
		putchar('\n'); 
	}
}
/************************************direction************************************************/
void direction()//获取关于方向指令的函数 
{
	char ch1;
	if(_kbhit()){
		newDir=_getch();
		if(newDir!='a' && newDir!='d' && newDir!='w' && newDir!='s' && newDir!=' '){ 
			newDir=oldDir;
		}
		if(abs(newDir-oldDir)==3 || abs(newDir-oldDir)==4){
			newDir=oldDir;
		}
	oldDir=newDir;
	}
 } 
/***********************************startnake*******************************************/ 
 void startSnake()
 {
 	int i;
 	for(i=0;i<3;i++){
 		snake[i][0]=10;
 		snake[i][1]=4-i;
	 }
  } 
/******************************************************************/ 
 void movement()
 {
 	int i;
 	
 	map[snake[length-1][0]][snake[length-1][1]]=0;
 	for(i=0;i<length-1;i++){//循环把下一节身体移到上一节
	          
	 	snake[length-1-i][0]=snake[length-i-2][0];
	 	snake[length-1-i][1]=snake[length-i-2][1];
	 }
 	switch(oldDir){//head[1]表示y坐标，小心还有边界占了一个坐标 
 		case 'a':
 			snake[0][1]--;//头部向左移动，x减少 
 			break;
 		case 'd':
 			snake[0][1]++;
 			break;
 		case 'w':
 			snake[0][0]--;
 			break;
 		case 's':
 			snake[0][0]++;
 			break;
 		default:
 			printf("按错键，游戏将要结束\n"); 
 			system("pause");
	 }
}
/********************************************************************************/
void creatfood()
{
	srand(time(NULL));
	if(map[food[0]][food[1]]==1){//如果被吃 
	    do{
		    food[0]=rand()%20;
	        food[1]=rand()%40;
	    }while(map[food[0]][food[1]]==1 || map[food[0]][food[1]]==4 || map[food[0]][food[1]]==3);//生成一个在范围外的 
	
	length++;
	score+=10;
	printf("\a");//吃食物的提示音 
    }
}

void poisonfood()
{
	srand(time(NULL));
	if(map[poison[0]][poison[1]]==1){//如果被吃 
	    do{
		    poison[0]=rand()%20;
	        poison[1]=rand()%40;
	    }while(map[poison[0]][poison[1]]==1 || map[poison[0]][poison[1]]==4 || map[poison[0]][poison[1]]==2);//生成一个在范围外的 
	
	length--;
	map[snake[length][0]][snake[length][1]]=0;
	score-=10;
	printf("\a");//吃du的提示音 
    }
} 
 
void gameover(void)
{
	int i;
	if(snake[0][0]==0 || snake[0][0]==19 || snake[0][1]==0 || snake[0][1]==39){
		system("color 74");
		printf("小蛇撞破南墙也不回头，果然是壮士，在下佩服\a\n再次点击退出游戏\n");
		system("pause");
		exit(0);
	}
	if(length<=1){
		system("color 74");
		printf("你的小蛇已廋成了一道闪电，从此消失不见，已然成仙\a\n再次点击退出游戏你也该好好修炼，同它修仙\n");
		system("pause");
		exit(0);
	}
	for(i=1;i<length;i++){//小心i从1开始而非0，因为开始就为0 
		if(snake[0][0]==snake[i][0] && snake[0][1]==snake[i][1]){
			system("color 74");
			printf("虎毒不食子，蛇贪不咬尾\n\a你还是再次点击任意键，带这孽畜退出这游戏，走吧!");
			system("pause");
			exit(0);
		}
	}
 } 
 
 void colorchange()
 {
 	switch(length){
 		case 1:
 			system("color 78");
 			break;
 		case 2:
 			system("color 78");
 			break;
 		case 3:
 			system("color 70");
 			break;
 		case 4:
 			system("color 71");
 			break;
 		case 5:
 			system("color 72");
 			break;
 		case 6:
 			system("color 76");
 			break;
 		default:
 			system("color 75");
 		
	 }
  } 
 
 
 
 
int main(void)
{
	system("color 70") ;
    printf("点击任意键开始《贪钱蛇》游戏,按错键小蛇会死\n");
    printf("wsad分别表示上下左右，按错键则小蛇不改变方向**************￥钱吃了变长，!!吃了变短,最长为10节\n");
	system("pause");
	startSnake();//初始化蛇 和 食物毒草 
	do{
		direction();
		movement();
		poisonfood();
		creatfood();
		colorchange();
		printGame();
		Sleep(200);
		gameover();
		system("cls");
	}while(length<10);
	system("color 70");
	printf("\a您的小蛇已经太大，这个小世界已容不下它，带它去海角天涯，赏尽繁花\n");
	
	return 0;
}
