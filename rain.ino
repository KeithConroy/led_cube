void initialize_rain(bool with_cloud) {
  for(int c = 0; c < sq(units); c++){
    columns[c].moving = false;
    columns[c].heading = -1;

    if (with_cloud){
      columns[c].y = units_index;
    } else {
      columns[c].y = units;
    }
  }
}

void rain(bool with_cloud){
  initialize_rain(with_cloud);

  unsigned long start = millis();

  while (millis() - start < 3000) {
    advance_rain(with_cloud);

    for(int c = 0; c < sq(units); c++){
      columns[c].set_y();
    }

    update_matrix(75);
  }
}

void advance_rain(bool with_cloud){
  for(int c = 0; c < sq(units); c++){
    if (columns[c].moving){
      if (columns[c].y == 0){
        if (with_cloud){
          columns[c].y = units_index;
        } else {
          columns[c].y = units;
        }
        columns[c].moving = false;
      } else {
        columns[c].move();
      }
    }
  }

  // select new falling
  int c = random(sq(units));
  if (!columns[c].moving){
    columns[c].moving = true;
  }
}

void rain_old(bool with_splash){
  unsigned long start = millis();

  while (millis() - start < 5000) {
    int c = random(sq(units));
    for (int y = units_index; y >= 0; y--){
      columns[c].set_bit(y);
      if (y == 0 && with_splash){
        splash(c);
      }
      update_matrix(50);
    }
  }
}

void splash(int c){
  columns[c+1].set_bit(0);
  columns[c-1].set_bit(0);

  columns[c-units].set_bit(0);
  columns[c+units].set_bit(0);
  update_matrix(50);

  columns[c+1].set_bit(1);
  columns[c-1].set_bit(1);

  columns[c-units].set_bit(1);
  columns[c+units].set_bit(1);
  update_matrix(50);
}
