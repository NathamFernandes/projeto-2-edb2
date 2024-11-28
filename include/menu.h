#ifndef MENU_H
#define MENU_H

#include "handlers.h"
#include "flight.h"

void main_loop(Flight *flights, int *flights_amount);
int render_first_menu();

#endif