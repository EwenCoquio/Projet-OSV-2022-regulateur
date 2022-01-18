#ifndef MESSAGERIE_H
#define MESSAGERIE_H
//file:///home/istic2/Documents/version_modifiee_OSV/2020-2021-Livrable_avant_Projet_OSV/BSM/BSM_OK/test_BSM_V1_OK/osv_types.h

#include "osv_types.h"

/**
 * @version 0.8
 */

//--------------------------------------------------------------------------
//
// CAN Bus 1
//
// Frame ID definition (priority order)
// Frame size definition
// Get/Set functions for command, data and state frames
//
//--------------------------------------------------------------------------

#define CAN1_FORMAT 0 // format frame CAN (0 standar, 1 extended)

#define CAN1_SIZE_FRAME 8 // size of frame when encryption mode ON

//TODO: ordre étrange ???

//BC
//Il faut pas le supprimer celui là ?
#define CAN1_ID_CMD_BC_BRAKE                                0x01
//BF
#define CAN1_ID_DATA_BF                                     CAN1_ID_CMD_BC_BRAKE+1      //0x05  in messagerie xls
//BA
#define CAN1_ID_DATA_BA                                     CAN1_ID_DATA_BF+1           //0x06  in messagerie xls
//BF
#define CAN1_ID_STATE_BF                                    CAN1_ID_DATA_BA+1           //0x0E  in messagerie xls
//BA
#define CAN1_ID_STATE_BA                                    CAN1_ID_STATE_BF+1          //0x0F  in messagerie xls
//BC
#define CAN1_ID_CMD_BC_PERIODIC                             CAN1_ID_STATE_BA+1          //0x11  in messagerie xls
//BSI
//We don't want event in the BSI
//#define CAN1_ID_CMD_BSI_EVENT                               CAN1_ID_CMD_BC_PERIODIC+1   //0x1A  in messagerie xls
//BSM
#define CAN1_ID_DATA_BSM                                    CAN1_ID_CMD_BC_PERIODIC+1     //0x200 in messagerie xls
// Use to send encryption mode
//STATE_BSM is deleted since it only exists because of encryption
//#define CAN1_ID_STATE_BSM                                   CAN1_ID_DATA_BSM+1

//Total number of frames in CAN1
#define CAN1_FRAME_NUMBER                                   CAN1_ID_DATA_BSM +1
//--------------------------------------------------------------------------
// BC 
//--------------------------------------------------------------------------
/*
//CMD BRAKE used by BSI and BA
//Period: event
#define CAN1_SIZE_CMD_BC_BRAKE                              1

//value: 0/1 (bit 0.0)
#define CAN1_GET_CMD_BC_BRAKE(t)                          ((u8)bitRead(t[0], 0))
#define CAN1_SET_CMD_BC_BRAKE(t,val)                        bitWrite(t[0], 0,val);
*/
//----------------

//CMD used by BSI, BF, BA and BSM??
//Period: 100ms
#define CAN1_SIZE_CMD_BC_PERIODIC                           4

//value: 0/1 (bit 0.0)
#define CAN1_GET_CMD_BC_LIGHT_MODE_AUTO(t)                  ((u8)bitRead(t[0], 0))
#define CAN1_SET_CMD_BC_LIGHT_MODE_AUTO(t,val)              bitWrite(t[0], 0,val);

//value: 0/1 (bit 0.1)
#define CAN1_GET_CMD_BC_BLINKER_LEFT(t)                     ((u8)bitRead(t[0], 1))
#define CAN1_SET_CMD_BC_BLINKER_LEFT(t,val)                 bitWrite(t[0], 1, val);

//value: 0/1 (bit 0.2)
#define CAN1_GET_CMD_BC_BLINKER_RIGHT(t)                    ((u8)bitRead(t[0], 2))
#define CAN1_SET_CMD_BC_BLINKER_RIGHT(t,val)                bitWrite(t[0], 2, val);

