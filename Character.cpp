// FILENAME: Character.cpp
// Author: Lan Luu
// Create: 11/01/2024
// Summary: Implementation file for Character class. 
///

#include <algorithm> 
#include <cassert>
#include <iostream>
#include <iomanip>
#include <cstring>
#include <random>
#include <vector>
#include "Character.h"

using namespace std;

/// Character Class Implementation
/**
  // move the class head comment here after finish the program.
**/

Character::Character(const string& a_name, const int a_current_hp, const int a_max_hp,
                      const int a_current_mp, const int a_max_mp, const int a_hp_per_turn,
                      const int a_mp_per_turn, const int a_atk, const int a_def): 
  m_name(a_name), m_current_hp(a_current_hp), m_max_hp(a_max_hp),
  m_current_mp(a_current_mp), m_max_mp(a_max_mp), m_hp_per_turn(a_hp_per_turn),
  m_mp_per_turn(a_mp_per_turn), m_atk(a_atk), m_def(a_def),
  m_spell_slot(1), m_equipment_slot(2), m_tech_slot(1)
{
}

/** DISPLAY
  @Purpose: display the Character information. 
  @param: format: const char.
          pass 'f' as arg for full info.
          pass 'i' as arg for card slot. display inline. 
          default for stat only (HP, MP, ATK, DEF) display inline
**/
bool Character::display(const char format) const
{
  if (format == 'f')
  {
    cout << "/// Name:  " << m_name << endl; 
    cout << "|| HP: " << m_current_hp << " / " << m_max_hp << endl; 
    cout << "|| MP: " << m_current_mp << " / " << m_max_mp << endl; 
    cout << "|| ATTACK: " << m_atk << " pts.\n";
    cout << "|| DEFENSE: " << m_def << " pts.\n";
    cout << "++";
    cout << setfill('-') << setw(m_name.length() + 15) << "\n";
    cout << setfill(' ');
    cout << "|| Spell: " << (!(m_spell_slot.empty())? m_spell_slot.front(): "No Spell Available!") << endl;
    cout << "|| Equipment: " << endl;
    cout << "|| " << (!(m_equipment_slot.empty())? m_equipment_slot.front(): "No Equipment Available!") << endl;
    cout << "|| " << (!(m_equipment_slot.empty())? m_equipment_slot.back(): "No Equipment Available!") << endl;
    cout << "||";
    cout << setfill('_') << setw(m_name.length() + 15) << "\n";
    cout << setfill(' ');
    return true;
  }
  else if(format == 'i')
  {
    cout << "/// " << m_name << " Current Slot:" << endl;
    cout << "|| Spell: " << m_spell_slot.back() << endl;
    cout << "|| Equipment: " << endl;
    cout << "|| slot 1: " << m_equipment_slot.front() << endl;
    cout << "|| slot 2: " << m_equipment_slot.back() << endl;
    cout << "||";
    cout << setfill('_') << setw(m_name.length() + 15) << "\n";
    cout << setfill(' ');
    return true;
  }
  
  cout << "///" << setw(25) << setfill('=') << "\n";
  cout << setfill(' ');
  cout << "| Name: " << m_name << " | HP: " << m_current_hp << " / " << m_max_hp;
  cout << " | MP: " << m_current_mp << " / " << m_max_mp << endl;
  cout << "| ATK: " << m_atk << " / DEF: " << m_def << endl;
  cout << "|==" << setw(25) << setfill('=') << "\n";
  cout << setfill(' ');
  return true;

  return false;
}

/* INCREASE_HP/MP
  Purpose: make change to the hp/mp by the amount provide.
  @precondition: m_current_hp < m_max_hp.
  @postcondition: m_current_hp/mp increase by amount.
  @param: amount, const int. value to add to the hp/mp.
  @return: bool, true if successfully increase, false otherwise.
*/
bool Character::increase_hp(const int amount)
{
  if (m_current_hp < m_max_hp)
  {
    m_current_hp += amount;
    if (m_current_hp > m_max_hp)
      m_current_hp = m_max_hp;
    return true;
  }

  return false;
}

