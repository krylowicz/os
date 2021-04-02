// kernel entry func instead of jumping to kernel.c:0x00
void test_entrypoint() {

}

void main() {
  char* video_memory = 0xb8000;
  *video_memory = 'X';
}

