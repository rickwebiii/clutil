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
func 1024 ; __OpenCL_dgemmNN_kernel
mov r1013, cb0[8].x
mov r1019, l1.0000
dcl_num_thread_per_group 16, 16, 1          
dcl_lds_id(1) 17024
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
dcl_literal l18, 0x00000000, 0x00000000, 0x00000000, 0x00000000; f32:i32 0
dcl_literal l12, 0x00000001, 0x00000001, 0x00000001, 0x00000001; f32:i32 1
dcl_literal l44, 0x00000002, 0x00000002, 0x00000002, 0x00000002; f32:i32 2
dcl_literal l15, 0x00000003, 0x00000003, 0x00000003, 0x00000003; f32:i32 3
dcl_literal l46, 0x00000004, 0x00000004, 0x00000004, 0x00000004; f32:i32 4
dcl_literal l13, 0x00000006, 0x00000006, 0x00000006, 0x00000006; f32:i32 6
dcl_literal l17, 0x00000007, 0x00000007, 0x00000007, 0x00000007; f32:i32 7
dcl_literal l23, 0x00000010, 0x00000010, 0x00000010, 0x00000010; f32:i32 16
dcl_literal l20, 0x00000011, 0x00000011, 0x00000011, 0x00000011; f32:i32 17
dcl_literal l24, 0x00000020, 0x00000020, 0x00000020, 0x00000020; f32:i32 32
dcl_literal l25, 0x00000030, 0x00000030, 0x00000030, 0x00000030; f32:i32 48
dcl_literal l45, 0x0000003F, 0x0000003F, 0x0000003F, 0x0000003F; f32:i32 63
dcl_literal l19, 0x00000041, 0x00000041, 0x00000041, 0x00000041; f32:i32 65
dcl_literal l27, 0x00000080, 0x00000080, 0x00000080, 0x00000080; f32:i32 128
dcl_literal l16, 0x00000100, 0x00000100, 0x00000100, 0x00000100; f32:i32 256
dcl_literal l31, 0x00000180, 0x00000180, 0x00000180, 0x00000180; f32:i32 384
dcl_literal l34, 0x00000208, 0x00000208, 0x00000208, 0x00000208; f32:i32 520
dcl_literal l43, 0x00000288, 0x00000288, 0x00000288, 0x00000288; f32:i32 648
dcl_literal l42, 0x00000308, 0x00000308, 0x00000308, 0x00000308; f32:i32 776
dcl_literal l41, 0x00000388, 0x00000388, 0x00000388, 0x00000388; f32:i32 904
dcl_literal l29, 0x00000880, 0x00000880, 0x00000880, 0x00000880; f32:i32 2176
dcl_literal l30, 0x00001100, 0x00001100, 0x00001100, 0x00001100; f32:i32 4352
dcl_literal l32, 0x00001980, 0x00001980, 0x00001980, 0x00001980; f32:i32 6528
dcl_literal l22, 0x00001988, 0x00001988, 0x00001988, 0x00001988; f32:i32 6536
dcl_literal l21, 0x00002080, 0x00002080, 0x00002080, 0x00002080; f32:i32 8320
dcl_literal l47, 0x00002200, 0x00002200, 0x00002200, 0x00002200; f32:i32 8704
dcl_literal l39, 0xFFFFE678, 0xFFFFE678, 0xFFFFE678, 0xFFFFE678; f32:i32 4294960760
dcl_literal l40, 0xFFFFE680, 0xFFFFE680, 0xFFFFE680, 0xFFFFE680; f32:i32 4294960768
dcl_literal l37, 0xFFFFEEF8, 0xFFFFEEF8, 0xFFFFEEF8, 0xFFFFEEF8; f32:i32 4294962936
dcl_literal l38, 0xFFFFEF00, 0xFFFFEF00, 0xFFFFEF00, 0xFFFFEF00; f32:i32 4294962944
dcl_literal l35, 0xFFFFF778, 0xFFFFF778, 0xFFFFF778, 0xFFFFF778; f32:i32 4294965112
dcl_literal l36, 0xFFFFF780, 0xFFFFF780, 0xFFFFF780, 0xFFFFF780; f32:i32 4294965120
dcl_literal l26, 0xFFFFFF00, 0xFFFFFF00, 0xFFFFFF00, 0xFFFFFF00; f32:i32 4294967040
dcl_literal l28, 0xFFFFFF80, 0xFFFFFF80, 0xFFFFFF80, 0xFFFFFF80; f32:i32 4294967168
dcl_literal l33, 0xFFFFFFF8, 0xFFFFFFF8, 0xFFFFFFF8, 0xFFFFFFF8; f32:i32 4294967288
dcl_literal l14, 0x00000000, 0x00000000, 0x00000000, 0x00000000; f64:i64 0
dcl_cb cb1[11]
; Kernel arg setup: n
mov r1.x, cb1[0].x
; Kernel arg setup: m
mov r1.y, cb1[1].x
; Kernel arg setup: k
mov r1.z, cb1[2].x
; Kernel arg setup: alpha
mov r2.xy__, cb1[3].xy
; Kernel arg setup: a
mov r1.w, cb1[4].x
; Kernel arg setup: lda
mov r2.z, cb1[5].x
; Kernel arg setup: b
mov r2.w, cb1[6].x
; Kernel arg setup: ldb
mov r3.x, cb1[7].x
; Kernel arg setup: beta
mov r3.__zw, cb1[8].00xy
; Kernel arg setup: c
mov r3.y, cb1[9].x
; Kernel arg setup: ldc
mov r4.x, cb1[10].x
call 1033 ; dgemmNN
ret
endfunc ; __OpenCL_dgemmNN_kernel
;ARGSTART:__OpenCL_dgemmNN_kernel
;version:3:0:98
;device:tahiti
;uniqueid:1024
;memory:uavprivate:0
;memory:hwregion:0
;memory:hwlocal:17024
;cws:16:16:1
;value:n:i32:1:1:0
;value:m:i32:1:1:16
;value:k:i32:1:1:32
;value:alpha:double:1:1:48
;pointer:a:double:1:1:64:uav:9:8:RW
;value:lda:i32:1:1:80
;pointer:b:double:1:1:96:uav:10:8:RO
;value:ldb:i32:1:1:112
;value:beta:double:1:1:128
;pointer:c:double:1:1:144:uav:11:8:RW
;value:ldc:i32:1:1:160
;function:1:1033
;privateid:8
;ARGEND:__OpenCL_dgemmNN_kernel
func 1033 ; dgemmNN                     ; @__OpenCL_dgemmNN_kernel
; BB#0:                                 ; %entry
	mov r65.xy__, r2.xyxy
	mov r65.__z_, r1.z
	mov r65.___w, l12
	ilt r65.___w, r65.z, r65.w
	mov r66, r1023.xyz0
	mov r67.x___, r66.y000
	mov r67._y__, l13
	ishl r67.x___, r67.x, r67.y
	mov r66.x___, r66.x000
	ishl r66.x___, r66.x, r67.y
	mov r68, r1022.xyz0
	mov r66._y__, r68.0y00
	mov r66.__z_, r68.00x0
	mov r67.__zw, l14
	mov r68.xy__, r67.zwzw
	mov r68.__zw, r67.zwzw
	mov r69.xy__, r67.zwzw
	mov r69.__zw, r67.zwzw
	mov r70.xy__, r67.zwzw
	mov r70.__zw, r67.zwzw
	mov r71.xy__, r67.zwzw
	mov r71.__zw, r67.zwzw
	mov r72.xy__, r67.zwzw
	mov r72.__zw, r67.zwzw
	mov r73.xy__, r67.zwzw
	mov r73.__zw, r67.zwzw
	mov r74.xy__, r67.zwzw
	mov r74.__zw, r67.zwzw
	mov r75.xy__, r67.zwzw
	if_logicalnz r65.w
	else
	imul r67.___w, r66.y, r2.z
	iadd r67.___w, r66.z, r67.w
	iadd r67.___w, r67.w, r66.x
	mov r75.__z_, l15
	ishl r67.___w, r67.w, r75.z
	iadd r67.__z_, r67.w, r1.w
	mov r75.___w, l16
	iadd r76.x___, r67.z, r75.w
	mov r67.__z_, l17
	ishl r67._y__, r2.z, r67.z
	ishl r67.__z_, r66.z, r75.z
	mov r76._y__, l18
	iadd r76.__z_, r76.y, r67.z
	mov r67.__z_, l19
	imul r67.__z_, r66.y, r67.z
	iadd r76.___w, r66.z, r67.z
	mov r67.__z_, l20
	imul r67.___w, r66.z, r67.z
	iadd r77.x___, r66.y, r67.w
	imul r67.__z_, r66.y, r67.z
	ishl r67.__z_, r67.z, r75.z
	mov r77._y__, l21
	iadd r67.__z_, r67.z, r77.y
	mov r67.___w, l22
	iadd r77.__z_, r67.z, r67.w
	iadd r67.__z_, r66.z, r67.x
	imul r67.___w, r3.x, r67.z
	iadd r67.___w, r66.y, r67.w
	ishl r67.___w, r67.w, r75.z
	iadd r77.___w, r2.w, r67.w
	mov r67.___w, l23
	iadd r67.___w, r67.z, r67.w
	imul r67.___w, r3.x, r67.w
	iadd r67.___w, r66.y, r67.w
	ishl r67.___w, r67.w, r75.z
	iadd r78.x___, r2.w, r67.w
	mov r67.___w, l24
	iadd r67.___w, r67.z, r67.w
	imul r67.___w, r3.x, r67.w
	iadd r67.___w, r66.y, r67.w
	ishl r67.___w, r67.w, r75.z
	iadd r78._y__, r2.w, r67.w
	mov r67.___w, l25
	iadd r67.__z_, r67.z, r67.w
	imul r65.___w, r3.x, r67.z
	iadd r65.___w, r66.y, r65.w
	ishl r65.___w, r65.w, r75.z
	iadd r65.___w, r2.w, r65.w
	mov r67.__zw, l14
	mov r66.___w, r76.y
	mov r68.xy__, r67.zwzw
	mov r68.__zw, r67.zwzw
	mov r69.xy__, r67.zwzw
	mov r69.__zw, r67.zwzw
	mov r70.xy__, r67.zwzw
	mov r70.__zw, r67.zwzw
	mov r71.xy__, r67.zwzw
	mov r71.__zw, r67.zwzw
	mov r72.xy__, r67.zwzw
	mov r72.__zw, r67.zwzw
	mov r73.xy__, r67.zwzw
	mov r73.__zw, r67.zwzw
	mov r74.xy__, r67.zwzw
	mov r74.__zw, r67.zwzw
	mov r75.xy__, r67.zwzw
	whileloop
	ishl r78.__z_, r76.w, r75.z
	iadd r78.__z_, r76.y, r78.z
	mov r78.___w, l26
	iadd r78.___w, r76.x, r78.w
	mov r1010.x___, r78.w
	uav_raw_load_id(9) r1011.xy__, r1010.x
	mov r79.xy__, r1011.xyxy
	mov r1011, r79.xyxy
	mov r1010.x___, r78.z
	lds_store_vec_id(1) mem0.xy__, r1010.xyxy, r1011.xyxy, r1011.xyxy
	ishl r78.___w, r77.x, r75.z
	iadd r78.___w, r77.y, r78.w
	ishl r79.x___, r66.w, r75.z
	iadd r79._y__, r77.w, r79.x
	mov r1010.x___, r79.y
	uav_raw_load_id(10)_cached r1011.xy__, r1010.x
	mov r79.__zw, r1011.xyxy
	mov r1011, r79.zwzw
	mov r1010.x___, r78.w
	lds_store_vec_id(1) mem0.xy__, r1010.xyxy, r1011.xyxy, r1011.xyxy
	mov r79._y__, l27
	iadd r79.__z_, r78.z, r79.y
	mov r79.___w, l28
	iadd r79.___w, r76.x, r79.w
	mov r1010.x___, r79.w
	uav_raw_load_id(9) r1011.xy__, r1010.x
	mov r80.xy__, r1011.xyxy
	mov r1011, r80.xyxy
	mov r1010.x___, r79.z
	lds_store_vec_id(1) mem0.xy__, r1010.xyxy, r1011.xyxy, r1011.xyxy
	mov r79.__z_, l29
	iadd r79.__z_, r78.w, r79.z
	iadd r79.___w, r78.x, r79.x
	mov r1010.x___, r79.w
	uav_raw_load_id(10)_cached r1011.xy__, r1010.x
	mov r80.xy__, r1011.xyxy
	mov r1011, r80.xyxy
	mov r1010.x___, r79.z
	lds_store_vec_id(1) mem0.xy__, r1010.xyxy, r1011.xyxy, r1011.xyxy
	iadd r79.__z_, r78.z, r75.w
	mov r1010.x___, r76.x
	uav_raw_load_id(9) r1011.xy__, r1010.x
	mov r80.xy__, r1011.xyxy
	mov r1011, r80.xyxy
	mov r1010.x___, r79.z
	lds_store_vec_id(1) mem0.xy__, r1010.xyxy, r1011.xyxy, r1011.xyxy
	mov r79.__z_, l30
	iadd r79.__z_, r78.w, r79.z
	iadd r79.___w, r78.y, r79.x
	mov r1010.x___, r79.w
	uav_raw_load_id(10)_cached r1011.xy__, r1010.x
	mov r80.xy__, r1011.xyxy
	mov r1011, r80.xyxy
	mov r1010.x___, r79.z
	lds_store_vec_id(1) mem0.xy__, r1010.xyxy, r1011.xyxy, r1011.xyxy
	mov r79.__z_, l31
	iadd r78.__z_, r78.z, r79.z
	iadd r79.___w, r76.x, r79.y
	mov r1010.x___, r79.w
	uav_raw_load_id(9) r1011.xy__, r1010.x
	mov r80.xy__, r1011.xyxy
	mov r1011, r80.xyxy
	mov r1010.x___, r78.z
	lds_store_vec_id(1) mem0.xy__, r1010.xyxy, r1011.xyxy, r1011.xyxy
	mov r78.__z_, l32
	iadd r78.__z_, r78.w, r78.z
	iadd r78.___w, r65.w, r79.x
	mov r1010.x___, r78.w
	uav_raw_load_id(10)_cached r1011.xy__, r1010.x
	mov r80.xy__, r1011.xyxy
	mov r1011, r80.xyxy
	mov r1010.x___, r78.z
	lds_store_vec_id(1) mem0.xy__, r1010.xyxy, r1011.xyxy, r1011.xyxy
	mov r78.__z_, l12
	fence_threads_lds
	mov r78.__z_, r76.y
	whileloop
	mov r78.___w, l15
	ishl r79.x___, r78.z, r78.w
	iadd r79.x___, r77.z, r79.x
	mov r79.___w, l33
	iadd r79.___w, r79.x, r79.w
	mov r1010.x___, r79.w
	lds_load_vec_id(1) r1011.xy__, r1010.xyxy, r1010.xyxy
	mov r80.xy__, r1011.xyxy
	mov r79.___w, l19
	imul r79.___w, r78.z, r79.w
	ishl r78.___w, r79.w, r78.w
	iadd r78.___w, r76.z, r78.w
	mov r1010.x___, r78.w
	lds_load_vec_id(1) r1011.xy__, r1010.xyxy, r1010.xyxy
	mov r80.__zw, r1011.xyxy
	dmad r73.__zw, r80.zwzw, r80.xyxy, r73.zwzw
	mov r1010.x___, r79.x
	lds_load_vec_id(1) r1011.xy__, r1010.xyxy, r1010.xyxy
	mov r81.xy__, r1011.xyxy
	mov r79.___w, l34
	iadd r79.___w, r78.w, r79.w
	mov r1010.x___, r79.w
	lds_load_vec_id(1) r1011.xy__, r1010.xyxy, r1010.xyxy
	mov r81.__zw, r1011.xyxy
	dmad r73.__zw, r81.zwzw, r81.xyxy, r73.zwzw
	mov r79.___w, l35
	iadd r79.___w, r79.x, r79.w
	mov r1010.x___, r79.w
	lds_load_vec_id(1) r1011.xy__, r1010.xyxy, r1010.xyxy
	mov r82.xy__, r1011.xyxy
	dmad r74.xy__, r80.zwzw, r82.xyxy, r74.xyxy
	mov r79.___w, l36
	iadd r79.___w, r79.x, r79.w
	mov r1010.x___, r79.w
	lds_load_vec_id(1) r1011.xy__, r1010.xyxy, r1010.xyxy
	mov r82.__zw, r1011.xyxy
	dmad r74.xy__, r81.zwzw, r82.zwzw, r74.xyxy
	mov r79.___w, l37
	iadd r79.___w, r79.x, r79.w
	mov r1010.x___, r79.w
	lds_load_vec_id(1) r1011.xy__, r1010.xyxy, r1010.xyxy
	mov r83.xy__, r1011.xyxy
	dmad r74.__zw, r80.zwzw, r83.xyxy, r74.zwzw
	mov r79.___w, l38
	iadd r79.___w, r79.x, r79.w
	mov r1010.x___, r79.w
	lds_load_vec_id(1) r1011.xy__, r1010.xyxy, r1010.xyxy
	mov r83.__zw, r1011.xyxy
	dmad r74.__zw, r81.zwzw, r83.zwzw, r74.zwzw
	mov r79.___w, l39
	iadd r79.___w, r79.x, r79.w
	mov r1010.x___, r79.w
	lds_load_vec_id(1) r1011.xy__, r1010.xyxy, r1010.xyxy
	mov r84.xy__, r1011.xyxy
	dmad r75.xy__, r80.zwzw, r84.xyxy, r75.xyxy
	mov r79.___w, l40
	iadd r79.x___, r79.x, r79.w
	mov r1010.x___, r79.x
	lds_load_vec_id(1) r1011.xy__, r1010.xyxy, r1010.xyxy
	mov r80.__zw, r1011.xyxy
	dmad r75.xy__, r81.zwzw, r80.zwzw, r75.xyxy
	iadd r79.x___, r78.w, r79.z
	mov r1010.x___, r79.x
	lds_load_vec_id(1) r1011.xy__, r1010.xyxy, r1010.xyxy
	mov r81.__zw, r1011.xyxy
	dmad r67.__zw, r81.zwzw, r80.xyxy, r67.zwzw
	mov r79.x___, l41
	iadd r79.x___, r78.w, r79.x
	mov r1010.x___, r79.x
	lds_load_vec_id(1) r1011.xy__, r1010.xyxy, r1010.xyxy
	mov r84.__zw, r1011.xyxy
	dmad r67.__zw, r84.zwzw, r81.xyxy, r67.zwzw
	dmad r68.xy__, r81.zwzw, r82.xyxy, r68.xyxy
	dmad r68.xy__, r84.zwzw, r82.zwzw, r68.xyxy
	dmad r68.__zw, r81.zwzw, r83.xyxy, r68.zwzw
	dmad r68.__zw, r84.zwzw, r83.zwzw, r68.zwzw
	dmad r69.xy__, r81.zwzw, r84.xyxy, r69.xyxy
	dmad r69.xy__, r84.zwzw, r80.zwzw, r69.xyxy
	mov r79.x___, l16
	iadd r79.x___, r78.w, r79.x
	mov r1010.x___, r79.x
	lds_load_vec_id(1) r1011.xy__, r1010.xyxy, r1010.xyxy
	mov r81.__zw, r1011.xyxy
	dmad r69.__zw, r81.zwzw, r80.xyxy, r69.zwzw
	mov r79.x___, l42
	iadd r79.x___, r78.w, r79.x
	mov r1010.x___, r79.x
	lds_load_vec_id(1) r1011.xy__, r1010.xyxy, r1010.xyxy
	mov r84.__zw, r1011.xyxy
	dmad r69.__zw, r84.zwzw, r81.xyxy, r69.zwzw
	dmad r70.xy__, r81.zwzw, r82.xyxy, r70.xyxy
	dmad r70.xy__, r84.zwzw, r82.zwzw, r70.xyxy
	dmad r70.__zw, r81.zwzw, r83.xyxy, r70.zwzw
	dmad r70.__zw, r84.zwzw, r83.zwzw, r70.zwzw
	dmad r71.xy__, r81.zwzw, r84.xyxy, r71.xyxy
	dmad r71.xy__, r84.zwzw, r80.zwzw, r71.xyxy
	iadd r79.x___, r78.w, r79.y
	mov r1010.x___, r79.x
	lds_load_vec_id(1) r1011.xy__, r1010.xyxy, r1010.xyxy
	mov r81.__zw, r1011.xyxy
	dmad r71.__zw, r81.zwzw, r80.xyxy, r71.zwzw
	mov r79.x___, l43
	iadd r78.___w, r78.w, r79.x
	mov r1010.x___, r78.w
	lds_load_vec_id(1) r1011.xy__, r1010.xyxy, r1010.xyxy
	mov r80.xy__, r1011.xyxy
	dmad r71.__zw, r80.xyxy, r81.xyxy, r71.zwzw
	dmad r72.xy__, r81.zwzw, r82.xyxy, r72.xyxy
	dmad r72.xy__, r80.xyxy, r82.zwzw, r72.xyxy
	dmad r72.__zw, r81.zwzw, r83.xyxy, r72.zwzw
	dmad r72.__zw, r80.xyxy, r83.zwzw, r72.zwzw
	dmad r73.xy__, r81.zwzw, r84.xyxy, r73.xyxy
	dmad r73.xy__, r80.xyxy, r80.zwzw, r73.xyxy
	mov r78.___w, l44
	iadd r78.__z_, r78.z, r78.w
	mov r78.___w, l23
	ieq r79.x___, r78.z, r78.w
	break_logicalnz r79.x
	endloop
	iadd r76.x___, r76.x, r67.y
	iadd r66.___w, r66.w, r78.w
	ilt r78.__z_, r66.w, r65.z
	mov r78.___w, l12
	fence_threads_lds
	break_logicalz r78.z
	endloop
	endif
	mov r65.___w, l45
	ior r66.___w, r66.x, r65.w
	ilt r65.__z_, r66.w, r1.y
	if_logicalnz r65.z
	ior r65.___w, r67.x, r65.w
	ilt r65.__z_, r65.w, r1.x
	if_logicalnz r65.z
	iadd r66._y__, r67.x, r66.y
	imul r66._y__, r66.y, r4.x
	iadd r66.x___, r66.y, r66.x
	dmul r67.xy__, r75.xyxy, r65.xyxy
	iadd r66._y__, r66.x, r66.z
	mov r66.___w, l15
	ishl r66._y__, r66.y, r66.w
	iadd r66._y__, r3.y, r66.y
	mov r1010.x___, r66.y
	uav_raw_load_id(11) r1011.xy__, r1010.x
	mov r75.xy__, r1011.xyxy
	dmul r75.xy__, r75.xyxy, r3.zwzw
	dadd r67.xy__, r67.xyxy, r75.xyxy
	mov r1011, r67.xyxy
	mov r1010.x___, r66.y
	uav_raw_store_id(11) mem0.xy__, r1010.x, r1011.xyxy
	dmul r67.xy__, r73.xyxy, r65.xyxy
	mov r66._y__, l23
	iadd r66._y__, r66.z, r66.y
	iadd r73.x___, r66.x, r66.y
	ishl r73.x___, r73.x, r66.w
	iadd r73.x___, r3.y, r73.x
	mov r1010.x___, r73.x
	uav_raw_load_id(11) r1011.xy__, r1010.x
	mov r75.xy__, r1011.xyxy
	dmul r75.xy__, r75.xyxy, r3.zwzw
	dadd r67.xy__, r67.xyxy, r75.xyxy
	mov r1011, r67.xyxy
	mov r1010.x___, r73.x
	uav_raw_store_id(11) mem0.xy__, r1010.x, r1011.xyxy
	dmul r67.xy__, r71.xyxy, r65.xyxy
	mov r71.x___, l24
	iadd r71.x___, r66.z, r71.x
	iadd r71._y__, r66.x, r71.x
	ishl r71._y__, r71.y, r66.w
	iadd r71._y__, r3.y, r71.y
	mov r1010.x___, r71.y
	uav_raw_load_id(11) r1011.xy__, r1010.x
	mov r73.xy__, r1011.xyxy
	dmul r73.xy__, r73.xyxy, r3.zwzw
	dadd r67.xy__, r67.xyxy, r73.xyxy
	mov r1011, r67.xyxy
	mov r1010.x___, r71.y
	uav_raw_store_id(11) mem0.xy__, r1010.x, r1011.xyxy
	dmul r67.xy__, r69.xyxy, r65.xyxy
	mov r69.x___, l25
	iadd r69.x___, r66.z, r69.x
	iadd r69._y__, r66.x, r69.x
	ishl r69._y__, r69.y, r66.w
	iadd r69._y__, r3.y, r69.y
	mov r1010.x___, r69.y
	uav_raw_load_id(11) r1011.xy__, r1010.x
	mov r73.xy__, r1011.xyxy
	dmul r73.xy__, r73.xyxy, r3.zwzw
	dadd r67.xy__, r67.xyxy, r73.xyxy
	mov r1011, r67.xyxy
	mov r1010.x___, r69.y
	uav_raw_store_id(11) mem0.xy__, r1010.x, r1011.xyxy
	dmul r67.xy__, r74.zwzw, r65.xyxy
	mov r69._y__, l46
	ishl r65.__z_, r4.x, r69.y
	iadd r66.x___, r66.x, r65.z
	iadd r69._y__, r66.x, r66.z
	ishl r69._y__, r69.y, r66.w
	iadd r69._y__, r3.y, r69.y
	mov r1010.x___, r69.y
	uav_raw_load_id(11) r1011.xy__, r1010.x
	mov r73.xy__, r1011.xyxy
	dmul r73.xy__, r73.xyxy, r3.zwzw
	dadd r67.xy__, r67.xyxy, r73.xyxy
	mov r1011, r67.xyxy
	mov r1010.x___, r69.y
	uav_raw_store_id(11) mem0.xy__, r1010.x, r1011.xyxy
	iadd r67.x___, r66.x, r66.y
	ishl r67.x___, r67.x, r66.w
	iadd r67.x___, r3.y, r67.x
	mov r1010.x___, r67.x
	uav_raw_load_id(11) r1011.xy__, r1010.x
	mov r73.xy__, r1011.xyxy
	dmul r73.xy__, r73.xyxy, r3.zwzw
	dmul r72.__zw, r72.zwzw, r65.xyxy
	dadd r72.__zw, r72.zwzw, r73.xyxy
	mov r1011, r72.zwzw
	mov r1010.x___, r67.x
	uav_raw_store_id(11) mem0.xy__, r1010.x, r1011.xyxy
	iadd r67.x___, r66.x, r71.x
	ishl r67.x___, r67.x, r66.w
	iadd r67.x___, r3.y, r67.x
	mov r1010.x___, r67.x
	uav_raw_load_id(11) r1011.xy__, r1010.x
	mov r72.__zw, r1011.xyxy
	dmul r72.__zw, r72.zwzw, r3.zwzw
	dmul r70.__zw, r70.zwzw, r65.xyxy
	dadd r70.__zw, r70.zwzw, r72.zwzw
	mov r1011, r70.zwzw
	mov r1010.x___, r67.x
	uav_raw_store_id(11) mem0.xy__, r1010.x, r1011.xyxy
	iadd r67.x___, r66.x, r69.x
	ishl r67.x___, r67.x, r66.w
	iadd r67.x___, r3.y, r67.x
	mov r1010.x___, r67.x
	uav_raw_load_id(11) r1011.xy__, r1010.x
	mov r70.__zw, r1011.xyxy
	dmul r70.__zw, r70.zwzw, r3.zwzw
	dmul r68.__zw, r68.zwzw, r65.xyxy
	dadd r68.__zw, r68.zwzw, r70.zwzw
	mov r1011, r68.zwzw
	mov r1010.x___, r67.x
	uav_raw_store_id(11) mem0.xy__, r1010.x, r1011.xyxy
	iadd r66.x___, r66.x, r65.z
	iadd r67.x___, r66.x, r66.z
	ishl r67.x___, r67.x, r66.w
	iadd r67.x___, r3.y, r67.x
	mov r1010.x___, r67.x
	uav_raw_load_id(11) r1011.xy__, r1010.x
	mov r68.__zw, r1011.xyxy
	dmul r68.__zw, r68.zwzw, r3.zwzw
	dmul r70.__zw, r74.xyxy, r65.xyxy
	dadd r68.__zw, r70.zwzw, r68.zwzw
	mov r1011, r68.zwzw
	mov r1010.x___, r67.x
	uav_raw_store_id(11) mem0.xy__, r1010.x, r1011.xyxy
	iadd r67.x___, r66.x, r66.y
	ishl r67.x___, r67.x, r66.w
	iadd r67.x___, r3.y, r67.x
	mov r1010.x___, r67.x
	uav_raw_load_id(11) r1011.xy__, r1010.x
	mov r68.__zw, r1011.xyxy
	dmul r68.__zw, r68.zwzw, r3.zwzw
	dmul r70.__zw, r72.xyxy, r65.xyxy
	dadd r68.__zw, r70.zwzw, r68.zwzw
	mov r1011, r68.zwzw
	mov r1010.x___, r67.x
	uav_raw_store_id(11) mem0.xy__, r1010.x, r1011.xyxy
	iadd r67.x___, r66.x, r71.x
	ishl r67.x___, r67.x, r66.w
	iadd r67.x___, r3.y, r67.x
	mov r1010.x___, r67.x
	uav_raw_load_id(11) r1011.xy__, r1010.x
	mov r68.__zw, r1011.xyxy
	dmul r68.__zw, r68.zwzw, r3.zwzw
	dmul r70.xy__, r70.xyxy, r65.xyxy
	dadd r68.__zw, r70.xyxy, r68.zwzw
	mov r1011, r68.zwzw
	mov r1010.x___, r67.x
	uav_raw_store_id(11) mem0.xy__, r1010.x, r1011.xyxy
	iadd r67.x___, r66.x, r69.x
	ishl r67.x___, r67.x, r66.w
	iadd r67.x___, r3.y, r67.x
	mov r1010.x___, r67.x
	uav_raw_load_id(11) r1011.xy__, r1010.x
	mov r68.__zw, r1011.xyxy
	dmul r68.__zw, r68.zwzw, r3.zwzw
	dmul r68.xy__, r68.xyxy, r65.xyxy
	dadd r68.xy__, r68.xyxy, r68.zwzw
	mov r1011, r68.xyxy
	mov r1010.x___, r67.x
	uav_raw_store_id(11) mem0.xy__, r1010.x, r1011.xyxy
	iadd r65.__z_, r66.x, r65.z
	iadd r66.x___, r65.z, r66.z
	ishl r66.x___, r66.x, r66.w
	iadd r66.x___, r3.y, r66.x
	mov r1010.x___, r66.x
	uav_raw_load_id(11) r1011.xy__, r1010.x
	mov r67.xy__, r1011.xyxy
	dmul r67.xy__, r67.xyxy, r3.zwzw
	dmul r68.xy__, r73.zwzw, r65.xyxy
	dadd r67.xy__, r68.xyxy, r67.xyxy
	mov r1011, r67.xyxy
	mov r1010.x___, r66.x
	uav_raw_store_id(11) mem0.xy__, r1010.x, r1011.xyxy
	iadd r66.x___, r65.z, r66.y
	ishl r66.x___, r66.x, r66.w
	iadd r66.x___, r3.y, r66.x
	mov r1010.x___, r66.x
	uav_raw_load_id(11) r1011.xy__, r1010.x
	mov r67.xy__, r1011.xyxy
	dmul r67.xy__, r67.xyxy, r3.zwzw
	dmul r68.xy__, r71.zwzw, r65.xyxy
	dadd r67.xy__, r68.xyxy, r67.xyxy
	mov r1011, r67.xyxy
	mov r1010.x___, r66.x
	uav_raw_store_id(11) mem0.xy__, r1010.x, r1011.xyxy
	iadd r66.x___, r65.z, r71.x
	ishl r66.x___, r66.x, r66.w
	iadd r66.x___, r3.y, r66.x
	mov r1010.x___, r66.x
	uav_raw_load_id(11) r1011.xy__, r1010.x
	mov r67.xy__, r1011.xyxy
	dmul r67.xy__, r67.xyxy, r3.zwzw
	dmul r68.xy__, r69.zwzw, r65.xyxy
	dadd r67.xy__, r68.xyxy, r67.xyxy
	mov r1011, r67.xyxy
	mov r1010.x___, r66.x
	uav_raw_store_id(11) mem0.xy__, r1010.x, r1011.xyxy
	iadd r65.__z_, r65.z, r69.x
	ishl r65.__z_, r65.z, r66.w
	iadd r65.__z_, r3.y, r65.z
	mov r1010.x___, r65.z
	uav_raw_load_id(11) r1011.xy__, r1010.x
	mov r66.xy__, r1011.xyxy
	dmul r66.xy__, r66.xyxy, r3.zwzw
	dmul r65.xy__, r67.zwzw, r65.xyxy
	dadd r65.xy__, r65.xyxy, r66.xyxy
	mov r1011, r65.xyxy
	mov r1010.x___, r65.z
	uav_raw_store_id(11) mem0.xy__, r1010.x, r1011.xyxy
	else
	endif
	else
	endif
	ret
endfunc ; dgemmNN
;ARGSTART:dgemmNN
;uniqueid:1033
;ARGEND:dgemmNN


end