bool Character::increase_mp(const int amount)
{
  if (m_current_mp < m_max_mp)
  {
    m_current_mp += amount;
    if (m_current_mp > m_max_mp)
      m_current_mp = m_max_mp;
    return true;
  }

  return false;
}

/** OBSOLETE
//  PICK
 purpose: add the choosen card to the correct slot.
 @postcondition: add the card picked to the slot. return true if success, false otherwise.
 @param: const Spell &/ const Tech &. 
//
bool Character::pick(const Spell & spell)
{
  if (m_spell_slot.front() == Spell()) // check if Spell_slot contain the default value of Spell
  {
    m_spell_slot[0] = spell;
    return true;
  }
  else // Case when already have Spell card in Spell slot
  {
   // put the current card to discard pile
   // m_spell_slot[0] = spell;
   // return true
  }

  return false;
}

bool Character::pick(const Tech & tech)
{
  if (m_tech_slot.front() == Tech()) // check if Tech_slot contain the default value of Tech
  {
    m_tech_slot[0] = tech;
    return true;
  }
  return false;
}
*/



/* CHECK_MP 
  Purpose: compare current mp with cost of Spell_slot.
  @precondition: Spell_slot contain a Spell Card.
  @postcondition: return true if current mp > cost of Spell_slot, false otherwise.
*/
bool Character::check_mp( ) const
{
  if(!(m_spell_slot.empty()))
  {
    return m_current_mp > m_spell_slot.back().m_cost;
  }

  return false;
}


/*
  CAST_SPELL
  @Purpose: cast the current spell in spell slot
  @precondition: player MP has to larger than Spell Mp cost
  @postcondition: Spell in spell slot is casted, Opp hp is decrease, Card in spell slot is push to discard.
  @return: int, amount of damage Opponent suffer.
*/
bool Character::cast_spell(Character & Opp, DeckManager & deck)
{
  if (m_spell_slot.back( ) != Spell( ) && check_mp( ))
  {
    // Spell is able to cast
    int damage { };
    cout << " Cast " << m_spell_slot.back();
    damage = m_spell_slot.back().m_damage;
    m_current_mp -= m_spell_slot.back().m_cost;
    deck.spell_discard.push_back(m_spell_slot.back());
    m_spell_slot.pop_back();
    Opp.take_damage(damage);
    cout << " The Opponent take " << damage << " pts of damage.";

    return true;
  }

  // Mp not enough
  cout << " Not enough mp to cast!";
  return false;
}


