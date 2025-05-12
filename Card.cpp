// FILENAME: Card.cpp
// Author: Lan Luu
// Create: 10/26/2024
// Summary: Implementation file of Card Class and its derived class
///

#include "Card.h"
#include <iostream>
#include <iomanip>
#include <cstring>
#include <cctype>

using namespace std;

/// Card Class
///////////////////////////////////////////////////////////////////
// Implement include: Contructor,
// Copy Constructor, destructor, display,
// Operator overlaod: =, <, >, <=, >=, ==, !=, <<, >>
//////////////////////////////////////////////////////////////////

const string CARD_TYPE [] = {"Blank", "Spell", "Equipment", "Tech"};
 
// Constructor
Card::Card(const char * a_index, const string & a_name, card_type a_type, const string & a_desc):m_index(nullptr), m_name(a_name), m_type(a_type), m_desc(a_desc)
{
  m_index = new char[strlen(a_index) + 1];
  strcpy(m_index, a_index);
}

// Copy Constructor
Card::Card(const Card & source):m_index(nullptr), m_name(source.m_name), m_type(source.m_type), m_desc(source.m_desc)
{
  m_index = new char[strlen(source.m_index) + 1];
  strcpy(m_index, source.m_index);
}

// Destructor
Card::~Card( )
{
  delete [] m_index;
  m_index = nullptr;
}

/// MEMBER FUNCTION
// function: display value of Card
// @param:  format, char, default to ' ', pass 'f' to specify full display, 
//          pass nothing for inline text display. 
// @return: true if success, false if not.
bool Card::display(char format) const
{
  if (format == 'f')
  {
    cout << "+";
    cout << setfill('-') << setw(m_desc.length() + 5) << "+\n";
    cout << setfill(' ');
    cout << "| " << "Name: " << m_name << setw(m_desc.length()) << "\n";
    cout << "| " << "Card Type: " << CARD_TYPE[m_type] << setw(m_desc.length()) << "\n";
    cout << "| " << "- " << m_desc << setw(m_desc.length()) << "\n"; 

    return true;
  } else if (format==' ')
  {
    cout << "[" << m_name << "] - ";
    cout << CARD_TYPE[m_type];
    return true;
  } 
  
  return false;
}

/// OPERATOR OVERLOADING
// Operator=
Card& Card::operator=(const Card & op2) 
{
  if (this == & op2)
    return *this;
 
  // Deallocate  
  delete [] m_index;
  
  // Assign new value
  m_index = new char[strlen(op2.m_index) + 1];
  strcpy(m_index, op2.m_index);
  m_name = op2.m_name;
  m_type = op2.m_type;
  m_desc = op2.m_desc;

  return *this;
}

bool Card::operator<(const Card & op2) const
{
  return m_index < op2.m_index;
}

bool Card::operator<=(const Card & op2) const
{
  return m_index <= op2.m_index;
}

bool Card::operator>(const Card & op2) const
{
  return m_index > op2.m_index;
}

bool Card::operator>=(const Card & op2) const
{
  return m_index >= op2.m_index;
}

bool Card::operator==(const Card & op2) const 
{
  return  strcmp(m_index, op2.m_index) == 0 &&
          m_name == op2.m_name &&
          m_type == op2.m_type &&
          m_desc == op2.m_desc;
}

bool Card::operator!=(const Card & op2) const
{
  return !(*this == op2);
}

// I/O Opeartor Overloading
ostream& operator<<(ostream& out, const Card& op2)
{
  if (!out)
    throw ios_base::failure("Output stream error with Card Object!\n");

  out << "[" << op2.m_name << "] - " << CARD_TYPE[op2.m_type];
  return out;
}

istream& operator>>(istream& in, Card & op2)
{ // This is for testing only
  if (!in)
    throw ios_base::failure("Input stream error with Card Object!\n");

  getline(in, op2.m_name);
  getline(in, op2.m_desc); 
  return in;
}
// END OF OPERATOR OVERLOADING



