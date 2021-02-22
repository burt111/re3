#if 0
//
// Generated by Microsoft (R) HLSL Shader Compiler 9.29.952.3111
//
//   fxc /nologo /T ps_2_0 /Fh matfx_env_PS.h matfx_env_PS.hlsl
//
//
// Parameters:
//
//   float4 colorClamp;
//   sampler2D envTex;
//   float4 fogColor;
//   float4 fxparams;
//
//
// Registers:
//
//   Name         Reg   Size
//   ------------ ----- ----
//   fogColor     c0       1
//   fxparams     c1       1
//   colorClamp   c2       1
//   envTex       s1       1
//

    ps_2_0
    dcl t0.xyz
    dcl t1.xy
    dcl v0
    dcl_2d s1
    texld r0, t1, s1
    max r1.xyz, v0, c2
    mul r1.xyz, r1, c1.x
    mul r0.xyz, r0, r1
    mul r0.xyz, r0, t0.z
    max r0.w, v0.w, c1.y
    mul r0.xyz, r0.w, r0
    add r1.xyz, v0, -c0
    mad r1.xyz, t0.z, r1, c0
    mad r0.xyz, r1, v0.w, r0
    mov r0.w, v0.w
    mov oC0, r0

// approximately 12 instruction slots used (1 texture, 11 arithmetic)
#endif

const BYTE g_ps20_main[] =
{
      0,   2, 255, 255, 254, 255, 
     60,   0,  67,  84,  65,  66, 
     28,   0,   0,   0, 185,   0, 
      0,   0,   0,   2, 255, 255, 
      4,   0,   0,   0,  28,   0, 
      0,   0,   0,   1,   0,   0, 
    178,   0,   0,   0, 108,   0, 
      0,   0,   2,   0,   2,   0, 
      1,   0,  10,   0, 120,   0, 
      0,   0,   0,   0,   0,   0, 
    136,   0,   0,   0,   3,   0, 
      1,   0,   1,   0,   6,   0, 
    144,   0,   0,   0,   0,   0, 
      0,   0, 160,   0,   0,   0, 
      2,   0,   0,   0,   1,   0, 
      2,   0, 120,   0,   0,   0, 
      0,   0,   0,   0, 169,   0, 
      0,   0,   2,   0,   1,   0, 
      1,   0,   6,   0, 120,   0, 
      0,   0,   0,   0,   0,   0, 
     99, 111, 108, 111, 114,  67, 
    108,  97, 109, 112,   0, 171, 
      1,   0,   3,   0,   1,   0, 
      4,   0,   1,   0,   0,   0, 
      0,   0,   0,   0, 101, 110, 
    118,  84, 101, 120,   0, 171, 
      4,   0,  12,   0,   1,   0, 
      1,   0,   1,   0,   0,   0, 
      0,   0,   0,   0, 102, 111, 
    103,  67, 111, 108, 111, 114, 
      0, 102, 120, 112,  97, 114, 
     97, 109, 115,   0, 112, 115, 
     95,  50,  95,  48,   0,  77, 
    105,  99, 114, 111, 115, 111, 
    102, 116,  32,  40,  82,  41, 
     32,  72,  76,  83,  76,  32, 
     83, 104,  97, 100, 101, 114, 
     32,  67, 111, 109, 112, 105, 
    108, 101, 114,  32,  57,  46, 
     50,  57,  46,  57,  53,  50, 
     46,  51,  49,  49,  49,   0, 
    171, 171,  31,   0,   0,   2, 
      0,   0,   0, 128,   0,   0, 
      7, 176,  31,   0,   0,   2, 
      0,   0,   0, 128,   1,   0, 
      3, 176,  31,   0,   0,   2, 
      0,   0,   0, 128,   0,   0, 
     15, 144,  31,   0,   0,   2, 
      0,   0,   0, 144,   1,   8, 
     15, 160,  66,   0,   0,   3, 
      0,   0,  15, 128,   1,   0, 
    228, 176,   1,   8, 228, 160, 
     11,   0,   0,   3,   1,   0, 
      7, 128,   0,   0, 228, 144, 
      2,   0, 228, 160,   5,   0, 
      0,   3,   1,   0,   7, 128, 
      1,   0, 228, 128,   1,   0, 
      0, 160,   5,   0,   0,   3, 
      0,   0,   7, 128,   0,   0, 
    228, 128,   1,   0, 228, 128, 
      5,   0,   0,   3,   0,   0, 
      7, 128,   0,   0, 228, 128, 
      0,   0, 170, 176,  11,   0, 
      0,   3,   0,   0,   8, 128, 
      0,   0, 255, 144,   1,   0, 
     85, 160,   5,   0,   0,   3, 
      0,   0,   7, 128,   0,   0, 
    255, 128,   0,   0, 228, 128, 
      2,   0,   0,   3,   1,   0, 
      7, 128,   0,   0, 228, 144, 
      0,   0, 228, 161,   4,   0, 
      0,   4,   1,   0,   7, 128, 
      0,   0, 170, 176,   1,   0, 
    228, 128,   0,   0, 228, 160, 
      4,   0,   0,   4,   0,   0, 
      7, 128,   1,   0, 228, 128, 
      0,   0, 255, 144,   0,   0, 
    228, 128,   1,   0,   0,   2, 
      0,   0,   8, 128,   0,   0, 
    255, 144,   1,   0,   0,   2, 
      0,   8,  15, 128,   0,   0, 
    228, 128, 255, 255,   0,   0
};
