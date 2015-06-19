	.syntax unified
	.cpu cortex-m3
	.fpu softvfp
	.eabi_attribute 20, 1
	.eabi_attribute 21, 1
	.eabi_attribute 23, 3
	.eabi_attribute 24, 1
	.eabi_attribute 25, 1
	.eabi_attribute 26, 1
	.eabi_attribute 30, 4
	.eabi_attribute 34, 1
	.eabi_attribute 18, 4
	.thumb
	.file	"mutex.cpp"
	.text
.Ltext0:
	.cfi_sections	.debug_frame
	.section	.text.takeM,"ax",%progbits
	.align	1
	.global	takeM
	.thumb
	.thumb_func
	.type	takeM, %function
takeM:
.LFB199:
	.file 1 "/tmp/build2649613775398481885.tmp/mutex.cpp"
	.loc 1 10 0
	.cfi_startproc
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	@ link register save eliminated.
.LVL0:
	.loc 1 13 0
@ 13 "/tmp/build2649613775398481885.tmp/mutex.cpp" 1
	.take:           
	
@ 0 "" 2
	.loc 1 14 0
@ 14 "/tmp/build2649613775398481885.tmp/mutex.cpp" 1
	push { r2, r5 }  
	
@ 0 "" 2
	.loc 1 21 0
@ 21 "/tmp/build2649613775398481885.tmp/mutex.cpp" 1
	ldrex r5, [r0]   
	
@ 0 "" 2
	.loc 1 30 0
@ 30 "/tmp/build2649613775398481885.tmp/mutex.cpp" 1
	mov r2, #1  
	
@ 0 "" 2
	.loc 1 31 0
@ 31 "/tmp/build2649613775398481885.tmp/mutex.cpp" 1
	cmp r2, r5  
	
@ 0 "" 2
	.loc 1 32 0
@ 32 "/tmp/build2649613775398481885.tmp/mutex.cpp" 1
	beq .take   
	
@ 0 "" 2
	.loc 1 37 0
@ 37 "/tmp/build2649613775398481885.tmp/mutex.cpp" 1
	strex r5, r2, [r0]  
	
@ 0 "" 2
	.loc 1 42 0
@ 42 "/tmp/build2649613775398481885.tmp/mutex.cpp" 1
	mov r2, #1  
	
@ 0 "" 2
	.loc 1 43 0
@ 43 "/tmp/build2649613775398481885.tmp/mutex.cpp" 1
	cmp r2, r5      
	
@ 0 "" 2
	.loc 1 44 0
@ 44 "/tmp/build2649613775398481885.tmp/mutex.cpp" 1
	beq .take       
	
@ 0 "" 2
	.loc 1 46 0
@ 46 "/tmp/build2649613775398481885.tmp/mutex.cpp" 1
	pop { r2, r5 }  
	
@ 0 "" 2
	.thumb
	bx	lr
	.cfi_endproc
.LFE199:
	.size	takeM, .-takeM
	.section	.text.freeM,"ax",%progbits
	.align	1
	.global	freeM
	.thumb
	.thumb_func
	.type	freeM, %function
freeM:
.LFB200:
	.loc 1 63 0
	.cfi_startproc
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	@ link register save eliminated.
.LVL1:
	.loc 1 64 0
@ 64 "/tmp/build2649613775398481885.tmp/mutex.cpp" 1
	push { r2 }   
	
@ 0 "" 2
	.loc 1 65 0
@ 65 "/tmp/build2649613775398481885.tmp/mutex.cpp" 1
	mov r2, #0    
	
@ 0 "" 2
	.loc 1 66 0
@ 66 "/tmp/build2649613775398481885.tmp/mutex.cpp" 1
	str r2, [r0]  
	
@ 0 "" 2
	.loc 1 68 0
@ 68 "/tmp/build2649613775398481885.tmp/mutex.cpp" 1
	pop { r2 }    
	