/// Spell Class: Derived from Card Class
///////////////////////////////////////////////////////////////////
// Implement include: Contructor,
// Copy Constructor, destructor, display,
// Operator overlaod: =,==, !=, <<
//////////////////////////////////////////////////////////////////
Spell::Spell(const char * a_index, const string & a_name, card_type a_type, const string& a_desc, const int a_cost, const int a_damage):Card(a_index, a_name, a_type, a_desc), m_cost(a_cost), m_damage(a_damage)
{
}

/// MEMBER FUNCTION
// function: display value of Spell Card
// @param:  format, char, default to ' ', pass 'f' to specify full display, 
//          pass nothing for inline text display. 
// @return: true if success, false if not.
bool Spell::display(const char format) const
{
  if (format == 'f')
  {
    Card::display('f');
    cout << "| MP Cost: " << m_cost << " pts"<< endl;
    cout << "| DAMAGE: " << m_damage << " pts" << endl;
    cout << "+" << setw(m_desc.length() + 5) << setfill('_') << "+" << endl;
    return true;
  } else
  {
    Card::display( );
    cout << " | Cost: " << m_cost << " | DAMAGE: " << m_damage;
    return true; 
  } 
    
  return false;
}

// OPERATOR OVERLOADING
Spell& Spell::operator= (const Spell & op2)
{
  // Check self assingment
  if (this == &op2)
    return *this;

  Card::operator=(op2);
  
  m_cost = op2.m_cost;
  m_damage = op2.m_damage;
  return *this;
}

bool Spell::operator==(const Spell & op2) const
{
  return  (strcmp(m_index, op2.m_index) == 0)  &&
          m_name == op2.m_name && 
          m_type == op2.m_type && 
          m_desc == op2.m_desc && 
          m_cost == op2.m_cost && 
          m_damage == op2.m_damage;
}

bool Spell::operator!=(const Spell & op2) const
{
  return !(*this == op2);
}
    
ostream& operator<<(ostream& out, const Spell & op2)
{
  if (!out)
    throw ios_base::failure("Output stream error with Spell Object!\n");

  operator<<(out, static_cast<Card>(op2));
  out << " | Cost: " << op2.m_cost << " | DAMAGE: " << op2.m_damage;
  return out; 
}

/// END OF SPELL CLASS IMPLEMENTATION




/// Equipment Class: Derived from Card Class
///////////////////////////////////////////////////////////////////
// Implement include: Contructor,
// Copy Constructor, destructor, display,
// Operator overlaod: =,==, !=, +, +=, <<
//////////////////////////////////////////////////////////////////
Equipment::Equipment(const char * a_index, const string& a_name, card_type a_type, const string& a_desc,
          const int a_atk, const int a_def): Card(a_index, a_name, a_type, a_desc), m_atk(a_atk), m_def(a_def)
{
}

/// MEMBER FUNCTION
// function: display value of Equipment Card
// @param:  format, char, default to ' ', pass 'f' to specify full display, 
//          pass nothing for inline text display. 
// @return: true if success, false if not.

bool Equipment::display(const char format) const
{ 
  if (format == 'f')
  {
    Card::display('f');
    cout << "| ATTACK: " << m_atk << " pts"<< endl;
    cout << "| DEF: " << m_def << " pts" << endl;
    cout << "+" << setw(m_desc.length() + 5) << setfill('_') << "+" << endl;
    return true;
  } else
  {
    Card::display( );
    cout << " | Attack: " << m_atk << " | Defense: " << m_def;
    return true; 
  } 
    
  return false;
}

/// OPERATOR OVERLOADING    
Equipment& Equipment::operator= (const Equipment & op2)
{
  // check self assignment
  if (this == &op2)
    return *this;

  // de-allocated dyn_array

  // assignment 
  Card::operator=(op2);
  m_atk = op2.m_atk;
  m_def = op2.m_def;
  return *this;
}
    

bool Equipment::operator==(const Equipment & op2)
{
  return  (strcmp(m_index, op2.m_index) == 0)  &&
          m_name == op2.m_name && 
          m_type == op2.m_type && 
          m_desc == op2.m_desc && 
          m_atk == op2.m_atk &&
          m_def == op2.m_def; 
}

    
bool Equipment::operator!=(const Equipment & op2)
{
  return !(*this == op2);
}

    
Equipment Equipment::operator+ (const Equipment & op2)
{
  Equipment result;
  result.m_atk = m_atk + op2.m_atk;
  result.m_def = m_def + op2.m_def;
  return result; 
}
    

