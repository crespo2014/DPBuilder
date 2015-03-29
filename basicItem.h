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

#include <stdexcept>
#include <limits>
#include <stdint.h>
#include <type_traits>
#include <memory>
#include <list>
#include <initializer_list>
#include <vector>
#include <list>
#include <string>

#include "iItem.h"
#include "../common/flag.h"
#include "formatstring.h"

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
      key_(name), type_(type)
  {
  }
  /// get id for this item
  virtual const SubString& getKey() const override
  {
    return key_;
  }

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
  bool isSet(item_flags f) const override
  {
    return flags_.is(f);
  }
  /// activate flag
  void setBit(item_flags bit) override
  {
    flags_.set(bit);
  }
  /// clear flag
  void clearBit(item_flags bit) override
  {
    flags_.clear(bit);
  }

  virtual Iitem* createChild(const SubString&) override
  {
    throw std::invalid_argument(FormatString() << "item " << key_ << " does not support subitems");
  }
  /**
   * Done working with this object.
   * Validate missing item
   * and duplicates ones
   */
  virtual bool close(const SubString& name) override
  {
    if (name.good() && !(name == key_))
    {
      throw std::invalid_argument(FormatString() << "item " << key_ << " has been closed as " << name);
    }
    if (isSet(mandatory) && isSet(empty))
    {
      throw std::invalid_argument(FormatString() << "Missing value for " << key_);
    }
    return true;
  }
  /**
   * Set Item value as string
   */
  virtual bool Set(const SubString&) override
  {
    throw std::invalid_argument(FormatString() << "item " << key_ << " does not support a string type");
  }
  /**
   * set item value
   */
  bool Set(const std::string&) override
  {
    throw std::invalid_argument(FormatString() << "item " << key_ << " does not support a string type");
  }
  /**
   * Assign signed value to this item
   * @param t - value to be assigned
   */
  virtual void setSigned(int64_t) override
  {
    throw std::invalid_argument(FormatString() << "item " << key_ << " does not support a integer type");
  }
  /**
   * Assign unsigned value to this item
   * @param t - value to be assigned
   */
  virtual void setUnSigned(uint64_t) override
  {
    throw std::invalid_argument(FormatString() << "item " << key_ << " does not support a unsigned type");
  }
  /**
   * Assign unsigned value to this item
   * @param t - value to be assigned
   */
  virtual void setBool(bool) override
  {
    throw std::invalid_argument(FormatString() << "item " << key_ << " does not support a bool type");
  }
  virtual void setDouble(double) override
  {
    throw std::invalid_argument(FormatString() << "item " << key_ << " does not support a double type");
  }
  /**
   * Call this function before set a new value to the item
   * to validate that everything is ok
   */
  void preSet()
  {
    if (basicItem::isSet(removed)) throw std::runtime_error(FormatString() << "item " << key_ << " has been removed");
    if (!basicItem::isSet(empty)) throw std::runtime_error(FormatString() << "item " << key_ << " is duplicated");
    clearBit(empty);
  }
protected:
private:
  const SubString key_;           ///< name for serialization
  item_type type_;                ///< item type
  BitFlags<item_flags> flags_;    ///< some flags

};

//! type traits for json item
template<class T>
struct item_traits
{
public:
  constexpr static item_type type = std::is_floating_point<T>::value ? item_type::floatingPoint : std::is_signed<T>::value ? item_type::signedNumber :
                                    std::is_unsigned<T>::value ? item_type::unsignedNumber : item_type::boolean;
  /// min value for type T
  constexpr static T min = std::is_integral<T>::value ? std::numeric_limits<T>::min() : -std::numeric_limits<T>::max();
  /// max value for type T
  constexpr static const T max = std::numeric_limits<T>::max();
};

/**
 * this class implements set mehods
 */