//value: 0/1 (bit 0.3)
#define CAN1_GET_CMD_BC_LIGHT(t)                            ((u8)bitRead(t[0], 3))
#define CAN1_SET_CMD_BC_LIGHT(t,val)                        bitWrite(t[0], 3, val);

//value: 0/1 (bit 0.4)
#define CAN1_GET_CMD_BC_INTER_FOOT_HAND(t)                  ((u8)bitRead(t[0], 4))
#define CAN1_SET_CMD_BC_INTER_FOOT_HAND(t,val)              bitWrite(t[0], 4, val);

//value: 0/1 (bit 0.5)
#define CAN1_GET_CMD_BC_REVERSE_LIGHT(t)                    ((u8)bitRead(t[0], 5))
#define CAN1_SET_CMD_BC_REVERSE_LIGHT(t,val)                bitWrite(t[0], 5, val);

/* //value: 0/1 (bit 0.6)
#define CAN1_GET_CMD_BC_ENCRYPTION_MODE(t)                   ((u8)bitRead(t[0], 6))
#define CAN1_SET_CMD_BC_ENCRYPTION_MODE(t,val)		bitWrite(t[0], 6, val); */

//value -240..240 in degree (bit 1.0 .. 2.7)
//TODO: CMD or DATA??? consistency issue???
#define CAN1_GET_CMD_BC_STEERING_WHEEL_ANGLE(t)             ((s16)(t[2]<<8 | t[1] ))                                // NB : pb d'envoie 2 octets -> passage en 1 octet
#define CAN1_SET_CMD_BC_STEERING_WHEEL_ANGLE(t,val)         t[1]=(val & 0x00ff);t[2]= ((val & 0xff00) >>8);

//value 0..255 (bit 3.0 .. 3.7)
//TODO value range not defined in messagerie xls
#define CAN1_GET_CMD_BC_ACCELARATION(t)                     ((u8)t[3])
#define CAN1_SET_CMD_BC_ACCELARATION(t,val)                 t[3]=val;


//--------------------------------------------------------------------------
// BF
//--------------------------------------------------------------------------

//DATA used by BSI
//Period: 100ms
#define CAN1_SIZE_DATA_BF                                   4

//value 0..100 in % (bit 0.0 .. 0.7)
//Rq: can be compressed in 7 bits if needed
#define CAN1_GET_DATA_BF_LIGHT_SENSOR(t)                    ((u8)t[0])
#define CAN1_SET_DATA_BF_LIGHT_SENSOR(t,val)                t[0]=val;

//value 0..255 in cm (bit 1.0 .. 1.7)
#define CAN1_GET_DATA_BF_ULTRASONIC_LEFT(t)                 ((u8)t[1])
#define CAN1_SET_DATA_BF_ULTRASONIC_LEFT(t,val)             t[1]=val;

//value 0..255 in cm (bit 2.0 .. 2.7)
#define CAN1_GET_DATA_BF_ULTRASONIC_CENTER(t)               ((u8)t[2])
#define CAN1_SET_DATA_BF_ULTRASONIC_CENTER(t,val)           t[2]=val;

//value 0..255 in cm (bit 3.0 .. 3.7)
#define CAN1_GET_DATA_BF_ULTRASONIC_RIGHT(t)                ((u8)t[3])
#define CAN1_SET_DATA_BF_ULTRASONIC_RIGHT(t,val)            t[3]=val;

//----------------

//STATE used by BSI
//Period: 200ms
#define CAN1_SIZE_STATE_BF                                  1

//value: 0/1 (bit 0.0)
#define CAN1_GET_STATE_BF_LIGHT(t)                          ((u8)bitRead(t[0], 0))
#define CAN1_SET_STATE_BF_LIGHT(t,val)                      bitWrite(t[0], 0, val);

