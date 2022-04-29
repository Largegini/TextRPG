// scanf�Լ��� ���Ȱ��� ������ �� �������� ���
#define _CRT_SECURE_NO_WARNINGS		

// ��������� ����ϱ����� ����
#include <stdio.h>		
#include <stdlib.h>
#include <string>
#include <time.h>
#include <malloc.h>
#include <Windows.h>


const int Scene_Logo = 0;
const int Scene_Menu = 1;
const int Scene_Stage = 2;
const int Scene_Exit = 3;

int Check = 1;

// Scene��ȯ�� ���� ���������� ����
int SceneState = 0;

//����ü�ȿ��� ����ڰ� ����ϰ� ���� ���� �־ �뵵���� �����Ѵ�
// Status ����ü
typedef struct tagInfo
{

	int HP;
	int MP;

	// �����ɷ°��õ� �����̸� �Ŀ� �÷��̾�� ������ ���� �İ��� �����ϱ����� ����
	int Speed;
	int EXP;

	short Level;

	float Att;
	float Def;

}INFO;

//  ��ü ����ü
typedef struct tagObject
{
	char* Name;


	INFO Info;

}Object;

typedef struct tagEquipment
{
	int Price;
	INFO Info;
	Object object;
}EQUIPMENT;

typedef struct tagItem
{
	int Price;
}ITEM;

typedef struct tagInventory
{
	int Space;
	int Stock;

}INVENTORY;

// �Լ� ���� ����
char* SetName();

void SceneManager(Object* Player, Object* Enemy, EQUIPMENT* Equipment);
void LogoScene();
void MenuScene();
void StageScene(Object* Player, Object* Enemy, EQUIPMENT* Equipment);

void GraveYard(Object* Player, Object* Enemy, EQUIPMENT* Equipment);
void GraveYardBackGround();
void AdventurerVillage(Object* Player, Object* Enemy, EQUIPMENT* Equipment);
void Castle(Object* Player, Object* Enemy, EQUIPMENT* Equipment);
void NecromancerTower(Object* Player, Object* Enemy, EQUIPMENT* Equipment);

void Dungeon(Object* Player, Object* Enemy, EQUIPMENT* Equipment, int EnemyIndex, int EventCount);

void InitializeObjectPlayer(Object* Player);
void PlayerScene(Object* Playe);

void InitializeObjectEnemy(Object* Enemy, int EnemyIndex);
int EnemyScene(Object* Enemy, int EnemyIndex);

void InitializeEquipment(EQUIPMENT* Equipment, int EquipmentIndex);

void Battle(Object* Player, Object* Enemy, int EnemyIndex);
void Status(Object* Player, Object* Enemy, int EnemyIndex);
void PlayerStatus(Object* Player);
void EnemyStatus(Object* Enemy, int EnemyIndex);
void PlayerAttack(Object* Player, Object* Enemy, int EnemyIndex);
void EnemyAttack(Object* Player, Object* Enemy, int EnamyIndex);

void SetPosition(int _x, int _y, char* _str, int _Color = 2);
void SetColor(int _Color);
void HideCursor();



int main(void)
{
	// ** Ŀ���� �Ⱥ��̰� ��
	HideCursor();

	//�ܼ�â�� ����� ����
	system("mode con:cols=120 lines=30");

	//�ܼ�â�� �̸��� ����
	system("title ������ Undead Fantasy v0.1");

	Object* Player = (Object*)malloc(sizeof(Object));		//PLAYER �����Ҵ�
	InitializeObjectPlayer(Player);							//�ʱ�ȭ//ENEMY �����Ҵ�

	int Max = 30;
	Object* Enemy;
	Enemy = (Object*)malloc(sizeof(Object) * 32);
	for (int i = 0; i < Max; i++)
	{
		InitializeObjectEnemy(Enemy, i);							//�ʱ�ȭ
	}
	EQUIPMENT* Equipment;
	Equipment = (EQUIPMENT*)malloc(sizeof(EQUIPMENT) * 32);

	for (int i = 0; i < Max; i++)
	{
		InitializeEquipment(Equipment,i);
	}

	// GetTickCount 1/1000���� ���� ����
	//DWORD dwTime = GetTickCount(); // typedef unsigned long DWORD
	//int Delay = 1000;

	while (true)
	{
		//Scene�� �����ϱ� ���� ���� �ʱ�ȭ

		// ** 1�ʸ��� ����Ǵ� ����
		// ó������ 0+1000 < GetTickCount()
	//	if (dwTime + Delay < GetTickCount())	
	//	{
			//GetTickCount�� 1000���� Ŀ������ ����
	//		dwTime = GetTickCount(); //dwTime = 1001

			//�ܼ�â�� �ִ� ��系���� ����
		system("cls");

		//** ���� ����
		//  �Լ� SceneManger�� �־� �۵� �Ѵ�
		SceneManager(Player, Enemy, Equipment);
		//	}
	}
	/*
	* /***** �����ʹ� �ּҸ� �޴´� �����ʹ� ���� �Ұ�
	int iNumber = 10;
	int* pNumber = (int*)malloc(sizeof(int));

	// �� ������ ���� �ֱ����� pNumber �տ� * �� �ִ´�
	*pNumber = iNumber;
	//�������� �ּ� = iNumber ;

	// �� ���� ���
	void ABC(int _i,int _n)
	{
		_i =100;										//i_Number1���� �����ؿ� �� 10�� 100���� ����
		_n = 200;										//i_Number2���� �����ؿ� �� 20�� 200���� ����

		printf_s("ABC _i : %d",_i);
		printf_s("ABC _n : %d",_n);
	}

	// �� ���� ���۷���
	void DEF (int* _i,int* _n)
	{
		_i = 100;										//i_Number1�� �ּҷ� ������ �� 10�� 100���� ����
		_n = 100;										//i_Number2�� �ּҷ� ������ �� 10�� 200���� ����
		printf_s("ABC *_i : %d", *_i);
		printf_s("ABC *_n : %d", *_n);
	}

	void main()
	{
		int iNumber1 = 10;
		int iNumber2 = 20;

		printf_f("iNumber1: %d\n", &iNumber1);			//iNumber1�� �ּҰ� ���
		printf_f("iNumber2: %d\n\n", &iNumber2);		//iNumber2�� �ּҰ� ���

		// �� ���� ���
		ABC(iNumber1, iNumber2);						// iNumber1,iNumber2�� ���� �Լ� ABC�� �Ű����� _i,_n�� ����
		printf_f("ABC iNumber1: %d\n",iNumber1);		// iNumber1�� ���� �Ǿ��ִ� ���� ������ �ʾ����Ƿ� 10���
		printf_f("ABC iNumber2: %d\n\n",iNumber2);		// iNumber2�� ���� �Ǿ��ִ� ���� ������ �ʾ����Ƿ� 20���

		// �� ���� ���۷���
		DEF(&iNumber1, &iNumber2);						// iNumber1, iNumber2�� �ּҸ� �Լ� DEF�� �Ű����� *_i, *_n�� ����
		printf_f("DEF iNumber1: %d\n",iNumber1);		// iNumber1�� ���� �Ǿ��ִ� ���� �������Ƿ� 100���
		printf_f("DEF iNumber2: %d\n\n",iNumber2);		// iNumber2�� ���� �Ǿ��ִ� ���� �������Ƿ� 200���
	}





	while (Loop)
	{


	}
	*/


	return 0;
}

