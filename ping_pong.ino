void initialize_ping_pong() {
  for(int c = 0; c < sq(units); c++){
    columns[c].moving = false;

    if(random(2) == 0){
      columns[c].y = 0;
      columns[c].heading = 1;
    }
    else {
      columns[c].y = units_index;
      columns[c].heading = -1;
    }
  }

  select_new_moving();
}

void ping_pong() {
  initialize_ping_pong();

  unsigned long start = millis();

  while(millis() - start < 4000) {

    for(int c = 0; c < sq(units); c++){
      columns[c].set_y();
    }

    update_matrix(50);

    move_led();
  }
}

void move_led() {
  for(int c = 0; c < sq(units); c++){
    if(columns[c].moving){
      columns[c].move();
      bool top = columns[c].y == units - 1 && columns[c].heading == 1;
      bool bottom = columns[c].y == 0 && columns[c].heading == -1;

      if (top || bottom){
        columns[c].heading = columns[c].heading * -1;
        columns[c].moving = false;
        select_new_moving();
      }
    }
  }
}

void select_new_moving() {
  int c = random(sq(units));
  columns[c].moving = true;
}
