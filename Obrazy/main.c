#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <locale.h>
#include <stdbool.h>

struct obraz
{
	char nazwa[100];
	char stan[2];
	int wys;
	int sze;
	int glebia;
	int** tab;

};


void odczyt(struct obraz** temp)
{
	struct obraz* ob1;
	char* litera = NULL;
	litera = malloc(100 * sizeof(*litera));
	ob1 = *temp;
	
	
	printf("Podaj nazwê pliku: ");
	scanf("%s", ob1->nazwa);


	FILE* plik;
	plik = fopen(ob1->nazwa, "r");                     
	if (plik == NULL)
	{
		printf("Nie uda³o siê otworzyæ pliku.");
		exit(1);
	}
	fscanf(plik,"%s", ob1->stan);
		do
		{
		fscanf(plik,"%s", litera);
		
		} while(isdigit(*litera) == 0);
		
		ob1->sze = atoi(litera);

		do
		{
			fscanf(plik, "%s", litera);

		} while (isdigit(*litera) == 0);
		
		ob1->wys = atoi(litera);
	
	
	ob1->tab = malloc(ob1->wys * sizeof(*ob1->tab));
	for (int i = 0; i<ob1->wys;i++)
	{
		ob1->tab[i] = malloc(ob1->sze * sizeof(ob1->tab));
	}
	do
	{
		fscanf(plik, "%s", litera);

	} while (isdigit(*litera) == 0);

	ob1->glebia = atoi(litera);
	
	
	for (int i = 0; i < ob1->wys; i++)
	{
		for (int j = 0; j < ob1->sze; j++)
		{
			do
			{
				fscanf(plik, "%s", litera);

			} while (isdigit(*litera) == 0);

			ob1->tab[i][j] = atoi(litera);
			
		}
	}
	fclose(plik);
	free(litera);
	litera = NULL;
}
void zapis(struct obraz ob2)
{
	char tab_string[100];
	printf("Podaj nazwê pliku: ");
	scanf("%s", tab_string);
	FILE* plik;
	plik = fopen(tab_string, "w");
	//plik = fopen("dupa.pgm", "w");
	if (plik == NULL)
	{
		printf("Nie uda³o siê otworzyæ pliku.");
		exit(1);
	}
	fprintf(plik, "%c%c\n", ob2.stan[0], ob2.stan[1]);
	fprintf(plik, "%d %d\n",ob2.sze, ob2.wys);
	fprintf(plik, "%d\n", ob2.glebia);
	for (int i = 0; i < ob2.wys; i++)
	{
		for (int j = 0; j < ob2.sze; j++)
		{
			fprintf(plik, "%d ", ob2.tab[i][j]);
		}
		fprintf(plik, "\n");
	}
	fclose(plik);
}

void zwolnienie(struct obraz** temp, int n)
{
	struct obraz* ob;
	
	int k=0;
	ob = *temp;
	for (int j = 0; j < n; j++)
	{
		
		for (int i = 0; i < ob[k].wys; i++)
		{
			free(ob[k].tab[i]);
		}
		free(ob[k].tab);
		k++;
		
	}
	
}

void usun(struct obraz* ob,int k,int n)
{
	int temp;
	if (n > 1)
	{
		temp = n - k - 1;
		for (int i = 0; i < ob[k].wys; i++)
		{
			free(ob[k].tab[i]);
		}
		free(ob[k].tab);
		for (int i = 0; i < temp; i++)
		{
			ob[k] = ob[k + 1];
			k++;
		}
		printf("\nUsuniêto obraz z bazy\n");
	}
	else if (n == 1)
	{
		for (int i = 0; i < ob[k].wys; i++)
		{
			free(ob[k].tab[i]);
		}
		free(ob[k].tab);
		printf("\nUsuniêto obraz z bazy\n");
	}
	else
		printf("\nW bazie nie ma odczytanego obrazu\n");
	
}

