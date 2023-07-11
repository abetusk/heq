#include <stdio.h>
#include <stdlib.h>

#include <stdint.h>

void print_hash32(uint32_t *h, uint32_t s, uint32_t n) {
  int32_t i, j, k;
  unsigned char c;

  for (i=0; i<n; i++) {
    printf("  ");
    for (j=0; j<s; j++) {

      for (k=0; k<4; k++) {
        c = ((0xff << (k*8)) & (h[(i*s)+j])) >> (k*8);
        printf("%02x", c);
      }
    }
    printf("\n");

  }
}

unsigned char xor_hash(unsigned char *data, uint32_t n, uint32_t nbit) {
  uint32_t i, j;
  unsigned char res=0, mask=0;
  uint32_t nblock;

  res = 0;
  mask = 0;

  nblock = 8 / nbit;
  for (i=0; i<nbit; i++) {
    mask = mask | (1<<i);
  }

  printf("%02x\n", mask);

  for (i=0; i<n; i++) {
    for (j=0; j<nblock; j++) {
      res = res ^ ((data[i] & (mask << (j*nbit))) >> (j*nbit));
    }
  }

  return res;
}

int main(int argc, char **argv) {
  int32_t i, j, r;
  long int li;

  uint32_t _r;

  uint32_t *hash_id_buf;
  uint32_t hash_stride = 8;

  uint32_t hash_n = 100;

  unsigned char b = 0;

  srand48(0);

  hash_stride = 1;

  hash_id_buf = (uint32_t *)malloc(sizeof(uint32_t)*hash_stride*hash_n);

  li = mrand48();

  for (i=0; i<hash_n; i++) {
    for (j=0; j<hash_stride; j++) {
      _r = (uint32_t)(mrand48());
      hash_id_buf[ (i*hash_stride) + j ] = _r;

      b = xor_hash((unsigned char *)(&(hash_id_buf[i*hash_stride])), hash_stride*4, 2);

      print_hash32(&(hash_id_buf[i*hash_stride]), hash_stride, 1);
      printf("   --> %02x\n", b);

    }
  }


  //print_hash32(hash_id_buf, hash_stride, hash_n);



}
