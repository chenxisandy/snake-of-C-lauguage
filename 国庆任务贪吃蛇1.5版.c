#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<windows.h> 
#include<string.h>
#include<conio.h>
#include<math.h>
//����ȫ�ֱ���
int map[20][40]; 
int length=3, score=0;//length�����þ͸����ǳء������Ϸ�е�countһ��������ע��lengthҪ��һ 
char oldDir='d', newDir;//��ֹĬ��ȡֵʹ�¾ɷ�����ͬ 
int snake[10][2];  //�������ѧ�����ԣ���2����0��ʾy����1��ʾx����  
int food[2]={10,20};
int poison[2]={5,30};

void printGame(void);//��ӡ��Ϸ 
void startSnake(void);//��ʼ���� 
void direction(void);//���Ʒ���ĺ���
void movement(void);//���˶��ĺ���
void creatfood(void);//����ʳ��ĺ���
void poisonfood(void);//�Զ��ݣ���һ�� 
void gameover(void);//������Ϸ�ĺ��� ��Ҳ����������***��0��1�ж������� 
void colorchange(void);//��ɫ�ı� 
void printGame()
{//Y������ǰ���������ں󣬴˴�ҪС�� ,�����ǵ�
	int i, j;  //��ӡ�߽�          
	for(i=0;i<20;i++){    
	    map[i][0]=4;        
	    map[i][39]=4;       
	}                     
	for(j=0;j<40;j++){     
		map[0][j]=4;      
	    map[19][j]=4;       
	}
	map[food[0]][food[1]]=2;//��������Ϊʳ��
	map[poison[0]][poison[1]]=3;//��������Ϊdu
	for(i=0;i<length;i++){//��ӡ�� 
		map[snake[i][0]][snake[i][1]]=1;
	}
	for(i=0;i<20;i++){//��ʽ��ӡ 
	    
		for(j=0;j<40;j++){
			
			if(map[i][j]==0)//0��ʾ��ӡ�հ� 
		    printf("  ");
		    else if(map[i][j]==1)//1��ʾ�˴�Ϊ�� 
			printf("��");
			else if(map[i][j]==2)//2��ʾ�˴�Ϊʳ��
			printf("��");
			else if(map[i][j]==3)//3��ʾ�˴�Ϊ����
			printf("!!");
			else if(map[i][j]==4)//4��ʾ�˴�Ϊ�߽� 
			printf("##"); 
		}
		if(i==5)
		printf("����С�߳��ȣ�   %d", length);
		else if(i==15){
		printf("���ĵ÷֣�     %d", score);
        }
		putchar('\n'); 
	}
}
/************************************direction************************************************/
void direction()//��ȡ���ڷ���ָ��ĺ��� 
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
 	for(i=0;i<length-1;i++){//ѭ������һ�������Ƶ���һ��
	          
	 	snake[length-1-i][0]=snake[length-i-2][0];
	 	snake[length-1-i][1]=snake[length-i-2][1];
	 }
 	switch(oldDir){//head[1]��ʾy���꣬С�Ļ��б߽�ռ��һ������ 
 		case 'a':
 			snake[0][1]--;//ͷ�������ƶ���x���� 
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
 			printf("���������Ϸ��Ҫ����\n"); 
 			system("pause");
	 }
}
/********************************************************************************/
void creatfood()
{
	srand(time(NULL));
	if(map[food[0]][food[1]]==1){//������� 
	    do{
		    food[0]=rand()%20;
	        food[1]=rand()%40;
	    }while(map[food[0]][food[1]]==1 || map[food[0]][food[1]]==4 || map[food[0]][food[1]]==3);//����һ���ڷ�Χ��� 
	
	length++;
	score+=10;
	printf("\a");//��ʳ�����ʾ�� 
    }
}

void poisonfood()
{
	srand(time(NULL));
	if(map[poison[0]][poison[1]]==1){//������� 
	    do{
		    poison[0]=rand()%20;
	        poison[1]=rand()%40;
	    }while(map[poison[0]][poison[1]]==1 || map[poison[0]][poison[1]]==4 || map[poison[0]][poison[1]]==2);//����һ���ڷ�Χ��� 
	
	length--;
	map[snake[length][0]][snake[length][1]]=0;
	score-=10;
	printf("\a");//��du����ʾ�� 
    }
} 
 
void gameover(void)
{
	int i;
	if(snake[0][0]==0 || snake[0][0]==19 || snake[0][1]==0 || snake[0][1]==39){
		system("color 74");
		printf("С��ײ����ǽҲ����ͷ����Ȼ��׳ʿ���������\a\n�ٴε���˳���Ϸ\n");
		system("pause");
		exit(0);
	}
	if(length<=1){
		system("color 74");
		printf("���С���яC����һ�����磬�Ӵ���ʧ��������Ȼ����\a\n�ٴε���˳���Ϸ��Ҳ�úú�������ͬ������\n");
		system("pause");
		exit(0);
	}
	for(i=1;i<length;i++){//С��i��1��ʼ����0����Ϊ��ʼ��Ϊ0 
		if(snake[0][0]==snake[i][0] && snake[0][1]==snake[i][1]){
			system("color 74");
			printf("������ʳ�ӣ���̰��ҧβ\n\a�㻹���ٴε������������������˳�����Ϸ���߰�!");
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
    printf("����������ʼ��̰Ǯ�ߡ���Ϸ,�����С�߻���\n");
    printf("wsad�ֱ��ʾ�������ң��������С�߲��ı䷽��**************��Ǯ���˱䳤��!!���˱��,�Ϊ10��\n");
	system("pause");
	startSnake();//��ʼ���� �� ʳ�ﶾ�� 
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
	printf("\a����С���Ѿ�̫�����С�������ݲ�����������ȥ�������ģ��;�����\n");
	
	return 0;
}