void rotate_left(struct obraz** ob) 
{
	
	struct obraz* image;
	image = *ob;
	int** new_tab = malloc(image->sze * sizeof(int*));
	

	
	for (int i = 0; i < image->sze; i++) 
	{
		new_tab[i] = malloc(image->wys * sizeof(int));
		
	}

	
	for (int y = 0; y < image->wys; y++) 
	{
		for (int x = 0; x < image->sze; x++) 
		{
			new_tab[x][image->wys - y - 1] = image->tab[y][x];
		}
	}

	
	for (int i = 0; i < image->wys; i++) 
	{
		free(image->tab[i]);
	}
	free(image->tab);

	
	image->tab = new_tab;

	
	int temp = image->sze;
	image->sze = image->wys;
	image->wys = temp;
}
void negatyw(struct obraz** ob)
{
	struct obraz* temp;
	temp = *ob;
	for (int i = 0; i < temp->wys; i++)
	{
		for (int j = 0; j < temp->sze; j++)
		{
			 temp->tab[i][j]=(temp->glebia-(temp->tab[i][j]));
		}
	}

}
void szum(struct obraz** ob)
{
	struct obraz* temp;
	srand(time(NULL));
	int a, b;
	temp = *ob;
	int il = (temp->wys * temp->sze) / 70;

	for (int i = 0; i<il; i++)
	{
		a = rand() % temp->wys;
		b = rand() % temp->sze;
		temp->tab[a][b] = 0;

	}
	for (int i = 0; i < il; i++)
	{
		a = rand() % temp->wys;
		b = rand() % temp->sze;
		temp->tab[a][b] = temp->glebia;

	}


}
void histogram(struct obraz** obr)
{
	int* tab;
	struct obraz* ob;
	ob = *obr;
	int g = -1;
	tab = malloc((ob->glebia+1) * sizeof(int));
	for (int i = 0; i <= ob->glebia; i++) 
	{
		tab[i] = 0;
	}
	for (int i = 0; i < ob->wys; i++)
	{
		for (int j = 0; j < ob->sze; j++)
		{
			g = -1;
			do
			{
				g++;
				if (ob->tab[i][j] == g)
				{
					tab[g]++;
				}
		
			} while (ob->tab[i][j] != g);
	
		}
	}
	FILE* plik;
	plik = fopen("histogram.CSV", "w");
	if (plik == NULL)
	{
		printf("Nie uda³o siê otworzyæ pliku.");
		exit(1);
	}
	fprintf(plik, "Histogram wybranego obrazu:\n");
	
	for (int i = 0; i <= ob->glebia; i++)
	{
		
		fprintf(plik, "%d\n",tab[i]);

	}
	fclose(plik);
	free(tab);
}
void filtr(struct obraz** ob)
{
	struct obraz* temp;
	temp = *ob;
	int tab[9];
	for (int i = 1; i < temp->wys-1; i++)
	{
		for (int j = 1; j < temp->sze-1; j++)
		{
			
			tab[0] = temp->tab[i-1][j-1];
			tab[1] = temp->tab[i][j - 1];
			tab[2] = temp->tab[i + 1][j - 1];
			tab[3] = temp->tab[i - 1][j];
			tab[4] = temp->tab[i][j];
			tab[5] = temp->tab[i + 1][j];
			tab[6] = temp->tab[i - 1][j + 1];
			tab[7] = temp->tab[i][j + 1];
			tab[8] = temp->tab[i + 1][j + 1];

			for (int i = 0; i < 8; i++)
			{
				for (int j = 0; j < 8-i; j++)
				{
					if (tab[j] > tab[j + 1])
					{
						int temp;

						temp = tab[j];
						tab[j] = tab[j + 1];
						tab[j + 1] = temp;

					}
				}
			}

			temp->tab[i][j] = tab[4];

		}
	}

}

