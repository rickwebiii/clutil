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
func 1024 ; __OpenCL_sgemmNT_kernel
mov r1013, cb0[8].x
mov r1019, l1.0000
dcl_num_thread_per_group 8, 8, 1          
dcl_typeless_uav_id(9)_stride(4)_length(4)_access(read_write)
mov r0.__z_, vThreadGrpIdFlat0.x
mov r1022.xyz0, vTidInGrp0.xyz
mov r1023.xyz0, vThreadGrpId0.xyz
dcl_literal l9, 8, 8, 1, 0
imad r1021.xyz0, r1023.xyzz, l9.xyzz, r1022.xyzz
iadd r1021.xyz0, r1021.xyz0, cb0[6].xyz0
iadd r1023.xyz0, r1023.xyz0, cb0[7].xyz0
mov r1023.___w, r0.z
ishl r1023.___w, r1023.w, l0.z
mov r1018.x___, l0.0000
udiv r1024.xyz_, r1021.xyzz, cb0[10].xyzz
imad r1025.xyz0, r1023.xyzz, cb0[10].xyzz, r1022.xyzz
dcl_cb cb1[11]
call 1026 ; sgemmNT
ret
endfunc ; __OpenCL_sgemmNT_kernel
;ARGSTART:__OpenCL_sgemmNT_kernel
;version:3:0:98
;device:tahiti
;uniqueid:1024
;memory:uavprivate:0
;memory:hwregion:0
;memory:hwlocal:0
;cws:8:8:1
;value:m:i32:1:1:0
;value:n:i32:1:1:16
;value:k:i32:1:1:32
;value:alpha:float:1:1:48
;pointer:a:float:1:1:64:uav:9:4:RW
;value:lda:i32:1:1:80
;pointer:b:float:1:1:96:uav:9:4:RW
;value:ldb:i32:1:1:112
;value:beta:float:1:1:128
;pointer:c:float:1:1:144:uav:9:4:RW
;value:ldc:i32:1:1:160
;function:1:1026
;privateid:8
;ARGEND:__OpenCL_sgemmNT_kernel
func 1026 ; sgemmNT                     ; @__OpenCL_sgemmNT_kernel
; BB#0:                                 ; %entry
	ret
endfunc ; sgemmNT
;ARGSTART:sgemmNT
;uniqueid:1026
;ARGEND:sgemmNT

end
