#include <ncurses.h>
#include <sstream>
#include <unistd.h>
#include <cmath>
#include <iostream>

#include "game_events.h"
#include "io.h"

void bug_bounty()
{
    Pokemon p_list[50];
    string s;

    for(int i = 0; i < 50; i++)
    {
        p_list[i] = Pokemon(1);
        s = "Species: " + string(p_list[i].get_species()) + " Gender:" + string(p_list[i].get_gender_string());
        mvprintw(i, 0, s.c_str());

    }
}

WINDOW *make_screen(string title)
{
    // display some kind of screen to prompt the pc to choose a pokemon
    WINDOW *starting_pokemon = newwin(24, 80, 0, 0);
    keypad(starting_pokemon, true);
    box(starting_pokemon, 0, 0);
    mvwprintw(starting_pokemon, 1, 1, title.c_str());
    wmove(starting_pokemon, 2, 1);
    whline(starting_pokemon, '-', 78);
    refresh();

    return starting_pokemon;
}

void print_starter_info(Pokemon p_list[3])
{
    // display some kind of screen to prompt the pc to choose a pokemon
    WINDOW *starting_pokemon = make_screen("CHOOSE YOUR STARTING POKEMON:");
    string s;
    // first pokemon
    mvwprintw(starting_pokemon, 3, 2, "#1");
    s = string(p_list[0].get_species());
    capitalize_string(s);
    s = "SPECIES: " + s;
    mvwprintw(starting_pokemon, 4, 2, s.c_str());
    s = p_list[0].get_gender_string();
    capitalize_string(s);
    s = "GENDER: " + s;
    mvwprintw(starting_pokemon, 5, 2, s.c_str());
    s = to_string(p_list[0].get_level());
    s = "LEVEL: " + s;
    mvwprintw(starting_pokemon, 6, 2, s.c_str());
    s = to_string(p_list[0].get_hp());
    s = "HP: " + s;
    mvwprintw(starting_pokemon, 7, 2, s.c_str());
    // second pokemon
    mvwprintw(starting_pokemon, 9, 2, "#2");
    s = string(p_list[1].get_species());
    capitalize_string(s);
    s = "SPECIES: " + s;
    mvwprintw(starting_pokemon, 10, 2, s.c_str());
    s = p_list[1].get_gender_string();
    capitalize_string(s);
    s = "GENDER: " + s;
    mvwprintw(starting_pokemon, 11, 2, s.c_str());
    s = to_string(p_list[1].get_level());
    s = "LEVEL: " + s;
    mvwprintw(starting_pokemon, 12, 2, s.c_str());
    s = to_string(p_list[1].get_hp());
    s = "HP: " + s;
    mvwprintw(starting_pokemon, 13, 2, s.c_str());
    // third pokemon
    mvwprintw(starting_pokemon, 15, 2, "#3");
    s = string(p_list[2].get_species());
    capitalize_string(s);
    s = "SPECIES: " + s;
    mvwprintw(starting_pokemon, 16, 2, s.c_str());
    s = string(p_list[2].get_gender_string());
    capitalize_string(s);
    s = "GENDER: " + s;
    mvwprintw(starting_pokemon, 17, 2, s.c_str());
    s = to_string(p_list[2].get_level());
    s = "LEVEL: " + s;
    mvwprintw(starting_pokemon, 18, 2, s.c_str());
    s = to_string(p_list[2].get_hp());
    s = "HP: " + s;
    mvwprintw(starting_pokemon, 19, 2, s.c_str());
    // prompt the user
    mvwprintw(starting_pokemon, 22, 13, "ENTER THE NUMBER OF THE POKEMON TO VIEW ITS STATS: ");
    // display these messages on screen
    wrefresh(starting_pokemon);
}

void print_basic_pokemon_info(Pokemon p, int p_num, WINDOW *menu)
{
    int spacing_y, spacing_x;
    // display some kind of screen to prompt the pc to choose a pokemon
    string s;
    switch(p_num % 6) {
        case 0:
            spacing_y = 3;
            spacing_x = 2;
            break;
        case 1:
            spacing_y = 9;
            spacing_x = 2;
            break;
        case 2:
            spacing_y = 15;
            spacing_x = 2;
            break;
        case 3:
            spacing_y = 3;
            spacing_x = 41;
            break;
        case 4:
            spacing_y = 9;
            spacing_x = 41;
            break;
        case 5:
            spacing_y = 15;
            spacing_x = 41;
            break;
        default: // error
            return;
    }
    
    // display the names, genders, and level of the trainer's pokemon
    s = "#" + to_string(p_num + 1); 
    mvwprintw(menu, spacing_y++, spacing_x, s.c_str());
    s = p.get_species();
    capitalize_string(s);
    s = "SPECIES: " + s;
    mvwprintw(menu, spacing_y++, spacing_x, s.c_str());
    s = p.get_gender_string();
    capitalize_string(s);
    s = "GENDER: " + s;
    mvwprintw(menu, spacing_y++, spacing_x, s.c_str());
    s = "LEVEL: " + to_string(p.get_level());
    mvwprintw(menu, spacing_y++, spacing_x, s.c_str());
    s = "HP: " + to_string(p.get_current_hp()) + "/" + to_string(p.get_hp());
    mvwprintw(menu, spacing_y++, spacing_x, s.c_str());

    // prompt the user
    mvwprintw(menu, 21, 14, "ENTER THE NUMBER OF THE POKEMON TO VIEW ITS STATS:");
    mvwprintw(menu, 22, 17, "PRESS THE ESCAPE BUTTON TO EXIT THIS WINDOW:");
}

void print_pokemon_starter_stats(Pokemon p)
{
    string s = p.get_species();
    for(int i = 0; i < s.length(); i++) {
        s[i] = toupper(s[i]);
    }
    s += "'S STATS:";
    WINDOW *starting_pokemon = make_screen(s);
    // display gender, level, and shiny status
    s = p.get_gender_string();
    capitalize_string(s);
    s = "GENDER: " + s;
    mvwprintw(starting_pokemon, 3, 2, s.c_str());
    s = to_string(p.get_level());
    capitalize_string(s);
    s = "LEVEL: " + s;
    mvwprintw(starting_pokemon, 3, 32, s.c_str());
    if (p.is_shiny()) s = "SHINY: YES";
    else s = "SHINY: NO";
    mvwprintw(starting_pokemon, 3, 62, s.c_str());
    // display hp, atk, and def
    s = to_string(p.get_hp());
    capitalize_string(s);
    s = "MAX HP: " + s;
    mvwprintw(starting_pokemon, 4, 62, s.c_str());
    s = to_string(p.get_atk());
    capitalize_string(s);
    s = "ATK: " + s;
    mvwprintw(starting_pokemon, 4, 2, s.c_str());
    s = to_string(p.get_def());
    capitalize_string(s);
    s = "DEF: " + s;
    mvwprintw(starting_pokemon, 4, 32, s.c_str());
    // display spatk, spdef, and speed
    s = to_string(p.get_spatk());
    capitalize_string(s);
    s = "SPATK: " + s;
    mvwprintw(starting_pokemon, 5, 62, s.c_str());
    s = to_string(p.get_spdef());
    capitalize_string(s);
    s = "SPDEF: " + s;
    mvwprintw(starting_pokemon, 5, 2, s.c_str());
    s = to_string(p.get_speed());
    capitalize_string(s);
    s = "SPEED: " + s;
    mvwprintw(starting_pokemon, 5, 32, s.c_str());
    // display first 3 IV values
    s = to_string(p.get_iv(0));
    capitalize_string(s);
    s = "HP IV: " + s;
    mvwprintw(starting_pokemon, 6, 62, s.c_str());
    s = to_string(p.get_iv(1));
    capitalize_string(s);
    s = "ATK IV: " + s;
    mvwprintw(starting_pokemon, 6, 2, s.c_str());
    s = to_string(p.get_iv(2));
    capitalize_string(s);
    s = "DEF IV: " + s;
    mvwprintw(starting_pokemon, 6, 32, s.c_str());
    // display last 3 IV values
    s = to_string(p.get_iv(3));
    capitalize_string(s);
    s = "SPATK IV: " + s;
    mvwprintw(starting_pokemon, 7, 62, s.c_str());
    s = to_string(p.get_iv(4));
    capitalize_string(s);
    s = "SPDEF IV: " + s;
    mvwprintw(starting_pokemon, 7, 2, s.c_str());
    s = to_string(p.get_iv(5));
    capitalize_string(s);
    s = "SPEED IV: " + s;
    mvwprintw(starting_pokemon, 7, 32, s.c_str());
    // make line and title for moves section
    wmove(starting_pokemon, 9, 1);
    whline(starting_pokemon, '-', 78);
    s = p.get_species();
    for(int i = 0; i < s.length(); i++) {
        s[i] = toupper(s[i]);
    }
    s += "'S KNOWN MOVES:";
    mvwprintw(starting_pokemon, 10, 1, s.c_str());
    wmove(starting_pokemon, 11, 1);
    whline(starting_pokemon, '-', 78);
    // display moves
    s = p.get_move(0);
    capitalize_string(s);
    s = "MOVE 1: " + s;
    mvwprintw(starting_pokemon, 12, 2, s.c_str());
    s = p.get_move(1);
    capitalize_string(s);
    s = "MOVE 2: " + s;
    mvwprintw(starting_pokemon, 12, 41, s.c_str());
    s = p.get_move(2);
    capitalize_string(s);
    s = "MOVE 3: " + s;
    mvwprintw(starting_pokemon, 13, 2, s.c_str());
    s = p.get_move(3);
    capitalize_string(s);
    s = "MOVE 4: " + s;
    mvwprintw(starting_pokemon, 13, 41, s.c_str());
    // prompt the user
    mvwprintw(starting_pokemon, 21, 25, "ENTER 'y' TO SELECT POKEMON:");
    mvwprintw(starting_pokemon, 22, 20, "ENTER 'n' TO RETURN TO ORIGINAL LIST:");
    // refresh the screen
    wrefresh(starting_pokemon);
}

void print_pokemon_stats(Pokemon p)
{
    string s = p.get_species();
    for(int i = 0; i < s.length(); i++) {
        s[i] = toupper(s[i]);
    }
    s += "'S STATS:";
    WINDOW *starting_pokemon = make_screen(s);
    // display gener, level, and shiny status
    s = p.get_gender_string();
    capitalize_string(s);
    s = "GENDER: " + s;
    mvwprintw(starting_pokemon, 3, 2, s.c_str());
    s = to_string(p.get_level());
    capitalize_string(s);
    s = "LEVEL: " + s;
    mvwprintw(starting_pokemon, 3, 32, s.c_str());
    if (p.is_shiny()) s = "SHINY: YES";
    else s = "SHINY: NO";
    mvwprintw(starting_pokemon, 3, 62, s.c_str());
    // display hp, atk, and def
    s = to_string(p.get_current_hp()) + "/" + to_string(p.get_hp());
    s = "HP: " + s;
    mvwprintw(starting_pokemon, 4, 62, s.c_str());
    s = to_string(p.get_atk());
    capitalize_string(s);
    s = "ATK: " + s;
    mvwprintw(starting_pokemon, 4, 2, s.c_str());
    s = to_string(p.get_def());
    capitalize_string(s);
    s = "DEF: " + s;
    mvwprintw(starting_pokemon, 4, 32, s.c_str());
    // display spatk, spdef, and speed
    s = to_string(p.get_spatk());
    capitalize_string(s);
    s = "SPATK: " + s;
    mvwprintw(starting_pokemon, 5, 62, s.c_str());
    s = to_string(p.get_spdef());
    capitalize_string(s);
    s = "SPDEF: " + s;
    mvwprintw(starting_pokemon, 5, 2, s.c_str());
    s = to_string(p.get_speed());
    capitalize_string(s);
    s = "SPEED: " + s;
    mvwprintw(starting_pokemon, 5, 32, s.c_str());
    // display first 3 IV values
    s = to_string(p.get_iv(0));
    capitalize_string(s);
    s = "HP IV: " + s;
    mvwprintw(starting_pokemon, 6, 62, s.c_str());
    s = to_string(p.get_iv(1));
    capitalize_string(s);
    s = "ATK IV: " + s;
    mvwprintw(starting_pokemon, 6, 2, s.c_str());
    s = to_string(p.get_iv(2));
    capitalize_string(s);
    s = "DEF IV: " + s;
    mvwprintw(starting_pokemon, 6, 32, s.c_str());
    // display last 3 IV values
    s = to_string(p.get_iv(3));
    capitalize_string(s);
    s = "SPATK IV: " + s;
    mvwprintw(starting_pokemon, 7, 62, s.c_str());
    s = to_string(p.get_iv(4));
    capitalize_string(s);
    s = "SPDEF IV: " + s;
    mvwprintw(starting_pokemon, 7, 2, s.c_str());
    s = to_string(p.get_iv(5));
    capitalize_string(s);
    s = "SPEED IV: " + s;
    mvwprintw(starting_pokemon, 7, 32, s.c_str());
    // make line and title for moves section
    wmove(starting_pokemon, 9, 1);
    whline(starting_pokemon, '-', 78);
    s = p.get_species();
    for(int i = 0; i < s.length(); i++) {
        s[i] = toupper(s[i]);
    }
    s += "'S KNOWN MOVES:";
    mvwprintw(starting_pokemon, 10, 1, s.c_str());
    wmove(starting_pokemon, 11, 1);
    whline(starting_pokemon, '-', 78);
    // display moves
    s = p.get_move(0);
    capitalize_string(s);
    s = "MOVE 1: " + s;
    mvwprintw(starting_pokemon, 12, 2, s.c_str());
    s = p.get_move(1);
    capitalize_string(s);
    s = "MOVE 2: " + s;
    mvwprintw(starting_pokemon, 12, 41, s.c_str());
    s = p.get_move(2);
    capitalize_string(s);
    s = "MOVE 3: " + s;
    mvwprintw(starting_pokemon, 13, 2, s.c_str());
    s = p.get_move(3);
    capitalize_string(s);
    s = "MOVE 4: " + s;
    mvwprintw(starting_pokemon, 13, 41, s.c_str());
    // prompt the user
    mvwprintw(starting_pokemon, 22, 20, "ENTER 'b' TO RETURN TO ORIGINAL LIST:");
    // refresh the screen
    wrefresh(starting_pokemon);
}

