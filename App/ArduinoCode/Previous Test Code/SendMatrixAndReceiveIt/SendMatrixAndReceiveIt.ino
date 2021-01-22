//int **piBuffer = NULL; //pointer to pointer
int nRow = 0; //variable store number of Row
int nColumn = 6; //variable store number of Row
int iRow = 0; //Variable for looping Row
int iCol = 0; //Variable for looping column
int rxRow = 0;
//int sensor_arr[6];
int stop_program = false;
int matrix_len;
int16_t ref1;
int16_t ref2;
int16_t ref3;
int16_t ref4;
int16_t ref5;
int16_t ref6;
char refs[40];

char stop_program_char[1];
char matrix_len_char[5];
char ref1_char[5];
char ref2_char[5];
char ref3_char[5];
char ref4_char[5];
char ref5_char[5];
char ref6_char[5];

char sens1_char[5];
char sens2_char[5];
char sens3_char[5];
char sens4_char[5];
char sens5_char[5];
char sens6_char[5];
char comma[1] = {','};
int c_len = strlen(comma);

char sensor_arr[40];

int piBuffer[100][6];

void setup() {
  Serial.begin(115200);
}

void loop() {
  // Store received rows in a matrix
  if (Serial.available()) {
    Serial.readString().toCharArray(refs, 40);
    parseData();
    piBuffer[rxRow][0] = ref1;
    piBuffer[rxRow][1] = ref2;
    piBuffer[rxRow][2] = ref3;
    piBuffer[rxRow][3] = ref4;
    piBuffer[rxRow][4] = ref5;
    piBuffer[rxRow][5] = ref6;
    rxRow++;

//    strcat(sensor_arr, ref1_char);
//    strcat(sensor_arr, comma);
//    strcat(sensor_arr, ref2_char);
//    strcat(sensor_arr, comma);
//    strcat(sensor_arr, ref3_char);
//    strcat(sensor_arr, comma);
//    strcat(sensor_arr, ref4_char);
//    strcat(sensor_arr, comma);
//    strcat(sensor_arr, ref5_char);
//    strcat(sensor_arr, comma);
//    strcat(sensor_arr, ref6_char);
//    strcat(sensor_arr, comma);
//    if (ref1 > 0) {
//      Serial.print(sensor_arr);
//    }
//    
//    sensor_arr[0] = '\0';
    

//    if (piBuffer == NULL) {
//      piBuffer = (int **)malloc(matrix_len * sizeof(int*));
//
//      //Allocate memory for column
//      for (iRow = 0 ; iRow < matrix_len ; iRow++) {
//        piBuffer[iRow] = (int *)malloc(nColumn * sizeof(int));
//        
//        //Check memory validity
//        if (piBuffer[iRow] == NULL) {
//          freeAllocatedMemory(piBuffer, iRow);
//        }
//      }
//
//      piBuffer[0][0] = ref1;
//      piBuffer[0][1] = ref2;
//      piBuffer[0][2] = ref3;
//      piBuffer[0][3] = ref4;
//      piBuffer[0][4] = ref5;
//      piBuffer[0][5] = ref6;
//      rxRow++;
    }
  }

  // Run only if all rows have been sent
  if (rxRow == (matrix_len-1)) {
    for (int i = 0; i < (nRow); i++) {
    itoa(piBuffer[i][0], sens1_char, 10);
//    itoa(piBuffer[i][1], sens2_char, 10);
//    itoa(piBuffer[i][2], sens3_char, 10);
//    itoa(piBuffer[i][3], sens4_char, 10);
//    itoa(piBuffer[i][4], sens5_char, 10);
//    itoa(piBuffer[i][5], sens6_char, 10);
    strcat(sensor_arr, ref1_char);
//    strcat(sensor_arr, comma);
//    strcat(sensor_arr, ref2_char);
//    strcat(sensor_arr, comma);
//    strcat(sensor_arr, ref3_char);
//    strcat(sensor_arr, comma);
//    strcat(sensor_arr, ref4_char);
//    strcat(sensor_arr, comma);
//    strcat(sensor_arr, ref5_char);
//    strcat(sensor_arr, comma);
//    strcat(sensor_arr, ref6_char);
//    strcat(sensor_arr, comma);
//    Serial.print(sensor_arr);
    sensor_arr[0] = '\0';
    
    delay(200);
    }
  
    //rxRow = 0;
  }
  Serial.println(rxRow);
}

void send_all_received_refs() {
  
}

void serial_memory_stor() {
  
}

//Free Allocated memory
void freeAllocatedMemory(int **piBuffer, int nRow)
{
  int iRow = 0;
  for (iRow = 0; iRow < nRow; iRow++)
  {
    free(piBuffer[iRow]); // free allocated memory
  }
  free(piBuffer);
}

void parseData() {
  char * strtokIndx;

  strtokIndx = strtok(refs,",");
  strcpy(stop_program_char, strtokIndx);
  stop_program = atoi(stop_program_char);
  
  strtokIndx = strtok(NULL,",");
  strcpy(matrix_len_char, strtokIndx);
  matrix_len = atoi(matrix_len_char);

  strtokIndx = strtok(NULL,",");
  strcpy(ref1_char, strtokIndx);
  ref1 = atoi(ref1_char);

  strtokIndx = strtok(NULL,",");
  strcpy(ref2_char, strtokIndx);
  ref2 = atoi(ref2_char);
  
  strtokIndx = strtok(NULL,",");
  strcpy(ref3_char, strtokIndx);
  ref3 = atoi(ref3_char);

  strtokIndx = strtok(NULL,",");
  strcpy(ref4_char, strtokIndx);
  ref4 = atoi(ref4_char);

  strtokIndx = strtok(NULL,",");
  strcpy(ref5_char, strtokIndx);
  ref5 = atoi(ref5_char);

  strtokIndx = strtok(NULL,",");
  strcpy(ref6_char, strtokIndx);
  ref6 = atoi(ref6_char);
}
