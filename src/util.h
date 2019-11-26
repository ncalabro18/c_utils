#ifndef UTIL_H
#define UTIL_H


//used to make pointer arithmetic simpler
//also conceptually make more sense
//in most application of byte*, its referring
//to a location which contains a certain
//amount of bytes which will be copied
typedef char byte;

//FAILURE is 0, SUCCESS is 1
//to test for an error in a function,
//either comparing it to FAILURE would
//work or simply doing:
//if(!<function_name>(...))
//  { // error handling here}
typedef enum _status {
	FAILURE = 0, SUCCESS = 1
}Status;


typedef enum _boolean {
	FALSE = 0, TRUE = 1
} Boolean;


#endif 
