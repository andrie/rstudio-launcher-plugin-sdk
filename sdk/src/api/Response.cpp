/*
 * Response.cpp
 *
 * Copyright (C) 2019 by RStudio, Inc.
 *
 * Unless you have received this program directly from RStudio pursuant to the terms of a commercial license agreement
 * with RStudio, then this program is licensed to you under the following terms:
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated
 * documentation files (the "Software"), to deal in the Software without restriction, including without limitation the
 * rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the
 * Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
 * WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
 * COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR
 * OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 */

#include <api/Response.hpp>

#include <atomic>

#include <json/Json.hpp>
#include "Constants.hpp"

namespace rstudio {
namespace launcher_plugins {
namespace api {

// Response ============================================================================================================
struct Response::Impl
{
   /**
    * @brief Constructor.
    *
    * @param in_responseType    The type of the response.
    * @param in_requestId       The ID of the request for which this response is being sent.
    */
   Impl(Type in_responseType, uint64_t in_requestId) :
      ResponseType(static_cast<int>(in_responseType)),
      RequestId(in_requestId),
      ResponseId(NEXT_RESPONSE_ID.fetch_add(1))
   {
   }

   /** Global atomic value to keep track of all response IDs used so far. */
   static std::atomic_uint64_t NEXT_RESPONSE_ID;

   /** The type of the response. */
   const int ResponseType;

   /** The ID of the request for which this response is being sent. */
   const uint64_t RequestId;

   /** The ID of this response. */
   const uint64_t ResponseId;
};

std::atomic_uint64_t Response::Impl::NEXT_RESPONSE_ID { 0 };

PRIVATE_IMPL_DELETER_IMPL(Response)

json::Object Response::asJson() const
{
   json::Object jsonObject;
   jsonObject.insert(FIELD_MESSAGE_TYPE, json::Value(m_responseImpl->ResponseType));
   jsonObject.insert(FIELD_REQUEST_ID, json::Value(m_responseImpl->RequestId));
   jsonObject.insert(FIELD_RESPONSE_ID, json::Value(m_responseImpl->ResponseId));

   return asJson(jsonObject);
}

Response::Response(Type in_responseType, uint64_t in_requestId) :
   m_responseImpl(new Impl(in_responseType, in_requestId))
{
}

// Bootstrap Response ==================================================================================================
BootstrapResponse::BootstrapResponse(uint64_t in_requestId) :
   Response(Type::BOOTSTRAP, in_requestId)
{
}

json::Object BootstrapResponse::asJson(json::Object in_jsonObject) const
{
   json::Object version;
   version.insert(FIELD_VERSION_MAJOR, json::Value(API_VERSION_MAJOR));
   version.insert(FIELD_VERSION_MINOR, json::Value(API_VERSION_MINOR));
   version.insert(FIELD_VERSION_PATCH, json::Value(API_VERSION_PATCH));

   in_jsonObject.insert(FIELD_VERSION, version);
   return in_jsonObject;
}

} // namespace api
} // namespace launcher_plugins
} // namespace rstudio
