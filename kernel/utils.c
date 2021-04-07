void execute(char *input) {
  if (compare_string(input, "EXIT") == 0) {
    print_string("Exiting..\n");
    asm volatile("hlt");
  }

  print_string("Unknown command: ");
  print_string(input);
  print_string("\n:: ");
}

