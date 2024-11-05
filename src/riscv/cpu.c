/*
 * Copyright © 2022, VideoLAN and dav1d authors
 * Copyright © 2022, Nathan Egge
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice, this
 *    list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include "config.h"

#include "common/attributes.h"

#include "src/cpu.h"
#include "src/riscv/cpu.h"

#if HAVE_GETAUXVAL
#include <sys/auxv.h>

#define HWCAP_RVV (1 << ('v' - 'a'))

#endif

int dav1d_has_compliant_rvv(void);

COLD unsigned dav1d_get_cpu_flags_riscv(void) {
    unsigned flags = dav1d_get_default_cpu_flags();
#if HAVE_GETAUXVAL
    unsigned long hw_cap = dav1d_getauxval(AT_HWCAP);
    flags |= (hw_cap & HWCAP_RVV) && dav1d_has_compliant_rvv() ? DAV1D_RISCV_CPU_FLAG_V : 0;
#endif

    return flags;
}
