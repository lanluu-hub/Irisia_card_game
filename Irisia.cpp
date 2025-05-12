// FILENAME: Luu_Lan_Program_2.cpp
// Author: Lan Luu
// Create: 10/29/2024
// Summary: Program to play Irisia, a pvp turn-based card game.
#include <ctime>
#include <cstdlib>
#include <iostream>
#include <stdexcept>
#include "Card.h"
#include "Character.h"
#include "Data_Structure.h"

using namespace std;
/*
  Display intro
*/
void intro( );

/*
  Generate deck
*/
void generate_deck(Deck<Spell>& , Deck<Equipment>&, Deck<Tech>& );

/*
  Shuffle deck
*/
void shuffle_deck(Deck<Spell>& , Deck<Equipment>& , Deck<Tech>& );

/*
  Turn decision
*/
int decide_turn( );

/*
  Create Character
*/
void create_character(Character & player);

/*
  Play_turn
*/
bool play_turn(Character & player, Character & Opponent, DeckManager & deck_system, const int turn);

/*
  End_game
*/
void end_game(Character & player1, Character & player2);

// Helper Fucntion
string input(const string& prompt);
void pause( );

int main()
{
  try {
    // Create Deck of each type
    Deck<Spell> spellDeck;
    Deck<Equipment> equipmentDeck;
    Deck<Tech> techDeck;

    // display intro
    intro( );

    // Populate deck
    generate_deck(spellDeck, equipmentDeck, techDeck);
/*
    spellDeck.display();
    pause();
*/
    // Shuffle the deck
    shuffle_deck(spellDeck, equipmentDeck, techDeck);
/*
    spellDeck.display();
    pause();
*/
    // generate deck holder system
    DeckManager deck_system(spellDeck, equipmentDeck, techDeck);


    // prompt user to enter Character name
    string player1_name = input("\nPlease enter what your Character would be called: ");
    string player2_name = input("\nPlease enter what your Character would be called: ");


    // Create Character
    Character player1(player1_name, 20, 20, 0, 20, 0, 1, 1, 1);
    Character player2(player2_name, 20, 20, 0, 20, 0, 1, 1, 1);

    Character * go_first;
    Character * go_second;

    // Throw dice decided who goes first
    if (decide_turn( ) == 1)   // Player 1 win the dice roll
    {
      cout << player1 << " Will Go first!\n";
      go_first = &player1;
      go_second = &player2;
    }
    else                    // Player 2 win the dice roll
    {
      cout << player2 << " Will Go first!\n";
      go_first = &player2;
      go_second = &player1;
    }

    pause( );

    cout << "\nHere is two player:\n";
    cout << "GO FIRST:\n";
    go_first->display('f');
    cout << endl;
    cout << "GO SECOND:\n";
    go_second->display('f');

    cout << "\n\t <<Press any key to start the game!>>" << endl;
    pause( );

    try {
      // turn loop
      cout << "\nGAME START!!!" << endl;
      int turn = 1;
      bool gameOver {false};
      while (gameOver == false)
      {
        cout << "[ Turn " << turn << " ]\n";
        if (turn % 2 != 0)
        {
          gameOver = play_turn(*go_first, *go_second, deck_system, turn);
        }
        else
        {
          gameOver = play_turn(*go_second, *go_first, deck_system, turn);
        }
        ++turn;
      }
    }
    catch (const invalid_argument& err)
    {
     cerr << "Error: " << err.what() << endl;
    }

    catch (const ios_base::failure& err)
    {
      cerr << "Stream error: " << err.what() << endl;
    }

    catch (const exception& err)
    {
      cerr << "Unexpected error: " << err.what() << endl;
      //gameOver = true;
    }

    end_game(player1, player2);
    cout << endl << endl;
  }
  catch (const exception& err)
  {
    cerr << "Fatal Error: " << err.what() << endl;
  }




/***********************************************
TEST PORTION
//TEST DECK
  Deck<Spell> spell_deck;
  Deck<Equipment> equipment_deck;
  Deck<Tech> tech_deck;
  Character player("Hero", 95, 100, 50, 50, 5, 3, 15, 10);
  Character player2("Demon", 95, 100, 50, 50, 5, 3, 15, 10);

  for (int idx = 0; idx < 5; ++idx)
  {
    Spell spell("001", "Fire Ball", Card::Spell, "An Powerful Fire element spell.", 2, 4);
    spell_deck.add_card(spell);
  }
  Spell spell1("002", "Ice Shard", Card::Spell, "A chilling spell that pierces enemies.", 3, 5);
  spell_deck.add_card(spell1);
  Spell spell2("003", "Lightning Strike", Card::Spell, "A quick bolt of lightning that stuns.", 4, 6);
  spell_deck.add_card(spell2);
  Spell spell3("004", "Earthquake", Card::Spell, "A powerful spell that shakes the ground.", 5, 8);
  spell_deck += spell3;
  cout << "\nDeck size: " << spell_deck.size( );
  spell_deck.shuffle_deck( );
  cout << "\nDeck size afer shuffle: " << spell_deck.size( );
  //deck.shuffle_spell( );
  // First equipment
  Equipment equip1("002", "Sword", Card::Equipment, "Basic Sword That sells everywhere.", 3, 0);
  equipment_deck.add_card(equip1);

  // Second equipment
  Equipment equip2("003", "Shield", Card::Equipment, "Sturdy Shield for protection.", 5, 1);
  equipment_deck.add_card(equip2);

  // Third equipment
  Equipment equip3("004", "Potion", Card::Equipment, "Heals 50 HP.", 2, 5);
  equipment_deck.add_card(equip3);

  // Fourth equipment
  Equipment equip4("005", "Bow", Card::Equipment, "A basic bow for ranged attacks.", 4, 0);
  equipment_deck.add_card(equip4);

  // add tech card
  Tech tech1("001", "Health Potion", Card::Tech, "A small health potion", 5, "Heal");
  tech_deck.add_card(tech1);

  Tech tech2("002", "Mana Potion", Card::Tech, "A small mane potion", 5, "Restore MP");
  tech_deck.add_card(tech1);


  DeckManager deck(spell_deck, equipment_deck, tech_deck);

  deck.show_option_box(player);
  cout << endl;
  deck.show_option_box(player);
  player.cast_spell(player2, deck);
  cout << player2;

  // test use_tech
  player.use_tech(deck);

  player.display('f');
  //cout << player;


  Spell draw_test;
  draw_test = deck.draw_spell();
  deck.discard(draw_test);
  draw_test.display('f');
  cout << endl;
  deck.shuffle_spell();
  deck.shuffle_equipment();


  cout << "\nYou draw " << spell_deck.back().get_data().display('f');
  spell_deck.pop_back();
  cout << "\nYou draw " << spell_deck.back().get_data().display('f');
  cout << "\nDeck size: " << spell_deck.size( );
  spell_deck.clear();
  cout << "\nDeck size: " << spell_deck.size( );

// TEST CHARACTER
  Spell spell1("001", "Fire Ball", Card::Equipment, "An Powerful Fire element spell.", 2, 4);
  Character player("Hero", 95, 100, 50, 50, 5, 3, 15, 10);
  Equipment equip("002", "Sword", Card::Equipment, "Basic Sword That sells every where.", 3, 0);
  cout << spell1 << endl;
  cout << equip << endl;
  player.pick(spell1);
  player.display('f');

  if(player.increase_hp(10))
    cout << "You are heal\n";
  else
    cout << "You already at full Hp\n";
  if (player.check_mp())
    cout << "Has enought MP!\n";
  else
    cout << "No Mp\n";
*/

/**
// TEST TECH
  Tech tech;
  Tech tech1("001", "Health Potion", Card::Tech, "A small health potion", 5, "Heal");

  tech.display();
  cout << endl;
  tech1.display('f');
  cout << endl;
  tech = tech1;
  cout << tech << endl;
  Equipment equip("002", "Sword", Card::Equipment, "Basic Sword That sells every where.", 3, 0);

  Equipment equip_copy;
  equip_copy = equip;
  equip_copy.display('f');
  //equip.display();
  if (equip == equip_copy)
    cout << "It THE SAME!";
  else
    cout << "IT NOT THE SAME!";
//TEST SPELL
  Spell spell1("001", "Fire Ball", Card::Spell, "An Powerful Fire element spell.", 2, 4);
  Spell spell_copy(spell1);

  spell_copy.display('f');
  spell1.display('f');
  cout << "This is an inline display: " << spell1;
  if (spell1 == spell_copy)
    cout << "\nEqual" << endl;
  else
    cout << "\nNOT Equal\n";
  spell1.display();

  Card object("001", "Fire Ball", Card::Spell, "An Powerful Fire element spell.");
  Card object_copy(object);
  Card object_2;
  object_2 = object;

  object.display('f');
  cout << "this is inline display ";
  object.display();
  cout << endl;

  object_2 < object;
  cout << "\nThis is another inline test " << object << endl;
  cin >> object_copy;
  object_copy.display('f');
**/
  return 0;
}



