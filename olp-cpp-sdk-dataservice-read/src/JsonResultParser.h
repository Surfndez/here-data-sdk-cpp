/*
 * Copyright (C) 2020 HERE Europe B.V.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 * SPDX-License-Identifier: Apache-2.0
 * License-Filename: LICENSE
 */

#pragma once

#include <sstream>
#include <string>
#include <utility>

#include <olp/core/client/ApiError.h>
#include <olp/core/generated/parser/JsonParser.h>
#include <olp/core/logging/Log.h>

namespace olp {
namespace parser {

template <typename OutputResult,
          typename ParsingType = typename OutputResult::ResultType,
          typename... AdditionalArgs>
typename std::enable_if<
    std::is_constructible<ParsingType, ParsingType, AdditionalArgs...>::value,
    OutputResult>::type
parse_result(std::stringstream& json_stream, const AdditionalArgs&... args) {
  bool res = true;
  auto obj = parse<ParsingType>(json_stream, res);

  if (res) {
    return ParsingType(std::move(obj), args...);
  } else {
    return {
        client::ApiError(client::ErrorCode::Unknown, "Fail parsing response.")};
  }
}

template <typename OutputResult,
          typename ParsingType = typename OutputResult::ResultType,
          typename... AdditionalArgs>
typename std::enable_if<
    !std::is_constructible<ParsingType, ParsingType, AdditionalArgs...>::value,
    OutputResult>::type
parse_result(std::stringstream& json_stream, const AdditionalArgs&... args) {
  bool res = true;
  auto obj = parse<ParsingType>(json_stream, res);

  if (res) {
    return OutputResult({std::move(obj), args...});
  } else {
    return {
        client::ApiError(client::ErrorCode::Unknown, "Fail parsing response.")};
  }
}

}  // namespace parser
}  // namespace olp
