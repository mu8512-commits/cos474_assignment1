#include "prog2_intrin.h"
#include "logger.h"

//******************
//* Implementation *
//******************

__prog2_mask _prog2_init_ones(int first) {
  __prog2_mask mask;
  for (int i=0; i<VECTOR_WIDTH; i++) {
    mask.value[i] = (i<first) ? true : false;
  }
  return mask;
}

__prog2_mask _prog2_mask_not(__prog2_mask &maska) {
  __prog2_mask resultMask;
  for (int i=0; i<VECTOR_WIDTH; i++) {
    resultMask.value[i] = !maska.value[i];
  }
  prog2_Logger.addLog("masknot", _prog2_init_ones(), VECTOR_WIDTH);
  return resultMask;
}

__prog2_mask _prog2_mask_or(__prog2_mask &maska, __prog2_mask &maskb) {
  __prog2_mask resultMask;
  for (int i=0; i<VECTOR_WIDTH; i++) {
    resultMask.value[i] = maska.value[i] | maskb.value[i];
  }
  prog2_Logger.addLog("maskor", _prog2_init_ones(), VECTOR_WIDTH);
  return resultMask;
}

__prog2_mask _prog2_mask_and(__prog2_mask &maska, __prog2_mask &maskb) {
  __prog2_mask resultMask;
  for (int i=0; i<VECTOR_WIDTH; i++) {
    resultMask.value[i] = maska.value[i] && maskb.value[i];
  }
  prog2_Logger.addLog("maskand", _prog2_init_ones(), VECTOR_WIDTH);
  return resultMask;
}

int _prog2_cntbits(__prog2_mask &maska) {
  int count = 0;
  for (int i=0; i<VECTOR_WIDTH; i++) {
    if (maska.value[i]) count++;
  }
  prog2_Logger.addLog("cntbits", _prog2_init_ones(), VECTOR_WIDTH);
  return count;
}

template <typename T>
void _prog2_vset(__prog2_vec<T> &vecResult, T value, __prog2_mask &mask) {
  for (int i=0; i<VECTOR_WIDTH; i++) {
    vecResult.value[i] = mask.value[i] ? value : vecResult.value[i];
  }
  prog2_Logger.addLog("vset", mask, VECTOR_WIDTH);
}

template void _prog2_vset<float>(__prog2_vec_float &vecResult, float value, __prog2_mask &mask);
template void _prog2_vset<int>(__prog2_vec_int &vecResult, int value, __prog2_mask &mask);

void _prog2_vset_float(__prog2_vec_float &vecResult, float value, __prog2_mask &mask) { _prog2_vset<float>(vecResult, value, mask); }
void _prog2_vset_int(__prog2_vec_int &vecResult, int value, __prog2_mask &mask) { _prog2_vset<int>(vecResult, value, mask); }

__prog2_vec_float _prog2_vset_float(float value) {
  __prog2_vec_float vecResult;
  __prog2_mask mask = _prog2_init_ones();
  _prog2_vset_float(vecResult, value, mask);
  return vecResult;
}
__prog2_vec_int _prog2_vset_int(int value) {
  __prog2_vec_int vecResult;
  __prog2_mask mask = _prog2_init_ones();
  _prog2_vset_int(vecResult, value, mask);
  return vecResult;
}

template <typename T>
void _prog2_vmove(__prog2_vec<T> &dest, __prog2_vec<T> &src, __prog2_mask &mask) {
    for (int i = 0; i < VECTOR_WIDTH; i++) {
        dest.value[i] = mask.value[i] ? src.value[i] : dest.value[i];
    }
    prog2_Logger.addLog("vmove", mask, VECTOR_WIDTH);
}

template void _prog2_vmove<float>(__prog2_vec_float &dest, __prog2_vec_float &src, __prog2_mask &mask);
template void _prog2_vmove<int>(__prog2_vec_int &dest, __prog2_vec_int &src, __prog2_mask &mask);

void _prog2_vmove_float(__prog2_vec_float &dest, __prog2_vec_float &src, __prog2_mask &mask) { _prog2_vmove<float>(dest, src, mask); }
void _prog2_vmove_int(__prog2_vec_int &dest, __prog2_vec_int &src, __prog2_mask &mask) { _prog2_vmove<int>(dest, src, mask); }

