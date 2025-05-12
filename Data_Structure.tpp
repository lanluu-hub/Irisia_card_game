// Author: Lan Luu
// Create: 11/03/2024
// Summary: Implement file for template class Data_structure
/////////////////////////////////////////////////////////////////

#include <cassert>
#include <iostream>
#include <vector>
#include <algorithm>
#include <random>

/*
  NODE<TYPE>
*/
template<class TYPE>
Node<TYPE>::Node(const TYPE & a_data): data(a_data), next(nullptr), previous(nullptr)
{
}

template<class TYPE>
Node<TYPE>::Node(const Node<TYPE> & source): data(source.data), next(nullptr), previous(nullptr)
{
}

template<class TYPE>
Node<TYPE>::~Node( )
{
}

/// END OF CONSTRUCTOR AND DESTRUCTOR SECTION

/*
  @Purpose: access data, manipulate next, previous
*/
template<class TYPE>
TYPE Node<TYPE>::get_data( ) const
{
  return data;
}

template<class TYPE>
Node<TYPE>* Node<TYPE>::get_next( ) const
{
  return next;
}

template<class TYPE>
Node<TYPE>* Node<TYPE>::get_previous( ) const
{
  return previous;
}


template<class TYPE>
bool Node<TYPE>::set_data(const TYPE & entry)
{
  data = entry;
  return true;
}

template<class TYPE>
bool Node<TYPE>::set_next(Node<TYPE> * node)
{
  next = node;
  return true;
}

template<class TYPE>
bool Node<TYPE>::set_previous(Node<TYPE> * node)
{
  previous = node;
  return true;
}
/// END OF DATA MANIPULATION



/*
  @Purpose: display the data to user
  @return: true, if data success to display
*/
template<class TYPE>
bool Node<TYPE>::display( ) const
{
  data.display();
  return true;
}

// Operator Overload
template<class TYPE>
Node<TYPE>& Node<TYPE>::operator=(const Node<TYPE> & op2)
{
  if (this == &op2)
    return *this;

  set_data(op2.get_data( ));
  set_next(nullptr);
  set_previous(nullptr);

  return *this;
}

template<class TYPE>
bool Node<TYPE>::operator==(const Node<TYPE> & op2)
{
  if (this == &op2)
    return true;

  return  data == op2.get_data( );
}

template<class TYPE>
bool Node<TYPE>::operator!=(const Node<TYPE> & op2)
{
  return !(*this == op2);
}

/// END OF TEMPLATE<CLASS TYPE> NODE<TYPE> CLASS


/*
  DECK<TYPE>
*/
/// CONTRUCTOR & DESTRUCTOR
template<class TYPE>
Deck<TYPE>::Deck( ): head(nullptr), tail(nullptr), card_count(0)
{
}

template<class TYPE>
Deck<TYPE>::Deck(const Deck<TYPE> & source):head(nullptr), tail(nullptr)
{
  if (source.head == nullptr)
  {
    card_count = 0;
    return;
  }

  if (head == nullptr)
  {
    Node<TYPE> * new_node = new Node<TYPE>(source.head->get_data());
    head = new_node;
    tail = new_node;
  }

  copy(head, tail, source.head);
  card_count = source.card_count;
}

template<class TYPE>
Deck<TYPE>::~Deck( )
{
  clear( );
  head = nullptr;
  tail = nullptr;
}

/*
COPY
  @Purpose: Copy the source DLL to current DLL.
  @precondition: the list have to be empty.
  @postcondtion: DLL is being copy from source one node at a time.
  @param: Current, Node<TYPE> *&; use to traverse the new list, create new node at current next pointer.
          tail, Node<TYPE> *&; the new list tail pointer.
          src_current, Node<TYPE> *; pointer to the source DLL.
*/
template<class TYPE>
int Deck<TYPE>::copy(Node<TYPE> * current, Node<TYPE>*& tail,  Node<TYPE> * src_current)
{
  if (src_current == nullptr)
    return 0;

  Node<TYPE> * new_node = new Node<TYPE>(src_current->get_data( ));
  if (tail != nullptr)
    new_node->set_previous(tail);
  new_node->set_next(nullptr);
  current->set_next(new_node);
  tail = new_node;
  return copy(current->get_next(), tail, src_current->get_next()) + 1;
}


/*
  function: SIZE
  @Purpose: return the number of card in the deck.
*/
template<class TYPE>
int Deck<TYPE>::size( ) const
{
  return card_count;
}

/*
  function: EMPTY
  @Purose: check to see deck is empty or not.
  @return: true if deck is empty, false otherwise
*/
template<class TYPE>
bool Deck<TYPE>::empty( ) const
{
  if (tail==nullptr)
    return true;
  return false;
}

/*
  function: BACK
  @Purpose: return by reference the last node of the deck.
  @precondtion: deck cant be empty
  @postcondition: return the ref to the last node.
*/
template<class TYPE>
Node<TYPE>& Deck<TYPE>::back( ) const
{
  assert(!empty());
  return *tail;
}


/*
  Function: ADD_CARD
  @Purpose: add a card Node to the end of the Deck.
  @postcondition: A card is added to the back of the deck, count increase by 1.
*/
template<class TYPE>
bool Deck<TYPE>::add_card(const TYPE & entry)
{
  Node<TYPE> * new_node = new Node<TYPE>(entry);
  new_node->set_next(nullptr);
  if (tail == nullptr)
  {
    new_node->set_previous(nullptr);
    head = new_node;
  } else
  {
    if (tail != nullptr)
      new_node->set_previous(tail);
    tail->set_next(new_node);
  }

  tail = new_node;
  ++card_count;
  return true;
}


