/**
FILE: Card.h
  Author: Lan Luu
  Date: 10/24/2024
  Instructor: Karla Fant
  Course: CS302-001
  
Summary: Core heirarchy of Program 2. 
Base Class: Card
Derived Class: Spell_Card, Equipment_Card, Tech_card.
**/ 
#ifndef CARD_H 
#define CARD_H 
 
#include <string> 

using namespace std;

/// Class Card (Based Class) 
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////// 
// Summarize: Create an Object represent a card.  
// Data member: 
//  m_index: char *, unique data act as a key for each Card. Format: "000" - "999"  
//  m_name: string, contain the data for a Card name.  
//  m_type: enum, contain the type of that card. ( enum {Spell, Equipment, Tech} )  
//  m_desc: string, Contain the infromation of the card. 
// Method:
//  display: bool, display the Card info to user.
//  operator=: Card&, assign target Card data to this.
//  operator<, >, <=, >=: bool, compare the m_index.
//  operator==, !=: boo, compare two Card.
//  operator<<: ostream&, output the Card data to user.
//  operator>>: istream&, take user input to Card. 
//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////// 
class Card 
{ 
  public:  
    enum card_type { Blank, Spell, Equipment, Tech };
    // const string CARD_TYPE [] { Blank, Spell, Equipment, Tech }; // move this to main.cpp
    
    // CTOR & DCTR 
    Card(const char * init_index= "000", const string& init_name= " ", card_type init_type= Blank, const string& init_desc=" "); 
    Card(const Card & source); 
    ~Card(); 
     
    // MEMBER FUNCTION 
    bool display(char format=' ') const; 
     
    //OPERATOR OVERLOADING 
    Card& operator=(const Card & op2); 
    bool operator<(const Card & op2) const; 
    bool operator<=(const Card & op2) const; 
    bool operator>(const Card & op2) const; 
    bool operator>=(const Card & op2) const; 
    bool operator==(const Card & op2) const; 
    bool operator!=(const Card & op2) const; 

    friend ostream& operator<<(ostream&, const Card & op2); 
    friend istream& operator>>(istream&, Card & op2); 
     
  protected: 
    char * m_index; 
    string m_name; 
    card_type m_type; 
    string m_desc; 
}; 
 
/// Class Spell_Card (Derived from Card Class) 
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////// 
// Summarize: Create an Object represent a spell card. Put in spell_slot when picked during Option_box. 
// Data member:  	 	
//  m_cost: int, amount of mp require to cast() this spell  
// 	m_damage: int, the damage this spell will deal to Opponent (bypass defense) 
//  
// Method:
//  display: bool, display the Spell Card data to the user, also call Card display
//  operator=: Spell&, Assignment operator, assign a target Spell obj to this.
//  operator==, !=: bool, compare two Spell Object.
//  operator<<: ostream&, display the Spell Object to outstream.
// 
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////// 
 
class Spell: public Card 
{ 
  public: 
    // CTOR & DTOR 
    Spell(const char * init_index= "000", const string& init_name= " ", Card::card_type init_type= Card::Spell, const string& init_desc=" ", const int init_cost = 0, const int init_damage = 0); 
     
    // MEMBER FUNCTION 
    bool display(const char format=' ') const; 
     
    // OPERATOR OVERLOADING 
    Spell& operator= (const Spell & op2); 	// For change spell slot 
    bool operator==(const Spell & op2) const; 	// to compare if two spell is the same, OR if spell in spell slot is the same  
    bool operator!=(const Spell & op2) const; 
    friend ostream& operator<<(ostream&, const Spell & op2); 	// For display Spell Card 
   
  protected: 
    int m_cost; 
    int m_damage; 

    friend class Character;   // Grand Character class access to protect member
}; 
 
/// Class Equipment_card (Derived from Card Class) 
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////// 
// Summarize: Create an Object represent a card. put in Equipment_slot_1 OR Equipment_slot_2 after get  
// 	 	picked during option_box 
// Data member:
//	m_atk: int, amount of attack characrter will increase when equip 
// 	m_def: int, amount of defense characrter will increase when equip 
// Method:
//  display: bool, display the data of Equipment to the user.
//  operator=: Equipment&, assign the data of target to new Equipment Object.
//  operator==, !=: bool, compare two Equipment object.
//  operator+: Equipment, add atk and def of two Equipment object.
//  operator+=: Equipment&, add atk and def of two Equipment object.
//  operator<<: ostream&, display the Equipment object data to outstream.
//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////// 
class Equipment: public Card 
{ 
  public: 
    // CTOR & DTOR 
    Equipment(const char * init_index= "000", const string& init_name= " ", Card::card_type init_type= Card::Equipment, const string& init_desc=" ",
              const int init_atk = 0, const int init_def = 0); 
     
    // MEMBER FUNCTION 
    bool display(const char format=' ') const;  
     
    //OPERATOR OVERLOADING 
    Equipment& operator= (const Equipment & op2); 
    bool operator==(const Equipment & op2);
    bool operator!=(const Equipment & op2);
    Equipment operator+ (const Equipment & op2); 
    Equipment& operator+= (const Equipment & op2); 
    friend ostream& operator<<(ostream&, const Equipment & op2); 
   
  protected: 
    int m_atk; 
    int m_def; 

    friend class Character;   // Grand Character class access to protect member
}; 
 
/// Class Tech_card (Derived from Card Class) 
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////// 
// Summarize: Create an Object represent a Tech card. Tech Card will be uses immediately upon get choosen.  
// 	 	put in use_slot when picked up during option box. 
// Data member:
// 	m_value: int, amount of value will affect characrter based on trait 
// 	m_trait: char * , determine the affect of value to character 
// Method:
//  display: bool, display the Tech card data to user.
//  operator=: Tech&, assign the target data to this
//  operator<<: ostream&, display the Tech object data to outstream.
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////// 
class Tech: public Card 
{ 
  public: 
    //CTOR  
    Tech(const char * init_index= "000", const string& init_name= " ", Card::card_type init_type= Card::Tech, const string& init_desc=" ",
         const int init_value = 0, const char * init_trait = " "); 
    Tech(const Tech & source);
    ~Tech( );
     
    // MEMBER FUNCTION 
    bool display(const char format=' ') const;  
      // Friend function for each trait to affect the Character
    //friend bool heal_hp(const Tech& a_tech, Character & a_character);   // increase character hp by m_value
    //friend bool recvr_mp(const Tech& a_tech, Character & a_character);  // increase character mp by m_value
     
    //OPERATOR OVERLOADING 
    Tech& operator= (const Tech& op2); 
    bool operator==(const Tech& op2);
    bool operator!=(const Tech& op2);
    friend ostream& operator<<(ostream&, const Tech & op2); 
   
  protected: 
    int m_value; 
    char * m_trait; 

    friend class Character;
}; 

# endif 


