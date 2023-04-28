/*

ARDUINO FOR MAKERS
702: Data Types
Example Code

This documens is for reference only. It is not
a fully executable sketch, but rather a visual
aid for the details discussed in the course.

*/

// INTEGER
// ================================================
// The primary data-type for number storage,
// with a range of -32.768 to 32,767 on most boards
// ================================================

// Stores the value of 100 into the 'age'
// integer variable:
int age = 100;

// ARRAY
// ================================================
// A collection of variables that are accessed with
// an index number and preceded by the type of
// its contents. The size can optionally be declared
// witin brackets.
// ================================================

// Creates an array of integers (int) with an
// unknown length, and fills it with 4 values:
int scores[] = {12,23,45,67};

// Accesses the item in the 'scores' array using
// the position of 0, which is the first item
// and stores the reference into the 'myScore' 
// variable:
int myScore = scores[0];

// Updates the first item in the array to 500.
// The scores array would now read: {500,23,34,67}
scores[0] = 500;

// CHAR
// ================================================
// A single character value, indicated with the
// character within single quotes or with the
// ASCII code.
// ================================================

// Stores the character B into the 'initial' 
// variable:
char initial = 'B';

// This can also be written as:
// char initial = 66;

// FLOAT
// ================================================
// A number that has a decimal point. They can
// store 32 bits of data (as large as 3.4028235E+38
// and as low as -3.4028235E+38).
// ================================================

// Stores a decimal number into the
// myDecimalNumber variable:
float myDecimalNumber = 100.5;

