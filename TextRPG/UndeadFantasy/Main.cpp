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

// Scene��ȯ�� ���� ���������� ����
int SceneState = 0;
int iStage = 0;

//����ü�ȿ��� ����ڰ� ����ϰ� ���� ���� �־ �뵵���� �����Ѵ�
// Status ����ü
typedef struct tagInfo
{
	int Gold;

	int HP;
	int MaxHP;
	int MP;
	int MaxMP;
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

	int State;
	//���� ��ȣ(����Ʈ�� ���� ����)
	int Num;
	int Kills;

	INFO Info;

}Object;

typedef struct tagEquipment
{
	int Price;
	int Stock;

	INFO Info;
	Object object;
}EQUIPMENT;

typedef struct tagEffect
{
	INFO Info;
}EFFECT;

typedef struct tagItem
{
	Object Object;
	EQUIPMENT Equipment;
	EFFECT Effect;
}ITEM;

typedef struct tagInventory
{
	EQUIPMENT Equipment;
	ITEM item;
	INFO Info;
}INVENTORY;

typedef struct tagSkill
{
	int Type;
	int Cost;

	float Damege;

	Object object;
	
}SKILL;

typedef struct tagPlayerSkill
{
	SKILL Skill;
}PLAYERSKILL;

// �Լ� ���� ����
char* SetName();

void SceneManager(Object* Player, Object* Enemy, EQUIPMENT* Equipment, INVENTORY* Inventory, Object* Quest, SKILL* Skill, PLAYERSKILL* PlayerSkill);
void LogoScene();
void MenuScene();
void StageScene(Object* Player, Object* Enemy, EQUIPMENT* Equipment, INVENTORY* Inventory, Object* Quest, SKILL* Skill, PLAYERSKILL* PlayerSkill);

void GraveYard(Object* Player, Object* Enemy, EQUIPMENT* Equipment, INVENTORY* Inventory);
void GraveYardBackGround();
void AdventurerVillage(Object* Player, Object* Enemy, EQUIPMENT* Equipment, INVENTORY* Inventory, Object* Quest, SKILL* Skill,PLAYERSKILL* PlayerSkill);
void Castle(Object* Player, Object* Enemy, EQUIPMENT* Equipment);
void NecromancerTower(Object* Player, Object* Enemy, EQUIPMENT* Equipment);

void DungeonEnterence(Object* Player, Object* Enemy, EQUIPMENT* Equipment, INVENTORY* Inventory, Object* Quest);
void Dungeon(Object* Player, Object* Enemy, EQUIPMENT* Equipment, int EnemyIndex, int EventCount, Object* Quest, INVENTORY* Inventory);
void Shop(Object* Player, INVENTORY* Inventory);
void ShopBackGround();
void Guild(Object* Player, Object* Quest, Object* Enemy, EQUIPMENT* Equipment);
void InitializeQuest(Object* Quest, int QuestIndex, int Stage);
void QuestState(Object* Quest, Object* Enemy, int _Choice);
void LevelUp(Object* Player, EQUIPMENT* Equipment);
void Forge(Object* Player, EQUIPMENT* Equipment);
void Training(Object* Player, EQUIPMENT* Equipment, INVENTORY* Inventory, SKILL* Skill, PLAYERSKILL* PlayerSkill);

void InitializeObjectPlayer(Object* Player);
void PlayerScene(Object* Player, INVENTORY* Inventory);

void InitializeObjectEnemy(Object* Enemy, int EnemyIndex);
int EnemyScene(Object* Enemy, int EnemyIndex);

void InitializeEquipment(EQUIPMENT* Equipment, int EquipmentIndex);
void InitializeObjectInventory(INVENTORY* Inventory, int ItemIndex);
void InitializeSkill(SKILL* Skill, int SkillNum);

short Battle(Object* Player, Object* Enemy, int EnemyIndex, Object* Quest, INVENTORY* Inventory);
void Status(Object* Player, Object* Enemy, int EnemyIndex);
void PlayerStatus(Object* Player, int State);
void EnemyStatus(Object* Enemy, int EnemyIndex);
void PlayerAttack(Object* Player, Object* Enemy, int EnemyIndex);
void EnemyAttack(Object* Player, Object* Enemy, int EnamyIndex);
void Equip(Object* Player, EQUIPMENT* Equipment, int EquipmentNum);
void Reinforce(Object* Player, EQUIPMENT* Equipment, int EquipmentID);
short GameOver();

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

	Object* Quest = (Object*)malloc(sizeof(Object)*4);
	

	EQUIPMENT* Equipment;
	Equipment = (EQUIPMENT*)malloc(sizeof(EQUIPMENT) * 32);

	for (int i = 0; i < 20; i++)
	{
		InitializeEquipment(Equipment,i);
	}

	INVENTORY* Inventory;
	Inventory = (INVENTORY*)malloc(sizeof(INVENTORY)*32);
	for (int i = 0; i < Max; i++)
	{
		InitializeObjectInventory(Inventory, i);							//�ʱ�ȭ
	}

	SKILL* Skill;
	Skill = (SKILL*)malloc(sizeof(SKILL)*16);
	for (int i = 0; i < Max; i++)
	{
		InitializeSkill(Skill, i);							
	}

	PLAYERSKILL* PlayerSkill = (PLAYERSKILL*)malloc(sizeof(PLAYERSKILL) * 4);

	while (true)
	{
			//�ܼ�â�� �ִ� ��系���� ����
		system("cls");

		//** ���� ����
		//  �Լ� SceneManger�� �־� �۵� �Ѵ�
		SceneManager(Player, Enemy, Equipment, Inventory, Quest,Skill, PlayerSkill);
	}

	return 0;
}

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

// Scene����
void SceneManager(Object* Player, Object* Enemy, EQUIPMENT* Equipment, INVENTORY* Inventory, Object* Quest, SKILL * Skill, PLAYERSKILL* PlayerSkill)					
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
		StageScene(Player, Enemy, Equipment, Inventory, Quest, Skill, PlayerSkill);						// StageScene ����
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