template<class T>
class singleItem: public basicItem
{
  static_assert(std::is_pointer<T>::value == false,"Items of type pointer are not allowed");
public:
  singleItem(const SubString& key, T min = item_traits<T>::min, T max = item_traits<T>::max) :
      basicItem(key, item_traits<T>::type)
  {

  }
  /// get item value
  T get() const
  {
    return val_;
  }
  /// item implicit convert to its type
  operator T() const
  {
    return val_;
  }
  /**
   * Set a new value to the item of template type
   * @param new value to set pas by reference
   */
  template<typename V>
  void set(V& value)
  {
    basicItem::preSet();
    if (value > max_ || value < min_)
    {
      throw std::out_of_range(FormatString() << "item " << key_ << " value " << value << " is out of range");
    }
    val_ = static_cast<T>(value);
  }
protected:
  /**
   * Assign signed value to this item
   * @param t - value to be assigned
   */
  virtual void setSigned(int64_t t) override
  {
    throw std::invalid_argument(FormatString() << "item " << key_ << " does not support a integer type");
  }
  /**
   * Assign unsigned value to this item
   * @param t - value to be assigned
   */
  virtual void setUnSigned(uint64_t) override
  {
    throw std::invalid_argument(FormatString() << "item " << key_ << " does not support a unsigned type");
  }
  /**
   * Assign unsigned value to this item
   * @param t - value to be assigned
   */
  virtual void setBool(bool) override
  {
    throw std::invalid_argument(FormatString() << "item " << key_ << " does not support a bool type");
  }
  /**
   * Set a value of type doble fpr this item
   * @param s new value to be set
   */
  virtual void setDouble(double s) override
  {
    if (std::is_integral<T>::value) throw std::invalid_argument(FormatString() << "item " << key_ << " does not support a double type");
    //if (s > std::numeric_limits<T>::max()) throw std::out_of_range(FormatString() << "item " << key_ << " value " << s " is out of range");
    return set(s);
  }

private:
  T val_;
  T min_;
  T max_;
};

template<>
class singleItem<std::string>: public basicItem
{

};

typedef singleItem<std::string> singleStringItem;


/**
 * This class is going to be use to hold data on vector
 * it allows us to open a item set value and close it
 */
template<class T, class C = std::vector<T>>
class deferredItem: public singleItem<T>
{
public:
  deferredItem(const SubString& key, T min, T max, C& container) :
      singleItem<T>(key, min, max), container_(container)
  {
  }
  virtual ~deferredItem()
  {

  }
  /**
   * Deferred item will store its value when it is closed
   * Handler has to check for missing values.
   */
  virtual bool close(const SubString& name) override
  {
    singleItem<T>::close(name);
    if (basicItem::isSet(empty))
    {
      //throw handler has to check this
    } else
      container_.push_back(singleItem<T>::get());
    basicItem::setBit(empty);
    return true;
  }
private:
  C& container_;
};

/*
 * Container for simple items
 * string item has to use list
 * basic types can use vector
 */
template<class T>
class singleItemContainer: basicItem
{
public:
  ~singleItemContainer()
  {

  }
protected:
private:
  singleItem<T> item;    /// use it to hold value and pass to vector
  std::vector<T> items_;
  const SubString childKey_;		///< key for subitems if necessary
};

/*
 * Container for string or complex objects
 */
template<class T>
class objectContainer: basicItem
{
public:
  ~objectContainer()
  {

  }
protected:
private:
  std::list<T> items_;

};

/**
 * Item of type object that contains sub items
 */
class ObjectItem: public basicItem
{
public:
protected:
  /**
   * Done working with this object.
   * Validate missing item
   * and duplicates ones
   */
  virtual bool close(const SubString& name) override
  {
    basicItem::close(name);
    // validate mandatory items
    for (auto& i : subitems_)
    {
      if (i->isSet(mandatory) && i->isSet(empty))
      {
        throw std::logic_error(FormatString() << "item " << i->getKey() << " in " << getKey() << " is missing");
      }
    }
    return true;
  }
  /**
   * Find child item
   */
  virtual Iitem* createChild(const SubString& name) override
  {
    for (auto& i : subitems_)
    {
      if (name == i->getKey()) return i;
    }
    return nullptr;
  }
private:
  std::vector<basicItem*> subitems_;    ///<child items
};

#endif /* BASICITEM_H_ */