//value: 0/1 (bit 0.1)
#define CAN1_GET_STATE_BF_BLINKER_LEFT(t)                   ((u8)bitRead(t[0], 1))
#define CAN1_SET_STATE_BF_BLINKER_LEFT(t,val)               bitWrite(t[0], 1, val);

//value: 0/1 (bit 0.2)
#define CAN1_GET_STATE_BF_BLINKER_RIGHT(t)                  ((u8)bitRead(t[0], 2))
#define CAN1_SET_STATE_BF_BLINKER_RIGHT(t,val)              bitWrite(t[0], 2, val);

/* //value: 0/1 (bit 0.3)
#define CAN1_GET_STATE_BF_ENCRYPTION_MODE(t)                  ((u8)bitRead(t[0], 3))
#define CAN1_SET_STATE_BF_ENCRYPTION_MODE(t,val)              bitWrite(t[0], 3, val);
 */
//--------------------------------------------------------------------------
// BA
//--------------------------------------------------------------------------

//DATA used by BSI
//Period: 100ms
#define CAN1_SIZE_DATA_BA                                   3

//value 0..255 in cm (bit 0.0 .. 0.7)
#define CAN1_GET_DATA_BA_ULTRASONIC_LEFT(t)                 ((u8)t[0])
#define CAN1_SET_DATA_BA_ULTRASONIC_LEFT(t,val)             t[0]=val;

//value 0..255 in cm (bit 1.0 .. 1.7)
#define CAN1_GET_DATA_BA_ULTRASONIC_CENTER(t)               ((u8)t[1])
#define CAN1_SET_DATA_BA_ULTRASONIC_CENTER(t,val)           t[1]=val;

//value 0..255 in cm (bit 2.0 .. 2.7)
#define CAN1_GET_DATA_BA_ULTRASONIC_RIGHT(t)                ((u8)t[2])
#define CAN1_SET_DATA_BA_ULTRASONIC_RIGHT(t,val)            t[2]=val;

//----------------

//STATE used by BSI
//Period: 200ms
#define CAN1_SIZE_STATE_BA                                  1

//value: 0/1 (bit 0.0)
#define CAN1_GET_STATE_BA_LIGHT(t)                          ((u8)bitRead(t[0], 0))
#define CAN1_SET_STATE_BA_LIGHT(t,val)                      bitWrite(t[0], 0, val);

//value: 0/1 (bit 0.1)
#define CAN1_GET_STATE_BA_BLINKER_LEFT(t)                   ((u8)bitRead(t[0], 1))
#define CAN1_SET_STATE_BA_BLINKER_LEFT(t,val)               bitWrite(t[0], 1, val);

//value: 0/1 (bit 0.2)
#define CAN1_GET_STATE_BA_BLINKER_RIGHT(t)                  ((u8)bitRead(t[0], 2))
#define CAN1_SET_STATE_BA_BLINKER_RIGHT(t,val)              bitWrite(t[0], 2, val);

//value: 0/1 (bit 0.3)
#define CAN1_GET_STATE_BA_BRAKE_LIGHT(t)                    ((u8)bitRead(t[0], 3))
#define CAN1_SET_STATE_BA_BRAKE_LIGHT(t,val)                bitWrite(t[0], 3, val);

//value: 0/1 (bit 0.4)
//TODO not defined in messagerie (DH add)
#define CAN1_GET_STATE_BA_REVERSE_LIGHT(t)                  ((u8)bitRead(t[0], 4))
#define CAN1_SET_STATE_BA_REVERSE_LIGHT(t,val)              bitWrite(t[0], 4, val);

/* //value: 0/1 (bit 0.5)
#define CAN1_GET_STATE_BA_ENCRYPTION_MODE(t)                  ((u8)bitRead(t[0], 5))
#define CAN1_SET_STATE_BA_ENCRYPTION_MODE(t,val)              bitWrite(t[0], 5, val); */

//--------------------------------------------------------------------------
// BSI
//--------------------------------------------------------------------------