void intro( )
{
  cout << "\t\tIRISIA: SIMPLE CARD GAME" << endl;
  cout << "Welcome to \"Irisia'\", a world of Sword and Magic dominance!" << endl;
  cout << "In this turn-based card game, you must reduce your opponent’s health to zero before they do the same to you." << endl;
  cout << "Draw cards from three decks—Spells, Equipment, and Tech—and use them to outsmart your enemy." << endl;
  cout << "Cast powerful spells, equip mighty weapons, or use tech such as potion to gain the edge." << endl;
  cout << "Your choices will shape the battle. Ready yourself, champion!" << endl;
}




void generate_deck(Deck<Spell>& s_deck, Deck<Equipment>& e_deck, Deck<Tech>& t_deck)
{
  // Populate Spell Deck with Spell
  for (int idx = 0; idx < 4; ++idx)
  {
    // Tier 1: Novice Spells
    s_deck.add_card(Spell("001", "Fire Ball", Card::Spell, "A basic fireball that deals moderate fire damage.", 2, 4));  // Tier 1
    s_deck.add_card(Spell("002", "Ice Spike", Card::Spell, "A sharp spike of ice that deals moderate cold damage.", 2, 3));
    s_deck.add_card(Spell("003", "Lightning Bolt", Card::Spell, "A bolt of lightning that zaps the enemy.", 3, 4));
    s_deck.add_card(Spell("004", "Flame Lash", Card::Spell, "A lash of flames that strikes the enemy.", 3, 5));

    // Tier 2: Apprentice Spells
    s_deck.add_card(Spell("005", "Fireball Volley", Card::Spell, "A rapid barrage of fireballs that deal fire damage.", 5, 6));  // Tier 2
    s_deck.add_card(Spell("006", "Icicle Storm", Card::Spell, "A storm of icy shards that pierce the enemy.", 5, 7));
    s_deck.add_card(Spell("007", "Chain Lightning", Card::Spell, "Lightning that arcs to multiple targets.", 6, 8));

    // Tier 3: Adept Spells
    s_deck.add_card(Spell("008", "Meteor Shower", Card::Spell, "A barrage of meteors that rains down and deals fire damage.", 7, 9));  // Tier 3
    s_deck.add_card(Spell("009", "Dragon Breath", Card::Spell, "A massive cone of fire that devastates enemies.", 8, 10));

    // Tier 4: Expert Spells
    s_deck.add_card(Spell("010", "Supernova", Card::Spell, "A fiery explosion that burns everything in its path.", 9, 12));  // Tier 4
  }



  // Populate Equipement Deck with Equipment
  for (int idx = 0; idx < 4; ++idx)
  {
    // Tier 1: Novice Equipment (Common, single stat focus)
    e_deck.add_card(Equipment("030", "Rusty Shortsword", Card::Equipment, "A worn-out sword, common in small villages.", 3, 0));
    e_deck.add_card(Equipment("031", "Wooden Buckler", Card::Equipment, "A small, wooden shield, often used by beginners.", 0, 3));
    e_deck.add_card(Equipment("032", "Traveler's Dagger", Card::Equipment, "A simple dagger, a common tool for travelers.", 2, 0));
    e_deck.add_card(Equipment("033", "Ragged Leather Vest", Card::Equipment, "A basic vest made of leather, offers some protection.", 0, 4));

    // Tier 2: Apprentice Equipment (Uncommon, mixed or single stat focus)
    e_deck.add_card(Equipment("034", "Ironclad Sword", Card::Equipment, "A sword crafted from solid iron, sharp enough for a fight.", 4, 0));
    e_deck.add_card(Equipment("035", "Bronze Shield", Card::Equipment, "A sturdy bronze shield with a slightly tarnished surface.", 0, 5));
    e_deck.add_card(Equipment("036", "Sturdy Leather Armor", Card::Equipment, "Light but tough armor that provides good defense.", 0, 6));
    e_deck.add_card(Equipment("037", "Mace of the Guild", Card::Equipment, "A blunt weapon used by guild warriors, designed for crushing.", 5, 0));

    // Tier 3: Adept Equipment (Rare, strong single stat or mixed stat)
    e_deck.add_card(Equipment("038", "Silverblade", Card::Equipment, "A beautifully crafted silver sword with a gleaming edge.", 6, 0));
    e_deck.add_card(Equipment("039", "Golden Guard Shield", Card::Equipment, "A large, golden shield that can withstand most attacks.", 0, 7));
    e_deck.add_card(Equipment("040", "Plated Battle Armor", Card::Equipment, "Armor forged with steel plates, providing superior protection.", 0, 8));

    // Tier 4: Legendary Equipment (Epic, high stat boosts, mixed stats)
    e_deck.add_card(Equipment("041", "Warhammer of the North", Card::Equipment, "A mighty warhammer, said to have once been wielded by a king.", 7, 0));
    e_deck.add_card(Equipment("042", "Sword of the Phoenix", Card::Equipment, "Forged from the flames of a dying star, this sword brings fire with every strike.", 8, 4));
  }

  // Populate Tech Deck with Tech
  for (int idx = 0; idx < 3; ++idx)
  {
    // Tier 1: Basic Tech (Common, low impact)
    t_deck.add_card(Tech("061", "Health Potion", Card::Tech, "Restores a small amount of health.", 3, "Heal"));  // Heal (3)
    t_deck.add_card(Tech("062", "Mana Draught", Card::Tech, "Restores a small amount of MP.", 2, "Restore MP"));  // Restore MP (2)
    t_deck.add_card(Tech("063", "Iron Elixir", Card::Tech, "Boosts attack for a short period.", 1, "Boost ATK"));  // Boost ATK (1)
    t_deck.add_card(Tech("064", "Shielding Tincture", Card::Tech, "Boosts defense for a short period.", 1, "Boost DEF"));  // Boost DEF (1)
    t_deck.add_card(Tech("065", "Health Regenerator", Card::Tech, "Heals 1 HP per turn for the next 2 turns.", 1, "Regen Hp"));  // Regen Hp (1 per turn for 2 turns)
    t_deck.add_card(Tech("066", "Mana Tonic", Card::Tech, "Restores 1 MP per turn for the next 2 turns.", 1, "Regen Mp"));  // Regen Mp (1 per turn for 2 turns)
  }
  for (int idx = 0; idx < 2; ++idx)
  {
    // Tier 2: Intermediate Tech (Uncommon, moderate impact)
    t_deck.add_card(Tech("067", "Greater Health Potion", Card::Tech, "Restores a medium amount of health.", 6, "Heal"));  // Heal (6)
    t_deck.add_card(Tech("068", "Elixir of Mana", Card::Tech, "Restores a moderate amount of MP.", 4, "Restore MP"));  // Restore MP (4)
    t_deck.add_card(Tech("069", "Potion of Strength", Card::Tech, "Increases attack permanently.", 1, "Boost ATK"));  // Boost ATK (Permanent, +1)
    t_deck.add_card(Tech("070", "Potion of Fortitude", Card::Tech, "Increases defense permanently.", 2, "Boost DEF"));  // Boost DEF (Permanent, +2)
    t_deck.add_card(Tech("071", "Vitality Elixir", Card::Tech, "Raises maximum HP permanently.", 3, "Raise Max Hp"));  // Raise Max HP (Permanent, +3)

    // Tier 3: Advanced Tech (Rare, stronger effects)
    t_deck.add_card(Tech("072", "Greater Elixir of Health", Card::Tech, "Restores a large amount of health.", 8, "Heal"));  // Heal (8)
    t_deck.add_card(Tech("073", "Mana Surge", Card::Tech, "Restores a large amount of MP.", 6, "Restore MP"));  // Restore MP (6)
    t_deck.add_card(Tech("074", "Artifact of the Berserker", Card::Tech, "Increases attack permanently.", 2, "Boost ATK"));  // Boost ATK (Permanent, +2)
    t_deck.add_card(Tech("075", "Artifact of the Sentinel", Card::Tech, "Increases defense permanently.", 3, "Boost DEF"));  // Boost DEF (Permanent, +3)

    // Tier 4: Legendary Tech (Epic, high value effects)
    t_deck.add_card(Tech("076", "Elixir of Vitality", Card::Tech, "Raises maximum health permanently.", 4, "Raise Max Hp"));  // Raise Max HP (Permanent, +4)
    t_deck.add_card(Tech("077", "Mana Infusion Crystal", Card::Tech, "Restores all Mp.", 10, "Raise Max Mp"));
  }
}