void print_pokemon_list()
{
    int key = 0;
    WINDOW *menu = make_screen("YOUR CURRENT POKEMON:");
    for (int i = 0; i < world.pc.num_pokemon; i++) {
    print_basic_pokemon_info(world.pc.p_list[i], i, menu);
    }
    wrefresh(menu);
    while(key != 27) {
        // handle user input
        key = getch();
        switch (key)
        {
            case 49: // first pokemon
                if (world.pc.num_pokemon > 0) {
                clear();
                print_pokemon_stats(world.pc.p_list[0]);
                key = getch();
                }
                break;
            case 50: // second pokemon
                if (world.pc.num_pokemon > 1) {
                clear();
                print_pokemon_stats(world.pc.p_list[1]);
                key = getch();
                }
                break;
            case 51: // third pokemon
                if (world.pc.num_pokemon > 2) {
                clear();
                print_pokemon_stats(world.pc.p_list[2]);
                key = getch();
                }
                break;
            case 52: // fourth pokemon
                if (world.pc.num_pokemon > 3) {
                clear();
                print_pokemon_stats(world.pc.p_list[3]);
                key = getch();
                }
                break;
            case 53: // fifth pokemon
                if (world.pc.num_pokemon > 4) {
                clear();
                print_pokemon_stats(world.pc.p_list[4]);
                key = getch();
                }
                break;
            case 54:
                if (world.pc.num_pokemon > 5) {
                clear();
                print_pokemon_stats(world.pc.p_list[5]);
                key = getch();
                }
                break;
            }
        if (key == 'b' || key == 'B') {
            print_pokemon_list();
        }
    }

    io_display();
}

void generate_starting_pokemon(Character *c)
{
    // dynamic cast to later check for type
    Pc *p = dynamic_cast<Pc *> (c);
    Pokemon p_list[3];
    string s;
    int input, temp_i = 110;
    bool chosen = false;
    // first, let's generate our first three pokemon
    p_list[0] = Pokemon(1);
    p_list[1] = Pokemon(1);
    p_list[2] = Pokemon(1);
    // now, let's check if the character is the pc
    if (p){
        // initially set the PC's starting Pokemon as their active pokemon
        p->active_index = 0;
        // print out the basic information about the three starting pokemon
        print_starter_info(p_list);
        // wait for user input and allow user to learn more about each pokemon
        while (!chosen){ // TODO - prevent input from not registering immediately after an incorrect input is entered
         /* 1, 2, or 3 */
            if (!(input == 49 || input == 50 || input == 51 || input == 110 || input == 89) || input == 121 || input == 78) input = temp_i;
            switch (input){
            case 49:
                while (input == 49) {
                temp_i = 49;
                clear();
                print_pokemon_starter_stats(p_list[0]);
                input = getch();
                while (input == 49) input = getch();
                if (input == 121 || input == 89) {
                    world.pc.p_list[0] = p_list[0];
                    chosen = true;
                    io_display();
                }
                else if (input == 110 || input == 78) print_starter_info(p_list);
                else if (input == 50) print_pokemon_starter_stats(p_list[1]);
                else if (input == 51) print_pokemon_starter_stats(p_list[2]);
                else input = 49;
                }
                break;
            case 50:
                while (input == 50) {
                temp_i = 50;
                clear();
                print_pokemon_starter_stats(p_list[1]);
                input = getch();
                while (input == 50) input = getch();
                if (input == 121 || input == 89) {
                    world.pc.p_list[0] = p_list[1];
                    chosen = true;
                    io_display();
                }
                else if (input == 110 || input == 78) print_starter_info(p_list);
                else if (input == 49) print_pokemon_starter_stats(p_list[0]);
                else if (input == 51) print_pokemon_starter_stats(p_list[2]);
                else input = 50;
                }
                break;
            case 51:
                while (input == 51) {
                temp_i = 51;
                clear();
                print_pokemon_starter_stats(p_list[2]);
                input = getch();
                while (input == 51) input = getch();
                if (input == 121 || input == 89) {
                    world.pc.p_list[0] = p_list[2];
                    chosen = true;
                    io_display();
                }
                else if (input == 110 || input == 78) print_starter_info(p_list);
                else if (input == 49) print_pokemon_starter_stats(p_list[0]);
                else if (input == 50) print_pokemon_starter_stats(p_list[1]);
                else input = 51;
                }
                break;
            case 89:
            case 121:
                if (temp_i == 49){
                temp_i = input;
                world.pc.p_list[0] = p_list[0];
                chosen = true;
                io_display();
                }
                else if (temp_i == 50){
                    temp_i = input;
                    world.pc.p_list[0] = p_list[1];
                    chosen = true;
                    io_display();
                }
                else if (temp_i == 51){
                    temp_i = input;
                    world.pc.p_list[0] = p_list[2];
                    chosen = true;
                    io_display();
                }
                break;
            default:
                input = getch();
                break;
            }   
        }
        world.pc.num_pokemon = 1;
    } else{
        // choose the npc's starting pokemon randomly
        c->p_list[0] = p_list[rand() % 3];
        c->num_pokemon = 1;
        // now time to see if trainer will receive more than 1 pokemon
        for (int i = 1; i < 6; i++){
            // 60% chance of adding another pokemon
            switch (rand() % 10){
                case 0:
                case 1:
                case 2:
                case 3:
                case 4:
                case 5:
                case 6:
                    // 6/10 = 60%
                    c->p_list[i] = Pokemon(1);
                    // increment num_pokemon
                    c->num_pokemon++;
                    // if we added another pokemon, keep checking
                    break;
                default:
                    // if we didn't add another pokemon, stop checking
                    return;
            }
        }
        // randomly choose active pokemon for said npc
        c->active_index = rand() % c->num_pokemon;
    }
}

/*
TODO - add selecting moves for PC, randomizing moves for NPC, calculating who to go first, calulcate damage done, update health. Implement bag (and revives,
potions, and Pokeballs), and implement the ability to select a different active Pokemon for the PC, and randomly selecting the active Pokemon for an NPC upon one
of their Pokemon becoming knocked out.
    - Calculating damage should be in its own function.
    - The Pokemon class will now need a setter method to update the current_hp of the Pokemon.
    - Once a Pokemon becomes knocked out, a user should be prompted to select their next active Pokemon.
==================================================================================================================================================================
The idea below this is an example of making simple problems more advanced than they need be. Since swtching to C and C++ I have found myself doing things like
this far too often - bad habits I never realized. Initially, many people might think you might need a vector for each kind of 'item' that exists in the bag,
at least I originally did due to my background with object oriented languages. 
    - The bag can be implemented easily with an array of vectors, 'bag', which would contain a vector for all three kinds of items.
No, it's far more simple than that, and this leads to a more efficient solution.
    - Make an array of ints, int bag[3], and each int within this array will pertain to the number of items you have for each category / item.
    - Handle printing of bag items, and using up items while updating the screena after each use.
    - Create setter methods for 'current_hp' and 'is_defeated' for Pokemon to allow for using revives and potions.
    - Change HP accordingly within 'use_item().'
==================================================================================================================================================================
Switching Pokemon can be made simple by avoiding allowing a user to specify the exact order of their list of Pokemon, meaning that when switching your Pokemon,
these two Pokemon directly swap their locations in your current list. Kind of a lazy solution, but reduces the complexity of the code and is remedied by simply
allowing the PC to select their next Pokemon upon their active Pokemon becoming knocked out during a battle.
*/

int calculate_damage_wild(Pokemon *p, int move_idx)
{
    int random;
    double damage_factor_1 = 1;
    double damage_factor_2 = 1;
    double crit, stab, type;
    stab = 1;
    // Calculate STAB for wild Pokemon, checking if dual-typed
    if (pokemon_types[p->get_species_idx() + 1].slot == 2) {
        if (moves[move_idx].type_id == pokemon_types[p->get_species_idx()].type_id || moves[move_idx].type_id == pokemon_types[p->get_species_idx() + 1].type_id) {
            stab = 1.5;
        }
    } else {
        if (moves[move_idx].type_id == pokemon_types[p->get_species_idx()].type_id) stab = 1.5;
    }
    // Calculate effectiveness based on PC's active Pokemon, checking if dual typed
    if (pokemon_types[world.pc.p_list[0].get_species_idx() + 1].slot == 2) {
        if (moves[move_idx].type_id == pokemon_types[world.pc.p_list[0].get_species_idx()].type_id) {
            stab = 1.5;
            for (int i = (moves[move_idx].type_id - 1 * 18) + moves[move_idx].type_id; i < 19 * moves[move_idx].type_id; i++) {
                if (type_efficacy[i].target_type_id == pokemon_types[world.pc.p_list[0].get_species_idx()].type_id) {
                    damage_factor_1 = type_efficacy[i].damage_factor / 100;
                }
            }
        }
        // checking dual-typed
        if (moves[move_idx].type_id == pokemon_types[world.pc.p_list[0].get_species_idx() + 1].type_id) {
            for (int i = (moves[move_idx].type_id - 1 * 18) + moves[move_idx].type_id; i < 19 * moves[move_idx].type_id; i++) {
                if (type_efficacy[i].target_type_id == pokemon_types[world.pc.p_list[0].get_species_idx() + 1].type_id) {
                    damage_factor_2 = type_efficacy[i].damage_factor / 100;
                }
            }
        }
    } else {
        if (moves[move_idx].type_id == pokemon_types[world.pc.p_list[0].get_species_idx()].type_id) {
            for (int i = (moves[move_idx].type_id - 1 * 18) + moves[move_idx].type_id; i < 19 * moves[move_idx].type_id; i++) {
                if (type_efficacy[i].target_type_id == pokemon_types[world.pc.p_list[0].get_species_idx()].type_id) {
                    damage_factor_1 = type_efficacy[i].damage_factor / 100;
                }
            }
        }
    }

    if (rand() % 256 < (p->get_base_speed() / 2)) crit = 1.5;
    else crit = 1;
    random = (rand() % 16) + 85;
    type = damage_factor_1 * damage_factor_2;

    return (((((((2 * p->get_level()) / 5) + 2) * moves[move_idx].power * (p->get_atk() / p->get_def())) / 50) + 2) * crit * random * stab * type);
}