void StageScene(Object* Player, Object* Enemy, EQUIPMENT* Equipment, INVENTORY* Inventory, Object* Quest, SKILL* Skill, PLAYERSKILL* PlayerSkill)
{
	//�׽�Ʈ�� ��ŵ����
	iStage = 1;
	// ** ���ȭ �Լ������ �뵵���� ����� �� �ְ�

	for (int i = 0; i < sizeof(int); i++)
	{
		InitializeQuest(Quest, i, iStage);
	}

	switch (iStage)
	{
	case 0:
		//** ����
		GraveYard(Player, Enemy, Equipment, Inventory);
		iStage++;
		break;

	case 1:
		// ** ���谡 ����
		AdventurerVillage(Player, Enemy, Equipment, Inventory, Quest, Skill, PlayerSkill);

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
	// ** �̵�
	//  * * * �Է�(Input)
	//  * * * �÷��̾� ��ǥ������ ����
	//  * * * ���� ������ ũ�� ������ ����
	//  * * * ���� ������Ʈ���� �̵��ӵ� ������ ����
	}


// �÷��̾�
void InitializeObjectPlayer(Object* Player)
{
	//PLAYER�� ��ü ������ �ʱ�ȭ�Ѵ�

	Player->Info.HP = 100;
	Player->Info.MaxHP = 100;
	Player->Info.MP = 10;
	Player->Info.MaxMP = 10;
	Player->Info.Att = 10;
	Player->Info.Def = 5;
	Player->Info.Speed = 10;
	Player->Info.Level = 1;
	Player->Info.EXP = 0;
	Player->Info.Gold = 1000;
}


void PlayerScene(Object* Player, INVENTORY* Inventory)
{
	printf_s("�����۸�\t����\t����\n");
	for (int i = 0; i < 1; i++)
	{
		if(Inventory[i].Equipment.Stock > 0)
			printf_s("%d. %s\t\t%d G\t\t%d\n",i+1, Inventory[i].item.Object.Name, Inventory[i].Equipment.Price, Inventory[i].Equipment.Stock);
	}
}


// ��
void InitializeObjectEnemy(Object* Enemy, int EnemyIndex)
{
	switch (EnemyIndex)
	{
		//����
		case 0:
			Enemy[EnemyIndex].Name = (char*)"��";
			Enemy[EnemyIndex].Info.HP = 10;
			Enemy[EnemyIndex].Info.MP = 5;
			Enemy[EnemyIndex].Info.Att = 7;
			Enemy[EnemyIndex].Info.Def = 5;
			Enemy[EnemyIndex].Info.Speed = 5;
			Enemy[EnemyIndex].Info.EXP = 1;
			Enemy[EnemyIndex].Info.Gold = 3;
			break;

		case 1:
			Enemy[EnemyIndex].Name = (char*)"���Ը��谡";
			Enemy[EnemyIndex].Info.HP = 25;
			Enemy[EnemyIndex].Info.MP = 5;
			Enemy[EnemyIndex].Info.Att = 10;
			Enemy[EnemyIndex].Info.Def = 10;
			Enemy[EnemyIndex].Info.Speed = 5;
			Enemy[EnemyIndex].Info.EXP = 5;
			Enemy[EnemyIndex].Info.Gold = 10;
			break;

		//���谡 ����
			// �ҳʽ� ���
		case 2:
			Enemy[EnemyIndex].Name = (char*)"������";
			Enemy[EnemyIndex].Info.HP = 35;
			Enemy[EnemyIndex].Info.MP = 5;
			Enemy[EnemyIndex].Info.Att = 12;
			Enemy[EnemyIndex].Info.Def = 10;
			Enemy[EnemyIndex].Info.Speed = 5;
			Enemy[EnemyIndex].Info.EXP = 4;
			break;
		case 3:
			Enemy[EnemyIndex].Name = (char*)"���";
			Enemy[EnemyIndex].Info.HP = 35;
			Enemy[EnemyIndex].Info.MP = 5;
			Enemy[EnemyIndex].Info.Att = 14;
			Enemy[EnemyIndex].Info.Def = 8;
			Enemy[EnemyIndex].Info.Speed = 11;
			Enemy[EnemyIndex].Info.EXP = 4;
			break;
		case 4:
			Enemy[EnemyIndex].Name = (char*)"���谡";
			Enemy[EnemyIndex].Info.HP = 50;
			Enemy[EnemyIndex].Info.MP = 5;
			Enemy[EnemyIndex].Info.Att = 17;
			Enemy[EnemyIndex].Info.Def = 15;
			Enemy[EnemyIndex].Info.Speed = 9;
			Enemy[EnemyIndex].Info.EXP = 10;
			break;
		case 5:
			Enemy[EnemyIndex].Name = (char*)"����";
			Enemy[EnemyIndex].Info.HP = 50;
			Enemy[EnemyIndex].Info.MP = 5;
			Enemy[EnemyIndex].Info.Att = 17;
			Enemy[EnemyIndex].Info.Def = 12;
			Enemy[EnemyIndex].Info.Speed = 9;
			Enemy[EnemyIndex].Info.EXP = 10;
			break;
		case 6:
			Enemy[EnemyIndex].Name = (char*)"�������";
			Enemy[EnemyIndex].Info.HP = 45;
			Enemy[EnemyIndex].Info.MP = 5;
			Enemy[EnemyIndex].Info.Att = 17;
			Enemy[EnemyIndex].Info.Def = 15;
			Enemy[EnemyIndex].Info.Speed = 9;
			Enemy[EnemyIndex].Info.EXP = 18;
			break;
		case 7:
			Enemy[EnemyIndex].Name = (char*)"�����ô��";
			Enemy[EnemyIndex].Info.HP = 30;
			Enemy[EnemyIndex].Info.MP = 5;
			Enemy[EnemyIndex].Info.Att = 20;
			Enemy[EnemyIndex].Info.Def = 10;
			Enemy[EnemyIndex].Info.Speed = 12;
			Enemy[EnemyIndex].Info.EXP = 18;
			break;
		case 8:
			Enemy[EnemyIndex].Name = (char*)"������̴�";
			Enemy[EnemyIndex].Info.HP = 70;
			Enemy[EnemyIndex].Info.MP = 5;
			Enemy[EnemyIndex].Info.Att = 25;
			Enemy[EnemyIndex].Info.Def = 20;
			Enemy[EnemyIndex].Info.Speed = 15;
			Enemy[EnemyIndex].Info.EXP = 25;
			break;
		case 9:
			Enemy[EnemyIndex].Name = (char*)"��ũ";
			Enemy[EnemyIndex].Info.HP = 60;
			Enemy[EnemyIndex].Info.MP = 5;
			Enemy[EnemyIndex].Info.Att = 20;
			Enemy[EnemyIndex].Info.Def = 15;
			Enemy[EnemyIndex].Info.Speed = 10;
			break;
		case 10:
			Enemy[EnemyIndex].Name = (char*)"��ũ����";
			Enemy[EnemyIndex].Info.HP = 75;
			Enemy[EnemyIndex].Info.MP = 5;
			Enemy[EnemyIndex].Info.Att = 27;
			Enemy[EnemyIndex].Info.Def = 20;
			Enemy[EnemyIndex].Info.Speed = 12;
			break;
		case 11:
			Enemy[EnemyIndex].Name = (char*)"��ũ�ּ���";
			Enemy[EnemyIndex].Info.HP = 50;
			Enemy[EnemyIndex].Info.MP = 100;
			Enemy[EnemyIndex].Info.Att = 40;
			Enemy[EnemyIndex].Info.Def = 10;
			Enemy[EnemyIndex].Info.Speed = 5;
			break;
		case 12:
			Enemy[EnemyIndex].Name = (char*)"�����";
			Enemy[EnemyIndex].Info.HP = 1;//20; �ӽ÷� ü�� ���� ����Ʈ �ϷḦ ���� ����
			Enemy[EnemyIndex].Info.MP = 5;
			Enemy[EnemyIndex].Info.Att = 37;
			Enemy[EnemyIndex].Info.Def = 17;
			Enemy[EnemyIndex].Info.Speed = 5;
			break;

		//�ռ�
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

		//��ɼ����� ž
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
	// *****	4 = �Ӹ� 5 = ���� 6 = ���� 7 = �� 8 = �尩 9 = ¡ǥ
		switch (EquipmentIndex)
		{
		case 0:
			Equipment[EquipmentIndex].object.Name = (char*)"������ ��";
			Equipment[EquipmentIndex].Info.MaxHP = 0;
			Equipment[EquipmentIndex].Info.MaxMP = 0;
			Equipment[EquipmentIndex].Info.Att = 5;
			Equipment[EquipmentIndex].Info.Def = 0;
			Equipment[EquipmentIndex].Info.Speed = 0;
			Equipment[EquipmentIndex].Info.Gold = 200;
			Equipment[EquipmentIndex].object.State = 0;
			break;
		case 1:
			Equipment[EquipmentIndex].object.Name = (char*)"������ ����";
			Equipment[EquipmentIndex].Info.MaxHP = 0;
			Equipment[EquipmentIndex].Info.MaxMP = 0;
			Equipment[EquipmentIndex].Info.Att = 7;
			Equipment[EquipmentIndex].Info.Def = 0;
			Equipment[EquipmentIndex].Info.Speed = -2;
			Equipment[EquipmentIndex].Info.Gold = 200;
			Equipment[EquipmentIndex].object.State = 0;
			break;
		case 2:
			Equipment[EquipmentIndex].object.Name = (char*)"������ â";
			Equipment[EquipmentIndex].Info.MaxHP = 0;
			Equipment[EquipmentIndex].Info.MaxMP = 0;
			Equipment[EquipmentIndex].Info.Att = 4;
			Equipment[EquipmentIndex].Info.Def = 0;
			Equipment[EquipmentIndex].Info.Speed = 1;
			Equipment[EquipmentIndex].Info.Gold = 200;
			Equipment[EquipmentIndex].object.State = 0;
			break;
		case 3:
			Equipment[EquipmentIndex].object.Name = (char*)"������ Ȱ";
			Equipment[EquipmentIndex].Info.MaxHP = 0;
			Equipment[EquipmentIndex].Info.MaxMP = 0;
			Equipment[EquipmentIndex].Info.Att = 5;
			Equipment[EquipmentIndex].Info.Def = 0;
			Equipment[EquipmentIndex].Info.Speed = 0;
			Equipment[EquipmentIndex].Info.Gold = 200;
			Equipment[EquipmentIndex].object.State = 0;
			break;
		case 4:
			Equipment[EquipmentIndex].object.Name = (char*)"�㸧�� ����";
			Equipment[EquipmentIndex].Info.MaxHP = 0;
			Equipment[EquipmentIndex].Info.MaxMP = 0;
			Equipment[EquipmentIndex].Info.Att = 0;
			Equipment[EquipmentIndex].Info.Def = 1;
			Equipment[EquipmentIndex].Info.Speed = 0;
			Equipment[EquipmentIndex].Info.Gold = 90;
			Equipment[EquipmentIndex].object.State = 0;
			break;
		case 5:
			Equipment[EquipmentIndex].object.Name = (char*)"�㸧�� ����";
			Equipment[EquipmentIndex].Info.MaxHP = 0;
			Equipment[EquipmentIndex].Info.MaxMP = 0;
			Equipment[EquipmentIndex].Info.Att = 0;
			Equipment[EquipmentIndex].Info.Def = 1;
			Equipment[EquipmentIndex].Info.Speed = 0;
			Equipment[EquipmentIndex].Info.Gold = 90;
			Equipment[EquipmentIndex].object.State = 0;
			break;
		case 6:
			Equipment[EquipmentIndex].object.Name = (char*)"�㸧�� ����";
			Equipment[EquipmentIndex].Info.MaxHP = 0;
			Equipment[EquipmentIndex].Info.MaxMP = 0;
			Equipment[EquipmentIndex].Info.Att = 0;
			Equipment[EquipmentIndex].Info.Def = 1;
			Equipment[EquipmentIndex].Info.Speed = 0;
			Equipment[EquipmentIndex].Info.Gold = 90;
			Equipment[EquipmentIndex].object.State = 0;
			break;
		case 7:
			Equipment[EquipmentIndex].object.Name = (char*)"�㸧�� ��ȭ";
			Equipment[EquipmentIndex].Info.MaxHP = 0;
			Equipment[EquipmentIndex].Info.MaxMP = 0;
			Equipment[EquipmentIndex].Info.Att = 0;
			Equipment[EquipmentIndex].Info.Def = 1;
			Equipment[EquipmentIndex].Info.Speed = 0;
			Equipment[EquipmentIndex].Info.Gold = 90;
			Equipment[EquipmentIndex].object.State = 0;
			break;
		case 8:
			Equipment[EquipmentIndex].object.Name = (char*)"�㸧�� �尩";
			Equipment[EquipmentIndex].Info.MaxHP = 0;
			Equipment[EquipmentIndex].Info.MaxMP = 0;
			Equipment[EquipmentIndex].Info.Att = 0;
			Equipment[EquipmentIndex].Info.Def = 1;
			Equipment[EquipmentIndex].Info.Speed = 0;
			Equipment[EquipmentIndex].Info.Gold = 90;
			Equipment[EquipmentIndex].object.State = 0;
			break;
		case 9 :
			Equipment[EquipmentIndex].object.Name = (char*)"�߽� ���谡�� ¡ǥ";
			Equipment[EquipmentIndex].Info.MaxHP = 50;
			Equipment[EquipmentIndex].Info.MaxMP = 25;
			Equipment[EquipmentIndex].Info.Att= 2;
			Equipment[EquipmentIndex].Info.Def = 2;
			Equipment[EquipmentIndex].Info.Speed = 0; 
			Equipment[EquipmentIndex].object.State = 0;
			break;
		case 10:
			Equipment[EquipmentIndex].object.Name = (char*)"ö�� ��";
			Equipment[EquipmentIndex].Info.MaxHP = 0;
			Equipment[EquipmentIndex].Info.MaxMP = 0;
			Equipment[EquipmentIndex].Info.Att = 15;
			Equipment[EquipmentIndex].Info.Def = 2;
			Equipment[EquipmentIndex].Info.Speed = 0;
			Equipment[EquipmentIndex].Info.Gold = 200;
			Equipment[EquipmentIndex].object.State = 0;
			break;
		case 11:
			Equipment[EquipmentIndex].object.Name = (char*)"�赵��";
			Equipment[EquipmentIndex].Info.MaxHP = 0;
			Equipment[EquipmentIndex].Info.MaxMP = 0;
			Equipment[EquipmentIndex].Info.Att = 17;
			Equipment[EquipmentIndex].Info.Def = 0;
			Equipment[EquipmentIndex].Info.Speed = -3;
			Equipment[EquipmentIndex].Info.Gold = 200;
			Equipment[EquipmentIndex].object.State = 0;
			break;
		case 12:
			Equipment[EquipmentIndex].object.Name = (char*)"��â";
			Equipment[EquipmentIndex].Info.MaxHP = 0;
			Equipment[EquipmentIndex].Info.MaxMP = 0;
			Equipment[EquipmentIndex].Info.Att = 14;
			Equipment[EquipmentIndex].Info.Def = 0;
			Equipment[EquipmentIndex].Info.Speed = 2;
			Equipment[EquipmentIndex].Info.Gold = 200;
			Equipment[EquipmentIndex].object.State = 0;
			break;
		case 13:
			Equipment[EquipmentIndex].object.Name = (char*)"�ܱ�";
			Equipment[EquipmentIndex].Info.MaxHP = 0;
			Equipment[EquipmentIndex].Info.MaxMP = 0;
			Equipment[EquipmentIndex].Info.Att = 16;
			Equipment[EquipmentIndex].Info.Def = 0;
			Equipment[EquipmentIndex].Info.Speed = 0;
			Equipment[EquipmentIndex].Info.Gold = 200;
			Equipment[EquipmentIndex].object.State = 0;
			break;
		case 14:
			Equipment[EquipmentIndex].object.Name = (char*)"���� ����";
			Equipment[EquipmentIndex].Info.MaxHP = 0;
			Equipment[EquipmentIndex].Info.MaxMP = 0;
			Equipment[EquipmentIndex].Info.Att = 0;
			Equipment[EquipmentIndex].Info.Def = 4;
			Equipment[EquipmentIndex].Info.Speed = 0;
			Equipment[EquipmentIndex].Info.Gold = 90;
			Equipment[EquipmentIndex].object.State = 0;
			break;
		case 15:
			Equipment[EquipmentIndex].object.Name = (char*)"���� ����";
			Equipment[EquipmentIndex].Info.MaxHP = 10;
			Equipment[EquipmentIndex].Info.MaxMP = 0;
			Equipment[EquipmentIndex].Info.Att = 0;
			Equipment[EquipmentIndex].Info.Def = 5;
			Equipment[EquipmentIndex].Info.Speed = 0;
			Equipment[EquipmentIndex].Info.Gold = 90;
			Equipment[EquipmentIndex].object.State = 0;
			break;
		case 16:
			Equipment[EquipmentIndex].object.Name = (char*)"���� ����";
			Equipment[EquipmentIndex].Info.MaxHP = 10;
			Equipment[EquipmentIndex].Info.MaxMP = 0;
			Equipment[EquipmentIndex].Info.Att = 0;
			Equipment[EquipmentIndex].Info.Def = 5;
			Equipment[EquipmentIndex].Info.Speed = 0;
			Equipment[EquipmentIndex].Info.Gold = 90;
			Equipment[EquipmentIndex].object.State = 0;
			break;
		case 17:
			Equipment[EquipmentIndex].object.Name = (char*)"���� ��ȭ";
			Equipment[EquipmentIndex].Info.MaxHP = 0;
			Equipment[EquipmentIndex].Info.MaxMP = 0;
			Equipment[EquipmentIndex].Info.Att = 0;
			Equipment[EquipmentIndex].Info.Def = 2;
			Equipment[EquipmentIndex].Info.Speed = 1;
			Equipment[EquipmentIndex].Info.Gold = 90;
			Equipment[EquipmentIndex].object.State = 0;
			break;
		case 18:
			Equipment[EquipmentIndex].object.Name = (char*)"���� �尩";
			Equipment[EquipmentIndex].Info.MaxHP = 0;
			Equipment[EquipmentIndex].Info.MaxMP = 0;
			Equipment[EquipmentIndex].Info.Att = 1;
			Equipment[EquipmentIndex].Info.Def = 2;
			Equipment[EquipmentIndex].Info.Speed = 0;
			Equipment[EquipmentIndex].Info.Gold = 90;
			Equipment[EquipmentIndex].object.State = 0;
			break;
		case 19:
			Equipment[EquipmentIndex].object.Name = (char*)"���谡�� ¡ǥ";
			Equipment[EquipmentIndex].Info.MaxHP = 50;
			Equipment[EquipmentIndex].Info.MaxMP = 25;
			Equipment[EquipmentIndex].Info.Att = 2;
			Equipment[EquipmentIndex].Info.Def = 2;
			Equipment[EquipmentIndex].Info.Speed = 0;
			Equipment[EquipmentIndex].object.State = 0;
			break;
		case 20:
			Equipment[EquipmentIndex].object.Name = (char*)"��ö ��";
			Equipment[EquipmentIndex].Info.MaxHP = 0;
			Equipment[EquipmentIndex].Info.MaxMP = 0;
			Equipment[EquipmentIndex].Info.Att = 15;
			Equipment[EquipmentIndex].Info.Def = 2;
			Equipment[EquipmentIndex].Info.Speed = 0;
			Equipment[EquipmentIndex].Info.Gold = 200;
			Equipment[EquipmentIndex].object.State = 0;
			break;
		case 21:
			Equipment[EquipmentIndex].object.Name = (char*)"��ö ����";
			Equipment[EquipmentIndex].Info.MaxHP = 0;
			Equipment[EquipmentIndex].Info.MaxMP = 0;
			Equipment[EquipmentIndex].Info.Att = 17;
			Equipment[EquipmentIndex].Info.Def = 0;
			Equipment[EquipmentIndex].Info.Speed = -3;
			Equipment[EquipmentIndex].Info.Gold = 200;
			Equipment[EquipmentIndex].object.State = 0;
			break;
		case 22:
			Equipment[EquipmentIndex].object.Name = (char*)"��ö â";
			Equipment[EquipmentIndex].Info.MaxHP = 0;
			Equipment[EquipmentIndex].Info.MaxMP = 0;
			Equipment[EquipmentIndex].Info.Att = 14;
			Equipment[EquipmentIndex].Info.Def = 0;
			Equipment[EquipmentIndex].Info.Speed = 2;
			Equipment[EquipmentIndex].Info.Gold = 200;
			Equipment[EquipmentIndex].object.State = 0;
			break;
		case 23:
			Equipment[EquipmentIndex].object.Name = (char*)"�ռ� �ܱ�";
			Equipment[EquipmentIndex].Info.MaxHP = 0;
			Equipment[EquipmentIndex].Info.MaxMP = 0;
			Equipment[EquipmentIndex].Info.Att = 16;
			Equipment[EquipmentIndex].Info.Def = 0;
			Equipment[EquipmentIndex].Info.Speed = 0;
			Equipment[EquipmentIndex].Info.Gold = 200;
			Equipment[EquipmentIndex].object.State = 0;
			break;
		case 24:
			Equipment[EquipmentIndex].object.Name = (char*)"�Ǳ� ����";
			Equipment[EquipmentIndex].Info.MaxHP = 0;
			Equipment[EquipmentIndex].Info.MaxMP = 0;
			Equipment[EquipmentIndex].Info.Att = 0;
			Equipment[EquipmentIndex].Info.Def = 4;
			Equipment[EquipmentIndex].Info.Speed = 0;
			Equipment[EquipmentIndex].Info.Gold = 90;
			Equipment[EquipmentIndex].object.State = 0;
			break;
		case 25:
			Equipment[EquipmentIndex].object.Name = (char*)"�Ǳ� ����";
			Equipment[EquipmentIndex].Info.MaxHP = 10;
			Equipment[EquipmentIndex].Info.MaxMP = 0;
			Equipment[EquipmentIndex].Info.Att = 0;
			Equipment[EquipmentIndex].Info.Def = 5;
			Equipment[EquipmentIndex].Info.Speed = 0;
			Equipment[EquipmentIndex].Info.Gold = 90;
			Equipment[EquipmentIndex].object.State = 0;
			break;
		case 26:
			Equipment[EquipmentIndex].object.Name = (char*)"�Ǳ� ����";
			Equipment[EquipmentIndex].Info.MaxHP = 10;
			Equipment[EquipmentIndex].Info.MaxMP = 0;
			Equipment[EquipmentIndex].Info.Att = 0;
			Equipment[EquipmentIndex].Info.Def = 5;
			Equipment[EquipmentIndex].Info.Speed = 0;
			Equipment[EquipmentIndex].Info.Gold = 90;
			Equipment[EquipmentIndex].object.State = 0;
			break;
		case 27:
			Equipment[EquipmentIndex].object.Name = (char*)"�Ǳ� ��ȭ";
			Equipment[EquipmentIndex].Info.MaxHP = 0;
			Equipment[EquipmentIndex].Info.MaxMP = 0;
			Equipment[EquipmentIndex].Info.Att = 0;
			Equipment[EquipmentIndex].Info.Def = 2;
			Equipment[EquipmentIndex].Info.Speed = 1;
			Equipment[EquipmentIndex].Info.Gold = 90;
			Equipment[EquipmentIndex].object.State = 0;
			break;
		case 28:
			Equipment[EquipmentIndex].object.Name = (char*)"�Ǳ� �尩";
			Equipment[EquipmentIndex].Info.MaxHP = 0;
			Equipment[EquipmentIndex].Info.MaxMP = 0;
			Equipment[EquipmentIndex].Info.Att = 1;
			Equipment[EquipmentIndex].Info.Def = 2;
			Equipment[EquipmentIndex].Info.Speed = 0;
			Equipment[EquipmentIndex].Info.Gold = 90;
			Equipment[EquipmentIndex].object.State = 0;
			break;
		case 29:
			Equipment[EquipmentIndex].object.Name = (char*)"���� ���谡�� ¡ǥ";
			Equipment[EquipmentIndex].Info.MaxHP = 50;
			Equipment[EquipmentIndex].Info.MaxMP = 25;
			Equipment[EquipmentIndex].Info.Att = 2;
			Equipment[EquipmentIndex].Info.Def = 2;
			Equipment[EquipmentIndex].Info.Speed = 0;
			Equipment[EquipmentIndex].object.State = 0;
			break;
		}
}

void InitializeObjectInventory(INVENTORY* Inventory, int ItemIndex)
{
	switch (ItemIndex)
	{
		case 0:
			Inventory[ItemIndex].item.Object.Name = (char*)"�İ���";
			Inventory[ItemIndex].item.Effect.Info.HP = 20;
			Inventory[ItemIndex].item.Effect.Info.MP = 0;
			Inventory[ItemIndex].Equipment.Price = 5;
			Inventory[ItemIndex].Equipment.Stock = 0;
			break;

		case 1:
			Inventory[ItemIndex].item.Object.Name = (char*)"������ �̽�";
			Inventory[ItemIndex].item.Effect.Info.HP = 0;
			Inventory[ItemIndex].item.Effect.Info.MP = 10;
			Inventory[ItemIndex].Equipment.Price = 3;
			Inventory[ItemIndex].Equipment.Stock = 0;
			break;
	}
}

void InitializeSkill(SKILL* Skill, int SkillNum)
{
	// 0 = ���ݷ±�� 1 = ��� �ִ�ü�� ��� 2 = �ӵ���� 3 = ��� ����ü�� ���  
	switch (SkillNum)
	{
		case 0:
			Skill[SkillNum].object.Name = (char*)"���� ����";
			Skill[SkillNum].Damege = 1.2f;
			Skill[SkillNum].Cost = 10;
			Skill[SkillNum].Type = SkillNum%4;
		break;

		case 1:
			Skill[SkillNum].object.Name = (char*)"�ɰ������� ��!";
			Skill[SkillNum].Damege = 1.2f;
			Skill[SkillNum].Cost = 10;
			Skill[SkillNum].Type = SkillNum % 4;
		break;

		case 2:
			Skill[SkillNum].object.Name = (char*)"���� ���";
			Skill[SkillNum].Damege = 1.2f;
			Skill[SkillNum].Cost = 10;
			Skill[SkillNum].Type = SkillNum % 4;
		break;

		case 3:
			Skill[SkillNum].object.Name = (char*)"���� ȭ��";
			Skill[SkillNum].Damege = 1.2f;
			Skill[SkillNum].Cost = 10;
			Skill[SkillNum].Type = SkillNum % 4;
		break;

		case 4:
			Skill[SkillNum].object.Name = (char*)"ȸ�� ����";
			Skill[SkillNum].Damege = 1.4f;
			Skill[SkillNum].Cost = 20;
			Skill[SkillNum].Type = SkillNum % 4;
		break;

		case 5:
			Skill[SkillNum].object.Name = (char*)"�м��Ѵ� ��!";
			Skill[SkillNum].Damege = 1.4f;
			Skill[SkillNum].Cost = 20;
			Skill[SkillNum].Type = SkillNum % 4;
		break;

		case 6:
			Skill[SkillNum].object.Name = (char*)"������";
			Skill[SkillNum].Damege = 1.4f;
			Skill[SkillNum].Cost = 20;
			Skill[SkillNum].Type = SkillNum % 4;
		break;

		case 7:
			Skill[SkillNum].object.Name = (char*)"ȯ�� ȭ��";
			Skill[SkillNum].Damege = 1.4f;
			Skill[SkillNum].Cost = 20;
			Skill[SkillNum].Type = SkillNum % 4;
		break;

		case 8:
			Skill[SkillNum].object.Name = (char*)"�޺� ����";
			Skill[SkillNum].Damege = 1.6f;
			Skill[SkillNum].Cost = 30;
			Skill[SkillNum].Type = SkillNum % 4;
		break;

		case 9:
			Skill[SkillNum].object.Name = (char*)"�� �þ�Ծ��ָ�!";
			Skill[SkillNum].Damege = 1.6f;
			Skill[SkillNum].Cost = 30;
			Skill[SkillNum].Type = SkillNum % 4;
		break;

		case 10:
			Skill[SkillNum].object.Name = (char*)"�ڻ� ����";
			Skill[SkillNum].Damege = 1.6f;
			Skill[SkillNum].Cost = 30;
			Skill[SkillNum].Type = SkillNum % 4;
		break;

		case 11:
			Skill[SkillNum].object.Name = (char*)"����� ���";
			Skill[SkillNum].Damege = 1.6f;
			Skill[SkillNum].Cost = 30;
			Skill[SkillNum].Type = SkillNum % 4;
		break;

		case 12:
			Skill[SkillNum].object.Name = (char*)"�𸮹�Ƽ�� �ҵ�";
			Skill[SkillNum].Damege = 2.0f;
			Skill[SkillNum].Cost = 45;
			Skill[SkillNum].Type = SkillNum % 4;
		break;

		case 13:
			Skill[SkillNum].object.Name = (char*)"���ڴ� ������ ���Ѵ�";
			Skill[SkillNum].Damege = 2.0f;
			Skill[SkillNum].Cost = 45;
			Skill[SkillNum].Type = SkillNum % 4;
		break;

		case 14:
			Skill[SkillNum].object.Name = (char*)"�ؽżӰ�";
			Skill[SkillNum].Damege = 2.0f;
			Skill[SkillNum].Cost = 45;
			Skill[SkillNum].Type = SkillNum % 4;
		break;

		case 15:
			Skill[SkillNum].object.Name = (char*)"�������� Ȱ";
			Skill[SkillNum].Damege = 2.0f;
			Skill[SkillNum].Cost = 45;
			Skill[SkillNum].Type = SkillNum % 4;
		break;

		case 16:
			Skill[SkillNum].object.Name = (char*)"�巹�� ��ġ";
			Skill[SkillNum].Damege = 0.8f;
			Skill[SkillNum].Cost = 5;
			Skill[SkillNum].Type = 5;
		break;
	}

}

void GraveYard(Object* Player, Object* Enemy, EQUIPMENT* Equipment, INVENTORY* Inventory)
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
			Equip(Player, Equipment, iStartWeapon);

			GraveYardBackGround();

			printf_s("%s\n�켱 ������ ���� ������ ��ƾ߰ھ�\n",Player->Name);
			Sleep(1000);

			GraveYardBackGround();
			//���� 0 ����
			Dungeon(Player, Enemy, Equipment, 0, 5, 0,Inventory);

			break;

		default:
			printf_s("%s\n�켱 ������ ���� ������ ��ƾ߰ھ�\n", Player->Name);

			GraveYardBackGround();
			//���� 0 ����
			Dungeon(Player, Enemy, Equipment, 0, 5, 0, Inventory);

			break;
		}
	
	// ��� �̹���
	system("cls");
	printf_s("���\n\n���߽ʽÿ�! �� ���� ���̽ŵ�...");
	Sleep(1000);
	// ��� �̹���
	system("cls");
	printf_s("%s\n\n ...", Player->Name);
	Sleep(1000);
	system("cls");
	// ��� �̹���
	printf_s("���\n\nȤ�� ���谡�� �Ƿ��� ���Ű̴ϱ�?");
	Sleep(1000);
	system("cls");
	// ��� �̹���
	printf_s("%s\n\n �׷���", Player->Name);
	Sleep(1000);
	system("cls");
	// ��� �̹���
	printf_s("���\n\nȯ���մϴ�! �� ���� ���谡���� ���� �شϿ��Դϴ�.\n");
	Sleep(500);
	printf_s("���谡�� �ǰ������ ��忡 ���� ��� �Ͻø� �˴ϴ�.");
	Sleep(1000);
	system("cls");

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

void AdventurerVillage(Object* Player, Object* Enemy, EQUIPMENT* Equipment, INVENTORY* Inventory, Object* Quest, SKILL* Skill, PLAYERSKILL* PlayerSkill)
{
	int iSelect = 0;

	int Village = 1;

	Player->Name = SetName();

	while(iStage == 1)
	{
		printf_s("���� ����?\n1.���谡 ��� 2.�� 3.���尣 4.�Ʒ��� 5.�� ���� 6.���� ������ ����\n�Է�: ");

		scanf("%d", &iSelect);

		switch (iSelect)
		{
			//����Ʈ NPC
			case 1:
				Guild(Player, Quest, Enemy, Equipment);
				break;
			//����
			case 2 :
				Shop(Player, Inventory);
				break;
			// ��ȭ	
			case 3 :
				Forge(Player, Equipment);
				break;
			case 4:
				Training(Player, Equipment, Inventory, Skill, PlayerSkill);
			//���� ��� & ���� ������ & ���� ���� ��ȸ
			case 5:
				PlayerStatus(Player, Village);
				for (int i = 0; i < 3; i++)
				{
					for (int j = 0; j < 10; j++)
					{
						if (Equipment[j + (i * 10)].object.State == 1)
							printf_s("%s", Equipment[j + (i * 10)].object.Name);
					}
				}
				break;
			//����
			case 6:
				DungeonEnterence(Player, Enemy, Equipment, Inventory, Quest);
				break;
		}
	}
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

void DungeonEnterence(Object* Player, Object* Enemy, EQUIPMENT* Equipment, INVENTORY* Inventory, Object* Quest)
{
	int StageNumber = 0;

	printf_s("���� ����?\n");
	switch (iStage)
	{
		case 1 :
			printf_s("1.�ҳʽ� ���\n2.������ �߿���\n3.������\n4.��ũ������\n5.����ž߿���\n(6.���ư���)\n�Է� : ");

			//���谡 ���� 1~5
			scanf("%d", &StageNumber);
			if (StageNumber > 0 && StageNumber < 6)
			{
				Dungeon(Player, Enemy, Equipment, StageNumber, 5, Quest, Inventory);
			}
			break;

		case 2 :
			printf_s("1.\n2.\n3.\n4.\n5.\n(6.���ư���)\n�Է� : ");

			//�ռ� 6~10
			scanf("%d", &StageNumber);
			StageNumber += 5;
			if (StageNumber > 0 && StageNumber < 6)
			{
				Dungeon(Player, Enemy, Equipment, StageNumber, 5, Quest, Inventory);
			}
			break;

		case 3:
			printf_s("1.\n2.\n3.\n4.\n5.\n(6.���ư���)\n�Է� : ");

			//��ɼ����� ž 11~15
			scanf("%d", &StageNumber);
			StageNumber += 15;
			if (StageNumber > 0 && StageNumber < 6)
			{
				Dungeon(Player, Enemy, Equipment, StageNumber, 5, Quest, Inventory);
			}
			break;
	}
}

void Dungeon(Object* Player, Object* Enemy, EQUIPMENT* Equipment, int EnemyIndex, int EventCount, Object* Quest, INVENTORY* Inventory)
{
	short Walk = 1;
	int Loop = 0;

	int RandomEnemy = 0;

	srand(time(NULL));

	while (Walk)
	{
		switch (iStage)
		{
			case 0 :
			{
				//** ���� �������� ����
				if (Loop < EventCount)
				{
					system("cls");
					GraveYardBackGround();

					for (int i = 0; i < 3; i++)
					{
						printf(".");
						Sleep(333);
					}
										
					++Loop;

					//�� ����
					//** 3��° ����� �ù�
					if (Loop == 3)
					{
						// �ù��� ������ �� �ڽ��� �𵥵��� �� �˰Ե�?
						// ������ �ؾ��� �ʿ並 ����
						Status(Player, Enemy, 1);

						printf_s("%s\n���ƾ�! �� �̷� ���� ���̷�����?!\n", Enemy[1].Name);
						Sleep(1000);

						system("cls");
						Status(Player, Enemy, 1);
						Battle(Player, Enemy, 1, Quest, Inventory);

						GraveYardBackGround();
						printf_s("%s\n���� �� ������� ������ ���� �� �ǰڱ�\n", Player->Name);
						Sleep(1000);

						GraveYardBackGround();

						printf_s("%s\n�̾������� �������� ����\n", Player->Name);
						Sleep(500);
						printf_s("����� �������� ���̴� ���� �ĳ´�.");
						Sleep(1000);

						GraveYardBackGround();

						//�ʱ� ��
						for (int i = 4; i < 9; i++)
						{
							Equip(Player, Equipment, i);
						}
					}

					else
					{
						Status(Player, Enemy, EnemyIndex);
						Battle(Player, Enemy, EnemyIndex, Quest, Inventory);
					}
				}

				else if (Loop >= EventCount)
					Walk = 0;

				break;
			}
			case 1:
			{
				if (Loop < EventCount)
				{
					system("cls");

					for (int i = 0; i < 3; i++)
					{
						printf(".");
						Sleep(333);
					}

					++Loop;

					switch (EnemyIndex)
					{
						case 1:
							RandomEnemy = (rand() % 2) + 2;
							Status(Player, Enemy, RandomEnemy);
							Walk = Battle(Player, Enemy, RandomEnemy, Quest, Inventory);
							break;

						case 2:
							RandomEnemy = (rand() % 3) + 3;
							Status(Player, Enemy, RandomEnemy);
							Walk = Battle(Player, Enemy, RandomEnemy, Quest, Inventory);
							break;

						case 3:
							RandomEnemy = rand() % 3 + 6;
							Status(Player, Enemy, RandomEnemy);
							Walk = Battle(Player, Enemy, RandomEnemy, Quest, Inventory);
							break;

						case 4:
							RandomEnemy = rand() % 3 + 9;
							Status(Player, Enemy, RandomEnemy);
							Walk = Battle(Player, Enemy, RandomEnemy, Quest, Inventory);
							break;

						case 5:

							Loop = 5;

							RandomEnemy = rand() % 2 + 10;
							
							if(Loop==EventCount)
							{
								Status(Player, Enemy, 12);
								Walk = Battle(Player, Enemy, 12, Quest, Inventory);
							}

							else
							{
								Status(Player, Enemy, RandomEnemy);
								Walk = Battle(Player, Enemy, RandomEnemy, Quest, Inventory);
							}
							break;
					}
				}

				else if (Loop >= EventCount)
					Walk = 0;

				break;
			}
		}
	}
		
}

void Guild(Object* Player, Object* Quest, Object * Enemy, EQUIPMENT* Equipment)
{
	int iChoice = 0;
	int QChoice = 0;

	int Continue = 1;

	//������ �̹���
	printf_s("�������!\n");
	printf_s("�� ���� ���谡 ����Դϴ�.\n");
	printf_s("�Ƿڸ� �ްų� ���谡 ����� �ø� �� �־��\n");
	//������ �̹���
	
	while (Continue)
	{
		printf_s("1.�Ƿ�\t2.�±�\t3.��� ��ȸ\t4.���ư���\n�Է� :");
		scanf("%d", &iChoice);

		switch (iChoice)
		{
			
			case 1 :
			//����Ʈ���
				
				//�Ϸ�
				for (int i = 0; i < 2; i++)
				{
					if (Quest[i].State == 1 && Quest[i].Kills == Enemy[Quest[i].Num].State)
					{
						printf_s("���谡��! %s�Ƿڸ� �ϼ����ּ̱���\n���� �����Դϴ�!\n", Quest[i].Name);
						Sleep(500);
						printf_s("%d Gold�� �����!\n", Quest[i].Info.Gold);
						Sleep(500);
						printf_s("%d EXP�� �����!\n", Quest[i].Info.EXP);
						Sleep(500);

						Quest[i].State = 2;

						switch (i)
						{
							case 0 :
								Quest[i].Name = (char*)"������ 3���� óġ(�Ϸ�)";
								break;
							case 1 :
								Quest[i].Name = (char*)"����� óġ(�Ϸ�)";
								break;
						}
						Player->Info.Gold += Quest[i].Info.Gold;
						Player->Info.EXP += Quest[i].Info.EXP;
						
					}
				}

				// 0 = ���� ���� 1 = ������ 2 = �Ϸ�
				for (int i = 0; i < 2; i++)
				{
					printf_s("No %d. %s\n", i + 1, Quest[i].Name);
				}

				printf_s("������ �Ƿ��� ��ȣ�� �Է� ���ּ���(4 : ���ư���)\n�Է� : ");
				scanf("%d", &QChoice);

				QuestState(Quest, Enemy, QChoice);

				break;
			
			case 2 :
			//���谡 ���(level)
				//�׽�Ʈ�� ����ġ
				Player->Info.EXP = 100;

				LevelUp(Player, Equipment);
				break;

			case 3 :
				printf_s("���� �÷��̾��� ����� %d �Դϴ�.\n", Player->Info.Level);
				Sleep(1000);
				break;

			case 4 :
				printf_s("�׻� ���������� �� ������!\n");
				Continue = 0;
				break;
		}
	}
}

void InitializeQuest(Object* Quest, int QuestIndex, int Stage)
{
	if (Stage == 1)
	{
		switch (QuestIndex)
		{
			case 0 :
				Quest[QuestIndex].Name = (char*)"������ 3 ���� óġ";
				Quest[QuestIndex].State = 0;
				Quest[QuestIndex].Num = 2;
				Quest[QuestIndex].Info.Gold = 50;
				Quest[QuestIndex].Info.EXP = 25;
				//����Ʈ �Ϸ� ����
				Quest[QuestIndex].Kills = 3;
				break;

			case 1 :
				Quest[QuestIndex].Name = (char*)"����� óġ";
				Quest[QuestIndex].State = 0;
				Quest[QuestIndex].Num = 12;
				Quest[QuestIndex].Info.Gold = 200;
				Quest[QuestIndex].Info.EXP = 100;
				Quest[QuestIndex].Kills = 1;
				break;
			
		}
	}

	else if (Stage == 2)
	{
		switch (QuestIndex)
		{

		}
	}
}

void QuestState(Object* Quest, Object* Enemy, int _Choice)
{
	

	switch (_Choice)
	{
		case 1:
			Quest[_Choice - 1].Name = (char*)"������ 3���� óġ(������)";
			Quest[_Choice - 1].State = 1;
			Enemy[Quest[_Choice-1].Num].State = 0;
			break;
		case 2:
			//����
			Quest[_Choice-1].Name = (char*)"����� óġ(������)";
			Quest[_Choice-1].State = 1;
			Enemy[Quest[_Choice-1].Num].State = 0;
			break;
	}
	
}

void LevelUp(Object* Player, EQUIPMENT* Equipment)
{
	int iAgree = 0;

	int iNeedEXP[16];

	for (int i = 0; i < 16; i++)
	{
		if (i == 0)
			iNeedEXP[i] = 10;

		else
			iNeedEXP[i] = iNeedEXP[i-1] * 2;

	}

	printf_s("���� �÷��̾��� ����� %d �Դϴ�.\n", Player->Info.Level);
	Sleep(500);
	printf_s("�±ޱ��� %d EXP�ʿ��մϴ�.\n", iNeedEXP[Player->Info.Level - 1]);
	Sleep(500);
	printf_s("�±��Ͻðڽ��ϱ�?(1.�� 2.�ƴϿ�)\n����EXP : %d\n�Է� : ", Player->Info.EXP);
	scanf("%d", &iAgree);

	if (iAgree == 1)
	{
		//	2Level���� �ö󰡱����� �ʿ��� ����ġ�� iNeed[0]���� ���� �Ǿ��ֱ� ������
		//	�÷��̾� ���� Level���� 1�� ���� �ȴ�.
		Player->Info.EXP -= iNeedEXP[Player->Info.Level - 1];
		Player->Info.Level++;

		printf_s("���谡����� %d�� �ö���!!\n", Player->Info.Level);
		if (Player->Info.Level == 2)
		{
			printf_s("ù ���� ���ϵ帳�ϴ�!\n�̰� ��忡���帮�� �����̿���!\n");
			Equip(Player, Equipment, 9);
			Player->State = 0;
		}

		else if (Player->Info.Level % 5 == 0)
		{
			switch (Player->State)
			{
				case 0:
					break;
			}
		}

	}
}

void Shop(Object* Player, INVENTORY* Inventory)
{
	int iIndex = 0;

	int iPurchase = 0;
	int iPNumber = 0;

	int iSell = 0;
	int iSNumber = 0;

	int Continue = 1;

	while (Continue)
	{

		ShopBackGround();
		printf_s("����ð�\n1.���\t2.�Ǵ�\t3.���ư���\n�Է� : ");
		scanf("%d", &iIndex);

		switch (iIndex)
		{
			case 1:
				//�������Ǹ��
				for (int i = 0; i < 1; i++)
				{
					printf_s("�����۸�\t����\n");
					printf_s("%d. %s\t\t%d G\n", i + 1, Inventory[i].item.Object.Name, Inventory[i].Equipment.Price);
					
				}
				printf_s("�����ݾ� : %d\n", Player->Info.Gold);

				printf_s("�����ϰ� ���� �׸��� ��ȣ�� �Է��Ͻʽÿ� : ");
				scanf("%d", &iPurchase);

				if (Inventory[iPurchase - 1].Equipment.Stock < 0)
				{
					printf_s("���� �׸� �Դϴ�!\n");
				}

				else
				{
					printf_s("�� �� �����Ͻðڽ��ϱ�?(������:%d) : ", Inventory[iPurchase-1].Equipment.Stock);
					scanf("%d", &iPNumber);

					if (Player->Info.Gold < (Inventory[iPurchase - 1].Equipment.Price * iPNumber))
					{
						printf_s("Gold�� �����մϴ�.\n");
					}

					else
					{
						printf_s("%s��(��) %d�� �����ߴ�.\n", Inventory[iPurchase - 1].item.Object.Name, iPNumber);
						Sleep(500);

						printf_s("%d Gold�� �����ߴ�\n", Inventory[iPurchase - 1].Equipment.Price * iPNumber);
						Inventory[iPurchase-1].Equipment.Stock += iPNumber;
						Player->Info.Gold -= Inventory[iPurchase-1].Equipment.Price * iPNumber;
						Sleep(1000);
					}
				}

				break;

			case 2:
				
				//�÷��̾� ���Ǹ��
				PlayerScene(Player, Inventory);
				printf_s("�����ݾ� : %d\n", Player->Info.Gold);

				printf_s("�Ǹ��ϰ� ���� �׸��� ��ȣ�� �Է��Ͻʽÿ� : ");
				scanf("%d", &iSell);

				if (Inventory[iSell - 1].Equipment.Stock < 0)
				{
					printf_s("���� �׸��Դϴ�!\n");
				}

				else
				{
					printf_s("�� �� �Ǹ��Ͻðڽ��ϱ�?(������:%d) : ", Inventory[iSell-1].Equipment.Stock);
					scanf("%d", &iSNumber);

					if (Inventory[iSell - 1].Equipment.Stock < iSNumber)
					{
						printf_s("���� �ͺ��� ���� �� �� �����ϴ�!\n");
					}

					else
					{
						printf_s("%s��(��) %d�� �Ǹ��ߴ�.\n", Inventory[iSell - 1].item.Object.Name, iSNumber);
						Sleep(500);
						printf_s("%d Gold�� �����\n", Inventory[iSell - 1].Equipment.Price * iSNumber);
						Inventory[iSell-1].Equipment.Stock -= iSNumber;
						Player->Info.Gold += Inventory[iSell-1].Equipment.Price * iSNumber;
						Sleep(1000);
					}

				}
				break;
				
			case 3:
				printf_s("����! �� ���ð�!\n");
				Continue = 0;
				break;
			}
		}
		
}

void ShopBackGround()
{

}

void Forge(Object* Player, EQUIPMENT* Equipment)
{
	int SelectParts = 0;

	printf("Gold�� �ָ� ��� �� ������ ����� �帮����!\n");
	//  ���� �ڸ��� 0~3���� 4���� 5���� 6���� 7�Ź� 8 �尩
	// 0�� 1 ���� 2 â 3 Ȱ
	printf("��� ��� ��ȭ�Ͻðڽ��ϱ�?\n1.����\n2.����\n3.����\n4.����\n5.�Ź�\n6.�尩\n�Է� : ");
	scanf("%d", &SelectParts);

		if (SelectParts == 1)
		{
			for (int i = 0; i < 3; i++)
			{
				for (int j = 0; j < 4; j++)
				{
					if (Equipment[j+(10*i)].object.State == 1)
					{
						Reinforce(Player, Equipment, i);
					}
				}
			}
		}

		else if (SelectParts<7 && SelectParts >1)
			for (int i = 0; i < 3; i++)
			{
				if(Equipment[(SelectParts+2)+(i*10)].object.State == 1)
					Reinforce(Player, Equipment, SelectParts + 2);
			}
}

void Training(Object* Player, EQUIPMENT* Equipment, INVENTORY* Inventory, SKILL* Skill, PLAYERSKILL* PlayerSkill)
{
	printf_s("����ʽÿ�. ����� �Ʒ���\n");
	Sleep(500);
	printf_s("���⼭�� ��ų�� ���� �ֽ��ϴ�.\n");
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 4; j++)
		{

			if (Equipment[j+(i*10)].object.State == 1)
			{
				switch (i % 10)
				{
					case 0 :
						break;
					case 1 :
						break;
					case 2 :
						break;
					case 3 :
						break;
				}
			}
		}
	}
}