//��ü ���� �ʱ�ȭ �Լ�



//�÷��̾� �̸��� �����ϴ� �Լ�
char* SetName()
{
	//���ڿ��� �Է¹ޱ����� ������ �迭 ����
	//�����ͷδ� ���ڿ��� �Է¹��� �� ���� ������ ������ �迭�� �����Ѵ�.
	char Buffer[128] = "";

	printf_s("���� �� �� �״� �̸��� �����ΰ�?\n");
	Sleep(1000);

	printf_s("�� �̸���...\n");
	Sleep(500);

	printf_s("�̸��� �Է��Ͻʽÿ�. : ");

	//���ڿ��� �Է� ����.
	scanf("%s", Buffer);

	// ** �Է¹��� ���� �迭�̳� ��ȯ ���� ĳ���� ��������(char*)�̹Ƿ� ���ڿ��� �����ؾ���.
	// ** ���ڿ��� ���� �ϱ����� �����Ͱ� ����Ű�� ������ �Է¹��� ���ڿ��� �� ��ŭ�� ũ��� �޸� �Ҵ�
	char* pName = (char*)malloc(strlen(Buffer) + 1);	//���ڿ��� ����ȯ�� �ؾ���, NULL���� �־��ֱ� ���� +1�� �Ѵ�

	// Buffer�� ���� ���ڿ��� ������pName�� ���ڿ� ����
	strcpy(pName, Buffer);

	// ������ �� ��ȯ
	return pName;
}

void SceneManager(Object* Player, Object* Enemy, EQUIPMENT* Equipment)						// Scene����
{
	switch (SceneState)									//������ ���� Scene�� �����ϱ����� switch��
	{
	case Scene_Logo:
		LogoScene();									// LogoScene ����
		break;

	case Scene_Menu:
		MenuScene();									// MenuScene ����
		break;

	case Scene_Stage:
		StageScene(Player, Enemy, Equipment);						// StageScene ����
		break;

	case Scene_Exit:									//����

		exit(NULL);
		break;
	}
}

void LogoScene()										//LogoScene
{
	int Width(120 / 2 - (strlen(" __    _____ _____ _____ ") / 2));
	int Height = 5;

	SetPosition(Width, Height, (char*)" __    _____ _____ _____ ");
	SetPosition(Width, Height + 1, (char*)"|  |  |     |   __|     |");
	SetPosition(Width, Height + 2, (char*)"|  |__|  |  |  |  |  |  |");
	SetPosition(Width, Height + 3, (char*)"|_____|_____|_____|_____|");

	Sleep(3000);
	//����Scene���� �������� ���� �� ����
	SceneState++;
}

void MenuScene()
{
	//�Է��� �ޱ����� ����
	int iChoice = 0;

	printf_s("Undead Fantasy \n");
	printf_s("1.���ӽ���\n2.����\n�Է� :");
	scanf("%d", &iChoice);

	//iChoice���� ���� ���� �Ѿ�ų� ������
	switch (iChoice)
	{
	case 1:												//1�� �Է��ϸ� ���� ���� ����
		SceneState++;
		break;

	case 2:											//2�� �Է��ϸ� ����
		SceneState = Scene_Exit;
		break;

	default:											//1�� 2���ƴ� �Է��� �޾��� ��� ó���ϱ�����
		printf_s("�߸��� �Է��Դϴ�! ���� �����մϴ�.\n");
		SceneState++;
		break;
	}

}