/*
  THE USE_TECH
  @Purpose: use tech card in the tech card slot.
  @precondition: Tech card cannot be empty or equal to Tech()
  @postcondition: The Card in tech_slot is used, card then being send to discard pile. 
                  The useage is based on the trait(keyword) of the tech card.
  @return: true if tech card is sucessful used.
*/ 
bool Character::use_tech(DeckManager & deck )
{
  if (m_tech_slot.back() == Tech( ) || m_tech_slot.empty())
  {
    return false;
  }

  // trait = Heal
  if (strcmp(m_tech_slot.back().m_trait, "Heal") == 0)
  {
    if (increase_hp(m_tech_slot.back().m_value))
      cout << "You are healed " << m_tech_slot.back().m_value << " pts of HP.";
    else
      cout << "You are already at Max HP.";
  }

  // trait = Restore Mp
  if (strcmp(m_tech_slot.back().m_trait, "Restore MP") == 0)
  {
    if (increase_mp(m_tech_slot.back().m_value))
      cout << "You are Restored " << m_tech_slot.back().m_value << " pts of MP.";
    else
      cout << "You are already at Max MP.";
  }

  // IMPLEMENT MORE TRAIT HERE

  // trait = Boost ATK 
  if (strcmp(m_tech_slot.back().m_trait, "Boost ATK") == 0)
  {
    m_atk += m_tech_slot.back().m_value;
    cout << "Your base attack raised " << m_tech_slot.back().m_value << " pts.";
  }
  
  // trait = Boost DEF
  if (strcmp(m_tech_slot.back().m_trait, "Boost DEF") == 0)
  {
    m_def += m_tech_slot.back().m_value;
    cout << "Your base defense raised " << m_tech_slot.back().m_value << " pts.";
  }

  if (strcmp(m_tech_slot.back().m_trait, "Raise Max Hp") == 0)
  {
    m_current_hp += m_tech_slot.back().m_value;
    m_max_hp += m_tech_slot.back().m_value;
    cout << "Your Max Hp Has been increased by " << m_tech_slot.back().m_value << " pts.";
  }

  if (strcmp(m_tech_slot.back().m_trait, "Regen Mp") == 0)
  { 
    m_mp_per_turn += m_tech_slot.back().m_value;
    cout << "Your Mp regen per turn has been increased by " << m_tech_slot.back().m_value << " pts.";
  }
  
  if (strcmp(m_tech_slot.back().m_trait, "Regen Hp") == 0)
  { 
    m_hp_per_turn += m_tech_slot.back().m_value;
    cout << "Your Hp regen per turn has been increased by " << m_tech_slot.back().m_value << " pts.";
  }


  // TRAIT ZONE

  // card to discard here!
  deck.tech_discard.push_back(m_tech_slot.back());
  m_tech_slot.pop_back( );

  return true;
}


/*
  UNEQUIP
  @Purpose: unequip the Equipment slot base on player option
  @precondition: size() == Capacity()
  @postcondition: a equipment slot is being free, Equipment card is moved to discard.
  @Param: the discard pile of equipment
  @Return: true if success.
*/
bool Character::unequip(vector<Equipment> & discard)
{
  char option;
  cout << "Here is your current slot: " << endl;
  display('i');
  cout << "\nWhich Equipment slot you wanted to unequip? (1 or 2) ( 0 to drop the change)";
  cout << " >> ";
  cin >> option;
  if (option != '1' && option != '2' && option != '0')
  {
    cin.clear();
    cin.ignore(1024, '\n');
    cout << "That not a valid option!\n";
    unequip(discard);
  }

  if (option == '1')
  {
    discard.push_back(m_equipment_slot.front());
    // decrease stat
    *this -= m_equipment_slot.front();
    m_equipment_slot.erase(m_equipment_slot.begin());
    return true;
  } else if (option == '2')
  {
    discard.push_back(m_equipment_slot.back());
    // decrease stat
    *this -= m_equipment_slot.back();
    m_equipment_slot.pop_back( );
    return true;
  } 
  
  cout << "\nNo change was made!";
  return false;
}

/* CALCULATE DAMAGE
  Purpose: calculate the amount of damage the player will suffer based on both player current stat.
  @precondition: 
  @postcondition: return the damage the Opponent will take after calculation.
  @param: const Character &, the target that will take the damage.
*/
int Character::calculate_damage(const Character & Opp) const
{
  if (Opp.m_def >= m_atk)
    return 0;
  return m_atk - Opp.m_def;
}


/* TAKE_DAMAGE 
  Purpose: Decrease the current_hp to the amount of damage. 
  @precondition:  
  @postcondition: decrease the amount of hp to current hp. 
  @param: const int, the amount of hp that will subtract from current hp
*/
bool Character::take_damage(const int amount)
{
  if (m_current_hp < amount)
  {
    m_current_hp = 0;
    return true;
  } 
  else
  {
    m_current_hp -= amount;
    return true;
  }

  return false;
}

/*
  Is_lost
  @purpose: set true if player HP reach 0, game over for you!
*/
bool Character::is_lost( ) const
{
  if(m_current_hp <= 0)
    return true;
  return false;
}