int calculate_damage_npc(Pokemon p, int move_idx)
{
    int random;
    double damage_factor_1 = 1;
    double damage_factor_2 = 1;
    double crit, stab, type;
    stab = 1;
    if (pokemon_types[p.get_species_idx() + 1].slot == 2) {
        if (moves[move_idx].type_id == pokemon_types[p.get_species_idx()].type_id || moves[move_idx].type_id == pokemon_types[p.get_species_idx() + 1].type_id) {
            stab = 1.5;
        }
    } else {
        if (moves[move_idx].type_id == pokemon_types[p.get_species_idx()].type_id) stab = 1.5;
    }

    // Calculate effectiveness based on PC's active Pokemon, checking if dual typed
    if (pokemon_types[world.pc.p_list[0].get_species_idx() + 1].slot == 2) {
        if (moves[move_idx].type_id == pokemon_types[world.pc.p_list[0].get_species_idx()].type_id) {
            stab = 1.5;
            for (int i = (moves[move_idx].type_id - 1 * 18) + moves[move_idx].type_id; i < 19 * moves[move_idx].type_id; i++) {
                if (type_efficacy[i].target_type_id == pokemon_types[world.pc.p_list[0].get_species_idx()].type_id) {
                    damage_factor_1 = type_efficacy[i].damage_factor / 100;
                }
            }
        }
        // checking dual-typed
        if (moves[move_idx].type_id == pokemon_types[world.pc.p_list[0].get_species_idx() + 1].type_id) {
            for (int i = (moves[move_idx].type_id - 1 * 18) + moves[move_idx].type_id; i < 19 * moves[move_idx].type_id; i++) {
                if (type_efficacy[i].target_type_id == pokemon_types[world.pc.p_list[0].get_species_idx() + 1].type_id) {
                    damage_factor_2 = type_efficacy[i].damage_factor / 100;
                }
            }
        }
    } else {
        if (moves[move_idx].type_id == pokemon_types[world.pc.p_list[0].get_species_idx()].type_id) {
            for (int i = (moves[move_idx].type_id - 1 * 18) + moves[move_idx].type_id; i < 19 * moves[move_idx].type_id; i++) {
                if (type_efficacy[i].target_type_id == pokemon_types[world.pc.p_list[0].get_species_idx()].type_id) {
                    damage_factor_1 = type_efficacy[i].damage_factor / 100;
                }
            }
        }
    }

    if (rand() % 256 < (p.get_base_speed() / 2)) crit = 1.5;
    else crit = 1;
    random = (rand() % 16) + 85;
    type = damage_factor_1 * damage_factor_2;

    return (((((((2 * p.get_level()) / 5) + 2) * moves[move_idx].power * (p.get_atk() / p.get_def())) / 50) + 2) * crit * random * stab * type);
}

int calculate_damage_pc(int move_idx, Pokemon target)
{
    int random;
    double damage_factor_1 = 1;
    double damage_factor_2 = 1;
    double crit, stab, type;
    stab = 1;
    if (pokemon_types[world.pc.p_list[0].get_species_idx() + 1].slot == 2) {
        if (moves[move_idx].type_id == pokemon_types[world.pc.p_list[0].get_species_idx()].type_id || moves[move_idx].type_id == pokemon_types[world.pc.p_list[0].get_species_idx() + 1].type_id) {
            stab = 1.5;
        }
    } else {
        if (moves[move_idx].type_id == pokemon_types[world.pc.p_list[0].get_species_idx()].type_id) stab = 1.5;
    }

    // Calculate effectiveness target Pokemon, checking if dual typed
    if (pokemon_types[target.get_species_idx() + 1].slot == 2) {
        if (moves[move_idx].type_id == pokemon_types[target.get_species_idx()].type_id) {
            stab = 1.5;
            for (int i = (moves[move_idx].type_id - 1 * 18) + moves[move_idx].type_id; i < 19 * moves[move_idx].type_id; i++) {
                if (type_efficacy[i].target_type_id == pokemon_types[target.get_species_idx()].type_id) {
                    damage_factor_1 = type_efficacy[i].damage_factor / 100;
                }
            }
        }
        // checking dual-typed
        if (moves[move_idx].type_id == pokemon_types[target.get_species_idx() + 1].type_id) {
            for (int i = (moves[move_idx].type_id - 1 * 18) + moves[move_idx].type_id; i < 19 * moves[move_idx].type_id; i++) {
                if (type_efficacy[i].target_type_id == pokemon_types[target.get_species_idx() + 1].type_id) {
                    damage_factor_2 = type_efficacy[i].damage_factor / 100;
                }
            }
        }
    } else {
        if (moves[move_idx].type_id == pokemon_types[target.get_species_idx()].type_id) {
            for (int i = (moves[move_idx].type_id - 1 * 18) + moves[move_idx].type_id; i < 19 * moves[move_idx].type_id; i++) {
                if (type_efficacy[i].target_type_id == pokemon_types[target.get_species_idx()].type_id) {
                    damage_factor_1 = type_efficacy[i].damage_factor / 100;
                }
            }
        }
    }

    if (rand() % 256 < (world.pc.p_list[0].get_base_speed() / 2)) crit = 1.5;
    else crit = 1;
    random = (rand() % 16) + 85;
    type = damage_factor_1 * damage_factor_2;

    return (((((((2 * world.pc.p_list[0].get_level()) / 5) + 2) * moves[move_idx].power * (world.pc.p_list[0].get_atk() / world.pc.p_list[0].get_def())) / 50) + 2) * crit * random * stab * type);
}

