/*
 * [Warning!] This file is auto-generated by pika compiler.
 * Do not edit it manually.
 * The source code is *.pyi file.
 * More details: 
 * English Doc:
 * https://pikadoc.readthedocs.io/en/latest/PikaScript%20%E6%A8%A1%E5%9D%97%E6%A6%82%E8%BF%B0.html
 * Chinese Doc:
 * https://pikadoc.readthedocs.io/zh/latest/PikaScript%20%E6%A8%A1%E5%9D%97%E6%A6%82%E8%BF%B0.html
 */

#ifndef __ZeptoWatchPeriphLib_Microphone__H
#define __ZeptoWatchPeriphLib_Microphone__H
#include <stdio.h>
#include <stdlib.h>
#include "PikaObj.h"

PikaObj *New_ZeptoWatchPeriphLib_Microphone(Args *args);

int ZeptoWatchPeriphLib_Microphone_getRawData(PikaObj *self);
void ZeptoWatchPeriphLib_Microphone_startSampling(PikaObj *self);
void ZeptoWatchPeriphLib_Microphone_stopSampling(PikaObj *self);

#endif
