#include <stdio.h>
#include <stdlib.h>

#include "carbase.h"


int main() {
    Tab_of_Cars tab;
    make_cars_table(&tab);
    int option;
    printf("Witaj w bazie naszego komisu!\n");
    do
        {
        while (1) {
        printf("\n1. Wyswietl samochody z bazy\n");
        printf("2. Dodaj samochod do bazy\n");
        printf("3. Usun samochod z bazy\n");
        printf("4. Modyfikuj informacje danego pojazdu\n");
        printf("5. Wyszukaj wybrane (filtrowanie)\n");
        printf("6. Zapisz dane do pliku\n");
        printf("7. Dodaj dane z pliku\n");
            printf("8. Zastap danymi z pliku\n");
        printf("0. Exit\n");
        printf("\nWybierz opcje:\n");

            if (scanf("%d", &option)==1) {
                break;
            }else {
                printf("Blad wprowadzania danych, podaj liczbe!");
                while (getchar()!='\n');
            }
        }
        switch (option) {
            case 1:
                if (empty_check(&tab)==1) {
                    break;
                }
                print_cars_info(&tab);
                break;
            case 2:
                add_car(&tab);
                break;
            case 3:
                if (empty_check(&tab)==1) {
                    break;
                }
                int index_of_del;
                while (1) {
                    printf("Podaj indeks auta, ktore chcesz usunac z bazy:");
                    if (scanf("%d", &index_of_del)==1) {
                        delete_car(&tab,index_of_del-1);
                        break;
                    }else {
                        printf("Blad wprowadzania danych, podaj liczbe!\n");
                        while (getchar()!='\n');
                        break;
                    }
                }

                case 4:
                if (empty_check(&tab)==1) {
                    break;
                }
                int index_of_modify;
                while (1) {
                    printf("Podaj indeks auta, ktore chcesz zmodyfikowac:");
                    if (scanf("%d", &index_of_modify)==1) {
                        modify_car(&tab,index_of_modify-1);
                        break;
                    }else {
                        printf("Blad wprowadzania danych, podaj liczbe!");
                        while (getchar()!='\n');
                    }
                }
                break;
            case 5:
                if (empty_check(&tab)==1) {
                    break;
                }
                filter_options(&tab);
                break;
            case 6:
                if (empty_check(&tab)==1) {
                    break;
                }
                char write_filename[30];
                printf("Podaj nazwe pliku do zapisu:");
                scanf("%s", write_filename);
                save_cars_to_file(&tab,write_filename);
                break;
            case 7:
                char read_filename[30];
                printf("Podaj nazwe pliku do odczytu:");
                scanf("%s", read_filename);
                read_from_file(&tab,read_filename);
                break;
            case 8:
                char read2_filename[30];
                printf("Podaj nazwe pliku do odczytu:");
                scanf("%s", read2_filename);
                clear_memory(&tab);
                make_cars_table(&tab);
                reset_from_file(&tab,read2_filename);
                break;
            case 0:
                clear_memory(&tab);
             break;
        default:
        printf("Zly wybor!\n");
        }
    } while (option != 0);


}