void print_pokemon_battle(Pokemon *p)
{
    bool is_over = false;
    int input, escape_attempts, wild_dmg, pc_dmg, wild_move_idx, pc_move_idx;
    escape_attempts = 0;
    string s = p->get_species();
    // int pc_dmg, wild_dmg = 0;
    for(int i = 0; i < s.length(); i++) {
        s[i] = toupper(s[i]);
    }
    s = "A WILD " + s + " HAS APPEARED!";
    WINDOW *menu = make_screen(s);

    // display level, hp, and gender of wild Pokemon
    s = to_string(p->get_level());
    capitalize_string(s);
    s = "LEVEL: " + s;
    mvwprintw(menu, 3, 2, s.c_str());
    s = "HP: " + to_string(p->get_current_hp()) + "/" + to_string(p->get_hp());
    mvwprintw(menu, 3, 32, s.c_str());
    s = string(p->get_gender_string());
    capitalize_string(s);
    s = "GENDER: " + s;
    mvwprintw(menu, 3, 62, s.c_str());

    // print PC's active pokemon info
    wmove(menu, 8, 1);
    whline(menu, '-', 78);
    s = "YOUR ACTIVE POKEMON: " + string(world.pc.p_list[0].get_species());
    for(int i = 0; i < s.length(); i++) {
        s[i] = toupper(s[i]);
    }
    mvwprintw(menu, 9, 1, s.c_str());
    wmove(menu, 10, 1);
    whline(menu, '-', 78);
    // print level, hp, and gender of PC's pokemon
    s = to_string(world.pc.p_list[world.pc.active_index].get_level());
    capitalize_string(s);
    s = "LEVEL: " + s;
    mvwprintw(menu, 11, 2, s.c_str());
    s = "HP: " + to_string(world.pc.p_list[0].get_current_hp()) + "/" + to_string(world.pc.p_list[0].get_hp());
    mvwprintw(menu, 11, 32, s.c_str());
    s = world.pc.p_list[world.pc.active_index].get_gender_string();
    capitalize_string(s);
    s = "GENDER: " + s;
    mvwprintw(menu, 11, 62, s.c_str());

    // print PC's active Pokemon moves
    s = world.pc.p_list[world.pc.active_index].get_move(0);
    capitalize_string(s);
    s = "MOVE 1: " + s;
    mvwprintw(menu, 13, 2, s.c_str());
    s = world.pc.p_list[world.pc.active_index].get_move(1);
    capitalize_string(s);
    s = "MOVE 2: " + s;
    mvwprintw(menu, 13, 32, s.c_str());
    s = world.pc.p_list[world.pc.active_index].get_move(2);
    capitalize_string(s);
    s = "MOVE 3: " + s;
    mvwprintw(menu, 15, 2, s.c_str());
    s = world.pc.p_list[world.pc.active_index].get_move(3);
    capitalize_string(s);
    s = "MOVE 4: " + s;
    mvwprintw(menu, 15, 32, s.c_str());

    // prompt the user
    mvwprintw(menu, 19, 19, "ENTER THE NUMBER OF THE MOVE TO USE IT:");
    mvwprintw(menu, 20, 24, "ENTER 'r' TO TRY AND RUN AWAY:");
    mvwprintw(menu, 21, 26, "ENTER 'b' TO OPEN YOUR BAG:");
    mvwprintw(menu, 22, 19, "ENTER 's' TO SWITCH YOUR ACTIVE POKEMON:");
    // refresh the screen
    wrefresh(menu);
    // handle input
    while (!is_over) {
        // need to randomly select a wild Pokemon's next move.
        do {
            wild_dmg = rand() % 4;
        }
        while (string(p->get_move(wild_dmg)) == "-");
        wild_move_idx = p->get_move_id(wild_dmg);
        wild_dmg = calculate_damage_wild(p, wild_move_idx);
        // handle input
        input = getch();
        switch (input) {
        case 82: // R
        case 114: // r
            escape_attempts++;
            if (((world.pc.p_list[world.pc.active_index].get_speed() * 32) / ((p->get_speed() / 4) % 256) + 30 * escape_attempts) > 255) {
                is_over = true;
                return;
            }
            else {
                wattron(menu, COLOR_PAIR(COLOR_RED));
                mvwprintw(menu, 18, 32, "CAN'T ESCAPE!");
                wattroff(menu, COLOR_PAIR(COLOR_RED));
                wrefresh(menu);
                usleep(2500000);
                wmove(menu, 18, 1);
                whline(menu, ' ', 78);
                wrefresh(menu);
            }
            break;
        case 66: // B
        case 98: // b
            wmove(menu, 18, 1);
            whline(menu, ' ', 78);
            print_bag(menu);
            print_pokemon_encounter(p);
            return;
        case 83: // S
        case 115: // s
            wmove(menu, 18, 1);
            whline(menu, ' ', 78);
            print_switch_pokemon(menu);
            print_pokemon_encounter(p);
            return;
        case 49: // 1
            if (string(world.pc.p_list[0].get_move(0)) == "-") pc_dmg = 0;
            else {
                pc_move_idx = world.pc.p_list[0].get_move_id(0);
                pc_dmg = calculate_damage_pc(pc_move_idx, *p);
            }
            break;
        case 50: // 2
            if (string(world.pc.p_list[0].get_move(1)) == "-") pc_dmg = 0;
            else {
                pc_move_idx = world.pc.p_list[0].get_move_id(1);
                pc_dmg = calculate_damage_pc(pc_move_idx, *p);
            }
            break;
        case 51: // 3
            if (string(world.pc.p_list[0].get_move(2)) == "-") pc_dmg = 0;
            else {
                pc_move_idx = world.pc.p_list[0].get_move_id(2);
                pc_dmg = calculate_damage_pc(pc_move_idx, *p);
            }
            break;
        case 52: // 4
            if (string(world.pc.p_list[0].get_move(3)) == "-") pc_dmg = 0;
            else {
                pc_move_idx = world.pc.p_list[0].get_move_id(3);
                pc_dmg = calculate_damage_pc(pc_move_idx, *p);
            }
            break;
        default:
            pc_dmg = 0;
            pc_move_idx = 0;
            break;
        }

        // check if PC elected to not choose a move
        if (pc_dmg == 0) {
            if (rand() % 100 < moves[wild_move_idx].accuracy) {
                // move hits
                world.pc.p_list[0].set_current_hp(world.pc.p_list[0].get_current_hp() - wild_dmg);
                if (world.pc.p_list[0].get_current_hp() <= 0) {
                    world.pc.p_list[0].set_is_defeated(true);
                    world.pc.p_list[0].set_current_hp(0);
                    // prompt user to switch active Pokemon
                }
            } else {
                wmove(menu, 18, 1);
                whline(menu, ' ', 78);
                wattron(menu, COLOR_PAIR(COLOR_RED));
                mvwprintw(menu, 18, 25, "WILD POKEMON'S MOVE MISSED!");
                wattroff(menu, COLOR_PAIR(COLOR_RED));
                wrefresh(menu);
                usleep(2500000);
                wmove(menu, 18, 1);
                whline(menu, ' ', 78);
                wrefresh(menu);
            }
        } else {
                if (moves[pc_move_idx].priority > moves[wild_move_idx].priority) {
                // PC move goes first
                // need to calculate if move hits
                if (rand() % 100 < moves[pc_move_idx].accuracy) {
                    // move hits
                    p->set_current_hp(p->get_current_hp() - pc_dmg);
                    if (p->get_current_hp() <= 0) {
                        p->set_is_defeated(true);
                        p->set_current_hp(0);
                    }
                } else {
                    wmove(menu, 18, 1);
                    whline(menu, ' ', 78);
                    wattron(menu, COLOR_PAIR(COLOR_RED));
                    mvwprintw(menu, 18, 30, "YOUR MOVE MISSED!");
                    wattroff(menu, COLOR_PAIR(COLOR_RED));
                    wrefresh(menu);
                    usleep(2500000);
                    wmove(menu, 18, 1);
                    whline(menu, ' ', 78);
                    wrefresh(menu);
                }
            }
            else if (moves[pc_move_idx].priority < moves[wild_move_idx].priority) {
                // wild Pokemon goes first
                // need to calculate if move hits
                if (rand() % 100 < moves[wild_move_idx].accuracy) {
                    // move hits
                    world.pc.p_list[0].set_current_hp(world.pc.p_list[0].get_current_hp() - wild_dmg);
                    if (world.pc.p_list[0].get_current_hp() <= 0) {
                        world.pc.p_list[0].set_is_defeated(true);
                        world.pc.p_list[0].set_current_hp(0);
                        // prompt user to switch active Pokemon
                    }
                } else {
                    wmove(menu, 18, 1);
                    whline(menu, ' ', 78);
                    wattron(menu, COLOR_PAIR(COLOR_RED));
                    mvwprintw(menu, 18, 25, "WILD POKEMON'S MOVE MISSED!");
                    wattroff(menu, COLOR_PAIR(COLOR_RED));
                    wrefresh(menu);
                    usleep(2500000);
                    wmove(menu, 18, 1);
                    whline(menu, ' ', 78);
                    wrefresh(menu);
                }
            }
            else if (moves[pc_move_idx].priority == moves[wild_move_idx].priority) {
                // move priorities are equal
                if (world.pc.p_list[0].get_speed() > p->get_speed()) {
                    // PC move goes first based on Pokemon's speed
                    // need to calculate if move hits
                    if (rand() % 100 < moves[pc_move_idx].accuracy) {
                        // move hits
                        p->set_current_hp(p->get_current_hp() - pc_dmg);
                        if (p->get_current_hp() <= 0) {
                            p->set_is_defeated(true);
                            p->set_current_hp(0);
                        }
                    } else {
                        wmove(menu, 18, 1);
                        whline(menu, ' ', 78);
                        wattron(menu, COLOR_PAIR(COLOR_RED));
                        mvwprintw(menu, 18, 30, "YOUR MOVE MISSED!");
                        wattroff(menu, COLOR_PAIR(COLOR_RED));
                        wrefresh(menu);
                        usleep(2500000);
                        wmove(menu, 18, 1);
                        whline(menu, ' ', 78);
                        wrefresh(menu);
                    }
                } else if (world.pc.p_list[0].get_speed() > p->get_speed()) {
                    // wild Pokemon move goes first based on Pokemon's speed
                    // need to calculate if move hits
                    if (rand() % 100 < moves[wild_move_idx].accuracy) {
                        // move hits
                        world.pc.p_list[0].set_current_hp(world.pc.p_list[0].get_current_hp() - wild_dmg);
                        if (world.pc.p_list[0].get_current_hp() <= 0) {
                            world.pc.p_list[0].set_is_defeated(true);
                            world.pc.p_list[0].set_current_hp(0);
                            // prompt user to switch active Pokemon
                        }
                    } else {
                        wmove(menu, 18, 1);
                        whline(menu, ' ', 78);
                        wattron(menu, COLOR_PAIR(COLOR_RED));
                        mvwprintw(menu, 18, 25, "WILD POKEMON'S MOVE MISSED!");
                        wattroff(menu, COLOR_PAIR(COLOR_RED));
                        wrefresh(menu);
                        usleep(2500000);
                        wmove(menu, 18, 1);
                        whline(menu, ' ', 78);
                        wrefresh(menu);
                    }
                }
                else {
                    // if Pokemon speeds are equal, choose at random for first move
                    if (rand() % 2 == 0) {
                        // PC move goes first
                        // need to calculate if move hits
                        if (rand() % 100 < moves[pc_move_idx].accuracy) {
                            // move hits
                            p->set_current_hp(p->get_current_hp() - pc_dmg);
                            if (p->get_current_hp() <= 0) {
                                p->set_is_defeated(true);
                                p->set_current_hp(0);
                            }
                        } else {
                            wmove(menu, 18, 1);
                            whline(menu, ' ', 78);
                            wattron(menu, COLOR_PAIR(COLOR_RED));
                            mvwprintw(menu, 18, 30, "YOUR MOVE MISSED!");
                            wattroff(menu, COLOR_PAIR(COLOR_RED));
                            wrefresh(menu);
                            usleep(2500000);
                            wmove(menu, 18, 1);
                            whline(menu, ' ', 78);
                            wrefresh(menu);
                        }
                    } else {
                        // wild Pokemon move goes first
                        // need to calculate if move hits
                        if (rand() % 100 < moves[wild_move_idx].accuracy) {
                            // move hits
                            world.pc.p_list[0].set_current_hp(world.pc.p_list[0].get_current_hp() - wild_dmg);
                            if (world.pc.p_list[0].get_current_hp() <= 0) {
                                world.pc.p_list[0].set_is_defeated(true);
                                world.pc.p_list[0].set_current_hp(0);
                                // prompt user to switch active Pokemon
                            }
                        } else {
                            wmove(menu, 18, 1);
                            whline(menu, ' ', 78);
                            wattron(menu, COLOR_PAIR(COLOR_RED));
                            mvwprintw(menu, 18, 25, "WILD POKEMON'S MOVE MISSED!");
                            wattroff(menu, COLOR_PAIR(COLOR_RED));
                            wrefresh(menu);
                            usleep(2500000);
                            wmove(menu, 18, 1);
                            whline(menu, ' ', 78);
                            wrefresh(menu);
                        }
                    }
                }
            }
        }

        // update screen
        wmove(menu, 3, 32);
        whline(menu, ' ', 47);
        s = "HP: " + to_string(p->get_current_hp()) + "/" + to_string(p->get_hp());
        mvwprintw(menu, 3, 32, s.c_str());
        s = string(p->get_gender_string());
        capitalize_string(s);
        s = "GENDER: " + s;
        mvwprintw(menu, 3, 62, s.c_str());
        wmove(menu, 11, 32);
        whline(menu, ' ', 47);
        s = "HP: " + to_string(world.pc.p_list[0].get_current_hp()) + "/" + to_string(world.pc.p_list[0].get_hp());
        mvwprintw(menu, 11, 32, s.c_str());
        s = world.pc.p_list[world.pc.active_index].get_gender_string();
        capitalize_string(s);
        s = "GENDER: " + s;
        mvwprintw(menu, 11, 62, s.c_str());
        wrefresh(menu);
        if (p->is_defeated()) {
            // inform user they have captured Pokemon
            wmove(menu, 18, 1);
            whline(menu, ' ', 78);
            wattron(menu, COLOR_PAIR(COLOR_RED));
            mvwprintw(menu, 18, 30, "POKEMON CAPTURED!");
            wattroff(menu, COLOR_PAIR(COLOR_RED));
            wrefresh(menu);
            usleep(2500000);
            // decrement number of Pokeballs
            use_item(2, 0);
            // add wild Pokemon to PC's p_list
            if (world.pc.num_pokemon < 6) {
                world.pc.p_list[world.pc.num_pokemon] = *p;
                // world.pc.p_list[world.pc.num_pokemon].set_current_hp(world.pc.p_list[world.pc.num_pokemon].get_hp());
                world.pc.num_pokemon++;
            }
            else {
                // inform user they already have six Pokemon
                wmove(menu, 18, 1);
                whline(menu, ' ', 78);
                wattron(menu, COLOR_PAIR(COLOR_RED));
                mvwprintw(menu, 18, 20, "YOU HAVE ALREADY CAPTURED SIX POKEMON!");
                wattroff(menu, COLOR_PAIR(COLOR_RED));
                wrefresh(menu);
                usleep(2500000);
                wmove(menu, 18, 1);
                whline(menu, ' ', 78);
                wattron(menu, COLOR_PAIR(COLOR_RED));
                mvwprintw(menu, 18, 8, "THIS WILD POKEMON CAN BE FOUND IN YOUR POKEDEX AT POKECENTERS!");
                wattroff(menu, COLOR_PAIR(COLOR_RED));
                wrefresh(menu);
                usleep(2500000);
                // add wild Pokemon to PC's Pokedex
                p->set_is_defeated(false);
                p->set_current_hp(p->get_hp());
                world.pc.pokedex.push_back(*p);
            }
            usleep(2500000);
            is_over = true;
        }
        else if (world.pc.p_list[0].is_defeated()) {
            // inform user that their active Pokemon has been defeated
            wmove(menu, 18, 1);
            whline(menu, ' ', 78);
            wattron(menu, COLOR_PAIR(COLOR_RED));
            mvwprintw(menu, 18, 22, "ACTIVE POKEMON HAS BEEN DEFEATED!");
            wattroff(menu, COLOR_PAIR(COLOR_RED));
            wrefresh(menu);
            usleep(2500000);
            wmove(menu, 18, 1);
            whline(menu, ' ', 78);
            // check if all of PC's Pokemon are defeated
            int count = 0;
            for (int i = 0; i < world.pc.num_pokemon; i++) {
                if (world.pc.p_list[i].is_defeated()) count++;
            }
            if (count == world.pc.num_pokemon) {
                wmove(menu, 18, 1);
                whline(menu, ' ', 78);
                is_over = true;
                wattron(menu, COLOR_PAIR(COLOR_RED));
                mvwprintw(menu, 18, 27, "YOU HAVE BEEN DEFEATED!");
                wattroff(menu, COLOR_PAIR(COLOR_RED));
                wrefresh(menu);
                usleep(2500000);
                wmove(menu, 18, 1);
                whline(menu, ' ', 78);
                io_display();
                return;
            }
            // prompt user to select a new active Pokemon
            WINDOW *switch_menu = make_screen("SELECT THE POKEMON YOU'D LIKE TO MAKE ACTIVE:");
            print_switch_pokemon(switch_menu);
            wclear(switch_menu);
            string s = p->get_species();
            for(int i = 0; i < s.length(); i++) {
                s[i] = toupper(s[i]);
            }
            s = "A WILD " + s + " HAS APPEARED!";
            WINDOW *menu = make_screen(s);
            // display level, hp, and gender
            s = to_string(p->get_level());
            capitalize_string(s);
            s = "LEVEL: " + s;
            mvwprintw(menu, 3, 2, s.c_str());
            s = "HP: " + to_string(p->get_current_hp()) + "/" + to_string(p->get_hp());
            mvwprintw(menu, 3, 32, s.c_str());
            s = string(p->get_gender_string());
            capitalize_string(s);
            s = "GENDER: " + s;
            mvwprintw(menu, 3, 62, s.c_str());
            // print PC's active pokemon info
            wmove(menu, 8, 1);
            whline(menu, '-', 78);
            s = "YOUR ACTIVE POKEMON: " + string(world.pc.p_list[0].get_species());
            for(int i = 0; i < s.length(); i++) {
                s[i] = toupper(s[i]);
            }
            mvwprintw(menu, 9, 1, s.c_str());
            wmove(menu, 10, 1);
            whline(menu, '-', 78);
            // print level, hp, and gender of PC's pokemon
            s = to_string(world.pc.p_list[world.pc.active_index].get_level());
            capitalize_string(s);
            s = "LEVEL: " + s;
            mvwprintw(menu, 11, 2, s.c_str());
            s = "HP: " + to_string(world.pc.p_list[0].get_current_hp()) + "/" + to_string(world.pc.p_list[0].get_hp());
            mvwprintw(menu, 11, 32, s.c_str());
            s = world.pc.p_list[world.pc.active_index].get_gender_string();
            capitalize_string(s);
            s = "GENDER: " + s;
            mvwprintw(menu, 11, 62, s.c_str());
            // print PC's active Pokemon moves
            s = world.pc.p_list[world.pc.active_index].get_move(0);
            capitalize_string(s);
            s = "MOVE 1: " + s;
            mvwprintw(menu, 13, 2, s.c_str());
            s = world.pc.p_list[world.pc.active_index].get_move(1);
            capitalize_string(s);
            s = "MOVE 2: " + s;
            mvwprintw(menu, 13, 32, s.c_str());
            s = world.pc.p_list[world.pc.active_index].get_move(2);
            capitalize_string(s);
            s = "MOVE 3: " + s;
            mvwprintw(menu, 15, 2, s.c_str());
            s = world.pc.p_list[world.pc.active_index].get_move(3);
            capitalize_string(s);
            s = "MOVE 4: " + s;
            mvwprintw(menu, 15, 32, s.c_str());
            // prompt the user
            mvwprintw(menu, 19, 19, "ENTER THE NUMBER OF THE MOVE TO USE IT:");
            mvwprintw(menu, 20, 24, "ENTER 'r' TO TRY AND RUN AWAY:");
            mvwprintw(menu, 21, 26, "ENTER 'b' TO OPEN YOUR BAG:");
            mvwprintw(menu, 22, 19, "ENTER 's' TO SWITCH YOUR ACTIVE POKEMON:");
            // refresh the screen
            wrefresh(menu);
        }
        // TODO - handle 'capturing' wild Pokemon, ie. copying it over to PC's p_list
        // and decrement number of Pokeballs
    }

    io_display();
}

