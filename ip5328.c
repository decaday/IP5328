
#include <stdint.h>
#include "ip5328.h"

enum ChipType chip_type = IP5328P;

// Read the data of the high and low registers and merge them
// 读取高低两个寄存器数据并合并
uint32_t ip5328_read_reg16(uint8_t addr_low, uint8_t addr2_heigh) {
  uint8_t data1 = ip5328_read_reg(addr2_heigh);
  uint8_t data2 = ip5328_read_reg(addr_low);
  return (data1 << 8) | data2;
}

// Set the chip type
// 设置芯片类型
void ip5328_set_chip_name(enum ChipType set_chip_type){
    chip_type = set_chip_type;
}

// Read the system status, see enum SysState for details
// 读取系统状态，详见enum SysState
// 0xD1 2:0
enum SysState ip5328_read_sys_state(){
    uint8_t reg_data = ip5328_read_reg(0xD1);
    return (enum SysState)(reg_data & 0b00000111);
}

// Read the charging status, see enum ChargingState for details
// 读取充电状态，详见enum ChargingState
// 0xD7 2:0
enum ChargingState ip5328_read_charging_state(){
    uint8_t reg_data = ip5328_read_reg(0xD7);
    return (enum ChargingState)(reg_data & 0b00000111);
}

// Read the simple charging status, see enum SimpleChangingState for details
// 读取简单充电状态，详见enum SimpleChangingState
// 0xD1 4   0:Discharging 1:Charging
// 0xD7 6   0:Charging  1:full charge
enum SimpleChangingState ip5328_read_simple_charging_state(){
    uint8_t reg_data1 = ip5328_read_reg(0xD1) & 0b00010000;
    if(reg_data1){
        uint8_t reg_data2 = ip5328_read_reg(0xD1) & 0b01000000;
        if(reg_data2){
            return SimpleChargingState_FullCharge;
        }
        else{
            return SimpleChargingState_Charging;
        }
    }
    else{
        return SimpleChargingState_Standby;
    }
}

// Read the BATOCV voltage, unit mv
// BATOCV voltage is the BAT voltage after compensating for the cell internal resistance and cell current, and also doing digital filtering
// 读取BATOCV电压，单位mv
// BATOCV电压是BAT电压经过电芯内阻和电芯电流进行补偿同时有做数字滤波后的电压
// 0x7A(Low)  0x7B(High)
uint32_t ip5328_read_batocv_mv() {
    uint32_t data = ip5328_read_reg16(0x7A, 0x7B);
    data = data * 0.26855 + 2600;
    return data;
}

// Read the BAT real voltage, unit mv
// 读取BAT真实电压，单位mv
// 0x64(Low)  0x65(High)
uint32_t ip5328_read_batvadc_mv() {
    uint32_t data = ip5328_read_reg16(0x64, 0x65);
    data = data * 0.26855 + 2600;
    return data;
}

// Read the BAT terminal current, unit ma
// Complement format, charging is positive, discharging is negative
// this current is calculated by the output power and efficiency, there is a certain error for different sizes of current
// 读取BAT端电流，单位ma
// 补码格式，充电为正，放电为负
// 该电流是通过输出功率和效率计算出来的值，不同大小的电流存在一定的误差
// 0x66(Low)  0x67(High)
uint32_t ip5328_read_batiadc_ma() {
    uint32_t data = ip5328_read_reg16(0x66, 0x67);
    data = data * 1.27883;
    return data;
}

// Read the Vsys terminal voltage, complement format, the valid value is usually negative
// 读取Vsys端电压，单位mv 补码格式，有效值通常为负值
// 0x68(Low)  0x69(High)
uint32_t ip5328_read_sysvadc_mv() {
    uint32_t data = ip5328_read_reg16(0x68, 0x69);
    data = data * 1.61133 + 15600;
    return data;
}

// Read the Vsys terminal current, unit ma
// 读取Vsys端电流，单位ma
// 0x6A(Low)  0x6B(High)
uint32_t ip5328_read_sysiadc_ma() {
    uint32_t data = ip5328_read_reg16(0x6A, 0x6B);
    data = data * 0.6394; //10mOhm
    return data;
}

// Read the input and output power, unit mv
// 读取输入输出功率，单位mv
// 0x7C(Low)  0x7D(High)
uint32_t ip5328_read_power_mw() {
    uint32_t data = ip5328_read_reg16(0x7C, 0x7D);
    data = data * 8.44; //10mOhm
    return data;
}