//CMD used by BF and BA
//Period: event
#define CAN1_SIZE_CMD_BSI_EVENT                             1

//value: 0/1 (bit 0.0)
#define CAN1_GET_CMD_BSI_LIGHT(t)                           ((u8)bitRead(t[0], 0))
#define CAN1_SET_CMD_BSI_LIGHT(t,val)                       bitWrite(t[0], 0, val);

//--------------------------------------------------------------------------
// BSM
//--------------------------------------------------------------------------

//DATA used by BSI
//Period: 200ms
//TODO DATA or STATE ???
#define CAN1_SIZE_DATA_BSM                                7

//value: 0..255 in degree celsius (bit 0.0 .. 0.7)
#define CAN1_GET_DATA_BSM_TEMPERATURE_ENGINE(t)             ((u8)t[0])
#define CAN1_SET_DATA_BSM_TEMPERATURE_ENGINE(t,val)         t[0]=val;

//value 0..100 in % (bit 1.0 .. 1.7)
//Rq: can be compressed in 7 bits if needed
#define CAN1_GET_DATA_BSM_BATTERY_PERCENTAGE(t)             ((u8)t[1])
#define CAN1_SET_DATA_BSM_BATTERY_PERCENTAGE(t,val)         t[1]=val;

//value: 0..255 in km/h (bit 2.0 .. 2.7)
//TODO: negative speed (reverse) ???
#define CAN1_GET_DATA_BSM_OSV_SPEED(t)                	((u8)t[2])
#define CAN1_SET_DATA_BSM_OSV_SPEED(t,val)            	t[2]=val;

#define CAN1_GET_DATA_BSM_ENGINE_SPEED(t)			((s16)(t[4]<<8 | t[3] ))
#define CAN1_SET_DATA_BSM_ENGINE_SPEED(t,val)			t[3]=(val & 0x00ff);t[4]= ((val & 0xff00) >>8);

#define CAN1_GET_DATA_BSM_BRAKE_PEDAL(t)			((u8)t[5])
#define CAN1_SET_DATA_BSM_BRAKE_PEDAL(t,val)			t[5]=val;

#define CAN1_GET_DATA_BSM_ACCEL_PEDAL(t)			((u8)t[6])
#define CAN1_SET_DATA_BSM_ACCEL_PEDAL(t,val)			t[6]=val;


#define CAN1_SIZE_STATE_BSM                                 2

//value 0/1 (bit 0.0)
#define CAN1_GET_STATE_BSM_ENCRYPTION_MODE(t)                     ((u8)bitRead(t[0], 0))
#define CAN1_SET_STATE_BSM_ENCRYPTION_MODE(t,val)                 bitWrite(t[0], 0, val);

//value: 0/1 (bit 0.1)
#define CAN1_GET_STATE_CMB_BC_BRAKE(t)                     ((u8)bitRead(t[1], 0))
#define CAN1_SET_STATE_CMB_BC_BRAKE(t,val)                 bitWrite(t[1], 0, val);

//--------------------------------------------------------------------------
//
// CAN Bus 2
//
// Frame ID definition
// Frame size definition
// Get/Set functions for command and state
//
//--------------------------------------------------------------------------

#define CAN2_FORMAT 0 // format frame CAN (0 standar, 1 extended)

#define CAN2_SIZE_FRAME 8 // size of frame when encryption mode ON

#define CAN2_ID_DATA_BSI_FAST                               0x01              // 0x0A  in messagerie xls
#define CAN2_ID_DATA_BSEC                                   CAN2_ID_DATA_BSI_FAST+1     // 0x201 in messagerie xls
#define CAN2_ID_DATA_BSI_MEDIUM                             CAN2_ID_DATA_BSEC+1         // 0x205 in messagerie xls
#define CAN2_ID_DATA_BSI_SLOW                               CAN2_ID_DATA_BSI_MEDIUM+1   // 0x210 in messagerie xls
#define CAN2_ID_DATA_LIDAR 									CAN2_ID_DATA_BSI_SLOW+1		// 0x220 in messagerie xls
//Total number of frames in CAN2
#define CAN2_FRAME_NUMBER                                   CAN2_ID_DATA_LIDAR +1