void StageScene(Object* Player, Object* Enemy, EQUIPMENT* Equipment)
{
	int iStage = 0;
	switch (iStage)
	{
	case 0:
		//** ����
		GraveYard(Player, Enemy, Equipment);
		iStage++;
		break;

	case 1:
		// ** ���谡 ����
		AdventurerVillage(Player, Enemy, Equipment);
		break;

	case 2:
		// ** �ռ�
		Castle(Player, Enemy, Equipment);
		break;

	case 3:
		// ** ��ɼ����� ž
		NecromancerTower(Player, Enemy, Equipment);
		break;
	}
	// ** ���ȭ �Լ������ �뵵���� ����� �� �ְ�
	// ** �̵�
	//  * * * �Է�(Input)
	//  * * * �÷��̾� ��ǥ������ ����
	//  * * * ���� ������ ũ�� ������ ����
	//  * * * ���� ������Ʈ���� �̵��ӵ� ������ ����

	// ** ����
	PlayerScene(Player);


	// ** ����
	// 
	// ** ��ȭ
	// 


	/*
	srand(time(NULL));									//rand �Լ��� ����ϱ����� �ʱ�ȭ

	// malloc �Լ��� ������ �Ǹ� �ּҰ��� ��ȯ�Ѵ�		** malloc�Լ��� ��ȯ ���� ������ �������� ������ �޸� ������ �߻��Ѵ�.
	//					�������� ������ �����
	/*
	*
	* int iNumber=10;
	*
	// �Q ������ ������ ����� �ּҰ��� ������ pNumber�� ����
	//pNumber�� �Q�� �Ҵ�� ������ ���� ����
	* int*pNumber = (int*) malloc(sizeof(int));
	*
	// ������ pNumber�� iNumber�� �ּҰ��� ����
	// ** �� �̻� pNumber�� �Q������ ���� ������ ���� �Ұ� �ϰԵ� (�޸� ����)
	* pNumber = &iNumber;
	*



	*/
}


// �÷��̾�
void InitializeObjectPlayer(Object* Player)
{
	//PLAYER�� ��ü ������ �ʱ�ȭ�Ѵ�

	Player->Info.HP = 100;
	Player->Info.MP = 10;
	Player->Info.Att = 10;
	Player->Info.Def = 5;
	Player->Info.Speed = 10;
	Player->Info.Level = 1;
	Player->Info.EXP = 0;
}


void PlayerScene(Object* Player)
{

}