void Status(Object* Player, Object* Enemy, int EnemyIndex)
{
	int Battle = 0;
	system("cls");
	EnemyStatus(Enemy, EnemyIndex);

	printf_s("\n\n");

	PlayerStatus(Player, Battle);
}

void PlayerStatus(Object* Player, int State)
{
	//�÷��̾��� ������ ���
	if (State == 0)
	{
		printf_s("[Player] : %s\n", Player->Name);
		printf_s("HP : %d/%d\n", Player->Info.HP,Player->Info.MaxHP);
		printf_s("MP : %d/%d\n", Player->Info.MP, Player->Info.MaxMP);
	}

	else if (State == 1)
	{
		printf_s("[Player] : %s\n", Player->Name);
		printf_s("HP : %d/%d\n", Player->Info.HP, Player->Info.MaxHP);
		printf_s("MP : %d/%d\n", Player->Info.MP, Player->Info.MaxMP);
		printf_s("���ݷ� : %.0f\n", Player->Info.Att);
		printf_s("���� : %.0f\n", Player->Info.Def);
		printf_s("��ø : %d\n", Player->Info.Speed);
		printf_s("���谡 ��� : %d\n", Player->Info.Level);
		printf_s("����ġ : %d\n", Player->Info.EXP);
		printf_s("Gold : %d\n", Player->Info.Gold);
	}
}