void use_item(int item, int poke_idx)
{
    // ensure that item is only used on an existing Pokemon
    if (poke_idx < world.pc.num_pokemon) {
        switch (item) {
            case 0: // revives
                if(world.pc.bag[item] > 0) {
                    world.pc.bag[0]--;
                    // check if Pokemon is knocked out
                    if (world.pc.p_list[poke_idx].is_defeated()) {
                        world.pc.p_list[poke_idx].set_is_defeated(false);
                        world.pc.p_list[poke_idx].set_current_hp(world.pc.p_list[poke_idx].get_hp() / 2);
                    }
                }
                break;
            case 1: // potions
                if(world.pc.bag[item] > 0) {
                    world.pc.bag[1]--;
                    // check if Pokemon is not knocked out
                    if (!world.pc.p_list[poke_idx].is_defeated()) {
                        // guarrantees that the Pokemon's healed HP will be higher than its max HP
                        if (world.pc.p_list[poke_idx].get_current_hp() + 20 > world.pc.p_list[poke_idx].get_hp()) {
                            world.pc.p_list[poke_idx].set_current_hp(world.pc.p_list[poke_idx].get_current_hp() + (world.pc.p_list[poke_idx].get_hp() - world.pc.p_list[poke_idx].get_current_hp()));
                        }
                    }
                }
                break;
            case 2: // pokeballs
                if(world.pc.bag[item] > 0) {
                    world.pc.bag[2]--;
                }
                break;
        }
    }
}

void switch_pokemon_npc(Npc *npc)
{
    // store current active Pokemon
    Pokemon temp = npc->p_list[0];
    // increment through list of NPC's Pokemon
    for (int i = 1; i < npc->num_pokemon; i++) {
        if (!npc->p_list[i].is_defeated()) {
            npc->p_list[0] = npc->p_list[i];
            npc->p_list[i] = temp;
        }
    }
}

void switch_pokemon(Pokemon p, int curr_idx)
{
    if (!p.is_defeated()) {
        Pokemon temp = world.pc.p_list[0];
        world.pc.p_list[0] = p;
        world.pc.p_list[curr_idx] = temp;

    }
}

void print_switch_pokemon(WINDOW *menu)
{
    int input;
    bool switched;
    switched = false;
    menu = make_screen("SELECT THE POKEMON YOU'D LIKE TO MAKE ACTIVE:");
    for (int i = 0; i < world.pc.num_pokemon; i++) {
        print_basic_pokemon_info(world.pc.p_list[i], i, menu);
    }
    wmove(menu, 21, 1);
    whline(menu, ' ', 78);
    mvwprintw(menu, 21, 11, "ENTER THE NUMBER OF THE POKEMON THAT YOU WANT TO MAKE ACTIVE:");
    wrefresh(menu);
    // handle input
    while (!switched && input != 27) {
        input = getch();
        switch (input) {
            case 49: // 1
                if (world.pc.p_list[0].is_defeated()) {
                    wmove(menu, 18, 1);
                    whline(menu, ' ', 78);
                    wattron(menu, COLOR_PAIR(COLOR_RED));
                    mvwprintw(menu, 20, 27, "POKEMON IS KNOCKED OUT!");
                    wattroff(menu, COLOR_PAIR(COLOR_RED));
                    wrefresh(menu);
                }
                else {
                    wmove(menu, 18, 1);
                    whline(menu, ' ', 78);
                    wattron(menu, COLOR_PAIR(COLOR_RED));
                    mvwprintw(menu, 20, 26, "POKEMON IS ALREADY ACTIVE!");
                    wattroff(menu, COLOR_PAIR(COLOR_RED));
                    wrefresh(menu);
                }
            case 50: // 2
                wmove(menu, 18, 1);
                whline(menu, ' ', 78);
                if (world.pc.num_pokemon > 1) {
                    switch_pokemon(world.pc.p_list[1], 1);
                    switched = true;
                }
                break;
            case 51: // 3
                wmove(menu, 18, 1);
                whline(menu, ' ', 78);
                if (world.pc.num_pokemon > 2) {
                    switch_pokemon(world.pc.p_list[2], 2);
                    switched = true;
                }
                break;
            case 52: // 4
                wmove(menu, 18, 1);
                whline(menu, ' ', 78);
                if (world.pc.num_pokemon > 3) {
                    switch_pokemon(world.pc.p_list[3], 3);
                    switched = true;
                }
                break;
            case 53: // 5
                wmove(menu, 18, 1);
                whline(menu, ' ', 78);
                if (world.pc.num_pokemon > 4) {
                    switch_pokemon(world.pc.p_list[4], 4);
                    switched = true;
                }
                break;
            case 54: // 6
                wmove(menu, 18, 1);
                whline(menu, ' ', 78);
                if (world.pc.num_pokemon > 5) {
                    switch_pokemon(world.pc.p_list[5], 5);
                    switched = true;
                }
                break;
        }
    }
    // reprint Pokemon information
    wclear(menu);
    menu = make_screen("SELECT THE POKEMON YOU'D LIKE TO MAKE ACTIVE:");
    for (int i = 0; i < world.pc.num_pokemon; i++) {
        print_basic_pokemon_info(world.pc.p_list[i], i, menu);
    }
    wmove(menu, 21, 1);
    whline(menu, ' ', 78);
    mvwprintw(menu, 21, 6, "ENTER THE NUMBER OF THE POKEMON THAT YOU WANT TO MAKE ACTIVE:");
    wrefresh(menu);
}

void print_bag(WINDOW *menu)
{
    int input;
    string s;

    menu = make_screen("YOUR BAG");
    // revives
    mvwprintw(menu, 3, 2, "* REVIVES:");
    wattron(menu, COLOR_PAIR(COLOR_RED));
    s = to_string(world.pc.bag[0]);
    mvwprintw(menu, 3, 13, s.c_str());
    wattroff(menu, COLOR_PAIR(COLOR_RED));
    // potions
    mvwprintw(menu, 4, 2, "* POTIONS:");
    wattron(menu, COLOR_PAIR(COLOR_RED));
    s = to_string(world.pc.bag[1]);
    mvwprintw(menu, 4, 13, s.c_str());
    wattroff(menu, COLOR_PAIR(COLOR_RED));
    // pokeballs
    mvwprintw(menu, 5, 2, "* POKEBALLS:");
    wattron(menu, COLOR_PAIR(COLOR_RED));
    s = to_string(world.pc.bag[2]);
    mvwprintw(menu, 5, 15, s.c_str());
    wattroff(menu, COLOR_PAIR(COLOR_RED));
    //pokebucks
    mvwprintw(menu, 6, 2, "* POKEBUCKS:");
    wattron(menu, COLOR_PAIR(COLOR_RED));
    s = to_string(world.pc.poke_bucks);
    mvwprintw(menu, 6, 15, s.c_str());
    wattroff(menu, COLOR_PAIR(COLOR_RED));
    // print Pokemon's HP species, level, 
    wmove(menu, 13, 1);
    whline(menu, '-', 78);
    // prompt user
    mvwprintw(menu, 20, 26, "ENTER 'r' TO REVIVE A POKEMON:");
    mvwprintw(menu, 21, 27, "ENTER 'h' TO HEAL A POKEMON:");
    mvwprintw(menu, 22, 26, "ENTER 'esc' TO CLOSE YOUR BAG:");
    wrefresh(menu);
    // handle input
    input = getch();
    while (input != 27) {
        switch (input) {
            case 114: // r
            case 82: // R
                bool revived;
                revived = false;
                menu = make_screen("SELECT THE POKEMON YOU'D LIKE TO REVIVE:");
                for (int i = 0; i < world.pc.num_pokemon; i++) {
                    print_basic_pokemon_info(world.pc.p_list[i], i, menu);
                }
                wmove(menu, 21, 1);
                whline(menu, ' ', 78);
                mvwprintw(menu, 21, 11, "ENTER THE NUMBER OF THE POKEMON THAT YOU WANT TO REVIVE:");
                wrefresh(menu);
                // handle input
                while (!revived) {
                    input = getch();
                    switch (input) {
                        case 49: // 1
                            use_item(0, 0);
                            revived = true;
                            break;
                        case 50: // 2
                            use_item(0, 1);
                            revived = true;
                            break;
                        case 51: // 3
                            use_item(0, 2);
                            revived = true;
                            break;
                        case 52: // 4
                            use_item(0, 3);
                            revived = true;
                            break;
                        case 53: // 5
                            use_item(0, 4);
                            revived = true;
                            break;
                        case 54: // 6
                            use_item(0, 5);
                            revived = true;
                            break;
                    }
                }
                // reprint Pokemon information
                wclear(menu);
                menu = make_screen("YOUR POKEMON HAS BEEN REVIVED!");
                for (int i = 0; i < world.pc.num_pokemon; i++) {
                    print_basic_pokemon_info(world.pc.p_list[i], i, menu);
                }
                wmove(menu, 21, 1);
                whline(menu, ' ', 78);
                wrefresh(menu);
                break;
            case 104: // H
            case 72: // h
                bool healed;
                healed = false;
                menu = make_screen("SELECT THE POKEMON YOU'D LIKE TO HEAL:");
                for (int i = 0; i < world.pc.num_pokemon; i++) {
                    print_basic_pokemon_info(world.pc.p_list[i], i, menu);
                }
                wmove(menu, 21, 1);
                whline(menu, ' ', 78);
                mvwprintw(menu, 21, 13, "ENTER THE NUMBER OF THE POKEMON THAT YOU WANT TO HEAL:");
                wrefresh(menu);
                // handle input
                while (!healed) {
                    input = getch();
                    switch (input) {
                        case 49: // 1
                            if (world.pc.p_list[0].is_defeated()) {
                                wmove(menu, 20, 1);
                                whline(menu, ' ', 78);
                                wattron(menu, COLOR_PAIR(COLOR_RED));
                                mvwprintw(menu, 20, 24, "YOUR POKEMON CAN'T BE HEALED!");
                                wattroff(menu, COLOR_PAIR(COLOR_RED));
                                wrefresh(menu);
                                usleep(2500000);
                                return;
                            }
                            else use_item(1, 0);
                            healed = true;
                            break;
                        case 50: // 2
                            if (world.pc.p_list[1].is_defeated()) {
                                wmove(menu, 20, 1);
                                whline(menu, ' ', 78);
                                wattron(menu, COLOR_PAIR(COLOR_RED));
                                mvwprintw(menu, 20, 24, "YOUR POKEMON CAN'T BE HEALED!");
                                wattroff(menu, COLOR_PAIR(COLOR_RED));
                                wrefresh(menu);
                                usleep(2500000);
                                return;
                            }
                            else use_item(1, 1);
                            healed = true;
                            break;
                        case 51: // 3
                            if (world.pc.p_list[2].is_defeated()) {
                                wmove(menu, 20, 1);
                                whline(menu, ' ', 78);
                                wattron(menu, COLOR_PAIR(COLOR_RED));
                                mvwprintw(menu, 20, 24, "YOUR POKEMON CAN'T BE HEALED!");
                                wattroff(menu, COLOR_PAIR(COLOR_RED));
                                wrefresh(menu);
                                usleep(2500000);
                                return;
                            }
                            else use_item(1, 2);
                            healed = true;
                            break;
                        case 52: // 4
                            if (world.pc.p_list[3].is_defeated()) {
                                wmove(menu, 20, 1);
                                whline(menu, ' ', 78);
                                wattron(menu, COLOR_PAIR(COLOR_RED));
                                mvwprintw(menu, 20, 24, "YOUR POKEMON CAN'T BE HEALED!");
                                wattroff(menu, COLOR_PAIR(COLOR_RED));
                                wrefresh(menu);
                                usleep(2500000);
                                return;
                            }
                            else use_item(1, 3);
                            healed = true;
                            break;
                        case 53: // 5
                            if (world.pc.p_list[4].is_defeated()) {
                                wmove(menu, 20, 1);
                                whline(menu, ' ', 78);
                                wattron(menu, COLOR_PAIR(COLOR_RED));
                                mvwprintw(menu, 20, 24, "YOUR POKEMON CAN'T BE HEALED!");
                                wattroff(menu, COLOR_PAIR(COLOR_RED));
                                wrefresh(menu);
                                usleep(2500000);
                                return;
                            }
                            else use_item(1, 4);
                            healed = true;
                            break;
                        case 54: // 6
                            if (world.pc.p_list[5].is_defeated()) {
                                wmove(menu, 20, 1);
                                whline(menu, ' ', 78);
                                wattron(menu, COLOR_PAIR(COLOR_RED));
                                mvwprintw(menu, 20, 24, "YOUR POKEMON CAN'T BE HEALED!");
                                wattroff(menu, COLOR_PAIR(COLOR_RED));
                                wrefresh(menu);
                                usleep(2500000);
                                return;
                            }
                            else use_item(1, 5);
                            healed = true;
                            break;
                    }
                }
                // reprint Pokemon information
                wclear(menu);
                menu = make_screen("YOUR POKEMON HAS BEEN HEALED!");
                for (int i = 0; i < world.pc.num_pokemon; i++) {
                    print_basic_pokemon_info(world.pc.p_list[i], i, menu);
                }
                wmove(menu, 21, 1);
                whline(menu, ' ', 78);
                wrefresh(menu);
                break;
            case 27: // esc
                return;
        }

        wrefresh(menu);
        input = getch();
    }
}