// ��
void InitializeObjectEnemy(Object* Enemy, int EnemyIndex)
{
	switch (EnemyIndex)
	{
	case 0:
		Enemy[EnemyIndex].Name = (char*)"��";
		Enemy[EnemyIndex].Info.HP = 10;
		Enemy[EnemyIndex].Info.MP = 5;
		Enemy[EnemyIndex].Info.Att = 7;
		Enemy[EnemyIndex].Info.Def = 5;
		Enemy[EnemyIndex].Info.Speed = 5;
		Enemy[EnemyIndex].Info.EXP = 1;
		break;

	case 1:
		Enemy[EnemyIndex].Name = (char*)"�ù�";
		Enemy[EnemyIndex].Info.HP = 30;
		Enemy[EnemyIndex].Info.MP = 5;
		Enemy[EnemyIndex].Info.Att = 5;
		Enemy[EnemyIndex].Info.Def = 15;
		Enemy[EnemyIndex].Info.Speed = 5;
		break;

	case 2:
		Enemy[EnemyIndex].Name = (char*)"���谡";
		Enemy[EnemyIndex].Info.HP = 30;
		Enemy[EnemyIndex].Info.MP = 5;
		Enemy[EnemyIndex].Info.Att = 5;
		Enemy[EnemyIndex].Info.Def = 15;
		Enemy[EnemyIndex].Info.Speed = 5;
		break;

	case 3:
		Enemy[EnemyIndex].Name = (char*)"����";
		Enemy[EnemyIndex].Info.HP = 30;
		Enemy[EnemyIndex].Info.MP = 5;
		Enemy[EnemyIndex].Info.Att = 5;
		Enemy[EnemyIndex].Info.Def = 15;
		Enemy[EnemyIndex].Info.Speed = 5;
		break;
	case 4:
		Enemy[EnemyIndex].Name = (char*)"������";
		Enemy[EnemyIndex].Info.HP = 30;
		Enemy[EnemyIndex].Info.MP = 5;
		Enemy[EnemyIndex].Info.Att = 5;
		Enemy[EnemyIndex].Info.Def = 15;
		Enemy[EnemyIndex].Info.Speed = 5;
		break;
	case 5:
		Enemy[EnemyIndex].Name = (char*)"���";
		Enemy[EnemyIndex].Info.HP = 30;
		Enemy[EnemyIndex].Info.MP = 5;
		Enemy[EnemyIndex].Info.Att = 5;
		Enemy[EnemyIndex].Info.Def = 15;
		Enemy[EnemyIndex].Info.Speed = 5;
		break;
	case 6:
		Enemy[EnemyIndex].Name = (char*)"�������";
		Enemy[EnemyIndex].Info.HP = 30;
		Enemy[EnemyIndex].Info.MP = 5;
		Enemy[EnemyIndex].Info.Att = 5;
		Enemy[EnemyIndex].Info.Def = 15;
		Enemy[EnemyIndex].Info.Speed = 5;
		break;
	case 7:
		Enemy[EnemyIndex].Name = (char*)"�����ô��";
		Enemy[EnemyIndex].Info.HP = 30;
		Enemy[EnemyIndex].Info.MP = 5;
		Enemy[EnemyIndex].Info.Att = 5;
		Enemy[EnemyIndex].Info.Def = 15;
		Enemy[EnemyIndex].Info.Speed = 5;
		break;
	case 8:
		Enemy[EnemyIndex].Name = (char*)"������̴�";
		Enemy[EnemyIndex].Info.HP = 30;
		Enemy[EnemyIndex].Info.MP = 5;
		Enemy[EnemyIndex].Info.Att = 5;
		Enemy[EnemyIndex].Info.Def = 15;
		Enemy[EnemyIndex].Info.Speed = 5;
		break;
	case 9:
		Enemy[EnemyIndex].Name = (char*)"��ũ";
		Enemy[EnemyIndex].Info.HP = 30;
		Enemy[EnemyIndex].Info.MP = 5;
		Enemy[EnemyIndex].Info.Att = 5;
		Enemy[EnemyIndex].Info.Def = 15;
		Enemy[EnemyIndex].Info.Speed = 5;
		break;
	case 10:
		Enemy[EnemyIndex].Name = (char*)"��ũ����";
		Enemy[EnemyIndex].Info.HP = 30;
		Enemy[EnemyIndex].Info.MP = 5;
		Enemy[EnemyIndex].Info.Att = 5;
		Enemy[EnemyIndex].Info.Def = 15;
		Enemy[EnemyIndex].Info.Speed = 5;
		break;
	case 11:
		Enemy[EnemyIndex].Name = (char*)"��ũ�ּ���";
		Enemy[EnemyIndex].Info.HP = 30;
		Enemy[EnemyIndex].Info.MP = 5;
		Enemy[EnemyIndex].Info.Att = 5;
		Enemy[EnemyIndex].Info.Def = 15;
		Enemy[EnemyIndex].Info.Speed = 5;
		break;
	case 12:
		Enemy[EnemyIndex].Name = (char*)"�����";
		Enemy[EnemyIndex].Info.HP = 30;
		Enemy[EnemyIndex].Info.MP = 5;
		Enemy[EnemyIndex].Info.Att = 5;
		Enemy[EnemyIndex].Info.Def = 15;
		Enemy[EnemyIndex].Info.Speed = 5;
		break;
	case 13:
		Enemy[EnemyIndex].Name = (char*)"����";
		Enemy[EnemyIndex].Info.HP = 30;
		Enemy[EnemyIndex].Info.MP = 5;
		Enemy[EnemyIndex].Info.Att = 5;
		Enemy[EnemyIndex].Info.Def = 15;
		Enemy[EnemyIndex].Info.Speed = 5;
		break;
	case 14:
		Enemy[EnemyIndex].Name = (char*)"���";
		Enemy[EnemyIndex].Info.HP = 30;
		Enemy[EnemyIndex].Info.MP = 5;
		Enemy[EnemyIndex].Info.Att = 5;
		Enemy[EnemyIndex].Info.Def = 15;
		Enemy[EnemyIndex].Info.Speed = 5;
		break;
	case 15:
		Enemy[EnemyIndex].Name = (char*)"������";
		Enemy[EnemyIndex].Info.HP = 30;
		Enemy[EnemyIndex].Info.MP = 5;
		Enemy[EnemyIndex].Info.Att = 5;
		Enemy[EnemyIndex].Info.Def = 15;
		Enemy[EnemyIndex].Info.Speed = 5;
		break;
	case 16:
		Enemy[EnemyIndex].Name = (char*)"����";
		Enemy[EnemyIndex].Info.HP = 30;
		Enemy[EnemyIndex].Info.MP = 5;
		Enemy[EnemyIndex].Info.Att = 5;
		Enemy[EnemyIndex].Info.Def = 15;
		Enemy[EnemyIndex].Info.Speed = 5;
		break;
	case 17:
		Enemy[EnemyIndex].Name = (char*)"�����";
		Enemy[EnemyIndex].Info.HP = 30;
		Enemy[EnemyIndex].Info.MP = 5;
		Enemy[EnemyIndex].Info.Att = 5;
		Enemy[EnemyIndex].Info.Def = 15;
		Enemy[EnemyIndex].Info.Speed = 5;
		break;
	case 18:
		Enemy[EnemyIndex].Name = (char*)"���˻�";
		Enemy[EnemyIndex].Info.HP = 30;
		Enemy[EnemyIndex].Info.MP = 5;
		Enemy[EnemyIndex].Info.Att = 5;
		Enemy[EnemyIndex].Info.Def = 15;
		Enemy[EnemyIndex].Info.Speed = 5;
		break;
	case 19:
		Enemy[EnemyIndex].Name = (char*)"��������";
		Enemy[EnemyIndex].Info.HP = 30;
		Enemy[EnemyIndex].Info.MP = 5;
		Enemy[EnemyIndex].Info.Att = 5;
		Enemy[EnemyIndex].Info.Def = 15;
		Enemy[EnemyIndex].Info.Speed = 5;
		break;
	case 20:
		Enemy[EnemyIndex].Name = (char*)"��������";
		Enemy[EnemyIndex].Info.HP = 30;
		Enemy[EnemyIndex].Info.MP = 5;
		Enemy[EnemyIndex].Info.Att = 5;
		Enemy[EnemyIndex].Info.Def = 15;
		Enemy[EnemyIndex].Info.Speed = 5;
		break;
	case 21:
		Enemy[EnemyIndex].Name = (char*)"�ٶ�����";
		Enemy[EnemyIndex].Info.HP = 30;
		Enemy[EnemyIndex].Info.MP = 5;
		Enemy[EnemyIndex].Info.Att = 5;
		Enemy[EnemyIndex].Info.Def = 15;
		Enemy[EnemyIndex].Info.Speed = 5;
		break;
	case 22:
		Enemy[EnemyIndex].Name = (char*)"��������";
		Enemy[EnemyIndex].Info.HP = 30;
		Enemy[EnemyIndex].Info.MP = 5;
		Enemy[EnemyIndex].Info.Att = 5;
		Enemy[EnemyIndex].Info.Def = 15;
		Enemy[EnemyIndex].Info.Speed = 5;
		break;
	case 23:
		Enemy[EnemyIndex].Name = (char*)"���ɻ�";
		Enemy[EnemyIndex].Info.HP = 30;
		Enemy[EnemyIndex].Info.MP = 5;
		Enemy[EnemyIndex].Info.Att = 5;
		Enemy[EnemyIndex].Info.Def = 15;
		Enemy[EnemyIndex].Info.Speed = 5;
		break;
	case 24:
		Enemy[EnemyIndex].Name = (char*)"�ذ�";
		Enemy[EnemyIndex].Info.HP = 30;
		Enemy[EnemyIndex].Info.MP = 5;
		Enemy[EnemyIndex].Info.Att = 5;
		Enemy[EnemyIndex].Info.Def = 15;
		Enemy[EnemyIndex].Info.Speed = 5;
		break;
	case 25:
		Enemy[EnemyIndex].Name = (char*)"�ذ񺴻�";
		Enemy[EnemyIndex].Info.HP = 30;
		Enemy[EnemyIndex].Info.MP = 5;
		Enemy[EnemyIndex].Info.Att = 5;
		Enemy[EnemyIndex].Info.Def = 15;
		Enemy[EnemyIndex].Info.Speed = 5;
		break;
	case 26:
		Enemy[EnemyIndex].Name = (char*)"�ذ�ü�";
		Enemy[EnemyIndex].Info.HP = 30;
		Enemy[EnemyIndex].Info.MP = 5;
		Enemy[EnemyIndex].Info.Att = 5;
		Enemy[EnemyIndex].Info.Def = 15;
		Enemy[EnemyIndex].Info.Speed = 5;
		break;
	case 27:
		Enemy[EnemyIndex].Name = (char*)"��ġ";
		Enemy[EnemyIndex].Info.HP = 30;
		Enemy[EnemyIndex].Info.MP = 5;
		Enemy[EnemyIndex].Info.Att = 5;
		Enemy[EnemyIndex].Info.Def = 15;
		Enemy[EnemyIndex].Info.Speed = 5;
		break;
	case 28:
		Enemy[EnemyIndex].Name = (char*)"����";
		Enemy[EnemyIndex].Info.HP = 30;
		Enemy[EnemyIndex].Info.MP = 5;
		Enemy[EnemyIndex].Info.Att = 5;
		Enemy[EnemyIndex].Info.Def = 15;
		Enemy[EnemyIndex].Info.Speed = 5;
		break;
	case 29:
		Enemy[EnemyIndex].Name = (char*)"�渶����";
		Enemy[EnemyIndex].Info.HP = 30;
		Enemy[EnemyIndex].Info.MP = 5;
		Enemy[EnemyIndex].Info.Att = 5;
		Enemy[EnemyIndex].Info.Def = 15;
		Enemy[EnemyIndex].Info.Speed = 5;
		break;
	case 30:
		Enemy[EnemyIndex].Name = (char*)"��ɼ���";
		Enemy[EnemyIndex].Info.HP = 30;
		Enemy[EnemyIndex].Info.MP = 5;
		Enemy[EnemyIndex].Info.Att = 5;
		Enemy[EnemyIndex].Info.Def = 15;
		Enemy[EnemyIndex].Info.Speed = 5;
		break;


	}


}

