byte a[] = {31, 40, 72, 136, 136, 72, 40, 31};
byte b[] = {255, 145, 145, 145, 145, 145, 145, 110};
byte c[] = {60, 66, 129, 129, 129, 129, 129, 66};
byte d[] = {255, 129, 129, 129, 129, 129, 66, 60};
byte e[] = {255, 145, 145, 145, 145, 145, 145, 129};
byte f[] = {255, 144, 144, 144, 144, 144, 128, 128};
byte g[] = {60, 66, 129, 129, 137, 137, 137, 78};
byte h[] = {255, 16, 16, 16, 16, 16, 16, 255};
byte i[] = {0, 129, 129, 129, 255, 129, 129, 129};
byte j[] = {0, 6, 129, 129, 129, 254, 128, 128};
byte k[] = {0, 255, 16, 16, 40, 68, 131, 0};
byte l[] = {255, 1, 1, 1, 1, 1, 1, 1};
byte m[] = {255, 64, 32, 16, 16, 32, 64, 255};
byte n[] = {255, 64, 32, 16, 8, 4, 2, 255};
byte o[] = {60, 66, 129, 129, 129, 129, 66, 60};
byte p[] = {255, 144, 144, 144, 144, 144, 144, 96};
byte q[] = {60, 66, 129, 129, 129, 133, 66, 61};
byte r[] = {255, 144, 144, 144, 152, 148, 146, 97};
byte s[] = {114, 145, 145, 145, 145, 145, 145, 78};
byte t[] = {0, 128, 128, 128, 255, 128, 128, 128};
byte u[] = {252, 2, 1, 1, 1, 1, 2, 252};
byte v[] = {192, 48, 12, 3, 3, 12, 48, 192};
byte w[] = {255, 2, 4, 8, 8, 4, 2, 255};
byte x[] = {129, 66, 36, 24, 24, 36, 66, 129};
byte y[] = {0, 128, 64, 32, 31, 32, 64, 128};
byte z[] = {129, 131, 133, 137, 145, 161, 193, 129};

//byte *alphabet[] = {(byte*)a, (byte*)b, (byte*)c, (byte*)d, (byte*)e, (byte*)f, (byte*)g, (byte*)h, (byte*)i, (byte*)j, (byte*)k, (byte*)l,(byte*)m, (byte*)n, (byte*)o, (byte*)p, (byte*)q, (byte*)r, (byte*)s, (byte*)t, (byte*)u, (byte*)v, (byte*)w, (byte*)x, (byte*)y, (byte*)z};
byte *zoe[] = {(byte*)z, (byte*)o, (byte*)e};
byte *hello[] = {(byte*)h, (byte*)e, (byte*)l, (byte*)l, (byte*)o};
byte *world[] = {(byte*)w, (byte*)o, (byte*)r, (byte*)l, (byte*)d};

void text(){
  display_word(hello, 5);
  delay(200);

  display_word(world, 5);
  delay(200);

//  display_word(zoe, 3);
//  delay(200);
}

void display_word(byte* word_array[], int word_length){
  for (int l = 0; l < word_length; l++){
//    for(int z = 0; z < units; z++){
    for(int z = units_index; z >= 0; z--){
      for(int x = 0; x < units; x++){
        int c = get_column_id(x, z);
        columns[c].set_byte(word_array[l][x]);
      }

      update_matrix(75);
    }
  }
}
