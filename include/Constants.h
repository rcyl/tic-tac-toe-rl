/*
 * Constants.h
 *
 *  Created on: 23 Jan, 2017
 *      Author: rcyl
 */

#ifndef INCLUDE_CONSTANTS_H_
#define INCLUDE_CONSTANTS_H_

#include <tuple>

typedef enum {
	O = 0,
	X = 1,
	E = 2
} sym;

//tuple takes in array of features, and their training values
typedef std::tuple<int *, double> train_t;

#define SYMNUM 3
#define NUMFEAT 7 //technically only 6 features, 1st feature is always 1

#endif /* INCLUDE_CONSTANTS_H */