int EnemyScene(Object* Enemy,int EnemyIndex)
{
	int Battle = 1;

	// �� �й�
	if (Enemy[EnemyIndex].Info.HP <= 0)
	{
		printf_s("%s��(��) �����߷ȴ�!\n", Enemy[EnemyIndex].Name);
		Sleep(300);

		printf_s("����ġ %d��(��) �����!\n", Enemy[EnemyIndex].Info.EXP);
		Sleep(300);

		//printf_s("��� %d��(��) �����!");

		Battle = 0;
		
	}
	return Battle;
}

void InitializeEquipment(EQUIPMENT* Equipment,int EquipmentIndex)
{
	// *****	0 = �� 1 = ���� 2 = â 3 = Ȱ
	// *****	4 = �Ӹ� 5 = ���� 6 = ���� 7 = �� 8 = �尩 9 = ��ű�
		switch (EquipmentIndex)
		{
		case 0:
			Equipment[EquipmentIndex].object.Name = (char*)"������ ��";
			Equipment[EquipmentIndex].Info.Att = 5;
			Equipment[EquipmentIndex].Info.Speed = 0;
			break;
		case 1:
			Equipment[EquipmentIndex].object.Name = (char*)"������ ����";
			Equipment[EquipmentIndex].Info.Att = 7;
			Equipment[EquipmentIndex].Info.Speed = -2;
			break;
		case 2:
			Equipment[EquipmentIndex].object.Name = (char*)"������ â";
			Equipment[EquipmentIndex].Info.Att = 4;
			Equipment[EquipmentIndex].Info.Speed = 1;
			break;
		case 3:
			Equipment[EquipmentIndex].object.Name = (char*)"������ Ȱ";
			Equipment[EquipmentIndex].Info.Att = 5;
			Equipment[EquipmentIndex].Info.Speed = 0;
			break;
		case 4:
			Equipment[EquipmentIndex].object.Name = (char*)"�㸧�� ����";
			Equipment[EquipmentIndex].Info.Def = 1;
			Equipment[EquipmentIndex].Info.Speed = 0;
		case 5:
			Equipment[EquipmentIndex].object.Name = (char*)"�㸧�� ����";
			Equipment[EquipmentIndex].Info.Def = 1;
			Equipment[EquipmentIndex].Info.Speed = 0;
		case 6:
			Equipment[EquipmentIndex].object.Name = (char*)"�㸧�� ����";
			Equipment[EquipmentIndex].Info.Def = 4;
			Equipment[EquipmentIndex].Info.Speed = 0;
		case 7:
			Equipment[EquipmentIndex].object.Name = (char*)"�㸧�� ��ȭ";
			Equipment[EquipmentIndex].Info.Def = 4;
			Equipment[EquipmentIndex].Info.Speed = 0;
		case 8:
			Equipment[EquipmentIndex].object.Name = (char*)"�㸧�� �尩";
			Equipment[EquipmentIndex].Info.Def = 4;
			Equipment[EquipmentIndex].Info.Speed = 0;

		}
}

