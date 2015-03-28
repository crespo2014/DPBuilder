/*
 * basicItem.h
 *
 *  Created on: 26 Mar 2015
 *      Author: lester
 *  Describe function is not implement here.
 *  Writter interface for descriptors is needed. 
 ObjectAItem::describe(const ObjectA&,Writter& wr ); // use template for writter.
 */

#ifndef BASICITEM_H_
#define BASICITEM_H_

#include "iItem.h"
#include "../common/flag.h"

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
class basicItem: public Iitem
{
public:
  /// Constructor
  basicItem(const char* name, item_type type) :
      name_(name), type_(type)
  {
  }
protected:
  const SubString getName() const
  {
    return {name_};
  }
  Iitem& createChild(const SubString& name) = 0;
  /**
   * No more data for this item, validate it
   * false if item does not validate fine
   */
  bool close(const SubString& name) = 0;
  bool Set(const std::string& value) = 0;    ///< Return false if value was already set
  /**
   * Item has to interpret this
   */
  bool Set(const SubString& value) = 0;
  /**
   * Get item type
   */
  item_type getType() const
  {
    return type_;
  }
  /**
   * Read flag status
   */
  bool isSet(item_flags f) const
  {
    return flags_.is(f);
  }
  /// activate flag
  void setBit(item_flags bit)
  {
    flags_.set(bit);
  }
  /// clear flag
  void clearBit(item_flags bit)
  {
    flags_.clear(bit);
  }
  //Set(T& val) - it is hard to figure out with method call base on type
private:
  const char* name_;               ///< name for serialization
  item_type type_;                ///< item type
  BitFlags<item_flags> flags_;    ///< some flags
  std::vector<basicItem*> subitems_;    ///<child items

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