@ 0 "" 2
	.thumb
	bx	lr
	.cfi_endproc
.LFE200:
	.size	freeM, .-freeM
	.global	Debug
	.section	.data.Debug,"aw",%progbits
	.align	2
	.type	Debug, %object
	.size	Debug, 4
Debug:
	.word	1
	.text
.Letext0:
	.file 2 "/home/maxime/.arduino15/packages/arduino/tools/arm-none-eabi-gcc/4.8.3-2014q1/arm-none-eabi/include/machine/_default_types.h"
	.file 3 "/home/maxime/.arduino15/packages/arduino/tools/arm-none-eabi-gcc/4.8.3-2014q1/arm-none-eabi/include/stdint.h"
	.file 4 "/home/maxime/.arduino15/packages/arduino/hardware/sam/1.6.4/system/CMSIS/CMSIS/Include/core_cm3.h"
	.file 5 "/home/maxime/.arduino15/packages/arduino/hardware/sam/1.6.4/system/libsam/include/interrupt_sam_nvic.h"
	.file 6 "/home/maxime/.arduino15/packages/arduino/hardware/sam/1.6.4/variants/arduino_due_x/variant.h"
	.section	.debug_info,"",%progbits
.Ldebug_info0:
	.4byte	0x278
	.2byte	0x4
	.4byte	.Ldebug_abbrev0
	.byte	0x4
	.uleb128 0x1
	.4byte	.LASF35
	.byte	0x4
	.4byte	.LASF36
	.4byte	.LASF37
	.4byte	.Ldebug_ranges0+0
	.4byte	0
	.4byte	.Ldebug_line0
	.uleb128 0x2
	.byte	0x1
	.byte	0x6
	.4byte	.LASF0
	.uleb128 0x3
	.4byte	.LASF4
	.byte	0x2
	.byte	0x1c
	.4byte	0x37
	.uleb128 0x2
	.byte	0x1
	.byte	0x8
	.4byte	.LASF1
	.uleb128 0x2
	.byte	0x2
	.byte	0x5
	.4byte	.LASF2
	.uleb128 0x2
	.byte	0x2
	.byte	0x7
	.4byte	.LASF3
	.uleb128 0x3
	.4byte	.LASF5
	.byte	0x2
	.byte	0x37
	.4byte	0x57
	.uleb128 0x2
	.byte	0x4
	.byte	0x5
	.4byte	.LASF6
	.uleb128 0x3
	.4byte	.LASF7
	.byte	0x2
	.byte	0x38
	.4byte	0x69
	.uleb128 0x2
	.byte	0x4
	.byte	0x7
	.4byte	.LASF8
	.uleb128 0x2
	.byte	0x8
	.byte	0x5
	.4byte	.LASF9
	.uleb128 0x2
	.byte	0x8
	.byte	0x7
	.4byte	.LASF10
	.uleb128 0x4
	.byte	0x4
	.byte	0x5
	.ascii	"int\000"
	.uleb128 0x2
	.byte	0x4
	.byte	0x7
	.4byte	.LASF11
	.uleb128 0x3
	.4byte	.LASF12
	.byte	0x3
	.byte	0x2a
	.4byte	0x2c
	.uleb128 0x3
	.4byte	.LASF13
	.byte	0x3
	.byte	0x41
	.4byte	0x4c
	.uleb128 0x3
	.4byte	.LASF14
	.byte	0x3
	.byte	0x42
	.4byte	0x5e
	.uleb128 0x2
	.byte	0x4
	.byte	0x7
	.4byte	.LASF15
	.uleb128 0x2
	.byte	0x1
	.byte	0x8
	.4byte	.LASF16
	.uleb128 0x2
	.byte	0x8
	.byte	0x4
	.4byte	.LASF17
	.uleb128 0x2
	.byte	0x4
	.byte	0x4
	.4byte	.LASF18
	.uleb128 0x2
	.byte	0x8
	.byte	0x4
	.4byte	.LASF19
	.uleb128 0x5
	.4byte	0xa2
	.uleb128 0x2
	.byte	0x1
	.byte	0x2
	.4byte	.LASF20
	.uleb128 0x6
	.4byte	.LASF21
	.byte	0x1
	.byte	0x9
	.4byte	.LFB199
	.4byte	.LFE199-.LFB199
	.uleb128 0x1
	.byte	0x9c
	.4byte	0xff
	.uleb128 0x7
	.4byte	.LASF23
	.byte	0x1
	.byte	0x9
	.4byte	0xff
	.uleb128 0x1
	.byte	0x50
	.byte	0
	.uleb128 0x8
	.byte	0x4
	.4byte	0xd0
	.uleb128 0x6
	.4byte	.LASF22
	.byte	0x1
	.byte	0x3f
	.4byte	.LFB200
	.4byte	.LFE200-.LFB200
	.uleb128 0x1
	.byte	0x9c
	.4byte	0x128
	.uleb128 0x7
	.4byte	.LASF23
	.byte	0x1
	.byte	0x3f
	.4byte	0xff
	.uleb128 0x1
	.byte	0x50
	.byte	0
	.uleb128 0x9
	.4byte	.LASF24
	.byte	0x4
	.2byte	0x494
	.4byte	0x134
	.uleb128 0x5
	.4byte	0x97
	.uleb128 0xa
	.4byte	.LASF25
	.byte	0x5
	.byte	0x76
	.4byte	0x7e
	.uleb128 0xb
	.ascii	"SS\000"
	.byte	0x6
	.byte	0x81
	.4byte	0x14f
	.byte	0xa
	.uleb128 0xc
	.4byte	0x8c
	.uleb128 0xb
	.ascii	"SS1\000"
	.byte	0x6
	.byte	0x82
	.4byte	0x14f
	.byte	0x4
	.uleb128 0xb
	.ascii	"SS2\000"
	.byte	0x6
	.byte	0x83
	.4byte	0x14f
	.byte	0x34
	.uleb128 0xb
	.ascii	"SS3\000"
	.byte	0x6
	.byte	0x84
	.4byte	0x14f
	.byte	0x4e
	.uleb128 0xd
	.4byte	.LASF26
	.byte	0x6
	.byte	0x85
	.4byte	0x14f
	.byte	0x4b
	.uleb128 0xd
	.4byte	.LASF27
	.byte	0x6
	.byte	0x86
	.4byte	0x14f
	.byte	0x4a
	.uleb128 0xb
	.ascii	"SCK\000"
	.byte	0x6
	.byte	0x87
	.4byte	0x14f
	.byte	0x4c
	.uleb128 0xb
	.ascii	"A0\000"
	.byte	0x6
	.byte	0xb0
	.4byte	0x14f
	.byte	0x36
	.uleb128 0xb
	.ascii	"A1\000"
	.byte	0x6
	.byte	0xb1
	.4byte	0x14f
	.byte	0x37
	.uleb128 0xb
	.ascii	"A2\000"
	.byte	0x6
	.byte	0xb2
	.4byte	0x14f
	.byte	0x38
	.uleb128 0xb
	.ascii	"A3\000"
	.byte	0x6
	.byte	0xb3
	.4byte	0x14f
	.byte	0x39
	.uleb128 0xb
	.ascii	"A4\000"
	.byte	0x6
	.byte	0xb4
	.4byte	0x14f
	.byte	0x3a
	.uleb128 0xb
	.ascii	"A5\000"
	.byte	0x6
	.byte	0xb5
	.4byte	0x14f
	.byte	0x3b
	.uleb128 0xb
	.ascii	"A6\000"
	.byte	0x6
	.byte	0xb6
	.4byte	0x14f
	.byte	0x3c
	.uleb128 0xb
	.ascii	"A7\000"
	.byte	0x6
	.byte	0xb7
	.4byte	0x14f
	.byte	0x3d
	.uleb128 0xb
	.ascii	"A8\000"
	.byte	0x6
	.byte	0xb8
	.4byte	0x14f
	.byte	0x3e
	.uleb128 0xb
	.ascii	"A9\000"
	.byte	0x6
	.byte	0xb9
	.4byte	0x14f
	.byte	0x3f
	.uleb128 0xb
	.ascii	"A10\000"
	.byte	0x6
	.byte	0xba
	.4byte	0x14f
	.byte	0x40
	.uleb128 0xb
	.ascii	"A11\000"
	.byte	0x6
	.byte	0xbb
	.4byte	0x14f
	.byte	0x41
	.uleb128 0xd
	.4byte	.LASF28
	.byte	0x6
	.byte	0xbc
	.4byte	0x14f
	.byte	0x42
	.uleb128 0xd
	.4byte	.LASF29
	.byte	0x6
	.byte	0xbd
	.4byte	0x14f
	.byte	0x43
	.uleb128 0xd
	.4byte	.LASF30
	.byte	0x6
	.byte	0xbe
	.4byte	0x14f
	.byte	0x44
	.uleb128 0xd
	.4byte	.LASF31
	.byte	0x6
	.byte	0xbf
	.4byte	0x14f
	.byte	0x45
	.uleb128 0xd
	.4byte	.LASF32
	.byte	0x6
	.byte	0xc5
	.4byte	0x14f
	.byte	0x58
	.uleb128 0xd
	.4byte	.LASF33
	.byte	0x6
	.byte	0xc6
	.4byte	0x14f
	.byte	0x59
	.uleb128 0xe
	.4byte	.LASF34
	.byte	0x1
	.byte	0x5
	.4byte	0x7e
	.uleb128 0x5
	.byte	0x3
	.4byte	Debug
	.byte	0
	.section	.debug_abbrev,"",%progbits