void GraveYard(Object* Player, Object* Enemy, EQUIPMENT* Equipment)
{
	int iChoice = 0;
	int iStartWeapon = 0;

	srand(time(NULL));
	
	SetColor(12);

	int Width(120 / 2 - (strlen("........................................................................") / 2));
	int Height = 5;

	SetPosition(Width, Height, (char*)"........................................................................");
	SetPosition(Width, Height+1, (char*)"..%%%%...%%%%%....%%%%...%%..%%..%%%%%%..%%..%%...%%%%...%%%%%...%%%%%..");
	SetPosition(Width, Height+2, (char*)".%%......%%..%%..%%..%%..%%..%%..%%.......%%%%...%%..%%..%%..%%..%%..%%.");
	SetPosition(Width, Height+3, (char*)".%%.%%%..%%%%%...%%%%%%..%%..%%..%%%%......%%....%%%%%%..%%%%%...%%..%%.");
	SetPosition(Width, Height+4, (char*)".%%..%%..%%..%%..%%..%%...%%%%...%%........%%....%%..%%..%%..%%..%%..%%.");
	SetPosition(Width, Height+5, (char*)"..%%%%...%%..%%..%%..%%....%%....%%%%%%....%%....%%..%%..%%..%%..%%%%%..");
	SetPosition(Width, Height+6, (char*)"........................................................................");

	Sleep(1500);

	system("cls");
	
	SetColor(15);

	GraveYardBackGround();

	Player->Name = SetName();
	Sleep(500);

	GraveYardBackGround();

	//�������� �����̹���
	printf_s("���� �Ͼ ���� ���� �ִ°� ����\n");
	printf_s("1.�������� 2.�׳� ���д� �Է�: ");
	scanf_s("%d", &iChoice);
	switch (iChoice)
	{
		case 1:
			GraveYardBackGround();

			//���� ��� �������� �ο�
			iStartWeapon = rand() % 4;

			//��� �̹���
			printf_s("%s�� �߰��ߴ�!\n", Equipment[iStartWeapon].object.Name);

			//����� ���ݷ��� �÷��̾� ���ݷ¿� ���Ѵ�
			Player->Info.Att += Equipment[iStartWeapon].Info.Att;
			Player->Info.Speed += Equipment[iStartWeapon].Info.Speed;
			Sleep(1000);

			GraveYardBackGround();

			printf_s("%s\n�켱 ������ ���� ������ ��ƾ߰ھ�\n",Player->Name);
			Sleep(1000);

			GraveYardBackGround();
			//���� 0 ����
			Dungeon(Player, Enemy, Equipment, 0, 5);

			break;

		default:
			printf_s("%s\n�켱 ������ ���� ������ ��ƾ߰ھ�\n", Player->Name);

			GraveYardBackGround();
			//���� 0 ����
			Dungeon(Player, Enemy, Equipment, 0, 5);

			break;
		}

	iChoice = 0;
	// ��� �̹���
	printf_s("���߽ʽÿ�! �� ���� ���̽ŵ�...\n");
	scanf("%d", &iChoice);
	printf_s("���谡��� ��忡 ���� ��� �Ͻô°� ���� �̴ϴ�.");

}

//** ���� ���
void GraveYardBackGround()
{
	system("cls");

	printf_s("                                                                                            #@@@@                       \n");
	printf_s("                                                #@@@$                 $@@@@@$               @   $                       \n");
	printf_s("              $@@@@@@$                          @   @                $@     @@$             @   @                       \n");
	printf_s("            $@@      @@@$                  =$   @   @               $@        @$         @@@@   @@@$                    \n");
	printf_s("           $@           @$                 *@@$ @   @               @          @         @         @                    \n");
	printf_s("           @             @$                @  @@@   @              $@          @$        #         @                    \n");
	printf_s("          $@              @                @    @@$ @              @            @        @@@#   @@@@                    \n");
	printf_s("          @               @                @$   @ @@@@@$          $@            @           @   $                       \n");
	printf_s("          @ $@$=@@@@$ $=  @                 @$  @   @  @@$        @             @           @   @                       \n");
	printf_s("          @ @ @@$   @@@   @                  @@$@   @    @       $@             @           @   @                       \n");
	printf_s("          @$@   @@@$      @                    @@@$ @    @       @              @           @   @                       \n");
	printf_s("     $@@@@@@     $@@      @                     @ @@@    @       @              @          $@@@@@$                      \n");
	printf_s("     @        =@@@        ,$                    @   @@@@@@       @              @       $@@@     @@$              $@@$  \n");
	printf_s("    =@         @@@@$       @                    @   @            @              @      $@          @$         $@@@@  @@@\n");
	printf_s("     @@@$          @$=@=   @                    @   @            @              @     $@            @$      $@@         \n");
	printf_s("       $@          $@      @=@@@@$              @   @            @              @     @              @$   $@@           \n");
	printf_s("      *@    $@@@@@@@       @     @@@@$          @  $@            @              #    $@               @  $@             \n");
	printf_s("     $@@    @              @         @@$        @  ##         *=@@@@@@@@@@@@@@@@@@$ $@                @$=@              \n");
	printf_s("     @@    $@  =@@@@@@@=   @           @$*  $@@@@= =@@@@$     @                   @ @                  @                \n");
	printf_s("    $@@   $@        #      @            #@$ @           @    $@     $@@@@$        @ @                  @$               \n");
}

void AdventurerVillage(Object* Player, Object* Enemy, EQUIPMENT* Equipment)
{

}

void AdventurerVillageBackGround()
{

}

