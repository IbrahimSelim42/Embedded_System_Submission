

#define PORT_B          (volatile uint8_t *)(0x25)
#define DDR_B           (volatile uint8_t *)(0x24)
#define PIN_B           (volatile uint8_t *)(0x23)
#define ADC_ADMUX       (volatile uint8_t *)(0x7C)

inline void Register_SetBit(volatile unsigned char* Register, unsigned char Bit){
  *Register = *Register | (1 << Bit);
}

inline void Register_ResetBit(volatile unsigned char* Register, unsigned char Bit){
  *Register = *Register & ~(1 << Bit);
}

inline void Register_ToggleBit(volatile unsigned char* Register, unsigned char Bit){
  *Register = *Register ^ (1 << Bit);
}

inline unsigned char Register_GetBit(volatile unsigned char* Register, unsigned char Bit){
  return (*Register >> Bit) & (unsigned char)0x01;
}
