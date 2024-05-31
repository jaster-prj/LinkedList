/**
 * @file    ll.h
 * @brief   Core Utility - Templated Linked List class
 * @author  sam grove
 * @version 1.0
 * @see     
 *
 * Copyright (c) 2013
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef LL_H_
#define LL_H_

#include <stdint.h>
#include <cstddef>

/**
 *  @struct node
 *  @brief The Linked List structure
 */ 
struct node
{
    void *data;         /*!< pointer to list member data */
    struct node *prv;   /*!< pointer to the prev list member */
    struct node *next;  /*!< pointer to the next list member */
    bool remove;
};

/** Example using the LL Class
 * @code
 *  #include "mbed.h"
 *  #include "LL.h"
 *  
 *  LL<node>list;
 *  
 *  int main()
 *  {
 *      node *tmp;
 *      
 *      list.push((char *)"Two\n");
 *      list.append((char *)"Three\n");
 *      list.append((char *)"Four\n");
 *      list.push((char*)"One\n");
 *      list.append((char*)"Five\n");
 *      
 *      for(int i=1; i<=list.length(); i++)
 *      {
 *          tmp = list.pop(i);
 *          printf("%s", (char *)tmp->data);
 *      }
 *      
 *      error("done\n");
 *  }
 * @endcode
 */


/**
 *  @class LL_ITERATOR
 *  @brief API abstraction for a Linked List Iterator
 */ 
template<class retT>
class LL_ITERATOR
{
protected:
    node *_current;
public:
    LL_ITERATOR(node *pointer);
    retT *previous(void);
    retT *next(void);
};


/**
 *  @class LL
 *  @brief API abstraction for a Linked List
 */ 
template<class retT>
class LL
{
protected:
    node *_head;

public:
    /** Create the LL object
     */   
    LL();
    
    /** Deconstructor for the LL object
     *  Removes any members
     */ 
    ~LL();

    void clear(void);

    LL_ITERATOR<retT> *create_iterator(void);

    /** Add a member to the begining of the list
     *  @param data - Some data type that is added to the list
     *  @return The member that was just inserted (NULL if empty)
     */
    retT *push(retT data);

    /** Add a member to the begining of the list
     *  @param data - Some data type that is added to the list
     *  @return The member that was just inserted (NULL if empty)
     */
    retT *push(retT *data, bool remove=false);
    
//    /** Add a member to some position in the list
//     *  @param data - Some data type that is added to the list
//     *  @param loc - Place in the list to put the data
//     *  @return The member that was just inserted (NULL if empty)
//     */
//    retT *insert(void *data, uint32_t loc);
    
    /** Add a member to the end of the list
     *  @param data - Some data type that is added to the list
     *  @return The member that was just inserted (NULL if empty)
     */
    retT *append(retT data);
    
    /** Add a member to the end of the list
     *  @param data - Some data type that is added to the list
     *  @return The member that was just inserted (NULL if empty)
     */
    retT *append(retT *data, bool remove=false);
    
    /** Remove a member from the list
     *  @param loc - The location of the member to remove
     *  @return The head of the list
     */
    retT *remove(uint32_t loc);
    
    /** Get access to a member from the list
     *  @param loc - The location of the member to access
     *  @return The member that was just requested (NULL if empty or out of bounds)
     */
    retT *pop(uint32_t loc);
    
    /** Get the length of the list
     *  @return The number of members in the list
     */
    uint32_t length(void);


};

template<class retT>
LL_ITERATOR<retT>::LL_ITERATOR(node *pointer)
{
    _current = pointer;

    return;
}

template<class retT>
retT *LL_ITERATOR<retT>::previous(void)
{
    if (_current == 0)
    {
        return nullptr;
    }
    void *ret_ptr = _current->data;
    _current = _current->prv;
    return (retT*)ret_ptr;
}

template<class retT>
retT *LL_ITERATOR<retT>::next(void)
{
    if (_current == 0)
    {
        return nullptr;
    }
    void *ret_ptr = _current->data;
    _current = _current->next;
    return (retT*)ret_ptr;
}

template<class retT>
LL<retT>::LL()
{
    // clear the member
    _head = 0;

    return;
}

template<class retT>
LL<retT>::~LL()
{
    while(remove(0) != nullptr);
    return;
}

template<class retT>
void LL<retT>::clear(void)
{
    // free any memory that is on the heap
    for(int i = length()-1; i >= 0; i--)
    {
        remove(i);
    }

    return;
}

template<class retT>
LL_ITERATOR<retT> *LL<retT>::create_iterator(void)
{
    return new LL_ITERATOR<retT>(_head);
}

