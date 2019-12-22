struct STATE {
  int column;
  int level;
  int heading;
  bool moving;
};
STATE states[sq(units)];

void initialize_states() {
  for(int c = 0; c < sq(units); c++){
    STATE state;
    state.column = c;
    state.moving = false;

    int r = random(2);
    if(r == 0){
      state.level = 0;
      state.heading = 1;
    }
    else {
      state.level = units - 1;
      state.heading = -1;
    }
    states[c] = state;
  }

  select_new_moving();
}

void ping_pong() {
  initialize_states();
  
  unsigned long start_1 = millis();
  while(millis() - start_1 < 4000) {
    
    for(int c = 0; c < sq(units); c++){
      STATE state = states[c];
      bitSet(columns[state.column], state.level);
    }
    
    update_matrix(50);
    
    move_led();
  }
}

void move_led() {
  for(int c = 0; c < sq(units); c++){
    if(states[c].moving){
      states[c].level = states[c].level + states[c].heading;
      bool top = states[c].level == units - 1 && states[c].heading == 1;
      bool bottom = states[c].level == 0 && states[c].heading == -1;
      
      if (top || bottom){
        states[c].heading = states[c].heading * -1;
        states[c].moving = false;
        select_new_moving();
      }
    }
  }
}

void select_new_moving() {
  int c = random(sq(units));
  states[c].moving = true;
}
