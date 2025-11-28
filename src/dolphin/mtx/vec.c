#include <dolphin.h>
#include <dolphin/mtx.h>

asm void PSVECAdd(const register Vec* a, const register Vec* b, register Vec* ab) {
    psq_l f2, Vec.x(a), 0, 0
    psq_l f4, Vec.x(b), 0, 0
    ps_add f6, f2, f4
    psq_st f6, Vec.x(ab), 0, 0
    psq_l f3, Vec.z(a), 1, 0
    psq_l f5, Vec.z(b), 1, 0
    ps_add f7, f3, f5
    psq_st f7, Vec.z(ab), 1, 0
}

asm void PSVECSubtract(const register Vec* a, const register Vec* b, register Vec* a_b) {
    psq_l f2, Vec.x(a), 0, 0
    psq_l f4, Vec.x(b), 0, 0
    ps_sub f6, f2, f4
    psq_st f6, Vec.x(a_b), 0, 0
    psq_l f3, Vec.z(a), 1, 0
    psq_l f5, Vec.z(b), 1, 0
    ps_sub f7, f3, f5
    psq_st f7, Vec.z(a_b), 1, 0
}

void PSVECScale(const register Vec* src, register Vec* dst, register f32 scale) {
    register f32 vxy, vz, rxy, rz;

    asm {
        psq_l vxy, 0x0(src), 0, 0
        psq_l vz, 0x8(src), 1, 0
        ps_muls0 rxy, vxy, scale
        psq_st rxy, 0x0(dst), 0, 0
        ps_muls0 rz, vz, scale
        psq_st rz, 0x8(dst), 1, 0
    }
}

// For float ordering to kick in here correctly, this MUST be placed
// before PSVECNormalize because otherwise nothing creates 0.0f and
// any amount of unused functions does not do this any better. SMH..
void C_VECHalfAngle(const Vec* a, const Vec* b, Vec* half) {
    Vec aTmp;
    Vec bTmp;
    Vec hTmp;

    aTmp.x = -a->x;
    aTmp.y = -a->y;
    aTmp.z = -a->z;
    bTmp.x = -b->x;
    bTmp.y = -b->y;
    bTmp.z = -b->z;

    VECNormalize(&aTmp, &aTmp);
    VECNormalize(&bTmp, &bTmp);
    VECAdd(&aTmp, &bTmp, &hTmp);

    if (VECDotProduct(&hTmp, &hTmp) > 0.0f) {
        VECNormalize(&hTmp, half);
    } else {
        *half = hTmp;
    }
}

void PSVECNormalize(const register Vec* src, register Vec* unit) {
    register float c_half = 0.5f;
    register float c_three = 3.0f;
    register float v1_xy;
    register float v1_z;
    register float xx_zz;
    register float xx_yy;
    register float sqsum;
    register float rsqrt;
    register float nwork0;
    register float nwork1;

    asm {
        psq_l v1_xy, 0x0(src), 0, 0
        ps_mul xx_yy, v1_xy, v1_xy
        psq_l v1_z, 0x8(src), 1, 0
        ps_madd xx_zz, v1_z, v1_z, xx_yy
        ps_sum0 sqsum, xx_zz, v1_z, xx_yy
        frsqrte rsqrt, sqsum
        fmuls nwork0, rsqrt, rsqrt
        fmuls nwork1, rsqrt, c_half
        fnmsubs nwork0, nwork0, sqsum, c_three
        fmuls rsqrt, nwork0, nwork1
        ps_muls0 v1_xy, v1_xy, rsqrt
        psq_st v1_xy, 0x0(unit), 0, 0
        ps_muls0 v1_z, v1_z, rsqrt
        psq_st v1_z, 0x8(unit), 1, 0
    }
}

f32 PSVECSquareMag(const register Vec* v) {
    register f32 vxy, vzz, sqmag;

    asm {
        psq_l vxy, 0x0(v), 0, 0
        ps_mul vxy, vxy, vxy
        lfs vzz, 0x8(v)
        ps_madd sqmag, vzz, vzz, vxy
        ps_sum0 sqmag, sqmag, vxy, vxy
    }

    return sqmag;
}

