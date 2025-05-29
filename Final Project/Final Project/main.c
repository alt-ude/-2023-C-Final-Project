#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

int screen(void); //ù ȭ�� 
int HANGMAN(void); //������
void writelist(void); //���ο� �ܾ� ����Ʈ �ۼ�
void MiniGame(void); //�̴� �ܾ� ����
int YorN(void); //����� 


int main (void)
{
	int sc, YN = 1;

	while (YN==1)
	{
		sc = screen();

		if (sc == 1)
		{
			HANGMAN();
			YN = YorN();
		}

		if (sc == 2)
		{
			MiniGame();
			YN = YorN();
		}

		if (sc == 3)
		{
			writelist();
			YN = YorN();
		}

		if (sc == 4)
		{
			return 0;
			YN = YorN();
		}

		if (sc != 1 && sc != 2 && sc != 3 && sc != 4)
		{
			printf("\nWRONG NUMBER!\n\n\n");
		}
		
	}

	return 0;

}

int HANGMAN(void)
{
	int life = 9, index, abc;

	char* c_index;

	srand(time(NULL));
	int random = rand() % 20 + 1;

	char c, 
		WORD[50] = { 0 }, WORDdummy[50] = { 0 }, 
		MEANING[50] = { 0 }, line[50] = { 0 }, filename[50],
		alphabet[60] = "a b c d e f g h i j k l m n o p q r s t u v w x y z", 
		alphabetdummy[60] = "a b c d e f g h i j k l m n o p q r s t u v w x y z";

	FILE* fp1;

	printf("\nWrite the name of the list you want to play: ");
	scanf_s("%s", filename, sizeof(filename));

	fopen_s(&fp1, filename, "r");

	if (fp1 == NULL)
	{
		printf("fail to open\n");
		return 0;
	}

	for (int i = 0; i < random; i++)
	{
		fscanf_s(fp1, "%s %s", WORD, sizeof(WORD), MEANING, sizeof(MEANING));
	}

	//printf("%s   meaning: %s\n", WORD, MEANING);

	fclose(fp1);

	//������� ���� ���ݱ� 



	for (int i = 0; i < strlen(WORD); i++)
	{	
		WORDdummy[i] = WORD[i];
		line[i] = '_'; // 0x5f;
		line[i+1] = '\0';
		//printf("%c ", line[i]); //�ܾ� ���ĺ� ����ŭ "_" ���
	}
	
	printf("\n\nHANGMAN\n\n");

	for (int i = 0; i < strlen(WORD); i++)
	{
		printf("%c ", line[i]); //�ܾ� ���ĺ� ����ŭ "_" ���
	}

	printf("\t life: %d\n", life);


	while(1) 
	{
		printf("\n\n\nLeft alphabets: %s\n", alphabet);
		printf("\nEnter the alphabet: ");
		scanf_s(" %c", &c);

		abc = (int)(strchr(alphabetdummy, c) - alphabetdummy);

		if (strchr(WORDdummy, c) == NULL) //�Է��� ���ĺ��� �ܾ ������
		{	

			printf("\nThe alphabet is not included in the word");
			life--;

			if (strchr(alphabet, c) == NULL)
			{
				printf(", but the alphabet was already used\n");
				life++;
			}

			if (life == 0) //life�� ���� �Ҹ��ϸ� break
			{
				printf("\n\nGAME OVER!\n\n");
				break;
			}

			printf("\n");

			for (int i = 0; i < strlen(WORD); i++)
			{
				printf("%c ", line[i]); //�ܾ� ���ĺ� ����ŭ "_" ���
			}
			printf("\tlife: %d\n", life);

		}
		else //�Է��� ���ĺ��� �ܾ ������ 
		{
			printf("\nThe alphabet is included in the word\n");

			while (strchr(WORD, c) != NULL) //�߰��ϰ� WORD�� ���� ������ ����(�ߺ� ���ĺ� Ȯ��) 
			{	
				c_index = strchr(WORD, c);
				index = (int)(c_index - WORD); //���ĺ��� �ִ� �ڸ� - ù ���ĺ� �ڸ� ����
				line[index] = c;
				WORD[index] = 0x5f;
			}

			for (int i = 0; i < strlen(WORD); i++)
			{
				printf("%c ", line[i]); //�ܾ� ���ĺ� ����ŭ "_" ���
			}

			printf("\tlife: %d\n", life);
			

			if (strchr(line, 0x5f) == NULL) //line�� "_"�� ���� ������ 
			{
				printf("\n\nGAME COMPLETE!\n\n");
				break;
			}

		}

		alphabet[abc] = 0x2d; //'-'

	}

	printf("\nThe word \"%s\" means \"%s\" in Korean\n\n", WORDdummy, MEANING);

	return 0;

}

