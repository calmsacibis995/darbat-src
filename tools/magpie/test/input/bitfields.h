typedef unsigned int Word;

typedef struct {
  Word a : 10;

  Word b : (sizeof(Word) * 8 - 10);

} foo;
