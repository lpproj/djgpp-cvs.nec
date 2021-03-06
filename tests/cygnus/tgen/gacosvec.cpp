// ------------------------------------------------------
// genacosv - generates test vectors for acos() & acosf()
// ------------------------------------------------------
#include <errno.h>
#include <float.h>
#include <math.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <qfloat.h>
#include "test.h"
#include "genmathv.h"

/* INDENT OFF */

LOOP_LIMITS  Ctls[] =
    {	/* Start   Step    Stop  */
	{ -1,	  +0.003125,   -.95 },
	{ -.875,   +0.0625, -0.5625 },
	{ -.5625, +0.03125, -0.4375 },
	{ -.4375, +0.0625,  +0.0    },
	{ +0.0 ,  +0.0625,  +0.4375 },
	{ +.4375, +0.03125, +0.5625 },
	{ +.5625, +0.0625,  +0.875  },
	{ +.95,	  +0.003125, 63./64.},
	{ +63./64.,1./128., +1.0    },
    };

/* INDENT ON */

#define	DBL_MEAS_BIT	62
#define	FLT_MEAS_BIT	34

// -------------------------------------------------------------------
// GenDblVector - Generates Test Vectors for Double Precision Function
// -------------------------------------------------------------------
void
GenDblVector(const char *Name)
{
    unsigned J;
    double   K;

    volatile  double  Argument, Expected;

    // Redirect stdout to disk file

    AssignOutputFile(Name);

    // Generate first two lines of file

    GEN_FIRST_TWO_LINES

    // Generate vectors

    for (J = 0; J < (sizeof(Ctls) / sizeof(Ctls[0])); ++J)
    {
	for (K = Ctls[J].Start; K <= Ctls[J].Stop; K += Ctls[J].Step)
	{
	    Argument = K;
	    Expected = xtod(xacos(Argument));

	    WriteVector(DBL_MEAS_BIT, Argument, Expected, __NO_ERROR_);
	}
    }

    // --------------
    // SPECIAL VALUES
    // --------------

    Argument = -1.25;
    Expected = nan("");
    _fpreset();
    WriteVector(DBL_MEAS_BIT, Argument, Expected, EDOM);

    Argument = +1.25;
    Expected = nan("");
    _fpreset();
    WriteVector(DBL_MEAS_BIT, Argument, Expected, EDOM);

    Argument = nan("");
    Expected = nan("");
    _fpreset();
    WriteVector(DBL_MEAS_BIT, Argument, Expected, __NO_ERROR_);

    Argument = infinity();
    Expected = nan("");
    _fpreset();
    WriteVector(DBL_MEAS_BIT, Argument, Expected, EDOM);

    volatile double  EpsNeg = pow(2, -53);
    Argument = 1-EpsNeg;

    Expected = xtod(xacos(Argument));
    _fpreset();
    WriteVector(DBL_MEAS_BIT, Argument, Expected, __NO_ERROR_);

    // Generate last lines (code lines) of file

    printf("0,};\nvoid\ntest_%s(int m)\t{ run_vector_1(m, %s_vec,(char *)"
	"(%s),\"%s\",\"dd\");}\n", Name, Name, Name, Name);
}
// ------------------------------------------------------------------
// GenFltVector - Generates Test Vectors for Float Precision Function
// ------------------------------------------------------------------
void
GenFltVector(const char *Name)
{
    unsigned J;
    float   K;

    volatile  float  Argument, Expected;

    // Redirect stdout to disk file

    AssignOutputFile(Name);

    // Generate first two lines of file

    GEN_FIRST_TWO_LINES

    // Generate vectors

    for (J = 0; J < (sizeof(Ctls) / sizeof(Ctls[0])); ++J)
    {
	for (K = Ctls[J].Start; K <= Ctls[J].Stop; K += Ctls[J].Step)
	{
	    Argument = K;
	    Expected = xtof(xacos(Argument));

	    WriteVector(FLT_MEAS_BIT, Argument, Expected, __NO_ERROR_);
	}
    }

    // --------------
    // SPECIAL VALUES
    // --------------

    Argument = -1.25;
    Expected = nan("");
    _fpreset();
    WriteVector(FLT_MEAS_BIT, Argument, Expected, EDOM);

    Argument = +1.25;
    Expected = nan("");
    _fpreset();
    WriteVector(FLT_MEAS_BIT, Argument, Expected, EDOM);

    Argument = nan("");
    Expected = nan("");
    _fpreset();
    WriteVector(FLT_MEAS_BIT, Argument, Expected, __NO_ERROR_);

    Argument = infinityf();
    Expected = nan("");
    _fpreset();
    WriteVector(FLT_MEAS_BIT, Argument, Expected, EDOM);

    volatile float  EpsNeg = pow(2, -24);
    Argument = 1-EpsNeg;
    __ieee_float_shape_type MyArg;
    MyArg.value = Argument;
    //fprintf(stderr, "1 - %g = %08lx\n", EpsNeg, MyArg.p1);
    Expected = xtof(xacos(Argument));
    _fpreset();
    WriteVector(FLT_MEAS_BIT, Argument, Expected, __NO_ERROR_);

    // Generate last lines (code lines) of file

    printf("0,};\nvoid\ntest_%s(int m)\t{ run_vector_1(m, %s_vec,(char *)"
	"(%s),\"%s\",\"ff\");}\n", Name, Name, Name, Name);
}
int
main()
{
    _LIB_VERSION = _POSIX_;

    signal(SIGINT, exit);
    GenDblVector("acos");
    GenFltVector("acosf");
    exit(0);
}
