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
call 1027;$
endmain


func 1027 ; __OpenCL_dgemmNN_reference_kernel
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
dcl_literal l17, 0x00000003, 0x00000003, 0x00000003, 0x00000003; f32:i32 3
dcl_literal l18, 0x00000008, 0x00000008, 0x00000008, 0x00000008; f32:i32 8
dcl_literal l15, 0x00000018, 0x00000018, 0x00000018, 0x00000018; f32:i32 24
dcl_literal l13, 0x000000FF, 0x000000FF, 0x000000FF, 0x000000FF; f32:i32 255
dcl_literal l19, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF; f32:i32 4294967295
dcl_literal l16, 0x00000000, 0x00000000, 0x00000000, 0x00000000; f64:i64 0
dcl_cb cb1[11]
; Kernel arg setup: m
mov r1.x, cb1[0].x
; Kernel arg setup: n
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
call 1036 ; dgemmNN_reference
ret
endfunc ; __OpenCL_dgemmNN_reference_kernel
;ARGSTART:__OpenCL_dgemmNN_reference_kernel
;version:3:0:98
;device:tahiti
;uniqueid:1027
;memory:uavprivate:0
;memory:hwregion:0
;memory:hwlocal:0
;value:m:i32:1:1:0
;value:n:i32:1:1:16
;value:k:i32:1:1:32
;value:alpha:double:1:1:48
;pointer:a:double:1:1:64:uav:10:8:RO
;value:lda:i32:1:1:80
;pointer:b:double:1:1:96:uav:11:8:RO
;value:ldb:i32:1:1:112
;value:beta:double:1:1:128
;pointer:c:double:1:1:144:uav:12:8:RW
;value:ldc:i32:1:1:160
;function:1:1036
;privateid:8
;ARGEND:__OpenCL_dgemmNN_reference_kernel
func 1036 ; dgemmNN_reference           ; @__OpenCL_dgemmNN_reference_kernel
; BB#0:                                 ; %entry
	mov r65.xy__, r2.xyxy
	mov r66, r1021.xyz0
	mov r67.x___, r66.x000
	ilt r65.___w, r67.x, r1.x
	mov r65.___w, r65.w
	mov r66.x___, r66.y000
	ilt r65.__z_, r66.x, r1.y
	mov r65.__z_, r65.z
	iand r65.__z_, r65.z, r65.w
	mov r65.___w, l12
	iand r65.__z_, r65.z, r65.w
	mov r66._y__, l13
	iand r65.__z_, r65.z, r66.y
	mov r65.__z_, r65.z
	mov r65.__z_, r65.z
	mov r66._y__, l14
	mov r66.__z_, l15
	ishl r65.__z_, r65.z, r66.z
	ishr r65.__z_, r65.z, r66.z
	ishl r66._y__, r66.y, r66.z
	ishr r66._y__, r66.y, r66.z
	ieq r65.__z_, r65.z, r66.y
	if_logicalnz r65.z
	else
	mov r65.__z_, r1.z
	ilt r65.___w, r65.z, r65.w
	mov r66.__zw, l16
	if_logicalnz r65.w
	else
	mov r67._y__, l17
	ishl r67.__z_, r2.z, r67.y
	ishl r66.__z_, r67.x, r67.y
	iadd r67.___w, r1.w, r66.z
	imul r65.___w, r66.x, r3.x
	ishl r65.___w, r65.w, r67.y
	iadd r65.___w, r2.w, r65.w
	mov r66.__zw, l16
	whileloop
	mov r1010.x___, r65.w
	uav_raw_load_id(11)_cached r1011.xy__, r1010.x
	mov r68.xy__, r1011.xyxy
	mov r1010.x___, r67.w
	uav_raw_load_id(10)_cached r1011.xy__, r1010.x
	mov r68.__zw, r1011.xyxy
	dmad r66.__zw, r68.zwzw, r68.xyxy, r66.zwzw
	mov r66._y__, l18
	iadd r65.___w, r65.w, r66.y
	iadd r67.___w, r67.w, r67.z
	mov r66._y__, l19
	iadd r65.__z_, r65.z, r66.y
	mov r66._y__, l14
	ieq r66._y__, r65.z, r66.y
	break_logicalnz r66.y
	endloop
	endif
	dmul r65.xy__, r66.zwzw, r65.xyxy
	imul r65.__z_, r66.x, r4.x
	iadd r65.__z_, r65.z, r67.x
	mov r66.x___, l17
	ishl r65.__z_, r65.z, r66.x
	iadd r65.__z_, r3.y, r65.z
	mov r1010.x___, r65.z
	uav_raw_load_id(12) r1011.xy__, r1010.x
	mov r66.__zw, r1011.xyxy
	dmul r66.__zw, r66.zwzw, r3.zwzw
	dadd r65.xy__, r65.xyxy, r66.zwzw
	mov r1011, r65.xyxy
	mov r1010.x___, r65.z
	uav_raw_store_id(12) mem0.xy__, r1010.x, r1011.xyxy
	endif
	ret
endfunc ; dgemmNN_reference
;ARGSTART:dgemmNN_reference
;uniqueid:1036
;ARGEND:dgemmNN_reference


mdef(140)_out(1)_in(3)
mov r0, in0
mov r1, in1
mov r2, in2
fma r0.x___, r0.x, r1.x, r2.x
mov out0, r0
mend

end