void print_pokemon_encounter(Pokemon *p)
{
    bool is_over = false;
    int input, escape_attempts = 0;
    string s = p->get_species();
    for(int i = 0; i < s.length(); i++) {
        s[i] = toupper(s[i]);
    }
    s = "A WILD " + s + " HAS APPEARED!";
    WINDOW *menu = make_screen(s);
    // display level, hp, and gender
    s = to_string(p->get_level());
    capitalize_string(s);
    s = "LEVEL: " + s;
    mvwprintw(menu, 3, 2, s.c_str());
    s = to_string(p->get_hp());
    capitalize_string(s);
    s = "HP: " + s;
    mvwprintw(menu, 3, 32, s.c_str());
    s = string(p->get_gender_string());
    capitalize_string(s);
    s = "GENDER: " + s;
    mvwprintw(menu, 3, 62, s.c_str());
    // prompt the user
    mvwprintw(menu, 19, 19, "ENTER 'c' TO TRY AND CATCH THE POKEMON:");
    mvwprintw(menu, 20, 24, "ENTER 'r' TO TRY AND RUN AWAY:");
    mvwprintw(menu, 21, 26, "ENTER 'b' TO OPEN YOUR BAG:");
    mvwprintw(menu, 22, 19, "ENTER 's' TO SWITCH YOUR ACTIVE POKEMON:");
    // refresh the screen
    wrefresh(menu);
    // handle input
    while (!is_over && input != 27) {
        input = getch();
        switch (input)
        {
        case 67: // C
        case 99: // c
            wclear(menu);
            print_pokemon_battle(p);
            return;
        case 82: // R
        case 114: // r
            escape_attempts++;
            if (((world.pc.p_list[world.pc.active_index].get_speed() * 32) / ((p->get_speed() / 4) % 256) + 30 * escape_attempts) > 255) is_over = true;
            else {
                wmove(menu, 18, 1);
                whline(menu, ' ', 78);
                wattron(menu, COLOR_PAIR(COLOR_RED));
                mvwprintw(menu, 18, 32, "CAN'T ESCAPE!");
                wattroff(menu, COLOR_PAIR(COLOR_RED));
                wrefresh(menu);
                usleep(2500000);
                wmove(menu, 18, 1);
                whline(menu, ' ', 78);
                wrefresh(menu);
            }
            break;
        case 66: // B
        case 98: // b
            wmove(menu, 18, 1);
            whline(menu, ' ', 78);
            print_bag(menu);
            print_pokemon_encounter(p);
            return;
        case 83: // S
        case 115: // s
            wmove(menu, 18, 1);
            whline(menu, ' ', 78);
            wrefresh(menu);
            print_switch_pokemon(menu);
            print_pokemon_encounter(p);
            return;
        }
  }
    wclear(menu);
    io_display();
}