void EnemyStatus(Object* Enemy, int EnemyIndex)
{
	//������ ������ ���
	printf_s("\n%s\n", Enemy[EnemyIndex].Name);
	printf_s("HP : %d\n", Enemy[EnemyIndex].Info.HP);
	printf_s("MP : %d\n", Enemy[EnemyIndex].Info.MP);
}


short Battle(Object* Player, Object* Enemy, int EnemyIndex, Object* Quest, INVENTORY* Inventory)
{
	// ���� �ݺ��� ���� �Լ�
	short Battle = 1;
	short Defeat = 1;

	int UseItem = 0;

	printf_s("%s��(��) ��Ÿ����!!\n",Enemy[EnemyIndex].Name);
	//����
	while (Battle)
	{
		//�Է��� �ޱ����� ���� �Լ�
		int iChoice = 0;
		printf("1.����\t2.���\t3.��ų\t4.������\t4.����\n�Է� : ");
		scanf_s("%d", &iChoice);

		//�Է¹��� ���� ���� ��������
		switch (iChoice)
		{
			//������ �������� ��
			case 1:
			{
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
						for (int i = 0; i < 2; i++)
						{
							if (Quest[i].State == 1)
							{
								if (EnemyIndex == Quest[i].Num)
								{
									Enemy[EnemyIndex].State++;
								}
							}
						}
						InitializeObjectEnemy(Enemy, EnemyIndex);
						break;
					}

					//�÷��̾� ���� �� ������ ����
					EnemyAttack(Player, Enemy, EnemyIndex);

					//���� ���� ������ ���̱� ���� ������ �Լ�
					Sleep(500);

					// ���� ���� �� ����â ����
					Status(Player, Enemy, EnemyIndex);

					//�÷��̾� ����
					if (Player->Info.HP <= 0)
					{
						printf_s("%s��(��) �ٽ�������.", Player->Name);
						SceneState = Scene_Logo;
						Battle = 0;
						Sleep(1000);
						Defeat = GameOver();
						break;
					}
				}

				else if (Player->Info.Speed <= Enemy[EnemyIndex].Info.Speed)
				{
					//������ ����
					EnemyAttack(Player, Enemy, EnemyIndex);

					//���� ���� ������ ���̱� ���� ������ �Լ�
					Sleep(500);

					// ���� ���� �� ����â ����
					Status(Player, Enemy, EnemyIndex);

					//�÷��̾� ����
					if (Player->Info.HP <= 0)
					{
						printf_s("%s��(��) �ٽ�������.\n", Player->Name);
						SceneState = Scene_Logo;
						Battle = 0;
						Sleep(1000);
						Defeat = GameOver();
						break;
					}

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
			}
				// **���
			case 2:
			{
				printf_s("%s��(��) �� �����Ѵ�.\n",Player->Name);
				Player->Info.Def *= 2;
				Sleep(500);

				EnemyAttack(Player, Enemy, EnemyIndex);
				Sleep(500);

				Player->Info.Def /= 2;

				Status(Player, Enemy, EnemyIndex);

				if (Player->Info.HP <= 0)
				{
					printf_s("%s��(��) �ٽ�������.\n", Player->Name);
					SceneState = Scene_Logo;
					Battle = 0;
					Sleep(1000);
					Defeat = GameOver();
					break;
				}
				break;
			}
				// ** ��ų
			case 3:
			{
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
			}
				//���� �� ������ ���
			case 4:
				printf_s("�����۸�\t����\n");
				for (int i = 0; i < 1; i++)
				{
					if (Inventory[i].Equipment.Stock > 0)
						printf_s("%d. %s\t\t%d\n", i + 1, Inventory[i].item.Object.Name, Inventory[i].Equipment.Stock);
				}
				printf_s("����Ͻ� �������� ��ȣ�� �Է��ϼ���\n �Է� :");

				scanf("%d", &UseItem);

				if (Inventory[UseItem - 1].Equipment.Stock > 0)
				{
					Inventory[UseItem - 1].Equipment.Stock -= 1;
					printf_s("%s��(��) ����ߴ�!\n", Inventory[UseItem - 1].item.Object.Name);
					Sleep(500);

					if (Inventory[UseItem - 1].item.Effect.Info.HP > 0)
					{
						if (Player->Info.HP + Inventory[UseItem - 1].item.Effect.Info.HP < Player->Info.MaxHP)
						{
							printf_s("ü���� %d��ŭ ȸ���ߴ�!\n", Inventory[UseItem - 1].item.Effect.Info.HP);
							Player->Info.HP += Inventory[UseItem - 1].item.Effect.Info.HP;
							Sleep(500);
						}

						else if (Player->Info.HP + Inventory[UseItem - 1].item.Effect.Info.HP > Player->Info.MaxHP)
						{
							printf_s("ü���� %d��ŭ ȸ���ߴ�!\n", Player->Info.MaxHP - Player->Info.HP);
							Player->Info.HP = Player->Info.MaxHP;
							Sleep(500);
						}

						else if (Player->Info.HP == Player->Info.MaxHP)
						{
							printf_s("�̹� ü���� ���� �� �����Դϴ�.\n");
						}
					}

					else if (Inventory[UseItem - 1].item.Effect.Info.MP > 0)
					{
						if (Player->Info.MP + Inventory[UseItem - 1].item.Effect.Info.MP < Player->Info.MaxMP)
						{
							printf_s("������ %d��ŭ ȸ���ߴ�!\n", Inventory[UseItem - 1].item.Effect.Info.MP);
							Player->Info.MP += Inventory[UseItem - 1].item.Effect.Info.MP;
							Sleep(500);
						}

						else if (Player->Info.MP + Inventory[UseItem - 1].item.Effect.Info.MP > Player->Info.MaxMP)
						{
							printf_s("������ %d��ŭ ȸ���ߴ�!\n", Player->Info.MaxMP - Player->Info.MP);
							Player->Info.MP = Player->Info.MaxMP;
							Sleep(500);
						}

						else if (Player->Info.MP == Player->Info.MaxMP)
						{
							printf_s("�̹� ������ ���� �� �����Դϴ�.\n");
						}
					}

					EnemyAttack(Player, Enemy, EnemyIndex);
					Sleep(500);

					Status(Player, Enemy, EnemyIndex);

					if (Player->Info.HP <= 0)
					{
						printf_s("%s��(��) �ٽ�������.\n", Player->Name);
						SceneState = Scene_Logo;
						Battle = 0;
						Sleep(1000);
						Defeat = GameOver();
						break;
					}
				}

				else
				{
					printf_s("���������ʰų� ������������ �׸��Դϴ�!\n");
				}
				break;
				//������ �������� ��
			case 5:

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

						if (Player->Info.HP <= 0)
						{
							printf_s("%s��(��) �ٽ�������.\n", Player->Name);
							SceneState = Scene_Logo;
							Battle = 0;
							Sleep(1000);
							Defeat = GameOver();
							break;
						}
					}
				}

				else
				{
					printf_s("%s�� ���� �������� ����!\n", Enemy[EnemyIndex].Name);
					Sleep(500);

					EnemyAttack(Player, Enemy, EnemyIndex);

					Sleep(500);

					Status(Player, Enemy, EnemyIndex);

					if (Player->Info.HP <= 0)
					{
						printf_s("%s��(��) �ٽ�������.\n", Player->Name);
						SceneState = Scene_Logo;
						Battle = 0;
						Sleep(1000);
						Defeat = GameOver();
						break;
					}
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

	return Defeat;
}

