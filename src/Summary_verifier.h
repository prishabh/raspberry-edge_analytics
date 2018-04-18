#ifndef SUMMARY_VERIFIER_H
#define SUMMARY_VERIFIER_H

/* Generated by flatcc 0.5.1-pre FlatBuffers schema compiler for C by dvide.com */

#ifndef SUMMARY_READER_H
#include "Summary_reader.h"
#endif
#include "flatcc/flatcc_verifier.h"
#include "flatcc/flatcc_prologue.h"

static int Test_Summary_verify_table(flatcc_table_verifier_descriptor_t *td);

static int Test_Summary_verify_table(flatcc_table_verifier_descriptor_t *td)
{
    int ret;
    if ((ret = flatcc_verify_field(td, 0, 8, 8) /* Rms */)) return ret;
    if ((ret = flatcc_verify_field(td, 1, 8, 8) /* Kurtosis */)) return ret;
    if ((ret = flatcc_verify_field(td, 2, 8, 8) /* Skewness */)) return ret;
    if ((ret = flatcc_verify_field(td, 3, 8, 8) /* Variance */)) return ret;
    if ((ret = flatcc_verify_field(td, 4, 8, 8) /* Mean */)) return ret;
    if ((ret = flatcc_verify_field(td, 5, 8, 8) /* min */)) return ret;
    if ((ret = flatcc_verify_field(td, 6, 8, 8) /* max */)) return ret;
    if ((ret = flatcc_verify_field(td, 7, 8, 8) /* count */)) return ret;
    if ((ret = flatcc_verify_field(td, 8, 8, 8) /* sumOfSquare */)) return ret;
    if ((ret = flatcc_verify_field(td, 9, 8, 8) /* Percentile_2 */)) return ret;
    if ((ret = flatcc_verify_field(td, 10, 8, 8) /* Percentile_5 */)) return ret;
    if ((ret = flatcc_verify_field(td, 11, 8, 8) /* Percentile_10 */)) return ret;
    if ((ret = flatcc_verify_field(td, 12, 8, 8) /* Percentile_20 */)) return ret;
    if ((ret = flatcc_verify_field(td, 13, 8, 8) /* Percentile_40 */)) return ret;
    if ((ret = flatcc_verify_field(td, 14, 8, 8) /* Percentile_50 */)) return ret;
    if ((ret = flatcc_verify_field(td, 15, 8, 8) /* Percentile_60 */)) return ret;
    if ((ret = flatcc_verify_field(td, 16, 8, 8) /* Percentile_80 */)) return ret;
    if ((ret = flatcc_verify_field(td, 17, 8, 8) /* Percentile_90 */)) return ret;
    if ((ret = flatcc_verify_field(td, 18, 8, 8) /* Percentile_95 */)) return ret;
    if ((ret = flatcc_verify_field(td, 19, 8, 8) /* Percentile_98 */)) return ret;
    if ((ret = flatcc_verify_field(td, 20, 8, 8) /* Percentile_99 */)) return ret;
    if ((ret = flatcc_verify_field(td, 21, 8, 8) /* Percentile_100 */)) return ret;
    if ((ret = flatcc_verify_field(td, 22, 8, 8) /* Percentile_98_2 */)) return ret;
    if ((ret = flatcc_verify_field(td, 23, 8, 8) /* Percentile_95_5 */)) return ret;
    if ((ret = flatcc_verify_field(td, 24, 8, 8) /* Percentile_95_10 */)) return ret;
    if ((ret = flatcc_verify_field(td, 25, 8, 8) /* Percentile_80_20 */)) return ret;
    if ((ret = flatcc_verify_field(td, 26, 8, 8) /* Percentile_60_40 */)) return ret;
    if ((ret = flatcc_verify_field(td, 27, 8, 8) /* Crest */)) return ret;
    return flatcc_verify_ok;
}

static inline int Test_Summary_verify_as_root(const void *buf, size_t bufsiz)
{
    return flatcc_verify_table_as_root(buf, bufsiz, Test_Summary_identifier, &Test_Summary_verify_table);
}

static inline int Test_Summary_verify_as_typed_root(const void *buf, size_t bufsiz)
{
    return flatcc_verify_table_as_root(buf, bufsiz, Test_Summary_type_identifier, &Test_Summary_verify_table);
}

static inline int Test_Summary_verify_as_root_with_identifier(const void *buf, size_t bufsiz, const char *fid)
{
    return flatcc_verify_table_as_root(buf, bufsiz, fid, &Test_Summary_verify_table);
}

static inline int Test_Summary_verify_as_root_with_type_hash(const void *buf, size_t bufsiz, flatbuffers_thash_t thash)
{
    return flatcc_verify_table_as_typed_root(buf, bufsiz, thash, &Test_Summary_verify_table);
}

#include "flatcc/flatcc_epilogue.h"
#endif /* SUMMARY_VERIFIER_H */