void Castle(Object* Player, Object* Enemy, EQUIPMENT* Equipment)
{

}

void NecromancerTower(Object* Player, Object* Enemy, EQUIPMENT* Equipment)
{

}



void Status(Object* Player, Object* Enemy, int EnemyIndex)
{
	system("cls");
	EnemyStatus(Enemy, EnemyIndex);

	printf_s("\n\n");

	PlayerStatus(Player);
}

void PlayerStatus(Object* Player)
{
	//�÷��̾��� ������ ���
	printf_s("[Player] : %s\n", Player->Name);
	printf_s("HP : %d\n", Player->Info.HP);
	printf_s("MP : %d\n", Player->Info.MP);
	//printf_s("���ݷ� : %.2f\n", Player->Info.Att);
	//printf_s("���� : %.2f\n", Player->Info.Def);
	//printf_s("���� : %d\n", Player->Info.Level);
	//printf_s("����ġ : %d\n", Player->Info.EXP);
}

void EnemyStatus(Object* Enemy, int EnemyIndex)
{
	//������ ������ ���
	printf_s("\n%s\n", Enemy[EnemyIndex].Name);
	printf_s("HP : %d\n", Enemy[EnemyIndex].Info.HP);
	printf_s("MP : %d\n", Enemy[EnemyIndex].Info.MP);
	//printf_s("���ݷ� : %.2f\n", Enemy[EnemyIndex].Info.Att);
	//printf_s("���� : %.2f\n", Enemy[EnemyIndex].Info.Def);
	//printf_s("���� : %d\n", Enemy[EnemyIndex].Info.Level);
	//printf_s("����ġ : %d\n", Enemy[EnemyIndex].Info.EXP);
}


void Battle(Object* Player, Object* Enemy, int EnemyIndex)
{
	// ���� �ݺ��� ���� �Լ�
	short Battle = 1;

	//����
	while (Battle)
	{
		//�Է��� �ޱ����� ���� �Լ�
		int iChoice = 0;
		printf_s("%s��(��) ��Ÿ����!!\n1.����\t2.���\t3.��ų\t4.����\n�Է� : ",Enemy[EnemyIndex].Name);
		scanf_s("%d", &iChoice);

		//�Է¹��� ���� ���� ��������
		switch (iChoice)
		{
			//������ �������� ��
		case 1:
			//** �ӵ��� ���� ��ü�� ���� �����ϰ��Ѵ�
			if (Player->Info.Speed > Enemy[EnemyIndex].Info.Speed)
			{
				PlayerAttack(Player, Enemy, EnemyIndex);
				// ���ݽ� ��Ÿ���� ������ ���̱� ���� ������ �Լ�
				Sleep(500);

				//�÷��̾� ���� �� ����â ����
				Status(Player, Enemy, EnemyIndex);

				Battle = EnemyScene(Enemy, EnemyIndex);
				if (Battle == 0)
				{
					InitializeObjectEnemy(Enemy, EnemyIndex);
					break;
				}

				//�÷��̾� ���� �� ������ ����
				EnemyAttack(Player, Enemy, EnemyIndex);

				//���� ���� ������ ���̱� ���� ������ �Լ�
				Sleep(500);

				// ���� ���� �� ����â ����
				Status(Player, Enemy, EnemyIndex);
			}

			else if (Player->Info.Speed <= Enemy[EnemyIndex].Info.Speed)
			{
				//������ ����
				EnemyAttack(Player, Enemy, EnemyIndex);

				//���� ���� ������ ���̱� ���� ������ �Լ�
				Sleep(500);

				// ���� ���� �� ����â ����
				Status(Player, Enemy, EnemyIndex);

				//���� ���� �� �÷��̾� ����
				PlayerAttack(Player, Enemy, EnemyIndex);
				// ���ݽ� ��Ÿ���� ������ ���̱� ���� ������ �Լ�
				Sleep(500);

				//�÷��̾� ���� �� ����â ����
				Status(Player, Enemy, EnemyIndex);

			}
			break;
			// **���
		case 2:

			break;
			// ** ��ų
		case 3:
			//** �ӵ��� ���� ��ü�� ���� �����ϰ��Ѵ�
			if (Player->Info.Speed > Enemy[EnemyIndex].Info.Speed)
			{
				PlayerAttack(Player, Enemy, EnemyIndex);
				// ���ݽ� ��Ÿ���� ������ ���̱� ���� ������ �Լ�
				Sleep(500);

				//�÷��̾� ���� �� ����â ����
				Status(Player, Enemy, EnemyIndex);

				//�÷��̾� ���� �� ������ ����
				EnemyAttack(Player, Enemy, EnemyIndex);

				//���� ���� ������ ���̱� ���� ������ �Լ�
				Sleep(500);

				// ���� ���� �� ����â ����
				Status(Player, Enemy, EnemyIndex);
			}

			else if (Player->Info.Speed <= Enemy[EnemyIndex].Info.Speed)
			{
				//������ ����
				EnemyAttack(Player, Enemy, EnemyIndex);

				//���� ���� ������ ���̱� ���� ������ �Լ�
				Sleep(500);

				// ���� ���� �� ����â ����
				Status(Player, Enemy, EnemyIndex);

				//���� ���� �� �÷��̾� ����
				PlayerAttack(Player, Enemy, EnemyIndex);
				// ���ݽ� ��Ÿ���� ������ ���̱� ���� ������ �Լ�
				Sleep(500);

				//�÷��̾� ���� �� ����â ����
				Status(Player, Enemy, EnemyIndex);

				Battle = EnemyScene(Enemy, EnemyIndex);
				if (Battle == 0)
				{
					InitializeObjectEnemy(Enemy, EnemyIndex);
					break;
				}

			}
			break;

			//������ �������� ��
		case 4:

			//�÷��̾��� Speed �� ������ ���� �� ����ĥ�� �ְ� ��
			if (Player->Info.Speed > Enemy[EnemyIndex].Info.Speed)
			{
				//������ Ȯ���� �� ���ְ� ��
				//�ֻ��� ������ �ý��� ä��
				if (rand() % 6 > 2)
				{
					printf_s("%s(��)�� �����ƴ�.\n", Player->Name);

					//���� ���� ��������
					Battle = 0;

					// ���� �� ���� ���� �ʱ�ȭ
					InitializeObjectEnemy(Enemy, EnemyIndex);

					//���������� ���̱����� ������
					Sleep(500);
				}

				// ���� ���� ��
				else
				{
					printf_s("%s�� ����ġġ ���ߴ�.\n", Player->Name);

					// ����ġ�� ������ �� ������ ���̱����� ������
					Sleep(500);

					// ���� ���� �� �� �Ҹ�� ������ ������ �ް��ϱ�����
					EnemyAttack(Player, Enemy, EnemyIndex);
					Sleep(500);

					Status(Player, Enemy, EnemyIndex);
				}
			}

			else
			{
				printf_s("%s�� ����ġġ ���ߴ�.\n", Player->Name);
				Sleep(500);

				EnemyAttack(Player, Enemy, EnemyIndex);

				Sleep(500);

				Status(Player, Enemy, EnemyIndex);
			}
			break;

			// �߸��� �Է½� �� �Ҹ� �ϰ� ����� ����
		default:
			printf_s("�߸��� �Է��Դϴ�! ");
			EnemyAttack(Player, Enemy, EnemyIndex);

			Sleep(500);

			Status(Player, Enemy, EnemyIndex);
			break;
		}

	
		
	}
}

