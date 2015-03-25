/*
 * iItem.h
 *
 *  Created on: 24 Mar 2015
 *      Author: lester
 */

#ifndef IITEM_H_
#define IITEM_H_


class Iitem
{
  const char* getName();
protected:
  /// not allowed to delete object throught the interface
  virtual ~Iitem() {};
};


#endif /* IITEM_H_ */