void print_trainer_battle(WINDOW *menu, Pc pc, Npc *npc)
{
    // if (world.pc.p_list[0].is_defeated()) print_switch_pokemon(menu);
    bool is_over = false;
    int input, npc_dmg, pc_dmg, npc_move_idx, pc_move_idx;
    // display level, hp, and gender of NPC's active Pokemon
    string s, npc_p_name;

    box(menu, 0, 0);
    wmove(menu, 2, 1);
    whline(menu, '-', 78);
    npc_p_name = npc->p_list[0].get_species();
    for(int i = 0; i < npc_p_name.length(); i++) {
        npc_p_name[i] = toupper(npc_p_name[i]);
    }
    switch (npc->symbol) {
        case 'h':
            s = "HIKER'S ACTIVE POKEMON: " + npc_p_name;
            break;
        case 'r':
            s = "RIVAL'S ACTIVE POKEMON: " + npc_p_name;
            break;
        case 'p':
            s = "PACER'S ACTIVE POKEMON: " + npc_p_name;
            break;
        case 'n':
            s = "RANDOM WALKER'S ACTIVE POKEMON: " + npc_p_name;
            break;
        case 'w':
            s = "WANDERER'S ACTIVE POKEMON: " + npc_p_name;
            break;
        case 's':
            s = "STATIONARY'S ACTIVE POKEMON: " + npc_p_name;
            break;
    }
    wmove(menu, 1, 1);
    whline(menu, ' ', 78);
    mvwprintw(menu, 1, 2, s.c_str());
    s = to_string(npc->p_list[0].get_level());
    s = "LEVEL: " + s;
    mvwprintw(menu, 3, 2, s.c_str());
    s = "HP: " + to_string(npc->p_list[0].get_current_hp()) + "/" + to_string(npc->p_list[0].get_hp());
    mvwprintw(menu, 3, 32, s.c_str());
    s = string(npc->p_list[0].get_gender_string());
    capitalize_string(s);
    s = "GENDER: " + s;
    mvwprintw(menu, 3, 62, s.c_str());
    // print PC's active pokemon info
    wmove(menu, 8, 1);
    whline(menu, '-', 78);
    s = "YOUR ACTIVE POKEMON: " + string(world.pc.p_list[0].get_species());
            for(int i = 0; i < s.length(); i++) {
                s[i] = toupper(s[i]);
            }
    mvwprintw(menu, 9, 1, s.c_str());
    wmove(menu, 10, 1);
    whline(menu, '-', 78);
    // print level, hp, and gender of PC's pokemon
    s = to_string(world.pc.p_list[world.pc.active_index].get_level());
    capitalize_string(s);
    s = "LEVEL: " + s;
    mvwprintw(menu, 11, 2, s.c_str());
    s = "HP: " + to_string(world.pc.p_list[0].get_current_hp()) + "/" + to_string(world.pc.p_list[0].get_hp());
    mvwprintw(menu, 11, 32, s.c_str());
    s = world.pc.p_list[world.pc.active_index].get_gender_string();
    capitalize_string(s);
    s = "GENDER: " + s;
    mvwprintw(menu, 11, 62, s.c_str());
    // print PC's active Pokemon moves
    s = world.pc.p_list[world.pc.active_index].get_move(0);
    capitalize_string(s);
    s = "MOVE 1: " + s;
    mvwprintw(menu, 13, 2, s.c_str());
    s = world.pc.p_list[world.pc.active_index].get_move(1);
    capitalize_string(s);
    s = "MOVE 2: " + s;
    mvwprintw(menu, 13, 32, s.c_str());
    s = world.pc.p_list[world.pc.active_index].get_move(2);
    capitalize_string(s);
    s = "MOVE 3: " + s;
    mvwprintw(menu, 15, 2, s.c_str());
    s = world.pc.p_list[world.pc.active_index].get_move(3);
    capitalize_string(s);
    s = "MOVE 4: " + s;
    mvwprintw(menu, 15, 32, s.c_str());
    // prompt the user
    mvwprintw(menu, 20, 19, "ENTER THE NUMBER OF THE MOVE TO USE IT:");
    mvwprintw(menu, 21, 26, "ENTER 'b' TO OPEN YOUR BAG:");
    mvwprintw(menu, 22, 19, "ENTER 's' TO SWITCH YOUR ACTIVE POKEMON:");
    // refresh the screen
    wrefresh(menu);
    // handle input
    while (!is_over) {
        // need to randomly select a wild Pokemon's next move.
        do {
            npc_dmg = rand() % 4;
        }
        while (string(npc->p_list[0].get_move(npc_dmg)) == "-");
        npc_move_idx = npc->p_list[0].get_move_id(npc_dmg);
        npc_dmg = calculate_damage_npc(npc->p_list[0], npc_move_idx);
        // handle input
        input = getch();
        switch (input) {
            case 66: // B
            case 98: // b
                wmove(menu, 18, 1);
                whline(menu, ' ', 78);
                print_bag(menu);
                wclear(menu);
                print_trainer_battle(menu, pc, npc);
                return;
            case 83: // S
            case 115: // s
                wmove(menu, 18, 1);
                whline(menu, ' ', 78);
                print_switch_pokemon(menu);
                wclear(menu);
                print_trainer_battle(menu, pc, npc);
                return;
            case 49: // 1
                if (string(world.pc.p_list[0].get_move(0)) == "-") pc_dmg = 0;
                else {
                    pc_move_idx = world.pc.p_list[0].get_move_id(0);
                    pc_dmg = calculate_damage_pc(pc_move_idx, npc->p_list[0]);
                }
                break;
            case 50: // 2
                if (string(world.pc.p_list[0].get_move(1)) == "-") pc_dmg = 0;
                else {
                    pc_move_idx = world.pc.p_list[0].get_move_id(1);
                    pc_dmg = calculate_damage_pc(pc_move_idx, npc->p_list[0]);
                }
                break;
            case 51: // 3
                if (string(world.pc.p_list[0].get_move(2)) == "-") pc_dmg = 0;
                else {
                    pc_move_idx = world.pc.p_list[0].get_move_id(2);
                    pc_dmg = calculate_damage_pc(pc_move_idx, npc->p_list[0]);
                }
                break;
            case 52: // 4
                if (string(world.pc.p_list[0].get_move(3)) == "-") pc_dmg = 0;
                else {
                    pc_move_idx = world.pc.p_list[0].get_move_id(3);
                    pc_dmg = calculate_damage_pc(pc_move_idx, npc->p_list[0]);
                }
                break;
            default:
                pc_dmg = 0;
                pc_move_idx = 0;
                break;
        }

        // check if PC has selected a non-existent move
        if (pc_dmg == 0) {
            if (rand() % 100 < moves[npc_move_idx].accuracy) {
                // move hits
                world.pc.p_list[0].set_current_hp(world.pc.p_list[0].get_current_hp() - npc_dmg);
                if (world.pc.p_list[0].get_current_hp() <= 0) {
                    world.pc.p_list[0].set_is_defeated(true);
                    world.pc.p_list[0].set_current_hp(0);
                    // prompt user to switch active Pokemon
                }
            } else {
                wmove(menu, 19, 1);
                whline(menu, ' ', 78);
                wattron(menu, COLOR_PAIR(COLOR_RED));
                mvwprintw(menu, 19, 28, "TRAINER'S MOVE MISSED!");
                wattroff(menu, COLOR_PAIR(COLOR_RED));
                wrefresh(menu);
                usleep(2500000);
                wmove(menu, 19, 1);
                whline(menu, ' ', 78);
                wrefresh(menu);
            }
        } else {
            if (moves[pc_move_idx].priority > moves[npc_move_idx].priority) {
            // PC move goes first
            // need to calculate if move hits
            if (rand() % 100 < moves[pc_move_idx].accuracy) {
                // move hits
                npc->p_list[0].set_current_hp(npc->p_list[0].get_current_hp() - pc_dmg);
                if (npc->p_list[0].get_current_hp() <= 0) {
                    npc->p_list[0].set_is_defeated(true);
                    npc->p_list[0].set_current_hp(0);
                }
            } else {
                wmove(menu, 19, 1);
                whline(menu, ' ', 78);
                wattron(menu, COLOR_PAIR(COLOR_RED));
                mvwprintw(menu, 19, 30, "YOUR MOVE MISSED!");
                wattroff(menu, COLOR_PAIR(COLOR_RED));
                wrefresh(menu);
                usleep(2500000);
                wmove(menu, 19, 1);
                whline(menu, ' ', 78);
                wrefresh(menu);
            }
            }
            else if (moves[pc_move_idx].priority < moves[npc_move_idx].priority) {
                // wild Pokemon goes first
                // need to calculate if move hits
                if (rand() % 100 < moves[npc_move_idx].accuracy) {
                    // move hits
                    world.pc.p_list[0].set_current_hp(world.pc.p_list[0].get_current_hp() - npc_dmg);
                    if (world.pc.p_list[0].get_current_hp() <= 0) {
                        world.pc.p_list[0].set_is_defeated(true);
                        world.pc.p_list[0].set_current_hp(0);
                        // prompt user to switch active Pokemon
                    }
                } else {
                    wmove(menu, 19, 1);
                    whline(menu, ' ', 78);
                    wattron(menu, COLOR_PAIR(COLOR_RED));
                    mvwprintw(menu, 19, 28, "TRAINER'S MOVE MISSED!");
                    wattroff(menu, COLOR_PAIR(COLOR_RED));
                    wrefresh(menu);
                    usleep(2500000);
                    wmove(menu, 19, 1);
                    whline(menu, ' ', 78);
                    wrefresh(menu);
                }
            }
            else if (moves[pc_move_idx].priority == moves[npc_move_idx].priority) {
                // move priorities are equal
                if (world.pc.p_list[0].get_speed() > npc->p_list[0].get_speed()) {
                    // PC move goes first based on Pokemon's speed
                    // need to calculate if move hits
                    if (rand() % 100 < moves[pc_move_idx].accuracy) {
                        // move hits
                        npc->p_list[0].set_current_hp(npc->p_list[0].get_current_hp() - pc_dmg);
                        if (npc->p_list[0].get_current_hp() <= 0) {
                            npc->p_list[0].set_is_defeated(true);
                            npc->p_list[0].set_current_hp(0);
                        }
                    } else {
                        wmove(menu, 19, 1);
                        whline(menu, ' ', 78);
                        wattron(menu, COLOR_PAIR(COLOR_RED));
                        mvwprintw(menu, 19, 30, "YOUR MOVE MISSED!");
                        wattroff(menu, COLOR_PAIR(COLOR_RED));
                        wrefresh(menu);
                        usleep(2500000);
                        wmove(menu, 19, 1);
                        whline(menu, ' ', 78);
                        wrefresh(menu);
                    }
                } else if (world.pc.p_list[0].get_speed() > npc->p_list[0].get_speed()) {
                    // wild Pokemon move goes first based on Pokemon's speed
                    // need to calculate if move hits
                    if (rand() % 100 < moves[npc_move_idx].accuracy) {
                        // move hits
                        world.pc.p_list[0].set_current_hp(world.pc.p_list[0].get_current_hp() - npc_dmg);
                        if (world.pc.p_list[0].get_current_hp() <= 0) {
                            world.pc.p_list[0].set_is_defeated(true);
                            world.pc.p_list[0].set_current_hp(0);
                            // prompt user to switch active Pokemon
                        }
                    } else {
                        wmove(menu, 19, 1);
                        whline(menu, ' ', 78);
                        wattron(menu, COLOR_PAIR(COLOR_RED));
                        mvwprintw(menu, 19, 28, "TRAINER'S MOVE MISSED!");
                        wattroff(menu, COLOR_PAIR(COLOR_RED));
                        wrefresh(menu);
                        usleep(2500000);
                        wmove(menu, 19, 1);
                        whline(menu, ' ', 78);
                        wrefresh(menu);
                    }
                }
                else {
                    // if Pokemon speeds are equal, choose at random for first move
                    if (rand() % 2 == 0) {
                        // PC move goes first
                        // need to calculate if move hits
                        if (rand() % 100 < moves[pc_move_idx].accuracy) {
                            // move hits
                            npc->p_list[0].set_current_hp(npc->p_list[0].get_current_hp() - pc_dmg);
                            if (npc->p_list[0].get_current_hp() <= 0) {
                                npc->p_list[0].set_is_defeated(true);
                                npc->p_list[0].set_current_hp(0);
                            }
                        } else {
                            wmove(menu, 19, 1);
                            whline(menu, ' ', 78);
                            wattron(menu, COLOR_PAIR(COLOR_RED));
                            mvwprintw(menu, 19, 30, "YOUR MOVE MISSED!");
                            wattroff(menu, COLOR_PAIR(COLOR_RED));
                            wrefresh(menu);
                            usleep(2500000);
                            wmove(menu, 19, 1);
                            whline(menu, ' ', 78);
                            wrefresh(menu);
                        }
                    } else {
                        // wild Pokemon move goes first
                        // need to calculate if move hits
                        if (rand() % 100 < moves[npc_move_idx].accuracy) {
                            // move hits
                            world.pc.p_list[0].set_current_hp(world.pc.p_list[0].get_current_hp() - npc_dmg);
                            if (world.pc.p_list[0].get_current_hp() <= 0) {
                                world.pc.p_list[0].set_is_defeated(true);
                                world.pc.p_list[0].set_current_hp(0);
                                // prompt user to switch active Pokemon
                            }
                        } else {
                            wmove(menu, 19, 1);
                            whline(menu, ' ', 78);
                            wattron(menu, COLOR_PAIR(COLOR_RED));
                            mvwprintw(menu, 19, 28, "TRAINER'S MOVE MISSED!");
                            wattroff(menu, COLOR_PAIR(COLOR_RED));
                            wrefresh(menu);
                            usleep(2500000);
                            wmove(menu, 19, 1);
                            whline(menu, ' ', 78);
                            wrefresh(menu);
                        }
                    }
                }
            }
        }
        // update screen
        wmove(menu, 3, 32);
        whline(menu, ' ', 47);
        s = "HP: " + to_string(npc->p_list[0].get_current_hp()) + "/" + to_string(npc->p_list[0].get_hp());
        mvwprintw(menu, 3, 32, s.c_str());
        s = string(npc->p_list[0].get_gender_string());
        capitalize_string(s);
        s = "GENDER: " + s;
        mvwprintw(menu, 3, 62, s.c_str());
        wmove(menu, 11, 32);
        whline(menu, ' ', 47);
        s = "HP: " + to_string(world.pc.p_list[0].get_current_hp()) + "/" + to_string(world.pc.p_list[0].get_hp());
        mvwprintw(menu, 11, 32, s.c_str());
        s = world.pc.p_list[world.pc.active_index].get_gender_string();
        capitalize_string(s);
        s = "GENDER: " + s;
        mvwprintw(menu, 11, 62, s.c_str());
        wrefresh(menu);
        if (npc->p_list[0].is_defeated()) {
            // reward PC with Pokebucks
            world.pc.poke_bucks += rand() % 100;
            // inform user they have defeated the Trainer's active Pokemon
            wmove(menu, 19, 1);
            whline(menu, ' ', 78);
            wattron(menu, COLOR_PAIR(COLOR_RED));
            mvwprintw(menu, 19, 15, "TRAINER'S ACTIVE POKEMON HAS BEEN KNOCKED OUT!");
            wattroff(menu, COLOR_PAIR(COLOR_RED));
            wrefresh(menu);
            usleep(2500000);
            wmove(menu, 19, 1);
            whline(menu, ' ', 78);
            wrefresh(menu);
            // check if all of NPC's Pokemon are defeated
            int count = 0;
            for (int i = 0; i < npc->num_pokemon; i++) {
                if (npc->p_list[i].is_defeated()) count++;
            }
            if (count == npc->num_pokemon) {
                is_over = true;
                wmove(menu, 19, 1);
                whline(menu, ' ', 78);
                wattron(menu, COLOR_PAIR(COLOR_RED));
                mvwprintw(menu, 19, 24, "THE TRAINER HAS BEEN DEFEATED!");
                npc->defeated = 1;
                wattroff(menu, COLOR_PAIR(COLOR_RED));
                wrefresh(menu);
                usleep(2500000);
                io_display();
                return;
            }
            else {
                wmove(menu, 19, 1);
                whline(menu, ' ', 78);
                wattron(menu, COLOR_PAIR(COLOR_RED));
                mvwprintw(menu, 19, 18, "TRAINER HAS SWITCHED THEIR ACTIVE POKEMON!");
                wattroff(menu, COLOR_PAIR(COLOR_RED));
                wrefresh(menu);
                usleep(2500000);
                wmove(menu, 19, 1);
                whline(menu, ' ', 78);
                wrefresh(menu);
                switch_pokemon_npc(npc);
                npc_p_name = npc->p_list[0].get_species();
                for(int i = 0; i < npc_p_name.length(); i++) {
                    if (npc_p_name[i] != ' ' || npc_p_name[i] != '-') npc_p_name[i] = toupper(npc_p_name[i]);
                }
                switch (npc->symbol) {
                    case 'h':
                        s = "HIKER'S ACTIVE POKEMON: " + npc_p_name;
                        break;
                    case 'r':
                        s = "RIVAL'S ACTIVE POKEMON: " + npc_p_name;
                        break;
                    case 'p':
                        s = "PACER'S ACTIVE POKEMON: " + npc_p_name;
                        break;
                    case 'n':
                        s = "RANDOM WALKER'S ACTIVE POKEMON: " + npc_p_name;
                        break;
                    case 'w':
                        s = "WANDERER'S ACTIVE POKEMON: " + npc_p_name;
                        break;
                    case 's':
                        s = "STATIONARY'S ACTIVE POKEMON: " + npc_p_name;
                        break;
                }
                for (int i = 1; i < 4; i++) {
                    wmove(menu, i, 2);
                    whline(menu, ' ', 77);
                }
                mvwprintw(menu, 1, 2, s.c_str());
                wmove(menu, 2, 1);
                whline(menu, '-', 78);
                s = "LEVEL: ";
                s = s + to_string(npc->p_list[0].get_level());
                mvwprintw(menu, 3, 2, s.c_str());
                s = "HP: " + to_string(npc->p_list[0].get_current_hp()) + "/" + to_string(npc->p_list[0].get_hp());
                mvwprintw(menu, 3, 32, s.c_str());
                s = string(npc->p_list[0].get_gender_string());
                capitalize_string(s);
                s = "GENDER: " + s;
                mvwprintw(menu, 3, 62, s.c_str());
                wrefresh(menu);
                usleep(2500000);
            }
        }
        else if (world.pc.p_list[0].is_defeated()) {
            // inform user that their active Pokemon has been defeated
            wmove(menu, 19, 1);
            whline(menu, ' ', 78);
            wattron(menu, COLOR_PAIR(COLOR_RED));
            mvwprintw(menu, 19, 22, "ACTIVE POKEMON HAS BEEN DEFEATED!");
            wattroff(menu, COLOR_PAIR(COLOR_RED));
            wrefresh(menu);
            usleep(2500000);
            wmove(menu, 19, 1);
            whline(menu, ' ', 78);
            // check if PC has been defeated
            int count = 0;
            for (int i = 0; i < world.pc.num_pokemon; i++) {
                if (world.pc.p_list[i].is_defeated()) count++;
            }
            if (count == world.pc.num_pokemon) {
                wmove(menu, 19, 1);
                whline(menu, ' ', 78);
                is_over = true;
                wattron(menu, COLOR_PAIR(COLOR_RED));
                mvwprintw(menu, 19, 27, "YOU HAVE BEEN DEFEATED!");
                wattroff(menu, COLOR_PAIR(COLOR_RED));
                wrefresh(menu);
                usleep(2500000);
                io_display();
                return;
            }
            // prompt user to select a new active Pokemon
            WINDOW *switch_menu = make_screen("SELECT THE POKEMON YOU'D LIKE TO MAKE ACTIVE:");
            print_switch_pokemon(switch_menu);
            wclear(switch_menu);
            // update screen
            print_trainer_battle(menu, pc, npc);
        }
    }

    io_display();
}

void print_trainer_encounter(Pc pc, Npc *npc)
{
    bool is_over = false;
    string s;
    int input = 0;
    switch (npc->symbol) {
        case 'h':
            s = "YOU ARE CHALLENGED BY HIKER!";
            break;
        case 'r':
            s = "YOU ARE CHALLENGED BY RIVAL!";
            break;
        case 'p':
            s = "YOU ARE CHALLENGED BY PACER!";
            break;
        case 'n':
            s = "YOU ARE CHALLENGED BY RANDOM WALKER!";
            break;
        case 'w':
            s = "YOU ARE CHALLENGED BY WANDERER!";
            break;
        case 's':
            s = "YOU ARE CHALLENGED BY STATIONARY!";
            break;
    }
    // make screen
    WINDOW *menu = make_screen(s);
    // prompt the user
    mvwprintw(menu, 20, 29, "ENTER 'f' TO BATTLE:");
    mvwprintw(menu, 21, 26, "ENTER 'b' TO OPEN YOUR BAG:");
    mvwprintw(menu, 22, 20, "ENTER 's' TO SWITCH YOUR ACTIVE POKEMON:");
    // refresh the screen
    wrefresh(menu);

    // handle input
    while (!is_over) {
        input = getch();
        switch (input)
        {
        case 70: // F
        case 102: // f
            print_trainer_battle(menu, pc, npc);
            is_over = true;
        // TODO - ADD SCREEN AND FUNCTIONALITY FOR BATTLING A TRAINER
            break;
        case 66: // B
        case 98: // b
            wmove(menu, 18, 1);
            whline(menu, ' ', 78);
            print_bag(menu);
            print_trainer_encounter(pc, npc);
            return;
        case 83: // S
        case 115: // s
            wmove(menu, 18, 1);
            whline(menu, ' ', 78);
            wrefresh(menu);
            print_switch_pokemon(menu);
            print_trainer_encounter(pc, npc);
            return;
        }
    }
  io_display();
}