/*
  Pass_turn
  @purpose: applied linger effect such as mp/hp per turn
  @return: true if function execute
*/
bool Character::pass_turn()
{
  if (m_hp_per_turn > 0)
    increase_hp(m_hp_per_turn);
  if (m_mp_per_turn > 0)
    increase_mp(m_mp_per_turn);
  return true;
}

/*
  GETTER TO ASSCESS TO VECTOR DATA
*/
vector<Spell>& Character::get_spell_slot()
{
  return m_spell_slot;
}

vector<Equipment>& Character::get_equipment_slot()
{
  return m_equipment_slot;
}

vector<Tech>& Character::get_tech_slot()
{
  return m_tech_slot;
}

/*
  OPERATOR OVERLOAD
*/
Character& Character::operator=(const Character & source)
{
  if (this == &source)
    return *this;

  // deallocate

  // assign new value
  m_name = source.m_name;
  m_current_hp = source.m_current_hp;
  m_max_hp = source.m_max_hp;
  m_current_mp = source.m_current_mp;
  m_max_mp = source.m_max_mp;
  m_hp_per_turn = source.m_hp_per_turn;
  m_mp_per_turn = source.m_mp_per_turn;
  m_atk = source.m_atk;
  m_def = source.m_def;
  m_spell_slot = source.m_spell_slot;
  m_equipment_slot = source.m_equipment_slot;
  m_tech_slot = source.m_tech_slot;
  return *this; 
}

bool Character::operator==(const Character & op2)
{
  return  m_name == op2.m_name &&
          m_current_hp == op2.m_current_hp &&
          m_max_hp == op2.m_max_hp &&
          m_current_mp == op2.m_current_mp &&
          m_max_mp == op2.m_max_mp &&
          m_hp_per_turn == op2.m_hp_per_turn &&
          m_mp_per_turn == op2.m_mp_per_turn &&
          m_atk == op2.m_atk &&
          m_def == op2.m_def;
}

bool Character::operator!=(const Character & op2)
{
  return !(*this == op2);
}

Character& Character::operator+=(const Equipment & op2)
{
  m_atk += op2.m_atk;
  m_def += op2.m_def;
  return *this;
}

Character& Character::operator-=(const Equipment & op2)
{
  m_atk -= op2.m_atk;
  m_def -= op2.m_def;
  return *this;
}

ostream& operator<<(ostream& out, const Character & op2)
{
  if (!out)
    throw ios_base::failure("Output stream error with Character Object!\n");
  out << " [" << op2.m_name << "] ";  
  return out;
}

/// END OF CHARACTER CLASS IMPLEMENTAION





/*
  DECKMANAGER CLASS
*/
DeckManager::DeckManager( )
{
}

DeckManager::DeckManager(Deck<Spell>& s_deck, Deck<Equipment>& e_deck, Deck<Tech> t_deck): spell_deck(s_deck), equipment_deck(e_deck), tech_deck(t_deck)
{
}


/*
  THE DRAW FUNCTION
  @Purpose: draw card from specific deck.
  @precondtion: Deck cannot be empty.
  @postcondition: return by value a card at the end of the deck, card then being pop from the deck.
*/
Spell DeckManager::draw_spell( )
{
  assert(!(spell_deck.empty()));    // check if deck is empty
  Spell to_draw;                    // a variable to store the return value
  to_draw = spell_deck.back().get_data(); // back() output the last node in the DLL, get_data() to access to the card data (Data_Structure.h)
  spell_deck.pop_back( );           // remove the last node in the deck
  return to_draw;
}

Equipment DeckManager::draw_equipment( )
{
  assert(!(equipment_deck.empty()));
  Equipment to_draw;
  to_draw = equipment_deck.back().get_data();
  equipment_deck.pop_back( );
  return to_draw;
}

Tech DeckManager::draw_tech( )
{
  assert(!(tech_deck.empty()));
  Tech to_draw;
  to_draw = tech_deck.back().get_data();
  tech_deck.pop_back( );
  return to_draw;
}

