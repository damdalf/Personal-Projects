#ifndef POKEMON_H
# define POKEMON_H

# include <iostream>

enum pokemon_stat {
  stat_hp,
  stat_atk,
  stat_def,
  stat_spatk,
  stat_spdef,
  stat_speed
};

enum pokemon_gender {
  gender_female,
  gender_male
};

class Pokemon {
 private:
  int level;
  // int pokemon_index;
  int move_index[4];
  int pokemon_species_index;
  int IV[6];
  int effective_stat[6];
  bool shiny;
  pokemon_gender gender;
  int current_hp;
  bool defeated;
 public:
  Pokemon();
  Pokemon(int level);
  const char *get_species() const;
  int get_hp() const;
  int get_current_hp() const;
  bool is_defeated() const;
  int get_atk() const;
  int get_def() const;
  int get_spatk() const;
  int get_spdef() const;
  int get_speed() const;
  int get_level() const;
  int get_iv(int stat) const;
  int get_base_speed() const;
  const char *get_gender_string() const;
  bool is_shiny() const;
// accepts a parameter, probably denoting which move to be used
  const char *get_move(int i) const;
  int get_move_id(int i) const;
  int get_species_idx() const;
  void set_current_hp(int hp);
  void set_is_defeated(bool b);
  std::ostream &print(std::ostream &o) const;
};

std::ostream &operator<<(std::ostream &o, const Pokemon &p);

#endif