.Ldebug_abbrev0:
	.uleb128 0x1
	.uleb128 0x11
	.byte	0x1
	.uleb128 0x25
	.uleb128 0xe
	.uleb128 0x13
	.uleb128 0xb
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x1b
	.uleb128 0xe
	.uleb128 0x55
	.uleb128 0x17
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x10
	.uleb128 0x17
	.byte	0
	.byte	0
	.uleb128 0x2
	.uleb128 0x24
	.byte	0
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x3e
	.uleb128 0xb
	.uleb128 0x3
	.uleb128 0xe
	.byte	0
	.byte	0
	.uleb128 0x3
	.uleb128 0x16
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x4
	.uleb128 0x24
	.byte	0
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x3e
	.uleb128 0xb
	.uleb128 0x3
	.uleb128 0x8
	.byte	0
	.byte	0
	.uleb128 0x5
	.uleb128 0x35
	.byte	0
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x6
	.uleb128 0x2e
	.byte	0x1
	.uleb128 0x3f
	.uleb128 0x19
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x6
	.uleb128 0x40
	.uleb128 0x18
	.uleb128 0x2117
	.uleb128 0x19
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x7
	.uleb128 0x5
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2
	.uleb128 0x18
	.byte	0
	.byte	0
	.uleb128 0x8
	.uleb128 0xf
	.byte	0
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x9
	.uleb128 0x34
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0x5
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x3f
	.uleb128 0x19
	.uleb128 0x3c
	.uleb128 0x19
	.byte	0
	.byte	0
	.uleb128 0xa
	.uleb128 0x34
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x3f
	.uleb128 0x19
	.uleb128 0x3c
	.uleb128 0x19
	.byte	0
	.byte	0
	.uleb128 0xb
	.uleb128 0x34
	.byte	0
	.uleb128 0x3
	.uleb128 0x8
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x1c
	.uleb128 0xb
	.byte	0
	.byte	0
	.uleb128 0xc
	.uleb128 0x26
	.byte	0
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0xd
	.uleb128 0x34
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x1c
	.uleb128 0xb
	.byte	0
	.byte	0
	.uleb128 0xe
	.uleb128 0x34
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x3f
	.uleb128 0x19
	.uleb128 0x2
	.uleb128 0x18
	.byte	0
	.byte	0
	.byte	0
	.section	.debug_aranges,"",%progbits
	.4byte	0x24
	.2byte	0x2
	.4byte	.Ldebug_info0
	.byte	0x4
	.byte	0
	.2byte	0
	.2byte	0
	.4byte	.LFB199
	.4byte	.LFE199-.LFB199
	.4byte	.LFB200
	.4byte	.LFE200-.LFB200
	.4byte	0
	.4byte	0
	.section	.debug_ranges,"",%progbits