int main()
{
	int n = 0, wybor, k, a = 0;
	bool akt = 0;
	setlocale(LC_ALL, "polish_poland");
	char* litera = NULL;
	litera = malloc(100 * sizeof(*litera));
	struct obraz* tab_ob;
	struct obraz* temp;
	struct obraz* tempakt;

	tab_ob = NULL;
	tempakt = NULL;

	do
	{
		printf("\n1  --> Odczytaj obraz z pliku\n2  --> Usuñ odczytany obraz\n3  --> Zapisz odczytany obraz do pliku .PGM\n4  --> Wybierz aktywny obraz\n5  --> Obróæ obraz o 90 stopni\n6  --> Negatyw\n7  --> Zaszum obraz pieprzem i sol¹\n8  --> Wyœwietl listy obrazów\n9  --> Utwórz histogram obrazu w excelu\n10 --> Odfiltruj obraz z szumu\n11 --> Wyczyœæ konsole\n12 --> Zakoñcz program\nWybierz dzia³anie: ");
		
		do
		{
			scanf("%s", litera);
			if (isdigit(*litera) == 0)
			{
				printf("\nWybierz dzia³anie: \n");
			}
		} while (isdigit(*litera) == 0);
		wybor = atoi(litera);
		switch (wybor)
		{
		case 1: //odczyt
			if (n == 0)
			{
				n++;
				tab_ob = malloc(n * sizeof(*tab_ob));
			
			}
			else
			{
				n++;
				tab_ob = realloc(tab_ob, n * sizeof(*tab_ob));
				

			}
			temp = (tab_ob + n - 1);
			odczyt(&temp);
			printf("\nOdczytano plik\n");

			break;

		case 2: //usuwanie
			printf("Usuñ obraz: ");
			scanf("%d", &k);
			if (k > n - 1||k<0)
			{
				printf("\nUsuwany obraz musi byæ w najpierw odczytany\nAby zobaczyæ, który obraz chcesz wybraæ wybierz 8 dzia³anie\n");
				break;
			}
			usun(tab_ob, k, n);
			n--;
			tab_ob = realloc(tab_ob, n * sizeof(*tab_ob));
			break;
		case 3: //zapis
			if (akt == 0)
			{
				printf("\nNie wybrano aktywnego obrazu!\n");
				break;
			}
			zapis(*tempakt);
			printf("\nZapisano plik\n");
			break;

		case 4: //aktywny obraz
			printf("\nPodaj aktywny obraz: ");
			scanf("%d", &a);
			if (a >= n||a<0)
			{
				printf("\nNie zapisano tylu obrazów\n");
				break;
			}
			tempakt = (tab_ob + a);
			akt = 1;
			break;
		case 5: //obrot
			if (akt == 0)
			{
				printf("\nNie wybrano aktywnego obrazu!\n");
				break;
			}
			rotate_left(&tempakt);
			printf("\nObrócono obraz o 90 stopni w lewo\n");
			break;
		case 6: //negatyw
			if (akt == 0)
			{
				printf("\nNie wybrano aktywnego obrazu!\n");
				break;
			}
			negatyw(&tempakt);
			printf("\nObraz jest teraz w negatywie\n");
			break;
		case 7: //szum
			if (akt == 0)
			{
				printf("\nNie wybrano aktywnego obrazu!\n");
				break;
			}
			szum(&tempakt);
			printf("\nZaszumiono obraz\n");
			break;
		case 8: //lista
			printf("\nLista obrazów:\n");
			if (n == 0)
			{
				printf("\nNie odczytano ¿adnego obrazu\n");
			}
			
			for (int i = 0; i < n; i++)
			{
				printf("%d - %s\n",i, tab_ob[i].nazwa);
				
			}
			break;
		case 9: //histogram
			if (akt == 0)
			{
				printf("\nNie wybrano aktywnego obrazu!\n");
				break;
			}
			histogram(&tempakt);
			printf("\nUtworzono histogram obrazu\n");
			break;
		case 10: //filtr
			if (akt == 0)
			{
				printf("\nNie wybrano aktywnego obrazu!\n");
				break;
			}
			filtr(&tempakt);
			printf("\nOdfiltrowano obraz\n");
			break;
		case 11: //czyszczenie konsoli
			system("cls");		
			break;
		default:
			printf("\nWybrano niepoprawne dzia³anie!\n");
			break;

		}
	} while (wybor != 12);
	zwolnienie(&tab_ob, n);
	free(litera);
	free(tab_ob);
	litera = NULL;
	printf("\n\nProgram wykona³ Wiktor Witaszek\n\n");

	return 0;
}