// Copyright 2020 The Tint Authors.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
#include "src/reader/wgsl/parser_impl_test_helper.h"

namespace tint {
namespace reader {
namespace wgsl {

ParserImplTest::ParserImplTest() = default;

ParserImplTest::~ParserImplTest() = default;

void ParserImplTest::SetUp() {
  ctx_.Reset();
}

void ParserImplTest::TearDown() {
  impl_ = nullptr;
}

}  // namespace wgsl
}  // namespace reader
}  // namespace tint
