/*
 * basicItem.h
 *
 *  Created on: 26 Mar 2015
 *      Author: lester
 */

#ifndef BASICITEM_H_
#define BASICITEM_H_

#include "iItem.h"

/**
 * Class to convert from string to numeric types
 */
template<class T>
class fromString
{
  
};

/**
 * Basic iItem implementation that implements basic behaviour
 * All functions will throw unimplements exception
 */
class basicItem : public Iitem
{
  public:
   basicItem(const char* name) : name_(name){}
  private:
    const char* name_;  ///< item name

};
/**
 * this class implements set mehods
 */ 
template<class T>
class singleItem 
{
  
};

template<class T>
class containerItem
{
  
};

class ObjectItem
{
};




#endif /* BASICITEM_H_ */