void print_pokemart()
{
    int key = 0;
    int num_potions = rand() % 20;
    int num_revives = rand() % 20;
    int num_pokeballs = rand() % 20;
    WINDOW *menu = make_screen("WELCOME TO THE POKEMART!");
    // display number of items that are in stock
    // revives
    mvwprintw(menu, 3, 2, "* REVIVES IN STOCK:");
    wattron(menu, COLOR_PAIR(COLOR_RED));
    string s = to_string(num_revives);
    mvwprintw(menu, 3, 22, s.c_str());
    wattroff(menu, COLOR_PAIR(COLOR_RED));
    // potions
    mvwprintw(menu, 4, 2, "* POTIONS IN STOCK:");
    wattron(menu, COLOR_PAIR(COLOR_RED));
    s = to_string(num_potions);
    mvwprintw(menu, 4, 22, s.c_str());
    wattroff(menu, COLOR_PAIR(COLOR_RED));
    // pokeballs
    mvwprintw(menu, 5, 2, "* POKEBALLS IN STOCK:");
    wattron(menu, COLOR_PAIR(COLOR_RED));
    s = to_string(num_pokeballs);
    mvwprintw(menu, 5, 24, s.c_str());
    wattroff(menu, COLOR_PAIR(COLOR_RED));
    // user pokebucks
    wmove(menu, 6, 1);
    whline(menu, '-', 78);
    mvwprintw(menu, 7, 2, "YOUR POKEBUCKS:");
    wattron(menu, COLOR_PAIR(COLOR_RED));
    s = to_string(world.pc.poke_bucks);
    mvwprintw(menu, 7, 18, s.c_str());
    wattroff(menu, COLOR_PAIR(COLOR_RED));
    wmove(menu, 8, 1);
    whline(menu, '-', 78);
    // prompt the user
    mvwprintw(menu, 19, 14, "ENTER '1' TO PURCHASE A REVIVE FOR 100 POKEBUCKS:");
    mvwprintw(menu, 20, 14, "ENTER '2' TO PURCHASE A POTION FOR 100 POKEBUCKS:");
    mvwprintw(menu, 21, 13, "ENTER '3' TO PURCHASE A POKEBALL FOR 100 POKEBUCKS:");
    mvwprintw(menu, 22, 22, "ENTER 'esc' TO EXIT THE POKEMART:");
    wrefresh(menu);

    while(key != 27) { // esc
        wmove(menu, 7, 1);
        whline(menu, ' ', 78);
        mvwprintw(menu, 7, 2, "YOUR POKEBUCKS:");
        wattron(menu, COLOR_PAIR(COLOR_RED));
        s = to_string(world.pc.poke_bucks);
        mvwprintw(menu, 7, 18, s.c_str());
        wattroff(menu, COLOR_PAIR(COLOR_RED));
        wrefresh(menu);
        key = getch();
        switch(key) {
            case 27:
                continue;
            case 49: // 1
                if (world.pc.poke_bucks >= 100) {
                    world.pc.poke_bucks -= 100;
                    world.pc.bag[0]++; // revive
                    num_revives--;
                    wmove(menu, 18, 1);
                    whline(menu, ' ', 78);
                    wattron(menu, COLOR_PAIR(COLOR_RED));
                    mvwprintw(menu, 18, 28, "ONE REVIVE PURCHASED!");
                    wattroff(menu, COLOR_PAIR(COLOR_RED));
                    wrefresh(menu);
                    usleep(2500000);
                    wmove(menu, 18, 1);
                    whline(menu, ' ', 78);
                    wmove(menu, 3, 1);
                    whline(menu, ' ', 78);
                    mvwprintw(menu, 3, 2, "* REVIVES IN STOCK:");
                    wattron(menu, COLOR_PAIR(COLOR_RED));
                    s = to_string(num_revives);
                    mvwprintw(menu, 3, 22, s.c_str());
                    wattroff(menu, COLOR_PAIR(COLOR_RED));
                    wrefresh(menu);
                } else {
                    wmove(menu, 18, 1);
                    whline(menu, ' ', 78);
                    wattron(menu, COLOR_PAIR(COLOR_RED));
                    mvwprintw(menu, 18, 28, "NOT ENOUGH POKEBUCKS!");
                    wattroff(menu, COLOR_PAIR(COLOR_RED));
                    wrefresh(menu);
                    usleep(2500000);
                    wmove(menu, 18, 1);
                    whline(menu, ' ', 78);
                }
                break;
            case 50: // 2
                if (world.pc.poke_bucks >= 100) {
                    world.pc.poke_bucks -= 100;
                    world.pc.bag[1]++; // potion
                    num_potions--;
                    wmove(menu, 18, 1);
                    whline(menu, ' ', 78);
                    wattron(menu, COLOR_PAIR(COLOR_RED));
                    mvwprintw(menu, 18, 28, "ONE POTION PURCHASED!");
                    wattroff(menu, COLOR_PAIR(COLOR_RED));
                    wrefresh(menu);
                    usleep(2500000);
                    wmove(menu, 18, 1);
                    whline(menu, ' ', 78);
                    wmove(menu, 4, 1);
                    whline(menu, ' ', 78);
                    mvwprintw(menu, 4, 2, "* POTIONS IN STOCK:");
                    wattron(menu, COLOR_PAIR(COLOR_RED));
                    s = to_string(num_potions);
                    mvwprintw(menu, 4, 22, s.c_str());
                    wattroff(menu, COLOR_PAIR(COLOR_RED));
                    wrefresh(menu);
                } else {
                    wmove(menu, 18, 1);
                    whline(menu, ' ', 78);
                    wattron(menu, COLOR_PAIR(COLOR_RED));
                    mvwprintw(menu, 18, 28, "NOT ENOUGH POKEBUCKS!");
                    wattroff(menu, COLOR_PAIR(COLOR_RED));
                    wrefresh(menu);
                    usleep(2500000);
                    wmove(menu, 18, 1);
                    whline(menu, ' ', 78);
                }
                break;
            case 51: // 3
            if (world.pc.poke_bucks >= 100) {
                world.pc.poke_bucks -= 100;
                world.pc.bag[2]++; // pokeball
                num_pokeballs--;
                wmove(menu, 18, 1);
                whline(menu, ' ', 78);
                wattron(menu, COLOR_PAIR(COLOR_RED));
                mvwprintw(menu, 18, 27, "ONE POKEBALL PURCHASED!");
                wattroff(menu, COLOR_PAIR(COLOR_RED));
                wrefresh(menu);
                usleep(2500000);
                wmove(menu, 18, 1);
                whline(menu, ' ', 78);
                wmove(menu, 5, 1);
                whline(menu, ' ', 78);
                mvwprintw(menu, 5, 2, "* POKEBALLS IN STOCK:");
                wattron(menu, COLOR_PAIR(COLOR_RED));
                s = to_string(num_pokeballs);
                mvwprintw(menu, 5, 24, s.c_str());
                wattroff(menu, COLOR_PAIR(COLOR_RED));
                wrefresh(menu);
            } else {
                wmove(menu, 18, 1);
                whline(menu, ' ', 78);
                wattron(menu, COLOR_PAIR(COLOR_RED));
                mvwprintw(menu, 18, 28, "NOT ENOUGH POKEBUCKS!");
                wattroff(menu, COLOR_PAIR(COLOR_RED));
                wrefresh(menu);
                usleep(2500000);
                wmove(menu, 18, 1);
                whline(menu, ' ', 78);
            }
                break;
            default:
                break;
        }
    }
}

void print_pokecenter()
{
    int key = 0;
    WINDOW *menu = make_screen("WELCOME TO THE POKECENTER!");
    // prompt the user
    mvwprintw(menu, 19, 14, "ENTER '1' TO REVIVE AND HEAL ALL OF YOUR POKEMON:");
    mvwprintw(menu, 20, 8, "ENTER '2' TO ACCESS ALL OF THE POKEMON THAT YOU HAVE CAPTURED:");
    mvwprintw(menu, 21, 15, "ENTER 'p' TO VIEW YOUR CURRENT LIST OF POKEMON:");
    mvwprintw(menu, 22, 22, "ENTER 'esc' TO EXIT THE POKEMART:");
    wrefresh(menu);

    while(key != 27) { // esc
        key = getch();
        switch(key) {
            case 27: // esc
                continue;
            case 49: // 1
                for (int i = 0; i < world.pc.num_pokemon; i++) {
                    world.pc.p_list[i].set_is_defeated(false);
                    world.pc.p_list[i].set_current_hp(world.pc.p_list[i].get_hp());
                }
                wmove(menu, 18, 1);
                whline(menu, ' ', 78);
                wattron(menu, COLOR_PAIR(COLOR_RED));
                mvwprintw(menu, 18, 18, "YOUR POKEMON HAVE BEEN REVIVED AND HEALED!");
                wattroff(menu, COLOR_PAIR(COLOR_RED));
                wrefresh(menu);
                usleep(2500000);
                wmove(menu, 18, 1);
                whline(menu, ' ', 78);
                wrefresh(menu);
                break;
            case 50: // 2
                print_pokedex();
                key = 27;
                print_pokecenter();
                break;
            case 112: // p
                print_pokemon_list();
                key = 27;
                print_pokecenter();
                break;
        }
    }
}

void print_six_pokemon(int page)
{
    int key = 0;
    int pages = round(ceil(world.pc.pokedex.size() / 6.0));
    string s = to_string(page) + "/" + to_string(int(pages));
    WINDOW *menu = make_screen("PAGE " + s + " OF YOUR POKEDEX");
    keypad(menu, TRUE);
    for (int i = (page - 1) * 6; i < (((page - 1) * 6) + 6); i++) {
        if (i < world.pc.pokedex.size()) print_basic_pokemon_info(world.pc.pokedex.at(i), i, menu);
    }
    wmove(menu, 20, 1);
    whline(menu, ' ', 78);
    wmove(menu, 21, 1);
    whline(menu, ' ', 78);
    wmove(menu, 22, 1);
    whline(menu, ' ', 78);
    mvwprintw(menu, 20, 6, "ENTER THE NUMBER OF THE POKEMON TO TRANSFER, FOLLOWED BY 'enter':");
    mvwprintw(menu, 21, 9, "PRESS THE LEFT AND RIGHT ARROWS TO MOVE THROUGH THE POKEDEX:");
    mvwprintw(menu, 22, 23, "ENTER 'esc' TO EXIT THE POKEDEX:");
    wrefresh(menu);
    s = "a";

    while(key != 27) { // esc
        key = getch();
        switch(key) {
            case 27: // esc
                continue;
            case KEY_LEFT:
                if (page > 1) {
                    print_six_pokemon(page - 1);
                    key = 27;
                }
                // TODO
                break;
            case KEY_RIGHT:
                if (page < pages) {
                    print_six_pokemon(page + 1);
                    key = 27;
                }
                // TODO
                break;
            case KEY_ENTER: // keypad enter
            case 10: // line feed
            case 13: // carriage return
                // print current Pokemon
                if (is_number(s)) {
                    wclear(menu);
                    menu = make_screen("YOUR CURRENT POKEMON:");
                    for (int i = 0; i < world.pc.num_pokemon; i++) {
                        print_basic_pokemon_info(world.pc.p_list[i], i, menu);
                    }
                    wmove(menu, 21, 1);
                    whline(menu, ' ', 78);
                    wmove(menu, 22, 1);
                    whline(menu, ' ', 78);
                    // prompt the user
                    mvwprintw(menu, 22, 13, "ENTER THE NUMBER OF THE POKEMON YOU'D LIKE TO SWAP:");
                    wrefresh(menu);
                    key = 0;
                    // while key is not within 1 - 6
                    while (!(key >= 49 && key <= 54)) {
                        key = getch();
                    }
                    swap_pokemon(key - 49, world.pc.pokedex[stoi(s) - 1], stoi(s) - 1);
                    // print current Pokemon
                    wclear(menu);
                    menu = make_screen("YOUR CURRENT POKEMON:");
                    for (int i = 0; i < world.pc.num_pokemon; i++) {
                        print_basic_pokemon_info(world.pc.p_list[i], i, menu);
                    }
                    wrefresh(menu);
                    usleep(2500000);
                    key = 27;
                    print_pokedex();
                } else s = "a";
                break;
            default:
                if (key >= 48 && key <= 57) {
                    if (s == "a") s = "";
                    s += to_string(key - 48);
                }
                break;
        }
    }
}

void print_pokedex()
{
    int pages = round(ceil(world.pc.pokedex.size() / 6.0));
    if (pages == 0) {
        WINDOW *menu = make_screen("YOUR POKEDEX IS EMPTY!");
        wrefresh(menu);
        usleep(2500000);
        return;
    }
    print_six_pokemon(1);
}

void swap_pokemon(int curr_idx, Pokemon pokedex_p, int pokedex_idx)
{
    if (world.pc.p_list[0].is_defeated()) {
        world.pc.p_list[0].set_is_defeated(false);
        world.pc.p_list[0].set_current_hp(world.pc.p_list[0].get_hp());
    }
    Pokemon temp = world.pc.p_list[curr_idx];
    world.pc.p_list[curr_idx] = pokedex_p;
    world.pc.pokedex[pokedex_idx] = temp;
}

bool is_number(const string &s)
{
    for (int i = 0; i < s.length(); i ++) {
        if (isdigit(s[i]) == 0) return false;
    }

    return true;
}