//--------------------------------------------------------------------------
// BSEC
//--------------------------------------------------------------------------

//Period: 500ms
#define CAN2_SIZE_DATA_BSEC									 2

//value: 0..255 (bit 0.0 .. 0.7)
#define CAN2_GET_DATA_BSEC_BREATHALYZER(t)                  ((u8)t[0])
#define CAN2_SET_DATA_BSEC_BREATHALYZER(t,val)              t[0]=val;

//value: 0/1 (bit 1.0)
#define CAN2_GET_DATA_BSEC_KEY(t)                           ((u8)bitRead(t[1], 0))
#define CAN2_SET_DATA_BSEC_KEY(t,val)                       bitWrite(t[1], 0, val);


//--------------------------------------------------------------------------
// LIDAR
//--------------------------------------------------------------------------


//Period: 100ms   
#define CAN2_SIZE_DATA_LIDAR									1

//value: 0 .. 2 (bit 0.0 .. 0.1)
#define CAN2_GET_DATA_LIDAR_AREA_1(t)							(u8)(t[0] & 0x03)
#define CAN2_SET_DATA_LIDAR_AREA_1(t,val)						t[0]= (val & 0x03);

//value: 0 .. 2 (bit 0.2 .. 0.3)
#define CAN2_GET_DATA_LIDAR_AREA_2(t)							(u8)((t[0] >> 2) & 0x03)
#define CAN2_SET_DATA_LIDAR_AREA_2(t,val)						t[0]= t[0]|((val << 2) & 0x0c);

//value: 0 .. 2 (bit 0.4 .. 0.5)
#define CAN2_GET_DATA_LIDAR_AREA_3(t)							(u8)((t[0] >> 4) & 0x03)
#define CAN2_SET_DATA_LIDAR_AREA_3(t,val)						t[0]= t[0]|((val << 4) & 0x30);

//value: 0 .. 2 (bit 0.6 .. 0.7)
#define CAN2_GET_DATA_LIDAR_AREA_4(t)							(u8)((t[0] >> 6) & 0x03)
#define CAN2_SET_DATA_LIDAR_AREA_4(t,val)						t[0]= t[0]|((val << 6) & 0xc0);



//--------------------------------------------------------------------------
// BSI
//--------------------------------------------------------------------------

//Period: 100ms
// #define CAN2_SIZE_DATA_BSI_FAST                                 7
#define CAN2_SIZE_DATA_BSI_FAST                                 8

//value: 0..255 (bit 0.0 .. 0.7)
#define CAN2_GET_DATA_BSI_FAST_ULTRASONIC_FRONT_LEFT(t)         ((u8)t[0])
#define CAN2_SET_DATA_BSI_FAST_ULTRASONIC_FRONT_LEFT(t,val)     t[0]=val;
//value: 0..255 (bit 1.0 .. 1.7)
#define CAN2_GET_DATA_BSI_FAST_ULTRASONIC_FRONT_CENTER(t)       ((u8)t[1])
#define CAN2_SET_DATA_BSI_FAST_ULTRASONIC_FRONT_CENTER(t,val)   t[1]=val;
//value: 0..255 (bit 2.0 .. 2.7)
#define CAN2_GET_DATA_BSI_FAST_ULTRASONIC_FRONT_RIGHT(t)        ((u8)t[2])
#define CAN2_SET_DATA_BSI_FAST_ULTRASONIC_FRONT_RIGHT(t,val)    t[2]=val;

