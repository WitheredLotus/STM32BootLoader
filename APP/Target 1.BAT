SET PATH=E:\Keil_v5\ARM\ARMCC\Bin;E:\Program Files (x86)\NetSarang\Xftp 6\;E:\Program Files (x86)\NetSarang\Xshell 6\;C:\Program Files (x86)\Common Files\Oracle\Java\javapath;C:\Program Files\Java\jdk1.8.0_131\bin;C:\Program Files\Java\jdk1.8.0_131\jre\bin;C:\Windows\system32\bin;C:\Windows\system32\jre\bin;C:\ProgramData\Oracle\Java\javapath;C:\Windows\system32;C:\Windows;C:\Windows\System32\Wbem;C:\Windows\System32\WindowsPowerShell\v1.0\;C:\Windows\System32\OpenSSH\;C:\Users\lotuscc\AppData\Local\Microsoft\WindowsApps;E:\ProgramData\Anaconda3;E:\Program Files (x86)\NASM;C:\Program Files\Git\cmd;E:\Qt\Qt5.13.0\5.13.0\mingw73_64\bin;C:\Users\lotuscc\AppData\Local\Microsoft\WindowsApps;;E:\Program Files\JetBrains\PyCharm Community Edition 2019.2.1\bin;
SET CPU_TYPE=STM32F103ZE
SET CPU_VENDOR=STMicroelectronics
SET UV2_TARGET=Target 1
SET CPU_CLOCK=0x007A1200
"E:\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via ".\output\ustart.__i"
"E:\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via ".\output\delay.__i"
"E:\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via ".\output\sys.__i"
"E:\Keil_v5\ARM\ARMCC\Bin\ArmAsm" --Via ".\output\startup_stm32f10x_hd._ia"
"E:\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via ".\output\core_cm3.__i"
"E:\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via ".\output\system_stm32f10x.__i"
"E:\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via ".\output\misc.__i"
"E:\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via ".\output\stm32f10x_rcc.__i"
"E:\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via ".\output\stm32f10x_usart.__i"
"E:\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via ".\output\stm32f10x_gpio.__i"
"E:\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via ".\output\main.__i"
"E:\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via ".\output\stm32f10x_it.__i"
"E:\Keil_v5\ARM\ARMCC\Bin\ArmLink" --Via ".\Output\new.lnp"
"E:\Keil_v5\ARM\ARMCC\Bin\fromelf.exe" ".\Output\new.axf" --i32combined --output ".\Output\new.hex"
