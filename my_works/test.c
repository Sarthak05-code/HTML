#include "types.h"
#include <stdio.h>
#include <stdlib.h>
#include <synchapi.h>
#include <sys/time.h>

const char *SENTENCES[] = {
    "The rain was pouring yesterday and the flood kept happening today",
    "The night was young and so was the youth, feeling the moment i asked her "
    "what is for food.",
    "the fox was quick to underestimate his opponent, fed by the ego, he "
    "mocked the hare tripping and falling to his death.",
    "The war, everyone thought has ended, where everyone has taken a signed "
    "relief, was just the beginning of another terror in the horizon",
    "Feeling the need to sleep and rejuvenate, he took a quick nap in the "
    "coop, waking up to be covered in the feces of the animals that were "
    "domesticated here.",
    "She was a material girl, dumb but smiling. Taking a trip to Paris, she "
    "bought every clothes she liked, and no place to stay and sleep, she used "
    "the clothes she brought and made it a home, a beggar for a person to "
    "mistake as.",
    "Young was his soul as he slept, bullied, he dreamt of vengeance on his "
    "bullies, he punched and punched the bullies in his sleep, waking up to "
    "his mother scolding him for he punches he gave her in his sleep",
    "The dispute rose between the philosopher, for whom shall take the spoon "
    "and eat among them, the food grew cold and tasteless. They left home "
    "hungry, while the Indians watched as they ate from their hand confused.",
    "The doctor checked the patient and asked her, what was the problem ,she "
    "said she heard her friends mention they have a mouse running in their "
    "belly, concerned she wanted to make sure she doesn't have a rat in her "
    "belly.",

};

int main(void) {
  // srand((unsigned int)time(NULL));

  // i32 count = sizeof(SENTENCES) / sizeof(SENTENCES[0]);
  // const char *sentence = SENTENCES[rand() % count];
  i64 WORDCOUNT = 0; // NOTE : helps count the words in the entire sentence.
  for (i32 init = 0; init < sizeof(SENTENCES) / sizeof(SENTENCES[0]); init++) {
    const char *sentence = SENTENCES[init];
    if (sentence[0] == '\0') {
      printf("The sentence is empty!\n");
      return EXIT_FAILURE;
    }
    i64 i = 0; // NOTE : is the name as int64_t
    printf("Sentence [%d]: ", init + 1);

    do {
      printf("%c", sentence[i]);
      fflush(stdout);
      Sleep(10);
      if (sentence[i] != ' ' AND(i == 0 OR sentence[i - 1] ==
                                 ' ')) { // NOTE : counting every words bar the
                                         // whitespace or the \0.
        WORDCOUNT++;
      }
      i++;

    } while (sentence[i] != '\0');
    printf("\n");
  }
  printf("The amount of words in this sentence is : %lld", WORDCOUNT);
  return EXIT_SUCCESS;
}