f32 PSVECMag(const register Vec* v) {
    register f32 vxy, vzz;
    register f32 sqmag, mag, rmag;
    register f32 nwork0, nwork1;
    register f32 c_three, c_half;

    
    asm {
        psq_l vxy, 0x0(v), 0, 0
        ps_mul vxy, vxy, vxy
        lfs vzz, 0x8(v)
        ps_madd sqmag, vzz, vzz, vxy
    }

    c_half = 0.5f;

    asm {

        ps_sum0 sqmag, sqmag, vxy, vxy
        frsqrte rmag, sqmag
    }

    c_three = 3.0f;

    asm {
        fmuls nwork0, rmag, rmag
        fmuls nwork1, rmag, c_half
        fnmsubs nwork0, nwork0, sqmag, c_three
        fmuls rmag, nwork0, nwork1
        fsel rmag, rmag, rmag, sqmag
        fmuls mag, sqmag, rmag
    }

    return mag;
}

asm f32 PSVECDotProduct(const register Vec* a, const register Vec* b) {
    psq_l f2, Vec.y(a), 0, 0
    psq_l f3, Vec.y(b), 0, 0
    ps_mul f2, f2, f3
    psq_l f5, Vec.x(a), 0, 0
    psq_l f4, Vec.x(b), 0, 0
    ps_madd f3, f5, f4, f2
    ps_sum0 f1, f3, f2, f2
}

asm void PSVECCrossProduct(const register Vec* a, const register Vec* b, register Vec* axb) {
    psq_l f1, Vec.x(b), 0, 0
    lfs f2, Vec.z(a)
    psq_l f0, Vec.x(a), 0, 0
    ps_merge10 f6, f1, f1
    lfs f3, Vec.z(b)
    ps_mul f4, f1, f2
    ps_muls0 f7, f1, f0
    ps_msub f5, f0, f3, f4
    ps_msub f8, f0, f6, f7
    ps_merge11 f9, f5, f5
    ps_merge01 f10, f5, f8
    psq_st f9, Vec.x(axb), 1, 0
    ps_neg f10, f10
    psq_st f10, Vec.y(axb), 0, 0
}

f32 PSVECSquareDistance(const register Vec* a, const register Vec* b) {
    register f32 v0yz, v1yz, v0xy, v1xy, dyz, dxy;
    register f32 sqdist;

    asm {
        psq_l v0yz, 0x4(a), 0, 0
        psq_l v1yz, 0x4(b), 0, 0
        ps_sub dyz, v0yz, v1yz
        psq_l v0xy, 0x0(a), 0, 0
        psq_l v1xy, 0x0(b), 0, 0
        ps_mul dyz, dyz, dyz
        ps_sub dxy, v0xy, v1xy
        ps_madd sqdist, dxy, dxy, dyz
        ps_sum0 sqdist, sqdist, dyz, dyz
    }

    return sqdist;
}

f32 PSVECDistance(const register Vec* a, const register Vec* b) {
    register f32 v0yz, v1yz, v0xy, v1xy, dyz, dxy;
    register f32 sqdist, rdist, dist;
    register f32 nwork0, nwork1;
    register f32 c_half, c_three;

    asm {
        psq_l v0yz, 0x4(a), 0, 0
        psq_l v1yz, 0x4(b), 0, 0
        ps_sub dyz, v0yz, v1yz
        psq_l v0xy, 0x0(a), 0, 0
        psq_l v1xy, 0x0(b), 0, 0
        ps_mul dyz, dyz, dyz
        ps_sub dxy, v0xy, v1xy
    }

    c_half  = 0.5f;

    asm {
        ps_madd sqdist, dxy, dxy, dyz
        ps_sum0 sqdist, sqdist, dyz, dyz
    }

    c_three = 3.0f;

    asm {
        frsqrte rdist, sqdist
        fmuls nwork0, rdist, rdist
        fmuls nwork1, rdist, c_half
        fnmsubs nwork0, nwork0, sqdist, c_three
        fmuls rdist, nwork0, nwork1
        fsel rdist, rdist, rdist, sqdist
        fmuls dist, sqdist, rdist
    }

    return dist;
}
