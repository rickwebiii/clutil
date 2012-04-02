mdef(16383)_out(1)_in(2)
mov r0, in0
mov r1, in1
div_zeroop(infinity) r0.x___, r0.x, r1.x
mov out0, r0
mend
il_cs_2_0
dcl_cb cb0[15] ; Constant buffer that holds ABI data
dcl_literal l0, 0x00000004, 0x00000001, 0x00000002, 0x00000003
dcl_literal l1, 0x00FFFFFF, 0xFFFFFFFF, 0xFFFFFFFE, 0xFFFFFFFD
dcl_literal l2, 0x0000FFFF, 0xFFFFFFFE, 0x000000FF, 0xFFFFFFFC
dcl_literal l3, 0x00000018, 0x00000010, 0x00000008, 0xFFFFFFFF
dcl_literal l4, 0xFFFFFF00, 0xFFFF0000, 0xFF00FFFF, 0xFFFF00FF
dcl_literal l5, 0x00000000, 0x00000004, 0x00000008, 0x0000000C
dcl_literal l6, 0x00000020, 0x00000020, 0x00000020, 0x00000020
dcl_literal l7, 0x00000018, 0x0000001F, 0x00000010, 0x0000001F
dcl_literal l8, 0x80000000, 0x80000000, 0x80000000, 0x80000000
call 1024;$
endmain
func 1024 ; __OpenCL_sgemmNN_kernel
mov r1013, cb0[8].x
mov r1019, l1.0000
dcl_num_thread_per_group 16, 16, 1          
dcl_lds_id(1) 14848
dcl_typeless_uav_id(9)_stride(4)_length(4)_access(read_write)
dcl_typeless_uav_id(11)_stride(4)_length(4)_access(read_write)
dcl_typeless_uav_id(10)_stride(4)_length(4)_access(read_write)
mov r0.__z_, vThreadGrpIdFlat0.x
mov r1022.xyz0, vTidInGrp0.xyz
mov r1023.xyz0, vThreadGrpId0.xyz
dcl_literal l9, 16, 16, 1, 0
imad r1021.xyz0, r1023.xyzz, l9.xyzz, r1022.xyzz
iadd r1021.xyz0, r1021.xyz0, cb0[6].xyz0
iadd r1023.xyz0, r1023.xyz0, cb0[7].xyz0
mov r1023.___w, r0.z
ishl r1023.___w, r1023.w, l0.z
mov r1018.x___, l0.0000
udiv r1024.xyz_, r1021.xyzz, cb0[10].xyzz
imad r1025.xyz0, r1023.xyzz, cb0[10].xyzz, r1022.xyzz
dcl_literal l15, 0x00000000, 0x00000000, 0x00000000, 0x00000000; f32:i32 0
dcl_literal l12, 0x00000001, 0x00000001, 0x00000001, 0x00000001; f32:i32 1
dcl_literal l16, 0x00000002, 0x00000002, 0x00000002, 0x00000002; f32:i32 2
dcl_literal l43, 0x00000004, 0x00000004, 0x00000004, 0x00000004; f32:i32 4
dcl_literal l23, 0x00000006, 0x00000006, 0x00000006, 0x00000006; f32:i32 6
dcl_literal l18, 0x00000010, 0x00000010, 0x00000010, 0x00000010; f32:i32 16
dcl_literal l25, 0x00000011, 0x00000011, 0x00000011, 0x00000011; f32:i32 17
dcl_literal l19, 0x00000020, 0x00000020, 0x00000020, 0x00000020; f32:i32 32
dcl_literal l20, 0x00000030, 0x00000030, 0x00000030, 0x00000030; f32:i32 48
dcl_literal l21, 0x00000040, 0x00000040, 0x00000040, 0x00000040; f32:i32 64
dcl_literal l22, 0x00000050, 0x00000050, 0x00000050, 0x00000050; f32:i32 80
dcl_literal l42, 0x0000005F, 0x0000005F, 0x0000005F, 0x0000005F; f32:i32 95
dcl_literal l13, 0x00000060, 0x00000060, 0x00000060, 0x00000060; f32:i32 96
dcl_literal l41, 0x0000006F, 0x0000006F, 0x0000006F, 0x0000006F; f32:i32 111
dcl_literal l14, 0x00000070, 0x00000070, 0x00000070, 0x00000070; f32:i32 112
dcl_literal l24, 0x00000071, 0x00000071, 0x00000071, 0x00000071; f32:i32 113
dcl_literal l30, 0x00000080, 0x00000080, 0x00000080, 0x00000080; f32:i32 128
dcl_literal l33, 0x000000C0, 0x000000C0, 0x000000C0, 0x000000C0; f32:i32 192
dcl_literal l17, 0x00000100, 0x00000100, 0x00000100, 0x00000100; f32:i32 256
dcl_literal l37, 0x00000140, 0x00000140, 0x00000140, 0x00000140; f32:i32 320
dcl_literal l39, 0x00000180, 0x00000180, 0x00000180, 0x00000180; f32:i32 384
dcl_literal l29, 0x00000440, 0x00000440, 0x00000440, 0x00000440; f32:i32 1088
dcl_literal l32, 0x00000880, 0x00000880, 0x00000880, 0x00000880; f32:i32 2176
dcl_literal l35, 0x00000CC0, 0x00000CC0, 0x00000CC0, 0x00000CC0; f32:i32 3264
dcl_literal l36, 0x00001100, 0x00001100, 0x00001100, 0x00001100; f32:i32 4352
dcl_literal l38, 0x00001540, 0x00001540, 0x00001540, 0x00001540; f32:i32 5440
dcl_literal l40, 0x00001980, 0x00001980, 0x00001980, 0x00001980; f32:i32 6528
dcl_literal l26, 0x00001C40, 0x00001C40, 0x00001C40, 0x00001C40; f32:i32 7232
dcl_literal l44, 0x00001DC0, 0x00001DC0, 0x00001DC0, 0x00001DC0; f32:i32 7616
dcl_literal l27, 0xFFFFFF00, 0xFFFFFF00, 0xFFFFFF00, 0xFFFFFF00; f32:i32 4294967040
dcl_literal l28, 0xFFFFFF40, 0xFFFFFF40, 0xFFFFFF40, 0xFFFFFF40; f32:i32 4294967104
dcl_literal l31, 0xFFFFFF80, 0xFFFFFF80, 0xFFFFFF80, 0xFFFFFF80; f32:i32 4294967168
dcl_literal l34, 0xFFFFFFC0, 0xFFFFFFC0, 0xFFFFFFC0, 0xFFFFFFC0; f32:i32 4294967232
dcl_cb cb1[11]
; Kernel arg setup: n
mov r1.x, cb1[0].x
; Kernel arg setup: m
mov r1.y, cb1[1].x
; Kernel arg setup: k
mov r1.z, cb1[2].x
; Kernel arg setup: alpha
mov r1.w, cb1[3].x
; Kernel arg setup: a
mov r2.x, cb1[4].x
; Kernel arg setup: lda
mov r2.y, cb1[5].x
; Kernel arg setup: b
mov r2.z, cb1[6].x
; Kernel arg setup: ldb
mov r2.w, cb1[7].x
; Kernel arg setup: beta
mov r3.x, cb1[8].x
; Kernel arg setup: c
mov r3.y, cb1[9].x
; Kernel arg setup: ldc
mov r3.z, cb1[10].x
call 1035 ; sgemmNN
ret
endfunc ; __OpenCL_sgemmNN_kernel
;ARGSTART:__OpenCL_sgemmNN_kernel
;version:3:0:98
;device:tahiti
;uniqueid:1024
;memory:uavprivate:0
;memory:hwregion:0
;memory:hwlocal:14848
;cws:16:16:1
;value:n:i32:1:1:0
;value:m:i32:1:1:16
;value:k:i32:1:1:32
;value:alpha:float:1:1:48
;pointer:a:float:1:1:64:uav:9:4:RW
;value:lda:i32:1:1:80
;pointer:b:float:1:1:96:uav:10:4:RO
;value:ldb:i32:1:1:112
;value:beta:float:1:1:128
;pointer:c:float:1:1:144:uav:11:4:RW
;value:ldc:i32:1:1:160
;function:1:1035
;privateid:8
;ARGEND:__OpenCL_sgemmNN_kernel
func 1035 ; sgemmNN                     ; @__OpenCL_sgemmNN_kernel
; BB#0:                                 ; %entry
	mov r65.x___, r1.z
	mov r65._y__, r1.y
	mov r65.__z_, r1.x
	mov r65.___w, l12
	ilt r65.___w, r65.x, r65.w
	mov r66, r1023.xyz0
	mov r67.x___, r66.y000
	mov r67._y__, l13
	imul r67.x___, r67.x, r67.y
	mov r66.x___, r66.x000
	mov r66._y__, l14
	imul r66.x___, r66.x, r66.y
	mov r68, r1022.xyz0
	mov r66._y__, r68.0y00
	mov r66.__z_, r68.00x0
	mov r66.___w, l15
	mov r67.__z_, r66.w
	mov r67.___w, r66.w
	mov r68.x___, r66.w
	mov r68._y__, r66.w
	mov r68.__z_, r66.w
	mov r68.___w, r66.w
	mov r69.x___, r66.w
	mov r69._y__, r66.w
	mov r69.__z_, r66.w
	mov r69.___w, r66.w
	mov r70.x___, r66.w
	mov r70._y__, r66.w
	mov r70.__z_, r66.w
	mov r70.___w, r66.w
	mov r71.x___, r66.w
	mov r71._y__, r66.w
	mov r71.__z_, r66.w
	mov r71.___w, r66.w
	mov r72.x___, r66.w
	mov r72._y__, r66.w
	mov r72.__z_, r66.w
	mov r72.___w, r66.w
	mov r73.x___, r66.w
	mov r73._y__, r66.w
	mov r73.__z_, r66.w
	mov r73.___w, r66.w
	mov r74.x___, r66.w
	mov r74._y__, r66.w
	mov r74.__z_, r66.w
	mov r74.___w, r66.w
	mov r75.x___, r66.w
	mov r75._y__, r66.w
	mov r75.__z_, r66.w
	mov r75.___w, r66.w
	mov r76.x___, r66.w
	mov r76._y__, r66.w
	mov r76.__z_, r66.w
	mov r76.___w, r66.w
	mov r77.x___, r66.w
	mov r77._y__, r66.w
	mov r77.__z_, r66.w
	if_logicalnz r65.w
	else
	mov r65.___w, l16
	ishl r68._y__, r66.y, r65.w
	iadd r67.__z_, r2.z, r68.y
	iadd r68._y__, r66.z, r67.x
	imul r68.__z_, r2.w, r68.y
	ishl r68.__z_, r68.z, r65.w
	iadd r77.___w, r67.z, r68.z
	imul r68.__z_, r66.y, r2.y
	iadd r68.__z_, r66.z, r68.z
	iadd r68.__z_, r68.z, r66.x
	ishl r68.__z_, r68.z, r65.w
	iadd r68.x___, r68.z, r2.x
	mov r78.x___, l17
	iadd r78._y__, r68.x, r78.x
	mov r68.x___, l18
	iadd r68.x___, r68.y, r68.x
	imul r68.x___, r2.w, r68.x
	ishl r68.x___, r68.x, r65.w
	iadd r78.__z_, r67.z, r68.x
	mov r68.x___, l19
	iadd r68.x___, r68.y, r68.x
	imul r68.x___, r2.w, r68.x
	ishl r68.x___, r68.x, r65.w
	iadd r78.___w, r67.z, r68.x
	mov r68.x___, l20
	iadd r68.x___, r68.y, r68.x
	imul r68.x___, r2.w, r68.x
	ishl r68.x___, r68.x, r65.w
	iadd r79.x___, r67.z, r68.x
	mov r79._y__, l21
	iadd r68.x___, r68.y, r79.y
	imul r68.x___, r2.w, r68.x
	ishl r68.x___, r68.x, r65.w
	iadd r79.__z_, r67.z, r68.x
	mov r68.x___, l22
	iadd r68.x___, r68.y, r68.x
	imul r68.x___, r2.w, r68.x
	ishl r68.x___, r68.x, r65.w
	iadd r79.___w, r67.z, r68.x
	iadd r68.x___, r68.y, r67.y
	imul r66.___w, r2.w, r68.x
	ishl r66.___w, r66.w, r65.w
	iadd r67._y__, r67.z, r66.w
	mov r66.___w, l23
	ishl r80.x___, r2.y, r66.w
	ishl r66.___w, r66.z, r65.w
	mov r80._y__, l15
	iadd r80.__z_, r80.y, r66.w
	mov r66.___w, l24
	imul r66.___w, r66.y, r66.w
	iadd r80.___w, r66.z, r66.w
	mov r66.___w, l25
	imul r67.__z_, r66.z, r66.w
	iadd r81.x___, r66.y, r67.z
	imul r66.___w, r66.y, r66.w
	ishl r66.___w, r66.w, r65.w
	mov r81._y__, l26
	iadd r81.__z_, r81.y, r66.w
	mov r66.___w, l15
	mov r81.___w, r80.y
	mov r67.__z_, r66.w
	mov r67.___w, r66.w
	mov r68.x___, r66.w
	mov r68._y__, r66.w
	mov r68.__z_, r66.w
	mov r68.___w, r66.w
	mov r69.x___, r66.w
	mov r69._y__, r66.w
	mov r69.__z_, r66.w
	mov r69.___w, r66.w
	mov r70.x___, r66.w
	mov r70._y__, r66.w
	mov r70.__z_, r66.w
	mov r70.___w, r66.w
	mov r71.x___, r66.w
	mov r71._y__, r66.w
	mov r71.__z_, r66.w
	mov r71.___w, r66.w
	mov r72.x___, r66.w
	mov r72._y__, r66.w
	mov r72.__z_, r66.w
	mov r72.___w, r66.w
	mov r73.x___, r66.w
	mov r73._y__, r66.w
	mov r73.__z_, r66.w
	mov r73.___w, r66.w
	mov r74.x___, r66.w
	mov r74._y__, r66.w
	mov r74.__z_, r66.w
	mov r74.___w, r66.w
	mov r75.x___, r66.w
	mov r75._y__, r66.w
	mov r75.__z_, r66.w
	mov r75.___w, r66.w
	mov r76.x___, r66.w
	mov r76._y__, r66.w
	mov r76.__z_, r66.w
	mov r76.___w, r66.w
	mov r77.x___, r66.w
	mov r77._y__, r66.w
	mov r77.__z_, r66.w
	whileloop
	ishl r82.x___, r80.w, r65.w
	iadd r82.x___, r80.y, r82.x
	mov r82._y__, l27
	iadd r82._y__, r78.y, r82.y
	mov r1010.x___, r82.y
	uav_raw_load_id(9) r1011.x___, r1010.x
	mov r82._y__, r1011.x
	mov r1011, r82.y
	mov r1010.x___, r82.x
	lds_store_id(1) r1010.x, r1011.x
	ishl r82._y__, r81.x, r65.w
	iadd r82._y__, r81.y, r82.y
	ishl r82.__z_, r81.w, r65.w
	iadd r82.___w, r77.w, r82.z
	mov r1010.x___, r82.w
	uav_raw_load_id(10)_cached r1011.x___, r1010.x
	mov r82.___w, r1011.x
	mov r1011, r82.w
	mov r1010.x___, r82.y
	lds_store_id(1) r1010.x, r1011.x
	iadd r82.___w, r82.x, r79.y
	mov r83.x___, l28
	iadd r83.x___, r78.y, r83.x
	mov r1010.x___, r83.x
	uav_raw_load_id(9) r1011.x___, r1010.x
	mov r83.x___, r1011.x
	mov r1011, r83.x
	mov r1010.x___, r82.w
	lds_store_id(1) r1010.x, r1011.x
	mov r82.___w, l29
	iadd r83.x___, r82.y, r82.w
	iadd r83._y__, r78.z, r82.z
	mov r1010.x___, r83.y
	uav_raw_load_id(10)_cached r1011.x___, r1010.x
	mov r83._y__, r1011.x
	mov r1011, r83.y
	mov r1010.x___, r83.x
	lds_store_id(1) r1010.x, r1011.x
	mov r83.x___, l30
	iadd r83._y__, r82.x, r83.x
	mov r83.__z_, l31
	iadd r83.__z_, r78.y, r83.z
	mov r1010.x___, r83.z
	uav_raw_load_id(9) r1011.x___, r1010.x
	mov r83.__z_, r1011.x
	mov r1011, r83.z
	mov r1010.x___, r83.y
	lds_store_id(1) r1010.x, r1011.x
	mov r83._y__, l32
	iadd r83.__z_, r82.y, r83.y
	iadd r83.___w, r78.w, r82.z
	mov r1010.x___, r83.w
	uav_raw_load_id(10)_cached r1011.x___, r1010.x
	mov r83.___w, r1011.x
	mov r1011, r83.w
	mov r1010.x___, r83.z
	lds_store_id(1) r1010.x, r1011.x
	mov r83.__z_, l33
	iadd r83.___w, r82.x, r83.z
	mov r84.x___, l34
	iadd r84.x___, r78.y, r84.x
	mov r1010.x___, r84.x
	uav_raw_load_id(9) r1011.x___, r1010.x
	mov r84.x___, r1011.x
	mov r1011, r84.x
	mov r1010.x___, r83.w
	lds_store_id(1) r1010.x, r1011.x
	mov r83.___w, l35
	iadd r84.x___, r82.y, r83.w
	iadd r84._y__, r79.x, r82.z
	mov r1010.x___, r84.y
	uav_raw_load_id(10)_cached r1011.x___, r1010.x
	mov r84._y__, r1011.x
	mov r1011, r84.y
	mov r1010.x___, r84.x
	lds_store_id(1) r1010.x, r1011.x
	iadd r84.x___, r82.x, r78.x
	mov r1010.x___, r78.y
	uav_raw_load_id(9) r1011.x___, r1010.x
	mov r84._y__, r1011.x
	mov r1011, r84.y
	mov r1010.x___, r84.x
	lds_store_id(1) r1010.x, r1011.x
	mov r84.x___, l36
	iadd r84._y__, r82.y, r84.x
	iadd r84.__z_, r79.z, r82.z
	mov r1010.x___, r84.z
	uav_raw_load_id(10)_cached r1011.x___, r1010.x
	mov r84.__z_, r1011.x
	mov r1011, r84.z
	mov r1010.x___, r84.y
	lds_store_id(1) r1010.x, r1011.x
	mov r84._y__, l37
	iadd r84.__z_, r82.x, r84.y
	iadd r84.___w, r78.y, r79.y
	mov r1010.x___, r84.w
	uav_raw_load_id(9) r1011.x___, r1010.x
	mov r84.___w, r1011.x
	mov r1011, r84.w
	mov r1010.x___, r84.z
	lds_store_id(1) r1010.x, r1011.x
	mov r84.__z_, l38
	iadd r84.___w, r82.y, r84.z
	iadd r85.x___, r79.w, r82.z
	mov r1010.x___, r85.x
	uav_raw_load_id(10)_cached r1011.x___, r1010.x
	mov r85.x___, r1011.x
	mov r1011, r85.x
	mov r1010.x___, r84.w
	lds_store_id(1) r1010.x, r1011.x
	mov r84.___w, l39
	iadd r82.x___, r82.x, r84.w
	iadd r85.x___, r78.y, r83.x
	mov r1010.x___, r85.x
	uav_raw_load_id(9) r1011.x___, r1010.x
	mov r85.x___, r1011.x
	mov r1011, r85.x
	mov r1010.x___, r82.x
	lds_store_id(1) r1010.x, r1011.x
	mov r82.x___, l40
	iadd r82.x___, r82.y, r82.x
	iadd r82._y__, r67.y, r82.z
	mov r1010.x___, r82.y
	uav_raw_load_id(10)_cached r1011.x___, r1010.x
	mov r82._y__, r1011.x
	mov r1011, r82.y
	mov r1010.x___, r82.x
	lds_store_id(1) r1010.x, r1011.x
	mov r82.x___, l12
	fence_threads_lds
	mov r82._y__, r80.y
	whileloop
	mov r82.__z_, l24
	imul r82.__z_, r82.y, r82.z
	mov r85.x___, l16
	ishl r82.__z_, r82.z, r85.x
	iadd r82.__z_, r80.z, r82.z
	iadd r85._y__, r82.z, r84.w
	mov r1010.x___, r85.y
	lds_load_id(1) r1011.x, r1010.x
	mov r85._y__, r1011.x
	iadd r85.__z_, r82.z, r84.y
	mov r1010.x___, r85.z
	lds_load_id(1) r1011.x, r1010.x
	mov r85.__z_, r1011.x
	mov r85.___w, l17
	iadd r85.___w, r82.z, r85.w
	mov r1010.x___, r85.w
	lds_load_id(1) r1011.x, r1010.x
	mov r85.___w, r1011.x
	iadd r86.x___, r82.z, r83.z
	mov r1010.x___, r86.x
	lds_load_id(1) r1011.x, r1010.x
	mov r86.x___, r1011.x
	iadd r86._y__, r82.z, r83.x
	mov r1010.x___, r86.y
	lds_load_id(1) r1011.x, r1010.x
	mov r86._y__, r1011.x
	mov r86.__z_, l21
	iadd r86.__z_, r82.z, r86.z
	mov r1010.x___, r86.z
	lds_load_id(1) r1011.x, r1010.x
	mov r86.__z_, r1011.x
	ishl r85.x___, r82.y, r85.x
	iadd r85.x___, r81.z, r85.x
	iadd r86.___w, r85.x, r84.z
	mov r1010.x___, r86.w
	lds_load_id(1) r1011.x, r1010.x
	mov r86.___w, r1011.x
	iadd r87.x___, r85.x, r84.x
	mov r1010.x___, r87.x
	lds_load_id(1) r1011.x, r1010.x
	mov r87.x___, r1011.x
	iadd r87._y__, r85.x, r83.w
	mov r1010.x___, r87.y
	lds_load_id(1) r1011.x, r1010.x
	mov r87._y__, r1011.x
	iadd r87.__z_, r85.x, r83.y
	mov r1010.x___, r87.z
	lds_load_id(1) r1011.x, r1010.x
	mov r87.__z_, r1011.x
	iadd r87.___w, r85.x, r82.w
	mov r1010.x___, r87.w
	lds_load_id(1) r1011.x, r1010.x
	mov r87.___w, r1011.x
	mov r1010.x___, r85.x
	lds_load_id(1) r1011.x, r1010.x
	mov r85.x___, r1011.x
	mov r1010.x___, r82.z
	lds_load_id(1) r1011.x, r1010.x
	mov r82.__z_, r1011.x
	mov r1.x___, r82.z
	mov r1._y__, r85.x
	mov r1.__z_, r73.x
	mcall(140)(r1.x),(r1.x, r1.y, r1.z) ;__hwfma_f32
	mov r73.x___, r1.x
	mov r1.x___, r82.z
	mov r1._y__, r87.w
	mov r1.__z_, r73.y
	mcall(140)(r1.x),(r1.x, r1.y, r1.z) ;__hwfma_f32
	mov r73._y__, r1.x
	mov r1.x___, r82.z
	mov r1._y__, r87.z
	mov r1.__z_, r73.z
	mcall(140)(r1.x),(r1.x, r1.y, r1.z) ;__hwfma_f32
	mov r73.__z_, r1.x
	mov r1.x___, r82.z
	mov r1._y__, r87.y
	mov r1.__z_, r73.w
	mcall(140)(r1.x),(r1.x, r1.y, r1.z) ;__hwfma_f32
	mov r73.___w, r1.x
	mov r1.x___, r82.z
	mov r1._y__, r87.x
	mov r1.__z_, r74.x
	mcall(140)(r1.x),(r1.x, r1.y, r1.z) ;__hwfma_f32
	mov r74.x___, r1.x
	mov r1.x___, r82.z
	mov r1._y__, r86.w
	mov r1.__z_, r74.y
	mcall(140)(r1.x),(r1.x, r1.y, r1.z) ;__hwfma_f32
	mov r74._y__, r1.x
	mov r1.x___, r86.z
	mov r1._y__, r85.x
	mov r1.__z_, r74.z
	mcall(140)(r1.x),(r1.x, r1.y, r1.z) ;__hwfma_f32
	mov r74.__z_, r1.x
	mov r1.x___, r86.z
	mov r1._y__, r87.w
	mov r1.__z_, r74.w
	mcall(140)(r1.x),(r1.x, r1.y, r1.z) ;__hwfma_f32
	mov r74.___w, r1.x
	mov r1.x___, r86.z
	mov r1._y__, r87.z
	mov r1.__z_, r75.x
	mcall(140)(r1.x),(r1.x, r1.y, r1.z) ;__hwfma_f32
	mov r75.x___, r1.x
	mov r1.x___, r86.z
	mov r1._y__, r87.y
	mov r1.__z_, r75.y
	mcall(140)(r1.x),(r1.x, r1.y, r1.z) ;__hwfma_f32
	mov r75._y__, r1.x
	mov r1.x___, r86.z
	mov r1._y__, r87.x
	mov r1.__z_, r75.z
	mcall(140)(r1.x),(r1.x, r1.y, r1.z) ;__hwfma_f32
	mov r75.__z_, r1.x
	mov r1.x___, r86.z
	mov r1._y__, r86.w
	mov r1.__z_, r75.w
	mcall(140)(r1.x),(r1.x, r1.y, r1.z) ;__hwfma_f32
	mov r75.___w, r1.x
	mov r1.x___, r86.y
	mov r1._y__, r85.x
	mov r1.__z_, r76.x
	mcall(140)(r1.x),(r1.x, r1.y, r1.z) ;__hwfma_f32
	mov r76.x___, r1.x
	mov r1.x___, r86.y
	mov r1._y__, r87.w
	mov r1.__z_, r76.y
	mcall(140)(r1.x),(r1.x, r1.y, r1.z) ;__hwfma_f32
	mov r76._y__, r1.x
	mov r1.x___, r86.y
	mov r1._y__, r87.z
	mov r1.__z_, r76.z
	mcall(140)(r1.x),(r1.x, r1.y, r1.z) ;__hwfma_f32
	mov r76.__z_, r1.x
	mov r1.x___, r86.y
	mov r1._y__, r87.y
	mov r1.__z_, r76.w
	mcall(140)(r1.x),(r1.x, r1.y, r1.z) ;__hwfma_f32
	mov r76.___w, r1.x
	mov r1.x___, r86.y
	mov r1._y__, r87.x
	mov r1.__z_, r77.x
	mcall(140)(r1.x),(r1.x, r1.y, r1.z) ;__hwfma_f32
	mov r77.x___, r1.x
	mov r1.x___, r86.y
	mov r1._y__, r86.w
	mov r1.__z_, r77.y
	mcall(140)(r1.x),(r1.x, r1.y, r1.z) ;__hwfma_f32
	mov r77._y__, r1.x
	mov r1.x___, r86.x
	mov r1._y__, r85.x
	mov r1.__z_, r77.z
	mcall(140)(r1.x),(r1.x, r1.y, r1.z) ;__hwfma_f32
	mov r77.__z_, r1.x
	mov r1.x___, r86.x
	mov r1._y__, r87.w
	mov r1.__z_, r72.w
	mcall(140)(r1.x),(r1.x, r1.y, r1.z) ;__hwfma_f32
	mov r72.___w, r1.x
	mov r1.x___, r86.x
	mov r1._y__, r87.z
	mov r1.__z_, r72.z
	mcall(140)(r1.x),(r1.x, r1.y, r1.z) ;__hwfma_f32
	mov r72.__z_, r1.x
	mov r1.x___, r86.x
	mov r1._y__, r87.y
	mov r1.__z_, r72.y
	mcall(140)(r1.x),(r1.x, r1.y, r1.z) ;__hwfma_f32
	mov r72._y__, r1.x
	mov r1.x___, r86.x
	mov r1._y__, r87.x
	mov r1.__z_, r72.x
	mcall(140)(r1.x),(r1.x, r1.y, r1.z) ;__hwfma_f32
	mov r72.x___, r1.x
	mov r1.x___, r86.x
	mov r1._y__, r86.w
	mov r1.__z_, r71.w
	mcall(140)(r1.x),(r1.x, r1.y, r1.z) ;__hwfma_f32
	mov r71.___w, r1.x
	mov r1.x___, r85.w
	mov r1._y__, r85.x
	mov r1.__z_, r71.z
	mcall(140)(r1.x),(r1.x, r1.y, r1.z) ;__hwfma_f32
	mov r71.__z_, r1.x
	mov r1.x___, r85.w
	mov r1._y__, r87.w
	mov r1.__z_, r71.y
	mcall(140)(r1.x),(r1.x, r1.y, r1.z) ;__hwfma_f32
	mov r71._y__, r1.x
	mov r1.x___, r85.w
	mov r1._y__, r87.z
	mov r1.__z_, r71.x
	mcall(140)(r1.x),(r1.x, r1.y, r1.z) ;__hwfma_f32
	mov r71.x___, r1.x
	mov r1.x___, r85.w
	mov r1._y__, r87.y
	mov r1.__z_, r70.w
	mcall(140)(r1.x),(r1.x, r1.y, r1.z) ;__hwfma_f32
	mov r70.___w, r1.x
	mov r1.x___, r85.w
	mov r1._y__, r87.x
	mov r1.__z_, r70.z
	mcall(140)(r1.x),(r1.x, r1.y, r1.z) ;__hwfma_f32
	mov r70.__z_, r1.x
	mov r1.x___, r85.w
	mov r1._y__, r86.w
	mov r1.__z_, r70.y
	mcall(140)(r1.x),(r1.x, r1.y, r1.z) ;__hwfma_f32
	mov r70._y__, r1.x
	mov r1.x___, r85.z
	mov r1._y__, r85.x
	mov r1.__z_, r70.x
	mcall(140)(r1.x),(r1.x, r1.y, r1.z) ;__hwfma_f32
	mov r70.x___, r1.x
	mov r1.x___, r85.z
	mov r1._y__, r87.w
	mov r1.__z_, r69.w
	mcall(140)(r1.x),(r1.x, r1.y, r1.z) ;__hwfma_f32
	mov r69.___w, r1.x
	mov r1.x___, r85.z
	mov r1._y__, r87.z
	mov r1.__z_, r69.z
	mcall(140)(r1.x),(r1.x, r1.y, r1.z) ;__hwfma_f32
	mov r69.__z_, r1.x
	mov r1.x___, r85.z
	mov r1._y__, r87.y
	mov r1.__z_, r69.y
	mcall(140)(r1.x),(r1.x, r1.y, r1.z) ;__hwfma_f32
	mov r69._y__, r1.x
	mov r1.x___, r85.z
	mov r1._y__, r87.x
	mov r1.__z_, r69.x
	mcall(140)(r1.x),(r1.x, r1.y, r1.z) ;__hwfma_f32
	mov r69.x___, r1.x
	mov r1.x___, r85.z
	mov r1._y__, r86.w
	mov r1.__z_, r68.w
	mcall(140)(r1.x),(r1.x, r1.y, r1.z) ;__hwfma_f32
	mov r68.___w, r1.x
	mov r1.x___, r85.y
	mov r1._y__, r85.x
	mov r1.__z_, r68.z
	mcall(140)(r1.x),(r1.x, r1.y, r1.z) ;__hwfma_f32
	mov r68.__z_, r1.x
	mov r1.x___, r85.y
	mov r1._y__, r87.w
	mov r1.__z_, r68.y
	mcall(140)(r1.x),(r1.x, r1.y, r1.z) ;__hwfma_f32
	mov r68._y__, r1.x
	mov r1.x___, r85.y
	mov r1._y__, r87.z
	mov r1.__z_, r68.x
	mcall(140)(r1.x),(r1.x, r1.y, r1.z) ;__hwfma_f32
	mov r68.x___, r1.x
	mov r1.x___, r85.y
	mov r1._y__, r87.y
	mov r1.__z_, r67.w
	mcall(140)(r1.x),(r1.x, r1.y, r1.z) ;__hwfma_f32
	mov r67.___w, r1.x
	mov r1.x___, r85.y
	mov r1._y__, r87.x
	mov r1.__z_, r67.z
	mcall(140)(r1.x),(r1.x, r1.y, r1.z) ;__hwfma_f32
	mov r67.__z_, r1.x
	mov r1.x___, r85.y
	mov r1._y__, r86.w
	mov r1.__z_, r66.w
	mcall(140)(r1.x),(r1.x, r1.y, r1.z) ;__hwfma_f32
	mov r66.___w, r1.x
	iadd r82._y__, r82.y, r82.x
	mov r82.__z_, l18
	ieq r85.x___, r82.y, r82.z
	break_logicalnz r85.x
	endloop
	iadd r78._y__, r78.y, r80.x
	iadd r81.___w, r81.w, r82.z
	ilt r82.x___, r81.w, r65.x
	mov r82._y__, l12
	fence_threads_lds
	break_logicalz r82.x
	endloop
	endif
	mov r65.x___, l41
	iadd r65.x___, r66.x, r65.x
	ilt r65.x___, r65.x, r65.y
	if_logicalnz r65.x
	mov r65.x___, l42
	iadd r65.x___, r67.x, r65.x
	ilt r65.x___, r65.x, r65.z
	if_logicalnz r65.x
	iadd r66._y__, r67.x, r66.y
	imul r66._y__, r66.y, r3.z
	iadd r66.x___, r66.y, r66.x
	mul_ieee r66._y__, r73.x, r1.w
	iadd r67.x___, r66.x, r66.z
	mov r67._y__, l16
	ishl r67.x___, r67.x, r67.y
	iadd r67.x___, r3.y, r67.x
	mov r1010.x___, r67.x
	uav_raw_load_id(11) r1011.x___, r1010.x
	mov r73.x___, r1011.x
	mul_ieee r73.x___, r73.x, r3.x
	add r66._y__, r66.y, r73.x
	mov r1011, r66.y
	mov r1010.x___, r67.x
	uav_raw_store_id(11) mem0.x___, r1010.x, r1011.x
	mul_ieee r66._y__, r74.z, r1.w
	mov r67.x___, l18
	iadd r67.x___, r66.z, r67.x
	iadd r73.x___, r66.x, r67.x
	ishl r73.x___, r73.x, r67.y
	iadd r73.x___, r3.y, r73.x
	mov r1010.x___, r73.x
	uav_raw_load_id(11) r1011.x___, r1010.x
	mov r74.__z_, r1011.x
	mul_ieee r74.__z_, r74.z, r3.x
	add r66._y__, r66.y, r74.z
	mov r1011, r66.y
	mov r1010.x___, r73.x
	uav_raw_store_id(11) mem0.x___, r1010.x, r1011.x
	mul_ieee r66._y__, r76.x, r1.w
	mov r73.x___, l19
	iadd r73.x___, r66.z, r73.x
	iadd r74.__z_, r66.x, r73.x
	ishl r74.__z_, r74.z, r67.y
	iadd r74.__z_, r3.y, r74.z
	mov r1010.x___, r74.z
	uav_raw_load_id(11) r1011.x___, r1010.x
	mov r76.x___, r1011.x
	mul_ieee r76.x___, r76.x, r3.x
	add r66._y__, r66.y, r76.x
	mov r1011, r66.y
	mov r1010.x___, r74.z
	uav_raw_store_id(11) mem0.x___, r1010.x, r1011.x
	mul_ieee r66._y__, r77.z, r1.w
	mov r74.__z_, l20
	iadd r74.__z_, r66.z, r74.z
	iadd r76.x___, r66.x, r74.z
	ishl r76.x___, r76.x, r67.y
	iadd r76.x___, r3.y, r76.x
	mov r1010.x___, r76.x
	uav_raw_load_id(11) r1011.x___, r1010.x
	mov r77.__z_, r1011.x
	mul_ieee r77.__z_, r77.z, r3.x
	add r66._y__, r66.y, r77.z
	mov r1011, r66.y
	mov r1010.x___, r76.x
	uav_raw_store_id(11) mem0.x___, r1010.x, r1011.x
	mul_ieee r66._y__, r71.z, r1.w
	mov r71.__z_, l21
	iadd r71.__z_, r66.z, r71.z
	iadd r76.x___, r66.x, r71.z
	ishl r76.x___, r76.x, r67.y
	iadd r76.x___, r3.y, r76.x
	mov r1010.x___, r76.x
	uav_raw_load_id(11) r1011.x___, r1010.x
	mov r77.__z_, r1011.x
	mul_ieee r77.__z_, r77.z, r3.x
	add r66._y__, r66.y, r77.z
	mov r1011, r66.y
	mov r1010.x___, r76.x
	uav_raw_store_id(11) mem0.x___, r1010.x, r1011.x
	mul_ieee r66._y__, r70.x, r1.w
	mov r70.x___, l22
	iadd r70.x___, r66.z, r70.x
	iadd r76.x___, r66.x, r70.x
	ishl r76.x___, r76.x, r67.y
	iadd r76.x___, r3.y, r76.x
	mov r1010.x___, r76.x
	uav_raw_load_id(11) r1011.x___, r1010.x
	mov r77.__z_, r1011.x
	mul_ieee r77.__z_, r77.z, r3.x
	add r66._y__, r66.y, r77.z
	mov r1011, r66.y
	mov r1010.x___, r76.x
	uav_raw_store_id(11) mem0.x___, r1010.x, r1011.x
	mul_ieee r66._y__, r68.z, r1.w
	mov r68.__z_, l13
	iadd r68.__z_, r66.z, r68.z
	iadd r76.x___, r66.x, r68.z
	ishl r76.x___, r76.x, r67.y
	iadd r76.x___, r3.y, r76.x
	mov r1010.x___, r76.x
	uav_raw_load_id(11) r1011.x___, r1010.x
	mov r77.__z_, r1011.x
	mul_ieee r77.__z_, r77.z, r3.x
	add r66._y__, r66.y, r77.z
	mov r1011, r66.y
	mov r1010.x___, r76.x
	uav_raw_store_id(11) mem0.x___, r1010.x, r1011.x
	mul_ieee r66._y__, r73.y, r1.w
	mov r73._y__, l43
	ishl r65.x___, r3.z, r73.y
	iadd r66.x___, r66.x, r65.x
	iadd r73._y__, r66.x, r66.z
	ishl r73._y__, r73.y, r67.y
	iadd r73._y__, r3.y, r73.y
	mov r1010.x___, r73.y
	uav_raw_load_id(11) r1011.x___, r1010.x
	mov r76.x___, r1011.x
	mul_ieee r76.x___, r76.x, r3.x
	add r66._y__, r66.y, r76.x
	mov r1011, r66.y
	mov r1010.x___, r73.y
	uav_raw_store_id(11) mem0.x___, r1010.x, r1011.x
	iadd r66._y__, r66.x, r67.x
	ishl r66._y__, r66.y, r67.y
	iadd r66._y__, r3.y, r66.y
	mov r1010.x___, r66.y
	uav_raw_load_id(11) r1011.x___, r1010.x
	mov r73._y__, r1011.x
	mul_ieee r73._y__, r73.y, r3.x
	mul_ieee r74.___w, r74.w, r1.w
	add r73._y__, r74.w, r73.y
	mov r1011, r73.y
	mov r1010.x___, r66.y
	uav_raw_store_id(11) mem0.x___, r1010.x, r1011.x
	iadd r66._y__, r66.x, r73.x
	ishl r66._y__, r66.y, r67.y
	iadd r66._y__, r3.y, r66.y
	mov r1010.x___, r66.y
	uav_raw_load_id(11) r1011.x___, r1010.x
	mov r73._y__, r1011.x
	mul_ieee r73._y__, r73.y, r3.x
	mul_ieee r74.___w, r76.y, r1.w
	add r73._y__, r74.w, r73.y
	mov r1011, r73.y
	mov r1010.x___, r66.y
	uav_raw_store_id(11) mem0.x___, r1010.x, r1011.x
	iadd r66._y__, r66.x, r74.z
	ishl r66._y__, r66.y, r67.y
	iadd r66._y__, r3.y, r66.y
	mov r1010.x___, r66.y
	uav_raw_load_id(11) r1011.x___, r1010.x
	mov r73._y__, r1011.x
	mul_ieee r73._y__, r73.y, r3.x
	mul_ieee r72.___w, r72.w, r1.w
	add r72.___w, r72.w, r73.y
	mov r1011, r72.w
	mov r1010.x___, r66.y
	uav_raw_store_id(11) mem0.x___, r1010.x, r1011.x
	iadd r66._y__, r66.x, r71.z
	ishl r66._y__, r66.y, r67.y
	iadd r66._y__, r3.y, r66.y
	mov r1010.x___, r66.y
	uav_raw_load_id(11) r1011.x___, r1010.x
	mov r72.___w, r1011.x
	mul_ieee r72.___w, r72.w, r3.x
	mul_ieee r71._y__, r71.y, r1.w
	add r71._y__, r71.y, r72.w
	mov r1011, r71.y
	mov r1010.x___, r66.y
	uav_raw_store_id(11) mem0.x___, r1010.x, r1011.x
	iadd r66._y__, r66.x, r70.x
	ishl r66._y__, r66.y, r67.y
	iadd r66._y__, r3.y, r66.y
	mov r1010.x___, r66.y
	uav_raw_load_id(11) r1011.x___, r1010.x
	mov r71._y__, r1011.x
	mul_ieee r71._y__, r71.y, r3.x
	mul_ieee r69.___w, r69.w, r1.w
	add r69.___w, r69.w, r71.y
	mov r1011, r69.w
	mov r1010.x___, r66.y
	uav_raw_store_id(11) mem0.x___, r1010.x, r1011.x
	iadd r66._y__, r66.x, r68.z
	ishl r66._y__, r66.y, r67.y
	iadd r66._y__, r3.y, r66.y
	mov r1010.x___, r66.y
	uav_raw_load_id(11) r1011.x___, r1010.x
	mov r69.___w, r1011.x
	mul_ieee r69.___w, r69.w, r3.x
	mul_ieee r68._y__, r68.y, r1.w
	add r68._y__, r68.y, r69.w
	mov r1011, r68.y
	mov r1010.x___, r66.y
	uav_raw_store_id(11) mem0.x___, r1010.x, r1011.x
	iadd r66.x___, r66.x, r65.x
	iadd r66._y__, r66.x, r66.z
	ishl r66._y__, r66.y, r67.y
	iadd r66._y__, r3.y, r66.y
	mov r1010.x___, r66.y
	uav_raw_load_id(11) r1011.x___, r1010.x
	mov r68._y__, r1011.x
	mul_ieee r68._y__, r68.y, r3.x
	mul_ieee r69.___w, r73.z, r1.w
	add r68._y__, r69.w, r68.y
	mov r1011, r68.y
	mov r1010.x___, r66.y
	uav_raw_store_id(11) mem0.x___, r1010.x, r1011.x
	iadd r66._y__, r66.x, r67.x
	ishl r66._y__, r66.y, r67.y
	iadd r66._y__, r3.y, r66.y
	mov r1010.x___, r66.y
	uav_raw_load_id(11) r1011.x___, r1010.x
	mov r68._y__, r1011.x
	mul_ieee r68._y__, r68.y, r3.x
	mul_ieee r69.___w, r75.x, r1.w
	add r68._y__, r69.w, r68.y
	mov r1011, r68.y
	mov r1010.x___, r66.y
	uav_raw_store_id(11) mem0.x___, r1010.x, r1011.x
	iadd r66._y__, r66.x, r73.x
	ishl r66._y__, r66.y, r67.y
	iadd r66._y__, r3.y, r66.y
	mov r1010.x___, r66.y
	uav_raw_load_id(11) r1011.x___, r1010.x
	mov r68._y__, r1011.x
	mul_ieee r68._y__, r68.y, r3.x
	mul_ieee r69.___w, r76.z, r1.w
	add r68._y__, r69.w, r68.y
	mov r1011, r68.y
	mov r1010.x___, r66.y
	uav_raw_store_id(11) mem0.x___, r1010.x, r1011.x
	iadd r66._y__, r66.x, r74.z
	ishl r66._y__, r66.y, r67.y
	iadd r66._y__, r3.y, r66.y
	mov r1010.x___, r66.y
	uav_raw_load_id(11) r1011.x___, r1010.x
	mov r68._y__, r1011.x
	mul_ieee r68._y__, r68.y, r3.x
	mul_ieee r69.___w, r72.z, r1.w
	add r68._y__, r69.w, r68.y
	mov r1011, r68.y
	mov r1010.x___, r66.y
	uav_raw_store_id(11) mem0.x___, r1010.x, r1011.x
	iadd r66._y__, r66.x, r71.z
	ishl r66._y__, r66.y, r67.y
	iadd r66._y__, r3.y, r66.y
	mov r1010.x___, r66.y
	uav_raw_load_id(11) r1011.x___, r1010.x
	mov r68._y__, r1011.x
	mul_ieee r68._y__, r68.y, r3.x
	mul_ieee r69.___w, r71.x, r1.w
	add r68._y__, r69.w, r68.y
	mov r1011, r68.y
	mov r1010.x___, r66.y
	uav_raw_store_id(11) mem0.x___, r1010.x, r1011.x
	iadd r66._y__, r66.x, r70.x
	ishl r66._y__, r66.y, r67.y
	iadd r66._y__, r3.y, r66.y
	mov r1010.x___, r66.y
	uav_raw_load_id(11) r1011.x___, r1010.x
	mov r68._y__, r1011.x
	mul_ieee r68._y__, r68.y, r3.x
	mul_ieee r69.__z_, r69.z, r1.w
	add r68._y__, r69.z, r68.y
	mov r1011, r68.y
	mov r1010.x___, r66.y
	uav_raw_store_id(11) mem0.x___, r1010.x, r1011.x
	iadd r66._y__, r66.x, r68.z
	ishl r66._y__, r66.y, r67.y
	iadd r66._y__, r3.y, r66.y
	mov r1010.x___, r66.y
	uav_raw_load_id(11) r1011.x___, r1010.x
	mov r68._y__, r1011.x
	mul_ieee r68._y__, r68.y, r3.x
	mul_ieee r68.x___, r68.x, r1.w
	add r68.x___, r68.x, r68.y
	mov r1011, r68.x
	mov r1010.x___, r66.y
	uav_raw_store_id(11) mem0.x___, r1010.x, r1011.x
	iadd r66.x___, r66.x, r65.x
	iadd r66._y__, r66.x, r66.z
	ishl r66._y__, r66.y, r67.y
	iadd r66._y__, r3.y, r66.y
	mov r1010.x___, r66.y
	uav_raw_load_id(11) r1011.x___, r1010.x
	mov r68.x___, r1011.x
	mul_ieee r68.x___, r68.x, r3.x
	mul_ieee r68._y__, r73.w, r1.w
	add r68.x___, r68.y, r68.x
	mov r1011, r68.x
	mov r1010.x___, r66.y
	uav_raw_store_id(11) mem0.x___, r1010.x, r1011.x
	iadd r66._y__, r66.x, r67.x
	ishl r66._y__, r66.y, r67.y
	iadd r66._y__, r3.y, r66.y
	mov r1010.x___, r66.y
	uav_raw_load_id(11) r1011.x___, r1010.x
	mov r68.x___, r1011.x
	mul_ieee r68.x___, r68.x, r3.x
	mul_ieee r68._y__, r75.y, r1.w
	add r68.x___, r68.y, r68.x
	mov r1011, r68.x
	mov r1010.x___, r66.y
	uav_raw_store_id(11) mem0.x___, r1010.x, r1011.x
	iadd r66._y__, r66.x, r73.x
	ishl r66._y__, r66.y, r67.y
	iadd r66._y__, r3.y, r66.y
	mov r1010.x___, r66.y
	uav_raw_load_id(11) r1011.x___, r1010.x
	mov r68.x___, r1011.x
	mul_ieee r68.x___, r68.x, r3.x
	mul_ieee r68._y__, r76.w, r1.w
	add r68.x___, r68.y, r68.x
	mov r1011, r68.x
	mov r1010.x___, r66.y
	uav_raw_store_id(11) mem0.x___, r1010.x, r1011.x
	iadd r66._y__, r66.x, r74.z
	ishl r66._y__, r66.y, r67.y
	iadd r66._y__, r3.y, r66.y
	mov r1010.x___, r66.y
	uav_raw_load_id(11) r1011.x___, r1010.x
	mov r68.x___, r1011.x
	mul_ieee r68.x___, r68.x, r3.x
	mul_ieee r68._y__, r72.y, r1.w
	add r68.x___, r68.y, r68.x
	mov r1011, r68.x
	mov r1010.x___, r66.y
	uav_raw_store_id(11) mem0.x___, r1010.x, r1011.x
	iadd r66._y__, r66.x, r71.z
	ishl r66._y__, r66.y, r67.y
	iadd r66._y__, r3.y, r66.y
	mov r1010.x___, r66.y
	uav_raw_load_id(11) r1011.x___, r1010.x
	mov r68.x___, r1011.x
	mul_ieee r68.x___, r68.x, r3.x
	mul_ieee r68._y__, r70.w, r1.w
	add r68.x___, r68.y, r68.x
	mov r1011, r68.x
	mov r1010.x___, r66.y
	uav_raw_store_id(11) mem0.x___, r1010.x, r1011.x
	iadd r66._y__, r66.x, r70.x
	ishl r66._y__, r66.y, r67.y
	iadd r66._y__, r3.y, r66.y
	mov r1010.x___, r66.y
	uav_raw_load_id(11) r1011.x___, r1010.x
	mov r68.x___, r1011.x
	mul_ieee r68.x___, r68.x, r3.x
	mul_ieee r68._y__, r69.y, r1.w
	add r68.x___, r68.y, r68.x
	mov r1011, r68.x
	mov r1010.x___, r66.y
	uav_raw_store_id(11) mem0.x___, r1010.x, r1011.x
	iadd r66._y__, r66.x, r68.z
	ishl r66._y__, r66.y, r67.y
	iadd r66._y__, r3.y, r66.y
	mov r1010.x___, r66.y
	uav_raw_load_id(11) r1011.x___, r1010.x
	mov r68.x___, r1011.x
	mul_ieee r68.x___, r68.x, r3.x
	mul_ieee r67.___w, r67.w, r1.w
	add r67.___w, r67.w, r68.x
	mov r1011, r67.w
	mov r1010.x___, r66.y
	uav_raw_store_id(11) mem0.x___, r1010.x, r1011.x
	iadd r66.x___, r66.x, r65.x
	iadd r66._y__, r66.x, r66.z
	ishl r66._y__, r66.y, r67.y
	iadd r66._y__, r3.y, r66.y
	mov r1010.x___, r66.y
	uav_raw_load_id(11) r1011.x___, r1010.x
	mov r67.___w, r1011.x
	mul_ieee r67.___w, r67.w, r3.x
	mul_ieee r68.x___, r74.x, r1.w
	add r67.___w, r68.x, r67.w
	mov r1011, r67.w
	mov r1010.x___, r66.y
	uav_raw_store_id(11) mem0.x___, r1010.x, r1011.x
	iadd r66._y__, r66.x, r67.x
	ishl r66._y__, r66.y, r67.y
	iadd r66._y__, r3.y, r66.y
	mov r1010.x___, r66.y
	uav_raw_load_id(11) r1011.x___, r1010.x
	mov r67.___w, r1011.x
	mul_ieee r67.___w, r67.w, r3.x
	mul_ieee r68.x___, r75.z, r1.w
	add r67.___w, r68.x, r67.w
	mov r1011, r67.w
	mov r1010.x___, r66.y
	uav_raw_store_id(11) mem0.x___, r1010.x, r1011.x
	iadd r66._y__, r66.x, r73.x
	ishl r66._y__, r66.y, r67.y
	iadd r66._y__, r3.y, r66.y
	mov r1010.x___, r66.y
	uav_raw_load_id(11) r1011.x___, r1010.x
	mov r67.___w, r1011.x
	mul_ieee r67.___w, r67.w, r3.x
	mul_ieee r68.x___, r77.x, r1.w
	add r67.___w, r68.x, r67.w
	mov r1011, r67.w
	mov r1010.x___, r66.y
	uav_raw_store_id(11) mem0.x___, r1010.x, r1011.x
	iadd r66._y__, r66.x, r74.z
	ishl r66._y__, r66.y, r67.y
	iadd r66._y__, r3.y, r66.y
	mov r1010.x___, r66.y
	uav_raw_load_id(11) r1011.x___, r1010.x
	mov r67.___w, r1011.x
	mul_ieee r67.___w, r67.w, r3.x
	mul_ieee r68.x___, r72.x, r1.w
	add r67.___w, r68.x, r67.w
	mov r1011, r67.w
	mov r1010.x___, r66.y
	uav_raw_store_id(11) mem0.x___, r1010.x, r1011.x
	iadd r66._y__, r66.x, r71.z
	ishl r66._y__, r66.y, r67.y
	iadd r66._y__, r3.y, r66.y
	mov r1010.x___, r66.y
	uav_raw_load_id(11) r1011.x___, r1010.x
	mov r67.___w, r1011.x
	mul_ieee r67.___w, r67.w, r3.x
	mul_ieee r68.x___, r70.z, r1.w
	add r67.___w, r68.x, r67.w
	mov r1011, r67.w
	mov r1010.x___, r66.y
	uav_raw_store_id(11) mem0.x___, r1010.x, r1011.x
	iadd r66._y__, r66.x, r70.x
	ishl r66._y__, r66.y, r67.y
	iadd r66._y__, r3.y, r66.y
	mov r1010.x___, r66.y
	uav_raw_load_id(11) r1011.x___, r1010.x
	mov r67.___w, r1011.x
	mul_ieee r67.___w, r67.w, r3.x
	mul_ieee r68.x___, r69.x, r1.w
	add r67.___w, r68.x, r67.w
	mov r1011, r67.w
	mov r1010.x___, r66.y
	uav_raw_store_id(11) mem0.x___, r1010.x, r1011.x
	iadd r66._y__, r66.x, r68.z
	ishl r66._y__, r66.y, r67.y
	iadd r66._y__, r3.y, r66.y
	mov r1010.x___, r66.y
	uav_raw_load_id(11) r1011.x___, r1010.x
	mov r67.___w, r1011.x
	mul_ieee r67.___w, r67.w, r3.x
	mul_ieee r67.__z_, r67.z, r1.w
	add r67.__z_, r67.z, r67.w
	mov r1011, r67.z
	mov r1010.x___, r66.y
	uav_raw_store_id(11) mem0.x___, r1010.x, r1011.x
	iadd r65.x___, r66.x, r65.x
	iadd r66.x___, r65.x, r66.z
	ishl r66.x___, r66.x, r67.y
	iadd r66.x___, r3.y, r66.x
	mov r1010.x___, r66.x
	uav_raw_load_id(11) r1011.x___, r1010.x
	mov r66._y__, r1011.x
	mul_ieee r66._y__, r66.y, r3.x
	mul_ieee r66.__z_, r74.y, r1.w
	add r66._y__, r66.z, r66.y
	mov r1011, r66.y
	mov r1010.x___, r66.x
	uav_raw_store_id(11) mem0.x___, r1010.x, r1011.x
	iadd r66.x___, r65.x, r67.x
	ishl r66.x___, r66.x, r67.y
	iadd r66.x___, r3.y, r66.x
	mov r1010.x___, r66.x
	uav_raw_load_id(11) r1011.x___, r1010.x
	mov r66._y__, r1011.x
	mul_ieee r66._y__, r66.y, r3.x
	mul_ieee r66.__z_, r75.w, r1.w
	add r66._y__, r66.z, r66.y
	mov r1011, r66.y
	mov r1010.x___, r66.x
	uav_raw_store_id(11) mem0.x___, r1010.x, r1011.x
	iadd r66.x___, r65.x, r73.x
	ishl r66.x___, r66.x, r67.y
	iadd r66.x___, r3.y, r66.x
	mov r1010.x___, r66.x
	uav_raw_load_id(11) r1011.x___, r1010.x
	mov r66._y__, r1011.x
	mul_ieee r66._y__, r66.y, r3.x
	mul_ieee r66.__z_, r77.y, r1.w
	add r66._y__, r66.z, r66.y
	mov r1011, r66.y
	mov r1010.x___, r66.x
	uav_raw_store_id(11) mem0.x___, r1010.x, r1011.x
	iadd r66.x___, r65.x, r74.z
	ishl r66.x___, r66.x, r67.y
	iadd r66.x___, r3.y, r66.x
	mov r1010.x___, r66.x
	uav_raw_load_id(11) r1011.x___, r1010.x
	mov r66._y__, r1011.x
	mul_ieee r66._y__, r66.y, r3.x
	mul_ieee r66.__z_, r71.w, r1.w
	add r66._y__, r66.z, r66.y
	mov r1011, r66.y
	mov r1010.x___, r66.x
	uav_raw_store_id(11) mem0.x___, r1010.x, r1011.x
	iadd r66.x___, r65.x, r71.z
	ishl r66.x___, r66.x, r67.y
	iadd r66.x___, r3.y, r66.x
	mov r1010.x___, r66.x
	uav_raw_load_id(11) r1011.x___, r1010.x
	mov r66._y__, r1011.x
	mul_ieee r66._y__, r66.y, r3.x
	mul_ieee r66.__z_, r70.y, r1.w
	add r66._y__, r66.z, r66.y
	mov r1011, r66.y
	mov r1010.x___, r66.x
	uav_raw_store_id(11) mem0.x___, r1010.x, r1011.x
	iadd r66.x___, r65.x, r70.x
	ishl r66.x___, r66.x, r67.y
	iadd r66.x___, r3.y, r66.x
	mov r1010.x___, r66.x
	uav_raw_load_id(11) r1011.x___, r1010.x
	mov r66._y__, r1011.x
	mul_ieee r66._y__, r66.y, r3.x
	mul_ieee r66.__z_, r68.w, r1.w
	add r66._y__, r66.z, r66.y
	mov r1011, r66.y
	mov r1010.x___, r66.x
	uav_raw_store_id(11) mem0.x___, r1010.x, r1011.x
	iadd r65.x___, r65.x, r68.z
	ishl r65.x___, r65.x, r67.y
	iadd r65.x___, r3.y, r65.x
	mov r1010.x___, r65.x
	uav_raw_load_id(11) r1011.x___, r1010.x
	mov r65._y__, r1011.x
	mul_ieee r65._y__, r65.y, r3.x
	mul_ieee r65.__z_, r66.w, r1.w
	add r65._y__, r65.z, r65.y
	mov r1011, r65.y
	mov r1010.x___, r65.x
	uav_raw_store_id(11) mem0.x___, r1010.x, r1011.x
	else
	endif
	else
	endif
	ret
endfunc ; sgemmNN
;ARGSTART:sgemmNN
;uniqueid:1035
;ARGEND:sgemmNN




mdef(140)_out(1)_in(3)
mov r0, in0
mov r1, in1
mov r2, in2
fma r0.x___, r0.x, r1.x, r2.x
mov out0, r0
mend

end
