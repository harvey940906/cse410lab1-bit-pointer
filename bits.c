/* 
 * CSE 410 Lab 1 (Data Lab )
 * 
 * Junfei Zhang, jz39
 * 
 * bits.c - Source file with your solutions to the Lab.
 *          This is the file you will hand in to your instructor.
 *
 * WARNING: Do not include the <stdio.h> header; it confuses the dlc
 * compiler. You can still use printf for debugging without including
 * <stdio.h>, although you might get a compiler warning. In general,
 * it's not good practice to ignore compiler warnings, but in this
 * case it's OK.  
 */

#if 0
/*
 * Instructions to Students:
 *
 * STEP 1: Read the following instructions carefully.
 */

You will provide your solution to this homework by
editing the collection of functions in this source file.

INTEGER CODING RULES:
 
  Replace the "return" statement in each function with one
  or more lines of C code that implements the function. Your code 
  must conform to the following style:
 
  int Funct(arg1, arg2, ...) {
      /* brief description of how your implementation works */
      int var1 = Expr1;
      ...
      int varM = ExprM;

      varJ = ExprJ;
      ...
      varN = ExprN;
      return ExprR;
  }

  Each "Expr" is an expression using ONLY the following:
  1. Integer constants 0 through 255 (0xFF), inclusive. You are
     not allowed to use big constants such as 0xFFFFFFFF. 
     However you are allowed to add constants to values greater
     than 255. e.g. 250+250 = 500.
  2. Function arguments and local variables (no global variables).
  3. Unary integer operations ! ~
  4. Binary integer operations & ^ | + << >>
    
  Some of the problems restrict the set of allowed operators even further.
  Each "Expr" may consist of multiple operators. You are not restricted to
  one operator per line.

  You are expressly forbidden to:
  1. Use any control constructs such as if, do, while, for, switch, etc.
  2. Define or use any macros.
  3. Define any additional functions in this file.
  4. Call any functions.
  5. Use any other operations, such as &&, ||, -, ?, ==, or !=:
  6. Use any form of casting.
  7. Use any data type other than int.  This implies that you
     cannot use arrays, structs, or unions.

 
  You may assume that your machine:
  1. Uses 2s complement, 32-bit representations of integers.
  2. Performs right shifts arithmetically.
  3. Has *undefined* behavior when shifting by a negative amount or an amount
  greater than or equal to the number of bits in the value being shifted.
  e.g. For x >> n, shifts by n < 0 or n >= *size of x* are undefined 
  e.g. if x is a 32-bit int, shifts by >= 32 bits are undefined 
  Undefined means you do not know what result you will get from the operation.

EXAMPLES OF ACCEPTABLE CODING STYLE:
  /*
   * pow2plus1 - returns 2^x + 1, where 0 <= x <= 31
   */
  int pow2plus1(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     return (1 << x) + 1;
  }

  /*
   * pow2plus4 - returns 2^x + 4, where 0 <= x <= 31
   */
  int pow2plus4(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     int result = (1 << x);
     result += 4;
     return result;
  }

NOTES:
  1. Use the dlc (data lab checker) compiler (described in the handout) to 
     check the legality of your solutions.
  2. Each function has a maximum number of operators (! ~ & ^ | + << >>)
     that you are allowed to use for your implementation of the function. 
     The max operator count is checked by dlc. Note that '=' is not 
     counted; you may use as many of these as you want without penalty.
  3. Use the btest test harness to check your functions for correctness.
  5. The maximum number of ops for each function is given in the
     header comment for each function. If there are any inconsistencies 
     between the maximum ops in the writeup and in this file, consider
     this file the authoritative source.

/*
 * STEP 2: Modify the following functions according the coding rules.
 * 
 *   IMPORTANT. TO AVOID GRADING SURPRISES:
 *   1. Use the dlc compiler to check that your solutions conform
 *      to the coding rules.
 */


#endif

// /*
//  * Included for reference (compare to print_binary_fp).
//  */
// void print_binary(int x) {
//   int i;
//   // start at MSB and go backwards (decrement)
//   for(i=31; i>=0; i--) {
//     // print the i-th bit (0 or 1)
//     printf("%d", (x>>i) & 0x1);
//     // add spaces to make more human-readable
//     if(i%8 == 0) printf(" ");
//     if(i%4 == 0) printf(" ");
//   }
//   printf("\n");
// }

// Rating: 1
/* 
 * bitAnd - x&y using only ~ and | 
 *   Example: bitAnd(6, 5) = 4
 *   Legal ops: ~ |
 *   Max ops: 8
 *   Rating: 1
 */
int bitAnd(int x, int y) {
  x = ~x;
  y = ~y;
  x = x | y; // only double 1 = 0, doule 0 and 1&0 = 1
  return ~x;
}
/* 
 * bitXor - x^y using only ~ and & 
 *   Example: bitXor(4, 5) = 1
 *   Legal ops: ~ &
 *   Max ops: 14
 *   Rating: 1
 */
