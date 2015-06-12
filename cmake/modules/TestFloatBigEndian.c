int main() {
  float f = -0.f;
  unsigned char *ptr = (unsigned char*) &f;
  int is_big = (ptr[3] == 0x80u);
  if (!is_big)
    return -1;
}
~
