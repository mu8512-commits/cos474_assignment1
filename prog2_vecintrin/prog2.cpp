#include "prog2_intrin.h"

// computes the absolute value of all elements in the input array
// values, stores result in output
void absSerial(float* values, float* output, int N) {
  for (int i = 0; i < N; i++) {
    float x = values[i];
    if (x < 0) {
      output[i] = -x;
    } else {
      output[i] = x;
    }
  }
}

// implementation of absSerial() above, but it is vectorized using the fake
// intrinsics
void absVector(float* values, float* output, int N) {
  __prog2_vec_float x;
  __prog2_vec_float result;
  __prog2_vec_float zero = _prog2_vset_float(0.f);
  __prog2_mask maskAll, maskIsNegative, maskIsNotNegative;

  //  Note: Take a careful look at this loop indexing.  This example
  //  code is not guaranteed to work when (N % VECTOR_WIDTH) != 0.
  //  Why is that the case?
  for (int i = 0; i < N; i += VECTOR_WIDTH) {
    // All ones
    maskAll = _prog2_init_ones();

    // All zeros
    maskIsNegative = _prog2_init_ones(0);

    // Load vector of values from contiguous memory addresses
    _prog2_vload_float(x, values + i, maskAll);  // x = values[i];

    // Set mask according to predicate
    _prog2_vlt_float(maskIsNegative, x, zero, maskAll);  // if (x < 0) {

    // Execute instruction using mask ("if" clause)
    _prog2_vsub_float(result, zero, x, maskIsNegative);  //   output[i] = -x;

    // Inverse maskIsNegative to generate "else" mask
    maskIsNotNegative = _prog2_mask_not(maskIsNegative);  // } else {

    // Execute instruction ("else" clause)
    _prog2_vload_float(result, values + i,
                       maskIsNotNegative);  //   output[i] = x; }

    // Write results back to memory
    _prog2_vstore_float(output + i, result, maskAll);
  }
}

// accepts an array of values and an array of exponents
//
// For each element, compute values[i]^exponents[i] and clamp value to
// 9.999.  Store result in output.
void clampedExpSerial(float* values, int* exponents, float* output, int N) {
  for (int i = 0; i < N; i++) {
    float x = values[i];
    int y = exponents[i];
    if (y == 0) {
      output[i] = 1.f;
    } else {
      float result = x;
      int count = y - 1;
      while (count > 0) {
        result *= x;
        count--;
      }
      if (result > 9.999999f) {
        result = 9.999999f;
      }
      output[i] = result;
    }
  }
}

void clampedExpVector(float* values, int* exponents, float* output, int N) {
  //
  // ECE476 STUDENTS TODO: Implement your vectorized version of
  // clampedExpSerial() here.
  //
  // Your solution should work for any value of
  // N and VECTOR_WIDTH, not just when VECTOR_WIDTH divides N
  //
  //
}

// returns the sum of all elements in values
float arraySumSerial(float* values, int N) {
  float sum = 0;
  for (int i = 0; i < N; i++) {
    sum += values[i];
  }

  return sum;
}

// returns the sum of all elements in values
// You can assume N is a multiple of VECTOR_WIDTH
// You can assume VECTOR_WIDTH is a power of 2
float arraySumVector(float* values, int N) {
  //
  // ECE476 STUDENTS TODO: Implement your vectorized version of arraySumSerial
  // here
  //
  // This is extra credit.

  return 0.0;
}