// FILENAME: Character.h
// Author: Lan Luu
// Create: 10/31/2024
// Summary: header file for Character class. 
// Purpose: create a Character instance, act as a avatar for player. 
#ifndef CHARACTER_H
#define CHARACTER_H

#include <string>
#include <vector>
#include "Card.h"
#include "Data_Structure.h"
 
using namespace std;

class DeckManager; // Forward declaration

/// Character Class
/////////////////////////////////////////////////////////////////////
// Summary: Represents a character in the game with attributes and methods
//          to manage health, mana, and equipment.
//
// Data Members:
//  - m_name: std::string, name of the character, input from user.
//  - m_current_hp: int, current HP remaining; starts equal to m_max_hp.
//  - m_max_hp: int, maximum HP the character can have; healing cannot exceed this value.
//  - m_current_mp: int, current MP remaining; starts at 0.
//  - m_max_mp: int, maximum MP the character can have; MP cannot exceed this value.
//  - m_hp_per_turn: int, continuous HP change per turn (increase or decrease); starts at 0.
//  - m_mp_per_turn: int, continuous MP change per turn (increase or decrease); starts at 1.
//  - m_atk: int, attack stat of the character; starts at 1 and is affected by equipment cards.
//  - m_def: int, defense stat of the character; starts at 1 and is affected by equipment cards.
//  - m_spell_slot: std::vector<Spell>, size 1; contains the current spell card, castable when MP is sufficient.
//  - m_equipment_slot: std::vector<Equipment>, size 2; contains the current equipment cards, main way to alter character stats.
//  - m_tech_slot: std::vector<Tech>, size 1; contains the tech card, used immediately during the resolve stage.
//
// Methods:
//  - display: bool; displays character info. Use 'f' for full display, default for stats (HP, MP, ATK, DEF) in line,
//             'i' for current spell and equipment slots.
//  - increase_hp: bool; increases character HP by a specified amount.
//  - increase_mp: bool; increases character MP by a specified amount.
//  - check_mp: bool; compares current MP with the cost of the spell in the spell slot; returns true if current MP >= cost.
//  - cast_spell: int; casts the current spell; returns the damage of the spell and frees the spell slot.
//  - unequip: bool; unequips the current equipment card; adjusts stats accordingly.
//  - use_tech: bool; uses the current tech card in the tech slot; checks traits and applies values.
//  - calculate_damage: int; calculates damage dealt to the opponent based on character ATK and opponent's DEF.
//  - take_damage: bool; decreases current HP by the specified damage amount.
//  - is_lost: bool; return true, if player HP is <= 0;
//  - operator=: Character&; assigns the target value to this character.
//  - operator+=, -=: Character&; increases or decreases character ATK and DEF.
//  - operator==, !=: bool; compares two characters for equality.
//  - friend operator<<: ostream&; displays character data to an output stream.
//
/////////////////////////////////////////////////////////////////////
class Character
{
  public:
  // CONTRUCTOR & DESTRUCTOR
    Character(const string& init_name=" ", const int init_current_hp=0, const int init_max_hp=0,
              const int init_current_mp=0, const int init_max_mp=0, const int init_hp_per_turn=0,
              const int init_mp_per_turn=0, const int init_atk=0, const int init_def=0);
 
  // METHOD
    bool display(const char format=' ') const;
    bool increase_hp(const int amount); 
    bool increase_mp(const int amount);
    //bool pick(const Spell & to_pick);
    //bool pick(const Tech & to_pick);
    bool check_mp( ) const;
    bool cast_spell(Character & Opp, DeckManager & deck);
    //bool equip( const Equipment & to_equip);
    bool unequip(vector<Equipment>& equipment_discard );
    bool use_tech(DeckManager & deck );
    int calculate_damage(const Character & Opp) const;
    bool take_damage(const int amount);
    bool is_lost() const;
    bool pass_turn( );
    vector<Spell>& get_spell_slot();
    vector<Equipment>& get_equipment_slot();
    vector<Tech>& get_tech_slot();

