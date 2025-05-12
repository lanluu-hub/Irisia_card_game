// Author: Lan Luu
// Create: 11/03/2024
// Summary: Header file for main data_structure of Program 2. Implement using template class.
//          each Node will be Node<TYPE> and main container will be DLL.
/////////////////////////////////////////////////////////////////////////////

#ifndef DATA_STRUCTURE_H
#define DATA_STRUCTURE_H

#include <cstdlib>

/// Node Class
/////////////////////////////////////////////////////////////////////
// Summary: Represents a node in a doubly linked list, containing
//          data and pointers to the next and previous nodes.
//
// Template Parameters:
//  - TYPE: The data will be stored in the node, data will be Spell, Equipment, Tech that derived from Card Class
//
// Data Members:
//  - data: TYPE, the data stored in the node; initialized to a default value.
//  - next: Node<TYPE>*, pointer to the next node in the list; nullptr if no next node.
//  - previous: Node<TYPE>*, pointer to the previous node in the list; nullptr if no previous node.
//
// Methods:
//  - Node(const TYPE & data = TYPE()): Constructor; initializes the node with the given data.
//  - Node(const Node<TYPE> & source): Copy constructor; initializes this node with the data from the source node.
//  - ~Node(): Destructor; cleans up the node resources.
//  - TYPE get_data() const: Returns a reference to the data stored in the node.
//  - bool display() const: Displays the node's data; returns true if successful.
//  - Node<TYPE>& operator= (const Node<TYPE>& op2): overload the assignment operator
//  - bool operator==(const Node<TYPE> & op2): to compare two node
//  - bool operator!=(const Node<TYPE> & op2): to compare two node
//
/////////////////////////////////////////////////////////////////////

template<class TYPE>
class Node
{
  public:
  // CONSTRUCTOR & DESTRUCTOR
    Node(const TYPE & init_data = TYPE());
    Node(const Node<TYPE> & source);
    ~Node( );

  // CLASS METHOD:
    TYPE get_data( ) const;
    Node<TYPE> * get_next( ) const;
    Node<TYPE> * get_previous( ) const;
    bool set_data(const TYPE & entry);
    bool set_next(Node<TYPE> * node);
    bool set_previous(Node<TYPE> * node);
    bool display( ) const;

  // Operator Overload
    Node<TYPE>& operator=(const Node<TYPE> & op2);
    bool operator==(const Node<TYPE> & op2);
    bool operator!=(const Node<TYPE> & op2);
    

  protected:
    TYPE  data; // EX: Spell data;
    Node<TYPE> * next;
    Node<TYPE> * previous;
};



/// Deck Class
/////////////////////////////////////////////////////////////////
// Summary: Represents a deck of cards implemented as a doubly 
//          linked list, providing methods to manage cards and 
//          perform operations such as adding, removing, and 
//          shuffling cards.
//
/// Data Members:
///  - head: Node<TYPE> *, the first node of DLL deck, represents the front of the deck.
///  - tail: Node<TYPE> *, the last node of DLL deck, represents the back of the deck.
///  - size: int, the current number of cards in the deck.
//
/// Methods:
///  - Deck(): Default constructor for the Deck.
///  - Deck(const Deck<TYPE>& source): Copy constructor for the Deck.
///  - ~Deck(): Destructor for the Deck.
///  - int size() const: Returns the number of cards in the deck.
///  - bool empty() const: Checks if the deck is empty.
///  - Node<TYPE>& back() const: Accesses the card at the back of the deck.
///  - bool add_card(const Node<TYPE>& entry): Adds a new card to the back of the deck.
///  - bool pop_back(): Removes the card from the back of the deck.
///  - int clear(): Clears all cards from the deck.
///  - bool shuffle_deck( ): Shuffles the specified deck into this deck.
///  
/// Operator Overloading:
///  - Deck<TYPE>& operator+=(const TYPE & card): Adds a card to the deck.
///  - bool operator==(const Deck<TYPE>& op2): Compares two decks for equality.
///  - bool operator!=(const Deck<TYPE>& op2): Compares two decks for inequality.
///
/// Helper Function:
///  - copy(Node<TYPE> *& current, Node<TYPE>*& tail, Node<TYPE> * src_current): copy the DLL to a new list.
///  - clear(Node<TYPE> *& tail): recursive function to remove all node from the deck.
///
/////////////////////////////////////////////////////////////////

template<class TYPE>
class Deck
{
  public:
  // CONSTRUCTOR AND DESTRUCTOR
    Deck( );
    Deck(const Deck<TYPE> & source);
    ~Deck( );

  // CLASS METHOD
    int size( ) const;
    bool empty( ) const;
    Node<TYPE>& back( ) const;
    bool add_card(const TYPE & card);
    bool pop_back( );
    bool clear( );
    bool shuffle_deck( );
    bool display( ) const;

  // Operator Overload
    Deck<TYPE>& operator+=(const TYPE & card);
    bool operator==(const Deck<TYPE>& op2);
    bool operator!=(const Deck<TYPE>& op2);

  protected:
    Node<TYPE> * head;
    Node<TYPE> * tail;
    int card_count;

  // HELPER FUNCTION
    int copy(Node<TYPE> * current, Node<TYPE> *& tail,  Node<TYPE> * src_current);  // for Copy CTOR
    void clear(Node<TYPE>*& tail);              // for clear( )
    bool compare(Node<TYPE> * head, Node<TYPE> * other_head);                       // For operator==,!=
    bool deck_to_vector(Deck<TYPE> & deck, vector<TYPE> & temp);   // for shuffle_deck()
    bool deck_to_vector(vector<TYPE> & temp, Deck<TYPE> & deck);   // for shuffle_deck()
    bool vector_to_deck(Deck<TYPE> & deck, vector<TYPE> & temp);   // for shuffle_deck()
    bool vector_to_deck(vector<TYPE> & temp, Deck<TYPE> & deck);   // for shuffle_deck()
    bool display(Node<TYPE> * head) const;
};


#include "Data_Structure.tpp"
#endif