void PlayerAttack(Object* Player, Object* Enemy, int EnemyIndex)
{
	printf_s("%s�� ����!!\n", Player->Name);
	Sleep(500);
	//�÷��̾��� ���ݷ°� ������ ������ ���Ͽ� �������� ����ϴ� ���ǹ�
	if (Player->Info.Att > Enemy[EnemyIndex].Info.Def)
	{
		printf_s("%s�� %d��ŭ�� �������� �޾Ҵ�!\n", Enemy[EnemyIndex].Name, (int)(Player->Info.Att - Enemy[EnemyIndex].Info.Def));
		Enemy[EnemyIndex].Info.HP -= (int)(Player->Info.Att - Enemy[EnemyIndex].Info.Def);
	}
	// ������ �� ���� ��� �ּ� 1�� �������� �ַ�����
	else
	{
		printf_s("%s�� 1��ŭ�� �������� �޾Ҵ�!\n", Enemy[EnemyIndex].Name);
		Enemy[EnemyIndex].Info.HP -= 1;
	}
}

void EnemyAttack(Object* Player, Object* Enemy, int EnemyIndex)
{
	printf_s("%s�� ����!!\n", Enemy[EnemyIndex].Name);
	Sleep(500);
	if (Enemy[EnemyIndex].Info.Att > Player->Info.Def)
	{
		printf_s("%s�� %d��ŭ�� �������� �Ծ���!\n", Player->Name, (int)Enemy[EnemyIndex].Info.Att - Player->Info.Def);
		Player->Info.HP -= (int)(Enemy[EnemyIndex].Info.Att - Player->Info.Def);
	}
	else
		Player->Info.HP -= 1;
}