  // OPERATOR OVERLOADIN
    Character& operator=(const Character & source);
    bool operator==(const Character & op2);
    bool operator!=(const Character & op2);
    Character& operator+=(const Equipment & op2);
    Character& operator-=(const Equipment & op2);
    friend ostream& operator<<(ostream& out, const Character & op2);

  protected:
    string m_name;
    int m_current_hp;
    int m_max_hp;
    int m_current_mp;
    int m_max_mp;
    int m_hp_per_turn;
    int m_mp_per_turn;
    int m_atk;
    int m_def;
    vector<Spell> m_spell_slot;
    vector<Equipment> m_equipment_slot;
    vector<Tech> m_tech_slot;
};



/// DeckManager Class
/////////////////////////////////////////////////////////////////////
/// Summary:  Class to manage three different type of decks, 
//            and 3 discard piles of the same type. 
//            This class will handle the draw, discard from each deck.
//            Main purpose is to display an option box of 3 card for player to choose from.
//
/// Data Member:
//    - Deck<Spell> spell_deck: Deck contain spell card.
//    - Deck<Equipment> equipment_deck: Deck contain Equipment card.
//    - Deck<Tech>  tech_deck: Deck contain Tech Card.
//    - vector<Spell> spell_discard: discard piles for spell card.
//    - vector<Equipment> equipment_discard: discard piles for Equipment card.
//    - vector<Tech>  tech_discard: discard piles for Tech Card.
//
/// Methods:
//    - show_option_box(): display the card draw from 3 deck. user choose 1 to keep.
//    - pick_a_card(Character & player): get user option, assign card to correct slot.
//    - draw_spell: draw a spell card from spell deck.
//    - draw_equipment: draw a equipment card from equipment deck.
//    - draw_tech: draw a tech card from a tech deck.
//    - discard(Spell & to_discard): discard the card to spell discard pile.
//    - discard(Equipment & to_discard): discard the card to equipment discard pile.
//    - discard(Tech & to_discard): discard the card to tech discard pile.
//    - shuffle_spell(): shuffle the spell discard pile
//    - shuffle_equipment(): shuffle the equipment discard pile
//    - shuffle_tech(): shuffle the tech discard piles.
//    - fill_spell_deck(Deck<Spell>& deck, vector<Spell>& discard): fill the empty deck with card from discard piles.
//    - fill_equipment_deck(Deck<Equipment>& deck, vector<Equipment>& discard): fill the empty deck with card from discard piles.
//    - fill_tech_deck(Deck<Tech>& deck, vector<Tech>& discard): fill the empty deck with card from discard piles.
//
/////////////////////////////////////////////////////////////////////
class DeckManager
{
  public:
  // CONSTRUCTOR
    DeckManager( );
    DeckManager(Deck<Spell>& s_deck, Deck<Equipment>& e_deck, Deck<Tech> t_deck);

  // METHOD:
    // Draw function
    Spell draw_spell( );
    Equipment draw_equipment( );
    Tech draw_tech( );

    // discard function
    bool discard(Spell & to_discard);
    bool discard(Equipment & to_discard);
    bool discard(Tech & to_discard);
    
    // Shuffle function
    bool shuffle_spell( );
    bool shuffle_equipment( );
    bool shuffle_tech( );

    // fill function
    bool fill_spell_deck(Deck<Spell>& deck, vector<Spell>& discard);
    bool fill_equipment_deck(Deck<Equipment>& deck, vector<Equipment>& discard);
    bool fill_tech_deck(Deck<Tech>& deck, vector<Tech>& discard);

    //Option_box
    bool show_option_box(Character & player);


  protected:
    Deck<Spell> spell_deck;
    Deck<Equipment> equipment_deck;
    Deck<Tech> tech_deck;
    vector<Spell> spell_discard;
    vector<Equipment> equipment_discard;
    vector<Tech> tech_discard;

    friend class Character;

    // Helper function
    char get_user_option( ) const;
};

#endif
