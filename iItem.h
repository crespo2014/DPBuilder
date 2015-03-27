/*
 * iItem.h
 *
 *  Created on: 24 Mar 2015
 *      Author: lester
 */

#ifndef IITEM_H_
#define IITEM_H_

#include "../common/substring.h"

/**
 * Substring does not support point to invalid location
 * size == 0 means zero end string.
 * ptr == null means empty string
 * characters are const
 */
enum class item_type 
{
  none,
  object,
  container,
  string,
  signedNumber,
  unsignedNumber,
  floatingPoint
  boolean,
};

//
enum item_flags
{
 none,
 empty,      ///< item does not have data
 mandatory,  ///< item is mandatory
 removed,    ///< item marked as remove
};

class Iitem
{
public:
  const SubString& getName() const = 0;
  Iitem& createChild(const SubString& name) = 0;
  /** 
   * No more data for this item, validate it
   * false if item does not validate fine
   */
  bool close(const SubString& name) = 0;
  /**
   * Return false if value was already set
  */
  bool Set(const std::string& value) = 0; // Item has to interpret this
  /**
   * Item has to interpret this
   */
  bool Set(const SubString& value) = 0;
  /**
   * Get item type
   */
  item_type getType() const = 0; 
  /**
   * Read flag status
   */
  bool isSet(item_flags) const = 0;
  //Set(T& val) - it is hard to figure out with method call base on type
protected:
  /// not allowed to delete object throught the interface
  virtual ~Iitem() {};
};


#endif /* IITEM_H_ */
