/**
 *
 *  Copyright (C) 2025 Roman Pauer
 *
 *  Permission is hereby granted, free of charge, to any person obtaining a copy of
 *  this software and associated documentation files (the "Software"), to deal in
 *  the Software without restriction, including without limitation the rights to
 *  use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies
 *  of the Software, and to permit persons to whom the Software is furnished to do
 *  so, subject to the following conditions:
 *
 *  The above copyright notice and this permission notice shall be included in all
 *  copies or substantial portions of the Software.
 *
 *  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 *  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 *  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 *  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 *  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 *  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 *  SOFTWARE.
 *
 */

extern uint8_t x87_fild_int64;
extern uint8_t x87_fist_int32;
extern uint8_t x87_fistp_int16;
extern uint8_t x87_fistp_int32;
extern uint8_t x87_fptan_void;
extern uint8_t x87_fsin_void;
extern uint8_t x87_ftol_int64;
extern uint8_t x87_fabs_void;
extern uint8_t x87_fadd_float;
extern uint8_t x87_fadd_st;
extern uint8_t x87_faddp_st;
extern uint8_t x87_fchs_void;
extern uint8_t x87_fcom_float;
extern uint8_t x87_fcomp_float;
extern uint8_t x87_fdiv_float;
extern uint8_t x87_fdivp_st;
extern uint8_t x87_fdivr_float;
extern uint8_t x87_fiadd_int32;
extern uint8_t x87_fidiv_int32;
extern uint8_t x87_fild_int32;
extern uint8_t x87_fimul_int32;
extern uint8_t x87_fisub_int32;
extern uint8_t x87_fld_float;
extern uint8_t x87_fld_st;
extern uint8_t x87_fldcw_uint16;
extern uint8_t x87_fldz_void;
extern uint8_t x87_fnstcw_void;
extern uint8_t x87_fnstsw_void;
extern uint8_t x87_fmul_float;
extern uint8_t x87_fmul_st;
extern uint8_t x87_fmul_to_st;
extern uint8_t x87_fmulp_st;
extern uint8_t x87_fst_float;
extern uint8_t x87_fst_st;
extern uint8_t x87_fstp_float;
extern uint8_t x87_fstp_st;
extern uint8_t x87_fsub_float;
extern uint8_t x87_fsub_st;
extern uint8_t x87_fsubp_st;
extern uint8_t x87_fsubr_float;
extern uint8_t x87_fucom_st;
extern uint8_t x87_fucomp_st;
extern uint8_t x87_fxch_st;

const static struct
{
    const char *name;
    uint8_t *value;
} symbol_table[] = {
    {"x87_fild_int64", &x87_fild_int64},
    {"x87_fist_int32", &x87_fist_int32},
    {"x87_fistp_int16", &x87_fistp_int16},
    {"x87_fistp_int32", &x87_fistp_int32},
    {"x87_fptan_void", &x87_fptan_void},
    {"x87_fsin_void", &x87_fsin_void},
    {"x87_ftol_int64", &x87_ftol_int64},
    {"x87_fabs_void", &x87_fabs_void},
    {"x87_fadd_float", &x87_fadd_float},
    {"x87_fadd_st", &x87_fadd_st},
    {"x87_faddp_st", &x87_faddp_st},
    {"x87_fchs_void", &x87_fchs_void},
    {"x87_fcom_float", &x87_fcom_float},
    {"x87_fcomp_float", &x87_fcomp_float},
    {"x87_fdiv_float", &x87_fdiv_float},
    {"x87_fdivp_st", &x87_fdivp_st},
    {"x87_fdivr_float", &x87_fdivr_float},
    {"x87_fiadd_int32", &x87_fiadd_int32},
    {"x87_fidiv_int32", &x87_fidiv_int32},
    {"x87_fild_int32", &x87_fild_int32},
    {"x87_fimul_int32", &x87_fimul_int32},
    {"x87_fisub_int32", &x87_fisub_int32},
    {"x87_fld_float", &x87_fld_float},
    {"x87_fld_st", &x87_fld_st},
    {"x87_fldcw_uint16", &x87_fldcw_uint16},
    {"x87_fldz_void", &x87_fldz_void},
    {"x87_fnstcw_void", &x87_fnstcw_void},
    {"x87_fnstsw_void", &x87_fnstsw_void},
    {"x87_fmul_float", &x87_fmul_float},
    {"x87_fmul_st", &x87_fmul_st},
    {"x87_fmul_to_st", &x87_fmul_to_st},
    {"x87_fmulp_st", &x87_fmulp_st},
    {"x87_fst_float", &x87_fst_float},
    {"x87_fst_st", &x87_fst_st},
    {"x87_fstp_float", &x87_fstp_float},
    {"x87_fstp_st", &x87_fstp_st},
    {"x87_fsub_float", &x87_fsub_float},
    {"x87_fsub_st", &x87_fsub_st},
    {"x87_fsubp_st", &x87_fsubp_st},
    {"x87_fsubr_float", &x87_fsubr_float},
    {"x87_fucom_st", &x87_fucom_st},
    {"x87_fucomp_st", &x87_fucomp_st},
    {"x87_fxch_st", &x87_fxch_st},
};

