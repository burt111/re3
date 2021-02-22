#if 0
//
// Generated by Microsoft (R) HLSL Shader Compiler 9.29.952.3111
//
//   fxc /nologo /T vs_2_0 /Fh matfx_env_amb_VS.h matfx_env_VS.hlsl
//
//
// Parameters:
//
//   float4 ambientLight;
//   float4x4 combinedMat;
//   float4 fogData;
//   float4 matCol;
//   float3x3 normalMat;
//   float4 surfProps;
//   float4x4 texMat;
//
//
// Registers:
//
//   Name         Reg   Size
//   ------------ ----- ----
//   combinedMat  c0       4
//   normalMat    c8       3
//   matCol       c12      1
//   surfProps    c13      1
//   fogData      c14      1
//   ambientLight c15      1
//   texMat       c41      4
//

    vs_2_0
    def c4, 0, 1, 0, 0
    dcl_position v0
    dcl_normal v1
    dcl_texcoord v2
    dcl_color v3
    mul r0.xyz, v1.y, c9
    mad r0.xyz, c8, v1.x, r0
    mad r0.xyz, c10, v1.z, r0
    mul r0.yw, r0.y, c42.xxzy
    mad r0.xy, c41, r0.x, r0.ywzw
    mad r0.xy, c43, r0.z, r0
    add oT1.xy, r0, c44
    mov r0.xyz, c15
    mad r0.xyz, r0, c13.x, v3
    mov r0.w, v3.w
    max r0, r0, c4.x
    min r0, r0, c4.y
    mul oD0, r0, c12
    mul r0, v0.y, c1
    mad r0, c0, v0.x, r0
    mad r0, c2, v0.z, r0
    mad r0, c3, v0.w, r0
    add r1.x, r0.w, -c14.y
    mov oPos, r0
    mul r0.x, r1.x, c14.z
    max r0.x, r0.x, c14.w
    min oT0.z, r0.x, c4.y
    mov oT0.xy, v2

// approximately 23 instruction slots used
#endif

