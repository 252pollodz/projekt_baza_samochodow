//
// Created by MAFILYW on 12.06.2025.
//

#ifndef CARBASE_H
#define CARBASE_H

typedef struct{
    char marka[31];
    char model[21];
    int year_of_production;
    long przebieg;
    char petrol_type[9];
} car_info;
typedef struct {
    car_info* car;
    int index_car;
} Tab_of_Cars;
void make_cars_table(Tab_of_Cars* tab);
void print_car_info(Tab_of_Cars* tab, int indeks);
void print_cars_info(const Tab_of_Cars* tab);
void add_car(Tab_of_Cars* tab);
void delete_car(Tab_of_Cars* tab, int indeks);
void modify_car(Tab_of_Cars* tab, int indeks);
void clear_memory(Tab_of_Cars* tab);
int empty_check(const Tab_of_Cars* tab);
void filter_options(Tab_of_Cars* tab);
void save_cars_to_file(Tab_of_Cars* tab, const char* filename);
void read_from_file(Tab_of_Cars* tab, const char* filename, int reset);

#endif //CARBASE_H
