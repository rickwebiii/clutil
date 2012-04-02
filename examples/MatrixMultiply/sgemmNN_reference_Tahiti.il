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
call 1028;$
endmain




func 1028 ; __OpenCL_sgemmNN_reference_kernel
mov r1013, cb0[8].x
mov r1019, l1.0000
dcl_max_thread_per_group 256 
dcl_typeless_uav_id(11)_stride(4)_length(4)_access(read_write)
dcl_typeless_uav_id(10)_stride(4)_length(4)_access(read_write)
dcl_typeless_uav_id(12)_stride(4)_length(4)_access(read_write)
mov r0.__z_, vThreadGrpIdFlat0.x
mov r1022.xyz0, vTidInGrp0.xyz
mov r1023.xyz0, vThreadGrpId0.xyz
imad r1021.xyz0, r1023.xyzz, cb0[1].xyzz, r1022.xyzz
iadd r1021.xyz0, r1021.xyz0, cb0[6].xyz0
iadd r1023.xyz0, r1023.xyz0, cb0[7].xyz0
mov r1023.___w, r0.z
ishl r1023.___w, r1023.w, l0.z
mov r1018.x___, l0.0000
udiv r1024.xyz_, r1021.xyzz, cb0[10].xyzz
imad r1025.xyz0, r1023.xyzz, cb0[10].xyzz, r1022.xyzz
dcl_literal l14, 0x00000000, 0x00000000, 0x00000000, 0x00000000; f32:i32 0
dcl_literal l12, 0x00000001, 0x00000001, 0x00000001, 0x00000001; f32:i32 1
dcl_literal l16, 0x00000002, 0x00000002, 0x00000002, 0x00000002; f32:i32 2
dcl_literal l17, 0x00000004, 0x00000004, 0x00000004, 0x00000004; f32:i32 4
dcl_literal l15, 0x00000018, 0x00000018, 0x00000018, 0x00000018; f32:i32 24
dcl_literal l13, 0x000000FF, 0x000000FF, 0x000000FF, 0x000000FF; f32:i32 255
dcl_literal l18, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF; f32:i32 4294967295
dcl_cb cb1[11]
; Kernel arg setup: m
mov r1.x, cb1[0].x
; Kernel arg setup: n
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
call 1037 ; sgemmNN_reference
ret
endfunc ; __OpenCL_sgemmNN_reference_kernel
;ARGSTART:__OpenCL_sgemmNN_reference_kernel
;version:3:0:98
;device:tahiti
;uniqueid:1028
;memory:uavprivate:0
;memory:hwregion:0
;memory:hwlocal:0
;value:m:i32:1:1:0
;value:n:i32:1:1:16
;value:k:i32:1:1:32
;value:alpha:float:1:1:48
;pointer:a:float:1:1:64:uav:10:4:RO
;value:lda:i32:1:1:80
;pointer:b:float:1:1:96:uav:11:4:RO
;value:ldb:i32:1:1:112
;value:beta:float:1:1:128
;pointer:c:float:1:1:144:uav:12:4:RW
;value:ldc:i32:1:1:160
;function:1:1037
;privateid:8
;ARGEND:__OpenCL_sgemmNN_reference_kernel
func 1037 ; sgemmNN_reference           ; @__OpenCL_sgemmNN_reference_kernel
; BB#0:                                 ; %entry
	mov r65.x___, r1.z
	mov r66, r1021.xyz0
	mov r65.___w, r66.000x
	ilt r65.__z_, r65.w, r1.x
	mov r65.__z_, r65.z
	mov r66.x___, r66.y000
	ilt r65._y__, r66.x, r1.y
	mov r65._y__, r65.y
	iand r65._y__, r65.y, r65.z
	mov r65.__z_, l12
	iand r65._y__, r65.y, r65.z
	mov r66._y__, l13
	iand r65._y__, r65.y, r66.y
	mov r65._y__, r65.y
	mov r65._y__, r65.y
	mov r66._y__, l14
	mov r66.__z_, l15
	ishl r65._y__, r65.y, r66.z
	ishr r65._y__, r65.y, r66.z
	ishl r66._y__, r66.y, r66.z
	ishr r66._y__, r66.y, r66.z
	ieq r65._y__, r65.y, r66.y
	if_logicalnz r65.y
	else
	ilt r65._y__, r65.x, r65.z
	mov r65.__z_, l14
	if_logicalnz r65.y
	else
	mov r66.___w, l16
	ishl r66._y__, r2.y, r66.w
	ishl r67.x___, r65.w, r66.w
	iadd r66.__z_, r2.x, r67.x
	imul r65.__z_, r66.x, r2.w
	ishl r65.__z_, r65.z, r66.w
	iadd r65._y__, r2.z, r65.z
	mov r65.__z_, l14
	whileloop
	mov r1010.x___, r65.y
	uav_raw_load_id(11)_cached r1011.x___, r1010.x
	mov r66.___w, r1011.x
	mov r1010.x___, r66.z
	uav_raw_load_id(10)_cached r1011.x___, r1010.x
	mov r67.x___, r1011.x
	mov r1.x___, r67.x
	mov r1._y__, r66.w
	mov r1.__z_, r65.z
	mcall(140)(r1.x),(r1.x, r1.y, r1.z) ;__hwfma_f32
	mov r65.__z_, r1.x
	mov r66.___w, l17
	iadd r65._y__, r65.y, r66.w
	iadd r66.__z_, r66.z, r66.y
	mov r66.___w, l18
	iadd r65.x___, r65.x, r66.w
	mov r66.___w, l14
	ieq r66.___w, r65.x, r66.w
	break_logicalnz r66.w
	endloop
	endif
	mul_ieee r65.__z_, r65.z, r1.w
	imul r65.x___, r66.x, r3.z
	iadd r65.x___, r65.x, r65.w
	mov r65.___w, l16
	ishl r65.x___, r65.x, r65.w
	iadd r65.x___, r3.y, r65.x
	mov r1010.x___, r65.x
	uav_raw_load_id(12) r1011.x___, r1010.x
	mov r65._y__, r1011.x
	mul_ieee r65._y__, r65.y, r3.x
	add r65._y__, r65.z, r65.y
	mov r1011, r65.y
	mov r1010.x___, r65.x
	uav_raw_store_id(12) mem0.x___, r1010.x, r1011.x
	endif
	ret
endfunc ; sgemmNN_reference
;ARGSTART:sgemmNN_reference
;uniqueid:1037
;ARGEND:sgemmNN_reference
mdef(140)_out(1)_in(3)
mov r0, in0
mov r1, in1
mov r2, in2
fma r0.x___, r0.x, r1.x, r2.x
mov out0, r0
mend

end