int bitXor(int x, int y) {
  int rxy = ~x & y; //x's bits 0 (only which should be 1 after xor) become 1
  int xry = x & ~y; //y's bits 0 (only which should be 1 after xor) become 1
  return ~(~rxy & ~xry);
  // (~rxy & ~xry) finds same bits of x and y
  // outter ~ finds different bit of x and y, aka Xor
}
/* 
 * thirdBits - return 32-bit quantity with every third bit 
 * (starting from the least significant bit) set to 1 (other bits set to zero).
 * For further clarification from and including the least signifigant bit 
 * each bit at an index that is a multiple of three should be set to 1. 
 * This is represented by the set {0, 3, 6, 9,...} all other bits should be
 * set to 0.
 *   Example: ....1001001
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 8
 *   Rating: 1
 */
int thirdBits(void) {
  int x = 0x49; //0100 1001, 0 3 6 okay
  x = x << 9; // 9 12 15 bits okay
  x = x + 0x49; //03691215 okay
  x = x << 6; // 6-21 okay
  x = x + 9; // 0-21 okay
  x = x << 9; // 9-30 okay
  x = x + 0x49; //0-32 okay
  return x;
}
/* 
 * sign - return 1 if positive, 0 if zero, and -1 if negative
 *  Examples: sign(130) = 1
 *            sign(-23) = -1
 *  Legal ops: ! ~ & ^ | + << >>
 *  Max ops: 10
 *  Rating: 2
 */
int sign(int x) {
  int a = x >> 31; // positive or 0 ? 0 : OxFFFFFFFF
  int b = ~x >> 31; // positive or 0 ? OxFFFFFFFF : 0
  return a + (b & !!x);
  // a for negitive, b for positive
}
/* 
 * getByte - Extract byte n from int x
 *   Bytes numbered from 0 (LSB) to 3 (MSB)
 *   Examples: getByte(0x12345678,1) = 0x56
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 6
 *   Rating: 2
 */
int getByte(int x, int n) {
  x = x >> (n << 3); // n = 8
  x = x & 0xFF; // remove front bits
  return x;
}
// Rating: 3
/* 
 * fitsBits - return 1 if x can be represented as an 
 *  n-bit, two's complement integer.
 *   1 <= n <= 32
 *   Examples: fitsBits(5,3) = 0, fitsBits(-4,3) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 15
 *   Rating: 3
 */
int fitsBits(int x, int n) {
  int s = 33 + ~n; // 33 - n - 1
  int xs = (x << s) >> s; // shake off unfit, remain fit
  x = x ^ xs; // get potential negitive sign and unfit back
  return !x;
}
// Rating: 3
/* 
 * logicalShift - shift x to the right by n, using a logical shift
 *   Can assume that 0 <= n <= 31
 *   Examples: logicalShift(0x87654321,4) = 0x08765432
 *   Legal ops: ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 3 
 */
int logicalShift(int x, int n) {
  int xs = x >> n; // get n arithmetical 1 first
  x = xs & ~(((1 << 31) >> n) << 1); // get n 1(not n+1), turn to 0
  return x;
}
/* 
 * addOK - Determine if can compute x+y without overflow
 *   Example: addOK(0x80000000,0x80000000) = 0,
 *            addOK(0x80000000,0x70000000) = 1, 
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 3
 */
int addOK(int x, int y) {
  int sum = x + y;
  return !(((sum ^ x) & (sum ^ y)) >> 31);
  // sum ^ x and y and & for the MSB
  // positive + negetive always fine
  // positive + posative and negitive + negative cannot affect MSB
}
/* invert - Return x with the n bits that begin at position p inverted 
 *          (i.e., turn 0 into 1 and vice versa) and the rest left 
 *          unchanged. Consider the indices of x to begin with the low-order
 *          bit numbered as 0.
 *   Can assume that 0 <= n <= 31 and 0 <= p <= 31
 *   Example: invert(0x80000000, 0, 1) = 0x80000001,
 *            invert(0x0000008e, 3, 3) = 0x000000b6,
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 3  
 */
int invert(int x, int p, int n) {
  int top = 1 << 31; // MSB
  int mask = top >> n; // n + 1 bit in front
  mask = mask ^ top; // 0 in front, n bit follow by
  mask = mask >> (32 + ~(p+n)); // 32 + ~(p+n) correct postion
  return x ^ mask;
}
// Rating: 4
/* 
 * bang - Compute !x without using !
 *   Examples: bang(3) = 0, bang(0) = 1
 *   Legal ops: ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 4 
 */
int bang(int x) {
  x = ((~x + 1) | x) >> 31; // ~x + 1 deals with x = 0
  // otherwise, all become 0xFFFFFFFF
  return x + 1;
}

// Extra Credit: Rating: 4
/*
 * isPower2 - returns 1 if x is a power of 2, and 0 otherwise
 *   Examples: isPower2(5) = 0, isPower2(8) = 1, isPower2(0) = 0
 *   Note that no negative number is a power of 2.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 4
 */
int isPower2(int x) {
  int min_one = ~0; // -1
  int sign = x >> 31;
  int y = min_one ^ sign; // x >= 0 ? -1 : 0
  x = (x & (x + y)) + !x; // if isPower2, x & (x-1) = 0; !x for 0
  return !x;
}