// END OF DRAW FUNCTION



/*
  THE DISCARD FUNCTION
  @Purpose: send the specific card to the discard pile.
  @precondtion: 
  @postcondtion: a card is add to the discard pile.
  @return: true if the card is successful added to the discard pile, false otherwise.
*/
bool DeckManager::discard(Spell & to_discard)
{
  if (to_discard == Spell( ))   // the card that going to be discard is a default card value (no card)
    return false;

  spell_discard.push_back(to_discard);
  return true;
}

bool DeckManager::discard(Equipment & to_discard)
{
  if (to_discard == Equipment( ))   // the card that going to be discard is a default card value (no card)
    return false;

  equipment_discard.push_back(to_discard);
  return true;
}

bool DeckManager::discard(Tech & to_discard)
{
  if (to_discard == Tech( ))   // the card that going to be discard is a default card value (no card)
    return false;

  tech_discard.push_back(to_discard);
  return true;
}

// END OF THE DISCARD FUNCTION


/*
  THE SHUFFLE FUNCTION
  @Purpose: shuffle the deck (if deck is not empty) or the discard pile.
  @precondition:
  @postcondition: deck/ discard is shuffle.
  @return: true if shuffle, false otherwise.
*/
bool DeckManager::shuffle_spell( )
{
  // generate a random seed
  static bool initialized {false};
  static mt19937 generator;     // Mersenne Twister

  // Initialized a random seed if not already been done
  if (!initialized)
  {
    random_device rd;
    generator.seed(rd());
    initialized = true;
  }

  if (spell_deck.empty())
  {
    std::shuffle(spell_discard.begin(), spell_discard.end(), generator);
    return true;
  } 
  else
  {
    spell_deck.shuffle_deck();
    return true;
  }

  return false;
}

bool DeckManager::shuffle_equipment( )
{
  // generate a random seed
  static bool initialized {false};
  static mt19937 generator;     // Mersenne Twister

  // Initialized a random seed if not already been done
  if (!initialized)
  {
    random_device rd;
    generator.seed(rd());
    initialized = true;
  }

  if (equipment_deck.empty())
  {
    std::shuffle(equipment_discard.begin(), equipment_discard.end(), generator);
    return true;
  } 
  else
  {
    equipment_deck.shuffle_deck();
    return true;
  }

  return false;
}

bool DeckManager::shuffle_tech( )
{
  // generate a random seed
  static bool initialized {false};
  static mt19937 generator;     // Mersenne Twister

  // Initialized a random seed if not already been done
  if (!initialized)
  {
    random_device rd;
    generator.seed(rd());
    initialized = true;
  }

  if (tech_deck.empty())
  {
    std::shuffle(tech_discard.begin(), tech_discard.end(), generator);
    return true;
  } 
  else
  {
    tech_deck.shuffle_deck();
    return true;
  }

  return false;
}


// END OF SHUFFLE FUNCTION



/*
    THE FILL FUNCTION
    @Purpose: fill the deck with card from the discard pile of the same type.
    @precondition: 
    @postcondition: a card is added to the deck from the back, and the card with same value is pop from the discard pile.
    @return: true if deck is successfully filled, false otherwise.
*/
bool DeckManager::fill_spell_deck(Deck<Spell>& deck, vector<Spell>& discard)
{
  if (discard.empty())
    return true;

  deck.add_card(discard.back());
  discard.pop_back();

  return fill_spell_deck(deck, discard);
}

bool DeckManager::fill_equipment_deck(Deck<Equipment>& deck, vector<Equipment>& discard)
{
  if (discard.empty())
    return true;

  deck.add_card(discard.back());
  discard.pop_back();

  return fill_equipment_deck(deck, discard);
}

