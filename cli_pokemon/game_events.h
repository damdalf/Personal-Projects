#ifndef GAME_EVENTS_H
#define GAME_EVENTS_H

#include <stdio.h>
#include <stdlib.h>
#include <string>
#include<ncurses.h>

#include "heap.h"
#include "poke327.h"
#include "character.h"
#include "io.h"
#include "db_parse.h"
#include "pokemon.h"

using namespace std;

// function used to illustrate bug bounty
void bug_bounty();
// function to make a screen to be used for game events
WINDOW *make_screen(string title);
// function to print the basic information for all three start pokemons
void print_starter_info(Pokemon p_list[3]);
// function to print the basic information for a single pokemon
void print_basic_pokemon_info(Pokemon p, int p_num, WINDOW *menu);
// function to print the detailed stats for a pokemon during the starter pokemon event
void print_pokemon_starter_stats(Pokemon p);
// function to print the detailed stats for a pokemon
void print_pokemon_stats(Pokemon p);
// function to print the PC's Pokemon list
void print_pokemon_list();
// function to generate a trainer's starting pokemon
void generate_starting_pokemon(Character *c);
// function to calculate the damage done by a Pokemon's move
int calculate_damage_wild(Pokemon *p, int move_idx);
// function to calculate the damage done by an NPC's Pokemon
int calculate_damage_npc(Pokemon p, int move_idx);
// function to calculate the damage done by the PC's Pokemon
int calculate_damage_pc(int move_idx, Pokemon target);
// function to print the battle screen during a wild Pokemon encounter with the PC
void print_pokemon_battle(Pokemon *p);
// function to handle the use of an item, while also updating the number displayed on the screen
void use_item(int item, int poke_idx);
// function to handle switching an NPC's active Pokemon
void switch_pokemon_npc(Npc *npc);
// function to handle switching a Pokemon to the PC's active Pokemon
void switch_pokemon(Pokemon p, int curr_idx);
// function to handle the interface for switching a PC's active Pokemon
void print_switch_pokemon(WINDOW *menu);
// function to print the contents of a PC's bag and handle input
void print_bag(WINDOW *menu);
// function to print the stats of a wild Pokemon during an encounter with the PC
void print_pokemon_encounter(Pokemon *p);
// function to print the screen for actually battling an NPC
void print_trainer_battle(WINDOW *menu, Pc pc, Npc *npc);
// function to print the screen for encountering an NPC
void print_trainer_encounter(Pc pc, Npc *npc);
// function to print the screen for visiting a PokeMart and handling a user's input
void print_pokemart();
// function to print the screen for visiting a PokeCenter and handling a user's input
void print_pokecenter();
// function to print six Pokemon
void print_six_pokemon(int page);
// function to view PC's Pokedex
void print_pokedex();
// function to swap Pokemon from Pokedex to PC's current team of Pokemon
void swap_pokemon(int curr_idx, Pokemon pokedex_p, int pokedex_idx);
// function to determine if a string contains non-numeric values
bool is_number(const string &s);

#endif