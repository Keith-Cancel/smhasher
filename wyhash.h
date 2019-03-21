/*Author: Wang Yi <godspeed_china@yeah.net>*/
#ifndef wyhash_included
#define wyhash_included
#define wyhash_version	20190321
#if defined(_MSC_VER) && defined(_M_X64)
#include <intrin.h>
#pragma intrinsic(_umul128)
#endif
const	unsigned long long	_wyp0=0x60bee2bee120fc15ull,	_wyp1=0xa3b195354a39b70dull,	_wyp2=0x1b03738712fad5c9ull;
const	unsigned long long	_wyp3=0xd985068bc5439bd7ull,	_wyp4=0x897f236fb004a8e7ull,	_wyp5=0xc104aa67c96b7d55ull;
static	inline	unsigned long long	_wymum(unsigned long long	A,	unsigned long long	B){
#ifdef __SIZEOF_INT128__
	__uint128_t	r=A;	r*=B;	return	(r>>64)^r;
#elif	defined(_MSC_VER) && defined(_M_X64)
	A=_umul128(A, B, &B);	return	A^B;
#else
	unsigned long long	ha=A>>32,	hb=B>>32,	la=(unsigned int)A,	lb=(unsigned int)B,	hi, lo;
	unsigned long long	rh=ha*hb,	rm0=ha*lb,	rm1=hb*la,	rl=la*lb,	t=rl+(rm0<<32),	c=t<rl;
	lo=t+(rm1<<32);	c+=lo<t;	hi=rh+(rm0>>32)+(rm1>>32)+c;
	return hi^lo;
#endif
}
#include	<string.h>
static	inline	unsigned long long	_wyr08(const	unsigned char	*p){	unsigned char v;	memcpy(&v,	p,	1);	return	v;	}
static	inline	unsigned long long	_wyr16(const	unsigned char	*p){	unsigned short v;	memcpy(&v,	p,	2);	return	v;	}
static	inline	unsigned long long	_wyr32(const	unsigned char	*p){	unsigned int v;	memcpy(&v,	p,	4);	return	v;	}
static	inline	unsigned long long	_wyr64(const	unsigned char	*p){	unsigned long long v;	memcpy(&v,	p,	8);	return	v;	}
#define __wyr64(p)	((_wyr32(p)<<32)|_wyr32(p+4))
static	inline	unsigned long long	wyhash(const void* key,	unsigned long long	len, unsigned long long	seed){
	const	unsigned char	*p=(const	unsigned char*)key;	unsigned long long i;
	for(i=0,	seed^=_wyp0;	i+32<=len;	i+=32,	p+=32)	seed=_wymum(seed,	_wymum(_wyr64(p)^_wyp1,_wyr64(p+8)^_wyp2)+_wymum(_wyr64(p+16)^_wyp3,_wyr64(p+24)^_wyp4));
	switch(len&31){
	case	1:	seed=_wymum(seed,_wyr08(p)^_wyp1);	break;
	case	2:	seed=_wymum(seed,_wyr16(p)^_wyp1);	break;
	case	3:	seed=_wymum(seed,((_wyr16(p)<<8)|_wyr08(p+2))^_wyp1);	break;
	case	4:	seed=_wymum(seed,_wyr32(p)^_wyp1);	break;
	case	5:	seed=_wymum(seed,((_wyr32(p)<<8)|_wyr08(p+4))^_wyp1);	break;
	case	6:	seed=_wymum(seed,((_wyr32(p)<<16)|_wyr16(p+4))^_wyp1);	break;
	case	7:	seed=_wymum(seed,((_wyr32(p)<<24)|(_wyr16(p+4)<<8)|_wyr08(p+6))^_wyp1);	break;
	case	8:	seed=_wymum(seed,__wyr64(p)^_wyp1);	break;
	case	9:	seed=_wymum(__wyr64(p)^seed,_wyr08(p+8)^_wyp2);	break;
	case	10:	seed=_wymum(__wyr64(p)^seed,_wyr16(p+8)^_wyp2);	break;
	case	11:	seed=_wymum(__wyr64(p)^seed,((_wyr16(p+8)<<8)|_wyr08(p+8+2))^_wyp2);	break;
	case	12:	seed=_wymum(__wyr64(p)^seed,_wyr32(p+8)^_wyp2);	break;
	case	13:	seed=_wymum(__wyr64(p)^seed,((_wyr32(p+8)<<8)|_wyr08(p+8+4))^_wyp2);	break;
	case	14:	seed=_wymum(__wyr64(p)^seed,((_wyr32(p+8)<<16)|_wyr16(p+8+4))^_wyp2);	break;
	case	15:	seed=_wymum(__wyr64(p)^seed,((_wyr32(p+8)<<24)|(_wyr16(p+8+4)<<8)|_wyr08(p+8+6))^_wyp2);	break;
	case	16:	seed=_wymum(__wyr64(p)^seed,__wyr64(p+8)^_wyp2);	break;
	case	17:	seed=_wymum(__wyr64(p)^seed,__wyr64(p+8)^_wyp2)^_wymum(seed,_wyr08(p+16)^_wyp3);	break;
	case	18:	seed=_wymum(__wyr64(p)^seed,__wyr64(p+8)^_wyp2)^_wymum(seed,_wyr16(p+16)^_wyp3);	break;
	case	19:	seed=_wymum(__wyr64(p)^seed,__wyr64(p+8)^_wyp2)^_wymum(seed,((_wyr16(p+16)<<8)|_wyr08(p+16+2))^_wyp3);	break;
	case	20:	seed=_wymum(__wyr64(p)^seed,__wyr64(p+8)^_wyp2)^_wymum(seed,_wyr32(p+16)^_wyp3);	break;
	case	21:	seed=_wymum(__wyr64(p)^seed,__wyr64(p+8)^_wyp2)^_wymum(seed,((_wyr32(p+16)<<8)|_wyr08(p+16+4))^_wyp3);	break;
	case	22:	seed=_wymum(__wyr64(p)^seed,__wyr64(p+8)^_wyp2)^_wymum(seed,((_wyr32(p+16)<<16)|_wyr16(p+16+4))^_wyp3);	break;
	case	23:	seed=_wymum(__wyr64(p)^seed,__wyr64(p+8)^_wyp2)^_wymum(seed,((_wyr32(p+16)<<24)|(_wyr16(p+16+4)<<8)|_wyr08(p+16+6))^_wyp3);	break;
	case	24:	seed=_wymum(__wyr64(p)^seed,__wyr64(p+8)^_wyp2)^_wymum(seed,__wyr64(p+16)^_wyp3);	break;
	case	25:	seed=_wymum(__wyr64(p)^seed,__wyr64(p+8)^_wyp2)^_wymum(__wyr64(p+16)^seed,_wyr08(p+24)^_wyp4);	break;
	case	26:	seed=_wymum(__wyr64(p)^seed,__wyr64(p+8)^_wyp2)^_wymum(__wyr64(p+16)^seed,_wyr16(p+24)^_wyp4);	break;
	case	27:	seed=_wymum(__wyr64(p)^seed,__wyr64(p+8)^_wyp2)^_wymum(__wyr64(p+16)^seed,((_wyr16(p+24)<<8)|_wyr08(p+24+2))^_wyp4);	break;
	case	28:	seed=_wymum(__wyr64(p)^seed,__wyr64(p+8)^_wyp2)^_wymum(__wyr64(p+16)^seed,_wyr32(p+24)^_wyp4);	break;
	case	29:	seed=_wymum(__wyr64(p)^seed,__wyr64(p+8)^_wyp2)^_wymum(__wyr64(p+16)^seed,((_wyr32(p+24)<<8)|_wyr08(p+24+4))^_wyp4);	break;
	case	30:	seed=_wymum(__wyr64(p)^seed,__wyr64(p+8)^_wyp2)^_wymum(__wyr64(p+16)^seed,((_wyr32(p+24)<<16)|_wyr16(p+24+4))^_wyp4);	break;
	case	31:	seed=_wymum(__wyr64(p)^seed,__wyr64(p+8)^_wyp2)^_wymum(__wyr64(p+16)^seed,((_wyr32(p+24)<<24)|(_wyr16(p+24+4)<<8)|_wyr08(p+24+6))^_wyp4);	break;
	}
	return	_wymum(seed,	len^_wyp5);
}
static	inline	unsigned long long	wyhash64(unsigned long long	A, unsigned long long	B){	return	_wymum(_wymum(A^_wyp0,	B^_wyp1),	_wyp2);	}
static	inline	unsigned long long	wyrng(unsigned long long *s){	*s+=_wyp0;	return	_wymum(*s^_wyp1,*s);	}
static	inline	double	wyrngu01(unsigned long long	*seed){	unsigned long long	r=(wyrng(seed)&0xfffffffffffffull)|0x3ff0000000000000ull;	return	*((double*)&r)-1.0;		}
#endif
