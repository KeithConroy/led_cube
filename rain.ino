struct RAIN {
  int column;
  int level;
  bool falling;
};

RAIN rain_drops[sq(units)];

void initialize_rain(bool with_cloud) {
  for(int c = 0; c < sq(units); c++){
    RAIN rain_drop;
    rain_drop.column = c;
    rain_drop.falling = false;
    
    if (with_cloud){
      rain_drop.level = units_index;
    } else {
      rain_drop.level = units;
    }

    rain_drops[c] = rain_drop;
  }
}

void rain(bool with_cloud){
  initialize_rain(with_cloud);
  
  unsigned long start = millis();
  
  while (millis() - start < 3000) {
    advance_rain(with_cloud);
    
    for(int c = 0; c < sq(units); c++){
      bitSet(columns[rain_drops[c].column], rain_drops[c].level);
    }
    
    update_matrix(75);
  }
}

void advance_rain(bool with_cloud){
  for(int c = 0; c < sq(units); c++){
    if (rain_drops[c].falling){
          
      if (rain_drops[c].level == 0){
        if (with_cloud){
          rain_drops[c].level = units_index;
        } else {
          rain_drops[c].level = units;
        }
        rain_drops[c].falling = false;
      } else {
        rain_drops[c].level--;
      }
    }
  }
  // select new falling
  int c = random(sq(units));
  if (!rain_drops[c].falling){
    rain_drops[c].falling = true;
  }
}

void rain_old(bool with_splash){
  unsigned long start = millis();
  
  while (millis() - start < 5000) {
    int c = random(sq(units));
    for (int y = units_index; y >= 0; y--){
      bitSet(columns[c], y);
      if (y == 0 && with_splash){
        splash(c);
      }
      update_matrix(50);
    }
  }
}

void splash(int c){
  bitSet(columns[c+1], 0);
  bitSet(columns[c-1], 0);
  
  bitSet(columns[c-units], 0);
  bitSet(columns[c+units], 0);
  update_matrix(50);
  
  bitSet(columns[c+1], 1);
  bitSet(columns[c-1], 1);
  
  bitSet(columns[c-units], 1);
  bitSet(columns[c+units], 1);
  update_matrix(50);
}
