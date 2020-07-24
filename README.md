# STM32_HID_Bootloader_F0
Simple USB HID Bootloader for STM32F0xx series

[bootsector/stm32-hid-bootloader](https://github.com/bootsector/stm32-hid-bootloader) 

[Serasidis/STM32_HID_Bootloader](https://github.com/Serasidis/STM32_HID_Bootloader) 


This is a USB HID bootloader for the STM32F0xx series.
This is a ported version of the above two projects for the STM32F0xx series, and the amount of FLASH usage is very compact, less than 2KB.
This is written for the STM32F072CB, but I think other F0 microcontrollers with USB will work too, if you adjust the page size and SRAM size.
You can use the downloadable CLI application in the repositories of the above two projects to write.

- Directory
   - hid_bootloader CubeIDE project of the bootloader itself
   - vtable_allocate_test　CubeIDE project in the user application example, relocating the vector table to SRAM for interrupts
   
---

# STM32_HID_Bootloader_F0
Simple USB HID Bootloader for STM32F0xx series

[bootsector/stm32-hid-bootloader](https://github.com/bootsector/stm32-hid-bootloader) 

[Serasidis/STM32_HID_Bootloader](https://github.com/Serasidis/STM32_HID_Bootloader) 


STM32F0xxシリーズ用USB HIDブートローダーです。
上記２つのプロジェクトをSTM32F0xxシリーズ用に移植したもので、FLASH使用量は2KB未満と非常にコンパクトです。
STM32F072CBに向けて書いてありますが、ページサイズ、SRAMサイズ等を調節すれば他のUSB搭載のF0マイコンでも動くと思います。
書き込みは上記プロジェクト2つのリポジトリでダウンロードできるCLIアプリが利用できます。

- ディレクトリ
   - hid_bootloader ブートローダー本体のCubeIDEプロジェクト
   - vtable_allocate_test　ユーザーアプリケーション例のCubeIDEプロジェクト、SRAMにベクターテーブルを再配置して割り込みを使います
