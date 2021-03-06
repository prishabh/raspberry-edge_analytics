#ifndef SUMMARY_READER_H
#define SUMMARY_READER_H

/* Generated by flatcc 0.5.1-pre FlatBuffers schema compiler for C by dvide.com */

#ifndef FLATBUFFERS_COMMON_READER_H
#include "flatbuffers_common_reader.h"
#endif
#include "flatcc/flatcc_flatbuffers.h"
#ifndef __alignas_is_defined
#include <stdalign.h>
#endif
#include "flatcc/flatcc_prologue.h"
#ifndef flatbuffers_identifier
#define flatbuffers_identifier 0
#endif
#ifndef flatbuffers_extension
#define flatbuffers_extension ".bin"
#endif


typedef const struct Test_Summary_table *Test_Summary_table_t;
typedef const flatbuffers_uoffset_t *Test_Summary_vec_t;
typedef flatbuffers_uoffset_t *Test_Summary_mutable_vec_t;
#ifndef Test_Summary_identifier
#define Test_Summary_identifier flatbuffers_identifier
#endif
#define Test_Summary_type_hash ((flatbuffers_thash_t)0xb040e4af)
#define Test_Summary_type_identifier "\xaf\xe4\x40\xb0"



struct Test_Summary_table { uint8_t unused__; };

static inline size_t Test_Summary_vec_len(Test_Summary_vec_t vec)
__flatbuffers_vec_len(vec)
static inline Test_Summary_table_t Test_Summary_vec_at(Test_Summary_vec_t vec, size_t i)
__flatbuffers_offset_vec_at(Test_Summary_table_t, vec, i, 0)
__flatbuffers_table_as_root(Test_Summary)

__flatbuffers_define_scalar_field(0, Test_Summary, Rms, flatbuffers_double, double, 0.000000)
__flatbuffers_define_scalar_field(1, Test_Summary, Kurtosis, flatbuffers_double, double, 0.000000)
__flatbuffers_define_scalar_field(2, Test_Summary, Skewness, flatbuffers_double, double, 0.000000)
__flatbuffers_define_scalar_field(3, Test_Summary, Variance, flatbuffers_double, double, 0.000000)
__flatbuffers_define_scalar_field(4, Test_Summary, Mean, flatbuffers_double, double, 0.000000)
__flatbuffers_define_scalar_field(5, Test_Summary, min, flatbuffers_double, double, 0.000000)
__flatbuffers_define_scalar_field(6, Test_Summary, max, flatbuffers_double, double, 0.000000)
__flatbuffers_define_scalar_field(7, Test_Summary, count, flatbuffers_double, double, 0.000000)
__flatbuffers_define_scalar_field(8, Test_Summary, sumOfSquare, flatbuffers_double, double, 0.000000)
__flatbuffers_define_scalar_field(9, Test_Summary, Percentile_2, flatbuffers_double, double, 0.000000)
__flatbuffers_define_scalar_field(10, Test_Summary, Percentile_5, flatbuffers_double, double, 0.000000)
__flatbuffers_define_scalar_field(11, Test_Summary, Percentile_10, flatbuffers_double, double, 0.000000)
__flatbuffers_define_scalar_field(12, Test_Summary, Percentile_20, flatbuffers_double, double, 0.000000)
__flatbuffers_define_scalar_field(13, Test_Summary, Percentile_40, flatbuffers_double, double, 0.000000)
__flatbuffers_define_scalar_field(14, Test_Summary, Percentile_50, flatbuffers_double, double, 0.000000)
__flatbuffers_define_scalar_field(15, Test_Summary, Percentile_60, flatbuffers_double, double, 0.000000)
__flatbuffers_define_scalar_field(16, Test_Summary, Percentile_80, flatbuffers_double, double, 0.000000)
__flatbuffers_define_scalar_field(17, Test_Summary, Percentile_90, flatbuffers_double, double, 0.000000)
__flatbuffers_define_scalar_field(18, Test_Summary, Percentile_95, flatbuffers_double, double, 0.000000)
__flatbuffers_define_scalar_field(19, Test_Summary, Percentile_98, flatbuffers_double, double, 0.000000)
__flatbuffers_define_scalar_field(20, Test_Summary, Percentile_99, flatbuffers_double, double, 0.000000)
__flatbuffers_define_scalar_field(21, Test_Summary, Percentile_100, flatbuffers_double, double, 0.000000)
__flatbuffers_define_scalar_field(22, Test_Summary, Percentile_98_2, flatbuffers_double, double, 0.000000)
__flatbuffers_define_scalar_field(23, Test_Summary, Percentile_95_5, flatbuffers_double, double, 0.000000)
__flatbuffers_define_scalar_field(24, Test_Summary, Percentile_95_10, flatbuffers_double, double, 0.000000)
__flatbuffers_define_scalar_field(25, Test_Summary, Percentile_80_20, flatbuffers_double, double, 0.000000)
__flatbuffers_define_scalar_field(26, Test_Summary, Percentile_60_40, flatbuffers_double, double, 0.000000)
__flatbuffers_define_scalar_field(27, Test_Summary, Crest, flatbuffers_double, double, 0.000000)

#include "flatcc/flatcc_epilogue.h"
#endif /* SUMMARY_READER_H */