void PlayerAttack(Object* Player, Object* Enemy, int EnemyIndex)
{
	printf_s("%s�� ����!!\n", Player->Name);
	//�÷��̾��� ���ݷ°� ������ ������ ���Ͽ� �������� ����ϴ� ���ǹ�
	if (Player->Info.Att > Enemy[EnemyIndex].Info.Def)
		Enemy[EnemyIndex].Info.HP -= (int)(Player->Info.Att - Enemy[EnemyIndex].Info.Def);
	// ������ �� ���� ��� �ּ� 1�� �������� �ַ�����
	else
		Enemy[EnemyIndex].Info.HP -= 1;
}

void EnemyAttack(Object* Player, Object* Enemy, int EnemyIndex)
{
	printf_s("������ ����!!\n");
	if (Enemy[EnemyIndex].Info.Att > Player->Info.Def)
		Enemy[EnemyIndex].Info.HP -= (int)(Enemy[EnemyIndex].Info.Att - Player->Info.Def);
	else
		Player->Info.HP -= 1;
}

void Dungeon(Object* Player, Object* Enemy, EQUIPMENT* Equipment, int EnemyIndex, int EventCount)
{
	short Walk = 1;
	int Loop = 0;
	while (Walk)

	{
		//** ���� �������� ����
		if (Loop < EventCount)
		{
			system("cls");

			//DWORD dwTime = GetTickCount(); // typedef unsigned long DWORD

			GraveYardBackGround();

			//int Delay = 1000;

			for (int i = 0; i < 3; i++)
			{
				printf(".");
				Sleep(333);
			}

			// ** 1�ʸ��� ����Ǵ� ����
			// ó������ 0+1000 < GetTickCount()
			//if (dwTime + Delay < GetTickCount())
			//{
				++Loop;
				//GetTickCount�� 1000���� Ŀ������ ����
				//dwTime = GetTickCount(); //dwTime = 1001

				//�� ����
				//** 3��° ����� �ù�
				if (Loop == 3)
				{
					// �ù��� ������ �� �ڽ��� �𵥵��� �� �˰Ե�?
					// ������ �ؾ��� �ʿ並 ����
					Status(Player, Enemy, 1);

					printf_s("%s\n���ƾ�! �� �̷� ���� ���̷�����?!\n",Enemy[1].Name);
					Sleep(500);

					system("cls");
					Battle(Player, Enemy, 1);
					printf_s("%s\n���� �� ������� ������ ���� �� �ǰڱ�\n",Player->Name);
					Sleep(1000);

					GraveYardBackGround();

					printf_s("%s\n�̾������� �������� ����\n", Player->Name);
					printf_s("����� �������� ���̴� ���� �ĳ´�.");

					GraveYardBackGround();

					//�ʱ� ��
					for (int i = 4; i < 9; i++)
					{
						printf_s("%s ��(��) �����!", Equipment[i].object.Name);
						Player->Info.Def += Equipment[i].Info.Def;
						Sleep(500);
					}
					
				}

				else
				{
					Status(Player, Enemy, EnemyIndex);
					Battle(Player, Enemy, EnemyIndex);
				}
			//}
		}

		else if (Loop >= EventCount)
			Walk = 0;

	}
}

void SetPosition(int _x, int _y, char* _str, int _Color)
{
	//SetConsoleCursorPosition �Լ��� �Ű� ������ ���� �ϱ⶧���� ����
	COORD Pos = { _x,_y };	//short���̴�.

	//�ܼ� Ŀ�� ��ġ ���� �Լ�
	//�Ű������� ���� �ڵ鰪, ���� Pos���� ���� �Ѵ�.
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
	SetColor(_Color);

	printf_s("%s", _str);
}

void SetColor(int _Color)
{
	//�ؽ�Ʈ �� ����
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), _Color);
}

void HideCursor()
{
	CONSOLE_CURSOR_INFO Info;

	Info.dwSize = 1;
	Info.bVisible = false;

	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &Info);
}