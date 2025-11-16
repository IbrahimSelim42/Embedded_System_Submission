#include "Dio.h"

inline void Dio_SetRegisterBit(volatile unsigned char* Register, unsigned char Bit){
  *Register = *Register | (1 << Bit);
}

inline void Dio_ResetRegisterBit(volatile unsigned char* Register, unsigned char Bit){
  *Register = *Register & ~(1 << Bit);
}

inline void Dio_ToggleRegisterBit(volatile unsigned char* Register, unsigned char Bit){
  *Register = *Register ^ (1 << Bit);
}

inline unsigned char Dio_GetRegisterBit(volatile unsigned char* Register, unsigned char Bit){
  return (*Register >> Bit) & (unsigned char)0x01;
}

void Dio_SetPinDirection(volatile unsigned char* Register, unsigned char Pin, unsigned char Direction) {
    if (Direction == DIO_DIR_INPUT)
    {
      Dio_ResetRegisterBit(Register, Pin);
    } else{
      Dio_SetRegisterBit(Register, Pin);
    }
}

void Dio_SetPinState(volatile unsigned char* Register, unsigned char Pin, unsigned char State) {
    if (State == DIO_STATE_LOW)
    {
      Dio_ResetRegisterBit(Register, Pin);
    } else{
      Dio_SetRegisterBit(Register, Pin);
    }
}

unsigned char Dio_GetPinState(volatile unsigned char* Register, unsigned char Pin) {
  return Dio_GetRegisterBit(Register, Pin);
}