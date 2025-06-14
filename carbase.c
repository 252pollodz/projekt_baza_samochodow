//
// Created by MAFILYW on 12.06.2025.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "carbase.h"

void make_cars_table(Tab_of_Cars* tab) {
    tab->car = NULL;
    tab->index_car =0;
}

void print_car_info(Tab_of_Cars* tab, int indeks) {
    printf(" %-6d|| %s || %s || %d || %ld || %s \n",indeks+1,tab->car[indeks].marka,tab->car[indeks].model,tab->car[indeks].year_of_production,tab->car[indeks].przebieg,tab->car[indeks].petrol_type);
}
int empty_check(const Tab_of_Cars* tab) {
    if (tab->car == NULL) {
        printf("Baza jest pusta!\n");
        return 1;
    }else
         return 0;
}
void print_cars_info(const Tab_of_Cars* tab) {
        printf("Samochody w bazie\nIndeks || Marka || Model || Rok produkcji || Przebieg || Rodaj paliwa\n");
        for(int i = 0; i < tab->index_car; i++) {
            printf(" %-d|| %s || %s || %d || %ld || %s\n",i+1,tab->car[i].marka,tab->car[i].model,tab->car[i].year_of_production,tab->car[i].przebieg,tab->car[i].petrol_type);
        }

}
void add_car(Tab_of_Cars* tab) {
    tab->car = realloc(tab->car, (tab->index_car + 1) * sizeof(car_info));
    if (tab->car == NULL) {
        printf("Blad alokacji pamieci\n");
        exit(EXIT_FAILURE);
    }
    char marka[31],model[21],petrol_type[9];

    int year_of_production;

    long przebieg;

    printf("Podaj dane do bazy:\n");

    while (1) {
        printf("\nMarka:\t");
        if (scanf("%30s",marka)==1) {
            int c;
            int too_long_input = 0;
            while ((c = getchar()) != '\n' && c != EOF) {
                too_long_input = 1;
            }
            if (too_long_input) {
                printf("Za dlugie dane, podaj krotsza marke (maks 30 znakow)!\n");
                continue;
            }
            break;
        }else {
            printf("Blad, podaj poprawna marke (do 30 znakow!)");
            while (getchar()!='\n');
        }
    }
    while (1) {
        printf("\nModel:\t");
        if (scanf("%20s",model)==1) {
            int c;
            int too_long_input = 0;
            while ((c = getchar()) != '\n' && c != EOF) {
                too_long_input = 1;
            }
            if (too_long_input) {
                printf("Za dlugie dane, podaj krotszy model(maks 20 znakow).\n");
                continue;
            }
            break;
        }else {
            printf("Blad, podaj poprawny model (do 20 znakow!)");
            while (getchar()!='\n');
        }
    }
    while (1) {
        printf("Rok produkcji:\t");
        if (scanf("%4d", &year_of_production) == 1 && year_of_production >= 1950 && year_of_production <= 2025) {
            break;
        }
        printf("Blad! Podaj poprawny rok (1950 %c 2025):\n",45);
        while (getchar() != '\n');
    }
    while (1) {
        printf("\nPrzebieg:\t");
        if (scanf("%ld",&przebieg)==1 && przebieg >= 1 && przebieg <= 3000000) {
            break;
        }else {
            printf("Blad, podaj poprawny przebieg (1 %c 3000000km)\n",45);
            while (getchar()!='\n');
        }
    }
    while (1) {
        printf("\nRodzaj paliwa:\t1 - Benzyna\t2 - Diesel\t3 - LPG\t4 - Elektryk\n");
        int fuel_choice;
        if (scanf("%d",&fuel_choice)==1){
            while (getchar()!='\n');
            if (fuel_choice >= 1 && fuel_choice <= 4) {
                switch (fuel_choice) {
                    case 1:
                        strncpy(petrol_type,"Benzyna",sizeof(petrol_type));
                        break;
                    case 2:
                        strncpy(petrol_type,"Diesel",sizeof(petrol_type));
                        break;
                    case 3:
                        strncpy(petrol_type,"LPG",sizeof(petrol_type));
                        break;
                    case 4:
                        strncpy(petrol_type,"Elektryk",sizeof(petrol_type));
                        break;
                    default:
                        printf("Blad opcji paliwa\n");continue;
                }break;
            }else {
                printf("Podaj liczbe od 1 do 4!");
                while (getchar()!='\n');
            }
        }else {
            printf("Blad wprowadzania danych, podaj liczbe od 1 do 4!");
            while (getchar()!='\n');
        }
    }

    strncpy(tab->car[tab->index_car].marka, marka, 31);
    strncpy(tab->car[tab->index_car].model, model, 21);
    tab->car[tab->index_car].year_of_production = year_of_production;
    tab->car[tab->index_car].przebieg = przebieg;
    strncpy(tab->car[tab->index_car].petrol_type, petrol_type, 9);
    tab->index_car++;

    printf("Pomyslnie dodano!\n");
    print_car_info(tab,tab->index_car-1);

}
void delete_car(Tab_of_Cars* tab, int indeks) {

    if (indeks < 0 || indeks > tab->index_car) {
        printf("Nieprawidlowy numer indeksu!\n");
        return;
    }
    printf("Pomyslnie usunieto samochod:\n");
    print_car_info(tab,indeks);
    for (int i = indeks; i < tab->index_car - 1; i++) {
        tab->car[i] = tab->car[i + 1];
    }
    tab->index_car--;
    tab->car = realloc(tab->car, tab->index_car * sizeof(car_info));

}
void modify_car(Tab_of_Cars* tab, int indeks) {
    int choice_of_modification;
    if (indeks < 0 || indeks > tab->index_car) {
        printf("Nieprawidlowy numer indeksu!\n");
        return;
    }
    print_car_info(tab,indeks);
    printf("Co chcesz zmodyfikowac?\n");
    printf("1 - marka\t2 - model\t3 - rok produkcji\t4 - przebieg\t5 - rodzaj paliwa\n");
    while (1) {
        if (scanf("%d", &choice_of_modification)==1) {
            switch (choice_of_modification) {
                case 1:
                    char new_mark[30];
                    printf("Podaj nowa marke pojazdu:");
                    scanf("%29s",new_mark);
                    strncpy(tab->car[indeks].marka, new_mark, 30);
                    break;
                case 2:
                    char new_model[30];
                    printf("Podaj nowy model:");
                    scanf("%29s",new_model);
                    strncpy(tab->car[indeks].model, new_model, 20);
                    break;
                case 3:
                    int new_year;
                    printf("Podaj nowy rok produkcji:");
                    scanf("%d", &new_year);
                    tab->car[indeks].year_of_production = new_year;
                    break;
                case 4:
                    long new_przebieg;
                    printf("Podaj nowy przebieg:");
                    scanf("%ld", &new_przebieg);
                    tab->car[indeks].przebieg = new_przebieg;
                    break;
                case 5:
                    char new_petrol_type[9];
                    while (1) {
                        printf("\nRodzaj paliwa:\t1 - Benzyna\t2 - Diesel\t3 - LPG\t4 - Elektryk\n");
                        int fuel_choice;
                        if (scanf("%d",&fuel_choice)==1){
                            while (getchar()!='\n');
                            if (fuel_choice >= 1 && fuel_choice <= 4) {
                                switch (fuel_choice) {
                                    case 1:
                                        strncpy(new_petrol_type,"Benzyna",sizeof(new_petrol_type));
                                        break;
                                    case 2:
                                        strncpy(new_petrol_type,"Diesel",sizeof(new_petrol_type));
                                        break;
                                    case 3:
                                        strncpy(new_petrol_type,"LPG",sizeof(new_petrol_type));
                                        break;
                                    case 4:
                                        strncpy(new_petrol_type,"Elektryk",sizeof(new_petrol_type));
                                        break;
                                    default:
                                        printf("Blad opcji paliwa\n");continue;
                                }break;
                            }else {
                                printf("Podaj liczbe od 1 do 4!");
                                while (getchar()!='\n');
                            }
                        }else {
                            printf("Blad wprowadzania danych, podaj liczbe od 1 do 4!");
                            while (getchar()!='\n');
                        }
                    }
                    strcpy(tab->car[indeks].petrol_type,new_petrol_type);
                    break;
                default:
                    printf("Zly numer!");

            }break;
        }else {
            printf("Podaj wlasciwy numer (1 %c 5)!",41);
        }
    }
    printf("Poprawnie zmodyfikowano!\n");
    print_car_info(tab,indeks);
}
void filter_options(Tab_of_Cars* tab) {
    int option_of_filter;
    int empty=0;
    printf("Wyszukaj za pomoca:\n");
    printf("1 - marka\t2 - model\t3 - rok produkcji\t4 - przebieg\t5 - rodzaj paliwa");
    if (scanf("%d", &option_of_filter)==1) {
        switch (option_of_filter) {
            case 1:
                char search_by_mark[31];
                printf("Podaj marke:");
                scanf("%30s",search_by_mark);
                for (int i = 0; i < tab->index_car; i++) {
                    if (strcmp(tab->car[i].marka,search_by_mark)==0) {
                        print_car_info(tab,i);
                        empty++;
                    }
                }if(empty==0) {
                    printf("Brak w bazie marki: %s\n",search_by_mark);
                }else {
                    empty=0;
                }
                break;
            case 2:
                char search_by_model[21];
                printf("Podaj model:");
                scanf("%20s",search_by_model);
                for (int i = 0; i < tab->index_car; i++) {
                    if (strcmp(tab->car[i].model,search_by_model)==0) {
                        print_car_info(tab,i);
                        empty++;
                    }
                }if(empty==0) {
                    printf("Brak tego modelu w bazie: %s\n",search_by_model);
                }else{
                    empty=0;
                }
                break;
            case 3:
                int search_by_year = 0;
                printf("Podaj rok produkcji:");
                scanf("%4d",&search_by_year);
                for (int i = 0; i < tab->index_car; i++) {
                    if (tab->car[i].year_of_production == search_by_year) {
                        print_car_info(tab,i);
                        empty++;
                    }
                }if(empty==0) {
                    printf("Brak rocznika %d w bazie.\n",search_by_year);
                }else{
                    empty=0;
                }
                break;
            case 4:
                long min_przebieg=0,max_przebieg=0;

                while (1){
                    printf("Podaj minimalny przebieg:");
                    if (scanf("%ld",&min_przebieg)!=1) {
                        printf("Blad wprowadzania danych, podaj liczbe!");
                    }else {
                        break;
                    }
                }
                while (1){
                    printf("Podaj maksymalny przebieg:");
                    if (scanf("%ld",&max_przebieg)!=1) {
                        printf("Blad wprowadzania danych, podaj liczbe!");
                    }else if(max_przebieg<min_przebieg) {
                        printf("Maksymalny przebieg musi byc wiekszy niz minimalny!");
                    }else {
                        break;
                    }
                }
                for (int i = 0; i < tab->index_car; i++) {
                    if (tab->car[i].przebieg>=min_przebieg && tab->car[i].przebieg<=max_przebieg) {
                        print_car_info(tab,i);
                        empty++;
                    }
                }if(empty==0) {
                    printf("Brak samochodu z przedzialu przebiegu: %ld %c %ld w bazie.\n",min_przebieg,41,max_przebieg);
                }else{
                    empty=0;
                }
                break;
            case 5:
                char search_by_petrol[9];
                printf("Podaj rodzaj paliwa:");
                scanf("%s",search_by_petrol);
                for (int i = 0; i < tab->index_car; i++) {
                    if (strcmp(tab->car[i].petrol_type,search_by_petrol)==0) {
                        print_car_info(tab,i);
                        empty++;
                    }
                }if(empty==0) {
                    printf("Brak samochodu z tym rodzajem paliwa: %s\n",search_by_petrol);
                }else{
                    empty=0;
                }
                break;
        }
    }
}
void save_cars_to_file(Tab_of_Cars* tab, const char* filename) {
    FILE* file = fopen(filename,"w");
    if (file == NULL) {
        printf("Nie mozna otworzyc pliku!\n");
        return;
    }
    for (int i =0; i < tab->index_car; i++) {
        fprintf(file, "%s;%s;%d;%ld;%s\n",tab->car[i].marka,tab->car[i].model,tab->car[i].year_of_production,tab->car[i].przebieg,tab->car[i].petrol_type);
    }fclose(file);
    printf("Dane zostaly zapisane to do pliku \"%s\".txt\n",filename);
}
void read_from_file(Tab_of_Cars* tab, const char* filename) {
    FILE* file = fopen(filename,"r");
    if (file == NULL) {
        printf("Nie mozna otworzyc pliku o nazwie: %s!\n",filename);
        return;
    }
    char marka[31],model[21],petrol_type[9];
    int year_of_production,przebieg;
    while (fscanf(file,"%30[^;];%20[^;];%d;%ld;%8[^\n]\n",marka,model,&year_of_production,&przebieg,petrol_type)==5){
        tab->car=realloc(tab->car, sizeof(car_info) * (1 + tab->index_car));
        if (tab->car==NULL) {
            printf("Blad alokacji pamieci!\n");
            exit(EXIT_FAILURE);
        }
        strncpy(tab->car[tab->index_car].marka,marka,31);
        strncpy(tab->car[tab->index_car].model,model,21);
        tab->car[tab->index_car].year_of_production=year_of_production;
        tab->car[tab->index_car].przebieg=przebieg;
        strncpy(tab->car[tab->index_car].petrol_type,petrol_type,9);
        tab->index_car++;
    }
    fclose(file);
    printf("Dane z pliku %s zostaly wczytane pomyslnie\n",filename);
}
void reset_from_file(Tab_of_Cars* tab, const char* filename) {
    FILE* file = fopen(filename,"r");
    if (file == NULL) {
        printf("Nie mozna otworzyc pliku o nazwie: %s!\n",filename);
        return;
    }
    char marka[31],model[21],petrol_type[9];
    int year_of_production,przebieg;
    tab->index_car=0;
    while (fscanf(file,"%30[^;];%20[^;];%d;%ld;%8[^\n]\n",marka,model,&year_of_production,&przebieg,petrol_type)==5){
        tab->car=realloc(tab->car, sizeof(car_info) * (1 + tab->index_car));
        if (tab->car==NULL) {
            printf("Blad alokacji pamieci!\n");
            exit(EXIT_FAILURE);
        }

        strncpy(tab->car[tab->index_car].marka,marka,31);
        strncpy(tab->car[tab->index_car].model,model,21);
        tab->car[tab->index_car].year_of_production=year_of_production;
        tab->car[tab->index_car].przebieg=przebieg;
        strncpy(tab->car[tab->index_car].petrol_type,petrol_type,9);
        tab->index_car++;
    }
    fclose(file);
    printf("Dane z pliku %s zostaly wczytane pomyslnie\n",filename);
}
void clear_memory(Tab_of_Cars* tab) {
    free(tab->car);
    tab->car = NULL;
    tab->index_car = 0;
}

