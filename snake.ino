int snake[sq(units)][3];
int snake_length = 0;
int food[3] = {0};

void init_snake(){
  snake_length = 0;

  for (int i = 0; i < 3; i++){
    snake[0][i] = 0;
  }
}

void init_food(){
  for (int i = 0; i < 3; i++){
    food[i] = random(units);
  }

  set_food();
}

void set_food(){
  int c = get_column_id(food[0], food[2]);
  columns[c].set_bit(food[1]);
}

void snake_game(){
  init_snake();
  init_food();

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
    set_food();

    update_matrix(100);
    advance_snake(counter);
  }
}

void advance_snake(int counter){
  int x = snake[counter][0];
  int y = snake[counter][1];
  int z = snake[counter][2];

  if (x < food[0]){
    x++;
  } else if (x > food[0]) {
    x--;
  } else if (y < food[1]){
    y++;
  } else if (y > food[1]) {
    y--;
  } else if (z < food[2]){
    z++;
  } else if (z > food[2]) {
    z--;
  } else {
    init_food();
    snake_length++;
  }

  // set next
  int next_id = counter + 1;
  snake[next_id][0] = x;
  snake[next_id][1] = y;
  snake[next_id][2] = z;

//  bool x_match = x == food[0];
//  bool y_match = y == food[1];
//  bool z_match = z == food[2];
//
//  if (x_match && x_match && x_match){
//    init_food();
//    snake_length++;
//  }

  // clear tail
  for (int i = 0; i < 3; i++){
    snake[counter - snake_length][i] = units;
  }
}