void Equip(Object* Player, EQUIPMENT* Equipment, int EquipmentNum)
{
	printf_s("%s ��(��) �����!\n", Equipment[EquipmentNum].object.Name);

	Player->Info.HP += Equipment[EquipmentNum].Info.MaxHP;
	Player->Info.MP += Equipment[EquipmentNum].Info.MaxMP;
	Player->Info.Att += Equipment[EquipmentNum].Info.Att;
	Player->Info.Def += Equipment[EquipmentNum].Info.Def;
	Player->Info.Speed += Equipment[EquipmentNum].Info.Speed;
	Equipment[EquipmentNum].object.State = 1;

	Sleep(1000);
}

void Reinforce(Object* Player, EQUIPMENT* Equipment, int EquipmentID)
{
	int iAgree = 0;
	for (EquipmentID; EquipmentID < 30; EquipmentID++)
	{
		if (Equipment[EquipmentID].object.State == 1)
		{
			printf_s("%s�� ��ȭ �ϰڳ�?\n", Equipment[EquipmentID].object.Name);
			printf_s("%d Gold�ʿ��ϳ�(1.�� 2.�ƴϿ�) : ",Equipment[EquipmentID].Info.Gold);
		}
	}
	scanf(" %d", &iAgree);

	if (iAgree == 1)
	{
		
				Equipment[EquipmentID].object.State = 0;
				Equip(Player, Equipment, EquipmentID + 10);
				Player->Info.Gold -= Equipment[EquipmentID].Info.Gold;
		
	}

}

