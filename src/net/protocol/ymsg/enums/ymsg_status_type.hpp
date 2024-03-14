// MIT License
//
// Copyright (c) 2024 r0neko, pushfq
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#pragma once

#include <cstdint>

namespace net {
    namespace protocol {
        enum YES_STATUS_ : std::int32_t {
            YES_STATUS_DUPLICATE = (std::int32_t) -3,
            YES_STATUS_ERR = (std::int32_t) -1,
            YES_STATUS_OK = 0,
            YES_STATUS_NOTIFY = 1,
            YES_STATUS_NOT_AVAILABLE = 2,
            YES_STATUS_NEW_BUDDYOF = 3,
            YES_STATUS_PARTIAL_LIST = 5,
            YES_STATUS_SAVED_MESG = 6,
            YES_STATUS_BUDDYOF_DENIED = 7,
            YES_STATUS_INVALID_USER = 8,
            YES_STATUS_CHUNKING = 9,
            YES_STATUS_INVITED = 11,
            YES_STATUS_DONT_DISTURB = 12,
            YES_STATUS_DISTURB_ME = 13,
            YES_STATUS_NEW_BUDDYOF_AUTH = 15,
            YES_STATUS_WEB_MESG = 16,
            YES_STATUS_ACK = 18,
            YES_STATUS_RELOGIN = 19,
            YES_STATUS_SPECIFIC_SNDR = 22,
            YES_STATUS_INCOMP_VERSION = 24,
            YES_STATUS_REQUEST = 26,
            YES_STATUS_SMS_CARRIER = 29,
            YES_STATUS_ISGROUP_IM = 33,
            YES_STATUS_PRELOGIN_SUCCEEDED = 100,
            YES_STATUS_SERVE = 101,
            YES_STATUS_FD_CONNECT_SUCCESS = 102,
            YES_STATUS_CMD_SENT_ACK = 1000,
            YES_STATUS_KNOWN_USER = 0x5A55AA56,
            YES_STATUS_UNKNOWN_USER = 0x5A55AA55
        };  // enum YES_STATUS_
    }  // namespace protocol
}  // namespace net