template <typename T>
void _prog2_vload(__prog2_vec<T> &dest, T* src, __prog2_mask &mask) {
  for (int i=0; i<VECTOR_WIDTH; i++) {
    dest.value[i] = mask.value[i] ? src[i] : dest.value[i];
  }
  prog2_Logger.addLog("vload", mask, VECTOR_WIDTH);
}

template void _prog2_vload<float>(__prog2_vec_float &dest, float* src, __prog2_mask &mask);
template void _prog2_vload<int>(__prog2_vec_int &dest, int* src, __prog2_mask &mask);

void _prog2_vload_float(__prog2_vec_float &dest, float* src, __prog2_mask &mask) { _prog2_vload<float>(dest, src, mask); }
void _prog2_vload_int(__prog2_vec_int &dest, int* src, __prog2_mask &mask) { _prog2_vload<int>(dest, src, mask); }

template <typename T>
void _prog2_vstore(T* dest, __prog2_vec<T> &src, __prog2_mask &mask) {
  for (int i=0; i<VECTOR_WIDTH; i++) {
    dest[i] = mask.value[i] ? src.value[i] : dest[i];
  }
  prog2_Logger.addLog("vstore", mask, VECTOR_WIDTH);
}

template void _prog2_vstore<float>(float* dest, __prog2_vec_float &src, __prog2_mask &mask);
template void _prog2_vstore<int>(int* dest, __prog2_vec_int &src, __prog2_mask &mask);

void _prog2_vstore_float(float* dest, __prog2_vec_float &src, __prog2_mask &mask) { _prog2_vstore<float>(dest, src, mask); }
void _prog2_vstore_int(int* dest, __prog2_vec_int &src, __prog2_mask &mask) { _prog2_vstore<int>(dest, src, mask); }

template <typename T>
void _prog2_vadd(__prog2_vec<T> &vecResult, __prog2_vec<T> &veca, __prog2_vec<T> &vecb, __prog2_mask &mask) {
  for (int i=0; i<VECTOR_WIDTH; i++) {
    vecResult.value[i] = mask.value[i] ? (veca.value[i] + vecb.value[i]) : vecResult.value[i];
  }
  prog2_Logger.addLog("vadd", mask, VECTOR_WIDTH);
}

template void _prog2_vadd<float>(__prog2_vec_float &vecResult, __prog2_vec_float &veca, __prog2_vec_float &vecb, __prog2_mask &mask);
template void _prog2_vadd<int>(__prog2_vec_int &vecResult, __prog2_vec_int &veca, __prog2_vec_int &vecb, __prog2_mask &mask);

void _prog2_vadd_float(__prog2_vec_float &vecResult, __prog2_vec_float &veca, __prog2_vec_float &vecb, __prog2_mask &mask) { _prog2_vadd<float>(vecResult, veca, vecb, mask); }
void _prog2_vadd_int(__prog2_vec_int &vecResult, __prog2_vec_int &veca, __prog2_vec_int &vecb, __prog2_mask &mask) { _prog2_vadd<int>(vecResult, veca, vecb, mask); }

template <typename T>
void _prog2_vsub(__prog2_vec<T> &vecResult, __prog2_vec<T> &veca, __prog2_vec<T> &vecb, __prog2_mask &mask) {
  for (int i=0; i<VECTOR_WIDTH; i++) {
    vecResult.value[i] = mask.value[i] ? (veca.value[i] - vecb.value[i]) : vecResult.value[i];
  }
  prog2_Logger.addLog("vsub", mask, VECTOR_WIDTH);
}

template void _prog2_vsub<float>(__prog2_vec_float &vecResult, __prog2_vec_float &veca, __prog2_vec_float &vecb, __prog2_mask &mask);
template void _prog2_vsub<int>(__prog2_vec_int &vecResult, __prog2_vec_int &veca, __prog2_vec_int &vecb, __prog2_mask &mask);

void _prog2_vsub_float(__prog2_vec_float &vecResult, __prog2_vec_float &veca, __prog2_vec_float &vecb, __prog2_mask &mask) { _prog2_vsub<float>(vecResult, veca, vecb, mask); }
void _prog2_vsub_int(__prog2_vec_int &vecResult, __prog2_vec_int &veca, __prog2_vec_int &vecb, __prog2_mask &mask) { _prog2_vsub<int>(vecResult, veca, vecb, mask); }

