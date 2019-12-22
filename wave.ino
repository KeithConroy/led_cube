struct WaveState {
  int y;
  int heading;
};

WaveState waveStates[units];

void initWave(){
  for (int x = 0; x < units; x++){
    WaveState state = {0 - x, 1};
    waveStates[x] = state;
  }
}

void wave(){
//  make_wave(true, false);
//  make_wave(false, false);
  make_wave(true, true);
  make_wave(false, true);
}

void make_wave(bool single, bool flat){
  initWave();

  unsigned long start = millis();
  int d = 3000;

  if (single){
    d = 2000;
  }

  while(millis() - start < d) {
    wave_helper(flat);
    advance_wave(single);
  }
}

void advance_wave(bool single){
  for (int x = 0; x < units; x++){
    waveStates[x].y = waveStates[x].y + waveStates[x].heading;

    bool top = waveStates[x].y == units - 1 && waveStates[x].heading == 1;
    bool bottom = waveStates[x].y == 0 && waveStates[x].heading == -1;

    if (single){
      bottom = false;
    }

    if (top || bottom){
      waveStates[x].heading = waveStates[x].heading * -1;
    }
  }
}

void wave_helper(bool flat){
  for (int x = 0; x < units; x++){
    for (int z = 0; z < units; z++){
      int c = get_column_id(x, z);

      if(waveStates[x].y >= 0){
        if (flat){
          columns[c].set_bit(waveStates[x].y);
        } else {
          for (int y = 0; y <= waveStates[x].y; y++){
            columns[c].set_bit(y);
          }
        }
      } else {
        columns[c].set_bit(0);
      }
    }
  }
  update_matrix(50);
}
