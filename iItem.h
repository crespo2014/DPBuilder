/*
 * iItem.h
 *
 *  Created on: 24 Mar 2015
 *      Author: lester
 */

#ifndef IITEM_H_
#define IITEM_H_

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
enum item_flags
{
 none,
 empty,      // item does not have data
 mandatory, // item is mandatory
 removed,   // item marked as remove
};
class Iitem
{
  const char* getName();
protected:
  /// not allowed to delete object throught the interface
  virtual ~Iitem() {};
};


#endif /* IITEM_H_ */