const BYTE g_vs20_main[] =
{
      0,   2, 254, 255, 254, 255, 
     88,   0,  67,  84,  65,  66, 
     28,   0,   0,   0,  40,   1, 
      0,   0,   0,   2, 254, 255, 
      7,   0,   0,   0,  28,   0, 
      0,   0,   0,   1,   0,   0, 
     33,   1,   0,   0, 168,   0, 
      0,   0,   2,   0,  15,   0, 
      1,   0,  62,   0, 184,   0, 
      0,   0,   0,   0,   0,   0, 
    200,   0,   0,   0,   2,   0, 
      0,   0,   4,   0,   2,   0, 
    212,   0,   0,   0,   0,   0, 
      0,   0, 228,   0,   0,   0, 
      2,   0,  14,   0,   1,   0, 
     58,   0, 184,   0,   0,   0, 
      0,   0,   0,   0, 236,   0, 
      0,   0,   2,   0,  12,   0, 
      1,   0,  50,   0, 184,   0, 
      0,   0,   0,   0,   0,   0, 
    243,   0,   0,   0,   2,   0, 
      8,   0,   3,   0,  34,   0, 
      0,   1,   0,   0,   0,   0, 
      0,   0,  16,   1,   0,   0, 
      2,   0,  13,   0,   1,   0, 
     54,   0, 184,   0,   0,   0, 
      0,   0,   0,   0,  26,   1, 
      0,   0,   2,   0,  41,   0, 
      4,   0, 166,   0, 212,   0, 
      0,   0,   0,   0,   0,   0, 
     97, 109,  98, 105, 101, 110, 
    116,  76, 105, 103, 104, 116, 
      0, 171, 171, 171,   1,   0, 
      3,   0,   1,   0,   4,   0, 
      1,   0,   0,   0,   0,   0, 
      0,   0,  99, 111, 109,  98, 
    105, 110, 101, 100,  77,  97, 
    116,   0,   3,   0,   3,   0, 
      4,   0,   4,   0,   1,   0, 
      0,   0,   0,   0,   0,   0, 
    102, 111, 103,  68,  97, 116, 
     97,   0, 109,  97, 116,  67, 
    111, 108,   0, 110, 111, 114, 
    109,  97, 108,  77,  97, 116, 
      0, 171, 171, 171,   3,   0, 
      3,   0,   3,   0,   3,   0, 
      1,   0,   0,   0,   0,   0, 
      0,   0, 115, 117, 114, 102, 
     80, 114, 111, 112, 115,   0, 
    116, 101, 120,  77,  97, 116, 
      0, 118, 115,  95,  50,  95, 
     48,   0,  77, 105,  99, 114, 
    111, 115, 111, 102, 116,  32, 
     40,  82,  41,  32,  72,  76, 
     83,  76,  32,  83, 104,  97, 
    100, 101, 114,  32,  67, 111, 
    109, 112, 105, 108, 101, 114, 
     32,  57,  46,  50,  57,  46, 
     57,  53,  50,  46,  51,  49, 
     49,  49,   0, 171, 171, 171, 
     81,   0,   0,   5,   4,   0, 
     15, 160,   0,   0,   0,   0, 
      0,   0, 128,  63,   0,   0, 
      0,   0,   0,   0,   0,   0, 
     31,   0,   0,   2,   0,   0, 
      0, 128,   0,   0,  15, 144, 
     31,   0,   0,   2,   3,   0, 
      0, 128,   1,   0,  15, 144, 
     31,   0,   0,   2,   5,   0, 
      0, 128,   2,   0,  15, 144, 
     31,   0,   0,   2,  10,   0, 
      0, 128,   3,   0,  15, 144, 
      5,   0,   0,   3,   0,   0, 
      7, 128,   1,   0,  85, 144, 
      9,   0, 228, 160,   4,   0, 
      0,   4,   0,   0,   7, 128, 
      8,   0, 228, 160,   1,   0, 
      0, 144,   0,   0, 228, 128, 
      4,   0,   0,   4,   0,   0, 
      7, 128,  10,   0, 228, 160, 
      1,   0, 170, 144,   0,   0, 
    228, 128,   5,   0,   0,   3, 
      0,   0,  10, 128,   0,   0, 
     85, 128,  42,   0,  96, 160, 
      4,   0,   0,   4,   0,   0, 
      3, 128,  41,   0, 228, 160, 
      0,   0,   0, 128,   0,   0, 
    237, 128,   4,   0,   0,   4, 
      0,   0,   3, 128,  43,   0, 
    228, 160,   0,   0, 170, 128, 
      0,   0, 228, 128,   2,   0, 
      0,   3,   1,   0,   3, 224, 
      0,   0, 228, 128,  44,   0, 
    228, 160,   1,   0,   0,   2, 
      0,   0,   7, 128,  15,   0, 
    228, 160,   4,   0,   0,   4, 
      0,   0,   7, 128,   0,   0, 
    228, 128,  13,   0,   0, 160, 
      3,   0, 228, 144,   1,   0, 
      0,   2,   0,   0,   8, 128, 
      3,   0, 255, 144,  11,   0, 
      0,   3,   0,   0,  15, 128, 
      0,   0, 228, 128,   4,   0, 
      0, 160,  10,   0,   0,   3, 
      0,   0,  15, 128,   0,   0, 
    228, 128,   4,   0,  85, 160, 
      5,   0,   0,   3,   0,   0, 
     15, 208,   0,   0, 228, 128, 
     12,   0, 228, 160,   5,   0, 
      0,   3,   0,   0,  15, 128, 
      0,   0,  85, 144,   1,   0, 
    228, 160,   4,   0,   0,   4, 
      0,   0,  15, 128,   0,   0, 
    228, 160,   0,   0,   0, 144, 
      0,   0, 228, 128,   4,   0, 
      0,   4,   0,   0,  15, 128, 
      2,   0, 228, 160,   0,   0, 
    170, 144,   0,   0, 228, 128, 
      4,   0,   0,   4,   0,   0, 
     15, 128,   3,   0, 228, 160, 
      0,   0, 255, 144,   0,   0, 
    228, 128,   2,   0,   0,   3, 
      1,   0,   1, 128,   0,   0, 
    255, 128,  14,   0,  85, 161, 
      1,   0,   0,   2,   0,   0, 
     15, 192,   0,   0, 228, 128, 
      5,   0,   0,   3,   0,   0, 
      1, 128,   1,   0,   0, 128, 
     14,   0, 170, 160,  11,   0, 
      0,   3,   0,   0,   1, 128, 
      0,   0,   0, 128,  14,   0, 
    255, 160,  10,   0,   0,   3, 
      0,   0,   4, 224,   0,   0, 
      0, 128,   4,   0,  85, 160, 
      1,   0,   0,   2,   0,   0, 
      3, 224,   2,   0, 228, 144, 
    255, 255,   0,   0
};
