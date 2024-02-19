#ifndef _IP5328_H_
#define _IP5328_H_

#define IP5328_I2C_ADDR 0xEA 

enum ChipType{
    IP5328,
    IP5328P
};


// 000: Standby 待机 
// 001: 5V Charging 5V充电 
// 010: Single Port Charging and Discharging 单口同充同放 
// 011: Multi Port Charging and Discharging 多口同充同放 
// 100: High Voltage Fast Charging 高压快充充电 
// 101: 5V Discharging 5V放电 
// 110: Multi Port 5V Discharging 多口5V放电 
// 111: High Voltage Fast Discharging 高压快充放电 
enum SysState{
    SysState_Standby = 0, // 000
    SysState_Charging5V = 1, // 001
    SysState_SinglePort = 2, // 010
    SysState_MultiPort = 3, // 011
    SysState_ChargingHV = 4, // 100
    SysState_Discharging5V = 5, // 101
    SysState_DischargingMulti5V = 6, // 110
    SysState_DischargingHV = 7 // 111
};



// 000: IDLE
// 001: Trickle Charging Stage 涓流充电阶段 
// 010: Constant Current Charging Stage 恒流充电阶段 
// 011: Constant Voltage Charging Stage 恒压充电阶段 
// 100: Stop Charging Detection 停充检测 
// 101: Battery Full End 电池充满结束 
// 110: Timer Out 超时
enum ChargingState {
    ChargingState_IDLE = 0, // 000
    ChargingState_TrickleCharging = 1, // 001
    ChargingState_ConstantCurrentCharging = 2, // 010
    ChargingState_ConstantVoltageCharging = 3, // 011
    ChargingState_StopChargingDetection = 4, // 100
    ChargingState_FullCharge = 5, // 101
    ChargingState_TimerOut = 6 // 110
};


enum SimpleChangingState {
    SimpleChargingState_Standby,
    SimpleChargingState_Charging,
    SimpleChargingState_FullCharge
};








#endif