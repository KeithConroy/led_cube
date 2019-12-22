int snake[sq(units)][3];
int snake_length = 0;
int target[3] = {0};

void init_snake(){
  snake_length = 0;

  for (int i = 0; i < 3; i++){
    snake[0][i] = 0;
  }
}

void init_target(){
  for (int i = 0; i < 3; i++){
    target[i] = random(units);
  }

  set_target();
}

void set_target(){
  int c = get_column_id(target[0], target[2]);
  columns[c].set_bit(target[1]);
}

void snake_game(){
  init_snake();
  init_target();

  unsigned long start = millis();

  int counter = -1;

  while(millis() - start < 25000) {
    if (counter >= sq(units)){
      counter = 0;
    } else {
      counter++;
    }

    for (int i = counter - snake_length; i <= counter; i++){
      int c = get_column_id(snake[i][0], snake[i][2]);
      columns[c].set_bit(snake[i][1]);
    }
    set_target();

    update_matrix(100);
    advance_snake(counter);
  }
}

void advance_snake(int counter){
  int x = snake[counter][0];
  int y = snake[counter][1];
  int z = snake[counter][2];

  if (x < target[0]){
    x++;
  } else if (x > target[0]) {
    x--;
  } else if (y < target[1]){
    y++;
  } else if (y > target[1]) {
    y--;
  } else if (z < target[2]){
    z++;
  } else if (z > target[2]) {
    z--;
  } else {
    init_target();
    snake_length++;
  }

  // set next
  int next_id = counter + 1;
  snake[next_id][0] = x;
  snake[next_id][1] = y;
  snake[next_id][2] = z;

//  bool x_match = x == target[0];
//  bool y_match = y == target[1];
//  bool z_match = z == target[2];
//
//  if (x_match && x_match && x_match){
//    init_target();
//    snake_length++;
//  }

  // clear tail
  for (int i = 0; i < 3; i++){
    snake[counter - snake_length][i] = units;
  }
}
