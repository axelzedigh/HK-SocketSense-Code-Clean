#include <stdio.h>
#include <stdlib.h>
#include "SerialTransfer.h"

struct STRUCT {
  int16_t len;
  int16_t len_sign;
  int16_t m1;
  int16_t m1_sign;
  int16_t m2;
  int16_t m2_sign;
  int16_t m3;
  int16_t m3_sign;
  int16_t m4;
  int16_t m4_sign;
  int16_t m5;
  int16_t m5_sign;
  int16_t m6;
  int16_t m6_sign;
} motorStruct;
SerialTransfer myTransfer;
bool blink = 1;

int **piBuffer = NULL; //pointer to pointer
int nRow = 0; //variable store number of Row
int nColumn = 6; //variable store number of Row
int iRow = 0; //Variable for looping Row
int iCol = 0; //Variable for looping column
int rxRow = 0;

bool matrix_downloaded = false;

int arr[6];
int irr[] = {1,2,3,4,5,6,7,8,9,10,11,12,13};

void setup() {
  Serial.begin(115200);
  myTransfer.begin(Serial);
  pinMode(LED_BUILTIN, OUTPUT);

  while (matrix_downloaded == false) {
    if (myTransfer.available()) {
      int16_t recSize = 0;
      recSize = myTransfer.rxObj(motorStruct, recSize);

      if (rxRow == 0) {
        digitalWrite(LED_BUILTIN, HIGH);
        nRow = motorStruct.len;
        piBuffer = (int **)malloc(nRow * sizeof(int*));

        //Allocate memory for column
        for (iRow = 0 ; iRow < nRow ; iRow++) {
          piBuffer[iRow] = (int *)malloc(nColumn * sizeof(int));
          //Check memory validity
          if (piBuffer[iRow] == NULL) {
            freeAllocatedMemory(piBuffer, iRow);
          }
        }

        piBuffer[rxRow][0] = (int)motorStruct.m1;
        piBuffer[rxRow][1] = (int)motorStruct.m2;
        piBuffer[rxRow][2] = (int)motorStruct.m3;
        piBuffer[rxRow][3] = (int)motorStruct.m4;
        piBuffer[rxRow][4] = (int)motorStruct.m5;
        piBuffer[rxRow][5] = (int)motorStruct.m6;
        rxRow++;
      } else if (rxRow > 0) {
        piBuffer[rxRow][0] = (int)motorStruct.m1;
        piBuffer[rxRow][1] = (int)motorStruct.m2;
        piBuffer[rxRow][2] = (int)motorStruct.m3;
        piBuffer[rxRow][3] = (int)motorStruct.m4;
        piBuffer[rxRow][4] = (int)motorStruct.m5;
        piBuffer[rxRow][5] = (int)motorStruct.m6;
        rxRow++;
        blink = !blink;
        digitalWrite(LED_BUILTIN, blink);
        } 
    }

    // Run only if all rows have been sent
    if (rxRow == nRow-1) {
      digitalWrite(LED_BUILTIN, LOW);
      //send_all_received_refs();
      rxRow = 0;
      matrix_downloaded = true;

      uint16_t sendSize = 0;
      sendSize = myTransfer.txObj(irr, sendSize);
      myTransfer.sendData(sendSize);
    }
  }
}

void loop() {
//  // Store received rows in a matrix
//  if (myTransfer.available()) {
//    int16_t recSize = 0;
//    recSize = myTransfer.rxObj(motorStruct, recSize);
//
//    if (rxRow == 0) {
//      digitalWrite(LED_BUILTIN, HIGH);
//      nRow = motorStruct.len;
//      piBuffer = (int **)malloc(nRow * sizeof(int*));
//
//      //Allocate memory for column
//      for (iRow = 0 ; iRow < nRow ; iRow++) {
//        piBuffer[iRow] = (int *)malloc(nColumn * sizeof(int));
//
//        //Check memory validity
//        if (piBuffer[iRow] == NULL) {
//          freeAllocatedMemory(piBuffer, iRow);
//        }
//      }
//
//      piBuffer[rxRow][0] = (int)motorStruct.m1;
//      piBuffer[rxRow][1] = (int)motorStruct.m2;
//      piBuffer[rxRow][2] = (int)motorStruct.m3;
//      piBuffer[rxRow][3] = (int)motorStruct.m4;
//      piBuffer[rxRow][4] = (int)motorStruct.m5;
//      piBuffer[rxRow][5] = (int)motorStruct.m6;
//      rxRow++;
//    } else if (rxRow > 0) {
//      piBuffer[rxRow][0] = (int)motorStruct.m1;
//      piBuffer[rxRow][1] = (int)motorStruct.m2;
//      piBuffer[rxRow][2] = (int)motorStruct.m3;
//      piBuffer[rxRow][3] = (int)motorStruct.m4;
//      piBuffer[rxRow][4] = (int)motorStruct.m5;
//      piBuffer[rxRow][5] = (int)motorStruct.m6;
//      rxRow++;
//      blink = !blink;
//      digitalWrite(LED_BUILTIN, blink);
//    }
//  }
//
//  // Run only if all rows have been sent
//  if (rxRow == nRow-1) {
//    digitalWrite(LED_BUILTIN, LOW);
//    send_all_received_refs();
//    rxRow = 0;
//  }
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

void send_all_received_refs() {
  for (int i = 0; i < nRow; i++) {
    for (int k = 0; k < 6; k++) {
      arr[k] = piBuffer[i][k];
    }
    myTransfer.packet.txBuff[i] = arr[0];
    uint16_t sendSize = 0;
    sendSize = myTransfer.txObj(arr, sendSize);
    myTransfer.sendData(myTransfer.bytesRead);
    delay(500);
    blink = !blink;
    digitalWrite(LED_BUILTIN, blink);

    // Clean up
    //for (iRow =0 ; iRow < nRow ; iRow++) {
    //      freeAllocatedMemory(piBuffer,iRow);
    //}
  }
}
