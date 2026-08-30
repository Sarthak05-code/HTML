#include <stdio.h>

int main() {
  int frames[3] = {-1, -1, -1}; // -1 means empty frame
  int values[] = {1, 2, 3, 4, 1, 2, 7, 3, 6, 3, 5, 2, 1, 3, 42, 2};

  int n = sizeof(values) / sizeof(values[0]);
  int pageFault = 0;
  int pointer = 0; // FIFO replacement pointer

  printf("Page\tFrames\t\tStatus\n");
  printf("---------------------------------------\n");

  for (int i = 0; i < n; i++) {
    int currentPage = values[i];
    int found = 0;

    // Check if page already exists in any frame
    for (int j = 0; j < 3; j++) {
      if (frames[j] == currentPage) {
        found = 1;
        break;
      }
    }

    if (found) {
      printf("%d\t%d %d %d\tHit\n", currentPage, frames[0], frames[1],
             frames[2]);
    } else {
      // Replace the oldest page
      frames[pointer] = currentPage;
      pointer = (pointer + 1) % 3;
      pageFault++;

      printf("%d\t%d %d %d\tFault\n", currentPage, frames[0], frames[1],
             frames[2]);
    }
  }

  printf("---------------------------------------\n");
  printf("Total Page Faults = %d\n", pageFault);

  return 0;
}