void shuffle_deck(Deck<Spell>& s_deck, Deck<Equipment>& e_deck, Deck<Tech>& t_deck)
{
  // Shuffle all deck
  s_deck.shuffle_deck();
  e_deck.shuffle_deck();
  t_deck.shuffle_deck();
}

int decide_turn( )
{
  // seed rand
  srand(time(0));

  cout << "Throw a Dice:\n";
  return rand() % 2 + 1;
}



bool play_turn(Character & player, Character & Opponent, DeckManager & deck_system, const int turn)
{
  // Increase hp/ mp per turn
  if (turn > 1)
  {
    player.pass_turn( );
  }

  // Draw Stage
  cout << "\n || DRAW STAGE!\n";
  cout << player << " Draw!!! . . .\n";

  deck_system.show_option_box(player);
  cout << "\nHere is your status:\n";
  player.display('i');

  pause( );

  // Resolve Stage
  cout << "\n || RESOLVE STAGE";

  if (player.get_tech_slot().back( ) == Tech() && player.get_spell_slot( ).back() == Spell())
  {
    cout << "\n [~] Nothing to resolve!";
  }

  if (player.get_tech_slot().back( ) != Tech() && !player.get_tech_slot().empty())
  {
    cout << "\n [!] Use Tech Card: ";
    player.use_tech(deck_system);
  }

  if (player.get_spell_slot( ).back() != Spell())
  {
    cout << "\n [!] Channeling Mana. . .";
    player.cast_spell(Opponent, deck_system);
  }


  // check lose here
  if (Opponent.is_lost( ))
  {
    cout << " [!!!] " << Opponent << " Hp reaches 0 ";
    return true;
  }

  pause( );


  // Combat Stage
  cout << "\n || COMBAT STAGE\n";
  if (turn > 1)
  {
    cout << player <<  " ATTACK!!! " << Opponent;
    cout << endl << endl;

    int damage = player.calculate_damage(Opponent);
    if (damage == 0)
      cout << " - But it not very effective.\n";
    else
    {
      Opponent.take_damage(damage);
      cout << "\n - " << Opponent << " suffer " << damage << " Pts of damamge.\n";
    }

    Opponent.display();
  }
  else
    cout << " [!] " <<  player << " Cannot Attack on first turn";

  pause( );

  // check lose here
  if (Opponent.is_lost( ))
  {
    cout << "\n [!!!] " << Opponent << " Hp reaches 0 ";
    return true;
  }

  cout << endl;



  // Pass Turn
  cout << " || PASS STAGE\n";
  player.display();
  cout << endl;
  cout << " - Pass Turn to " << Opponent;

  cout << endl << endl;

  return false;
}


void end_game(Character & p1, Character & p2)
{
  cout << " - After a Great Battle, We have our Winner!!\n";
  if (p1.is_lost())
    cout << p2 << " IS OUR CHAMPION!!!\n";
  else if (p2.is_lost())
    cout << p1 << " IS OUR CHAMPION!!!\n";
  else
    cout << " - Wait, it a TIE?? How did this Happended?\n";
}



// Helper Fucntion
string input(const string& prompt)
{
  cout << prompt;
  string name;
  if ((cin >> name).fail())
  {
    cin.clear( );
    cin.ignore(1024, '\n');
  }
  return name;
}


void pause( )
{
  cin.ignore(1024, '\n');
  cin.get();
}