template<class retT>
retT *LL<retT>::push(retT data)
{
    retT *pointer = new retT;
    memcpy(pointer, data, sizeof(retT));

    node *new_node = new node [1];
    new_node->remove = true;
    // update the next item in the list to the current head
    new_node->next = _head;
    new_node->prv = 0;
    if(_head != 0){
        _head->prv = new_node;
    }
    // store the address to the linked datatype
    new_node->data = pointer;
    _head = new_node;

    return (retT*)_head->data;
}

template<class retT>
retT *LL<retT>::push(retT *data, bool remove)
{
    node *new_node = new node [1];
    new_node->remove = remove;
    // update the next item in the list to the current head
    new_node->next = _head;
    new_node->prv = 0;
    if(_head != 0){
        _head->prv = new_node;
    }
    // store the address to the linked datatype
    new_node->data = data;
    _head = new_node;

    return (retT*)_head->data;
}

//template<class retT>
//retT *LL<retT>::insert(void *data, uint32_t loc)
//{
//    retT *new_node = new retT [1];
//    retT *current = _head->next;
//    retT *prev = _head;
//    // move to the item we want to insert
//    for (uint32_t i=1; i!=(loc-1); i++)
//    {
//        prev = current;
//        current = current->next;
//    }
//    // store the address to the linked datatype
//    new_node->data = data;
//    // clear the next pointer
//    new_node->next = 0;
//    // update the list and store the new stuff
//    prev->next = new_node;
//    new_node->next = current;
//    // store the address to the linked datatype
//    _head->data = data;
//
//    return prev->next;
//}

template<class retT>
retT *LL<retT>::append(retT data)
{
    retT *pointer = new retT;
    memcpy(pointer, &data, sizeof(retT));

    node *current = _head;
    node *new_node = new node [1];
    new_node->remove = true;
    // store the address to the linked datatype
    new_node->data = pointer;
    // clear the next pointer
    new_node->next = 0;
    // check for an empty list
    if (current == 0)
    {
        new_node->prv = 0;
        _head = new_node;
        return (retT *)_head->data;
    }
    else
    {
        // look for the end of the list
        while (current->next != 0)
        {
            current = current->next;
        }
        // and then add the new item to the list
        current->next = new_node;
        new_node->prv = current;
    }

    return (retT*)current->next->data;
}

template<class retT>
retT *LL<retT>::append(retT *data, bool remove)
{

    node *current = _head;
    node *new_node = new node [1];
    new_node->remove = remove;
    // store the address to the linked datatype
    new_node->data = data;
    // clear the next pointer
    new_node->next = 0;
    // check for an empty list
    if (current == 0)
    {
        new_node->prv = 0;
        _head = new_node;
        return (retT *)_head->data;
    }
    else
    {
        // look for the end of the list
        while (current->next != 0)
        {
            current = current->next;
        }
        // and then add the new item to the list
        current->next = new_node;
        new_node->prv = current;
    }

    return (retT*)current->next->data;
}

template<class retT>
retT *LL<retT>::remove(uint32_t loc)
{
    node *current = _head;
    node *prev = 0;
    if (current == 0)
    {
        return nullptr;
    }
    // make sure we have an item to remove
    if (loc < length())
    {
        // move to the item we want to delete
        if (loc == 0)
        {
            _head = current->next;
            if(current->remove) {
                delete current->data;
            }
            delete [] current;
            if(_head == 0) {
                return nullptr;
            }
            _head->prv = 0;
        }
        else
        {
            for (uint32_t i=0; i<loc; ++i)
            {
                prev = current;
                current = current->next;
            }
            // store the item + 1 to replace what we are deleting
            prev->next = current->next;
            if (current->next != nullptr) {
                current->next->prv = prev;
            }
            if(current->remove) {
                delete current->data;
            }
            delete [] current;
        }
    }

    return (retT*)_head->data;
}

template<class retT>
retT *LL<retT>::pop(uint32_t loc)
{
    node *current = _head;
    // make sure we have something in the location
    if (loc >= length() || current == 0)
    {
        return 0;
    }
    // and if so jump down the list
    for (uint32_t i=0; i<loc; ++i)
    {
        current = current->next;
    }

    return (retT*)current->data;
}

template<class retT>
uint32_t LL<retT>::length(void)
{
    uint32_t count = 0;
    volatile node *current = _head;
    //loop until the end of the list is found
    while (current != 0)
    {
        ++count;
        current = current->next;
    }

    return count;
}

#endif /* LL_H_ */