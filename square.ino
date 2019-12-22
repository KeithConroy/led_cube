const long squareInterval = 75;

void square(){
  square_border('z');
//  square_border('y');
//  square_border('x');
}

void square_border(char axis) {
  // forward
  for (int a = 0; a < units; a++) {
    square_helper(axis, a);
  }
  
  // bounce back
  for (int a = units - 2; a > 0; a--) {
    square_helper(axis, a);
  }
  
  all_off();
}

void square_helper(char axis, int a){
  int offset = a * units;
  
  for (int i = 0; i < units; i++) {
    int col = i + offset;
    if (i == 0 || i == units_index){
      columns[col] = 255;
    } else {
      columns[col] = 129;
    }
  }
  
  update_matrix(squareInterval);
  
  for (int i = 0; i < units; i++) {
    int col = i + offset;
    columns[col] = 0;
  }
}

//void square_border(char axis) {
//  // forward
//  for (int a = 0; a < units; a++) {
//    square_helper(axis, a);
//  }
//  
//  // bounce back
//  for (int a = (units - 2); a >= 0; a--) {
//    square_helper(axis, a);
//  }
//  all_off();
//}

//void square_helper(char axis, int a){
//  unsigned long start = millis();
//  
//  while(millis() - start < squareInterval) {
//    for (int b = 0; b < units; b++)
//    for (int c = 0; c < units; c++)
//    
//    if(part_of_square(b, c)){
//      switch(axis) {
//        case 'z':
//          pulse_single_led(c, b, a, 2);
//          break;
//        case 'y':
//          pulse_single_led(c, a, b, 2);
//          break;
//        case 'x':
//          pulse_single_led(a, b, c, 2);
//          break;
//      }
//    }
//  }
//}

bool part_of_square(int b, int c){
  return !(not_part_of_square(b) && not_part_of_square(c));
}

bool not_part_of_square(int i){
  return i > 0 && i < (units - 1);
}

void cube(){
  cube_directional(0,0,0);
//  cube_directional(units_index,0,0);
//  cube_directional(units_index,0,units_index);
//  cube_directional(0,0,units_index);
}

void cube_directional(int x, int y, int z){
  // shrink
  for (int cube_units = units; cube_units >= 2; cube_units--){
    cube_helper(cube_units, x, y, z);
  }
  // expand
  for (int cube_units = 3; cube_units <= units; cube_units++) {
    cube_helper(cube_units, x, y, z);
  }
}

void cube_helper(int cube_units, int a, int b, int c){
  int x,z = 0;
  int less_one = cube_units - 1;
  
  for(x = 0; x < cube_units; x = x + less_one){
     for(z = 0; z < cube_units; z = z + less_one){
        for (int i = 0; i < cube_units; i++){
          int col_id = get_column_id(x, z);
           bitSet(columns[col_id], i);
        }

        for(int y = 0; y < cube_units; y = y + less_one){
          for(int zz = z + 1; zz < less_one; zz++){
            int col_id = get_column_id(x, zz);
            bitSet(columns[col_id], y);
          }
          
          for(int xx = x + 1; xx < less_one; xx++){
            int col_id = get_column_id(xx, z);
            bitSet(columns[col_id], y);
          }
        }
     }
  }
  
  update_matrix(100);
}
//
//void cube_helper_old(int cube_units, int a, int b, int c) {
//  unsigned long start = millis();
//  
//  while(millis() - start < 150) {
//    if(a == 0 && b == 0 && c == 0){
//      int x,z;
//      int less_one = cube_units - 1;
//      
//      for(x = 0; x < cube_units; x = x + less_one){
//         for(z = 0; z < cube_units; z = z + less_one){
//            pulse_single_column(x, z, cube_units, 1);
//  
//            for(int y = 0; y < cube_units; y = y + less_one){
//              for(int zz = z + 1; zz < less_one; zz++)
//              pulse_single_led(x,y,zz,1);
//  
//              for(int xx = x + 1; xx < less_one; xx++)
//              pulse_single_led(xx,y,z,1);
//            }
//         }
//      }
//    }
//    else if(a == units_index && b == 0 && c == 0){
//      int x,z;
//      int less_one = cube_units - 1;
//      for(x = units_index; x >= units - cube_units; x = x - less_one){
//         for(z = 0; z < cube_units; z = z + less_one){
//            pulse_single_column(x, z, cube_units, 1);
//  
//            for(int y = 0; y < cube_units; y = y + less_one){
//              for(int zz = z + 1; zz < less_one; zz++)
//              pulse_single_led(x,y,zz,1);
//  
//              for(int xx = x + 1; xx < less_one; xx++)
//              pulse_single_led(xx,y,z,1);
//            }
//         }
//      }
//    }
//    else if(a == units_index && b == 0 && c == units_index){
//      int x,z;
//      int less_one = cube_units - 1;
//      for(x = units_index; x >= units - cube_units; x = x - less_one){
//         for(z = units_index; z >= units - cube_units; z = z - less_one){
//            pulse_single_column(x, z, cube_units, 1);
//  
//            for(int y = 0; y < cube_units; y = y + less_one){
//              for(int zz = z + 1; zz < less_one; zz++)
//              pulse_single_led(x,y,zz,1);
//  
//              for(int xx = x + 1; xx < less_one; xx++)
//              pulse_single_led(xx,y,z,1);
//            }
//         }
//      }
//    }
//    else if(a == 0 && b == 0 && c == units_index){
//      int x,z;
//      int less_one = cube_units - 1;
//      for(x = 0; x < cube_units; x = x + less_one){
//         for(z = units_index; z >= units - cube_units; z = z - less_one){
//            pulse_single_column(x, z, cube_units, 1);
//  
//            for(int y = 0; y < cube_units; y = y + less_one){
//              for(int zz = z + 1; zz < less_one; zz++)
//              pulse_single_led(x,y,zz,1);
//  
//              for(int xx = x + 1; xx < less_one; xx++)
//              pulse_single_led(xx,y,z,1);
//            }
//         }
//      }
//    }
//  } 
//}
//
//void cube_helper_2(int cube_units, int a, int b, int c) {
//  unsigned long start = millis();
//  while(millis() - start < 300) {
//    int x,z;
//    int less_one = cube_units - 1;
//
//    for(x = a; condish(a, x, cube_units); x = stepper(a,x,less_one)){
//      for(z = b; condish(b, z, cube_units); z = stepper(b,z,less_one)){
//          pulse_single_column(x, z, cube_units, 1);
//
////          for(int y = c; condish(c, y, cube_units); y = stepper(c,y,less_one)){
//          for(int y = 0; y < cube_units; y = y + less_one){
//            for(int zz = z + 1; zz < less_one; zz++)
//            pulse_single_led(x,y,zz,1);
//
//            for(int xx = x + 1; xx < less_one; xx++)
//            pulse_single_led(xx,y,z,1);
//          }
//       }
//    }
//  }
//}
//int stepper(int a, int x, int less_one){
//  if(a > 0){
//    return x - less_one;
//  }
//  else {
//    return x + less_one;
//  }
//}
//bool condish(int start, int x, int cube_units){
//  if(start > 0){
//    return x >= units - cube_units;
//  }
//  else {
//    return x < cube_units;
//  }
//}