bool DeckManager::fill_tech_deck(Deck<Tech>& deck, vector<Tech>& discard)
{
  if (discard.empty())
    return true;

  deck.add_card(discard.back());
  discard.pop_back();

  return fill_tech_deck(deck, discard);
}



/*
  THE SHOW_OPTION_BOX FUNCTION
  @Purpose: display the option box to player to choose a card to keep
  @precondition: Deck has to be initialized 
  @postcondition: and option box contain 3 card is present to player
  @param: Character& player, the current player that option is showed to. 
  @return: true if option is show successfully
*/
bool DeckManager::show_option_box(Character & player)
{
  Spell     spell_option;
  Equipment equipment_option;
  Tech      tech_option;
  char      choice;

  // check deck is empty, and shuffle discard to deck if it is empty
  // check spell deck
  if(spell_deck.empty())
  {
    shuffle_spell();
    fill_spell_deck(spell_deck, spell_discard);
  } 

  // check equipment deck
  if(equipment_deck.empty())
  {
    shuffle_equipment();
    fill_equipment_deck(equipment_deck, equipment_discard);
  } 
 
  // check tech deck
  if(tech_deck.empty())
  {
    shuffle_tech();
    fill_tech_deck(tech_deck, tech_discard);
  } 

  // draw card from each deck
  spell_option = draw_spell( );
  equipment_option = draw_equipment( );
  tech_option = draw_tech( );

  // display the option_box
  cout << "You Draw:\n\n";
  spell_option.display('f');
  cout << endl;
  equipment_option.display('f');
  cout << endl;
  tech_option.display('f');
  cout << endl;
  
  // get user input
  cout << "\tPlease choose to keep one:\n";
  cout << "[1. Spell] - [2. Equipment] - [3. Tech]\n";
  cout << " >> ";
  choice = get_user_option( );

  // Check option
  switch (choice)
  {
    case '1': // picked Spell card
      if (player.get_spell_slot().empty())  // check slot empty
      {
        player.get_spell_slot().push_back(spell_option); // if slot empty, simply assign the card to slot
      } else
      {
        spell_discard.push_back(player.get_spell_slot().back());  // push the old card to discard
        player.get_spell_slot().pop_back( );                      // remove the old card
        player.get_spell_slot().push_back(spell_option);          // assign the new card
      }

      // discard the other two option
      equipment_discard.push_back(equipment_option);
      tech_discard.push_back(tech_option);
      break;

    case '2': // Picked Equipment Card
      if (player.get_equipment_slot().empty())    // check if slot empty
      {
        player.get_equipment_slot().push_back(equipment_option);
        player += equipment_option;
      } 
      else if (player.get_equipment_slot().size() < player.get_equipment_slot().capacity()) // check if there other slot available
      {
        player.get_equipment_slot().push_back(equipment_option);
        player += equipment_option;
      }
      else  // no slot free
      {
        if (player.unequip(equipment_discard)) // prompt user to remove an equipment slot
        {
          player.get_equipment_slot().push_back(equipment_option);    // add to the freed equipment slot
          player += equipment_option;
        }
        else // no change was made
          equipment_discard.push_back(equipment_option); // discard the equipment option 
      }
     
      // discard the other 2 option
      spell_discard.push_back(spell_option);
      tech_discard.push_back(tech_option);
      break;

    case '3': // Picked Tech Card
        player.get_tech_slot().push_back(tech_option);
        // discard the other 2 option
        spell_discard.push_back(spell_option);
        equipment_discard.push_back(equipment_option);
      break;

    default: cout << "That is not a valid option!\n";
  }

  return true;
}


/*
  GET_USER_OPTION
  @Purpose: an recursive helper function to help get user input
*/
char DeckManager::get_user_option( ) const
{
  char choice;
  
  cin >> choice;

  if (choice == '1' || choice == '2' || choice == '3')
    return choice;
  
  cin.clear();
  cin.ignore(1024, '\n');
  cout << "Please select a valid option: (1 , 2, 3): ";
  return get_user_option( );
}