void writelist(void)
{
	char WORD[50], fWORD[50], MEANING[50], fMEANING[50], filename[50];

	printf("\nWrite the name of the list you want to make: ");
	scanf_s("%s", filename, sizeof(filename));

	FILE *fp2;
	fopen_s(&fp2, filename, "w"); 

	if (fp2 == NULL)
	{
		printf("fail to open\n");
		return 0;
	}

	printf("\nWrite twenty words and Korean meanings.\n");

	for (int i = 0; i < 20; i++)
	{
		scanf_s("%s %s", WORD, sizeof(WORD), MEANING, sizeof(MEANING));
		fprintf(fp2, "%s %s\n", WORD, MEANING);
	}

	fclose(fp2);

	fopen_s(&fp2, filename, "r");

	printf("\nCheck the list.\n");

	printf("\nList name: %s\n", filename);

	for (int i = 0; i < 20; i++)
	{
		fscanf_s(fp2, "%s %s", fWORD, sizeof(fWORD), fMEANING, sizeof(fMEANING));
		printf("%s %s\n", fWORD, fMEANING);
	}

	fclose(fp2);

}

void MiniGame(void)
{
	char filename[50];

	FILE* fp3;
	printf("\nWrite the name of the list you want to play: ");
	scanf_s("%s", filename, sizeof(filename));

	fopen_s(&fp3, filename, "r");

	if (fp3 == NULL)
	{
		printf("fail to open\n");
		return 0;
	}

	char c,
		WORD[50] = { 0 }, WORDinput[50] = { 0 },
		MEANING[50] = { 0 };

	int index1 = 0, index2 = 0, minilife, numlist[30] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20 };

	srand(time(NULL));
	int random = rand() % 20 + 1;

	for (int i = 0; i < numlist[random-1]; i++)
	{
		fscanf_s(fp3, "%s %s", WORD, sizeof(WORD), MEANING, sizeof(MEANING));
	}

	numlist[random - 1] = 0;

	for (int i = 0; i < 3; )
	{
		minilife = 3 - i;

		printf("\n%s \tlife: %d\n", MEANING, minilife);
		scanf_s("%s", WORDinput, sizeof(WORDinput));

		if (strcmp(WORD, WORDinput) == 0) //��ġ
		{
			printf("\n\nCORRECT!\n\n");
			break;
		}
		else
		{
			i++;
			if (minilife == 1)
			{
				printf("\n\nGAME OVER!\n\n");
				printf("\nThe answer was %s\n", WORD);
			}
			else
				printf("\n\nTRY AGAIN!\n\n");
		}
		
	}



}

int screen(void)
{
	int screennum;
	printf("Press the number\n\n");
	printf("HANGMAN: 1 \nMinigame:2 \nNew Word List: 3\nExit: 4\n\n");
	scanf_s("%d", &screennum);

	return screennum;
}

int YorN(void)
{
	int YorN;
	printf("\n\nPress 1 to return to the first screen\nPress 2 to exit the game\n");
	scanf_s("%d", &YorN);
	printf("\n\n\n");
	return YorN; 
}

