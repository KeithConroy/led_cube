const long faderInterval = 75;

void fadder_rows() {
  for (int z = 0; z < units; z++){
    single_row(z, 255);
    update_matrix_no_clear(faderInterval);
  }
  for (int z = 0; z < units-1; z++){
    single_row(z, 0);
    update_matrix_no_clear(faderInterval);
  }
  
  for (int z = units-1; z >= 0; z--){
    single_row(z, 255);
    update_matrix_no_clear(faderInterval);
  }
  for (int z = units; z > 0; z--){
    single_row(z, 0);
    update_matrix_no_clear(faderInterval);
  }

  for (int z = 0; z < units; z++){
    single_row(z, 255);
    update_matrix_no_clear(faderInterval);
  }
}

void fadder_levels() {
  for (int y = 0; y < units; y++){
    single_level(y, 1);
    update_matrix_no_clear(faderInterval);
  }
  for (int y = 0; y < units-1; y++){
    single_level(y, 0);
    update_matrix_no_clear(faderInterval);
  }

  for (int y = units-1; y >= 0; y--){
    single_level(y, 1);
    update_matrix_no_clear(faderInterval);
  }
  for (int y = units; y > 0; y--){
    single_level(y, 0);
    update_matrix_no_clear(faderInterval);
  }

  for (int y = 0; y < units; y++){
    single_level(y, 1);
    update_matrix_no_clear(faderInterval);
  }
}

void single_level(int y, int value) {
  for(int c = 0; c < sq(units); c++){
    bitWrite(columns[c], y, value);
  }
}

void single_row(int z, int value){
  for(int x = 0; x < units; x++){
    int c = get_column_id(x, z);
    columns[c] = value;
  }
}
