// MIT License
//
// Copyright (c) 2024 r0neko
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

#ifndef YMSG_FRAME_FIELD_GUARD
#define YMSG_FRAME_FIELD_GUARD

#include <string>
#include <vector>

#include <ymsg/ymsg_frame_field_type.hpp>

namespace ymsg {
    struct YMSGFrameField {
        ymsg::YMSG_FLD_ key;
        std::string value;

        YMSGFrameField(ymsg::YMSG_FLD_ _key, std::string _value);

        std::vector<uint8_t> serialize();
    };

    using YMSGFrameFieldCollection = std::vector<YMSGFrameField>;
}

#endif //YMSG_FRAME_FIELD_GUARD
