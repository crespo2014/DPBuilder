/*
 * iWritter.h
 *
 *  Created on: 27 Mar 2015
 *      Author: lester.crespo
 *
 *   Writter interface for serialization
 */

#ifndef IWRITTER_H_
#define IWRITTER_H_

class iWritter
{
  void StartObject(const char* name);
  void EndObject(const char* name);
  void StartContainer(const char* name);
  void EndContainer(const char* name);
  void Item(const char* name,const char* value);  // what about formatiing. do we need a method per type
}

#endif /* IWRITTER_H_ */
