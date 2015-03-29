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
 * How de-serialization has to be done
 * root object, name and type to be validate, no need to be open it, it is not mandatory
 * open item does not means that has a value.
 * open objects and container implies clear empty bit.
 * empty items are considered valid for string type. numerical item will complain
 * xml empty tag will produce set empty string
 * closing an item inside container without value will produce an error
 *
 */
enum class item_type
{
	none, ///<
	object, ///<
	container, ///<
	string, ///<
	signedNumber, ///<
	unsignedNumber, ///<
	floatingPoint, ///<
	boolean,
};

//
enum item_flags
{
	none, empty,      ///< item does not have data
	mandatory,  ///< item is mandatory
	removed,    ///< item marked as remove
};

class Iitem
{
public:
	virtual const SubString& getKey() const = 0;
	virtual Iitem* createChild(const SubString& name) = 0;
	/**
	 * No more data for this item, validate it
	 * false if item does not validate fine
	 */
	virtual bool close(const SubString& name) = 0;
	/**
	 * Return false if value was already set
	 */
	virtual bool Set(const std::string& value) = 0; // Item has to interpret this
	/**
	 * Item has to interpret this
	 */
	virtual bool Set(const SubString& value) = 0;
	/**
	 * Assign signed value to this item
	 * @param t - value to be assigned
	 */
	virtual void setSigned(int64_t) = 0;
	/**
	 * Assign unsigned value to this item
	 * @param t - value to be assigned
	 */
	virtual void setUnSigned(uint64_t) = 0;
	/**
	 * Assign unsigned value to this item
	 * @param t - value to be assigned
	 */
	virtual void setBool(bool) = 0;
	/**
	 * Get item type
	 */
	virtual item_type getType() const = 0;
	/**
	 * Read flag status
	 */
	virtual bool isSet(item_flags) const = 0; ///< Test for a specific flag
	virtual void setBit(item_flags) = 0;      ///< activate flag
	virtual void clearBit(item_flags) = 0;    ///< clear flag
	//Set(T& val) - it is hard to figure out with method call base on type
protected:
	/// not allowed to delete object throught the interface
	virtual ~Iitem()
	{
	}
	;
};

#endif /* IITEM_H_ */
