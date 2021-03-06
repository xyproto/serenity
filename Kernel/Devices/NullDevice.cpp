/*
 * Copyright (c) 2018-2020, Andreas Kling <kling@serenityos.org>
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
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include "NullDevice.h"
#include <AK/Singleton.h>
#include <AK/StdLibExtras.h>

namespace Kernel {

static AK::Singleton<NullDevice> s_the;

void NullDevice::initialize()
{
    s_the.ensure_instance();
}

NullDevice& NullDevice::the()
{
    return *s_the;
}

NullDevice::NullDevice()
    : CharacterDevice(1, 3)
{
}

NullDevice::~NullDevice()
{
}

bool NullDevice::can_read(const FileDescription&, size_t) const
{
    return true;
}

KResultOr<size_t> NullDevice::read(FileDescription&, size_t, UserOrKernelBuffer&, size_t)
{
    return 0;
}

KResultOr<size_t> NullDevice::write(FileDescription&, size_t, const UserOrKernelBuffer&, size_t buffer_size)
{
    return min(static_cast<size_t>(PAGE_SIZE), buffer_size);
}

}