Equipment& Equipment::operator+= (const Equipment & op2)
{
  m_atk += op2.m_atk;
  m_def += op2.m_def;
  return *this;
}
   

ostream& operator<<(ostream& out, const Equipment & op2)
{
  if (!out)
    throw ios_base::failure("Output stream error with Equipment Object!\n");
  operator<<(out, static_cast<Card>(op2));
  out << " | Attack: " << op2.m_atk << " | Defense: " << op2.m_def;
  return out; 
}
          

/// END OF EQUIPMENT CLASS IMPLEMENTATION



/// Tech Class: Derived from Card Class
///////////////////////////////////////////////////////////////////
// Implement include: Contructor,
// Copy Constructor, destructor, display,
// Operator overlaod: =,==, !=, +, +=, <<
//////////////////////////////////////////////////////////////////
Tech::Tech(const char * a_index, const string& a_name, card_type a_type, const string& a_desc,
           const int a_value, const char * a_trait): Card(a_index, a_name, a_type, a_desc), m_value(a_value), m_trait(nullptr)
{
  m_trait = new char[strlen(a_trait) + 1];
  strcpy(m_trait, a_trait);
}

Tech::Tech(const Tech & source):Card(static_cast<Card>(source)), m_value(source.m_value), m_trait(nullptr)
{
  m_trait = new char[strlen(source.m_trait) + 1];
  strcpy(m_trait, source.m_trait);
}

Tech::~Tech( )
{
  delete [] m_trait;
  m_trait = nullptr;
}


/// MEMBER FUNCTION
// function: display value of Tech Card
// @param:  format, char, default to ' ', pass 'f' to specify full display, 
//          pass nothing for inline text display. 
// @return: true if success, false if not.
bool Tech::display(const char format) const
{
  if (format == 'f')
  {
    Card::display('f');
    if (!strcmp(m_trait, "Heal"))
      cout << "| Recover " << m_value << " pts of HP." << endl;
    else if (!strcmp(m_trait, "gain_mp"))
      cout << "| Gain " << m_value << " pts of MP." << endl;
    cout << "+" << setw(m_desc.length() + 5) << setfill('_') << "+" << endl;
    return true;
  } else
  {
    Card::display( );
    if (!strcmp(m_trait, "Heal"))
      cout << " | Recover " << m_value << " pts of HP.";
    else if (!strcmp(m_trait, "gain_mp"))
      cout << " | Gain " << m_value << " pts of MP.";
    return true; 
  } 
    
  return false;
}

 
//OPERATOR OVERLOADING 
Tech& Tech::operator= (const Tech& op2)
{
  // Check self-Assignment
  if (this == &op2)
    return *this;

  // De-allocate dynamic array memory
  delete [] m_trait;
  m_trait = nullptr;

  // Assign new value
  Card::operator=(op2);
  m_value = op2.m_value;
  m_trait = new char[strlen(op2.m_trait) + 1];
  strcpy(m_trait, op2.m_trait);
  
  return *this; 
}


bool Tech::operator==(const Tech& op2)
{
  return  (strcmp(m_index, op2.m_index) == 0)  &&
          m_name == op2.m_name && 
          m_type == op2.m_type && 
          m_desc == op2.m_desc && 
          m_value == op2.m_value &&
          (strcmp(m_trait, op2.m_trait) == 0);
}

bool Tech::operator!=(const Tech& op2)
{
  return (!(*this == op2));
}


ostream& operator<<(ostream& out, const Tech & op2)
{
  if (!out)
    throw ios_base::failure("Output stream error with Tech Object!\n");
  operator<<(out, static_cast<Card>(op2));
  if (!strcmp(op2.m_trait, "Heal"))
    out << " | Recover " << op2.m_value << " pts of HP.";
  else if (!strcmp(op2.m_trait, "gain_mp"))
    out << " | Gain " << op2.m_value << " pts of MP.";
  return out;
}


/// END OF TECH CLASS IMPLEMENTATION