template <typename T>
void _prog2_vmult(__prog2_vec<T> &vecResult, __prog2_vec<T> &veca, __prog2_vec<T> &vecb, __prog2_mask &mask) {
  for (int i=0; i<VECTOR_WIDTH; i++) {
    vecResult.value[i] = mask.value[i] ? (veca.value[i] * vecb.value[i]) : vecResult.value[i];
  }
  prog2_Logger.addLog("vmult", mask, VECTOR_WIDTH);
}

template void _prog2_vmult<float>(__prog2_vec_float &vecResult, __prog2_vec_float &veca, __prog2_vec_float &vecb, __prog2_mask &mask);
template void _prog2_vmult<int>(__prog2_vec_int &vecResult, __prog2_vec_int &veca, __prog2_vec_int &vecb, __prog2_mask &mask);

void _prog2_vmult_float(__prog2_vec_float &vecResult, __prog2_vec_float &veca, __prog2_vec_float &vecb, __prog2_mask &mask) { _prog2_vmult<float>(vecResult, veca, vecb, mask); }
void _prog2_vmult_int(__prog2_vec_int &vecResult, __prog2_vec_int &veca, __prog2_vec_int &vecb, __prog2_mask &mask) { _prog2_vmult<int>(vecResult, veca, vecb, mask); }

template <typename T>
void _prog2_vdiv(__prog2_vec<T> &vecResult, __prog2_vec<T> &veca, __prog2_vec<T> &vecb, __prog2_mask &mask) {
  for (int i=0; i<VECTOR_WIDTH; i++) {
    vecResult.value[i] = mask.value[i] ? (veca.value[i] / vecb.value[i]) : vecResult.value[i];
  }
  prog2_Logger.addLog("vdiv", mask, VECTOR_WIDTH);
}

template void _prog2_vdiv<float>(__prog2_vec_float &vecResult, __prog2_vec_float &veca, __prog2_vec_float &vecb, __prog2_mask &mask);
template void _prog2_vdiv<int>(__prog2_vec_int &vecResult, __prog2_vec_int &veca, __prog2_vec_int &vecb, __prog2_mask &mask);

void _prog2_vdiv_float(__prog2_vec_float &vecResult, __prog2_vec_float &veca, __prog2_vec_float &vecb, __prog2_mask &mask) { _prog2_vdiv<float>(vecResult, veca, vecb, mask); }
void _prog2_vdiv_int(__prog2_vec_int &vecResult, __prog2_vec_int &veca, __prog2_vec_int &vecb, __prog2_mask &mask) { _prog2_vdiv<int>(vecResult, veca, vecb, mask); }

template <typename T>
void _prog2_vabs(__prog2_vec<T> &vecResult, __prog2_vec<T> &veca, __prog2_mask &mask) {
  for (int i=0; i<VECTOR_WIDTH; i++) {
    vecResult.value[i] = mask.value[i] ? (abs(veca.value[i])) : vecResult.value[i];
  }
  prog2_Logger.addLog("vabs", mask, VECTOR_WIDTH);
}

template void _prog2_vabs<float>(__prog2_vec_float &vecResult, __prog2_vec_float &veca, __prog2_mask &mask);
template void _prog2_vabs<int>(__prog2_vec_int &vecResult, __prog2_vec_int &veca, __prog2_mask &mask);

void _prog2_vabs_float(__prog2_vec_float &vecResult, __prog2_vec_float &veca, __prog2_mask &mask) { _prog2_vabs<float>(vecResult, veca, mask); }
void _prog2_vabs_int(__prog2_vec_int &vecResult, __prog2_vec_int &veca, __prog2_mask &mask) { _prog2_vabs<int>(vecResult, veca, mask); }

template <typename T>
void _prog2_vgt(__prog2_mask &maskResult, __prog2_vec<T> &veca, __prog2_vec<T> &vecb, __prog2_mask &mask) {
  for (int i=0; i<VECTOR_WIDTH; i++) {
    maskResult.value[i] = mask.value[i] ? (veca.value[i] > vecb.value[i]) : maskResult.value[i];
  }
  prog2_Logger.addLog("vgt", mask, VECTOR_WIDTH);
}

template void _prog2_vgt<float>(__prog2_mask &maskResult, __prog2_vec_float &veca, __prog2_vec_float &vecb, __prog2_mask &mask);
template void _prog2_vgt<int>(__prog2_mask &maskResult, __prog2_vec_int &veca, __prog2_vec_int &vecb, __prog2_mask &mask);