.Ldebug_ranges0:
	.4byte	.LFB199
	.4byte	.LFE199
	.4byte	.LFB200
	.4byte	.LFE200
	.4byte	0
	.4byte	0
	.section	.debug_line,"",%progbits
.Ldebug_line0:
	.section	.debug_str,"MS",%progbits,1
.LASF30:
	.ascii	"CANRX\000"
.LASF4:
	.ascii	"__uint8_t\000"
.LASF31:
	.ascii	"CANTX\000"
.LASF5:
	.ascii	"__int32_t\000"
.LASF20:
	.ascii	"bool\000"
.LASF29:
	.ascii	"DAC1\000"
.LASF18:
	.ascii	"float\000"
.LASF10:
	.ascii	"long long unsigned int\000"
.LASF1:
	.ascii	"unsigned char\000"
.LASF36:
	.ascii	"/tmp/build2649613775398481885.tmp/mutex.cpp\000"
.LASF8:
	.ascii	"long unsigned int\000"
.LASF3:
	.ascii	"short unsigned int\000"
.LASF34:
	.ascii	"Debug\000"
.LASF17:
	.ascii	"double\000"
.LASF7:
	.ascii	"__uint32_t\000"
.LASF27:
	.ascii	"MISO\000"
.LASF33:
	.ascii	"CAN1TX\000"