/*
  Function: POP_BACK
  @Purpose: remove a card at the end of the Deck.
  @postcondtion: A card is removed from the end of the Deck, card count decrease by 1.
  @Return: true if a node is being remove, false if the deck is empty.
*/
template<class TYPE>
bool Deck<TYPE>::pop_back( )
{
  if (empty())  // Deck is empty, no Node was being pop
    return false;

  Node<TYPE>* to_remove = tail;
  if (head == tail)
  {
    head = nullptr;
    tail = nullptr;
  }
  else
  {
    tail = to_remove->get_previous( );
    tail->set_next(nullptr);
  }

  delete to_remove;
  --card_count;
  return true;
}


/*
  Function: CLEAR
  @Purpose: remove all card from the Deck
  @precondtion: Deck is not empty
  @postcondtion: all Card from the deck is being remove, card count set to 0;
  @return: true if deck is cleared. false if deck is empty.
*/
template<class TYPE>
bool Deck<TYPE>::clear( )
{
  if (empty( ))
    return false;

  clear(tail);
  return true;
}

/// Helper function for CLEAR
template<class TYPE>
void Deck<TYPE>::clear(Node<TYPE> *& tail)
{
  if (tail == nullptr)
    return;
  pop_back( );
  return clear(tail);
}


/*
  Function: SHUFFLE
  @Purpose: Shuffle the deck of card
  @precondtion: Deck cannot be empty
  @postcondtion: the deck will be shuffle, size remian unchange.
*/
template<class TYPE>
bool Deck<TYPE>::shuffle_deck( )
{
  if (empty())
    return false;

  random_device rd;   // create a random device and seed generator
  mt19937 g(rd());    // Mersenne Twister generator

  vector<TYPE> temp;

  // Transfer all card to a temp vector
  deck_to_vector(*this, temp);
/*
  while (!empty())
  {
    temp.push_back(back().get_data());
    pop_back( );
  }
*/


  //Shuffle the deck
  shuffle(temp.begin(), temp.end(), g);

  // Transfer all card from temp to main deck
  vector_to_deck(*this, temp);
/*
  while (!(temp.empty()))
  {
    add_card(temp.back( ));
    temp.pop_back( );
  }
*/
  return true;
}

// Display deck
template<class TYPE>
bool Deck<TYPE>::display( ) const
{
  if (head == nullptr)
    return false;

  display(head);

  return true;
}

template<class TYPE>
bool Deck<TYPE>::display(Node<TYPE> * head) const
{
  if (head == nullptr)
    return true;
  head->display();
  cout << "  ";
  return display(head->get_next( ));
}

/*
  OPERATOR OVERLOADING
*/

/*
  Operator+=
  @Purpose: Overload the += operator to perform add_back( )
  @param: TYPE &, data to feed into Node CTOR.
*/
template<class TYPE>
Deck<TYPE>& Deck<TYPE>::operator+=(const TYPE & card)
{
  add_card(card);
  return *this;
}


/*
  Operator==, !=
  @Purpose: Overload the operator == and != to compare two Deck of the same type
  @param: Deck<TYPE>&; deck to compare with.
  @return: true if both deck are equal in Size, and node. false if not (reverse with !=)
*/
template<class TYPE>
bool Deck<TYPE>::operator==(const Deck<TYPE>& op2)
{
  if (empty())
  {
    if (op2.empty( ))
      return true;
    else
      return false;
  }

  if (size( ) != op2.size())
    return false;

  assert(size() == op2.size());
  return compare(head, op2.head);
}

template<class TYPE>
bool Deck<TYPE>::operator!=(const Deck<TYPE>& op2)
{
  return !(*this == op2);
}


/*
  Function: COMPARE
  @Purpose: compare each node of 2 deck.
  @precondtion: Size of both deck have to be the same.
  @postcondition: return true if all node from both deck are the same. False otherwise.
*/
template<class TYPE>
bool Deck<TYPE>::compare(Node<TYPE> * head, Node<TYPE> * other_head)
{
  if (head == nullptr && other_head == nullptr)
    return true;

  if (head != other_head)
    return false;

  return compare(head->get_next( ), other_head->get_next());
}

/*
  Function: DECK_TO_VECTOR
            VECTOR_TO_DECK
  @Purpose: transfer card from Deck to vector and vice versa
  @precondition: Deck can't be empty
  @postcondition: Card Node are completely transfer from Deck to Card in Vector, vice versa.
  @Param: Deck<TYPE> & deck: deck to transfer to and from vector
          vector<TYPE> & temp: the vector to hold the card from deck
  @return: true if transfer successful
*/
template<class TYPE>
bool Deck<TYPE>::deck_to_vector(Deck<TYPE> & deck, vector<TYPE> & temp)
{
  if (deck.empty())
    return true;

  temp.push_back(deck.back().get_data());
  deck.pop_back();

  return deck_to_vector(deck, temp);
}

template<class TYPE>
bool Deck<TYPE>::deck_to_vector(vector<TYPE> & temp, Deck<TYPE> & deck)
{
  return deck_to_vector(deck, temp);
}

template<class TYPE>
bool Deck<TYPE>::vector_to_deck(Deck<TYPE> & deck, vector<TYPE> & temp)
{
  if (temp.empty())
    return true;

  deck.add_card(temp.back());
  temp.pop_back();

  return vector_to_deck(deck, temp);
}

template<class TYPE>
bool Deck<TYPE>::vector_to_deck(vector<TYPE> & temp, Deck<TYPE> & deck)
{
  return vector_to_deck(deck, temp);
}
