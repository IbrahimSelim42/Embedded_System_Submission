| **Author**              | `Ibrahim Selim Abomosalam , Mohamed Khaled Ghobashy` |
| **ID**                  | `202301024 , 202101628`                                       |
|:------------------------|:-----------------------------------------------------|
| **Status**              | `Approved`                          |
| **Version**             | `1.0`                                                |
| **Date**                | `17/11/2025`                                         |

##  1.Introduction
This document provides the specifics of design of the monitoring system based on ADC, which offers the mechanism of threshold assessment that could be configured using digital buttons, an analogual input source, and a visual LCD display. This system is based on an ATmega328P microcontroller, and it incorporates ADC conversion, UART messages, digital I/O processing and LCD display updates. This document details the software architecture, hardware interface and the functionality of the system.
###  1.1 Purpose
This document is aimed to explain the way in which this system reads an analog value using a potentiometer, and compares it to user-defined thresholds to show the resulting status (OK / NOK) on an LCD. The system supports dynamic configuration by giving the user the opportunity of adjusting the lower and higher limits using the special push buttons. UART communication is also utilized in order to record log button events and threshold changes.
##  1.2 Scope
It has a single design scope which consists of the ADC module, LCD user interface, two digital buttons which are used to adjust the limits and UART communication which is used to report on the status. The system will assist in the real-time analog sampling and threshold validation, as well as the limit change controlled by the user, offering an easy, yet useful monitoring platform.
##  2.Architectural Overview
These ADC based monitoring module defines the interface between the analog input, user controls and display interface. The ADC is constantly turning the signal of the potentiometer into a 10-bit digital representation. In the meantime, the digital I/O module receives button presses used to change threshold limits. The LCD is able to give real-time feedback whereas the UART communication sends system logs like button presses and mode changes.
##  2.1 Assumptions and constraints
The system is based on ATmega328P microcontroller with a frequency of 16 MHz. The ADC is programmed to take AVCC as reference voltage and has a prescaler of 128 which generates stable 10 bit readings. Limit adjustment is done through two physical push buttons and the analog voltage input is done through a potentiometer. LCD is running on 4-bit mode and the UART is set at 9600 bps. The microcontroller clock and the conversion rate of the ADCs are a limitation on timing of the display and update cycles.
##  3.Functional Description
The system has three key functions, which include analog sampling, limit adjustment and status evaluation. First, the ADC takes the analog signal on a potentiometer attached to channel 0 and converts it to a digital signal of between 0 and 1023. Secondly, there are 2 push buttons, which enable the user to increase or decrease the lower and upper limits; the combination of both buttons also switches an operating mode between increasing and decreasing. Further, every time a button is pressed or the mode is changed, UART messages are sent. Lastly, when the new ADC value has been compared against the two limits, the system will indicate OK when the value falls within the set range and NOK when the value does not fall within the set range.
## 4.Implementaion of the Module
First of all, the implementation is a combination of several integrated modules: Uart, Adc, Dio, Lcd and main application logic. To begin with, the UART module ( Uart.c / Uart.h) controls serial communication such as the initialisation, transmission of characters and structured output of messages. Secondly, it uses the ADC module (Adc.c / Adc.h) to set reference voltage, prescaler and analog sampling by channel. Thirdly, the DIO module (Dio.c / Dio.h) hides low-level pin direction, state control and register interactions. The LCD module (Lcd.c / Lcd.h) is also used to control all LCD processes in the 4-bit mode, which allows printing strings and cursor positioning. Lastly, the primary application brings together these components, the reading of ADC values, the working of button inputs, the updating of thresholds, the determination of system status and the production of LCD outputs.
## 5.Integration and Configuration
### 5.1 Static Files
| File name   | Contents                                       |
|-------------|------------------------------------------------|	
| Uart.c      | Initialization and handling of UART messaging  |
| Uart.h      | UART function prototypes                       |
| Adc.c       | ADC configuration and analog value reading     |
| Adc.h       | ADC function prototypes                        |
| Dio.c       | Digital I/O configuration and state control    |
| Dio.h       | Pin configuration and I/O definitions          |
| Lcd.c       | LCD initialization and 4-bit display control   |
| Lcd.        | LCD function prototypes                        |
| registers.h | Definitions and low-level hardware mappings    |
| main.c      | Core application logic integrating all modules |