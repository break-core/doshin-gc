#ifndef _DOLPHIN_MTX_H_
#define _DOLPHIN_MTX_H_

#include <dolphin/types.h>

/*
    Heavily stripped down version of this header from dolsdk2001-dec:
    https://github.com/doldecomp/dolsdk2001-dec/blob/master/include/dolphin/mtx.h

    Mainly to clean up the clutter
*/

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
	f32 x, y, z;
} Vec, *VecPtr, Point3d, *Point3dPtr;

typedef struct {
    s16 x, y, z;
} S16Vec, *S16VecPtr;

typedef struct {
	f32 x, y, z, w;
} Quaternion, *QuaternionPtr, Qtrn, *QtrnPtr;

typedef f32 Mtx[3][4];
typedef f32 (*MtxPtr)[4];

typedef f32 Mtx44[4][4];
typedef f32 (*Mtx44Ptr)[4];

typedef f32 ROMtx[4][3];
typedef f32 (*ROMtxPtr)[4];

typedef struct {
    u32 numMtx;
    MtxPtr stackBase;
    MtxPtr stackPtr;
} MTXStack;

#define MTXDegToRad(d) (d * 0.01745329252f)
#define MTXRadToDeg(r) (r * 57.29577951f)

// MTX
// C version
void C_MTXIdentity(Mtx m);

// PS version
void PSMTXIdentity(Mtx m);
void PSMTXCopy(const Mtx src, Mtx dst);
void PSMTXConcat(const Mtx a, const Mtx b, Mtx ab);
void PSMTXTranspose(const Mtx src, Mtx xPose);
u32 PSMTXInverse(const Mtx src, Mtx inv);
void PSMTXRotRad(Mtx m, char axis, f32 rad);
void PSMTXRotTrig(Mtx m, char axis, f32 sinA, f32 cosA);
void PSMTXRotAxisRad(Mtx m, const Vec* axis, f32 rad);
void PSMTXTrans(Mtx m, f32 xT, f32 yT, f32 zT);
void PSMTXScale(Mtx m, f32 xS, f32 yS, f32 zS);
void PSMTXScaleApply(const Mtx src, Mtx dst, f32 xS, f32 yS, f32 zS);
void PSMTXQuat(Mtx m, const Quaternion* q);

#define MTXIdentity   PSMTXIdentity
#define MTXCopy       PSMTXCopy
#define MTXConcat     PSMTXConcat
#define MTXTranspose  PSMTXTranspose
#define MTXInverse    PSMTXInverse
#define MTXRotRad     PSMTXRotRad
#define MTXRotTrig    PSMTXRotTrig
#define MTXRotAxisRad PSMTXRotRad
#define MTXTrans      PSMTXTrans
#define MTXScale      PSMTXScale
#define MTXQuat       PSMTXQuat

// C versions only
void C_MTXLookAt(Mtx m, const Point3d* camPos, const Vec* camUp, const Point3d* target);
void C_MTXLightFrustum(Mtx m, f32 t, f32 b, f32 l, f32 r, f32 n, f32 scaleS, f32 scaleT, f32 transS, f32 transT);
void C_MTXLightPerspective(Mtx m, f32 fovY, f32 aspect, f32 scaleS, f32 scaleT, f32 transS, f32 transT);
void C_MTXLightOrtho(Mtx m, f32 t, f32 b, f32 l, f32 r, f32 scaleS, f32 scaleT, f32 transS, f32 transT);

#define MTXLookAt           C_MTXLookAt
#define MTXLightFrustum     C_MTXLightFrustum
#define MTXLightPerspective C_MTXLightPerspective
#define MTXLightOrtho       C_MTXLightOrtho

// MTXVEC
void PSMTXMultVec(const Mtx m, const Vec* src, Vec* dst);
void PSMTXMultVecSR(const Mtx m, const Vec* src, Vec* dst);

#define MTXMultVec        PSMTXMultVec
#define MTXMultVecSR      PSMTXMultVecSR

// MTX44
void C_MTXFrustum(Mtx44 m, f32 t, f32 b, f32 l, f32 r, f32 n, f32 f);
void C_MTXOrtho(Mtx44 m, f32 t, f32 b, f32 l, f32 r, f32 n, f32 f);

#define MTXFrustum     C_MTXFrustum
#define MTXOrtho       C_MTXOrtho

// PSMTX
void PSMTXReorder(const Mtx src, ROMtx dest);

// VEC
// PS versions
void PSVECAdd(const Vec* a, const Vec* b, Vec* ab);
void PSVECSubtract(const Vec* a, const Vec* b, Vec* a_b);
void PSVECScale(const Vec* src, Vec* dst, f32 scale);
void PSVECNormalize(const Vec* src, Vec* dst);
f32 PSVECSquareMag(const Vec* v);
f32 PSVECMag(const Vec* v);
f32 PSVECDotProduct(const Vec* a, const Vec* b);
void PSVECCrossProduct(const Vec* a, const Vec* b, Vec* axb);
f32 PSVECSquareDistance(const Vec* a, const Vec* b);
f32 PSVECDistance(const Vec* a, const Vec* b);

#define VECAdd            PSVECAdd
#define VECSubtract       PSVECSubtract
#define VECScale          PSVECScale
#define VECNormalize      PSVECNormalize
#define VECSquareMag      PSVECSquareMag
#define VECMag            PSVECMag
#define VECDotProduct     PSVECDotProduct
#define VECCrossProduct   PSVECCrossProduct
#define VECSquareDistance PSVECSquareDistance
#define VECDistance       PSVECDistance

void C_VECHalfAngle(const Vec* a, const Vec* b, Vec* half);

#define VECHalfAngle C_VECHalfAngle

// QUAT
// PS versions
void PSQUATMultiply(const Quaternion* p, const Quaternion* q, Quaternion* pq);
f32 PSQUATDotProduct(const Quaternion* p, const Quaternion* q);

#define QUATMultiply   PSQUATMultiply
#define QUATDotProduct PSQUATDotProduct

// C versions only
void C_QUATRotAxisRad(Quaternion* r, const Vec* axis, f32 rad);

#define QUATRotAxisRad  C_QUATRotAxisRad

#ifdef __cplusplus
}
#endif

#endif