//value: 0..255 (bit 3.0 .. 3.7)
#define CAN2_GET_DATA_BSI_FAST_ULTRASONIC_REAR_LEFT(t)          ((u8)t[3])
#define CAN2_SET_DATA_BSI_FAST_ULTRASONIC_REAR_LEFT(t,val)      t[3]=val;
//value: 0..255 (bit 4.0 .. 4.7)
#define CAN2_GET_DATA_BSI_FAST_ULTRASONIC_REAR_CENTER(t)        ((u8)t[4])
#define CAN2_SET_DATA_BSI_FAST_ULTRASONIC_REAR_CENTER(t,val)    t[4]=val;
//value: 0..255 (bit 5.0 .. 5.7)
#define CAN2_GET_DATA_BSI_FAST_ULTRASONIC_REAR_RIGHT(t)         ((u8)t[5])
#define CAN2_SET_DATA_BSI_FAST_ULTRASONIC_REAR_RIGHT(t,val)     t[5]=val;

// value: -540...540 in degree => 1080 values (bit 6.0 .. 7.7)
#define CAN2_GET_DATA_BSI_FAST_STEERING_WHEEL_ANGLE(t)           ((s16)(t[7]<<8 | t[6] ))
#define CAN2_SET_DATA_BSI_FAST_STEERING_WHEEL_ANGLE(t, val)      t[6]=(val & 0x00ff);t[7]= ((val & 0xff00) >>8);

//----------------

//Period: 200ms
#define CAN2_SIZE_DATA_BSI_MEDIUM                               6

//value: 0..255 (bit 0.0 .. 0.7)
#define CAN2_GET_DATA_BSI_MEDIUM_OSV_SPEED(t)                   ((u8)t[0])
#define CAN2_SET_DATA_BSI_MEDIUM_OSV_SPEED(t,val)               t[0]=val;

//value: 0..6553 (bit 1.0 .. 2.7)
//TODO: no data available in the BSI for that
//TODO strange range : 2 bytes -> 0..65535
#define CAN2_GET_DATA_BSI_MEDIUM_ENGINE_SPEED(t)                ((u16)(t[2]<<8 | t[1] ))
#define CAN2_SET_DATA_BSI_MEDIUM_ENGINE_SPEED(t,val)            t[1]=(val & 0x00ff);t[2]= ((val & 0xff00) >>8);

//value: 0..255 (bit 3.0 .. 3.7)
#define CAN2_GET_DATA_BSI_MEDIUM_TEMPERATURE_ENGINE(t)          ((u8)t[3])
#define CAN2_SET_DATA_BSI_MEDIUM_TEMPERATURE_ENGINE(t,val)      t[3]=val;

//value 0..100 in % (bit 4.0 .. 4.7)
#define CAN2_GET_DATA_BSI_MEDIUM_BATTERY_PERCENTAGE(t)          ((u8)t[4])
#define CAN2_SET_DATA_BSI_MEDIUM_BATTERY_PERCENTAGE(t,val)      t[4]=val;


//value: 0/1 (bit 5.0)
#define CAN2_GET_DATA_BSI_MEDIUM_BLINKER_LEFT(t)                ((u8)bitRead(t[5], 0))
#define CAN2_SET_DATA_BSI_MEDIUM_BLINKER_LEFT(t,val)            bitWrite(t[5], 0,val);

//value: 0/1 (bit 5.1)
#define CAN2_GET_DATA_BSI_MEDIUM_BLINKER_RIGHT(t)               ((u8)bitRead(t[5], 1))
#define CAN2_SET_DATA_BSI_MEDIUM_BLINKER_RIGHT(t,val)           bitWrite(t[5], 1,val);

/* // value : 0/1 (bit 5.2)
#define CAN2_GET_DATA_BSI_MEDIUM_ENCRYPTION_MODE(t)                   ((u8)bitRead(t[5], 2))
#define CAN2_SET_DATA_BSI_MEDIUM_ENCRYPTION_MODE(t,val)               bitWrite(t[5], 2, val); */