void _prog2_vgt_float(__prog2_mask &maskResult, __prog2_vec_float &veca, __prog2_vec_float &vecb, __prog2_mask &mask) { _prog2_vgt<float>(maskResult, veca, vecb, mask); }
void _prog2_vgt_int(__prog2_mask &maskResult, __prog2_vec_int &veca, __prog2_vec_int &vecb, __prog2_mask &mask) { _prog2_vgt<int>(maskResult, veca, vecb, mask); }

template <typename T>
void _prog2_vlt(__prog2_mask &maskResult, __prog2_vec<T> &veca, __prog2_vec<T> &vecb, __prog2_mask &mask) {
  for (int i=0; i<VECTOR_WIDTH; i++) {
    maskResult.value[i] = mask.value[i] ? (veca.value[i] < vecb.value[i]) : maskResult.value[i];
  }
  prog2_Logger.addLog("vlt", mask, VECTOR_WIDTH);
}

template void _prog2_vlt<float>(__prog2_mask &maskResult, __prog2_vec_float &veca, __prog2_vec_float &vecb, __prog2_mask &mask);
template void _prog2_vlt<int>(__prog2_mask &maskResult, __prog2_vec_int &veca, __prog2_vec_int &vecb, __prog2_mask &mask);

void _prog2_vlt_float(__prog2_mask &maskResult, __prog2_vec_float &veca, __prog2_vec_float &vecb, __prog2_mask &mask) { _prog2_vlt<float>(maskResult, veca, vecb, mask); }
void _prog2_vlt_int(__prog2_mask &maskResult, __prog2_vec_int &veca, __prog2_vec_int &vecb, __prog2_mask &mask) { _prog2_vlt<int>(maskResult, veca, vecb, mask); }

template <typename T>
void _prog2_veq(__prog2_mask &maskResult, __prog2_vec<T> &veca, __prog2_vec<T> &vecb, __prog2_mask &mask) {
  for (int i=0; i<VECTOR_WIDTH; i++) {
    maskResult.value[i] = mask.value[i] ? (veca.value[i] == vecb.value[i]) : maskResult.value[i];
  }
  prog2_Logger.addLog("veq", mask, VECTOR_WIDTH);
}

template void _prog2_veq<float>(__prog2_mask &maskResult, __prog2_vec_float &veca, __prog2_vec_float &vecb, __prog2_mask &mask);
template void _prog2_veq<int>(__prog2_mask &maskResult, __prog2_vec_int &veca, __prog2_vec_int &vecb, __prog2_mask &mask);

void _prog2_veq_float(__prog2_mask &maskResult, __prog2_vec_float &veca, __prog2_vec_float &vecb, __prog2_mask &mask) { _prog2_veq<float>(maskResult, veca, vecb, mask); }
void _prog2_veq_int(__prog2_mask &maskResult, __prog2_vec_int &veca, __prog2_vec_int &vecb, __prog2_mask &mask) { _prog2_veq<int>(maskResult, veca, vecb, mask); }

template <typename T>
void _prog2_hadd(__prog2_vec<T> &vecResult, __prog2_vec<T> &vec) {
  for (int i=0; i<VECTOR_WIDTH/2; i++) {
    T result = vec.value[2*i] + vec.value[2*i+1];
    vecResult.value[2 * i] = result;
    vecResult.value[2 * i + 1] = result;
  }
}

template void _prog2_hadd<float>(__prog2_vec_float &vecResult, __prog2_vec_float &vec);

void _prog2_hadd_float(__prog2_vec_float &vecResult, __prog2_vec_float &vec) { _prog2_hadd<float>(vecResult, vec); }

template <typename T>
void _prog2_interleave(__prog2_vec<T> &vecResult, __prog2_vec<T> &vec) {
  for (int i=0; i<VECTOR_WIDTH; i++) {
    int index = i < VECTOR_WIDTH/2 ? (2 * i) : (2 * (i - VECTOR_WIDTH/2) + 1);
    vecResult.value[i] = vec.value[index];
  }
}

template void _prog2_interleave<float>(__prog2_vec_float &vecResult, __prog2_vec_float &vec);

void _prog2_interleave_float(__prog2_vec_float &vecResult, __prog2_vec_float &vec) { _prog2_interleave<float>(vecResult, vec); }

void addUserLog(const char * logStr) {
  prog2_Logger.addLog(logStr, _prog2_init_ones(), 0);
}