.LASF24:
	.ascii	"ITM_RxBuffer\000"
.LASF26:
	.ascii	"MOSI\000"
.LASF11:
	.ascii	"unsigned int\000"
.LASF25:
	.ascii	"g_interrupt_enabled\000"
.LASF16:
	.ascii	"char\000"
.LASF12:
	.ascii	"uint8_t\000"
.LASF28:
	.ascii	"DAC0\000"
.LASF21:
	.ascii	"takeM\000"
.LASF35:
	.ascii	"GNU C++ 4.8.3 20140228 (release) [ARM/embedded-4_8-"
	.ascii	"branch revision 208322] -mcpu=cortex-m3 -mthumb -g "
	.ascii	"-Os -ffunction-sections -fdata-sections -fno-thread"
	.ascii	"safe-statics -fno-rtti -fno-exceptions --param max-"
	.ascii	"inline-insns-single=500\000"
.LASF13:
	.ascii	"int32_t\000"
.LASF15:
	.ascii	"sizetype\000"
.LASF32:
	.ascii	"CAN1RX\000"
.LASF9:
	.ascii	"long long int\000"
.LASF23:
	.ascii	"mutex\000"
.LASF37:
	.ascii	"/home/maxime/Documents/Babix\000"
.LASF2:
	.ascii	"short int\000"
.LASF14:
	.ascii	"uint32_t\000"
.LASF6:
	.ascii	"long int\000"
.LASF22:
	.ascii	"freeM\000"
.LASF19:
	.ascii	"long double\000"
.LASF0:
	.ascii	"signed char\000"
	.ident	"GCC: (GNU Tools for ARM Embedded Processors (Arduino build)) 4.8.3 20140228 (release) [ARM/embedded-4_8-branch revision 208322]"