//value: 0/1 (bit 5.2)
#define CAN2_GET_DATA_BSI_MEDIUM_LIGHT(t)                       ((u8)bitRead(t[5], 2))
#define CAN2_SET_DATA_BSI_MEDIUM_LIGHT(t,val)                   bitWrite(t[5], 2,val);

//value: 0/1 (bit 5.3)
//TODO: no data available in the BSI for that
#define CAN2_GET_DATA_BSI_MEDIUM_PARKING_BRAKE(t)               ((u8)bitRead(t[5], 3))
#define CAN2_SET_DATA_BSI_MEDIUM_PARKING_BRAKE(t,val)           bitWrite(t[5], 3,val);

//value: 0/1/2 (bit 5.4 . 5.5)
//TODO: data can be derived in the BSI from reverse light and speed
#define CAN2_GET_DATA_BSI_MEDIUM_OSV_STATE(t)                   ((u8)( (t[5] >> 4) & 0x3))
#define CAN2_SET_DATA_BSI_MEDIUM_OSV_STATE(t,val)               t[5] = (t[5] | ((val & 0x3) << 4));

//Retirer à la fin des tests
//value : 0/1 (bit 5.6)
#define CAN2_GET_DATA_BSI_MEDIUM_BRAKE_PEDAL(t)                    ((u8)bitRead(t[5], 6))
#define CAN2_SET_DATA_BSI_MEDIUM_BRAKE_PEDAL(t,val)                bitWrite (t[5],6,val);

//value: 0/1 (bit 5.7)
#define CAN2_GET_DATA_BSI_MEDIUM_ACCEL_PEDAL(t)                    ((u8) bitRead(t[5], 7))
#define CAN2_SET_DATA_BSI_MEDIUM_ACCEL_PEDAL(t,val)                bitWrite (t[5],7,val);


//TODO:
//mode auto pour les lumières
//capteur de luminosité
//CAN1_GET_CMD_BC_INTER_FOOT_HAND

//----------------

//Period: 200ms
//TODO Period is the same as medium in messagerie xls ???
#define CAN2_SIZE_DATA_BSI_SLOW                                 6 

//value: 0..16777215 (bit 0.0 .. 2.7)
//TODO: error for the range in messagerie xls
//TODO: can be compressed if needed
#if ARDUINO
#define CAN2_GET_DATA_BSI_SLOW_TOTAL_DISTANCE(t)                ((u32( t[2]) << 16) | (u32(t[1]) << 8) | u32(t[0]))
#else //linux
#define CAN2_GET_DATA_BSI_SLOW_TOTAL_DISTANCE(t)                ( (t[2] << 16) | (t[1] << 8) | t[0] )
#endif
#define CAN2_SET_DATA_BSI_SLOW_TOTAL_DISTANCE(t,val)            t[2]= ((val >> 16) & 0xff) ; t[1]= ((val >> 8) & 0xff) ; t[0]= (val & 0xff) ;

//value: 0..16777215 (bit 3.0 .. 5.7)
//TODO: error for the range or the number of bytes in messagerie xls
//TODO: can be compressed if needed
#if ARDUINO
#define CAN2_GET_DATA_BSI_SLOW_RESET_DISTANCE(t)                ((u32(t[5]) << 16) | (u32(t[4]) << 8) | u32(t[3]))
#else //linux
#define CAN2_GET_DATA_BSI_SLOW_RESET_DISTANCE(t)                ( (t[5] << 16) | (t[4] << 8) | t[3] )
#endif
#define CAN2_SET_DATA_BSI_SLOW_RESET_DISTANCE(t,val)            t[5]= ((val >> 16) & 0xff) ; t[4]= ((val >> 8) & 0xff) ; t[3]= (val & 0xff) ;

//TODO: ETHYLO not needed because sent periodically by BSEC on can2

#endif