short GameOver()
{
	system("cls");

	int Width = 120 / 2 - (strlen("===================================================================") / 2);
	int Height = 5;
	
	SetPosition(Width, Height, (char*)"===================================================================");
	SetPosition(Width, Height+1, (char*)"==      =============================    ==========================");
	SetPosition(Width, Height+2, (char*)"=   ==   ===========================  ==  =========================");
	SetPosition(Width, Height+3, (char*)"=  ====  ==========================  ====  ========================");
	SetPosition(Width, Height+4, (char*)"=  =========   ===  =  = ====   ===  ====  ==  =  ===   ===  =   ==");
	SetPosition(Width, Height+5, (char*)"=  ========  =  ==        ==  =  ==  ====  ==  =  ==  =  ==    =  =");
	SetPosition(Width, Height+6, (char*)"=  ===   =====  ==  =  =  ==     ==  ====  ===   ===     ==  ======");
	SetPosition(Width, Height+7, (char*)"=  ====  ===    ==  =  =  ==  =====  ====  ===   ===  =====  ======");
	SetPosition(Width, Height+8, (char*)"=   ==   ==  =  ==  =  =  ==  =  ===  ==  ===== ====  =  ==  ======");
	SetPosition(Width, Height+9, (char*)"==      ====    ==  =  =  ===   =====    ====== =====   ===  ======");
	SetPosition(Width, Height+10, (char*)"===================================================================");
	Sleep(1000);

	iStage = 0;
	return 0;
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