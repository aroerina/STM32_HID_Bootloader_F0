# STM32_HID_Bootloader_F0
Simple USB HID Bootloader for STM32F0xx series

[bootsector/stm32-hid-bootloader](https://github.com/bootsector/stm32-hid-bootloader) 

[Serasidis/STM32_HID_Bootloader](https://github.com/Serasidis/STM32_HID_Bootloader) 


This is a USB HID bootloader for the STM32F0xx series.
This is a ported version of the above two projects for the STM32F0xx series, and the amount of FLASH usage is very compact, less than 2KB.
This is written for the STM32F072CB, but I think other F0 microcontrollers with USB will work too, if you adjust the page size and SRAM size.
You can use the downloadable CLI application in the repositories of the above two projects to write.

The STM32 Cortex M0/M0+ core microcontrollers do not have a VTOR register, so if you want to use interrupts in your user applications, you need to use
You need to change the memory alias by rewriting the SYSCFG register.
In that case, you also need to edit the RAM start position in the linker script, as you will need an offset for the vector table.
See main.c in vtable_allocate_test for details.

- Directory
   - hid_bootloader CubeIDE project of the bootloader itself
   - vtable_allocate_test　CubeIDE project in the user application example, relocating the vector table to SRAM for interrupts
   
---

# STM32_HID_Bootloader_F0
Simple USB HID Bootloader for STM32F0xx series

[bootsector/stm32-hid-bootloader](https://github.com/bootsector/stm32-hid-bootloader) 

[Serasidis/STM32_HID_Bootloader](https://github.com/Serasidis/STM32_HID_Bootloader) 


STM32F0xxシリーズ用USB HIDブートローダーです。Windows等でドライバ不要で動作します。
上記２つのプロジェクトをSTM32F0xxシリーズ用に移植したもので、FLASH使用量は2KB未満と非常にコンパクトです。
STM32F072CBに向けて書いてありますが、ページサイズ、SRAMサイズ等を調節すれば他のUSB搭載のF0マイコンでも動くと思います。
書き込みは上記プロジェクト2つのリポジトリでダウンロードできるCLIアプリが利用できます。

STM32のCortex M0/M0+コアのマイコンはVTORレジスタが無いので、ユーザーアプリケーションで割り込みを使用する場合は
SYSCFGレジスタを書き換えてメモリーエイリアスを変更する必要があります。
その場合、ベクターテーブル分のオフセットが必要になってくるのでリンカスクリプトのRAM開始位置の編集も必要です。
詳しくはvtable_allocate_testのmain.cを見てください

- ディレクトリ
   - hid_bootloader ブートローダー本体のCubeIDEプロジェクト
   - vtable_allocate_test　ユーザーアプリケーション例のCubeIDEプロジェクト、SRAMにベクターテーブルを再配置して割り込みを使います
