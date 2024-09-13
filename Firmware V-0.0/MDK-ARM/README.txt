/* CAN DEBUG CODES */

USE_PDO သုံးရင် ACTUAL RPM, ACTUAL POSITION များကို REQUEST လုပ်စရာမလိုပါ။ main.h ထဲမှာ #define USE_PDO 1 ဟု သုံးပါ။
မသုံးရင် COMMENT အုပ်ပါ။

#ifdef CAN_DEBUG 1 ဆိုပါက
led blink blue သည် 10ms loop ထဲဝင်ရောက်ကြောင်းဖြစ်သည်။
led blink red, green, blue, orange  ( 500ms ) သည် CAN_Error_Handler()  ဖြစ် သည်။
led blink orange သည် CAN Transmit လုပ်ဆောင်ကြောင်း ဖြစ်သည်။ 
led blink green သည် fifo callback ကြောင့်ဖြစ်သည်။
